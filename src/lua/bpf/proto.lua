--[[
Copyright 2016 Marek Vavrusa <mvavrusa@cloudflare.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
]]
local ffi = require('ffi')
local BPF = ffi.typeof('struct bpf')

ffi.cdef [[
struct sk_buff {
	uint32_t len;
	uint32_t pkt_type;
	uint32_t mark;
	uint32_t queue_mapping;
	uint32_t protocol;
	uint32_t vlan_present;
	uint32_t vlan_tci;
	uint32_t vlan_proto;
	uint32_t priority;
	uint32_t ingress_ifindex;
	uint32_t ifindex;
	uint32_t tc_index;
	uint32_t cb[5];
	uint32_t hash;
	uint32_t tc_classid;
	uint32_t data;
	uint32_t data_end;
	uint32_t napi_id;

	/* Accessed by BPF_PROG_TYPE_sk_skb types from here to ... */
	uint32_t family;
	uint32_t remote_ip4;	/* Stored in network byte order */
	uint32_t local_ip4;	/* Stored in network byte order */
	uint32_t remote_ip6[4];	/* Stored in network byte order */
	uint32_t local_ip6[4];	/* Stored in network byte order */
	uint32_t remote_port;	/* Stored in network byte order */
	uint32_t local_port;	/* stored in host byte order */
	/* ... here. */

	uint32_t data_meta;
};

struct net_off_t {
	uint8_t  ver:4;
} __attribute__((packed));

struct eth_t {
	uint8_t  dst[6];
	uint8_t  src[6];
	uint16_t type;
} __attribute__((packed));

struct dot1q_t {
	uint16_t pri:3;
	uint16_t cfi:1;
	uint16_t vlanid:12;
	uint16_t type;
} __attribute__((packed));

struct arp_t {
	uint16_t htype;
	uint16_t ptype;
	uint8_t  hlen;
	uint8_t  plen;
	uint16_t oper;
	uint8_t  sha[6];
	uint32_t spa;
	uint8_t  tha[6];
	uint32_t tpa;
} __attribute__((packed));

struct ip_t {
	uint8_t  ver:4;
	uint8_t  hlen:4;
	uint8_t  tos;
	uint16_t tlen;
	uint16_t identification;
	uint16_t ffo_unused:1;
	uint16_t df:1;
	uint16_t mf:1;
	uint16_t foffset:13;
	uint8_t  ttl;
	uint8_t  proto;
	uint16_t hchecksum;
	uint32_t src;
	uint32_t dst;
} __attribute__((packed));

struct icmp_t {
	uint8_t  type;
	uint8_t  code;
	uint16_t checksum;
} __attribute__((packed));

struct ip6_t {
	uint32_t ver:4;
	uint32_t priority:8;
	uint32_t flow_label:20;
	uint16_t payload_len;
	uint8_t  next_header;
	uint8_t  hop_limit;
	uint64_t src_hi;
	uint64_t src_lo;
	uint64_t dst_hi;
	uint64_t dst_lo;
} __attribute__((packed));

struct ip6_opt_t {
	uint8_t  next_header;
	uint8_t  ext_len;
	uint8_t  pad[6];
} __attribute__((packed));

struct icmp6_t {
	uint8_t  type;
	uint8_t  code;
	uint16_t checksum;
} __attribute__((packed));

struct udp_t {
	uint16_t src_port;
	uint16_t dst_port;
	uint16_t length;
	uint16_t crc;
} __attribute__((packed));

struct tcp_t {
	uint16_t src_port;
	uint16_t dst_port;
	uint32_t seq_num;
	uint32_t ack_num;
	uint8_t  offset:4;
	uint8_t  reserved:4;
	uint8_t  flag_cwr:1;
	uint8_t  flag_ece:1;
	uint8_t  flag_urg:1;
	uint8_t  flag_ack:1;
	uint8_t  flag_psh:1;
	uint8_t  flag_rst:1;
	uint8_t  flag_syn:1;
	uint8_t  flag_fin:1;
	uint16_t rcv_wnd;
	uint16_t cksum;
	uint16_t urg_ptr;
} __attribute__((packed));

struct vxlan_t {
	uint32_t rsv1:4;
	uint32_t iflag:1;
	uint32_t rsv2:3;
	uint32_t rsv3:24;
	uint32_t key:24;
	uint32_t rsv4:8;
} __attribute__((packed));
]]


-- Architecture-specific ptrace register layout
local S = require('syscall')
local arch = S.abi.arch
local parm_to_reg = {}
if arch == 'x64' then
	ffi.cdef [[
	struct pt_regs {
		unsigned long r15;
		unsigned long r14;
		unsigned long r13;
		unsigned long r12;
		unsigned long bp;
		unsigned long bx;
		unsigned long r11;
		unsigned long r10;
		unsigned long r9;
		unsigned long r8;
		unsigned long ax;
		unsigned long cx;
		unsigned long dx;
		unsigned long si;
		unsigned long di;
		unsigned long orig_ax;
		unsigned long ip;
		unsigned long cs;
		unsigned long flags;
		unsigned long sp;
		unsigned long ss;
	};]]
	parm_to_reg = {parm1='di', parm2='si', parm3='dx', parm4='cx', parm5='r8', ret='sp', fp='bp'}
else
	ffi.cdef 'struct pt_regs {};'
end
-- Map symbolic registers to architecture ABI
ffi.metatype('struct pt_regs', {
		__index = function (_ --[[t]],k)
			return assert(parm_to_reg[k], 'no such register: '..k)
		end,
})

local M = {}

-- Dissector interface
local function dissector(type, e, dst, src, field)
	local parent = e.V[src].const
	-- Create new dissector variable
	e.vcopy(dst, src)
	-- Compute and materialize new dissector offset from parent
	e.V[dst].const = {off=e.V[src].const.off, __dissector=e.V[src].const.__dissector}
	parent.__dissector[field](e, dst)
	e.V[dst].const.__dissector = type
end
M.dissector = dissector

-- Get current effective offset, load field value at an offset relative to it and
-- add its value to compute next effective offset (e.g. udp_off = ip_off + pkt[ip_off].hlen)
local function next_offset(e, var, type, off, mask, shift)
	local d = e.V[var].const
	-- Materialize relative offset value in R0
	local dst_reg, tmp_reg
	if d.off then
		dst_reg = e.vreg(var, 0, true)
		tmp_reg = dst_reg -- Use target register to avoid copy
		e.emit(BPF.LD + BPF.ABS + e.const_width[ffi.sizeof(type)], tmp_reg, 0, 0, d.off + off or 0)
	else
		tmp_reg = e.vreg(e.tmpvar, 0, true, type) -- Reserve R0 for temporary relative offset
		dst_reg = e.vreg(var) -- Must rematerialize (if it was spilled by tmp var)
		e.emit(BPF.LD + BPF.IND + e.const_width[ffi.sizeof(type)], tmp_reg, dst_reg, 0, off or 0)
	end
	-- Finalize relative offset
	if mask then
		e.emit(BPF.ALU + BPF.AND + BPF.K, tmp_reg, 0, 0, mask)
	end
	if shift and shift ~= 0 then
		local op = BPF.LSH
		if shift < 0 then
			op = BPF.RSH
			shift = -shift
		end
		e.emit(BPF.ALU + op + BPF.K, tmp_reg, 0, 0, shift)
	end
	-- Add to base offset to turn it into effective address
	if dst_reg ~= tmp_reg then
		e.emit(BPF.ALU + BPF.ADD + BPF.X, dst_reg, tmp_reg, 0, 0)
	else
		e.emit(BPF.ALU + BPF.ADD + BPF.K, dst_reg, 0, 0, d.off)
	end
	-- Discard temporary allocations
	d.off = nil
	e.V[e.tmpvar].reg = nil
end

local function next_skip(e, var, off)
	local d = e.V[var].const
	if not d.off then
		local dst_reg = e.vreg(var)
		e.emit(BPF.ALU64 + BPF.ADD + BPF.K, dst_reg, 0, 0, off)
	else
		d.off = d.off + off
	end
end

local function skip_eth(e, dst)
	-- IP starts right after ETH header (fixed size)
	local d = e.V[dst].const
	d.off = d.off + ffi.sizeof('struct eth_t')
end

-- Export types
M.type = function(typestr, t)
	t = t or {}
	t.__dissector=ffi.typeof(typestr)
	return t
end
M.skb     = M.type('struct sk_buff', {source='ptr_to_ctx'})
M.pt_regs = M.type('struct pt_regs', {source='ptr_to_probe'})
M.pkt     = M.type('struct eth_t',   {off=0, source='ptr_to_pkt'}) -- skb needs special accessors
-- M.eth     = function (...) return dissector(ffi.typeof('struct eth_t'), ...) end
M.dot1q   = function (...) return dissector(ffi.typeof('struct dot1q_t'), ...) end
M.arp     = function (...) return dissector(ffi.typeof('struct arp_t'), ...) end
M.icmp    = function (...) return dissector(ffi.typeof('struct icmp_t'), ...) end
M.ip      = function (...) return dissector(ffi.typeof('struct ip_t'), ...) end
M.icmp6   = function (...) return dissector(ffi.typeof('struct icmp6_t'), ...) end
M.ip6     = function (...) return dissector(ffi.typeof('struct ip6_t'), ...) end
M.ip6_opt = function (...) return dissector(ffi.typeof('struct ip6_opt_t'), ...) end
M.udp     = function (...) return dissector(ffi.typeof('struct udp_t'), ...) end
M.tcp     = function (...) return dissector(ffi.typeof('struct tcp_t'), ...) end
M.vxlan   = function (...) return dissector(ffi.typeof('struct vxlan_t'), ...) end
M.data    = function (...) return dissector(ffi.typeof('uint8_t'), ...) end
M.net_off = function (...) return dissector(ffi.typeof('struct net_off_t'), ...) end

-- Metatables
ffi.metatype(ffi.typeof('struct eth_t'), {
	__index = {
		ip = skip_eth,
		ip6 = skip_eth,
		net_off = function (e, dst)
			next_skip(e, dst, BPF.NET_OFF)
		end,
	}
})

ffi.metatype(ffi.typeof('struct net_off_t'), {
	__index = {
		ip = function () end,
		ip6 = function () end,
	}
})

ffi.metatype(ffi.typeof('struct ip_t'), {
	__index = {
		-- Skip IP header length (stored as number of words)
		-- e.g. hlen = 5, Header Length = 5 x sizeof(u32) = 20 octets
		-- Mask first nibble and shift by 2 (multiplication by 4)
		icmp = function(e, dst) next_offset(e, dst, ffi.typeof('uint8_t'), 0, 0x0f, 2) end,
		udp  = function(e, dst) next_offset(e, dst, ffi.typeof('uint8_t'), 0, 0x0f, 2) end,
		tcp  = function(e, dst) next_offset(e, dst, ffi.typeof('uint8_t'), 0, 0x0f, 2) end,
	}
})

ffi.metatype(ffi.typeof('struct ip6_t'), {
	__index = {
		-- Skip fixed IPv6 header length (40 bytes)
		-- The caller must check the value of `next_header` to skip any extension headers
		icmp6 = function(e, dst) next_skip(e, dst, ffi.sizeof('struct ip6_t'), 0) end,
		udp  = function(e, dst) next_skip(e, dst, ffi.sizeof('struct ip6_t'), 0) end,
		tcp  = function(e, dst) next_skip(e, dst, ffi.sizeof('struct ip6_t'), 0) end,
		ip6_opt = function(e, dst) next_skip(e, dst, ffi.sizeof('struct ip6_t'), 0) end,
	}
})

local ip6_opt_ext_len_off = ffi.offsetof('struct ip6_opt_t', 'ext_len')
ffi.metatype(ffi.typeof('struct ip6_opt_t'), {
	__index = {
		-- Skip IPv6 extension header length (field `ext_len`)
		icmp6 = function(e, dst) next_offset(e, dst, ffi.typeof('uint8_t'), ip6_opt_ext_len_off) end,
		udp  = function(e, dst) next_offset(e, dst, ffi.typeof('uint8_t'), ip6_opt_ext_len_off) end,
		tcp  = function(e, dst) next_offset(e, dst, ffi.typeof('uint8_t'), ip6_opt_ext_len_off) end,
		ip6_opt = function(e, dst) next_offset(e, dst, ffi.typeof('uint8_t'), ip6_opt_ext_len_off) end,
	}
})

ffi.metatype(ffi.typeof('struct tcp_t'), {
	__index = {
		-- Skip TCP header length (stored as number of words)
		-- e.g. hlen = 5, Header Length = 5 x sizeof(u32) = 20 octets
		data = function(e, dst)
			next_offset(e, dst, ffi.typeof('uint8_t'), ffi.offsetof('struct tcp_t', 'offset'), 0xf0, -2)
		end,
	}
})

ffi.metatype(ffi.typeof('struct udp_t'), {
	__index = {
		-- Skip UDP header length (8 octets)
		data = function(e, dst)
			next_skip(e, dst, ffi.sizeof('struct udp_t'))
		end,
	}
})

-- Constants
M.c = {
	eth = { -- Constants http://standards.ieee.org/regauth/ethertype
		ip     = 0x0800, -- IP (v4) protocol
		ip6    = 0x86dd, -- IP (v6) protocol
		arp    = 0x0806, -- Address resolution protocol
		revarp = 0x8035, -- Reverse addr resolution protocol
		vlan   = 0x8100, -- IEEE 802.1Q VLAN tagging
	},
	ip = {
		-- Reserved Addresses
		addr_any         = 0x00000000, -- 0.0.0.0
		addr_broadcast   = 0xffffffff, -- 255.255.255.255
		addr_loopback    = 0x7f000001, -- 127.0.0.1
		addr_mcast_all   = 0xe0000001, -- 224.0.0.1
		addr_mcast_local = 0xe00000ff, -- 224.0.0.255
		-- Type of service (ip_tos), RFC 1349 ("obsoleted by RFC 2474")
		tos_default      = 0x00, -- default
		tos_lowdelay     = 0x10, -- low delay
		tos_throughput   = 0x08, -- high throughput
		tos_reliability  = 0x04, -- high reliability
		tos_lowcost      = 0x02, -- low monetary cost - XXX
		tos_ect          = 0x02, -- ECN-capable transport
		tos_ce           = 0x01, -- congestion experienced
		-- Fragmentation flags (ip_off)
		rf = 0x8000, -- reserved
		df = 0x4000, -- don't fragment
		mf = 0x2000, -- more fragments (not last frag)
		offmask  = 0x1fff, -- mask for fragment offset
		-- Time-to-live (ip_ttl), seconds
		ttl_default = 64,  -- default ttl, RFC 1122, RFC 1340
		ttl_max     = 255, -- maximum ttl
		-- Protocol (ip_p) - http://www.iana.org/assignments/protocol-numbers
		proto_ip      = 0,  -- dummy for IP
		proto_hopopts = 0,  -- IPv6 hop-by-hop options
		proto_icmp    = 1,  -- ICMP
		proto_igmp    = 2,  -- IGMP
		proto_ggp     = 3,  -- gateway-gateway protocol
		proto_ipip    = 4,  -- IP in IP
		proto_st      = 5,  -- ST datagram mode
		proto_tcp     = 6,  -- TCP
		proto_cbt     = 7,  -- CBT
		proto_egp     = 8,  -- exterior gateway protocol
		proto_igp     = 9,  -- interior gateway protocol
		proto_bbnrcc  = 10,  -- BBN RCC monitoring
		proto_nvp     = 11,  -- Network Voice Protocol
		proto_pup     = 12,  -- PARC universal packet
		proto_argus   = 13,  -- ARGUS
		proto_emcon   = 14,  -- EMCON
		proto_xnet    = 15,  -- Cross Net Debugger
		proto_chaos   = 16,  -- Chaos
		proto_udp     = 17,  -- UDP
		proto_mux     = 18,  -- multiplexing
		proto_dcnmeas = 19,  -- DCN measurement
		proto_hmp     = 20,  -- Host Monitoring Protocol
		proto_prm     = 21,  -- Packet Radio Measurement
		proto_idp     = 22,  -- Xerox NS IDP
		proto_trunk1  = 23,  -- Trunk-1
		proto_trunk2  = 24,  -- Trunk-2
		proto_leaf1   = 25,  -- Leaf-1
		proto_leaf2   = 26,  -- Leaf-2
		proto_rdp     = 27,  -- "Reliable Datagram" proto
		proto_irtp    = 28,  -- Inet Reliable Transaction
		proto_tp      = 29,  -- ISO TP class 4
		proto_netblt  = 30,  -- Bulk Data Transfer
		proto_mfpnsp  = 31,  -- MFE Network Services
		proto_meritinp= 32,  -- Merit Internodal Protocol
		proto_sep     = 33,  -- Sequential Exchange proto
		proto_3pc     = 34,  -- Third Party Connect proto
		proto_idpr    = 35,  -- Interdomain Policy Route
		proto_xtp     = 36,  -- Xpress Transfer Protocol
		proto_ddp     = 37,  -- Datagram Delivery