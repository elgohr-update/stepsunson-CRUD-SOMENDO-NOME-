
#ifndef __VMLINUX_H__
#define __VMLINUX_H__

#ifndef BPF_NO_PRESERVE_ACCESS_INDEX
#pragma clang attribute push (__attribute__((preserve_access_index)), apply_to = record)
#endif

typedef char *va_list;

typedef signed char __s8;

typedef unsigned char __u8;

typedef short int __s16;

typedef short unsigned int __u16;

typedef int __s32;

typedef unsigned int __u32;

typedef long long int __s64;

typedef long long unsigned int __u64;

typedef __s8 s8;

typedef __u8 u8;

typedef __s16 s16;

typedef __u16 u16;

typedef __s32 s32;

typedef __u32 u32;

typedef __s64 s64;

typedef __u64 u64;

typedef struct {
	__u32 u[4];
} __vector128;

typedef __vector128 vector128;

enum {
	false = 0,
	true = 1,
};

typedef long int __kernel_long_t;

typedef long unsigned int __kernel_ulong_t;

typedef int __kernel_pid_t;

typedef unsigned int __kernel_uid32_t;

typedef unsigned int __kernel_gid32_t;

typedef __kernel_ulong_t __kernel_size_t;

typedef __kernel_long_t __kernel_ssize_t;

typedef long long int __kernel_loff_t;

typedef long long int __kernel_time64_t;

typedef __kernel_long_t __kernel_clock_t;

typedef int __kernel_timer_t;

typedef int __kernel_clockid_t;

typedef __u16 __be16;

typedef __u32 __be32;

typedef __u64 __be64;

typedef unsigned int __poll_t;

typedef u32 __kernel_dev_t;

typedef __kernel_dev_t dev_t;

typedef short unsigned int umode_t;

typedef __kernel_pid_t pid_t;

typedef __kernel_clockid_t clockid_t;

typedef _Bool bool;

typedef __kernel_uid32_t uid_t;

typedef __kernel_gid32_t gid_t;

typedef __kernel_loff_t loff_t;

typedef __kernel_size_t size_t;

typedef __kernel_ssize_t ssize_t;

typedef s32 int32_t;

typedef u32 uint32_t;

typedef u64 uint64_t;

typedef u64 sector_t;

typedef u64 blkcnt_t;

typedef unsigned int gfp_t;

typedef unsigned int fmode_t;

typedef struct {
	int counter;
} atomic_t;

typedef struct {
	s64 counter;
} atomic64_t;

struct list_head {
	struct list_head *next;
	struct list_head *prev;
};

struct hlist_node;

struct hlist_head {
	struct hlist_node *first;
};

struct hlist_node {
	struct hlist_node *next;
	struct hlist_node **pprev;
};

struct callback_head {
	struct callback_head *next;
	void (*func)(struct callback_head *);
};

struct kernel_symbol {
	long unsigned int value;
	const char *name;
	const char *namespace;
};

struct user_pt_regs {
	long unsigned int gpr[32];
	long unsigned int nip;
	long unsigned int msr;
	long unsigned int orig_gpr3;
	long unsigned int ctr;
	long unsigned int link;
	long unsigned int xer;
	long unsigned int ccr;
	long unsigned int softe;
	long unsigned int trap;
	long unsigned int dar;
	long unsigned int dsisr;
	long unsigned int result;
};

struct pt_regs {
	union {
		struct user_pt_regs user_regs;
		struct {
			long unsigned int gpr[32];
			long unsigned int nip;
			long unsigned int msr;
			long unsigned int orig_gpr3;
			long unsigned int ctr;
			long unsigned int link;
			long unsigned int xer;
			long unsigned int ccr;
			long unsigned int softe;
			long unsigned int trap;
			long unsigned int dar;
			long unsigned int dsisr;
			long unsigned int result;
		};
	};
	union {
		struct {
			long unsigned int ppr;
			long unsigned int exit_result;
			union {
				long unsigned int kuap;
				long unsigned int amr;
			};
			long unsigned int iamr;
		};
		long unsigned int __pad[4];
	};
};

struct lock_class_key {};

struct fs_context;

struct fs_parameter_spec;

struct dentry;

struct super_block;

struct module;

struct file_system_type {
	const char *name;
	int fs_flags;
	int (*init_fs_context)(struct fs_context *);
	const struct fs_parameter_spec *parameters;
	struct dentry * (*mount)(struct file_system_type *, int, const char *, void *);
	void (*kill_sb)(struct super_block *);
	struct module *owner;
	struct file_system_type *next;
	struct hlist_head fs_supers;
	struct lock_class_key s_lock_key;
	struct lock_class_key s_umount_key;
	struct lock_class_key s_vfs_rename_key;
	struct lock_class_key s_writers_key[3];
	struct lock_class_key i_lock_key;
	struct lock_class_key i_mutex_key;
	struct lock_class_key invalidate_lock_key;
	struct lock_class_key i_mutex_dir_key;
};

struct qspinlock {
	union {
		atomic_t val;
		struct {
			u8 locked;
			u8 pending;
		};
		struct {
			u16 locked_pending;
			u16 tail;
		};
	};
};

typedef struct qspinlock arch_spinlock_t;

struct qrwlock {
	union {
		atomic_t cnts;
		struct {
			u8 wlocked;
			u8 __lstate[3];
		};
	};
	arch_spinlock_t wait_lock;
};

typedef struct qrwlock arch_rwlock_t;

struct lockdep_map {};

struct raw_spinlock {
	arch_spinlock_t raw_lock;
};

typedef struct raw_spinlock raw_spinlock_t;

struct ratelimit_state {
	raw_spinlock_t lock;
	int interval;
	int burst;
	int printed;
	int missed;
	long unsigned int begin;
	long unsigned int flags;
};

struct pi_entry {
	const char *fmt;
	const char *func;
	const char *file;
	unsigned int line;
	const char *level;
	const char *subsys_fmt_prefix;
} __attribute__((packed));

struct jump_entry {
	s32 code;
	s32 target;
	long int key;
};

struct static_key_mod;

struct static_key {
	atomic_t enabled;
	union {
		long unsigned int type;
		struct jump_entry *entries;
		struct static_key_mod *next;
	};
};

typedef void *fl_owner_t;

struct file;

struct kiocb;

struct iov_iter;

struct io_comp_batch;

struct dir_context;

struct poll_table_struct;

struct vm_area_struct;

struct inode;

struct file_lock;

struct page;

struct pipe_inode_info;

struct seq_file;

struct file_operations {
	struct module *owner;
	loff_t (*llseek)(struct file *, loff_t, int);
	ssize_t (*read)(struct file *, char *, size_t, loff_t *);
	ssize_t (*write)(struct file *, const char *, size_t, loff_t *);
	ssize_t (*read_iter)(struct kiocb *, struct iov_iter *);
	ssize_t (*write_iter)(struct kiocb *, struct iov_iter *);
	int (*iopoll)(struct kiocb *, struct io_comp_batch *, unsigned int);
	int (*iterate)(struct file *, struct dir_context *);
	int (*iterate_shared)(struct file *, struct dir_context *);
	__poll_t (*poll)(struct file *, struct poll_table_struct *);
	long int (*unlocked_ioctl)(struct file *, unsigned int, long unsigned int);
	long int (*compat_ioctl)(struct file *, unsigned int, long unsigned int);
	int (*mmap)(struct file *, struct vm_area_struct *);
	long unsigned int mmap_supported_flags;
	int (*open)(struct inode *, struct file *);
	int (*flush)(struct file *, fl_owner_t);
	int (*release)(struct inode *, struct file *);
	int (*fsync)(struct file *, loff_t, loff_t, int);
	int (*fasync)(int, struct file *, int);
	int (*lock)(struct file *, int, struct file_lock *);
	ssize_t (*sendpage)(struct file *, struct page *, int, size_t, loff_t *, int);
	long unsigned int (*get_unmapped_area)(struct file *, long unsigned int, long unsigned int, long unsigned int, long unsigned int);
	int (*check_flags)(int);
	int (*flock)(struct file *, int, struct file_lock *);
	ssize_t (*splice_write)(struct pipe_inode_info *, struct file *, loff_t *, size_t, unsigned int);
	ssize_t (*splice_read)(struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
	int (*setlease)(struct file *, long int, struct file_lock **, void **);
	long int (*fallocate)(struct file *, int, loff_t, loff_t);
	void (*show_fdinfo)(struct seq_file *, struct file *);
	ssize_t (*copy_file_range)(struct file *, loff_t, struct file *, loff_t, size_t, unsigned int);
	loff_t (*remap_file_range)(struct file *, loff_t, struct file *, loff_t, loff_t, unsigned int);
	int (*fadvise)(struct file *, loff_t, loff_t, int);
};

struct static_call_key {
	void *func;
};

struct bug_entry {
	int bug_addr_disp;
	int file_disp;
	short unsigned int line;
	short unsigned int flags;
};

typedef __s64 time64_t;

struct __kernel_timespec {
	__kernel_time64_t tv_sec;
	long long int tv_nsec;
};

struct timespec64 {
	time64_t tv_sec;
	long int tv_nsec;
};

enum timespec_type {
	TT_NONE = 0,
	TT_NATIVE = 1,
	TT_COMPAT = 2,
};

typedef s32 old_time32_t;

struct old_timespec32 {
	old_time32_t tv_sec;
	s32 tv_nsec;
};

struct pollfd;

struct restart_block {
	long unsigned int arch_data;
	long int (*fn)(struct restart_block *);
	union {
		struct {
			u32 *uaddr;
			u32 val;
			u32 flags;
			u32 bitset;
			u64 time;
			u32 *uaddr2;
		} futex;
		struct {
			clockid_t clockid;
			enum timespec_type type;
			union {
				struct __kernel_timespec *rmtp;
				struct old_timespec32 *compat_rmtp;
			};
			u64 expires;
		} nanosleep;
		struct {
			struct pollfd *ufds;
			int nfds;
			int has_timeout;
			long unsigned int tv_sec;
			long unsigned int tv_nsec;
		} poll;
	};
};

typedef struct {
	__be64 pte;
} pte_t;

typedef struct {
	__be64 pmd;
} pmd_t;

typedef struct {
	__be64 pud;
} pud_t;

typedef struct {
	__be64 pgd;
} pgd_t;

typedef struct {
	long unsigned int pgprot;
} pgprot_t;

typedef pte_t *pgtable_t;

typedef atomic64_t atomic_long_t;

struct spinlock {
	union {
		struct raw_spinlock rlock;
	};
};

typedef struct spinlock spinlock_t;

struct address_space;

struct page_pool;

struct mm_struct;

struct dev_pagemap;

struct page {
	long unsigned int flags;
	union {
		struct {
			union {
				struct list_head lru;
				struct {
					void *__filler;
					unsigned int mlock_count;
				};
			};
			struct address_space *mapping;
			long unsigned int index;
			long unsigned int private;
		};
		struct {
			long unsigned int pp_magic;
			struct page_pool *pp;
			long unsigned int _pp_mapping_pad;
			long unsigned int dma_addr;
			union {
				long unsigned int dma_addr_upper;
				atomic_long_t pp_frag_count;
			};
		};
		struct {
			long unsigned int compound_head;
			unsigned char compound_dtor;
			unsigned char compound_order;
			atomic_t compound_mapcount;
			atomic_t compound_pincount;
			unsigned int compound_nr;
		};
		struct {
			long unsigned int _compound_pad_1;
			long unsigned int _compound_pad_2;
			struct list_head deferred_list;
		};
		struct {
			long unsigned int _pt_pad_1;
			pgtable_t pmd_huge_pte;
			long unsigned int _pt_pad_2;
			union {
				struct mm_struct *pt_mm;
				atomic_t pt_frag_refcount;
			};
			spinlock_t ptl;
		};
		struct {
			struct dev_pagemap *pgmap;
			void *zone_device_data;
		};
		struct callback_head callback_head;
	};
	union {
		atomic_t _mapcount;
		unsigned int page_type;
	};
	atomic_t _refcount;
	long unsigned int memcg_data;
};

struct slb_entry {
	u64 esid;
	u64 vsid;
};

struct subpage_prot_table {
	long unsigned int maxaddr;
	unsigned int **protptrs[512];
	unsigned int *low_prot[4];
};

struct slice_mask {
	u64 low_slices;
	long unsigned int high_slices[64];
};

struct hash_mm_context {
	u16 user_psize;
	unsigned char low_slices_psize[8];
	unsigned char high_slices_psize[2048];
	long unsigned int slb_addr_limit;
	struct slice_mask mask_64k;
	struct slice_mask mask_4k;
	struct slice_mask mask_16m;
	struct slice_mask mask_16g;
	struct subpage_prot_table *spt;
};

typedef long unsigned int mm_context_id_t;

typedef struct {
	union {
		mm_context_id_t id;
		mm_context_id_t extended_id[8];
	};
	atomic_t active_cpus;
	atomic_t copros;
	atomic_t vas_windows;
	struct hash_mm_context *hash_context;
	void *vdso;
	void *pte_frag;
	void *pmd_frag;
	struct list_head iommu_group_mem_list;
	u32 pkey_allocation_map;
	s16 execute_only_pkey;
} mm_context_t;

struct lppaca {
	__be32 desc;
	__be16 size;
	u8 reserved1[3];
	u8 __old_status;
	u8 reserved3[14];
	volatile __be32 dyn_hw_node_id;
	volatile __be32 dyn_hw_proc_id;
	u8 reserved4[56];
	volatile u8 vphn_assoc_counts[8];
	u8 reserved5[32];
	u8 reserved6[48];
	u8 cede_latency_hint;
	u8 ebb_regs_in_use;
	u8 reserved7[6];
	u8 dtl_enable_mask;
	u8 donate_dedicated_cpu;
	u8 fpregs_in_use;
	u8 pmcregs_in_use;
	u8 reserved8[28];
	__be64 wait_state_cycles;
	u8 reserved9[28];
	__be16 slb_count;
	u8 idle;
	u8 vmxregs_in_use;
	volatile __be32 yield_count;
	volatile __be32 dispersion_count;
	volatile __be64 cmo_faults;
	volatile __be64 cmo_fault_time;
	u8 reserved10[104];
	__be32 page_ins;
	u8 reserved11[148];
	volatile __be64 dtl_idx;
	u8 reserved12[96];
};

struct slb_shadow {
	__be32 persistent;
	__be32 buffer_length;
	__be64 reserved;
	struct {
		__be64 esid;
		__be64 vsid;
	} save_area[2];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct cpu_accounting_data {
	long unsigned int utime;
	long unsigned int stime;
	long unsigned int gtime;
	long unsigned int hardirq_time;
	long unsigned int softirq_time;
	long unsigned int steal_time;
	long unsigned int idle_time;
	long unsigned int starttime;
	long unsigned int starttime_user;
};

enum MCE_Version {
	MCE_V1 = 1,
};

enum MCE_Severity {
	MCE_SEV_NO_ERROR = 0,
	MCE_SEV_WARNING = 1,
	MCE_SEV_SEVERE = 2,
	MCE_SEV_FATAL = 3,
};

enum MCE_Disposition {
	MCE_DISPOSITION_RECOVERED = 0,
	MCE_DISPOSITION_NOT_RECOVERED = 1,
};

enum MCE_Initiator {
	MCE_INITIATOR_UNKNOWN = 0,
	MCE_INITIATOR_CPU = 1,
	MCE_INITIATOR_PCI = 2,
	MCE_INITIATOR_ISA = 3,
	MCE_INITIATOR_MEMORY = 4,
	MCE_INITIATOR_POWERMGM = 5,
};

enum MCE_ErrorType {
	MCE_ERROR_TYPE_UNKNOWN = 0,
	MCE_ERROR_TYPE_UE = 1,
	MCE_ERROR_TYPE_SLB = 2,
	MCE_ERROR_TYPE_ERAT = 3,
	MCE_ERROR_TYPE_TLB = 4,
	MCE_ERROR_TYPE_USER = 5,
	MCE_ERROR_TYPE_RA = 6,
	MCE_ERROR_TYPE_LINK = 7,
	MCE_ERROR_TYPE_DCACHE = 8,
	MCE_ERROR_TYPE_ICACHE = 9,
};

enum MCE_ErrorClass {
	MCE_ECLASS_UNKNOWN = 0,
	MCE_ECLASS_HARDWARE = 1,
	MCE_ECLASS_HARD_INDETERMINATE = 2,
	MCE_ECLASS_SOFTWARE = 3,
	MCE_ECLASS_SOFT_INDETERMINATE = 4,
};

enum MCE_UeErrorType {
	MCE_UE_ERROR_INDETERMINATE = 0,
	MCE_UE_ERROR_IFETCH = 1,
	MCE_UE_ERROR_PAGE_TABLE_WALK_IFETCH = 2,
	MCE_UE_ERROR_LOAD_STORE = 3,
	MCE_UE_ERROR_PAGE_TABLE_WALK_LOAD_STORE = 4,
};

enum MCE_SlbErrorType {
	MCE_SLB_ERROR_INDETERMINATE = 0,
	MCE_SLB_ERROR_PARITY = 1,
	MCE_SLB_ERROR_MULTIHIT = 2,
};

enum MCE_EratErrorType {
	MCE_ERAT_ERROR_INDETERMINATE = 0,
	MCE_ERAT_ERROR_PARITY = 1,
	MCE_ERAT_ERROR_MULTIHIT = 2,
};

enum MCE_TlbErrorType {
	MCE_TLB_ERROR_INDETERMINATE = 0,
	MCE_TLB_ERROR_PARITY = 1,
	MCE_TLB_ERROR_MULTIHIT = 2,
};

enum MCE_UserErrorType {
	MCE_USER_ERROR_INDETERMINATE = 0,
	MCE_USER_ERROR_TLBIE = 1,
	MCE_USER_ERROR_SCV = 2,
};

enum MCE_RaErrorType {
	MCE_RA_ERROR_INDETERMINATE = 0,
	MCE_RA_ERROR_IFETCH = 1,
	MCE_RA_ERROR_IFETCH_FOREIGN = 2,
	MCE_RA_ERROR_PAGE_TABLE_WALK_IFETCH = 3,
	MCE_RA_ERROR_PAGE_TABLE_WALK_IFETCH_FOREIGN = 4,
	MCE_RA_ERROR_LOAD = 5,
	MCE_RA_ERROR_STORE = 6,
	MCE_RA_ERROR_PAGE_TABLE_WALK_LOAD_STORE = 7,
	MCE_RA_ERROR_PAGE_TABLE_WALK_LOAD_STORE_FOREIGN = 8,
	MCE_RA_ERROR_LOAD_STORE_FOREIGN = 9,
};

enum MCE_LinkErrorType {
	MCE_LINK_ERROR_INDETERMINATE = 0,
	MCE_LINK_ERROR_IFETCH_TIMEOUT = 1,
	MCE_LINK_ERROR_PAGE_TABLE_WALK_IFETCH_TIMEOUT = 2,
	MCE_LINK_ERROR_LOAD_TIMEOUT = 3,
	MCE_LINK_ERROR_STORE_TIMEOUT = 4,
	MCE_LINK_ERROR_PAGE_TABLE_WALK_LOAD_STORE_TIMEOUT = 5,
};

struct machine_check_event {
	enum MCE_Version version: 8;
	u8 in_use;
	enum MCE_Severity severity: 8;
	enum MCE_Initiator initiator: 8;
	enum MCE_ErrorType error_type: 8;
	enum MCE_ErrorClass error_class: 8;
	enum MCE_Disposition disposition: 8;
	bool sync_error;
	u16 cpu;
	u64 gpr3;
	u64 srr0;
	u64 srr1;
	union {
		struct {
			enum MCE_UeErrorType ue_error_type: 8;
			u8 effective_address_provided;
			u8 physical_address_provided;
			u8 ignore_event;
			u8 reserved_1[4];
			u64 effective_address;
			u64 physical_address;
			u8 reserved_2[8];
		} ue_error;
		struct {
			enum MCE_SlbErrorType slb_error_type: 8;
			u8 effective_address_provided;
			u8 reserved_1[6];
			u64 effective_address;
			u8 reserved_2[16];
		} slb_error;
		struct {
			enum MCE_EratErrorType erat_error_type: 8;
			u8 effective_address_provided;
			u8 reserved_1[6];
			u64 effective_address;
			u8 reserved_2[16];
		} erat_error;
		struct {
			enum MCE_TlbErrorType tlb_error_type: 8;
			u8 effective_address_provided;
			u8 reserved_1[6];
			u64 effective_address;
			u8 reserved_2[16];
		} tlb_error;
		struct {
			enum MCE_UserErrorType user_error_type: 8;
			u8 effective_address_provided;
			u8 reserved_1[6];
			u64 effective_address;
			u8 reserved_2[16];
		} user_error;
		struct {
			enum MCE_RaErrorType ra_error_type: 8;
			u8 effective_address_provided;
			u8 reserved_1[6];
			u64 effective_address;
			u8 reserved_2[16];
		} ra_error;
		struct {
			enum MCE_LinkErrorType link_error_type: 8;
			u8 effective_address_provided;
			u8 reserved_1[6];
			u64 effective_address;
			u8 reserved_2[16];
		} link_error;
	} u;
};

struct mce_info {
	int mce_nest_count;
	struct machine_check_event mce_event[10];
	int mce_queue_count;
	struct machine_check_event mce_event_queue[10];
	int mce_ue_count;
	struct machine_check_event mce_ue_event_queue[10];
};

struct mmiowb_state {
	u16 nesting_count;
	u16 mmiowb_pending;
};

struct dtl_entry;

struct task_struct;

struct rtas_args;

struct paca_struct {
	struct lppaca *lppaca_ptr;
	u16 paca_index;
	u16 lock_token;
	u64 kernel_toc;
	u64 kernelbase;
	u64 kernel_msr;
	void *emergency_sp;
	u64 data_offset;
	s16 hw_cpu_id;
	u8 cpu_start;
	u8 kexec_state;
	struct slb_shadow *slb_shadow_ptr;
	struct dtl_entry *dispatch_log;
	struct dtl_entry *dispatch_log_end;
	u64 dscr_default;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	u64 exgen[10];
	u16 vmalloc_sllp;
	u8 slb_cache_ptr;
	u8 stab_rr;
	u32 slb_used_bitmap;
	u32 slb_kern_bitmap;
	u32 slb_cache[8];
	unsigned char mm_ctx_low_slices_psize[8];
	unsigned char mm_ctx_high_slices_psize[2048];
	struct task_struct *__current;
	u64 kstack;
	u64 saved_r1;
	u64 saved_msr;
	u64 exit_save_r1;
	u8 hsrr_valid;
	u8 srr_valid;
	u8 irq_soft_mask;
	u8 irq_happened;
	u8 irq_work_pending;
	u64 sprg_vdso;
	u64 tm_scratch;
	long unsigned int idle_state;
	union {
		struct {
			u8 thread_idle_state;
			u8 subcore_sibling_mask;
		};
		struct {		};
	};
	u64 exnmi[10];
	u64 exmc[10];
	void *nmi_emergency_sp;
	void *mc_emergency_sp;
	u16 in_nmi;
	u16 in_mce;
	u8 hmi_event_available;
	u8 hmi_p9_special_emu;
	u32 hmi_irqs;
	u8 ftrace_enabled;
	struct cpu_accounting_data accounting;
	u64 dtl_ridx;
	struct dtl_entry *dtl_curr;
	long: 64;
	long: 64;
	u64 exrfi[10];
	void *rfi_flush_fallback_area;
	u64 l1d_flush_size;
	struct rtas_args *rtas_args_reentrant;
	u8 *mce_data_buf;
	struct slb_entry *mce_faulty_slbs;
	u16 slb_save_cache_ptr;
	long unsigned int canary;
	struct mmiowb_state mmiowb_state;
	struct mce_info *mce_info;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct thread_info {
	int preempt_count;
	long unsigned int local_flags;
	long unsigned int *livepatch_sp;
	unsigned char slb_preload_nr;
	unsigned char slb_preload_tail;
	u32 slb_preload_esid[16];
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long unsigned int flags;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct refcount_struct {
	atomic_t refs;
};

typedef struct refcount_struct refcount_t;

struct llist_node {
	struct llist_node *next;
};

struct __call_single_node {
	struct llist_node llist;
	union {
		unsigned int u_flags;
		atomic_t a_flags;
	};
	u16 src;
	u16 dst;
};

struct load_weight {
	long unsigned int weight;
	u32 inv_weight;
};

struct rb_node {
	long unsigned int __rb_parent_color;
	struct rb_node *rb_right;
	struct rb_node *rb_left;
};

struct util_est {
	unsigned int enqueued;
	unsigned int ewma;
};

struct sched_avg {
	u64 last_update_time;
	u64 load_sum;
	u64 runnable_sum;
	u32 util_sum;
	u32 period_contrib;
	long unsigned int load_avg;
	long unsigned int runnable_avg;
	long unsigned int util_avg;
	struct util_est util_est;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct cfs_rq;

struct sched_entity {
	struct load_weight load;
	struct rb_node run_node;
	struct list_head group_node;
	unsigned int on_rq;
	u64 exec_start;
	u64 sum_exec_runtime;
	u64 vruntime;
	u64 prev_sum_exec_runtime;
	u64 nr_migrations;
	int depth;
	struct sched_entity *parent;
	struct cfs_rq *cfs_rq;
	struct cfs_rq *my_q;
	long unsigned int runnable_weight;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct sched_avg avg;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct sched_rt_entity {
	struct list_head run_list;
	long unsigned int timeout;
	long unsigned int watchdog_stamp;
	unsigned int time_slice;
	short unsigned int on_rq;
	short unsigned int on_list;
	struct sched_rt_entity *back;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

typedef s64 ktime_t;

struct timerqueue_node {
	struct rb_node node;
	ktime_t expires;
};

enum hrtimer_restart {
	HRTIMER_NORESTART = 0,
	HRTIMER_RESTART = 1,
};

struct hrtimer_clock_base;

struct hrtimer {
	struct timerqueue_node node;
	ktime_t _softexpires;
	enum hrtimer_restart (*function)(struct hrtimer *);
	struct hrtimer_clock_base *base;
	u8 state;
	u8 is_rel;
	u8 is_soft;
	u8 is_hard;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

struct sched_dl_entity {
	struct rb_node rb_node;
	u64 dl_runtime;
	u64 dl_deadline;
	u64 dl_period;
	u64 dl_bw;
	u64 dl_density;
	s64 runtime;
	u64 deadline;
	unsigned int flags;
	unsigned int dl_throttled: 1;
	unsigned int dl_yielded: 1;
	unsigned int dl_non_contending: 1;
	unsigned int dl_overrun: 1;
	struct hrtimer dl_timer;
	struct hrtimer inactive_timer;
	struct sched_dl_entity *pi_se;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
};

struct sched_statistics {
	u64 wait_start;
	u64 wait_max;
	u64 wait_count;
	u64 wait_sum;
	u64 iowait_count;
	u64 iowait_sum;
	u64 sleep_start;
	u64 sleep_max;
	s64 sum_sleep_runtime;
	u64 block_start;
	u64 block_max;
	s64 sum_block_runtime;
	u64 exec_max;
	u64 slice_max;
	u64 nr_migrations_cold;
	u64 nr_failed_migrations_affine;
	u64 nr_failed_migrations_running;
	u64 nr_failed_migrations_hot;
	u64 nr_forced_migrations;
	u64 nr_wakeups;
	u64 nr_wakeups_sync;
	u64 nr_wakeups_migrate;
	u64 nr_wakeups_local;
	u64 nr_wakeups_remote;
	u64 nr_wakeups_affine;
	u64 nr_wakeups_affine_attempts;
	u64 nr_wakeups_passive;
	u64 nr_wakeups_idle;
	u64 core_forceidle_sum;
	long: 64;
	long: 64;
	long: 64;
};

struct cpumask {
	long unsigned int bits[32];
};

typedef struct cpumask cpumask_t;

union rcu_special {
	struct {
		u8 blocked;
		u8 need_qs;
		u8 exp_hint;
		u8 need_mb;
	} b;
	u32 s;
};

struct sched_info {
	long unsigned int pcount;
	long long unsigned int run_delay;
	long long unsigned int last_arrival;
	long long unsigned int last_queued;
};

struct plist_node {
	int prio;
	struct list_head prio_list;
	struct list_head node_list;
};

struct vmacache {
	u64 seqnum;
	struct vm_area_struct *vmas[4];
};

struct task_rss_stat {
	int events;
	int count[4];
};

struct prev_cputime {
	u64 utime;
	u64 stime;
	raw_spinlock_t lock;
};

struct seqcount {
	unsigned int sequence;
};

typedef struct seqcount seqcount_t;

enum vtime_state {
	VTIME_INACTIVE = 0,
	VTIME_IDLE = 1,
	VTIME_SYS = 2,
	VTIME_USER = 3,
	VTIME_GUEST = 4,
};

struct vtime {
	seqcount_t seqcount;
	long long unsigned int starttime;
	enum vtime_state state;
	unsigned int cpu;
	u64 utime;
	u64 stime;
	u64 gtime;
};

struct rb_root {
	struct rb_node *rb_node;
};

struct rb_root_cached {
	struct rb_root rb_root;
	struct rb_node *rb_leftmost;
};

struct timerqueue_head {
	struct rb_root_cached rb_root;
};

struct posix_cputimer_base {
	u64 nextevt;
	struct timerqueue_head tqhead;
};

struct posix_cputimers {
	struct posix_cputimer_base bases[3];
	unsigned int timers_active;
	unsigned int expiry_active;
};

struct sem_undo_list;

struct sysv_sem {
	struct sem_undo_list *undo_list;
};

struct sysv_shm {
	struct list_head shm_clist;
};

typedef struct {
	long unsigned int sig[1];
} sigset_t;

struct sigpending {
	struct list_head list;
	sigset_t signal;
};

typedef struct {
	uid_t val;
} kuid_t;

struct seccomp_filter;

struct seccomp {
	int mode;
	atomic_t filter_count;
	struct seccomp_filter *filter;
};

struct syscall_user_dispatch {};

struct wake_q_node {
	struct wake_q_node *next;
};

struct task_io_accounting {
	u64 rchar;
	u64 wchar;
	u64 syscr;
	u64 syscw;
	u64 read_bytes;
	u64 write_bytes;
	u64 cancelled_write_bytes;
};

typedef struct {
	long unsigned int bits[4];
} nodemask_t;

struct seqcount_spinlock {
	seqcount_t seqcount;
};

typedef struct seqcount_spinlock seqcount_spinlock_t;

struct optimistic_spin_queue {
	atomic_t tail;
};

struct mutex {
	atomic_long_t owner;
	raw_spinlock_t wait_lock;
	struct optimistic_spin_queue osq;
	struct list_head wait_list;
};

struct tlbflush_unmap_batch {};

struct page_frag {
	struct page *page;
	__u32 offset;
	__u32 size;
};

struct kmap_ctrl {};

struct timer_list {
	struct hlist_node entry;
	long unsigned int expires;
	void (*function)(struct timer_list *);
	u32 flags;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

struct llist_head {
	struct llist_node *first;
};

struct debug_reg {};

struct thread_fp_state {
	u64 fpr[64];
	u64 fpscr;
	long: 64;
};

struct arch_hw_breakpoint {
	long unsigned int address;
	u16 type;
	u16 len;
	u16 hw_len;
	u8 flags;
};

struct thread_vr_state {
	vector128 vr[32];
	vector128 vscr;
};

struct perf_event;

struct thread_struct {
	long unsigned int ksp;
	long unsigned int ksp_vsid;
	struct pt_regs *regs;
	struct debug_reg debug;
	long: 64;
	struct thread_fp_state fp_state;
	struct thread_fp_state *fp_save_area;
	int fpexc_mode;
	unsigned int align_ctl;
	struct perf_event *ptrace_bps[2];
	struct perf_event *last_hit_ubp[2];
	struct arch_hw_breakpoint hw_brk[2];
	long unsigned int trap_nr;
	u8 load_slb;
	u8 load_fp;
	u8 load_vec;
	long: 40;
	struct thread_vr_state vr_state;
	struct thread_vr_state *vr_save_area;
	long unsigned int vrsave;
	int used_vr;
	int used_vsr;
	u8 load_tm;
	u64 tm_tfhar;
	u64 tm_texasr;
	u64 tm_tfiar;
	struct pt_regs ckpt_regs;
	long unsigned int tm_tar;
	long unsigned int tm_ppr;
	long unsigned int tm_dscr;
	long unsigned int tm_amr;
	long: 64;
	struct thread_fp_state ckfp_state;
	struct thread_vr_state ckvr_state;
	long unsigned int ckvrsave;
	long unsigned int dscr;
	long unsigned int fscr;
	int dscr_inherit;
	long unsigned int tidr;
	long unsigned int tar;
	long unsigned int ebbrr;
	long unsigned int ebbhr;
	long unsigned int bescr;
	long unsigned int siar;
	long unsigned int sdar;
	long unsigned int sier;
	long unsigned int mmcr2;
	unsigned int mmcr0;
	unsigned int used_ebb;
	long unsigned int mmcr3;
	long unsigned int sier2;
	long unsigned int sier3;
	long: 64;
};

struct sched_class;

struct task_group;

struct pid;

struct completion;

struct cred;

struct key;

struct nameidata;

struct fs_struct;

struct files_struct;

struct nsproxy;

struct signal_struct;

struct sighand_struct;

struct audit_context;

struct rt_mutex_waiter;

struct bio_list;

struct blk_plug;

struct reclaim_state;

struct backing_dev_info;

struct io_context;

struct capture_control;

struct kernel_siginfo;

typedef struct kernel_siginfo kernel_siginfo_t;

struct css_set;

struct robust_list_head;

struct futex_pi_state;

struct perf_event_context;

struct mempolicy;

struct numa_group;

struct rseq;

struct task_delay_info;

struct kunit;

struct ftrace_ret_stack;

struct mem_cgroup;

struct request_queue;

struct uprobe_task;

struct bpf_local_storage;

struct bpf_run_ctx;

struct task_struct {
	struct thread_info thread_info;
	unsigned int __state;
	void *stack;
	refcount_t usage;
	unsigned int flags;
	unsigned int ptrace;
	int on_cpu;
	struct __call_single_node wake_entry;
	unsigned int cpu;
	unsigned int wakee_flips;
	long unsigned int wakee_flip_decay_ts;
	struct task_struct *last_wakee;
	int recent_used_cpu;
	int wake_cpu;
	int on_rq;
	int prio;
	int static_prio;
	int normal_prio;
	unsigned int rt_priority;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	struct sched_entity se;
	struct sched_rt_entity rt;
	struct sched_dl_entity dl;
	const struct sched_class *sched_class;
	struct rb_node core_node;
	long unsigned int core_cookie;
	unsigned int core_occupation;
	struct task_group *sched_task_group;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct sched_statistics stats;
	unsigned int btrace_seq;
	unsigned int policy;
	int nr_cpus_allowed;
	const cpumask_t *cpus_ptr;
	cpumask_t *user_cpus_ptr;
	cpumask_t cpus_mask;
	void *migration_pending;
	short unsigned int migration_disabled;
	short unsigned int migration_flags;
	int trc_reader_nesting;
	int trc_ipi_to_cpu;
	union rcu_special trc_reader_special;
	bool trc_reader_checked;
	struct list_head trc_holdout_list;
	struct sched_info sched_info;
	struct list_head tasks;
	struct plist_node pushable_tasks;
	struct rb_node pushable_dl_tasks;
	struct mm_struct *mm;
	struct mm_struct *active_mm;
	struct vmacache vmacache;
	struct task_rss_stat rss_stat;
	int exit_state;
	int exit_code;
	int exit_signal;
	int pdeath_signal;
	long unsigned int jobctl;
	unsigned int personality;
	unsigned int sched_reset_on_fork: 1;
	unsigned int sched_contributes_to_load: 1;
	unsigned int sched_migrated: 1;
	unsigned int sched_psi_wake_requeue: 1;
	int: 28;
	unsigned int sched_remote_wakeup: 1;
	unsigned int in_execve: 1;
	unsigned int in_iowait: 1;
	unsigned int restore_sigmask: 1;
	unsigned int in_user_fault: 1;
	unsigned int no_cgroup_migration: 1;
	unsigned int frozen: 1;
	unsigned int use_memdelay: 1;
	unsigned int in_memstall: 1;
	unsigned int in_page_owner: 1;
	unsigned int in_eventfd_signal: 1;
	long unsigned int atomic_flags;
	struct restart_block restart_block;
	pid_t pid;
	pid_t tgid;
	long unsigned int stack_canary;
	struct task_struct *real_parent;
	struct task_struct *parent;
	struct list_head children;
	struct list_head sibling;
	struct task_struct *group_leader;
	struct list_head ptraced;
	struct list_head ptrace_entry;
	struct pid *thread_pid;
	struct hlist_node pid_links[4];
	struct list_head thread_group;
	struct list_head thread_node;
	struct completion *vfork_done;
	int *set_child_tid;
	int *clear_child_tid;
	void *worker_private;
	u64 utime;
	u64 stime;
	u64 gtime;
	struct prev_cputime prev_cputime;
	struct vtime vtime;
	atomic_t tick_dep_mask;
	long unsigned int nvcsw;
	long unsigned int nivcsw;
	u64 start_time;
	u64 start_boottime;
	long unsigned int min_flt;
	long unsigned int maj_flt;
	struct posix_cputimers posix_cputimers;
	const struct cred *ptracer_cred;
	const struct cred *real_cred;
	const struct cred *cred;
	struct key *cached_requested_key;
	char comm[16];
	struct nameidata *nameidata;
	struct sysv_sem sysvsem;
	struct sysv_shm sysvshm;
	long unsigned int last_switch_count;
	long unsigned int last_switch_time;
	struct fs_struct *fs;
	struct files_struct *files;
	struct nsproxy *nsproxy;
	struct signal_struct *signal;
	struct sighand_struct *sighand;
	sigset_t blocked;
	sigset_t real_blocked;
	sigset_t saved_sigmask;
	struct sigpending pending;
	long unsigned int sas_ss_sp;
	size_t sas_ss_size;
	unsigned int sas_ss_flags;
	struct callback_head *task_works;
	struct audit_context *audit_context;
	kuid_t loginuid;
	unsigned int sessionid;
	struct seccomp seccomp;
	struct syscall_user_dispatch syscall_dispatch;
	u64 parent_exec_id;
	u64 self_exec_id;
	spinlock_t alloc_lock;
	raw_spinlock_t pi_lock;
	struct wake_q_node wake_q;
	struct rb_root_cached pi_waiters;
	struct task_struct *pi_top_task;
	struct rt_mutex_waiter *pi_blocked_on;
	void *journal_info;
	struct bio_list *bio_list;
	struct blk_plug *plug;
	struct reclaim_state *reclaim_state;
	struct backing_dev_info *backing_dev_info;
	struct io_context *io_context;
	struct capture_control *capture_control;
	long unsigned int ptrace_message;
	kernel_siginfo_t *last_siginfo;
	struct task_io_accounting ioac;
	unsigned int psi_flags;
	u64 acct_rss_mem1;
	u64 acct_vm_mem1;
	u64 acct_timexpd;
	nodemask_t mems_allowed;
	seqcount_spinlock_t mems_allowed_seq;
	int cpuset_mem_spread_rotor;
	int cpuset_slab_spread_rotor;
	struct css_set *cgroups;
	struct list_head cg_list;
	struct robust_list_head *robust_list;
	struct list_head pi_state_list;
	struct futex_pi_state *pi_state_cache;
	struct mutex futex_exit_mutex;
	unsigned int futex_state;
	struct perf_event_context *perf_event_ctxp[2];
	struct mutex perf_event_mutex;
	struct list_head perf_event_list;
	struct mempolicy *mempolicy;
	short int il_prev;
	short int pref_node_fork;
	int numa_scan_seq;
	unsigned int numa_scan_period;
	unsigned int numa_scan_period_max;
	int numa_preferred_nid;
	long unsigned int numa_migrate_retry;
	u64 node_stamp;
	u64 last_task_numa_placement;
	u64 last_sum_exec_runtime;
	struct callback_head numa_work;
	struct numa_group *numa_group;
	long unsigned int *numa_faults;
	long unsigned int total_numa_faults;
	long unsigned int numa_faults_locality[3];
	long unsigned int numa_pages_migrated;
	struct rseq *rseq;
	u32 rseq_sig;
	long unsigned int rseq_event_mask;
	struct tlbflush_unmap_batch tlb_ubc;
	union {
		refcount_t rcu_users;
		struct callback_head rcu;
	};
	struct pipe_inode_info *splice_pipe;
	struct page_frag task_frag;
	struct task_delay_info *delays;
	int nr_dirtied;
	int nr_dirtied_pause;
	long unsigned int dirty_paused_when;
	u64 timer_slack_ns;
	u64 default_timer_slack_ns;
	struct kunit *kunit_test;
	int curr_ret_stack;
	int curr_ret_depth;
	struct ftrace_ret_stack *ret_stack;
	long long unsigned int ftrace_timestamp;
	atomic_t trace_overrun;
	atomic_t tracing_graph_pause;
	long unsigned int trace;
	long unsigned int trace_recursion;
	struct mem_cgroup *memcg_in_oom;
	gfp_t memcg_oom_gfp_mask;
	int memcg_oom_order;
	unsigned int memcg_nr_pages_over_high;
	struct mem_cgroup *active_memcg;
	struct request_queue *throttle_queue;
	struct uprobe_task *utask;
	struct kmap_ctrl kmap_ctrl;
	int pagefault_disabled;
	struct task_struct *oom_reaper_list;
	struct timer_list oom_reaper_timer;
	refcount_t stack_refcount;
	int patch_state;
	void *security;
	struct bpf_local_storage *bpf_storage;
	struct bpf_run_ctx *bpf_ctx;
	struct llist_head kretprobe_instances;
	union {
		struct {
			int rh_kabi_dummy;
		};
		struct {
			long int rh_reserved[64];
		} rh_kabi_hidden_1522;
	};
	struct thread_struct thread;
	long: 64;
	long: 64;
};

typedef __be32 rtas_arg_t;

struct rtas_args {
	__be32 token;
	__be32 nargs;
	__be32 nret;
	rtas_arg_t args[16];
	rtas_arg_t *rets;
};

typedef struct {
	arch_rwlock_t raw_lock;
} rwlock_t;

typedef struct {
	__u8 b[16];
} uuid_t;

enum pcpu_fc {
	PCPU_FC_AUTO = 0,
	PCPU_FC_EMBED = 1,
	PCPU_FC_PAGE = 2,
	PCPU_FC_NR = 3,
};

struct wait_queue_head {
	spinlock_t lock;
	struct list_head head;
};

typedef struct wait_queue_head wait_queue_head_t;

struct seqcount_raw_spinlock {
	seqcount_t seqcount;
};

typedef struct seqcount_raw_spinlock seqcount_raw_spinlock_t;

typedef struct {
	seqcount_spinlock_t seqcount;
	spinlock_t lock;
} seqlock_t;

enum node_states {
	N_POSSIBLE = 0,
	N_ONLINE = 1,
	N_NORMAL_MEMORY = 2,
	N_HIGH_MEMORY = 2,
	N_MEMORY = 3,
	N_CPU = 4,
	N_GENERIC_INITIATOR = 5,
	NR_NODE_STATES = 6,
};

struct userfaultfd_ctx;

struct vm_userfaultfd_ctx {
	struct userfaultfd_ctx *ctx;
};

struct anon_vma_name;

struct anon_vma;

struct vm_operations_struct;

struct vm_area_struct {
	long unsigned int vm_start;
	long unsigned int vm_end;
	struct vm_area_struct *vm_next;
	struct vm_area_struct *vm_prev;
	struct rb_node vm_rb;
	long unsigned int rb_subtree_gap;
	struct mm_struct *vm_mm;
	pgprot_t vm_page_prot;
	long unsigned int vm_flags;
	union {
		struct {
			struct rb_node rb;
			long unsigned int rb_subtree_last;
		} shared;
		struct anon_vma_name *anon_name;
	};
	struct list_head anon_vma_chain;
	struct anon_vma *anon_vma;
	const struct vm_operations_struct *vm_ops;
	long unsigned int vm_pgoff;
	struct file *vm_file;
	void *vm_private_data;
	atomic_long_t swap_readahead_info;
	struct mempolicy *vm_policy;
	struct vm_userfaultfd_ctx vm_userfaultfd_ctx;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
};

enum {
	MM_FILEPAGES = 0,
	MM_ANONPAGES = 1,
	MM_SWAPENTS = 2,
	MM_SHMEMPAGES = 3,
	NR_MM_COUNTERS = 4,
};

struct mm_rss_stat {
	atomic_long_t count[4];
};

struct kref {
	refcount_t refcount;
};

struct rw_semaphore {
	atomic_long_t count;
	atomic_long_t owner;
	struct optimistic_spin_queue osq;
	raw_spinlock_t wait_lock;
	struct list_head wait_list;
};

struct swait_queue_head {
	raw_spinlock_t lock;
	struct list_head task_list;
};

struct completion {
	unsigned int done;
	struct swait_queue_head wait;
};

struct xol_area;

struct uprobes_state {
	struct xol_area *xol_area;
};

struct work_struct;

typedef void (*work_func_t)(struct work_struct *);

struct work_struct {
	atomic_long_t data;
	struct list_head entry;
	work_func_t func;
};

struct linux_binfmt;

struct kioctx_table;

struct user_namespace;

struct mmu_notifier_subscriptions;

struct mm_struct {
	struct {
		struct vm_area_struct *mmap;
		struct rb_root mm_rb;
		u64 vmacache_seqnum;
		long unsigned int (*get_unmapped_area)(struct file *, long unsigned int, long unsigned int, long unsigned int, long unsigned int);
		long unsigned int mmap_base;
		long unsigned int mmap_legacy_base;
		long unsigned int task_size;
		long unsigned int highest_vm_end;
		pgd_t *pgd;
		atomic_t membarrier_state;
		atomic_t mm_users;
		atomic_t mm_count;
		atomic_long_t pgtables_bytes;
		int map_count;
		spinlock_t page_table_lock;
		struct rw_semaphore mmap_lock;
		struct list_head mmlist;
		long unsigned int hiwater_rss;
		long unsigned int hiwater_vm;
		long unsigned int total_vm;
		long unsigned int locked_vm;
		atomic64_t pinned_vm;
		long unsigned int data_vm;
		long unsigned int exec_vm;
		long unsigned int stack_vm;
		long unsigned int def_flags;
		seqcount_t write_protect_seq;
		spinlock_t arg_lock;
		long unsigned int start_code;
		long unsigned int end_code;
		long unsigned int start_data;
		long unsigned int end_data;
		long unsigned int start_brk;
		long unsigned int brk;
		long unsigned int start_stack;
		long unsigned int arg_start;
		long unsigned int arg_end;
		long unsigned int env_start;
		long unsigned int env_end;
		long unsigned int saved_auxv[70];
		struct mm_rss_stat rss_stat;
		struct linux_binfmt *binfmt;
		mm_context_t context;
		long unsigned int flags;
		spinlock_t ioctx_lock;
		struct kioctx_table *ioctx_table;
		struct task_struct *owner;
		struct user_namespace *user_ns;
		struct file *exe_file;
		struct mmu_notifier_subscriptions *notifier_subscriptions;
		long unsigned int numa_next_scan;
		long unsigned int numa_scan_offset;
		int numa_scan_seq;
		atomic_t tlb_flush_pending;
		struct uprobes_state uprobes_state;
		atomic_long_t hugetlb_usage;
		struct work_struct async_put_work;
	};
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	long unsigned int rh_reserved5;
	long unsigned int cpu_bitmap[0];
};

struct workqueue_struct;

struct delayed_work {
	struct work_struct work;
	struct timer_list timer;
	struct workqueue_struct *wq;
	int cpu;
};

struct rcu_segcblist {
	struct callback_head *head;
	struct callback_head **tails[4];
	long unsigned int gp_seq[4];
	atomic_long_t len;
	long int seglen[4];
	u8 flags;
};

struct srcu_node;

struct srcu_struct;

struct srcu_data {
	long unsigned int srcu_lock_count[2];
	long unsigned int srcu_unlock_count[2];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	spinlock_t lock;
	struct rcu_segcblist srcu_cblist;
	long unsigned int srcu_gp_seq_needed;
	long unsigned int srcu_gp_seq_needed_exp;
	bool srcu_cblist_invoking;
	struct timer_list delay_work;
	struct work_struct work;
	struct callback_head srcu_barrier_head;
	struct srcu_node *mynode;
	long unsigned int grpmask;
	int cpu;
	struct srcu_struct *ssp;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct srcu_node {
	spinlock_t lock;
	long unsigned int srcu_have_cbs[4];
	long unsigned int srcu_data_have_cbs[4];
	long unsigned int srcu_gp_seq_needed_exp;
	struct srcu_node *srcu_parent;
	int grplo;
	int grphi;
};

struct srcu_struct {
	struct srcu_node *node;
	struct srcu_node *level[4];
	int srcu_size_state;
	struct mutex srcu_cb_mutex;
	spinlock_t lock;
	struct mutex srcu_gp_mutex;
	unsigned int srcu_idx;
	long unsigned int srcu_gp_seq;
	long unsigned int srcu_gp_seq_needed;
	long unsigned int srcu_gp_seq_needed_exp;
	long unsigned int srcu_gp_start;
	long unsigned int srcu_last_gp_end;
	long unsigned int srcu_size_jiffies;
	long unsigned int srcu_n_lock_retries;
	long unsigned int srcu_n_exp_nodelay;
	struct srcu_data *sda;
	bool sda_is_static;
	long unsigned int srcu_barrier_seq;
	struct mutex srcu_barrier_mutex;
	struct completion srcu_barrier_completion;
	atomic_t srcu_barrier_cpu_cnt;
	long unsigned int reschedule_jiffies;
	long unsigned int reschedule_count;
	struct delayed_work work;
	struct lockdep_map dep_map;
};

struct arch_uprobe_task {
	long unsigned int saved_trap_nr;
};

enum uprobe_task_state {
	UTASK_RUNNING = 0,
	UTASK_SSTEP = 1,
	UTASK_SSTEP_ACK = 2,
	UTASK_SSTEP_TRAPPED = 3,
};

struct uprobe;

struct return_instance;

struct uprobe_task {
	enum uprobe_task_state state;
	union {
		struct {
			struct arch_uprobe_task autask;
			long unsigned int vaddr;
		};
		struct {
			struct callback_head dup_xol_work;
			long unsigned int dup_xol_addr;
		};
	};
	struct uprobe *active_uprobe;
	long unsigned int xol_vaddr;
	struct return_instance *return_instances;
	unsigned int depth;
};

struct return_instance {
	struct uprobe *uprobe;
	long unsigned int func;
	long unsigned int stack;
	long unsigned int orig_ret_vaddr;
	bool chained;
	struct return_instance *next;
};

struct xarray {
	spinlock_t xa_lock;
	gfp_t xa_flags;
	void *xa_head;
};

typedef u32 errseq_t;

struct address_space_operations;

struct address_space {
	struct inode *host;
	struct xarray i_pages;
	struct rw_semaphore invalidate_lock;
	gfp_t gfp_mask;
	atomic_t i_mmap_writable;
	struct rb_root_cached i_mmap;
	struct rw_semaphore i_mmap_rwsem;
	long unsigned int nrpages;
	long unsigned int writeback_index;
	const struct address_space_operations *a_ops;
	long unsigned int flags;
	errseq_t wb_err;
	spinlock_t private_lock;
	struct list_head private_list;
	void *private_data;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
};

struct folio {
	union {
		struct {
			long unsigned int flags;
			union {
				struct list_head lru;
				struct {
					void *__filler;
					unsigned int mlock_count;
				};
			};
			struct address_space *mapping;
			long unsigned int index;
			void *private;
			atomic_t _mapcount;
			atomic_t _refcount;
			long unsigned int memcg_data;
		};
		struct page page;
	};
};

struct vfsmount;

struct path {
	struct vfsmount *mnt;
	struct dentry *dentry;
};

enum pid_type {
	PIDTYPE_PID = 0,
	PIDTYPE_TGID = 1,
	PIDTYPE_PGID = 2,
	PIDTYPE_SID = 3,
	PIDTYPE_MAX = 4,
};

struct fown_struct {
	rwlock_t lock;
	struct pid *pid;
	enum pid_type pid_type;
	kuid_t uid;
	kuid_t euid;
	int signum;
};

struct file_ra_state {
	long unsigned int start;
	unsigned int size;
	unsigned int async_size;
	unsigned int ra_pages;
	unsigned int mmap_miss;
	loff_t prev_pos;
};

struct file {
	union {
		struct llist_node fu_llist;
		struct callback_head fu_rcuhead;
	} f_u;
	struct path f_path;
	struct inode *f_inode;
	const struct file_operations *f_op;
	spinlock_t f_lock;
	atomic_long_t f_count;
	unsigned int f_flags;
	fmode_t f_mode;
	struct mutex f_pos_lock;
	loff_t f_pos;
	struct fown_struct f_owner;
	const struct cred *f_cred;
	struct file_ra_state f_ra;
	u64 f_version;
	void *f_security;
	void *private_data;
	struct hlist_head *f_ep;
	struct address_space *f_mapping;
	errseq_t f_wb_err;
	errseq_t f_sb_err;
};

struct anon_vma_name {
	struct kref kref;
	char name[0];
};

typedef unsigned int vm_fault_t;

enum page_entry_size {
	PE_SIZE_PTE = 0,
	PE_SIZE_PMD = 1,
	PE_SIZE_PUD = 2,
};

struct vm_fault;

struct vm_operations_struct {
	void (*open)(struct vm_area_struct *);
	void (*close)(struct vm_area_struct *);
	int (*may_split)(struct vm_area_struct *, long unsigned int);
	int (*mremap)(struct vm_area_struct *);
	int (*mprotect)(struct vm_area_struct *, long unsigned int, long unsigned int, long unsigned int);
	vm_fault_t (*fault)(struct vm_fault *);
	vm_fault_t (*huge_fault)(struct vm_fault *, enum page_entry_size);
	vm_fault_t (*map_pages)(struct vm_fault *, long unsigned int, long unsigned int);
	long unsigned int (*pagesize)(struct vm_area_struct *);
	vm_fault_t (*page_mkwrite)(struct vm_fault *);
	vm_fault_t (*pfn_mkwrite)(struct vm_fault *);
	int (*access)(struct vm_area_struct *, long unsigned int, void *, int, int);
	const char * (*name)(struct vm_area_struct *);
	int (*set_policy)(struct vm_area_struct *, struct mempolicy *);
	struct mempolicy * (*get_policy)(struct vm_area_struct *, long unsigned int);
	struct page * (*find_special_page)(struct vm_area_struct *, long unsigned int);
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
};

enum fault_flag {
	FAULT_FLAG_WRITE = 1,
	FAULT_FLAG_MKWRITE = 2,
	FAULT_FLAG_ALLOW_RETRY = 4,
	FAULT_FLAG_RETRY_NOWAIT = 8,
	FAULT_FLAG_KILLABLE = 16,
	FAULT_FLAG_TRIED = 32,
	FAULT_FLAG_USER = 64,
	FAULT_FLAG_REMOTE = 128,
	FAULT_FLAG_INSTRUCTION = 256,
	FAULT_FLAG_INTERRUPTIBLE = 512,
	FAULT_FLAG_UNSHARE = 1024,
};

struct vm_fault {
	const struct {
		struct vm_area_struct *vma;
		gfp_t gfp_mask;
		long unsigned int pgoff;
		long unsigned int address;
		long unsigned int real_address;
	};
	enum fault_flag flags;
	pmd_t *pmd;
	pud_t *pud;
	union {
		pte_t orig_pte;
		pmd_t orig_pmd;
	};
	struct page *cow_page;
	struct page *page;
	pte_t *pte;
	spinlock_t *ptl;
	pgtable_t prealloc_pte;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
};

enum migratetype {
	MIGRATE_UNMOVABLE = 0,
	MIGRATE_MOVABLE = 1,
	MIGRATE_RECLAIMABLE = 2,
	MIGRATE_PCPTYPES = 3,
	MIGRATE_HIGHATOMIC = 3,
	MIGRATE_CMA = 4,
	MIGRATE_ISOLATE = 5,
	MIGRATE_TYPES = 6,
};

enum numa_stat_item {
	NUMA_HIT = 0,
	NUMA_MISS = 1,
	NUMA_FOREIGN = 2,
	NUMA_INTERLEAVE_HIT = 3,
	NUMA_LOCAL = 4,
	NUMA_OTHER = 5,
	NR_VM_NUMA_EVENT_ITEMS = 6,
};

enum zone_stat_item {
	NR_FREE_PAGES = 0,
	NR_ZONE_LRU_BASE = 1,
	NR_ZONE_INACTIVE_ANON = 1,
	NR_ZONE_ACTIVE_ANON = 2,
	NR_ZONE_INACTIVE_FILE = 3,
	NR_ZONE_ACTIVE_FILE = 4,
	NR_ZONE_UNEVICTABLE = 5,
	NR_ZONE_WRITE_PENDING = 6,
	NR_MLOCK = 7,
	NR_BOUNCE = 8,
	NR_ZSPAGES = 9,
	NR_FREE_CMA_PAGES = 10,
	NR_VM_ZONE_STAT_ITEMS = 11,
};

enum node_stat_item {
	NR_LRU_BASE = 0,
	NR_INACTIVE_ANON = 0,
	NR_ACTIVE_ANON = 1,
	NR_INACTIVE_FILE = 2,
	NR_ACTIVE_FILE = 3,
	NR_UNEVICTABLE = 4,
	NR_SLAB_RECLAIMABLE_B = 5,
	NR_SLAB_UNRECLAIMABLE_B = 6,
	NR_ISOLATED_ANON = 7,
	NR_ISOLATED_FILE = 8,
	WORKINGSET_NODES = 9,
	WORKINGSET_REFAULT_BASE = 10,
	WORKINGSET_REFAULT_ANON = 10,
	WORKINGSET_REFAULT_FILE = 11,
	WORKINGSET_ACTIVATE_BASE = 12,
	WORKINGSET_ACTIVATE_ANON = 12,
	WORKINGSET_ACTIVATE_FILE = 13,
	WORKINGSET_RESTORE_BASE = 14,
	WORKINGSET_RESTORE_ANON = 14,
	WORKINGSET_RESTORE_FILE = 15,
	WORKINGSET_NODERECLAIM = 16,
	NR_ANON_MAPPED = 17,
	NR_FILE_MAPPED = 18,
	NR_FILE_PAGES = 19,
	NR_FILE_DIRTY = 20,
	NR_WRITEBACK = 21,
	NR_WRITEBACK_TEMP = 22,
	NR_SHMEM = 23,
	NR_SHMEM_THPS = 24,
	NR_SHMEM_PMDMAPPED = 25,
	NR_FILE_THPS = 26,
	NR_FILE_PMDMAPPED = 27,
	NR_ANON_THPS = 28,
	NR_VMSCAN_WRITE = 29,
	NR_VMSCAN_IMMEDIATE = 30,
	NR_DIRTIED = 31,
	NR_WRITTEN = 32,
	NR_THROTTLED_WRITTEN = 33,
	NR_KERNEL_MISC_RECLAIMABLE = 34,
	NR_FOLL_PIN_ACQUIRED = 35,
	NR_FOLL_PIN_RELEASED = 36,
	NR_KERNEL_STACK_KB = 37,
	NR_PAGETABLE = 38,
	NR_SWAPCACHE = 39,
	PGPROMOTE_SUCCESS = 40,
	NR_VM_NODE_STAT_ITEMS = 41,
};

enum lru_list {
	LRU_INACTIVE_ANON = 0,
	LRU_ACTIVE_ANON = 1,
	LRU_INACTIVE_FILE = 2,
	LRU_ACTIVE_FILE = 3,
	LRU_UNEVICTABLE = 4,
	NR_LRU_LISTS = 5,
};

enum vmscan_throttle_state {
	VMSCAN_THROTTLE_WRITEBACK = 0,
	VMSCAN_THROTTLE_ISOLATED = 1,
	VMSCAN_THROTTLE_NOPROGRESS = 2,
	VMSCAN_THROTTLE_CONGESTED = 3,
	NR_VMSCAN_THROTTLE = 4,
};

typedef unsigned int isolate_mode_t;

enum zone_watermarks {
	WMARK_MIN = 0,
	WMARK_LOW = 1,
	WMARK_HIGH = 2,
	WMARK_PROMO = 3,
	NR_WMARK = 4,
};

enum {
	ZONELIST_FALLBACK = 0,
	ZONELIST_NOFALLBACK = 1,
	MAX_ZONELISTS = 2,
};

struct list_lru_node;

struct list_lru {
	struct list_lru_node *node;
	struct list_head list;
	int shrinker_id;
	bool memcg_aware;
	struct xarray xa;
};

struct idr {
	struct xarray idr_rt;
	unsigned int idr_base;
	unsigned int idr_next;
};

typedef struct {
	gid_t val;
} kgid_t;

struct kernfs_root;

struct kernfs_elem_dir {
	long unsigned int subdirs;
	struct rb_root children;
	struct kernfs_root *root;
	long unsigned int rev;
};

struct kernfs_node;

struct kernfs_syscall_ops;

struct kernfs_root {
	struct kernfs_node *kn;
	unsigned int flags;
	struct idr ino_idr;
	u32 last_id_lowbits;
	u32 id_highbits;
	struct kernfs_syscall_ops *syscall_ops;
	struct list_head supers;
	wait_queue_head_t deactivate_waitq;
};

struct kernfs_elem_symlink {
	struct kernfs_node *target_kn;
};

struct kernfs_ops;

struct kernfs_open_node;

struct kernfs_elem_attr {
	const struct kernfs_ops *ops;
	struct kernfs_open_node *open;
	loff_t size;
	struct kernfs_node *notify_next;
};

struct kernfs_iattrs;

struct kernfs_node {
	atomic_t count;
	atomic_t active;
	struct kernfs_node *parent;
	const char *name;
	struct rb_node rb;
	const void *ns;
	unsigned int hash;
	union {
		struct kernfs_elem_dir dir;
		struct kernfs_elem_symlink symlink;
		struct kernfs_elem_attr attr;
	};
	void *priv;
	u64 id;
	short unsigned int flags;
	umode_t mode;
	struct kernfs_iattrs *iattr;
};

struct kernfs_open_file;

struct kernfs_ops {
	int (*open)(struct kernfs_open_file *);
	void (*release)(struct kernfs_open_file *);
	int (*seq_show)(struct seq_file *, void *);
	void * (*seq_start)(struct seq_file *, loff_t *);
	void * (*seq_next)(struct seq_file *, void *, loff_t *);
	void (*seq_stop)(struct seq_file *, void *);
	ssize_t (*read)(struct kernfs_open_file *, char *, size_t, loff_t);
	size_t atomic_write_len;
	bool prealloc;
	ssize_t (*write)(struct kernfs_open_file *, char *, size_t, loff_t);
	__poll_t (*poll)(struct kernfs_open_file *, struct poll_table_struct *);
	int (*mmap)(struct kernfs_open_file *, struct vm_area_struct *);
};

struct kernfs_syscall_ops {
	int (*show_options)(struct seq_file *, struct kernfs_root *);
	int (*mkdir)(struct kernfs_node *, const char *, umode_t);
	int (*rmdir)(struct kernfs_node *);
	int (*rename)(struct kernfs_node *, struct kernfs_node *, const char *);
	int (*show_path)(struct seq_file *, struct kernfs_node *, struct kernfs_root *);
};

struct seq_operations;

struct seq_file {
	char *buf;
	size_t size;
	size_t from;
	size_t count;
	size_t pad_until;
	loff_t index;
	loff_t read_pos;
	struct mutex lock;
	const struct seq_operations *op;
	int poll_event;
	const struct file *file;
	void *private;
};

struct kernfs_open_file {
	struct kernfs_node *kn;
	struct file *file;
	struct seq_file *seq_file;
	void *priv;
	struct mutex mutex;
	struct mutex prealloc_mutex;
	int event;
	struct list_head list;
	char *prealloc_buf;
	size_t atomic_write_len;
	bool mmapped: 1;
	bool released: 1;
	const struct vm_operations_struct *vm_ops;
};

enum kobj_ns_type {
	KOBJ_NS_TYPE_NONE = 0,
	KOBJ_NS_TYPE_NET = 1,
	KOBJ_NS_TYPES = 2,
};

struct sock;

struct kobj_ns_type_operations {
	enum kobj_ns_type type;
	bool (*current_may_mount)();
	void * (*grab_current_ns)();
	const void * (*netlink_ns)(struct sock *);
	const void * (*initial_ns)();
	void (*drop_ns)(void *);
};

struct kstat {
	u32 result_mask;
	umode_t mode;
	unsigned int nlink;
	uint32_t blksize;
	u64 attributes;
	u64 attributes_mask;
	u64 ino;
	dev_t dev;
	dev_t rdev;
	kuid_t uid;
	kgid_t gid;
	loff_t size;
	struct timespec64 atime;
	struct timespec64 mtime;
	struct timespec64 ctime;
	struct timespec64 btime;
	u64 blocks;
	u64 mnt_id;
};

struct attribute {
	const char *name;
	umode_t mode;
};

struct kobject;

struct bin_attribute;

struct attribute_group {
	const char *name;
	umode_t (*is_visible)(struct kobject *, struct attribute *, int);
	umode_t (*is_bin_visible)(struct kobject *, struct bin_attribute *, int);
	struct attribute **attrs;
	struct bin_attribute **bin_attrs;
};

struct kset;

struct kobj_type;

struct kobject {
	const char *name;
	struct list_head entry;
	struct kobject *parent;
	struct kset *kset;
	const struct kobj_type *ktype;
	struct kernfs_node *sd;
	struct kref kref;
	unsigned int state_initialized: 1;
	unsigned int state_in_sysfs: 1;
	unsigned int state_add_uevent_sent: 1;
	unsigned int state_remove_uevent_sent: 1;
	unsigned int uevent_suppress: 1;
};

struct bin_attribute {
	struct attribute attr;
	size_t size;
	void *private;
	struct address_space *mapping;
	ssize_t (*read)(struct file *, struct kobject *, struct bin_attribute *, char *, loff_t, size_t);
	ssize_t (*write)(struct file *, struct kobject *, struct bin_attribute *, char *, loff_t, size_t);
	int (*mmap)(struct file *, struct kobject *, struct bin_attribute *, struct vm_area_struct *);
};

struct sysfs_ops {
	ssize_t (*show)(struct kobject *, struct attribute *, char *);
	ssize_t (*store)(struct kobject *, struct attribute *, const char *, size_t);
};

struct kset_uevent_ops;

struct kset {
	struct list_head list;
	spinlock_t list_lock;
	struct kobject kobj;
	const struct kset_uevent_ops *uevent_ops;
};

struct kobj_type {
	void (*release)(struct kobject *);
	const struct sysfs_ops *sysfs_ops;
	struct attribute **default_attrs;
	const struct attribute_group **default_groups;
	const struct kobj_ns_type_operations * (*child_ns_type)(struct kobject *);
	const void * (*namespace)(struct kobject *);
	void (*get_ownership)(struct kobject *, kuid_t *, kgid_t *);
};

struct kobj_uevent_env {
	char *argv[3];
	char *envp[64];
	int envp_idx;
	char buf[2048];
	int buflen;
};

struct kset_uevent_ops {
	int (* const filter)(struct kobject *);
	const char * (* const name)(struct kobject *);
	int (* const uevent)(struct kobject *, struct kobj_uevent_env *);
};

struct pid_namespace;

struct upid {
	int nr;
	struct pid_namespace *ns;
};

struct proc_ns_operations;

struct ns_common {
	atomic_long_t stashed;
	const struct proc_ns_operations *ops;
	unsigned int inum;
	refcount_t count;
};

struct kmem_cache;

struct fs_pin;

struct ucounts;

struct pid_namespace {
	struct idr idr;
	struct callback_head rcu;
	unsigned int pid_allocated;
	struct task_struct *child_reaper;
	struct kmem_cache *pid_cachep;
	unsigned int level;
	struct pid_namespace *parent;
	struct fs_pin *bacct;
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	int reboot;
	struct ns_common ns;
};

struct pid {
	refcount_t count;
	unsigned int level;
	spinlock_t lock;
	struct hlist_head tasks[4];
	struct hlist_head inodes;
	wait_queue_head_t wait_pidfd;
	struct callback_head rcu;
	struct upid numbers[1];
};

struct hrtimer_cpu_base;

struct hrtimer_clock_base {
	struct hrtimer_cpu_base *cpu_base;
	unsigned int index;
	clockid_t clockid;
	seqcount_raw_spinlock_t seq;
	struct hrtimer *running;
	struct timerqueue_head active;
	ktime_t (*get_time)();
	ktime_t offset;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct hrtimer_cpu_base {
	raw_spinlock_t lock;
	unsigned int cpu;
	unsigned int active_bases;
	unsigned int clock_was_set_seq;
	unsigned int hres_active: 1;
	unsigned int in_hrtirq: 1;
	unsigned int hang_detected: 1;
	unsigned int softirq_activated: 1;
	unsigned int nr_events;
	short unsigned int nr_retries;
	short unsigned int nr_hangs;
	unsigned int max_hang_time;
	ktime_t expires_next;
	struct hrtimer *next_timer;
	ktime_t softirq_expires_next;
	struct hrtimer *softirq_next_timer;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct hrtimer_clock_base clock_base[8];
};

enum hrtimer_base_type {
	HRTIMER_BASE_MONOTONIC = 0,
	HRTIMER_BASE_REALTIME = 1,
	HRTIMER_BASE_BOOTTIME = 2,
	HRTIMER_BASE_TAI = 3,
	HRTIMER_BASE_MONOTONIC_SOFT = 4,
	HRTIMER_BASE_REALTIME_SOFT = 5,
	HRTIMER_BASE_BOOTTIME_SOFT = 6,
	HRTIMER_BASE_TAI_SOFT = 7,
	HRTIMER_MAX_CLOCK_BASES = 8,
};

struct rlimit {
	__kernel_ulong_t rlim_cur;
	__kernel_ulong_t rlim_max;
};

typedef void __signalfn_t(int);

typedef __signalfn_t *__sighandler_t;

typedef void __restorefn_t();

typedef __restorefn_t *__sigrestore_t;

union sigval {
	int sival_int;
	void *sival_ptr;
};

typedef union sigval sigval_t;

union __sifields {
	struct {
		__kernel_pid_t _pid;
		__kernel_uid32_t _uid;
	} _kill;
	struct {
		__kernel_timer_t _tid;
		int _overrun;
		sigval_t _sigval;
		int _sys_private;
	} _timer;
	struct {
		__kernel_pid_t _pid;
		__kernel_uid32_t _uid;
		sigval_t _sigval;
	} _rt;
	struct {
		__kernel_pid_t _pid;
		__kernel_uid32_t _uid;
		int _status;
		__kernel_clock_t _utime;
		__kernel_clock_t _stime;
	} _sigchld;
	struct {
		void *_addr;
		union {
			int _trapno;
			short int _addr_lsb;
			struct {
				char _dummy_bnd[8];
				void *_lower;
				void *_upper;
			} _addr_bnd;
			struct {
				char _dummy_pkey[8];
				__u32 _pkey;
			} _addr_pkey;
			struct {
				long unsigned int _data;
				__u32 _type;
				__u32 _flags;
			} _perf;
		};
	} _sigfault;
	struct {
		long int _band;
		int _fd;
	} _sigpoll;
	struct {
		void *_call_addr;
		int _syscall;
		unsigned int _arch;
	} _sigsys;
};

struct kernel_siginfo {
	struct {
		int si_signo;
		int si_errno;
		int si_code;
		union __sifields _sifields;
	};
};

struct sigaction {
	__sighandler_t sa_handler;
	long unsigned int sa_flags;
	__sigrestore_t sa_restorer;
	sigset_t sa_mask;
};

struct k_sigaction {
	struct sigaction sa;
};

struct cpu_itimer {
	u64 expires;
	u64 incr;
};

struct task_cputime_atomic {
	atomic64_t utime;
	atomic64_t stime;
	atomic64_t sum_exec_runtime;
};

struct thread_group_cputimer {
	struct task_cputime_atomic cputime_atomic;
};

struct pacct_struct {
	int ac_flag;
	long int ac_exitcode;
	long unsigned int ac_mem;
	u64 ac_utime;
	u64 ac_stime;
	long unsigned int ac_minflt;
	long unsigned int ac_majflt;
};

struct core_state;

struct tty_struct;

struct autogroup;

struct taskstats;

struct tty_audit_buf;

struct signal_struct {
	refcount_t sigcnt;
	atomic_t live;
	int nr_threads;
	struct list_head thread_head;
	wait_queue_head_t wait_chldexit;
	struct task_struct *curr_target;
	struct sigpending shared_pending;
	struct hlist_head multiprocess;
	int group_exit_code;
	int notify_count;
	struct task_struct *group_exec_task;
	int group_stop_count;
	unsigned int flags;
	struct core_state *core_state;
	unsigned int is_child_subreaper: 1;
	unsigned int has_child_subreaper: 1;
	int posix_timer_id;
	struct list_head posix_timers;
	struct hrtimer real_timer;
	ktime_t it_real_incr;
	struct cpu_itimer it[2];
	struct thread_group_cputimer cputimer;
	struct posix_cputimers posix_cputimers;
	struct pid *pids[4];
	atomic_t tick_dep_mask;
	struct pid *tty_old_pgrp;
	int leader;
	struct tty_struct *tty;
	struct autogroup *autogroup;
	seqlock_t stats_lock;
	u64 utime;
	u64 stime;
	u64 cutime;
	u64 cstime;
	u64 gtime;
	u64 cgtime;
	struct prev_cputime prev_cputime;
	long unsigned int nvcsw;
	long unsigned int nivcsw;
	long unsigned int cnvcsw;
	long unsigned int cnivcsw;
	long unsigned int min_flt;
	long unsigned int maj_flt;
	long unsigned int cmin_flt;
	long unsigned int cmaj_flt;
	long unsigned int inblock;
	long unsigned int oublock;
	long unsigned int cinblock;
	long unsigned int coublock;
	long unsigned int maxrss;
	long unsigned int cmaxrss;
	struct task_io_accounting ioac;
	long long unsigned int sum_sched_runtime;
	struct rlimit rlim[16];
	struct pacct_struct pacct;
	struct taskstats *stats;
	unsigned int audit_tty;
	struct tty_audit_buf *tty_audit_buf;
	bool oom_flag_origin;
	short int oom_score_adj;
	short int oom_score_adj_min;
	struct mm_struct *oom_mm;
	struct mutex cred_guard_mutex;
	struct rw_semaphore exec_update_lock;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
};

enum rseq_cs_flags_bit {
	RSEQ_CS_FLAG_NO_RESTART_ON_PREEMPT_BIT = 0,
	RSEQ_CS_FLAG_NO_RESTART_ON_SIGNAL_BIT = 1,
	RSEQ_CS_FLAG_NO_RESTART_ON_MIGRATE_BIT = 2,
};

struct rseq {
	__u32 cpu_id_start;
	__u32 cpu_id;
	union {
		__u64 ptr64;
		__u64 ptr;
	} rseq_cs;
	__u32 flags;
	long: 32;
	long: 64;
};

enum {
	TASK_COMM_LEN = 16,
};

enum perf_event_task_context {
	perf_invalid_context = 4294967295,
	perf_hw_context = 0,
	perf_sw_context = 1,
	perf_nr_task_contexts = 2,
};

struct rq;

struct rq_flags;

struct affinity_context;

struct sched_class {
	void (*enqueue_task)(struct rq *, struct task_struct *, int);
	void (*dequeue_task)(struct rq *, struct task_struct *, int);
	void (*yield_task)(struct rq *);
	bool (*yield_to_task)(struct rq *, struct task_struct *);
	void (*check_preempt_curr)(struct rq *, struct task_struct *, int);
	struct task_struct * (*pick_next_task)(struct rq *);
	void (*put_prev_task)(struct rq *, struct task_struct *);
	void (*set_next_task)(struct rq *, struct task_struct *, bool);
	int (*balance)(struct rq *, struct task_struct *, struct rq_flags *);
	int (*select_task_rq)(struct task_struct *, int, int);
	struct task_struct * (*pick_task)(struct rq *);
	void (*migrate_task_rq)(struct task_struct *, int);
	void (*task_woken)(struct rq *, struct task_struct *);
	void (*set_cpus_allowed)(struct task_struct *, struct affinity_context *);
	void (*rq_online)(struct rq *);
	void (*rq_offline)(struct rq *);
	struct rq * (*find_lock_rq)(struct task_struct *, struct rq *);
	void (*task_tick)(struct rq *, struct task_struct *, int);
	void (*task_fork)(struct task_struct *);
	void (*task_dead)(struct task_struct *);
	void (*switched_from)(struct rq *, struct task_struct *);
	void (*switched_to)(struct rq *, struct task_struct *);
	void (*prio_changed)(struct rq *, struct task_struct *, int);
	unsigned int (*get_rr_interval)(struct rq *, struct task_struct *);
	void (*update_curr)(struct rq *);
	void (*task_change_group)(struct task_struct *, int);
};

struct kernel_cap_struct {
	__u32 cap[2];
};

typedef struct kernel_cap_struct kernel_cap_t;

struct user_struct;

struct group_info;

struct cred {
	atomic_t usage;
	kuid_t uid;
	kgid_t gid;
	kuid_t suid;
	kgid_t sgid;
	kuid_t euid;
	kgid_t egid;
	kuid_t fsuid;
	kgid_t fsgid;
	unsigned int securebits;
	kernel_cap_t cap_inheritable;
	kernel_cap_t cap_permitted;
	kernel_cap_t cap_effective;
	kernel_cap_t cap_bset;
	kernel_cap_t cap_ambient;
	unsigned char jit_keyring;
	struct key *session_keyring;
	struct key *process_keyring;
	struct key *thread_keyring;
	struct key *request_key_auth;
	void *security;
	struct user_struct *user;
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	struct group_info *group_info;
	union {
		int non_rcu;
		struct callback_head rcu;
	};
};

typedef int32_t key_serial_t;

typedef uint32_t key_perm_t;

struct key_type;

struct key_tag;

struct keyring_index_key {
	long unsigned int hash;
	union {
		struct {
			u16 desc_len;
			char desc[6];
		};
		long unsigned int x;
	};
	struct key_type *type;
	struct key_tag *domain_tag;
	const char *description;
};

union key_payload {
	void *rcu_data0;
	void *data[4];
};

struct assoc_array_ptr;

struct assoc_array {
	struct assoc_array_ptr *root;
	long unsigned int nr_leaves_on_tree;
};

struct watch_list;

struct key_user;

struct key_restriction;

struct key {
	refcount_t usage;
	key_serial_t serial;
	union {
		struct list_head graveyard_link;
		struct rb_node serial_node;
	};
	struct watch_list *watchers;
	struct rw_semaphore sem;
	struct key_user *user;
	void *security;
	union {
		time64_t expiry;
		time64_t revoked_at;
	};
	time64_t last_used_at;
	kuid_t uid;
	kgid_t gid;
	key_perm_t perm;
	short unsigned int quotalen;
	short unsigned int datalen;
	short int state;
	long unsigned int flags;
	union {
		struct keyring_index_key index_key;
		struct {
			long unsigned int hash;
			long unsigned int len_desc;
			struct key_type *type;
			struct key_tag *domain_tag;
			char *description;
		};
	};
	union {
		union key_payload payload;
		struct {
			struct list_head name_link;
			struct assoc_array keys;
		};
	};
	struct key_restriction *restrict_link;
};

struct uts_namespace;

struct ipc_namespace;

struct mnt_namespace;

struct net;

struct time_namespace;

struct cgroup_namespace;

struct nsproxy {
	atomic_t count;
	struct uts_namespace *uts_ns;
	struct ipc_namespace *ipc_ns;
	struct mnt_namespace *mnt_ns;
	struct pid_namespace *pid_ns_for_children;
	struct net *net_ns;
	struct time_namespace *time_ns;
	struct time_namespace *time_ns_for_children;
	struct cgroup_namespace *cgroup_ns;
};

struct sighand_struct {
	spinlock_t siglock;
	refcount_t count;
	wait_queue_head_t signalfd_wqh;
	struct k_sigaction action[64];
};

struct io_cq;

struct io_context {
	atomic_long_t refcount;
	atomic_t active_ref;
	short unsigned int ioprio;
	spinlock_t lock;
	struct xarray icq_tree;
	struct io_cq *icq_hint;
	struct hlist_head icq_list;
	struct work_struct release_work;
};

enum rseq_event_mask_bits {
	RSEQ_EVENT_PREEMPT_BIT = 0,
	RSEQ_EVENT_SIGNAL_BIT = 1,
	RSEQ_EVENT_MIGRATE_BIT = 2,
};

enum cpu_idle_type {
	CPU_IDLE = 0,
	CPU_NOT_IDLE = 1,
	CPU_NEWLY_IDLE = 2,
	CPU_MAX_IDLE_TYPES = 3,
};

enum {
	__SD_BALANCE_NEWIDLE = 0,
	__SD_BALANCE_EXEC = 1,
	__SD_BALANCE_FORK = 2,
	__SD_BALANCE_WAKE = 3,
	__SD_WAKE_AFFINE = 4,
	__SD_ASYM_CPUCAPACITY = 5,
	__SD_ASYM_CPUCAPACITY_FULL = 6,
	__SD_SHARE_CPUCAPACITY = 7,
	__SD_SHARE_PKG_RESOURCES = 8,
	__SD_SERIALIZE = 9,
	__SD_ASYM_PACKING = 10,
	__SD_PREFER_SIBLING = 11,
	__SD_OVERLAP = 12,
	__SD_NUMA = 13,
	__SD_FLAG_CNT = 14,
};

enum module_state {
	MODULE_STATE_LIVE = 0,
	MODULE_STATE_COMING = 1,
	MODULE_STATE_GOING = 2,
	MODULE_STATE_UNFORMED = 3,
};

struct module_param_attrs;

struct module_kobject {
	struct kobject kobj;
	struct module *mod;
	struct kobject *drivers_dir;
	struct module_param_attrs *mp;
	struct completion *kobj_completion;
};

struct latch_tree_node {
	struct rb_node node[2];
};

struct mod_tree_node {
	struct module *mod;
	struct latch_tree_node node;
};

struct module_layout {
	void *base;
	unsigned int size;
	unsigned int text_size;
	unsigned int ro_size;
	unsigned int ro_after_init_size;
	struct mod_tree_node mtn;
};

struct mod_arch_specific {
	unsigned int stubs_section;
	unsigned int toc_section;
	bool toc_fixed;
	long unsigned int start_opd;
	long unsigned int end_opd;
	long unsigned int tramp;
	long unsigned int tramp_regs;
	struct list_head bug_list;
	struct bug_entry *bug_table;
	unsigned int num_bugs;
};

struct elf64_sym;

typedef struct elf64_sym Elf64_Sym;

struct mod_kallsyms {
	Elf64_Sym *symtab;
	unsigned int num_symtab;
	char *strtab;
	char *typetab;
};

struct module_attribute;

struct kernel_param;

struct exception_table_entry;

struct module_sect_attrs;

struct module_notes_attrs;

struct tracepoint;

typedef struct tracepoint * const tracepoint_ptr_t;

struct bpf_raw_event_map;

struct trace_event_call;

struct trace_eval_map;

struct klp_modinfo;

struct error_injection_entry;

struct module {
	enum module_state state;
	struct list_head list;
	char name[56];
	struct module_kobject mkobj;
	struct module_attribute *modinfo_attrs;
	const char *version;
	const char *srcversion;
	const char *rhelversion;
	struct kobject *holders_dir;
	const struct kernel_symbol *syms;
	const s32 *crcs;
	unsigned int num_syms;
	struct mutex param_lock;
	struct kernel_param *kp;
	unsigned int num_kp;
	unsigned int num_gpl_syms;
	const struct kernel_symbol *gpl_syms;
	const s32 *gpl_crcs;
	bool using_gplonly_symbols;
	bool sig_ok;
	bool async_probe_requested;
	unsigned int num_exentries;
	struct exception_table_entry *extable;
	int (*init)();
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct module_layout core_layout;
	struct module_layout init_layout;
	struct mod_arch_specific arch;
	long unsigned int taints;
	unsigned int num_bugs;
	struct list_head bug_list;
	struct bug_entry *bug_table;
	struct mod_kallsyms *kallsyms;
	struct mod_kallsyms core_kallsyms;
	struct module_sect_attrs *sect_attrs;
	struct module_notes_attrs *notes_attrs;
	char *args;
	void *percpu;
	unsigned int percpu_size;
	void *noinstr_text_start;
	unsigned int noinstr_text_size;
	unsigned int num_tracepoints;
	tracepoint_ptr_t *tracepoints_ptrs;
	unsigned int num_srcu_structs;
	struct srcu_struct **srcu_struct_ptrs;
	unsigned int num_bpf_raw_events;
	struct bpf_raw_event_map *bpf_raw_events;
	unsigned int btf_data_size;
	void *btf_data;
	struct jump_entry *jump_entries;
	unsigned int num_jump_entries;
	unsigned int num_trace_bprintk_fmt;
	const char **trace_bprintk_fmt_start;
	struct trace_event_call **trace_events;
	unsigned int num_trace_events;
	struct trace_eval_map **trace_evals;
	unsigned int num_trace_evals;
	unsigned int num_ftrace_callsites;
	long unsigned int *ftrace_callsites;
	void *kprobes_text_start;
	unsigned int kprobes_text_size;
	long unsigned int *kprobe_blacklist;
	unsigned int num_kprobe_blacklist;
	bool klp;
	bool klp_alive;
	struct klp_modinfo *klp_info;
	unsigned int printk_index_size;
	struct pi_entry **printk_index_start;
	struct list_head source_list;
	struct list_head target_list;
	void (*exit)();
	atomic_t refcnt;
	struct error_injection_entry *ei_funcs;
	unsigned int num_ei_funcs;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
};

typedef __u64 Elf64_Addr;

typedef __u16 Elf64_Half;

typedef __u64 Elf64_Off;

typedef __u32 Elf64_Word;

typedef __u64 Elf64_Xword;

struct elf64_sym {
	Elf64_Word st_name;
	unsigned char st_info;
	unsigned char st_other;
	Elf64_Half st_shndx;
	Elf64_Addr st_value;
	Elf64_Xword st_size;
};

struct elf64_hdr {
	unsigned char e_ident[16];
	Elf64_Half e_type;
	Elf64_Half e_machine;
	Elf64_Word e_version;
	Elf64_Addr e_entry;
	Elf64_Off e_phoff;
	Elf64_Off e_shoff;
	Elf64_Word e_flags;
	Elf64_Half e_ehsize;
	Elf64_Half e_phentsize;
	Elf64_Half e_phnum;
	Elf64_Half e_shentsize;
	Elf64_Half e_shnum;
	Elf64_Half e_shstrndx;
};

typedef struct elf64_hdr Elf64_Ehdr;

struct elf64_shdr {
	Elf64_Word sh_name;
	Elf64_Word sh_type;
	Elf64_Xword sh_flags;
	Elf64_Addr sh_addr;
	Elf64_Off sh_offset;
	Elf64_Xword sh_size;
	Elf64_Word sh_link;
	Elf64_Word sh_info;
	Elf64_Xword sh_addralign;
	Elf64_Xword sh_entsize;
};

typedef struct elf64_shdr Elf64_Shdr;

struct kernel_param_ops {
	unsigned int flags;
	int (*set)(const char *, const struct kernel_param *);
	int (*get)(char *, const struct kernel_param *);
	void (*free)(void *);
};

struct kparam_string;

struct kparam_array;

struct kernel_param {
	const char *name;
	struct module *mod;
	const struct kernel_param_ops *ops;
	const u16 perm;
	s8 level;
	u8 flags;
	union {
		void *arg;
		const struct kparam_string *str;
		const struct kparam_array *arr;
	};
};

struct kparam_string {
	unsigned int maxlen;
	char *string;
};

struct kparam_array {
	unsigned int max;
	unsigned int elemsize;
	unsigned int *num;
	const struct kernel_param_ops *ops;
	void *elem;
};

struct error_injection_entry {
	long unsigned int addr;
	int etype;
};

struct tracepoint_func {
	void *func;
	void *data;
	int prio;
};

struct tracepoint {
	const char *name;
	struct static_key key;
	struct static_call_key *static_call_key;
	void *static_call_tramp;
	void *iterator;
	int (*regfunc)();
	void (*unregfunc)();
	struct tracepoint_func *funcs;
};

struct bpf_raw_event_map {
	struct tracepoint *tp;
	void *bpf_func;
	u32 num_args;
	u32 writable_size;
	long: 64;
};

struct module_attribute {
	struct attribute attr;
	ssize_t (*show)(struct module_attribute *, struct module_kobject *, char *);
	ssize_t (*store)(struct module_attribute *, struct module_kobject *, const char *, size_t);
	void (*setup)(struct module *, const char *);
	int (*test)(struct module *);
	void (*free)(struct module *);
};

struct klp_modinfo {
	Elf64_Ehdr hdr;
	Elf64_Shdr *sechdrs;
	char *secstrings;
	unsigned int symndx;
};

struct exception_table_entry {
	int insn;
	int fixup;
};

struct shrink_control {
	gfp_t gfp_mask;
	int nid;
	long unsigned int nr_to_scan;
	long unsigned int nr_scanned;
	struct mem_cgroup *memcg;
};

struct shrinker {
	long unsigned int (*count_objects)(struct shrinker *, struct shrink_control *);
	long unsigned int (*scan_objects)(struct shrinker *, struct shrink_control *);
	long int batch;
	int seeks;
	unsigned int flags;
	struct list_head list;
	int id;
	atomic_long_t *nr_deferred;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

struct hlist_bl_node;

struct hlist_bl_head {
	struct hlist_bl_node *first;
};

struct hlist_bl_node {
	struct hlist_bl_node *next;
	struct hlist_bl_node **pprev;
};

struct lockref {
	union {
		__u64 lock_count;
		struct {
			spinlock_t lock;
			int count;
		};
	};
};

struct qstr {
	union {
		struct {
			u32 hash;
			u32 len;
		};
		u64 hash_len;
	};
	const unsigned char *name;
};

struct dentry_operations;

struct dentry {
	unsigned int d_flags;
	seqcount_spinlock_t d_seq;
	struct hlist_bl_node d_hash;
	struct dentry *d_parent;
	struct qstr d_name;
	struct inode *d_inode;
	unsigned char d_iname[32];
	struct lockref d_lockref;
	const struct dentry_operations *d_op;
	struct super_block *d_sb;
	long unsigned int d_time;
	void *d_fsdata;
	union {
		struct list_head d_lru;
		wait_queue_head_t *d_wait;
	};
	struct list_head d_child;
	struct list_head d_subdirs;
	union {
		struct hlist_node d_alias;
		struct hlist_bl_node d_in_lookup_hash;
		struct callback_head d_rcu;
	} d_u;
};

struct posix_acl;

struct inode_operations;

struct bdi_writeback;

struct file_lock_context;

struct cdev;

struct fsnotify_mark_connector;

struct inode {
	umode_t i_mode;
	short unsigned int i_opflags;
	kuid_t i_uid;
	kgid_t i_gid;
	unsigned int i_flags;
	struct posix_acl *i_acl;
	struct posix_acl *i_default_acl;
	const struct inode_operations *i_op;
	struct super_block *i_sb;
	struct address_space *i_mapping;
	void *i_security;
	long unsigned int i_ino;
	union {
		const unsigned int i_nlink;
		unsigned int __i_nlink;
	};
	dev_t i_rdev;
	loff_t i_size;
	struct timespec64 i_atime;
	struct timespec64 i_mtime;
	struct timespec64 i_ctime;
	spinlock_t i_lock;
	short unsigned int i_bytes;
	u8 i_blkbits;
	u8 i_write_hint;
	blkcnt_t i_blocks;
	long unsigned int i_state;
	struct rw_semaphore i_rwsem;
	long unsigned int dirtied_when;
	long unsigned int dirtied_time_when;
	struct hlist_node i_hash;
	struct list_head i_io_list;
	struct bdi_writeback *i_wb;
	int i_wb_frn_winner;
	u16 i_wb_frn_avg_time;
	u16 i_wb_frn_history;
	struct list_head i_lru;
	struct list_head i_sb_list;
	struct list_head i_wb_list;
	union {
		struct hlist_head i_dentry;
		struct callback_head i_rcu;
	};
	atomic64_t i_version;
	atomic64_t i_sequence;
	atomic_t i_count;
	atomic_t i_dio_count;
	atomic_t i_writecount;
	atomic_t i_readcount;
	union {
		const struct file_operations *i_fop;
		void (*free_inode)(struct inode *);
	};
	struct file_lock_context *i_flctx;
	struct address_space i_data;
	struct list_head i_devices;
	union {
		struct pipe_inode_info *i_pipe;
		struct cdev *i_cdev;
		char *i_link;
		unsigned int i_dir_seq;
	};
	__u32 i_generation;
	__u32 i_fsnotify_mask;
	struct fsnotify_mark_connector *i_fsnotify_marks;
	void *i_private;
};

struct dentry_operations {
	int (*d_revalidate)(struct dentry *, unsigned int);
	int (*d_weak_revalidate)(struct dentry *, unsigned int);
	int (*d_hash)(const struct dentry *, struct qstr *);
	int (*d_compare)(const struct dentry *, unsigned int, const char *, const struct qstr *);
	int (*d_delete)(const struct dentry *);
	int (*d_init)(struct dentry *);
	void (*d_release)(struct dentry *);
	void (*d_prune)(struct dentry *);
	void (*d_iput)(struct dentry *, struct inode *);
	char * (*d_dname)(struct dentry *, char *, int);
	struct vfsmount * (*d_automount)(struct path *);
	int (*d_manage)(const struct path *, bool);
	struct dentry * (*d_real)(struct dentry *, const struct inode *);
	long: 64;
	long: 64;
	long: 64;
};

struct mtd_info;

typedef long long int qsize_t;

struct quota_format_type;

struct mem_dqinfo {
	struct quota_format_type *dqi_format;
	int dqi_fmt_id;
	struct list_head dqi_dirty_list;
	long unsigned int dqi_flags;
	unsigned int dqi_bgrace;
	unsigned int dqi_igrace;
	qsize_t dqi_max_spc_limit;
	qsize_t dqi_max_ino_limit;
	void *dqi_priv;
};

struct quota_format_ops;

struct quota_info {
	unsigned int flags;
	struct rw_semaphore dqio_sem;
	struct inode *files[3];
	struct mem_dqinfo info[3];
	const struct quota_format_ops *ops[3];
};

struct rcu_sync {
	int gp_state;
	int gp_count;
	wait_queue_head_t gp_wait;
	struct callback_head cb_head;
};

struct rcuwait {
	struct task_struct *task;
};

struct percpu_rw_semaphore {
	struct rcu_sync rss;
	unsigned int *read_count;
	struct rcuwait writer;
	wait_queue_head_t waiters;
	atomic_t block;
};

struct sb_writers {
	int frozen;
	wait_queue_head_t wait_unfrozen;
	struct percpu_rw_semaphore rw_sem[3];
};

struct super_operations;

struct dquot_operations;

struct quotactl_ops;

struct export_operations;

struct xattr_handler;

struct block_device;

struct super_block {
	struct list_head s_list;
	dev_t s_dev;
	unsigned char s_blocksize_bits;
	long unsigned int s_blocksize;
	loff_t s_maxbytes;
	struct file_system_type *s_type;
	const struct super_operations *s_op;
	const struct dquot_operations *dq_op;
	const struct quotactl_ops *s_qcop;
	const struct export_operations *s_export_op;
	long unsigned int s_flags;
	long unsigned int s_iflags;
	long unsigned int s_magic;
	struct dentry *s_root;
	struct rw_semaphore s_umount;
	int s_count;
	atomic_t s_active;
	void *s_security;
	const struct xattr_handler **s_xattr;
	struct hlist_bl_head s_roots;
	struct list_head s_mounts;
	struct block_device *s_bdev;
	struct backing_dev_info *s_bdi;
	struct mtd_info *s_mtd;
	struct hlist_node s_instances;
	unsigned int s_quota_types;
	struct quota_info s_dquot;
	struct sb_writers s_writers;
	void *s_fs_info;
	u32 s_time_gran;
	time64_t s_time_min;
	time64_t s_time_max;
	__u32 s_fsnotify_mask;
	struct fsnotify_mark_connector *s_fsnotify_marks;
	char s_id[32];
	uuid_t s_uuid;
	unsigned int s_max_links;
	fmode_t s_mode;
	struct mutex s_vfs_rename_mutex;
	const char *s_subtype;
	const struct dentry_operations *s_d_op;
	struct shrinker s_shrink;
	atomic_long_t s_remove_count;
	atomic_long_t s_fsnotify_connectors;
	int s_readonly_remount;
	errseq_t s_wb_err;
	struct workqueue_struct *s_dio_done_wq;
	struct hlist_head s_pins;
	struct user_namespace *s_user_ns;
	struct list_lru s_dentry_lru;
	struct list_lru s_inode_lru;
	struct callback_head rcu;
	struct work_struct destroy_work;
	struct mutex s_sync_lock;
	int s_stack_depth;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	spinlock_t s_inode_list_lock;
	struct list_head s_inodes;
	spinlock_t s_inode_wblist_lock;
	struct list_head s_inodes_wb;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct vfsmount {
	struct dentry *mnt_root;
	struct super_block *mnt_sb;
	int mnt_flags;
	struct user_namespace *mnt_userns;
};

struct list_lru_one {
	struct list_head list;
	long int nr_items;
};

struct list_lru_node {
	spinlock_t lock;
	struct list_lru_one lru;
	long int nr_items;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

enum migrate_mode {
	MIGRATE_ASYNC = 0,
	MIGRATE_SYNC_LIGHT = 1,
	MIGRATE_SYNC = 2,
	MIGRATE_SYNC_NO_COPY = 3,
};

struct key_tag {
	struct callback_head rcu;
	refcount_t usage;
	bool removed;
};

typedef int (*request_key_actor_t)(struct key *, void *);

struct key_preparsed_payload;

struct key_match_data;

struct kernel_pkey_params;

struct kernel_pkey_query;

struct key_type {
	const char *name;
	size_t def_datalen;
	unsigned int flags;
	int (*vet_description)(const char *);
	int (*preparse)(struct key_preparsed_payload *);
	void (*free_preparse)(struct key_preparsed_payload *);
	int (*instantiate)(struct key *, struct key_preparsed_payload *);
	int (*update)(struct key *, struct key_preparsed_payload *);
	int (*match_preparse)(struct key_match_data *);
	void (*match_free)(struct key_match_data *);
	void (*revoke)(struct key *);
	void (*destroy)(struct key *);
	void (*describe)(const struct key *, struct seq_file *);
	long int (*read)(const struct key *, char *, size_t);
	request_key_actor_t request_key;
	struct key_restriction * (*lookup_restriction)(const char *);
	int (*asym_query)(const struct kernel_pkey_params *, struct kernel_pkey_query *);
	int (*asym_eds_op)(struct kernel_pkey_params *, const void *, void *);
	int (*asym_verify_signature)(struct kernel_pkey_params *, const void *, const void *);
	struct list_head link;
	struct lock_class_key lock_class;
};

typedef int (*key_restrict_link_func_t)(struct key *, const struct key_type *, const union key_payload *, struct key *);

struct key_restriction {
	key_restrict_link_func_t check;
	struct key *key;
	struct key_type *keytype;
};

struct user_struct {
	refcount_t __count;
	atomic_long_t epoll_watches;
	long unsigned int unix_inflight;
	atomic_long_t pipe_bufs;
	struct hlist_node uidhash_node;
	kuid_t uid;
	atomic_long_t locked_vm;
	atomic_t nr_watches;
	struct ratelimit_state ratelimit;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

struct group_info {
	atomic_t usage;
	int ngroups;
	kgid_t gid[0];
};

struct core_thread {
	struct task_struct *task;
	struct core_thread *next;
};

struct core_state {
	atomic_t nr_threads;
	struct core_thread dumper;
	struct completion startup;
};

struct delayed_call {
	void (*fn)(void *);
	void *arg;
};

struct io_cq {
	struct request_queue *q;
	struct io_context *ioc;
	union {
		struct list_head q_node;
		struct kmem_cache *__rcu_icq_cache;
	};
	union {
		struct hlist_node ioc_node;
		struct callback_head __rcu_head;
	};
	unsigned int flags;
};

enum kmalloc_cache_type {
	KMALLOC_NORMAL = 0,
	KMALLOC_DMA = 0,
	KMALLOC_CGROUP = 1,
	KMALLOC_RECLAIM = 2,
	NR_KMALLOC_TYPES = 3,
};

struct wait_page_queue;

struct kiocb {
	struct file *ki_filp;
	loff_t ki_pos;
	void (*ki_complete)(struct kiocb *, long int);
	void *private;
	int ki_flags;
	u16 ki_ioprio;
	struct wait_page_queue *ki_waitq;
};

struct iattr {
	unsigned int ia_valid;
	umode_t ia_mode;
	kuid_t ia_uid;
	kgid_t ia_gid;
	loff_t ia_size;
	struct timespec64 ia_atime;
	struct timespec64 ia_mtime;
	struct timespec64 ia_ctime;
	struct file *ia_file;
};

typedef __kernel_uid32_t projid_t;

typedef struct {
	projid_t val;
} kprojid_t;

enum quota_type {
	USRQUOTA = 0,
	GRPQUOTA = 1,
	PRJQUOTA = 2,
};

struct kqid {
	union {
		kuid_t uid;
		kgid_t gid;
		kprojid_t projid;
	};
	enum quota_type type;
};

struct mem_dqblk {
	qsize_t dqb_bhardlimit;
	qsize_t dqb_bsoftlimit;
	qsize_t dqb_curspace;
	qsize_t dqb_rsvspace;
	qsize_t dqb_ihardlimit;
	qsize_t dqb_isoftlimit;
	qsize_t dqb_curinodes;
	time64_t dqb_btime;
	time64_t dqb_itime;
};

struct dquot {
	struct hlist_node dq_hash;
	struct list_head dq_inuse;
	struct list_head dq_free;
	struct list_head dq_dirty;
	struct mutex dq_lock;
	spinlock_t dq_dqb_lock;
	atomic_t dq_count;
	struct super_block *dq_sb;
	struct kqid dq_id;
	loff_t dq_off;
	long unsigned int dq_flags;
	struct mem_dqblk dq_dqb;
};

enum {
	DQF_ROOT_SQUASH_B = 0,
	DQF_SYS_FILE_B = 16,
	DQF_PRIVATE = 17,
};

struct quota_format_type {
	int qf_fmt_id;
	const struct quota_format_ops *qf_ops;
	struct module *qf_owner;
	struct quota_format_type *qf_next;
};

enum {
	DQST_LOOKUPS = 0,
	DQST_DROPS = 1,
	DQST_READS = 2,
	DQST_WRITES = 3,
	DQST_CACHE_HITS = 4,
	DQST_ALLOC_DQUOTS = 5,
	DQST_FREE_DQUOTS = 6,
	DQST_SYNCS = 7,
	_DQST_DQSTAT_LAST = 8,
};

struct quota_format_ops {
	int (*check_quota_file)(struct super_block *, int);
	int (*read_file_info)(struct super_block *, int);
	int (*write_file_info)(struct super_block *, int);
	int (*free_file_info)(struct super_block *, int);
	int (*read_dqblk)(struct dquot *);
	int (*commit_dqblk)(struct dquot *);
	int (*release_dqblk)(struct dquot *);
	int (*get_next_id)(struct super_block *, struct kqid *);
};

struct dquot_operations {
	int (*write_dquot)(struct dquot *);
	struct dquot * (*alloc_dquot)(struct super_block *, int);
	void (*destroy_dquot)(struct dquot *);
	int (*acquire_dquot)(struct dquot *);
	int (*release_dquot)(struct dquot *);
	int (*mark_dirty)(struct dquot *);
	int (*write_info)(struct super_block *, int);
	qsize_t * (*get_reserved_space)(struct inode *);
	int (*get_projid)(struct inode *, kprojid_t *);
	int (*get_inode_usage)(struct inode *, qsize_t *);
	int (*get_next_id)(struct super_block *, struct kqid *);
};

struct qc_dqblk {
	int d_fieldmask;
	u64 d_spc_hardlimit;
	u64 d_spc_softlimit;
	u64 d_ino_hardlimit;
	u64 d_ino_softlimit;
	u64 d_space;
	u64 d_ino_count;
	s64 d_ino_timer;
	s64 d_spc_timer;
	int d_ino_warns;
	int d_spc_warns;
	u64 d_rt_spc_hardlimit;
	u64 d_rt_spc_softlimit;
	u64 d_rt_space;
	s64 d_rt_spc_timer;
	int d_rt_spc_warns;
};

struct qc_type_state {
	unsigned int flags;
	unsigned int spc_timelimit;
	unsigned int ino_timelimit;
	unsigned int rt_spc_timelimit;
	unsigned int spc_warnlimit;
	unsigned int ino_warnlimit;
	unsigned int rt_spc_warnlimit;
	long long unsigned int ino;
	blkcnt_t blocks;
	blkcnt_t nextents;
};

struct qc_state {
	unsigned int s_incoredqs;
	struct qc_type_state s_state[3];
};

struct qc_info {
	int i_fieldmask;
	unsigned int i_flags;
	unsigned int i_spc_timelimit;
	unsigned int i_ino_timelimit;
	unsigned int i_rt_spc_timelimit;
	unsigned int i_spc_warnlimit;
	unsigned int i_ino_warnlimit;
	unsigned int i_rt_spc_warnlimit;
};

struct quotactl_ops {
	int (*quota_on)(struct super_block *, int, int, const struct path *);
	int (*quota_off)(struct super_block *, int);
	int (*quota_enable)(struct super_block *, unsigned int);
	int (*quota_disable)(struct super_block *, unsigned int);
	int (*quota_sync)(struct super_block *, int);
	int (*set_info)(struct super_block *, int, struct qc_info *);
	int (*get_dqblk)(struct super_block *, struct kqid, struct qc_dqblk *);
	int (*get_nextdqblk)(struct super_block *, struct kqid *, struct qc_dqblk *);
	int (*set_dqblk)(struct super_block *, struct kqid, struct qc_dqblk *);
	int (*get_state)(struct super_block *, struct qc_state *);
	int (*rm_xquota)(struct super_block *, unsigned int);
};

struct writeback_control;

struct readahead_control;

struct swap_info_struct;

struct address_space_operations {
	int (*writepage)(struct page *, struct writeback_control *);
	int (*readpage)(struct file *, struct page *);
	int (*writepages)(struct address_space *, struct writeback_control *);
	bool (*dirty_folio)(struct address_space *, struct folio *);
	void (*readahead)(struct readahead_control *);
	int (*write_begin)(struct file *, struct address_space *, loff_t, unsigned int, unsigned int, struct page **, void **);
	int (*write_end)(struct file *, struct address_space *, loff_t, unsigned int, unsigned int, struct page *, void *);
	sector_t (*bmap)(struct address_space *, sector_t);
	void (*invalidate_folio)(struct folio *, size_t, size_t);
	void (*invalidatepage)(struct page *, unsigned int, unsigned int);
	int (*releasepage)(struct page *, gfp_t);
	void (*freepage)(struct page *);
	ssize_t (*direct_IO)(struct kiocb *, struct iov_iter *);
	int (*migratepage)(struct address_space *, struct page *, struct page *, enum migrate_mode);
	bool (*isolate_page)(struct page *, isolate_mode_t);
	void (*putback_page)(struct page *);
	union {
		int (*launder_page)(struct page *);
		int (*launder_folio)(struct folio *);
	};
	bool (*is_partially_uptodate)(struct folio *, size_t, size_t);
	void (*is_dirty_writeback)(struct page *, bool *, bool *);
	int (*error_remove_page)(struct address_space *, struct page *);
	int (*swap_activate)(struct swap_info_struct *, struct file *, sector_t *);
	void (*swap_deactivate)(struct file *);
};

struct fiemap_extent_info;

struct fileattr;

struct inode_operations {
	struct dentry * (*lookup)(struct inode *, struct dentry *, unsigned int);
	const char * (*get_link)(struct dentry *, struct inode *, struct delayed_call *);
	int (*permission)(struct user_namespace *, struct inode *, int);
	struct posix_acl * (*get_acl)(struct inode *, int);
	int (*readlink)(struct dentry *, char *, int);
	int (*create)(struct user_namespace *, struct inode *, struct dentry *, umode_t, bool);
	int (*link)(struct dentry *, struct inode *, struct dentry *);
	int (*unlink)(struct inode *, struct dentry *);
	int (*symlink)(struct user_namespace *, struct inode *, struct dentry *, const char *);
	int (*mkdir)(struct user_namespace *, struct inode *, struct dentry *, umode_t);
	int (*rmdir)(struct inode *, struct dentry *);
	int (*mknod)(struct user_namespace *, struct inode *, struct dentry *, umode_t, dev_t);
	int (*rename)(struct user_namespace *, struct inode *, struct dentry *, struct inode *, struct dentry *, unsigned int);
	int (*setattr)(struct user_namespace *, struct dentry *, struct iattr *);
	int (*getattr)(struct user_namespace *, const struct path *, struct kstat *, u32, unsigned int);
	ssize_t (*listxattr)(struct dentry *, char *, size_t);
	int (*fiemap)(struct inode *, struct fiemap_extent_info *, u64, u64);
	int (*update_time)(struct inode *, struct timespec64 *, int);
	int (*atomic_open)(struct inode *, struct dentry *, struct file *, unsigned int, umode_t);
	int (*tmpfile)(struct user_namespace *, struct inode *, struct dentry *, umode_t);
	int (*set_acl)(struct user_namespace *, struct inode *, struct posix_acl *, int);
	int (*fileattr_set)(struct user_namespace *, struct dentry *, struct fileattr *);
	int (*fileattr_get)(struct dentry *, struct fileattr *);
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct file_lock_context {
	spinlock_t flc_lock;
	struct list_head flc_flock;
	struct list_head flc_posix;
	struct list_head flc_lease;
};

struct file_lock_operations {
	void (*fl_copy_lock)(struct file_lock *, struct file_lock *);
	void (*fl_release_private)(struct file_lock *);
};

struct nlm_lockowner;

struct nfs_lock_info {
	u32 state;
	struct nlm_lockowner *owner;
	struct list_head list;
};

struct nfs4_lock_state;

struct nfs4_lock_info {
	struct nfs4_lock_state *owner;
};

struct fasync_struct;

struct lock_manager_operations;

struct file_lock {
	struct file_lock *fl_blocker;
	struct list_head fl_list;
	struct hlist_node fl_link;
	struct list_head fl_blocked_requests;
	struct list_head fl_blocked_member;
	fl_owner_t fl_owner;
	unsigned int fl_flags;
	unsigned char fl_type;
	unsigned int fl_pid;
	int fl_link_cpu;
	wait_queue_head_t fl_wait;
	struct file *fl_file;
	loff_t fl_start;
	loff_t fl_end;
	struct fasync_struct *fl_fasync;
	long unsigned int fl_break_time;
	long unsigned int fl_downgrade_time;
	const struct file_lock_operations *fl_ops;
	const struct lock_manager_operations *fl_lmops;
	union {
		struct nfs_lock_info nfs_fl;
		struct nfs4_lock_info nfs4_fl;
		struct {
			struct list_head link;
			int state;
			unsigned int debug_id;
		} afs;
	} fl_u;
};

struct lock_manager_operations {
	fl_owner_t (*lm_get_owner)(fl_owner_t);
	void (*lm_put_owner)(fl_owner_t);
	void (*lm_notify)(struct file_lock *);
	int (*lm_grant)(struct file_lock *, int);
	bool (*lm_break)(struct file_lock *);
	int (*lm_change)(struct file_lock *, int, struct list_head *);
	void (*lm_setup)(struct file_lock *, void **);
	bool (*lm_breaker_owns_lease)(struct file_lock *);
};

struct fasync_struct {
	rwlock_t fa_lock;
	int magic;
	int fa_fd;
	struct fasync_struct *fa_next;
	struct file *fa_file;
	struct callback_head fa_rcu;
};

enum {
	SB_UNFROZEN = 0,
	SB_FREEZE_WRITE = 1,
	SB_FREEZE_PAGEFAULT = 2,
	SB_FREEZE_FS = 3,
	SB_FREEZE_COMPLETE = 4,
};

struct kstatfs;

struct super_operations {
	struct inode * (*alloc_inode)(struct super_block *);
	void (*destroy_inode)(struct inode *);
	void (*free_inode)(struct inode *);
	void (*dirty_inode)(struct inode *, int);
	int (*write_inode)(struct inode *, struct writeback_control *);
	int (*drop_inode)(struct inode *);
	void (*evict_inode)(struct inode *);
	void (*put_super)(struct super_block *);
	int (*sync_fs)(struct super_block *, int);
	int (*freeze_super)(struct super_block *);
	int (*freeze_fs)(struct super_block *);
	int (*thaw_super)(struct super_block *);
	int (*unfreeze_fs)(struct super_block *);
	int (*statfs)(struct dentry *, struct kstatfs *);
	int (*remount_fs)(struct super_block *, int *, char *);
	void (*umount_begin)(struct super_block *);
	int (*show_options)(struct seq_file *, struct dentry *);
	int (*show_devname)(struct seq_file *, struct dentry *);
	int (*show_path)(struct seq_file *, struct dentry *);
	int (*show_stats)(struct seq_file *, struct dentry *);
	ssize_t (*quota_read)(struct super_block *, int, char *, size_t, loff_t);
	ssize_t (*quota_write)(struct super_block *, int, const char *, size_t, loff_t);
	struct dquot ** (*get_dquots)(struct inode *);
	long int (*nr_cached_objects)(struct super_block *, struct shrink_control *);
	long int (*free_cached_objects)(struct super_block *, struct shrink_control *);
};

struct iomap;

struct fid;

struct export_operations {
	int (*encode_fh)(struct inode *, __u32 *, int *, struct inode *);
	struct dentry * (*fh_to_dentry)(struct super_block *, struct fid *, int, int);
	struct dentry * (*fh_to_parent)(struct super_block *, struct fid *, int, int);
	int (*get_name)(struct dentry *, char *, struct dentry *);
	struct dentry * (*get_parent)(struct dentry *);
	int (*commit_metadata)(struct inode *);
	int (*get_uuid)(struct super_block *, u8 *, u32 *, u64 *);
	int (*map_blocks)(struct inode *, loff_t, u64, struct iomap *, bool, u32 *);
	int (*commit_blocks)(struct inode *, struct iomap *, int, struct iattr *);
	u64 (*fetch_iversion)(struct inode *);
	long unsigned int flags;
};

struct xattr_handler {
	const char *name;
	const char *prefix;
	int flags;
	bool (*list)(struct dentry *);
	int (*get)(const struct xattr_handler *, struct dentry *, struct inode *, const char *, void *, size_t);
	int (*set)(const struct xattr_handler *, struct user_namespace *, struct dentry *, struct inode *, const char *, const void *, size_t, int);
};

typedef int (*filldir_t)(struct dir_context *, const char *, int, loff_t, u64, unsigned int);

struct dir_context {
	filldir_t actor;
	loff_t pos;
};

struct p_log;

struct fs_parameter;

struct fs_parse_result;

typedef int fs_param_type(struct p_log *, const struct fs_parameter_spec *, struct fs_parameter *, struct fs_parse_result *);

struct fs_parameter_spec {
	const char *name;
	fs_param_type *type;
	u8 opt;
	short unsigned int flags;
	const void *data;
};

enum compound_dtor_id {
	NULL_COMPOUND_DTOR = 0,
	COMPOUND_PAGE_DTOR = 1,
	HUGETLB_PAGE_DTOR = 2,
	TRANSHUGE_PAGE_DTOR = 3,
	NR_COMPOUND_DTORS = 4,
};

enum vm_event_item {
	PGPGIN = 0,
	PGPGOUT = 1,
	PSWPIN = 2,
	PSWPOUT = 3,
	PGALLOC_NORMAL = 4,
	PGALLOC_MOVABLE = 5,
	ALLOCSTALL_NORMAL = 6,
	ALLOCSTALL_MOVABLE = 7,
	PGSCAN_SKIP_NORMAL = 8,
	PGSCAN_SKIP_MOVABLE = 9,
	PGFREE = 10,
	PGACTIVATE = 11,
	PGDEACTIVATE = 12,
	PGLAZYFREE = 13,
	PGFAULT = 14,
	PGMAJFAULT = 15,
	PGLAZYFREED = 16,
	PGREFILL = 17,
	PGREUSE = 18,
	PGSTEAL_KSWAPD = 19,
	PGSTEAL_DIRECT = 20,
	PGDEMOTE_KSWAPD = 21,
	PGDEMOTE_DIRECT = 22,
	PGSCAN_KSWAPD = 23,
	PGSCAN_DIRECT = 24,
	PGSCAN_DIRECT_THROTTLE = 25,
	PGSCAN_ANON = 26,
	PGSCAN_FILE = 27,
	PGSTEAL_ANON = 28,
	PGSTEAL_FILE = 29,
	PGSCAN_ZONE_RECLAIM_FAILED = 30,
	PGINODESTEAL = 31,
	SLABS_SCANNED = 32,
	KSWAPD_INODESTEAL = 33,
	KSWAPD_LOW_WMARK_HIT_QUICKLY = 34,
	KSWAPD_HIGH_WMARK_HIT_QUICKLY = 35,
	PAGEOUTRUN = 36,
	PGROTATED = 37,
	DROP_PAGECACHE = 38,
	DROP_SLAB = 39,
	OOM_KILL = 40,
	NUMA_PTE_UPDATES = 41,
	NUMA_HUGE_PTE_UPDATES = 42,
	NUMA_HINT_FAULTS = 43,
	NUMA_HINT_FAULTS_LOCAL = 44,
	NUMA_PAGE_MIGRATE = 45,
	PGMIGRATE_SUCCESS = 46,
	PGMIGRATE_FAIL = 47,
	THP_MIGRATION_SUCCESS = 48,
	THP_MIGRATION_FAIL = 49,
	THP_MIGRATION_SPLIT = 50,
	COMPACTMIGRATE_SCANNED = 51,
	COMPACTFREE_SCANNED = 52,
	COMPACTISOLATED = 53,
	COMPACTSTALL = 54,
	COMPACTFAIL = 55,
	COMPACTSUCCESS = 56,
	KCOMPACTD_WAKE = 57,
	KCOMPACTD_MIGRATE_SCANNED = 58,
	KCOMPACTD_FREE_SCANNED = 59,
	HTLB_BUDDY_PGALLOC = 60,
	HTLB_BUDDY_PGALLOC_FAIL = 61,
	CMA_ALLOC_SUCCESS = 62,
	CMA_ALLOC_FAIL = 63,
	UNEVICTABLE_PGCULLED = 64,
	UNEVICTABLE_PGSCANNED = 65,
	UNEVICTABLE_PGRESCUED = 66,
	UNEVICTABLE_PGMLOCKED = 67,
	UNEVICTABLE_PGMUNLOCKED = 68,
	UNEVICTABLE_PGCLEARED = 69,
	UNEVICTABLE_PGSTRANDED = 70,
	THP_FAULT_ALLOC = 71,
	THP_FAULT_FALLBACK = 72,
	THP_FAULT_FALLBACK_CHARGE = 73,
	THP_COLLAPSE_ALLOC = 74,
	THP_COLLAPSE_ALLOC_FAILED = 75,
	THP_FILE_ALLOC = 76,
	THP_FILE_FALLBACK = 77,
	THP_FILE_FALLBACK_CHARGE = 78,
	THP_FILE_MAPPED = 79,
	THP_SPLIT_PAGE = 80,
	THP_SPLIT_PAGE_FAILED = 81,
	THP_DEFERRED_SPLIT_PAGE = 82,
	THP_SPLIT_PMD = 83,
	THP_ZERO_PAGE_ALLOC = 84,
	THP_ZERO_PAGE_ALLOC_FAILED = 85,
	THP_SWPOUT = 86,
	THP_SWPOUT_FALLBACK = 87,
	BALLOON_INFLATE = 88,
	BALLOON_DEFLATE = 89,
	BALLOON_MIGRATE = 90,
	SWAP_RA = 91,
	SWAP_RA_HIT = 92,
	KSM_SWPIN_COPY = 93,
	COW_KSM = 94,
	ZSWPIN = 95,
	ZSWPOUT = 96,
	NR_VM_EVENT_ITEMS = 97,
};

enum {
	HI_SOFTIRQ = 0,
	TIMER_SOFTIRQ = 1,
	NET_TX_SOFTIRQ = 2,
	NET_RX_SOFTIRQ = 3,
	BLOCK_SOFTIRQ = 4,
	IRQ_POLL_SOFTIRQ = 5,
	TASKLET_SOFTIRQ = 6,
	SCHED_SOFTIRQ = 7,
	HRTIMER_SOFTIRQ = 8,
	RCU_SOFTIRQ = 9,
	NR_SOFTIRQS = 10,
};

enum {
	PCI_STD_RESOURCES = 0,
	PCI_STD_RESOURCE_END = 5,
	PCI_ROM_RESOURCE = 6,
	PCI_IOV_RESOURCES = 7,
	PCI_IOV_RESOURCE_END = 12,
	PCI_BRIDGE_RESOURCES = 13,
	PCI_BRIDGE_RESOURCE_END = 16,
	PCI_NUM_RESOURCES = 17,
	DEVICE_COUNT_RESOURCE = 17,
};

typedef unsigned int pci_channel_state_t;

typedef unsigned int pcie_reset_state_t;

typedef short unsigned int pci_dev_flags_t;

typedef short unsigned int pci_bus_flags_t;

typedef unsigned int pci_ers_result_t;

struct seq_operations {
	void * (*start)(struct seq_file *, loff_t *);
	void (*stop)(struct seq_file *, void *);
	void * (*next)(struct seq_file *, void *, loff_t *);
	int (*show)(struct seq_file *, void *);
};

typedef u32 phandle;

typedef u32 ihandle;

struct boot_param_header {
	__be32 magic;
	__be32 totalsize;
	__be32 off_dt_struct;
	__be32 off_dt_strings;
	__be32 off_mem_rsvmap;
	__be32 version;
	__be32 last_comp_version;
	__be32 boot_cpuid_phys;
	__be32 dt_strings_size;
	__be32 dt_struct_size;
};

struct nsset;

struct proc_ns_operations {
	const char *name;
	const char *real_ns_name;
	int type;
	struct ns_common * (*get)(struct task_struct *);
	void (*put)(struct ns_common *);
	int (*install)(struct nsset *, struct ns_common *);
	struct user_namespace * (*owner)(struct ns_common *);
	struct ns_common * (*get_parent)(struct ns_common *);
};

struct linux_logo {
	int type;
	unsigned int width;
	unsigned int height;
	unsigned int clutsize;
	const unsigned char *clut;
	const unsigned char *data;
};

typedef u32 prom_arg_t;

struct prom_args {
	__be32 service;
	__be32 nargs;
	__be32 nret;
	__be32 args[10];
};

struct prom_t {
	ihandle root;
	phandle chosen;
	int cpu;
	ihandle stdout;
	ihandle mmumap;
	ihandle memory;
};

struct mem_map_entry {
	__be64 base;
	__be64 size;
};

typedef __be32 cell_t;

struct platform_support {
	bool hash_mmu;
	bool radix_mmu;
	bool radix_gtse;
	bool xive;
};

struct option_vector1 {
	u8 byte1;
	u8 arch_versions;
	u8 arch_versions3;
};

struct option_vector2 {
	u8 byte1;
	__be16 reserved;
	__be32 real_base;
	__be32 real_size;
	__be32 virt_base;
	__be32 virt_size;
	__be32 load_base;
	__be32 min_rma;
	__be32 min_load;
	u8 min_rma_percent;
	u8 max_pft_size;
} __attribute__((packed));

struct option_vector3 {
	u8 byte1;
	u8 byte2;
};

struct option_vector4 {
	u8 byte1;
	u8 min_vp_cap;
};

struct option_vector5 {
	u8 byte1;
	u8 byte2;
	u8 byte3;
	u8 cmo;
	u8 associativity;
	u8 bin_opts;
	u8 micro_checkpoint;
	u8 reserved0;
	__be32 max_cpus;
	__be16 papr_level;
	__be16 reserved1;
	u8 platform_facilities;
	u8 reserved2;
	__be16 reserved3;
	u8 subprocessors;
	u8 byte22;
	u8 intarch;
	u8 mmu;
	u8 hash_ext;
	u8 radix_ext;
} __attribute__((packed));

struct option_vector6 {
	u8 reserved;
	u8 secondary_pteg;
	u8 os_name;
};

struct option_vector7 {
	u8 os_id[256];
};

struct ibm_arch_vec {
	struct {
		u32 mask;
		u32 val;
	} pvrs[14];
	u8 num_vectors;
	u8 vec1_len;
	struct option_vector1 vec1;
	u8 vec2_len;
	struct option_vector2 vec2;
	u8 vec3_len;
	struct option_vector3 vec3;
	u8 vec4_len;
	struct option_vector4 vec4;
	u8 vec5_len;
	struct option_vector5 vec5;
	u8 vec6_len;
	struct option_vector6 vec6;
	u8 vec7_len;
	struct option_vector7 vec7;
} __attribute__((packed));

typedef __u32 __le32;

typedef __u32 __wsum;

typedef u64 dma_addr_t;

typedef u64 phys_addr_t;

typedef long unsigned int irq_hw_number_t;

typedef int (*initcall_t)();

typedef initcall_t initcall_entry_t;

struct obs_kernel_param {
	const char *str;
	int (*setup_func)(char *);
	int early;
};

struct static_key_true {
	struct static_key key;
};

struct static_key_false {
	struct static_key key;
};

struct _ddebug {
	const char *modname;
	const char *function;
	const char *filename;
	const char *format;
	unsigned int lineno: 18;
	unsigned int flags: 8;
	union {
		struct static_key_true dd_key_true;
		struct static_key_false dd_key_false;
	} key;
};

enum system_states {
	SYSTEM_BOOTING = 0,
	SYSTEM_SCHEDULING = 1,
	SYSTEM_FREEING_INITMEM = 2,
	SYSTEM_RUNNING = 3,
	SYSTEM_HALT = 4,
	SYSTEM_POWER_OFF = 5,
	SYSTEM_RESTART = 6,
	SYSTEM_SUSPEND = 7,
};

struct cacheline_padding {
	char x[0];
};

struct uid_gid_extent {
	u32 first;
	u32 lower_first;
	u32 count;
};

struct uid_gid_map {
	u32 nr_extents;
	union {
		struct uid_gid_extent extent[5];
		struct {
			struct uid_gid_extent *forward;
			struct uid_gid_extent *reverse;
		};
	};
};

struct ctl_table;

struct ctl_table_root;

struct ctl_table_set;

struct ctl_dir;

struct ctl_node;

struct ctl_table_header {
	union {
		struct {
			struct ctl_table *ctl_table;
			int used;
			int count;
			int nreg;
		};
		struct callback_head rcu;
	};
	struct completion *unregistering;
	struct ctl_table *ctl_table_arg;
	struct ctl_table_root *root;
	struct ctl_table_set *set;
	struct ctl_dir *parent;
	struct ctl_node *node;
	struct hlist_head inodes;
};

struct ctl_dir {
	struct ctl_table_header header;
	struct rb_root root;
};

struct ctl_table_set {
	int (*is_seen)(struct ctl_table_set *);
	struct ctl_dir dir;
};

struct user_namespace {
	struct uid_gid_map uid_map;
	struct uid_gid_map gid_map;
	struct uid_gid_map projid_map;
	struct user_namespace *parent;
	int level;
	kuid_t owner;
	kgid_t group;
	struct ns_common ns;
	long unsigned int flags;
	bool parent_could_setfcap;
	struct list_head keyring_name_list;
	struct key *user_keyring_register;
	struct rw_semaphore keyring_sem;
	struct key *persistent_keyring_register;
	struct work_struct work;
	struct ctl_table_set set;
	struct ctl_table_header *sysctls;
	struct ucounts *ucounts;
	long int ucount_max[16];
};

typedef struct cpumask cpumask_var_t[1];

struct pollfd {
	int fd;
	short int events;
	short int revents;
};

struct device;

struct perf_cpu_context;

struct perf_output_handle;

struct pmu {
	struct list_head entry;
	struct module *module;
	struct device *dev;
	const struct attribute_group **attr_groups;
	const struct attribute_group **attr_update;
	const char *name;
	int type;
	int capabilities;
	int *pmu_disable_count;
	struct perf_cpu_context *pmu_cpu_context;
	atomic_t exclusive_cnt;
	int task_ctx_nr;
	int hrtimer_interval_ms;
	unsigned int nr_addr_filters;
	void (*pmu_enable)(struct pmu *);
	void (*pmu_disable)(struct pmu *);
	int (*event_init)(struct perf_event *);
	void (*event_mapped)(struct perf_event *, struct mm_struct *);
	void (*event_unmapped)(struct perf_event *, struct mm_struct *);
	int (*add)(struct perf_event *, int);
	void (*del)(struct perf_event *, int);
	void (*start)(struct perf_event *, int);
	void (*stop)(struct perf_event *, int);
	void (*read)(struct perf_event *);
	void (*start_txn)(struct pmu *, unsigned int);
	int (*commit_txn)(struct pmu *);
	void (*cancel_txn)(struct pmu *);
	int (*event_idx)(struct perf_event *);
	void (*sched_task)(struct perf_event_context *, bool);
	struct kmem_cache *task_ctx_cache;
	void (*swap_task_ctx)(struct perf_event_context *, struct perf_event_context *);
	void * (*setup_aux)(struct perf_event *, void **, int, bool);
	void (*free_aux)(void *);
	long int (*snapshot_aux)(struct perf_event *, struct perf_output_handle *, long unsigned int);
	int (*addr_filters_validate)(struct list_head *);
	void (*addr_filters_sync)(struct perf_event *);
	int (*aux_output_match)(struct perf_event *);
	int (*filter_match)(struct perf_event *);
	int (*check_period)(struct perf_event *, u64);
};

enum perf_event_state {
	PERF_EVENT_STATE_DEAD = 4294967292,
	PERF_EVENT_STATE_EXIT = 4294967293,
	PERF_EVENT_STATE_ERROR = 4294967294,
	PERF_EVENT_STATE_OFF = 4294967295,
	PERF_EVENT_STATE_INACTIVE = 0,
	PERF_EVENT_STATE_ACTIVE = 1,
};

typedef struct {
	long int v;
} local_t;

typedef struct {
	local_t a;
} local64_t;

struct perf_event_attr {
	__u32 type;
	__u32 size;
	__u64 config;
	union {
		__u64 sample_period;
		__u64 sample_freq;
	};
	__u64 sample_type;
	__u64 read_format;
	__u64 disabled: 1;
	__u64 inherit: 1;
	__u64 pinned: 1;
	__u64 exclusive: 1;
	__u64 exclude_user: 1;
	__u64 exclude_kernel: 1;
	__u64 exclude_hv: 1;
	__u64 exclude_idle: 1;
	__u64 mmap: 1;
	__u64 comm: 1;
	__u64 freq: 1;
	__u64 inherit_stat: 1;
	__u64 enable_on_exec: 1;
	__u64 task: 1;
	__u64 watermark: 1;
	__u64 precise_ip: 2;
	__u64 mmap_data: 1;
	__u64 sample_id_all: 1;
	__u64 exclude_host: 1;
	__u64 exclude_guest: 1;
	__u64 exclude_callchain_kernel: 1;
	__u64 exclude_callchain_user: 1;
	__u64 mmap2: 1;
	__u64 comm_exec: 1;
	__u64 use_clockid: 1;
	__u64 context_switch: 1;
	__u64 write_backward: 1;
	__u64 namespaces: 1;
	__u64 ksymbol: 1;
	__u64 bpf_event: 1;
	__u64 aux_output: 1;
	__u64 cgroup: 1;
	__u64 text_poke: 1;
	__u64 build_id: 1;
	__u64 inherit_thread: 1;
	__u64 remove_on_exec: 1;
	__u64 sigtrap: 1;
	__u64 __reserved_1: 26;
	union {
		__u32 wakeup_events;
		__u32 wakeup_watermark;
	};
	__u32 bp_type;
	union {
		__u64 bp_addr;
		__u64 kprobe_func;
		__u64 uprobe_path;
		__u64 config1;
	};
	union {
		__u64 bp_len;
		__u64 kprobe_addr;
		__u64 probe_offset;
		__u64 config2;
	};
	__u64 branch_sample_type;
	__u64 sample_regs_user;
	__u32 sample_stack_user;
	__s32 clockid;
	__u64 sample_regs_intr;
	__u32 aux_watermark;
	__u16 sample_max_stack;
	__u16 __reserved_2;
	__u32 aux_sample_size;
	__u32 __reserved_3;
	__u64 sig_data;
};

struct hw_perf_event_extra {
	u64 config;
	unsigned int reg;
	int alloc;
	int idx;
};

struct hw_perf_event {
	union {
		struct {
			u64 config;
			u64 last_tag;
			long unsigned int config_base;
			long unsigned int event_base;
			int event_base_rdpmc;
			int idx;
			int last_cpu;
			int flags;
			struct hw_perf_event_extra extra_reg;
			struct hw_perf_event_extra branch_reg;
		};
		struct {
			struct hrtimer hrtimer;
		};
		struct {
			struct list_head tp_list;
		};
		struct {
			u64 pwr_acc;
			u64 ptsc;
		};
		struct {
			struct arch_hw_breakpoint info;
			struct list_head bp_list;
		};
		struct {
			u8 iommu_bank;
			u8 iommu_cntr;
			u16 padding;
			u64 conf;
			u64 conf1;
		};
	};
	struct task_struct *target;
	void *addr_filters;
	long unsigned int addr_filters_gen;
	int state;
	local64_t prev_count;
	u64 sample_period;
	union {
		struct {
			u64 last_period;
			local64_t period_left;
		};
		struct {
			u64 saved_metric;
			u64 saved_slots;
		};
	};
	u64 interrupts_seq;
	u64 interrupts;
	u64 freq_time_stamp;
	u64 freq_count_stamp;
};

struct irq_work {
	struct __call_single_node node;
	void (*func)(struct irq_work *);
	struct rcuwait irqwait;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
};

struct perf_addr_filters_head {
	struct list_head list;
	raw_spinlock_t lock;
	unsigned int nr_file_filters;
};

struct perf_sample_data;

typedef void (*perf_overflow_handler_t)(struct perf_event *, struct perf_sample_data *, struct pt_regs *);

struct ftrace_ops;

struct ftrace_regs;

typedef void (*ftrace_func_t)(long unsigned int, long unsigned int, struct ftrace_ops *, struct ftrace_regs *);

struct ftrace_hash;

struct ftrace_ops_hash {
	struct ftrace_hash *notrace_hash;
	struct ftrace_hash *filter_hash;
	struct mutex regex_lock;
};

struct ftrace_ops {
	ftrace_func_t func;
	struct ftrace_ops *next;
	long unsigned int flags;
	void *private;
	ftrace_func_t saved_func;
	struct ftrace_ops_hash local_hash;
	struct ftrace_ops_hash *func_hash;
	struct ftrace_ops_hash old_hash;
	long unsigned int trampoline;
	long unsigned int trampoline_size;
	struct list_head list;
};

struct perf_buffer;

struct perf_addr_filter_range;

struct bpf_prog;

struct event_filter;

struct perf_cgroup;

struct perf_event {
	struct list_head event_entry;
	struct list_head sibling_list;
	struct list_head active_list;
	struct rb_node group_node;
	u64 group_index;
	struct list_head migrate_entry;
	struct hlist_node hlist_entry;
	struct list_head active_entry;
	int nr_siblings;
	int event_caps;
	int group_caps;
	struct perf_event *group_leader;
	struct pmu *pmu;
	void *pmu_private;
	enum perf_event_state state;
	unsigned int attach_state;
	local64_t count;
	atomic64_t child_count;
	u64 total_time_enabled;
	u64 total_time_running;
	u64 tstamp;
	struct perf_event_attr attr;
	u16 header_size;
	u16 id_header_size;
	u16 read_size;
	struct hw_perf_event hw;
	struct perf_event_context *ctx;
	atomic_long_t refcount;
	atomic64_t child_total_time_enabled;
	atomic64_t child_total_time_running;
	struct mutex child_mutex;
	struct list_head child_list;
	struct perf_event *parent;
	int oncpu;
	int cpu;
	struct list_head owner_entry;
	struct task_struct *owner;
	struct mutex mmap_mutex;
	atomic_t mmap_count;
	struct perf_buffer *rb;
	struct list_head rb_entry;
	long unsigned int rcu_batches;
	int rcu_pending;
	wait_queue_head_t waitq;
	struct fasync_struct *fasync;
	int pending_wakeup;
	int pending_kill;
	int pending_disable;
	long unsigned int pending_addr;
	struct irq_work pending;
	atomic_t event_limit;
	struct perf_addr_filters_head addr_filters;
	struct perf_addr_filter_range *addr_filter_ranges;
	long unsigned int addr_filters_gen;
	struct perf_event *aux_event;
	void (*destroy)(struct perf_event *);
	struct callback_head callback_head;
	struct pid_namespace *ns;
	u64 id;
	atomic64_t lost_samples;
	u64 (*clock)();
	perf_overflow_handler_t overflow_handler;
	void *overflow_handler_context;
	perf_overflow_handler_t orig_overflow_handler;
	struct bpf_prog *prog;
	u64 bpf_cookie;
	struct trace_event_call *tp_event;
	struct event_filter *filter;
	struct ftrace_ops ftrace_ops;
	struct perf_cgroup *cgrp;
	void *security;
	struct list_head sb_list;
};

enum irqreturn {
	IRQ_NONE = 0,
	IRQ_HANDLED = 1,
	IRQ_WAKE_THREAD = 2,
};

typedef enum irqreturn irqreturn_t;

enum refcount_saturation_type {
	REFCOUNT_ADD_NOT_ZERO_OVF = 0,
	REFCOUNT_ADD_OVF = 1,
	REFCOUNT_ADD_UAF = 2,
	REFCOUNT_SUB_UAF = 3,
	REFCOUNT_DEC_LEAK = 4,
};

struct wait_queue_entry;

typedef int (*wait_queue_func_t)(struct wait_queue_entry *, unsigned int, int, void *);

struct wait_queue_entry {
	unsigned int flags;
	void *private;
	wait_queue_func_t func;
	struct list_head entry;
};

typedef struct wait_queue_entry wait_queue_entry_t;

struct rcu_work {
	struct work_struct work;
	struct callback_head rcu;
	struct workqueue_struct *wq;
};

struct notifier_block;

typedef int (*notifier_fn_t)(struct notifier_block *, long unsigned int, void *);

struct notifier_block {
	notifier_fn_t notifier_call;
	struct notifier_block *next;
	int priority;
};

struct blocking_notifier_head {
	struct rw_semaphore rwsem;
	struct notifier_block *head;
};

struct raw_notifier_head {
	struct notifier_block *head;
};

enum dma_data_direction {
	DMA_BIDIRECTIONAL = 0,
	DMA_TO_DEVICE = 1,
	DMA_FROM_DEVICE = 2,
	DMA_NONE = 3,
};

struct page_pool_params {
	unsigned int flags;
	unsigned int order;
	unsigned int pool_size;
	int nid;
	struct device *dev;
	enum dma_data_direction dma_dir;
	unsigned int max_len;
	unsigned int offset;
	void (*init_callback)(struct page *, void *);
	void *init_arg;
};

struct pp_alloc_cache {
	u32 count;
	struct page *cache[128];
};

struct ptr_ring {
	int producer;
	spinlock_t producer_lock;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	int consumer_head;
	int consumer_tail;
	spinlock_t consumer_lock;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	int size;
	int batch;
	void **queue;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct page_pool {
	struct page_pool_params p;
	struct delayed_work release_dw;
	void (*disconnect)(void *);
	long unsigned int defer_start;
	long unsigned int defer_warn;
	u32 pages_state_hold_cnt;
	unsigned int frag_offset;
	struct page *frag_page;
	long int frag_users;
	u32 xdp_mem_id;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct pp_alloc_cache alloc;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct ptr_ring ring;
	atomic_t pages_state_release_cnt;
	refcount_t user_cnt;
	u64 destroy_cnt;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct vmem_altmap {
	long unsigned int base_pfn;
	const long unsigned int end_pfn;
	const long unsigned int reserve;
	long unsigned int free;
	long unsigned int align;
	long unsigned int alloc;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

struct percpu_ref_data;

struct percpu_ref {
	long unsigned int percpu_count_ptr;
	struct percpu_ref_data *data;
};

enum memory_type {
	MEMORY_DEVICE_PRIVATE = 1,
	MEMORY_DEVICE_FS_DAX = 2,
	MEMORY_DEVICE_GENERIC = 3,
	MEMORY_DEVICE_PCI_P2PDMA = 4,
};

struct range {
	u64 start;
	u64 end;
};

struct dev_pagemap_ops;

struct dev_pagemap {
	struct vmem_altmap altmap;
	struct percpu_ref ref;
	struct completion done;
	enum memory_type type;
	unsigned int flags;
	long unsigned int vmemmap_shift;
	const struct dev_pagemap_ops *ops;
	void *owner;
	int nr_range;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	long unsigned int rh_reserved5;
	union {
		struct range range;
		struct range ranges[0];
	};
};

struct anon_vma {
	struct anon_vma *root;
	struct rw_semaphore rwsem;
	atomic_t refcount;
	long unsigned int num_children;
	long unsigned int num_active_vmas;
	struct anon_vma *parent;
	struct rb_root_cached rb_root;
};

struct mempolicy {
	atomic_t refcnt;
	short unsigned int mode;
	short unsigned int flags;
	nodemask_t nodes;
	int home_node;
	union {
		nodemask_t cpuset_mems_allowed;
		nodemask_t user_nodemask;
	} w;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
};

struct linux_binprm;

struct coredump_params;

struct linux_binfmt {
	struct list_head lh;
	struct module *module;
	int (*load_binary)(struct linux_binprm *);
	int (*load_shlib)(struct file *);
	int (*core_dump)(struct coredump_params *);
	long unsigned int min_coredump;
};

struct free_area {
	struct list_head free_list[6];
	long unsigned int nr_free;
};

struct pglist_data;

struct lruvec {
	struct list_head lists[5];
	spinlock_t lru_lock;
	long unsigned int anon_cost;
	long unsigned int file_cost;
	atomic_long_t nonresident_age;
	long unsigned int refaults[2];
	long unsigned int flags;
	struct pglist_data *pgdat;
};

struct per_cpu_pages;

struct per_cpu_zonestat;

struct zone {
	long unsigned int _watermark[4];
	long unsigned int watermark_boost;
	long unsigned int nr_reserved_highatomic;
	long int lowmem_reserve[3];
	int node;
	struct pglist_data *zone_pgdat;
	struct per_cpu_pages *per_cpu_pageset;
	struct per_cpu_zonestat *per_cpu_zonestats;
	int pageset_high;
	int pageset_batch;
	long unsigned int zone_start_pfn;
	atomic_long_t managed_pages;
	long unsigned int spanned_pages;
	long unsigned int present_pages;
	long unsigned int present_early_pages;
	long unsigned int cma_pages;
	const char *name;
	long unsigned int nr_isolate_pageblock;
	seqlock_t span_seqlock;
	int initialized;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct cacheline_padding _pad1_;
	struct free_area free_area[9];
	long unsigned int flags;
	spinlock_t lock;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct cacheline_padding _pad2_;
	long unsigned int percpu_drift_mark;
	long unsigned int compact_cached_free_pfn;
	long unsigned int compact_cached_migrate_pfn[2];
	long unsigned int compact_init_migrate_pfn;
	long unsigned int compact_init_free_pfn;
	unsigned int compact_considered;
	unsigned int compact_defer_shift;
	int compact_order_failed;
	bool compact_blockskip_flush;
	bool contiguous;
	long: 16;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct cacheline_padding _pad3_;
	atomic_long_t vm_stat[11];
	atomic_long_t vm_numa_event[6];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct zoneref {
	struct zone *zone;
	int zone_idx;
};

struct zonelist {
	struct zoneref _zonerefs[769];
};

enum zone_type {
	ZONE_NORMAL = 0,
	ZONE_MOVABLE = 1,
	ZONE_DEVICE = 2,
	__MAX_NR_ZONES = 3,
};

struct deferred_split {
	spinlock_t split_queue_lock;
	struct list_head split_queue;
	long unsigned int split_queue_len;
};

struct per_cpu_nodestat;

struct pglist_data {
	struct zone node_zones[3];
	struct zonelist node_zonelists[2];
	int nr_zones;
	spinlock_t node_size_lock;
	long unsigned int node_start_pfn;
	long unsigned int node_present_pages;
	long unsigned int node_spanned_pages;
	int node_id;
	wait_queue_head_t kswapd_wait;
	wait_queue_head_t pfmemalloc_wait;
	wait_queue_head_t reclaim_wait[4];
	atomic_t nr_writeback_throttled;
	long unsigned int nr_reclaim_start;
	struct task_struct *kswapd;
	int kswapd_order;
	enum zone_type kswapd_highest_zoneidx;
	int kswapd_failures;
	int kcompactd_max_order;
	enum zone_type kcompactd_highest_zoneidx;
	wait_queue_head_t kcompactd_wait;
	struct task_struct *kcompactd;
	bool proactive_compact_trigger;
	long unsigned int totalreserve_pages;
	long unsigned int min_unmapped_pages;
	long unsigned int min_slab_pages;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct cacheline_padding _pad1_;
	struct deferred_split deferred_split_queue;
	struct lruvec __lruvec;
	long unsigned int flags;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct cacheline_padding _pad2_;
	struct per_cpu_nodestat *per_cpu_nodestats;
	atomic_long_t vm_stat[41];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct per_cpu_pages {
	int count;
	int high;
	int batch;
	short int free_factor;
	short int expire;
	struct list_head lists[15];
};

struct per_cpu_zonestat {
	s8 vm_stat_diff[11];
	s8 stat_threshold;
	long unsigned int vm_numa_event[6];
};

struct per_cpu_nodestat {
	s8 stat_threshold;
	s8 vm_node_stat_diff[41];
};

typedef struct pglist_data pg_data_t;

typedef int proc_handler(struct ctl_table *, int, void *, size_t *, loff_t *);

struct ctl_table_poll;

struct ctl_table {
	const char *procname;
	void *data;
	int maxlen;
	umode_t mode;
	struct ctl_table *child;
	proc_handler *proc_handler;
	struct ctl_table_poll *poll;
	void *extra1;
	void *extra2;
};

struct ctl_table_poll {
	atomic_t event;
	wait_queue_head_t wait;
};

struct ctl_node {
	struct rb_node node;
	struct ctl_table_header *header;
};

struct ctl_table_root {
	struct ctl_table_set default_set;
	struct ctl_table_set * (*lookup)(struct ctl_table_root *);
	void (*set_ownership)(struct ctl_table_header *, struct ctl_table *, kuid_t *, kgid_t *);
	int (*permissions)(struct ctl_table_header *, struct ctl_table *);
};

enum umh_disable_depth {
	UMH_ENABLED = 0,
	UMH_FREEZING = 1,
	UMH_DISABLED = 2,
};

struct rhash_head {
	struct rhash_head *next;
};

struct rhashtable;

struct rhashtable_compare_arg {
	struct rhashtable *ht;
	const void *key;
};

typedef u32 (*rht_hashfn_t)(const void *, u32, u32);

typedef u32 (*rht_obj_hashfn_t)(const void *, u32, u32);

typedef int (*rht_obj_cmpfn_t)(struct rhashtable_compare_arg *, const void *);

struct rhashtable_params {
	u16 nelem_hint;
	u16 key_len;
	u16 key_offset;
	u16 head_offset;
	unsigned int max_size;
	u16 min_size;
	bool automatic_shrinking;
	rht_hashfn_t hashfn;
	rht_obj_hashfn_t obj_hashfn;
	rht_obj_cmpfn_t obj_cmpfn;
};

struct bucket_table;

struct rhashtable {
	struct bucket_table *tbl;
	unsigned int key_len;
	unsigned int max_elems;
	struct rhashtable_params p;
	bool rhlist;
	struct work_struct run_work;
	struct mutex mutex;
	spinlock_t lock;
	atomic_t nelems;
};

struct task_cputime {
	u64 stime;
	u64 utime;
	long long unsigned int sum_exec_runtime;
};

struct ucounts {
	struct hlist_node node;
	struct user_namespace *ns;
	kuid_t uid;
	atomic_t count;
	atomic_long_t ucount[16];
};

struct bio;

struct bio_list {
	struct bio *head;
	struct bio *tail;
};

struct request;

struct blk_plug {
	struct request *mq_list;
	struct request *cached_rq;
	short unsigned int nr_ios;
	short unsigned int rq_count;
	bool multiple_queues;
	bool has_elevator;
	bool nowait;
	struct list_head cb_list;
};

struct reclaim_state {
	long unsigned int reclaimed_slab;
};

struct percpu_counter {
	raw_spinlock_t lock;
	s64 count;
	struct list_head list;
	s32 *counters;
};

struct fprop_local_percpu {
	struct percpu_counter events;
	unsigned int period;
	raw_spinlock_t lock;
};

enum wb_reason {
	WB_REASON_BACKGROUND = 0,
	WB_REASON_VMSCAN = 1,
	WB_REASON_SYNC = 2,
	WB_REASON_PERIODIC = 3,
	WB_REASON_LAPTOP_TIMER = 4,
	WB_REASON_FS_FREE_SPACE = 5,
	WB_REASON_FORKER_THREAD = 6,
	WB_REASON_FOREIGN_FLUSH = 7,
	WB_REASON_MAX = 8,
};

struct cgroup_subsys_state;

struct bdi_writeback {
	struct backing_dev_info *bdi;
	long unsigned int state;
	long unsigned int last_old_flush;
	struct list_head b_dirty;
	struct list_head b_io;
	struct list_head b_more_io;
	struct list_head b_dirty_time;
	spinlock_t list_lock;
	atomic_t writeback_inodes;
	struct percpu_counter stat[4];
	long unsigned int congested;
	long unsigned int bw_time_stamp;
	long unsigned int dirtied_stamp;
	long unsigned int written_stamp;
	long unsigned int write_bandwidth;
	long unsigned int avg_write_bandwidth;
	long unsigned int dirty_ratelimit;
	long unsigned int balanced_dirty_ratelimit;
	struct fprop_local_percpu completions;
	int dirty_exceeded;
	enum wb_reason start_all_reason;
	spinlock_t work_lock;
	struct list_head work_list;
	struct delayed_work dwork;
	struct delayed_work bw_dwork;
	long unsigned int dirty_sleep;
	struct list_head bdi_node;
	struct percpu_ref refcnt;
	struct fprop_local_percpu memcg_completions;
	struct cgroup_subsys_state *memcg_css;
	struct cgroup_subsys_state *blkcg_css;
	struct list_head memcg_node;
	struct list_head blkcg_node;
	struct list_head b_attached;
	struct list_head offline_node;
	union {
		struct work_struct release_work;
		struct callback_head rcu;
	};
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
};

struct backing_dev_info {
	u64 id;
	struct rb_node rb_node;
	struct list_head bdi_list;
	long unsigned int ra_pages;
	long unsigned int io_pages;
	struct kref refcnt;
	unsigned int capabilities;
	unsigned int min_ratio;
	unsigned int max_ratio;
	unsigned int max_prop_frac;
	atomic_long_t tot_write_bandwidth;
	struct bdi_writeback wb;
	struct list_head wb_list;
	struct xarray cgwb_tree;
	struct mutex cgwb_release_mutex;
	struct rw_semaphore wb_switch_rwsem;
	wait_queue_head_t wb_waitq;
	struct device *dev;
	char dev_name[64];
	struct device *owner;
	struct timer_list laptop_mode_wb_timer;
	struct dentry *debug_dir;
};

struct cgroup;

struct css_set {
	struct cgroup_subsys_state *subsys[14];
	refcount_t refcount;
	struct css_set *dom_cset;
	struct cgroup *dfl_cgrp;
	int nr_tasks;
	struct list_head tasks;
	struct list_head mg_tasks;
	struct list_head dying_tasks;
	struct list_head task_iters;
	struct list_head e_cset_node[14];
	struct list_head threaded_csets;
	struct list_head threaded_csets_node;
	struct hlist_node hlist;
	struct list_head cgrp_links;
	struct list_head mg_preload_node;
	struct list_head mg_node;
	struct cgroup *mg_src_cgrp;
	struct cgroup *mg_dst_cgrp;
	struct css_set *mg_dst_cset;
	bool dead;
	struct callback_head callback_head;
};

struct perf_event_groups {
	struct rb_root tree;
	u64 index;
};

struct perf_event_context {
	struct pmu *pmu;
	raw_spinlock_t lock;
	struct mutex mutex;
	struct list_head active_ctx_list;
	struct perf_event_groups pinned_groups;
	struct perf_event_groups flexible_groups;
	struct list_head event_list;
	struct list_head pinned_active;
	struct list_head flexible_active;
	int nr_events;
	int nr_active;
	int nr_user;
	int is_active;
	int nr_stat;
	int nr_freq;
	int rotate_disable;
	int rotate_necessary;
	refcount_t refcount;
	struct task_struct *task;
	u64 time;
	u64 timestamp;
	u64 timeoffset;
	struct perf_event_context *parent_ctx;
	u64 parent_gen;
	u64 generation;
	int pin_count;
	int nr_cgroups;
	void *task_ctx_data;
	struct callback_head callback_head;
};

struct pipe_buffer;

struct watch_queue;

struct pipe_inode_info {
	struct mutex mutex;
	wait_queue_head_t rd_wait;
	wait_queue_head_t wr_wait;
	unsigned int head;
	unsigned int tail;
	unsigned int max_usage;
	unsigned int ring_size;
	bool note_loss;
	unsigned int nr_accounted;
	unsigned int readers;
	unsigned int writers;
	unsigned int files;
	unsigned int r_counter;
	unsigned int w_counter;
	unsigned int poll_usage;
	struct page *tmp_page;
	struct fasync_struct *fasync_readers;
	struct fasync_struct *fasync_writers;
	struct pipe_buffer *bufs;
	struct user_struct *user;
	struct watch_queue *watch_queue;
};

struct task_delay_info {
	raw_spinlock_t lock;
	unsigned int flags;
	u64 blkio_start;
	u64 blkio_delay;
	u64 swapin_start;
	u64 swapin_delay;
	u32 blkio_count;
	u32 swapin_count;
	u64 freepages_start;
	u64 freepages_delay;
	u64 thrashing_start;
	u64 thrashing_delay;
	u64 compact_start;
	u64 compact_delay;
	u32 freepages_count;
	u32 thrashing_count;
	u32 compact_count;
};

typedef void (*kunit_try_catch_func_t)(void *);

struct kunit_try_catch {
	struct kunit *test;
	struct completion *try_completion;
	int try_result;
	kunit_try_catch_func_t try;
	kunit_try_catch_func_t catch;
	void *context;
};

enum kunit_status {
	KUNIT_SUCCESS = 0,
	KUNIT_FAILURE = 1,
	KUNIT_SKIPPED = 2,
};

struct kunit {
	void *priv;
	const char *name;
	char *log;
	struct kunit_try_catch try_catch;
	const void *param_value;
	int param_index;
	spinlock_t lock;
	enum kunit_status status;
	struct list_head resources;
	char status_comment[256];
};

struct ftrace_ret_stack {
	long unsigned int ret;
	long unsigned int func;
	long long unsigned int calltime;
	long long unsigned int subtime;
	long unsigned int *retp;
};

struct cgroup_subsys;

struct cgroup_subsys_state {
	struct cgroup *cgroup;
	struct cgroup_subsys *ss;
	struct percpu_ref refcnt;
	struct list_head sibling;
	struct list_head children;
	struct list_head rstat_css_node;
	int id;
	unsigned int flags;
	u64 serial_nr;
	atomic_t online_cnt;
	struct work_struct destroy_work;
	struct rcu_work destroy_rwork;
	struct cgroup_subsys_state *parent;
};

struct mem_cgroup_id {
	int id;
	refcount_t ref;
};

struct page_counter {
	atomic_long_t usage;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct cacheline_padding _pad1_;
	long unsigned int emin;
	atomic_long_t min_usage;
	atomic_long_t children_min_usage;
	long unsigned int elow;
	atomic_long_t low_usage;
	atomic_long_t children_low_usage;
	long unsigned int watermark;
	long unsigned int failcnt;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct cacheline_padding _pad2_;
	long unsigned int min;
	long unsigned int low;
	long unsigned int high;
	long unsigned int max;
	struct page_counter *parent;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct vmpressure {
	long unsigned int scanned;
	long unsigned int reclaimed;
	long unsigned int tree_scanned;
	long unsigned int tree_reclaimed;
	spinlock_t sr_lock;
	struct list_head events;
	struct mutex events_lock;
	struct work_struct work;
};

struct cgroup_file {
	struct kernfs_node *kn;
	long unsigned int notified_at;
	struct timer_list notify_timer;
};

struct mem_cgroup_threshold_ary;

struct mem_cgroup_thresholds {
	struct mem_cgroup_threshold_ary *primary;
	struct mem_cgroup_threshold_ary *spare;
};

struct fprop_global {
	struct percpu_counter events;
	unsigned int period;
	seqcount_t sequence;
};

struct wb_domain {
	spinlock_t lock;
	struct fprop_global completions;
	struct timer_list period_timer;
	long unsigned int period_time;
	long unsigned int dirty_limit_tstamp;
	long unsigned int dirty_limit;
};

struct wb_completion {
	atomic_t cnt;
	wait_queue_head_t *waitq;
};

struct memcg_cgwb_frn {
	u64 bdi_id;
	int memcg_id;
	u64 at;
	struct wb_completion done;
};

struct memcg_vmstats;

struct obj_cgroup;

struct memcg_vmstats_percpu;

struct mem_cgroup_per_node;

struct mem_cgroup {
	struct cgroup_subsys_state css;
	struct mem_cgroup_id id;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct page_counter memory;
	union {
		struct page_counter swap;
		struct page_counter memsw;
	};
	struct page_counter kmem;
	struct page_counter tcpmem;
	struct work_struct high_work;
	long unsigned int zswap_max;
	long unsigned int soft_limit;
	struct vmpressure vmpressure;
	bool oom_group;
	bool oom_lock;
	int under_oom;
	int swappiness;
	int oom_kill_disable;
	struct cgroup_file events_file;
	struct cgroup_file events_local_file;
	struct cgroup_file swap_events_file;
	struct mutex thresholds_lock;
	struct mem_cgroup_thresholds thresholds;
	struct mem_cgroup_thresholds memsw_thresholds;
	struct list_head oom_notify;
	long unsigned int move_charge_at_immigrate;
	spinlock_t move_lock;
	long unsigned int move_lock_flags;
	long: 64;
	struct cacheline_padding _pad1_;
	struct memcg_vmstats *vmstats;
	atomic_long_t memory_events[9];
	atomic_long_t memory_events_local[9];
	long unsigned int socket_pressure;
	bool tcpmem_active;
	int tcpmem_pressure;
	int kmemcg_id;
	struct obj_cgroup *objcg;
	struct list_head objcg_list;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct cacheline_padding _pad2_;
	atomic_t moving_account;
	struct task_struct *move_lock_task;
	struct memcg_vmstats_percpu *vmstats_percpu;
	struct list_head cgwb_list;
	struct wb_domain cgwb_domain;
	struct memcg_cgwb_frn cgwb_frn[4];
	struct list_head event_list;
	spinlock_t event_list_lock;
	struct deferred_split deferred_split_queue;
	struct mem_cgroup_per_node *nodeinfo[0];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct blk_integrity_profile;

struct blk_integrity {
	const struct blk_integrity_profile *profile;
	unsigned char flags;
	unsigned char tuple_size;
	unsigned char interval_exp;
	unsigned char tag_size;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

enum rpm_status {
	RPM_INVALID = 4294967295,
	RPM_ACTIVE = 0,
	RPM_RESUMING = 1,
	RPM_SUSPENDED = 2,
	RPM_SUSPENDING = 3,
};

enum blk_bounce {
	BLK_BOUNCE_NONE = 0,
	BLK_BOUNCE_HIGH = 1,
};

enum blk_zoned_model {
	BLK_ZONED_NONE = 0,
	BLK_ZONED_HA = 1,
	BLK_ZONED_HM = 2,
};

struct queue_limits {
	enum blk_bounce bounce;
	long unsigned int seg_boundary_mask;
	long unsigned int virt_boundary_mask;
	unsigned int max_hw_sectors;
	unsigned int max_dev_sectors;
	unsigned int chunk_sectors;
	unsigned int max_sectors;
	unsigned int max_segment_size;
	unsigned int physical_block_size;
	unsigned int logical_block_size;
	unsigned int alignment_offset;
	unsigned int io_min;
	unsigned int io_opt;
	unsigned int max_discard_sectors;
	unsigned int max_hw_discard_sectors;
	unsigned int max_secure_erase_sectors;
	unsigned int max_write_zeroes_sectors;
	unsigned int max_zone_append_sectors;
	unsigned int discard_granularity;
	unsigned int discard_alignment;
	unsigned int zone_write_granularity;
	short unsigned int max_segments;
	short unsigned int max_integrity_segments;
	short unsigned int max_discard_segments;
	unsigned char misaligned;
	unsigned char discard_misaligned;
	unsigned char raid_partial_stripes_expensive;
	enum blk_zoned_model zoned;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	long unsigned int rh_reserved5;
	long unsigned int rh_reserved6;
	long unsigned int rh_reserved7;
	long unsigned int rh_reserved8;
};

struct elevator_queue;

struct blk_queue_stats;

struct rq_qos;

struct blk_mq_ops;

struct blk_mq_ctx;

struct gendisk;

struct blk_stat_callback;

struct blk_rq_stat;

struct blk_mq_tags;

struct blkcg_gq;

struct blk_trace;

struct blk_flush_queue;

struct throtl_data;

struct blk_mq_tag_set;

struct request_queue {
	struct request *last_merge;
	struct elevator_queue *elevator;
	struct percpu_ref q_usage_counter;
	struct blk_queue_stats *stats;
	struct rq_qos *rq_qos;
	const struct blk_mq_ops *mq_ops;
	struct blk_mq_ctx *queue_ctx;
	unsigned int queue_depth;
	struct xarray hctx_table;
	unsigned int nr_hw_queues;
	void *queuedata;
	long unsigned int queue_flags;
	atomic_t pm_only;
	int id;
	spinlock_t queue_lock;
	struct gendisk *disk;
	struct kobject kobj;
	struct kobject *mq_kobj;
	struct blk_integrity integrity;
	struct device *dev;
	enum rpm_status rpm_status;
	long unsigned int nr_requests;
	unsigned int dma_pad_mask;
	unsigned int dma_alignment;
	unsigned int rq_timeout;
	int poll_nsec;
	struct blk_stat_callback *poll_cb;
	struct blk_rq_stat *poll_stat;
	struct timer_list timeout;
	struct work_struct timeout_work;
	atomic_t nr_active_requests_shared_tags;
	struct blk_mq_tags *sched_shared_tags;
	struct list_head icq_list;
	long unsigned int blkcg_pols[1];
	struct blkcg_gq *root_blkg;
	struct list_head blkg_list;
	struct queue_limits limits;
	unsigned int required_elevator_features;
	int node;
	struct blk_trace *blk_trace;
	struct blk_flush_queue *fq;
	struct list_head requeue_list;
	spinlock_t requeue_lock;
	struct delayed_work requeue_work;
	struct mutex sysfs_lock;
	struct mutex sysfs_dir_lock;
	struct list_head unused_hctx_list;
	spinlock_t unused_hctx_lock;
	int mq_freeze_depth;
	struct throtl_data *td;
	struct callback_head callback_head;
	wait_queue_head_t mq_freeze_wq;
	struct mutex mq_freeze_lock;
	int quiesce_depth;
	struct blk_mq_tag_set *tag_set;
	struct list_head tag_set_list;
	struct dentry *debugfs_dir;
	struct dentry *sched_debugfs_dir;
	struct dentry *rqos_debugfs_dir;
	struct mutex debugfs_mutex;
	bool mq_sysfs_init_done;
	struct srcu_struct srcu[0];
};

typedef void (*poll_queue_proc)(struct file *, wait_queue_head_t *, struct poll_table_struct *);

struct poll_table_struct {
	poll_queue_proc _qproc;
	__poll_t _key;
};

struct trace_event_functions;

struct trace_event {
	struct hlist_node node;
	struct list_head list;
	int type;
	struct trace_event_functions *funcs;
};

struct trace_event_class;

struct bpf_prog_array;

struct trace_event_call {
	struct list_head list;
	struct trace_event_class *class;
	union {
		char *name;
		struct tracepoint *tp;
	};
	struct trace_event event;
	char *print_fmt;
	struct event_filter *filter;
	void *mod;
	void *data;
	int flags;
	int perf_refcount;
	struct hlist_head *perf_events;
	struct bpf_prog_array *prog_array;
	int (*perf_perm)(struct trace_event_call *, struct perf_event *);
};

struct trace_eval_map {
	const char *system;
	const char *eval_string;
	long unsigned int eval_value;
};

struct cgroup_base_stat {
	struct task_cputime cputime;
};

struct psi_group_cpu;

struct psi_group {
	struct mutex avgs_lock;
	struct psi_group_cpu *pcpu;
	u64 avg_total[6];
	u64 avg_last_update;
	u64 avg_next_update;
	struct delayed_work avgs_work;
	u64 total[12];
	long unsigned int avg[18];
	struct task_struct *poll_task;
	struct timer_list poll_timer;
	wait_queue_head_t poll_wait;
	atomic_t poll_wakeup;
	struct mutex trigger_lock;
	struct list_head triggers;
	u32 nr_triggers[6];
	u32 poll_states;
	u64 poll_min_period;
	u64 polling_total[6];
	u64 polling_next_update;
	u64 polling_until;
};

struct cgroup_bpf {
	struct bpf_prog_array *effective[23];
	struct list_head progs[23];
	u32 flags[23];
	struct list_head storages;
	struct bpf_prog_array *inactive;
	struct percpu_ref refcnt;
	struct work_struct release_work;
};

struct cgroup_freezer_state {
	bool freeze;
	int e_freeze;
	int nr_frozen_descendants;
	int nr_frozen_tasks;
};

struct cgroup_root;

struct cgroup_rstat_cpu;

struct cgroup {
	struct cgroup_subsys_state self;
	long unsigned int flags;
	int level;
	int max_depth;
	int nr_descendants;
	int nr_dying_descendants;
	int max_descendants;
	int nr_populated_csets;
	int nr_populated_domain_children;
	int nr_populated_threaded_children;
	int nr_threaded_children;
	struct kernfs_node *kn;
	struct cgroup_file procs_file;
	struct cgroup_file events_file;
	u16 subtree_control;
	u16 subtree_ss_mask;
	u16 old_subtree_control;
	u16 old_subtree_ss_mask;
	struct cgroup_subsys_state *subsys[14];
	struct cgroup_root *root;
	struct list_head cset_links;
	struct list_head e_csets[14];
	struct cgroup *dom_cgrp;
	struct cgroup *old_dom_cgrp;
	struct cgroup_rstat_cpu *rstat_cpu;
	struct list_head rstat_css_list;
	struct cgroup_base_stat last_bstat;
	struct cgroup_base_stat bstat;
	struct prev_cputime prev_cputime;
	struct list_head pidlists;
	struct mutex pidlist_mutex;
	wait_queue_head_t offline_waitq;
	struct work_struct release_agent_work;
	struct psi_group psi;
	struct cgroup_bpf bpf;
	atomic_t congestion_count;
	struct cgroup_freezer_state freezer;
	u64 ancestor_ids[0];
};

struct taskstats {
	__u16 version;
	__u32 ac_exitcode;
	__u8 ac_flag;
	__u8 ac_nice;
	__u64 cpu_count;
	__u64 cpu_delay_total;
	__u64 blkio_count;
	__u64 blkio_delay_total;
	__u64 swapin_count;
	__u64 swapin_delay_total;
	__u64 cpu_run_real_total;
	__u64 cpu_run_virtual_total;
	char ac_comm[32];
	__u8 ac_sched;
	__u8 ac_pad[3];
	int: 32;
	__u32 ac_uid;
	__u32 ac_gid;
	__u32 ac_pid;
	__u32 ac_ppid;
	__u32 ac_btime;
	__u64 ac_etime;
	__u64 ac_utime;
	__u64 ac_stime;
	__u64 ac_minflt;
	__u64 ac_majflt;
	__u64 coremem;
	__u64 virtmem;
	__u64 hiwater_rss;
	__u64 hiwater_vm;
	__u64 read_char;
	__u64 write_char;
	__u64 read_syscalls;
	__u64 write_syscalls;
	__u64 read_bytes;
	__u64 write_bytes;
	__u64 cancelled_write_bytes;
	__u64 nvcsw;
	__u64 nivcsw;
	__u64 ac_utimescaled;
	__u64 ac_stimescaled;
	__u64 cpu_scaled_run_real_total;
	__u64 freepages_count;
	__u64 freepages_delay_total;
	__u64 thrashing_count;
	__u64 thrashing_delay_total;
	__u64 ac_btime64;
	__u64 compact_count;
	__u64 compact_delay_total;
};

typedef void percpu_ref_func_t(struct percpu_ref *);

struct percpu_ref_data {
	atomic_long_t count;
	percpu_ref_func_t *release;
	percpu_ref_func_t *confirm_switch;
	bool force_atomic: 1;
	bool allow_reinit: 1;
	struct callback_head rcu;
	struct percpu_ref *ref;
};

struct wait_page_queue {
	struct folio *folio;
	int bit_nr;
	wait_queue_entry_t wait;
};

enum writeback_sync_modes {
	WB_SYNC_NONE = 0,
	WB_SYNC_ALL = 1,
};

struct writeback_control {
	long int nr_to_write;
	long int pages_skipped;
	loff_t range_start;
	loff_t range_end;
	enum writeback_sync_modes sync_mode;
	unsigned int for_kupdate: 1;
	unsigned int for_background: 1;
	unsigned int tagged_writepages: 1;
	unsigned int for_reclaim: 1;
	unsigned int range_cyclic: 1;
	unsigned int for_sync: 1;
	unsigned int unpinned_fscache_wb: 1;
	unsigned int no_cgroup_owner: 1;
	unsigned int punt_to_cgroup: 1;
	struct bdi_writeback *wb;
	struct inode *inode;
	int wb_id;
	int wb_lcand_id;
	int wb_tcand_id;
	size_t wb_bytes;
	size_t wb_lcand_bytes;
	size_t wb_tcand_bytes;
};

struct readahead_control {
	struct file *file;
	struct address_space *mapping;
	struct file_ra_state *ra;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int _index;
	unsigned int _nr_pages;
	unsigned int _batch_count;
	bool _workingset;
	long unsigned int _pflags;
};

struct iovec;

struct kvec;

struct bio_vec;

struct iov_iter {
	u8 iter_type;
	bool nofault;
	bool data_source;
	size_t iov_offset;
	size_t count;
	union {
		const struct iovec *iov;
		const struct kvec *kvec;
		const struct bio_vec *bvec;
		struct xarray *xarray;
		struct pipe_inode_info *pipe;
	};
	union {
		long unsigned int nr_segs;
		struct {
			unsigned int head;
			unsigned int start_head;
		};
		loff_t xarray_start;
	};
};

struct swap_cluster_info {
	spinlock_t lock;
	unsigned int data: 24;
	unsigned int flags: 8;
};

struct swap_cluster_list {
	struct swap_cluster_info head;
	struct swap_cluster_info tail;
};

struct percpu_cluster;

struct swap_info_struct {
	struct percpu_ref users;
	long unsigned int flags;
	short int prio;
	struct plist_node list;
	signed char type;
	unsigned int max;
	unsigned char *swap_map;
	struct swap_cluster_info *cluster_info;
	struct swap_cluster_list free_clusters;
	unsigned int lowest_bit;
	unsigned int highest_bit;
	unsigned int pages;
	unsigned int inuse_pages;
	unsigned int cluster_next;
	unsigned int cluster_nr;
	unsigned int *cluster_next_cpu;
	struct percpu_cluster *percpu_cluster;
	struct rb_root swap_extent_root;
	struct block_device *bdev;
	struct file *swap_file;
	unsigned int old_block_size;
	struct completion comp;
	long unsigned int *frontswap_map;
	atomic_t frontswap_pages;
	spinlock_t lock;
	spinlock_t cont_lock;
	struct work_struct discard_work;
	struct swap_cluster_list discard_clusters;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	struct plist_node avail_lists[0];
};

struct cdev {
	struct kobject kobj;
	struct module *owner;
	const struct file_operations *ops;
	struct list_head list;
	dev_t dev;
	unsigned int count;
};

enum dl_dev_state {
	DL_DEV_NO_DRIVER = 0,
	DL_DEV_PROBING = 1,
	DL_DEV_DRIVER_BOUND = 2,
	DL_DEV_UNBINDING = 3,
};

struct dev_links_info {
	struct list_head suppliers;
	struct list_head consumers;
	struct list_head defer_sync;
	enum dl_dev_state status;
};

struct pm_message {
	int event;
};

typedef struct pm_message pm_message_t;

enum rpm_request {
	RPM_REQ_NONE = 0,
	RPM_REQ_IDLE = 1,
	RPM_REQ_SUSPEND = 2,
	RPM_REQ_AUTOSUSPEND = 3,
	RPM_REQ_RESUME = 4,
};

struct wakeup_source;

struct wake_irq;

struct pm_subsys_data;

struct dev_pm_qos;

struct dev_pm_info {
	pm_message_t power_state;
	unsigned int can_wakeup: 1;
	unsigned int async_suspend: 1;
	bool in_dpm_list: 1;
	bool is_prepared: 1;
	bool is_suspended: 1;
	bool is_noirq_suspended: 1;
	bool is_late_suspended: 1;
	bool no_pm: 1;
	bool early_init: 1;
	bool direct_complete: 1;
	u32 driver_flags;
	spinlock_t lock;
	struct list_head entry;
	struct completion completion;
	struct wakeup_source *wakeup;
	bool wakeup_path: 1;
	bool syscore: 1;
	bool no_pm_callbacks: 1;
	unsigned int must_resume: 1;
	unsigned int may_skip_resume: 1;
	struct hrtimer suspend_timer;
	u64 timer_expires;
	struct work_struct work;
	wait_queue_head_t wait_queue;
	struct wake_irq *wakeirq;
	atomic_t usage_count;
	atomic_t child_count;
	unsigned int disable_depth: 3;
	unsigned int idle_notification: 1;
	unsigned int request_pending: 1;
	unsigned int deferred_resume: 1;
	unsigned int needs_force_resume: 1;
	unsigned int runtime_auto: 1;
	bool ignore_children: 1;
	unsigned int no_callbacks: 1;
	unsigned int irq_safe: 1;
	unsigned int use_autosuspend: 1;
	unsigned int timer_autosuspends: 1;
	unsigned int memalloc_noio: 1;
	unsigned int links_count;
	enum rpm_request request;
	enum rpm_status runtime_status;
	enum rpm_status last_status;
	int runtime_error;
	int autosuspend_delay;
	u64 last_busy;
	u64 active_time;
	u64 suspended_time;
	u64 accounting_timestamp;
	struct pm_subsys_data *subsys_data;
	void (*set_latency_tolerance)(struct device *, s32);
	struct dev_pm_qos *qos;
};

struct iommu_table;

struct pci_dn;

struct eeh_dev;

struct cxl_context;

struct dev_archdata {
	dma_addr_t dma_offset;
	struct iommu_table *iommu_table_base;
	struct pci_dn *pci_data;
	struct eeh_dev *edev;
	struct cxl_context *cxl_ctx;
	void *iov_data;
};

enum device_removable {
	DEVICE_REMOVABLE_NOT_SUPPORTED = 0,
	DEVICE_REMOVABLE_UNKNOWN = 1,
	DEVICE_FIXED = 2,
	DEVICE_REMOVABLE = 3,
};

struct device_private;

struct device_type;

struct bus_type;

struct device_driver;

struct dev_pm_domain;

struct em_perf_domain;

struct irq_domain;

struct dma_map_ops;

struct bus_dma_region;

struct device_dma_parameters;

struct dma_coherent_mem;

struct io_tlb_mem;

struct device_node;

struct fwnode_handle;

struct class;

struct iommu_group;

struct dev_iommu;

struct device {
	struct kobject kobj;
	struct device *parent;
	struct device_private *p;
	const char *init_name;
	const struct device_type *type;
	struct bus_type *bus;
	struct device_driver *driver;
	void *platform_data;
	void *driver_data;
	struct mutex mutex;
	struct dev_links_info links;
	struct dev_pm_info power;
	struct dev_pm_domain *pm_domain;
	struct em_perf_domain *em_pd;
	struct irq_domain *msi_domain;
	raw_spinlock_t msi_lock;
	struct list_head msi_list;
	const struct dma_map_ops *dma_ops;
	u64 *dma_mask;
	u64 coherent_dma_mask;
	u64 bus_dma_limit;
	const struct bus_dma_region *dma_range_map;
	struct device_dma_parameters *dma_parms;
	struct list_head dma_pools;
	struct dma_coherent_mem *dma_mem;
	struct io_tlb_mem *dma_io_tlb_mem;
	struct dev_archdata archdata;
	struct device_node *of_node;
	struct fwnode_handle *fwnode;
	int numa_node;
	dev_t devt;
	u32 id;
	spinlock_t devres_lock;
	struct list_head devres_head;
	struct class *class;
	const struct attribute_group **groups;
	void (*release)(struct device *);
	struct iommu_group *iommu_group;
	struct dev_iommu *iommu;
	enum device_removable removable;
	bool offline_disabled: 1;
	bool offline: 1;
	bool of_node_reused: 1;
	bool state_synced: 1;
	bool can_match: 1;
	bool dma_ops_bypass: 1;
};

struct disk_stats;

struct partition_meta_info;

struct block_device {
	sector_t bd_start_sect;
	sector_t bd_nr_sectors;
	struct disk_stats *bd_stats;
	long unsigned int bd_stamp;
	bool bd_read_only;
	dev_t bd_dev;
	atomic_t bd_openers;
	struct inode *bd_inode;
	struct super_block *bd_super;
	void *bd_claiming;
	struct device bd_device;
	void *bd_holder;
	int bd_holders;
	bool bd_write_holder;
	struct kobject *bd_holder_dir;
	u8 bd_partno;
	spinlock_t bd_size_lock;
	struct gendisk *bd_disk;
	struct request_queue *bd_queue;
	int bd_fsfreeze_count;
	struct mutex bd_fsfreeze_mutex;
	struct super_block *bd_fsfreeze_sb;
	struct partition_meta_info *bd_meta_info;
};

struct io_comp_batch {
	struct request *req_list;
	bool need_ts;
	void (*complete)(struct io_comp_batch *);
};

struct fc_log;

struct p_log {
	const char *prefix;
	struct fc_log *log;
};

enum fs_context_purpose {
	FS_CONTEXT_FOR_MOUNT = 0,
	FS_CONTEXT_FOR_SUBMOUNT = 1,
	FS_CONTEXT_FOR_RECONFIGURE = 2,
};

enum fs_context_phase {
	FS_CONTEXT_CREATE_PARAMS = 0,
	FS_CONTEXT_CREATING = 1,
	FS_CONTEXT_AWAITING_MOUNT = 2,
	FS_CONTEXT_AWAITING_RECONF = 3,
	FS_CONTEXT_RECONF_PARAMS = 4,
	FS_CONTEXT_RECONFIGURING = 5,
	FS_CONTEXT_FAILED = 6,
};

struct fs_context_operations;

struct fs_context {
	const struct fs_context_operations *ops;
	struct mutex uapi_mutex;
	struct file_system_type *fs_type;
	void *fs_private;
	void *sget_key;
	struct dentry *root;
	struct user_namespace *user_ns;
	struct net *net_ns;
	const struct cred *cred;
	struct p_log log;
	const char *source;
	void *security;
	void *s_fs_info;
	unsigned int sb_flags;
	unsigned int sb_flags_mask;
	unsigned int s_iflags;
	unsigned int lsm_flags;
	enum fs_context_purpose purpose: 8;
	enum fs_context_phase phase: 8;
	bool need_free: 1;
	bool global: 1;
	bool oldapi: 1;
};

struct audit_names;

struct filename {
	const char *name;
	const char *uptr;
	int refcnt;
	struct audit_names *aname;
	const char iname[0];
};

typedef __u32 blk_opf_t;

typedef u8 blk_status_t;

struct bvec_iter {
	sector_t bi_sector;
	unsigned int bi_size;
	unsigned int bi_idx;
	unsigned int bi_bvec_done;
} __attribute__((packed));

typedef unsigned int blk_qc_t;

typedef void bio_end_io_t(struct bio *);

struct bio_issue {
	u64 value;
};

struct bio_vec {
	struct page *bv_page;
	unsigned int bv_len;
	unsigned int bv_offset;
};

struct bio_integrity_payload;

struct bio_set;

struct bio {
	struct bio *bi_next;
	struct block_device *bi_bdev;
	blk_opf_t bi_opf;
	short unsigned int bi_flags;
	short unsigned int bi_ioprio;
	blk_status_t bi_status;
	atomic_t __bi_remaining;
	struct bvec_iter bi_iter;
	blk_qc_t bi_cookie;
	bio_end_io_t *bi_end_io;
	void *bi_private;
	struct blkcg_gq *bi_blkg;
	struct bio_issue bi_issue;
	union {
		struct bio_integrity_payload *bi_integrity;
	};
	short unsigned int bi_vcnt;
	short unsigned int bi_max_vecs;
	atomic_t __bi_cnt;
	struct bio_vec *bi_io_vec;
	struct bio_set *bi_pool;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	struct bio_vec bi_inline_vecs[0];
};

struct linux_binprm {
	struct vm_area_struct *vma;
	long unsigned int vma_pages;
	struct mm_struct *mm;
	long unsigned int p;
	long unsigned int argmin;
	unsigned int have_execfd: 1;
	unsigned int execfd_creds: 1;
	unsigned int secureexec: 1;
	unsigned int point_of_no_return: 1;
	struct file *executable;
	struct file *interpreter;
	struct file *file;
	struct cred *cred;
	int unsafe;
	unsigned int per_clear;
	int argc;
	int envc;
	const char *filename;
	const char *interp;
	const char *fdpath;
	unsigned int interp_flags;
	int execfd;
	long unsigned int loader;
	long unsigned int exec;
	struct rlimit rlim_stack;
	char buf[256];
};

struct coredump_params {
	const kernel_siginfo_t *siginfo;
	struct pt_regs *regs;
	struct file *file;
	long unsigned int limit;
	long unsigned int mm_flags;
	loff_t written;
	loff_t pos;
	loff_t to_skip;
};

struct em_perf_state {
	long unsigned int frequency;
	long unsigned int power;
	long unsigned int cost;
	long unsigned int flags;
};

struct em_perf_domain {
	struct em_perf_state *table;
	int nr_perf_states;
	long unsigned int flags;
	long unsigned int cpus[0];
};

struct dev_pm_ops {
	int (*prepare)(struct device *);
	void (*complete)(struct device *);
	int (*suspend)(struct device *);
	int (*resume)(struct device *);
	int (*freeze)(struct device *);
	int (*thaw)(struct device *);
	int (*poweroff)(struct device *);
	int (*restore)(struct device *);
	int (*suspend_late)(struct device *);
	int (*resume_early)(struct device *);
	int (*freeze_late)(struct device *);
	int (*thaw_early)(struct device *);
	int (*poweroff_late)(struct device *);
	int (*restore_early)(struct device *);
	int (*suspend_noirq)(struct device *);
	int (*resume_noirq)(struct device *);
	int (*freeze_noirq)(struct device *);
	int (*thaw_noirq)(struct device *);
	int (*poweroff_noirq)(struct device *);
	int (*restore_noirq)(struct device *);
	int (*runtime_suspend)(struct device *);
	int (*runtime_resume)(struct device *);
	int (*runtime_idle)(struct device *);
};

struct pm_domain_data;

struct pm_subsys_data {
	spinlock_t lock;
	unsigned int refcount;
	unsigned int clock_op_might_sleep;
	struct mutex clock_mutex;
	struct list_head clock_list;
	struct pm_domain_data *domain_data;
};

struct wakeup_source {
	const char *name;
	int id;
	struct list_head entry;
	spinlock_t lock;
	struct wake_irq *wakeirq;
	struct timer_list timer;
	long unsigned int timer_expires;
	ktime_t total_time;
	ktime_t max_time;
	ktime_t last_time;
	ktime_t start_prevent_time;
	ktime_t prevent_sleep_time;
	long unsigned int event_count;
	long unsigned int active_count;
	long unsigned int relax_count;
	long unsigned int expire_count;
	long unsigned int wakeup_count;
	struct device *dev;
	bool active: 1;
	bool autosleep_enabled: 1;
};

struct dev_pm_domain {
	struct dev_pm_ops ops;
	int (*start)(struct device *);
	void (*detach)(struct device *, bool);
	int (*activate)(struct device *);
	void (*sync)(struct device *);
	void (*dismiss)(struct device *);
};

struct iommu_ops;

struct subsys_private;

struct bus_type {
	const char *name;
	const char *dev_name;
	struct device *dev_root;
	const struct attribute_group **bus_groups;
	const struct attribute_group **dev_groups;
	const struct attribute_group **drv_groups;
	int (*match)(struct device *, struct device_driver *);
	int (*uevent)(struct device *, struct kobj_uevent_env *);
	int (*probe)(struct device *);
	void (*sync_state)(struct device *);
	void (*remove)(struct device *);
	void (*shutdown)(struct device *);
	int (*online)(struct device *);
	int (*offline)(struct device *);
	int (*suspend)(struct device *, pm_message_t);
	int (*resume)(struct device *);
	int (*num_vf)(struct device *);
	int (*dma_configure)(struct device *);
	void (*dma_cleanup)(struct device *);
	const struct dev_pm_ops *pm;
	const struct iommu_ops *iommu_ops;
	struct subsys_private *p;
	struct lock_class_key lock_key;
	bool need_parent_lock;
};

enum probe_type {
	PROBE_DEFAULT_STRATEGY = 0,
	PROBE_PREFER_ASYNCHRONOUS = 1,
	PROBE_FORCE_SYNCHRONOUS = 2,
};

struct of_device_id;

struct acpi_device_id;

struct driver_private;

struct device_driver {
	const char *name;
	struct bus_type *bus;
	struct module *owner;
	const char *mod_name;
	bool suppress_bind_attrs;
	enum probe_type probe_type;
	const struct of_device_id *of_match_table;
	const struct acpi_device_id *acpi_match_table;
	int (*probe)(struct device *);
	void (*sync_state)(struct device *);
	int (*remove)(struct device *);
	void (*shutdown)(struct device *);
	int (*suspend)(struct device *, pm_message_t);
	int (*resume)(struct device *);
	const struct attribute_group **groups;
	const struct attribute_group **dev_groups;
	const struct dev_pm_ops *pm;
	void (*coredump)(struct device *);
	struct driver_private *p;
};

enum iommu_cap {
	IOMMU_CAP_CACHE_COHERENCY = 0,
	IOMMU_CAP_INTR_REMAP = 1,
	IOMMU_CAP_NOEXEC = 2,
	IOMMU_CAP_PRE_BOOT_PROTECTION = 3,
};

enum iommu_dev_features {
	IOMMU_DEV_FEAT_SVA = 0,
	IOMMU_DEV_FEAT_IOPF = 1,
};

struct iommu_domain;

struct iommu_device;

struct of_phandle_args;

struct iommu_sva;

struct iommu_fault_event;

struct iommu_page_response;

struct iommu_domain_ops;

struct iommu_ops {
	bool (*capable)(enum iommu_cap);
	struct iommu_domain * (*domain_alloc)(unsigned int);
	struct iommu_device * (*probe_device)(struct device *);
	void (*release_device)(struct device *);
	void (*probe_finalize)(struct device *);
	struct iommu_group * (*device_group)(struct device *);
	void (*get_resv_regions)(struct device *, struct list_head *);
	int (*of_xlate)(struct device *, struct of_phandle_args *);
	bool (*is_attach_deferred)(struct device *);
	int (*dev_enable_feat)(struct device *, enum iommu_dev_features);
	int (*dev_disable_feat)(struct device *, enum iommu_dev_features);
	struct iommu_sva * (*sva_bind)(struct device *, struct mm_struct *, void *);
	void (*sva_unbind)(struct iommu_sva *);
	u32 (*sva_get_pasid)(struct iommu_sva *);
	int (*page_response)(struct device *, struct iommu_fault_event *, struct iommu_page_response *);
	int (*def_domain_type)(struct device *);
	const struct iommu_domain_ops *default_domain_ops;
	long unsigned int pgsize_bitmap;
	struct module *owner;
};

struct device_type {
	const char *name;
	const struct attribute_group **groups;
	int (*uevent)(struct device *, struct kobj_uevent_env *);
	char * (*devnode)(struct device *, umode_t *, kuid_t *, kgid_t *);
	void (*release)(struct device *);
	const struct dev_pm_ops *pm;
};

struct class {
	const char *name;
	struct module *owner;
	const struct attribute_group **class_groups;
	const struct attribute_group **dev_groups;
	struct kobject *dev_kobj;
	int (*dev_uevent)(struct device *, struct kobj_uevent_env *);
	char * (*devnode)(struct device *, umode_t *);
	void (*class_release)(struct class *);
	void (*dev_release)(struct device *);
	int (*shutdown_pre)(struct device *);
	const struct kobj_ns_type_operations *ns_type;
	const void * (*namespace)(struct device *);
	void (*get_ownership)(struct device *, kuid_t *, kgid_t *);
	const struct dev_pm_ops *pm;
	struct subsys_private *p;
};

struct of_device_id {
	char name[32];
	char type[32];
	char compatible[128];
	const void *data;
};

typedef long unsigned int kernel_ulong_t;

struct acpi_device_id {
	__u8 id[9];
	kernel_ulong_t driver_data;
	__u32 cls;
	__u32 cls_msk;
};

struct pci_controller;

struct eeh_pe;

struct pci_dev;

struct eeh_dev {
	int mode;
	int bdfn;
	struct pci_controller *controller;
	int pe_config_addr;
	u32 config_space[16];
	int pcix_cap;
	int pcie_cap;
	int aer_cap;
	int af_cap;
	struct eeh_pe *pe;
	struct list_head entry;
	struct list_head rmv_entry;
	struct pci_dn *pdn;
	struct pci_dev *pdev;
	bool in_error;
	struct pci_dev *physfn;
	int vf_index;
};

struct device_dma_parameters {
	unsigned int max_segment_size;
	unsigned int min_align_mask;
	long unsigned int segment_boundary_mask;
};

enum irq_domain_bus_token {
	DOMAIN_BUS_ANY = 0,
	DOMAIN_BUS_WIRED = 1,
	DOMAIN_BUS_GENERIC_MSI = 2,
	DOMAIN_BUS_PCI_MSI = 3,
	DOMAIN_BUS_PLATFORM_MSI = 4,
	DOMAIN_BUS_NEXUS = 5,
	DOMAIN_BUS_IPI = 6,
	DOMAIN_BUS_FSL_MC_MSI = 7,
	DOMAIN_BUS_TI_SCI_INTA_MSI = 8,
	DOMAIN_BUS_WAKEUP = 9,
	DOMAIN_BUS_VMD_MSI = 10,
};

struct irq_domain_ops;

struct irq_domain_chip_generic;

struct irq_data;

struct irq_domain {
	struct list_head link;
	const char *name;
	const struct irq_domain_ops *ops;
	void *host_data;
	unsigned int flags;
	unsigned int mapcount;
	struct fwnode_handle *fwnode;
	enum irq_domain_bus_token bus_token;
	struct irq_domain_chip_generic *gc;
	struct irq_domain *parent;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	irq_hw_number_t hwirq_max;
	unsigned int revmap_size;
	struct xarray revmap_tree;
	struct mutex revmap_mutex;
	struct irq_data *revmap[0];
};

struct sg_table;

struct scatterlist;

struct dma_map_ops {
	unsigned int flags;
	void * (*alloc)(struct device *, size_t, dma_addr_t *, gfp_t, long unsigned int);
	void (*free)(struct device *, size_t, void *, dma_addr_t, long unsigned int);
	struct page * (*alloc_pages)(struct device *, size_t, dma_addr_t *, enum dma_data_direction, gfp_t);
	void (*free_pages)(struct device *, size_t, struct page *, dma_addr_t, enum dma_data_direction);
	struct sg_table * (*alloc_noncontiguous)(struct device *, size_t, enum dma_data_direction, gfp_t, long unsigned int);
	void (*free_noncontiguous)(struct device *, size_t, struct sg_table *, enum dma_data_direction);
	int (*mmap)(struct device *, struct vm_area_struct *, void *, dma_addr_t, size_t, long unsigned int);
	int (*get_sgtable)(struct device *, struct sg_table *, void *, dma_addr_t, size_t, long unsigned int);
	dma_addr_t (*map_page)(struct device *, struct page *, long unsigned int, size_t, enum dma_data_direction, long unsigned int);
	void (*unmap_page)(struct device *, dma_addr_t, size_t, enum dma_data_direction, long unsigned int);
	int (*map_sg)(struct device *, struct scatterlist *, int, enum dma_data_direction, long unsigned int);
	void (*unmap_sg)(struct device *, struct scatterlist *, int, enum dma_data_direction, long unsigned int);
	dma_addr_t (*map_resource)(struct device *, phys_addr_t, size_t, enum dma_data_direction, long unsigned int);
	void (*unmap_resource)(struct device *, dma_addr_t, size_t, enum dma_data_direction, long unsigned int);
	void (*sync_single_for_cpu)(struct device *, dma_addr_t, size_t, enum dma_data_direction);
	void (*sync_single_for_device)(struct device *, dma_addr_t, size_t, enum dma_data_direction);
	void (*sync_sg_for_cpu)(struct device *, struct scatterlist *, int, enum dma_data_direction);
	void (*sync_sg_for_device)(struct device *, struct scatterlist *, int, enum dma_data_direction);
	void (*cache_sync)(struct device *, void *, size_t, enum dma_data_direction);
	int (*dma_supported)(struct device *, u64);
	u64 (*get_required_mask)(struct device *);
	size_t (*max_mapping_size)(struct device *);
	size_t (*opt_mapping_size)();
	long unsigned int (*get_merge_boundary)(struct device *);
};

struct bus_dma_region {
	phys_addr_t cpu_start;
	dma_addr_t dma_start;
	u64 size;
	u64 offset;
};

struct fwnode_operations;

struct fwnode_handle {
	struct fwnode_handle *secondary;
	const struct fwnode_operations *ops;
	struct device *dev;
	struct list_head suppliers;
	struct list_head consumers;
	u8 flags;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
};

struct property;

struct device_node {
	const char *name;
	phandle phandle;
	const char *full_name;
	struct fwnode_handle fwnode;
	struct property *properties;
	struct property *deadprops;
	struct device_node *parent;
	struct device_node *child;
	struct device_node *sibling;
	struct kobject kobj;
	long unsigned int _flags;
	void *data;
};

enum cpuhp_state {
	CPUHP_INVALID = 4294967295,
	CPUHP_OFFLINE = 0,
	CPUHP_CREATE_THREADS = 1,
	CPUHP_PERF_PREPARE = 2,
	CPUHP_PERF_X86_PREPARE = 3,
	CPUHP_PERF_X86_AMD_UNCORE_PREP = 4,
	CPUHP_PERF_POWER = 5,
	CPUHP_PERF_SUPERH = 6,
	CPUHP_X86_HPET_DEAD = 7,
	CPUHP_X86_APB_DEAD = 8,
	CPUHP_X86_MCE_DEAD = 9,
	CPUHP_VIRT_NET_DEAD = 10,
	CPUHP_SLUB_DEAD = 11,
	CPUHP_DEBUG_OBJ_DEAD = 12,
	CPUHP_MM_WRITEBACK_DEAD = 13,
	CPUHP_MM_DEMOTION_DEAD = 14,
	CPUHP_MM_VMSTAT_DEAD = 15,
	CPUHP_SOFTIRQ_DEAD = 16,
	CPUHP_NET_MVNETA_DEAD = 17,
	CPUHP_CPUIDLE_DEAD = 18,
	CPUHP_ARM64_FPSIMD_DEAD = 19,
	CPUHP_ARM_OMAP_WAKE_DEAD = 20,
	CPUHP_IRQ_POLL_DEAD = 21,
	CPUHP_BLOCK_SOFTIRQ_DEAD = 22,
	CPUHP_BIO_DEAD = 23,
	CPUHP_ACPI_CPUDRV_DEAD = 24,
	CPUHP_S390_PFAULT_DEAD = 25,
	CPUHP_BLK_MQ_DEAD = 26,
	CPUHP_FS_BUFF_DEAD = 27,
	CPUHP_PRINTK_DEAD = 28,
	CPUHP_MM_MEMCQ_DEAD = 29,
	CPUHP_XFS_DEAD = 30,
	CPUHP_PERCPU_CNT_DEAD = 31,
	CPUHP_RADIX_DEAD = 32,
	CPUHP_PAGE_ALLOC = 33,
	CPUHP_NET_DEV_DEAD = 34,
	CPUHP_PCI_XGENE_DEAD = 35,
	CPUHP_IOMMU_IOVA_DEAD = 36,
	CPUHP_LUSTRE_CFS_DEAD = 37,
	CPUHP_AP_ARM_CACHE_B15_RAC_DEAD = 38,
	CPUHP_PADATA_DEAD = 39,
	CPUHP_AP_DTPM_CPU_DEAD = 40,
	CPUHP_RANDOM_PREPARE = 41,
	CPUHP_WORKQUEUE_PREP = 42,
	CPUHP_POWER_NUMA_PREPARE = 43,
	CPUHP_HRTIMERS_PREPARE = 44,
	CPUHP_PROFILE_PREPARE = 45,
	CPUHP_X2APIC_PREPARE = 46,
	CPUHP_SMPCFD_PREPARE = 47,
	CPUHP_RELAY_PREPARE = 48,
	CPUHP_SLAB_PREPARE = 49,
	CPUHP_MD_RAID5_PREPARE = 50,
	CPUHP_RCUTREE_PREP = 51,
	CPUHP_CPUIDLE_COUPLED_PREPARE = 52,
	CPUHP_POWERPC_PMAC_PREPARE = 53,
	CPUHP_POWERPC_MMU_CTX_PREPARE = 54,
	CPUHP_XEN_PREPARE = 55,
	CPUHP_XEN_EVTCHN_PREPARE = 56,
	CPUHP_ARM_SHMOBILE_SCU_PREPARE = 57,
	CPUHP_SH_SH3X_PREPARE = 58,
	CPUHP_NET_FLOW_PREPARE = 59,
	CPUHP_TOPOLOGY_PREPARE = 60,
	CPUHP_NET_IUCV_PREPARE = 61,
	CPUHP_ARM_BL_PREPARE = 62,
	CPUHP_TRACE_RB_PREPARE = 63,
	CPUHP_MM_ZS_PREPARE = 64,
	CPUHP_MM_ZSWP_MEM_PREPARE = 65,
	CPUHP_MM_ZSWP_POOL_PREPARE = 66,
	CPUHP_KVM_PPC_BOOK3S_PREPARE = 67,
	CPUHP_ZCOMP_PREPARE = 68,
	CPUHP_TIMERS_PREPARE = 69,
	CPUHP_MIPS_SOC_PREPARE = 70,
	CPUHP_BP_PREPARE_DYN = 71,
	CPUHP_BP_PREPARE_DYN_END = 91,
	CPUHP_BRINGUP_CPU = 92,
	CPUHP_AP_IDLE_DEAD = 93,
	CPUHP_AP_OFFLINE = 94,
	CPUHP_AP_SCHED_STARTING = 95,
	CPUHP_AP_RCUTREE_DYING = 96,
	CPUHP_AP_CPU_PM_STARTING = 97,
	CPUHP_AP_IRQ_GIC_STARTING = 98,
	CPUHP_AP_IRQ_HIP04_STARTING = 99,
	CPUHP_AP_IRQ_APPLE_AIC_STARTING = 100,
	CPUHP_AP_IRQ_ARMADA_XP_STARTING = 101,
	CPUHP_AP_IRQ_BCM2836_STARTING = 102,
	CPUHP_AP_IRQ_MIPS_GIC_STARTING = 103,
	CPUHP_AP_IRQ_RISCV_STARTING = 104,
	CPUHP_AP_IRQ_SIFIVE_PLIC_STARTING = 105,
	CPUHP_AP_ARM_MVEBU_COHERENCY = 106,
	CPUHP_AP_MICROCODE_LOADER = 107,
	CPUHP_AP_PERF_X86_AMD_UNCORE_STARTING = 108,
	CPUHP_AP_PERF_X86_STARTING = 109,
	CPUHP_AP_PERF_X86_AMD_IBS_STARTING = 110,
	CPUHP_AP_PERF_X86_CQM_STARTING = 111,
	CPUHP_AP_PERF_X86_CSTATE_STARTING = 112,
	CPUHP_AP_PERF_XTENSA_STARTING = 113,
	CPUHP_AP_MIPS_OP_LOONGSON3_STARTING = 114,
	CPUHP_AP_ARM_SDEI_STARTING = 115,
	CPUHP_AP_ARM_VFP_STARTING = 116,
	CPUHP_AP_ARM64_DEBUG_MONITORS_STARTING = 117,
	CPUHP_AP_PERF_ARM_HW_BREAKPOINT_STARTING = 118,
	CPUHP_AP_PERF_ARM_ACPI_STARTING = 119,
	CPUHP_AP_PERF_ARM_STARTING = 120,
	CPUHP_AP_ARM_L2X0_STARTING = 121,
	CPUHP_AP_EXYNOS4_MCT_TIMER_STARTING = 122,
	CPUHP_AP_ARM_ARCH_TIMER_STARTING = 123,
	CPUHP_AP_ARM_GLOBAL_TIMER_STARTING = 124,
	CPUHP_AP_JCORE_TIMER_STARTING = 125,
	CPUHP_AP_ARM_TWD_STARTING = 126,
	CPUHP_AP_QCOM_TIMER_STARTING = 127,
	CPUHP_AP_TEGRA_TIMER_STARTING = 128,
	CPUHP_AP_ARMADA_TIMER_STARTING = 129,
	CPUHP_AP_MARCO_TIMER_STARTING = 130,
	CPUHP_AP_MIPS_GIC_TIMER_STARTING = 131,
	CPUHP_AP_ARC_TIMER_STARTING = 132,
	CPUHP_AP_RISCV_TIMER_STARTING = 133,
	CPUHP_AP_CLINT_TIMER_STARTING = 134,
	CPUHP_AP_CSKY_TIMER_STARTING = 135,
	CPUHP_AP_TI_GP_TIMER_STARTING = 136,
	CPUHP_AP_HYPERV_TIMER_STARTING = 137,
	CPUHP_AP_KVM_STARTING = 138,
	CPUHP_AP_KVM_ARM_VGIC_INIT_STARTING = 139,
	CPUHP_AP_KVM_ARM_VGIC_STARTING = 140,
	CPUHP_AP_KVM_ARM_TIMER_STARTING = 141,
	CPUHP_AP_DUMMY_TIMER_STARTING = 142,
	CPUHP_AP_ARM_XEN_STARTING = 143,
	CPUHP_AP_ARM_CORESIGHT_STARTING = 144,
	CPUHP_AP_ARM_CORESIGHT_CTI_STARTING = 145,
	CPUHP_AP_ARM64_ISNDEP_STARTING = 146,
	CPUHP_AP_SMPCFD_DYING = 147,
	CPUHP_AP_X86_TBOOT_DYING = 148,
	CPUHP_AP_ARM_CACHE_B15_RAC_DYING = 149,
	CPUHP_AP_ONLINE = 150,
	CPUHP_TEARDOWN_CPU = 151,
	CPUHP_AP_ONLINE_IDLE = 152,
	CPUHP_AP_SCHED_WAIT_EMPTY = 153,
	CPUHP_AP_SMPBOOT_THREADS = 154,
	CPUHP_AP_X86_VDSO_VMA_ONLINE = 155,
	CPUHP_AP_IRQ_AFFINITY_ONLINE = 156,
	CPUHP_AP_BLK_MQ_ONLINE = 157,
	CPUHP_AP_ARM_MVEBU_SYNC_CLOCKS = 158,
	CPUHP_AP_X86_INTEL_EPB_ONLINE = 159,
	CPUHP_AP_PERF_ONLINE = 160,
	CPUHP_AP_PERF_X86_ONLINE = 161,
	CPUHP_AP_PERF_X86_UNCORE_ONLINE = 162,
	CPUHP_AP_PERF_X86_AMD_UNCORE_ONLINE = 163,
	CPUHP_AP_PERF_X86_AMD_POWER_ONLINE = 164,
	CPUHP_AP_PERF_X86_RAPL_ONLINE = 165,
	CPUHP_AP_PERF_X86_CQM_ONLINE = 166,
	CPUHP_AP_PERF_X86_CSTATE_ONLINE = 167,
	CPUHP_AP_PERF_X86_IDXD_ONLINE = 168,
	CPUHP_AP_PERF_S390_CF_ONLINE = 169,
	CPUHP_AP_PERF_S390_SF_ONLINE = 170,
	CPUHP_AP_PERF_ARM_CCI_ONLINE = 171,
	CPUHP_AP_PERF_ARM_CCN_ONLINE = 172,
	CPUHP_AP_PERF_ARM_HISI_DDRC_ONLINE = 173,
	CPUHP_AP_PERF_ARM_HISI_HHA_ONLINE = 174,
	CPUHP_AP_PERF_ARM_HISI_L3_ONLINE = 175,
	CPUHP_AP_PERF_ARM_HISI_PA_ONLINE = 176,
	CPUHP_AP_PERF_ARM_HISI_SLLC_ONLINE = 177,
	CPUHP_AP_PERF_ARM_L2X0_ONLINE = 178,
	CPUHP_AP_PERF_ARM_QCOM_L2_ONLINE = 179,
	CPUHP_AP_PERF_ARM_QCOM_L3_ONLINE = 180,
	CPUHP_AP_PERF_ARM_APM_XGENE_ONLINE = 181,
	CPUHP_AP_PERF_ARM_CAVIUM_TX2_UNCORE_ONLINE = 182,
	CPUHP_AP_PERF_POWERPC_NEST_IMC_ONLINE = 183,
	CPUHP_AP_PERF_POWERPC_CORE_IMC_ONLINE = 184,
	CPUHP_AP_PERF_POWERPC_THREAD_IMC_ONLINE = 185,
	CPUHP_AP_PERF_POWERPC_TRACE_IMC_ONLINE = 186,
	CPUHP_AP_PERF_POWERPC_HV_24x7_ONLINE = 187,
	CPUHP_AP_PERF_POWERPC_HV_GPCI_ONLINE = 188,
	CPUHP_AP_PERF_CSKY_ONLINE = 189,
	CPUHP_AP_WATCHDOG_ONLINE = 190,
	CPUHP_AP_WORKQUEUE_ONLINE = 191,
	CPUHP_AP_RANDOM_ONLINE = 192,
	CPUHP_AP_RCUTREE_ONLINE = 193,
	CPUHP_AP_BASE_CACHEINFO_ONLINE = 194,
	CPUHP_AP_ONLINE_DYN = 195,
	CPUHP_AP_ONLINE_DYN_END = 225,
	CPUHP_AP_MM_DEMOTION_ONLINE = 226,
	CPUHP_AP_X86_HPET_ONLINE = 227,
	CPUHP_AP_X86_KVM_CLK_ONLINE = 228,
	CPUHP_AP_ACTIVE = 229,
	CPUHP_ONLINE = 230,
};

struct ring_buffer_event {
	u32 type_len: 5;
	u32 time_delta: 27;
	u32 array[0];
};

struct seq_buf {
	char *buffer;
	size_t size;
	size_t len;
	loff_t readpos;
};

struct trace_seq {
	char buffer[65536];
	struct seq_buf seq;
	int full;
};

struct irq_desc;

typedef void (*irq_flow_handler_t)(struct irq_desc *);

struct msi_desc;

struct irq_common_data {
	unsigned int state_use_accessors;
	unsigned int node;
	void *handler_data;
	struct msi_desc *msi_desc;
	cpumask_var_t affinity;
};

struct irq_chip;

struct irq_data {
	u32 mask;
	unsigned int irq;
	long unsigned int hwirq;
	struct irq_common_data *common;
	struct irq_chip *chip;
	struct irq_domain *domain;
	struct irq_data *parent_data;
	void *chip_data;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
};

struct irqaction;

struct irq_affinity_notify;

struct proc_dir_entry;

struct irq_desc {
	struct irq_common_data irq_common_data;
	struct irq_data irq_data;
	unsigned int *kstat_irqs;
	irq_flow_handler_t handle_irq;
	struct irqaction *action;
	unsigned int status_use_accessors;
	unsigned int core_internal_state__do_not_mess_with_it;
	unsigned int depth;
	unsigned int wake_depth;
	unsigned int tot_count;
	unsigned int irq_count;
	long unsigned int last_unhandled;
	unsigned int irqs_unhandled;
	atomic_t threads_handled;
	int threads_handled_last;
	raw_spinlock_t lock;
	struct cpumask *percpu_enabled;
	const struct cpumask *percpu_affinity;
	const struct cpumask *affinity_hint;
	struct irq_affinity_notify *affinity_notify;
	long unsigned int threads_oneshot;
	atomic_t threads_active;
	wait_queue_head_t wait_for_threads;
	unsigned int nr_actions;
	unsigned int no_suspend_depth;
	unsigned int cond_suspend_depth;
	unsigned int force_resume_depth;
	struct proc_dir_entry *dir;
	struct callback_head rcu;
	struct kobject kobj;
	struct mutex request_mutex;
	int parent_irq;
	struct module *owner;
	const char *name;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct pci_bus;

struct eeh_pe {
	int type;
	int state;
	int addr;
	struct pci_controller *phb;
	struct pci_bus *bus;
	int check_count;
	int freeze_count;
	time64_t tstamp;
	int false_positives;
	atomic_t pass_dev_cnt;
	struct eeh_pe *parent;
	void *data;
	struct list_head child_list;
	struct list_head child;
	struct list_head edevs;
	long unsigned int stack_trace[64];
	int trace_entries;
};

enum dev_dma_attr {
	DEV_DMA_NOT_SUPPORTED = 0,
	DEV_DMA_NON_COHERENT = 1,
	DEV_DMA_COHERENT = 2,
};

struct fwnode_reference_args;

struct fwnode_endpoint;

struct fwnode_operations {
	struct fwnode_handle * (*get)(struct fwnode_handle *);
	void (*put)(struct fwnode_handle *);
	bool (*device_is_available)(const struct fwnode_handle *);
	const void * (*device_get_match_data)(const struct fwnode_handle *, const struct device *);
	bool (*device_dma_supported)(const struct fwnode_handle *);
	enum dev_dma_attr (*device_get_dma_attr)(const struct fwnode_handle *);
	bool (*property_present)(const struct fwnode_handle *, const char *);
	int (*property_read_int_array)(const struct fwnode_handle *, const char *, unsigned int, void *, size_t);
	int (*property_read_string_array)(const struct fwnode_handle *, const char *, const char **, size_t);
	const char * (*get_name)(const struct fwnode_handle *);
	const char * (*get_name_prefix)(const struct fwnode_handle *);
	struct fwnode_handle * (*get_parent)(const struct fwnode_handle *);
	struct fwnode_handle * (*get_next_child_node)(const struct fwnode_handle *, struct fwnode_handle *);
	struct fwnode_handle * (*get_named_child_node)(const struct fwnode_handle *, const char *);
	int (*get_reference_args)(const struct fwnode_handle *, const char *, const char *, unsigned int, unsigned int, struct fwnode_reference_args *);
	struct fwnode_handle * (*graph_get_next_endpoint)(const struct fwnode_handle *, struct fwnode_handle *);
	struct fwnode_handle * (*graph_get_remote_endpoint)(const struct fwnode_handle *);
	struct fwnode_handle * (*graph_get_port_parent)(struct fwnode_handle *);
	int (*graph_parse_endpoint)(const struct fwnode_handle *, struct fwnode_endpoint *);
	void * (*iomap)(struct fwnode_handle *, int);
	int (*irq_get)(const struct fwnode_handle *, unsigned int);
	int (*add_links)(struct fwnode_handle *);
};

struct fwnode_endpoint {
	unsigned int port;
	unsigned int id;
	const struct fwnode_handle *local_fwnode;
};

struct fwnode_reference_args {
	struct fwnode_handle *fwnode;
	unsigned int nargs;
	u64 args[8];
};

enum irqchip_irq_state {
	IRQCHIP_STATE_PENDING = 0,
	IRQCHIP_STATE_ACTIVE = 1,
	IRQCHIP_STATE_MASKED = 2,
	IRQCHIP_STATE_LINE_LEVEL = 3,
};

struct msi_msg;

struct irq_chip {
	struct device *parent_device;
	const char *name;
	unsigned int (*irq_startup)(struct irq_data *);
	void (*irq_shutdown)(struct irq_data *);
	void (*irq_enable)(struct irq_data *);
	void (*irq_disable)(struct irq_data *);
	void (*irq_ack)(struct irq_data *);
	void (*irq_mask)(struct irq_data *);
	void (*irq_mask_ack)(struct irq_data *);
	void (*irq_unmask)(struct irq_data *);
	void (*irq_eoi)(struct irq_data *);
	int (*irq_set_affinity)(struct irq_data *, const struct cpumask *, bool);
	int (*irq_retrigger)(struct irq_data *);
	int (*irq_set_type)(struct irq_data *, unsigned int);
	int (*irq_set_wake)(struct irq_data *, unsigned int);
	void (*irq_bus_lock)(struct irq_data *);
	void (*irq_bus_sync_unlock)(struct irq_data *);
	void (*irq_cpu_online)(struct irq_data *);
	void (*irq_cpu_offline)(struct irq_data *);
	void (*irq_suspend)(struct irq_data *);
	void (*irq_resume)(struct irq_data *);
	void (*irq_pm_shutdown)(struct irq_data *);
	void (*irq_calc_mask)(struct irq_data *);
	void (*irq_print_chip)(struct irq_data *, struct seq_file *);
	int (*irq_request_resources)(struct irq_data *);
	void (*irq_release_resources)(struct irq_data *);
	void (*irq_compose_msi_msg)(struct irq_data *, struct msi_msg *);
	void (*irq_write_msi_msg)(struct irq_data *, struct msi_msg *);
	int (*irq_get_irqchip_state)(struct irq_data *, enum irqchip_irq_state, bool *);
	int (*irq_set_irqchip_state)(struct irq_data *, enum irqchip_irq_state, bool);
	int (*irq_set_vcpu_affinity)(struct irq_data *, void *);
	void (*ipi_send_single)(struct irq_data *, unsigned int);
	void (*ipi_send_mask)(struct irq_data *, const struct cpumask *);
	int (*irq_nmi_setup)(struct irq_data *);
	void (*irq_nmi_teardown)(struct irq_data *);
	long unsigned int flags;
};

typedef irqreturn_t (*irq_handler_t)(int, void *);

struct irqaction {
	irq_handler_t handler;
	void *dev_id;
	void *percpu_dev_id;
	struct irqaction *next;
	irq_handler_t thread_fn;
	struct task_struct *thread;
	struct irqaction *secondary;
	unsigned int irq;
	unsigned int flags;
	long unsigned int thread_flags;
	long unsigned int thread_mask;
	const char *name;
	struct proc_dir_entry *dir;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct irq_affinity_notify {
	unsigned int irq;
	struct kref kref;
	struct work_struct work;
	void (*notify)(struct irq_affinity_notify *, const cpumask_t *);
	void (*release)(struct kref *);
};

struct irq_chip_regs {
	long unsigned int enable;
	long unsigned int disable;
	long unsigned int mask;
	long unsigned int ack;
	long unsigned int eoi;
	long unsigned int type;
	long unsigned int polarity;
};

struct irq_chip_type {
	struct irq_chip chip;
	struct irq_chip_regs regs;
	irq_flow_handler_t handler;
	u32 type;
	u32 mask_cache_priv;
	u32 *mask_cache;
};

struct irq_chip_generic {
	raw_spinlock_t lock;
	void *reg_base;
	u32 (*reg_readl)(void *);
	void (*reg_writel)(u32, void *);
	void (*suspend)(struct irq_chip_generic *);
	void (*resume)(struct irq_chip_generic *);
	unsigned int irq_base;
	unsigned int irq_cnt;
	u32 mask_cache;
	u32 type_cache;
	u32 polarity_cache;
	u32 wake_enabled;
	u32 wake_active;
	unsigned int num_ct;
	void *private;
	long unsigned int installed;
	long unsigned int unused;
	struct irq_domain *domain;
	struct list_head list;
	struct irq_chip_type chip_types[0];
};

enum irq_gc_flags {
	IRQ_GC_INIT_MASK_CACHE = 1,
	IRQ_GC_INIT_NESTED_LOCK = 2,
	IRQ_GC_MASK_CACHE_PER_TYPE = 4,
	IRQ_GC_NO_MASK = 8,
	IRQ_GC_BE_IO = 16,
};

struct irq_domain_chip_generic {
	unsigned int irqs_per_chip;
	unsigned int num_chips;
	unsigned int irq_flags_to_clear;
	unsigned int irq_flags_to_set;
	enum irq_gc_flags gc_flags;
	struct irq_chip_generic *gc[0];
};

enum perf_sw_ids {
	PERF_COUNT_SW_CPU_CLOCK = 0,
	PERF_COUNT_SW_TASK_CLOCK = 1,
	PERF_COUNT_SW_PAGE_FAULTS = 2,
	PERF_COUNT_SW_CONTEXT_SWITCHES = 3,
	PERF_COUNT_SW_CPU_MIGRATIONS = 4,
	PERF_COUNT_SW_PAGE_FAULTS_MIN = 5,
	PERF_COUNT_SW_PAGE_FAULTS_MAJ = 6,
	PERF_COUNT_SW_ALIGNMENT_FAULTS = 7,
	PERF_COUNT_SW_EMULATION_FAULTS = 8,
	PERF_COUNT_SW_DUMMY = 9,
	PERF_COUNT_SW_BPF_OUTPUT = 10,
	PERF_COUNT_SW_CGROUP_SWITCHES = 11,
	PERF_COUNT_SW_MAX = 12,
};

union perf_mem_data_src {
	__u64 val;
	struct {
		__u64 mem_op: 5;
		__u64 mem_lvl: 14;
		__u64 mem_snoop: 5;
		__u64 mem_lock: 2;
		__u64 mem_dtlb: 7;
		__u64 mem_lvl_num: 4;
		__u64 mem_remote: 1;
		__u64 mem_snoopx: 2;
		__u64 mem_blk: 3;
		__u64 mem_hops: 3;
		__u64 mem_rsvd: 18;
	};
};

struct perf_branch_entry {
	__u64 from;
	__u64 to;
	__u64 mispred: 1;
	__u64 predicted: 1;
	__u64 in_tx: 1;
	__u64 abort: 1;
	__u64 cycles: 16;
	__u64 type: 4;
	__u64 reserved: 40;
};

union perf_sample_weight {
	__u64 full;
	struct {
		__u32 var1_dw;
		__u16 var2_w;
		__u16 var3_w;
	};
};

struct new_utsname {
	char sysname[65];
	char nodename[65];
	char release[65];
	char version[65];
	char machine[65];
	char domainname[65];
};

struct uts_namespace {
	struct new_utsname name;
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	struct ns_common ns;
};

struct ref_tracker_dir {};

struct prot_inuse;

struct netns_core {
	struct ctl_table_header *sysctl_hdr;
	int sysctl_somaxconn;
	struct prot_inuse *prot_inuse;
};

struct ipstats_mib;

struct tcp_mib;

struct linux_mib;

struct udp_mib;

struct linux_xfrm_mib;

struct linux_tls_mib;

struct mptcp_mib;

struct icmp_mib;

struct icmpmsg_mib;

struct icmpv6_mib;

struct icmpv6msg_mib;

struct netns_mib {
	struct ipstats_mib *ip_statistics;
	struct ipstats_mib *ipv6_statistics;
	struct tcp_mib *tcp_statistics;
	struct linux_mib *net_statistics;
	struct udp_mib *udp_statistics;
	struct udp_mib *udp_stats_in6;
	struct linux_xfrm_mib *xfrm_statistics;
	struct linux_tls_mib *tls_statistics;
	struct mptcp_mib *mptcp_statistics;
	struct udp_mib *udplite_statistics;
	struct udp_mib *udplite_stats_in6;
	struct icmp_mib *icmp_statistics;
	struct icmpmsg_mib *icmpmsg_statistics;
	struct icmpv6_mib *icmpv6_statistics;
	struct icmpv6msg_mib *icmpv6msg_statistics;
	struct proc_dir_entry *proc_net_devsnmp6;
};

struct netns_packet {
	struct mutex sklist_lock;
	struct hlist_head sklist;
};

struct netns_unix {
	int sysctl_max_dgram_qlen;
	struct ctl_table_header *ctl;
};

struct netns_nexthop {
	struct rb_root rb_root;
	struct hlist_head *devhash;
	unsigned int seq;
	u32 last_id_allocated;
	struct blocking_notifier_head notifier_chain;
};

struct inet_hashinfo;

struct inet_timewait_death_row {
	atomic_t tw_count;
	char tw_pad[124];
	struct inet_hashinfo *hashinfo;
	int sysctl_max_tw_buckets;
};

struct local_ports {
	seqlock_t lock;
	int range[2];
	bool warned;
};

struct ping_group_range {
	seqlock_t lock;
	kgid_t range[2];
};

typedef struct {
	u64 key[2];
} siphash_key_t;

struct ipv4_devconf;

struct ip_ra_chain;

struct fib_rules_ops;

struct fib_table;

struct inet_peer_base;

struct fqdir;

struct tcp_congestion_ops;

struct tcp_fastopen_context;

struct fib_notifier_ops;

struct netns_ipv4 {
	struct inet_timewait_death_row tcp_death_row;
	struct ctl_table_header *forw_hdr;
	struct ctl_table_header *frags_hdr;
	struct ctl_table_header *ipv4_hdr;
	struct ctl_table_header *route_hdr;
	struct ctl_table_header *xfrm4_hdr;
	struct ipv4_devconf *devconf_all;
	struct ipv4_devconf *devconf_dflt;
	struct ip_ra_chain *ra_chain;
	struct mutex ra_mutex;
	struct fib_rules_ops *rules_ops;
	struct fib_table *fib_main;
	struct fib_table *fib_default;
	unsigned int fib_rules_require_fldissect;
	bool fib_has_custom_rules;
	bool fib_has_custom_local_routes;
	bool fib_offload_disabled;
	atomic_t fib_num_tclassid_users;
	struct hlist_head *fib_table_hash;
	struct sock *fibnl;
	struct sock *mc_autojoin_sk;
	struct inet_peer_base *peers;
	struct sock **tcp_sk;
	struct fqdir *fqdir;
	u8 sysctl_icmp_echo_ignore_all;
	u8 sysctl_icmp_echo_enable_probe;
	u8 sysctl_icmp_echo_ignore_broadcasts;
	u8 sysctl_icmp_ignore_bogus_error_responses;
	u8 sysctl_icmp_errors_use_inbound_ifaddr;
	int sysctl_icmp_ratelimit;
	int sysctl_icmp_ratemask;
	struct local_ports ip_local_ports;
	u8 sysctl_tcp_ecn;
	u8 sysctl_tcp_ecn_fallback;
	u8 sysctl_ip_default_ttl;
	u8 sysctl_ip_no_pmtu_disc;
	u8 sysctl_ip_fwd_use_pmtu;
	u8 sysctl_ip_fwd_update_priority;
	u8 sysctl_ip_nonlocal_bind;
	u8 sysctl_ip_autobind_reuse;
	u8 sysctl_ip_dynaddr;
	u8 sysctl_ip_early_demux;
	u8 sysctl_raw_l3mdev_accept;
	u8 sysctl_tcp_early_demux;
	u8 sysctl_udp_early_demux;
	u8 sysctl_nexthop_compat_mode;
	u8 sysctl_fwmark_reflect;
	u8 sysctl_tcp_fwmark_accept;
	u8 sysctl_tcp_l3mdev_accept;
	u8 sysctl_tcp_mtu_probing;
	int sysctl_tcp_mtu_probe_floor;
	int sysctl_tcp_base_mss;
	int sysctl_tcp_min_snd_mss;
	int sysctl_tcp_probe_threshold;
	u32 sysctl_tcp_probe_interval;
	int sysctl_tcp_keepalive_time;
	int sysctl_tcp_keepalive_intvl;
	u8 sysctl_tcp_keepalive_probes;
	u8 sysctl_tcp_syn_retries;
	u8 sysctl_tcp_synack_retries;
	u8 sysctl_tcp_syncookies;
	u8 sysctl_tcp_migrate_req;
	int sysctl_tcp_reordering;
	u8 sysctl_tcp_retries1;
	u8 sysctl_tcp_retries2;
	u8 sysctl_tcp_orphan_retries;
	u8 sysctl_tcp_tw_reuse;
	int sysctl_tcp_fin_timeout;
	unsigned int sysctl_tcp_notsent_lowat;
	u8 sysctl_tcp_sack;
	u8 sysctl_tcp_window_scaling;
	u8 sysctl_tcp_timestamps;
	u8 sysctl_tcp_early_retrans;
	u8 sysctl_tcp_recovery;
	u8 sysctl_tcp_thin_linear_timeouts;
	u8 sysctl_tcp_slow_start_after_idle;
	u8 sysctl_tcp_retrans_collapse;
	u8 sysctl_tcp_stdurg;
	u8 sysctl_tcp_rfc1337;
	u8 sysctl_tcp_abort_on_overflow;
	u8 sysctl_tcp_fack;
	int sysctl_tcp_max_reordering;
	int sysctl_tcp_adv_win_scale;
	u8 sysctl_tcp_dsack;
	u8 sysctl_tcp_app_win;
	u8 sysctl_tcp_frto;
	u8 sysctl_tcp_nometrics_save;
	u8 sysctl_tcp_no_ssthresh_metrics_save;
	u8 sysctl_tcp_moderate_rcvbuf;
	u8 sysctl_tcp_tso_win_divisor;
	u8 sysctl_tcp_workaround_signed_windows;
	int sysctl_tcp_limit_output_bytes;
	int sysctl_tcp_challenge_ack_limit;
	int sysctl_tcp_min_rtt_wlen;
	u8 sysctl_tcp_min_tso_segs;
	u8 sysctl_tcp_autocorking;
	u8 sysctl_tcp_reflect_tos;
	u8 sysctl_tcp_comp_sack_nr;
	int sysctl_tcp_invalid_ratelimit;
	int sysctl_tcp_pacing_ss_ratio;
	int sysctl_tcp_pacing_ca_ratio;
	int sysctl_tcp_wmem[3];
	int sysctl_tcp_rmem[3];
	long unsigned int sysctl_tcp_comp_sack_delay_ns;
	long unsigned int sysctl_tcp_comp_sack_slack_ns;
	int sysctl_max_syn_backlog;
	int sysctl_tcp_fastopen;
	const struct tcp_congestion_ops *tcp_congestion_control;
	struct tcp_fastopen_context *tcp_fastopen_ctx;
	spinlock_t tcp_fastopen_ctx_lock;
	unsigned int sysctl_tcp_fastopen_blackhole_timeout;
	atomic_t tfo_active_disable_times;
	long unsigned int tfo_active_disable_stamp;
	int sysctl_udp_wmem_min;
	int sysctl_udp_rmem_min;
	u8 sysctl_fib_notify_on_flag_change;
	u8 sysctl_udp_l3mdev_accept;
	u8 sysctl_igmp_llm_reports;
	int sysctl_igmp_max_memberships;
	int sysctl_igmp_max_msf;
	int sysctl_igmp_qrv;
	struct ping_group_range ping_group_range;
	atomic_t dev_addr_genid;
	long unsigned int *sysctl_local_reserved_ports;
	int sysctl_ip_prot_sock;
	struct list_head mr_tables;
	struct fib_rules_ops *mr_rules_ops;
	u32 sysctl_fib_multipath_hash_fields;
	u8 sysctl_fib_multipath_use_neigh;
	u8 sysctl_fib_multipath_hash_policy;
	struct fib_notifier_ops *notifier_ops;
	unsigned int fib_seq;
	struct fib_notifier_ops *ipmr_notifier_ops;
	unsigned int ipmr_seq;
	atomic_t rt_genid;
	siphash_key_t ip_id_key;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct dst_entry;

struct net_device;

struct sk_buff;

struct neighbour;

struct dst_ops {
	short unsigned int family;
	unsigned int gc_thresh;
	int (*gc)(struct dst_ops *);
	struct dst_entry * (*check)(struct dst_entry *, __u32);
	unsigned int (*default_advmss)(const struct dst_entry *);
	unsigned int (*mtu)(const struct dst_entry *);
	u32 * (*cow_metrics)(struct dst_entry *, long unsigned int);
	void (*destroy)(struct dst_entry *);
	void (*ifdown)(struct dst_entry *, struct net_device *, int);
	struct dst_entry * (*negative_advice)(struct dst_entry *);
	void (*link_failure)(struct sk_buff *);
	void (*update_pmtu)(struct dst_entry *, struct sock *, struct sk_buff *, u32, bool);
	void (*redirect)(struct dst_entry *, struct sock *, struct sk_buff *);
	int (*local_out)(struct net *, struct sock *, struct sk_buff *);
	struct neighbour * (*neigh_lookup)(const struct dst_entry *, struct sk_buff *, const void *);
	void (*confirm_neigh)(const struct dst_entry *, const void *);
	struct kmem_cache *kmem_cachep;
	struct percpu_counter pcpuc_entries;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct netns_sysctl_ipv6 {
	struct ctl_table_header *hdr;
	struct ctl_table_header *route_hdr;
	struct ctl_table_header *icmp_hdr;
	struct ctl_table_header *frags_hdr;
	struct ctl_table_header *xfrm6_hdr;
	int flush_delay;
	int ip6_rt_max_size;
	int ip6_rt_gc_min_interval;
	int ip6_rt_gc_timeout;
	int ip6_rt_gc_interval;
	int ip6_rt_gc_elasticity;
	int ip6_rt_mtu_expires;
	int ip6_rt_min_advmss;
	u32 multipath_hash_fields;
	u8 multipath_hash_policy;
	u8 bindv6only;
	u8 flowlabel_consistency;
	u8 auto_flowlabels;
	int icmpv6_time;
	u8 icmpv6_echo_ignore_all;
	u8 icmpv6_echo_ignore_multicast;
	u8 icmpv6_echo_ignore_anycast;
	long unsigned int icmpv6_ratemask[4];
	long unsigned int *icmpv6_ratemask_ptr;
	u8 anycast_src_echo_reply;
	u8 ip_nonlocal_bind;
	u8 fwmark_reflect;
	u8 flowlabel_state_ranges;
	int idgen_retries;
	int idgen_delay;
	int flowlabel_reflect;
	int max_dst_opts_cnt;
	int max_hbh_opts_cnt;
	int max_dst_opts_len;
	int max_hbh_opts_len;
	int seg6_flowlabel;
	bool skip_notify_on_dev_down;
	u8 fib_notify_on_flag_change;
};

struct ipv6_devconf;

struct fib6_info;

struct rt6_info;

struct rt6_statistics;

struct fib6_table;

struct seg6_pernet_data;

struct netns_ipv6 {
	struct dst_ops ip6_dst_ops;
	struct netns_sysctl_ipv6 sysctl;
	struct ipv6_devconf *devconf_all;
	struct ipv6_devconf *devconf_dflt;
	struct inet_peer_base *peers;
	struct fqdir *fqdir;
	struct fib6_info *fib6_null_entry;
	struct rt6_info *ip6_null_entry;
	struct rt6_statistics *rt6_stats;
	struct timer_list ip6_fib_timer;
	struct hlist_head *fib_table_hash;
	struct fib6_table *fib6_main_tbl;
	struct list_head fib6_walkers;
	rwlock_t fib6_walker_lock;
	spinlock_t fib6_gc_lock;
	atomic_t ip6_rt_gc_expire;
	long unsigned int ip6_rt_last_gc;
	unsigned char flowlabel_has_excl;
	bool fib6_has_custom_rules;
	unsigned int fib6_rules_require_fldissect;
	struct rt6_info *ip6_prohibit_entry;
	struct rt6_info *ip6_blk_hole_entry;
	struct fib6_table *fib6_local_tbl;
	struct fib_rules_ops *fib6_rules_ops;
	struct sock **icmp_sk;
	struct sock *ndisc_sk;
	struct sock *tcp_sk;
	struct sock *igmp_sk;
	struct sock *mc_autojoin_sk;
	struct list_head mr6_tables;
	struct fib_rules_ops *mr6_rules_ops;
	atomic_t dev_addr_genid;
	atomic_t fib6_sernum;
	struct seg6_pernet_data *seg6_data;
	struct fib_notifier_ops *notifier_ops;
	struct fib_notifier_ops *ip6mr_notifier_ops;
	unsigned int ipmr_seq;
	struct {
		struct hlist_head head;
		spinlock_t lock;
		u32 seq;
	} ip6addrlbl_table;
	long: 64;
	long: 64;
};

struct netns_sysctl_lowpan {
	struct ctl_table_header *frags_hdr;
};

struct netns_ieee802154_lowpan {
	struct netns_sysctl_lowpan sysctl;
	struct fqdir *fqdir;
};

struct sctp_mib;

struct netns_sctp {
	struct sctp_mib *sctp_statistics;
	struct proc_dir_entry *proc_net_sctp;
	struct ctl_table_header *sysctl_header;
	struct sock *ctl_sock;
	struct sock *udp4_sock;
	struct sock *udp6_sock;
	int udp_port;
	int encap_port;
	struct list_head local_addr_list;
	struct list_head addr_waitq;
	struct timer_list addr_wq_timer;
	struct list_head auto_asconf_splist;
	spinlock_t addr_wq_lock;
	spinlock_t local_addr_lock;
	unsigned int rto_initial;
	unsigned int rto_min;
	unsigned int rto_max;
	int rto_alpha;
	int rto_beta;
	int max_burst;
	int cookie_preserve_enable;
	char *sctp_hmac_alg;
	unsigned int valid_cookie_life;
	unsigned int sack_timeout;
	unsigned int hb_interval;
	unsigned int probe_interval;
	int max_retrans_association;
	int max_retrans_path;
	int max_retrans_init;
	int pf_retrans;
	int ps_retrans;
	int pf_enable;
	int pf_expose;
	int sndbuf_policy;
	int rcvbuf_policy;
	int default_auto_asconf;
	int addip_enable;
	int addip_noauth;
	int prsctp_enable;
	int reconf_enable;
	int auth_enable;
	int intl_enable;
	int ecn_enable;
	int scope_policy;
	int rwnd_upd_shift;
	long unsigned int max_autoclose;
};

struct nf_queue_handler;

struct nf_logger;

struct nf_hook_entries;

struct netns_nf {
	struct proc_dir_entry *proc_netfilter;
	const struct nf_queue_handler *queue_handler;
	const struct nf_logger *nf_loggers[13];
	struct ctl_table_header *nf_log_dir_header;
	struct nf_hook_entries *hooks_ipv4[5];
	struct nf_hook_entries *hooks_ipv6[5];
	struct nf_hook_entries *hooks_arp[3];
	struct nf_hook_entries *hooks_bridge[5];
	unsigned int defrag_ipv4_users;
	unsigned int defrag_ipv6_users;
};

struct netns_xt {
	bool notrack_deprecated_warning;
	bool clusterip_deprecated_warning;
};

struct nf_generic_net {
	unsigned int timeout;
};

struct nf_tcp_net {
	unsigned int timeouts[14];
	u8 tcp_loose;
	u8 tcp_be_liberal;
	u8 tcp_max_retrans;
	u8 tcp_ignore_invalid_rst;
	unsigned int offload_timeout;
};

struct nf_udp_net {
	unsigned int timeouts[2];
	unsigned int offload_timeout;
};

struct nf_icmp_net {
	unsigned int timeout;
};

struct nf_dccp_net {
	u8 dccp_loose;
	unsigned int dccp_timeout[10];
};

struct nf_sctp_net {
	unsigned int timeouts[10];
};

struct nf_gre_net {
	struct list_head keymap_list;
	unsigned int timeouts[2];
};

struct nf_ip_net {
	struct nf_generic_net generic;
	struct nf_tcp_net tcp;
	struct nf_udp_net udp;
	struct nf_icmp_net icmp;
	struct nf_icmp_net icmpv6;
	struct nf_dccp_net dccp;
	struct nf_sctp_net sctp;
	struct nf_gre_net gre;
};

struct ip_conntrack_stat;

struct nf_ct_event_notifier;

struct netns_ct {
	u8 ctnetlink_has_listener;
	bool ecache_dwork_pending;
	u8 sysctl_log_invalid;
	u8 sysctl_events;
	u8 sysctl_acct;
	u8 sysctl_auto_assign_helper;
	u8 sysctl_tstamp;
	u8 sysctl_checksum;
	struct ip_conntrack_stat *stat;
	struct nf_ct_event_notifier *nf_conntrack_event_cb;
	struct nf_ip_net nf_ct_proto;
	unsigned int labels_used;
};

struct netns_nftables {
	u8 gencursor;
};

struct netns_bpf {
	struct bpf_prog_array *run_array[2];
	struct bpf_prog *progs[2];
	struct list_head links[2];
};

struct xfrm_policy_hash {
	struct hlist_head *table;
	unsigned int hmask;
	u8 dbits4;
	u8 sbits4;
	u8 dbits6;
	u8 sbits6;
};

struct xfrm_policy_hthresh {
	struct work_struct work;
	seqlock_t lock;
	u8 lbits4;
	u8 rbits4;
	u8 lbits6;
	u8 rbits6;
};

struct netns_xfrm {
	struct list_head state_all;
	struct hlist_head *state_bydst;
	struct hlist_head *state_bysrc;
	struct hlist_head *state_byspi;
	struct hlist_head *state_byseq;
	unsigned int state_hmask;
	unsigned int state_num;
	struct work_struct state_hash_work;
	struct list_head policy_all;
	struct hlist_head *policy_byidx;
	unsigned int policy_idx_hmask;
	struct hlist_head policy_inexact[3];
	struct xfrm_policy_hash policy_bydst[3];
	unsigned int policy_count[6];
	struct work_struct policy_hash_work;
	struct xfrm_policy_hthresh policy_hthresh;
	struct list_head inexact_bins;
	struct sock *nlsk;
	struct sock *nlsk_stash;
	u32 sysctl_aevent_etime;
	u32 sysctl_aevent_rseqth;
	int sysctl_larval_drop;
	u32 sysctl_acq_expires;
	struct ctl_table_header *sysctl_hdr;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct dst_ops xfrm4_dst_ops;
	struct dst_ops xfrm6_dst_ops;
	spinlock_t xfrm_state_lock;
	seqcount_spinlock_t xfrm_state_hash_generation;
	seqcount_spinlock_t xfrm_policy_hash_generation;
	spinlock_t xfrm_policy_lock;
	struct mutex xfrm_cfg_mutex;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct netns_ipvs;

struct mpls_route;

struct netns_mpls {
	int ip_ttl_propagate;
	int default_ttl;
	size_t platform_labels;
	struct mpls_route **platform_label;
	struct ctl_table_header *ctl;
};

struct can_dev_rcv_lists;

struct can_pkg_stats;

struct can_rcv_lists_stats;

struct netns_can {
	struct proc_dir_entry *proc_dir;
	struct proc_dir_entry *pde_stats;
	struct proc_dir_entry *pde_reset_stats;
	struct proc_dir_entry *pde_rcvlist_all;
	struct proc_dir_entry *pde_rcvlist_fil;
	struct proc_dir_entry *pde_rcvlist_inv;
	struct proc_dir_entry *pde_rcvlist_sff;
	struct proc_dir_entry *pde_rcvlist_eff;
	struct proc_dir_entry *pde_rcvlist_err;
	struct proc_dir_entry *bcmproc_dir;
	struct can_dev_rcv_lists *rx_alldev_list;
	spinlock_t rcvlists_lock;
	struct timer_list stattimer;
	struct can_pkg_stats *pkg_stats;
	struct can_rcv_lists_stats *rcv_lists_stats;
	struct hlist_head cgw_list;
};

struct netns_xdp {
	struct mutex lock;
	struct hlist_head list;
};

struct uevent_sock;

struct net_generic;

struct net {
	refcount_t passive;
	spinlock_t rules_mod_lock;
	unsigned int dev_unreg_count;
	unsigned int dev_base_seq;
	int ifindex;
	spinlock_t nsid_lock;
	atomic_t fnhe_genid;
	struct list_head list;
	struct list_head exit_list;
	struct llist_node cleanup_list;
	struct key_tag *key_domain;
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	struct idr netns_ids;
	struct ns_common ns;
	struct ref_tracker_dir refcnt_tracker;
	struct list_head dev_base_head;
	struct proc_dir_entry *proc_net;
	struct proc_dir_entry *proc_net_stat;
	struct ctl_table_set sysctls;
	struct sock *rtnl;
	struct sock *genl_sock;
	struct uevent_sock *uevent_sock;
	struct hlist_head *dev_name_head;
	struct hlist_head *dev_index_head;
	struct raw_notifier_head netdev_chain;
	u32 hash_mix;
	struct net_device *loopback_dev;
	struct list_head rules_ops;
	struct netns_core core;
	struct netns_mib mib;
	struct netns_packet packet;
	struct netns_unix unx;
	struct netns_nexthop nexthop;
	long: 64;
	struct netns_ipv4 ipv4;
	struct netns_ipv6 ipv6;
	struct netns_ieee802154_lowpan ieee802154_lowpan;
	struct netns_sctp sctp;
	struct netns_nf nf;
	struct netns_xt xt;
	struct netns_ct ct;
	struct netns_nftables nft;
	struct net_generic *gen;
	struct netns_bpf bpf;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct netns_xfrm xfrm;
	u64 net_cookie;
	struct netns_ipvs *ipvs;
	struct netns_mpls mpls;
	struct netns_can can;
	struct netns_xdp xdp;
	struct sock *crypto_nlsk;
	struct sock *diag_nlsk;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct cgroup_namespace {
	struct ns_common ns;
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	struct css_set *root_cset;
};

struct nsset {
	unsigned int flags;
	struct nsproxy *nsproxy;
	struct fs_struct *fs;
	const struct cred *cred;
};

struct ftrace_regs {
	struct pt_regs regs;
};

struct perf_regs {
	__u64 abi;
	struct pt_regs *regs;
};

struct u64_stats_sync {};

struct psi_group_cpu {
	seqcount_t seq;
	unsigned int tasks[4];
	u32 state_mask;
	u32 times[7];
	u64 state_start;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	u32 times_prev[14];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct cgroup_taskset;

struct cftype;

struct cgroup_subsys {
	struct cgroup_subsys_state * (*css_alloc)(struct cgroup_subsys_state *);
	int (*css_online)(struct cgroup_subsys_state *);
	void (*css_offline)(struct cgroup_subsys_state *);
	void (*css_released)(struct cgroup_subsys_state *);
	void (*css_free)(struct cgroup_subsys_state *);
	void (*css_reset)(struct cgroup_subsys_state *);
	void (*css_rstat_flush)(struct cgroup_subsys_state *, int);
	int (*css_extra_stat_show)(struct seq_file *, struct cgroup_subsys_state *);
	int (*can_attach)(struct cgroup_taskset *);
	void (*cancel_attach)(struct cgroup_taskset *);
	void (*attach)(struct cgroup_taskset *);
	void (*post_attach)();
	int (*can_fork)(struct task_struct *, struct css_set *);
	void (*cancel_fork)(struct task_struct *, struct css_set *);
	void (*fork)(struct task_struct *);
	void (*exit)(struct task_struct *);
	void (*release)(struct task_struct *);
	void (*bind)(struct cgroup_subsys_state *);
	bool early_init: 1;
	bool implicit_on_dfl: 1;
	bool threaded: 1;
	int id;
	const char *name;
	const char *legacy_name;
	struct cgroup_root *root;
	struct idr css_idr;
	struct list_head cfts;
	struct cftype *dfl_cftypes;
	struct cftype *legacy_cftypes;
	unsigned int depends_on;
};

struct cgroup_rstat_cpu {
	struct u64_stats_sync bsync;
	struct cgroup_base_stat bstat;
	struct cgroup_base_stat last_bstat;
	struct cgroup *updated_children;
	struct cgroup *updated_next;
};

struct cgroup_root {
	struct kernfs_root *kf_root;
	unsigned int subsys_mask;
	int hierarchy_id;
	struct cgroup cgrp;
	u64 cgrp_ancestor_id_storage;
	atomic_t nr_cgrps;
	struct list_head root_list;
	unsigned int flags;
	char release_agent_path[4096];
	char name[64];
};

struct cftype {
	char name[64];
	long unsigned int private;
	size_t max_write_len;
	unsigned int flags;
	unsigned int file_offset;
	struct cgroup_subsys *ss;
	struct list_head node;
	struct kernfs_ops *kf_ops;
	int (*open)(struct kernfs_open_file *);
	void (*release)(struct kernfs_open_file *);
	u64 (*read_u64)(struct cgroup_subsys_state *, struct cftype *);
	s64 (*read_s64)(struct cgroup_subsys_state *, struct cftype *);
	int (*seq_show)(struct seq_file *, void *);
	void * (*seq_start)(struct seq_file *, loff_t *);
	void * (*seq_next)(struct seq_file *, void *, loff_t *);
	void (*seq_stop)(struct seq_file *, void *);
	int (*write_u64)(struct cgroup_subsys_state *, struct cftype *, u64);
	int (*write_s64)(struct cgroup_subsys_state *, struct cftype *, s64);
	ssize_t (*write)(struct kernfs_open_file *, char *, size_t, loff_t);
	__poll_t (*poll)(struct kernfs_open_file *, struct poll_table_struct *);
};

struct perf_callchain_entry {
	__u64 nr;
	__u64 ip[0];
};

typedef long unsigned int (*perf_copy_f)(void *, const void *, long unsigned int, long unsigned int);

struct perf_raw_frag {
	union {
		struct perf_raw_frag *next;
		long unsigned int pad;
	};
	perf_copy_f copy;
	void *data;
	u32 size;
} __attribute__((packed));

struct perf_raw_record {
	struct perf_raw_frag frag;
	u32 size;
};

struct perf_branch_stack {
	__u64 nr;
	__u64 hw_idx;
	struct perf_branch_entry entries[0];
};

struct perf_cpu_context {
	struct perf_event_context ctx;
	struct perf_event_context *task_ctx;
	int active_oncpu;
	int exclusive;
	raw_spinlock_t hrtimer_lock;
	struct hrtimer hrtimer;
	ktime_t hrtimer_interval;
	unsigned int hrtimer_active;
	struct perf_cgroup *cgrp;
	struct list_head cgrp_cpuctx_entry;
	struct list_head sched_cb_entry;
	int sched_cb_usage;
	int online;
	int heap_size;
	struct perf_event **heap;
	struct perf_event *heap_default[2];
};

struct perf_output_handle {
	struct perf_event *event;
	struct perf_buffer *rb;
	long unsigned int wakeup;
	long unsigned int size;
	u64 aux_flags;
	union {
		void *addr;
		long unsigned int head;
	};
	int page;
};

struct perf_addr_filter_range {
	long unsigned int start;
	long unsigned int size;
};

struct perf_sample_data {
	u64 addr;
	struct perf_raw_record *raw;
	struct perf_branch_stack *br_stack;
	u64 period;
	union perf_sample_weight weight;
	u64 txn;
	union perf_mem_data_src data_src;
	u64 type;
	u64 ip;
	struct {
		u32 pid;
		u32 tid;
	} tid_entry;
	u64 time;
	u64 id;
	u64 stream_id;
	struct {
		u32 cpu;
		u32 reserved;
	} cpu_entry;
	struct perf_callchain_entry *callchain;
	u64 aux_size;
	struct perf_regs regs_user;
	struct perf_regs regs_intr;
	u64 stack_user_size;
	u64 phys_addr;
	u64 cgroup;
	u64 data_page_size;
	u64 code_page_size;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct perf_cgroup_info;

struct perf_cgroup {
	struct cgroup_subsys_state css;
	struct perf_cgroup_info *info;
};

struct perf_cgroup_info {
	u64 time;
	u64 timestamp;
	u64 timeoffset;
	int active;
};

struct trace_entry {
	short unsigned int type;
	unsigned char flags;
	unsigned char preempt_count;
	int pid;
};

struct trace_array;

struct tracer;

struct array_buffer;

struct ring_buffer_iter;

struct trace_iterator {
	struct trace_array *tr;
	struct tracer *trace;
	struct array_buffer *array_buffer;
	void *private;
	int cpu_file;
	struct mutex mutex;
	struct ring_buffer_iter **buffer_iter;
	long unsigned int iter_flags;
	void *temp;
	unsigned int temp_size;
	char *fmt;
	unsigned int fmt_size;
	struct trace_seq tmp_seq;
	cpumask_var_t started;
	bool snapshot;
	struct trace_seq seq;
	struct trace_entry *ent;
	long unsigned int lost_events;
	int leftover;
	int ent_size;
	int cpu;
	u64 ts;
	loff_t pos;
	long int idx;
};

enum print_line_t {
	TRACE_TYPE_PARTIAL_LINE = 0,
	TRACE_TYPE_HANDLED = 1,
	TRACE_TYPE_UNHANDLED = 2,
	TRACE_TYPE_NO_CONSUME = 3,
};

typedef enum print_line_t (*trace_print_func)(struct trace_iterator *, int, struct trace_event *);

struct trace_event_functions {
	trace_print_func trace;
	trace_print_func raw;
	trace_print_func hex;
	trace_print_func binary;
};

enum trace_reg {
	TRACE_REG_REGISTER = 0,
	TRACE_REG_UNREGISTER = 1,
	TRACE_REG_PERF_REGISTER = 2,
	TRACE_REG_PERF_UNREGISTER = 3,
	TRACE_REG_PERF_OPEN = 4,
	TRACE_REG_PERF_CLOSE = 5,
	TRACE_REG_PERF_ADD = 6,
	TRACE_REG_PERF_DEL = 7,
};

struct trace_event_fields {
	const char *type;
	union {
		struct {
			const char *name;
			const int size;
			const int align;
			const int is_signed;
			const int filter_type;
		};
		int (*define_fields)(struct trace_event_call *);
	};
};

struct trace_event_class {
	const char *system;
	void *probe;
	void *perf_probe;
	int (*reg)(struct trace_event_call *, enum trace_reg, void *);
	struct trace_event_fields *fields_array;
	struct list_head * (*get_fields)(struct trace_event_call *);
	struct list_head fields;
	int (*raw_init)(struct trace_event_call *);
};

struct trace_buffer;

struct trace_event_file;

struct trace_event_buffer {
	struct trace_buffer *buffer;
	struct ring_buffer_event *event;
	struct trace_event_file *trace_file;
	void *entry;
	unsigned int trace_ctx;
	struct pt_regs *regs;
};

struct trace_subsystem_dir;

struct trace_event_file {
	struct list_head list;
	struct trace_event_call *event_call;
	struct event_filter *filter;
	struct dentry *dir;
	struct trace_array *tr;
	struct trace_subsystem_dir *system;
	struct list_head triggers;
	long unsigned int flags;
	atomic_t sm_ref;
	atomic_t tm_ref;
};

enum {
	TRACE_EVENT_FL_FILTERED_BIT = 0,
	TRACE_EVENT_FL_CAP_ANY_BIT = 1,
	TRACE_EVENT_FL_NO_SET_FILTER_BIT = 2,
	TRACE_EVENT_FL_IGNORE_ENABLE_BIT = 3,
	TRACE_EVENT_FL_TRACEPOINT_BIT = 4,
	TRACE_EVENT_FL_KPROBE_BIT = 5,
	TRACE_EVENT_FL_UPROBE_BIT = 6,
};

enum {
	TRACE_EVENT_FL_FILTERED = 1,
	TRACE_EVENT_FL_CAP_ANY = 2,
	TRACE_EVENT_FL_NO_SET_FILTER = 4,
	TRACE_EVENT_FL_IGNORE_ENABLE = 8,
	TRACE_EVENT_FL_TRACEPOINT = 16,
	TRACE_EVENT_FL_KPROBE = 32,
	TRACE_EVENT_FL_UPROBE = 64,
};

enum {
	EVENT_FILE_FL_ENABLED_BIT = 0,
	EVENT_FILE_FL_RECORDED_CMD_BIT = 1,
	EVENT_FILE_FL_RECORDED_TGID_BIT = 2,
	EVENT_FILE_FL_FILTERED_BIT = 3,
	EVENT_FILE_FL_NO_SET_FILTER_BIT = 4,
	EVENT_FILE_FL_SOFT_MODE_BIT = 5,
	EVENT_FILE_FL_SOFT_DISABLED_BIT = 6,
	EVENT_FILE_FL_TRIGGER_MODE_BIT = 7,
	EVENT_FILE_FL_TRIGGER_COND_BIT = 8,
	EVENT_FILE_FL_PID_FILTER_BIT = 9,
	EVENT_FILE_FL_WAS_ENABLED_BIT = 10,
};

enum {
	EVENT_FILE_FL_ENABLED = 1,
	EVENT_FILE_FL_RECORDED_CMD = 2,
	EVENT_FILE_FL_RECORDED_TGID = 4,
	EVENT_FILE_FL_FILTERED = 8,
	EVENT_FILE_FL_NO_SET_FILTER = 16,
	EVENT_FILE_FL_SOFT_MODE = 32,
	EVENT_FILE_FL_SOFT_DISABLED = 64,
	EVENT_FILE_FL_TRIGGER_MODE = 128,
	EVENT_FILE_FL_TRIGGER_COND = 256,
	EVENT_FILE_FL_PID_FILTER = 512,
	EVENT_FILE_FL_WAS_ENABLED = 1024,
};

enum event_trigger_type {
	ETT_NONE = 0,
	ETT_TRACE_ONOFF = 1,
	ETT_SNAPSHOT = 2,
	ETT_STACKTRACE = 4,
	ETT_EVENT_ENABLE = 8,
	ETT_EVENT_HIST = 16,
	ETT_HIST_ENABLE = 32,
};

enum {
	FILTER_OTHER = 0,
	FILTER_STATIC_STRING = 1,
	FILTER_DYN_STRING = 2,
	FILTER_PTR_STRING = 3,
	FILTER_TRACE_FN = 4,
	FILTER_COMM = 5,
	FILTER_CPU = 6,
};

struct property {
	char *name;
	int length;
	void *value;
	struct property *next;
	long unsigned int _flags;
	struct bin_attribute attr;
};

struct irq_fwspec {
	struct fwnode_handle *fwnode;
	int param_count;
	u32 param[16];
};

struct irq_domain_ops {
	int (*match)(struct irq_domain *, struct device_node *, enum irq_domain_bus_token);
	int (*select)(struct irq_domain *, struct irq_fwspec *, enum irq_domain_bus_token);
	int (*map)(struct irq_domain *, unsigned int, irq_hw_number_t);
	void (*unmap)(struct irq_domain *, unsigned int);
	int (*xlate)(struct irq_domain *, struct device_node *, const u32 *, unsigned int, long unsigned int *, unsigned int *);
	int (*alloc)(struct irq_domain *, unsigned int, unsigned int, void *);
	void (*free)(struct irq_domain *, unsigned int, unsigned int);
	int (*activate)(struct irq_domain *, struct irq_data *, bool);
	void (*deactivate)(struct irq_domain *, struct irq_data *);
	int (*translate)(struct irq_domain *, struct irq_fwspec *, long unsigned int *, unsigned int *);
};

struct xbc_node {
	u16 next;
	u16 child;
	u16 parent;
	u16 data;
};

enum wb_stat_item {
	WB_RECLAIMABLE = 0,
	WB_WRITEBACK = 1,
	WB_DIRTIED = 2,
	WB_WRITTEN = 3,
	NR_WB_STAT_ITEMS = 4,
};

typedef void *mempool_alloc_t(gfp_t, void *);

typedef void mempool_free_t(void *, void *);

struct mempool_s {
	spinlock_t lock;
	int min_nr;
	int curr_nr;
	void **elements;
	void *pool_data;
	mempool_alloc_t *alloc;
	mempool_free_t *free;
	wait_queue_head_t wait;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
};

typedef struct mempool_s mempool_t;

struct bio_alloc_cache;

struct bio_set {
	struct kmem_cache *bio_slab;
	unsigned int front_pad;
	struct bio_alloc_cache *cache;
	mempool_t bio_pool;
	mempool_t bvec_pool;
	mempool_t bio_integrity_pool;
	mempool_t bvec_integrity_pool;
	unsigned int back_pad;
	spinlock_t rescue_lock;
	struct bio_list rescue_list;
	struct work_struct rescue_work;
	struct workqueue_struct *rescue_workqueue;
	struct hlist_node cpuhp_dead;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
};

struct block_device_operations;

struct timer_rand_state;

struct disk_events;

struct cdrom_device_info;

struct badblocks;

struct blk_independent_access_ranges;

struct gendisk {
	int major;
	int first_minor;
	int minors;
	char disk_name[32];
	short unsigned int events;
	short unsigned int event_flags;
	struct xarray part_tbl;
	struct block_device *part0;
	const struct block_device_operations *fops;
	struct request_queue *queue;
	void *private_data;
	struct bio_set bio_split;
	int flags;
	long unsigned int state;
	struct mutex open_mutex;
	unsigned int open_partitions;
	struct backing_dev_info *bdi;
	struct kobject *slave_dir;
	struct list_head slave_bdevs;
	struct timer_rand_state *random;
	atomic_t sync_io;
	struct disk_events *ev;
	struct kobject integrity_kobj;
	unsigned int nr_zones;
	unsigned int max_open_zones;
	unsigned int max_active_zones;
	long unsigned int *conv_zones_bitmap;
	long unsigned int *seq_zones_wlock;
	struct cdrom_device_info *cdi;
	int node_id;
	struct badblocks *bb;
	struct lockdep_map lockdep_map;
	u64 diskseq;
	struct blk_independent_access_ranges *ia_ranges;
};

struct partition_meta_info {
	char uuid[37];
	u8 volname[64];
};

struct bio_integrity_payload {
	struct bio *bip_bio;
	struct bvec_iter bip_iter;
	short unsigned int bip_vcnt;
	short unsigned int bip_max_vcnt;
	short unsigned int bip_flags;
	struct bvec_iter bio_iter;
	short: 16;
	struct work_struct bip_work;
	struct bio_vec *bip_vec;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	struct bio_vec bip_inline_vecs[0];
} __attribute__((packed));

enum req_op {
	REQ_OP_READ = 0,
	REQ_OP_WRITE = 1,
	REQ_OP_FLUSH = 2,
	REQ_OP_DISCARD = 3,
	REQ_OP_SECURE_ERASE = 5,
	REQ_OP_WRITE_ZEROES = 9,
	REQ_OP_ZONE_OPEN = 10,
	REQ_OP_ZONE_CLOSE = 11,
	REQ_OP_ZONE_FINISH = 12,
	REQ_OP_ZONE_APPEND = 13,
	REQ_OP_ZONE_RESET = 15,
	REQ_OP_ZONE_RESET_ALL = 17,
	REQ_OP_DRV_IN = 34,
	REQ_OP_DRV_OUT = 35,
	REQ_OP_LAST = 36,
};

struct blk_rq_stat {
	u64 mean;
	u64 min;
	u64 max;
	u32 nr_samples;
	u64 batch;
};

struct iovec {
	void *iov_base;
	__kernel_size_t iov_len;
};

struct kvec {
	void *iov_base;
	size_t iov_len;
};

enum memcg_memory_event {
	MEMCG_LOW = 0,
	MEMCG_HIGH = 1,
	MEMCG_MAX = 2,
	MEMCG_OOM = 3,
	MEMCG_OOM_KILL = 4,
	MEMCG_OOM_GROUP_KILL = 5,
	MEMCG_SWAP_HIGH = 6,
	MEMCG_SWAP_MAX = 7,
	MEMCG_SWAP_FAIL = 8,
	MEMCG_NR_MEMORY_EVENTS = 9,
};

struct mem_cgroup_reclaim_iter {
	struct mem_cgroup *position;
	unsigned int generation;
};

struct shrinker_info {
	struct callback_head rcu;
	atomic_long_t *nr_deferred;
	long unsigned int *map;
};

struct lruvec_stats_percpu {
	long int state[41];
	long int state_prev[41];
};

struct lruvec_stats {
	long int state[41];
	long int state_pending[41];
};

struct mem_cgroup_per_node {
	struct lruvec lruvec;
	struct lruvec_stats_percpu *lruvec_stats_percpu;
	struct lruvec_stats lruvec_stats;
	long unsigned int lru_zone_size[15];
	struct mem_cgroup_reclaim_iter iter;
	struct shrinker_info *shrinker_info;
	struct rb_node tree_node;
	long unsigned int usage_in_excess;
	bool on_tree;
	struct mem_cgroup *memcg;
};

struct eventfd_ctx;

struct mem_cgroup_threshold {
	struct eventfd_ctx *eventfd;
	long unsigned int threshold;
};

struct mem_cgroup_threshold_ary {
	int current_threshold;
	unsigned int size;
	struct mem_cgroup_threshold entries[0];
};

struct obj_cgroup {
	struct percpu_ref refcnt;
	struct mem_cgroup *memcg;
	atomic_t nr_charged_bytes;
	union {
		struct list_head list;
		struct callback_head rcu;
	};
};

struct dev_pagemap_ops {
	void (*page_free)(struct page *);
	vm_fault_t (*migrate_to_ram)(struct vm_fault *);
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

struct percpu_cluster {
	struct swap_cluster_info index;
	unsigned int next;
};

enum fs_value_type {
	fs_value_is_undefined = 0,
	fs_value_is_flag = 1,
	fs_value_is_string = 2,
	fs_value_is_blob = 3,
	fs_value_is_filename = 4,
	fs_value_is_file = 5,
};

struct fs_parameter {
	const char *key;
	enum fs_value_type type: 8;
	union {
		char *string;
		void *blob;
		struct filename *name;
		struct file *file;
	};
	size_t size;
	int dirfd;
};

struct fc_log {
	refcount_t usage;
	u8 head;
	u8 tail;
	u8 need_free;
	struct module *owner;
	char *buffer[8];
};

struct fs_context_operations {
	void (*free)(struct fs_context *);
	int (*dup)(struct fs_context *, struct fs_context *);
	int (*parse_param)(struct fs_context *, struct fs_parameter *);
	int (*parse_monolithic)(struct fs_context *, void *);
	int (*get_tree)(struct fs_context *);
	int (*reconfigure)(struct fs_context *);
};

struct fs_parse_result {
	bool negated;
	union {
		bool boolean;
		int int_32;
		unsigned int uint_32;
		u64 uint_64;
	};
};

struct blk_zone {
	__u64 start;
	__u64 len;
	__u64 wp;
	__u8 type;
	__u8 cond;
	__u8 non_seq;
	__u8 reset;
	__u8 resv[4];
	__u64 capacity;
	__u8 reserved[24];
};

struct blk_integrity_iter;

typedef blk_status_t integrity_processing_fn(struct blk_integrity_iter *);

typedef void integrity_prepare_fn(struct request *);

typedef void integrity_complete_fn(struct request *, unsigned int);

struct blk_integrity_profile {
	integrity_processing_fn *generate_fn;
	integrity_processing_fn *verify_fn;
	integrity_prepare_fn *prepare_fn;
	integrity_complete_fn *complete_fn;
	const char *name;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

typedef int (*report_zones_cb)(struct blk_zone *, unsigned int, void *);

enum blk_unique_id {
	BLK_UID_T10 = 1,
	BLK_UID_EUI64 = 2,
	BLK_UID_NAA = 3,
};

struct hd_geometry;

struct pr_ops;

struct block_device_operations {
	void (*submit_bio)(struct bio *);
	int (*poll_bio)(struct bio *, struct io_comp_batch *, unsigned int);
	int (*open)(struct block_device *, fmode_t);
	void (*release)(struct gendisk *, fmode_t);
	int (*rw_page)(struct block_device *, sector_t, struct page *, enum req_op);
	int (*ioctl)(struct block_device *, fmode_t, unsigned int, long unsigned int);
	int (*compat_ioctl)(struct block_device *, fmode_t, unsigned int, long unsigned int);
	unsigned int (*check_events)(struct gendisk *, unsigned int);
	void (*unlock_native_capacity)(struct gendisk *);
	int (*getgeo)(struct block_device *, struct hd_geometry *);
	int (*set_read_only)(struct block_device *, bool);
	void (*free_disk)(struct gendisk *);
	void (*swap_slot_free_notify)(struct block_device *, long unsigned int);
	int (*report_zones)(struct gendisk *, sector_t, unsigned int, report_zones_cb, void *);
	char * (*devnode)(struct gendisk *, umode_t *);
	int (*get_unique_id)(struct gendisk *, u8 *, enum blk_unique_id);
	struct module *owner;
	const struct pr_ops *pr_ops;
	int (*alternative_gpt_sector)(struct gendisk *, sector_t *);
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
};

struct blk_independent_access_range {
	struct kobject kobj;
	sector_t sector;
	sector_t nr_sectors;
};

struct blk_independent_access_ranges {
	struct kobject kobj;
	bool sysfs_registered;
	unsigned int nr_ia_ranges;
	struct blk_independent_access_range ia_range[0];
};

enum blk_eh_timer_return {
	BLK_EH_DONE = 0,
	BLK_EH_RESET_TIMER = 1,
};

struct blk_mq_hw_ctx;

struct blk_mq_queue_data;

struct blk_mq_ops {
	blk_status_t (*queue_rq)(struct blk_mq_hw_ctx *, const struct blk_mq_queue_data *);
	void (*commit_rqs)(struct blk_mq_hw_ctx *);
	void (*queue_rqs)(struct request **);
	int (*get_budget)(struct request_queue *);
	void (*put_budget)(struct request_queue *, int);
	void (*set_rq_budget_token)(struct request *, int);
	int (*get_rq_budget_token)(struct request *);
	enum blk_eh_timer_return (*timeout)(struct request *);
	int (*poll)(struct blk_mq_hw_ctx *, struct io_comp_batch *);
	void (*complete)(struct request *);
	int (*init_hctx)(struct blk_mq_hw_ctx *, void *, unsigned int);
	void (*exit_hctx)(struct blk_mq_hw_ctx *, unsigned int);
	int (*init_request)(struct blk_mq_tag_set *, struct request *, unsigned int, unsigned int);
	void (*exit_request)(struct blk_mq_tag_set *, struct request *, unsigned int);
	void (*cleanup_rq)(struct request *);
	bool (*busy)(struct request_queue *);
	void (*map_queues)(struct blk_mq_tag_set *);
	void (*show_rq)(struct seq_file *, struct request *);
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	long unsigned int rh_reserved5;
	long unsigned int rh_reserved6;
	long unsigned int rh_reserved7;
	long unsigned int rh_reserved8;
};

enum pr_type {
	PR_WRITE_EXCLUSIVE = 1,
	PR_EXCLUSIVE_ACCESS = 2,
	PR_WRITE_EXCLUSIVE_REG_ONLY = 3,
	PR_EXCLUSIVE_ACCESS_REG_ONLY = 4,
	PR_WRITE_EXCLUSIVE_ALL_REGS = 5,
	PR_EXCLUSIVE_ACCESS_ALL_REGS = 6,
};

struct pr_ops {
	int (*pr_register)(struct block_device *, u64, u64, u32);
	int (*pr_reserve)(struct block_device *, u64, enum pr_type, u32);
	int (*pr_release)(struct block_device *, u64, enum pr_type);
	int (*pr_preempt)(struct block_device *, u64, u64, enum pr_type, bool);
	int (*pr_clear)(struct block_device *, u64);
};

struct in6_addr {
	union {
		__u8 u6_addr8[16];
		__be16 u6_addr16[8];
		__be32 u6_addr32[4];
	} in6_u;
};

enum flow_dissector_key_id {
	FLOW_DISSECTOR_KEY_CONTROL = 0,
	FLOW_DISSECTOR_KEY_BASIC = 1,
	FLOW_DISSECTOR_KEY_IPV4_ADDRS = 2,
	FLOW_DISSECTOR_KEY_IPV6_ADDRS = 3,
	FLOW_DISSECTOR_KEY_PORTS = 4,
	FLOW_DISSECTOR_KEY_PORTS_RANGE = 5,
	FLOW_DISSECTOR_KEY_ICMP = 6,
	FLOW_DISSECTOR_KEY_ETH_ADDRS = 7,
	FLOW_DISSECTOR_KEY_TIPC = 8,
	FLOW_DISSECTOR_KEY_ARP = 9,
	FLOW_DISSECTOR_KEY_VLAN = 10,
	FLOW_DISSECTOR_KEY_FLOW_LABEL = 11,
	FLOW_DISSECTOR_KEY_GRE_KEYID = 12,
	FLOW_DISSECTOR_KEY_MPLS_ENTROPY = 13,
	FLOW_DISSECTOR_KEY_ENC_KEYID = 14,
	FLOW_DISSECTOR_KEY_ENC_IPV4_ADDRS = 15,
	FLOW_DISSECTOR_KEY_ENC_IPV6_ADDRS = 16,
	FLOW_DISSECTOR_KEY_ENC_CONTROL = 17,
	FLOW_DISSECTOR_KEY_ENC_PORTS = 18,
	FLOW_DISSECTOR_KEY_MPLS = 19,
	FLOW_DISSECTOR_KEY_TCP = 20,
	FLOW_DISSECTOR_KEY_IP = 21,
	FLOW_DISSECTOR_KEY_CVLAN = 22,
	FLOW_DISSECTOR_KEY_ENC_IP = 23,
	FLOW_DISSECTOR_KEY_ENC_OPTS = 24,
	FLOW_DISSECTOR_KEY_META = 25,
	FLOW_DISSECTOR_KEY_CT = 26,
	FLOW_DISSECTOR_KEY_HASH = 27,
	FLOW_DISSECTOR_KEY_NUM_OF_VLANS = 28,
	FLOW_DISSECTOR_KEY_PPPOE = 29,
	FLOW_DISSECTOR_KEY_MAX = 30,
};

typedef unsigned int sk_buff_data_t;

struct skb_ext;

struct sk_buff {
	union {
		struct {
			struct sk_buff *next;
			struct sk_buff *prev;
			union {
				struct net_device *dev;
				long unsigned int dev_scratch;
			};
		};
		struct rb_node rbnode;
		struct list_head list;
		struct llist_node ll_node;
	};
	union {
		struct sock *sk;
		int ip_defrag_offset;
	};
	union {
		ktime_t tstamp;
		u64 skb_mstamp_ns;
	};
	char cb[48];
	union {
		struct {
			long unsigned int _skb_refdst;
			void (*destructor)(struct sk_buff *);
		};
		struct list_head tcp_tsorted_anchor;
		long unsigned int _sk_redir;
	};
	long unsigned int _nfct;
	unsigned int len;
	unsigned int data_len;
	__u16 mac_len;
	__u16 hdr_len;
	__u16 queue_mapping;
	__u8 __cloned_offset[0];
	__u8 cloned: 1;
	__u8 nohdr: 1;
	__u8 fclone: 2;
	__u8 peeked: 1;
	__u8 head_frag: 1;
	__u8 pfmemalloc: 1;
	__u8 pp_recycle: 1;
	__u8 active_extensions;
	__u32 headers_start[0];
	__u8 __pkt_type_offset[0];
	__u8 pkt_type: 3;
	__u8 ignore_df: 1;
	__u8 nf_trace: 1;
	__u8 ip_summed: 2;
	__u8 ooo_okay: 1;
	__u8 l4_hash: 1;
	__u8 sw_hash: 1;
	__u8 wifi_acked_valid: 1;
	__u8 wifi_acked: 1;
	__u8 no_fcs: 1;
	__u8 encapsulation: 1;
	__u8 encap_hdr_csum: 1;
	__u8 csum_valid: 1;
	__u8 __pkt_vlan_present_offset[0];
	__u8 vlan_present: 1;
	__u8 csum_complete_sw: 1;
	__u8 csum_level: 2;
	__u8 csum_not_inet: 1;
	__u8 dst_pending_confirm: 1;
	__u8 ndisc_nodetype: 2;
	__u8 ipvs_property: 1;
	__u8 inner_protocol_type: 1;
	__u8 remcsum_offload: 1;
	__u8 offload_fwd_mark: 1;
	__u8 offload_l3_fwd_mark: 1;
	__u8 tc_skip_classify: 1;
	__u8 tc_at_ingress: 1;
	__u8 redirected: 1;
	__u8 from_ingress: 1;
	__u8 decrypted: 1;
	__u8 slow_gro: 1;
	__u16 tc_index;
	union {
		__wsum csum;
		struct {
			__u16 csum_start;
			__u16 csum_offset;
		};
	};
	__u32 priority;
	int skb_iif;
	__u32 hash;
	__be16 vlan_proto;
	__u16 vlan_tci;
	union {
		unsigned int napi_id;
		unsigned int sender_cpu;
	};
	__u32 secmark;
	union {
		__u32 mark;
		__u32 reserved_tailroom;
	};
	union {
		__be16 inner_protocol;
		__u8 inner_ipproto;
	};
	__u16 inner_transport_header;
	__u16 inner_network_header;
	__u16 inner_mac_header;
	__be16 protocol;
	__u16 transport_header;
	__u16 network_header;
	__u16 mac_header;
	__u32 headers_end[0];
	sk_buff_data_t tail;
	sk_buff_data_t end;
	unsigned char *head;
	unsigned char *data;
	unsigned int truesize;
	refcount_t users;
	struct skb_ext *extensions;
};

enum {
	IPSTATS_MIB_NUM = 0,
	IPSTATS_MIB_INPKTS = 1,
	IPSTATS_MIB_INOCTETS = 2,
	IPSTATS_MIB_INDELIVERS = 3,
	IPSTATS_MIB_OUTFORWDATAGRAMS = 4,
	IPSTATS_MIB_OUTPKTS = 5,
	IPSTATS_MIB_OUTOCTETS = 6,
	IPSTATS_MIB_INHDRERRORS = 7,
	IPSTATS_MIB_INTOOBIGERRORS = 8,
	IPSTATS_MIB_INNOROUTES = 9,
	IPSTATS_MIB_INADDRERRORS = 10,
	IPSTATS_MIB_INUNKNOWNPROTOS = 11,
	IPSTATS_MIB_INTRUNCATEDPKTS = 12,
	IPSTATS_MIB_INDISCARDS = 13,
	IPSTATS_MIB_OUTDISCARDS = 14,
	IPSTATS_MIB_OUTNOROUTES = 15,
	IPSTATS_MIB_REASMTIMEOUT = 16,
	IPSTATS_MIB_REASMREQDS = 17,
	IPSTATS_MIB_REASMOKS = 18,
	IPSTATS_MIB_REASMFAILS = 19,
	IPSTATS_MIB_FRAGOKS = 20,
	IPSTATS_MIB_FRAGFAILS = 21,
	IPSTATS_MIB_FRAGCREATES = 22,
	IPSTATS_MIB_INMCASTPKTS = 23,
	IPSTATS_MIB_OUTMCASTPKTS = 24,
	IPSTATS_MIB_INBCASTPKTS = 25,
	IPSTATS_MIB_OUTBCASTPKTS = 26,
	IPSTATS_MIB_INMCASTOCTETS = 27,
	IPSTATS_MIB_OUTMCASTOCTETS = 28,
	IPSTATS_MIB_INBCASTOCTETS = 29,
	IPSTATS_MIB_OUTBCASTOCTETS = 30,
	IPSTATS_MIB_CSUMERRORS = 31,
	IPSTATS_MIB_NOECTPKTS = 32,
	IPSTATS_MIB_ECT1PKTS = 33,
	IPSTATS_MIB_ECT0PKTS = 34,
	IPSTATS_MIB_CEPKTS = 35,
	IPSTATS_MIB_REASM_OVERLAPS = 36,
	__IPSTATS_MIB_MAX = 37,
};

enum {
	ICMP_MIB_NUM = 0,
	ICMP_MIB_INMSGS = 1,
	ICMP_MIB_INERRORS = 2,
	ICMP_MIB_INDESTUNREACHS = 3,
	ICMP_MIB_INTIMEEXCDS = 4,
	ICMP_MIB_INPARMPROBS = 5,
	ICMP_MIB_INSRCQUENCHS = 6,
	ICMP_MIB_INREDIRECTS = 7,
	ICMP_MIB_INECHOS = 8,
	ICMP_MIB_INECHOREPS = 9,
	ICMP_MIB_INTIMESTAMPS = 10,
	ICMP_MIB_INTIMESTAMPREPS = 11,
	ICMP_MIB_INADDRMASKS = 12,
	ICMP_MIB_INADDRMASKREPS = 13,
	ICMP_MIB_OUTMSGS = 14,
	ICMP_MIB_OUTERRORS = 15,
	ICMP_MIB_OUTDESTUNREACHS = 16,
	ICMP_MIB_OUTTIMEEXCDS = 17,
	ICMP_MIB_OUTPARMPROBS = 18,
	ICMP_MIB_OUTSRCQUENCHS = 19,
	ICMP_MIB_OUTREDIRECTS = 20,
	ICMP_MIB_OUTECHOS = 21,
	ICMP_MIB_OUTECHOREPS = 22,
	ICMP_MIB_OUTTIMESTAMPS = 23,
	ICMP_MIB_OUTTIMESTAMPREPS = 24,
	ICMP_MIB_OUTADDRMASKS = 25,
	ICMP_MIB_OUTADDRMASKREPS = 26,
	ICMP_MIB_CSUMERRORS = 27,
	__ICMP_MIB_MAX = 28,
};

enum {
	ICMP6_MIB_NUM = 0,
	ICMP6_MIB_INMSGS = 1,
	ICMP6_MIB_INERRORS = 2,
	ICMP6_MIB_OUTMSGS = 3,
	ICMP6_MIB_OUTERRORS = 4,
	ICMP6_MIB_CSUMERRORS = 5,
	__ICMP6_MIB_MAX = 6,
};

enum {
	TCP_MIB_NUM = 0,
	TCP_MIB_RTOALGORITHM = 1,
	TCP_MIB_RTOMIN = 2,
	TCP_MIB_RTOMAX = 3,
	TCP_MIB_MAXCONN = 4,
	TCP_MIB_ACTIVEOPENS = 5,
	TCP_MIB_PASSIVEOPENS = 6,
	TCP_MIB_ATTEMPTFAILS = 7,
	TCP_MIB_ESTABRESETS = 8,
	TCP_MIB_CURRESTAB = 9,
	TCP_MIB_INSEGS = 10,
	TCP_MIB_OUTSEGS = 11,
	TCP_MIB_RETRANSSEGS = 12,
	TCP_MIB_INERRS = 13,
	TCP_MIB_OUTRSTS = 14,
	TCP_MIB_CSUMERRORS = 15,
	__TCP_MIB_MAX = 16,
};

enum {
	UDP_MIB_NUM = 0,
	UDP_MIB_INDATAGRAMS = 1,
	UDP_MIB_NOPORTS = 2,
	UDP_MIB_INERRORS = 3,
	UDP_MIB_OUTDATAGRAMS = 4,
	UDP_MIB_RCVBUFERRORS = 5,
	UDP_MIB_SNDBUFERRORS = 6,
	UDP_MIB_CSUMERRORS = 7,
	UDP_MIB_IGNOREDMULTI = 8,
	UDP_MIB_MEMERRORS = 9,
	__UDP_MIB_MAX = 10,
};

enum {
	LINUX_MIB_NUM = 0,
	LINUX_MIB_SYNCOOKIESSENT = 1,
	LINUX_MIB_SYNCOOKIESRECV = 2,
	LINUX_MIB_SYNCOOKIESFAILED = 3,
	LINUX_MIB_EMBRYONICRSTS = 4,
	LINUX_MIB_PRUNECALLED = 5,
	LINUX_MIB_RCVPRUNED = 6,
	LINUX_MIB_OFOPRUNED = 7,
	LINUX_MIB_OUTOFWINDOWICMPS = 8,
	LINUX_MIB_LOCKDROPPEDICMPS = 9,
	LINUX_MIB_ARPFILTER = 10,
	LINUX_MIB_TIMEWAITED = 11,
	LINUX_MIB_TIMEWAITRECYCLED = 12,
	LINUX_MIB_TIMEWAITKILLED = 13,
	LINUX_MIB_PAWSACTIVEREJECTED = 14,
	LINUX_MIB_PAWSESTABREJECTED = 15,
	LINUX_MIB_DELAYEDACKS = 16,
	LINUX_MIB_DELAYEDACKLOCKED = 17,
	LINUX_MIB_DELAYEDACKLOST = 18,
	LINUX_MIB_LISTENOVERFLOWS = 19,
	LINUX_MIB_LISTENDROPS = 20,
	LINUX_MIB_TCPHPHITS = 21,
	LINUX_MIB_TCPPUREACKS = 22,
	LINUX_MIB_TCPHPACKS = 23,
	LINUX_MIB_TCPRENORECOVERY = 24,
	LINUX_MIB_TCPSACKRECOVERY = 25,
	LINUX_MIB_TCPSACKRENEGING = 26,
	LINUX_MIB_TCPSACKREORDER = 27,
	LINUX_MIB_TCPRENOREORDER = 28,
	LINUX_MIB_TCPTSREORDER = 29,
	LINUX_MIB_TCPFULLUNDO = 30,
	LINUX_MIB_TCPPARTIALUNDO = 31,
	LINUX_MIB_TCPDSACKUNDO = 32,
	LINUX_MIB_TCPLOSSUNDO = 33,
	LINUX_MIB_TCPLOSTRETRANSMIT = 34,
	LINUX_MIB_TCPRENOFAILURES = 35,
	LINUX_MIB_TCPSACKFAILURES = 36,
	LINUX_MIB_TCPLOSSFAILURES = 37,
	LINUX_MIB_TCPFASTRETRANS = 38,
	LINUX_MIB_TCPSLOWSTARTRETRANS = 39,
	LINUX_MIB_TCPTIMEOUTS = 40,
	LINUX_MIB_TCPLOSSPROBES = 41,
	LINUX_MIB_TCPLOSSPROBERECOVERY = 42,
	LINUX_MIB_TCPRENORECOVERYFAIL = 43,
	LINUX_MIB_TCPSACKRECOVERYFAIL = 44,
	LINUX_MIB_TCPRCVCOLLAPSED = 45,
	LINUX_MIB_TCPDSACKOLDSENT = 46,
	LINUX_MIB_TCPDSACKOFOSENT = 47,
	LINUX_MIB_TCPDSACKRECV = 48,
	LINUX_MIB_TCPDSACKOFORECV = 49,
	LINUX_MIB_TCPABORTONDATA = 50,
	LINUX_MIB_TCPABORTONCLOSE = 51,
	LINUX_MIB_TCPABORTONMEMORY = 52,
	LINUX_MIB_TCPABORTONTIMEOUT = 53,
	LINUX_MIB_TCPABORTONLINGER = 54,
	LINUX_MIB_TCPABORTFAILED = 55,
	LINUX_MIB_TCPMEMORYPRESSURES = 56,
	LINUX_MIB_TCPMEMORYPRESSURESCHRONO = 57,
	LINUX_MIB_TCPSACKDISCARD = 58,
	LINUX_MIB_TCPDSACKIGNOREDOLD = 59,
	LINUX_MIB_TCPDSACKIGNOREDNOUNDO = 60,
	LINUX_MIB_TCPSPURIOUSRTOS = 61,
	LINUX_MIB_TCPMD5NOTFOUND = 62,
	LINUX_MIB_TCPMD5UNEXPECTED = 63,
	LINUX_MIB_TCPMD5FAILURE = 64,
	LINUX_MIB_SACKSHIFTED = 65,
	LINUX_MIB_SACKMERGED = 66,
	LINUX_MIB_SACKSHIFTFALLBACK = 67,
	LINUX_MIB_TCPBACKLOGDROP = 68,
	LINUX_MIB_PFMEMALLOCDROP = 69,
	LINUX_MIB_TCPMINTTLDROP = 70,
	LINUX_MIB_TCPDEFERACCEPTDROP = 71,
	LINUX_MIB_IPRPFILTER = 72,
	LINUX_MIB_TCPTIMEWAITOVERFLOW = 73,
	LINUX_MIB_TCPREQQFULLDOCOOKIES = 74,
	LINUX_MIB_TCPREQQFULLDROP = 75,
	LINUX_MIB_TCPRETRANSFAIL = 76,
	LINUX_MIB_TCPRCVCOALESCE = 77,
	LINUX_MIB_TCPBACKLOGCOALESCE = 78,
	LINUX_MIB_TCPOFOQUEUE = 79,
	LINUX_MIB_TCPOFODROP = 80,
	LINUX_MIB_TCPOFOMERGE = 81,
	LINUX_MIB_TCPCHALLENGEACK = 82,
	LINUX_MIB_TCPSYNCHALLENGE = 83,
	LINUX_MIB_TCPFASTOPENACTIVE = 84,
	LINUX_MIB_TCPFASTOPENACTIVEFAIL = 85,
	LINUX_MIB_TCPFASTOPENPASSIVE = 86,
	LINUX_MIB_TCPFASTOPENPASSIVEFAIL = 87,
	LINUX_MIB_TCPFASTOPENLISTENOVERFLOW = 88,
	LINUX_MIB_TCPFASTOPENCOOKIEREQD = 89,
	LINUX_MIB_TCPFASTOPENBLACKHOLE = 90,
	LINUX_MIB_TCPSPURIOUS_RTX_HOSTQUEUES = 91,
	LINUX_MIB_BUSYPOLLRXPACKETS = 92,
	LINUX_MIB_TCPAUTOCORKING = 93,
	LINUX_MIB_TCPFROMZEROWINDOWADV = 94,
	LINUX_MIB_TCPTOZEROWINDOWADV = 95,
	LINUX_MIB_TCPWANTZEROWINDOWADV = 96,
	LINUX_MIB_TCPSYNRETRANS = 97,
	LINUX_MIB_TCPORIGDATASENT = 98,
	LINUX_MIB_TCPHYSTARTTRAINDETECT = 99,
	LINUX_MIB_TCPHYSTARTTRAINCWND = 100,
	LINUX_MIB_TCPHYSTARTDELAYDETECT = 101,
	LINUX_MIB_TCPHYSTARTDELAYCWND = 102,
	LINUX_MIB_TCPACKSKIPPEDSYNRECV = 103,
	LINUX_MIB_TCPACKSKIPPEDPAWS = 104,
	LINUX_MIB_TCPACKSKIPPEDSEQ = 105,
	LINUX_MIB_TCPACKSKIPPEDFINWAIT2 = 106,
	LINUX_MIB_TCPACKSKIPPEDTIMEWAIT = 107,
	LINUX_MIB_TCPACKSKIPPEDCHALLENGE = 108,
	LINUX_MIB_TCPWINPROBE = 109,
	LINUX_MIB_TCPKEEPALIVE = 110,
	LINUX_MIB_TCPMTUPFAIL = 111,
	LINUX_MIB_TCPMTUPSUCCESS = 112,
	LINUX_MIB_TCPDELIVERED = 113,
	LINUX_MIB_TCPDELIVEREDCE = 114,
	LINUX_MIB_TCPACKCOMPRESSED = 115,
	LINUX_MIB_TCPZEROWINDOWDROP = 116,
	LINUX_MIB_TCPRCVQDROP = 117,
	LINUX_MIB_TCPWQUEUETOOBIG = 118,
	LINUX_MIB_TCPFASTOPENPASSIVEALTKEY = 119,
	LINUX_MIB_TCPTIMEOUTREHASH = 120,
	LINUX_MIB_TCPDUPLICATEDATAREHASH = 121,
	LINUX_MIB_TCPDSACKRECVSEGS = 122,
	LINUX_MIB_TCPDSACKIGNOREDDUBIOUS = 123,
	LINUX_MIB_TCPMIGRATEREQSUCCESS = 124,
	LINUX_MIB_TCPMIGRATEREQFAILURE = 125,
	__LINUX_MIB_MAX = 126,
};

enum {
	LINUX_MIB_XFRMNUM = 0,
	LINUX_MIB_XFRMINERROR = 1,
	LINUX_MIB_XFRMINBUFFERERROR = 2,
	LINUX_MIB_XFRMINHDRERROR = 3,
	LINUX_MIB_XFRMINNOSTATES = 4,
	LINUX_MIB_XFRMINSTATEPROTOERROR = 5,
	LINUX_MIB_XFRMINSTATEMODEERROR = 6,
	LINUX_MIB_XFRMINSTATESEQERROR = 7,
	LINUX_MIB_XFRMINSTATEEXPIRED = 8,
	LINUX_MIB_XFRMINSTATEMISMATCH = 9,
	LINUX_MIB_XFRMINSTATEINVALID = 10,
	LINUX_MIB_XFRMINTMPLMISMATCH = 11,
	LINUX_MIB_XFRMINNOPOLS = 12,
	LINUX_MIB_XFRMINPOLBLOCK = 13,
	LINUX_MIB_XFRMINPOLERROR = 14,
	LINUX_MIB_XFRMOUTERROR = 15,
	LINUX_MIB_XFRMOUTBUNDLEGENERROR = 16,
	LINUX_MIB_XFRMOUTBUNDLECHECKERROR = 17,
	LINUX_MIB_XFRMOUTNOSTATES = 18,
	LINUX_MIB_XFRMOUTSTATEPROTOERROR = 19,
	LINUX_MIB_XFRMOUTSTATEMODEERROR = 20,
	LINUX_MIB_XFRMOUTSTATESEQERROR = 21,
	LINUX_MIB_XFRMOUTSTATEEXPIRED = 22,
	LINUX_MIB_XFRMOUTPOLBLOCK = 23,
	LINUX_MIB_XFRMOUTPOLDEAD = 24,
	LINUX_MIB_XFRMOUTPOLERROR = 25,
	LINUX_MIB_XFRMFWDHDRERROR = 26,
	LINUX_MIB_XFRMOUTSTATEINVALID = 27,
	LINUX_MIB_XFRMACQUIREERROR = 28,
	__LINUX_MIB_XFRMMAX = 29,
};

enum {
	LINUX_MIB_TLSNUM = 0,
	LINUX_MIB_TLSCURRTXSW = 1,
	LINUX_MIB_TLSCURRRXSW = 2,
	LINUX_MIB_TLSCURRTXDEVICE = 3,
	LINUX_MIB_TLSCURRRXDEVICE = 4,
	LINUX_MIB_TLSTXSW = 5,
	LINUX_MIB_TLSRXSW = 6,
	LINUX_MIB_TLSTXDEVICE = 7,
	LINUX_MIB_TLSRXDEVICE = 8,
	LINUX_MIB_TLSDECRYPTERROR = 9,
	LINUX_MIB_TLSRXDEVICERESYNC = 10,
	__LINUX_MIB_TLSMAX = 11,
};

struct ipstats_mib {
	u64 mibs[37];
	struct u64_stats_sync syncp;
};

struct icmp_mib {
	long unsigned int mibs[28];
};

struct icmpmsg_mib {
	atomic_long_t mibs[512];
};

struct icmpv6_mib {
	long unsigned int mibs[6];
};

struct icmpv6msg_mib {
	atomic_long_t mibs[512];
};

struct tcp_mib {
	long unsigned int mibs[16];
};

struct udp_mib {
	long unsigned int mibs[10];
};

struct linux_mib {
	long unsigned int mibs[126];
};

struct linux_xfrm_mib {
	long unsigned int mibs[29];
};

struct linux_tls_mib {
	long unsigned int mibs[11];
};

struct inet_frags;

struct fqdir {
	long int high_thresh;
	long int low_thresh;
	int timeout;
	int max_dist;
	struct inet_frags *f;
	struct net *net;
	bool dead;
	long: 56;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct rhashtable rhashtable;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	atomic_long_t mem;
	struct work_struct destroy_work;
	struct llist_node free_list;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct inet_frag_queue;

struct inet_frags {
	unsigned int qsize;
	void (*constructor)(struct inet_frag_queue *, const void *);
	void (*destructor)(struct inet_frag_queue *);
	void (*frag_expire)(struct timer_list *);
	struct kmem_cache *frags_cachep;
	const char *frags_cache_name;
	struct rhashtable_params rhash_params;
	refcount_t refcnt;
	struct completion completion;
};

struct frag_v4_compare_key {
	__be32 saddr;
	__be32 daddr;
	u32 user;
	u32 vif;
	__be16 id;
	u16 protocol;
};

struct frag_v6_compare_key {
	struct in6_addr saddr;
	struct in6_addr daddr;
	u32 user;
	__be32 id;
	u32 iif;
};

struct inet_frag_queue {
	struct rhash_head node;
	union {
		struct frag_v4_compare_key v4;
		struct frag_v6_compare_key v6;
	} key;
	struct timer_list timer;
	spinlock_t lock;
	refcount_t refcnt;
	struct rb_root rb_fragments;
	struct sk_buff *fragments_tail;
	struct sk_buff *last_run_head;
	ktime_t stamp;
	int len;
	int meat;
	__u8 flags;
	u16 max_size;
	struct fqdir *fqdir;
	struct callback_head rcu;
};

enum tcp_ca_event {
	CA_EVENT_TX_START = 0,
	CA_EVENT_CWND_RESTART = 1,
	CA_EVENT_COMPLETE_CWR = 2,
	CA_EVENT_LOSS = 3,
	CA_EVENT_ECN_NO_CE = 4,
	CA_EVENT_ECN_IS_CE = 5,
};

struct ack_sample;

struct rate_sample;

union tcp_cc_info;

struct tcp_congestion_ops {
	u32 (*ssthresh)(struct sock *);
	void (*cong_avoid)(struct sock *, u32, u32);
	void (*set_state)(struct sock *, u8);
	void (*cwnd_event)(struct sock *, enum tcp_ca_event);
	void (*in_ack_event)(struct sock *, u32);
	void (*pkts_acked)(struct sock *, const struct ack_sample *);
	u32 (*min_tso_segs)(struct sock *);
	void (*cong_control)(struct sock *, const struct rate_sample *);
	u32 (*undo_cwnd)(struct sock *);
	u32 (*sndbuf_expand)(struct sock *);
	size_t (*get_info)(struct sock *, u32, int *, union tcp_cc_info *);
	char name[16];
	struct module *owner;
	struct list_head list;
	u32 key;
	u32 flags;
	void (*init)(struct sock *);
	void (*release)(struct sock *);
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

typedef struct {} netdevice_tracker;

struct xfrm_state;

struct lwtunnel_state;

struct dst_entry {
	struct net_device *dev;
	struct dst_ops *ops;
	long unsigned int _metrics;
	long unsigned int expires;
	struct xfrm_state *xfrm;
	int (*input)(struct sk_buff *);
	int (*output)(struct net *, struct sock *, struct sk_buff *);
	short unsigned int flags;
	short int obsolete;
	short unsigned int header_len;
	short unsigned int trailer_len;
	atomic_t __refcnt;
	int __use;
	long unsigned int lastuse;
	struct lwtunnel_state *lwtstate;
	struct callback_head callback_head;
	short int error;
	short int __pad;
	__u32 tclassid;
	netdevice_tracker dev_tracker;
};

enum nf_inet_hooks {
	NF_INET_PRE_ROUTING = 0,
	NF_INET_LOCAL_IN = 1,
	NF_INET_FORWARD = 2,
	NF_INET_LOCAL_OUT = 3,
	NF_INET_POST_ROUTING = 4,
	NF_INET_NUMHOOKS = 5,
	NF_INET_INGRESS = 5,
};

enum {
	NFPROTO_UNSPEC = 0,
	NFPROTO_INET = 1,
	NFPROTO_IPV4 = 2,
	NFPROTO_ARP = 3,
	NFPROTO_NETDEV = 5,
	NFPROTO_BRIDGE = 7,
	NFPROTO_IPV6 = 10,
	NFPROTO_DECNET = 12,
	NFPROTO_NUMPROTO = 13,
};

struct nf_queue_entry;

struct nf_queue_handler {
	int (*outfn)(struct nf_queue_entry *, unsigned int);
	void (*nf_hook_drop)(struct net *);
};

enum nf_log_type {
	NF_LOG_TYPE_LOG = 0,
	NF_LOG_TYPE_ULOG = 1,
	NF_LOG_TYPE_MAX = 2,
};

typedef u8 u_int8_t;

struct nf_loginfo;

typedef void nf_logfn(struct net *, u_int8_t, unsigned int, const struct sk_buff *, const struct net_device *, const struct net_device *, const struct nf_loginfo *, const char *);

struct nf_logger {
	char *name;
	enum nf_log_type type;
	nf_logfn *logfn;
	struct module *me;
};

enum tcp_conntrack {
	TCP_CONNTRACK_NONE = 0,
	TCP_CONNTRACK_SYN_SENT = 1,
	TCP_CONNTRACK_SYN_RECV = 2,
	TCP_CONNTRACK_ESTABLISHED = 3,
	TCP_CONNTRACK_FIN_WAIT = 4,
	TCP_CONNTRACK_CLOSE_WAIT = 5,
	TCP_CONNTRACK_LAST_ACK = 6,
	TCP_CONNTRACK_TIME_WAIT = 7,
	TCP_CONNTRACK_CLOSE = 8,
	TCP_CONNTRACK_LISTEN = 9,
	TCP_CONNTRACK_MAX = 10,
	TCP_CONNTRACK_IGNORE = 11,
	TCP_CONNTRACK_RETRANS = 12,
	TCP_CONNTRACK_UNACK = 13,
	TCP_CONNTRACK_TIMEOUT_MAX = 14,
};

enum ct_dccp_states {
	CT_DCCP_NONE = 0,
	CT_DCCP_REQUEST = 1,
	CT_DCCP_RESPOND = 2,
	CT_DCCP_PARTOPEN = 3,
	CT_DCCP_OPEN = 4,
	CT_DCCP_CLOSEREQ = 5,
	CT_DCCP_CLOSING = 6,
	CT_DCCP_TIMEWAIT = 7,
	CT_DCCP_IGNORE = 8,
	CT_DCCP_INVALID = 9,
	__CT_DCCP_MAX = 10,
};

struct ip_conntrack_stat {
	unsigned int found;
	unsigned int invalid;
	unsigned int insert;
	unsigned int insert_failed;
	unsigned int clash_resolve;
	unsigned int drop;
	unsigned int early_drop;
	unsigned int error;
	unsigned int expect_new;
	unsigned int expect_create;
	unsigned int expect_delete;
	unsigned int search_restart;
	unsigned int chaintoolong;
};

enum ip_conntrack_dir {
	IP_CT_DIR_ORIGINAL = 0,
	IP_CT_DIR_REPLY = 1,
	IP_CT_DIR_MAX = 2,
};

enum sctp_conntrack {
	SCTP_CONNTRACK_NONE = 0,
	SCTP_CONNTRACK_CLOSED = 1,
	SCTP_CONNTRACK_COOKIE_WAIT = 2,
	SCTP_CONNTRACK_COOKIE_ECHOED = 3,
	SCTP_CONNTRACK_ESTABLISHED = 4,
	SCTP_CONNTRACK_SHUTDOWN_SENT = 5,
	SCTP_CONNTRACK_SHUTDOWN_RECD = 6,
	SCTP_CONNTRACK_SHUTDOWN_ACK_SENT = 7,
	SCTP_CONNTRACK_HEARTBEAT_SENT = 8,
	SCTP_CONNTRACK_HEARTBEAT_ACKED = 9,
	SCTP_CONNTRACK_MAX = 10,
};

enum udp_conntrack {
	UDP_CT_UNREPLIED = 0,
	UDP_CT_REPLIED = 1,
	UDP_CT_MAX = 2,
};

enum gre_conntrack {
	GRE_CT_UNREPLIED = 0,
	GRE_CT_REPLIED = 1,
	GRE_CT_MAX = 2,
};

enum {
	XFRM_POLICY_IN = 0,
	XFRM_POLICY_OUT = 1,
	XFRM_POLICY_FWD = 2,
	XFRM_POLICY_MASK = 3,
	XFRM_POLICY_MAX = 3,
};

enum netns_bpf_attach_type {
	NETNS_BPF_INVALID = 4294967295,
	NETNS_BPF_FLOW_DISSECTOR = 0,
	NETNS_BPF_SK_LOOKUP = 1,
	MAX_NETNS_BPF_ATTACH_TYPE = 2,
};

struct pipe_buf_operations;

struct pipe_buffer {
	struct page *page;
	unsigned int offset;
	unsigned int len;
	const struct pipe_buf_operations *ops;
	unsigned int flags;
	long unsigned int private;
};

struct pipe_buf_operations {
	int (*confirm)(struct pipe_inode_info *, struct pipe_buffer *);
	void (*release)(struct pipe_inode_info *, struct pipe_buffer *);
	bool (*try_steal)(struct pipe_inode_info *, struct pipe_buffer *);
	bool (*get)(struct pipe_inode_info *, struct pipe_buffer *);
};

struct skb_ext {
	refcount_t refcnt;
	u8 offset[4];
	u8 chunks;
	long: 56;
	char data[0];
};

enum skb_ext_id {
	SKB_EXT_BRIDGE_NF = 0,
	SKB_EXT_SEC_PATH = 1,
	TC_SKB_EXT = 2,
	SKB_EXT_MPTCP = 3,
	SKB_EXT_NUM = 4,
};

struct trace_event_raw_initcall_level {
	struct trace_entry ent;
	u32 __data_loc_level;
	char __data[0];
};

struct trace_event_raw_initcall_start {
	struct trace_entry ent;
	initcall_t func;
	char __data[0];
};

struct trace_event_raw_initcall_finish {
	struct trace_entry ent;
	initcall_t func;
	int ret;
	char __data[0];
};

struct trace_event_data_offsets_initcall_level {
	u32 level;
};

struct trace_event_data_offsets_initcall_start {};

struct trace_event_data_offsets_initcall_finish {};

typedef void (*btf_trace_initcall_level)(void *, const char *);

typedef void (*btf_trace_initcall_start)(void *, initcall_t);

typedef void (*btf_trace_initcall_finish)(void *, initcall_t, int);

struct blacklist_entry {
	struct list_head next;
	char *buf;
};

typedef __u32 Elf32_Word;

struct elf32_note {
	Elf32_Word n_namesz;
	Elf32_Word n_descsz;
	Elf32_Word n_type;
};

enum {
	PROC_ROOT_INO = 1,
	PROC_IPC_INIT_INO = 4026531839,
	PROC_UTS_INIT_INO = 4026531838,
	PROC_USER_INIT_INO = 4026531837,
	PROC_PID_INIT_INO = 4026531836,
	PROC_CGROUP_INIT_INO = 4026531835,
	PROC_TIME_INIT_INO = 4026531834,
};

typedef __u16 __le16;

typedef unsigned int slab_flags_t;

struct fs_struct {
	int users;
	spinlock_t lock;
	seqcount_spinlock_t seq;
	int umask;
	int in_exec;
	struct path root;
	struct path pwd;
};

typedef __u64 __addrpair;

typedef __u32 __portpair;

typedef struct {
	struct net *net;
} possible_net_t;

struct hlist_nulls_node {
	struct hlist_nulls_node *next;
	struct hlist_nulls_node **pprev;
};

struct proto;

struct sock_common {
	union {
		__addrpair skc_addrpair;
		struct {
			__be32 skc_daddr;
			__be32 skc_rcv_saddr;
		};
	};
	union {
		unsigned int skc_hash;
		__u16 skc_u16hashes[2];
	};
	union {
		__portpair skc_portpair;
		struct {
			__be16 skc_dport;
			__u16 skc_num;
		};
	};
	short unsigned int skc_family;
	volatile unsigned char skc_state;
	unsigned char skc_reuse: 4;
	unsigned char skc_reuseport: 1;
	unsigned char skc_ipv6only: 1;
	unsigned char skc_net_refcnt: 1;
	int skc_bound_dev_if;
	union {
		struct hlist_node skc_bind_node;
		struct hlist_node skc_portaddr_node;
	};
	struct proto *skc_prot;
	possible_net_t skc_net;
	struct in6_addr skc_v6_daddr;
	struct in6_addr skc_v6_rcv_saddr;
	atomic64_t skc_cookie;
	union {
		long unsigned int skc_flags;
		struct sock *skc_listener;
		struct inet_timewait_death_row *skc_tw_dr;
	};
	int skc_dontcopy_begin[0];
	union {
		struct hlist_node skc_node;
		struct hlist_nulls_node skc_nulls_node;
	};
	short unsigned int skc_tx_queue_mapping;
	short unsigned int skc_rx_queue_mapping;
	union {
		int skc_incoming_cpu;
		u32 skc_rcv_wnd;
		u32 skc_tw_rcv_nxt;
	};
	refcount_t skc_refcnt;
	int skc_dontcopy_end[0];
	union {
		u32 skc_rxhash;
		u32 skc_window_clamp;
		u32 skc_tw_snd_nxt;
	};
};

typedef struct {
	spinlock_t slock;
	int owned;
	wait_queue_head_t wq;
} socket_lock_t;

struct sk_buff_head {
	struct sk_buff *next;
	struct sk_buff *prev;
	__u32 qlen;
	spinlock_t lock;
};

typedef u64 netdev_features_t;

struct sock_cgroup_data {
	struct cgroup *cgroup;
	u32 classid;
	u16 prioidx;
};

typedef struct {} netns_tracker;

struct sk_filter;

struct socket_wq;

struct xfrm_policy;

struct socket;

struct sock_reuseport;

struct sock {
	struct sock_common __sk_common;
	struct dst_entry *sk_rx_dst;
	int sk_rx_dst_ifindex;
	u32 sk_rx_dst_cookie;
	socket_lock_t sk_lock;
	atomic_t sk_drops;
	int sk_rcvlowat;
	struct sk_buff_head sk_error_queue;
	struct sk_buff_head sk_receive_queue;
	struct {
		atomic_t rmem_alloc;
		int len;
		struct sk_buff *head;
		struct sk_buff *tail;
	} sk_backlog;
	struct llist_head defer_list;
	int sk_forward_alloc;
	u32 sk_reserved_mem;
	unsigned int sk_ll_usec;
	unsigned int sk_napi_id;
	int sk_rcvbuf;
	struct sk_filter *sk_filter;
	union {
		struct socket_wq *sk_wq;
		struct socket_wq *sk_wq_raw;
	};
	struct xfrm_policy *sk_policy[2];
	struct dst_entry *sk_dst_cache;
	atomic_t sk_omem_alloc;
	int sk_sndbuf;
	int sk_wmem_queued;
	refcount_t sk_wmem_alloc;
	long unsigned int sk_tsq_flags;
	union {
		struct sk_buff *sk_send_head;
		struct rb_root tcp_rtx_queue;
	};
	struct sk_buff_head sk_write_queue;
	__s32 sk_peek_off;
	int sk_write_pending;
	__u32 sk_dst_pending_confirm;
	u32 sk_pacing_status;
	long int sk_sndtimeo;
	struct timer_list sk_timer;
	__u32 sk_priority;
	__u32 sk_mark;
	long unsigned int sk_pacing_rate;
	long unsigned int sk_max_pacing_rate;
	struct page_frag sk_frag;
	netdev_features_t sk_route_caps;
	int sk_gso_type;
	unsigned int sk_gso_max_size;
	gfp_t sk_allocation;
	__u32 sk_txhash;
	u8 sk_gso_disabled: 1;
	u8 sk_kern_sock: 1;
	u8 sk_no_check_tx: 1;
	u8 sk_no_check_rx: 1;
	u8 sk_userlocks: 4;
	u8 sk_pacing_shift;
	u16 sk_type;
	u16 sk_protocol;
	u16 sk_gso_max_segs;
	long unsigned int sk_lingertime;
	struct proto *sk_prot_creator;
	rwlock_t sk_callback_lock;
	int sk_err;
	int sk_err_soft;
	u32 sk_ack_backlog;
	u32 sk_max_ack_backlog;
	kuid_t sk_uid;
	u8 sk_prefer_busy_poll;
	u16 sk_busy_poll_budget;
	spinlock_t sk_peer_lock;
	int sk_bind_phc;
	struct pid *sk_peer_pid;
	const struct cred *sk_peer_cred;
	long int sk_rcvtimeo;
	ktime_t sk_stamp;
	u16 sk_tsflags;
	u8 sk_shutdown;
	atomic_t sk_tskey;
	atomic_t sk_zckey;
	u8 sk_clockid;
	u8 sk_txtime_deadline_mode: 1;
	u8 sk_txtime_report_errors: 1;
	u8 sk_txtime_unused: 6;
	struct socket *sk_socket;
	void *sk_user_data;
	void *sk_security;
	struct sock_cgroup_data sk_cgrp_data;
	struct mem_cgroup *sk_memcg;
	void (*sk_state_change)(struct sock *);
	void (*sk_data_ready)(struct sock *);
	void (*sk_write_space)(struct sock *);
	void (*sk_error_report)(struct sock *);
	int (*sk_backlog_rcv)(struct sock *, struct sk_buff *);
	struct sk_buff * (*sk_validate_xmit_skb)(struct sock *, struct net_device *, struct sk_buff *);
	void (*sk_destruct)(struct sock *);
	struct sock_reuseport *sk_reuseport_cb;
	struct bpf_local_storage *sk_bpf_storage;
	struct callback_head sk_rcu;
	netns_tracker ns_tracker;
};

struct ld_semaphore {
	atomic_long_t count;
	raw_spinlock_t wait_lock;
	unsigned int wait_readers;
	struct list_head read_wait;
	struct list_head write_wait;
};

typedef unsigned int tcflag_t;

typedef unsigned char cc_t;

typedef unsigned int speed_t;

struct ktermios {
	tcflag_t c_iflag;
	tcflag_t c_oflag;
	tcflag_t c_cflag;
	tcflag_t c_lflag;
	cc_t c_cc[19];
	cc_t c_line;
	speed_t c_ispeed;
	speed_t c_ospeed;
};

struct winsize {
	short unsigned int ws_row;
	short unsigned int ws_col;
	short unsigned int ws_xpixel;
	short unsigned int ws_ypixel;
};

struct tty_driver;

struct tty_operations;

struct tty_ldisc;

struct tty_port;

struct tty_struct {
	int magic;
	struct kref kref;
	struct device *dev;
	struct tty_driver *driver;
	const struct tty_operations *ops;
	int index;
	struct ld_semaphore ldisc_sem;
	struct tty_ldisc *ldisc;
	struct mutex atomic_write_lock;
	struct mutex legacy_mutex;
	struct mutex throttle_mutex;
	struct rw_semaphore termios_rwsem;
	struct mutex winsize_mutex;
	struct ktermios termios;
	struct ktermios termios_locked;
	char name[64];
	long unsigned int flags;
	int count;
	struct winsize winsize;
	struct {
		spinlock_t lock;
		bool stopped;
		bool tco_stopped;
		long unsigned int unused[0];
	} flow;
	struct {
		spinlock_t lock;
		struct pid *pgrp;
		struct pid *session;
		unsigned char pktstatus;
		bool packet;
		long unsigned int unused[0];
	} ctrl;
	int hw_stopped;
	unsigned int receive_room;
	int flow_change;
	struct tty_struct *link;
	struct fasync_struct *fasync;
	wait_queue_head_t write_wait;
	wait_queue_head_t read_wait;
	struct work_struct hangup_work;
	void *disc_data;
	void *driver_data;
	spinlock_t files_lock;
	struct list_head tty_files;
	int closing;
	unsigned char *write_buf;
	int write_cnt;
	struct work_struct SAK_work;
	struct tty_port *port;
};

typedef struct {
	size_t written;
	size_t count;
	union {
		char *buf;
		void *data;
	} arg;
	int error;
} read_descriptor_t;

struct posix_acl_entry {
	short int e_tag;
	short unsigned int e_perm;
	union {
		kuid_t e_uid;
		kgid_t e_gid;
	};
};

struct posix_acl {
	refcount_t a_refcount;
	struct callback_head a_rcu;
	unsigned int a_count;
	struct posix_acl_entry a_entries[0];
};

struct serial_icounter_struct;

struct serial_struct;

struct tty_operations {
	struct tty_struct * (*lookup)(struct tty_driver *, struct file *, int);
	int (*install)(struct tty_driver *, struct tty_struct *);
	void (*remove)(struct tty_driver *, struct tty_struct *);
	int (*open)(struct tty_struct *, struct file *);
	void (*close)(struct tty_struct *, struct file *);
	void (*shutdown)(struct tty_struct *);
	void (*cleanup)(struct tty_struct *);
	int (*write)(struct tty_struct *, const unsigned char *, int);
	int (*put_char)(struct tty_struct *, unsigned char);
	void (*flush_chars)(struct tty_struct *);
	unsigned int (*write_room)(struct tty_struct *);
	unsigned int (*chars_in_buffer)(struct tty_struct *);
	int (*ioctl)(struct tty_struct *, unsigned int, long unsigned int);
	long int (*compat_ioctl)(struct tty_struct *, unsigned int, long unsigned int);
	void (*set_termios)(struct tty_struct *, struct ktermios *);
	void (*throttle)(struct tty_struct *);
	void (*unthrottle)(struct tty_struct *);
	void (*stop)(struct tty_struct *);
	void (*start)(struct tty_struct *);
	void (*hangup)(struct tty_struct *);
	int (*break_ctl)(struct tty_struct *, int);
	void (*flush_buffer)(struct tty_struct *);
	void (*set_ldisc)(struct tty_struct *);
	void (*wait_until_sent)(struct tty_struct *, int);
	void (*send_xchar)(struct tty_struct *, char);
	int (*tiocmget)(struct tty_struct *);
	int (*tiocmset)(struct tty_struct *, unsigned int, unsigned int);
	int (*resize)(struct tty_struct *, struct winsize *);
	int (*get_icount)(struct tty_struct *, struct serial_icounter_struct *);
	int (*get_serial)(struct tty_struct *, struct serial_struct *);
	int (*set_serial)(struct tty_struct *, struct serial_struct *);
	void (*show_fdinfo)(struct tty_struct *, struct seq_file *);
	int (*poll_init)(struct tty_driver *, int, char *);
	int (*poll_get_char)(struct tty_driver *, int);
	void (*poll_put_char)(struct tty_driver *, int, char);
	int (*proc_show)(struct seq_file *, void *);
};

struct tty_driver {
	int magic;
	struct kref kref;
	struct cdev **cdevs;
	struct module *owner;
	const char *driver_name;
	const char *name;
	int name_base;
	int major;
	int minor_start;
	unsigned int num;
	short int type;
	short int subtype;
	struct ktermios init_termios;
	long unsigned int flags;
	struct proc_dir_entry *proc_entry;
	struct tty_driver *other;
	struct tty_struct **ttys;
	struct tty_port **ports;
	struct ktermios **termios;
	void *driver_state;
	const struct tty_operations *ops;
	struct list_head tty_drivers;
};

struct tty_buffer {
	union {
		struct tty_buffer *next;
		struct llist_node free;
	};
	int used;
	int size;
	int commit;
	int read;
	int flags;
	long unsigned int data[0];
};

struct tty_bufhead {
	struct tty_buffer *head;
	struct work_struct work;
	struct mutex lock;
	atomic_t priority;
	struct tty_buffer sentinel;
	struct llist_head free;
	atomic_t mem_used;
	int mem_limit;
	struct tty_buffer *tail;
};

struct tty_port_operations;

struct tty_port_client_operations;

struct tty_port {
	struct tty_bufhead buf;
	struct tty_struct *tty;
	struct tty_struct *itty;
	const struct tty_port_operations *ops;
	const struct tty_port_client_operations *client_ops;
	spinlock_t lock;
	int blocked_open;
	int count;
	wait_queue_head_t open_wait;
	wait_queue_head_t delta_msr_wait;
	long unsigned int flags;
	long unsigned int iflags;
	unsigned char console: 1;
	struct mutex mutex;
	struct mutex buf_mutex;
	unsigned char *xmit_buf;
	unsigned int close_delay;
	unsigned int closing_wait;
	int drain_delay;
	struct kref kref;
	void *client_data;
};

struct tty_ldisc_ops {
	char *name;
	int num;
	int flags;
	int (*open)(struct tty_struct *);
	void (*close)(struct tty_struct *);
	void (*flush_buffer)(struct tty_struct *);
	ssize_t (*read)(struct tty_struct *, struct file *, unsigned char *, size_t, void **, long unsigned int);
	ssize_t (*write)(struct tty_struct *, struct file *, const unsigned char *, size_t);
	int (*ioctl)(struct tty_struct *, unsigned int, long unsigned int);
	int (*compat_ioctl)(struct tty_struct *, unsigned int, long unsigned int);
	void (*set_termios)(struct tty_struct *, struct ktermios *);
	__poll_t (*poll)(struct tty_struct *, struct file *, struct poll_table_struct *);
	int (*hangup)(struct tty_struct *);
	void (*receive_buf)(struct tty_struct *, const unsigned char *, const char *, int);
	void (*write_wakeup)(struct tty_struct *);
	void (*dcd_change)(struct tty_struct *, unsigned int);
	int (*receive_buf2)(struct tty_struct *, const unsigned char *, const char *, int);
	struct module *owner;
};

struct tty_ldisc {
	struct tty_ldisc_ops *ops;
	struct tty_struct *tty;
};

struct tty_port_operations {
	int (*carrier_raised)(struct tty_port *);
	void (*dtr_rts)(struct tty_port *, int);
	void (*shutdown)(struct tty_port *);
	int (*activate)(struct tty_port *, struct tty_struct *);
	void (*destruct)(struct tty_port *);
};

struct tty_port_client_operations {
	int (*receive_buf)(struct tty_port *, const unsigned char *, const unsigned char *, size_t);
	void (*write_wakeup)(struct tty_port *);
};

typedef struct {
	local64_t v;
} u64_stats_t;

enum {
	Root_NFS = 255,
	Root_CIFS = 254,
	Root_RAM0 = 1048576,
	Root_RAM1 = 1048577,
	Root_FD0 = 2097152,
	Root_HDA1 = 3145729,
	Root_HDA2 = 3145730,
	Root_SDA1 = 8388609,
	Root_SDA2 = 8388610,
	Root_HDC1 = 23068673,
	Root_SR0 = 11534336,
};

typedef short unsigned int __kernel_sa_family_t;

typedef __kernel_sa_family_t sa_family_t;

struct sockaddr {
	sa_family_t sa_family;
	char sa_data[14];
};

struct msghdr {
	void *msg_name;
	int msg_namelen;
	struct iov_iter msg_iter;
	union {
		void *msg_control;
		void *msg_control_user;
	};
	bool msg_control_is_user: 1;
	__kernel_size_t msg_controllen;
	unsigned int msg_flags;
	struct kiocb *msg_iocb;
};

enum {
	IPPROTO_IP = 0,
	IPPROTO_ICMP = 1,
	IPPROTO_IGMP = 2,
	IPPROTO_IPIP = 4,
	IPPROTO_TCP = 6,
	IPPROTO_EGP = 8,
	IPPROTO_PUP = 12,
	IPPROTO_UDP = 17,
	IPPROTO_IDP = 22,
	IPPROTO_TP = 29,
	IPPROTO_DCCP = 33,
	IPPROTO_IPV6 = 41,
	IPPROTO_RSVP = 46,
	IPPROTO_GRE = 47,
	IPPROTO_ESP = 50,
	IPPROTO_AH = 51,
	IPPROTO_MTP = 92,
	IPPROTO_BEETPH = 94,
	IPPROTO_ENCAP = 98,
	IPPROTO_PIM = 103,
	IPPROTO_COMP = 108,
	IPPROTO_SCTP = 132,
	IPPROTO_UDPLITE = 136,
	IPPROTO_MPLS = 137,
	IPPROTO_ETHERNET = 143,
	IPPROTO_RAW = 255,
	IPPROTO_MPTCP = 262,
	IPPROTO_MAX = 263,
};

struct flowi_tunnel {
	__be64 tun_id;
};

struct flowi_common {
	int flowic_oif;
	int flowic_iif;
	int flowic_l3mdev;
	__u32 flowic_mark;
	__u8 flowic_tos;
	__u8 flowic_scope;
	__u8 flowic_proto;
	__u8 flowic_flags;
	__u32 flowic_secid;
	kuid_t flowic_uid;
	struct flowi_tunnel flowic_tun_key;
	__u32 flowic_multipath_hash;
};

union flowi_uli {
	struct {
		__be16 dport;
		__be16 sport;
	} ports;
	struct {
		__u8 type;
		__u8 code;
	} icmpt;
	struct {
		__le16 dport;
		__le16 sport;
	} dnports;
	__be32 gre_key;
	struct {
		__u8 type;
	} mht;
};

struct flowi4 {
	struct flowi_common __fl_common;
	__be32 saddr;
	__be32 daddr;
	union flowi_uli uli;
};

struct flowi6 {
	struct flowi_common __fl_common;
	struct in6_addr daddr;
	struct in6_addr saddr;
	__be32 flowlabel;
	union flowi_uli uli;
	__u32 mp_hash;
};

struct flowidn {
	struct flowi_common __fl_common;
	__le16 daddr;
	__le16 saddr;
	union flowi_uli uli;
};

struct flowi {
	union {
		struct flowi_common __fl_common;
		struct flowi4 ip4;
		struct flowi6 ip6;
		struct flowidn dn;
	} u;
};

struct prot_inuse {
	int all;
	int val[64];
};

struct icmpv6_mib_device {
	atomic_long_t mibs[6];
};

struct icmpv6msg_mib_device {
	atomic_long_t mibs[512];
};

struct fib_rule;

struct fib_lookup_arg;

struct fib_rule_hdr;

struct nlattr;

struct netlink_ext_ack;

struct nla_policy;

struct fib_rules_ops {
	int family;
	struct list_head list;
	int rule_size;
	int addr_size;
	int unresolved_rules;
	int nr_goto_rules;
	unsigned int fib_rules_seq;
	int (*action)(struct fib_rule *, struct flowi *, int, struct fib_lookup_arg *);
	bool (*suppress)(struct fib_rule *, int, struct fib_lookup_arg *);
	int (*match)(struct fib_rule *, struct flowi *, int);
	int (*configure)(struct fib_rule *, struct sk_buff *, struct fib_rule_hdr *, struct nlattr **, struct netlink_ext_ack *);
	int (*delete)(struct fib_rule *);
	int (*compare)(struct fib_rule *, struct fib_rule_hdr *, struct nlattr **);
	int (*fill)(struct fib_rule *, struct sk_buff *, struct fib_rule_hdr *);
	size_t (*nlmsg_payload)(struct fib_rule *);
	void (*flush_cache)(struct fib_rules_ops *);
	int nlgroup;
	const struct nla_policy *policy;
	struct list_head rules_list;
	struct module *owner;
	struct net *fro_net;
	struct callback_head rcu;
};

struct fib_notifier_ops {
	int family;
	struct list_head list;
	unsigned int (*fib_seq_read)(struct net *);
	int (*fib_dump)(struct net *, struct notifier_block *, struct netlink_ext_ack *);
	struct module *owner;
	struct callback_head rcu;
};

struct net_device_stats {
	long unsigned int rx_packets;
	long unsigned int tx_packets;
	long unsigned int rx_bytes;
	long unsigned int tx_bytes;
	long unsigned int rx_errors;
	long unsigned int tx_errors;
	long unsigned int rx_dropped;
	long unsigned int tx_dropped;
	long unsigned int multicast;
	long unsigned int collisions;
	long unsigned int rx_length_errors;
	long unsigned int rx_over_errors;
	long unsigned int rx_crc_errors;
	long unsigned int rx_frame_errors;
	long unsigned int rx_fifo_errors;
	long unsigned int rx_missed_errors;
	long unsigned int tx_aborted_errors;
	long unsigned int tx_carrier_errors;
	long unsigned int tx_fifo_errors;
	long unsigned int tx_heartbeat_errors;
	long unsigned int tx_window_errors;
	long unsigned int rx_compressed;
	long unsigned int tx_compressed;
};

struct netdev_hw_addr_list {
	struct list_head list;
	int count;
};

struct tipc_bearer;

struct wireless_dev;

struct mpls_dev;

enum rx_handler_result {
	RX_HANDLER_CONSUMED = 0,
	RX_HANDLER_ANOTHER = 1,
	RX_HANDLER_EXACT = 2,
	RX_HANDLER_PASS = 3,
};

typedef enum rx_handler_result rx_handler_result_t;

typedef rx_handler_result_t rx_handler_func_t(struct sk_buff **);

enum netdev_ml_priv_type {
	ML_PRIV_NONE = 0,
	ML_PRIV_CAN = 1,
};

struct pcpu_dstats;

struct garp_port;

struct mrp_port;

struct netdev_tc_txq {
	u16 count;
	u16 offset;
};

struct sfp_bus;

struct macsec_ops;

struct udp_tunnel_nic;

struct bpf_xdp_link;

struct bpf_xdp_entity {
	struct bpf_prog *prog;
	struct bpf_xdp_link *link;
};

struct netdev_name_node;

struct dev_ifalias;

struct net_device_ops;

struct ethtool_ops;

struct l3mdev_ops;

struct ndisc_ops;

struct xfrmdev_ops;

struct tlsdev_ops;

struct header_ops;

struct vlan_info;

struct in_device;

struct inet6_dev;

struct wpan_dev;

struct netdev_rx_queue;

struct mini_Qdisc;

struct netdev_queue;

struct cpu_rmap;

struct Qdisc;

struct xdp_dev_bulk_queue;

struct xps_dev_maps;

struct netpoll_info;

struct pcpu_lstats;

struct pcpu_sw_netstats;

struct rtnl_link_ops;

struct dcbnl_rtnl_ops;

struct netprio_map;

struct phy_device;

struct udp_tunnel_nic_info;

struct rtnl_hw_stats64;

struct net_device {
	char name[16];
	struct netdev_name_node *name_node;
	struct dev_ifalias *ifalias;
	long unsigned int mem_end;
	long unsigned int mem_start;
	long unsigned int base_addr;
	long unsigned int state;
	struct list_head dev_list;
	struct list_head napi_list;
	struct list_head unreg_list;
	struct list_head close_list;
	struct list_head ptype_all;
	struct list_head ptype_specific;
	struct {
		struct list_head upper;
		struct list_head lower;
	} adj_list;
	unsigned int flags;
	long long unsigned int priv_flags;
	const struct net_device_ops *netdev_ops;
	int ifindex;
	short unsigned int gflags;
	short unsigned int hard_header_len;
	unsigned int mtu;
	short unsigned int needed_headroom;
	short unsigned int needed_tailroom;
	netdev_features_t features;
	netdev_features_t hw_features;
	netdev_features_t wanted_features;
	netdev_features_t vlan_features;
	netdev_features_t hw_enc_features;
	netdev_features_t mpls_features;
	netdev_features_t gso_partial_features;
	unsigned int min_mtu;
	unsigned int max_mtu;
	short unsigned int type;
	unsigned char min_header_len;
	unsigned char name_assign_type;
	int group;
	struct net_device_stats stats;
	atomic_long_t rx_dropped;
	atomic_long_t tx_dropped;
	atomic_long_t rx_nohandler;
	atomic_t carrier_up_count;
	atomic_t carrier_down_count;
	const struct ethtool_ops *ethtool_ops;
	const struct l3mdev_ops *l3mdev_ops;
	const struct ndisc_ops *ndisc_ops;
	const struct xfrmdev_ops *xfrmdev_ops;
	const struct tlsdev_ops *tlsdev_ops;
	const struct header_ops *header_ops;
	unsigned char operstate;
	unsigned char link_mode;
	unsigned char if_port;
	unsigned char dma;
	unsigned char perm_addr[32];
	unsigned char addr_assign_type;
	unsigned char addr_len;
	unsigned char upper_level;
	unsigned char lower_level;
	short unsigned int neigh_priv_len;
	short unsigned int dev_id;
	short unsigned int dev_port;
	short unsigned int padded;
	spinlock_t addr_list_lock;
	int irq;
	struct netdev_hw_addr_list uc;
	struct netdev_hw_addr_list mc;
	struct netdev_hw_addr_list dev_addrs;
	struct kset *queues_kset;
	unsigned int promiscuity;
	unsigned int allmulti;
	bool uc_promisc;
	struct vlan_info *vlan_info;
	struct tipc_bearer *tipc_ptr;
	struct in_device *ip_ptr;
	struct inet6_dev *ip6_ptr;
	struct wireless_dev *ieee80211_ptr;
	struct wpan_dev *ieee802154_ptr;
	struct mpls_dev *mpls_ptr;
	unsigned char *dev_addr;
	struct netdev_rx_queue *_rx;
	unsigned int num_rx_queues;
	unsigned int real_num_rx_queues;
	struct bpf_prog *xdp_prog;
	long unsigned int gro_flush_timeout;
	int napi_defer_hard_irqs;
	unsigned int gro_max_size;
	rx_handler_func_t *rx_handler;
	void *rx_handler_data;
	struct mini_Qdisc *miniq_ingress;
	struct netdev_queue *ingress_queue;
	struct nf_hook_entries *nf_hooks_ingress;
	unsigned char broadcast[32];
	struct cpu_rmap *rx_cpu_rmap;
	struct hlist_node index_hlist;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct netdev_queue *_tx;
	unsigned int num_tx_queues;
	unsigned int real_num_tx_queues;
	struct Qdisc *qdisc;
	unsigned int tx_queue_len;
	spinlock_t tx_global_lock;
	struct xdp_dev_bulk_queue *xdp_bulkq;
	struct xps_dev_maps *xps_maps[2];
	struct mini_Qdisc *miniq_egress;
	struct hlist_head qdisc_hash[16];
	struct timer_list watchdog_timer;
	int watchdog_timeo;
	u32 proto_down_reason;
	struct list_head todo_list;
	int *pcpu_refcnt;
	struct ref_tracker_dir refcnt_tracker;
	struct list_head link_watch_list;
	enum {
		NETREG_UNINITIALIZED = 0,
		NETREG_REGISTERED = 1,
		NETREG_UNREGISTERING = 2,
		NETREG_UNREGISTERED = 3,
		NETREG_RELEASED = 4,
		NETREG_DUMMY = 5,
	} reg_state: 8;
	bool dismantle;
	enum {
		RTNL_LINK_INITIALIZED = 0,
		RTNL_LINK_INITIALIZING = 1,
	} rtnl_link_state: 16;
	bool needs_free_netdev;
	void (*priv_destructor)(struct net_device *);
	struct netpoll_info *npinfo;
	possible_net_t nd_net;
	void *ml_priv;
	enum netdev_ml_priv_type ml_priv_type;
	union {
		struct pcpu_lstats *lstats;
		struct pcpu_sw_netstats *tstats;
		struct pcpu_dstats *dstats;
	};
	struct garp_port *garp_port;
	struct mrp_port *mrp_port;
	struct device dev;
	const struct attribute_group *sysfs_groups[4];
	const struct attribute_group *sysfs_rx_queue_group;
	const struct rtnl_link_ops *rtnl_link_ops;
	unsigned int gso_max_size;
	unsigned int tso_max_size;
	u16 gso_max_segs;
	u16 tso_max_segs;
	const struct dcbnl_rtnl_ops *dcbnl_ops;
	s16 num_tc;
	struct netdev_tc_txq tc_to_txq[16];
	u8 prio_tc_map[16];
	struct netprio_map *priomap;
	struct phy_device *phydev;
	struct sfp_bus *sfp_bus;
	struct lock_class_key *qdisc_tx_busylock;
	bool proto_down;
	unsigned int wol_enabled: 1;
	unsigned int threaded: 1;
	struct list_head net_notifier_list;
	const struct macsec_ops *macsec_ops;
	const struct udp_tunnel_nic_info *udp_tunnel_nic_info;
	struct udp_tunnel_nic *udp_tunnel_nic;
	struct bpf_xdp_entity xdp_state[3];
	netdevice_tracker linkwatch_dev_tracker;
	netdevice_tracker watchdog_dev_tracker;
	netdevice_tracker dev_registered_tracker;
	struct rtnl_hw_stats64 *offload_xstats_l3;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct hh_cache {
	unsigned int hh_len;
	seqlock_t hh_lock;
	long unsigned int hh_data[4];
};

struct neigh_table;

struct neigh_parms;

struct neigh_ops;

struct neighbour {
	struct neighbour *next;
	struct neigh_table *tbl;
	struct neigh_parms *parms;
	long unsigned int confirmed;
	long unsigned int updated;
	rwlock_t lock;
	refcount_t refcnt;
	unsigned int arp_queue_len_bytes;
	struct sk_buff_head arp_queue;
	struct timer_list timer;
	long unsigned int used;
	atomic_t probes;
	__u8 flags;
	__u8 nud_state;
	__u8 type;
	__u8 dead;
	u8 protocol;
	seqlock_t ha_lock;
	int: 32;
	unsigned char ha[32];
	struct hh_cache hh;
	int (*output)(struct neighbour *, struct sk_buff *);
	const struct neigh_ops *ops;
	struct list_head gc_list;
	struct callback_head rcu;
	struct net_device *dev;
	netdevice_tracker dev_tracker;
	u8 primary_key[0];
};

struct ipv6_stable_secret {
	bool initialized;
	struct in6_addr secret;
};

struct ipv6_devconf {
	__s32 forwarding;
	__s32 hop_limit;
	__s32 mtu6;
	__s32 accept_ra;
	__s32 accept_redirects;
	__s32 autoconf;
	__s32 dad_transmits;
	__s32 rtr_solicits;
	__s32 rtr_solicit_interval;
	__s32 rtr_solicit_max_interval;
	__s32 rtr_solicit_delay;
	__s32 force_mld_version;
	__s32 mldv1_unsolicited_report_interval;
	__s32 mldv2_unsolicited_report_interval;
	__s32 use_tempaddr;
	__s32 temp_valid_lft;
	__s32 temp_prefered_lft;
	__s32 regen_max_retry;
	__s32 max_desync_factor;
	__s32 max_addresses;
	__s32 accept_ra_defrtr;
	__u32 ra_defrtr_metric;
	__s32 accept_ra_min_hop_limit;
	__s32 accept_ra_pinfo;
	__s32 ignore_routes_with_linkdown;
	__s32 accept_ra_rtr_pref;
	__s32 rtr_probe_interval;
	__s32 accept_ra_rt_info_min_plen;
	__s32 accept_ra_rt_info_max_plen;
	__s32 proxy_ndp;
	__s32 accept_source_route;
	__s32 accept_ra_from_local;
	__s32 optimistic_dad;
	__s32 use_optimistic;
	__s32 mc_forwarding;
	__s32 disable_ipv6;
	__s32 drop_unicast_in_l2_multicast;
	__s32 accept_dad;
	__s32 force_tllao;
	__s32 ndisc_notify;
	__s32 suppress_frag_ndisc;
	__s32 accept_ra_mtu;
	__s32 drop_unsolicited_na;
	struct ipv6_stable_secret stable_secret;
	__s32 use_oif_addrs_only;
	__s32 keep_addr_on_down;
	__s32 seg6_enabled;
	__u32 enhanced_dad;
	__u32 addr_gen_mode;
	__s32 disable_policy;
	__s32 ndisc_tclass;
	__s32 rpl_seg_enabled;
	struct ctl_table_header *sysctl_header;
};

typedef struct {
	union {
		void *kernel;
		void *user;
	};
	bool is_kernel: 1;
} sockptr_t;

typedef enum {
	SS_FREE = 0,
	SS_UNCONNECTED = 1,
	SS_CONNECTING = 2,
	SS_CONNECTED = 3,
	SS_DISCONNECTING = 4,
} socket_state;

struct socket_wq {
	wait_queue_head_t wait;
	struct fasync_struct *fasync_list;
	long unsigned int flags;
	struct callback_head rcu;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct proto_ops;

struct socket {
	socket_state state;
	short int type;
	long unsigned int flags;
	struct file *file;
	struct sock *sk;
	const struct proto_ops *ops;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct socket_wq wq;
};

typedef int (*sk_read_actor_t)(read_descriptor_t *, struct sk_buff *, unsigned int, size_t);

struct proto_ops {
	int family;
	struct module *owner;
	int (*release)(struct socket *);
	int (*bind)(struct socket *, struct sockaddr *, int);
	int (*connect)(struct socket *, struct sockaddr *, int, int);
	int (*socketpair)(struct socket *, struct socket *);
	int (*accept)(struct socket *, struct socket *, int, bool);
	int (*getname)(struct socket *, struct sockaddr *, int);
	__poll_t (*poll)(struct file *, struct socket *, struct poll_table_struct *);
	int (*ioctl)(struct socket *, unsigned int, long unsigned int);
	int (*gettstamp)(struct socket *, void *, bool, bool);
	int (*listen)(struct socket *, int);
	int (*shutdown)(struct socket *, int);
	int (*setsockopt)(struct socket *, int, int, sockptr_t, unsigned int);
	int (*getsockopt)(struct socket *, int, int, char *, int *);
	void (*show_fdinfo)(struct seq_file *, struct socket *);
	int (*sendmsg)(struct socket *, struct msghdr *, size_t);
	int (*recvmsg)(struct socket *, struct msghdr *, size_t, int);
	int (*mmap)(struct file *, struct socket *, struct vm_area_struct *);
	ssize_t (*sendpage)(struct socket *, struct page *, int, size_t, int);
	ssize_t (*splice_read)(struct socket *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
	int (*set_peek_off)(struct sock *, int);
	int (*peek_len)(struct socket *);
	int (*read_sock)(struct sock *, read_descriptor_t *, sk_read_actor_t);
	int (*sendpage_locked)(struct sock *, struct page *, int, size_t, int);
	int (*sendmsg_locked)(struct sock *, struct msghdr *, size_t);
	int (*set_rcvlowat)(struct sock *, int);
};

enum rpc_display_format_t {
	RPC_DISPLAY_ADDR = 0,
	RPC_DISPLAY_PORT = 1,
	RPC_DISPLAY_PROTO = 2,
	RPC_DISPLAY_HEX_ADDR = 3,
	RPC_DISPLAY_HEX_PORT = 4,
	RPC_DISPLAY_NETID = 5,
	RPC_DISPLAY_MAX = 6,
};

struct dql {
	unsigned int num_queued;
	unsigned int adj_limit;
	unsigned int last_obj_cnt;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	unsigned int limit;
	unsigned int num_completed;
	unsigned int prev_ovlimit;
	unsigned int prev_num_queued;
	unsigned int prev_last_obj_cnt;
	unsigned int lowest_slack;
	long unsigned int slack_start_time;
	unsigned int max_limit;
	unsigned int min_limit;
	unsigned int slack_hold_time;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct ieee_ets {
	__u8 willing;
	__u8 ets_cap;
	__u8 cbs;
	__u8 tc_tx_bw[8];
	__u8 tc_rx_bw[8];
	__u8 tc_tsa[8];
	__u8 prio_tc[8];
	__u8 tc_reco_bw[8];
	__u8 tc_reco_tsa[8];
	__u8 reco_prio_tc[8];
};

struct ieee_maxrate {
	__u64 tc_maxrate[8];
};

struct ieee_qcn {
	__u8 rpg_enable[8];
	__u32 rppp_max_rps[8];
	__u32 rpg_time_reset[8];
	__u32 rpg_byte_reset[8];
	__u32 rpg_threshold[8];
	__u32 rpg_max_rate[8];
	__u32 rpg_ai_rate[8];
	__u32 rpg_hai_rate[8];
	__u32 rpg_gd[8];
	__u32 rpg_min_dec_fac[8];
	__u32 rpg_min_rate[8];
	__u32 cndd_state_machine[8];
};

struct ieee_qcn_stats {
	__u64 rppp_rp_centiseconds[8];
	__u32 rppp_created_rps[8];
};

struct ieee_pfc {
	__u8 pfc_cap;
	__u8 pfc_en;
	__u8 mbc;
	__u16 delay;
	__u64 requests[8];
	__u64 indications[8];
};

struct dcbnl_buffer {
	__u8 prio2buffer[8];
	__u32 buffer_size[8];
	__u32 total_size;
};

struct cee_pg {
	__u8 willing;
	__u8 error;
	__u8 pg_en;
	__u8 tcs_supported;
	__u8 pg_bw[8];
	__u8 prio_pg[8];
};

struct cee_pfc {
	__u8 willing;
	__u8 error;
	__u8 pfc_en;
	__u8 tcs_supported;
};

struct dcb_app {
	__u8 selector;
	__u8 priority;
	__u16 protocol;
};

struct dcb_peer_app_info {
	__u8 willing;
	__u8 error;
};

struct dcbnl_rtnl_ops {
	int (*ieee_getets)(struct net_device *, struct ieee_ets *);
	int (*ieee_setets)(struct net_device *, struct ieee_ets *);
	int (*ieee_getmaxrate)(struct net_device *, struct ieee_maxrate *);
	int (*ieee_setmaxrate)(struct net_device *, struct ieee_maxrate *);
	int (*ieee_getqcn)(struct net_device *, struct ieee_qcn *);
	int (*ieee_setqcn)(struct net_device *, struct ieee_qcn *);
	int (*ieee_getqcnstats)(struct net_device *, struct ieee_qcn_stats *);
	int (*ieee_getpfc)(struct net_device *, struct ieee_pfc *);
	int (*ieee_setpfc)(struct net_device *, struct ieee_pfc *);
	int (*ieee_getapp)(struct net_device *, struct dcb_app *);
	int (*ieee_setapp)(struct net_device *, struct dcb_app *);
	int (*ieee_delapp)(struct net_device *, struct dcb_app *);
	int (*ieee_peer_getets)(struct net_device *, struct ieee_ets *);
	int (*ieee_peer_getpfc)(struct net_device *, struct ieee_pfc *);
	u8 (*getstate)(struct net_device *);
	u8 (*setstate)(struct net_device *, u8);
	void (*getpermhwaddr)(struct net_device *, u8 *);
	void (*setpgtccfgtx)(struct net_device *, int, u8, u8, u8, u8);
	void (*setpgbwgcfgtx)(struct net_device *, int, u8);
	void (*setpgtccfgrx)(struct net_device *, int, u8, u8, u8, u8);
	void (*setpgbwgcfgrx)(struct net_device *, int, u8);
	void (*getpgtccfgtx)(struct net_device *, int, u8 *, u8 *, u8 *, u8 *);
	void (*getpgbwgcfgtx)(struct net_device *, int, u8 *);
	void (*getpgtccfgrx)(struct net_device *, int, u8 *, u8 *, u8 *, u8 *);
	void (*getpgbwgcfgrx)(struct net_device *, int, u8 *);
	void (*setpfccfg)(struct net_device *, int, u8);
	void (*getpfccfg)(struct net_device *, int, u8 *);
	u8 (*setall)(struct net_device *);
	u8 (*getcap)(struct net_device *, int, u8 *);
	int (*getnumtcs)(struct net_device *, int, u8 *);
	int (*setnumtcs)(struct net_device *, int, u8);
	u8 (*getpfcstate)(struct net_device *);
	void (*setpfcstate)(struct net_device *, u8);
	void (*getbcncfg)(struct net_device *, int, u32 *);
	void (*setbcncfg)(struct net_device *, int, u32);
	void (*getbcnrp)(struct net_device *, int, u8 *);
	void (*setbcnrp)(struct net_device *, int, u8);
	int (*setapp)(struct net_device *, u8, u16, u8);
	int (*getapp)(struct net_device *, u8, u16);
	u8 (*getfeatcfg)(struct net_device *, int, u8 *);
	u8 (*setfeatcfg)(struct net_device *, int, u8);
	u8 (*getdcbx)(struct net_device *);
	u8 (*setdcbx)(struct net_device *, u8);
	int (*peer_getappinfo)(struct net_device *, struct dcb_peer_app_info *, u16 *);
	int (*peer_getapptable)(struct net_device *, struct dcb_app *);
	int (*cee_peer_getpg)(struct net_device *, struct cee_pg *);
	int (*cee_peer_getpfc)(struct net_device *, struct cee_pfc *);
	int (*dcbnl_getbuffer)(struct net_device *, struct dcbnl_buffer *);
	int (*dcbnl_setbuffer)(struct net_device *, struct dcbnl_buffer *);
};

struct netprio_map {
	struct callback_head rcu;
	u32 priomap_len;
	u32 priomap[0];
};

struct xdp_mem_info {
	u32 type;
	u32 id;
};

struct xdp_rxq_info {
	struct net_device *dev;
	u32 queue_index;
	u32 reg_state;
	struct xdp_mem_info mem;
	unsigned int napi_id;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct xdp_txq_info {
	struct net_device *dev;
};

struct xdp_buff {
	void *data;
	void *data_end;
	void *data_meta;
	void *data_hard_start;
	struct xdp_rxq_info *rxq;
	struct xdp_txq_info *txq;
	u32 frame_sz;
};

struct xdp_frame {
	void *data;
	u16 len;
	u16 headroom;
	u32 metasize: 8;
	u32 frame_sz: 24;
	struct xdp_mem_info mem;
	struct net_device *dev_rx;
};

struct nlmsghdr {
	__u32 nlmsg_len;
	__u16 nlmsg_type;
	__u16 nlmsg_flags;
	__u32 nlmsg_seq;
	__u32 nlmsg_pid;
};

struct nlattr {
	__u16 nla_len;
	__u16 nla_type;
};

struct netlink_ext_ack {
	const char *_msg;
	const struct nlattr *bad_attr;
	const struct nla_policy *policy;
	u8 cookie[20];
	u8 cookie_len;
};

struct netlink_range_validation;

struct netlink_range_validation_signed;

struct nla_policy {
	u8 type;
	u8 validation_type;
	u16 len;
	union {
		const u32 bitfield32_valid;
		const u32 mask;
		const char *reject_message;
		const struct nla_policy *nested_policy;
		struct netlink_range_validation *range;
		struct netlink_range_validation_signed *range_signed;
		struct {
			s16 min;
			s16 max;
		};
		int (*validate)(const struct nlattr *, struct netlink_ext_ack *);
		u16 strict_start_type;
	};
};

struct netlink_callback {
	struct sk_buff *skb;
	const struct nlmsghdr *nlh;
	int (*dump)(struct sk_buff *, struct netlink_callback *);
	int (*done)(struct netlink_callback *);
	void *data;
	struct module *module;
	struct netlink_ext_ack *extack;
	u16 family;
	u16 answer_flags;
	u32 min_dump_alloc;
	unsigned int prev_seq;
	unsigned int seq;
	bool strict_check;
	union {
		u8 ctx[48];
		long int args[6];
	};
};

struct ndmsg {
	__u8 ndm_family;
	__u8 ndm_pad1;
	__u16 ndm_pad2;
	__s32 ndm_ifindex;
	__u16 ndm_state;
	__u8 ndm_flags;
	__u8 ndm_type;
};

typedef struct {
	unsigned int clock_rate;
	unsigned int clock_type;
	short unsigned int loopback;
} sync_serial_settings;

typedef struct {
	unsigned int clock_rate;
	unsigned int clock_type;
	short unsigned int loopback;
	unsigned int slot_map;
} te1_settings;

typedef struct {
	short unsigned int encoding;
	short unsigned int parity;
} raw_hdlc_proto;

typedef struct {
	unsigned int t391;
	unsigned int t392;
	unsigned int n391;
	unsigned int n392;
	unsigned int n393;
	short unsigned int lmi;
	short unsigned int dce;
} fr_proto;

typedef struct {
	unsigned int dlci;
} fr_proto_pvc;

typedef struct {
	unsigned int dlci;
	char master[16];
} fr_proto_pvc_info;

typedef struct {
	unsigned int interval;
	unsigned int timeout;
} cisco_proto;

typedef struct {
	short unsigned int dce;
	unsigned int modulo;
	unsigned int window;
	unsigned int t1;
	unsigned int t2;
	unsigned int n2;
} x25_hdlc_proto;

struct ifmap {
	long unsigned int mem_start;
	long unsigned int mem_end;
	short unsigned int base_addr;
	unsigned char irq;
	unsigned char dma;
	unsigned char port;
};

struct if_settings {
	unsigned int type;
	unsigned int size;
	union {
		raw_hdlc_proto *raw_hdlc;
		cisco_proto *cisco;
		fr_proto *fr;
		fr_proto_pvc *fr_pvc;
		fr_proto_pvc_info *fr_pvc_info;
		x25_hdlc_proto *x25;
		sync_serial_settings *sync;
		te1_settings *te1;
	} ifs_ifsu;
};

struct ifreq {
	union {
		char ifrn_name[16];
	} ifr_ifrn;
	union {
		struct sockaddr ifru_addr;
		struct sockaddr ifru_dstaddr;
		struct sockaddr ifru_broadaddr;
		struct sockaddr ifru_netmask;
		struct sockaddr ifru_hwaddr;
		short int ifru_flags;
		int ifru_ivalue;
		int ifru_mtu;
		struct ifmap ifru_map;
		char ifru_slave[16];
		char ifru_newname[16];
		void *ifru_data;
		struct if_settings ifru_settings;
	} ifr_ifru;
};

struct rtnl_link_stats64 {
	__u64 rx_packets;
	__u64 tx_packets;
	__u64 rx_bytes;
	__u64 tx_bytes;
	__u64 rx_errors;
	__u64 tx_errors;
	__u64 rx_dropped;
	__u64 tx_dropped;
	__u64 multicast;
	__u64 collisions;
	__u64 rx_length_errors;
	__u64 rx_over_errors;
	__u64 rx_crc_errors;
	__u64 rx_frame_errors;
	__u64 rx_fifo_errors;
	__u64 rx_missed_errors;
	__u64 tx_aborted_errors;
	__u64 tx_carrier_errors;
	__u64 tx_fifo_errors;
	__u64 tx_heartbeat_errors;
	__u64 tx_window_errors;
	__u64 rx_compressed;
	__u64 tx_compressed;
	__u64 rx_nohandler;
};

struct rtnl_hw_stats64 {
	__u64 rx_packets;
	__u64 tx_packets;
	__u64 rx_bytes;
	__u64 tx_bytes;
	__u64 rx_errors;
	__u64 tx_errors;
	__u64 rx_dropped;
	__u64 tx_dropped;
	__u64 multicast;
};

struct ifla_vf_guid {
	__u32 vf;
	__u64 guid;
};

struct ifla_vf_stats {
	__u64 rx_packets;
	__u64 tx_packets;
	__u64 rx_bytes;
	__u64 tx_bytes;
	__u64 broadcast;
	__u64 multicast;
	__u64 rx_dropped;
	__u64 tx_dropped;
};

struct ifla_vf_info {
	__u32 vf;
	__u8 mac[32];
	__u32 vlan;
	__u32 qos;
	__u32 spoofchk;
	__u32 linkstate;
	__u32 min_tx_rate;
	__u32 max_tx_rate;
	__u32 rss_query_en;
	__u32 trusted;
	__be16 vlan_proto;
};

enum netdev_tx {
	__NETDEV_TX_MIN = 2147483648,
	NETDEV_TX_OK = 0,
	NETDEV_TX_BUSY = 16,
};

typedef enum netdev_tx netdev_tx_t;

struct header_ops {
	int (*create)(struct sk_buff *, struct net_device *, short unsigned int, const void *, const void *, unsigned int);
	int (*parse)(const struct sk_buff *, unsigned char *);
	int (*cache)(const struct neighbour *, struct hh_cache *, __be16);
	void (*cache_update)(struct hh_cache *, const struct net_device *, const unsigned char *);
	bool (*validate)(const char *, unsigned int);
	__be16 (*parse_protocol)(const struct sk_buff *);
};

enum {
	NAPI_STATE_SCHED = 0,
	NAPI_STATE_MISSED = 1,
	NAPI_STATE_DISABLE = 2,
	NAPI_STATE_NPSVC = 3,
	NAPI_STATE_LISTED = 4,
	NAPI_STATE_NO_BUSY_POLL = 5,
	NAPI_STATE_IN_BUSY_POLL = 6,
	NAPI_STATE_PREFER_BUSY_POLL = 7,
	NAPI_STATE_THREADED = 8,
	NAPI_STATE_SCHED_THREADED = 9,
};

struct xsk_buff_pool;

struct netdev_queue {
	struct net_device *dev;
	netdevice_tracker dev_tracker;
	struct Qdisc *qdisc;
	struct Qdisc *qdisc_sleeping;
	struct kobject kobj;
	int numa_node;
	long unsigned int tx_maxrate;
	atomic_long_t trans_timeout;
	struct net_device *sb_dev;
	struct xsk_buff_pool *pool;
	spinlock_t _xmit_lock;
	int xmit_lock_owner;
	long unsigned int trans_start;
	long unsigned int state;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct dql dql;
};

struct rps_map {
	unsigned int len;
	struct callback_head rcu;
	u16 cpus[0];
};

struct rps_dev_flow {
	u16 cpu;
	u16 filter;
	unsigned int last_qtail;
};

struct rps_dev_flow_table {
	unsigned int mask;
	struct callback_head rcu;
	struct rps_dev_flow flows[0];
};

struct netdev_rx_queue {
	struct xdp_rxq_info xdp_rxq;
	struct rps_map *rps_map;
	struct rps_dev_flow_table *rps_flow_table;
	struct kobject kobj;
	struct net_device *dev;
	netdevice_tracker dev_tracker;
	struct xsk_buff_pool *pool;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

enum xps_map_type {
	XPS_CPUS = 0,
	XPS_RXQS = 1,
	XPS_MAPS_MAX = 2,
};

struct xps_map {
	unsigned int len;
	unsigned int alloc_len;
	struct callback_head rcu;
	u16 queues[0];
};

struct xps_dev_maps {
	struct callback_head rcu;
	unsigned int nr_ids;
	s16 num_tc;
	struct xps_map *attr_map[0];
};

struct netdev_phys_item_id {
	unsigned char id[32];
	unsigned char id_len;
};

enum net_device_path_type {
	DEV_PATH_ETHERNET = 0,
	DEV_PATH_VLAN = 1,
	DEV_PATH_BRIDGE = 2,
	DEV_PATH_PPPOE = 3,
	DEV_PATH_DSA = 4,
};

struct net_device_path {
	enum net_device_path_type type;
	const struct net_device *dev;
	union {
		struct {
			u16 id;
			__be16 proto;
			u8 h_dest[6];
		} encap;
		struct {
			enum {
				DEV_PATH_BR_VLAN_KEEP = 0,
				DEV_PATH_BR_VLAN_TAG = 1,
				DEV_PATH_BR_VLAN_UNTAG = 2,
				DEV_PATH_BR_VLAN_UNTAG_HW = 3,
			} vlan_mode;
			u16 vlan_id;
			__be16 vlan_proto;
		} bridge;
		struct {
			int port;
			u16 proto;
		} dsa;
	};
};

struct net_device_path_ctx {
	const struct net_device *dev;
	u8 daddr[6];
	int num_vlans;
	struct {
		u16 id;
		__be16 proto;
	} vlan[2];
};

enum tc_setup_type {
	TC_SETUP_QDISC_MQPRIO = 0,
	TC_SETUP_CLSU32 = 1,
	TC_SETUP_CLSFLOWER = 2,
	TC_SETUP_CLSMATCHALL = 3,
	TC_SETUP_CLSBPF = 4,
	TC_SETUP_BLOCK = 5,
	TC_SETUP_QDISC_CBS = 6,
	TC_SETUP_QDISC_RED = 7,
	TC_SETUP_QDISC_PRIO = 8,
	TC_SETUP_QDISC_MQ = 9,
	TC_SETUP_QDISC_ETF = 10,
	TC_SETUP_ROOT_QDISC = 11,
	TC_SETUP_QDISC_GRED = 12,
	TC_SETUP_QDISC_TAPRIO = 13,
	TC_SETUP_FT = 14,
	TC_SETUP_QDISC_ETS = 15,
	TC_SETUP_QDISC_TBF = 16,
	TC_SETUP_QDISC_FIFO = 17,
	TC_SETUP_QDISC_HTB = 18,
	TC_SETUP_ACT = 19,
};

enum bpf_netdev_command {
	XDP_SETUP_PROG = 0,
	XDP_SETUP_PROG_HW = 1,
	BPF_OFFLOAD_MAP_ALLOC = 2,
	BPF_OFFLOAD_MAP_FREE = 3,
	XDP_SETUP_XSK_POOL = 4,
};

enum bpf_xdp_mode {
	XDP_MODE_SKB = 0,
	XDP_MODE_DRV = 1,
	XDP_MODE_HW = 2,
	__MAX_XDP_MODE = 3,
};

struct bpf_offloaded_map;

struct netdev_bpf {
	enum bpf_netdev_command command;
	union {
		struct {
			u32 flags;
			struct bpf_prog *prog;
			struct netlink_ext_ack *extack;
		};
		struct {
			struct bpf_offloaded_map *offmap;
		};
		struct {
			struct xsk_buff_pool *pool;
			u16 queue_id;
		} xsk;
	};
};

struct xfrmdev_ops {
	int (*xdo_dev_state_add)(struct xfrm_state *);
	void (*xdo_dev_state_delete)(struct xfrm_state *);
	void (*xdo_dev_state_free)(struct xfrm_state *);
	bool (*xdo_dev_offload_ok)(struct sk_buff *, struct xfrm_state *);
	void (*xdo_dev_state_advance_esn)(struct xfrm_state *);
};

struct dev_ifalias {
	struct callback_head rcuhead;
	char ifalias[0];
};

struct devlink_port;

struct ip_tunnel_parm;

struct net_device_ops {
	int (*ndo_init)(struct net_device *);
	void (*ndo_uninit)(struct net_device *);
	int (*ndo_open)(struct net_device *);
	int (*ndo_stop)(struct net_device *);
	netdev_tx_t (*ndo_start_xmit)(struct sk_buff *, struct net_device *);
	netdev_features_t (*ndo_features_check)(struct sk_buff *, struct net_device *, netdev_features_t);
	u16 (*ndo_select_queue)(struct net_device *, struct sk_buff *, struct net_device *);
	void (*ndo_change_rx_flags)(struct net_device *, int);
	void (*ndo_set_rx_mode)(struct net_device *);
	int (*ndo_set_mac_address)(struct net_device *, void *);
	int (*ndo_validate_addr)(struct net_device *);
	int (*ndo_do_ioctl)(struct net_device *, struct ifreq *, int);
	int (*ndo_eth_ioctl)(struct net_device *, struct ifreq *, int);
	int (*ndo_siocbond)(struct net_device *, struct ifreq *, int);
	int (*ndo_siocwandev)(struct net_device *, struct if_settings *);
	int (*ndo_siocdevprivate)(struct net_device *, struct ifreq *, void *, int);
	int (*ndo_set_config)(struct net_device *, struct ifmap *);
	int (*ndo_change_mtu)(struct net_device *, int);
	int (*ndo_neigh_setup)(struct net_device *, struct neigh_parms *);
	void (*ndo_tx_timeout)(struct net_device *, unsigned int);
	void (*ndo_get_stats64)(struct net_device *, struct rtnl_link_stats64 *);
	bool (*ndo_has_offload_stats)(const struct net_device *, int);
	int (*ndo_get_offload_stats)(int, const struct net_device *, void *);
	struct net_device_stats * (*ndo_get_stats)(struct net_device *);
	int (*ndo_vlan_rx_add_vid)(struct net_device *, __be16, u16);
	int (*ndo_vlan_rx_kill_vid)(struct net_device *, __be16, u16);
	void (*ndo_poll_controller)(struct net_device *);
	int (*ndo_netpoll_setup)(struct net_device *, struct netpoll_info *);
	void (*ndo_netpoll_cleanup)(struct net_device *);
	int (*ndo_set_vf_mac)(struct net_device *, int, u8 *);
	int (*ndo_set_vf_vlan)(struct net_device *, int, u16, u8, __be16);
	int (*ndo_set_vf_rate)(struct net_device *, int, int, int);
	int (*ndo_set_vf_spoofchk)(struct net_device *, int, bool);
	int (*ndo_set_vf_trust)(struct net_device *, int, bool);
	int (*ndo_get_vf_config)(struct net_device *, int, struct ifla_vf_info *);
	int (*ndo_set_vf_link_state)(struct net_device *, int, int);
	int (*ndo_get_vf_stats)(struct net_device *, int, struct ifla_vf_stats *);
	int (*ndo_set_vf_port)(struct net_device *, int, struct nlattr **);
	int (*ndo_get_vf_port)(struct net_device *, int, struct sk_buff *);
	int (*ndo_get_vf_guid)(struct net_device *, int, struct ifla_vf_guid *, struct ifla_vf_guid *);
	int (*ndo_set_vf_guid)(struct net_device *, int, u64, int);
	int (*ndo_set_vf_rss_query_en)(struct net_device *, int, bool);
	int (*ndo_setup_tc)(struct net_device *, enum tc_setup_type, void *);
	int (*ndo_fcoe_get_wwn)(struct net_device *, u64 *, int);
	int (*ndo_rx_flow_steer)(struct net_device *, const struct sk_buff *, u16, u32);
	int (*ndo_add_slave)(struct net_device *, struct net_device *, struct netlink_ext_ack *);
	int (*ndo_del_slave)(struct net_device *, struct net_device *);
	struct net_device * (*ndo_get_xmit_slave)(struct net_device *, struct sk_buff *, bool);
	struct net_device * (*ndo_sk_get_lower_dev)(struct net_device *, struct sock *);
	netdev_features_t (*ndo_fix_features)(struct net_device *, netdev_features_t);
	int (*ndo_set_features)(struct net_device *, netdev_features_t);
	int (*ndo_neigh_construct)(struct net_device *, struct neighbour *);
	void (*ndo_neigh_destroy)(struct net_device *, struct neighbour *);
	int (*ndo_fdb_add)(struct ndmsg *, struct nlattr **, struct net_device *, const unsigned char *, u16, u16, struct netlink_ext_ack *);
	int (*ndo_fdb_del)(struct ndmsg *, struct nlattr **, struct net_device *, const unsigned char *, u16);
	int (*ndo_fdb_dump)(struct sk_buff *, struct netlink_callback *, struct net_device *, struct net_device *, int *);
	int (*ndo_fdb_get)(struct sk_buff *, struct nlattr **, struct net_device *, const unsigned char *, u16, u32, u32, struct netlink_ext_ack *);
	int (*ndo_bridge_setlink)(struct net_device *, struct nlmsghdr *, u16, struct netlink_ext_ack *);
	int (*ndo_bridge_getlink)(struct sk_buff *, u32, u32, struct net_device *, u32, int);
	int (*ndo_bridge_dellink)(struct net_device *, struct nlmsghdr *, u16);
	int (*ndo_change_carrier)(struct net_device *, bool);
	int (*ndo_get_phys_port_id)(struct net_device *, struct netdev_phys_item_id *);
	int (*ndo_get_port_parent_id)(struct net_device *, struct netdev_phys_item_id *);
	int (*ndo_get_phys_port_name)(struct net_device *, char *, size_t);
	void * (*ndo_dfwd_add_station)(struct net_device *, struct net_device *);
	void (*ndo_dfwd_del_station)(struct net_device *, void *);
	int (*ndo_set_tx_maxrate)(struct net_device *, int, u32);
	int (*ndo_get_iflink)(const struct net_device *);
	int (*ndo_fill_metadata_dst)(struct net_device *, struct sk_buff *);
	void (*ndo_set_rx_headroom)(struct net_device *, int);
	int (*ndo_bpf)(struct net_device *, struct netdev_bpf *);
	int (*ndo_xdp_xmit)(struct net_device *, int, struct xdp_frame **, u32);
	struct net_device * (*ndo_xdp_get_xmit_slave)(struct net_device *, struct xdp_buff *);
	int (*ndo_xsk_wakeup)(struct net_device *, u32, u32);
	struct devlink_port * (*ndo_get_devlink_port)(struct net_device *);
	int (*ndo_tunnel_ctl)(struct net_device *, struct ip_tunnel_parm *, int);
	struct net_device * (*ndo_get_peer_dev)(struct net_device *);
	int (*ndo_fill_forward_path)(struct net_device_path_ctx *, struct net_device_path *);
};

struct neigh_parms {
	possible_net_t net;
	struct net_device *dev;
	netdevice_tracker dev_tracker;
	struct list_head list;
	int (*neigh_setup)(struct neighbour *);
	struct neigh_table *tbl;
	void *sysctl_table;
	int dead;
	refcount_t refcnt;
	struct callback_head callback_head;
	int reachable_time;
	int data[13];
	long unsigned int data_state[1];
};

struct pcpu_lstats {
	u64_stats_t packets;
	u64_stats_t bytes;
	struct u64_stats_sync syncp;
};

struct pcpu_sw_netstats {
	u64 rx_packets;
	u64 rx_bytes;
	u64 tx_packets;
	u64 tx_bytes;
	struct u64_stats_sync syncp;
};

enum ethtool_phys_id_state {
	ETHTOOL_ID_INACTIVE = 0,
	ETHTOOL_ID_ACTIVE = 1,
	ETHTOOL_ID_ON = 2,
	ETHTOOL_ID_OFF = 3,
};

struct ethtool_drvinfo;

struct ethtool_regs;

struct ethtool_wolinfo;

struct ethtool_link_ext_state_info;

struct ethtool_eeprom;

struct ethtool_coalesce;

struct kernel_ethtool_coalesce;

struct ethtool_ringparam;

struct kernel_ethtool_ringparam;

struct ethtool_pause_stats;

struct ethtool_pauseparam;

struct ethtool_test;

struct ethtool_stats;

struct ethtool_rxnfc;

struct ethtool_flash;

struct ethtool_channels;

struct ethtool_dump;

struct ethtool_ts_info;

struct ethtool_modinfo;

struct ethtool_eee;

struct ethtool_tunable;

struct ethtool_link_ksettings;

struct ethtool_fec_stats;

struct ethtool_fecparam;

struct ethtool_module_eeprom;

struct ethtool_eth_phy_stats;

struct ethtool_eth_mac_stats;

struct ethtool_eth_ctrl_stats;

struct ethtool_rmon_stats;

struct ethtool_rmon_hist_range;

struct ethtool_module_power_mode_params;

struct ethtool_ops {
	u32 cap_link_lanes_supported: 1;
	u32 supported_coalesce_params;
	u32 supported_ring_params;
	void (*get_drvinfo)(struct net_device *, struct ethtool_drvinfo *);
	int (*get_regs_len)(struct net_device *);
	void (*get_regs)(struct net_device *, struct ethtool_regs *, void *);
	void (*get_wol)(struct net_device *, struct ethtool_wolinfo *);
	int (*set_wol)(struct net_device *, struct ethtool_wolinfo *);
	u32 (*get_msglevel)(struct net_device *);
	void (*set_msglevel)(struct net_device *, u32);
	int (*nway_reset)(struct net_device *);
	u32 (*get_link)(struct net_device *);
	int (*get_link_ext_state)(struct net_device *, struct ethtool_link_ext_state_info *);
	int (*get_eeprom_len)(struct net_device *);
	int (*get_eeprom)(struct net_device *, struct ethtool_eeprom *, u8 *);
	int (*set_eeprom)(struct net_device *, struct ethtool_eeprom *, u8 *);
	int (*get_coalesce)(struct net_device *, struct ethtool_coalesce *, struct kernel_ethtool_coalesce *, struct netlink_ext_ack *);
	int (*set_coalesce)(struct net_device *, struct ethtool_coalesce *, struct kernel_ethtool_coalesce *, struct netlink_ext_ack *);
	void (*get_ringparam)(struct net_device *, struct ethtool_ringparam *, struct kernel_ethtool_ringparam *, struct netlink_ext_ack *);
	int (*set_ringparam)(struct net_device *, struct ethtool_ringparam *, struct kernel_ethtool_ringparam *, struct netlink_ext_ack *);
	void (*get_pause_stats)(struct net_device *, struct ethtool_pause_stats *);
	void (*get_pauseparam)(struct net_device *, struct ethtool_pauseparam *);
	int (*set_pauseparam)(struct net_device *, struct ethtool_pauseparam *);
	void (*self_test)(struct net_device *, struct ethtool_test *, u64 *);
	void (*get_strings)(struct net_device *, u32, u8 *);
	int (*set_phys_id)(struct net_device *, enum ethtool_phys_id_state);
	void (*get_ethtool_stats)(struct net_device *, struct ethtool_stats *, u64 *);
	int (*begin)(struct net_device *);
	void (*complete)(struct net_device *);
	u32 (*get_priv_flags)(struct net_device *);
	int (*set_priv_flags)(struct net_device *, u32);
	int (*get_sset_count)(struct net_device *, int);
	int (*get_rxnfc)(struct net_device *, struct ethtool_rxnfc *, u32 *);
	int (*set_rxnfc)(struct net_device *, struct ethtool_rxnfc *);
	int (*flash_device)(struct net_device *, struct ethtool_flash *);
	int (*reset)(struct net_device *, u32 *);
	u32 (*get_rxfh_key_size)(struct net_device *);
	u32 (*get_rxfh_indir_size)(struct net_device *);
	int (*get_rxfh)(struct net_device *, u32 *, u8 *, u8 *);
	int (*set_rxfh)(struct net_device *, const u32 *, const u8 *, const u8);
	int (*get_rxfh_context)(struct net_device *, u32 *, u8 *, u8 *, u32);
	int (*set_rxfh_context)(struct net_device *, const u32 *, const u8 *, const u8, u32 *, bool);
	void (*get_channels)(struct net_device *, struct ethtool_channels *);
	int (*set_channels)(struct net_device *, struct ethtool_channels *);
	int (*get_dump_flag)(struct net_device *, struct ethtool_dump *);
	int (*get_dump_data)(struct net_device *, struct ethtool_dump *, void *);
	int (*set_dump)(struct net_device *, struct ethtool_dump *);
	int (*get_ts_info)(struct net_device *, struct ethtool_ts_info *);
	int (*get_module_info)(struct net_device *, struct ethtool_modinfo *);
	int (*get_module_eeprom)(struct net_device *, struct ethtool_eeprom *, u8 *);
	int (*get_eee)(struct net_device *, struct ethtool_eee *);
	int (*set_eee)(struct net_device *, struct ethtool_eee *);
	int (*get_tunable)(struct net_device *, const struct ethtool_tunable *, void *);
	int (*set_tunable)(struct net_device *, const struct ethtool_tunable *, const void *);
	int (*get_per_queue_coalesce)(struct net_device *, u32, struct ethtool_coalesce *);
	int (*set_per_queue_coalesce)(struct net_device *, u32, struct ethtool_coalesce *);
	int (*get_link_ksettings)(struct net_device *, struct ethtool_link_ksettings *);
	int (*set_link_ksettings)(struct net_device *, const struct ethtool_link_ksettings *);
	void (*get_fec_stats)(struct net_device *, struct ethtool_fec_stats *);
	int (*get_fecparam)(struct net_device *, struct ethtool_fecparam *);
	int (*set_fecparam)(struct net_device *, struct ethtool_fecparam *);
	void (*get_ethtool_phy_stats)(struct net_device *, struct ethtool_stats *, u64 *);
	int (*get_phy_tunable)(struct net_device *, const struct ethtool_tunable *, void *);
	int (*set_phy_tunable)(struct net_device *, const struct ethtool_tunable *, const void *);
	int (*get_module_eeprom_by_page)(struct net_device *, const struct ethtool_module_eeprom *, struct netlink_ext_ack *);
	void (*get_eth_phy_stats)(struct net_device *, struct ethtool_eth_phy_stats *);
	void (*get_eth_mac_stats)(struct net_device *, struct ethtool_eth_mac_stats *);
	void (*get_eth_ctrl_stats)(struct net_device *, struct ethtool_eth_ctrl_stats *);
	void (*get_rmon_stats)(struct net_device *, struct ethtool_rmon_stats *, const struct ethtool_rmon_hist_range **);
	int (*get_module_power_mode)(struct net_device *, struct ethtool_module_power_mode_params *, struct netlink_ext_ack *);
	int (*set_module_power_mode)(struct net_device *, const struct ethtool_module_power_mode_params *, struct netlink_ext_ack *);
};

struct l3mdev_ops {
	u32 (*l3mdev_fib_table)(const struct net_device *);
	struct sk_buff * (*l3mdev_l3_rcv)(struct net_device *, struct sk_buff *, u16);
	struct sk_buff * (*l3mdev_l3_out)(struct net_device *, struct sock *, struct sk_buff *, u16);
	struct dst_entry * (*l3mdev_link_scope_lookup)(const struct net_device *, struct flowi6 *);
};

struct nd_opt_hdr;

struct ndisc_options;

struct prefix_info;

struct ndisc_ops {
	int (*is_useropt)(u8);
	int (*parse_options)(const struct net_device *, struct nd_opt_hdr *, struct ndisc_options *);
	void (*update)(const struct net_device *, struct neighbour *, u32, u8, const struct ndisc_options *);
	int (*opt_addr_space)(const struct net_device *, u8, struct neighbour *, u8 *, u8 **);
	void (*fill_addr_option)(const struct net_device *, struct sk_buff *, u8, const u8 *);
	void (*prefix_rcv_add_addr)(struct net *, struct net_device *, const struct prefix_info *, struct inet6_dev *, struct in6_addr *, int, u32, bool, bool, __u32, u32, bool);
};

enum tls_offload_ctx_dir {
	TLS_OFFLOAD_CTX_DIR_RX = 0,
	TLS_OFFLOAD_CTX_DIR_TX = 1,
};

struct tls_crypto_info;

struct tls_context;

struct tlsdev_ops {
	int (*tls_dev_add)(struct net_device *, struct sock *, enum tls_offload_ctx_dir, struct tls_crypto_info *, u32);
	void (*tls_dev_del)(struct net_device *, struct tls_context *, enum tls_offload_ctx_dir);
	int (*tls_dev_resync)(struct net_device *, struct sock *, u32, u8 *, enum tls_offload_ctx_dir);
};

struct ipv6_devstat {
	struct proc_dir_entry *proc_dir_entry;
	struct ipstats_mib *ipv6;
	struct icmpv6_mib_device *icmpv6dev;
	struct icmpv6msg_mib_device *icmpv6msgdev;
};

struct ifmcaddr6;

struct ifacaddr6;

struct inet6_dev {
	struct net_device *dev;
	netdevice_tracker dev_tracker;
	struct list_head addr_list;
	struct ifmcaddr6 *mc_list;
	struct ifmcaddr6 *mc_tomb;
	unsigned char mc_qrv;
	unsigned char mc_gq_running;
	unsigned char mc_ifc_count;
	unsigned char mc_dad_count;
	long unsigned int mc_v1_seen;
	long unsigned int mc_qi;
	long unsigned int mc_qri;
	long unsigned int mc_maxdelay;
	struct delayed_work mc_gq_work;
	struct delayed_work mc_ifc_work;
	struct delayed_work mc_dad_work;
	struct delayed_work mc_query_work;
	struct delayed_work mc_report_work;
	struct sk_buff_head mc_query_queue;
	struct sk_buff_head mc_report_queue;
	spinlock_t mc_query_lock;
	spinlock_t mc_report_lock;
	struct mutex mc_lock;
	struct ifacaddr6 *ac_list;
	rwlock_t lock;
	refcount_t refcnt;
	__u32 if_flags;
	int dead;
	u32 desync_factor;
	struct list_head tempaddr_list;
	struct in6_addr token;
	struct neigh_parms *nd_parms;
	struct ipv6_devconf cnf;
	struct ipv6_devstat stats;
	struct timer_list rs_timer;
	__s32 rs_interval;
	__u8 rs_probes;
	long unsigned int tstamp;
	struct callback_head rcu;
};

struct rtnl_link_ops {
	struct list_head list;
	const char *kind;
	size_t priv_size;
	struct net_device * (*alloc)(struct nlattr **, const char *, unsigned char, unsigned int, unsigned int);
	void (*setup)(struct net_device *);
	bool netns_refund;
	unsigned int maxtype;
	const struct nla_policy *policy;
	int (*validate)(struct nlattr **, struct nlattr **, struct netlink_ext_ack *);
	int (*newlink)(struct net *, struct net_device *, struct nlattr **, struct nlattr **, struct netlink_ext_ack *);
	int (*changelink)(struct net_device *, struct nlattr **, struct nlattr **, struct netlink_ext_ack *);
	void (*dellink)(struct net_device *, struct list_head *);
	size_t (*get_size)(const struct net_device *);
	int (*fill_info)(struct sk_buff *, const struct net_device *);
	size_t (*get_xstats_size)(const struct net_device *);
	int (*fill_xstats)(struct sk_buff *, const struct net_device *);
	unsigned int (*get_num_tx_queues)();
	unsigned int (*get_num_rx_queues)();
	unsigned int slave_maxtype;
	const struct nla_policy *slave_policy;
	int (*slave_changelink)(struct net_device *, struct net_device *, struct nlattr **, struct nlattr **, struct netlink_ext_ack *);
	size_t (*get_slave_size)(const struct net_device *, const struct net_device *);
	int (*fill_slave_info)(struct sk_buff *, const struct net_device *, const struct net_device *);
	struct net * (*get_link_net)(const struct net_device *);
	size_t (*get_linkxstats_size)(const struct net_device *, int);
	int (*fill_linkxstats)(struct sk_buff *, const struct net_device *, int *, int);
};

struct udp_tunnel_nic_table_info {
	unsigned int n_entries;
	unsigned int tunnel_types;
};

struct udp_tunnel_info;

struct udp_tunnel_nic_shared;

struct udp_tunnel_nic_info {
	int (*set_port)(struct net_device *, unsigned int, unsigned int, struct udp_tunnel_info *);
	int (*unset_port)(struct net_device *, unsigned int, unsigned int, struct udp_tunnel_info *);
	int (*sync_table)(struct net_device *, unsigned int);
	struct udp_tunnel_nic_shared *shared;
	unsigned int flags;
	struct udp_tunnel_nic_table_info tables[4];
};

enum {
	NETIF_MSG_DRV_BIT = 0,
	NETIF_MSG_PROBE_BIT = 1,
	NETIF_MSG_LINK_BIT = 2,
	NETIF_MSG_TIMER_BIT = 3,
	NETIF_MSG_IFDOWN_BIT = 4,
	NETIF_MSG_IFUP_BIT = 5,
	NETIF_MSG_RX_ERR_BIT = 6,
	NETIF_MSG_TX_ERR_BIT = 7,
	NETIF_MSG_TX_QUEUED_BIT = 8,
	NETIF_MSG_INTR_BIT = 9,
	NETIF_MSG_TX_DONE_BIT = 10,
	NETIF_MSG_RX_STATUS_BIT = 11,
	NETIF_MSG_PKTDATA_BIT = 12,
	NETIF_MSG_HW_BIT = 13,
	NETIF_MSG_WOL_BIT = 14,
	NETIF_MSG_CLASS_COUNT = 15,
};

enum {
	RTAX_UNSPEC = 0,
	RTAX_LOCK = 1,
	RTAX_MTU = 2,
	RTAX_WINDOW = 3,
	RTAX_RTT = 4,
	RTAX_RTTVAR = 5,
	RTAX_SSTHRESH = 6,
	RTAX_CWND = 7,
	RTAX_ADVMSS = 8,
	RTAX_REORDERING = 9,
	RTAX_HOPLIMIT = 10,
	RTAX_INITCWND = 11,
	RTAX_FEATURES = 12,
	RTAX_RTO_MIN = 13,
	RTAX_INITRWND = 14,
	RTAX_QUICKACK = 15,
	RTAX_CC_ALGO = 16,
	RTAX_FASTOPEN_NO_COOKIE = 17,
	__RTAX_MAX = 18,
};

struct netlink_range_validation {
	u64 min;
	u64 max;
};

struct netlink_range_validation_signed {
	s64 min;
	s64 max;
};

enum {
	NEIGH_VAR_MCAST_PROBES = 0,
	NEIGH_VAR_UCAST_PROBES = 1,
	NEIGH_VAR_APP_PROBES = 2,
	NEIGH_VAR_MCAST_REPROBES = 3,
	NEIGH_VAR_RETRANS_TIME = 4,
	NEIGH_VAR_BASE_REACHABLE_TIME = 5,
	NEIGH_VAR_DELAY_PROBE_TIME = 6,
	NEIGH_VAR_GC_STALETIME = 7,
	NEIGH_VAR_QUEUE_LEN_BYTES = 8,
	NEIGH_VAR_PROXY_QLEN = 9,
	NEIGH_VAR_ANYCAST_DELAY = 10,
	NEIGH_VAR_PROXY_DELAY = 11,
	NEIGH_VAR_LOCKTIME = 12,
	NEIGH_VAR_QUEUE_LEN = 13,
	NEIGH_VAR_RETRANS_TIME_MS = 14,
	NEIGH_VAR_BASE_REACHABLE_TIME_MS = 15,
	NEIGH_VAR_GC_INTERVAL = 16,
	NEIGH_VAR_GC_THRESH1 = 17,
	NEIGH_VAR_GC_THRESH2 = 18,
	NEIGH_VAR_GC_THRESH3 = 19,
	NEIGH_VAR_MAX = 20,
};

struct pneigh_entry;

struct neigh_statistics;

struct neigh_hash_table;

struct neigh_table {
	int family;
	unsigned int entry_size;
	unsigned int key_len;
	__be16 protocol;
	__u32 (*hash)(const void *, const struct net_device *, __u32 *);
	bool (*key_eq)(const struct neighbour *, const void *);
	int (*constructor)(struct neighbour *);
	int (*pconstructor)(struct pneigh_entry *);
	void (*pdestructor)(struct pneigh_entry *);
	void (*proxy_redo)(struct sk_buff *);
	int (*is_multicast)(const void *);
	bool (*allow_add)(const struct net_device *, struct netlink_ext_ack *);
	char *id;
	struct neigh_parms parms;
	struct list_head parms_list;
	int gc_interval;
	int gc_thresh1;
	int gc_thresh2;
	int gc_thresh3;
	long unsigned int last_flush;
	struct delayed_work gc_work;
	struct timer_list proxy_timer;
	struct sk_buff_head proxy_queue;
	atomic_t entries;
	atomic_t gc_entries;
	struct list_head gc_list;
	rwlock_t lock;
	long unsigned int last_rand;
	struct neigh_statistics *stats;
	struct neigh_hash_table *nht;
	struct pneigh_entry **phash_buckets;
};

struct neigh_statistics {
	long unsigned int allocs;
	long unsigned int destroys;
	long unsigned int hash_grows;
	long unsigned int res_failed;
	long unsigned int lookups;
	long unsigned int hits;
	long unsigned int rcv_probes_mcast;
	long unsigned int rcv_probes_ucast;
	long unsigned int periodic_gc_runs;
	long unsigned int forced_gc_runs;
	long unsigned int unres_discards;
	long unsigned int table_fulls;
};

struct neigh_ops {
	int family;
	void (*solicit)(struct neighbour *, struct sk_buff *);
	void (*error_report)(struct neighbour *, struct sk_buff *);
	int (*output)(struct neighbour *, struct sk_buff *);
	int (*connected_output)(struct neighbour *, struct sk_buff *);
};

struct pneigh_entry {
	struct pneigh_entry *next;
	possible_net_t net;
	struct net_device *dev;
	netdevice_tracker dev_tracker;
	u8 flags;
	u8 protocol;
	u8 key[0];
};

struct neigh_hash_table {
	struct neighbour **hash_buckets;
	unsigned int hash_shift;
	__u32 hash_rnd[4];
	struct callback_head rcu;
};

enum {
	TCP_ESTABLISHED = 1,
	TCP_SYN_SENT = 2,
	TCP_SYN_RECV = 3,
	TCP_FIN_WAIT1 = 4,
	TCP_FIN_WAIT2 = 5,
	TCP_TIME_WAIT = 6,
	TCP_CLOSE = 7,
	TCP_CLOSE_WAIT = 8,
	TCP_LAST_ACK = 9,
	TCP_LISTEN = 10,
	TCP_CLOSING = 11,
	TCP_NEW_SYN_RECV = 12,
	TCP_MAX_STATES = 13,
};

struct fib_rule_hdr {
	__u8 family;
	__u8 dst_len;
	__u8 src_len;
	__u8 tos;
	__u8 table;
	__u8 res1;
	__u8 res2;
	__u8 action;
	__u32 flags;
};

struct fib_rule_port_range {
	__u16 start;
	__u16 end;
};

struct fib_kuid_range {
	kuid_t start;
	kuid_t end;
};

struct fib_rule {
	struct list_head list;
	int iifindex;
	int oifindex;
	u32 mark;
	u32 mark_mask;
	u32 flags;
	u32 table;
	u8 action;
	u8 l3mdev;
	u8 proto;
	u8 ip_proto;
	u32 target;
	__be64 tun_id;
	struct fib_rule *ctarget;
	struct net *fr_net;
	refcount_t refcnt;
	u32 pref;
	int suppress_ifgroup;
	int suppress_prefixlen;
	char iifname[16];
	char oifname[16];
	struct fib_kuid_range uid_range;
	struct fib_rule_port_range sport_range;
	struct fib_rule_port_range dport_range;
	struct callback_head rcu;
};

struct fib_lookup_arg {
	void *lookup_ptr;
	const void *lookup_data;
	void *result;
	struct fib_rule *rule;
	u32 table;
	int flags;
};

struct smc_hashinfo;

struct sk_psock;

struct request_sock_ops;

struct timewait_sock_ops;

struct udp_table;

struct raw_hashinfo;

struct proto {
	void (*close)(struct sock *, long int);
	int (*pre_connect)(struct sock *, struct sockaddr *, int);
	int (*connect)(struct sock *, struct sockaddr *, int);
	int (*disconnect)(struct sock *, int);
	struct sock * (*accept)(struct sock *, int, int *, bool);
	int (*ioctl)(struct sock *, int, long unsigned int);
	int (*init)(struct sock *);
	void (*destroy)(struct sock *);
	void (*shutdown)(struct sock *, int);
	int (*setsockopt)(struct sock *, int, int, sockptr_t, unsigned int);
	int (*getsockopt)(struct sock *, int, int, char *, int *);
	void (*keepalive)(struct sock *, int);
	int (*sendmsg)(struct sock *, struct msghdr *, size_t);
	int (*recvmsg)(struct sock *, struct msghdr *, size_t, int, int, int *);
	int (*sendpage)(struct sock *, struct page *, int, size_t, int);
	int (*bind)(struct sock *, struct sockaddr *, int);
	int (*bind_add)(struct sock *, struct sockaddr *, int);
	int (*backlog_rcv)(struct sock *, struct sk_buff *);
	bool (*bpf_bypass_getsockopt)(int, int);
	void (*release_cb)(struct sock *);
	int (*hash)(struct sock *);
	void (*unhash)(struct sock *);
	void (*rehash)(struct sock *);
	int (*get_port)(struct sock *, short unsigned int);
	void (*put_port)(struct sock *);
	int (*psock_update_sk_prot)(struct sock *, struct sk_psock *, bool);
	unsigned int inuse_idx;
	int (*forward_alloc_get)(const struct sock *);
	bool (*stream_memory_free)(const struct sock *, int);
	bool (*sock_is_readable)(struct sock *);
	void (*enter_memory_pressure)(struct sock *);
	void (*leave_memory_pressure)(struct sock *);
	atomic_long_t *memory_allocated;
	int *per_cpu_fw_alloc;
	struct percpu_counter *sockets_allocated;
	long unsigned int *memory_pressure;
	long int *sysctl_mem;
	int *sysctl_wmem;
	int *sysctl_rmem;
	u32 sysctl_wmem_offset;
	u32 sysctl_rmem_offset;
	int max_header;
	bool no_autobind;
	struct kmem_cache *slab;
	unsigned int obj_size;
	slab_flags_t slab_flags;
	unsigned int useroffset;
	unsigned int usersize;
	unsigned int *orphan_count;
	struct request_sock_ops *rsk_prot;
	struct timewait_sock_ops *twsk_prot;
	union {
		struct inet_hashinfo *hashinfo;
		struct udp_table *udp_table;
		struct raw_hashinfo *raw_hash;
		struct smc_hashinfo *smc_hash;
	} h;
	struct module *owner;
	char name[32];
	struct list_head node;
	int (*diag_destroy)(struct sock *, int);
};

struct request_sock;

struct request_sock_ops {
	int family;
	unsigned int obj_size;
	struct kmem_cache *slab;
	char *slab_name;
	int (*rtx_syn_ack)(const struct sock *, struct request_sock *);
	void (*send_ack)(const struct sock *, struct sk_buff *, struct request_sock *);
	void (*send_reset)(const struct sock *, struct sk_buff *);
	void (*destructor)(struct request_sock *);
	void (*syn_ack_timeout)(const struct request_sock *);
};

struct timewait_sock_ops {
	struct kmem_cache *twsk_slab;
	char *twsk_slab_name;
	unsigned int twsk_obj_size;
	int (*twsk_unique)(struct sock *, struct sock *, void *);
	void (*twsk_destructor)(struct sock *);
};

struct saved_syn;

struct request_sock {
	struct sock_common __req_common;
	struct request_sock *dl_next;
	u16 mss;
	u8 num_retrans;
	u8 syncookie: 1;
	u8 num_timeout: 7;
	u32 ts_recent;
	struct timer_list rsk_timer;
	const struct request_sock_ops *rsk_ops;
	struct sock *sk;
	struct saved_syn *saved_syn;
	u32 secid;
	u32 peer_secid;
};

struct saved_syn {
	u32 mac_hdrlen;
	u32 network_hdrlen;
	u32 tcp_hdrlen;
	u8 data[0];
};

enum tsq_enum {
	TSQ_THROTTLED = 0,
	TSQ_QUEUED = 1,
	TCP_TSQ_DEFERRED = 2,
	TCP_WRITE_TIMER_DEFERRED = 3,
	TCP_DELACK_TIMER_DEFERRED = 4,
	TCP_MTU_REDUCED_DEFERRED = 5,
};

struct ip6_sf_list {
	struct ip6_sf_list *sf_next;
	struct in6_addr sf_addr;
	long unsigned int sf_count[2];
	unsigned char sf_gsresp;
	unsigned char sf_oldin;
	unsigned char sf_crcount;
	struct callback_head rcu;
};

struct ifmcaddr6 {
	struct in6_addr mca_addr;
	struct inet6_dev *idev;
	struct ifmcaddr6 *next;
	struct ip6_sf_list *mca_sources;
	struct ip6_sf_list *mca_tomb;
	unsigned int mca_sfmode;
	unsigned char mca_crcount;
	long unsigned int mca_sfcount[2];
	struct delayed_work mca_work;
	unsigned int mca_flags;
	int mca_users;
	refcount_t mca_refcnt;
	long unsigned int mca_cstamp;
	long unsigned int mca_tstamp;
	struct callback_head rcu;
};

struct ifacaddr6 {
	struct in6_addr aca_addr;
	struct fib6_info *aca_rt;
	struct ifacaddr6 *aca_next;
	struct hlist_node aca_addr_lst;
	int aca_users;
	refcount_t aca_refcnt;
	long unsigned int aca_cstamp;
	long unsigned int aca_tstamp;
	struct callback_head rcu;
};

enum {
	__ND_OPT_PREFIX_INFO_END = 0,
	ND_OPT_SOURCE_LL_ADDR = 1,
	ND_OPT_TARGET_LL_ADDR = 2,
	ND_OPT_PREFIX_INFO = 3,
	ND_OPT_REDIRECT_HDR = 4,
	ND_OPT_MTU = 5,
	ND_OPT_NONCE = 14,
	__ND_OPT_ARRAY_MAX = 15,
	ND_OPT_ROUTE_INFO = 24,
	ND_OPT_RDNSS = 25,
	ND_OPT_DNSSL = 31,
	ND_OPT_6CO = 34,
	ND_OPT_CAPTIVE_PORTAL = 37,
	ND_OPT_PREF64 = 38,
	__ND_OPT_MAX = 39,
};

struct nd_opt_hdr {
	__u8 nd_opt_type;
	__u8 nd_opt_len;
};

struct ndisc_options {
	struct nd_opt_hdr *nd_opt_array[15];
	struct nd_opt_hdr *nd_opts_ri;
	struct nd_opt_hdr *nd_opts_ri_end;
	struct nd_opt_hdr *nd_useropts;
	struct nd_opt_hdr *nd_useropts_end;
	struct nd_opt_hdr *nd_802154_opt_array[3];
};

struct prefix_info {
	__u8 type;
	__u8 length;
	__u8 prefix_len;
	__u8 reserved: 6;
	__u8 autoconf: 1;
	__u8 onlink: 1;
	__be32 valid;
	__be32 prefered;
	__be32 reserved2;
	struct in6_addr prefix;
};

enum nfs_opnum4 {
	OP_ACCESS = 3,
	OP_CLOSE = 4,
	OP_COMMIT = 5,
	OP_CREATE = 6,
	OP_DELEGPURGE = 7,
	OP_DELEGRETURN = 8,
	OP_GETATTR = 9,
	OP_GETFH = 10,
	OP_LINK = 11,
	OP_LOCK = 12,
	OP_LOCKT = 13,
	OP_LOCKU = 14,
	OP_LOOKUP = 15,
	OP_LOOKUPP = 16,
	OP_NVERIFY = 17,
	OP_OPEN = 18,
	OP_OPENATTR = 19,
	OP_OPEN_CONFIRM = 20,
	OP_OPEN_DOWNGRADE = 21,
	OP_PUTFH = 22,
	OP_PUTPUBFH = 23,
	OP_PUTROOTFH = 24,
	OP_READ = 25,
	OP_READDIR = 26,
	OP_READLINK = 27,
	OP_REMOVE = 28,
	OP_RENAME = 29,
	OP_RENEW = 30,
	OP_RESTOREFH = 31,
	OP_SAVEFH = 32,
	OP_SECINFO = 33,
	OP_SETATTR = 34,
	OP_SETCLIENTID = 35,
	OP_SETCLIENTID_CONFIRM = 36,
	OP_VERIFY = 37,
	OP_WRITE = 38,
	OP_RELEASE_LOCKOWNER = 39,
	OP_BACKCHANNEL_CTL = 40,
	OP_BIND_CONN_TO_SESSION = 41,
	OP_EXCHANGE_ID = 42,
	OP_CREATE_SESSION = 43,
	OP_DESTROY_SESSION = 44,
	OP_FREE_STATEID = 45,
	OP_GET_DIR_DELEGATION = 46,
	OP_GETDEVICEINFO = 47,
	OP_GETDEVICELIST = 48,
	OP_LAYOUTCOMMIT = 49,
	OP_LAYOUTGET = 50,
	OP_LAYOUTRETURN = 51,
	OP_SECINFO_NO_NAME = 52,
	OP_SEQUENCE = 53,
	OP_SET_SSV = 54,
	OP_TEST_STATEID = 55,
	OP_WANT_DELEGATION = 56,
	OP_DESTROY_CLIENTID = 57,
	OP_RECLAIM_COMPLETE = 58,
	OP_ALLOCATE = 59,
	OP_COPY = 60,
	OP_COPY_NOTIFY = 61,
	OP_DEALLOCATE = 62,
	OP_IO_ADVISE = 63,
	OP_LAYOUTERROR = 64,
	OP_LAYOUTSTATS = 65,
	OP_OFFLOAD_CANCEL = 66,
	OP_OFFLOAD_STATUS = 67,
	OP_READ_PLUS = 68,
	OP_SEEK = 69,
	OP_WRITE_SAME = 70,
	OP_CLONE = 71,
	OP_GETXATTR = 72,
	OP_SETXATTR = 73,
	OP_LISTXATTRS = 74,
	OP_REMOVEXATTR = 75,
	OP_ILLEGAL = 10044,
};

enum {
	UNAME26 = 131072,
	ADDR_NO_RANDOMIZE = 262144,
	FDPIC_FUNCPTRS = 524288,
	MMAP_PAGE_ZERO = 1048576,
	ADDR_COMPAT_LAYOUT = 2097152,
	READ_IMPLIES_EXEC = 4194304,
	ADDR_LIMIT_32BIT = 8388608,
	SHORT_INODE = 16777216,
	WHOLE_SECONDS = 33554432,
	STICKY_TIMEOUTS = 67108864,
	ADDR_LIMIT_3GB = 134217728,
};

enum perf_hw_cache_id {
	PERF_COUNT_HW_CACHE_L1D = 0,
	PERF_COUNT_HW_CACHE_L1I = 1,
	PERF_COUNT_HW_CACHE_LL = 2,
	PERF_COUNT_HW_CACHE_DTLB = 3,
	PERF_COUNT_HW_CACHE_ITLB = 4,
	PERF_COUNT_HW_CACHE_BPU = 5,
	PERF_COUNT_HW_CACHE_NODE = 6,
	PERF_COUNT_HW_CACHE_MAX = 7,
};

enum perf_hw_cache_op_id {
	PERF_COUNT_HW_CACHE_OP_READ = 0,
	PERF_COUNT_HW_CACHE_OP_WRITE = 1,
	PERF_COUNT_HW_CACHE_OP_PREFETCH = 2,
	PERF_COUNT_HW_CACHE_OP_MAX = 3,
};

enum perf_hw_cache_op_result_id {
	PERF_COUNT_HW_CACHE_RESULT_ACCESS = 0,
	PERF_COUNT_HW_CACHE_RESULT_MISS = 1,
	PERF_COUNT_HW_CACHE_RESULT_MAX = 2,
};

enum perf_branch_sample_type_shift {
	PERF_SAMPLE_BRANCH_USER_SHIFT = 0,
	PERF_SAMPLE_BRANCH_KERNEL_SHIFT = 1,
	PERF_SAMPLE_BRANCH_HV_SHIFT = 2,
	PERF_SAMPLE_BRANCH_ANY_SHIFT = 3,
	PERF_SAMPLE_BRANCH_ANY_CALL_SHIFT = 4,
	PERF_SAMPLE_BRANCH_ANY_RETURN_SHIFT = 5,
	PERF_SAMPLE_BRANCH_IND_CALL_SHIFT = 6,
	PERF_SAMPLE_BRANCH_ABORT_TX_SHIFT = 7,
	PERF_SAMPLE_BRANCH_IN_TX_SHIFT = 8,
	PERF_SAMPLE_BRANCH_NO_TX_SHIFT = 9,
	PERF_SAMPLE_BRANCH_COND_SHIFT = 10,
	PERF_SAMPLE_BRANCH_CALL_STACK_SHIFT = 11,
	PERF_SAMPLE_BRANCH_IND_JUMP_SHIFT = 12,
	PERF_SAMPLE_BRANCH_CALL_SHIFT = 13,
	PERF_SAMPLE_BRANCH_NO_FLAGS_SHIFT = 14,
	PERF_SAMPLE_BRANCH_NO_CYCLES_SHIFT = 15,
	PERF_SAMPLE_BRANCH_TYPE_SAVE_SHIFT = 16,
	PERF_SAMPLE_BRANCH_HW_INDEX_SHIFT = 17,
	PERF_SAMPLE_BRANCH_MAX_SHIFT = 18,
};

enum {
	TSK_TRACE_FL_TRACE_BIT = 0,
	TSK_TRACE_FL_GRAPH_BIT = 1,
};

struct uuidcmp {
	const char *uuid;
	int len;
};

struct subprocess_info {
	struct work_struct work;
	struct completion *complete;
	const char *path;
	char **argv;
	char **envp;
	int wait;
	int retval;
	int (*init)(struct subprocess_info *, struct cred *);
	void (*cleanup)(struct subprocess_info *);
	void *data;
};

typedef phys_addr_t resource_size_t;

struct resource {
	resource_size_t start;
	resource_size_t end;
	const char *name;
	long unsigned int flags;
	long unsigned int desc;
	struct resource *parent;
	struct resource *sibling;
	struct resource *child;
};

typedef u64 async_cookie_t;

typedef void (*async_func_t)(void *, async_cookie_t);

struct async_domain {
	struct list_head pending;
	unsigned int registered: 1;
};

struct hash {
	int ino;
	int minor;
	int major;
	umode_t mode;
	struct hash *next;
	char name[4098];
};

struct dir_entry {
	struct list_head list;
	char *name;
	time64_t mtime;
};

enum state {
	Start = 0,
	Collect = 1,
	GotHeader = 2,
	SkipIt = 3,
	GotName = 4,
	CopyFile = 5,
	GotSymlink = 6,
	Reset = 7,
};

typedef int (*decompress_fn)(unsigned char *, long int, long int (*)(void *, long unsigned int), long int (*)(void *, long unsigned int), unsigned char *, long int *, void (*)(char *));

enum key_being_used_for {
	VERIFYING_MODULE_SIGNATURE = 0,
	VERIFYING_FIRMWARE_SIGNATURE = 1,
	VERIFYING_KEXEC_PE_SIGNATURE = 2,
	VERIFYING_KEY_SIGNATURE = 3,
	VERIFYING_KEY_SELF_SIGNATURE = 4,
	VERIFYING_UNSPECIFIED_SIGNATURE = 5,
	NR__KEY_BEING_USED_FOR = 6,
};

enum ucount_type {
	UCOUNT_USER_NAMESPACES = 0,
	UCOUNT_PID_NAMESPACES = 1,
	UCOUNT_UTS_NAMESPACES = 2,
	UCOUNT_IPC_NAMESPACES = 3,
	UCOUNT_NET_NAMESPACES = 4,
	UCOUNT_MNT_NAMESPACES = 5,
	UCOUNT_CGROUP_NAMESPACES = 6,
	UCOUNT_TIME_NAMESPACES = 7,
	UCOUNT_INOTIFY_INSTANCES = 8,
	UCOUNT_INOTIFY_WATCHES = 9,
	UCOUNT_FANOTIFY_GROUPS = 10,
	UCOUNT_FANOTIFY_MARKS = 11,
	UCOUNT_RLIMIT_NPROC = 12,
	UCOUNT_RLIMIT_MSGQUEUE = 13,
	UCOUNT_RLIMIT_SIGPENDING = 14,
	UCOUNT_RLIMIT_MEMLOCK = 15,
	UCOUNT_COUNTS = 16,
};

enum audit_ntp_type {
	AUDIT_NTP_OFFSET = 0,
	AUDIT_NTP_FREQ = 1,
	AUDIT_NTP_STATUS = 2,
	AUDIT_NTP_TAI = 3,
	AUDIT_NTP_TICK = 4,
	AUDIT_NTP_ADJUST = 5,
	AUDIT_NTP_NVALS = 6,
};

struct cpu_spec;

typedef void (*cpu_setup_t)(long unsigned int, struct cpu_spec *);

enum powerpc_pmc_type {
	PPC_PMC_DEFAULT = 0,
	PPC_PMC_IBM = 1,
	PPC_PMC_PA6T = 2,
	PPC_PMC_G4 = 3,
};

typedef void (*cpu_restore_t)();

struct cpu_spec {
	unsigned int pvr_mask;
	unsigned int pvr_value;
	char *cpu_name;
	long unsigned int cpu_features;
	unsigned int cpu_user_features;
	unsigned int cpu_user_features2;
	unsigned int mmu_features;
	unsigned int icache_bsize;
	unsigned int dcache_bsize;
	void (*cpu_down_flush)();
	unsigned int num_pmcs;
	enum powerpc_pmc_type pmc_type;
	cpu_setup_t cpu_setup;
	cpu_restore_t cpu_restore;
	char *oprofile_cpu_type;
	char *platform;
	int (*machine_check)(struct pt_regs *);
	long int (*machine_check_early)(struct pt_regs *);
};

typedef __kernel_long_t __kernel_off_t;

typedef __kernel_off_t off_t;

enum {
	FW_FEATURE_PSERIES_POSSIBLE = 3479175167,
	FW_FEATURE_PSERIES_ALWAYS = 0,
	FW_FEATURE_POWERNV_POSSIBLE = 268435456,
	FW_FEATURE_POWERNV_ALWAYS = 0,
	FW_FEATURE_PS3_POSSIBLE = 12582912,
	FW_FEATURE_PS3_ALWAYS = 12582912,
	FW_FEATURE_NATIVE_POSSIBLE = 0,
	FW_FEATURE_NATIVE_ALWAYS = 0,
	FW_FEATURE_POSSIBLE = 3747610623,
	FW_FEATURE_ALWAYS = 0,
};

enum {
	PER_LINUX = 0,
	PER_LINUX_32BIT = 8388608,
	PER_LINUX_FDPIC = 524288,
	PER_SVR4 = 68157441,
	PER_SVR3 = 83886082,
	PER_SCOSVR3 = 117440515,
	PER_OSR5 = 100663299,
	PER_WYSEV386 = 83886084,
	PER_ISCR4 = 67108869,
	PER_BSD = 6,
	PER_SUNOS = 67108870,
	PER_XENIX = 83886087,
	PER_LINUX32 = 8,
	PER_LINUX32_3GB = 134217736,
	PER_IRIX32 = 67108873,
	PER_IRIXN32 = 67108874,
	PER_IRIX64 = 67108875,
	PER_RISCOS = 12,
	PER_SOLARIS = 67108877,
	PER_UW7 = 68157454,
	PER_OSF4 = 15,
	PER_HPUX = 16,
	PER_MASK = 255,
};

enum {
	EI_ETYPE_NONE = 0,
	EI_ETYPE_NULL = 1,
	EI_ETYPE_ERRNO = 2,
	EI_ETYPE_ERRNO_NULL = 3,
	EI_ETYPE_TRUE = 4,
};

struct syscall_metadata {
	const char *name;
	int syscall_nr;
	int nb_args;
	const char **types;
	const char **args;
	struct list_head enter_fields;
	struct trace_event_call *enter_event;
	struct trace_event_call *exit_event;
};

enum {
	MMU_FTRS_POSSIBLE = 2113994305,
};

enum ctx_state {
	CONTEXT_DISABLED = 4294967295,
	CONTEXT_KERNEL = 0,
	CONTEXT_USER = 1,
	CONTEXT_GUEST = 2,
};

struct context_tracking {
	bool active;
	int recursion;
	enum ctx_state state;
};

typedef int pci_power_t;

struct pci_vpd {
	struct mutex lock;
	unsigned int len;
	u8 cap;
};

struct pci_dev_extended_rh {};

struct pci_slot;

struct aer_stats;

struct rcec_ea;

struct pci_driver;

struct pcie_link_state;

struct pci_sriov;

struct pci_p2pdma;

struct pci_dev {
	struct list_head bus_list;
	struct pci_bus *bus;
	struct pci_bus *subordinate;
	void *sysdata;
	struct proc_dir_entry *procent;
	struct pci_slot *slot;
	unsigned int devfn;
	short unsigned int vendor;
	short unsigned int device;
	short unsigned int subsystem_vendor;
	short unsigned int subsystem_device;
	unsigned int class;
	u8 revision;
	u8 hdr_type;
	u16 aer_cap;
	struct aer_stats *aer_stats;
	struct rcec_ea *rcec_ea;
	struct pci_dev *rcec;
	u32 devcap;
	u8 pcie_cap;
	u8 msi_cap;
	u8 msix_cap;
	u8 pcie_mpss: 3;
	u8 rom_base_reg;
	u8 pin;
	u16 pcie_flags_reg;
	long unsigned int *dma_alias_mask;
	struct pci_driver *driver;
	u64 dma_mask;
	struct device_dma_parameters dma_parms;
	pci_power_t current_state;
	unsigned int imm_ready: 1;
	u8 pm_cap;
	unsigned int pme_support: 5;
	unsigned int pme_poll: 1;
	unsigned int d1_support: 1;
	unsigned int d2_support: 1;
	unsigned int no_d1d2: 1;
	unsigned int no_d3cold: 1;
	unsigned int bridge_d3: 1;
	unsigned int d3cold_allowed: 1;
	unsigned int mmio_always_on: 1;
	unsigned int wakeup_prepared: 1;
	unsigned int skip_bus_pm: 1;
	unsigned int ignore_hotplug: 1;
	unsigned int hotplug_user_indicators: 1;
	unsigned int clear_retrain_link: 1;
	unsigned int d3hot_delay;
	unsigned int d3cold_delay;
	struct pcie_link_state *link_state;
	unsigned int ltr_path: 1;
	u16 l1ss;
	unsigned int pasid_no_tlp: 1;
	unsigned int eetlp_prefix_path: 1;
	pci_channel_state_t error_state;
	struct device dev;
	int cfg_size;
	unsigned int irq;
	struct resource resource[17];
	bool match_driver;
	unsigned int transparent: 1;
	unsigned int io_window: 1;
	unsigned int pref_window: 1;
	unsigned int pref_64_window: 1;
	unsigned int multifunction: 1;
	unsigned int is_busmaster: 1;
	unsigned int no_msi: 1;
	unsigned int no_64bit_msi: 1;
	unsigned int block_cfg_access: 1;
	unsigned int broken_parity_status: 1;
	unsigned int irq_reroute_variant: 2;
	unsigned int msi_enabled: 1;
	unsigned int msix_enabled: 1;
	unsigned int ari_enabled: 1;
	unsigned int ats_enabled: 1;
	unsigned int pasid_enabled: 1;
	unsigned int pri_enabled: 1;
	unsigned int is_managed: 1;
	unsigned int needs_freset: 1;
	unsigned int state_saved: 1;
	unsigned int is_physfn: 1;
	unsigned int is_virtfn: 1;
	unsigned int is_hotplug_bridge: 1;
	unsigned int shpc_managed: 1;
	unsigned int is_thunderbolt: 1;
	unsigned int untrusted: 1;
	unsigned int external_facing: 1;
	unsigned int broken_intx_masking: 1;
	unsigned int io_window_1k: 1;
	unsigned int irq_managed: 1;
	unsigned int non_compliant_bars: 1;
	unsigned int is_probed: 1;
	unsigned int link_active_reporting: 1;
	unsigned int no_vf_scan: 1;
	unsigned int no_command_memory: 1;
	unsigned int rom_bar_overlap: 1;
	pci_dev_flags_t dev_flags;
	atomic_t enable_cnt;
	u32 saved_config_space[16];
	struct hlist_head saved_cap_space;
	int rom_attr_enabled;
	struct bin_attribute *res_attr[17];
	struct bin_attribute *res_attr_wc[17];
	const struct attribute_group **msi_irq_groups;
	struct pci_vpd vpd;
	u16 dpc_cap;
	unsigned int dpc_rp_extensions: 1;
	u8 dpc_rp_log_size;
	union {
		struct pci_sriov *sriov;
		struct pci_dev *physfn;
	};
	u16 ats_cap;
	u8 ats_stu;
	u16 pri_cap;
	u32 pri_reqs_alloc;
	unsigned int pasid_required: 1;
	u16 pasid_cap;
	u16 pasid_features;
	struct pci_p2pdma *p2pdma;
	u16 acs_cap;
	phys_addr_t rom;
	size_t romlen;
	char *driver_override;
	long unsigned int priv_flags;
	u8 reset_methods[7];
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	long unsigned int rh_reserved5;
	long unsigned int rh_reserved6;
	long unsigned int rh_reserved7;
	long unsigned int rh_reserved8;
	long unsigned int rh_reserved9;
	long unsigned int rh_reserved10;
	long unsigned int rh_reserved11;
	long unsigned int rh_reserved12;
	long unsigned int rh_reserved13;
	long unsigned int rh_reserved14;
	long unsigned int rh_reserved15;
	long unsigned int rh_reserved16;
	long unsigned int rh_reserved17;
	long unsigned int rh_reserved18;
	long unsigned int rh_reserved19;
	long unsigned int rh_reserved20;
	long unsigned int rh_reserved21;
	long unsigned int rh_reserved22;
	long unsigned int rh_reserved23;
	long unsigned int rh_reserved24;
	size_t pci_dev_extended_size_rh;
	struct pci_dev_extended_rh _rh;
};

struct iommu_table_group;

struct pci_dn {
	int flags;
	int busno;
	int devfn;
	int vendor_id;
	int device_id;
	int class_code;
	struct pci_dn *parent;
	struct pci_controller *phb;
	struct iommu_table_group *table_group;
	int pci_ext_config_space;
	struct eeh_dev *edev;
	unsigned int pe_number;
	u16 vfs_expanded;
	u16 num_vfs;
	unsigned int *pe_num_map;
	bool m64_single_mode;
	int (*m64_map)[6];
	int last_allow_rc;
	int mps;
	struct list_head child_list;
	struct list_head list;
	struct resource holes[6];
};

struct pci_controller_ops {
	void (*dma_dev_setup)(struct pci_dev *);
	void (*dma_bus_setup)(struct pci_bus *);
	bool (*iommu_bypass_supported)(struct pci_dev *, u64);
	int (*probe_mode)(struct pci_bus *);
	bool (*enable_device_hook)(struct pci_dev *);
	void (*disable_device)(struct pci_dev *);
	void (*release_device)(struct pci_dev *);
	resource_size_t (*window_alignment)(struct pci_bus *, long unsigned int);
	void (*setup_bridge)(struct pci_bus *, long unsigned int);
	void (*reset_secondary_bus)(struct pci_dev *);
	int (*setup_msi_irqs)(struct pci_dev *, int, int);
	void (*teardown_msi_irqs)(struct pci_dev *);
	void (*shutdown)(struct pci_controller *);
};

struct pci_ops;

struct pci_controller {
	struct pci_bus *bus;
	char is_dynamic;
	int node;
	struct device_node *dn;
	struct list_head list_node;
	struct device *parent;
	int first_busno;
	int last_busno;
	int self_busno;
	struct resource busn;
	void *io_base_virt;
	void *io_base_alloc;
	resource_size_t io_base_phys;
	resource_size_t pci_io_size;
	resource_size_t isa_mem_phys;
	resource_size_t isa_mem_size;
	struct pci_controller_ops controller_ops;
	struct pci_ops *ops;
	unsigned int *cfg_addr;
	void *cfg_data;
	u32 indirect_type;
	struct resource io_resource;
	struct resource mem_resources[3];
	resource_size_t mem_offset[3];
	int global_number;
	resource_size_t dma_window_base_cur;
	resource_size_t dma_window_size;
	long unsigned int buid;
	struct pci_dn *pci_data;
	void *private_data;
};

struct pci_bus {
	struct list_head node;
	struct pci_bus *parent;
	struct list_head children;
	struct list_head devices;
	struct pci_dev *self;
	struct list_head slots;
	struct resource *resource[4];
	struct list_head resources;
	struct resource busn_res;
	struct pci_ops *ops;
	void *sysdata;
	struct proc_dir_entry *procdir;
	unsigned char number;
	unsigned char primary;
	unsigned char max_bus_speed;
	unsigned char cur_bus_speed;
	char name[48];
	short unsigned int bridge_ctl;
	pci_bus_flags_t bus_flags;
	struct device *bridge;
	struct device dev;
	struct bin_attribute *legacy_io;
	struct bin_attribute *legacy_mem;
	unsigned int is_added: 1;
	unsigned int unsafe_warn: 1;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	long unsigned int rh_reserved5;
	long unsigned int rh_reserved6;
	long unsigned int rh_reserved7;
	long unsigned int rh_reserved8;
};

struct arch_msi_msg_addr_lo {
	u32 address_lo;
};

typedef struct arch_msi_msg_addr_lo arch_msi_msg_addr_lo_t;

struct arch_msi_msg_addr_hi {
	u32 address_hi;
};

typedef struct arch_msi_msg_addr_hi arch_msi_msg_addr_hi_t;

struct arch_msi_msg_data {
	u32 data;
};

typedef struct arch_msi_msg_data arch_msi_msg_data_t;

struct msi_msg {
	union {
		u32 address_lo;
		arch_msi_msg_addr_lo_t arch_addr_lo;
	};
	union {
		u32 address_hi;
		arch_msi_msg_addr_hi_t arch_addr_hi;
	};
	union {
		u32 data;
		arch_msi_msg_data_t arch_data;
	};
};

struct platform_msi_priv_data;

struct platform_msi_desc {
	struct platform_msi_priv_data *msi_priv_data;
	u16 msi_index;
};

struct fsl_mc_msi_desc {
	u16 msi_index;
};

struct ti_sci_inta_msi_desc {
	u16 dev_index;
};

struct irq_affinity_desc;

struct msi_desc {
	struct list_head list;
	unsigned int irq;
	unsigned int nvec_used;
	struct device *dev;
	struct msi_msg msg;
	struct irq_affinity_desc *affinity;
	void (*write_msi_msg)(struct msi_desc *, void *);
	void *write_msi_msg_data;
	union {
		struct {
			union {
				u32 msi_mask;
				u32 msix_ctrl;
			};
			struct {
				u8 is_msix: 1;
				u8 multiple: 3;
				u8 multi_cap: 3;
				u8 can_mask: 1;
				u8 is_64: 1;
				u8 is_virtual: 1;
				u16 entry_nr;
				unsigned int default_irq;
			} msi_attrib;
			union {
				u8 mask_pos;
				void *mask_base;
			};
		};
		struct platform_msi_desc platform;
		struct fsl_mc_msi_desc fsl_mc;
		struct ti_sci_inta_msi_desc inta;
	};
};

typedef struct {
	unsigned int __softirq_pending;
	unsigned int timer_irqs_event;
	unsigned int broadcast_irqs_event;
	unsigned int timer_irqs_others;
	unsigned int pmu_irqs;
	unsigned int mce_exceptions;
	unsigned int spurious_irqs;
	unsigned int sreset_irqs;
	unsigned int soft_nmi_irqs;
	unsigned int doorbell_irqs;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
} irq_cpustat_t;

struct irq_affinity_desc {
	struct cpumask mask;
	unsigned int is_managed: 1;
};

enum cpu_usage_stat {
	CPUTIME_USER = 0,
	CPUTIME_NICE = 1,
	CPUTIME_SYSTEM = 2,
	CPUTIME_SOFTIRQ = 3,
	CPUTIME_IRQ = 4,
	CPUTIME_IDLE = 5,
	CPUTIME_IOWAIT = 6,
	CPUTIME_STEAL = 7,
	CPUTIME_GUEST = 8,
	CPUTIME_GUEST_NICE = 9,
	NR_STATS = 10,
};

struct pci_device_id {
	__u32 vendor;
	__u32 device;
	__u32 subvendor;
	__u32 subdevice;
	__u32 class;
	__u32 class_mask;
	kernel_ulong_t driver_data;
	__u32 override_only;
};

struct hotplug_slot;

struct pci_slot {
	struct pci_bus *bus;
	struct list_head list;
	struct hotplug_slot *hotplug;
	unsigned char number;
	struct kobject kobj;
};

struct pci_dynids {
	spinlock_t lock;
	struct list_head list;
};

struct pci_error_handlers;

struct pci_driver {
	struct list_head node;
	const char *name;
	const struct pci_device_id *id_table;
	int (*probe)(struct pci_dev *, const struct pci_device_id *);
	void (*remove)(struct pci_dev *);
	int (*suspend)(struct pci_dev *, pm_message_t);
	int (*resume)(struct pci_dev *);
	void (*shutdown)(struct pci_dev *);
	int (*sriov_configure)(struct pci_dev *, int);
	int (*sriov_set_msix_vec_count)(struct pci_dev *, int);
	u32 (*sriov_get_vf_total_msix)(struct pci_dev *);
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	const struct pci_error_handlers *err_handler;
	const struct attribute_group **groups;
	const struct attribute_group **dev_groups;
	struct device_driver driver;
	struct pci_dynids dynids;
	bool driver_managed_dma;
	long unsigned int rh_reserved5;
	long unsigned int rh_reserved6;
	long unsigned int rh_reserved7;
	long unsigned int rh_reserved8;
};

struct pci_host_bridge {
	struct device dev;
	struct pci_bus *bus;
	struct pci_ops *ops;
	struct pci_ops *child_ops;
	void *sysdata;
	int busnr;
	int domain_nr;
	struct list_head windows;
	struct list_head dma_ranges;
	u8 (*swizzle_irq)(struct pci_dev *, u8 *);
	int (*map_irq)(const struct pci_dev *, u8, u8);
	void (*release_fn)(struct pci_host_bridge *);
	void *release_data;
	unsigned int ignore_reset_delay: 1;
	unsigned int no_ext_tags: 1;
	unsigned int native_aer: 1;
	unsigned int native_pcie_hotplug: 1;
	unsigned int native_shpc_hotplug: 1;
	unsigned int native_pme: 1;
	unsigned int native_ltr: 1;
	unsigned int native_dpc: 1;
	unsigned int preserve_config: 1;
	unsigned int size_windows: 1;
	unsigned int msi_domain: 1;
	resource_size_t (*align_resource)(struct pci_dev *, const struct resource *, resource_size_t, resource_size_t, resource_size_t);
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long unsigned int private[0];
};

struct pci_ops {
	int (*add_bus)(struct pci_bus *);
	void (*remove_bus)(struct pci_bus *);
	void * (*map_bus)(struct pci_bus *, unsigned int, int);
	int (*read)(struct pci_bus *, unsigned int, int, int, u32 *);
	int (*write)(struct pci_bus *, unsigned int, int, int, u32);
};

struct pci_error_handlers {
	pci_ers_result_t (*error_detected)(struct pci_dev *, pci_channel_state_t);
	pci_ers_result_t (*mmio_enabled)(struct pci_dev *);
	pci_ers_result_t (*slot_reset)(struct pci_dev *);
	void (*reset_prepare)(struct pci_dev *);
	void (*reset_done)(struct pci_dev *);
	void (*resume)(struct pci_dev *);
};

struct scatterlist {
	long unsigned int page_link;
	unsigned int offset;
	unsigned int length;
	dma_addr_t dma_address;
	unsigned int dma_length;
	unsigned int dma_flags;
};

struct sg_table {
	struct scatterlist *sgl;
	unsigned int nents;
	unsigned int orig_nents;
};

struct rtc_time;

struct kimage;

struct machdep_calls {
	char *name;
	void (*iommu_save)();
	void (*iommu_restore)();
	long unsigned int (*memory_block_size)();
	void (*dma_set_mask)(struct device *, u64);
	int (*probe)();
	void (*setup_arch)();
	void (*show_cpuinfo)(struct seq_file *);
	void (*show_percpuinfo)(struct seq_file *, int);
	long unsigned int (*get_proc_freq)(unsigned int);
	void (*init_IRQ)();
	unsigned int (*get_irq)();
	void (*pcibios_fixup)();
	void (*pci_irq_fixup)(struct pci_dev *);
	int (*pcibios_root_bridge_prepare)(struct pci_host_bridge *);
	void (*discover_phbs)();
	int (*pci_setup_phb)(struct pci_controller *);
	void (*restart)(char *);
	void (*halt)();
	void (*panic)(char *);
	long int (*time_init)();
	int (*set_rtc_time)(struct rtc_time *);
	void (*get_rtc_time)(struct rtc_time *);
	time64_t (*get_boot_time)();
	unsigned char (*rtc_read_val)(int);
	void (*rtc_write_val)(int, unsigned char);
	void (*calibrate_decr)();
	void (*progress)(char *, short unsigned int);
	void (*log_error)(char *, unsigned int, int);
	unsigned char (*nvram_read_val)(int);
	void (*nvram_write_val)(int, unsigned char);
	ssize_t (*nvram_write)(char *, size_t, loff_t *);
	ssize_t (*nvram_read)(char *, size_t, loff_t *);
	ssize_t (*nvram_size)();
	void (*nvram_sync)();
	int (*system_reset_exception)(struct pt_regs *);
	int (*machine_check_exception)(struct pt_regs *);
	int (*handle_hmi_exception)(struct pt_regs *);
	int (*hmi_exception_early)(struct pt_regs *);
	long int (*machine_check_early)(struct pt_regs *);
	bool (*mce_check_early_recovery)(struct pt_regs *);
	long int (*feature_call)(unsigned int, ...);
	int (*pci_get_legacy_ide_irq)(struct pci_dev *, int);
	pgprot_t (*phys_mem_access_prot)(struct file *, long unsigned int, long unsigned int, pgprot_t);
	void (*power_save)();
	void (*enable_pmcs)();
	int (*set_dabr)(long unsigned int, long unsigned int);
	int (*set_dawr)(int, long unsigned int, long unsigned int);
	int (*pci_exclude_device)(struct pci_controller *, unsigned char, unsigned char);
	void (*pcibios_fixup_resources)(struct pci_dev *);
	void (*pcibios_fixup_bus)(struct pci_bus *);
	void (*pcibios_fixup_phb)(struct pci_controller *);
	void (*pcibios_bus_add_device)(struct pci_dev *);
	resource_size_t (*pcibios_default_alignment)();
	void (*pcibios_fixup_sriov)(struct pci_dev *);
	resource_size_t (*pcibios_iov_resource_alignment)(struct pci_dev *, int);
	int (*pcibios_sriov_enable)(struct pci_dev *, u16);
	int (*pcibios_sriov_disable)(struct pci_dev *);
	void (*machine_shutdown)();
	void (*kexec_cpu_down)(int, int);
	int (*machine_kexec_prepare)(struct kimage *);
	void (*machine_kexec)(struct kimage *);
	void (*suspend_disable_irqs)();
	void (*suspend_enable_irqs)();
	ssize_t (*cpu_probe)(const char *, size_t);
	ssize_t (*cpu_release)(const char *, size_t);
	int (*get_random_seed)(long unsigned int *);
};

struct interrupt_state {};

enum kvm_bus {
	KVM_MMIO_BUS = 0,
	KVM_PIO_BUS = 1,
	KVM_VIRTIO_CCW_NOTIFY_BUS = 2,
	KVM_FAST_MMIO_BUS = 3,
	KVM_NR_BUSES = 4,
};

enum ppc_dbell {
	PPC_DBELL = 0,
	PPC_DBELL_CRIT = 1,
	PPC_G_DBELL = 2,
	PPC_G_DBELL_CRIT = 3,
	PPC_G_DBELL_MC = 4,
	PPC_DBELL_SERVER = 5,
};

struct trace_event_raw_ppc64_interrupt_class {
	struct trace_entry ent;
	struct pt_regs *regs;
	char __data[0];
};

struct trace_event_raw_hcall_entry {
	struct trace_entry ent;
	long unsigned int opcode;
	char __data[0];
};

struct trace_event_raw_hcall_exit {
	struct trace_entry ent;
	long unsigned int opcode;
	long int retval;
	char __data[0];
};

struct trace_event_raw_opal_entry {
	struct trace_entry ent;
	long unsigned int opcode;
	char __data[0];
};

struct trace_event_raw_opal_exit {
	struct trace_entry ent;
	long unsigned int opcode;
	long unsigned int retval;
	char __data[0];
};

struct trace_event_raw_hash_fault {
	struct trace_entry ent;
	long unsigned int addr;
	long unsigned int access;
	long unsigned int trap;
	char __data[0];
};

struct trace_event_raw_tlbie {
	struct trace_entry ent;
	long unsigned int lpid;
	long unsigned int local;
	long unsigned int rb;
	long unsigned int rs;
	long unsigned int ric;
	long unsigned int prs;
	long unsigned int r;
	char __data[0];
};

struct trace_event_raw_tlbia {
	struct trace_entry ent;
	long unsigned int id;
	char __data[0];
};

struct trace_event_data_offsets_ppc64_interrupt_class {};

struct trace_event_data_offsets_hcall_entry {};

struct trace_event_data_offsets_hcall_exit {};

struct trace_event_data_offsets_opal_entry {};

struct trace_event_data_offsets_opal_exit {};

struct trace_event_data_offsets_hash_fault {};

struct trace_event_data_offsets_tlbie {};

struct trace_event_data_offsets_tlbia {};

typedef void (*btf_trace_irq_entry)(void *, struct pt_regs *);

typedef void (*btf_trace_irq_exit)(void *, struct pt_regs *);

typedef void (*btf_trace_timer_interrupt_entry)(void *, struct pt_regs *);

typedef void (*btf_trace_timer_interrupt_exit)(void *, struct pt_regs *);

typedef void (*btf_trace_doorbell_entry)(void *, struct pt_regs *);

typedef void (*btf_trace_doorbell_exit)(void *, struct pt_regs *);

typedef void (*btf_trace_hcall_entry)(void *, long unsigned int, long unsigned int *);

typedef void (*btf_trace_hcall_exit)(void *, long unsigned int, long int, long unsigned int *);

typedef void (*btf_trace_opal_entry)(void *, long unsigned int, long unsigned int *);

typedef void (*btf_trace_opal_exit)(void *, long unsigned int, long unsigned int);

typedef void (*btf_trace_hash_fault)(void *, long unsigned int, long unsigned int, long unsigned int);

typedef void (*btf_trace_tlbie)(void *, long unsigned int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, long unsigned int);

typedef void (*btf_trace_tlbia)(void *, long unsigned int);

struct ppc_inst {
	u32 val;
	u32 suffix;
};

struct ppc_emulated_entry {
	const char *name;
	atomic_t val;
};

struct ppc_emulated {
	struct ppc_emulated_entry altivec;
	struct ppc_emulated_entry dcba;
	struct ppc_emulated_entry dcbz;
	struct ppc_emulated_entry fp_pair;
	struct ppc_emulated_entry isel;
	struct ppc_emulated_entry mcrxr;
	struct ppc_emulated_entry mfpvr;
	struct ppc_emulated_entry multiple;
	struct ppc_emulated_entry popcntb;
	struct ppc_emulated_entry spe;
	struct ppc_emulated_entry string;
	struct ppc_emulated_entry sync;
	struct ppc_emulated_entry unaligned;
	struct ppc_emulated_entry vsx;
	struct ppc_emulated_entry mfdscr;
	struct ppc_emulated_entry mtdscr;
	struct ppc_emulated_entry lq_stq;
	struct ppc_emulated_entry lxvw4x;
	struct ppc_emulated_entry lxvh8x;
	struct ppc_emulated_entry lxvd2x;
	struct ppc_emulated_entry lxvb16x;
};

enum instruction_type {
	COMPUTE = 0,
	LOAD = 1,
	LOAD_MULTI = 2,
	LOAD_FP = 3,
	LOAD_VMX = 4,
	LOAD_VSX = 5,
	STORE = 6,
	STORE_MULTI = 7,
	STORE_FP = 8,
	STORE_VMX = 9,
	STORE_VSX = 10,
	LARX = 11,
	STCX = 12,
	BRANCH = 13,
	MFSPR = 14,
	MTSPR = 15,
	CACHEOP = 16,
	BARRIER = 17,
	SYSCALL = 18,
	SYSCALL_VECTORED_0 = 19,
	MFMSR = 20,
	MTMSR = 21,
	RFI = 22,
	INTERRUPT = 23,
	UNKNOWN = 24,
};

struct instruction_op {
	int type;
	int reg;
	long unsigned int val;
	long unsigned int ea;
	int update_reg;
	int spr;
	u32 ccval;
	u32 xerval;
	u8 element_size;
	u8 vsx_flags;
};

typedef struct {
	long unsigned int entry;
	long unsigned int toc;
	long unsigned int env;
} func_descr_t;

typedef long unsigned int uintptr_t;

typedef u8 uint8_t;

struct sigaltstack {
	void *ss_sp;
	int ss_flags;
	size_t ss_size;
};

typedef struct sigaltstack stack_t;

struct siginfo {
	union {
		struct {
			int si_signo;
			int si_errno;
			int si_code;
			union __sifields _sifields;
		};
		int _si_pad[32];
	};
};

typedef struct siginfo siginfo_t;

struct ksignal {
	struct k_sigaction ka;
	kernel_siginfo_t info;
	int sig;
};

typedef long unsigned int elf_greg_t64;

typedef elf_greg_t64 elf_gregset_t64[48];

typedef elf_gregset_t64 elf_gregset_t;

typedef double elf_fpreg_t;

typedef elf_fpreg_t elf_fpregset_t[33];

typedef __vector128 elf_vrreg_t;

struct sigcontext {
	long unsigned int _unused[4];
	int signal;
	int _pad0;
	long unsigned int handler;
	long unsigned int oldmask;
	struct user_pt_regs *regs;
	elf_gregset_t gp_regs;
	elf_fpregset_t fp_regs;
	elf_vrreg_t *v_regs;
	long int vmx_reserve[101];
};

struct ucontext {
	long unsigned int uc_flags;
	struct ucontext *uc_link;
	stack_t uc_stack;
	sigset_t uc_sigmask;
	sigset_t __unused[15];
	struct sigcontext uc_mcontext;
};

struct rt_sigframe {
	struct ucontext uc;
	struct ucontext uc_transact;
	long unsigned int _unused[2];
	unsigned int tramp[7];
	struct siginfo *pinfo;
	void *puc;
	struct siginfo info;
	char abigap[512];
};

typedef void (*perf_irq_t)(struct pt_regs *);

struct ppc_cache_info {
	u32 size;
	u32 line_size;
	u32 block_size;
	u32 log_block_size;
	u32 blocks_per_page;
	u32 sets;
	u32 assoc;
};

struct ppc64_caches {
	struct ppc_cache_info l1d;
	struct ppc_cache_info l1i;
	struct ppc_cache_info l2;
	struct ppc_cache_info l3;
};

struct timens_offset {
	s64 sec;
	u64 nsec;
};

enum vm_fault_reason {
	VM_FAULT_OOM = 1,
	VM_FAULT_SIGBUS = 2,
	VM_FAULT_MAJOR = 4,
	VM_FAULT_WRITE = 8,
	VM_FAULT_HWPOISON = 16,
	VM_FAULT_HWPOISON_LARGE = 32,
	VM_FAULT_SIGSEGV = 64,
	VM_FAULT_NOPAGE = 256,
	VM_FAULT_LOCKED = 512,
	VM_FAULT_RETRY = 1024,
	VM_FAULT_FALLBACK = 2048,
	VM_FAULT_DONE_COW = 4096,
	VM_FAULT_NEEDDSYNC = 8192,
	VM_FAULT_HINDEX_MASK = 983040,
};

struct vm_special_mapping {
	const char *name;
	struct page **pages;
	vm_fault_t (*fault)(const struct vm_special_mapping *, struct vm_area_struct *, struct vm_fault *);
	int (*mremap)(const struct vm_special_mapping *, struct vm_area_struct *);
};

struct timens_offsets {
	struct timespec64 monotonic;
	struct timespec64 boottime;
};

struct time_namespace {
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	struct ns_common ns;
	struct timens_offsets offsets;
	struct page *vvar_page;
	bool frozen_offsets;
};

enum {
	TASKSTATS_CMD_UNSPEC = 0,
	TASKSTATS_CMD_GET = 1,
	TASKSTATS_CMD_NEW = 2,
	__TASKSTATS_CMD_MAX = 3,
};

enum cgroup_bpf_attach_type {
	CGROUP_BPF_ATTACH_TYPE_INVALID = 4294967295,
	CGROUP_INET_INGRESS = 0,
	CGROUP_INET_EGRESS = 1,
	CGROUP_INET_SOCK_CREATE = 2,
	CGROUP_SOCK_OPS = 3,
	CGROUP_DEVICE = 4,
	CGROUP_INET4_BIND = 5,
	CGROUP_INET6_BIND = 6,
	CGROUP_INET4_CONNECT = 7,
	CGROUP_INET6_CONNECT = 8,
	CGROUP_INET4_POST_BIND = 9,
	CGROUP_INET6_POST_BIND = 10,
	CGROUP_UDP4_SENDMSG = 11,
	CGROUP_UDP6_SENDMSG = 12,
	CGROUP_SYSCTL = 13,
	CGROUP_UDP4_RECVMSG = 14,
	CGROUP_UDP6_RECVMSG = 15,
	CGROUP_GETSOCKOPT = 16,
	CGROUP_SETSOCKOPT = 17,
	CGROUP_INET4_GETPEERNAME = 18,
	CGROUP_INET6_GETPEERNAME = 19,
	CGROUP_INET4_GETSOCKNAME = 20,
	CGROUP_INET6_GETSOCKNAME = 21,
	CGROUP_INET_SOCK_RELEASE = 22,
	MAX_CGROUP_BPF_ATTACH_TYPE = 23,
};

enum psi_task_count {
	NR_IOWAIT = 0,
	NR_MEMSTALL = 1,
	NR_RUNNING = 2,
	NR_ONCPU = 3,
	NR_PSI_TASK_COUNTS = 4,
};

enum psi_states {
	PSI_IO_SOME = 0,
	PSI_IO_FULL = 1,
	PSI_MEM_SOME = 2,
	PSI_MEM_FULL = 3,
	PSI_CPU_SOME = 4,
	PSI_CPU_FULL = 5,
	PSI_NONIDLE = 6,
	NR_PSI_STATES = 7,
};

enum psi_aggregators {
	PSI_AVGS = 0,
	PSI_POLL = 1,
	NR_PSI_AGGREGATORS = 2,
};

enum cgroup_subsys_id {
	cpuset_cgrp_id = 0,
	cpu_cgrp_id = 1,
	cpuacct_cgrp_id = 2,
	io_cgrp_id = 3,
	memory_cgrp_id = 4,
	devices_cgrp_id = 5,
	freezer_cgrp_id = 6,
	net_cls_cgrp_id = 7,
	perf_event_cgrp_id = 8,
	net_prio_cgrp_id = 9,
	hugetlb_cgrp_id = 10,
	pids_cgrp_id = 11,
	rdma_cgrp_id = 12,
	misc_cgrp_id = 13,
	CGROUP_SUBSYS_COUNT = 14,
};

struct arch_vdso_data {};

struct vdso_timestamp {
	u64 sec;
	u64 nsec;
};

struct vdso_data {
	u32 seq;
	s32 clock_mode;
	u64 cycle_last;
	u64 mask;
	u32 mult;
	u32 shift;
	union {
		struct vdso_timestamp basetime[12];
		struct timens_offset offset[12];
	};
	s32 tz_minuteswest;
	s32 tz_dsttime;
	u32 hrtimer_res;
	u32 __unused;
	struct arch_vdso_data arch_data;
};

struct vdso_arch_data {
	__u8 eye_catcher[16];
	struct {
		__u32 major;
		__u32 minor;
	} version;
	__u32 platform;
	__u32 processor;
	__u64 processorCount;
	__u64 physicalMemorySize;
	__u64 tb_orig_stamp;
	__u64 tb_ticks_per_sec;
	__u64 tb_to_xs;
	__u64 stamp_xsec;
	__u64 tb_update_count;
	__u32 tz_minuteswest;
	__u32 tz_dsttime;
	__u32 dcache_size;
	__u32 dcache_line_size;
	__u32 icache_size;
	__u32 icache_line_size;
	__u32 dcache_block_size;
	__u32 icache_block_size;
	__u32 dcache_log_block_size;
	__u32 icache_log_block_size;
	__u32 syscall_map[15];
	__u32 compat_syscall_map[15];
	struct vdso_data data[2];
};

enum vvar_pages {
	VVAR_DATA_PAGE_OFFSET = 0,
	VVAR_TIMENS_PAGE_OFFSET = 1,
	VVAR_NR_PAGES = 2,
};

typedef struct {
	pte_t pte;
	long unsigned int hidx;
} real_pte_t;

struct mmu_psize_def {
	unsigned int shift;
	int penc[16];
	unsigned int tlbiel;
	long unsigned int avpnm;
	long unsigned int h_rpt_pgsize;
	union {
		long unsigned int sllp;
		long unsigned int ap;
	};
};

enum die_val {
	DIE_OOPS = 1,
	DIE_IABR_MATCH = 2,
	DIE_DABR_MATCH = 3,
	DIE_BPT = 4,
	DIE_SSTEP = 5,
};

struct ppc64_tlb_batch {
	int active;
	long unsigned int index;
	struct mm_struct *mm;
	real_pte_t pte[192];
	long unsigned int vpn[192];
	unsigned int psize;
	int ssize;
};

struct regbit {
	long unsigned int bit;
	const char *name;
};

enum idle_boot_override {
	IDLE_NO_OVERRIDE = 0,
	IDLE_POWERSAVE_OFF = 1,
};

typedef void (*smp_call_func_t)(void *);

typedef bool (*smp_cond_func_t)(int, void *);

struct smp_ops_t {
	void (*message_pass)(int, int);
	void (*cause_ipi)(int);
	int (*cause_nmi_ipi)(int);
	void (*probe)();
	int (*kick_cpu)(int);
	int (*prepare_cpu)(int);
	void (*setup_cpu)(int);
	void (*bringup_done)();
	void (*take_timebase)();
	void (*give_timebase)();
	int (*cpu_disable)();
	void (*cpu_die)(unsigned int);
	int (*cpu_bootable)(unsigned int);
	void (*cpu_offline_self)();
};

struct device_attribute {
	struct attribute attr;
	ssize_t (*show)(struct device *, struct device_attribute *, char *);
	ssize_t (*store)(struct device *, struct device_attribute *, const char *, size_t);
};

struct node {
	struct device dev;
	struct list_head access_list;
	struct work_struct node_work;
};

struct cpu {
	int node_id;
	int hotpluggable;
	struct device dev;
};

struct kobj_attribute {
	struct attribute attr;
	ssize_t (*show)(struct kobject *, struct kobj_attribute *, char *);
	ssize_t (*store)(struct kobject *, struct kobj_attribute *, const char *, size_t);
};

struct cache_index_dir;

struct cache_dir {
	struct kobject *kobj;
	struct cache_index_dir *index;
};

struct cache;

struct cache_index_dir {
	struct kobject kobj;
	struct cache_index_dir *next;
	struct cache *cache;
};

struct cache {
	struct device_node *ofnode;
	struct cpumask shared_cpu_map;
	int type;
	int level;
	int group_id;
	struct list_head list;
	struct cache *next_local;
};

struct cache_type_info {
	const char *name;
	const char *size_prop;
	const char *line_size_props[2];
	const char *nr_sets_prop;
};

struct timezone {
	int tz_minuteswest;
	int tz_dsttime;
};

enum clocksource_ids {
	CSID_GENERIC = 0,
	CSID_ARM_ARCH_COUNTER = 1,
	CSID_MAX = 2,
};

enum vdso_clock_mode {
	VDSO_CLOCKMODE_NONE = 0,
	VDSO_CLOCKMODE_ARCHTIMER = 1,
	VDSO_CLOCKMODE_MAX = 2,
	VDSO_CLOCKMODE_TIMENS = 2147483647,
};

struct clocksource {
	u64 (*read)(struct clocksource *);
	u64 mask;
	u32 mult;
	u32 shift;
	u64 max_idle_ns;
	u32 maxadj;
	u32 uncertainty_margin;
	u64 max_cycles;
	const char *name;
	struct list_head list;
	int rating;
	enum clocksource_ids id;
	enum vdso_clock_mode vdso_clock_mode;
	long unsigned int flags;
	int (*enable)(struct clocksource *);
	void (*disable)(struct clocksource *);
	void (*suspend)(struct clocksource *);
	void (*resume)(struct clocksource *);
	void (*mark_unstable)(struct clocksource *);
	void (*tick_stable)(struct clocksource *);
	struct module *owner;
};

struct pdev_archdata {
	u64 dma_mask;
	void *priv;
};

enum clock_event_state {
	CLOCK_EVT_STATE_DETACHED = 0,
	CLOCK_EVT_STATE_SHUTDOWN = 1,
	CLOCK_EVT_STATE_PERIODIC = 2,
	CLOCK_EVT_STATE_ONESHOT = 3,
	CLOCK_EVT_STATE_ONESHOT_STOPPED = 4,
};

struct clock_event_device {
	void (*event_handler)(struct clock_event_device *);
	int (*set_next_event)(long unsigned int, struct clock_event_device *);
	int (*set_next_ktime)(ktime_t, struct clock_event_device *);
	ktime_t next_event;
	u64 max_delta_ns;
	u64 min_delta_ns;
	u32 mult;
	u32 shift;
	enum clock_event_state state_use_accessors;
	unsigned int features;
	long unsigned int retries;
	int (*set_state_periodic)(struct clock_event_device *);
	int (*set_state_oneshot)(struct clock_event_device *);
	int (*set_state_oneshot_stopped)(struct clock_event_device *);
	int (*set_state_shutdown)(struct clock_event_device *);
	int (*tick_resume)(struct clock_event_device *);
	void (*broadcast)(const struct cpumask *);
	void (*suspend)(struct clock_event_device *);
	void (*resume)(struct clock_event_device *);
	long unsigned int min_delta_ticks;
	long unsigned int max_delta_ticks;
	const char *name;
	int rating;
	int irq;
	int bound_on;
	const struct cpumask *cpumask;
	struct list_head list;
	struct module *owner;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct div_result {
	u64 result_high;
	u64 result_low;
};

struct kernel_cpustat {
	u64 cpustat[10];
};

struct rtc_time {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};

struct rtc_wkalrm {
	unsigned char enabled;
	unsigned char pending;
	struct rtc_time time;
};

struct rtc_param {
	__u64 param;
	union {
		__u64 uvalue;
		__s64 svalue;
		__u64 ptr;
	};
	__u32 index;
	__u32 __pad;
};

struct rtc_class_ops {
	int (*ioctl)(struct device *, unsigned int, long unsigned int);
	int (*read_time)(struct device *, struct rtc_time *);
	int (*set_time)(struct device *, struct rtc_time *);
	int (*read_alarm)(struct device *, struct rtc_wkalrm *);
	int (*set_alarm)(struct device *, struct rtc_wkalrm *);
	int (*proc)(struct device *, struct seq_file *);
	int (*alarm_irq_enable)(struct device *, unsigned int);
	int (*read_offset)(struct device *, long int *);
	int (*set_offset)(struct device *, long int);
	int (*param_get)(struct device *, struct rtc_param *);
	int (*param_set)(struct device *, struct rtc_param *);
};

struct platform_device_id {
	char name[20];
	kernel_ulong_t driver_data;
};

enum dev_prop_type {
	DEV_PROP_U8 = 0,
	DEV_PROP_U16 = 1,
	DEV_PROP_U32 = 2,
	DEV_PROP_U64 = 3,
	DEV_PROP_STRING = 4,
	DEV_PROP_REF = 5,
};

struct property_entry {
	const char *name;
	size_t length;
	bool is_inline;
	enum dev_prop_type type;
	union {
		const void *pointer;
		union {
			u8 u8_data[8];
			u16 u16_data[4];
			u32 u32_data[2];
			u64 u64_data[1];
			const char *str[1];
		} value;
	};
};

struct mfd_cell;

struct platform_device {
	const char *name;
	int id;
	bool id_auto;
	struct device dev;
	u64 platform_dma_mask;
	struct device_dma_parameters dma_parms;
	u32 num_resources;
	struct resource *resource;
	const struct platform_device_id *id_entry;
	char *driver_override;
	struct mfd_cell *mfd_cell;
	struct pdev_archdata archdata;
};

struct platform_device_info {
	struct device *parent;
	struct fwnode_handle *fwnode;
	bool of_node_reused;
	const char *name;
	int id;
	const struct resource *res;
	unsigned int num_res;
	const void *data;
	size_t size_data;
	u64 dma_mask;
	const struct property_entry *properties;
};

struct iommu_pool {
	long unsigned int start;
	long unsigned int end;
	long unsigned int hint;
	spinlock_t lock;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct iommu_table_ops;

struct iommu_table {
	long unsigned int it_busno;
	long unsigned int it_size;
	long unsigned int it_indirect_levels;
	long unsigned int it_level_size;
	long unsigned int it_allocated_size;
	long unsigned int it_offset;
	long unsigned int it_base;
	long unsigned int it_index;
	long unsigned int it_type;
	long unsigned int it_blocksize;
	long unsigned int poolsize;
	long unsigned int nr_pools;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct iommu_pool large_pool;
	struct iommu_pool pools[4];
	long unsigned int *it_map;
	long unsigned int it_page_shift;
	struct list_head it_group_list;
	__be64 *it_userspace;
	struct iommu_table_ops *it_ops;
	struct kref it_kref;
	int it_nid;
	long unsigned int it_reserved_start;
	long unsigned int it_reserved_end;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct iommu_table_group_ops;

struct iommu_table_group {
	__u32 tce32_start;
	__u32 tce32_size;
	__u64 pgsizes;
	__u32 max_dynamic_windows_supported;
	__u32 max_levels;
	struct iommu_group *group;
	struct iommu_table *tables[2];
	struct iommu_table_group_ops *ops;
};

typedef __be32 fdt32_t;

struct fdt_header {
	fdt32_t magic;
	fdt32_t totalsize;
	fdt32_t off_dt_struct;
	fdt32_t off_dt_strings;
	fdt32_t off_mem_rsvmap;
	fdt32_t version;
	fdt32_t last_comp_version;
	fdt32_t boot_cpuid_phys;
	fdt32_t size_dt_strings;
	fdt32_t size_dt_struct;
};

struct iommu_table_ops {
	int (*set)(struct iommu_table *, long int, long int, long unsigned int, enum dma_data_direction, long unsigned int);
	int (*xchg_no_kill)(struct iommu_table *, long int, long unsigned int *, enum dma_data_direction *, bool);
	void (*tce_kill)(struct iommu_table *, long unsigned int, long unsigned int, bool);
	__be64 * (*useraddrptr)(struct iommu_table *, long int, bool);
	void (*clear)(struct iommu_table *, long int, long int);
	long unsigned int (*get)(struct iommu_table *, long int);
	void (*flush)(struct iommu_table *);
	void (*free)(struct iommu_table *);
};

struct iommu_table_group_ops {
	long unsigned int (*get_table_size)(__u32, __u64, __u32);
	long int (*create_table)(struct iommu_table_group *, int, __u32, __u64, __u32, struct iommu_table **);
	long int (*set_window)(struct iommu_table_group *, int, struct iommu_table *);
	long int (*unset_window)(struct iommu_table_group *, int);
	void (*take_ownership)(struct iommu_table_group *);
	void (*release_ownership)(struct iommu_table_group *);
};

enum {
	OPAL_P7IOC_NUM_PEST_REGS = 128,
	OPAL_PHB3_NUM_PEST_REGS = 256,
	OPAL_PHB4_NUM_PEST_REGS = 512,
};

struct drmem_lmb {
	u64 base_addr;
	u32 drc_index;
	u32 aa_index;
	u32 flags;
};

struct drmem_lmb_info {
	struct drmem_lmb *lmbs;
	int n_lmbs;
	u64 lmb_size;
};

struct ibm_pa_feature {
	long unsigned int cpu_features;
	long unsigned int mmu_features;
	unsigned int cpu_user_ftrs;
	unsigned int cpu_user_ftrs2;
	unsigned char pabyte;
	unsigned char pabit;
	unsigned char invert;
};

struct feature_property {
	const char *name;
	u32 min_value;
	long unsigned int cpu_feature;
	long unsigned int cpu_user_ftr;
};

enum lockdep_ok {
	LOCKDEP_STILL_OK = 0,
	LOCKDEP_NOW_UNRELIABLE = 1,
};

enum bug_trap_type {
	BUG_TRAP_TYPE_NONE = 0,
	BUG_TRAP_TYPE_WARN = 1,
	BUG_TRAP_TYPE_BUG = 2,
};

typedef int kexec_probe_t(const char *, long unsigned int);

typedef void *kexec_load_t(struct kimage *, char *, long unsigned int, char *, long unsigned int, char *, long unsigned int);

typedef int kexec_cleanup_t(void *);

struct kexec_file_ops {
	kexec_probe_t *probe;
	kexec_load_t *load;
	kexec_cleanup_t *cleanup;
};

struct crash_mem;

struct kimage_arch {
	struct crash_mem *exclude_ranges;
	long unsigned int backup_start;
	void *backup_buf;
	void *fdt;
};

struct crash_mem_range {
	u64 start;
	u64 end;
};

struct crash_mem {
	unsigned int max_nr_ranges;
	unsigned int nr_ranges;
	struct crash_mem_range ranges[0];
};

typedef long unsigned int kimage_entry_t;

struct kexec_segment {
	union {
		void *buf;
		void *kbuf;
	};
	size_t bufsz;
	long unsigned int mem;
	size_t memsz;
};

struct purgatory_info {
	const Elf64_Ehdr *ehdr;
	Elf64_Shdr *sechdrs;
	void *purgatory_buf;
};

struct kimage {
	kimage_entry_t head;
	kimage_entry_t *entry;
	kimage_entry_t *last_entry;
	long unsigned int start;
	struct page *control_code_page;
	struct page *swap_page;
	void *vmcoreinfo_data_copy;
	long unsigned int nr_segments;
	struct kexec_segment segment[16];
	struct list_head control_pages;
	struct list_head dest_pages;
	struct list_head unusable_pages;
	long unsigned int control_page;
	unsigned int type: 1;
	unsigned int preserve_context: 1;
	unsigned int file_mode: 1;
	struct kimage_arch arch;
	void *kernel_buf;
	long unsigned int kernel_buf_len;
	void *initrd_buf;
	long unsigned int initrd_buf_len;
	char *cmdline_buf;
	long unsigned int cmdline_buf_len;
	const struct kexec_file_ops *fops;
	void *image_loader_data;
	struct purgatory_info purgatory_info;
	void *ima_buffer;
	phys_addr_t ima_buffer_addr;
	size_t ima_buffer_size;
	void *elf_headers;
	long unsigned int elf_headers_sz;
	long unsigned int elf_load_addr;
};

enum con_flush_mode {
	CONSOLE_FLUSH_PENDING = 0,
	CONSOLE_REPLAY_ALL = 1,
};

enum kmsg_dump_reason {
	KMSG_DUMP_UNDEF = 0,
	KMSG_DUMP_PANIC = 1,
	KMSG_DUMP_OOPS = 2,
	KMSG_DUMP_EMERG = 3,
	KMSG_DUMP_SHUTDOWN = 4,
	KMSG_DUMP_MAX = 5,
};

struct interrupt_nmi_state {
	u8 irq_soft_mask;
	u8 irq_happened;
	u8 ftrace_enabled;
	u64 softe;
};

struct atomic_notifier_head {
	spinlock_t lock;
	struct notifier_block *head;
};

struct screen_info {
	__u8 orig_x;
	__u8 orig_y;
	__u16 ext_mem_k;
	__u16 orig_video_page;
	__u8 orig_video_mode;
	__u8 orig_video_cols;
	__u8 flags;
	__u8 unused2;
	__u16 orig_video_ega_bx;
	__u16 unused3;
	__u8 orig_video_lines;
	__u8 orig_video_isVGA;
	__u16 orig_video_points;
	__u16 lfb_width;
	__u16 lfb_height;
	__u16 lfb_depth;
	__u32 lfb_base;
	__u32 lfb_size;
	__u16 cl_magic;
	__u16 cl_offset;
	__u16 lfb_linelength;
	__u8 red_size;
	__u8 red_pos;
	__u8 green_size;
	__u8 green_pos;
	__u8 blue_size;
	__u8 blue_pos;
	__u8 rsvd_size;
	__u8 rsvd_pos;
	__u16 vesapm_seg;
	__u16 vesapm_off;
	__u16 pages;
	__u16 vesa_attributes;
	__u32 capabilities;
	__u32 ext_lfb_base;
	__u8 _reserved[2];
} __attribute__((packed));

struct serial_struct {
	int type;
	int line;
	unsigned int port;
	int irq;
	int flags;
	int xmit_fifo_size;
	int custom_divisor;
	int baud_base;
	short unsigned int close_delay;
	char io_type;
	char reserved_char[1];
	int hub6;
	short unsigned int closing_wait;
	short unsigned int closing_wait2;
	unsigned char *iomem_base;
	short unsigned int iomem_reg_shift;
	unsigned int port_high;
	long unsigned int iomap_base;
};

struct serial_icounter_struct {
	int cts;
	int dsr;
	int rng;
	int dcd;
	int rx;
	int tx;
	int frame;
	int overrun;
	int parity;
	int brk;
	int buf_overrun;
	int reserved[9];
};

enum lockdown_reason {
	LOCKDOWN_NONE = 0,
	LOCKDOWN_MODULE_SIGNATURE = 1,
	LOCKDOWN_DEV_MEM = 2,
	LOCKDOWN_EFI_TEST = 3,
	LOCKDOWN_KEXEC = 4,
	LOCKDOWN_HIBERNATION = 5,
	LOCKDOWN_PCI_ACCESS = 6,
	LOCKDOWN_IOPORT = 7,
	LOCKDOWN_MSR = 8,
	LOCKDOWN_ACPI_TABLES = 9,
	LOCKDOWN_PCMCIA_CIS = 10,
	LOCKDOWN_TIOCSSERIAL = 11,
	LOCKDOWN_MODULE_PARAMETERS = 12,
	LOCKDOWN_MMIOTRACE = 13,
	LOCKDOWN_DEBUGFS = 14,
	LOCKDOWN_XMON_WR = 15,
	LOCKDOWN_BPF_WRITE_USER = 16,
	LOCKDOWN_DBG_WRITE_KERNEL = 17,
	LOCKDOWN_INTEGRITY_MAX = 18,
	LOCKDOWN_KCORE = 19,
	LOCKDOWN_KPROBES = 20,
	LOCKDOWN_BPF_READ_KERNEL = 21,
	LOCKDOWN_DBG_READ_KERNEL = 22,
	LOCKDOWN_PERF = 23,
	LOCKDOWN_TRACEFS = 24,
	LOCKDOWN_XMON_RW = 25,
	LOCKDOWN_XFRM_SECRET = 26,
	LOCKDOWN_CONFIDENTIALITY_MAX = 27,
};

typedef unsigned int uint;

struct console {
	char name[16];
	void (*write)(struct console *, const char *, unsigned int);
	int (*read)(struct console *, char *, unsigned int);
	struct tty_driver * (*device)(struct console *, int *);
	void (*unblank)();
	int (*setup)(struct console *, char *);
	int (*exit)(struct console *);
	int (*match)(struct console *, char *, int, char *);
	short int flags;
	short int index;
	int cflag;
	uint ispeed;
	uint ospeed;
	u64 seq;
	long unsigned int dropped;
	void *data;
	struct console *next;
};

typedef long int (*syscall_fn)(long int, long int, long int, long int, long int, long int);

struct mem_section_usage {
	long unsigned int subsection_map[1];
	long unsigned int pageblock_flags[0];
};

struct page_ext;

struct mem_section {
	long unsigned int section_mem_map;
	struct mem_section_usage *usage;
	struct page_ext *page_ext;
	long unsigned int pad;
};

struct page_ext {
	long unsigned int flags;
};

typedef bool (*stack_trace_consume_fn)(void *, long unsigned int);

struct ppc_debug_info {
	__u32 version;
	__u32 num_instruction_bps;
	__u32 num_data_bps;
	__u32 num_condition_regs;
	__u32 data_bp_alignment;
	__u32 sizeof_condition;
	__u64 features;
};

struct ppc_hw_breakpoint {
	__u32 version;
	__u32 trigger_type;
	__u32 addr_mode;
	__u32 condition_mode;
	__u64 addr;
	__u64 addr2;
	__u64 condition_value;
};

struct seccomp_data {
	int nr;
	__u32 arch;
	__u64 instruction_pointer;
	__u64 args[6];
};

struct membuf {
	void *p;
	size_t left;
};

struct user_regset;

typedef int user_regset_active_fn(struct task_struct *, const struct user_regset *);

typedef int user_regset_get2_fn(struct task_struct *, const struct user_regset *, struct membuf);

typedef int user_regset_set_fn(struct task_struct *, const struct user_regset *, unsigned int, unsigned int, const void *, const void *);

typedef int user_regset_writeback_fn(struct task_struct *, const struct user_regset *, int);

struct user_regset {
	user_regset_get2_fn *regset_get;
	user_regset_set_fn *set;
	user_regset_active_fn *active;
	user_regset_writeback_fn *writeback;
	unsigned int n;
	unsigned int size;
	unsigned int align;
	unsigned int bias;
	unsigned int core_note_type;
};

struct user_regset_view {
	const char *name;
	const struct user_regset *regsets;
	unsigned int n;
	u32 e_flags;
	u16 e_machine;
	u8 ei_osabi;
};

struct trace_event_raw_sys_enter {
	struct trace_entry ent;
	long int id;
	long unsigned int args[6];
	char __data[0];
};

struct trace_event_raw_sys_exit {
	struct trace_entry ent;
	long int id;
	long int ret;
	char __data[0];
};

struct trace_event_data_offsets_sys_enter {};

struct trace_event_data_offsets_sys_exit {};

typedef void (*btf_trace_sys_enter)(void *, struct pt_regs *, long int);

typedef void (*btf_trace_sys_exit)(void *, struct pt_regs *, long int);

enum powerpc_regset {
	REGSET_GPR = 0,
	REGSET_FPR = 1,
	REGSET_VMX = 2,
	REGSET_VSX = 3,
	REGSET_TM_CGPR = 4,
	REGSET_TM_CFPR = 5,
	REGSET_TM_CVMX = 6,
	REGSET_TM_CVSX = 7,
	REGSET_TM_SPR = 8,
	REGSET_TM_CTAR = 9,
	REGSET_TM_CPPR = 10,
	REGSET_TM_CDSCR = 11,
	REGSET_PPR = 12,
	REGSET_DSCR = 13,
	REGSET_TAR = 14,
	REGSET_EBB = 15,
	REGSET_PMR = 16,
	REGSET_PKEY = 17,
};

struct pt_regs_offset {
	const char *name;
	int offset;
};

typedef u32 compat_ulong_t;

enum perf_type_id {
	PERF_TYPE_HARDWARE = 0,
	PERF_TYPE_SOFTWARE = 1,
	PERF_TYPE_TRACEPOINT = 2,
	PERF_TYPE_HW_CACHE = 3,
	PERF_TYPE_RAW = 4,
	PERF_TYPE_BREAKPOINT = 5,
	PERF_TYPE_MAX = 6,
};

typedef int pcpu_fc_cpu_to_node_fn_t(int);

typedef int pcpu_fc_cpu_distance_fn_t(unsigned int, unsigned int);

struct ppc_pci_io {
	u8 (*readb)(const volatile void *);
	u16 (*readw)(const volatile void *);
	u32 (*readl)(const volatile void *);
	u16 (*readw_be)(const volatile void *);
	u32 (*readl_be)(const volatile void *);
	void (*writeb)(u8, volatile void *);
	void (*writew)(u16, volatile void *);
	void (*writel)(u32, volatile void *);
	void (*writew_be)(u16, volatile void *);
	void (*writel_be)(u32, volatile void *);
	u64 (*readq)(const volatile void *);
	u64 (*readq_be)(const volatile void *);
	void (*writeq)(u64, volatile void *);
	void (*writeq_be)(u64, volatile void *);
	u8 (*inb)(long unsigned int);
	u16 (*inw)(long unsigned int);
	u32 (*inl)(long unsigned int);
	void (*outb)(u8, long unsigned int);
	void (*outw)(u16, long unsigned int);
	void (*outl)(u32, long unsigned int);
	void (*readsb)(const volatile void *, void *, long unsigned int);
	void (*readsw)(const volatile void *, void *, long unsigned int);
	void (*readsl)(const volatile void *, void *, long unsigned int);
	void (*writesb)(volatile void *, const void *, long unsigned int);
	void (*writesw)(volatile void *, const void *, long unsigned int);
	void (*writesl)(volatile void *, const void *, long unsigned int);
	void (*insb)(long unsigned int, void *, long unsigned int);
	void (*insw)(long unsigned int, void *, long unsigned int);
	void (*insl)(long unsigned int, void *, long unsigned int);
	void (*outsb)(long unsigned int, const void *, long unsigned int);
	void (*outsw)(long unsigned int, const void *, long unsigned int);
	void (*outsl)(long unsigned int, const void *, long unsigned int);
	void (*memset_io)(volatile void *, int, long unsigned int);
	void (*memcpy_fromio)(void *, const volatile void *, long unsigned int);
	void (*memcpy_toio)(volatile void *, const void *, long unsigned int);
};

enum memblock_flags {
	MEMBLOCK_NONE = 0,
	MEMBLOCK_HOTPLUG = 1,
	MEMBLOCK_MIRROR = 2,
	MEMBLOCK_NOMAP = 4,
	MEMBLOCK_DRIVER_MANAGED = 8,
};

struct memblock_region {
	phys_addr_t base;
	phys_addr_t size;
	enum memblock_flags flags;
	int nid;
};

struct memblock_type {
	long unsigned int cnt;
	long unsigned int max;
	phys_addr_t total_size;
	struct memblock_region *regions;
	char *name;
};

struct memblock {
	bool bottom_up;
	phys_addr_t current_limit;
	struct memblock_type memory;
	struct memblock_type reserved;
};

struct kmsg_dump_iter {
	u64 cur_seq;
	u64 next_seq;
};

struct kmsg_dumper {
	struct list_head list;
	void (*dump)(struct kmsg_dumper *, enum kmsg_dump_reason);
	enum kmsg_dump_reason max_reason;
	bool registered;
};

enum pstore_type_id {
	PSTORE_TYPE_DMESG = 0,
	PSTORE_TYPE_MCE = 1,
	PSTORE_TYPE_CONSOLE = 2,
	PSTORE_TYPE_FTRACE = 3,
	PSTORE_TYPE_PPC_RTAS = 4,
	PSTORE_TYPE_PPC_OF = 5,
	PSTORE_TYPE_PPC_COMMON = 6,
	PSTORE_TYPE_PMSG = 7,
	PSTORE_TYPE_PPC_OPAL = 8,
	PSTORE_TYPE_MAX = 9,
};

struct pstore_info;

struct pstore_record {
	struct pstore_info *psi;
	enum pstore_type_id type;
	u64 id;
	struct timespec64 time;
	char *buf;
	ssize_t size;
	ssize_t ecc_notice_size;
	int count;
	enum kmsg_dump_reason reason;
	unsigned int part;
	bool compressed;
};

struct pstore_info {
	struct module *owner;
	const char *name;
	spinlock_t buf_lock;
	char *buf;
	size_t bufsize;
	struct mutex read_mutex;
	int flags;
	int max_reason;
	void *data;
	int (*open)(struct pstore_info *);
	int (*close)(struct pstore_info *);
	ssize_t (*read)(struct pstore_record *);
	int (*write)(struct pstore_record *);
	int (*write_user)(struct pstore_record *, const char *);
	int (*erase)(struct pstore_record *);
};

typedef unsigned char Byte;

typedef long unsigned int uLong;

struct internal_state;

struct z_stream_s {
	const Byte *next_in;
	uLong avail_in;
	uLong total_in;
	Byte *next_out;
	uLong avail_out;
	uLong total_out;
	char *msg;
	struct internal_state *state;
	void *workspace;
	int data_type;
	uLong adler;
	uLong reserved;
};

struct internal_state {
	int dummy;
};

typedef struct z_stream_s z_stream;

typedef z_stream *z_streamp;

struct err_log_info {
	__be32 error_type;
	__be32 seq_num;
};

struct nvram_os_partition {
	const char *name;
	int req_size;
	int min_size;
	long int size;
	long int index;
	bool os_partition;
};

struct oops_log_info {
	__be16 version;
	__be16 report_length;
	__be64 timestamp;
} __attribute__((packed));

struct nvram_header {
	unsigned char signature;
	unsigned char checksum;
	short unsigned int length;
	char name[12];
};

struct nvram_partition {
	struct list_head partition;
	struct nvram_header header;
	unsigned int index;
};

enum hrtimer_mode {
	HRTIMER_MODE_ABS = 0,
	HRTIMER_MODE_REL = 1,
	HRTIMER_MODE_PINNED = 2,
	HRTIMER_MODE_SOFT = 4,
	HRTIMER_MODE_HARD = 8,
	HRTIMER_MODE_ABS_PINNED = 2,
	HRTIMER_MODE_REL_PINNED = 3,
	HRTIMER_MODE_ABS_SOFT = 4,
	HRTIMER_MODE_REL_SOFT = 5,
	HRTIMER_MODE_ABS_PINNED_SOFT = 6,
	HRTIMER_MODE_REL_PINNED_SOFT = 7,
	HRTIMER_MODE_ABS_HARD = 8,
	HRTIMER_MODE_REL_HARD = 9,
	HRTIMER_MODE_ABS_PINNED_HARD = 10,
	HRTIMER_MODE_REL_PINNED_HARD = 11,
};

struct die_args {
	struct pt_regs *regs;
	const char *str;
	long int err;
	int trapnr;
	int signr;
};

enum {
	HW_BREAKPOINT_EMPTY = 0,
	HW_BREAKPOINT_R = 1,
	HW_BREAKPOINT_W = 2,
	HW_BREAKPOINT_RW = 3,
	HW_BREAKPOINT_X = 4,
	HW_BREAKPOINT_INVALID = 7,
};

enum bp_type_idx {
	TYPE_INST = 0,
	TYPE_DATA = 1,
	TYPE_MAX = 2,
};

struct breakpoint {
	struct list_head list;
	struct perf_event *bp;
	bool ptrace_bp;
};

struct mce_error_info {
	enum MCE_ErrorType error_type: 8;
	union {
		enum MCE_UeErrorType ue_error_type: 8;
		enum MCE_SlbErrorType slb_error_type: 8;
		enum MCE_EratErrorType erat_error_type: 8;
		enum MCE_TlbErrorType tlb_error_type: 8;
		enum MCE_UserErrorType user_error_type: 8;
		enum MCE_RaErrorType ra_error_type: 8;
		enum MCE_LinkErrorType link_error_type: 8;
	} u;
	enum MCE_Severity severity: 8;
	enum MCE_Initiator initiator: 8;
	enum MCE_ErrorClass error_class: 8;
	bool sync_error;
	bool ignore_event;
};

enum {
	WORK_STRUCT_PENDING_BIT = 0,
	WORK_STRUCT_INACTIVE_BIT = 1,
	WORK_STRUCT_PWQ_BIT = 2,
	WORK_STRUCT_LINKED_BIT = 3,
	WORK_STRUCT_COLOR_SHIFT = 4,
	WORK_STRUCT_COLOR_BITS = 4,
	WORK_STRUCT_PENDING = 1,
	WORK_STRUCT_INACTIVE = 2,
	WORK_STRUCT_PWQ = 4,
	WORK_STRUCT_LINKED = 8,
	WORK_STRUCT_STATIC = 0,
	WORK_NR_COLORS = 16,
	WORK_CPU_UNBOUND = 2048,
	WORK_STRUCT_FLAG_BITS = 8,
	WORK_OFFQ_FLAG_BASE = 4,
	__WORK_OFFQ_CANCELING = 4,
	WORK_OFFQ_CANCELING = 16,
	WORK_OFFQ_FLAG_BITS = 1,
	WORK_OFFQ_POOL_SHIFT = 5,
	WORK_OFFQ_LEFT = 59,
	WORK_OFFQ_POOL_BITS = 31,
	WORK_OFFQ_POOL_NONE = 2147483647,
	WORK_STRUCT_FLAG_MASK = 255,
	WORK_STRUCT_WQ_DATA_MASK = 4294967040,
	WORK_STRUCT_NO_POOL = 4294967264,
	WORK_BUSY_PENDING = 1,
	WORK_BUSY_RUNNING = 2,
	WORKER_DESC_LEN = 24,
};

enum {
	DTRIG_UNKNOWN = 0,
	DTRIG_VECTOR_CI = 1,
	DTRIG_SUSPEND_ESCAPE = 2,
};

enum {
	TLB_INVAL_SCOPE_GLOBAL = 0,
	TLB_INVAL_SCOPE_LPID = 1,
};

struct mce_ierror_table {
	long unsigned int srr1_mask;
	long unsigned int srr1_value;
	bool nip_valid;
	unsigned int error_type;
	unsigned int error_subtype;
	unsigned int error_class;
	unsigned int initiator;
	unsigned int severity;
	bool sync_error;
};

struct mce_derror_table {
	long unsigned int dsisr_value;
	bool dar_valid;
	unsigned int error_type;
	unsigned int error_subtype;
	unsigned int error_class;
	unsigned int initiator;
	unsigned int severity;
	bool sync_error;
};

enum stf_barrier_type {
	STF_BARRIER_NONE = 1,
	STF_BARRIER_FALLBACK = 2,
	STF_BARRIER_EIEIO = 4,
	STF_BARRIER_SYNC_ORI = 8,
};

enum l1d_flush_type {
	L1D_FLUSH_NONE = 1,
	L1D_FLUSH_FALLBACK = 2,
	L1D_FLUSH_ORI = 4,
	L1D_FLUSH_MTTRIG = 8,
};

enum branch_cache_flush_type {
	BRANCH_CACHE_FLUSH_NONE = 1,
	BRANCH_CACHE_FLUSH_SW = 2,
	BRANCH_CACHE_FLUSH_HW = 4,
};

struct proc_ops {
	unsigned int proc_flags;
	int (*proc_open)(struct inode *, struct file *);
	ssize_t (*proc_read)(struct file *, char *, size_t, loff_t *);
	ssize_t (*proc_read_iter)(struct kiocb *, struct iov_iter *);
	ssize_t (*proc_write)(struct file *, const char *, size_t, loff_t *);
	loff_t (*proc_lseek)(struct file *, loff_t, int);
	int (*proc_release)(struct inode *, struct file *);
	__poll_t (*proc_poll)(struct file *, struct poll_table_struct *);
	long int (*proc_ioctl)(struct file *, unsigned int, long unsigned int);
	int (*proc_mmap)(struct file *, struct vm_area_struct *);
	long unsigned int (*proc_get_unmapped_area)(struct file *, long unsigned int, long unsigned int, long unsigned int, long unsigned int);
};

typedef u16 uint16_t;

struct rtas_t {
	long unsigned int entry;
	long unsigned int base;
	long unsigned int size;
	arch_spinlock_t lock;
	struct rtas_args args;
	struct device_node *dev;
};

struct rtas_error_log {
	u8 byte0;
	u8 byte1;
	u8 byte2;
	u8 byte3;
	__be32 extended_log_length;
	unsigned char buffer[1];
};

struct rtas_ext_event_log_v6 {
	u8 byte0;
	u8 byte1;
	u8 byte2;
	u8 byte3;
	u8 reserved[8];
	__be32 company_id;
	u8 vendor_log[1];
};

struct pseries_errorlog {
	__be16 id;
	__be16 length;
	u8 version;
	u8 subtype;
	__be16 creator_component;
	u8 data[0];
};

struct rtas_filter {
	const char *name;
	int token;
	int buf_idx1;
	int size_idx1;
	int buf_idx2;
	int size_idx2;
	int fixed_size;
};

struct indicator_elem {
	__be32 token;
	__be32 maxindex;
};

typedef long unsigned int ulong;

typedef struct poll_table_struct poll_table;

typedef void (*exitcall_t)();

struct flash_block {
	char *data;
	long unsigned int length;
};

struct flash_block_list {
	long unsigned int num_blocks;
	struct flash_block_list *next;
	struct flash_block blocks[255];
};

struct rtas_update_flash_t {
	int status;
	struct flash_block_list *flist;
};

struct rtas_manage_flash_t {
	int status;
};

struct rtas_validate_flash_t {
	int status;
	char *buf;
	unsigned int buf_size;
	unsigned int update_results;
};

struct rtas_flash_file {
	const char *filename;
	const char *rtas_call_name;
	int *status;
	const struct proc_ops ops;
};

struct individual_sensor {
	unsigned int token;
	unsigned int quant;
};

struct rtas_sensors {
	struct individual_sensor sensor[17];
	unsigned int quant;
};

struct dt_cpu_feature {
	const char *name;
	uint32_t isa;
	uint32_t usable_privilege;
	uint32_t hv_support;
	uint32_t os_support;
	uint32_t hfscr_bit_nr;
	uint32_t fscr_bit_nr;
	uint32_t hwcap_bit_nr;
	long unsigned int node;
	int enabled;
	int disabled;
};

struct dt_cpu_feature_match {
	const char *name;
	int (*enable)(struct dt_cpu_feature *);
	u64 cpu_ftr_bit_mask;
};

struct iopf_device_param;

struct iommu_fault_param;

struct iommu_fwspec;

struct dev_iommu {
	struct mutex lock;
	struct iommu_fault_param *fault_param;
	struct iopf_device_param *iopf_param;
	struct iommu_fwspec *fwspec;
	struct iommu_device *iommu_dev;
	void *priv;
};

struct eeh_ops {
	char *name;
	struct eeh_dev * (*probe)(struct pci_dev *);
	int (*set_option)(struct eeh_pe *, int);
	int (*get_state)(struct eeh_pe *, int *);
	int (*reset)(struct eeh_pe *, int);
	int (*get_log)(struct eeh_pe *, int, char *, long unsigned int);
	int (*configure_bridge)(struct eeh_pe *);
	int (*err_inject)(struct eeh_pe *, int, int, long unsigned int, long unsigned int);
	int (*read_config)(struct eeh_dev *, int, int, u32 *);
	int (*write_config)(struct eeh_dev *, int, int, u32);
	int (*next_error)(struct eeh_pe **);
	int (*restore_config)(struct eeh_dev *);
	int (*notify_resume)(struct eeh_dev *);
};

typedef void (*eeh_edev_traverse_func)(struct eeh_dev *, void *);

typedef void * (*eeh_pe_traverse_func)(struct eeh_pe *, void *);

enum pcie_reset_state {
	pcie_deassert_reset = 1,
	pcie_warm_reset = 2,
	pcie_hot_reset = 3,
};

struct of_phandle_args {
	struct device_node *np;
	int args_count;
	uint32_t args[16];
};

struct iommu_fault_unrecoverable {
	__u32 reason;
	__u32 flags;
	__u32 pasid;
	__u32 perm;
	__u64 addr;
	__u64 fetch_addr;
};

struct iommu_fault_page_request {
	__u32 flags;
	__u32 pasid;
	__u32 grpid;
	__u32 perm;
	__u64 addr;
	__u64 private_data[2];
};

struct iommu_fault {
	__u32 type;
	__u32 padding;
	union {
		struct iommu_fault_unrecoverable event;
		struct iommu_fault_page_request prm;
		__u8 padding2[56];
	};
};

struct iommu_page_response {
	__u32 argsz;
	__u32 version;
	__u32 flags;
	__u32 pasid;
	__u32 grpid;
	__u32 code;
};

typedef int (*iommu_fault_handler_t)(struct iommu_domain *, struct device *, long unsigned int, int, void *);

struct iommu_domain_geometry {
	dma_addr_t aperture_start;
	dma_addr_t aperture_end;
	bool force_aperture;
};

struct iommu_dma_cookie;

struct iommu_domain {
	unsigned int type;
	const struct iommu_domain_ops *ops;
	long unsigned int pgsize_bitmap;
	iommu_fault_handler_t handler;
	void *handler_token;
	struct iommu_domain_geometry geometry;
	struct iommu_dma_cookie *iova_cookie;
};

typedef int (*iommu_dev_fault_handler_t)(struct iommu_fault *, void *);

struct iommu_iotlb_gather;

struct iommu_domain_ops {
	int (*attach_dev)(struct iommu_domain *, struct device *);
	void (*detach_dev)(struct iommu_domain *, struct device *);
	int (*map)(struct iommu_domain *, long unsigned int, phys_addr_t, size_t, int, gfp_t);
	int (*map_pages)(struct iommu_domain *, long unsigned int, phys_addr_t, size_t, size_t, int, gfp_t, size_t *);
	size_t (*unmap)(struct iommu_domain *, long unsigned int, size_t, struct iommu_iotlb_gather *);
	size_t (*unmap_pages)(struct iommu_domain *, long unsigned int, size_t, size_t, struct iommu_iotlb_gather *);
	void (*flush_iotlb_all)(struct iommu_domain *);
	void (*iotlb_sync_map)(struct iommu_domain *, long unsigned int, size_t);
	void (*iotlb_sync)(struct iommu_domain *, struct iommu_iotlb_gather *);
	phys_addr_t (*iova_to_phys)(struct iommu_domain *, dma_addr_t);
	bool (*enforce_cache_coherency)(struct iommu_domain *);
	int (*enable_nesting)(struct iommu_domain *);
	int (*set_pgtable_quirks)(struct iommu_domain *, long unsigned int);
	void (*free)(struct iommu_domain *);
};

struct iommu_iotlb_gather {
	long unsigned int start;
	long unsigned int end;
	size_t pgsize;
	struct list_head freelist;
	bool queued;
};

struct iommu_device {
	struct list_head list;
	const struct iommu_ops *ops;
	struct fwnode_handle *fwnode;
	struct device *dev;
};

struct iommu_sva {
	struct device *dev;
};

struct iommu_fault_event {
	struct iommu_fault fault;
	struct list_head list;
};

struct iommu_fault_param {
	iommu_dev_fault_handler_t handler;
	void *data;
	struct list_head faults;
	struct mutex lock;
};

struct iommu_fwspec {
	const struct iommu_ops *ops;
	struct fwnode_handle *iommu_fwnode;
	u32 flags;
	unsigned int num_ids;
	u32 ids[0];
};

struct eeh_stats {
	u64 no_device;
	u64 no_dn;
	u64 no_cfg_addr;
	u64 ignored_check;
	u64 total_mmio_ffs;
	u64 false_positives;
	u64 slot_resets;
};

enum {
	pci_channel_io_normal = 1,
	pci_channel_io_frozen = 2,
	pci_channel_io_perm_failure = 3,
};

struct pci_io_addr_range {
	struct rb_node rb_node;
	resource_size_t addr_lo;
	resource_size_t addr_hi;
	struct eeh_dev *edev;
	struct pci_dev *pcidev;
	long unsigned int flags;
};

struct pci_io_addr_cache {
	struct rb_root rb_root;
	spinlock_t piar_lock;
};

enum {
	EEH_NEXT_ERR_NONE = 0,
	EEH_NEXT_ERR_INF = 1,
	EEH_NEXT_ERR_FROZEN_PE = 2,
	EEH_NEXT_ERR_FENCED_PHB = 3,
	EEH_NEXT_ERR_DEAD_PHB = 4,
	EEH_NEXT_ERR_DEAD_IOC = 5,
};

enum {
	IRQD_TRIGGER_MASK = 15,
	IRQD_SETAFFINITY_PENDING = 256,
	IRQD_ACTIVATED = 512,
	IRQD_NO_BALANCING = 1024,
	IRQD_PER_CPU = 2048,
	IRQD_AFFINITY_SET = 4096,
	IRQD_LEVEL = 8192,
	IRQD_WAKEUP_STATE = 16384,
	IRQD_MOVE_PCNTXT = 32768,
	IRQD_IRQ_DISABLED = 65536,
	IRQD_IRQ_MASKED = 131072,
	IRQD_IRQ_INPROGRESS = 262144,
	IRQD_WAKEUP_ARMED = 524288,
	IRQD_FORWARDED_TO_VCPU = 1048576,
	IRQD_AFFINITY_MANAGED = 2097152,
	IRQD_IRQ_STARTED = 4194304,
	IRQD_MANAGED_SHUTDOWN = 8388608,
	IRQD_SINGLE_TARGET = 16777216,
	IRQD_DEFAULT_TRIGGER_SET = 33554432,
	IRQD_CAN_RESERVE = 67108864,
	IRQD_MSI_NOMASK_QUIRK = 134217728,
	IRQD_HANDLE_ENFORCE_IRQCTX = 268435456,
	IRQD_AFFINITY_ON_ACTIVATE = 536870912,
	IRQD_IRQ_ENABLED_ON_SUSPEND = 1073741824,
};

struct hotplug_slot_ops;

struct hotplug_slot {
	const struct hotplug_slot_ops *ops;
	struct list_head slot_list;
	struct pci_slot *pci_slot;
	struct module *owner;
	const char *mod_name;
};

enum pci_ers_result {
	PCI_ERS_RESULT_NONE = 1,
	PCI_ERS_RESULT_CAN_RECOVER = 2,
	PCI_ERS_RESULT_NEED_RESET = 3,
	PCI_ERS_RESULT_DISCONNECT = 4,
	PCI_ERS_RESULT_RECOVERED = 5,
	PCI_ERS_RESULT_NO_AER_DRIVER = 6,
};

struct hotplug_slot_ops {
	int (*enable_slot)(struct hotplug_slot *);
	int (*disable_slot)(struct hotplug_slot *);
	int (*set_attention_status)(struct hotplug_slot *, u8);
	int (*hardware_test)(struct hotplug_slot *, u32);
	int (*get_power_status)(struct hotplug_slot *, u8 *);
	int (*get_attention_status)(struct hotplug_slot *, u8 *);
	int (*get_latch_status)(struct hotplug_slot *, u8 *);
	int (*get_adapter_status)(struct hotplug_slot *, u8 *);
	int (*reset_slot)(struct hotplug_slot *, bool);
};

struct eeh_rmv_data {
	struct list_head removed_vf_list;
	int removed_dev_count;
};

typedef enum pci_ers_result (*eeh_report_fn)(struct eeh_dev *, struct pci_dev *, struct pci_driver *);

struct eeh_event {
	struct list_head list;
	struct eeh_pe *pe;
};

enum pageflags {
	PG_locked = 0,
	PG_referenced = 1,
	PG_uptodate = 2,
	PG_dirty = 3,
	PG_lru = 4,
	PG_active = 5,
	PG_workingset = 6,
	PG_waiters = 7,
	PG_error = 8,
	PG_slab = 9,
	PG_owner_priv_1 = 10,
	PG_arch_1 = 11,
	PG_reserved = 12,
	PG_private = 13,
	PG_private_2 = 14,
	PG_writeback = 15,
	PG_head = 16,
	PG_mappedtodisk = 17,
	PG_reclaim = 18,
	PG_swapbacked = 19,
	PG_unevictable = 20,
	PG_mlocked = 21,
	PG_hwpoison = 22,
	PG_young = 23,
	PG_idle = 24,
	PG_arch_2 = 25,
	__NR_PAGEFLAGS = 26,
	PG_readahead = 18,
	PG_anon_exclusive = 17,
	PG_checked = 10,
	PG_swapcache = 10,
	PG_fscache = 14,
	PG_pinned = 10,
	PG_savepinned = 3,
	PG_foreign = 10,
	PG_xen_remapped = 10,
	PG_slob_free = 13,
	PG_double_map = 6,
	PG_has_hwpoisoned = 8,
	PG_isolated = 18,
	PG_reported = 2,
};

struct __kernel_old_timeval {
	__kernel_long_t tv_sec;
	__kernel_long_t tv_usec;
};

struct elf64_phdr {
	Elf64_Word p_type;
	Elf64_Word p_flags;
	Elf64_Off p_offset;
	Elf64_Addr p_vaddr;
	Elf64_Addr p_paddr;
	Elf64_Xword p_filesz;
	Elf64_Xword p_memsz;
	Elf64_Xword p_align;
};

struct elf_siginfo {
	int si_signo;
	int si_code;
	int si_errno;
};

struct elf_prstatus_common {
	struct elf_siginfo pr_info;
	short int pr_cursig;
	long unsigned int pr_sigpend;
	long unsigned int pr_sighold;
	pid_t pr_pid;
	pid_t pr_ppid;
	pid_t pr_pgrp;
	pid_t pr_sid;
	struct __kernel_old_timeval pr_utime;
	struct __kernel_old_timeval pr_stime;
	struct __kernel_old_timeval pr_cutime;
	struct __kernel_old_timeval pr_cstime;
};

struct elf_prstatus {
	struct elf_prstatus_common common;
	elf_gregset_t pr_reg;
	int pr_fpvalid;
};

struct fadump_crash_info_header {
	u64 magic_number;
	u64 elfcorehdr_addr;
	u32 crashing_cpu;
	struct pt_regs regs;
	struct cpumask cpu_mask;
};

struct fadump_memory_range {
	u64 base;
	u64 size;
};

struct fadump_mrange_info {
	char name[16];
	struct fadump_memory_range *mem_ranges;
	u32 mem_ranges_sz;
	u32 mem_range_cnt;
	u32 max_mem_ranges;
	bool is_static;
};

struct fadump_ops;

struct fw_dump {
	long unsigned int reserve_dump_area_start;
	long unsigned int reserve_dump_area_size;
	long unsigned int reserve_bootvar;
	long unsigned int cpu_state_data_size;
	u64 cpu_state_dest_vaddr;
	u32 cpu_state_data_version;
	u32 cpu_state_entry_size;
	long unsigned int hpte_region_size;
	long unsigned int boot_memory_size;
	u64 boot_mem_dest_addr;
	u64 boot_mem_addr[128];
	u64 boot_mem_sz[128];
	u64 boot_mem_top;
	u64 boot_mem_regs_cnt;
	long unsigned int fadumphdr_addr;
	long unsigned int cpu_notes_buf_vaddr;
	long unsigned int cpu_notes_buf_size;
	u64 max_copy_size;
	u64 kernel_metadata;
	int ibm_configure_kernel_dump;
	long unsigned int fadump_enabled: 1;
	long unsigned int fadump_supported: 1;
	long unsigned int dump_active: 1;
	long unsigned int dump_registered: 1;
	long unsigned int nocma: 1;
	struct fadump_ops *ops;
};

struct fadump_ops {
	u64 (*fadump_init_mem_struct)(struct fw_dump *);
	u64 (*fadump_get_metadata_size)();
	int (*fadump_setup_metadata)(struct fw_dump *);
	u64 (*fadump_get_bootmem_min)();
	int (*fadump_register)(struct fw_dump *);
	int (*fadump_unregister)(struct fw_dump *);
	int (*fadump_invalidate)(struct fw_dump *);
	void (*fadump_cleanup)(struct fw_dump *);
	int (*fadump_process)(struct fw_dump *);
	void (*fadump_region_show)(struct fw_dump *, struct seq_file *);
	void (*fadump_trigger)(struct fadump_crash_info_header *, const char *);
};

struct cma;

typedef void (*swap_func_t)(void *, void *, int);

typedef int (*cmp_func_t)(const void *, const void *);

typedef __s64 Elf64_Sxword;

struct elf64_rela {
	Elf64_Addr r_offset;
	Elf64_Xword r_info;
	Elf64_Sxword r_addend;
};

typedef struct elf64_rela Elf64_Rela;

struct modversion_info {
	long unsigned int crc;
	char name[56];
};

typedef long unsigned int func_desc_t;

struct ppc64_stub_entry {
	u32 jump[7];
	u32 magic;
	func_desc_t funcdata;
};

enum jump_label_type {
	JUMP_LABEL_NOP = 0,
	JUMP_LABEL_JMP = 1,
};

struct io_tlb_area;

struct io_tlb_slot;

struct io_tlb_mem {
	phys_addr_t start;
	phys_addr_t end;
	void *vaddr;
	long unsigned int nslabs;
	long unsigned int used;
	struct dentry *debugfs;
	bool late_alloc;
	bool force_bounce;
	bool for_alloc;
	unsigned int nareas;
	unsigned int area_nslabs;
	struct io_tlb_area *areas;
	struct io_tlb_slot *slots;
};

enum kgdb_bptype {
	BP_BREAKPOINT = 0,
	BP_HARDWARE_BREAKPOINT = 1,
	BP_WRITE_WATCHPOINT = 2,
	BP_READ_WATCHPOINT = 3,
	BP_ACCESS_WATCHPOINT = 4,
	BP_POKE_BREAKPOINT = 5,
};

enum kgdb_bpstate {
	BP_UNDEFINED = 0,
	BP_REMOVED = 1,
	BP_SET = 2,
	BP_ACTIVE = 3,
};

struct kgdb_bkpt {
	long unsigned int bpt_addr;
	unsigned char saved_instr[4];
	enum kgdb_bptype type;
	enum kgdb_bpstate state;
};

struct dbg_reg_def_t {
	char *name;
	int size;
	int offset;
};

struct kgdb_arch {
	unsigned char gdb_bpt_instr[4];
	long unsigned int flags;
	int (*set_breakpoint)(long unsigned int, char *);
	int (*remove_breakpoint)(long unsigned int, char *);
	int (*set_hw_breakpoint)(long unsigned int, int, enum kgdb_bptype);
	int (*remove_hw_breakpoint)(long unsigned int, int, enum kgdb_bptype);
	void (*disable_hw_break)(struct pt_regs *);
	void (*remove_all_hw_break)();
	void (*correct_hw_break)();
	void (*enable_nmi)(bool);
};

struct hard_trap_info {
	unsigned int tt;
	unsigned char signo;
};

enum {
	SD_BALANCE_NEWIDLE = 1,
	SD_BALANCE_EXEC = 2,
	SD_BALANCE_FORK = 4,
	SD_BALANCE_WAKE = 8,
	SD_WAKE_AFFINE = 16,
	SD_ASYM_CPUCAPACITY = 32,
	SD_ASYM_CPUCAPACITY_FULL = 64,
	SD_SHARE_CPUCAPACITY = 128,
	SD_SHARE_PKG_RESOURCES = 256,
	SD_SERIALIZE = 512,
	SD_ASYM_PACKING = 1024,
	SD_PREFER_SIBLING = 2048,
	SD_OVERLAP = 4096,
	SD_NUMA = 8192,
};

struct sched_domain_shared {
	atomic_t ref;
	atomic_t nr_busy_cpus;
	int has_idle_cores;
	int nr_idle_scan;
};

struct sched_group;

struct sched_domain {
	struct sched_domain *parent;
	struct sched_domain *child;
	struct sched_group *groups;
	long unsigned int min_interval;
	long unsigned int max_interval;
	unsigned int busy_factor;
	unsigned int imbalance_pct;
	unsigned int cache_nice_tries;
	unsigned int imb_numa_nr;
	int nohz_idle;
	int flags;
	int level;
	long unsigned int last_balance;
	unsigned int balance_interval;
	unsigned int nr_balance_failed;
	u64 max_newidle_lb_cost;
	long unsigned int last_decay_max_lb_cost;
	u64 avg_scan_cost;
	unsigned int lb_count[3];
	unsigned int lb_failed[3];
	unsigned int lb_balanced[3];
	unsigned int lb_imbalance[3];
	unsigned int lb_gained[3];
	unsigned int lb_hot_gained[3];
	unsigned int lb_nobusyg[3];
	unsigned int lb_nobusyq[3];
	unsigned int alb_count;
	unsigned int alb_failed;
	unsigned int alb_pushed;
	unsigned int sbe_count;
	unsigned int sbe_balanced;
	unsigned int sbe_pushed;
	unsigned int sbf_count;
	unsigned int sbf_balanced;
	unsigned int sbf_pushed;
	unsigned int ttwu_wake_remote;
	unsigned int ttwu_move_affine;
	unsigned int ttwu_move_balance;
	char *name;
	union {
		void *private;
		struct callback_head rcu;
	};
	struct sched_domain_shared *shared;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	unsigned int span_weight;
	long unsigned int span[0];
};

typedef const struct cpumask * (*sched_domain_mask_f)(int);

typedef int (*sched_domain_flags_f)();

struct sched_group_capacity;

struct sd_data {
	struct sched_domain **sd;
	struct sched_domain_shared **sds;
	struct sched_group **sg;
	struct sched_group_capacity **sgc;
};

struct sched_domain_topology_level {
	sched_domain_mask_f mask;
	sched_domain_flags_f sd_flags;
	int flags;
	int numa_level;
	struct sd_data data;
	char *name;
};

enum {
	smt_idx = 0,
	cache_idx = 1,
	mc_idx = 2,
	die_idx = 3,
};

struct thread_groups {
	unsigned int property;
	unsigned int nr_groups;
	unsigned int threads_per_group;
	unsigned int thread_list[8];
};

struct thread_groups_list {
	unsigned int nr_properties;
	struct thread_groups property_tgs[2];
};

struct cpu_messages {
	long int messages;
};

typedef u32 ppc_opcode_t;

struct freelist_node {
	atomic_t refs;
	struct freelist_node *next;
};

struct freelist_head {
	struct freelist_node *head;
};

typedef ppc_opcode_t kprobe_opcode_t;

struct arch_specific_insn {
	kprobe_opcode_t *insn;
	int boostable;
};

struct kprobe;

struct prev_kprobe {
	struct kprobe *kp;
	long unsigned int status;
	long unsigned int saved_msr;
};

typedef int (*kprobe_pre_handler_t)(struct kprobe *, struct pt_regs *);

typedef void (*kprobe_post_handler_t)(struct kprobe *, struct pt_regs *, long unsigned int);

struct kprobe {
	struct hlist_node hlist;
	struct list_head list;
	long unsigned int nmissed;
	kprobe_opcode_t *addr;
	const char *symbol_name;
	unsigned int offset;
	kprobe_pre_handler_t pre_handler;
	kprobe_post_handler_t post_handler;
	kprobe_opcode_t opcode;
	struct arch_specific_insn ainsn;
	u32 flags;
};

struct kprobe_ctlblk {
	long unsigned int kprobe_status;
	long unsigned int kprobe_saved_msr;
	struct prev_kprobe prev_kprobe;
};

struct kretprobe_instance;

typedef int (*kretprobe_handler_t)(struct kretprobe_instance *, struct pt_regs *);

struct kretprobe_holder;

struct kretprobe_instance {
	union {
		struct freelist_node freelist;
		struct callback_head rcu;
	};
	struct llist_node llist;
	struct kretprobe_holder *rph;
	kprobe_opcode_t *ret_addr;
	void *fp;
	char data[0];
};

struct kretprobe;

struct kretprobe_holder {
	struct kretprobe *rp;
	refcount_t ref;
};

struct kretprobe {
	struct kprobe kp;
	kretprobe_handler_t handler;
	kretprobe_handler_t entry_handler;
	int maxactive;
	int nmissed;
	size_t data_size;
	struct freelist_head freelist;
	struct kretprobe_holder *rph;
};

struct kretprobe_blackpoint {
	const char *name;
	void *addr;
};

struct kprobe_insn_cache {
	struct mutex mutex;
	void * (*alloc)();
	void (*free)(void *);
	const char *sym;
	struct list_head pages;
	size_t insn_size;
	int nr_garbage;
};

struct arch_optimized_insn {
	kprobe_opcode_t copied_insn[1];
	kprobe_opcode_t *insn;
};

struct optimized_kprobe {
	struct kprobe kp;
	struct list_head list;
	struct arch_optimized_insn optinsn;
};

enum {
	TRACE_FTRACE_BIT = 0,
	TRACE_FTRACE_NMI_BIT = 1,
	TRACE_FTRACE_IRQ_BIT = 2,
	TRACE_FTRACE_SIRQ_BIT = 3,
	TRACE_INTERNAL_BIT = 4,
	TRACE_INTERNAL_NMI_BIT = 5,
	TRACE_INTERNAL_IRQ_BIT = 6,
	TRACE_INTERNAL_SIRQ_BIT = 7,
	TRACE_BRANCH_BIT = 8,
	TRACE_IRQ_BIT = 9,
	TRACE_GRAPH_BIT = 10,
	TRACE_GRAPH_DEPTH_START_BIT = 11,
	TRACE_GRAPH_DEPTH_END_BIT = 12,
	TRACE_GRAPH_NOTRACE_BIT = 13,
	TRACE_TRANSITION_BIT = 14,
	TRACE_RECORD_RECURSION_BIT = 15,
};

enum {
	TRACE_CTX_NMI = 0,
	TRACE_CTX_IRQ = 1,
	TRACE_CTX_SOFTIRQ = 2,
	TRACE_CTX_NORMAL = 3,
};

typedef ppc_opcode_t uprobe_opcode_t;

struct arch_uprobe {
	union {
		u32 insn[2];
		u32 ixol[2];
	};
};

enum rp_check {
	RP_CHECK_CALL = 0,
	RP_CHECK_CHAIN_CALL = 1,
	RP_CHECK_RET = 2,
};

struct serial_rs485 {
	__u32 flags;
	__u32 delay_rts_before_send;
	__u32 delay_rts_after_send;
	__u32 padding[5];
};

struct serial_iso7816 {
	__u32 flags;
	__u32 tg;
	__u32 sc_fi;
	__u32 sc_di;
	__u32 clk;
	__u32 reserved[5];
};

struct circ_buf {
	char *buf;
	int head;
	int tail;
};

struct uart_port;

struct uart_ops {
	unsigned int (*tx_empty)(struct uart_port *);
	void (*set_mctrl)(struct uart_port *, unsigned int);
	unsigned int (*get_mctrl)(struct uart_port *);
	void (*stop_tx)(struct uart_port *);
	void (*start_tx)(struct uart_port *);
	void (*throttle)(struct uart_port *);
	void (*unthrottle)(struct uart_port *);
	void (*send_xchar)(struct uart_port *, char);
	void (*stop_rx)(struct uart_port *);
	void (*enable_ms)(struct uart_port *);
	void (*break_ctl)(struct uart_port *, int);
	int (*startup)(struct uart_port *);
	void (*shutdown)(struct uart_port *);
	void (*flush_buffer)(struct uart_port *);
	void (*set_termios)(struct uart_port *, struct ktermios *, struct ktermios *);
	void (*set_ldisc)(struct uart_port *, struct ktermios *);
	void (*pm)(struct uart_port *, unsigned int, unsigned int);
	const char * (*type)(struct uart_port *);
	void (*release_port)(struct uart_port *);
	int (*request_port)(struct uart_port *);
	void (*config_port)(struct uart_port *, int);
	int (*verify_port)(struct uart_port *, struct serial_struct *);
	int (*ioctl)(struct uart_port *, unsigned int, long unsigned int);
	int (*poll_init)(struct uart_port *);
	void (*poll_put_char)(struct uart_port *, unsigned char);
	int (*poll_get_char)(struct uart_port *);
};

struct uart_icount {
	__u32 cts;
	__u32 dsr;
	__u32 rng;
	__u32 dcd;
	__u32 rx;
	__u32 tx;
	__u32 frame;
	__u32 overrun;
	__u32 parity;
	__u32 brk;
	__u32 buf_overrun;
};

typedef unsigned int upf_t;

typedef unsigned int upstat_t;

struct gpio_desc;

struct uart_state;

struct uart_port {
	spinlock_t lock;
	long unsigned int iobase;
	unsigned char *membase;
	unsigned int (*serial_in)(struct uart_port *, int);
	void (*serial_out)(struct uart_port *, int, int);
	void (*set_termios)(struct uart_port *, struct ktermios *, struct ktermios *);
	void (*set_ldisc)(struct uart_port *, struct ktermios *);
	unsigned int (*get_mctrl)(struct uart_port *);
	void (*set_mctrl)(struct uart_port *, unsigned int);
	unsigned int (*get_divisor)(struct uart_port *, unsigned int, unsigned int *);
	void (*set_divisor)(struct uart_port *, unsigned int, unsigned int, unsigned int);
	int (*startup)(struct uart_port *);
	void (*shutdown)(struct uart_port *);
	void (*throttle)(struct uart_port *);
	void (*unthrottle)(struct uart_port *);
	int (*handle_irq)(struct uart_port *);
	void (*pm)(struct uart_port *, unsigned int, unsigned int);
	void (*handle_break)(struct uart_port *);
	int (*rs485_config)(struct uart_port *, struct serial_rs485 *);
	int (*iso7816_config)(struct uart_port *, struct serial_iso7816 *);
	unsigned int irq;
	long unsigned int irqflags;
	unsigned int uartclk;
	unsigned int fifosize;
	unsigned char x_char;
	unsigned char regshift;
	unsigned char iotype;
	unsigned char quirks;
	unsigned int read_status_mask;
	unsigned int ignore_status_mask;
	struct uart_state *state;
	struct uart_icount icount;
	struct console *cons;
	upf_t flags;
	upstat_t status;
	int hw_stopped;
	unsigned int mctrl;
	unsigned int timeout;
	unsigned int type;
	const struct uart_ops *ops;
	unsigned int custom_divisor;
	unsigned int line;
	unsigned int minor;
	resource_size_t mapbase;
	resource_size_t mapsize;
	struct device *dev;
	long unsigned int sysrq;
	unsigned int sysrq_ch;
	unsigned char has_sysrq;
	unsigned char sysrq_seq;
	unsigned char hub6;
	unsigned char suspended;
	unsigned char console_reinit;
	const char *name;
	struct attribute_group *attr_group;
	const struct attribute_group **tty_groups;
	struct serial_rs485 rs485;
	struct gpio_desc *rs485_term_gpio;
	struct serial_iso7816 iso7816;
	void *private_data;
};

enum uart_pm_state {
	UART_PM_STATE_ON = 0,
	UART_PM_STATE_OFF = 3,
	UART_PM_STATE_UNDEFINED = 4,
};

struct uart_state {
	struct tty_port port;
	enum uart_pm_state pm_state;
	struct circ_buf xmit;
	atomic_t refcount;
	wait_queue_head_t remove_wait;
	struct uart_port *uart_port;
};

struct plat_serial8250_port {
	long unsigned int iobase;
	void *membase;
	resource_size_t mapbase;
	unsigned int irq;
	long unsigned int irqflags;
	unsigned int uartclk;
	void *private_data;
	unsigned char regshift;
	unsigned char iotype;
	unsigned char hub6;
	unsigned char has_sysrq;
	upf_t flags;
	unsigned int type;
	unsigned int (*serial_in)(struct uart_port *, int);
	void (*serial_out)(struct uart_port *, int, int);
	void (*set_termios)(struct uart_port *, struct ktermios *, struct ktermios *);
	void (*set_ldisc)(struct uart_port *, struct ktermios *);
	unsigned int (*get_mctrl)(struct uart_port *);
	int (*handle_irq)(struct uart_port *);
	void (*pm)(struct uart_port *, unsigned int, unsigned int);
	void (*handle_break)(struct uart_port *);
};

enum {
	PLAT8250_DEV_LEGACY = 4294967295,
	PLAT8250_DEV_PLATFORM = 0,
	PLAT8250_DEV_PLATFORM1 = 1,
	PLAT8250_DEV_PLATFORM2 = 2,
	PLAT8250_DEV_FOURPORT = 3,
	PLAT8250_DEV_ACCENT = 4,
	PLAT8250_DEV_BOCA = 5,
	PLAT8250_DEV_EXAR_ST16C554 = 6,
	PLAT8250_DEV_HUB6 = 7,
	PLAT8250_DEV_AU1X00 = 8,
	PLAT8250_DEV_SM501 = 9,
};

struct legacy_serial_info {
	struct device_node *np;
	unsigned int speed;
	unsigned int clock;
	int irq_check_parent;
	phys_addr_t taddr;
	void *early_addr;
};

struct vm_struct {
	struct vm_struct *next;
	void *addr;
	long unsigned int size;
	long unsigned int flags;
	struct page **pages;
	unsigned int page_order;
	unsigned int nr_pages;
	phys_addr_t phys_addr;
	const void *caller;
};

enum {
	PCI_REASSIGN_ALL_RSRC = 1,
	PCI_REASSIGN_ALL_BUS = 2,
	PCI_PROBE_ONLY = 4,
	PCI_CAN_SKIP_ISA_ALIGN = 8,
	PCI_ENABLE_PROC_DOMAINS = 16,
	PCI_COMPAT_DOMAIN_0 = 32,
	PCI_SCAN_ALL_PCIE_DEVS = 64,
};

struct pci_fixup {
	u16 vendor;
	u16 device;
	u32 class;
	unsigned int class_shift;
	void (*hook)(struct pci_dev *);
};

struct pci_address {
	u32 a_hi;
	u32 a_mid;
	u32 a_lo;
};

struct isa_address {
	u32 a_hi;
	u32 a_lo;
};

struct isa_range {
	struct isa_address isa_addr;
	struct pci_address pci_addr;
	unsigned int size;
};

enum {
	IRQ_TYPE_NONE = 0,
	IRQ_TYPE_EDGE_RISING = 1,
	IRQ_TYPE_EDGE_FALLING = 2,
	IRQ_TYPE_EDGE_BOTH = 3,
	IRQ_TYPE_LEVEL_HIGH = 4,
	IRQ_TYPE_LEVEL_LOW = 8,
	IRQ_TYPE_LEVEL_MASK = 12,
	IRQ_TYPE_SENSE_MASK = 15,
	IRQ_TYPE_DEFAULT = 15,
	IRQ_TYPE_PROBE = 16,
	IRQ_LEVEL = 256,
	IRQ_PER_CPU = 512,
	IRQ_NOPROBE = 1024,
	IRQ_NOREQUEST = 2048,
	IRQ_NOAUTOEN = 4096,
	IRQ_NO_BALANCING = 8192,
	IRQ_MOVE_PCNTXT = 16384,
	IRQ_NESTED_THREAD = 32768,
	IRQ_NOTHREAD = 65536,
	IRQ_PER_CPU_DEVID = 131072,
	IRQ_IS_POLLED = 262144,
	IRQ_DISABLE_UNLAZY = 524288,
	IRQ_HIDDEN = 1048576,
	IRQ_NO_DEBUG = 2097152,
};

enum pci_mmap_state {
	pci_mmap_io = 0,
	pci_mmap_mem = 1,
};

struct pci_sriov {
	int pos;
	int nres;
	u32 cap;
	u16 ctrl;
	u16 total_VFs;
	u16 initial_VFs;
	u16 num_VFs;
	u16 offset;
	u16 stride;
	u16 vf_device;
	u32 pgsz;
	u8 link;
	u8 max_VF_buses;
	u16 driver_max_VFs;
	struct pci_dev *dev;
	struct pci_dev *self;
	u32 class;
	u8 hdr_type;
	u16 subsystem_vendor;
	u16 subsystem_device;
	resource_size_t barsz[6];
	bool drivers_autoprobe;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	long unsigned int rh_reserved5;
	long unsigned int rh_reserved6;
	long unsigned int rh_reserved7;
	long unsigned int rh_reserved8;
};

struct rcec_ea {
	u8 nextbusn;
	u8 lastbusn;
	u32 bitmap;
};

typedef u64 pci_bus_addr_t;

struct pci_bus_region {
	pci_bus_addr_t start;
	pci_bus_addr_t end;
};

struct of_bus;

struct of_pci_range_parser {
	struct device_node *node;
	struct of_bus *bus;
	const __be32 *range;
	const __be32 *end;
	int na;
	int ns;
	int pna;
	bool dma;
};

struct of_pci_range {
	union {
		u64 pci_addr;
		u64 bus_addr;
	};
	u64 cpu_addr;
	u64 size;
	u32 flags;
};

struct pci_intx_virq {
	int virq;
	struct kref kref;
	struct list_head list_node;
};

enum pci_fixup_pass {
	pci_fixup_early = 0,
	pci_fixup_header = 1,
	pci_fixup_final = 2,
	pci_fixup_enable = 3,
	pci_fixup_resume = 4,
	pci_fixup_suspend = 5,
	pci_fixup_resume_early = 6,
	pci_fixup_suspend_late = 7,
};

enum auditsc_class_t {
	AUDITSC_NATIVE = 0,
	AUDITSC_COMPAT = 1,
	AUDITSC_OPEN = 2,
	AUDITSC_OPENAT = 3,
	AUDITSC_SOCKETCALL = 4,
	AUDITSC_EXECVE = 5,
	AUDITSC_OPENAT2 = 6,
	AUDITSC_NVALS = 7,
};

struct dyn_arch_ftrace {
	struct module *mod;
};

enum {
	FTRACE_FL_ENABLED = 2147483648,
	FTRACE_FL_REGS = 1073741824,
	FTRACE_FL_REGS_EN = 536870912,
	FTRACE_FL_TRAMP = 268435456,
	FTRACE_FL_TRAMP_EN = 134217728,
	FTRACE_FL_IPMODIFY = 67108864,
	FTRACE_FL_DISABLED = 33554432,
	FTRACE_FL_DIRECT = 16777216,
	FTRACE_FL_DIRECT_EN = 8388608,
};

struct dyn_ftrace {
	long unsigned int ip;
	long unsigned int flags;
	struct dyn_arch_ftrace arch;
};

struct secvar_operations {
	int (*get)(const char *, uint64_t, u8 *, uint64_t *);
	int (*get_next)(const char *, uint64_t *, uint64_t);
	int (*set)(const char *, uint64_t, u8 *, uint64_t);
};

enum kobject_action {
	KOBJ_ADD = 0,
	KOBJ_REMOVE = 1,
	KOBJ_CHANGE = 2,
	KOBJ_MOVE = 3,
	KOBJ_ONLINE = 4,
	KOBJ_OFFLINE = 5,
	KOBJ_BIND = 6,
	KOBJ_UNBIND = 7,
};

struct hstate {
	struct mutex resize_lock;
	int next_nid_to_alloc;
	int next_nid_to_free;
	unsigned int order;
	unsigned int demote_order;
	long unsigned int mask;
	long unsigned int max_huge_pages;
	long unsigned int nr_huge_pages;
	long unsigned int free_huge_pages;
	long unsigned int resv_huge_pages;
	long unsigned int surplus_huge_pages;
	long unsigned int nr_overcommit_huge_pages;
	struct list_head hugepage_activelist;
	struct list_head hugepage_freelists[256];
	unsigned int max_huge_pages_node[256];
	unsigned int nr_huge_pages_node[256];
	unsigned int free_huge_pages_node[256];
	unsigned int surplus_huge_pages_node[256];
	struct cftype cgroup_files_dfl[8];
	struct cftype cgroup_files_legacy[10];
	char name[32];
};

struct mhp_params {
	struct vmem_altmap *altmap;
	pgprot_t pgprot;
};

typedef struct {
	__be64 pdbe;
} hugepd_t;

typedef struct {
	pgd_t pgd;
} p4d_t;

struct hugepage_subpool {
	spinlock_t lock;
	long int count;
	long int max_hpages;
	long int used_hpages;
	struct hstate *hstate;
	long int min_hpages;
	long int rsv_hpages;
};

struct hugetlbfs_sb_info {
	long int max_inodes;
	long int free_inodes;
	spinlock_t stat_lock;
	struct hstate *hstate;
	struct hugepage_subpool *spool;
	kuid_t uid;
	kgid_t gid;
	umode_t mode;
};

typedef long unsigned int pte_basic_t;

typedef int (*pte_fn_t)(pte_t *, long unsigned int, void *);

struct vmemmap_backing {
	struct vmemmap_backing *list;
	long unsigned int phys;
	long unsigned int virt_addr;
};

struct prtb_entry {
	__be64 prtb0;
	__be64 prtb1;
};

struct patb_entry {
	__be64 patb0;
	__be64 patb1;
};

enum {
	MEMBARRIER_STATE_PRIVATE_EXPEDITED_READY = 1,
	MEMBARRIER_STATE_PRIVATE_EXPEDITED = 2,
	MEMBARRIER_STATE_GLOBAL_EXPEDITED_READY = 4,
	MEMBARRIER_STATE_GLOBAL_EXPEDITED = 8,
	MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE_READY = 16,
	MEMBARRIER_STATE_PRIVATE_EXPEDITED_SYNC_CORE = 32,
	MEMBARRIER_STATE_PRIVATE_EXPEDITED_RSEQ_READY = 64,
	MEMBARRIER_STATE_PRIVATE_EXPEDITED_RSEQ = 128,
};

struct of_drconf_cell_v1 {
	__be64 base_addr;
	__be32 drc_index;
	__be32 reserved;
	__be32 aa_index;
	__be32 flags;
};

struct of_drconf_cell_v2 {
	u32 seq_lmbs;
	u64 base_addr;
	u32 drc_index;
	u32 aa_index;
	u32 flags;
} __attribute__((packed));

typedef unsigned int xa_mark_t;

enum xa_lock_type {
	XA_LOCK_IRQ = 1,
	XA_LOCK_BH = 2,
};

struct ida {
	struct xarray xa;
};

enum pgtable_index {
	PTE_INDEX = 0,
	PMD_INDEX = 1,
	PUD_INDEX = 2,
	PGD_INDEX = 3,
	HTLB_16M_INDEX = 4,
	HTLB_16G_INDEX = 5,
};

struct mmu_hash_ops {
	void (*hpte_invalidate)(long unsigned int, long unsigned int, int, int, int, int);
	long int (*hpte_updatepp)(long unsigned int, long unsigned int, long unsigned int, int, int, int, long unsigned int);
	void (*hpte_updateboltedpp)(long unsigned int, long unsigned int, int, int);
	long int (*hpte_insert)(long unsigned int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, int, int, int);
	long int (*hpte_remove)(long unsigned int);
	int (*hpte_removebolted)(long unsigned int, int, int);
	void (*flush_hash_range)(long unsigned int, int);
	void (*hugepage_invalidate)(long unsigned int, long unsigned int, unsigned char *, int, int, int);
	int (*resize_hpt)(long unsigned int);
	void (*hpte_clear_all)();
};

struct mmu_table_batch {
	struct callback_head rcu;
	unsigned int nr;
	void *tables[0];
};

struct mmu_gather_batch {
	struct mmu_gather_batch *next;
	unsigned int nr;
	unsigned int max;
	struct page *pages[0];
};

struct mmu_gather {
	struct mm_struct *mm;
	struct mmu_table_batch *batch;
	long unsigned int start;
	long unsigned int end;
	unsigned int fullmm: 1;
	unsigned int need_flush_all: 1;
	unsigned int freed_tables: 1;
	unsigned int cleared_ptes: 1;
	unsigned int cleared_pmds: 1;
	unsigned int cleared_puds: 1;
	unsigned int cleared_p4ds: 1;
	unsigned int vma_exec: 1;
	unsigned int vma_huge: 1;
	unsigned int vma_pfn: 1;
	unsigned int batch_count;
	struct mmu_gather_batch *active;
	struct mmu_gather_batch local;
	struct page *__pages[8];
	unsigned int page_size;
};

typedef int (*cpu_stop_fn_t)(void *);

struct change_memory_parms {
	long unsigned int start;
	long unsigned int end;
	long unsigned int newpp;
	unsigned int step;
	unsigned int nr_cpus;
	unsigned int master_cpu;
	atomic_t cpu_counter;
};

struct hash_pte {
	__be64 v;
	__be64 r;
};

enum slb_index {
	LINEAR_INDEX = 0,
	KSTACK_INDEX = 1,
};

struct vm_unmapped_area_info {
	long unsigned int flags;
	long unsigned int length;
	long unsigned int low_limit;
	long unsigned int high_limit;
	long unsigned int align_mask;
	long unsigned int align_offset;
};

struct mm_walk;

struct mm_walk_ops {
	int (*pgd_entry)(pgd_t *, long unsigned int, long unsigned int, struct mm_walk *);
	int (*p4d_entry)(p4d_t *, long unsigned int, long unsigned int, struct mm_walk *);
	int (*pud_entry)(pud_t *, long unsigned int, long unsigned int, struct mm_walk *);
	int (*pmd_entry)(pmd_t *, long unsigned int, long unsigned int, struct mm_walk *);
	int (*pte_entry)(pte_t *, long unsigned int, long unsigned int, struct mm_walk *);
	int (*pte_hole)(long unsigned int, long unsigned int, int, struct mm_walk *);
	int (*hugetlb_entry)(pte_t *, long unsigned int, long unsigned int, long unsigned int, struct mm_walk *);
	int (*test_walk)(long unsigned int, long unsigned int, struct mm_walk *);
	int (*pre_vma)(long unsigned int, long unsigned int, struct mm_walk *);
	void (*post_vma)(struct mm_walk *);
};

enum page_walk_action {
	ACTION_SUBTREE = 0,
	ACTION_CONTINUE = 1,
	ACTION_AGAIN = 2,
};

struct mm_walk {
	const struct mm_walk_ops *ops;
	struct mm_struct *mm;
	pgd_t *pgd;
	struct vm_area_struct *vma;
	enum page_walk_action action;
	bool no_vma;
	void *private;
};

enum string_size_units {
	STRING_UNITS_10 = 0,
	STRING_UNITS_2 = 1,
};

struct tlbiel_pid {
	long unsigned int pid;
	long unsigned int ric;
};

struct tlbiel_va {
	long unsigned int pid;
	long unsigned int va;
	long unsigned int psize;
	long unsigned int ric;
};

struct tlbiel_va_range {
	long unsigned int pid;
	long unsigned int start;
	long unsigned int end;
	long unsigned int page_size;
	long unsigned int psize;
	bool also_pwc;
};

enum tlb_flush_type {
	FLUSH_TYPE_NONE = 0,
	FLUSH_TYPE_LOCAL = 1,
	FLUSH_TYPE_GLOBAL = 2,
};

typedef void (*rcu_callback_t)(struct callback_head *);

enum migrate_reason {
	MR_COMPACTION = 0,
	MR_MEMORY_FAILURE = 1,
	MR_MEMORY_HOTPLUG = 2,
	MR_SYSCALL = 3,
	MR_MEMPOLICY_MBIND = 4,
	MR_NUMA_MISPLACED = 5,
	MR_CONTIG_RANGE = 6,
	MR_LONGTERM_PIN = 7,
	MR_DEMOTION = 8,
	MR_TYPES = 9,
};

struct mm_iommu_table_group_mem_t {
	struct list_head next;
	struct callback_head rcu;
	long unsigned int used;
	atomic64_t mapped;
	unsigned int pageshift;
	u64 ua;
	u64 entries;
	union {
		struct page **hpages;
		phys_addr_t *hpas;
	};
	u64 dev_hpa;
};

struct assoc_arrays {
	u32 n_arrays;
	u32 array_sz;
	const __be32 *arrays;
};

struct huge_bootmem_page {
	struct list_head list;
	struct hstate *hstate;
};

struct copro_slb {
	u64 esid;
	u64 vsid;
};

enum spu_utilization_state {
	SPU_UTIL_USER = 0,
	SPU_UTIL_SYSTEM = 1,
	SPU_UTIL_IOWAIT = 2,
	SPU_UTIL_IDLE_LOADED = 3,
	SPU_UTIL_MAX = 4,
};

struct ptdump_range {
	long unsigned int start;
	long unsigned int end;
};

struct ptdump_state {
	void (*note_page)(struct ptdump_state *, long unsigned int, int, u64);
	void (*effective_prot)(struct ptdump_state *, int, u64);
	const struct ptdump_range *range;
};

struct flag_info {
	u64 mask;
	u64 val;
	const char *set;
	const char *clear;
	bool is_val;
	int shift;
};

struct pgtable_level {
	const struct flag_info *flag;
	size_t num;
	u64 mask;
};

struct addr_marker;

struct pg_state {
	struct ptdump_state ptdump;
	struct seq_file *seq;
	const struct addr_marker *marker;
	long unsigned int start_address;
	long unsigned int start_pa;
	int level;
	u64 current_flags;
	bool check_wx;
	long unsigned int wx_pages;
};

struct addr_marker {
	long unsigned int start_address;
	const char *name;
};

struct fixup_entry {
	long unsigned int mask;
	long unsigned int value;
	long int start_off;
	long int end_off;
	long int alt_start_off;
	long int alt_end_off;
};

enum {
	NDD_ALIASING = 0,
	NDD_UNARMED = 1,
	NDD_LOCKED = 2,
	NDD_SECURITY_OVERWRITE = 3,
	NDD_WORK_PENDING = 4,
	NDD_NOBLK = 5,
	NDD_LABELING = 6,
	ND_IOCTL_MAX_BUFLEN = 4194304,
	ND_CMD_MAX_ELEM = 5,
	ND_CMD_MAX_ENVELOPE = 256,
	ND_MAX_MAPPINGS = 32,
	ND_REGION_PAGEMAP = 0,
	ND_REGION_PERSIST_CACHE = 1,
	ND_REGION_PERSIST_MEMCTRL = 2,
	ND_REGION_ASYNC = 3,
	DPA_RESOURCE_ADJUSTED = 1,
};

struct soft_mask_table_entry {
	long unsigned int start;
	long unsigned int end;
};

struct restart_table_entry {
	long unsigned int start;
	long unsigned int end;
	long unsigned int fixup;
};

union vsx_reg {
	u8 b[16];
	u16 h[8];
	u32 w[4];
	long unsigned int d[2];
	float fp[4];
	double dp[2];
	__vector128 v;
};

typedef signed char unative_t[16];

enum {
	IRQ_SET_MASK_OK = 0,
	IRQ_SET_MASK_OK_NOCOPY = 1,
	IRQ_SET_MASK_OK_DONE = 2,
};

enum {
	IRQCHIP_SET_TYPE_MASKED = 1,
	IRQCHIP_EOI_IF_HANDLED = 2,
	IRQCHIP_MASK_ON_SUSPEND = 4,
	IRQCHIP_ONOFFLINE_ENABLED = 8,
	IRQCHIP_SKIP_SET_WAKE = 16,
	IRQCHIP_ONESHOT_SAFE = 32,
	IRQCHIP_EOI_THREADED = 64,
	IRQCHIP_SUPPORTS_LEVEL_MSI = 128,
	IRQCHIP_SUPPORTS_NMI = 256,
	IRQCHIP_ENABLE_WAKEUP_ON_SUSPEND = 512,
	IRQCHIP_AFFINITY_PRE_STARTUP = 1024,
	IRQCHIP_IMMUTABLE = 2048,
};

struct syscore_ops {
	struct list_head node;
	int (*suspend)();
	void (*resume)();
	void (*shutdown)();
};

struct msi_bitmap {
	struct device_node *of_node;
	long unsigned int *bitmap;
	spinlock_t lock;
	unsigned int irq_count;
	bool bitmap_from_slab;
};

enum mpic_reg_type {
	mpic_access_mmio_le = 0,
	mpic_access_mmio_be = 1,
};

struct mpic_reg_bank {
	u32 *base;
};

struct mpic_irq_save {
	u32 vecprio;
	u32 dest;
};

struct mpic {
	struct device_node *node;
	struct irq_domain *irqhost;
	struct irq_chip hc_irq;
	struct irq_chip hc_ipi;
	struct irq_chip hc_tm;
	struct irq_chip hc_err;
	const char *name;
	unsigned int flags;
	unsigned int isu_size;
	unsigned int isu_shift;
	unsigned int isu_mask;
	unsigned int num_sources;
	unsigned int ipi_vecs[4];
	unsigned int timer_vecs[8];
	unsigned int err_int_vecs[32];
	unsigned int spurious_vec;
	enum mpic_reg_type reg_type;
	phys_addr_t paddr;
	struct mpic_reg_bank thiscpuregs;
	struct mpic_reg_bank gregs;
	struct mpic_reg_bank tmregs;
	struct mpic_reg_bank cpuregs[32];
	struct mpic_reg_bank isus[32];
	u32 *err_regs;
	long unsigned int *protected;
	struct msi_bitmap msi_bitmap;
	struct mpic *next;
	struct mpic_irq_save *save_data;
};

struct icp_ops {
	unsigned int (*get_irq)();
	void (*eoi)(struct irq_data *);
	void (*set_priority)(unsigned char);
	void (*teardown_cpu)();
	void (*flush_ipi)();
	void (*cause_ipi)(int);
	irq_handler_t ipi_action;
};

struct ics {
	struct list_head link;
	int (*map)(struct ics *, unsigned int);
	void (*mask_unknown)(struct ics *, long unsigned int);
	long int (*get_server)(struct ics *, long unsigned int);
	int (*host_match)(struct ics *, struct device_node *);
	char data[0];
};

struct xics_cppr {
	unsigned char stack[3];
	int index;
};

struct icp_ipl {
	union {
		u32 word;
		u8 bytes[4];
	} xirr_poll;
	union {
		u32 word;
		u8 bytes[4];
	} xirr;
	u32 dummy;
	union {
		u32 word;
		u8 bytes[4];
	} qirr;
	u32 link_a;
	u32 link_b;
	u32 link_c;
};

typedef s8 int8_t;

typedef s16 int16_t;

typedef s64 int64_t;

enum {
	IRQCHIP_FWNODE_REAL = 0,
	IRQCHIP_FWNODE_NAMED = 1,
	IRQCHIP_FWNODE_NAMED_ID = 2,
};

struct xive_irq_data {
	u64 flags;
	u64 eoi_page;
	void *eoi_mmio;
	u64 trig_page;
	void *trig_mmio;
	u32 esb_shift;
	int src_chip;
	u32 hw_irq;
	int target;
	bool saved_p;
	bool stale_p;
};

struct xive_q {
	__be32 *qpage;
	u32 msk;
	u32 idx;
	u32 toggle;
	u64 eoi_phys;
	u32 esc_irq;
	atomic_t count;
	atomic_t pending_count;
	u64 guest_qaddr;
	u32 guest_qshift;
};

struct xive_cpu {
	u32 hw_ipi;
	struct xive_irq_data ipi_data;
	int chip_id;
	struct xive_q queue[8];
	u8 pending_prio;
	u8 cppr;
};

struct xive_ops {
	int (*populate_irq_data)(u32, struct xive_irq_data *);
	int (*configure_irq)(u32, u32, u8, u32);
	int (*get_irq_config)(u32, u32 *, u8 *, u32 *);
	int (*setup_queue)(unsigned int, struct xive_cpu *, u8);
	void (*cleanup_queue)(unsigned int, struct xive_cpu *, u8);
	void (*prepare_cpu)(unsigned int, struct xive_cpu *);
	void (*setup_cpu)(unsigned int, struct xive_cpu *);
	void (*teardown_cpu)(unsigned int, struct xive_cpu *);
	bool (*match)(struct device_node *);
	void (*shutdown)();
	void (*update_pending)(struct xive_cpu *);
	void (*sync_source)(u32);
	u64 (*esb_rw)(u32, u32, u64, bool);
	int (*get_ipi)(unsigned int, struct xive_cpu *);
	void (*put_ipi)(unsigned int, struct xive_cpu *);
	int (*debug_show)(struct seq_file *, void *);
	const char *name;
};

struct xive_ipi_desc {
	unsigned int irq;
	char name[16];
	atomic_t started;
};

struct xive_ipi_alloc_info {
	irq_hw_number_t hwirq;
};

enum {
	OPAL_XIVE_MODE_EMU = 0,
	OPAL_XIVE_MODE_EXPL = 1,
};

enum {
	OPAL_XIVE_IRQ_TRIGGER_PAGE = 1,
	OPAL_XIVE_IRQ_STORE_EOI = 2,
	OPAL_XIVE_IRQ_LSI = 4,
	OPAL_XIVE_IRQ_SHIFT_BUG = 8,
	OPAL_XIVE_IRQ_MASK_VIA_FW = 16,
	OPAL_XIVE_IRQ_EOI_VIA_FW = 32,
};

enum {
	OPAL_XIVE_EQ_ENABLED = 1,
	OPAL_XIVE_EQ_ALWAYS_NOTIFY = 2,
	OPAL_XIVE_EQ_ESCALATE = 4,
};

enum {
	OPAL_XIVE_VP_ENABLED = 1,
	OPAL_XIVE_VP_SINGLE_ESCALATION = 2,
};

enum {
	XIVE_SYNC_EAS = 1,
	XIVE_SYNC_QUEUE = 2,
};

struct xive_irq_bitmap {
	long unsigned int *bitmap;
	unsigned int base;
	unsigned int count;
	spinlock_t lock;
	struct list_head list;
};

struct plist_head {
	struct list_head node_list;
};

enum pm_qos_type {
	PM_QOS_UNITIALIZED = 0,
	PM_QOS_MAX = 1,
	PM_QOS_MIN = 2,
};

struct pm_qos_constraints {
	struct plist_head list;
	s32 target_value;
	s32 default_value;
	s32 no_constraint_value;
	enum pm_qos_type type;
	struct blocking_notifier_head *notifiers;
};

struct freq_constraints {
	struct pm_qos_constraints min_freq;
	struct blocking_notifier_head min_freq_notifiers;
	struct pm_qos_constraints max_freq;
	struct blocking_notifier_head max_freq_notifiers;
};

struct pm_qos_flags {
	struct list_head list;
	s32 effective_flags;
};

struct dev_pm_qos_request;

struct dev_pm_qos {
	struct pm_qos_constraints resume_latency;
	struct pm_qos_constraints latency_tolerance;
	struct freq_constraints freq;
	struct pm_qos_flags flags;
	struct dev_pm_qos_request *resume_latency_req;
	struct dev_pm_qos_request *latency_tolerance_req;
	struct dev_pm_qos_request *flags_req;
};

struct pm_qos_flags_request {
	struct list_head node;
	s32 flags;
};

enum freq_qos_req_type {
	FREQ_QOS_MIN = 1,
	FREQ_QOS_MAX = 2,
};

struct freq_qos_request {
	enum freq_qos_req_type type;
	struct plist_node pnode;
	struct freq_constraints *qos;
};

enum dev_pm_qos_req_type {
	DEV_PM_QOS_RESUME_LATENCY = 1,
	DEV_PM_QOS_LATENCY_TOLERANCE = 2,
	DEV_PM_QOS_MIN_FREQUENCY = 3,
	DEV_PM_QOS_MAX_FREQUENCY = 4,
	DEV_PM_QOS_FLAGS = 5,
};

struct dev_pm_qos_request {
	enum dev_pm_qos_req_type type;
	union {
		struct plist_node pnode;
		struct pm_qos_flags_request flr;
		struct freq_qos_request freq;
	} data;
	struct device *dev;
};

enum OpalThreadStatus {
	OPAL_THREAD_INACTIVE = 0,
	OPAL_THREAD_STARTED = 1,
	OPAL_THREAD_UNAVAILABLE = 2,
};

enum {
	OPAL_REINIT_CPUS_HILE_BE = 1,
	OPAL_REINIT_CPUS_HILE_LE = 2,
	OPAL_REINIT_CPUS_MMU_HASH = 4,
	OPAL_REINIT_CPUS_MMU_RADIX = 8,
	OPAL_REINIT_CPUS_TM_SUSPEND_DISABLED = 16,
};

enum {
	OPAL_REBOOT_NORMAL = 0,
	OPAL_REBOOT_PLATFORM_ERROR = 1,
	OPAL_REBOOT_FULL_IPL = 2,
	OPAL_REBOOT_MPIPL = 3,
	OPAL_REBOOT_FAST = 4,
};

enum OpalPendingState {
	OPAL_EVENT_OPAL_INTERNAL = 1,
	OPAL_EVENT_NVRAM = 2,
	OPAL_EVENT_RTC = 4,
	OPAL_EVENT_CONSOLE_OUTPUT = 8,
	OPAL_EVENT_CONSOLE_INPUT = 16,
	OPAL_EVENT_ERROR_LOG_AVAIL = 32,
	OPAL_EVENT_ERROR_LOG = 64,
	OPAL_EVENT_EPOW = 128,
	OPAL_EVENT_LED_STATUS = 256,
	OPAL_EVENT_PCI_ERROR = 512,
	OPAL_EVENT_DUMP_AVAIL = 1024,
	OPAL_EVENT_MSG_PENDING = 2048,
};

enum opal_msg_type {
	OPAL_MSG_ASYNC_COMP = 0,
	OPAL_MSG_MEM_ERR = 1,
	OPAL_MSG_EPOW = 2,
	OPAL_MSG_SHUTDOWN = 3,
	OPAL_MSG_HMI_EVT = 4,
	OPAL_MSG_DPO = 5,
	OPAL_MSG_PRD = 6,
	OPAL_MSG_OCC = 7,
	OPAL_MSG_PRD2 = 8,
	OPAL_MSG_TYPE_MAX = 9,
};

struct opal_msg {
	__be32 msg_type;
	__be32 reserved;
	__be64 params[8];
};

struct opal_ipmi_msg {
	uint8_t version;
	uint8_t netfn;
	uint8_t cmd;
	uint8_t data[0];
};

enum {
	OPAL_HMI_FLAGS_TB_RESYNC = 1,
	OPAL_HMI_FLAGS_DEC_LOST = 2,
	OPAL_HMI_FLAGS_HDEC_LOST = 4,
	OPAL_HMI_FLAGS_TOD_TB_FAIL = 8,
	OPAL_HMI_FLAGS_NEW_EVENT = 0,
};

struct oppanel_line {
	__be64 line;
	__be64 line_len;
};

typedef struct oppanel_line oppanel_line_t;

struct opal_sg_entry {
	__be64 data;
	__be64 length;
};

struct opal_sg_list {
	__be64 length;
	__be64 next;
	struct opal_sg_entry entry[0];
};

struct opal_i2c_request {
	uint8_t type;
	uint8_t flags;
	uint8_t subaddr_sz;
	uint8_t reserved;
	__be16 addr;
	__be16 reserved2;
	__be32 subaddr;
	__be32 size;
	__be64 buffer_ra;
};

struct opal_msg_node {
	struct list_head list;
	struct opal_msg msg;
};

struct opal {
	u64 base;
	u64 entry;
	u64 size;
};

struct mcheck_recoverable_range {
	u64 start_addr;
	u64 end_addr;
	u64 recover_addr;
};

struct opal_prd_msg;

struct semaphore {
	raw_spinlock_t lock;
	unsigned int count;
	struct list_head wait_list;
};

enum opal_async_token_state {
	ASYNC_TOKEN_UNALLOCATED = 0,
	ASYNC_TOKEN_ALLOCATED = 1,
	ASYNC_TOKEN_DISPATCHED = 2,
	ASYNC_TOKEN_ABANDONED = 3,
	ASYNC_TOKEN_COMPLETED = 4,
};

struct opal_async_token {
	enum opal_async_token_state state;
	struct opal_msg response;
};

struct pnv_idle_states_t {
	char name[16];
	u32 latency_ns;
	u32 residency_ns;
	u64 psscr_val;
	u64 psscr_mask;
	u32 flags;
	bool valid;
};

struct p7_sprs {
	u64 tscr;
	u64 worc;
	u64 sdr1;
	u64 rpr;
	u64 lpcr;
	u64 hfscr;
	u64 fscr;
	u64 purr;
	u64 spurr;
	u64 dscr;
	u64 wort;
	u64 amr;
	u64 iamr;
	u64 amor;
	u64 uamor;
};

struct p9_sprs {
	u64 ptcr;
	u64 rpr;
	u64 tscr;
	u64 ldbar;
	u64 lpcr;
	u64 hfscr;
	u64 fscr;
	u64 pid;
	u64 purr;
	u64 spurr;
	u64 dscr;
	u64 wort;
	u64 ciabr;
	u64 mmcra;
	u32 mmcr0;
	u32 mmcr1;
	u64 mmcr2;
	u64 amr;
	u64 iamr;
	u64 amor;
	u64 uamor;
};

enum OpalLPCAddressType {
	OPAL_LPC_MEM = 0,
	OPAL_LPC_IO = 1,
	OPAL_LPC_FW = 2,
};

struct lpc_debugfs_entry {
	enum OpalLPCAddressType lpc_type;
};

enum {
	IMAGE_INVALID = 0,
	IMAGE_LOADING = 1,
	IMAGE_READY = 2,
};

struct image_data_t {
	int status;
	void *data;
	uint32_t size;
};

struct image_header_t {
	uint16_t magic;
	uint16_t version;
	uint32_t size;
};

struct validate_flash_t {
	int status;
	void *buf;
	uint32_t buf_size;
	uint32_t result;
};

struct manage_flash_t {
	int status;
};

struct update_flash_t {
	int status;
};

struct powernv_rng {
	void *regs;
	void *regs_real;
	long unsigned int mask;
};

struct elog_obj {
	struct kobject kobj;
	struct bin_attribute raw_attr;
	uint64_t id;
	uint64_t type;
	size_t size;
	char *buffer;
};

struct elog_attribute {
	struct attribute attr;
	ssize_t (*show)(struct elog_obj *, struct elog_attribute *, char *);
	ssize_t (*store)(struct elog_obj *, struct elog_attribute *, const char *, size_t);
};

struct dump_obj {
	struct kobject kobj;
	struct bin_attribute dump_attr;
	uint32_t id;
	uint32_t type;
	uint32_t size;
	char *buffer;
};

struct dump_attribute {
	struct attribute attr;
	ssize_t (*show)(struct dump_obj *, struct dump_attribute *, char *);
	ssize_t (*store)(struct dump_obj *, struct dump_attribute *, const char *, size_t);
};

enum OpalSysparamPerm {
	OPAL_SYSPARAM_READ = 1,
	OPAL_SYSPARAM_WRITE = 2,
	OPAL_SYSPARAM_RW = 3,
};

struct param_attr {
	struct list_head list;
	u32 param_id;
	u32 param_size;
	struct kobj_attribute kobj_attr;
};

struct memcons {
	__be64 magic;
	__be64 obuf_phys;
	__be64 ibuf_phys;
	__be32 obuf_size;
	__be32 ibuf_size;
	__be32 out_pos;
	__be32 in_prod;
	__be32 in_cons;
};

enum OpalHMI_Version {
	OpalHMIEvt_V1 = 1,
	OpalHMIEvt_V2 = 2,
};

enum OpalHMI_Severity {
	OpalHMI_SEV_NO_ERROR = 0,
	OpalHMI_SEV_WARNING = 1,
	OpalHMI_SEV_ERROR_SYNC = 2,
	OpalHMI_SEV_FATAL = 3,
};

enum OpalHMI_Disposition {
	OpalHMI_DISPOSITION_RECOVERED = 0,
	OpalHMI_DISPOSITION_NOT_RECOVERED = 1,
};

enum OpalHMI_ErrType {
	OpalHMI_ERROR_MALFUNC_ALERT = 0,
	OpalHMI_ERROR_PROC_RECOV_DONE = 1,
	OpalHMI_ERROR_PROC_RECOV_DONE_AGAIN = 2,
	OpalHMI_ERROR_PROC_RECOV_MASKED = 3,
	OpalHMI_ERROR_TFAC = 4,
	OpalHMI_ERROR_TFMR_PARITY = 5,
	OpalHMI_ERROR_HA_OVERFLOW_WARN = 6,
	OpalHMI_ERROR_XSCOM_FAIL = 7,
	OpalHMI_ERROR_XSCOM_DONE = 8,
	OpalHMI_ERROR_SCOM_FIR = 9,
	OpalHMI_ERROR_DEBUG_TRIG_FIR = 10,
	OpalHMI_ERROR_HYP_RESOURCE = 11,
	OpalHMI_ERROR_CAPP_RECOVERY = 12,
};

enum OpalHMI_XstopType {
	CHECKSTOP_TYPE_UNKNOWN = 0,
	CHECKSTOP_TYPE_CORE = 1,
	CHECKSTOP_TYPE_NX = 2,
	CHECKSTOP_TYPE_NPU = 3,
};

enum OpalHMI_CoreXstopReason {
	CORE_CHECKSTOP_IFU_REGFILE = 1,
	CORE_CHECKSTOP_IFU_LOGIC = 2,
	CORE_CHECKSTOP_PC_DURING_RECOV = 4,
	CORE_CHECKSTOP_ISU_REGFILE = 8,
	CORE_CHECKSTOP_ISU_LOGIC = 16,
	CORE_CHECKSTOP_FXU_LOGIC = 32,
	CORE_CHECKSTOP_VSU_LOGIC = 64,
	CORE_CHECKSTOP_PC_RECOV_IN_MAINT_MODE = 128,
	CORE_CHECKSTOP_LSU_REGFILE = 256,
	CORE_CHECKSTOP_PC_FWD_PROGRESS = 512,
	CORE_CHECKSTOP_LSU_LOGIC = 1024,
	CORE_CHECKSTOP_PC_LOGIC = 2048,
	CORE_CHECKSTOP_PC_HYP_RESOURCE = 4096,
	CORE_CHECKSTOP_PC_HANG_RECOV_FAILED = 8192,
	CORE_CHECKSTOP_PC_AMBI_HANG_DETECTED = 16384,
	CORE_CHECKSTOP_PC_DEBUG_TRIG_ERR_INJ = 32768,
	CORE_CHECKSTOP_PC_SPRD_HYP_ERR_INJ = 65536,
};

enum OpalHMI_NestAccelXstopReason {
	NX_CHECKSTOP_SHM_INVAL_STATE_ERR = 1,
	NX_CHECKSTOP_DMA_INVAL_STATE_ERR_1 = 2,
	NX_CHECKSTOP_DMA_INVAL_STATE_ERR_2 = 4,
	NX_CHECKSTOP_DMA_CH0_INVAL_STATE_ERR = 8,
	NX_CHECKSTOP_DMA_CH1_INVAL_STATE_ERR = 16,
	NX_CHECKSTOP_DMA_CH2_INVAL_STATE_ERR = 32,
	NX_CHECKSTOP_DMA_CH3_INVAL_STATE_ERR = 64,
	NX_CHECKSTOP_DMA_CH4_INVAL_STATE_ERR = 128,
	NX_CHECKSTOP_DMA_CH5_INVAL_STATE_ERR = 256,
	NX_CHECKSTOP_DMA_CH6_INVAL_STATE_ERR = 512,
	NX_CHECKSTOP_DMA_CH7_INVAL_STATE_ERR = 1024,
	NX_CHECKSTOP_DMA_CRB_UE = 2048,
	NX_CHECKSTOP_DMA_CRB_SUE = 4096,
	NX_CHECKSTOP_PBI_ISN_UE = 8192,
};

struct OpalHMIEvent {
	uint8_t version;
	uint8_t severity;
	uint8_t type;
	uint8_t disposition;
	uint8_t reserved_1[4];
	__be64 hmer;
	__be64 tfmr;
	union {
		struct {
			uint8_t xstop_type;
			uint8_t reserved_1[3];
			__be32 xstop_reason;
			union {
				__be32 pir;
				__be32 chip_id;
			} u;
		} xstop_error;
	} u;
};

struct OpalHmiEvtNode {
	struct list_head list;
	struct OpalHMIEvent hmi_evt;
};

struct xstop_reason {
	uint32_t xstop_reason;
	const char *unit_failed;
	const char *description;
};

enum OpalSysEpow {
	OPAL_SYSEPOW_POWER = 0,
	OPAL_SYSEPOW_TEMP = 1,
	OPAL_SYSEPOW_COOLING = 2,
	OPAL_SYSEPOW_MAX = 3,
};

enum OpalSysPower {
	OPAL_SYSPOWER_UPS = 1,
	OPAL_SYSPOWER_CHNG = 2,
	OPAL_SYSPOWER_FAIL = 4,
	OPAL_SYSPOWER_INCL = 8,
};

struct opal_event_irqchip {
	struct irq_chip irqchip;
	struct irq_domain *domain;
	long unsigned int mask;
};

struct powercap_attr {
	u32 handle;
	struct kobj_attribute attr;
};

struct pcap {
	struct attribute_group pg;
	struct powercap_attr *pattrs;
};

struct psr_attr {
	u32 handle;
	struct kobj_attribute attr;
};

struct sg_attr {
	u32 handle;
	struct kobj_attribute attr;
};

struct sensor_group {
	char name[20];
	struct attribute_group sg;
	struct sg_attr *sgattrs;
};

struct sg_ops_info {
	int opal_no;
	const char *attr_name;
	ssize_t (*store)(struct kobject *, struct kobj_attribute *, const char *, size_t);
};

struct memcons___2;

struct split_state {
	u8 step;
	u8 master;
};

enum opal_mpipl_ops {
	OPAL_MPIPL_ADD_RANGE = 0,
	OPAL_MPIPL_REMOVE_RANGE = 1,
	OPAL_MPIPL_REMOVE_ALL = 2,
	OPAL_MPIPL_FREE_PRESERVED_MEMORY = 3,
};

enum opal_mpipl_tags {
	OPAL_MPIPL_TAG_CPU = 0,
	OPAL_MPIPL_TAG_OPAL = 1,
	OPAL_MPIPL_TAG_KERNEL = 2,
	OPAL_MPIPL_TAG_BOOT_MEM = 3,
};

struct opal_mpipl_region {
	__be64 src;
	__be64 dest;
	__be64 size;
};

struct opal_mpipl_fadump {
	u8 version;
	u8 reserved[7];
	__be32 crashing_pir;
	__be32 cpu_data_version;
	__be32 cpu_data_size;
	__be32 region_cnt;
	struct opal_mpipl_region region[0];
};

struct opal_fadump_mem_struct {
	u8 version;
	u8 reserved[3];
	u16 region_cnt;
	u16 registered_regions;
	u64 fadumphdr_addr;
	struct opal_mpipl_region rgn[128];
};

struct hdat_fadump_thread_hdr {
	__be32 pir;
	u8 core_state;
	u8 reserved[3];
	__be32 offset;
	__be32 ecnt;
	__be32 esize;
	__be32 eactsz;
};

struct hdat_fadump_reg_entry {
	__be32 reg_type;
	__be32 reg_num;
	__be64 reg_val;
};

enum OpalFreezeState {
	OPAL_EEH_STOPPED_NOT_FROZEN = 0,
	OPAL_EEH_STOPPED_MMIO_FREEZE = 1,
	OPAL_EEH_STOPPED_DMA_FREEZE = 2,
	OPAL_EEH_STOPPED_MMIO_DMA_FREEZE = 3,
	OPAL_EEH_STOPPED_RESET = 4,
	OPAL_EEH_STOPPED_TEMP_UNAVAIL = 5,
	OPAL_EEH_STOPPED_PERM_UNAVAIL = 6,
};

enum OpalEehFreezeActionToken {
	OPAL_EEH_ACTION_CLEAR_FREEZE_MMIO = 1,
	OPAL_EEH_ACTION_CLEAR_FREEZE_DMA = 2,
	OPAL_EEH_ACTION_CLEAR_FREEZE_ALL = 3,
	OPAL_EEH_ACTION_SET_FREEZE_MMIO = 1,
	OPAL_EEH_ACTION_SET_FREEZE_DMA = 2,
	OPAL_EEH_ACTION_SET_FREEZE_ALL = 3,
};

enum {
	OPAL_PHB_ERROR_DATA_TYPE_P7IOC = 1,
	OPAL_PHB_ERROR_DATA_TYPE_PHB3 = 2,
	OPAL_PHB_ERROR_DATA_TYPE_PHB4 = 3,
};

struct OpalIoPhbErrorCommon {
	__be32 version;
	__be32 ioType;
	__be32 len;
};

struct OpalIoP7IOCPhbErrorData {
	struct OpalIoPhbErrorCommon common;
	__be32 brdgCtl;
	__be32 portStatusReg;
	__be32 rootCmplxStatus;
	__be32 busAgentStatus;
	__be32 deviceStatus;
	__be32 slotStatus;
	__be32 linkStatus;
	__be32 devCmdStatus;
	__be32 devSecStatus;
	__be32 rootErrorStatus;
	__be32 uncorrErrorStatus;
	__be32 corrErrorStatus;
	__be32 tlpHdr1;
	__be32 tlpHdr2;
	__be32 tlpHdr3;
	__be32 tlpHdr4;
	__be32 sourceId;
	__be32 rsv3;
	__be64 errorClass;
	__be64 correlator;
	__be64 p7iocPlssr;
	__be64 p7iocCsr;
	__be64 lemFir;
	__be64 lemErrorMask;
	__be64 lemWOF;
	__be64 phbErrorStatus;
	__be64 phbFirstErrorStatus;
	__be64 phbErrorLog0;
	__be64 phbErrorLog1;
	__be64 mmioErrorStatus;
	__be64 mmioFirstErrorStatus;
	__be64 mmioErrorLog0;
	__be64 mmioErrorLog1;
	__be64 dma0ErrorStatus;
	__be64 dma0FirstErrorStatus;
	__be64 dma0ErrorLog0;
	__be64 dma0ErrorLog1;
	__be64 dma1ErrorStatus;
	__be64 dma1FirstErrorStatus;
	__be64 dma1ErrorLog0;
	__be64 dma1ErrorLog1;
	__be64 pestA[128];
	__be64 pestB[128];
};

struct OpalIoPhb3ErrorData {
	struct OpalIoPhbErrorCommon common;
	__be32 brdgCtl;
	__be32 portStatusReg;
	__be32 rootCmplxStatus;
	__be32 busAgentStatus;
	__be32 deviceStatus;
	__be32 slotStatus;
	__be32 linkStatus;
	__be32 devCmdStatus;
	__be32 devSecStatus;
	__be32 rootErrorStatus;
	__be32 uncorrErrorStatus;
	__be32 corrErrorStatus;
	__be32 tlpHdr1;
	__be32 tlpHdr2;
	__be32 tlpHdr3;
	__be32 tlpHdr4;
	__be32 sourceId;
	__be32 rsv3;
	__be64 errorClass;
	__be64 correlator;
	__be64 nFir;
	__be64 nFirMask;
	__be64 nFirWOF;
	__be64 phbPlssr;
	__be64 phbCsr;
	__be64 lemFir;
	__be64 lemErrorMask;
	__be64 lemWOF;
	__be64 phbErrorStatus;
	__be64 phbFirstErrorStatus;
	__be64 phbErrorLog0;
	__be64 phbErrorLog1;
	__be64 mmioErrorStatus;
	__be64 mmioFirstErrorStatus;
	__be64 mmioErrorLog0;
	__be64 mmioErrorLog1;
	__be64 dma0ErrorStatus;
	__be64 dma0FirstErrorStatus;
	__be64 dma0ErrorLog0;
	__be64 dma0ErrorLog1;
	__be64 dma1ErrorStatus;
	__be64 dma1FirstErrorStatus;
	__be64 dma1ErrorLog0;
	__be64 dma1ErrorLog1;
	__be64 pestA[256];
	__be64 pestB[256];
};

struct OpalIoPhb4ErrorData {
	struct OpalIoPhbErrorCommon common;
	__be32 brdgCtl;
	__be32 deviceStatus;
	__be32 slotStatus;
	__be32 linkStatus;
	__be32 devCmdStatus;
	__be32 devSecStatus;
	__be32 rootErrorStatus;
	__be32 uncorrErrorStatus;
	__be32 corrErrorStatus;
	__be32 tlpHdr1;
	__be32 tlpHdr2;
	__be32 tlpHdr3;
	__be32 tlpHdr4;
	__be32 sourceId;
	__be64 nFir;
	__be64 nFirMask;
	__be64 nFirWOF;
	__be64 phbPlssr;
	__be64 phbCsr;
	__be64 lemFir;
	__be64 lemErrorMask;
	__be64 lemWOF;
	__be64 phbErrorStatus;
	__be64 phbFirstErrorStatus;
	__be64 phbErrorLog0;
	__be64 phbErrorLog1;
	__be64 phbTxeErrorStatus;
	__be64 phbTxeFirstErrorStatus;
	__be64 phbTxeErrorLog0;
	__be64 phbTxeErrorLog1;
	__be64 phbRxeArbErrorStatus;
	__be64 phbRxeArbFirstErrorStatus;
	__be64 phbRxeArbErrorLog0;
	__be64 phbRxeArbErrorLog1;
	__be64 phbRxeMrgErrorStatus;
	__be64 phbRxeMrgFirstErrorStatus;
	__be64 phbRxeMrgErrorLog0;
	__be64 phbRxeMrgErrorLog1;
	__be64 phbRxeTceErrorStatus;
	__be64 phbRxeTceFirstErrorStatus;
	__be64 phbRxeTceErrorLog0;
	__be64 phbRxeTceErrorLog1;
	__be64 phbPblErrorStatus;
	__be64 phbPblFirstErrorStatus;
	__be64 phbPblErrorLog0;
	__be64 phbPblErrorLog1;
	__be64 phbPcieDlpErrorLog1;
	__be64 phbPcieDlpErrorLog2;
	__be64 phbPcieDlpErrorStatus;
	__be64 phbRegbErrorStatus;
	__be64 phbRegbFirstErrorStatus;
	__be64 phbRegbErrorLog0;
	__be64 phbRegbErrorLog1;
	__be64 pestA[512];
	__be64 pestB[512];
};

enum pnv_phb_type {
	PNV_PHB_IODA1 = 0,
	PNV_PHB_IODA2 = 1,
	PNV_PHB_NPU_OCAPI = 2,
};

enum pnv_phb_model {
	PNV_PHB_MODEL_UNKNOWN = 0,
	PNV_PHB_MODEL_P7IOC = 1,
	PNV_PHB_MODEL_PHB3 = 2,
};

struct pnv_phb;

struct pnv_ioda_pe {
	long unsigned int flags;
	struct pnv_phb *phb;
	int device_count;
	struct pci_dev *parent_dev;
	struct pci_dev *pdev;
	struct pci_bus *pbus;
	unsigned int rid;
	unsigned int pe_number;
	struct iommu_table_group table_group;
	bool tce_bypass_enabled;
	uint64_t tce_bypass_base;
	bool dma_setup_done;
	int mve_number;
	struct pnv_ioda_pe *master;
	struct list_head slaves;
	struct list_head list;
};

struct pnv_phb {
	struct pci_controller *hose;
	enum pnv_phb_type type;
	enum pnv_phb_model model;
	u64 hub_id;
	u64 opal_id;
	int flags;
	void *regs;
	u64 regs_phys;
	spinlock_t lock;
	int has_dbgfs;
	struct dentry *dbgfs;
	unsigned int msi_base;
	unsigned int msi32_support;
	struct msi_bitmap msi_bmp;
	int (*msi_setup)(struct pnv_phb *, struct pci_dev *, unsigned int, unsigned int, unsigned int, struct msi_msg *);
	int (*init_m64)(struct pnv_phb *);
	int (*get_pe_state)(struct pnv_phb *, int);
	void (*freeze_pe)(struct pnv_phb *, int);
	int (*unfreeze_pe)(struct pnv_phb *, int, int);
	struct {
		unsigned int total_pe_num;
		unsigned int reserved_pe_idx;
		unsigned int root_pe_idx;
		unsigned int m32_size;
		unsigned int m32_segsize;
		unsigned int m32_pci_base;
		unsigned int m64_bar_idx;
		long unsigned int m64_size;
		long unsigned int m64_segsize;
		long unsigned int m64_base;
		long unsigned int m64_bar_alloc;
		unsigned int io_size;
		unsigned int io_segsize;
		unsigned int io_pci_base;
		struct mutex pe_alloc_mutex;
		long unsigned int *pe_alloc;
		struct pnv_ioda_pe *pe_array;
		unsigned int *m64_segmap;
		unsigned int *m32_segmap;
		unsigned int *io_segmap;
		unsigned int dma32_count;
		unsigned int *dma32_segmap;
		int irq_chip_init;
		struct irq_chip irq_chip;
		struct list_head pe_list;
		struct mutex pe_list_mutex;
		unsigned int pe_rmap[65536];
	} ioda;
	unsigned int diag_data_size;
	u8 *diag_data;
};

struct va_format {
	const char *fmt;
	va_list *va;
};

enum OpalMmioWindowType {
	OPAL_M32_WINDOW_TYPE = 1,
	OPAL_M64_WINDOW_TYPE = 2,
	OPAL_IO_WINDOW_TYPE = 3,
};

enum OpalPciBusCompare {
	OpalPciBusAny = 0,
	OpalPciBus3Bits = 2,
	OpalPciBus4Bits = 3,
	OpalPciBus5Bits = 4,
	OpalPciBus6Bits = 5,
	OpalPciBus7Bits = 6,
	OpalPciBusAll = 7,
};

enum OpalDeviceCompare {
	OPAL_IGNORE_RID_DEVICE_NUMBER = 0,
	OPAL_COMPARE_RID_DEVICE_NUMBER = 1,
};

enum OpalFuncCompare {
	OPAL_IGNORE_RID_FUNCTION_NUMBER = 0,
	OPAL_COMPARE_RID_FUNCTION_NUMBER = 1,
};

enum OpalPeAction {
	OPAL_UNMAP_PE = 0,
	OPAL_MAP_PE = 1,
};

enum OpalPeltvAction {
	OPAL_REMOVE_PE_FROM_DOMAIN = 0,
	OPAL_ADD_PE_TO_DOMAIN = 1,
};

enum OpalMveEnableAction {
	OPAL_DISABLE_MVE = 0,
	OPAL_ENABLE_MVE = 1,
};

enum OpalM64Action {
	OPAL_DISABLE_M64 = 0,
	OPAL_ENABLE_M64_SPLIT = 1,
	OPAL_ENABLE_M64_NON_SPLIT = 2,
};

enum OpalPciResetScope {
	OPAL_RESET_PHB_COMPLETE = 1,
	OPAL_RESET_PCI_LINK = 2,
	OPAL_RESET_PHB_ERROR = 3,
	OPAL_RESET_PCI_HOT = 4,
	OPAL_RESET_PCI_FUNDAMENTAL = 5,
	OPAL_RESET_PCI_IODA_TABLE = 6,
};

enum OpalPciResetState {
	OPAL_DEASSERT_RESET = 0,
	OPAL_ASSERT_RESET = 1,
};

enum {
	OPAL_PCI_TCE_KILL_PAGES = 0,
	OPAL_PCI_TCE_KILL_PE = 1,
	OPAL_PCI_TCE_KILL_ALL = 2,
};

struct iommu_table_group_link {
	struct list_head next;
	struct callback_head rcu;
	struct iommu_table_group *table_group;
};

struct pnv_iov_data {
	u16 num_vfs;
	struct pnv_ioda_pe *vf_pe_arr;
	bool m64_single_mode[6];
	bool need_shift;
	long unsigned int used_m64_bar_mask[1];
	struct resource holes[6];
};

struct cxl_irq_ranges {
	irq_hw_number_t offset[4];
	irq_hw_number_t range[4];
};

enum OpalPciStatusToken {
	OPAL_EEH_NO_ERROR = 0,
	OPAL_EEH_IOC_ERROR = 1,
	OPAL_EEH_PHB_ERROR = 2,
	OPAL_EEH_PE_ERROR = 3,
	OPAL_EEH_PE_MMIO_ERROR = 4,
	OPAL_EEH_PE_DMA_ERROR = 5,
};

enum OpalPciErrorSeverity {
	OPAL_EEH_SEV_NO_ERROR = 0,
	OPAL_EEH_SEV_IOC_DEAD = 1,
	OPAL_EEH_SEV_PHB_DEAD = 2,
	OPAL_EEH_SEV_PHB_FENCED = 3,
	OPAL_EEH_SEV_PE_ER = 4,
	OPAL_EEH_SEV_INF = 5,
};

enum OpalErrinjectType {
	OPAL_ERR_INJECT_TYPE_IOA_BUS_ERR = 0,
	OPAL_ERR_INJECT_TYPE_IOA_BUS_ERR64 = 1,
};

enum OpalErrinjectFunc {
	OPAL_ERR_INJECT_FUNC_IOA_LD_MEM_ADDR = 0,
	OPAL_ERR_INJECT_FUNC_IOA_LD_MEM_DATA = 1,
	OPAL_ERR_INJECT_FUNC_IOA_LD_IO_ADDR = 2,
	OPAL_ERR_INJECT_FUNC_IOA_LD_IO_DATA = 3,
	OPAL_ERR_INJECT_FUNC_IOA_LD_CFG_ADDR = 4,
	OPAL_ERR_INJECT_FUNC_IOA_LD_CFG_DATA = 5,
	OPAL_ERR_INJECT_FUNC_IOA_ST_MEM_ADDR = 6,
	OPAL_ERR_INJECT_FUNC_IOA_ST_MEM_DATA = 7,
	OPAL_ERR_INJECT_FUNC_IOA_ST_IO_ADDR = 8,
	OPAL_ERR_INJECT_FUNC_IOA_ST_IO_DATA = 9,
	OPAL_ERR_INJECT_FUNC_IOA_ST_CFG_ADDR = 10,
	OPAL_ERR_INJECT_FUNC_IOA_ST_CFG_DATA = 11,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_RD_ADDR = 12,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_RD_DATA = 13,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_RD_MASTER = 14,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_RD_TARGET = 15,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_WR_ADDR = 16,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_WR_DATA = 17,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_WR_MASTER = 18,
	OPAL_ERR_INJECT_FUNC_IOA_DMA_WR_TARGET = 19,
};

enum OpalPciReinitScope {
	OPAL_REINIT_PCI_DEV = 1000,
};

enum {
	OPAL_P7IOC_DIAG_TYPE_NONE = 0,
	OPAL_P7IOC_DIAG_TYPE_RGC = 1,
	OPAL_P7IOC_DIAG_TYPE_BI = 2,
	OPAL_P7IOC_DIAG_TYPE_CI = 3,
	OPAL_P7IOC_DIAG_TYPE_MISC = 4,
	OPAL_P7IOC_DIAG_TYPE_I2C = 5,
	OPAL_P7IOC_DIAG_TYPE_LAST = 6,
};

struct OpalIoP7IOCRgcErrorData {
	__be64 rgcStatus;
	__be64 rgcLdcp;
};

struct OpalIoP7IOCBiErrorData {
	__be64 biLdcp0;
	__be64 biLdcp1;
	__be64 biLdcp2;
	__be64 biFenceStatus;
	uint8_t biDownbound;
};

struct OpalIoP7IOCCiErrorData {
	__be64 ciPortStatus;
	__be64 ciPortLdcp;
	uint8_t ciPort;
};

struct OpalIoP7IOCErrorData {
	__be16 type;
	__be64 gemXfir;
	__be64 gemRfir;
	__be64 gemRirqfir;
	__be64 gemMask;
	__be64 gemRwof;
	__be64 lemFir;
	__be64 lemErrMask;
	__be64 lemAction0;
	__be64 lemAction1;
	__be64 lemWof;
	union {
		struct OpalIoP7IOCRgcErrorData rgc;
		struct OpalIoP7IOCBiErrorData bi;
		struct OpalIoP7IOCCiErrorData ci;
	};
};

enum OpalMemErr_Version {
	OpalMemErr_V1 = 1,
};

enum OpalMemErrType {
	OPAL_MEM_ERR_TYPE_RESILIENCE = 0,
	OPAL_MEM_ERR_TYPE_DYN_DALLOC = 1,
};

enum OpalMemErr_ResilErrType {
	OPAL_MEM_RESILIENCE_CE = 0,
	OPAL_MEM_RESILIENCE_UE = 1,
	OPAL_MEM_RESILIENCE_UE_SCRUB = 2,
};

enum OpalMemErr_DynErrType {
	OPAL_MEM_DYNAMIC_DEALLOC = 0,
};

struct OpalMemoryErrorData {
	enum OpalMemErr_Version version: 8;
	enum OpalMemErrType type: 8;
	__be16 flags;
	uint8_t reserved_1[4];
	union {
		struct {
			enum OpalMemErr_ResilErrType resil_err_type: 8;
			uint8_t reserved_1[7];
			__be64 physical_address_start;
			__be64 physical_address_end;
		} resilience;
		struct {
			enum OpalMemErr_DynErrType dyn_err_type: 8;
			uint8_t reserved_1[7];
			__be64 physical_address_start;
			__be64 physical_address_end;
		} dyn_dealloc;
	} u;
};

struct OpalMsgNode {
	struct list_head list;
	struct opal_msg msg;
};

struct platform_driver {
	int (*probe)(struct platform_device *);
	int (*remove)(struct platform_device *);
	void (*shutdown)(struct platform_device *);
	int (*suspend)(struct platform_device *, pm_message_t);
	int (*resume)(struct platform_device *);
	struct device_driver driver;
	const struct platform_device_id *id_table;
	bool prevent_deferred_probe;
	bool driver_managed_dma;
};

enum {
	OPAL_IMC_COUNTERS_NEST = 1,
	OPAL_IMC_COUNTERS_CORE = 2,
	OPAL_IMC_COUNTERS_TRACE = 3,
};

struct imc_mem_info {
	u64 *vbase;
	u32 id;
};

struct imc_events {
	u32 value;
	char *name;
	char *unit;
	char *scale;
};

struct imc_pmu {
	struct pmu pmu;
	struct imc_mem_info *mem_info;
	struct imc_events *events;
	const struct attribute_group *attr_groups[4];
	u32 counter_mem_size;
	int domain;
	bool imc_counter_mmaped;
};

enum {
	IMC_TYPE_THREAD = 1,
	IMC_TYPE_TRACE = 2,
	IMC_TYPE_CORE = 4,
	IMC_TYPE_CHIP = 16,
};

enum vas_cop_type {
	VAS_COP_TYPE_FAULT = 0,
	VAS_COP_TYPE_842 = 1,
	VAS_COP_TYPE_842_HIPRI = 2,
	VAS_COP_TYPE_GZIP = 3,
	VAS_COP_TYPE_GZIP_HIPRI = 4,
	VAS_COP_TYPE_FTW = 5,
	VAS_COP_TYPE_MAX = 6,
};

struct vas_user_win_ref {
	struct pid *pid;
	struct pid *tgid;
	struct mm_struct *mm;
	struct mutex mmap_mutex;
	struct vm_area_struct *vma;
};

struct vas_window {
	u32 winid;
	u32 wcreds_max;
	u32 status;
	enum vas_cop_type cop;
	struct vas_user_win_ref task_ref;
	char *dbgname;
	struct dentry *dbgdir;
};

struct pnv_vas_window;

struct vas_instance {
	int vas_id;
	struct ida ida;
	struct list_head node;
	struct platform_device *pdev;
	u64 hvwc_bar_start;
	u64 uwc_bar_start;
	u64 paste_base_addr;
	u64 paste_win_id_shift;
	u64 irq_port;
	int virq;
	int fault_crbs;
	int fault_fifo_size;
	int fifo_in_progress;
	spinlock_t fault_lock;
	void *fault_fifo;
	struct pnv_vas_window *fault_win;
	struct mutex mutex;
	struct pnv_vas_window *rxwin[6];
	struct pnv_vas_window *windows[65536];
	char *name;
	char *dbgname;
	struct dentry *dbgdir;
};

struct pnv_vas_window {
	struct vas_window vas_win;
	struct vas_instance *vinst;
	bool tx_win;
	bool nx_win;
	bool user_win;
	void *hvwc_map;
	void *uwc_map;
	void *paste_kaddr;
	char *paste_addr_name;
	struct pnv_vas_window *rxwin;
	atomic_t num_txwins;
};

struct vas_user_win_ops {
	struct vas_window * (*open_win)(int, u64, enum vas_cop_type);
	u64 (*paste_addr)(struct vas_window *);
	int (*close_win)(struct vas_window *);
};

struct vas_rx_win_attr {
	void *rx_fifo;
	int rx_fifo_size;
	int wcreds_max;
	bool pin_win;
	bool rej_no_credit;
	bool tx_wcred_mode;
	bool rx_wcred_mode;
	bool tx_win_ord_mode;
	bool rx_win_ord_mode;
	bool data_stamp;
	bool nx_win;
	bool fault_win;
	bool user_win;
	bool notify_disable;
	bool intr_disable;
	bool notify_early;
	int lnotify_lpid;
	int lnotify_pid;
	int lnotify_tid;
	u32 pswid;
	int tc_mode;
};

struct vas_tx_win_attr {
	enum vas_cop_type cop;
	int wcreds_max;
	int lpid;
	int pidr;
	int pswid;
	int rsvd_txbuf_count;
	int tc_mode;
	bool user_win;
	bool pin_win;
	bool rej_no_credit;
	bool rsvd_txbuf_enable;
	bool tx_wcred_mode;
	bool rx_wcred_mode;
	bool tx_win_ord_mode;
	bool rx_win_ord_mode;
};

enum vas_notify_scope {
	VAS_SCOPE_LOCAL = 0,
	VAS_SCOPE_GROUP = 1,
	VAS_SCOPE_VECTORED_GROUP = 2,
	VAS_SCOPE_UNUSED = 3,
};

enum vas_dma_type {
	VAS_DMA_TYPE_INJECT = 0,
	VAS_DMA_TYPE_WRITE = 1,
};

enum vas_notify_after_count {
	VAS_NOTIFY_AFTER_256 = 0,
	VAS_NOTIFY_NONE = 1,
	VAS_NOTIFY_AFTER_2 = 2,
};

struct vas_winctx {
	void *rx_fifo;
	int rx_fifo_size;
	int wcreds_max;
	int rsvd_txbuf_count;
	bool user_win;
	bool nx_win;
	bool fault_win;
	bool rsvd_txbuf_enable;
	bool pin_win;
	bool rej_no_credit;
	bool tx_wcred_mode;
	bool rx_wcred_mode;
	bool tx_word_mode;
	bool rx_word_mode;
	bool data_stamp;
	bool xtra_write;
	bool notify_disable;
	bool intr_disable;
	bool fifo_disable;
	bool notify_early;
	bool notify_os_intr_reg;
	int lpid;
	int pidr;
	int lnotify_lpid;
	int lnotify_pid;
	int lnotify_tid;
	u32 pswid;
	int rx_win_id;
	int fault_win_id;
	int tc_mode;
	u64 irq_port;
	enum vas_dma_type dma_type;
	enum vas_notify_scope min_scope;
	enum vas_notify_scope max_scope;
	enum vas_notify_after_count notify_after_count;
};

struct trace_event_raw_vas_rx_win_open {
	struct trace_entry ent;
	struct task_struct *tsk;
	int pid;
	int cop;
	int vasid;
	struct vas_rx_win_attr *rxattr;
	int lnotify_lpid;
	int lnotify_pid;
	int lnotify_tid;
	char __data[0];
};

struct trace_event_raw_vas_tx_win_open {
	struct trace_entry ent;
	struct task_struct *tsk;
	int pid;
	int cop;
	int vasid;
	struct vas_tx_win_attr *txattr;
	int lpid;
	int pidr;
	char __data[0];
};

struct trace_event_raw_vas_paste_crb {
	struct trace_entry ent;
	struct task_struct *tsk;
	struct vas_window *win;
	int pid;
	int vasid;
	int winid;
	long unsigned int paste_kaddr;
	char __data[0];
};

struct trace_event_data_offsets_vas_rx_win_open {};

struct trace_event_data_offsets_vas_tx_win_open {};

struct trace_event_data_offsets_vas_paste_crb {};

typedef void (*btf_trace_vas_rx_win_open)(void *, struct task_struct *, int, int, struct vas_rx_win_attr *);

typedef void (*btf_trace_vas_tx_win_open)(void *, struct task_struct *, int, int, struct vas_tx_win_attr *);

typedef void (*btf_trace_vas_paste_crb)(void *, struct task_struct *, struct pnv_vas_window *);

struct coprocessor_completion_block {
	__be64 value;
	__be64 address;
};

struct coprocessor_status_block {
	u8 flags;
	u8 cs;
	u8 cc;
	u8 ce;
	__be32 count;
	__be64 address;
};

struct data_descriptor_entry {
	__be16 flags;
	u8 count;
	u8 index;
	__be32 length;
	__be64 address;
};

struct nx_fault_stamp {
	__be64 fault_storage_addr;
	__be16 reserved;
	__u8 flags;
	__u8 fault_status;
	__be32 pswid;
};

struct coprocessor_request_block {
	__be32 ccw;
	__be32 flags;
	__be64 csb_addr;
	struct data_descriptor_entry source;
	struct data_descriptor_entry target;
	struct coprocessor_completion_block ccb;
	union {
		struct nx_fault_stamp nx;
		u8 reserved[16];
	} stamp;
	u8 reserved[32];
	struct coprocessor_status_block csb;
};

struct actag_range {
	u16 start;
	u16 count;
};

struct npu_link {
	struct list_head list;
	int domain;
	int bus;
	int dev;
	u16 fn_desired_actags[8];
	struct actag_range fn_actags[8];
	bool assignment_done;
};

struct spa_data {
	u64 phb_opal_id;
	u32 bdfn;
};

struct debugfs_blob_wrapper {
	void *data;
	long unsigned int size;
};

struct scom_debug_entry {
	u32 chip;
	struct debugfs_blob_wrapper path;
	char name[16];
};

struct hvcall_mpp_data {
	long unsigned int entitled_mem;
	long unsigned int mapped_mem;
	short unsigned int group_num;
	short unsigned int pool_num;
	unsigned char mem_weight;
	unsigned char unallocated_mem_weight;
	long unsigned int unallocated_entitlement;
	long unsigned int pool_size;
	long int loan_request;
	long unsigned int backing_mem;
};

struct hvcall_mpp_x_data {
	long unsigned int coalesced_bytes;
	long unsigned int pool_coalesced_bytes;
	long unsigned int pool_purr_cycles;
	long unsigned int pool_spurr_cycles;
	long unsigned int reserved[3];
};

struct dtl_entry {
	u8 dispatch_reason;
	u8 preempt_reason;
	__be16 processor_id;
	__be32 enqueue_to_dispatch_time;
	__be32 ready_to_enqueue_time;
	__be32 waiting_to_ready_time;
	__be64 timebase;
	__be64 fault_addr;
	__be64 srr0;
	__be64 srr1;
};

struct dtl_worker {
	struct delayed_work work;
	int cpu;
};

struct vcpu_dispatch_data {
	int last_disp_cpu;
	int total_disp;
	int same_cpu_disp;
	int same_chip_disp;
	int diff_chip_disp;
	int far_chip_disp;
	int numa_home_disp;
	int numa_remote_disp;
	int numa_far_disp;
};

struct hpt_resize_state {
	long unsigned int shift;
	int commit_rc;
};

struct of_drc_info {
	char *drc_type;
	char *drc_name_prefix;
	u32 drc_index_start;
	u32 drc_name_suffix_start;
	u32 num_sequential_elems;
	u32 sequential_inc;
	u32 drc_power_domain;
	u32 last_drc_index;
};

struct h_cpu_char_result {
	u64 character;
	u64 behaviour;
};

struct of_reconfig_data {
	struct device_node *dn;
	struct property *prop;
	struct property *old_prop;
};

enum rtas_iov_fw_value_map {
	NUM_RES_PROPERTY = 0,
	LOW_INT = 1,
	START_OF_ENTRIES = 2,
	APERTURE_PROPERTY = 2,
	WDW_SIZE_PROPERTY = 4,
	NEXT_ENTRY = 7,
};

enum get_iov_fw_value_index {
	BAR_ADDRS = 1,
	APERTURE_SIZE = 2,
	WDW_SIZE = 3,
};

struct memory_notify {
	long unsigned int start_pfn;
	long unsigned int nr_pages;
	int status_change_nid_normal;
	int status_change_nid;
};

enum {
	DDW_QUERY_PE_DMA_WIN = 0,
	DDW_CREATE_PE_DMA_WIN = 1,
	DDW_REMOVE_PE_DMA_WIN = 2,
	DDW_APPLICABLE_SIZE = 3,
};

enum {
	DDW_EXT_SIZE = 0,
	DDW_EXT_RESET_DMA_WIN = 1,
	DDW_EXT_QUERY_OUT_SIZE = 2,
};

struct dynamic_dma_window_prop {
	__be32 liobn;
	__be64 dma_base;
	__be32 tce_shift;
	__be32 window_shift;
};

struct direct_window {
	struct device_node *device;
	const struct dynamic_dma_window_prop *prop;
	struct list_head list;
};

struct ddw_query_response {
	u32 windows_available;
	u64 largest_available_block;
	u32 page_size;
	u32 migration_capable;
};

struct ddw_create_response {
	u32 liobn;
	u32 addr_hi;
	u32 addr_lo;
};

struct failed_ddw_pdn {
	struct device_node *pdn;
	struct list_head list;
};

struct pseries_hp_errorlog {
	u8 resource;
	u8 action;
	u8 id_type;
	u8 reserved;
	union {
		__be32 drc_index;
		__be32 drc_count;
		struct {
			__be32 count;
			__be32 index;
		} ic;
		char drc_name[1];
	} _drc_u;
};

struct pseries_mc_errorlog {
	__be32 fru_id;
	__be32 proc_id;
	u8 error_type;
	u8 sub_err_type;
	u8 reserved_1[6];
	__be64 effective_address;
	__be64 logical_address;
};

struct epow_errorlog {
	unsigned char sensor_value;
	unsigned char event_modifier;
	unsigned char extended_modifier;
	unsigned char reserved;
	unsigned char platform_reason;
};

struct hypertas_fw_feature {
	long unsigned int val;
	char *name;
};

struct vec5_fw_feature {
	long unsigned int val;
	unsigned int feature;
};

enum {
	WQ_UNBOUND = 2,
	WQ_FREEZABLE = 4,
	WQ_MEM_RECLAIM = 8,
	WQ_HIGHPRI = 16,
	WQ_CPU_INTENSIVE = 32,
	WQ_SYSFS = 64,
	WQ_POWER_EFFICIENT = 128,
	__WQ_DRAINING = 65536,
	__WQ_ORDERED = 131072,
	__WQ_LEGACY = 262144,
	__WQ_ORDERED_EXPLICIT = 524288,
	WQ_MAX_ACTIVE = 512,
	WQ_MAX_UNBOUND_PER_CPU = 4,
	WQ_DFL_ACTIVE = 256,
};

struct class_attribute {
	struct attribute attr;
	ssize_t (*show)(struct class *, struct class_attribute *, char *);
	ssize_t (*store)(struct class *, struct class_attribute *, const char *, size_t);
};

struct pseries_hp_work {
	struct work_struct work;
	struct pseries_hp_errorlog *errlog;
};

struct cc_workarea {
	__be32 drc_index;
	__be32 zero;
	__be32 name_offset;
	__be32 prop_length;
	__be32 prop_offset;
};

struct class_attribute_string {
	struct class_attribute attr;
	char *str;
};

enum vas_migrate_action {
	VAS_SUSPEND = 0,
	VAS_RESUME = 1,
};

struct update_props_workarea {
	__be32 phandle;
	__be32 state;
	__be64 reserved;
	__be32 nprops;
} __attribute__((packed));

struct pseries_suspend_info {
	atomic_t counter;
	bool done;
};

enum vasi_aborting_entity {
	ORCHESTRATOR = 1,
	VSP_SOURCE = 2,
	PARTITION_FIRMWARE = 3,
	PLATFORM_FIRMWARE = 4,
	VSP_TARGET = 5,
	MIGRATING_PARTITION = 6,
};

enum pci_bus_speed {
	PCI_SPEED_33MHz = 0,
	PCI_SPEED_66MHz = 1,
	PCI_SPEED_66MHz_PCIX = 2,
	PCI_SPEED_100MHz_PCIX = 3,
	PCI_SPEED_133MHz_PCIX = 4,
	PCI_SPEED_66MHz_PCIX_ECC = 5,
	PCI_SPEED_100MHz_PCIX_ECC = 6,
	PCI_SPEED_133MHz_PCIX_ECC = 7,
	PCI_SPEED_66MHz_PCIX_266 = 9,
	PCI_SPEED_100MHz_PCIX_266 = 10,
	PCI_SPEED_133MHz_PCIX_266 = 11,
	AGP_UNKNOWN = 12,
	AGP_1X = 13,
	AGP_2X = 14,
	AGP_4X = 15,
	AGP_8X = 16,
	PCI_SPEED_66MHz_PCIX_533 = 17,
	PCI_SPEED_100MHz_PCIX_533 = 18,
	PCI_SPEED_133MHz_PCIX_533 = 19,
	PCIE_SPEED_2_5GT = 20,
	PCIE_SPEED_5_0GT = 21,
	PCIE_SPEED_8_0GT = 22,
	PCIE_SPEED_16_0GT = 23,
	PCIE_SPEED_32_0GT = 24,
	PCIE_SPEED_64_0GT = 25,
	PCI_SPEED_UNKNOWN = 255,
};

struct pe_map_bar_entry {
	__be64 bar;
	__be16 rid;
	__be16 pe_num;
	__be32 reserved;
};

struct msi_counts {
	struct device_node *requestor;
	int num_devices;
	int request;
	int quota;
	int spare;
	int over_quota;
};

struct energy_scale_attribute {
	__be64 id;
	__be64 val;
	u8 desc[64];
	u8 value_desc[64];
};

struct h_energy_scale_info_hdr {
	__be64 num_attrs;
	__be64 array_offset;
	u8 data_header_version;
} __attribute__((packed));

struct papr_attr {
	u64 id;
	struct kobj_attribute kobj_attr;
};

struct papr_group {
	struct attribute_group pg;
	struct papr_attr pgattrs[3];
};

struct papr_ops_info {
	const char *attr_name;
	ssize_t (*show)(struct kobject *, struct kobj_attribute *, char *);
};

typedef int mhp_t;

struct memory_group {
	int nid;
	struct list_head memory_blocks;
	long unsigned int present_kernel_pages;
	long unsigned int present_movable_pages;
	bool is_dynamic;
	union {
		struct {
			long unsigned int max_pages;
		} s;
		struct {
			long unsigned int unit_pages;
		} d;
	};
};

struct memory_block {
	long unsigned int start_section_nr;
	long unsigned int state;
	int online_type;
	int nid;
	struct zone *zone;
	struct device dev;
	long unsigned int nr_vmemmap_pages;
	struct memory_group *group;
	struct list_head group_next;
};

struct module_version_attribute {
	struct module_attribute mattr;
	const char *module_name;
	const char *version;
};

struct dev_ext_attribute {
	struct device_attribute attr;
	void *var;
};

struct pseudo_fs_context {
	const struct super_operations *ops;
	const struct xattr_handler **xattr;
	const struct dentry_operations *dops;
	long unsigned int magic;
};

struct balloon_dev_info {
	long unsigned int isolated_pages;
	spinlock_t pages_lock;
	struct list_head pages;
	int (*migratepage)(struct balloon_dev_info *, struct page *, struct page *, enum migrate_mode);
	struct inode *inode;
};

struct dtl {
	struct dtl_entry *buf;
	int cpu;
	int buf_entries;
	u64 last_idx;
	spinlock_t lock;
};

struct pseries_io_event {
	uint8_t event_type;
	uint8_t rpc_data_len;
	uint8_t scope;
	uint8_t event_subtype;
	uint32_t drc_index;
	uint8_t rpc_data[216];
};

struct hv_get_perf_counter_info_params {
	__be32 counter_request;
	__be32 starting_index;
	__be16 secondary_index;
	__be16 returned_values;
	__be32 detail_rc;
	__be16 cv_element_size;
	__u8 counter_info_version_in;
	__u8 counter_info_version_out;
	__u8 reserved[12];
	__u8 counter_value[0];
};

struct hv_gpci_request_buffer {
	struct hv_get_perf_counter_info_params params;
	uint8_t bytes[4064];
};

struct hvcall_ppp_data {
	u64 entitlement;
	u64 unallocated_entitlement;
	u16 group_num;
	u16 pool_num;
	u8 capped;
	u8 weight;
	u8 unallocated_weight;
	u16 active_procs_in_pool;
	u16 active_system_procs;
	u16 phys_platform_procs;
	u32 max_proc_cap_avail;
	u32 entitled_proc_cap_avail;
};

struct bus_attribute {
	struct attribute attr;
	ssize_t (*show)(struct bus_type *, char *);
	ssize_t (*store)(struct bus_type *, const char *, size_t);
};

struct vio_device_id {
	char type[32];
	char compat[32];
};

struct vio_pfo_op {
	u64 flags;
	s64 in;
	s64 inlen;
	s64 out;
	s64 outlen;
	u64 csbcpb;
	void *done;
	long unsigned int handle;
	unsigned int timeout;
	long int hcall_err;
};

enum vio_dev_family {
	VDEVICE = 0,
	PFO = 1,
};

struct vio_dev {
	const char *name;
	const char *type;
	uint32_t unit_address;
	uint32_t resource_id;
	unsigned int irq;
	struct {
		size_t desired;
		size_t entitled;
		size_t allocated;
		atomic_t allocs_failed;
	} cmo;
	enum vio_dev_family family;
	struct device dev;
};

struct vio_driver {
	const char *name;
	const struct vio_device_id *id_table;
	int (*probe)(struct vio_dev *, const struct vio_device_id *);
	void (*remove)(struct vio_dev *);
	void (*shutdown)(struct vio_dev *);
	long unsigned int (*get_desired_dma)(struct vio_dev *);
	const struct dev_pm_ops *pm;
	struct device_driver driver;
};

struct vio_cmo_pool {
	size_t size;
	size_t free;
};

struct vio_cmo_dev_entry {
	struct vio_dev *viodev;
	struct list_head list;
};

struct vio_cmo {
	spinlock_t lock;
	struct delayed_work balance_q;
	struct list_head device_list;
	size_t entitled;
	struct vio_cmo_pool reserve;
	struct vio_cmo_pool excess;
	size_t spare;
	size_t min;
	size_t desired;
	size_t curr;
	size_t high;
};

enum cc_attr {
	CC_ATTR_MEM_ENCRYPT = 0,
	CC_ATTR_HOST_MEM_ENCRYPT = 1,
	CC_ATTR_GUEST_MEM_ENCRYPT = 2,
	CC_ATTR_GUEST_STATE_ENCRYPT = 3,
	CC_ATTR_GUEST_UNROLL_STRING_IO = 4,
	CC_ATTR_GUEST_SEV_SNP = 5,
};

struct rtas_fadump_section {
	__be32 request_flag;
	__be16 source_data_type;
	__be16 error_flags;
	__be64 source_address;
	__be64 source_len;
	__be64 bytes_dumped;
	__be64 destination_address;
};

struct rtas_fadump_section_header {
	__be32 dump_format_version;
	__be16 dump_num_sections;
	__be16 dump_status_flag;
	__be32 offset_first_dump_section;
	__be32 dd_block_size;
	__be64 dd_block_offset;
	__be64 dd_num_blocks;
	__be32 dd_offset_disk_path;
	__be32 max_time_auto;
};

struct rtas_fadump_mem_struct {
	struct rtas_fadump_section_header header;
	struct rtas_fadump_section cpu_state_data;
	struct rtas_fadump_section hpte_region;
	struct rtas_fadump_section rmr_region;
};

struct rtas_fadump_reg_save_area_header {
	__be64 magic_number;
	__be32 version;
	__be32 num_cpu_offset;
};

struct rtas_fadump_reg_entry {
	__be64 reg_id;
	__be64 reg_value;
};

typedef int suspend_state_t;

struct platform_suspend_ops {
	int (*valid)(suspend_state_t);
	int (*begin)(suspend_state_t);
	int (*prepare)();
	int (*prepare_late)();
	int (*enter)(suspend_state_t);
	void (*wake)();
	void (*finish)();
	bool (*suspend_again)();
	void (*end)();
	void (*recover)();
};

struct hv_vas_all_caps {
	__be64 descriptor;
	__be64 feat_type;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct vas_all_caps {
	u64 descriptor;
	u64 feat_type;
};

enum vas_cop_feat_type {
	VAS_GZIP_QOS_FEAT_TYPE = 0,
	VAS_GZIP_DEF_FEAT_TYPE = 1,
	VAS_MAX_FEAT_TYPE = 2,
};

struct hv_vas_cop_feat_caps {
	__be64 descriptor;
	u8 win_type;
	u8 user_mode;
	__be16 max_lpar_creds;
	__be16 max_win_creds;
	union {
		__be16 reserved;
		__be16 def_lpar_creds;
	};
	__be16 target_lpar_creds;
	long: 48;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct vas_cop_feat_caps {
	u64 descriptor;
	u8 win_type;
	u8 user_mode;
	u16 max_lpar_creds;
	u16 max_win_creds;
	union {
		u16 reserved;
		u16 def_lpar_creds;
	};
	atomic_t nr_total_credits;
	atomic_t nr_used_credits;
};

struct vas_caps {
	struct vas_cop_feat_caps caps;
	struct list_head list;
	int nr_close_wins;
	int nr_open_windows;
	u8 feat;
};

struct pseries_vas_window {
	struct vas_window vas_win;
	u64 win_addr;
	u8 win_type;
	u32 complete_irq;
	u32 fault_irq;
	u64 domain[6];
	u64 util;
	u32 pid;
	struct list_head win_list;
	u64 flags;
	char *name;
	int fault_virq;
};

struct miscdevice {
	int minor;
	const char *name;
	const struct file_operations *fops;
	struct list_head list;
	struct device *parent;
	struct device *this_device;
	const struct attribute_group **groups;
	const char *nodename;
	umode_t mode;
};

struct vas_caps_entry {
	struct kobject kobj;
	struct vas_cop_feat_caps *caps;
};

struct vas_sysfs_entry {
	struct attribute attr;
	ssize_t (*show)(struct vas_cop_feat_caps *, char *);
	ssize_t (*store)(struct vas_cop_feat_caps *, const char *, size_t);
};

struct vas_tx_win_open_attr {
	__u32 version;
	__s16 vas_id;
	__u16 reserved1;
	__u64 flags;
	__u64 reserved2[6];
};

struct coproc_dev {
	struct cdev cdev;
	struct device *device;
	char *name;
	dev_t devt;
	struct class *class;
	enum vas_cop_type cop_type;
	const struct vas_user_win_ops *vops;
};

struct coproc_instance {
	struct coproc_dev *coproc;
	struct vas_window *txwin;
};

enum {
	DUMP_PREFIX_NONE = 0,
	DUMP_PREFIX_ADDRESS = 1,
	DUMP_PREFIX_OFFSET = 2,
};

struct bpf_run_ctx {};

struct bpf_cgroup_storage;

struct bpf_prog_array_item {
	struct bpf_prog *prog;
	union {
		struct bpf_cgroup_storage *cgroup_storage[2];
		u64 bpf_cookie;
	};
};

struct bpf_prog_array {
	struct callback_head rcu;
	struct bpf_prog_array_item items[0];
};

enum bpf_prog_type {
	BPF_PROG_TYPE_UNSPEC = 0,
	BPF_PROG_TYPE_SOCKET_FILTER = 1,
	BPF_PROG_TYPE_KPROBE = 2,
	BPF_PROG_TYPE_SCHED_CLS = 3,
	BPF_PROG_TYPE_SCHED_ACT = 4,
	BPF_PROG_TYPE_TRACEPOINT = 5,
	BPF_PROG_TYPE_XDP = 6,
	BPF_PROG_TYPE_PERF_EVENT = 7,
	BPF_PROG_TYPE_CGROUP_SKB = 8,
	BPF_PROG_TYPE_CGROUP_SOCK = 9,
	BPF_PROG_TYPE_LWT_IN = 10,
	BPF_PROG_TYPE_LWT_OUT = 11,
	BPF_PROG_TYPE_LWT_XMIT = 12,
	BPF_PROG_TYPE_SOCK_OPS = 13,
	BPF_PROG_TYPE_SK_SKB = 14,
	BPF_PROG_TYPE_CGROUP_DEVICE = 15,
	BPF_PROG_TYPE_SK_MSG = 16,
	BPF_PROG_TYPE_RAW_TRACEPOINT = 17,
	BPF_PROG_TYPE_CGROUP_SOCK_ADDR = 18,
	BPF_PROG_TYPE_LWT_SEG6LOCAL = 19,
	BPF_PROG_TYPE_LIRC_MODE2 = 20,
	BPF_PROG_TYPE_SK_REUSEPORT = 21,
	BPF_PROG_TYPE_FLOW_DISSECTOR = 22,
	BPF_PROG_TYPE_CGROUP_SYSCTL = 23,
	BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE = 24,
	BPF_PROG_TYPE_CGROUP_SOCKOPT = 25,
	BPF_PROG_TYPE_TRACING = 26,
	BPF_PROG_TYPE_STRUCT_OPS = 27,
	BPF_PROG_TYPE_EXT = 28,
	BPF_PROG_TYPE_LSM = 29,
	BPF_PROG_TYPE_SK_LOOKUP = 30,
	BPF_PROG_TYPE_SYSCALL = 31,
};

enum bpf_attach_type {
	BPF_CGROUP_INET_INGRESS = 0,
	BPF_CGROUP_INET_EGRESS = 1,
	BPF_CGROUP_INET_SOCK_CREATE = 2,
	BPF_CGROUP_SOCK_OPS = 3,
	BPF_SK_SKB_STREAM_PARSER = 4,
	BPF_SK_SKB_STREAM_VERDICT = 5,
	BPF_CGROUP_DEVICE = 6,
	BPF_SK_MSG_VERDICT = 7,
	BPF_CGROUP_INET4_BIND = 8,
	BPF_CGROUP_INET6_BIND = 9,
	BPF_CGROUP_INET4_CONNECT = 10,
	BPF_CGROUP_INET6_CONNECT = 11,
	BPF_CGROUP_INET4_POST_BIND = 12,
	BPF_CGROUP_INET6_POST_BIND = 13,
	BPF_CGROUP_UDP4_SENDMSG = 14,
	BPF_CGROUP_UDP6_SENDMSG = 15,
	BPF_LIRC_MODE2 = 16,
	BPF_FLOW_DISSECTOR = 17,
	BPF_CGROUP_SYSCTL = 18,
	BPF_CGROUP_UDP4_RECVMSG = 19,
	BPF_CGROUP_UDP6_RECVMSG = 20,
	BPF_CGROUP_GETSOCKOPT = 21,
	BPF_CGROUP_SETSOCKOPT = 22,
	BPF_TRACE_RAW_TP = 23,
	BPF_TRACE_FENTRY = 24,
	BPF_TRACE_FEXIT = 25,
	BPF_MODIFY_RETURN = 26,
	BPF_LSM_MAC = 27,
	BPF_TRACE_ITER = 28,
	BPF_CGROUP_INET4_GETPEERNAME = 29,
	BPF_CGROUP_INET6_GETPEERNAME = 30,
	BPF_CGROUP_INET4_GETSOCKNAME = 31,
	BPF_CGROUP_INET6_GETSOCKNAME = 32,
	BPF_XDP_DEVMAP = 33,
	BPF_CGROUP_INET_SOCK_RELEASE = 34,
	BPF_XDP_CPUMAP = 35,
	BPF_SK_LOOKUP = 36,
	BPF_XDP = 37,
	BPF_SK_SKB_VERDICT = 38,
	BPF_SK_REUSEPORT_SELECT = 39,
	BPF_SK_REUSEPORT_SELECT_OR_MIGRATE = 40,
	BPF_PERF_EVENT = 41,
	__MAX_BPF_ATTACH_TYPE = 42,
};

struct sock_filter {
	__u16 code;
	__u8 jt;
	__u8 jf;
	__u32 k;
};

struct bpf_insn {
	__u8 code;
	__u8 dst_reg: 4;
	__u8 src_reg: 4;
	__s16 off;
	__s32 imm;
};

struct bpf_prog_stats;

struct bpf_prog_aux;

struct sock_fprog_kern;

struct bpf_prog {
	u16 pages;
	u16 jited: 1;
	u16 jit_requested: 1;
	u16 gpl_compatible: 1;
	u16 cb_access: 1;
	u16 dst_needed: 1;
	u16 blinded: 1;
	u16 is_func: 1;
	u16 kprobe_override: 1;
	u16 has_callchain_buf: 1;
	u16 enforce_expected_attach_type: 1;
	u16 call_get_stack: 1;
	u16 call_get_func_ip: 1;
	enum bpf_prog_type type;
	enum bpf_attach_type expected_attach_type;
	u32 len;
	u32 jited_len;
	u8 tag[8];
	struct bpf_prog_stats *stats;
	int *active;
	unsigned int (*bpf_func)(const void *, const struct bpf_insn *);
	struct bpf_prog_aux *aux;
	struct sock_fprog_kern *orig_prog;
	struct sock_filter insns[0];
	struct bpf_insn insnsi[0];
};

struct tc_stats {
	__u64 bytes;
	__u32 packets;
	__u32 drops;
	__u32 overlimits;
	__u32 bps;
	__u32 pps;
	__u32 qlen;
	__u32 backlog;
};

struct tc_sizespec {
	unsigned char cell_log;
	unsigned char size_log;
	short int cell_align;
	int overhead;
	unsigned int linklayer;
	unsigned int mpu;
	unsigned int mtu;
	unsigned int tsize;
};

struct net_rate_estimator;

struct qdisc_skb_head {
	struct sk_buff *head;
	struct sk_buff *tail;
	__u32 qlen;
	spinlock_t lock;
};

struct gnet_stats_basic_sync {
	u64_stats_t bytes;
	u64_stats_t packets;
	struct u64_stats_sync syncp;
};

struct gnet_stats_queue {
	__u32 qlen;
	__u32 backlog;
	__u32 drops;
	__u32 requeues;
	__u32 overlimits;
};

struct Qdisc_ops;

struct qdisc_size_table;

struct Qdisc {
	int (*enqueue)(struct sk_buff *, struct Qdisc *, struct sk_buff **);
	struct sk_buff * (*dequeue)(struct Qdisc *);
	unsigned int flags;
	u32 limit;
	const struct Qdisc_ops *ops;
	struct qdisc_size_table *stab;
	struct hlist_node hash;
	u32 handle;
	u32 parent;
	struct netdev_queue *dev_queue;
	struct net_rate_estimator *rate_est;
	struct gnet_stats_basic_sync *cpu_bstats;
	struct gnet_stats_queue *cpu_qstats;
	int pad;
	refcount_t refcnt;
	long: 64;
	long: 64;
	long: 64;
	struct sk_buff_head gso_skb;
	struct qdisc_skb_head q;
	struct gnet_stats_basic_sync bstats;
	struct gnet_stats_queue qstats;
	long unsigned int state;
	long unsigned int state2;
	struct Qdisc *next_sched;
	struct sk_buff_head skb_bad_txq;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	spinlock_t busylock;
	spinlock_t seqlock;
	struct callback_head rcu;
	netdevice_tracker dev_tracker;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long int privdata[0];
};

enum bpf_map_type {
	BPF_MAP_TYPE_UNSPEC = 0,
	BPF_MAP_TYPE_HASH = 1,
	BPF_MAP_TYPE_ARRAY = 2,
	BPF_MAP_TYPE_PROG_ARRAY = 3,
	BPF_MAP_TYPE_PERF_EVENT_ARRAY = 4,
	BPF_MAP_TYPE_PERCPU_HASH = 5,
	BPF_MAP_TYPE_PERCPU_ARRAY = 6,
	BPF_MAP_TYPE_STACK_TRACE = 7,
	BPF_MAP_TYPE_CGROUP_ARRAY = 8,
	BPF_MAP_TYPE_LRU_HASH = 9,
	BPF_MAP_TYPE_LRU_PERCPU_HASH = 10,
	BPF_MAP_TYPE_LPM_TRIE = 11,
	BPF_MAP_TYPE_ARRAY_OF_MAPS = 12,
	BPF_MAP_TYPE_HASH_OF_MAPS = 13,
	BPF_MAP_TYPE_DEVMAP = 14,
	BPF_MAP_TYPE_SOCKMAP = 15,
	BPF_MAP_TYPE_CPUMAP = 16,
	BPF_MAP_TYPE_XSKMAP = 17,
	BPF_MAP_TYPE_SOCKHASH = 18,
	BPF_MAP_TYPE_CGROUP_STORAGE = 19,
	BPF_MAP_TYPE_REUSEPORT_SOCKARRAY = 20,
	BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE = 21,
	BPF_MAP_TYPE_QUEUE = 22,
	BPF_MAP_TYPE_STACK = 23,
	BPF_MAP_TYPE_SK_STORAGE = 24,
	BPF_MAP_TYPE_DEVMAP_HASH = 25,
	BPF_MAP_TYPE_STRUCT_OPS = 26,
	BPF_MAP_TYPE_RINGBUF = 27,
	BPF_MAP_TYPE_INODE_STORAGE = 28,
	BPF_MAP_TYPE_TASK_STORAGE = 29,
	BPF_MAP_TYPE_BLOOM_FILTER = 30,
};

struct bpf_map_ops;

struct btf;

struct bpf_map {
	const struct bpf_map_ops *ops;
	struct bpf_map *inner_map_meta;
	void *security;
	enum bpf_map_type map_type;
	u32 key_size;
	u32 value_size;
	u32 max_entries;
	u64 map_extra;
	u32 map_flags;
	int spin_lock_off;
	int timer_off;
	u32 id;
	int numa_node;
	u32 btf_key_type_id;
	u32 btf_value_type_id;
	u32 btf_vmlinux_value_type_id;
	struct btf *btf;
	struct mem_cgroup *memcg;
	char name[16];
	bool bypass_spec_v1;
	bool frozen;
	long: 48;
	long: 64;
	atomic64_t refcnt;
	atomic64_t usercnt;
	struct work_struct work;
	struct mutex freeze_mutex;
	atomic64_t writecnt;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct bpf_map_dev_ops;

struct bpf_offloaded_map {
	struct bpf_map map;
	struct net_device *netdev;
	const struct bpf_map_dev_ops *dev_ops;
	void *dev_priv;
	struct list_head offloads;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct tcf_proto;

struct tcf_block;

struct mini_Qdisc {
	struct tcf_proto *filter_list;
	struct tcf_block *block;
	struct gnet_stats_basic_sync *cpu_bstats;
	struct gnet_stats_queue *cpu_qstats;
	long unsigned int rcu_state;
};

union bpf_attr {
	struct {
		__u32 map_type;
		__u32 key_size;
		__u32 value_size;
		__u32 max_entries;
		__u32 map_flags;
		__u32 inner_map_fd;
		__u32 numa_node;
		char map_name[16];
		__u32 map_ifindex;
		__u32 btf_fd;
		__u32 btf_key_type_id;
		__u32 btf_value_type_id;
		__u32 btf_vmlinux_value_type_id;
		__u64 map_extra;
	};
	struct {
		__u32 map_fd;
		__u64 key;
		union {
			__u64 value;
			__u64 next_key;
		};
		__u64 flags;
	};
	struct {
		__u64 in_batch;
		__u64 out_batch;
		__u64 keys;
		__u64 values;
		__u32 count;
		__u32 map_fd;
		__u64 elem_flags;
		__u64 flags;
	} batch;
	struct {
		__u32 prog_type;
		__u32 insn_cnt;
		__u64 insns;
		__u64 license;
		__u32 log_level;
		__u32 log_size;
		__u64 log_buf;
		__u32 kern_version;
		__u32 prog_flags;
		char prog_name[16];
		__u32 prog_ifindex;
		__u32 expected_attach_type;
		__u32 prog_btf_fd;
		__u32 func_info_rec_size;
		__u64 func_info;
		__u32 func_info_cnt;
		__u32 line_info_rec_size;
		__u64 line_info;
		__u32 line_info_cnt;
		__u32 attach_btf_id;
		union {
			__u32 attach_prog_fd;
			__u32 attach_btf_obj_fd;
		};
		__u32 core_relo_cnt;
		__u64 fd_array;
		__u64 core_relos;
		__u32 core_relo_rec_size;
	};
	struct {
		__u64 pathname;
		__u32 bpf_fd;
		__u32 file_flags;
	};
	struct {
		__u32 target_fd;
		__u32 attach_bpf_fd;
		__u32 attach_type;
		__u32 attach_flags;
		__u32 replace_bpf_fd;
	};
	struct {
		__u32 prog_fd;
		__u32 retval;
		__u32 data_size_in;
		__u32 data_size_out;
		__u64 data_in;
		__u64 data_out;
		__u32 repeat;
		__u32 duration;
		__u32 ctx_size_in;
		__u32 ctx_size_out;
		__u64 ctx_in;
		__u64 ctx_out;
		__u32 flags;
		__u32 cpu;
	} test;
	struct {
		union {
			__u32 start_id;
			__u32 prog_id;
			__u32 map_id;
			__u32 btf_id;
			__u32 link_id;
		};
		__u32 next_id;
		__u32 open_flags;
	};
	struct {
		__u32 bpf_fd;
		__u32 info_len;
		__u64 info;
	} info;
	struct {
		__u32 target_fd;
		__u32 attach_type;
		__u32 query_flags;
		__u32 attach_flags;
		__u64 prog_ids;
		__u32 prog_cnt;
	} query;
	struct {
		__u64 name;
		__u32 prog_fd;
	} raw_tracepoint;
	struct {
		__u64 btf;
		__u64 btf_log_buf;
		__u32 btf_size;
		__u32 btf_log_size;
		__u32 btf_log_level;
	};
	struct {
		__u32 pid;
		__u32 fd;
		__u32 flags;
		__u32 buf_len;
		__u64 buf;
		__u32 prog_id;
		__u32 fd_type;
		__u64 probe_offset;
		__u64 probe_addr;
	} task_fd_query;
	struct {
		__u32 prog_fd;
		union {
			__u32 target_fd;
			__u32 target_ifindex;
		};
		__u32 attach_type;
		__u32 flags;
		union {
			__u32 target_btf_id;
			struct {
				__u64 iter_info;
				__u32 iter_info_len;
			};
			struct {
				__u64 bpf_cookie;
			} perf_event;
		};
	} link_create;
	struct {
		__u32 link_fd;
		__u32 new_prog_fd;
		__u32 flags;
		__u32 old_prog_fd;
	} link_update;
	struct {
		__u32 link_fd;
	} link_detach;
	struct {
		__u32 type;
	} enable_stats;
	struct {
		__u32 link_fd;
		__u32 flags;
	} iter_create;
	struct {
		__u32 prog_fd;
		__u32 map_fd;
		__u32 flags;
	} prog_bind_map;
};

struct bpf_func_info {
	__u32 insn_off;
	__u32 type_id;
};

struct bpf_line_info {
	__u32 insn_off;
	__u32 file_name_off;
	__u32 line_off;
	__u32 line_col;
};

typedef u64 (*bpf_callback_t)(u64, u64, u64, u64, u64);

struct bpf_iter_aux_info;

typedef int (*bpf_iter_init_seq_priv_t)(void *, struct bpf_iter_aux_info *);

struct bpf_iter_aux_info {
	struct bpf_map *map;
};

typedef void (*bpf_iter_fini_seq_priv_t)(void *);

struct bpf_iter_seq_info {
	const struct seq_operations *seq_ops;
	bpf_iter_init_seq_priv_t init_seq_private;
	bpf_iter_fini_seq_priv_t fini_seq_private;
	u32 seq_priv_size;
};

struct btf_type;

struct bpf_local_storage_map;

struct bpf_verifier_env;

struct bpf_func_state;

struct bpf_map_ops {
	int (*map_alloc_check)(union bpf_attr *);
	struct bpf_map * (*map_alloc)(union bpf_attr *);
	void (*map_release)(struct bpf_map *, struct file *);
	void (*map_free)(struct bpf_map *);
	int (*map_get_next_key)(struct bpf_map *, void *, void *);
	void (*map_release_uref)(struct bpf_map *);
	void * (*map_lookup_elem_sys_only)(struct bpf_map *, void *);
	int (*map_lookup_batch)(struct bpf_map *, const union bpf_attr *, union bpf_attr *);
	int (*map_lookup_and_delete_elem)(struct bpf_map *, void *, void *, u64);
	int (*map_lookup_and_delete_batch)(struct bpf_map *, const union bpf_attr *, union bpf_attr *);
	int (*map_update_batch)(struct bpf_map *, const union bpf_attr *, union bpf_attr *);
	int (*map_delete_batch)(struct bpf_map *, const union bpf_attr *, union bpf_attr *);
	void * (*map_lookup_elem)(struct bpf_map *, void *);
	int (*map_update_elem)(struct bpf_map *, void *, void *, u64);
	int (*map_delete_elem)(struct bpf_map *, void *);
	int (*map_push_elem)(struct bpf_map *, void *, u64);
	int (*map_pop_elem)(struct bpf_map *, void *);
	int (*map_peek_elem)(struct bpf_map *, void *);
	void * (*map_fd_get_ptr)(struct bpf_map *, struct file *, int);
	void (*map_fd_put_ptr)(void *);
	int (*map_gen_lookup)(struct bpf_map *, struct bpf_insn *);
	u32 (*map_fd_sys_lookup_elem)(void *);
	void (*map_seq_show_elem)(struct bpf_map *, void *, struct seq_file *);
	int (*map_check_btf)(const struct bpf_map *, const struct btf *, const struct btf_type *, const struct btf_type *);
	int (*map_poke_track)(struct bpf_map *, struct bpf_prog_aux *);
	void (*map_poke_untrack)(struct bpf_map *, struct bpf_prog_aux *);
	void (*map_poke_run)(struct bpf_map *, u32, struct bpf_prog *, struct bpf_prog *);
	int (*map_direct_value_addr)(const struct bpf_map *, u64 *, u32);
	int (*map_direct_value_meta)(const struct bpf_map *, u64, u32 *);
	int (*map_mmap)(struct bpf_map *, struct vm_area_struct *);
	__poll_t (*map_poll)(struct bpf_map *, struct file *, struct poll_table_struct *);
	int (*map_local_storage_charge)(struct bpf_local_storage_map *, void *, u32);
	void (*map_local_storage_uncharge)(struct bpf_local_storage_map *, void *, u32);
	struct bpf_local_storage ** (*map_owner_storage_ptr)(void *);
	int (*map_redirect)(struct bpf_map *, u32, u64);
	bool (*map_meta_equal)(const struct bpf_map *, const struct bpf_map *);
	int (*map_set_for_each_callback_args)(struct bpf_verifier_env *, struct bpf_func_state *, struct bpf_func_state *);
	int (*map_for_each_callback)(struct bpf_map *, bpf_callback_t, void *, u64);
	const char * const map_btf_name;
	int *map_btf_id;
	const struct bpf_iter_seq_info *iter_seq_info;
};

struct btf_header {
	__u16 magic;
	__u8 version;
	__u8 flags;
	__u32 hdr_len;
	__u32 type_off;
	__u32 type_len;
	__u32 str_off;
	__u32 str_len;
};

struct btf {
	void *data;
	struct btf_type **types;
	u32 *resolved_ids;
	u32 *resolved_sizes;
	const char *strings;
	void *nohdr_data;
	struct btf_header hdr;
	u32 nr_types;
	u32 types_size;
	u32 data_size;
	refcount_t refcnt;
	u32 id;
	struct callback_head rcu;
	struct btf *base_btf;
	u32 start_id;
	u32 start_str_off;
	char name[56];
	bool kernel_btf;
};

struct btf_type {
	__u32 name_off;
	__u32 info;
	union {
		__u32 size;
		__u32 type;
	};
};

struct bpf_ksym {
	long unsigned int start;
	long unsigned int end;
	char name[128];
	struct list_head lnode;
	struct latch_tree_node tnode;
	bool prog;
};

struct bpf_ctx_arg_aux;

struct bpf_trampoline;

struct bpf_jit_poke_descriptor;

struct bpf_kfunc_desc_tab;

struct bpf_kfunc_btf_tab;

struct bpf_prog_ops;

struct btf_mod_pair;

struct bpf_prog_offload;

struct bpf_func_info_aux;

struct bpf_prog_aux {
	atomic64_t refcnt;
	u32 used_map_cnt;
	u32 used_btf_cnt;
	u32 max_ctx_offset;
	u32 max_pkt_offset;
	u32 max_tp_access;
	u32 stack_depth;
	u32 id;
	u32 func_cnt;
	u32 func_idx;
	u32 attach_btf_id;
	u32 ctx_arg_info_size;
	u32 max_rdonly_access;
	u32 max_rdwr_access;
	struct btf *attach_btf;
	const struct bpf_ctx_arg_aux *ctx_arg_info;
	struct mutex dst_mutex;
	struct bpf_prog *dst_prog;
	struct bpf_trampoline *dst_trampoline;
	enum bpf_prog_type saved_dst_prog_type;
	enum bpf_attach_type saved_dst_attach_type;
	bool verifier_zext;
	bool offload_requested;
	bool attach_btf_trace;
	bool func_proto_unreliable;
	bool sleepable;
	bool tail_call_reachable;
	struct hlist_node tramp_hlist;
	const struct btf_type *attach_func_proto;
	const char *attach_func_name;
	struct bpf_prog **func;
	void *jit_data;
	struct bpf_jit_poke_descriptor *poke_tab;
	struct bpf_kfunc_desc_tab *kfunc_tab;
	struct bpf_kfunc_btf_tab *kfunc_btf_tab;
	u32 size_poke_tab;
	struct bpf_ksym ksym;
	const struct bpf_prog_ops *ops;
	struct bpf_map **used_maps;
	struct mutex used_maps_mutex;
	struct btf_mod_pair *used_btfs;
	struct bpf_prog *prog;
	struct user_struct *user;
	u64 load_time;
	u32 verified_insns;
	struct bpf_map *cgroup_storage[2];
	char name[16];
	void *security;
	struct bpf_prog_offload *offload;
	struct btf *btf;
	struct bpf_func_info *func_info;
	struct bpf_func_info_aux *func_info_aux;
	struct bpf_line_info *linfo;
	void **jited_linfo;
	u32 func_info_cnt;
	u32 nr_linfo;
	u32 linfo_idx;
	u32 num_exentries;
	struct exception_table_entry *extable;
	union {
		struct work_struct work;
		struct callback_head rcu;
	};
};

struct bpf_map_dev_ops {
	int (*map_get_next_key)(struct bpf_offloaded_map *, void *, void *);
	int (*map_lookup_elem)(struct bpf_offloaded_map *, void *, void *);
	int (*map_update_elem)(struct bpf_offloaded_map *, void *, void *, u64);
	int (*map_delete_elem)(struct bpf_offloaded_map *, void *);
};

enum bpf_reg_type {
	NOT_INIT = 0,
	SCALAR_VALUE = 1,
	PTR_TO_CTX = 2,
	CONST_PTR_TO_MAP = 3,
	PTR_TO_MAP_VALUE = 4,
	PTR_TO_MAP_KEY = 5,
	PTR_TO_STACK = 6,
	PTR_TO_PACKET_META = 7,
	PTR_TO_PACKET = 8,
	PTR_TO_PACKET_END = 9,
	PTR_TO_FLOW_KEYS = 10,
	PTR_TO_SOCKET = 11,
	PTR_TO_SOCK_COMMON = 12,
	PTR_TO_TCP_SOCK = 13,
	PTR_TO_TP_BUFFER = 14,
	PTR_TO_XDP_SOCK = 15,
	PTR_TO_BTF_ID = 16,
	PTR_TO_MEM = 17,
	PTR_TO_BUF = 18,
	PTR_TO_PERCPU_BTF_ID = 19,
	PTR_TO_FUNC = 20,
	__BPF_REG_TYPE_MAX = 21,
	PTR_TO_MAP_VALUE_OR_NULL = 260,
	PTR_TO_SOCKET_OR_NULL = 267,
	PTR_TO_SOCK_COMMON_OR_NULL = 268,
	PTR_TO_TCP_SOCK_OR_NULL = 269,
	PTR_TO_BTF_ID_OR_NULL = 272,
	__BPF_REG_TYPE_LIMIT = 2047,
};

struct bpf_prog_ops {
	int (*test_run)(struct bpf_prog *, const union bpf_attr *, union bpf_attr *);
};

struct bpf_offload_dev;

struct bpf_prog_offload {
	struct bpf_prog *prog;
	struct net_device *netdev;
	struct bpf_offload_dev *offdev;
	void *dev_priv;
	struct list_head offloads;
	bool dev_state;
	bool opt_failed;
	void *jited_image;
	u32 jited_len;
};

struct btf_func_model {
	u8 ret_size;
	u8 nr_args;
	u8 arg_size[12];
};

struct bpf_tramp_image {
	void *image;
	struct bpf_ksym ksym;
	struct percpu_ref pcref;
	void *ip_after_call;
	void *ip_epilogue;
	union {
		struct callback_head rcu;
		struct work_struct work;
	};
};

struct bpf_trampoline {
	struct hlist_node hlist;
	struct mutex mutex;
	refcount_t refcnt;
	u64 key;
	struct {
		struct btf_func_model model;
		void *addr;
		bool ftrace_managed;
	} func;
	struct bpf_prog *extension_prog;
	struct hlist_head progs_hlist[3];
	int progs_cnt[3];
	struct bpf_tramp_image *cur_image;
	u64 selector;
	struct module *mod;
};

struct bpf_func_info_aux {
	u16 linkage;
	bool unreliable;
};

struct bpf_jit_poke_descriptor {
	void *tailcall_target;
	void *tailcall_bypass;
	void *bypass_addr;
	void *aux;
	union {
		struct {
			struct bpf_map *map;
			u32 key;
		} tail_call;
	};
	bool tailcall_target_stable;
	u8 adj_off;
	u16 reason;
	u32 insn_idx;
};

struct bpf_ctx_arg_aux {
	u32 offset;
	enum bpf_reg_type reg_type;
	u32 btf_id;
};

struct btf_mod_pair {
	struct btf *btf;
	struct module *module;
};

struct tcmsg {
	unsigned char tcm_family;
	unsigned char tcm__pad1;
	short unsigned int tcm__pad2;
	int tcm_ifindex;
	__u32 tcm_handle;
	__u32 tcm_parent;
	__u32 tcm_info;
};

struct gnet_dump {
	spinlock_t *lock;
	struct sk_buff *skb;
	struct nlattr *tail;
	int compat_tc_stats;
	int compat_xstats;
	int padattr;
	void *xstats;
	int xstats_len;
	struct tc_stats tc_stats;
};

struct flow_block {
	struct list_head cb_list;
};

typedef int flow_setup_cb_t(enum tc_setup_type, void *, void *);

struct qdisc_size_table {
	struct callback_head rcu;
	struct list_head list;
	struct tc_sizespec szopts;
	int refcnt;
	u16 data[0];
};

struct Qdisc_class_ops;

struct Qdisc_ops {
	struct Qdisc_ops *next;
	const struct Qdisc_class_ops *cl_ops;
	char id[16];
	int priv_size;
	unsigned int static_flags;
	int (*enqueue)(struct sk_buff *, struct Qdisc *, struct sk_buff **);
	struct sk_buff * (*dequeue)(struct Qdisc *);
	struct sk_buff * (*peek)(struct Qdisc *);
	int (*init)(struct Qdisc *, struct nlattr *, struct netlink_ext_ack *);
	void (*reset)(struct Qdisc *);
	void (*destroy)(struct Qdisc *);
	int (*change)(struct Qdisc *, struct nlattr *, struct netlink_ext_ack *);
	void (*attach)(struct Qdisc *);
	int (*change_tx_queue_len)(struct Qdisc *, unsigned int);
	void (*change_real_num_tx)(struct Qdisc *, unsigned int);
	int (*dump)(struct Qdisc *, struct sk_buff *);
	int (*dump_stats)(struct Qdisc *, struct gnet_dump *);
	void (*ingress_block_set)(struct Qdisc *, u32);
	void (*egress_block_set)(struct Qdisc *, u32);
	u32 (*ingress_block_get)(struct Qdisc *);
	u32 (*egress_block_get)(struct Qdisc *);
	struct module *owner;
};

struct qdisc_walker;

struct Qdisc_class_ops {
	unsigned int flags;
	struct netdev_queue * (*select_queue)(struct Qdisc *, struct tcmsg *);
	int (*graft)(struct Qdisc *, long unsigned int, struct Qdisc *, struct Qdisc **, struct netlink_ext_ack *);
	struct Qdisc * (*leaf)(struct Qdisc *, long unsigned int);
	void (*qlen_notify)(struct Qdisc *, long unsigned int);
	long unsigned int (*find)(struct Qdisc *, u32);
	int (*change)(struct Qdisc *, u32, u32, struct nlattr **, long unsigned int *, struct netlink_ext_ack *);
	int (*delete)(struct Qdisc *, long unsigned int, struct netlink_ext_ack *);
	void (*walk)(struct Qdisc *, struct qdisc_walker *);
	struct tcf_block * (*tcf_block)(struct Qdisc *, long unsigned int, struct netlink_ext_ack *);
	long unsigned int (*bind_tcf)(struct Qdisc *, long unsigned int, u32);
	void (*unbind_tcf)(struct Qdisc *, long unsigned int);
	int (*dump)(struct Qdisc *, long unsigned int, struct sk_buff *, struct tcmsg *);
	int (*dump_stats)(struct Qdisc *, long unsigned int, struct gnet_dump *);
};

struct tcf_chain;

struct tcf_block {
	struct mutex lock;
	struct list_head chain_list;
	u32 index;
	u32 classid;
	refcount_t refcnt;
	struct net *net;
	struct Qdisc *q;
	struct rw_semaphore cb_lock;
	struct flow_block flow_block;
	struct list_head owner_list;
	bool keep_dst;
	atomic_t offloadcnt;
	unsigned int nooffloaddevcnt;
	unsigned int lockeddevcnt;
	struct {
		struct tcf_chain *chain;
		struct list_head filter_chain_list;
	} chain0;
	struct callback_head rcu;
	struct hlist_head proto_destroy_ht[128];
	struct mutex proto_destroy_lock;
};

struct tcf_result;

struct tcf_proto_ops;

struct tcf_proto {
	struct tcf_proto *next;
	void *root;
	int (*classify)(struct sk_buff *, const struct tcf_proto *, struct tcf_result *);
	__be16 protocol;
	u32 prio;
	void *data;
	const struct tcf_proto_ops *ops;
	struct tcf_chain *chain;
	spinlock_t lock;
	bool deleting;
	refcount_t refcnt;
	struct callback_head rcu;
	struct hlist_node destroy_ht_node;
};

struct tcf_result {
	union {
		struct {
			long unsigned int class;
			u32 classid;
		};
		const struct tcf_proto *goto_tp;
		struct {
			bool ingress;
			struct gnet_stats_queue *qstats;
		};
	};
};

struct tcf_walker;

struct tcf_proto_ops {
	struct list_head head;
	char kind[16];
	int (*classify)(struct sk_buff *, const struct tcf_proto *, struct tcf_result *);
	int (*init)(struct tcf_proto *);
	void (*destroy)(struct tcf_proto *, bool, struct netlink_ext_ack *);
	void * (*get)(struct tcf_proto *, u32);
	void (*put)(struct tcf_proto *, void *);
	int (*change)(struct net *, struct sk_buff *, struct tcf_proto *, long unsigned int, u32, struct nlattr **, void **, u32, struct netlink_ext_ack *);
	int (*delete)(struct tcf_proto *, void *, bool *, bool, struct netlink_ext_ack *);
	bool (*delete_empty)(struct tcf_proto *);
	void (*walk)(struct tcf_proto *, struct tcf_walker *, bool);
	int (*reoffload)(struct tcf_proto *, bool, flow_setup_cb_t *, void *, struct netlink_ext_ack *);
	void (*hw_add)(struct tcf_proto *, void *);
	void (*hw_del)(struct tcf_proto *, void *);
	void (*bind_class)(void *, u32, long unsigned int, void *, long unsigned int);
	void * (*tmplt_create)(struct net *, struct tcf_chain *, struct nlattr **, struct netlink_ext_ack *);
	void (*tmplt_destroy)(void *);
	int (*dump)(struct net *, struct tcf_proto *, void *, struct sk_buff *, struct tcmsg *, bool);
	int (*terse_dump)(struct net *, struct tcf_proto *, void *, struct sk_buff *, struct tcmsg *, bool);
	int (*tmplt_dump)(struct sk_buff *, struct net *, void *);
	struct module *owner;
	int flags;
};

struct tcf_chain {
	struct mutex filter_chain_lock;
	struct tcf_proto *filter_chain;
	struct list_head list;
	struct tcf_block *block;
	u32 index;
	unsigned int refcnt;
	unsigned int action_refcnt;
	bool explicitly_created;
	bool flushing;
	const struct tcf_proto_ops *tmplt_ops;
	void *tmplt_priv;
	struct callback_head rcu;
};

struct sock_fprog_kern {
	u16 len;
	struct sock_filter *filter;
};

struct bpf_binary_header {
	u32 pages;
	int: 32;
	u8 image[0];
};

struct bpf_prog_stats {
	u64_stats_t cnt;
	u64_stats_t nsecs;
	u64_stats_t misses;
	struct u64_stats_sync syncp;
	long: 64;
};

typedef void (*bpf_jit_fill_hole_t)(void *, unsigned int);

struct codegen_context {
	unsigned int seen;
	unsigned int idx;
	unsigned int stack_size;
	int b2p[14];
	unsigned int exentry_idx;
};

struct powerpc64_jit_data {
	struct bpf_binary_header *header;
	u32 *addrs;
	u8 *image;
	u32 proglen;
	struct codegen_context ctx;
};

enum {
	BPF_REG_0 = 0,
	BPF_REG_1 = 1,
	BPF_REG_2 = 2,
	BPF_REG_3 = 3,
	BPF_REG_4 = 4,
	BPF_REG_5 = 5,
	BPF_REG_6 = 6,
	BPF_REG_7 = 7,
	BPF_REG_8 = 8,
	BPF_REG_9 = 9,
	BPF_REG_10 = 10,
	__MAX_BPF_REG = 11,
};

enum flow_action_hw_stats_bit {
	FLOW_ACTION_HW_STATS_IMMEDIATE_BIT = 0,
	FLOW_ACTION_HW_STATS_DELAYED_BIT = 1,
	FLOW_ACTION_HW_STATS_DISABLED_BIT = 2,
	FLOW_ACTION_HW_STATS_NUM_BITS = 3,
};

enum ftrace_dump_mode {
	DUMP_NONE = 0,
	DUMP_ALL = 1,
	DUMP_ORIG = 2,
};

enum tk_offsets {
	TK_OFFS_REAL = 0,
	TK_OFFS_BOOT = 1,
	TK_OFFS_TAI = 2,
	TK_OFFS_MAX = 3,
};

struct sysrq_key_op {
	void (* const handler)(int);
	const char * const help_msg;
	const char * const action_msg;
	const int enable_mask;
};

enum {
	XIVE_DUMP_TM_HYP = 0,
	XIVE_DUMP_TM_POOL = 1,
	XIVE_DUMP_TM_OS = 2,
	XIVE_DUMP_TM_USER = 3,
	XIVE_DUMP_VP = 4,
	XIVE_DUMP_EMU_STATE = 5,
};

struct bpt {
	long unsigned int address;
	u32 *instr;
	atomic_t ref_count;
	int enabled;
	long unsigned int pad;
};

typedef int (*instruction_dump_func)(long unsigned int, long unsigned int);

typedef long unsigned int (*callfunc_t)(long unsigned int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, long unsigned int, long unsigned int);

typedef uint64_t ppc_cpu_t;

struct powerpc_opcode {
	const char *name;
	long unsigned int opcode;
	long unsigned int mask;
	ppc_cpu_t flags;
	ppc_cpu_t deprecated;
	unsigned char operands[8];
};

struct powerpc_operand {
	unsigned int bitm;
	int shift;
	long unsigned int (*insert)(long unsigned int, long int, ppc_cpu_t, const char **);
	long int (*extract)(long unsigned int, ppc_cpu_t, int *);
	long unsigned int flags;
};

struct powerpc_macro {
	const char *name;
	unsigned int operands;
	ppc_cpu_t flags;
	const char *format;
};

enum perf_callchain_context {
	PERF_CONTEXT_HV = 4294967264,
	PERF_CONTEXT_KERNEL = 4294967168,
	PERF_CONTEXT_USER = 4294966784,
	PERF_CONTEXT_GUEST = 4294965248,
	PERF_CONTEXT_GUEST_KERNEL = 4294965120,
	PERF_CONTEXT_GUEST_USER = 4294964736,
	PERF_CONTEXT_MAX = 4294963201,
};

struct perf_callchain_entry_ctx {
	struct perf_callchain_entry *entry;
	u32 max_stack;
	u32 nr;
	short int contexts;
	bool contexts_maxed;
};

struct signal_frame_64 {
	char dummy[128];
	struct ucontext uc;
	long unsigned int unused[2];
	unsigned int tramp[6];
	struct siginfo *pinfo;
	void *puc;
	struct siginfo info;
	char abigap[288];
};

enum perf_sample_regs_abi {
	PERF_SAMPLE_REGS_ABI_NONE = 0,
	PERF_SAMPLE_REGS_ABI_32 = 1,
	PERF_SAMPLE_REGS_ABI_64 = 2,
};

enum perf_event_powerpc_regs {
	PERF_REG_POWERPC_R0 = 0,
	PERF_REG_POWERPC_R1 = 1,
	PERF_REG_POWERPC_R2 = 2,
	PERF_REG_POWERPC_R3 = 3,
	PERF_REG_POWERPC_R4 = 4,
	PERF_REG_POWERPC_R5 = 5,
	PERF_REG_POWERPC_R6 = 6,
	PERF_REG_POWERPC_R7 = 7,
	PERF_REG_POWERPC_R8 = 8,
	PERF_REG_POWERPC_R9 = 9,
	PERF_REG_POWERPC_R10 = 10,
	PERF_REG_POWERPC_R11 = 11,
	PERF_REG_POWERPC_R12 = 12,
	PERF_REG_POWERPC_R13 = 13,
	PERF_REG_POWERPC_R14 = 14,
	PERF_REG_POWERPC_R15 = 15,
	PERF_REG_POWERPC_R16 = 16,
	PERF_REG_POWERPC_R17 = 17,
	PERF_REG_POWERPC_R18 = 18,
	PERF_REG_POWERPC_R19 = 19,
	PERF_REG_POWERPC_R20 = 20,
	PERF_REG_POWERPC_R21 = 21,
	PERF_REG_POWERPC_R22 = 22,
	PERF_REG_POWERPC_R23 = 23,
	PERF_REG_POWERPC_R24 = 24,
	PERF_REG_POWERPC_R25 = 25,
	PERF_REG_POWERPC_R26 = 26,
	PERF_REG_POWERPC_R27 = 27,
	PERF_REG_POWERPC_R28 = 28,
	PERF_REG_POWERPC_R29 = 29,
	PERF_REG_POWERPC_R30 = 30,
	PERF_REG_POWERPC_R31 = 31,
	PERF_REG_POWERPC_NIP = 32,
	PERF_REG_POWERPC_MSR = 33,
	PERF_REG_POWERPC_ORIG_R3 = 34,
	PERF_REG_POWERPC_CTR = 35,
	PERF_REG_POWERPC_LINK = 36,
	PERF_REG_POWERPC_XER = 37,
	PERF_REG_POWERPC_CCR = 38,
	PERF_REG_POWERPC_SOFTE = 39,
	PERF_REG_POWERPC_TRAP = 40,
	PERF_REG_POWERPC_DAR = 41,
	PERF_REG_POWERPC_DSISR = 42,
	PERF_REG_POWERPC_SIER = 43,
	PERF_REG_POWERPC_MMCRA = 44,
	PERF_REG_POWERPC_MMCR0 = 45,
	PERF_REG_POWERPC_MMCR1 = 46,
	PERF_REG_POWERPC_MMCR2 = 47,
	PERF_REG_POWERPC_MMCR3 = 48,
	PERF_REG_POWERPC_SIER2 = 49,
	PERF_REG_POWERPC_SIER3 = 50,
	PERF_REG_POWERPC_PMC1 = 51,
	PERF_REG_POWERPC_PMC2 = 52,
	PERF_REG_POWERPC_PMC3 = 53,
	PERF_REG_POWERPC_PMC4 = 54,
	PERF_REG_POWERPC_PMC5 = 55,
	PERF_REG_POWERPC_PMC6 = 56,
	PERF_REG_POWERPC_SDAR = 57,
	PERF_REG_POWERPC_SIAR = 58,
	PERF_REG_POWERPC_MAX = 45,
	PERF_REG_EXTENDED_MAX = 59,
};

enum perf_event_sample_format {
	PERF_SAMPLE_IP = 1,
	PERF_SAMPLE_TID = 2,
	PERF_SAMPLE_TIME = 4,
	PERF_SAMPLE_ADDR = 8,
	PERF_SAMPLE_READ = 16,
	PERF_SAMPLE_CALLCHAIN = 32,
	PERF_SAMPLE_ID = 64,
	PERF_SAMPLE_CPU = 128,
	PERF_SAMPLE_PERIOD = 256,
	PERF_SAMPLE_STREAM_ID = 512,
	PERF_SAMPLE_RAW = 1024,
	PERF_SAMPLE_BRANCH_STACK = 2048,
	PERF_SAMPLE_REGS_USER = 4096,
	PERF_SAMPLE_STACK_USER = 8192,
	PERF_SAMPLE_WEIGHT = 16384,
	PERF_SAMPLE_DATA_SRC = 32768,
	PERF_SAMPLE_IDENTIFIER = 65536,
	PERF_SAMPLE_TRANSACTION = 131072,
	PERF_SAMPLE_REGS_INTR = 262144,
	PERF_SAMPLE_PHYS_ADDR = 524288,
	PERF_SAMPLE_AUX = 1048576,
	PERF_SAMPLE_CGROUP = 2097152,
	PERF_SAMPLE_DATA_PAGE_SIZE = 4194304,
	PERF_SAMPLE_CODE_PAGE_SIZE = 8388608,
	PERF_SAMPLE_WEIGHT_STRUCT = 16777216,
	PERF_SAMPLE_MAX = 33554432,
	__PERF_SAMPLE_CALLCHAIN_EARLY = 0,
};

struct mmcr_regs {
	long unsigned int mmcr0;
	long unsigned int mmcr1;
	long unsigned int mmcr2;
	long unsigned int mmcra;
	long unsigned int mmcr3;
};

struct power_pmu {
	const char *name;
	int n_counter;
	int max_alternatives;
	long unsigned int add_fields;
	long unsigned int test_adder;
	int (*compute_mmcr)(u64 *, int, unsigned int *, struct mmcr_regs *, struct perf_event **, u32);
	int (*get_constraint)(u64, long unsigned int *, long unsigned int *, u64);
	int (*get_alternatives)(u64, unsigned int, u64 *);
	void (*get_mem_data_src)(union perf_mem_data_src *, u32, struct pt_regs *);
	void (*get_mem_weight)(u64 *, u64);
	long unsigned int group_constraint_mask;
	long unsigned int group_constraint_val;
	u64 (*bhrb_filter_map)(u64);
	void (*config_bhrb)(u64);
	void (*disable_pmc)(unsigned int, struct mmcr_regs *);
	int (*limited_pmc_event)(u64);
	u32 flags;
	const struct attribute_group **attr_groups;
	int n_generic;
	int *generic_events;
	u64 (*cache_events)[42];
	int n_blacklist_ev;
	int *blacklist_ev;
	int bhrb_nr;
	int capabilities;
	int (*check_attr_config)(struct perf_event *);
};

struct perf_pmu_events_attr {
	struct device_attribute attr;
	u64 id;
	const char *event_str;
};

struct cpu_hw_events {
	int n_events;
	int n_percpu;
	int disabled;
	int n_added;
	int n_limited;
	u8 pmcs_enabled;
	struct perf_event *event[8];
	u64 events[8];
	unsigned int flags[8];
	struct mmcr_regs mmcr;
	struct perf_event *limited_counter[2];
	u8 limited_hwidx[2];
	u64 alternatives[64];
	long unsigned int amasks[64];
	long unsigned int avalues[64];
	unsigned int txn_flags;
	int n_txn_start;
	u64 bhrb_filter;
	unsigned int bhrb_users;
	void *bhrb_context;
	struct perf_branch_stack bhrb_stack;
	struct perf_branch_entry bhrb_entries[32];
	u64 ic_init;
	long unsigned int pmcs[8];
};

struct perf_event_header {
	__u32 type;
	__u16 misc;
	__u16 size;
};

enum perf_event_type {
	PERF_RECORD_MMAP = 1,
	PERF_RECORD_LOST = 2,
	PERF_RECORD_COMM = 3,
	PERF_RECORD_EXIT = 4,
	PERF_RECORD_THROTTLE = 5,
	PERF_RECORD_UNTHROTTLE = 6,
	PERF_RECORD_FORK = 7,
	PERF_RECORD_READ = 8,
	PERF_RECORD_SAMPLE = 9,
	PERF_RECORD_MMAP2 = 10,
	PERF_RECORD_AUX = 11,
	PERF_RECORD_ITRACE_START = 12,
	PERF_RECORD_LOST_SAMPLES = 13,
	PERF_RECORD_SWITCH = 14,
	PERF_RECORD_SWITCH_CPU_WIDE = 15,
	PERF_RECORD_NAMESPACES = 16,
	PERF_RECORD_KSYMBOL = 17,
	PERF_RECORD_BPF_EVENT = 18,
	PERF_RECORD_CGROUP = 19,
	PERF_RECORD_TEXT_POKE = 20,
	PERF_RECORD_AUX_OUTPUT_HW_ID = 21,
	PERF_RECORD_MAX = 22,
};

struct trace_imc_data {
	u64 tb1;
	u64 ip;
	u64 val;
	u64 cpmc1;
	u64 cpmc2;
	u64 cpmc3;
	u64 cpmc4;
	u64 tb2;
};

struct imc_pmu_ref {
	struct mutex lock;
	unsigned int id;
	int refc;
};

enum hv_perf_domains {
	HV_PERF_DOMAIN_PHYS_CHIP = 1,
	HV_PERF_DOMAIN_PHYS_CORE = 2,
	HV_PERF_DOMAIN_VCPU_HOME_CORE = 3,
	HV_PERF_DOMAIN_VCPU_HOME_CHIP = 4,
	HV_PERF_DOMAIN_VCPU_HOME_NODE = 5,
	HV_PERF_DOMAIN_VCPU_REMOTE_NODE = 6,
	HV_PERF_DOMAIN_MAX = 7,
};

struct hv_24x7_request {
	__u8 performance_domain;
	__u8 reserved[1];
	__be16 data_size;
	__be32 data_offset;
	__be16 starting_lpar_ix;
	__be16 max_num_lpars;
	__be16 starting_ix;
	__be16 max_ix;
	__u8 starting_thread_group_ix;
	__u8 max_num_thread_groups;
	__u8 reserved2[14];
};

struct hv_24x7_request_buffer {
	__u8 interface_version;
	__u8 num_requests;
	__u8 reserved[14];
	struct hv_24x7_request requests[0];
};

struct hv_24x7_result {
	__u8 result_ix;
	__u8 results_complete;
	__be16 num_elements_returned;
	__be16 result_element_data_size;
	__u8 reserved[2];
	char elements[0];
};

struct hv_24x7_data_result_buffer {
	__u8 interface_version;
	__u8 num_results;
	__u8 reserved[1];
	__u8 failing_request_ix;
	__be32 detailed_rc;
	__be64 cec_cfg_instance_id;
	__be64 catalog_version_num;
	__u8 reserved2[8];
	struct hv_24x7_result results[0];
};

struct hv_24x7_catalog_page_0 {
	__be32 magic;
	__be32 length;
	__be64 version;
	__u8 build_time_stamp[16];
	__u8 reserved2[32];
	__be16 schema_data_offs;
	__be16 schema_data_len;
	__be16 schema_entry_count;
	__u8 reserved3[2];
	__be16 event_data_offs;
	__be16 event_data_len;
	__be16 event_entry_count;
	__u8 reserved4[2];
	__be16 group_data_offs;
	__be16 group_data_len;
	__be16 group_entry_count;
	__u8 reserved5[2];
	__be16 formula_data_offs;
	__be16 formula_data_len;
	__be16 formula_entry_count;
	__u8 reserved6[2];
};

struct hv_24x7_event_data {
	__be16 length;
	__u8 reserved1[2];
	__u8 domain;
	__u8 reserved2[1];
	__be16 event_group_record_offs;
	__be16 event_group_record_len;
	__be16 event_counter_offs;
	__be32 flags;
	__be16 primary_group_ix;
	__be16 group_count;
	__be16 event_name_len;
	__u8 remainder[0];
} __attribute__((packed));

struct hv_perf_caps {
	u16 version;
	u16 collect_privileged: 1;
	u16 ga: 1;
	u16 expanded: 1;
	u16 lab: 1;
	u16 unused: 12;
};

struct hv_24x7_hw {
	struct perf_event *events[255];
};

struct event_uniq {
	struct rb_node node;
	const char *name;
	int nl;
	unsigned int ct;
	unsigned int domain;
};

enum {
	HV_GPCI_CM_GA = 128,
	HV_GPCI_CM_EXPANDED = 64,
	HV_GPCI_CM_LAB = 32,
};

enum hv_gpci_requests {
	HV_GPCI_dispatch_timebase_by_processor = 16,
	HV_GPCI_entitled_capped_uncapped_donated_idle_timebase_by_partition = 32,
	HV_GPCI_run_instructions_run_cycles_by_partition = 48,
	HV_GPCI_system_performance_capabilities = 64,
	HV_GPCI_processor_bus_utilization_abc_links = 80,
	HV_GPCI_processor_bus_utilization_wxyz_links = 96,
	HV_GPCI_processor_bus_utilization_gx_links = 112,
	HV_GPCI_processor_bus_utilization_mc_links = 128,
	HV_GPCI_processor_core_utilization = 148,
	HV_GPCI_partition_hypervisor_queuing_times = 224,
	HV_GPCI_system_hypervisor_times = 240,
	HV_GPCI_system_tlbie_count_and_time = 244,
	HV_GPCI_partition_instruction_count_and_time = 256,
};

struct hv_gpci_system_performance_capabilities {
	__u8 perf_collect_privileged;
	__u8 capability_mask;
	__u8 reserved[14];
};

struct p {
	struct hv_get_perf_counter_info_params params;
	struct hv_gpci_system_performance_capabilities caps;
};

enum perf_hw_id {
	PERF_COUNT_HW_CPU_CYCLES = 0,
	PERF_COUNT_HW_INSTRUCTIONS = 1,
	PERF_COUNT_HW_CACHE_REFERENCES = 2,
	PERF_COUNT_HW_CACHE_MISSES = 3,
	PERF_COUNT_HW_BRANCH_INSTRUCTIONS = 4,
	PERF_COUNT_HW_BRANCH_MISSES = 5,
	PERF_COUNT_HW_BUS_CYCLES = 6,
	PERF_COUNT_HW_STALLED_CYCLES_FRONTEND = 7,
	PERF_COUNT_HW_STALLED_CYCLES_BACKEND = 8,
	PERF_COUNT_HW_REF_CPU_CYCLES = 9,
	PERF_COUNT_HW_MAX = 10,
};

enum {
	PM_IC_DEMAND_L2_BR_ALL = 18584,
	PM_GCT_UTIL_7_TO_10_SLOTS = 8352,
	PM_PMC2_SAVED = 65570,
	PM_CMPLU_STALL_DFU = 131132,
	PM_VSU0_16FLOP = 41124,
	PM_MRK_LSU_DERAT_MISS = 249946,
	PM_MRK_ST_CMPL = 65588,
	PM_NEST_PAIR3_ADD = 264321,
	PM_L2_ST_DISP = 287104,
	PM_L2_CASTOUT_MOD = 90496,
	PM_ISEG = 8356,
	PM_MRK_INST_TIMEO = 262196,
	PM_L2_RCST_DISP_FAIL_ADDR = 221826,
	PM_LSU1_DC_PREF_STREAM_CONFIRM = 53430,
	PM_IERAT_WR_64K = 16574,
	PM_MRK_DTLB_MISS_16M = 315486,
	PM_IERAT_MISS = 65782,
	PM_MRK_PTEG_FROM_LMEM = 315474,
	PM_FLOP = 65780,
	PM_THRD_PRIO_4_5_CYC = 16564,
	PM_BR_PRED_TA = 16554,
	PM_CMPLU_STALL_FXU = 131092,
	PM_EXT_INT = 131320,
	PM_VSU_FSQRT_FDIV = 43144,
	PM_MRK_LD_MISS_EXPOSED_CYC = 65598,
	PM_LSU1_LDF = 49286,
	PM_IC_WRITE_ALL = 18572,
	PM_LSU0_SRQ_STFWD = 49312,
	PM_PTEG_FROM_RL2L3_MOD = 114770,
	PM_MRK_DATA_FROM_L31_SHR = 118862,
	PM_DATA_FROM_L21_MOD = 245830,
	PM_VSU1_SCAL_DOUBLE_ISSUED = 45194,
	PM_VSU0_8FLOP = 41120,
	PM_POWER_EVENT1 = 65646,
	PM_DISP_CLB_HELD_BAL = 8338,
	PM_VSU1_2FLOP = 41114,
	PM_LWSYNC_HELD = 8346,
	PM_PTEG_FROM_DL2L3_SHR = 245844,
	PM_INST_FROM_L21_MOD = 213062,
	PM_IERAT_XLATE_WR_16MPLUS = 16572,
	PM_IC_REQ_ALL = 18568,
	PM_DSLB_MISS = 53392,
	PM_L3_MISS = 127106,
	PM_LSU0_L1_PREF = 53432,
	PM_VSU_SCALAR_SINGLE_ISSUED = 47236,
	PM_LSU1_DC_PREF_STREAM_CONFIRM_STRIDE = 53438,
	PM_L2_INST = 221312,
	PM_VSU0_FRSP = 41140,
	PM_FLUSH_DISP = 8322,
	PM_PTEG_FROM_L2MISS = 311384,
	PM_VSU1_DQ_ISSUED = 45210,
	PM_CMPLU_STALL_LSU = 131090,
	PM_MRK_DATA_FROM_DMEM = 118858,
	PM_LSU_FLUSH_ULD = 51376,
	PM_PTEG_FROM_LMEM = 311378,
	PM_MRK_DERAT_MISS_16M = 249948,
	PM_THRD_ALL_RUN_CYC = 131084,
	PM_MEM0_PREFETCH_DISP = 131203,
	PM_MRK_STALL_CMPLU_CYC_COUNT = 196671,
	PM_DATA_FROM_DL2L3_MOD = 245836,
	PM_VSU_FRSP = 43188,
	PM_MRK_DATA_FROM_L21_MOD = 249926,
	PM_PMC1_OVERFLOW = 131088,
	PM_VSU0_SINGLE = 41128,
	PM_MRK_PTEG_FROM_L3MISS = 184408,
	PM_MRK_PTEG_FROM_L31_SHR = 184406,
	PM_VSU0_VECTOR_SP_ISSUED = 45200,
	PM_VSU1_FEST = 41146,
	PM_MRK_INST_DISP = 131120,
	PM_VSU0_COMPLEX_ISSUED = 45206,
	PM_LSU1_FLUSH_UST = 49334,
	PM_INST_CMPL = 2,
	PM_FXU_IDLE = 65550,
	PM_LSU0_FLUSH_ULD = 49328,
	PM_MRK_DATA_FROM_DL2L3_MOD = 249932,
	PM_LSU_LMQ_SRQ_EMPTY_ALL_CYC = 196636,
	PM_LSU1_REJECT_LMQ_FULL = 49318,
	PM_INST_PTEG_FROM_L21_MOD = 254038,
	PM_INST_FROM_RL2L3_MOD = 81986,
	PM_SHL_CREATED = 20610,
	PM_L2_ST_HIT = 287106,
	PM_DATA_FROM_DMEM = 114762,
	PM_L3_LD_MISS = 192642,
	PM_FXU1_BUSY_FXU0_IDLE = 262158,
	PM_DISP_CLB_HELD_RES = 8340,
	PM_L2_SN_SX_I_DONE = 222082,
	PM_GRP_CMPL = 196612,
	PM_STCX_CMPL = 49304,
	PM_VSU0_2FLOP = 41112,
	PM_L3_PREF_MISS = 258178,
	PM_LSU_SRQ_SYNC_CYC = 53398,
	PM_LSU_REJECT_ERAT_MISS = 131172,
	PM_L1_ICACHE_MISS = 131324,
	PM_LSU1_FLUSH_SRQ = 49342,
	PM_LD_REF_L1_LSU0 = 49280,
	PM_VSU0_FEST = 41144,
	PM_VSU_VECTOR_SINGLE_ISSUED = 47248,
	PM_FREQ_UP = 262156,
	PM_DATA_FROM_LMEM = 245834,
	PM_LSU1_LDX = 49290,
	PM_PMC3_OVERFLOW = 262160,
	PM_MRK_BR_MPRED = 196662,
	PM_SHL_MATCH = 20614,
	PM_MRK_BR_TAKEN = 65590,
	PM_CMPLU_STALL_BRU = 262222,
	PM_ISLB_MISS = 53394,
	PM_CYC = 30,
	PM_DISP_HELD_THERMAL = 196614,
	PM_INST_PTEG_FROM_RL2L3_SHR = 188500,
	PM_LSU1_SRQ_STFWD = 49314,
	PM_GCT_NOSLOT_BR_MPRED = 262170,
	PM_1PLUS_PPC_CMPL = 65778,
	PM_PTEG_FROM_DMEM = 180306,
	PM_VSU_2FLOP = 43160,
	PM_GCT_FULL_CYC = 16518,
	PM_MRK_DATA_FROM_L3_CYC = 262176,
	PM_LSU_SRQ_S0_ALLOC = 53405,
	PM_MRK_DERAT_MISS_4K = 118876,
	PM_BR_MPRED_TA = 16558,
	PM_INST_PTEG_FROM_L2MISS = 319576,
	PM_DPU_HELD_POWER = 131078,
	PM_RUN_INST_CMPL = 262394,
	PM_MRK_VSU_FIN = 196658,
	PM_LSU_SRQ_S0_VALID = 53404,
	PM_GCT_EMPTY_CYC = 131080,
	PM_IOPS_DISP = 196628,
	PM_RUN_SPURR = 65544,
	PM_PTEG_FROM_L21_MOD = 245846,
	PM_VSU0_1FLOP = 41088,
	PM_SNOOP_TLBIE = 53426,
	PM_DATA_FROM_L3MISS = 180296,
	PM_VSU_SINGLE = 43176,
	PM_DTLB_MISS_16G = 114782,
	PM_CMPLU_STALL_VECTOR = 131100,
	PM_FLUSH = 262392,
	PM_L2_LD_HIT = 221570,
	PM_NEST_PAIR2_AND = 198787,
	PM_VSU1_1FLOP = 41090,
	PM_IC_PREF_REQ = 16522,
	PM_L3_LD_HIT = 192640,
	PM_GCT_NOSLOT_IC_MISS = 131098,
	PM_DISP_HELD = 65542,
	PM_L2_LD = 90240,
	PM_LSU_FLUSH_SRQ = 51388,
	PM_BC_PLUS_8_CONV = 16568,
	PM_MRK_DATA_FROM_L31_MOD_CYC = 262182,
	PM_CMPLU_STALL_VECTOR_LONG = 262218,
	PM_L2_RCST_BUSY_RC_FULL = 156290,
	PM_TB_BIT_TRANS = 196856,
	PM_THERMAL_MAX = 262150,
	PM_LSU1_FLUSH_ULD = 49330,
	PM_LSU1_REJECT_LHS = 49326,
	PM_LSU_LRQ_S0_ALLOC = 53407,
	PM_L3_CO_L31 = 323712,
	PM_POWER_EVENT4 = 262254,
	PM_DATA_FROM_L31_SHR = 114766,
	PM_BR_UNCOND = 16542,
	PM_LSU1_DC_PREF_STREAM_ALLOC = 53418,
	PM_PMC4_REWIND = 65568,
	PM_L2_RCLD_DISP = 90752,
	PM_THRD_PRIO_2_3_CYC = 16562,
	PM_MRK_PTEG_FROM_L2MISS = 315480,
	PM_IC_DEMAND_L2_BHT_REDIRECT = 16536,
	PM_LSU_DERAT_MISS = 131318,
	PM_IC_PREF_CANCEL_L2 = 16532,
	PM_MRK_FIN_STALL_CYC_COUNT = 65597,
	PM_BR_PRED_CCACHE = 16544,
	PM_GCT_UTIL_1_TO_2_SLOTS = 8348,
	PM_MRK_ST_CMPL_INT = 196660,
	PM_LSU_TWO_TABLEWALK_CYC = 53414,
	PM_MRK_DATA_FROM_L3MISS = 184392,
	PM_GCT_NOSLOT_CYC = 65784,
	PM_LSU_SET_MPRED = 49320,
	PM_FLUSH_DISP_TLBIE = 8330,
	PM_VSU1_FCONV = 41138,
	PM_DERAT_MISS_16G = 311388,
	PM_INST_FROM_LMEM = 213066,
	PM_IC_DEMAND_L2_BR_REDIRECT = 16538,
	PM_CMPLU_STALL_SCALAR_LONG = 131096,
	PM_INST_PTEG_FROM_L2 = 122960,
	PM_PTEG_FROM_L2 = 114768,
	PM_MRK_DATA_FROM_L21_SHR_CYC = 131108,
	PM_MRK_DTLB_MISS_4K = 184410,
	PM_VSU0_FPSCR = 45212,
	PM_VSU1_VECT_DOUBLE_ISSUED = 45186,
	PM_MRK_PTEG_FROM_RL2L3_MOD = 118866,
	PM_MEM0_RQ_DISP = 65667,
	PM_L2_LD_MISS = 155776,
	PM_VMX_RESULT_SAT_1 = 45216,
	PM_L1_PREF = 55480,
	PM_MRK_DATA_FROM_LMEM_CYC = 131116,
	PM_GRP_IC_MISS_NONSPEC = 65548,
	PM_PB_NODE_PUMP = 65665,
	PM_SHL_MERGED = 20612,
	PM_NEST_PAIR1_ADD = 133249,
	PM_DATA_FROM_L3 = 114760,
	PM_LSU_FLUSH = 8334,
	PM_LSU_SRQ_SYNC_COUNT = 53399,
	PM_PMC2_OVERFLOW = 196624,
	PM_LSU_LDF = 51332,
	PM_POWER_EVENT3 = 196718,
	PM_DISP_WT = 196616,
	PM_CMPLU_STALL_REJECT = 262166,
	PM_IC_BANK_CONFLICT = 16514,
	PM_BR_MPRED_CR_TA = 18606,
	PM_L2_INST_MISS = 221314,
	PM_CMPLU_STALL_ERAT_MISS = 262168,
	PM_NEST_PAIR2_ADD = 198785,
	PM_MRK_LSU_FLUSH = 53388,
	PM_L2_LDST = 92288,
	PM_INST_FROM_L31_SHR = 81998,
	PM_VSU0_FIN = 41148,
	PM_LARX_LSU = 51348,
	PM_INST_FROM_RMEM = 213058,
	PM_DISP_CLB_HELD_TLBIE = 8342,
	PM_MRK_DATA_FROM_DMEM_CYC = 131118,
	PM_BR_PRED_CR = 16552,
	PM_LSU_REJECT = 65636,
	PM_GCT_UTIL_3_TO_6_SLOTS = 8350,
	PM_CMPLU_STALL_END_GCT_NOSLOT = 65576,
	PM_LSU0_REJECT_LMQ_FULL = 49316,
	PM_VSU_FEST = 43192,
	PM_NEST_PAIR0_AND = 67715,
	PM_PTEG_FROM_L3 = 180304,
	PM_POWER_EVENT2 = 131182,
	PM_IC_PREF_CANCEL_PAGE = 16528,
	PM_VSU0_FSQRT_FDIV = 41096,
	PM_MRK_GRP_CMPL = 262192,
	PM_VSU0_SCAL_DOUBLE_ISSUED = 45192,
	PM_GRP_DISP = 196618,
	PM_LSU0_LDX = 49288,
	PM_DATA_FROM_L2 = 114752,
	PM_MRK_DATA_FROM_RL2L3_MOD = 118850,
	PM_LD_REF_L1 = 51328,
	PM_VSU0_VECT_DOUBLE_ISSUED = 45184,
	PM_VSU1_2FLOP_DOUBLE = 41102,
	PM_THRD_PRIO_6_7_CYC = 16566,
	PM_BC_PLUS_8_RSLV_TAKEN = 16570,
	PM_BR_MPRED_CR = 16556,
	PM_L3_CO_MEM = 323714,
	PM_LD_MISS_L1 = 262384,
	PM_DATA_FROM_RL2L3_MOD = 114754,
	PM_LSU_SRQ_FULL_CYC = 65562,
	PM_TABLEWALK_CYC = 65574,
	PM_MRK_PTEG_FROM_RMEM = 249938,
	PM_LSU_SRQ_STFWD = 51360,
	PM_INST_PTEG_FROM_RMEM = 254034,
	PM_FXU0_FIN = 65540,
	PM_LSU1_L1_SW_PREF = 49310,
	PM_PTEG_FROM_L31_MOD = 114772,
	PM_PMC5_OVERFLOW = 65572,
	PM_LD_REF_L1_LSU1 = 49282,
	PM_INST_PTEG_FROM_L21_SHR = 319574,
	PM_CMPLU_STALL_THRD = 65564,
	PM_DATA_FROM_RMEM = 245826,
	PM_VSU0_SCAL_SINGLE_ISSUED = 45188,
	PM_BR_MPRED_LSTACK = 16550,
	PM_MRK_DATA_FROM_RL2L3_MOD_CYC = 262184,
	PM_LSU0_FLUSH_UST = 49332,
	PM_LSU_NCST = 49296,
	PM_BR_TAKEN = 131076,
	PM_INST_PTEG_FROM_LMEM = 319570,
	PM_GCT_NOSLOT_BR_MPRED_IC_MISS = 262172,
	PM_DTLB_MISS_4K = 180314,
	PM_PMC4_SAVED = 196642,
	PM_VSU1_PERMUTE_ISSUED = 45202,
	PM_SLB_MISS = 55440,
	PM_LSU1_FLUSH_LRQ = 49338,
	PM_DTLB_MISS = 196860,
	PM_VSU1_FRSP = 41142,
	PM_VSU_VECTOR_DOUBLE_ISSUED = 47232,
	PM_L2_CASTOUT_SHR = 90498,
	PM_DATA_FROM_DL2L3_SHR = 245828,
	PM_VSU1_STF = 45198,
	PM_ST_FIN = 131312,
	PM_PTEG_FROM_L21_SHR = 311382,
	PM_L2_LOC_GUESS_WRONG = 156800,
	PM_MRK_STCX_FAIL = 53390,
	PM_LSU0_REJECT_LHS = 49324,
	PM_IC_PREF_CANCEL_HIT = 16530,
	PM_L3_PREF_BUSY = 323712,
	PM_MRK_BRU_FIN = 131130,
	PM_LSU1_NCLD = 49294,
	PM_INST_PTEG_FROM_L31_MOD = 122964,
	PM_LSU_NCLD = 51340,
	PM_LSU_LDX = 51336,
	PM_L2_LOC_GUESS_CORRECT = 91264,
	PM_THRESH_TIMEO = 65592,
	PM_L3_PREF_ST = 53422,
	PM_DISP_CLB_HELD_SYNC = 8344,
	PM_VSU_SIMPLE_ISSUED = 47252,
	PM_VSU1_SINGLE = 41130,
	PM_DATA_TABLEWALK_CYC = 196634,
	PM_L2_RC_ST_DONE = 222080,
	PM_MRK_PTEG_FROM_L21_MOD = 249942,
	PM_LARX_LSU1 = 49302,
	PM_MRK_DATA_FROM_RMEM = 249922,
	PM_DISP_CLB_HELD = 8336,
	PM_DERAT_MISS_4K = 114780,
	PM_L2_RCLD_DISP_FAIL_ADDR = 90754,
	PM_SEG_EXCEPTION = 10404,
	PM_FLUSH_DISP_SB = 8332,
	PM_L2_DC_INV = 156034,
	PM_PTEG_FROM_DL2L3_MOD = 311380,
	PM_DSEG = 8358,
	PM_BR_PRED_LSTACK = 16546,
	PM_VSU0_STF = 45196,
	PM_LSU_FX_FIN = 65638,
	PM_DERAT_MISS_16M = 245852,
	PM_MRK_PTEG_FROM_DL2L3_MOD = 315476,
	PM_GCT_UTIL_11_PLUS_SLOTS = 8354,
	PM_INST_FROM_L3 = 81992,
	PM_MRK_IFU_FIN = 196666,
	PM_ITLB_MISS = 262396,
	PM_VSU_STF = 47244,
	PM_LSU_FLUSH_UST = 51380,
	PM_L2_LDST_MISS = 157824,
	PM_FXU1_FIN = 262148,
	PM_SHL_DEALLOCATED = 20608,
	PM_L2_SN_M_WR_DONE = 287618,
	PM_LSU_REJECT_SET_MPRED = 51368,
	PM_L3_PREF_LD = 53420,
	PM_L2_SN_M_RD_DONE = 287616,
	PM_MRK_DERAT_MISS_16G = 315484,
	PM_VSU_FCONV = 43184,
	PM_ANY_THRD_RUN_CYC = 65786,
	PM_LSU_LMQ_FULL_CYC = 53412,
	PM_MRK_LSU_REJECT_LHS = 53378,
	PM_MRK_LD_MISS_L1_CYC = 262206,
	PM_MRK_DATA_FROM_L2_CYC = 131104,
	PM_INST_IMC_MATCH_DISP = 196630,
	PM_MRK_DATA_FROM_RMEM_CYC = 262188,
	PM_VSU0_SIMPLE_ISSUED = 45204,
	PM_CMPLU_STALL_DIV = 262164,
	PM_MRK_PTEG_FROM_RL2L3_SHR = 184404,
	PM_VSU_FMA_DOUBLE = 43152,
	PM_VSU_4FLOP = 43164,
	PM_VSU1_FIN = 41150,
	PM_NEST_PAIR1_AND = 133251,
	PM_INST_PTEG_FROM_RL2L3_MOD = 122962,
	PM_RUN_CYC = 131316,
	PM_PTEG_FROM_RMEM = 245842,
	PM_LSU_LRQ_S0_VALID = 53406,
	PM_LSU0_LDF = 49284,
	PM_FLUSH_COMPLETION = 196626,
	PM_ST_MISS_L1 = 196848,
	PM_L2_NODE_PUMP = 222336,
	PM_INST_FROM_DL2L3_SHR = 213060,
	PM_MRK_STALL_CMPLU_CYC = 196670,
	PM_VSU1_DENORM = 41134,
	PM_MRK_DATA_FROM_L31_SHR_CYC = 131110,
	PM_NEST_PAIR0_ADD = 67713,
	PM_INST_FROM_L3MISS = 147528,
	PM_EE_OFF_EXT_INT = 8320,
	PM_INST_PTEG_FROM_DMEM = 188498,
	PM_INST_FROM_DL2L3_MOD = 213068,
	PM_PMC6_OVERFLOW = 196644,
	PM_VSU_2FLOP_DOUBLE = 43148,
	PM_TLB_MISS = 131174,
	PM_FXU_BUSY = 131086,
	PM_L2_RCLD_DISP_FAIL_OTHER = 156288,
	PM_LSU_REJECT_LMQ_FULL = 51364,
	PM_IC_RELOAD_SHR = 16534,
	PM_GRP_MRK = 65585,
	PM_MRK_ST_NEST = 131124,
	PM_VSU1_FSQRT_FDIV = 41098,
	PM_LSU0_FLUSH_LRQ = 49336,
	PM_LARX_LSU0 = 49300,
	PM_IBUF_FULL_CYC = 16516,
	PM_MRK_DATA_FROM_DL2L3_SHR_CYC = 131114,
	PM_LSU_DC_PREF_STREAM_ALLOC = 55464,
	PM_GRP_MRK_CYC = 65584,
	PM_MRK_DATA_FROM_RL2L3_SHR_CYC = 131112,
	PM_L2_GLOB_GUESS_CORRECT = 91266,
	PM_LSU_REJECT_LHS = 51372,
	PM_MRK_DATA_FROM_LMEM = 249930,
	PM_INST_PTEG_FROM_L3 = 188496,
	PM_FREQ_DOWN = 196620,
	PM_PB_RETRY_NODE_PUMP = 196737,
	PM_INST_FROM_RL2L3_SHR = 81996,
	PM_MRK_INST_ISSUED = 65586,
	PM_PTEG_FROM_L3MISS = 180312,
	PM_RUN_PURR = 262388,
	PM_MRK_GRP_IC_MISS = 262200,
	PM_MRK_DATA_FROM_L3 = 118856,
	PM_CMPLU_STALL_DCACHE_MISS = 131094,
	PM_PTEG_FROM_RL2L3_SHR = 180308,
	PM_LSU_FLUSH_LRQ = 51384,
	PM_MRK_DERAT_MISS_64K = 184412,
	PM_INST_PTEG_FROM_DL2L3_MOD = 319572,
	PM_L2_ST_MISS = 155778,
	PM_MRK_PTEG_FROM_L21_SHR = 315478,
	PM_LWSYNC = 53396,
	PM_LSU0_DC_PREF_STREAM_CONFIRM_STRIDE = 53436,
	PM_MRK_LSU_FLUSH_LRQ = 53384,
	PM_INST_IMC_MATCH_CMPL = 65776,
	PM_NEST_PAIR3_AND = 264323,
	PM_PB_RETRY_SYS_PUMP = 262273,
	PM_MRK_INST_FIN = 196656,
	PM_MRK_PTEG_FROM_DL2L3_SHR = 249940,
	PM_INST_FROM_L31_MOD = 81988,
	PM_MRK_DTLB_MISS_64K = 249950,
	PM_LSU_FIN = 196710,
	PM_MRK_LSU_REJECT = 262244,
	PM_L2_CO_FAIL_BUSY = 91010,
	PM_MEM0_WQ_DISP = 262275,
	PM_DATA_FROM_L31_MOD = 114756,
	PM_THERMAL_WARN = 65558,
	PM_VSU0_4FLOP = 41116,
	PM_BR_MPRED_CCACHE = 16548,
	PM_CMPLU_STALL_IFU = 262220,
	PM_L1_DEMAND_WRITE = 16524,
	PM_FLUSH_BR_MPRED = 8324,
	PM_MRK_DTLB_MISS_16G = 118878,
	PM_MRK_PTEG_FROM_DMEM = 184402,
	PM_L2_RCST_DISP = 221824,
	PM_CMPLU_STALL = 262154,
	PM_LSU_PARTIAL_CDF = 49322,
	PM_DISP_CLB_HELD_SB = 8360,
	PM_VSU0_FMA_DOUBLE = 41104,
	PM_FXU0_BUSY_FXU1_IDLE = 196622,
	PM_IC_DEMAND_CYC = 65560,
	PM_MRK_DATA_FROM_L21_SHR = 249934,
	PM_MRK_LSU_FLUSH_UST = 53382,
	PM_INST_PTEG_FROM_L3MISS = 188504,
	PM_VSU_DENORM = 43180,
	PM_MRK_LSU_PARTIAL_CDF = 53376,
	PM_INST_FROM_L21_SHR = 213070,
	PM_IC_PREF_WRITE = 16526,
	PM_BR_PRED = 16540,
	PM_INST_FROM_DMEM = 81994,
	PM_IC_PREF_CANCEL_ALL = 18576,
	PM_LSU_DC_PREF_STREAM_CONFIRM = 55476,
	PM_MRK_LSU_FLUSH_SRQ = 53386,
	PM_MRK_FIN_STALL_CYC = 65596,
	PM_L2_RCST_DISP_FAIL_OTHER = 287360,
	PM_VSU1_DD_ISSUED = 45208,
	PM_PTEG_FROM_L31_SHR = 180310,
	PM_DATA_FROM_L21_SHR = 245838,
	PM_LSU0_NCLD = 49292,
	PM_VSU1_4FLOP = 41118,
	PM_VSU1_8FLOP = 41122,
	PM_VSU_8FLOP = 43168,
	PM_LSU_LMQ_SRQ_EMPTY_CYC = 131134,
	PM_DTLB_MISS_64K = 245854,
	PM_THRD_CONC_RUN_INST = 196852,
	PM_MRK_PTEG_FROM_L2 = 118864,
	PM_PB_SYS_PUMP = 131201,
	PM_VSU_FIN = 43196,
	PM_MRK_DATA_FROM_L31_MOD = 118852,
	PM_THRD_PRIO_0_1_CYC = 16560,
	PM_DERAT_MISS_64K = 180316,
	PM_PMC2_REWIND = 196640,
	PM_INST_FROM_L2 = 81984,
	PM_GRP_BR_MPRED_NONSPEC = 65546,
	PM_INST_DISP = 131314,
	PM_MEM0_RD_CANCEL_TOTAL = 196739,
	PM_LSU0_DC_PREF_STREAM_CONFIRM = 53428,
	PM_L1_DCACHE_RELOAD_VALID = 196854,
	PM_VSU_SCALAR_DOUBLE_ISSUED = 47240,
	PM_L3_PREF_HIT = 258176,
	PM_MRK_PTEG_FROM_L31_MOD = 118868,
	PM_CMPLU_STALL_STORE = 131146,
	PM_MRK_FXU_FIN = 131128,
	PM_PMC4_OVERFLOW = 65552,
	PM_MRK_PTEG_FROM_L3 = 184400,
	PM_LSU0_LMQ_LHR_MERGE = 53400,
	PM_BTAC_HIT = 20618,
	PM_L3_RD_BUSY = 323714,
	PM_LSU0_L1_SW_PREF = 49308,
	PM_INST_FROM_L2MISS = 278600,
	PM_LSU0_DC_PREF_STREAM_ALLOC = 53416,
	PM_L2_ST = 90242,
	PM_VSU0_DENORM = 41132,
	PM_MRK_DATA_FROM_DL2L3_SHR = 249924,
	PM_BR_PRED_CR_TA = 18602,
	PM_VSU0_FCONV = 41136,
	PM_MRK_LSU_FLUSH_ULD = 53380,
	PM_BTAC_MISS = 20616,
	PM_MRK_LD_MISS_EXPOSED_CYC_COUNT = 65599,
	PM_MRK_DATA_FROM_L2 = 118848,
	PM_LSU_DCACHE_RELOAD_VALID = 53410,
	PM_VSU_FMA = 43140,
	PM_LSU0_FLUSH_SRQ = 49340,
	PM_LSU1_L1_PREF = 53434,
	PM_IOPS_CMPL = 65556,
	PM_L2_SYS_PUMP = 222338,
	PM_L2_RCLD_BUSY_RC_FULL = 287362,
	PM_LSU_LMQ_S0_ALLOC = 53409,
	PM_FLUSH_DISP_SYNC = 8328,
	PM_MRK_DATA_FROM_DL2L3_MOD_CYC = 262186,
	PM_L2_IC_INV = 156032,
	PM_MRK_DATA_FROM_L21_MOD_CYC = 262180,
	PM_L3_PREF_LDST = 55468,
	PM_LSU_SRQ_EMPTY_CYC = 262152,
	PM_LSU_LMQ_S0_VALID = 53408,
	PM_FLUSH_PARTIAL = 8326,
	PM_VSU1_FMA_DOUBLE = 41106,
	PM_1PLUS_PPC_DISP = 262386,
	PM_DATA_FROM_L2MISS = 131326,
	PM_SUSPENDED = 0,
	PM_VSU0_FMA = 41092,
	PM_CMPLU_STALL_SCALAR = 262162,
	PM_STCX_FAIL = 49306,
	PM_VSU0_FSQRT_FDIV_DOUBLE = 41108,
	PM_DC_PREF_DST = 53424,
	PM_VSU1_SCAL_SINGLE_ISSUED = 45190,
	PM_L3_HIT = 127104,
	PM_L2_GLOB_GUESS_WRONG = 156802,
	PM_MRK_DFU_FIN = 131122,
	PM_INST_FROM_L1 = 16512,
	PM_BRU_FIN = 65640,
	PM_IC_DEMAND_REQ = 16520,
	PM_VSU1_FSQRT_FDIV_DOUBLE = 41110,
	PM_VSU1_FMA = 41094,
	PM_MRK_LD_MISS_L1 = 131126,
	PM_VSU0_2FLOP_DOUBLE = 41100,
	PM_LSU_DC_PREF_STRIDED_STREAM_CONFIRM = 55484,
	PM_INST_PTEG_FROM_L31_SHR = 188502,
	PM_MRK_LSU_REJECT_ERAT_MISS = 196708,
	PM_MRK_DATA_FROM_L2MISS = 315464,
	PM_DATA_FROM_RL2L3_SHR = 114764,
	PM_INST_FROM_PREF = 81990,
	PM_VSU1_SQ = 45214,
	PM_L2_LD_DISP = 221568,
	PM_L2_DISP_ALL = 286848,
	PM_THRD_GRP_CMPL_BOTH_CYC = 65554,
	PM_VSU_FSQRT_FDIV_DOUBLE = 43156,
	PM_BR_MPRED = 262390,
	PM_INST_PTEG_FROM_DL2L3_SHR = 254036,
	PM_VSU_1FLOP = 43136,
	PM_HV_CYC = 131082,
	PM_MRK_LSU_FIN = 262194,
	PM_MRK_DATA_FROM_RL2L3_SHR = 118860,
	PM_DTLB_MISS_16M = 311390,
	PM_LSU1_LMQ_LHR_MERGE = 53402,
	PM_IFU_FIN = 262246,
	PM_1THRD_CON_RUN_INSTR = 196706,
	PM_CMPLU_STALL_COUNT = 262155,
	PM_MEM0_PB_RD_CL = 196739,
	PM_THRD_1_RUN_CYC = 65632,
	PM_THRD_2_CONC_RUN_INSTR = 262242,
	PM_THRD_2_RUN_CYC = 131168,
	PM_THRD_3_CONC_RUN_INST = 65634,
	PM_THRD_3_RUN_CYC = 196704,
	PM_THRD_4_CONC_RUN_INST = 131170,
	PM_THRD_4_RUN_CYC = 262240,
};

enum perf_branch_sample_type {
	PERF_SAMPLE_BRANCH_USER = 1,
	PERF_SAMPLE_BRANCH_KERNEL = 2,
	PERF_SAMPLE_BRANCH_HV = 4,
	PERF_SAMPLE_BRANCH_ANY = 8,
	PERF_SAMPLE_BRANCH_ANY_CALL = 16,
	PERF_SAMPLE_BRANCH_ANY_RETURN = 32,
	PERF_SAMPLE_BRANCH_IND_CALL = 64,
	PERF_SAMPLE_BRANCH_ABORT_TX = 128,
	PERF_SAMPLE_BRANCH_IN_TX = 256,
	PERF_SAMPLE_BRANCH_NO_TX = 512,
	PERF_SAMPLE_BRANCH_COND = 1024,
	PERF_SAMPLE_BRANCH_CALL_STACK = 2048,
	PERF_SAMPLE_BRANCH_IND_JUMP = 4096,
	PERF_SAMPLE_BRANCH_CALL = 8192,
	PERF_SAMPLE_BRANCH_NO_FLAGS = 16384,
	PERF_SAMPLE_BRANCH_NO_CYCLES = 32768,
	PERF_SAMPLE_BRANCH_TYPE_SAVE = 65536,
	PERF_SAMPLE_BRANCH_HW_INDEX = 131072,
	PERF_SAMPLE_BRANCH_MAX = 262144,
};

enum {
	PM_CYC___2 = 30,
	PM_GCT_NOSLOT_CYC___2 = 65784,
	PM_CMPLU_STALL___2 = 262154,
	PM_INST_CMPL___2 = 2,
	PM_BRU_FIN___2 = 65640,
	PM_BR_MPRED_CMPL = 262390,
	PM_LD_REF_L1___2 = 65774,
	PM_LD_MISS_L1___2 = 254036,
	PM_ST_MISS_L1___2 = 196848,
	PM_L1_PREF___2 = 55480,
	PM_INST_FROM_L1___2 = 16512,
	PM_L1_ICACHE_MISS___2 = 131325,
	PM_L1_DEMAND_WRITE___2 = 16524,
	PM_IC_PREF_WRITE___2 = 16526,
	PM_DATA_FROM_L3___2 = 311362,
	PM_DATA_FROM_L3MISS___2 = 196862,
	PM_L2_ST___2 = 94336,
	PM_L2_ST_MISS___2 = 94338,
	PM_L3_PREF_ALL = 319570,
	PM_DTLB_MISS___2 = 196860,
	PM_ITLB_MISS___2 = 262396,
	PM_RUN_INST_CMPL___2 = 327930,
	PM_RUN_INST_CMPL_ALT = 262394,
	PM_RUN_CYC___2 = 393460,
	PM_RUN_CYC_ALT = 131316,
	PM_MRK_ST_CMPL___2 = 65844,
	PM_MRK_ST_CMPL_ALT = 197090,
	PM_BR_MRK_2PATH = 65848,
	PM_BR_MRK_2PATH_ALT = 262456,
	PM_L3_CO_MEPF = 98434,
	PM_L3_CO_MEPF_ALT = 254046,
	PM_MRK_DATA_FROM_L2MISS___2 = 119118,
	PM_MRK_DATA_FROM_L2MISS_ALT = 262632,
	PM_CMPLU_STALL_ALT = 122964,
	PM_BR_2PATH = 131126,
	PM_BR_2PATH_ALT = 262198,
	PM_INST_DISP___2 = 131314,
	PM_INST_DISP_ALT = 196850,
	PM_MRK_FILT_MATCH = 131388,
	PM_MRK_FILT_MATCH_ALT = 196910,
	PM_LD_MISS_L1_ALT = 262384,
	MEM_ACCESS = 17039840,
};

enum {
	PM_CYC___3 = 30,
	PM_ICT_NOSLOT_CYC = 65784,
	PM_CMPLU_STALL___3 = 122964,
	PM_INST_CMPL___3 = 2,
	PM_BR_CMPL = 315486,
	PM_BR_MPRED_CMPL___2 = 262390,
	PM_LD_REF_L1___3 = 65788,
	PM_LD_MISS_L1_FIN = 180302,
	PM_LD_MISS_L1___3 = 254036,
	PM_LD_MISS_L1_ALT___2 = 262384,
	PM_ST_MISS_L1___3 = 196848,
	PM_L1_PREF___3 = 131156,
	PM_INST_FROM_L1___3 = 16512,
	PM_L1_ICACHE_MISS___3 = 131325,
	PM_L1_DEMAND_WRITE___3 = 16524,
	PM_IC_PREF_WRITE___3 = 18572,
	PM_DATA_FROM_L3___3 = 311362,
	PM_DATA_FROM_L3MISS___3 = 196862,
	PM_L2_ST___3 = 92288,
	PM_L2_ST_MISS___3 = 157824,
	PM_L3_PREF_ALL___2 = 319570,
	PM_DTLB_MISS___3 = 196860,
	PM_ITLB_MISS___3 = 262396,
	PM_RUN_INST_CMPL___3 = 327930,
	PM_RUN_INST_CMPL_ALT___2 = 262394,
	PM_RUN_CYC___3 = 393460,
	PM_RUN_CYC_ALT___2 = 131316,
	PM_INST_DISP___3 = 131314,
	PM_INST_DISP_ALT___2 = 196850,
	PM_BR_2PATH___2 = 131126,
	PM_BR_2PATH_ALT___2 = 262198,
	PM_MRK_ST_DONE_L2 = 65844,
	PM_RADIX_PWC_L1_HIT = 127062,
	PM_FLOP_CMPL = 65780,
	PM_MRK_NTF_FIN = 131346,
	PM_RADIX_PWC_L2_HIT = 184356,
	PM_IFETCH_THROTTLE = 213086,
	PM_MRK_L2_TM_ST_ABORT_SISTER = 254300,
	PM_RADIX_PWC_L3_HIT = 258134,
	PM_RUN_CYC_SMT2_MODE = 196716,
	PM_TM_TX_PASS_RUN_INST = 319508,
	PM_DISP_HELD_SYNC_HOLD = 262204,
	PM_DTLB_MISS_16G___2 = 114776,
	PM_DERAT_MISS_2M = 114778,
	PM_DTLB_MISS_2M = 114780,
	PM_MRK_DTLB_MISS_1G = 119132,
	PM_DTLB_MISS_4K___2 = 180310,
	PM_DERAT_MISS_1G = 180314,
	PM_MRK_DERAT_MISS_2M = 184658,
	PM_MRK_DTLB_MISS_4K___2 = 184662,
	PM_MRK_DTLB_MISS_16G___2 = 184670,
	PM_DTLB_MISS_64K___2 = 245846,
	PM_MRK_DERAT_MISS_1G = 250194,
	PM_MRK_DTLB_MISS_64K___2 = 250198,
	PM_DTLB_MISS_16M___2 = 311382,
	PM_DTLB_MISS_1G = 311386,
	PM_MRK_DTLB_MISS_16M___2 = 311646,
	MEM_LOADS = 872677856,
	MEM_STORES = 1006895584,
};

enum {
	PM_CYC_ALT = 65776,
	PM_CYC_INST_CMPL = 65778,
	PM_FLOP_CMPL___2 = 65780,
	PM_L1_ITLB_MISS = 65782,
	PM_NO_INST_AVAIL = 65784,
	PM_LD_CMPL = 65788,
	PM_INST_CMPL_ALT = 65790,
	PM_ST_CMPL = 131312,
	PM_INST_DISP___4 = 131314,
	PM_RUN_CYC___4 = 131316,
	PM_L1_DTLB_RELOAD = 131318,
	PM_BR_TAKEN_CMPL = 131322,
	PM_L1_ICACHE_MISS___4 = 131324,
	PM_L1_RELOAD_FROM_MEM = 131326,
	PM_ST_MISS_L1___4 = 196848,
	PM_INST_DISP_ALT___3 = 196850,
	PM_BR_MISPREDICT = 196854,
	PM_DTLB_MISS___4 = 196860,
	PM_DATA_FROM_L3MISS___4 = 196862,
	PM_LD_MISS_L1___4 = 262384,
	PM_CYC_INST_DISP = 262386,
	PM_BR_MPRED_CMPL___3 = 262390,
	PM_RUN_INST_CMPL___4 = 262394,
	PM_ITLB_MISS___4 = 262396,
	PM_LD_NOT_CACHED = 262398,
	PM_INST_CMPL___4 = 327930,
	PM_CYC___4 = 393460,
};

enum {
	PM_CYC___5 = 393460,
};

enum {
	PM_INST_CMPL___5 = 327930,
};

enum {
	PM_BR_CMPL___2 = 315486,
};

enum {
	PM_BR_MPRED_CMPL___4 = 262390,
};

enum {
	PM_BR_FIN = 192586,
};

enum {
	PM_MPRED_BR_FIN = 254104,
};

enum {
	PM_LD_DEMAND_MISS_L1_FIN = 262384,
};

enum {
	PM_LD_REF_L1___4 = 65788,
};

enum {
	PM_LD_MISS_L1___5 = 254036,
};

enum {
	PM_ST_MISS_L1___5 = 196848,
};

enum {
	PM_LD_PREFETCH_CACHE_LINE_MISS = 65580,
};

enum {
	PM_L1_ICACHE_MISS___5 = 131324,
};

enum {
	PM_INST_FROM_L1___4 = 16512,
};

enum {
	PM_INST_FROM_L1MISS = 114752,
};

enum {
	PM_IC_PREF_REQ___2 = 16544,
};

enum {
	PM_DATA_FROM_L3___4 = 114752,
};

enum {
	PM_DATA_FROM_L3MISS___5 = 196862,
};

enum {
	PM_L2_ST___4 = 286848,
};

enum {
	PM_L2_ST_MISS___4 = 157824,
};

enum {
	PM_L3_PF_MISS_L3 = 90240,
};

enum {
	PM_DTLB_MISS___5 = 196860,
};

enum {
	PM_ITLB_MISS___5 = 262396,
};

enum {
	PM_CYC_ALT___2 = 30,
};

enum {
	PM_INST_CMPL_ALT___2 = 2,
};

enum {
	MEM_LOADS___2 = 872677856,
};

enum {
	MEM_STORES___2 = 1006895584,
};

typedef void (*crash_shutdown_t)();

union thread_union {
	struct task_struct task;
	long unsigned int stack[2048];
};

typedef struct elf64_phdr Elf64_Phdr;

struct kexec_buf {
	struct kimage *image;
	void *buffer;
	long unsigned int bufsz;
	long unsigned int mem;
	long unsigned int memsz;
	long unsigned int buf_align;
	long unsigned int buf_min;
	long unsigned int buf_max;
	bool top_down;
};

struct umem_info {
	u64 *buf;
	u32 size;
	u32 max_entries;
	u32 idx;
	unsigned int nr_ranges;
	const struct crash_mem_range *ranges;
};

struct kexec_elf_info {
	const char *buffer;
	const struct elf64_hdr *ehdr;
	const struct elf64_phdr *proghdrs;
};

typedef long unsigned int vm_flags_t;

struct clone_args {
	__u64 flags;
	__u64 pidfd;
	__u64 child_tid;
	__u64 parent_tid;
	__u64 exit_signal;
	__u64 stack;
	__u64 stack_size;
	__u64 tls;
	__u64 set_tid;
	__u64 set_tid_size;
	__u64 cgroup;
};

struct fdtable {
	unsigned int max_fds;
	struct file **fd;
	long unsigned int *close_on_exec;
	long unsigned int *open_fds;
	long unsigned int *full_fds_bits;
	struct callback_head rcu;
};

struct files_struct {
	atomic_t count;
	bool resize_in_progress;
	wait_queue_head_t resize_wait;
	struct fdtable *fdt;
	struct fdtable fdtab;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	spinlock_t file_lock;
	unsigned int next_fd;
	long unsigned int close_on_exec_init[1];
	long unsigned int open_fds_init[1];
	long unsigned int full_fds_bits_init[1];
	struct file *fd_array[64];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct robust_list {
	struct robust_list *next;
};

struct robust_list_head {
	struct robust_list list;
	long int futex_offset;
	struct robust_list *list_op_pending;
};

struct kernel_clone_args {
	u64 flags;
	int *pidfd;
	int *child_tid;
	int *parent_tid;
	int exit_signal;
	long unsigned int stack;
	long unsigned int stack_size;
	long unsigned int tls;
	pid_t *set_tid;
	size_t set_tid_size;
	int cgroup;
	int io_thread;
	int kthread;
	struct cgroup *cgrp;
	struct css_set *cset;
};

struct multiprocess_signals {
	sigset_t signal;
	struct hlist_node node;
};

typedef int (*proc_visitor)(struct task_struct *, void *);

enum {
	FUTEX_STATE_OK = 0,
	FUTEX_STATE_EXITING = 1,
	FUTEX_STATE_DEAD = 2,
};

enum proc_hidepid {
	HIDEPID_OFF = 0,
	HIDEPID_NO_ACCESS = 1,
	HIDEPID_INVISIBLE = 2,
	HIDEPID_NOT_PTRACEABLE = 4,
};

enum proc_pidonly {
	PROC_PIDONLY_OFF = 0,
	PROC_PIDONLY_ON = 1,
};

struct proc_fs_info {
	struct pid_namespace *pid_ns;
	struct dentry *proc_self;
	struct dentry *proc_thread_self;
	kgid_t pid_gid;
	enum proc_hidepid hide_pid;
	enum proc_pidonly pidonly;
};

enum bpf_type_flag {
	PTR_MAYBE_NULL = 256,
	MEM_RDONLY = 512,
	MEM_ALLOC = 1024,
	__BPF_TYPE_LAST_FLAG = 1024,
};

enum bpf_arg_type {
	ARG_DONTCARE = 0,
	ARG_CONST_MAP_PTR = 1,
	ARG_PTR_TO_MAP_KEY = 2,
	ARG_PTR_TO_MAP_VALUE = 3,
	ARG_PTR_TO_UNINIT_MAP_VALUE = 4,
	ARG_PTR_TO_MEM = 5,
	ARG_PTR_TO_UNINIT_MEM = 6,
	ARG_CONST_SIZE = 7,
	ARG_CONST_SIZE_OR_ZERO = 8,
	ARG_PTR_TO_CTX = 9,
	ARG_ANYTHING = 10,
	ARG_PTR_TO_SPIN_LOCK = 11,
	ARG_PTR_TO_SOCK_COMMON = 12,
	ARG_PTR_TO_INT = 13,
	ARG_PTR_TO_LONG = 14,
	ARG_PTR_TO_SOCKET = 15,
	ARG_PTR_TO_BTF_ID = 16,
	ARG_PTR_TO_ALLOC_MEM = 17,
	ARG_CONST_ALLOC_SIZE_OR_ZERO = 18,
	ARG_PTR_TO_BTF_ID_SOCK_COMMON = 19,
	ARG_PTR_TO_PERCPU_BTF_ID = 20,
	ARG_PTR_TO_FUNC = 21,
	ARG_PTR_TO_STACK = 22,
	ARG_PTR_TO_CONST_STR = 23,
	ARG_PTR_TO_TIMER = 24,
	__BPF_ARG_TYPE_MAX = 25,
	ARG_PTR_TO_MAP_VALUE_OR_NULL = 259,
	ARG_PTR_TO_MEM_OR_NULL = 261,
	ARG_PTR_TO_CTX_OR_NULL = 265,
	ARG_PTR_TO_SOCKET_OR_NULL = 271,
	ARG_PTR_TO_ALLOC_MEM_OR_NULL = 273,
	ARG_PTR_TO_STACK_OR_NULL = 278,
	__BPF_ARG_TYPE_LIMIT = 2047,
};

enum bpf_return_type {
	RET_INTEGER = 0,
	RET_VOID = 1,
	RET_PTR_TO_MAP_VALUE = 2,
	RET_PTR_TO_SOCKET = 3,
	RET_PTR_TO_TCP_SOCK = 4,
	RET_PTR_TO_SOCK_COMMON = 5,
	RET_PTR_TO_ALLOC_MEM = 6,
	RET_PTR_TO_MEM_OR_BTF_ID = 7,
	RET_PTR_TO_BTF_ID = 8,
	__BPF_RET_TYPE_MAX = 9,
	RET_PTR_TO_MAP_VALUE_OR_NULL = 258,
	RET_PTR_TO_SOCKET_OR_NULL = 259,
	RET_PTR_TO_TCP_SOCK_OR_NULL = 260,
	RET_PTR_TO_SOCK_COMMON_OR_NULL = 261,
	RET_PTR_TO_ALLOC_MEM_OR_NULL = 1286,
	RET_PTR_TO_BTF_ID_OR_NULL = 264,
	__BPF_RET_TYPE_LIMIT = 2047,
};

enum bpf_cgroup_storage_type {
	BPF_CGROUP_STORAGE_SHARED = 0,
	BPF_CGROUP_STORAGE_PERCPU = 1,
	__BPF_CGROUP_STORAGE_MAX = 2,
};

enum bpf_tramp_prog_type {
	BPF_TRAMP_FENTRY = 0,
	BPF_TRAMP_FEXIT = 1,
	BPF_TRAMP_MODIFY_RETURN = 2,
	BPF_TRAMP_MAX = 3,
	BPF_TRAMP_REPLACE = 4,
};

struct trace_event_raw_task_newtask {
	struct trace_entry ent;
	pid_t pid;
	char comm[16];
	long unsigned int clone_flags;
	short int oom_score_adj;
	char __data[0];
};

struct trace_event_raw_task_rename {
	struct trace_entry ent;
	pid_t pid;
	char oldcomm[16];
	char newcomm[16];
	short int oom_score_adj;
	char __data[0];
};

struct trace_event_data_offsets_task_newtask {};

struct trace_event_data_offsets_task_rename {};

typedef void (*btf_trace_task_newtask)(void *, struct task_struct *, long unsigned int);

typedef void (*btf_trace_task_rename)(void *, struct task_struct *, const char *);

struct taint_flag {
	char c_true;
	char c_false;
	bool module;
};

enum reboot_mode {
	REBOOT_UNDEFINED = 4294967295,
	REBOOT_COLD = 0,
	REBOOT_WARM = 1,
	REBOOT_HARD = 2,
	REBOOT_SOFT = 3,
	REBOOT_GPIO = 4,
};

struct warn_args {
	const char *fmt;
	va_list args;
};

enum hk_type {
	HK_TYPE_TIMER = 0,
	HK_TYPE_RCU = 1,
	HK_TYPE_MISC = 2,
	HK_TYPE_SCHED = 3,
	HK_TYPE_TICK = 4,
	HK_TYPE_DOMAIN = 5,
	HK_TYPE_WQ = 6,
	HK_TYPE_MANAGED_IRQ = 7,
	HK_TYPE_KTHREAD = 8,
	HK_TYPE_MAX = 9,
};

enum cpuhp_smt_control {
	CPU_SMT_ENABLED = 0,
	CPU_SMT_DISABLED = 1,
	CPU_SMT_FORCE_DISABLED = 2,
	CPU_SMT_NOT_SUPPORTED = 3,
	CPU_SMT_NOT_IMPLEMENTED = 4,
};

struct smp_hotplug_thread {
	struct task_struct **store;
	struct list_head list;
	int (*thread_should_run)(unsigned int);
	void (*thread_fn)(unsigned int);
	void (*create)(unsigned int);
	void (*setup)(unsigned int);
	void (*cleanup)(unsigned int, bool);
	void (*park)(unsigned int);
	void (*unpark)(unsigned int);
	bool selfparking;
	const char *thread_comm;
};

struct trace_event_raw_cpuhp_enter {
	struct trace_entry ent;
	unsigned int cpu;
	int target;
	int idx;
	void *fun;
	char __data[0];
};

struct trace_event_raw_cpuhp_multi_enter {
	struct trace_entry ent;
	unsigned int cpu;
	int target;
	int idx;
	void *fun;
	char __data[0];
};

struct trace_event_raw_cpuhp_exit {
	struct trace_entry ent;
	unsigned int cpu;
	int state;
	int idx;
	int ret;
	char __data[0];
};

struct trace_event_data_offsets_cpuhp_enter {};

struct trace_event_data_offsets_cpuhp_multi_enter {};

struct trace_event_data_offsets_cpuhp_exit {};

typedef void (*btf_trace_cpuhp_enter)(void *, unsigned int, int, int, int (*)(unsigned int));

typedef void (*btf_trace_cpuhp_multi_enter)(void *, unsigned int, int, int, int (*)(unsigned int, struct hlist_node *), struct hlist_node *);

typedef void (*btf_trace_cpuhp_exit)(void *, unsigned int, int, int, int);

struct cpuhp_cpu_state {
	enum cpuhp_state state;
	enum cpuhp_state target;
	enum cpuhp_state fail;
	struct task_struct *thread;
	bool should_run;
	bool rollback;
	bool single;
	bool bringup;
	int cpu;
	struct hlist_node *node;
	struct hlist_node *last;
	enum cpuhp_state cb_state;
	int result;
	struct completion done_up;
	struct completion done_down;
};

struct cpuhp_step {
	const char *name;
	union {
		int (*single)(unsigned int);
		int (*multi)(unsigned int, struct hlist_node *);
	} startup;
	union {
		int (*single)(unsigned int);
		int (*multi)(unsigned int, struct hlist_node *);
	} teardown;
	struct hlist_head list;
	bool cant_stop;
	bool multi_instance;
};

enum cpu_mitigations {
	CPU_MITIGATIONS_OFF = 0,
	CPU_MITIGATIONS_AUTO = 1,
	CPU_MITIGATIONS_AUTO_NOSMT = 2,
};

struct rusage {
	struct __kernel_old_timeval ru_utime;
	struct __kernel_old_timeval ru_stime;
	__kernel_long_t ru_maxrss;
	__kernel_long_t ru_ixrss;
	__kernel_long_t ru_idrss;
	__kernel_long_t ru_isrss;
	__kernel_long_t ru_minflt;
	__kernel_long_t ru_majflt;
	__kernel_long_t ru_nswap;
	__kernel_long_t ru_inblock;
	__kernel_long_t ru_oublock;
	__kernel_long_t ru_msgsnd;
	__kernel_long_t ru_msgrcv;
	__kernel_long_t ru_nsignals;
	__kernel_long_t ru_nvcsw;
	__kernel_long_t ru_nivcsw;
};

struct waitid_info {
	pid_t pid;
	uid_t uid;
	int status;
	int cause;
};

struct wait_opts {
	enum pid_type wo_type;
	int wo_flags;
	struct pid *wo_pid;
	struct waitid_info *wo_info;
	int wo_stat;
	struct rusage *wo_rusage;
	wait_queue_entry_t child_wait;
	int notask_error;
};

struct trace_print_flags {
	long unsigned int mask;
	const char *name;
};

struct wait_bit_key {
	void *flags;
	int bit_nr;
	long unsigned int timeout;
};

struct wait_bit_queue_entry {
	struct wait_bit_key key;
	struct wait_queue_entry wq_entry;
};

struct softirq_action {
	void (*action)(struct softirq_action *);
};

struct tasklet_struct {
	struct tasklet_struct *next;
	long unsigned int state;
	atomic_t count;
	bool use_callback;
	union {
		void (*func)(long unsigned int);
		void (*callback)(struct tasklet_struct *);
	};
	long unsigned int data;
};

enum {
	TASKLET_STATE_SCHED = 0,
	TASKLET_STATE_RUN = 1,
};

struct kernel_stat {
	long unsigned int irqs_sum;
	unsigned int softirqs[10];
};

struct trace_event_raw_irq_handler_entry {
	struct trace_entry ent;
	int irq;
	u32 __data_loc_name;
	char __data[0];
};

struct trace_event_raw_irq_handler_exit {
	struct trace_entry ent;
	int irq;
	int ret;
	char __data[0];
};

struct trace_event_raw_softirq {
	struct trace_entry ent;
	unsigned int vec;
	char __data[0];
};

struct trace_event_data_offsets_irq_handler_entry {
	u32 name;
};

struct trace_event_data_offsets_irq_handler_exit {};

struct trace_event_data_offsets_softirq {};

typedef void (*btf_trace_irq_handler_entry)(void *, int, struct irqaction *);

typedef void (*btf_trace_irq_handler_exit)(void *, int, struct irqaction *, int);

typedef void (*btf_trace_softirq_entry)(void *, unsigned int);

typedef void (*btf_trace_softirq_exit)(void *, unsigned int);

typedef void (*btf_trace_softirq_raise)(void *, unsigned int);

struct tasklet_head {
	struct tasklet_struct *head;
	struct tasklet_struct **tail;
};

enum {
	IORES_DESC_NONE = 0,
	IORES_DESC_CRASH_KERNEL = 1,
	IORES_DESC_ACPI_TABLES = 2,
	IORES_DESC_ACPI_NV_STORAGE = 3,
	IORES_DESC_PERSISTENT_MEMORY = 4,
	IORES_DESC_PERSISTENT_MEMORY_LEGACY = 5,
	IORES_DESC_DEVICE_PRIVATE_MEMORY = 6,
	IORES_DESC_RESERVED = 7,
	IORES_DESC_SOFT_RESERVED = 8,
};

enum {
	REGION_INTERSECTS = 0,
	REGION_DISJOINT = 1,
	REGION_MIXED = 2,
};

typedef void (*dr_release_t)(struct device *, void *);

typedef int (*dr_match_t)(struct device *, void *, void *);

struct resource_entry {
	struct list_head node;
	struct resource *res;
	resource_size_t offset;
	struct resource __res;
};

struct resource_constraint {
	resource_size_t min;
	resource_size_t max;
	resource_size_t align;
	resource_size_t (*alignf)(void *, const struct resource *, resource_size_t, resource_size_t);
	void *alignf_data;
};

enum {
	MAX_IORES_LEVEL = 5,
};

struct region_devres {
	struct resource *parent;
	resource_size_t start;
	resource_size_t n;
};

typedef __kernel_clock_t clock_t;

struct dentry_stat_t {
	long int nr_dentry;
	long int nr_unused;
	long int age_limit;
	long int want_pages;
	long int nr_negative;
	long int dummy;
};

struct files_stat_struct {
	long unsigned int nr_files;
	long unsigned int nr_free_files;
	long unsigned int max_files;
};

struct inodes_stat_t {
	long int nr_inodes;
	long int nr_unused;
	long int dummy[5];
};

struct sk_filter {
	refcount_t refcnt;
	struct callback_head rcu;
	struct bpf_prog *prog;
};

enum sysctl_writes_mode {
	SYSCTL_WRITES_LEGACY = 4294967295,
	SYSCTL_WRITES_WARN = 0,
	SYSCTL_WRITES_STRICT = 1,
};

struct do_proc_dointvec_minmax_conv_param {
	int *min;
	int *max;
};

struct do_proc_douintvec_minmax_conv_param {
	unsigned int *min;
	unsigned int *max;
};

struct __user_cap_header_struct {
	__u32 version;
	int pid;
};

typedef struct __user_cap_header_struct *cap_user_header_t;

struct __user_cap_data_struct {
	__u32 effective;
	__u32 permitted;
	__u32 inheritable;
};

typedef struct __user_cap_data_struct *cap_user_data_t;

struct sigqueue {
	struct list_head list;
	int flags;
	kernel_siginfo_t info;
	struct ucounts *ucounts;
};

typedef int wait_bit_action_f(struct wait_bit_key *, int);

struct ptrace_peeksiginfo_args {
	__u64 off;
	__u32 flags;
	__s32 nr;
};

struct ptrace_syscall_info {
	__u8 op;
	__u8 pad[3];
	__u32 arch;
	__u64 instruction_pointer;
	__u64 stack_pointer;
	union {
		struct {
			__u64 nr;
			__u64 args[6];
		} entry;
		struct {
			__s64 rval;
			__u8 is_error;
		} exit;
		struct {
			__u64 nr;
			__u64 args[6];
			__u32 ret_data;
		} seccomp;
	};
};

struct ptrace_rseq_configuration {
	__u64 rseq_abi_pointer;
	__u32 rseq_abi_size;
	__u32 signature;
	__u32 flags;
	__u32 pad;
};

typedef long unsigned int old_sigset_t;

enum siginfo_layout {
	SIL_KILL = 0,
	SIL_TIMER = 1,
	SIL_POLL = 2,
	SIL_FAULT = 3,
	SIL_FAULT_TRAPNO = 4,
	SIL_FAULT_MCEERR = 5,
	SIL_FAULT_BNDERR = 6,
	SIL_FAULT_PKUERR = 7,
	SIL_PERF_EVENT = 8,
	SIL_CHLD = 9,
	SIL_RT = 10,
	SIL_SYS = 11,
};

struct fd {
	struct file *file;
	unsigned int flags;
};

enum {
	TRACE_SIGNAL_DELIVERED = 0,
	TRACE_SIGNAL_IGNORED = 1,
	TRACE_SIGNAL_ALREADY_PENDING = 2,
	TRACE_SIGNAL_OVERFLOW_FAIL = 3,
	TRACE_SIGNAL_LOSE_INFO = 4,
};

struct trace_event_raw_signal_generate {
	struct trace_entry ent;
	int sig;
	int errno;
	int code;
	char comm[16];
	pid_t pid;
	int group;
	int result;
	char __data[0];
};

struct trace_event_raw_signal_deliver {
	struct trace_entry ent;
	int sig;
	int errno;
	int code;
	long unsigned int sa_handler;
	long unsigned int sa_flags;
	char __data[0];
};

struct trace_event_data_offsets_signal_generate {};

struct trace_event_data_offsets_signal_deliver {};

typedef void (*btf_trace_signal_generate)(void *, int, struct kernel_siginfo *, struct task_struct *, int, int);

typedef void (*btf_trace_signal_deliver)(void *, int, struct kernel_siginfo *, struct k_sigaction *);

enum sig_handler {
	HANDLER_CURRENT = 0,
	HANDLER_SIG_DFL = 1,
	HANDLER_EXIT = 2,
};

struct sysinfo {
	__kernel_long_t uptime;
	__kernel_ulong_t loads[3];
	__kernel_ulong_t totalram;
	__kernel_ulong_t freeram;
	__kernel_ulong_t sharedram;
	__kernel_ulong_t bufferram;
	__kernel_ulong_t totalswap;
	__kernel_ulong_t freeswap;
	__u16 procs;
	__u16 pad;
	__kernel_ulong_t totalhigh;
	__kernel_ulong_t freehigh;
	__u32 mem_unit;
	char _f[0];
};

struct rlimit64 {
	__u64 rlim_cur;
	__u64 rlim_max;
};

struct oldold_utsname {
	char sysname[9];
	char nodename[9];
	char release[9];
	char version[9];
	char machine[9];
};

struct old_utsname {
	char sysname[65];
	char nodename[65];
	char release[65];
	char version[65];
	char machine[65];
};

enum uts_proc {
	UTS_PROC_OSTYPE = 0,
	UTS_PROC_OSRELEASE = 1,
	UTS_PROC_VERSION = 2,
	UTS_PROC_HOSTNAME = 3,
	UTS_PROC_DOMAINNAME = 4,
};

struct prctl_mm_map {
	__u64 start_code;
	__u64 end_code;
	__u64 start_data;
	__u64 end_data;
	__u64 start_brk;
	__u64 brk;
	__u64 start_stack;
	__u64 arg_start;
	__u64 arg_end;
	__u64 env_start;
	__u64 env_end;
	__u64 *auxv;
	__u32 auxv_size;
	__u32 exe_fd;
};

struct tms {
	__kernel_clock_t tms_utime;
	__kernel_clock_t tms_stime;
	__kernel_clock_t tms_cutime;
	__kernel_clock_t tms_cstime;
};

struct getcpu_cache {
	long unsigned int blob[16];
};

struct wq_flusher;

struct worker;

struct workqueue_attrs;

struct pool_workqueue;

struct wq_device;

struct workqueue_struct {
	struct list_head pwqs;
	struct list_head list;
	struct mutex mutex;
	int work_color;
	int flush_color;
	atomic_t nr_pwqs_to_flush;
	struct wq_flusher *first_flusher;
	struct list_head flusher_queue;
	struct list_head flusher_overflow;
	struct list_head maydays;
	struct worker *rescuer;
	int nr_drainers;
	int saved_max_active;
	struct workqueue_attrs *unbound_attrs;
	struct pool_workqueue *dfl_pwq;
	struct wq_device *wq_dev;
	char name[24];
	struct callback_head rcu;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	unsigned int flags;
	struct pool_workqueue *cpu_pwqs;
	struct pool_workqueue *numa_pwq_tbl[0];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct workqueue_attrs {
	int nice;
	cpumask_var_t cpumask;
	bool no_numa;
};

struct execute_work {
	struct work_struct work;
};

struct __una_u32 {
	u32 x;
};

struct worker_pool;

struct worker {
	union {
		struct list_head entry;
		struct hlist_node hentry;
	};
	struct work_struct *current_work;
	work_func_t current_func;
	struct pool_workqueue *current_pwq;
	unsigned int current_color;
	struct list_head scheduled;
	struct task_struct *task;
	struct worker_pool *pool;
	struct list_head node;
	long unsigned int last_active;
	unsigned int flags;
	int id;
	int sleeping;
	char desc[24];
	struct workqueue_struct *rescue_wq;
	work_func_t last_func;
};

struct pool_workqueue {
	struct worker_pool *pool;
	struct workqueue_struct *wq;
	int work_color;
	int flush_color;
	int refcnt;
	int nr_in_flight[16];
	int nr_active;
	int max_active;
	struct list_head inactive_works;
	struct list_head pwqs_node;
	struct list_head mayday_node;
	struct work_struct unbound_release_work;
	struct callback_head rcu;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct worker_pool {
	raw_spinlock_t lock;
	int cpu;
	int node;
	int id;
	unsigned int flags;
	long unsigned int watchdog_ts;
	struct list_head worklist;
	int nr_workers;
	int nr_idle;
	struct list_head idle_list;
	struct timer_list idle_timer;
	struct timer_list mayday_timer;
	struct hlist_head busy_hash[64];
	struct worker *manager;
	struct list_head workers;
	struct completion *detach_completion;
	struct ida worker_ida;
	struct workqueue_attrs *attrs;
	struct hlist_node hash_node;
	int refcnt;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	atomic_t nr_running;
	struct callback_head rcu;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

enum {
	POOL_MANAGER_ACTIVE = 1,
	POOL_DISASSOCIATED = 4,
	WORKER_DIE = 2,
	WORKER_IDLE = 4,
	WORKER_PREP = 8,
	WORKER_CPU_INTENSIVE = 64,
	WORKER_UNBOUND = 128,
	WORKER_REBOUND = 256,
	WORKER_NOT_RUNNING = 456,
	NR_STD_WORKER_POOLS = 2,
	UNBOUND_POOL_HASH_ORDER = 6,
	BUSY_WORKER_HASH_ORDER = 6,
	MAX_IDLE_WORKERS_RATIO = 4,
	IDLE_WORKER_TIMEOUT = 30000,
	MAYDAY_INITIAL_TIMEOUT = 2,
	MAYDAY_INTERVAL = 10,
	CREATE_COOLDOWN = 100,
	RESCUER_NICE_LEVEL = 4294967276,
	HIGHPRI_NICE_LEVEL = 4294967276,
	WQ_NAME_LEN = 24,
};

struct wq_flusher {
	struct list_head list;
	int flush_color;
	struct completion done;
};

struct wq_device {
	struct workqueue_struct *wq;
	struct device dev;
};

struct trace_event_raw_workqueue_queue_work {
	struct trace_entry ent;
	void *work;
	void *function;
	u32 __data_loc_workqueue;
	unsigned int req_cpu;
	unsigned int cpu;
	char __data[0];
};

struct trace_event_raw_workqueue_activate_work {
	struct trace_entry ent;
	void *work;
	char __data[0];
};

struct trace_event_raw_workqueue_execute_start {
	struct trace_entry ent;
	void *work;
	void *function;
	char __data[0];
};

struct trace_event_raw_workqueue_execute_end {
	struct trace_entry ent;
	void *work;
	void *function;
	char __data[0];
};

struct trace_event_data_offsets_workqueue_queue_work {
	u32 workqueue;
};

struct trace_event_data_offsets_workqueue_activate_work {};

struct trace_event_data_offsets_workqueue_execute_start {};

struct trace_event_data_offsets_workqueue_execute_end {};

typedef void (*btf_trace_workqueue_queue_work)(void *, unsigned int, struct pool_workqueue *, struct work_struct *);

typedef void (*btf_trace_workqueue_activate_work)(void *, struct work_struct *);

typedef void (*btf_trace_workqueue_execute_start)(void *, struct work_struct *);

typedef void (*btf_trace_workqueue_execute_end)(void *, struct work_struct *, work_func_t);

struct wq_barrier {
	struct work_struct work;
	struct completion done;
	struct task_struct *task;
};

struct cwt_wait {
	wait_queue_entry_t wait;
	struct work_struct *work;
};

struct apply_wqattrs_ctx {
	struct workqueue_struct *wq;
	struct workqueue_attrs *attrs;
	struct list_head list;
	struct pool_workqueue *dfl_pwq;
	struct pool_workqueue *pwq_tbl[0];
};

struct work_for_cpu {
	struct work_struct work;
	long int (*fn)(void *);
	void *arg;
	long int ret;
};

typedef struct {} local_lock_t;

typedef void (*task_work_func_t)(struct callback_head *);

enum task_work_notify_mode {
	TWA_NONE = 0,
	TWA_RESUME = 1,
	TWA_SIGNAL = 2,
};

enum {
	KERNEL_PARAM_OPS_FL_NOARG = 1,
};

enum {
	KERNEL_PARAM_FL_UNSAFE = 1,
	KERNEL_PARAM_FL_HWPARAM = 2,
};

struct param_attribute {
	struct module_attribute mattr;
	const struct kernel_param *param;
};

struct module_param_attrs {
	unsigned int num;
	struct attribute_group grp;
	struct param_attribute attrs[0];
};

struct kmalloced_param {
	struct list_head list;
	char val[0];
};

struct sched_param {
	int sched_priority;
};

enum {
	__PERCPU_REF_ATOMIC = 1,
	__PERCPU_REF_DEAD = 2,
	__PERCPU_REF_ATOMIC_DEAD = 3,
	__PERCPU_REF_FLAG_BITS = 2,
};

struct kthread_work;

typedef void (*kthread_work_func_t)(struct kthread_work *);

struct kthread_worker;

struct kthread_work {
	struct list_head node;
	kthread_work_func_t func;
	struct kthread_worker *worker;
	int canceling;
};

enum {
	KTW_FREEZABLE = 1,
};

struct kthread_worker {
	unsigned int flags;
	raw_spinlock_t lock;
	struct list_head work_list;
	struct list_head delayed_work_list;
	struct task_struct *task;
	struct kthread_work *current_work;
};

struct kthread_delayed_work {
	struct kthread_work work;
	struct timer_list timer;
};

enum {
	CSS_NO_REF = 1,
	CSS_ONLINE = 2,
	CSS_RELEASED = 4,
	CSS_VISIBLE = 8,
	CSS_DYING = 16,
};

struct kthread_create_info {
	int (*threadfn)(void *);
	void *data;
	int node;
	struct task_struct *result;
	struct completion *done;
	struct list_head list;
};

struct kthread {
	long unsigned int flags;
	unsigned int cpu;
	int result;
	int (*threadfn)(void *);
	void *data;
	struct completion parked;
	struct completion exited;
	struct cgroup_subsys_state *blkcg_css;
};

enum KTHREAD_BITS {
	KTHREAD_IS_PER_CPU = 0,
	KTHREAD_SHOULD_STOP = 1,
	KTHREAD_SHOULD_PARK = 2,
};

struct kthread_flush_work {
	struct kthread_work work;
	struct completion done;
};

struct ipc_ids {
	int in_use;
	short unsigned int seq;
	struct rw_semaphore rwsem;
	struct idr ipcs_idr;
	int max_idx;
	int last_idx;
	int next_id;
	struct rhashtable key_ht;
};

struct ipc_namespace {
	struct ipc_ids ids[3];
	int sem_ctls[4];
	int used_sems;
	unsigned int msg_ctlmax;
	unsigned int msg_ctlmnb;
	unsigned int msg_ctlmni;
	atomic_t msg_bytes;
	atomic_t msg_hdrs;
	size_t shm_ctlmax;
	size_t shm_ctlall;
	long unsigned int shm_tot;
	int shm_ctlmni;
	int shm_rmid_forced;
	struct notifier_block ipcns_nb;
	struct vfsmount *mq_mnt;
	unsigned int mq_queues_count;
	unsigned int mq_queues_max;
	unsigned int mq_msg_max;
	unsigned int mq_msgsize_max;
	unsigned int mq_msg_default;
	unsigned int mq_msgsize_default;
	struct user_namespace *user_ns;
	struct ucounts *ucounts;
	struct llist_node mnt_llist;
	struct ns_common ns;
};

struct srcu_notifier_head {
	struct mutex mutex;
	struct srcu_struct srcu;
	struct notifier_block *head;
};

enum what {
	PROC_EVENT_NONE = 0,
	PROC_EVENT_FORK = 1,
	PROC_EVENT_EXEC = 2,
	PROC_EVENT_UID = 4,
	PROC_EVENT_GID = 64,
	PROC_EVENT_SID = 128,
	PROC_EVENT_PTRACE = 256,
	PROC_EVENT_COMM = 512,
	PROC_EVENT_COREDUMP = 1073741824,
	PROC_EVENT_EXIT = 2147483648,
};

enum reboot_type {
	BOOT_TRIPLE = 116,
	BOOT_KBD = 107,
	BOOT_BIOS = 98,
	BOOT_ACPI = 97,
	BOOT_EFI = 101,
	BOOT_CF9_FORCE = 112,
	BOOT_CF9_SAFE = 113,
};

struct async_entry {
	struct list_head domain_list;
	struct list_head global_list;
	struct work_struct work;
	async_cookie_t cookie;
	async_func_t func;
	void *data;
	struct async_domain *domain;
};

struct smpboot_thread_data {
	unsigned int cpu;
	unsigned int status;
	struct smp_hotplug_thread *ht;
};

enum {
	HP_THREAD_NONE = 0,
	HP_THREAD_ACTIVE = 1,
	HP_THREAD_PARKED = 2,
};

struct pin_cookie {};

enum {
	CSD_FLAG_LOCK = 1,
	IRQ_WORK_PENDING = 1,
	IRQ_WORK_BUSY = 2,
	IRQ_WORK_LAZY = 4,
	IRQ_WORK_HARD_IRQ = 8,
	IRQ_WORK_CLAIMED = 3,
	CSD_TYPE_ASYNC = 0,
	CSD_TYPE_SYNC = 16,
	CSD_TYPE_IRQ_WORK = 32,
	CSD_TYPE_TTWU = 48,
	CSD_FLAG_TYPE_MASK = 240,
};

struct __call_single_data {
	struct __call_single_node node;
	smp_call_func_t func;
	void *info;
};

typedef struct __call_single_data call_single_data_t;

typedef int (*task_call_f)(struct task_struct *, void *);

struct dl_bw {
	raw_spinlock_t lock;
	u64 bw;
	u64 total_bw;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

struct cpudl_item;

struct cpudl {
	raw_spinlock_t lock;
	int size;
	cpumask_var_t free_cpus;
	struct cpudl_item *elements;
};

struct cpupri_vec {
	atomic_t count;
	cpumask_var_t mask;
};

struct cpupri {
	struct cpupri_vec pri_to_cpu[101];
	int *cpu_to_pri;
};

struct perf_domain;

struct root_domain {
	atomic_t refcount;
	atomic_t rto_count;
	struct callback_head rcu;
	cpumask_var_t span;
	cpumask_var_t online;
	int overload;
	int overutilized;
	cpumask_var_t dlo_mask;
	atomic_t dlo_count;
	struct dl_bw dl_bw;
	struct cpudl cpudl;
	u64 visit_gen;
	struct irq_work rto_push_work;
	raw_spinlock_t rto_lock;
	int rto_loop;
	int rto_cpu;
	atomic_t rto_loop_next;
	atomic_t rto_loop_start;
	cpumask_var_t rto_mask;
	struct cpupri cpupri;
	long unsigned int max_cpu_capacity;
	struct perf_domain *pd;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
};

struct cfs_rq {
	struct load_weight load;
	unsigned int nr_running;
	unsigned int h_nr_running;
	unsigned int idle_nr_running;
	unsigned int idle_h_nr_running;
	u64 exec_clock;
	u64 min_vruntime;
	unsigned int forceidle_seq;
	u64 min_vruntime_fi;
	struct rb_root_cached tasks_timeline;
	struct sched_entity *curr;
	struct sched_entity *next;
	struct sched_entity *last;
	struct sched_entity *skip;
	unsigned int nr_spread_over;
	long: 32;
	long: 64;
	struct sched_avg avg;
	struct {
		raw_spinlock_t lock;
		int nr;
		long unsigned int load_avg;
		long unsigned int util_avg;
		long unsigned int runnable_avg;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
	} removed;
	long unsigned int tg_load_avg_contrib;
	long int propagate;
	long int prop_runnable_sum;
	long unsigned int h_load;
	u64 last_h_load_update;
	struct sched_entity *h_load_next;
	struct rq *rq;
	int on_list;
	struct list_head leaf_cfs_rq_list;
	struct task_group *tg;
	int idle;
	int runtime_enabled;
	s64 runtime_remaining;
	u64 throttled_clock;
	u64 throttled_clock_task;
	u64 throttled_clock_task_time;
	int throttled;
	int throttle_count;
	struct list_head throttled_list;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct cfs_bandwidth {
	raw_spinlock_t lock;
	ktime_t period;
	u64 quota;
	u64 runtime;
	u64 burst;
	u64 runtime_snap;
	s64 hierarchical_quota;
	u8 idle;
	u8 period_active;
	u8 slack_started;
	struct hrtimer period_timer;
	struct hrtimer slack_timer;
	struct list_head throttled_cfs_rq;
	int nr_periods;
	int nr_throttled;
	int nr_burst;
	u64 throttled_time;
	u64 burst_time;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

struct task_group {
	struct cgroup_subsys_state css;
	struct sched_entity **se;
	struct cfs_rq **cfs_rq;
	long unsigned int shares;
	int idle;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	atomic_long_t load_avg;
	struct callback_head rcu;
	struct list_head list;
	struct task_group *parent;
	struct list_head siblings;
	struct list_head children;
	struct autogroup *autogroup;
	struct cfs_bandwidth cfs_bandwidth;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct autogroup {
	struct kref kref;
	struct task_group *tg;
	struct rw_semaphore lock;
	long unsigned int id;
	int nice;
};

struct sched_domain_attr {
	int relax_domain_level;
};

struct sched_group {
	struct sched_group *next;
	atomic_t ref;
	unsigned int group_weight;
	struct sched_group_capacity *sgc;
	int asym_prefer_cpu;
	int flags;
	long unsigned int cpumask[0];
};

struct sched_group_capacity {
	atomic_t ref;
	long unsigned int capacity;
	long unsigned int min_capacity;
	long unsigned int max_capacity;
	long unsigned int next_update;
	int imbalance;
	int id;
	long unsigned int cpumask[0];
};

enum {
	CFTYPE_ONLY_ON_ROOT = 1,
	CFTYPE_NOT_ON_ROOT = 2,
	CFTYPE_NS_DELEGATABLE = 4,
	CFTYPE_NO_PREFIX = 8,
	CFTYPE_WORLD_WRITABLE = 16,
	CFTYPE_DEBUG = 32,
	CFTYPE_PRESSURE = 64,
	__CFTYPE_ONLY_ON_DFL = 65536,
	__CFTYPE_NOT_ON_DFL = 131072,
};

struct wake_q_head {
	struct wake_q_node *first;
	struct wake_q_node **lastp;
};

struct sched_attr {
	__u32 size;
	__u32 sched_policy;
	__u64 sched_flags;
	__s32 sched_nice;
	__u32 sched_priority;
	__u64 sched_runtime;
	__u64 sched_deadline;
	__u64 sched_period;
	__u32 sched_util_min;
	__u32 sched_util_max;
};

struct trace_event_raw_sched_kthread_stop {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	char __data[0];
};

struct trace_event_raw_sched_kthread_stop_ret {
	struct trace_entry ent;
	int ret;
	char __data[0];
};

struct trace_event_raw_sched_kthread_work_queue_work {
	struct trace_entry ent;
	void *work;
	void *function;
	void *worker;
	char __data[0];
};

struct trace_event_raw_sched_kthread_work_execute_start {
	struct trace_entry ent;
	void *work;
	void *function;
	char __data[0];
};

struct trace_event_raw_sched_kthread_work_execute_end {
	struct trace_entry ent;
	void *work;
	void *function;
	char __data[0];
};

struct trace_event_raw_sched_wakeup_template {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	int prio;
	int target_cpu;
	char __data[0];
};

struct trace_event_raw_sched_switch {
	struct trace_entry ent;
	char prev_comm[16];
	pid_t prev_pid;
	int prev_prio;
	long int prev_state;
	char next_comm[16];
	pid_t next_pid;
	int next_prio;
	char __data[0];
};

struct trace_event_raw_sched_migrate_task {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	int prio;
	int orig_cpu;
	int dest_cpu;
	char __data[0];
};

struct trace_event_raw_sched_process_template {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	int prio;
	char __data[0];
};

struct trace_event_raw_sched_process_wait {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	int prio;
	char __data[0];
};

struct trace_event_raw_sched_process_fork {
	struct trace_entry ent;
	char parent_comm[16];
	pid_t parent_pid;
	char child_comm[16];
	pid_t child_pid;
	char __data[0];
};

struct trace_event_raw_sched_process_exec {
	struct trace_entry ent;
	u32 __data_loc_filename;
	pid_t pid;
	pid_t old_pid;
	char __data[0];
};

struct trace_event_raw_sched_stat_template {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	u64 delay;
	char __data[0];
};

struct trace_event_raw_sched_stat_runtime {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	u64 runtime;
	u64 vruntime;
	char __data[0];
};

struct trace_event_raw_sched_pi_setprio {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	int oldprio;
	int newprio;
	char __data[0];
};

struct trace_event_raw_sched_process_hang {
	struct trace_entry ent;
	char comm[16];
	pid_t pid;
	char __data[0];
};

struct trace_event_raw_sched_move_numa {
	struct trace_entry ent;
	pid_t pid;
	pid_t tgid;
	pid_t ngid;
	int src_cpu;
	int src_nid;
	int dst_cpu;
	int dst_nid;
	char __data[0];
};

struct trace_event_raw_sched_numa_pair_template {
	struct trace_entry ent;
	pid_t src_pid;
	pid_t src_tgid;
	pid_t src_ngid;
	int src_cpu;
	int src_nid;
	pid_t dst_pid;
	pid_t dst_tgid;
	pid_t dst_ngid;
	int dst_cpu;
	int dst_nid;
	char __data[0];
};

struct trace_event_raw_sched_wake_idle_without_ipi {
	struct trace_entry ent;
	int cpu;
	char __data[0];
};

struct trace_event_data_offsets_sched_kthread_stop {};

struct trace_event_data_offsets_sched_kthread_stop_ret {};

struct trace_event_data_offsets_sched_kthread_work_queue_work {};

struct trace_event_data_offsets_sched_kthread_work_execute_start {};

struct trace_event_data_offsets_sched_kthread_work_execute_end {};

struct trace_event_data_offsets_sched_wakeup_template {};

struct trace_event_data_offsets_sched_switch {};

struct trace_event_data_offsets_sched_migrate_task {};

struct trace_event_data_offsets_sched_process_template {};

struct trace_event_data_offsets_sched_process_wait {};

struct trace_event_data_offsets_sched_process_fork {};

struct trace_event_data_offsets_sched_process_exec {
	u32 filename;
};

struct trace_event_data_offsets_sched_stat_template {};

struct trace_event_data_offsets_sched_stat_runtime {};

struct trace_event_data_offsets_sched_pi_setprio {};

struct trace_event_data_offsets_sched_process_hang {};

struct trace_event_data_offsets_sched_move_numa {};

struct trace_event_data_offsets_sched_numa_pair_template {};

struct trace_event_data_offsets_sched_wake_idle_without_ipi {};

typedef void (*btf_trace_sched_kthread_stop)(void *, struct task_struct *);

typedef void (*btf_trace_sched_kthread_stop_ret)(void *, int);

typedef void (*btf_trace_sched_kthread_work_queue_work)(void *, struct kthread_worker *, struct kthread_work *);

typedef void (*btf_trace_sched_kthread_work_execute_start)(void *, struct kthread_work *);

typedef void (*btf_trace_sched_kthread_work_execute_end)(void *, struct kthread_work *, kthread_work_func_t);

typedef void (*btf_trace_sched_waking)(void *, struct task_struct *);

typedef void (*btf_trace_sched_wakeup)(void *, struct task_struct *);

typedef void (*btf_trace_sched_wakeup_new)(void *, struct task_struct *);

typedef void (*btf_trace_sched_switch)(void *, bool, struct task_struct *, struct task_struct *, unsigned int);

typedef void (*btf_trace_sched_migrate_task)(void *, struct task_struct *, int);

typedef void (*btf_trace_sched_process_free)(void *, struct task_struct *);

typedef void (*btf_trace_sched_process_exit)(void *, struct task_struct *);

typedef void (*btf_trace_sched_wait_task)(void *, struct task_struct *);

typedef void (*btf_trace_sched_process_wait)(void *, struct pid *);

typedef void (*btf_trace_sched_process_fork)(void *, struct task_struct *, struct task_struct *);

typedef void (*btf_trace_sched_process_exec)(void *, struct task_struct *, pid_t, struct linux_binprm *);

typedef void (*btf_trace_sched_stat_wait)(void *, struct task_struct *, u64);

typedef void (*btf_trace_sched_stat_sleep)(void *, struct task_struct *, u64);

typedef void (*btf_trace_sched_stat_iowait)(void *, struct task_struct *, u64);

typedef void (*btf_trace_sched_stat_blocked)(void *, struct task_struct *, u64);

typedef void (*btf_trace_sched_stat_runtime)(void *, struct task_struct *, u64, u64);

typedef void (*btf_trace_sched_pi_setprio)(void *, struct task_struct *, struct task_struct *);

typedef void (*btf_trace_sched_process_hang)(void *, struct task_struct *);

typedef void (*btf_trace_sched_move_numa)(void *, struct task_struct *, int, int);

typedef void (*btf_trace_sched_stick_numa)(void *, struct task_struct *, int, struct task_struct *, int);

typedef void (*btf_trace_sched_swap_numa)(void *, struct task_struct *, int, struct task_struct *, int);

typedef void (*btf_trace_sched_wake_idle_without_ipi)(void *, int);

typedef void (*btf_trace_pelt_cfs_tp)(void *, struct cfs_rq *);

typedef void (*btf_trace_pelt_rt_tp)(void *, struct rq *);

struct rt_prio_array {
	long unsigned int bitmap[2];
	struct list_head queue[100];
};

struct rt_rq {
	struct rt_prio_array active;
	unsigned int rt_nr_running;
	unsigned int rr_nr_running;
	struct {
		int curr;
		int next;
	} highest_prio;
	unsigned int rt_nr_migratory;
	unsigned int rt_nr_total;
	int overloaded;
	struct plist_head pushable_tasks;
	int rt_queued;
	int rt_throttled;
	u64 rt_time;
	u64 rt_runtime;
	raw_spinlock_t rt_runtime_lock;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

struct dl_rq {
	struct rb_root_cached root;
	unsigned int dl_nr_running;
	struct {
		u64 curr;
		u64 next;
	} earliest_dl;
	unsigned int dl_nr_migratory;
	int overloaded;
	struct rb_root_cached pushable_dl_tasks_root;
	u64 running_bw;
	u64 this_bw;
	u64 extra_bw;
	u64 bw_ratio;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

struct cpu_stop_done;

struct cpu_stop_work {
	struct list_head list;
	cpu_stop_fn_t fn;
	long unsigned int caller;
	void *arg;
	struct cpu_stop_done *done;
};

struct cpuidle_state;

struct rq {
	raw_spinlock_t __lock;
	unsigned int nr_running;
	unsigned int nr_numa_running;
	unsigned int nr_preferred_running;
	unsigned int numa_migrate_on;
	long unsigned int last_blocked_load_update_tick;
	unsigned int has_blocked_load;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	call_single_data_t nohz_csd;
	unsigned int nohz_tick_stopped;
	atomic_t nohz_flags;
	unsigned int ttwu_pending;
	u64 nr_switches;
	long: 64;
	struct cfs_rq cfs;
	struct rt_rq rt;
	struct dl_rq dl;
	struct list_head leaf_cfs_rq_list;
	struct list_head *tmp_alone_branch;
	unsigned int nr_uninterruptible;
	struct task_struct *curr;
	struct task_struct *idle;
	struct task_struct *stop;
	long unsigned int next_balance;
	struct mm_struct *prev_mm;
	unsigned int clock_update_flags;
	u64 clock;
	long: 64;
	u64 clock_task;
	u64 clock_pelt;
	long unsigned int lost_idle_time;
	atomic_t nr_iowait;
	u64 last_seen_need_resched_ns;
	int ticks_without_resched;
	int membarrier_state;
	struct root_domain *rd;
	struct sched_domain *sd;
	long unsigned int cpu_capacity;
	long unsigned int cpu_capacity_orig;
	struct callback_head *balance_callback;
	unsigned char nohz_idle_balance;
	unsigned char idle_balance;
	long unsigned int misfit_task_load;
	int active_balance;
	int push_cpu;
	struct cpu_stop_work active_balance_work;
	int cpu;
	int online;
	struct list_head cfs_tasks;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct sched_avg avg_rt;
	struct sched_avg avg_dl;
	u64 idle_stamp;
	u64 avg_idle;
	long unsigned int wake_stamp;
	u64 wake_avg_idle;
	u64 max_idle_balance_cost;
	struct rcuwait hotplug_wait;
	long unsigned int calc_load_update;
	long int calc_load_active;
	call_single_data_t hrtick_csd;
	struct hrtimer hrtick_timer;
	ktime_t hrtick_time;
	struct sched_info rq_sched_info;
	long long unsigned int rq_cpu_time;
	unsigned int yld_count;
	unsigned int sched_count;
	unsigned int sched_goidle;
	unsigned int ttwu_count;
	unsigned int ttwu_local;
	struct cpuidle_state *idle_state;
	unsigned int nr_pinned;
	unsigned int push_busy;
	struct cpu_stop_work push_work;
	struct rq *core;
	struct task_struct *core_pick;
	unsigned int core_enabled;
	unsigned int core_sched_seq;
	struct rb_root core_tree;
	unsigned int core_task_seq;
	unsigned int core_pick_seq;
	long unsigned int core_cookie;
	unsigned int core_forceidle_count;
	unsigned int core_forceidle_seq;
	unsigned int core_forceidle_occupation;
	u64 core_forceidle_start;
	cpumask_var_t scratch_mask;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

typedef void (*btf_trace_pelt_dl_tp)(void *, struct rq *);

typedef void (*btf_trace_pelt_thermal_tp)(void *, struct rq *);

typedef void (*btf_trace_pelt_irq_tp)(void *, struct rq *);

typedef void (*btf_trace_pelt_se_tp)(void *, struct sched_entity *);

typedef void (*btf_trace_sched_cpu_capacity_tp)(void *, struct rq *);

typedef void (*btf_trace_sched_overutilized_tp)(void *, struct root_domain *, bool);

typedef void (*btf_trace_sched_util_est_cfs_tp)(void *, struct cfs_rq *);

typedef void (*btf_trace_sched_util_est_se_tp)(void *, struct sched_entity *);

typedef void (*btf_trace_sched_update_nr_running_tp)(void *, struct rq *, int);

struct cpudl_item {
	u64 dl;
	int cpu;
	int idx;
};

struct rt_bandwidth {
	raw_spinlock_t rt_runtime_lock;
	ktime_t rt_period;
	u64 rt_runtime;
	struct hrtimer rt_period_timer;
	unsigned int rt_period_active;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

typedef int (*tg_visitor)(struct task_group *, void *);

struct perf_domain {
	struct em_perf_domain *em_pd;
	struct perf_domain *next;
	struct callback_head rcu;
};

struct rq_flags {
	long unsigned int flags;
	struct pin_cookie cookie;
	unsigned int clock_update_flags;
};

struct sched_entity_stats {
	struct sched_entity se;
	struct sched_statistics stats;
};

enum {
	__SCHED_FEAT_GENTLE_FAIR_SLEEPERS = 0,
	__SCHED_FEAT_START_DEBIT = 1,
	__SCHED_FEAT_NEXT_BUDDY = 2,
	__SCHED_FEAT_LAST_BUDDY = 3,
	__SCHED_FEAT_CACHE_HOT_BUDDY = 4,
	__SCHED_FEAT_WAKEUP_PREEMPTION = 5,
	__SCHED_FEAT_HRTICK = 6,
	__SCHED_FEAT_HRTICK_DL = 7,
	__SCHED_FEAT_DOUBLE_TICK = 8,
	__SCHED_FEAT_NONTASK_CAPACITY = 9,
	__SCHED_FEAT_TTWU_QUEUE = 10,
	__SCHED_FEAT_SIS_PROP = 11,
	__SCHED_FEAT_SIS_UTIL = 12,
	__SCHED_FEAT_WARN_DOUBLE_CLOCK = 13,
	__SCHED_FEAT_RT_PUSH_IPI = 14,
	__SCHED_FEAT_RT_RUNTIME_SHARE = 15,
	__SCHED_FEAT_LB_MIN = 16,
	__SCHED_FEAT_ATTACH_AGE_LOAD = 17,
	__SCHED_FEAT_WA_IDLE = 18,
	__SCHED_FEAT_WA_WEIGHT = 19,
	__SCHED_FEAT_WA_BIAS = 20,
	__SCHED_FEAT_UTIL_EST = 21,
	__SCHED_FEAT_UTIL_EST_FASTUP = 22,
	__SCHED_FEAT_LATENCY_WARN = 23,
	__SCHED_FEAT_ALT_PERIOD = 24,
	__SCHED_FEAT_BASE_SLICE = 25,
	__SCHED_FEAT_NR = 26,
};

struct affinity_context {
	const struct cpumask *new_mask;
	struct cpumask *user_mask;
	unsigned int flags;
};

enum cpu_util_type {
	FREQUENCY_UTIL = 0,
	ENERGY_UTIL = 1,
};

struct set_affinity_pending;

struct migration_arg {
	struct task_struct *task;
	int dest_cpu;
	struct set_affinity_pending *pending;
};

struct set_affinity_pending {
	refcount_t refs;
	unsigned int stop_pending;
	struct completion done;
	struct cpu_stop_work stop_work;
	struct migration_arg arg;
};

struct migration_swap_arg {
	struct task_struct *src_task;
	struct task_struct *dst_task;
	int src_cpu;
	int dst_cpu;
};

struct tick_work {
	int cpu;
	atomic_t state;
	struct delayed_work work;
};

struct cfs_schedulable_data {
	struct task_group *tg;
	u64 period;
	u64 quota;
};

enum {
	cpuset = 0,
	possible = 1,
	fail = 2,
};

struct numa_group {
	refcount_t refcount;
	spinlock_t lock;
	int nr_tasks;
	pid_t gid;
	int active_nodes;
	struct callback_head rcu;
	long unsigned int total_faults;
	long unsigned int max_faults_cpu;
	long unsigned int faults[0];
};

struct update_util_data {
	void (*func)(struct update_util_data *, u64, unsigned int);
};

enum tick_dep_bits {
	TICK_DEP_BIT_POSIX_TIMER = 0,
	TICK_DEP_BIT_PERF_EVENTS = 1,
	TICK_DEP_BIT_SCHED = 2,
	TICK_DEP_BIT_CLOCK_UNSTABLE = 3,
	TICK_DEP_BIT_RCU = 4,
	TICK_DEP_BIT_RCU_EXP = 5,
};

struct cpuidle_state_usage {
	long long unsigned int disable;
	long long unsigned int usage;
	u64 time_ns;
	long long unsigned int above;
	long long unsigned int below;
	long long unsigned int rejected;
	long long unsigned int s2idle_usage;
	long long unsigned int s2idle_time;
};

struct cpuidle_device;

struct cpuidle_driver;

struct cpuidle_state {
	char name[16];
	char desc[32];
	s64 exit_latency_ns;
	s64 target_residency_ns;
	unsigned int flags;
	unsigned int exit_latency;
	int power_usage;
	unsigned int target_residency;
	int (*enter)(struct cpuidle_device *, struct cpuidle_driver *, int);
	int (*enter_dead)(struct cpuidle_device *, int);
	int (*enter_s2idle)(struct cpuidle_device *, struct cpuidle_driver *, int);
};

struct cpuidle_driver_kobj;

struct cpuidle_state_kobj;

struct cpuidle_device_kobj;

struct cpuidle_device {
	unsigned int registered: 1;
	unsigned int enabled: 1;
	unsigned int poll_time_limit: 1;
	unsigned int cpu;
	ktime_t next_hrtimer;
	int last_state_idx;
	u64 last_residency_ns;
	u64 poll_limit_ns;
	u64 forced_idle_latency_limit_ns;
	struct cpuidle_state_usage states_usage[10];
	struct cpuidle_state_kobj *kobjs[10];
	struct cpuidle_driver_kobj *kobj_driver;
	struct cpuidle_device_kobj *kobj_dev;
	struct list_head device_list;
};

struct cpuidle_driver {
	const char *name;
	struct module *owner;
	unsigned int bctimer: 1;
	struct cpuidle_state states[10];
	int state_count;
	int safe_state_index;
	struct cpumask *cpumask;
	const char *governor;
};

enum sched_tunable_scaling {
	SCHED_TUNABLESCALING_NONE = 0,
	SCHED_TUNABLESCALING_LOG = 1,
	SCHED_TUNABLESCALING_LINEAR = 2,
	SCHED_TUNABLESCALING_END = 3,
};

enum numa_topology_type {
	NUMA_DIRECT = 0,
	NUMA_GLUELESS_MESH = 1,
	NUMA_BACKPLANE = 2,
};

enum numa_faults_stats {
	NUMA_MEM = 0,
	NUMA_CPU = 1,
	NUMA_MEMBUF = 2,
	NUMA_CPUBUF = 3,
};

enum numa_type {
	node_has_spare = 0,
	node_fully_busy = 1,
	node_overloaded = 2,
};

struct numa_stats {
	long unsigned int load;
	long unsigned int runnable;
	long unsigned int util;
	long unsigned int compute_capacity;
	unsigned int nr_running;
	unsigned int weight;
	enum numa_type node_type;
	int idle_cpu;
};

struct task_numa_env {
	struct task_struct *p;
	int src_cpu;
	int src_nid;
	int dst_cpu;
	int dst_nid;
	int imb_numa_nr;
	struct numa_stats src_stats;
	struct numa_stats dst_stats;
	int imbalance_pct;
	int dist;
	struct task_struct *best_task;
	long int best_imp;
	int best_cpu;
};

enum fbq_type {
	regular = 0,
	remote = 1,
	all = 2,
};

enum group_type {
	group_has_spare = 0,
	group_fully_busy = 1,
	group_misfit_task = 2,
	group_asym_packing = 3,
	group_imbalanced = 4,
	group_overloaded = 5,
};

enum migration_type {
	migrate_load = 0,
	migrate_util = 1,
	migrate_task = 2,
	migrate_misfit = 3,
};

struct lb_env {
	struct sched_domain *sd;
	struct rq *src_rq;
	int src_cpu;
	int dst_cpu;
	struct rq *dst_rq;
	struct cpumask *dst_grpmask;
	int new_dst_cpu;
	enum cpu_idle_type idle;
	long int imbalance;
	struct cpumask *cpus;
	unsigned int flags;
	unsigned int loop;
	unsigned int loop_break;
	unsigned int loop_max;
	enum fbq_type fbq_type;
	enum migration_type migration_type;
	struct list_head tasks;
};

struct sg_lb_stats {
	long unsigned int avg_load;
	long unsigned int group_load;
	long unsigned int group_capacity;
	long unsigned int group_util;
	long unsigned int group_runnable;
	unsigned int sum_nr_running;
	unsigned int sum_h_nr_running;
	unsigned int idle_cpus;
	unsigned int group_weight;
	enum group_type group_type;
	unsigned int group_asym_packing;
	long unsigned int group_misfit_task_load;
	unsigned int nr_numa_running;
	unsigned int nr_preferred_running;
};

struct sd_lb_stats {
	struct sched_group *busiest;
	struct sched_group *local;
	long unsigned int total_load;
	long unsigned int total_capacity;
	long unsigned int avg_load;
	unsigned int prefer_sibling;
	struct sg_lb_stats busiest_stat;
	struct sg_lb_stats local_stat;
};

enum s2idle_states {
	S2IDLE_STATE_NONE = 0,
	S2IDLE_STATE_ENTER = 1,
	S2IDLE_STATE_WAKE = 2,
};

struct dl_bandwidth {
	raw_spinlock_t dl_runtime_lock;
	u64 dl_runtime;
	u64 dl_period;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
};

struct idle_timer {
	struct hrtimer timer;
	int done;
};

typedef struct rt_rq *rt_rq_iter_t;

struct swait_queue {
	struct task_struct *task;
	struct list_head task_list;
};

struct sd_flag_debug {
	unsigned int meta_flags;
	char *name;
};

enum {
	MEMBARRIER_FLAG_SYNC_CORE = 1,
	MEMBARRIER_FLAG_RSEQ = 2,
};

enum cpufreq_table_sorting {
	CPUFREQ_TABLE_UNSORTED = 0,
	CPUFREQ_TABLE_SORTED_ASCENDING = 1,
	CPUFREQ_TABLE_SORTED_DESCENDING = 2,
};

struct cpufreq_cpuinfo {
	unsigned int max_freq;
	unsigned int min_freq;
	unsigned int transition_latency;
};

struct clk;

struct cpufreq_governor;

struct cpufreq_frequency_table;

struct cpufreq_stats;

struct thermal_cooling_device;

struct cpufreq_policy {
	cpumask_var_t cpus;
	cpumask_var_t related_cpus;
	cpumask_var_t real_cpus;
	unsigned int shared_type;
	unsigned int cpu;
	struct clk *clk;
	struct cpufreq_cpuinfo cpuinfo;
	unsigned int min;
	unsigned int max;
	unsigned int cur;
	unsigned int suspend_freq;
	unsigned int policy;
	unsigned int last_policy;
	struct cpufreq_governor *governor;
	void *governor_data;
	char last_governor[16];
	struct work_struct update;
	struct freq_constraints constraints;
	struct freq_qos_request *min_freq_req;
	struct freq_qos_request *max_freq_req;
	struct cpufreq_frequency_table *freq_table;
	enum cpufreq_table_sorting freq_table_sorted;
	struct list_head policy_list;
	struct kobject kobj;
	struct completion kobj_unregister;
	struct rw_semaphore rwsem;
	bool fast_switch_possible;
	bool fast_switch_enabled;
	bool strict_target;
	bool efficiencies_available;
	unsigned int transition_delay_us;
	bool dvfs_possible_from_any_cpu;
	unsigned int cached_target_freq;
	unsigned int cached_resolved_idx;
	bool transition_ongoing;
	spinlock_t transition_lock;
	wait_queue_head_t transition_wait;
	struct task_struct *transition_task;
	struct cpufreq_stats *stats;
	void *driver_data;
	struct thermal_cooling_device *cdev;
	struct notifier_block nb_min;
	struct notifier_block nb_max;
};

struct cpufreq_governor {
	char name[16];
	int (*init)(struct cpufreq_policy *);
	void (*exit)(struct cpufreq_policy *);
	int (*start)(struct cpufreq_policy *);
	void (*stop)(struct cpufreq_policy *);
	void (*limits)(struct cpufreq_policy *);
	ssize_t (*show_setspeed)(struct cpufreq_policy *, char *);
	int (*store_setspeed)(struct cpufreq_policy *, unsigned int);
	struct list_head governor_list;
	struct module *owner;
	u8 flags;
};

struct cpufreq_frequency_table {
	unsigned int flags;
	unsigned int driver_data;
	unsigned int frequency;
};

struct gov_attr_set {
	struct kobject kobj;
	struct list_head policy_list;
	struct mutex update_lock;
	int usage_count;
};

struct governor_attr {
	struct attribute attr;
	ssize_t (*show)(struct gov_attr_set *, char *);
	ssize_t (*store)(struct gov_attr_set *, const char *, size_t);
};

enum membarrier_cmd {
	MEMBARRIER_CMD_QUERY = 0,
	MEMBARRIER_CMD_GLOBAL = 1,
	MEMBARRIER_CMD_GLOBAL_EXPEDITED = 2,
	MEMBARRIER_CMD_REGISTER_GLOBAL_EXPEDITED = 4,
	MEMBARRIER_CMD_PRIVATE_EXPEDITED = 8,
	MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED = 16,
	MEMBARRIER_CMD_PRIVATE_EXPEDITED_SYNC_CORE = 32,
	MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_SYNC_CORE = 64,
	MEMBARRIER_CMD_PRIVATE_EXPEDITED_RSEQ = 128,
	MEMBARRIER_CMD_REGISTER_PRIVATE_EXPEDITED_RSEQ = 256,
	MEMBARRIER_CMD_SHARED = 1,
};

enum membarrier_cmd_flag {
	MEMBARRIER_CMD_FLAG_CPU = 1,
};

enum psi_res {
	PSI_IO = 0,
	PSI_MEM = 1,
	PSI_CPU = 2,
	NR_PSI_RESOURCES = 3,
};

struct psi_window {
	u64 size;
	u64 start_time;
	u64 start_value;
	u64 prev_growth;
};

struct psi_trigger {
	enum psi_states state;
	u64 threshold;
	struct list_head node;
	struct psi_group *group;
	wait_queue_head_t event_wait;
	int event;
	struct psi_window win;
	u64 last_event_time;
	bool pending_event;
};

enum cpuacct_stat_index {
	CPUACCT_STAT_USER = 0,
	CPUACCT_STAT_SYSTEM = 1,
	CPUACCT_STAT_NSTATS = 2,
};

struct cpuacct {
	struct cgroup_subsys_state css;
	u64 *cpuusage;
	struct kernel_cpustat *cpustat;
};

struct sugov_tunables {
	struct gov_attr_set attr_set;
	unsigned int rate_limit_us;
};

struct sugov_policy {
	struct cpufreq_policy *policy;
	struct sugov_tunables *tunables;
	struct list_head tunables_hook;
	raw_spinlock_t update_lock;
	u64 last_freq_update_time;
	s64 freq_update_delay_ns;
	unsigned int next_freq;
	unsigned int cached_raw_freq;
	struct irq_work irq_work;
	struct kthread_work work;
	struct mutex work_lock;
	struct kthread_worker worker;
	struct task_struct *thread;
	bool work_in_progress;
	bool limits_changed;
	bool need_freq_update;
};

struct sugov_cpu {
	struct update_util_data update_util;
	struct sugov_policy *sg_policy;
	unsigned int cpu;
	bool iowait_boost_pending;
	unsigned int iowait_boost;
	u64 last_update;
	long unsigned int util;
	long unsigned int bw_dl;
	long unsigned int max;
	long unsigned int saved_idle_calls;
};

struct s_data {
	struct sched_domain **sd;
	struct root_domain *rd;
};

enum s_alloc {
	sa_rootdomain = 0,
	sa_sd = 1,
	sa_sd_storage = 2,
	sa_none = 3,
};

struct asym_cap_data {
	struct list_head link;
	long unsigned int capacity;
	long unsigned int cpus[0];
};

struct sched_core_cookie {
	refcount_t refcnt;
};

enum hk_flags {
	HK_FLAG_TIMER = 1,
	HK_FLAG_RCU = 2,
	HK_FLAG_MISC = 4,
	HK_FLAG_SCHED = 8,
	HK_FLAG_TICK = 16,
	HK_FLAG_DOMAIN = 32,
	HK_FLAG_WQ = 64,
	HK_FLAG_MANAGED_IRQ = 128,
	HK_FLAG_KTHREAD = 256,
};

struct housekeeping {
	struct cpumask cpumasks[9];
	long unsigned int flags;
};

struct ww_acquire_ctx;

struct ww_mutex {
	struct mutex base;
	struct ww_acquire_ctx *ctx;
};

struct ww_acquire_ctx {
	struct task_struct *task;
	long unsigned int stamp;
	unsigned int acquired;
	short unsigned int wounded;
	short unsigned int is_wait_die;
};

struct mutex_waiter {
	struct list_head list;
	struct task_struct *task;
	struct ww_acquire_ctx *ww_ctx;
};

struct semaphore_waiter {
	struct list_head list;
	struct task_struct *task;
	bool up;
};

enum rwsem_waiter_type {
	RWSEM_WAITING_FOR_WRITE = 0,
	RWSEM_WAITING_FOR_READ = 1,
};

struct rwsem_waiter {
	struct list_head list;
	struct task_struct *task;
	enum rwsem_waiter_type type;
	long unsigned int timeout;
};

enum rwsem_wake_type {
	RWSEM_WAKE_ANY = 0,
	RWSEM_WAKE_READERS = 1,
	RWSEM_WAKE_READ_OWNED = 2,
};

enum writer_wait_state {
	WRITER_NOT_FIRST = 0,
	WRITER_FIRST = 1,
	WRITER_HANDOFF = 2,
};

enum owner_state {
	OWNER_NULL = 1,
	OWNER_WRITER = 2,
	OWNER_READER = 4,
	OWNER_NONSPINNABLE = 8,
};

struct optimistic_spin_node {
	struct optimistic_spin_node *next;
	struct optimistic_spin_node *prev;
	int locked;
	int cpu;
};

struct mcs_spinlock {
	struct mcs_spinlock *next;
	int locked;
	int count;
};

struct qnode {
	struct mcs_spinlock mcs;
	long int reserved[2];
};

enum vcpu_state {
	vcpu_running = 0,
	vcpu_halted = 1,
	vcpu_hashed = 2,
};

struct pv_node {
	struct mcs_spinlock mcs;
	int cpu;
	u8 state;
};

struct pv_hash_entry {
	struct qspinlock *lock;
	struct pv_node *node;
};

struct rt_mutex_base {
	raw_spinlock_t wait_lock;
	struct rb_root_cached waiters;
	struct task_struct *owner;
};

struct rt_mutex {
	struct rt_mutex_base rtmutex;
};

struct hrtimer_sleeper {
	struct hrtimer timer;
	struct task_struct *task;
};

struct rt_mutex_waiter {
	struct rb_node tree_entry;
	struct rb_node pi_tree_entry;
	struct task_struct *task;
	struct rt_mutex_base *lock;
	unsigned int wake_state;
	int prio;
	u64 deadline;
	struct ww_acquire_ctx *ww_ctx;
};

struct rt_wake_q_head {
	struct wake_q_head head;
	struct task_struct *rtlock_task;
};

enum rtmutex_chainwalk {
	RT_MUTEX_MIN_CHAINWALK = 0,
	RT_MUTEX_FULL_CHAINWALK = 1,
};

struct pm_qos_request {
	struct plist_node node;
	struct pm_qos_constraints *qos;
};

enum pm_qos_req_action {
	PM_QOS_ADD_REQ = 0,
	PM_QOS_UPDATE_REQ = 1,
	PM_QOS_REMOVE_REQ = 2,
};

enum suspend_stat_step {
	SUSPEND_FREEZE = 1,
	SUSPEND_PREPARE = 2,
	SUSPEND_SUSPEND = 3,
	SUSPEND_SUSPEND_LATE = 4,
	SUSPEND_SUSPEND_NOIRQ = 5,
	SUSPEND_RESUME_NOIRQ = 6,
	SUSPEND_RESUME_EARLY = 7,
	SUSPEND_RESUME = 8,
};

struct suspend_stats {
	int success;
	int fail;
	int failed_freeze;
	int failed_prepare;
	int failed_suspend;
	int failed_suspend_late;
	int failed_suspend_noirq;
	int failed_resume;
	int failed_resume_early;
	int failed_resume_noirq;
	int last_failed_dev;
	char failed_devs[80];
	int last_failed_errno;
	int errno[2];
	int last_failed_step;
	enum suspend_stat_step failed_steps[2];
};

enum {
	TEST_NONE = 0,
	TEST_CORE = 1,
	TEST_CPUS = 2,
	TEST_PLATFORM = 3,
	TEST_DEVICES = 4,
	TEST_FREEZER = 5,
	__TEST_AFTER_LAST = 6,
};

struct pm_vt_switch {
	struct list_head head;
	struct device *dev;
	bool required;
};

struct platform_s2idle_ops {
	int (*begin)();
	int (*prepare)();
	int (*prepare_late)();
	bool (*wake)();
	void (*restore_early)();
	void (*restore)();
	void (*end)();
};

struct em_data_callback {
	int (*active_power)(struct device *, long unsigned int *, long unsigned int *);
	int (*get_cost)(struct device *, long unsigned int, long unsigned int *);
};

typedef struct {
	seqcount_t seqcount;
} seqcount_latch_t;

struct dev_printk_info {
	char subsystem[16];
	char device[48];
};

struct trace_event_raw_console {
	struct trace_entry ent;
	u32 __data_loc_msg;
	char __data[0];
};

struct trace_event_data_offsets_console {
	u32 msg;
};

typedef void (*btf_trace_console)(void *, const char *, size_t);

struct printk_info {
	u64 seq;
	u64 ts_nsec;
	u16 text_len;
	u8 facility;
	u8 flags: 5;
	u8 level: 3;
	u32 caller_id;
	struct dev_printk_info dev_info;
};

struct printk_record {
	struct printk_info *info;
	char *text_buf;
	unsigned int text_buf_size;
};

struct prb_data_blk_lpos {
	long unsigned int begin;
	long unsigned int next;
};

struct prb_desc {
	atomic_long_t state_var;
	struct prb_data_blk_lpos text_blk_lpos;
};

struct prb_data_ring {
	unsigned int size_bits;
	char *data;
	atomic_long_t head_lpos;
	atomic_long_t tail_lpos;
};

struct prb_desc_ring {
	unsigned int count_bits;
	struct prb_desc *descs;
	struct printk_info *infos;
	atomic_long_t head_id;
	atomic_long_t tail_id;
	atomic_long_t last_finalized_id;
};

struct printk_ringbuffer {
	struct prb_desc_ring desc_ring;
	struct prb_data_ring text_data_ring;
	atomic_long_t fail;
};

struct prb_reserved_entry {
	struct printk_ringbuffer *rb;
	long unsigned int irqflags;
	long unsigned int id;
	unsigned int text_space;
};

enum desc_state {
	desc_miss = 4294967295,
	desc_reserved = 0,
	desc_committed = 1,
	desc_finalized = 2,
	desc_reusable = 3,
};

struct console_cmdline {
	char name[16];
	int index;
	bool user_specified;
	char *options;
};

enum printk_info_flags {
	LOG_NEWLINE = 2,
	LOG_CONT = 8,
};

enum devkmsg_log_bits {
	__DEVKMSG_LOG_BIT_ON = 0,
	__DEVKMSG_LOG_BIT_OFF = 1,
	__DEVKMSG_LOG_BIT_LOCK = 2,
};

enum devkmsg_log_masks {
	DEVKMSG_LOG_MASK_ON = 1,
	DEVKMSG_LOG_MASK_OFF = 2,
	DEVKMSG_LOG_MASK_LOCK = 4,
};

enum con_msg_format_flags {
	MSG_FORMAT_DEFAULT = 0,
	MSG_FORMAT_SYSLOG = 1,
};

struct latched_seq {
	seqcount_latch_t latch;
	u64 val[2];
};

struct devkmsg_user {
	atomic64_t seq;
	struct ratelimit_state rs;
	struct mutex lock;
	char buf[8192];
	struct printk_info info;
	char text_buf[8192];
	struct printk_record record;
};

enum kdb_msgsrc {
	KDB_MSGSRC_INTERNAL = 0,
	KDB_MSGSRC_PRINTK = 1,
};

struct prb_data_block {
	long unsigned int id;
	char data[0];
};

enum {
	IRQS_AUTODETECT = 1,
	IRQS_SPURIOUS_DISABLED = 2,
	IRQS_POLL_INPROGRESS = 8,
	IRQS_ONESHOT = 32,
	IRQS_REPLAY = 64,
	IRQS_WAITING = 128,
	IRQS_PENDING = 512,
	IRQS_SUSPENDED = 2048,
	IRQS_TIMINGS = 4096,
	IRQS_NMI = 8192,
};

enum {
	_IRQ_DEFAULT_INIT_FLAGS = 2048,
	_IRQ_PER_CPU = 512,
	_IRQ_LEVEL = 256,
	_IRQ_NOPROBE = 1024,
	_IRQ_NOREQUEST = 2048,
	_IRQ_NOTHREAD = 65536,
	_IRQ_NOAUTOEN = 4096,
	_IRQ_MOVE_PCNTXT = 16384,
	_IRQ_NO_BALANCING = 8192,
	_IRQ_NESTED_THREAD = 32768,
	_IRQ_PER_CPU_DEVID = 131072,
	_IRQ_IS_POLLED = 262144,
	_IRQ_DISABLE_UNLAZY = 524288,
	_IRQ_HIDDEN = 1048576,
	_IRQ_NO_DEBUG = 2097152,
	_IRQF_MODIFY_MASK = 2096911,
};

enum {
	IRQTF_RUNTHREAD = 0,
	IRQTF_WARNED = 1,
	IRQTF_AFFINITY = 2,
	IRQTF_FORCED_THREAD = 3,
};

enum {
	IRQC_IS_HARDIRQ = 0,
	IRQC_IS_NESTED = 1,
};

enum {
	IRQ_STARTUP_NORMAL = 0,
	IRQ_STARTUP_MANAGED = 1,
	IRQ_STARTUP_ABORT = 2,
};

struct irq_devres {
	unsigned int irq;
	void *dev_id;
};

struct irq_desc_devres {
	unsigned int from;
	unsigned int cnt;
};

enum {
	IRQ_DOMAIN_FLAG_HIERARCHY = 1,
	IRQ_DOMAIN_NAME_ALLOCATED = 2,
	IRQ_DOMAIN_FLAG_IPI_PER_CPU = 4,
	IRQ_DOMAIN_FLAG_IPI_SINGLE = 8,
	IRQ_DOMAIN_FLAG_MSI = 16,
	IRQ_DOMAIN_FLAG_MSI_REMAP = 32,
	IRQ_DOMAIN_MSI_NOMASK_QUIRK = 64,
	IRQ_DOMAIN_FLAG_NO_MAP = 128,
	IRQ_DOMAIN_FLAG_NONCORE = 65536,
};

struct irqchip_fwid {
	struct fwnode_handle fwnode;
	unsigned int type;
	char *name;
	phys_addr_t *pa;
};

enum {
	AFFINITY = 0,
	AFFINITY_LIST = 1,
	EFFECTIVE = 2,
	EFFECTIVE_LIST = 3,
};

struct msi_alloc_info {
	struct msi_desc *desc;
	irq_hw_number_t hwirq;
	long unsigned int flags;
	union {
		long unsigned int ul;
		void *ptr;
	} scratchpad[2];
};

typedef struct msi_alloc_info msi_alloc_info_t;

struct msi_domain_info;

struct msi_domain_ops {
	irq_hw_number_t (*get_hwirq)(struct msi_domain_info *, msi_alloc_info_t *);
	int (*msi_init)(struct irq_domain *, struct msi_domain_info *, unsigned int, irq_hw_number_t, msi_alloc_info_t *);
	void (*msi_free)(struct irq_domain *, struct msi_domain_info *, unsigned int);
	int (*msi_check)(struct irq_domain *, struct msi_domain_info *, struct device *);
	int (*msi_prepare)(struct irq_domain *, struct device *, int, msi_alloc_info_t *);
	void (*msi_finish)(msi_alloc_info_t *, int);
	void (*set_desc)(msi_alloc_info_t *, struct msi_desc *);
	int (*handle_error)(struct irq_domain *, struct msi_desc *, int);
	int (*domain_alloc_irqs)(struct irq_domain *, struct device *, int);
	void (*domain_free_irqs)(struct irq_domain *, struct device *);
};

struct msi_domain_info {
	u32 flags;
	struct msi_domain_ops *ops;
	struct irq_chip *chip;
	void *chip_data;
	irq_flow_handler_t handler;
	void *handler_data;
	const char *handler_name;
	void *data;
};

enum {
	MSI_FLAG_USE_DEF_DOM_OPS = 1,
	MSI_FLAG_USE_DEF_CHIP_OPS = 2,
	MSI_FLAG_MULTI_PCI_MSI = 4,
	MSI_FLAG_PCI_MSIX = 8,
	MSI_FLAG_ACTIVATE_EARLY = 16,
	MSI_FLAG_MUST_REACTIVATE = 32,
	MSI_FLAG_LEVEL_CAPABLE = 64,
};

struct irq_affinity {
	unsigned int pre_vectors;
	unsigned int post_vectors;
	unsigned int nr_sets;
	unsigned int set_size[4];
	void (*calc_sets)(struct irq_affinity *, unsigned int);
	void *priv;
};

struct node_vectors {
	unsigned int id;
	union {
		unsigned int nvectors;
		unsigned int ncpus;
	};
};

typedef void (*call_rcu_func_t)(struct callback_head *, rcu_callback_t);

struct rcu_cblist {
	struct callback_head *head;
	struct callback_head **tail;
	long int len;
};

struct rcu_synchronize {
	struct callback_head head;
	struct completion completion;
};

struct trace_event_raw_rcu_utilization {
	struct trace_entry ent;
	const char *s;
	char __data[0];
};

struct trace_event_raw_rcu_stall_warning {
	struct trace_entry ent;
	const char *rcuname;
	const char *msg;
	char __data[0];
};

struct trace_event_data_offsets_rcu_utilization {};

struct trace_event_data_offsets_rcu_stall_warning {};

typedef void (*btf_trace_rcu_utilization)(void *, const char *);

typedef void (*btf_trace_rcu_stall_warning)(void *, const char *, const char *);

struct rcu_tasks;

typedef void (*rcu_tasks_gp_func_t)(struct rcu_tasks *);

typedef void (*pregp_func_t)();

typedef void (*pertask_func_t)(struct task_struct *, struct list_head *);

typedef void (*postscan_func_t)(struct list_head *);

typedef void (*holdouts_func_t)(struct list_head *, bool, bool *);

typedef void (*postgp_func_t)(struct rcu_tasks *);

struct rcu_tasks_percpu;

struct rcu_tasks {
	struct rcuwait cbs_wait;
	raw_spinlock_t cbs_gbl_lock;
	int gp_state;
	int gp_sleep;
	int init_fract;
	long unsigned int gp_jiffies;
	long unsigned int gp_start;
	long unsigned int tasks_gp_seq;
	long unsigned int n_ipis;
	long unsigned int n_ipis_fails;
	struct task_struct *kthread_ptr;
	rcu_tasks_gp_func_t gp_func;
	pregp_func_t pregp_func;
	pertask_func_t pertask_func;
	postscan_func_t postscan_func;
	holdouts_func_t holdouts_func;
	postgp_func_t postgp_func;
	call_rcu_func_t call_func;
	struct rcu_tasks_percpu *rtpcpu;
	int percpu_enqueue_shift;
	int percpu_enqueue_lim;
	int percpu_dequeue_lim;
	long unsigned int percpu_dequeue_gpseq;
	struct mutex barrier_q_mutex;
	atomic_t barrier_q_count;
	struct completion barrier_q_completion;
	long unsigned int barrier_q_seq;
	char *name;
	char *kname;
};

struct rcu_tasks_percpu {
	struct rcu_segcblist cblist;
	raw_spinlock_t lock;
	long unsigned int rtp_jiffies;
	long unsigned int rtp_n_lock_retries;
	struct work_struct rtp_work;
	struct irq_work rtp_irq_work;
	struct callback_head barrier_q_head;
	int cpu;
	struct rcu_tasks *rtpp;
};

struct trc_stall_chk_rdr {
	int nesting;
	int ipi_to_cpu;
	u8 needqs;
};

enum {
	GP_IDLE = 0,
	GP_ENTER = 1,
	GP_PASSED = 2,
	GP_EXIT = 3,
	GP_REPLAY = 4,
};

enum rcutorture_type {
	RCU_FLAVOR = 0,
	RCU_TASKS_FLAVOR = 1,
	RCU_TASKS_RUDE_FLAVOR = 2,
	RCU_TASKS_TRACING_FLAVOR = 3,
	RCU_TRIVIAL_FLAVOR = 4,
	SRCU_FLAVOR = 5,
	INVALID_RCU_FLAVOR = 6,
};

struct rcu_exp_work {
	long unsigned int rew_s;
	struct work_struct rew_work;
};

struct rcu_node {
	raw_spinlock_t lock;
	long unsigned int gp_seq;
	long unsigned int gp_seq_needed;
	long unsigned int completedqs;
	long unsigned int qsmask;
	long unsigned int rcu_gp_init_mask;
	long unsigned int qsmaskinit;
	long unsigned int qsmaskinitnext;
	long unsigned int expmask;
	long unsigned int expmaskinit;
	long unsigned int expmaskinitnext;
	long unsigned int cbovldmask;
	long unsigned int ffmask;
	long unsigned int grpmask;
	int grplo;
	int grphi;
	u8 grpnum;
	u8 level;
	bool wait_blkd_tasks;
	struct rcu_node *parent;
	struct list_head blkd_tasks;
	struct list_head *gp_tasks;
	struct list_head *exp_tasks;
	struct list_head *boost_tasks;
	struct rt_mutex boost_mtx;
	long unsigned int boost_time;
	struct mutex boost_kthread_mutex;
	struct task_struct *boost_kthread_task;
	unsigned int boost_kthread_status;
	long unsigned int n_boosts;
	struct swait_queue_head nocb_gp_wq[2];
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	raw_spinlock_t fqslock;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	spinlock_t exp_lock;
	long unsigned int exp_seq_rq;
	wait_queue_head_t exp_wq[4];
	struct rcu_exp_work rew;
	bool exp_need_flush;
	long: 56;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

union rcu_noqs {
	struct {
		u8 norm;
		u8 exp;
	} b;
	u16 s;
};

struct rcu_data {
	long unsigned int gp_seq;
	long unsigned int gp_seq_needed;
	union rcu_noqs cpu_no_qs;
	bool core_needs_qs;
	bool beenonline;
	bool gpwrap;
	bool cpu_started;
	struct rcu_node *mynode;
	long unsigned int grpmask;
	long unsigned int ticks_this_gp;
	struct irq_work defer_qs_iw;
	bool defer_qs_iw_pending;
	struct work_struct strict_work;
	struct rcu_segcblist cblist;
	long int qlen_last_fqs_check;
	long unsigned int n_cbs_invoked;
	long unsigned int n_force_qs_snap;
	long int blimit;
	int dynticks_snap;
	long int dynticks_nesting;
	long int dynticks_nmi_nesting;
	atomic_t dynticks;
	bool rcu_need_heavy_qs;
	bool rcu_urgent_qs;
	bool rcu_forced_tick;
	bool rcu_forced_tick_exp;
	long unsigned int barrier_seq_snap;
	struct callback_head barrier_head;
	int exp_dynticks_snap;
	struct swait_queue_head nocb_cb_wq;
	struct swait_queue_head nocb_state_wq;
	struct task_struct *nocb_gp_kthread;
	raw_spinlock_t nocb_lock;
	atomic_t nocb_lock_contended;
	int nocb_defer_wakeup;
	struct timer_list nocb_timer;
	long unsigned int nocb_gp_adv_time;
	struct mutex nocb_gp_kthread_mutex;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	raw_spinlock_t nocb_bypass_lock;
	struct rcu_cblist nocb_bypass;
	long unsigned int nocb_bypass_first;
	long unsigned int nocb_nobypass_last;
	int nocb_nobypass_count;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	raw_spinlock_t nocb_gp_lock;
	u8 nocb_gp_sleep;
	u8 nocb_gp_bypass;
	u8 nocb_gp_gp;
	long unsigned int nocb_gp_seq;
	long unsigned int nocb_gp_loops;
	struct swait_queue_head nocb_gp_wq;
	bool nocb_cb_sleep;
	struct task_struct *nocb_cb_kthread;
	struct list_head nocb_head_rdp;
	struct list_head nocb_entry_rdp;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	struct rcu_data *nocb_gp_rdp;
	struct task_struct *rcu_cpu_kthread_task;
	unsigned int rcu_cpu_kthread_status;
	char rcu_cpu_has_work;
	long unsigned int rcuc_activity;
	unsigned int softirq_snap;
	struct irq_work rcu_iw;
	bool rcu_iw_pending;
	long unsigned int rcu_iw_gp_seq;
	long unsigned int rcu_ofl_gp_seq;
	short int rcu_ofl_gp_flags;
	long unsigned int rcu_onl_gp_seq;
	short int rcu_onl_gp_flags;
	long unsigned int last_fqs_resched;
	long unsigned int last_sched_clock;
	int cpu;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct rcu_state {
	struct rcu_node node[131];
	struct rcu_node *level[4];
	int ncpus;
	int n_online_cpus;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long unsigned int gp_seq;
	long unsigned int gp_max;
	struct task_struct *gp_kthread;
	struct swait_queue_head gp_wq;
	short int gp_flags;
	short int gp_state;
	long unsigned int gp_wake_time;
	long unsigned int gp_wake_seq;
	struct mutex barrier_mutex;
	atomic_t barrier_cpu_count;
	struct completion barrier_completion;
	long unsigned int barrier_sequence;
	raw_spinlock_t barrier_lock;
	struct mutex exp_mutex;
	struct mutex exp_wake_mutex;
	long unsigned int expedited_sequence;
	atomic_t expedited_need_qs;
	struct swait_queue_head expedited_wq;
	int ncpus_snap;
	u8 cbovld;
	u8 cbovldnext;
	long unsigned int jiffies_force_qs;
	long unsigned int jiffies_kick_kthreads;
	long unsigned int n_force_qs;
	long unsigned int gp_start;
	long unsigned int gp_end;
	long unsigned int gp_activity;
	long unsigned int gp_req_activity;
	long unsigned int jiffies_stall;
	long unsigned int jiffies_resched;
	long unsigned int n_force_qs_gpstart;
	const char *name;
	char abbr;
	long: 56;
	long: 64;
	long: 64;
	arch_spinlock_t ofl_lock;
	int nocb_is_setup;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct kvfree_rcu_bulk_data {
	long unsigned int nr_records;
	struct kvfree_rcu_bulk_data *next;
	void *records[0];
};

struct kfree_rcu_cpu;

struct kfree_rcu_cpu_work {
	struct rcu_work rcu_work;
	struct callback_head *head_free;
	struct kvfree_rcu_bulk_data *bkvhead_free[2];
	struct kfree_rcu_cpu *krcp;
};

struct kfree_rcu_cpu {
	struct callback_head *head;
	struct kvfree_rcu_bulk_data *bkvhead[2];
	struct kfree_rcu_cpu_work krw_arr[2];
	raw_spinlock_t lock;
	struct delayed_work monitor_work;
	bool monitor_todo;
	bool initialized;
	int count;
	struct delayed_work page_cache_work;
	atomic_t backoff_page_cache_fill;
	atomic_t work_in_progress;
	struct hrtimer hrtimer;
	struct llist_head bkvcache;
	int nr_bkv_objs;
};

struct klp_func {
	const char *old_name;
	void *new_func;
	long unsigned int old_sympos;
	void *old_func;
	struct kobject kobj;
	struct list_head node;
	struct list_head stack_node;
	long unsigned int old_size;
	long unsigned int new_size;
	bool nop;
	bool patched;
	bool transition;
};

struct klp_object;

struct klp_callbacks {
	int (*pre_patch)(struct klp_object *);
	void (*post_patch)(struct klp_object *);
	void (*pre_unpatch)(struct klp_object *);
	void (*post_unpatch)(struct klp_object *);
	bool post_unpatch_enabled;
};

struct klp_object {
	const char *name;
	struct klp_func *funcs;
	struct klp_callbacks callbacks;
	struct kobject kobj;
	struct list_head func_list;
	struct list_head node;
	struct module *mod;
	bool dynamic;
	bool patched;
};

struct klp_state {
	long unsigned int id;
	unsigned int version;
	void *data;
};

struct klp_patch {
	struct module *mod;
	struct klp_object *objs;
	struct klp_state *states;
	bool replace;
	struct list_head list;
	struct kobject kobj;
	struct list_head obj_list;
	bool enabled;
	bool forced;
	struct work_struct free_work;
	struct completion finish;
};

struct klp_find_arg {
	const char *objname;
	const char *name;
	long unsigned int addr;
	long unsigned int count;
	long unsigned int pos;
};

enum {
	FTRACE_OPS_FL_ENABLED = 1,
	FTRACE_OPS_FL_DYNAMIC = 2,
	FTRACE_OPS_FL_SAVE_REGS = 4,
	FTRACE_OPS_FL_SAVE_REGS_IF_SUPPORTED = 8,
	FTRACE_OPS_FL_RECURSION = 16,
	FTRACE_OPS_FL_STUB = 32,
	FTRACE_OPS_FL_INITIALIZED = 64,
	FTRACE_OPS_FL_DELETED = 128,
	FTRACE_OPS_FL_ADDING = 256,
	FTRACE_OPS_FL_REMOVING = 512,
	FTRACE_OPS_FL_MODIFYING = 1024,
	FTRACE_OPS_FL_ALLOC_TRAMP = 2048,
	FTRACE_OPS_FL_IPMODIFY = 4096,
	FTRACE_OPS_FL_PID = 8192,
	FTRACE_OPS_FL_RCU = 16384,
	FTRACE_OPS_FL_TRACE_ARRAY = 32768,
	FTRACE_OPS_FL_PERMANENT = 65536,
	FTRACE_OPS_FL_DIRECT = 131072,
};

struct klp_ops {
	struct list_head node;
	struct list_head func_stack;
	struct ftrace_ops fops;
};

typedef int (*klp_shadow_ctor_t)(void *, void *, void *);

typedef void (*klp_shadow_dtor_t)(void *, void *);

struct klp_shadow {
	struct hlist_node node;
	struct callback_head callback_head;
	void *obj;
	long unsigned int id;
	char data[0];
};

struct dma_sgt_handle {
	struct sg_table sgt;
	struct page **pages;
};

struct dma_devres {
	size_t size;
	void *vaddr;
	dma_addr_t dma_handle;
	long unsigned int attrs;
};

enum pci_p2pdma_map_type {
	PCI_P2PDMA_MAP_UNKNOWN = 0,
	PCI_P2PDMA_MAP_NOT_SUPPORTED = 1,
	PCI_P2PDMA_MAP_BUS_ADDR = 2,
	PCI_P2PDMA_MAP_THRU_HOST_BRIDGE = 3,
};

struct pci_p2pdma_map_state {
	struct dev_pagemap *pgmap;
	int map;
	u64 bus_off;
};

struct dma_coherent_mem {
	void *virt_base;
	dma_addr_t device_base;
	long unsigned int pfn_base;
	int size;
	long unsigned int *bitmap;
	spinlock_t spinlock;
	bool use_dev_dma_pfn_offset;
};

enum {
	MEMREMAP_WB = 1,
	MEMREMAP_WT = 2,
	MEMREMAP_WC = 4,
	MEMREMAP_ENC = 8,
	MEMREMAP_DEC = 16,
};

struct reserved_mem_ops;

struct reserved_mem {
	const char *name;
	long unsigned int fdt_node;
	long unsigned int phandle;
	const struct reserved_mem_ops *ops;
	phys_addr_t base;
	phys_addr_t size;
	void *priv;
};

struct reserved_mem_ops {
	int (*device_init)(struct reserved_mem *, struct device *);
	void (*device_release)(struct reserved_mem *, struct device *);
};

typedef int (*reservedmem_of_init_fn)(struct reserved_mem *);

struct io_tlb_area {
	long unsigned int used;
	unsigned int index;
	spinlock_t lock;
};

struct io_tlb_slot {
	phys_addr_t orig_addr;
	size_t alloc_size;
	unsigned int list;
};

struct trace_event_raw_swiotlb_bounced {
	struct trace_entry ent;
	u32 __data_loc_dev_name;
	u64 dma_mask;
	dma_addr_t dev_addr;
	size_t size;
	bool force;
	char __data[0];
};

struct trace_event_data_offsets_swiotlb_bounced {
	u32 dev_name;
};

typedef void (*btf_trace_swiotlb_bounced)(void *, struct device *, dma_addr_t, size_t);

enum kcmp_type {
	KCMP_FILE = 0,
	KCMP_VM = 1,
	KCMP_FILES = 2,
	KCMP_FS = 3,
	KCMP_SIGHAND = 4,
	KCMP_IO = 5,
	KCMP_SYSVSEM = 6,
	KCMP_EPOLL_TFD = 7,
	KCMP_TYPES = 8,
};

struct kcmp_epoll_slot {
	__u32 efd;
	__u32 tfd;
	__u32 toff;
};

struct profile_hit {
	u32 pc;
	u32 hits;
};

struct stacktrace_cookie {
	long unsigned int *store;
	unsigned int size;
	unsigned int skip;
	unsigned int len;
};

typedef __kernel_long_t __kernel_suseconds_t;

typedef __kernel_long_t __kernel_old_time_t;

typedef __kernel_suseconds_t suseconds_t;

typedef __u64 timeu64_t;

struct __kernel_itimerspec {
	struct __kernel_timespec it_interval;
	struct __kernel_timespec it_value;
};

struct itimerspec64 {
	struct timespec64 it_interval;
	struct timespec64 it_value;
};

struct old_timeval32 {
	old_time32_t tv_sec;
	s32 tv_usec;
};

struct old_itimerspec32 {
	struct old_timespec32 it_interval;
	struct old_timespec32 it_value;
};

struct old_timex32 {
	u32 modes;
	s32 offset;
	s32 freq;
	s32 maxerror;
	s32 esterror;
	s32 status;
	s32 constant;
	s32 precision;
	s32 tolerance;
	struct old_timeval32 time;
	s32 tick;
	s32 ppsfreq;
	s32 jitter;
	s32 shift;
	s32 stabil;
	s32 jitcnt;
	s32 calcnt;
	s32 errcnt;
	s32 stbcnt;
	s32 tai;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct __kernel_timex_timeval {
	__kernel_time64_t tv_sec;
	long long int tv_usec;
};

struct __kernel_timex {
	unsigned int modes;
	long long int offset;
	long long int freq;
	long long int maxerror;
	long long int esterror;
	int status;
	long long int constant;
	long long int precision;
	long long int tolerance;
	struct __kernel_timex_timeval time;
	long long int tick;
	long long int ppsfreq;
	long long int jitter;
	int shift;
	long long int stabil;
	long long int jitcnt;
	long long int calcnt;
	long long int errcnt;
	long long int stbcnt;
	int tai;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct trace_event_raw_timer_class {
	struct trace_entry ent;
	void *timer;
	char __data[0];
};

struct trace_event_raw_timer_start {
	struct trace_entry ent;
	void *timer;
	void *function;
	long unsigned int expires;
	long unsigned int now;
	unsigned int flags;
	char __data[0];
};

struct trace_event_raw_timer_expire_entry {
	struct trace_entry ent;
	void *timer;
	long unsigned int now;
	void *function;
	long unsigned int baseclk;
	char __data[0];
};

struct trace_event_raw_hrtimer_init {
	struct trace_entry ent;
	void *hrtimer;
	clockid_t clockid;
	enum hrtimer_mode mode;
	char __data[0];
};

struct trace_event_raw_hrtimer_start {
	struct trace_entry ent;
	void *hrtimer;
	void *function;
	s64 expires;
	s64 softexpires;
	enum hrtimer_mode mode;
	char __data[0];
};

struct trace_event_raw_hrtimer_expire_entry {
	struct trace_entry ent;
	void *hrtimer;
	s64 now;
	void *function;
	char __data[0];
};

struct trace_event_raw_hrtimer_class {
	struct trace_entry ent;
	void *hrtimer;
	char __data[0];
};

struct trace_event_raw_itimer_state {
	struct trace_entry ent;
	int which;
	long long unsigned int expires;
	long int value_sec;
	long int value_nsec;
	long int interval_sec;
	long int interval_nsec;
	char __data[0];
};

struct trace_event_raw_itimer_expire {
	struct trace_entry ent;
	int which;
	pid_t pid;
	long long unsigned int now;
	char __data[0];
};

struct trace_event_raw_tick_stop {
	struct trace_entry ent;
	int success;
	int dependency;
	char __data[0];
};

struct trace_event_data_offsets_timer_class {};

struct trace_event_data_offsets_timer_start {};

struct trace_event_data_offsets_timer_expire_entry {};

struct trace_event_data_offsets_hrtimer_init {};

struct trace_event_data_offsets_hrtimer_start {};

struct trace_event_data_offsets_hrtimer_expire_entry {};

struct trace_event_data_offsets_hrtimer_class {};

struct trace_event_data_offsets_itimer_state {};

struct trace_event_data_offsets_itimer_expire {};

struct trace_event_data_offsets_tick_stop {};

typedef void (*btf_trace_timer_init)(void *, struct timer_list *);

typedef void (*btf_trace_timer_start)(void *, struct timer_list *, long unsigned int, unsigned int);

typedef void (*btf_trace_timer_expire_entry)(void *, struct timer_list *, long unsigned int);

typedef void (*btf_trace_timer_expire_exit)(void *, struct timer_list *);

typedef void (*btf_trace_timer_cancel)(void *, struct timer_list *);

typedef void (*btf_trace_hrtimer_init)(void *, struct hrtimer *, clockid_t, enum hrtimer_mode);

typedef void (*btf_trace_hrtimer_start)(void *, struct hrtimer *, enum hrtimer_mode);

typedef void (*btf_trace_hrtimer_expire_entry)(void *, struct hrtimer *, ktime_t *);

typedef void (*btf_trace_hrtimer_expire_exit)(void *, struct hrtimer *);

typedef void (*btf_trace_hrtimer_cancel)(void *, struct hrtimer *);

typedef void (*btf_trace_itimer_state)(void *, int, const struct itimerspec64 * const, long long unsigned int);

typedef void (*btf_trace_itimer_expire)(void *, int, struct pid *, long long unsigned int);

typedef void (*btf_trace_tick_stop)(void *, int, int);

struct timer_base {
	raw_spinlock_t lock;
	struct timer_list *running_timer;
	long unsigned int clk;
	long unsigned int next_expiry;
	unsigned int cpu;
	bool next_expiry_recalc;
	bool is_idle;
	bool timers_pending;
	long unsigned int pending_map[8];
	struct hlist_head vectors[512];
	long: 64;
	long: 64;
	long: 64;
};

struct process_timer {
	struct timer_list timer;
	struct task_struct *task;
};

enum tick_device_mode {
	TICKDEV_MODE_PERIODIC = 0,
	TICKDEV_MODE_ONESHOT = 1,
};

struct tick_device {
	struct clock_event_device *evtdev;
	enum tick_device_mode mode;
};

struct ktime_timestamps {
	u64 mono;
	u64 boot;
	u64 real;
};

struct system_time_snapshot {
	u64 cycles;
	ktime_t real;
	ktime_t raw;
	enum clocksource_ids cs_id;
	unsigned int clock_was_set_seq;
	u8 cs_was_changed_seq;
};

struct system_device_crosststamp {
	ktime_t device;
	ktime_t sys_realtime;
	ktime_t sys_monoraw;
};

struct system_counterval_t {
	u64 cycles;
	struct clocksource *cs;
};

struct tk_read_base {
	struct clocksource *clock;
	u64 mask;
	u64 cycle_last;
	u32 mult;
	u32 shift;
	u64 xtime_nsec;
	ktime_t base;
	u64 base_real;
};

struct timekeeper {
	struct tk_read_base tkr_mono;
	struct tk_read_base tkr_raw;
	u64 xtime_sec;
	long unsigned int ktime_sec;
	struct timespec64 wall_to_monotonic;
	ktime_t offs_real;
	ktime_t offs_boot;
	ktime_t offs_tai;
	s32 tai_offset;
	unsigned int clock_was_set_seq;
	u8 cs_was_changed_seq;
	ktime_t next_leap_ktime;
	u64 raw_sec;
	struct timespec64 monotonic_to_boot;
	u64 cycle_interval;
	u64 xtime_interval;
	s64 xtime_remainder;
	u64 raw_interval;
	u64 ntp_tick;
	s64 ntp_error;
	u32 ntp_error_shift;
	u32 ntp_err_mult;
	u32 skip_second_overflow;
};

struct audit_ntp_val {
	long long int oldval;
	long long int newval;
};

struct audit_ntp_data {
	struct audit_ntp_val vals[6];
};

enum timekeeping_adv_mode {
	TK_ADV_TICK = 0,
	TK_ADV_FREQ = 1,
};

struct tk_fast {
	seqcount_latch_t seq;
	struct tk_read_base base[2];
};

struct rtc_device;

struct rtc_timer {
	struct timerqueue_node node;
	ktime_t period;
	void (*func)(struct rtc_device *);
	struct rtc_device *rtc;
	int enabled;
};

struct rtc_device {
	struct device dev;
	struct module *owner;
	int id;
	const struct rtc_class_ops *ops;
	struct mutex ops_lock;
	struct cdev char_dev;
	long unsigned int flags;
	long unsigned int irq_data;
	spinlock_t irq_lock;
	wait_queue_head_t irq_queue;
	struct fasync_struct *async_queue;
	int irq_freq;
	int max_user_freq;
	struct timerqueue_head timerqueue;
	struct rtc_timer aie_timer;
	struct rtc_timer uie_rtctimer;
	struct hrtimer pie_timer;
	int pie_enabled;
	struct work_struct irqwork;
	long unsigned int set_offset_nsec;
	long unsigned int features[1];
	time64_t range_min;
	timeu64_t range_max;
	time64_t start_secs;
	time64_t offset_secs;
	bool set_start_time;
};

enum tick_nohz_mode {
	NOHZ_MODE_INACTIVE = 0,
	NOHZ_MODE_LOWRES = 1,
	NOHZ_MODE_HIGHRES = 2,
};

struct tick_sched {
	struct hrtimer sched_timer;
	long unsigned int check_clocks;
	enum tick_nohz_mode nohz_mode;
	unsigned int inidle: 1;
	unsigned int tick_stopped: 1;
	unsigned int idle_active: 1;
	unsigned int do_timer_last: 1;
	unsigned int got_idle_tick: 1;
	ktime_t last_tick;
	ktime_t next_tick;
	long unsigned int idle_jiffies;
	long unsigned int idle_calls;
	long unsigned int idle_sleeps;
	ktime_t idle_entrytime;
	ktime_t idle_waketime;
	ktime_t idle_exittime;
	ktime_t idle_sleeptime;
	ktime_t iowait_sleeptime;
	long unsigned int last_jiffies;
	u64 timer_expires;
	u64 timer_expires_base;
	u64 next_timer;
	ktime_t idle_expires;
	atomic_t tick_dep_mask;
	long unsigned int last_tick_jiffies;
	unsigned int stalled_jiffies;
};

struct timer_list_iter {
	int cpu;
	bool second_pass;
	u64 now;
};

struct tm {
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	long int tm_year;
	int tm_wday;
	int tm_yday;
};

struct cyclecounter {
	u64 (*read)(const struct cyclecounter *);
	u64 mask;
	u32 mult;
	u32 shift;
};

struct timecounter {
	const struct cyclecounter *cc;
	u64 cycle_last;
	u64 nsec;
	u64 mask;
	u64 frac;
};

typedef __kernel_timer_t timer_t;

enum alarmtimer_type {
	ALARM_REALTIME = 0,
	ALARM_BOOTTIME = 1,
	ALARM_NUMTYPE = 2,
	ALARM_REALTIME_FREEZER = 3,
	ALARM_BOOTTIME_FREEZER = 4,
};

enum alarmtimer_restart {
	ALARMTIMER_NORESTART = 0,
	ALARMTIMER_RESTART = 1,
};

struct alarm {
	struct timerqueue_node node;
	struct hrtimer timer;
	enum alarmtimer_restart (*function)(struct alarm *, ktime_t);
	enum alarmtimer_type type;
	int state;
	void *data;
};

struct cpu_timer {
	struct timerqueue_node node;
	struct timerqueue_head *head;
	struct pid *pid;
	struct list_head elist;
	int firing;
};

struct k_clock;

struct k_itimer {
	struct list_head list;
	struct hlist_node t_hash;
	spinlock_t it_lock;
	const struct k_clock *kclock;
	clockid_t it_clock;
	timer_t it_id;
	int it_active;
	s64 it_overrun;
	s64 it_overrun_last;
	int it_requeue_pending;
	int it_sigev_notify;
	ktime_t it_interval;
	struct signal_struct *it_signal;
	union {
		struct pid *it_pid;
		struct task_struct *it_process;
	};
	struct sigqueue *sigq;
	union {
		struct {
			struct hrtimer timer;
		} real;
		struct cpu_timer cpu;
		struct {
			struct alarm alarmtimer;
		} alarm;
	} it;
	struct callback_head rcu;
};

struct k_clock {
	int (*clock_getres)(const clockid_t, struct timespec64 *);
	int (*clock_set)(const clockid_t, const struct timespec64 *);
	int (*clock_get_timespec)(const clockid_t, struct timespec64 *);
	ktime_t (*clock_get_ktime)(const clockid_t);
	int (*clock_adj)(const clockid_t, struct __kernel_timex *);
	int (*timer_create)(struct k_itimer *);
	int (*nsleep)(const clockid_t, int, const struct timespec64 *);
	int (*timer_set)(struct k_itimer *, int, struct itimerspec64 *, struct itimerspec64 *);
	int (*timer_del)(struct k_itimer *);
	void (*timer_get)(struct k_itimer *, struct itimerspec64 *);
	void (*timer_rearm)(struct k_itimer *);
	s64 (*timer_forward)(struct k_itimer *, ktime_t);
	ktime_t (*timer_remaining)(struct k_itimer *, ktime_t);
	int (*timer_try_to_cancel)(struct k_itimer *);
	void (*timer_arm)(struct k_itimer *, ktime_t, bool, bool);
	void (*timer_wait_running)(struct k_itimer *);
};

struct class_interface {
	struct list_head node;
	struct class *class;
	int (*add_dev)(struct device *, struct class_interface *);
	void (*remove_dev)(struct device *, struct class_interface *);
};

struct trace_event_raw_alarmtimer_suspend {
	struct trace_entry ent;
	s64 expires;
	unsigned char alarm_type;
	char __data[0];
};

struct trace_event_raw_alarm_class {
	struct trace_entry ent;
	void *alarm;
	unsigned char alarm_type;
	s64 expires;
	s64 now;
	char __data[0];
};

struct trace_event_data_offsets_alarmtimer_suspend {};

struct trace_event_data_offsets_alarm_class {};

typedef void (*btf_trace_alarmtimer_suspend)(void *, ktime_t, int);

typedef void (*btf_trace_alarmtimer_fired)(void *, struct alarm *, ktime_t);

typedef void (*btf_trace_alarmtimer_start)(void *, struct alarm *, ktime_t);

typedef void (*btf_trace_alarmtimer_cancel)(void *, struct alarm *, ktime_t);

struct alarm_base {
	spinlock_t lock;
	struct timerqueue_head timerqueue;
	ktime_t (*get_ktime)();
	void (*get_timespec)(struct timespec64 *);
	clockid_t base_clockid;
};

struct sigevent {
	sigval_t sigev_value;
	int sigev_signo;
	int sigev_notify;
	union {
		int _pad[12];
		int _tid;
		struct {
			void (*_function)(sigval_t);
			void *_attribute;
		} _sigev_thread;
	} _sigev_un;
};

typedef struct sigevent sigevent_t;

struct posix_clock;

struct posix_clock_operations {
	struct module *owner;
	int (*clock_adjtime)(struct posix_clock *, struct __kernel_timex *);
	int (*clock_gettime)(struct posix_clock *, struct timespec64 *);
	int (*clock_getres)(struct posix_clock *, struct timespec64 *);
	int (*clock_settime)(struct posix_clock *, const struct timespec64 *);
	long int (*ioctl)(struct posix_clock *, unsigned int, long unsigned int);
	int (*open)(struct posix_clock *, fmode_t);
	__poll_t (*poll)(struct posix_clock *, struct file *, poll_table *);
	int (*release)(struct posix_clock *);
	ssize_t (*read)(struct posix_clock *, uint, char *, size_t);
};

struct posix_clock {
	struct posix_clock_operations ops;
	struct cdev cdev;
	struct device *dev;
	struct rw_semaphore rwsem;
	bool zombie;
};

struct posix_clock_desc {
	struct file *fp;
	struct posix_clock *clk;
};

struct __kernel_old_itimerval {
	struct __kernel_old_timeval it_interval;
	struct __kernel_old_timeval it_value;
};

struct ce_unbind {
	struct clock_event_device *ce;
	int res;
};

enum tick_broadcast_state {
	TICK_BROADCAST_EXIT = 0,
	TICK_BROADCAST_ENTER = 1,
};

enum tick_broadcast_mode {
	TICK_BROADCAST_OFF = 0,
	TICK_BROADCAST_ON = 1,
	TICK_BROADCAST_FORCE = 2,
};

struct proc_timens_offset {
	int clockid;
	struct timespec64 val;
};

union futex_key {
	struct {
		u64 i_seq;
		long unsigned int pgoff;
		unsigned int offset;
	} shared;
	struct {
		union {
			struct mm_struct *mm;
			u64 __tmp;
		};
		long unsigned int address;
		unsigned int offset;
	} private;
	struct {
		u64 ptr;
		long unsigned int word;
		unsigned int offset;
	} both;
};

struct futex_pi_state {
	struct list_head list;
	struct rt_mutex_base pi_mutex;
	struct task_struct *owner;
	refcount_t refcount;
	union futex_key key;
};

struct futex_hash_bucket {
	atomic_t waiters;
	spinlock_t lock;
	struct plist_head chain;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct futex_q {
	struct plist_node list;
	struct task_struct *task;
	spinlock_t *lock_ptr;
	union futex_key key;
	struct futex_pi_state *pi_state;
	struct rt_mutex_waiter *rt_waiter;
	union futex_key *requeue_pi_key;
	u32 bitset;
	atomic_t requeue_state;
};

enum futex_access {
	FUTEX_READ = 0,
	FUTEX_WRITE = 1,
};

struct futex_waitv {
	__u64 val;
	__u64 uaddr;
	__u32 flags;
	__u32 __reserved;
};

struct futex_vector {
	struct futex_waitv w;
	struct futex_q q;
};

enum {
	Q_REQUEUE_PI_NONE = 0,
	Q_REQUEUE_PI_IGNORE = 1,
	Q_REQUEUE_PI_IN_PROGRESS = 2,
	Q_REQUEUE_PI_WAIT = 3,
	Q_REQUEUE_PI_DONE = 4,
	Q_REQUEUE_PI_LOCKED = 5,
};

struct dma_chan {
	int lock;
	const char *device_id;
};

struct cfd_percpu {
	call_single_data_t csd;
};

struct call_function_data {
	struct cfd_percpu *pcpu;
	cpumask_var_t cpumask;
	cpumask_var_t cpumask_ipi;
};

struct smp_call_on_cpu_struct {
	struct work_struct work;
	struct completion done;
	int (*func)(void *);
	void *data;
	int ret;
	int cpu;
};

struct latch_tree_root {
	seqcount_latch_t seq;
	struct rb_root tree[2];
};

struct latch_tree_ops {
	bool (*less)(struct latch_tree_node *, struct latch_tree_node *);
	int (*comp)(void *, struct latch_tree_node *);
};

struct module_use {
	struct list_head source_list;
	struct list_head target_list;
	struct module *source;
	struct module *target;
};

struct module_sect_attr {
	struct bin_attribute battr;
	long unsigned int address;
};

struct module_sect_attrs {
	struct attribute_group grp;
	unsigned int nsections;
	struct module_sect_attr attrs[0];
};

struct module_notes_attrs {
	struct kobject *dir;
	unsigned int notes;
	struct bin_attribute attrs[0];
};

enum kernel_read_file_id {
	READING_UNKNOWN = 0,
	READING_FIRMWARE = 1,
	READING_MODULE = 2,
	READING_KEXEC_IMAGE = 3,
	READING_KEXEC_INITRAMFS = 4,
	READING_POLICY = 5,
	READING_X509_CERTIFICATE = 6,
	READING_MAX_ID = 7,
};

enum kernel_load_data_id {
	LOADING_UNKNOWN = 0,
	LOADING_FIRMWARE = 1,
	LOADING_MODULE = 2,
	LOADING_KEXEC_IMAGE = 3,
	LOADING_KEXEC_INITRAMFS = 4,
	LOADING_POLICY = 5,
	LOADING_X509_CERTIFICATE = 6,
	LOADING_MAX_ID = 7,
};

enum {
	PROC_ENTRY_PERMANENT = 1,
};

struct load_info {
	const char *name;
	struct module *mod;
	Elf64_Ehdr *hdr;
	long unsigned int len;
	Elf64_Shdr *sechdrs;
	char *secstrings;
	char *strtab;
	long unsigned int symoffs;
	long unsigned int stroffs;
	long unsigned int init_typeoffs;
	long unsigned int core_typeoffs;
	struct _ddebug *debug;
	unsigned int num_debug;
	bool sig_ok;
	long unsigned int mod_kallsyms_init_off;
	struct {
		unsigned int sym;
		unsigned int str;
		unsigned int mod;
		unsigned int vers;
		unsigned int info;
		unsigned int pcpu;
	} index;
};

struct trace_event_raw_module_load {
	struct trace_entry ent;
	unsigned int taints;
	u32 __data_loc_name;
	char __data[0];
};

struct trace_event_raw_module_free {
	struct trace_entry ent;
	u32 __data_loc_name;
	char __data[0];
};

struct trace_event_raw_module_refcnt {
	struct trace_entry ent;
	long unsigned int ip;
	int refcnt;
	u32 __data_loc_name;
	char __data[0];
};

struct trace_event_raw_module_request {
	struct trace_entry ent;
	long unsigned int ip;
	bool wait;
	u32 __data_loc_name;
	char __data[0];
};

struct trace_event_data_offsets_module_load {
	u32 name;
};

struct trace_event_data_offsets_module_free {
	u32 name;
};

struct trace_event_data_offsets_module_refcnt {
	u32 name;
};

struct trace_event_data_offsets_module_request {
	u32 name;
};

typedef void (*btf_trace_module_load)(void *, struct module *);

typedef void (*btf_trace_module_free)(void *, struct module *);

typedef void (*btf_trace_module_get)(void *, struct module *, long unsigned int);

typedef void (*btf_trace_module_put)(void *, struct module *, long unsigned int);

typedef void (*btf_trace_module_request)(void *, char *, bool, long unsigned int);

struct mod_tree_root {
	struct latch_tree_root root;
	long unsigned int addr_min;
	long unsigned int addr_max;
};

enum mod_license {
	NOT_GPL_ONLY = 0,
	GPL_ONLY = 1,
};

struct symsearch {
	const struct kernel_symbol *start;
	const struct kernel_symbol *stop;
	const s32 *crcs;
	enum mod_license license;
};

struct find_symbol_arg {
	const char *name;
	bool gplok;
	bool warn;
	struct module *owner;
	const s32 *crc;
	const struct kernel_symbol *sym;
	enum mod_license license;
};

struct mod_initfree {
	struct llist_node node;
	void *module_init;
};

struct module_signature {
	u8 algo;
	u8 hash;
	u8 id_type;
	u8 signer_len;
	u8 key_id_len;
	u8 __pad[3];
	__be32 sig_len;
};

enum pkey_id_type {
	PKEY_ID_PGP = 0,
	PKEY_ID_X509 = 1,
	PKEY_ID_PKCS7 = 2,
};

struct kallsym_iter {
	loff_t pos;
	loff_t pos_arch_end;
	loff_t pos_mod_end;
	loff_t pos_ftrace_mod_end;
	loff_t pos_bpf_end;
	long unsigned int value;
	unsigned int nameoff;
	char type;
	char name[128];
	char module_name[56];
	int exported;
	int show_value;
};

typedef struct {
	int val[2];
} __kernel_fsid_t;

struct kstatfs {
	long int f_type;
	long int f_bsize;
	u64 f_blocks;
	u64 f_bfree;
	u64 f_bavail;
	u64 f_files;
	u64 f_ffree;
	__kernel_fsid_t f_fsid;
	long int f_namelen;
	long int f_frsize;
	long int f_flags;
	long int f_spare[4];
};

typedef __u16 comp_t;

struct acct_v3 {
	char ac_flag;
	char ac_version;
	__u16 ac_tty;
	__u32 ac_exitcode;
	__u32 ac_uid;
	__u32 ac_gid;
	__u32 ac_pid;
	__u32 ac_ppid;
	__u32 ac_btime;
	__u32 ac_etime;
	comp_t ac_utime;
	comp_t ac_stime;
	comp_t ac_mem;
	comp_t ac_io;
	comp_t ac_rw;
	comp_t ac_minflt;
	comp_t ac_majflt;
	comp_t ac_swaps;
	char ac_comm[16];
};

typedef struct acct_v3 acct_t;

struct fs_pin {
	wait_queue_head_t wait;
	int done;
	struct hlist_node s_list;
	struct hlist_node m_list;
	void (*kill)(struct fs_pin *);
};

struct bsd_acct_struct {
	struct fs_pin pin;
	atomic_long_t count;
	struct callback_head rcu;
	struct mutex lock;
	int active;
	long unsigned int needcheck;
	struct file *file;
	struct pid_namespace *ns;
	struct work_struct work;
	struct completion done;
};

struct elf64_note {
	Elf64_Word n_namesz;
	Elf64_Word n_descsz;
	Elf64_Word n_type;
};

typedef u32 note_buf_t[134];

struct crypto_alg;

struct crypto_tfm {
	u32 crt_flags;
	int node;
	void (*exit)(struct crypto_tfm *);
	struct crypto_alg *__crt_alg;
	void *__crt_ctx[0];
};

struct cipher_alg {
	unsigned int cia_min_keysize;
	unsigned int cia_max_keysize;
	int (*cia_setkey)(struct crypto_tfm *, const u8 *, unsigned int);
	void (*cia_encrypt)(struct crypto_tfm *, u8 *, const u8 *);
	void (*cia_decrypt)(struct crypto_tfm *, u8 *, const u8 *);
};

struct compress_alg {
	int (*coa_compress)(struct crypto_tfm *, const u8 *, unsigned int, u8 *, unsigned int *);
	int (*coa_decompress)(struct crypto_tfm *, const u8 *, unsigned int, u8 *, unsigned int *);
};

struct crypto_istat_aead {
	atomic64_t encrypt_cnt;
	atomic64_t encrypt_tlen;
	atomic64_t decrypt_cnt;
	atomic64_t decrypt_tlen;
	atomic64_t err_cnt;
};

struct crypto_istat_akcipher {
	atomic64_t encrypt_cnt;
	atomic64_t encrypt_tlen;
	atomic64_t decrypt_cnt;
	atomic64_t decrypt_tlen;
	atomic64_t verify_cnt;
	atomic64_t sign_cnt;
	atomic64_t err_cnt;
};

struct crypto_istat_cipher {
	atomic64_t encrypt_cnt;
	atomic64_t encrypt_tlen;
	atomic64_t decrypt_cnt;
	atomic64_t decrypt_tlen;
	atomic64_t err_cnt;
};

struct crypto_istat_compress {
	atomic64_t compress_cnt;
	atomic64_t compress_tlen;
	atomic64_t decompress_cnt;
	atomic64_t decompress_tlen;
	atomic64_t err_cnt;
};

struct crypto_istat_hash {
	atomic64_t hash_cnt;
	atomic64_t hash_tlen;
	atomic64_t err_cnt;
};

struct crypto_istat_kpp {
	atomic64_t setsecret_cnt;
	atomic64_t generate_public_key_cnt;
	atomic64_t compute_shared_secret_cnt;
	atomic64_t err_cnt;
};

struct crypto_istat_rng {
	atomic64_t generate_cnt;
	atomic64_t generate_tlen;
	atomic64_t seed_cnt;
	atomic64_t err_cnt;
};

struct crypto_type;

struct crypto_alg {
	struct list_head cra_list;
	struct list_head cra_users;
	u32 cra_flags;
	unsigned int cra_blocksize;
	unsigned int cra_ctxsize;
	unsigned int cra_alignmask;
	int cra_priority;
	refcount_t cra_refcnt;
	char cra_name[128];
	char cra_driver_name[128];
	const struct crypto_type *cra_type;
	union {
		struct cipher_alg cipher;
		struct compress_alg compress;
	} cra_u;
	int (*cra_init)(struct crypto_tfm *);
	void (*cra_exit)(struct crypto_tfm *);
	void (*cra_destroy)(struct crypto_alg *);
	struct module *cra_module;
	union {
		struct crypto_istat_aead aead;
		struct crypto_istat_akcipher akcipher;
		struct crypto_istat_cipher cipher;
		struct crypto_istat_compress compress;
		struct crypto_istat_hash hash;
		struct crypto_istat_rng rng;
		struct crypto_istat_kpp kpp;
	} stats;
};

struct crypto_instance;

struct crypto_type {
	unsigned int (*ctxsize)(struct crypto_alg *, u32, u32);
	unsigned int (*extsize)(struct crypto_alg *);
	int (*init)(struct crypto_tfm *, u32, u32);
	int (*init_tfm)(struct crypto_tfm *);
	void (*show)(struct seq_file *, struct crypto_alg *);
	int (*report)(struct sk_buff *, struct crypto_alg *);
	void (*free)(struct crypto_instance *);
	unsigned int type;
	unsigned int maskclear;
	unsigned int maskset;
	unsigned int tfmsize;
};

struct crypto_shash;

struct shash_desc {
	struct crypto_shash *tfm;
	void *__ctx[0];
};

struct crypto_shash {
	unsigned int descsize;
	struct crypto_tfm base;
};

struct shash_alg {
	int (*init)(struct shash_desc *);
	int (*update)(struct shash_desc *, const u8 *, unsigned int);
	int (*final)(struct shash_desc *, u8 *);
	int (*finup)(struct shash_desc *, const u8 *, unsigned int, u8 *);
	int (*digest)(struct shash_desc *, const u8 *, unsigned int, u8 *);
	int (*export)(struct shash_desc *, void *);
	int (*import)(struct shash_desc *, const void *);
	int (*setkey)(struct crypto_shash *, const u8 *, unsigned int);
	int (*init_tfm)(struct crypto_shash *);
	void (*exit_tfm)(struct crypto_shash *);
	unsigned int descsize;
	int: 32;
	unsigned int digestsize;
	unsigned int statesize;
	struct crypto_alg base;
};

struct kexec_sha_region {
	long unsigned int start;
	long unsigned int len;
};

typedef __u64 __le64;

typedef __kernel_ulong_t ino_t;

enum kernfs_node_type {
	KERNFS_DIR = 1,
	KERNFS_FILE = 2,
	KERNFS_LINK = 4,
};

enum kernfs_root_flag {
	KERNFS_ROOT_CREATE_DEACTIVATED = 1,
	KERNFS_ROOT_EXTRA_OPEN_PERM_CHECK = 2,
	KERNFS_ROOT_SUPPORT_EXPORTOP = 4,
	KERNFS_ROOT_SUPPORT_USER_XATTR = 8,
};

struct kernfs_fs_context {
	struct kernfs_root *root;
	void *ns_tag;
	long unsigned int magic;
	bool new_sb_created;
};

enum {
	CGRP_NOTIFY_ON_RELEASE = 0,
	CGRP_CPUSET_CLONE_CHILDREN = 1,
	CGRP_FREEZE = 2,
	CGRP_FROZEN = 3,
	CGRP_KILL = 4,
};

enum {
	CGRP_ROOT_NOPREFIX = 2,
	CGRP_ROOT_XATTR = 4,
	CGRP_ROOT_NS_DELEGATE = 8,
	CGRP_ROOT_CPUSET_V2_MODE = 16,
	CGRP_ROOT_MEMORY_LOCAL_EVENTS = 32,
	CGRP_ROOT_MEMORY_RECURSIVE_PROT = 64,
};

struct cgroup_taskset {
	struct list_head src_csets;
	struct list_head dst_csets;
	int nr_tasks;
	int ssid;
	struct list_head *csets;
	struct css_set *cur_cset;
	struct task_struct *cur_task;
};

struct css_task_iter {
	struct cgroup_subsys *ss;
	unsigned int flags;
	struct list_head *cset_pos;
	struct list_head *cset_head;
	struct list_head *tcset_pos;
	struct list_head *tcset_head;
	struct list_head *task_pos;
	struct list_head *cur_tasks_head;
	struct css_set *cur_cset;
	struct css_set *cur_dcset;
	struct task_struct *cur_task;
	struct list_head iters_node;
};

struct cgroup_fs_context {
	struct kernfs_fs_context kfc;
	struct cgroup_root *root;
	struct cgroup_namespace *ns;
	unsigned int flags;
	bool cpuset_clone_children;
	bool none;
	bool all_ss;
	u16 subsys_mask;
	char *name;
	char *release_agent;
};

struct cgroup_pidlist;

struct cgroup_file_ctx {
	struct cgroup_namespace *ns;
	struct {
		void *trigger;
	} psi;
	struct {
		bool started;
		struct css_task_iter iter;
	} procs;
	struct {
		struct cgroup_pidlist *pidlist;
	} procs1;
};

struct cgrp_cset_link {
	struct cgroup *cgrp;
	struct css_set *cset;
	struct list_head cset_link;
	struct list_head cgrp_link;
};

struct cgroup_mgctx {
	struct list_head preloaded_src_csets;
	struct list_head preloaded_dst_csets;
	struct cgroup_taskset tset;
	u16 ss_mask;
};

struct bpf_cgroup_storage_key {
	__u64 cgroup_inode_id;
	__u32 attach_type;
};

struct bpf_storage_buffer;

struct bpf_cgroup_storage_map;

struct bpf_cgroup_storage {
	union {
		struct bpf_storage_buffer *buf;
		void *percpu_buf;
	};
	struct bpf_cgroup_storage_map *map;
	struct bpf_cgroup_storage_key key;
	struct list_head list_map;
	struct list_head list_cg;
	struct rb_node node;
	struct callback_head rcu;
};

struct bpf_storage_buffer {
	struct callback_head rcu;
	char data[0];
};

struct trace_event_raw_cgroup_root {
	struct trace_entry ent;
	int root;
	u16 ss_mask;
	u32 __data_loc_name;
	char __data[0];
};

struct trace_event_raw_cgroup {
	struct trace_entry ent;
	int root;
	int id;
	int level;
	u32 __data_loc_path;
	char __data[0];
};

struct trace_event_raw_cgroup_migrate {
	struct trace_entry ent;
	int dst_root;
	int dst_id;
	int dst_level;
	int pid;
	u32 __data_loc_dst_path;
	u32 __data_loc_comm;
	char __data[0];
};

struct trace_event_raw_cgroup_event {
	struct trace_entry ent;
	int root;
	int id;
	int level;
	u32 __data_loc_path;
	int val;
	char __data[0];
};

struct trace_event_data_offsets_cgroup_root {
	u32 name;
};

struct trace_event_data_offsets_cgroup {
	u32 path;
};

struct trace_event_data_offsets_cgroup_migrate {
	u32 dst_path;
	u32 comm;
};

struct trace_event_data_offsets_cgroup_event {
	u32 path;
};

typedef void (*btf_trace_cgroup_setup_root)(void *, struct cgroup_root *);

typedef void (*btf_trace_cgroup_destroy_root)(void *, struct cgroup_root *);

typedef void (*btf_trace_cgroup_remount)(void *, struct cgroup_root *);

typedef void (*btf_trace_cgroup_mkdir)(void *, struct cgroup *, const char *);

typedef void (*btf_trace_cgroup_rmdir)(void *, struct cgroup *, const char *);

typedef void (*btf_trace_cgroup_release)(void *, struct cgroup *, const char *);

typedef void (*btf_trace_cgroup_rename)(void *, struct cgroup *, const char *);

typedef void (*btf_trace_cgroup_freeze)(void *, struct cgroup *, const char *);

typedef void (*btf_trace_cgroup_unfreeze)(void *, struct cgroup *, const char *);

typedef void (*btf_trace_cgroup_attach_task)(void *, struct cgroup *, const char *, struct task_struct *, bool);

typedef void (*btf_trace_cgroup_transfer_tasks)(void *, struct cgroup *, const char *, struct task_struct *, bool);

typedef void (*btf_trace_cgroup_notify_populated)(void *, struct cgroup *, const char *, int);

typedef void (*btf_trace_cgroup_notify_frozen)(void *, struct cgroup *, const char *, int);

enum cgroup_opt_features {
	OPT_FEATURE_PRESSURE = 0,
	OPT_FEATURE_COUNT = 1,
};

enum cgroup2_param {
	Opt_nsdelegate = 0,
	Opt_memory_localevents = 1,
	Opt_memory_recursiveprot = 2,
	nr__cgroup2_params = 3,
};

struct cgroupstats {
	__u64 nr_sleeping;
	__u64 nr_running;
	__u64 nr_stopped;
	__u64 nr_uninterruptible;
	__u64 nr_io_wait;
};

enum cgroup_filetype {
	CGROUP_FILE_PROCS = 0,
	CGROUP_FILE_TASKS = 1,
};

struct cgroup_pidlist {
	struct {
		enum cgroup_filetype type;
		struct pid_namespace *ns;
	} key;
	pid_t *list;
	int length;
	struct list_head links;
	struct cgroup *owner;
	struct delayed_work destroy_dwork;
};

enum cgroup1_param {
	Opt_all = 0,
	Opt_clone_children = 1,
	Opt_cpuset_v2_mode = 2,
	Opt_name = 3,
	Opt_none = 4,
	Opt_noprefix = 5,
	Opt_release_agent = 6,
	Opt_xattr = 7,
};

enum freezer_state_flags {
	CGROUP_FREEZER_ONLINE = 1,
	CGROUP_FREEZING_SELF = 2,
	CGROUP_FREEZING_PARENT = 4,
	CGROUP_FROZEN = 8,
	CGROUP_FREEZING = 6,
};

struct freezer {
	struct cgroup_subsys_state css;
	unsigned int state;
};

struct pids_cgroup {
	struct cgroup_subsys_state css;
	atomic64_t counter;
	atomic64_t limit;
	struct cgroup_file events_file;
	atomic64_t events_limit;
};

typedef struct {
	char *from;
	char *to;
} substring_t;

enum rdmacg_resource_type {
	RDMACG_RESOURCE_HCA_HANDLE = 0,
	RDMACG_RESOURCE_HCA_OBJECT = 1,
	RDMACG_RESOURCE_MAX = 2,
};

struct rdma_cgroup {
	struct cgroup_subsys_state css;
	struct list_head rpools;
};

struct rdmacg_device {
	struct list_head dev_node;
	struct list_head rpools;
	char *name;
};

enum rdmacg_file_type {
	RDMACG_RESOURCE_TYPE_MAX = 0,
	RDMACG_RESOURCE_TYPE_STAT = 1,
};

struct rdmacg_resource {
	int max;
	int usage;
};

struct rdmacg_resource_pool {
	struct rdmacg_device *device;
	struct rdmacg_resource resources[2];
	struct list_head cg_node;
	struct list_head dev_node;
	u64 usage_sum;
	int num_max_cnt;
};

struct root_domain___2;

struct fmeter {
	int cnt;
	int val;
	time64_t time;
	spinlock_t lock;
};

enum prs_errcode {
	PERR_NONE = 0,
	PERR_INVCPUS = 1,
	PERR_INVPARENT = 2,
	PERR_NOTPART = 3,
	PERR_NOTEXCL = 4,
	PERR_NOCPUS = 5,
	PERR_HOTPLUG = 6,
	PERR_CPUSEMPTY = 7,
};

struct cpuset {
	struct cgroup_subsys_state css;
	long unsigned int flags;
	cpumask_var_t cpus_allowed;
	nodemask_t mems_allowed;
	cpumask_var_t effective_cpus;
	nodemask_t effective_mems;
	cpumask_var_t subparts_cpus;
	nodemask_t old_mems_allowed;
	struct fmeter fmeter;
	int attach_in_progress;
	int pn;
	int relax_domain_level;
	int nr_subparts_cpus;
	int partition_root_state;
	int use_parent_ecpus;
	int child_ecpus_count;
	enum prs_errcode prs_err;
	struct cgroup_file partition_file;
};

struct tmpmasks {
	cpumask_var_t addmask;
	cpumask_var_t delmask;
	cpumask_var_t new_cpus;
};

typedef enum {
	CS_ONLINE = 0,
	CS_CPU_EXCLUSIVE = 1,
	CS_MEM_EXCLUSIVE = 2,
	CS_MEM_HARDWALL = 3,
	CS_MEMORY_MIGRATE = 4,
	CS_SCHED_LOAD_BALANCE = 5,
	CS_SPREAD_PAGE = 6,
	CS_SPREAD_SLAB = 7,
} cpuset_flagbits_t;

enum subparts_cmd {
	partcmd_enable = 0,
	partcmd_disable = 1,
	partcmd_update = 2,
	partcmd_invalidate = 3,
};

struct cpuset_migrate_mm_work {
	struct work_struct work;
	struct mm_struct *mm;
	nodemask_t from;
	nodemask_t to;
};

typedef enum {
	FILE_MEMORY_MIGRATE = 0,
	FILE_CPULIST = 1,
	FILE_MEMLIST = 2,
	FILE_EFFECTIVE_CPULIST = 3,
	FILE_EFFECTIVE_MEMLIST = 4,
	FILE_SUBPARTS_CPULIST = 5,
	FILE_CPU_EXCLUSIVE = 6,
	FILE_MEM_EXCLUSIVE = 7,
	FILE_MEM_HARDWALL = 8,
	FILE_SCHED_LOAD_BALANCE = 9,
	FILE_PARTITION_ROOT = 10,
	FILE_SCHED_RELAX_DOMAIN_LEVEL = 11,
	FILE_MEMORY_PRESSURE_ENABLED = 12,
	FILE_MEMORY_PRESSURE = 13,
	FILE_SPREAD_PAGE = 14,
	FILE_SPREAD_SLAB = 15,
} cpuset_filetype_t;

enum misc_res_type {
	MISC_CG_RES_TYPES = 0,
};

struct misc_res {
	long unsigned int max;
	atomic_long_t usage;
	bool failed;
};

struct misc_cg {
	struct cgroup_subsys_state css;
	struct misc_res res[0];
};

struct kernel_pkey_query {
	__u32 supported_ops;
	__u32 key_size;
	__u16 max_data_size;
	__u16 max_sig_size;
	__u16 max_enc_size;
	__u16 max_dec_size;
};

enum kernel_pkey_operation {
	kernel_pkey_encrypt = 0,
	kernel_pkey_decrypt = 1,
	kernel_pkey_sign = 2,
	kernel_pkey_verify = 3,
};

struct kernel_pkey_params {
	struct key *key;
	const char *encoding;
	const char *hash_algo;
	char *info;
	__u32 in_len;
	union {
		__u32 out_len;
		__u32 in2_len;
	};
	enum kernel_pkey_operation op: 8;
};

struct key_preparsed_payload {
	const char *orig_description;
	char *description;
	union key_payload payload;
	const void *data;
	size_t datalen;
	size_t quotalen;
	time64_t expiry;
};

struct key_match_data {
	bool (*cmp)(const struct key *, const struct key_match_data *);
	const void *raw_data;
	void *preparsed;
	unsigned int lookup_type;
};

struct idmap_key {
	bool map_up;
	u32 id;
	u32 count;
};

struct ctl_path {
	const char *procname;
};

struct cpu_stop_done {
	atomic_t nr_todo;
	int ret;
	struct completion completion;
};

struct cpu_stopper {
	struct task_struct *thread;
	raw_spinlock_t lock;
	bool enabled;
	struct list_head works;
	struct cpu_stop_work stop_work;
	long unsigned int caller;
	cpu_stop_fn_t fn;
};

enum multi_stop_state {
	MULTI_STOP_NONE = 0,
	MULTI_STOP_PREPARE = 1,
	MULTI_STOP_DISABLE_IRQ = 2,
	MULTI_STOP_RUN = 3,
	MULTI_STOP_EXIT = 4,
};

struct multi_stop_data {
	cpu_stop_fn_t fn;
	void *data;
	unsigned int num_threads;
	const struct cpumask *active_cpus;
	enum multi_stop_state state;
	atomic_t thread_ack;
};

typedef int __kernel_mqd_t;

typedef __kernel_mqd_t mqd_t;

enum audit_state {
	AUDIT_STATE_DISABLED = 0,
	AUDIT_STATE_BUILD = 1,
	AUDIT_STATE_RECORD = 2,
};

struct audit_cap_data {
	kernel_cap_t permitted;
	kernel_cap_t inheritable;
	union {
		unsigned int fE;
		kernel_cap_t effective;
	};
	kernel_cap_t ambient;
	kuid_t rootid;
};

struct audit_names {
	struct list_head list;
	struct filename *name;
	int name_len;
	bool hidden;
	long unsigned int ino;
	dev_t dev;
	umode_t mode;
	kuid_t uid;
	kgid_t gid;
	dev_t rdev;
	u32 osid;
	struct audit_cap_data fcap;
	unsigned int fcap_ver;
	unsigned char type;
	bool should_free;
};

struct mq_attr {
	__kernel_long_t mq_flags;
	__kernel_long_t mq_maxmsg;
	__kernel_long_t mq_msgsize;
	__kernel_long_t mq_curmsgs;
	__kernel_long_t __reserved[4];
};

struct open_how {
	__u64 flags;
	__u64 mode;
	__u64 resolve;
};

struct audit_proctitle {
	int len;
	char *value;
};

struct audit_aux_data;

struct __kernel_sockaddr_storage;

struct audit_tree_refs;

struct audit_context {
	int dummy;
	enum {
		AUDIT_CTX_UNUSED = 0,
		AUDIT_CTX_SYSCALL = 1,
		AUDIT_CTX_URING = 2,
	} context;
	enum audit_state state;
	enum audit_state current_state;
	unsigned int serial;
	int major;
	int uring_op;
	struct timespec64 ctime;
	long unsigned int argv[4];
	long int return_code;
	u64 prio;
	int return_valid;
	struct audit_names preallocated_names[5];
	int name_count;
	struct list_head names_list;
	char *filterkey;
	struct path pwd;
	struct audit_aux_data *aux;
	struct audit_aux_data *aux_pids;
	struct __kernel_sockaddr_storage *sockaddr;
	size_t sockaddr_len;
	pid_t ppid;
	kuid_t uid;
	kuid_t euid;
	kuid_t suid;
	kuid_t fsuid;
	kgid_t gid;
	kgid_t egid;
	kgid_t sgid;
	kgid_t fsgid;
	long unsigned int personality;
	int arch;
	pid_t target_pid;
	kuid_t target_auid;
	kuid_t target_uid;
	unsigned int target_sessionid;
	u32 target_sid;
	char target_comm[16];
	struct audit_tree_refs *trees;
	struct audit_tree_refs *first_trees;
	struct list_head killed_trees;
	int tree_count;
	int type;
	union {
		struct {
			int nargs;
			long int args[6];
		} socketcall;
		struct {
			kuid_t uid;
			kgid_t gid;
			umode_t mode;
			u32 osid;
			int has_perm;
			uid_t perm_uid;
			gid_t perm_gid;
			umode_t perm_mode;
			long unsigned int qbytes;
		} ipc;
		struct {
			mqd_t mqdes;
			struct mq_attr mqstat;
		} mq_getsetattr;
		struct {
			mqd_t mqdes;
			int sigev_signo;
		} mq_notify;
		struct {
			mqd_t mqdes;
			size_t msg_len;
			unsigned int msg_prio;
			struct timespec64 abs_timeout;
		} mq_sendrecv;
		struct {
			int oflag;
			umode_t mode;
			struct mq_attr attr;
		} mq_open;
		struct {
			pid_t pid;
			struct audit_cap_data cap;
		} capset;
		struct {
			int fd;
			int flags;
		} mmap;
		struct open_how openat2;
		struct {
			int argc;
		} execve;
		struct {
			char *name;
		} module;
		struct {
			struct audit_ntp_data ntp_data;
			struct timespec64 tk_injoffset;
		} time;
	};
	int fds[2];
	struct audit_proctitle proctitle;
};

enum audit_nlgrps {
	AUDIT_NLGRP_NONE = 0,
	AUDIT_NLGRP_READLOG = 1,
	__AUDIT_NLGRP_MAX = 2,
};

struct audit_status {
	__u32 mask;
	__u32 enabled;
	__u32 failure;
	__u32 pid;
	__u32 rate_limit;
	__u32 backlog_limit;
	__u32 lost;
	__u32 backlog;
	union {
		__u32 version;
		__u32 feature_bitmap;
	};
	__u32 backlog_wait_time;
	__u32 backlog_wait_time_actual;
};

struct audit_features {
	__u32 vers;
	__u32 mask;
	__u32 features;
	__u32 lock;
};

struct audit_tty_status {
	__u32 enabled;
	__u32 log_passwd;
};

struct audit_sig_info {
	uid_t uid;
	pid_t pid;
	char ctx[0];
};

struct __kernel_sockaddr_storage {
	union {
		struct {
			__kernel_sa_family_t ss_family;
			char __data[126];
		};
		void *__align;
	};
};

enum skb_drop_reason {
	SKB_NOT_DROPPED_YET = 0,
	SKB_DROP_REASON_NOT_SPECIFIED = 1,
	SKB_DROP_REASON_NO_SOCKET = 2,
	SKB_DROP_REASON_PKT_TOO_SMALL = 3,
	SKB_DROP_REASON_TCP_CSUM = 4,
	SKB_DROP_REASON_SOCKET_FILTER = 5,
	SKB_DROP_REASON_UDP_CSUM = 6,
	SKB_DROP_REASON_NETFILTER_DROP = 7,
	SKB_DROP_REASON_OTHERHOST = 8,
	SKB_DROP_REASON_IP_CSUM = 9,
	SKB_DROP_REASON_IP_INHDR = 10,
	SKB_DROP_REASON_IP_RPFILTER = 11,
	SKB_DROP_REASON_UNICAST_IN_L2_MULTICAST = 12,
	SKB_DROP_REASON_XFRM_POLICY = 13,
	SKB_DROP_REASON_IP_NOPROTO = 14,
	SKB_DROP_REASON_SOCKET_RCVBUFF = 15,
	SKB_DROP_REASON_PROTO_MEM = 16,
	SKB_DROP_REASON_TCP_MD5NOTFOUND = 17,
	SKB_DROP_REASON_TCP_MD5UNEXPECTED = 18,
	SKB_DROP_REASON_TCP_MD5FAILURE = 19,
	SKB_DROP_REASON_SOCKET_BACKLOG = 20,
	SKB_DROP_REASON_TCP_FLAGS = 21,
	SKB_DROP_REASON_TCP_ZEROWINDOW = 22,
	SKB_DROP_REASON_TCP_OLD_DATA = 23,
	SKB_DROP_REASON_TCP_OVERWINDOW = 24,
	SKB_DROP_REASON_TCP_OFOMERGE = 25,
	SKB_DROP_REASON_TCP_RFC7323_PAWS = 26,
	SKB_DROP_REASON_TCP_INVALID_SEQUENCE = 27,
	SKB_DROP_REASON_TCP_RESET = 28,
	SKB_DROP_REASON_TCP_INVALID_SYN = 29,
	SKB_DROP_REASON_TCP_CLOSE = 30,
	SKB_DROP_REASON_TCP_FASTOPEN = 31,
	SKB_DROP_REASON_TCP_OLD_ACK = 32,
	SKB_DROP_REASON_TCP_TOO_OLD_ACK = 33,
	SKB_DROP_REASON_TCP_ACK_UNSENT_DATA = 34,
	SKB_DROP_REASON_TCP_OFO_QUEUE_PRUNE = 35,
	SKB_DROP_REASON_TCP_OFO_DROP = 36,
	SKB_DROP_REASON_IP_OUTNOROUTES = 37,
	SKB_DROP_REASON_BPF_CGROUP_EGRESS = 38,
	SKB_DROP_REASON_IPV6DISABLED = 39,
	SKB_DROP_REASON_NEIGH_CREATEFAIL = 40,
	SKB_DROP_REASON_NEIGH_FAILED = 41,
	SKB_DROP_REASON_NEIGH_QUEUEFULL = 42,
	SKB_DROP_REASON_NEIGH_DEAD = 43,
	SKB_DROP_REASON_TC_EGRESS = 44,
	SKB_DROP_REASON_QDISC_DROP = 45,
	SKB_DROP_REASON_CPU_BACKLOG = 46,
	SKB_DROP_REASON_XDP = 47,
	SKB_DROP_REASON_TC_INGRESS = 48,
	SKB_DROP_REASON_UNHANDLED_PROTO = 49,
	SKB_DROP_REASON_SKB_CSUM = 50,
	SKB_DROP_REASON_SKB_GSO_SEG = 51,
	SKB_DROP_REASON_SKB_UCOPY_FAULT = 52,
	SKB_DROP_REASON_DEV_HDR = 53,
	SKB_DROP_REASON_DEV_READY = 54,
	SKB_DROP_REASON_FULL_RING = 55,
	SKB_DROP_REASON_NOMEM = 56,
	SKB_DROP_REASON_HDR_TRUNC = 57,
	SKB_DROP_REASON_TAP_FILTER = 58,
	SKB_DROP_REASON_TAP_TXFILTER = 59,
	SKB_DROP_REASON_ICMP_CSUM = 60,
	SKB_DROP_REASON_INVALID_PROTO = 61,
	SKB_DROP_REASON_IP_INADDRERRORS = 62,
	SKB_DROP_REASON_IP_INNOROUTES = 63,
	SKB_DROP_REASON_PKT_TOO_BIG = 64,
	SKB_DROP_REASON_MAX = 65,
};

struct net_generic {
	union {
		struct {
			unsigned int len;
			struct callback_head rcu;
		} s;
		void *ptr[0];
	};
};

struct pernet_operations {
	struct list_head list;
	int (*init)(struct net *);
	void (*pre_exit)(struct net *);
	void (*exit)(struct net *);
	void (*exit_batch)(struct list_head *);
	unsigned int *id;
	size_t size;
};

struct scm_creds {
	u32 pid;
	kuid_t uid;
	kgid_t gid;
};

struct netlink_skb_parms {
	struct scm_creds creds;
	__u32 portid;
	__u32 dst_group;
	__u32 flags;
	struct sock *sk;
	bool nsid_is_set;
	int nsid;
};

struct netlink_kernel_cfg {
	unsigned int groups;
	unsigned int flags;
	void (*input)(struct sk_buff *);
	struct mutex *cb_mutex;
	int (*bind)(struct net *, int);
	void (*unbind)(struct net *, int);
	bool (*compare)(struct net *, struct sock *);
};

struct audit_netlink_list {
	__u32 portid;
	struct net *net;
	struct sk_buff_head q;
};

struct audit_net {
	struct sock *sk;
};

struct auditd_connection {
	struct pid *pid;
	u32 portid;
	struct net *net;
	struct callback_head rcu;
};

struct audit_ctl_mutex {
	struct mutex lock;
	void *owner;
};

struct audit_buffer {
	struct sk_buff *skb;
	struct audit_context *ctx;
	gfp_t gfp_mask;
};

struct audit_reply {
	__u32 portid;
	struct net *net;
	struct sk_buff *skb;
};

enum {
	Audit_equal = 0,
	Audit_not_equal = 1,
	Audit_bitmask = 2,
	Audit_bittest = 3,
	Audit_lt = 4,
	Audit_gt = 5,
	Audit_le = 6,
	Audit_ge = 7,
	Audit_bad = 8,
};

struct audit_rule_data {
	__u32 flags;
	__u32 action;
	__u32 field_count;
	__u32 mask[64];
	__u32 fields[64];
	__u32 values[64];
	__u32 fieldflags[64];
	__u32 buflen;
	char buf[0];
};

struct audit_field;

struct audit_watch;

struct audit_tree;

struct audit_fsnotify_mark;

struct audit_krule {
	u32 pflags;
	u32 flags;
	u32 listnr;
	u32 action;
	u32 mask[64];
	u32 buflen;
	u32 field_count;
	char *filterkey;
	struct audit_field *fields;
	struct audit_field *arch_f;
	struct audit_field *inode_f;
	struct audit_watch *watch;
	struct audit_tree *tree;
	struct audit_fsnotify_mark *exe;
	struct list_head rlist;
	struct list_head list;
	u64 prio;
};

struct audit_field {
	u32 type;
	union {
		u32 val;
		kuid_t uid;
		kgid_t gid;
		struct {
			char *lsm_str;
			void *lsm_rule;
		};
	};
	u32 op;
};

struct audit_entry {
	struct list_head list;
	struct callback_head rcu;
	struct audit_krule rule;
};

struct audit_buffer___2;

typedef int __kernel_key_t;

typedef __kernel_key_t key_t;

struct cpu_vfs_cap_data {
	__u32 magic_etc;
	kernel_cap_t permitted;
	kernel_cap_t inheritable;
	kuid_t rootid;
};

struct kern_ipc_perm {
	spinlock_t lock;
	bool deleted;
	int id;
	key_t key;
	kuid_t uid;
	kgid_t gid;
	kuid_t cuid;
	kgid_t cgid;
	umode_t mode;
	long unsigned int seq;
	void *security;
	struct rhash_head khtnode;
	struct callback_head rcu;
	refcount_t refcount;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

typedef struct fsnotify_mark_connector *fsnotify_connp_t;

struct fsnotify_mark_connector {
	spinlock_t lock;
	short unsigned int type;
	short unsigned int flags;
	__kernel_fsid_t fsid;
	union {
		fsnotify_connp_t *obj;
		struct fsnotify_mark_connector *destroy_next;
	};
	struct hlist_head list;
};

enum audit_nfcfgop {
	AUDIT_XT_OP_REGISTER = 0,
	AUDIT_XT_OP_REPLACE = 1,
	AUDIT_XT_OP_UNREGISTER = 2,
	AUDIT_NFT_OP_TABLE_REGISTER = 3,
	AUDIT_NFT_OP_TABLE_UNREGISTER = 4,
	AUDIT_NFT_OP_CHAIN_REGISTER = 5,
	AUDIT_NFT_OP_CHAIN_UNREGISTER = 6,
	AUDIT_NFT_OP_RULE_REGISTER = 7,
	AUDIT_NFT_OP_RULE_UNREGISTER = 8,
	AUDIT_NFT_OP_SET_REGISTER = 9,
	AUDIT_NFT_OP_SET_UNREGISTER = 10,
	AUDIT_NFT_OP_SETELEM_REGISTER = 11,
	AUDIT_NFT_OP_SETELEM_UNREGISTER = 12,
	AUDIT_NFT_OP_GEN_REGISTER = 13,
	AUDIT_NFT_OP_OBJ_REGISTER = 14,
	AUDIT_NFT_OP_OBJ_UNREGISTER = 15,
	AUDIT_NFT_OP_OBJ_RESET = 16,
	AUDIT_NFT_OP_FLOWTABLE_REGISTER = 17,
	AUDIT_NFT_OP_FLOWTABLE_UNREGISTER = 18,
	AUDIT_NFT_OP_INVALID = 19,
};

enum fsnotify_obj_type {
	FSNOTIFY_OBJ_TYPE_INODE = 0,
	FSNOTIFY_OBJ_TYPE_PARENT = 1,
	FSNOTIFY_OBJ_TYPE_VFSMOUNT = 2,
	FSNOTIFY_OBJ_TYPE_SB = 3,
	FSNOTIFY_OBJ_TYPE_COUNT = 4,
	FSNOTIFY_OBJ_TYPE_DETACHED = 4,
};

struct audit_aux_data {
	struct audit_aux_data *next;
	int type;
};

struct audit_chunk;

struct audit_tree_refs {
	struct audit_tree_refs *next;
	struct audit_chunk *c[31];
};

struct audit_aux_data_pids {
	struct audit_aux_data d;
	pid_t target_pid[16];
	kuid_t target_auid[16];
	kuid_t target_uid[16];
	unsigned int target_sessionid[16];
	u32 target_sid[16];
	char target_comm[256];
	int pid_count;
};

struct audit_aux_data_bprm_fcaps {
	struct audit_aux_data d;
	struct audit_cap_data fcap;
	unsigned int fcap_ver;
	struct audit_cap_data old_pcap;
	struct audit_cap_data new_pcap;
};

struct audit_nfcfgop_tab {
	enum audit_nfcfgop op;
	const char *s;
};

struct audit_parent;

struct audit_watch {
	refcount_t count;
	dev_t dev;
	char *path;
	long unsigned int ino;
	struct audit_parent *parent;
	struct list_head wlist;
	struct list_head rules;
};

struct fsnotify_group;

struct fsnotify_iter_info;

struct fsnotify_mark;

struct fsnotify_event;

struct fsnotify_ops {
	int (*handle_event)(struct fsnotify_group *, u32, const void *, int, struct inode *, const struct qstr *, u32, struct fsnotify_iter_info *);
	int (*handle_inode_event)(struct fsnotify_mark *, u32, struct inode *, struct inode *, const struct qstr *, u32);
	void (*free_group_priv)(struct fsnotify_group *);
	void (*freeing_mark)(struct fsnotify_mark *, struct fsnotify_group *);
	void (*free_event)(struct fsnotify_event *);
	void (*free_mark)(struct fsnotify_mark *);
};

struct inotify_group_private_data {
	spinlock_t idr_lock;
	struct idr idr;
	struct ucounts *ucounts;
};

struct fanotify_group_private_data {
	struct hlist_head *merge_hash;
	struct list_head access_list;
	wait_queue_head_t access_waitq;
	int flags;
	int f_flags;
	struct ucounts *ucounts;
};

struct fsnotify_group {
	const struct fsnotify_ops *ops;
	refcount_t refcnt;
	spinlock_t notification_lock;
	struct list_head notification_list;
	wait_queue_head_t notification_waitq;
	unsigned int q_len;
	unsigned int max_events;
	unsigned int priority;
	bool shutdown;
	struct mutex mark_mutex;
	atomic_t user_waits;
	struct list_head marks_list;
	struct fasync_struct *fsn_fa;
	struct fsnotify_event *overflow_event;
	struct mem_cgroup *memcg;
	union {
		void *private;
		struct inotify_group_private_data inotify_data;
		struct fanotify_group_private_data fanotify_data;
	};
};

struct fsnotify_iter_info {
	struct fsnotify_mark *marks[4];
	unsigned int report_mask;
	int srcu_idx;
};

struct fsnotify_mark {
	__u32 mask;
	refcount_t refcnt;
	struct fsnotify_group *group;
	struct list_head g_list;
	spinlock_t lock;
	struct hlist_node obj_list;
	struct fsnotify_mark_connector *connector;
	__u32 ignored_mask;
	unsigned int flags;
};

struct fsnotify_event {
	struct list_head list;
};

struct audit_parent {
	struct list_head watches;
	struct fsnotify_mark mark;
};

struct audit_fsnotify_mark {
	dev_t dev;
	long unsigned int ino;
	char *path;
	struct fsnotify_mark mark;
	struct audit_krule *rule;
};

struct audit_chunk___2;

struct audit_tree {
	refcount_t count;
	int goner;
	struct audit_chunk___2 *root;
	struct list_head chunks;
	struct list_head rules;
	struct list_head list;
	struct list_head same_root;
	struct callback_head head;
	char pathname[0];
};

struct audit_node {
	struct list_head list;
	struct audit_tree *owner;
	unsigned int index;
};

struct audit_chunk___2 {
	struct list_head hash;
	long unsigned int key;
	struct fsnotify_mark *mark;
	struct list_head trees;
	int count;
	atomic_long_t refs;
	struct callback_head head;
	struct audit_node owners[0];
};

struct audit_tree_mark {
	struct fsnotify_mark mark;
	struct audit_chunk___2 *chunk;
};

enum {
	HASH_SIZE = 128,
};

struct kprobe_blacklist_entry {
	struct list_head list;
	long unsigned int start_addr;
	long unsigned int end_addr;
};

enum perf_record_ksymbol_type {
	PERF_RECORD_KSYMBOL_TYPE_UNKNOWN = 0,
	PERF_RECORD_KSYMBOL_TYPE_BPF = 1,
	PERF_RECORD_KSYMBOL_TYPE_OOL = 2,
	PERF_RECORD_KSYMBOL_TYPE_MAX = 3,
};

struct kprobe_insn_page {
	struct list_head list;
	kprobe_opcode_t *insns;
	struct kprobe_insn_cache *cache;
	int nused;
	int ngarbage;
	char slot_used[0];
};

enum kprobe_slot_state {
	SLOT_CLEAN = 0,
	SLOT_DIRTY = 1,
	SLOT_USED = 2,
};

struct kgdb_io {
	const char *name;
	int (*read_char)();
	void (*write_char)(u8);
	void (*flush)();
	int (*init)();
	void (*deinit)();
	void (*pre_exception)();
	void (*post_exception)();
	struct console *cons;
};

enum {
	KDB_NOT_INITIALIZED = 0,
	KDB_INIT_EARLY = 1,
	KDB_INIT_FULL = 2,
};

struct kgdb_state {
	int ex_vector;
	int signo;
	int err_code;
	int cpu;
	int pass_exception;
	long unsigned int thr_query;
	long unsigned int threadid;
	long int kgdb_usethreadid;
	struct pt_regs *linux_regs;
	atomic_t *send_ready;
};

struct debuggerinfo_struct {
	void *debuggerinfo;
	struct task_struct *task;
	int exception_state;
	int ret_state;
	int irq_depth;
	int enter_kgdb;
	bool rounding_up;
};

typedef int (*get_char_func)();

typedef enum {
	KDB_ENABLE_ALL = 1,
	KDB_ENABLE_MEM_READ = 2,
	KDB_ENABLE_MEM_WRITE = 4,
	KDB_ENABLE_REG_READ = 8,
	KDB_ENABLE_REG_WRITE = 16,
	KDB_ENABLE_INSPECT = 32,
	KDB_ENABLE_FLOW_CTRL = 64,
	KDB_ENABLE_SIGNAL = 128,
	KDB_ENABLE_REBOOT = 256,
	KDB_ENABLE_ALWAYS_SAFE = 512,
	KDB_ENABLE_MASK = 1023,
	KDB_ENABLE_ALL_NO_ARGS = 1024,
	KDB_ENABLE_MEM_READ_NO_ARGS = 2048,
	KDB_ENABLE_MEM_WRITE_NO_ARGS = 4096,
	KDB_ENABLE_REG_READ_NO_ARGS = 8192,
	KDB_ENABLE_REG_WRITE_NO_ARGS = 16384,
	KDB_ENABLE_INSPECT_NO_ARGS = 32768,
	KDB_ENABLE_FLOW_CTRL_NO_ARGS = 65536,
	KDB_ENABLE_SIGNAL_NO_ARGS = 131072,
	KDB_ENABLE_REBOOT_NO_ARGS = 262144,
	KDB_ENABLE_ALWAYS_SAFE_NO_ARGS = 524288,
	KDB_ENABLE_MASK_NO_ARGS = 1047552,
	KDB_REPEAT_NO_ARGS = 1073741824,
	KDB_REPEAT_WITH_ARGS = 2147483648,
} kdb_cmdflags_t;

typedef int (*kdb_func_t)(int, const char **);

typedef enum {
	KDB_REASON_ENTER = 1,
	KDB_REASON_ENTER_SLAVE = 2,
	KDB_REASON_BREAK = 3,
	KDB_REASON_DEBUG = 4,
	KDB_REASON_OOPS = 5,
	KDB_REASON_SWITCH = 6,
	KDB_REASON_KEYBOARD = 7,
	KDB_REASON_NMI = 8,
	KDB_REASON_RECURSE = 9,
	KDB_REASON_SSTEP = 10,
	KDB_REASON_SYSTEM_NMI = 11,
} kdb_reason_t;

struct __ksymtab {
	long unsigned int value;
	const char *mod_name;
	long unsigned int mod_start;
	long unsigned int mod_end;
	const char *sec_name;
	long unsigned int sec_start;
	long unsigned int sec_end;
	const char *sym_name;
	long unsigned int sym_start;
	long unsigned int sym_end;
};

typedef struct __ksymtab kdb_symtab_t;

struct _kdbtab {
	char *cmd_name;
	kdb_func_t cmd_func;
	char *cmd_usage;
	char *cmd_help;
	short int cmd_minlen;
	kdb_cmdflags_t cmd_flags;
	struct list_head list_node;
	bool is_dynamic;
};

typedef struct _kdbtab kdbtab_t;

typedef enum {
	KDB_DB_BPT = 0,
	KDB_DB_SS = 1,
	KDB_DB_SSBPT = 2,
	KDB_DB_NOBPT = 3,
} kdb_dbtrap_t;

struct _kdbmsg {
	int km_diag;
	char *km_msg;
};

typedef struct _kdbmsg kdbmsg_t;

struct defcmd_set {
	int count;
	bool usable;
	char *name;
	char *usage;
	char *help;
	char **command;
};

struct debug_alloc_header {
	u32 next;
	u32 size;
	void *caller;
};

struct _kdb_bp {
	long unsigned int bp_addr;
	unsigned int bp_free: 1;
	unsigned int bp_enabled: 1;
	unsigned int bp_type: 4;
	unsigned int bp_installed: 1;
	unsigned int bp_delay: 1;
	unsigned int bp_delayed: 1;
	unsigned int bph_length;
};

typedef struct _kdb_bp kdb_bp_t;

typedef short unsigned int u_short;

struct seccomp_notif_sizes {
	__u16 seccomp_notif;
	__u16 seccomp_notif_resp;
	__u16 seccomp_data;
};

struct seccomp_notif {
	__u64 id;
	__u32 pid;
	__u32 flags;
	struct seccomp_data data;
};

struct seccomp_notif_resp {
	__u64 id;
	__s64 val;
	__s32 error;
	__u32 flags;
};

struct seccomp_notif_addfd {
	__u64 id;
	__u32 flags;
	__u32 srcfd;
	__u32 newfd;
	__u32 newfd_flags;
};

struct action_cache {
	long unsigned int allow_native[8];
};

struct notification;

struct seccomp_filter {
	refcount_t refs;
	refcount_t users;
	bool log;
	struct action_cache cache;
	struct seccomp_filter *prev;
	struct bpf_prog *prog;
	struct notification *notif;
	struct mutex notify_lock;
	wait_queue_head_t wqh;
};

struct seccomp_metadata {
	__u64 filter_off;
	__u64 flags;
};

struct sock_fprog {
	short unsigned int len;
	struct sock_filter *filter;
};

typedef unsigned int (*bpf_dispatcher_fn)(const void *, const struct bpf_insn *, unsigned int (*)(const void *, const struct bpf_insn *));

typedef int (*bpf_aux_classic_check_t)(struct sock_filter *, unsigned int);

enum notify_state {
	SECCOMP_NOTIFY_INIT = 0,
	SECCOMP_NOTIFY_SENT = 1,
	SECCOMP_NOTIFY_REPLIED = 2,
};

struct seccomp_knotif {
	struct task_struct *task;
	u64 id;
	const struct seccomp_data *data;
	enum notify_state state;
	int error;
	long int val;
	u32 flags;
	struct completion ready;
	struct list_head list;
	struct list_head addfd;
};

struct seccomp_kaddfd {
	struct file *file;
	int fd;
	unsigned int flags;
	__u32 ioctl_flags;
	union {
		bool setfd;
		int ret;
	};
	struct completion completion;
	struct list_head list;
};

struct notification {
	struct semaphore request;
	u64 next_id;
	struct list_head notifications;
};

struct seccomp_log_name {
	u32 log;
	const char *name;
};

struct rchan;

struct rchan_buf {
	void *start;
	void *data;
	size_t offset;
	size_t subbufs_produced;
	size_t subbufs_consumed;
	struct rchan *chan;
	wait_queue_head_t read_wait;
	struct irq_work wakeup_work;
	struct dentry *dentry;
	struct kref kref;
	struct page **page_array;
	unsigned int page_count;
	unsigned int finalized;
	size_t *padding;
	size_t prev_padding;
	size_t bytes_consumed;
	size_t early_bytes;
	unsigned int cpu;
	long: 32;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct rchan_callbacks;

struct rchan {
	u32 version;
	size_t subbuf_size;
	size_t n_subbufs;
	size_t alloc_size;
	const struct rchan_callbacks *cb;
	struct kref kref;
	void *private_data;
	size_t last_toobig;
	struct rchan_buf **buf;
	int is_global;
	struct list_head list;
	struct dentry *parent;
	int has_base_filename;
	char base_filename[255];
};

struct rchan_callbacks {
	int (*subbuf_start)(struct rchan_buf *, void *, void *, size_t);
	struct dentry * (*create_buf_file)(const char *, struct dentry *, umode_t, struct rchan_buf *, int *);
	int (*remove_buf_file)(struct dentry *);
};

struct partial_page {
	unsigned int offset;
	unsigned int len;
	long unsigned int private;
};

struct splice_pipe_desc {
	struct page **pages;
	struct partial_page *partial;
	int nr_pages;
	unsigned int nr_pages_max;
	const struct pipe_buf_operations *ops;
	void (*spd_release)(struct splice_pipe_desc *, unsigned int);
};

struct rchan_percpu_buf_dispatcher {
	struct rchan_buf *buf;
	struct dentry *dentry;
};

enum {
	TASKSTATS_TYPE_UNSPEC = 0,
	TASKSTATS_TYPE_PID = 1,
	TASKSTATS_TYPE_TGID = 2,
	TASKSTATS_TYPE_STATS = 3,
	TASKSTATS_TYPE_AGGR_PID = 4,
	TASKSTATS_TYPE_AGGR_TGID = 5,
	TASKSTATS_TYPE_NULL = 6,
	__TASKSTATS_TYPE_MAX = 7,
};

enum {
	TASKSTATS_CMD_ATTR_UNSPEC = 0,
	TASKSTATS_CMD_ATTR_PID = 1,
	TASKSTATS_CMD_ATTR_TGID = 2,
	TASKSTATS_CMD_ATTR_REGISTER_CPUMASK = 3,
	TASKSTATS_CMD_ATTR_DEREGISTER_CPUMASK = 4,
	__TASKSTATS_CMD_ATTR_MAX = 5,
};

enum {
	CGROUPSTATS_CMD_UNSPEC = 3,
	CGROUPSTATS_CMD_GET = 4,
	CGROUPSTATS_CMD_NEW = 5,
	__CGROUPSTATS_CMD_MAX = 6,
};

enum {
	CGROUPSTATS_TYPE_UNSPEC = 0,
	CGROUPSTATS_TYPE_CGROUP_STATS = 1,
	__CGROUPSTATS_TYPE_MAX = 2,
};

enum {
	CGROUPSTATS_CMD_ATTR_UNSPEC = 0,
	CGROUPSTATS_CMD_ATTR_FD = 1,
	__CGROUPSTATS_CMD_ATTR_MAX = 2,
};

struct genlmsghdr {
	__u8 cmd;
	__u8 version;
	__u16 reserved;
};

enum {
	NLA_UNSPEC = 0,
	NLA_U8 = 1,
	NLA_U16 = 2,
	NLA_U32 = 3,
	NLA_U64 = 4,
	NLA_STRING = 5,
	NLA_FLAG = 6,
	NLA_MSECS = 7,
	NLA_NESTED = 8,
	NLA_NESTED_ARRAY = 9,
	NLA_NUL_STRING = 10,
	NLA_BINARY = 11,
	NLA_S8 = 12,
	NLA_S16 = 13,
	NLA_S32 = 14,
	NLA_S64 = 15,
	NLA_BITFIELD32 = 16,
	NLA_REJECT = 17,
	__NLA_TYPE_MAX = 18,
};

struct genl_multicast_group {
	char name[16];
	u8 flags;
};

struct genl_ops;

struct genl_info;

struct genl_small_ops;

struct genl_family {
	int id;
	unsigned int hdrsize;
	char name[16];
	unsigned int version;
	unsigned int maxattr;
	unsigned int mcgrp_offset;
	u8 netnsok: 1;
	u8 parallel_ops: 1;
	u8 n_ops;
	u8 n_small_ops;
	u8 n_mcgrps;
	const struct nla_policy *policy;
	int (*pre_doit)(const struct genl_ops *, struct sk_buff *, struct genl_info *);
	void (*post_doit)(const struct genl_ops *, struct sk_buff *, struct genl_info *);
	const struct genl_ops *ops;
	const struct genl_small_ops *small_ops;
	const struct genl_multicast_group *mcgrps;
	struct module *module;
};

struct genl_ops {
	int (*doit)(struct sk_buff *, struct genl_info *);
	int (*start)(struct netlink_callback *);
	int (*dumpit)(struct sk_buff *, struct netlink_callback *);
	int (*done)(struct netlink_callback *);
	const struct nla_policy *policy;
	unsigned int maxattr;
	u8 cmd;
	u8 internal_flags;
	u8 flags;
	u8 validate;
};

struct genl_info {
	u32 snd_seq;
	u32 snd_portid;
	struct nlmsghdr *nlhdr;
	struct genlmsghdr *genlhdr;
	void *userhdr;
	struct nlattr **attrs;
	possible_net_t _net;
	void *user_ptr[2];
	struct netlink_ext_ack *extack;
};

struct genl_small_ops {
	int (*doit)(struct sk_buff *, struct genl_info *);
	int (*dumpit)(struct sk_buff *, struct netlink_callback *);
	u8 cmd;
	u8 internal_flags;
	u8 flags;
	u8 validate;
};

enum genl_validate_flags {
	GENL_DONT_VALIDATE_STRICT = 1,
	GENL_DONT_VALIDATE_DUMP = 2,
	GENL_DONT_VALIDATE_DUMP_STRICT = 4,
};

struct listener {
	struct list_head list;
	pid_t pid;
	char valid;
};

struct listener_list {
	struct rw_semaphore sem;
	struct list_head list;
};

enum actions {
	REGISTER = 0,
	DEREGISTER = 1,
	CPU_DONT_CARE = 2,
};

struct tp_module {
	struct list_head list;
	struct module *mod;
};

enum tp_func_state {
	TP_FUNC_0 = 0,
	TP_FUNC_1 = 1,
	TP_FUNC_2 = 2,
	TP_FUNC_N = 3,
};

enum tp_transition_sync {
	TP_TRANSITION_SYNC_1_0_1 = 0,
	TP_TRANSITION_SYNC_N_2_1 = 1,
	_NR_TP_TRANSITION_SYNC = 2,
};

struct tp_transition_snapshot {
	long unsigned int rcu;
	long unsigned int srcu;
	bool ongoing;
};

struct tp_probes {
	struct callback_head rcu;
	struct tracepoint_func probes[0];
};

struct ftrace_hash {
	long unsigned int size_bits;
	struct hlist_head *buckets;
	long unsigned int count;
	long unsigned int flags;
	struct callback_head rcu;
};

struct ftrace_func_entry {
	struct hlist_node hlist;
	long unsigned int ip;
	long unsigned int direct;
};

enum ftrace_bug_type {
	FTRACE_BUG_UNKNOWN = 0,
	FTRACE_BUG_INIT = 1,
	FTRACE_BUG_NOP = 2,
	FTRACE_BUG_CALL = 3,
	FTRACE_BUG_UPDATE = 4,
};

enum {
	FTRACE_UPDATE_CALLS = 1,
	FTRACE_DISABLE_CALLS = 2,
	FTRACE_UPDATE_TRACE_FUNC = 4,
	FTRACE_START_FUNC_RET = 8,
	FTRACE_STOP_FUNC_RET = 16,
	FTRACE_MAY_SLEEP = 32,
};

enum {
	FTRACE_UPDATE_IGNORE = 0,
	FTRACE_UPDATE_MAKE_CALL = 1,
	FTRACE_UPDATE_MODIFY_CALL = 2,
	FTRACE_UPDATE_MAKE_NOP = 3,
};

enum {
	FTRACE_ITER_FILTER = 1,
	FTRACE_ITER_NOTRACE = 2,
	FTRACE_ITER_PRINTALL = 4,
	FTRACE_ITER_DO_PROBES = 8,
	FTRACE_ITER_PROBE = 16,
	FTRACE_ITER_MOD = 32,
	FTRACE_ITER_ENABLED = 64,
};

struct ftrace_graph_ent {
	long unsigned int func;
	int depth;
} __attribute__((packed));

struct ftrace_graph_ret {
	long unsigned int func;
	int depth;
	unsigned int overrun;
	long long unsigned int calltime;
	long long unsigned int rettime;
};

typedef void (*trace_func_graph_ret_t)(struct ftrace_graph_ret *);

typedef int (*trace_func_graph_ent_t)(struct ftrace_graph_ent *);

struct fgraph_ops {
	trace_func_graph_ent_t entryfunc;
	trace_func_graph_ret_t retfunc;
};

struct prog_entry;

struct event_filter {
	struct prog_entry *prog;
	char *filter_string;
};

struct trace_array_cpu;

struct array_buffer {
	struct trace_array *tr;
	struct trace_buffer *buffer;
	struct trace_array_cpu *data;
	u64 time_start;
	int cpu;
};

struct trace_pid_list;

struct trace_options;

struct cond_snapshot;

struct trace_func_repeats;

struct trace_array {
	struct list_head list;
	char *name;
	struct array_buffer array_buffer;
	struct array_buffer max_buffer;
	bool allocated_snapshot;
	long unsigned int max_latency;
	struct dentry *d_max_latency;
	struct work_struct fsnotify_work;
	struct irq_work fsnotify_irqwork;
	struct trace_pid_list *filtered_pids;
	struct trace_pid_list *filtered_no_pids;
	arch_spinlock_t max_lock;
	int buffer_disabled;
	int sys_refcount_enter;
	int sys_refcount_exit;
	struct trace_event_file *enter_syscall_files[450];
	struct trace_event_file *exit_syscall_files[450];
	int stop_count;
	int clock_id;
	int nr_topts;
	bool clear_trace;
	int buffer_percent;
	unsigned int n_err_log_entries;
	struct tracer *current_trace;
	unsigned int trace_flags;
	unsigned char trace_flags_index[32];
	unsigned int flags;
	raw_spinlock_t start_lock;
	struct list_head err_log;
	struct dentry *dir;
	struct dentry *options;
	struct dentry *percpu_dir;
	struct dentry *event_dir;
	struct trace_options *topts;
	struct list_head systems;
	struct list_head events;
	struct trace_event_file *trace_marker_file;
	cpumask_var_t tracing_cpumask;
	int ref;
	int trace_ref;
	struct ftrace_ops *ops;
	struct trace_pid_list *function_pids;
	struct trace_pid_list *function_no_pids;
	struct list_head func_probes;
	struct list_head mod_trace;
	struct list_head mod_notrace;
	int function_enabled;
	int no_filter_buffering_ref;
	struct list_head hist_vars;
	struct cond_snapshot *cond_snapshot;
	struct trace_func_repeats *last_func_repeats;
};

struct tracer_flags;

struct tracer {
	const char *name;
	int (*init)(struct trace_array *);
	void (*reset)(struct trace_array *);
	void (*start)(struct trace_array *);
	void (*stop)(struct trace_array *);
	int (*update_thresh)(struct trace_array *);
	void (*open)(struct trace_iterator *);
	void (*pipe_open)(struct trace_iterator *);
	void (*close)(struct trace_iterator *);
	void (*pipe_close)(struct trace_iterator *);
	ssize_t (*read)(struct trace_iterator *, struct file *, char *, size_t, loff_t *);
	ssize_t (*splice_read)(struct trace_iterator *, struct file *, loff_t *, struct pipe_inode_info *, size_t, unsigned int);
	void (*print_header)(struct seq_file *);
	enum print_line_t (*print_line)(struct trace_iterator *);
	int (*set_flag)(struct trace_array *, u32, u32, int);
	int (*flag_changed)(struct trace_array *, u32, int);
	struct tracer *next;
	struct tracer_flags *flags;
	int enabled;
	bool print_max;
	bool allow_instances;
	bool use_max_tr;
	bool noboot;
};

struct event_subsystem;

struct trace_subsystem_dir {
	struct list_head list;
	struct event_subsystem *subsystem;
	struct trace_array *tr;
	struct dentry *entry;
	int ref_count;
	int nr_events;
};

struct trace_array_cpu {
	atomic_t disabled;
	void *buffer_page;
	long unsigned int entries;
	long unsigned int saved_latency;
	long unsigned int critical_start;
	long unsigned int critical_end;
	long unsigned int critical_sequence;
	long unsigned int nice;
	long unsigned int policy;
	long unsigned int rt_priority;
	long unsigned int skipped_entries;
	u64 preempt_timestamp;
	pid_t pid;
	kuid_t uid;
	char comm[16];
	int ftrace_ignore_pid;
	bool ignore_pid;
};

struct trace_option_dentry;

struct trace_options {
	struct tracer *tracer;
	struct trace_option_dentry *topts;
};

struct tracer_opt;

struct trace_option_dentry {
	struct tracer_opt *opt;
	struct tracer_flags *flags;
	struct trace_array *tr;
	struct dentry *entry;
};

struct trace_pid_list {
	int pid_max;
	long unsigned int *pids;
};

enum {
	TRACE_PIDS = 1,
	TRACE_NO_PIDS = 2,
};

typedef bool (*cond_update_fn_t)(struct trace_array *, void *);

struct cond_snapshot {
	void *cond_data;
	cond_update_fn_t update;
};

struct trace_func_repeats {
	long unsigned int ip;
	long unsigned int parent_ip;
	long unsigned int count;
	u64 ts_last_call;
};

enum {
	TRACE_ARRAY_FL_GLOBAL = 1,
};

struct tracer_opt {
	const char *name;
	u32 bit;
};

struct tracer_flags {
	u32 val;
	struct tracer_opt *opts;
	struct tracer *trace;
};

struct ftrace_mod_load {
	struct list_head list;
	char *func;
	char *module;
	int enable;
};

enum {
	FTRACE_HASH_FL_MOD = 1,
};

struct ftrace_func_command {
	struct list_head list;
	char *name;
	int (*func)(struct trace_array *, struct ftrace_hash *, char *, char *, char *, int);
};

struct ftrace_probe_ops {
	void (*func)(long unsigned int, long unsigned int, struct trace_array *, struct ftrace_probe_ops *, void *);
	int (*init)(struct ftrace_probe_ops *, struct trace_array *, long unsigned int, void *, void **);
	void (*free)(struct ftrace_probe_ops *, struct trace_array *, long unsigned int, void *);
	int (*print)(struct seq_file *, long unsigned int, struct ftrace_probe_ops *, void *);
};

typedef int (*ftrace_mapper_func)(void *);

struct trace_parser {
	bool cont;
	char *buffer;
	unsigned int idx;
	unsigned int size;
};

enum trace_iterator_bits {
	TRACE_ITER_PRINT_PARENT_BIT = 0,
	TRACE_ITER_SYM_OFFSET_BIT = 1,
	TRACE_ITER_SYM_ADDR_BIT = 2,
	TRACE_ITER_VERBOSE_BIT = 3,
	TRACE_ITER_RAW_BIT = 4,
	TRACE_ITER_HEX_BIT = 5,
	TRACE_ITER_BIN_BIT = 6,
	TRACE_ITER_BLOCK_BIT = 7,
	TRACE_ITER_PRINTK_BIT = 8,
	TRACE_ITER_ANNOTATE_BIT = 9,
	TRACE_ITER_USERSTACKTRACE_BIT = 10,
	TRACE_ITER_SYM_USEROBJ_BIT = 11,
	TRACE_ITER_PRINTK_MSGONLY_BIT = 12,
	TRACE_ITER_CONTEXT_INFO_BIT = 13,
	TRACE_ITER_LATENCY_FMT_BIT = 14,
	TRACE_ITER_RECORD_CMD_BIT = 15,
	TRACE_ITER_RECORD_TGID_BIT = 16,
	TRACE_ITER_OVERWRITE_BIT = 17,
	TRACE_ITER_STOP_ON_FREE_BIT = 18,
	TRACE_ITER_IRQ_INFO_BIT = 19,
	TRACE_ITER_MARKERS_BIT = 20,
	TRACE_ITER_EVENT_FORK_BIT = 21,
	TRACE_ITER_PAUSE_ON_TRACE_BIT = 22,
	TRACE_ITER_HASH_PTR_BIT = 23,
	TRACE_ITER_FUNCTION_BIT = 24,
	TRACE_ITER_FUNC_FORK_BIT = 25,
	TRACE_ITER_DISPLAY_GRAPH_BIT = 26,
	TRACE_ITER_STACKTRACE_BIT = 27,
	TRACE_ITER_LAST_BIT = 28,
};

struct event_subsystem {
	struct list_head list;
	const char *name;
	struct event_filter *filter;
	int ref_count;
};

enum regex_type {
	MATCH_FULL = 0,
	MATCH_FRONT_ONLY = 1,
	MATCH_MIDDLE_ONLY = 2,
	MATCH_END_ONLY = 3,
	MATCH_GLOB = 4,
	MATCH_INDEX = 5,
};

struct tracer_stat {
	const char *name;
	void * (*stat_start)(struct tracer_stat *);
	void * (*stat_next)(void *, int);
	cmp_func_t stat_cmp;
	int (*stat_show)(struct seq_file *, void *);
	void (*stat_release)(void *);
	int (*stat_headers)(struct seq_file *);
};

enum {
	FTRACE_MODIFY_ENABLE_FL = 1,
	FTRACE_MODIFY_MAY_SLEEP_FL = 2,
};

struct ftrace_profile {
	struct hlist_node node;
	long unsigned int ip;
	long unsigned int counter;
	long long unsigned int time;
	long long unsigned int time_squared;
};

struct ftrace_profile_page {
	struct ftrace_profile_page *next;
	long unsigned int index;
	struct ftrace_profile records[0];
};

struct ftrace_profile_stat {
	atomic_t disabled;
	struct hlist_head *hash;
	struct ftrace_profile_page *pages;
	struct ftrace_profile_page *start;
	struct tracer_stat stat;
};

struct ftrace_func_probe {
	struct ftrace_probe_ops *probe_ops;
	struct ftrace_ops ops;
	struct trace_array *tr;
	struct list_head list;
	void *data;
	int ref;
};

struct ftrace_page {
	struct ftrace_page *next;
	struct dyn_ftrace *records;
	int index;
	int order;
};

struct ftrace_rec_iter {
	struct ftrace_page *pg;
	int index;
};

struct ftrace_iterator {
	loff_t pos;
	loff_t func_pos;
	loff_t mod_pos;
	struct ftrace_page *pg;
	struct dyn_ftrace *func;
	struct ftrace_func_probe *probe;
	struct ftrace_func_entry *probe_entry;
	struct trace_parser parser;
	struct ftrace_hash *hash;
	struct ftrace_ops *ops;
	struct trace_array *tr;
	struct list_head *mod_list;
	int pidx;
	int idx;
	unsigned int flags;
};

struct ftrace_glob {
	char *search;
	unsigned int len;
	int type;
};

struct ftrace_func_map {
	struct ftrace_func_entry entry;
	void *data;
};

struct ftrace_func_mapper {
	struct ftrace_hash hash;
};

enum graph_filter_type {
	GRAPH_FILTER_NOTRACE = 0,
	GRAPH_FILTER_FUNCTION = 1,
};

struct ftrace_graph_data {
	struct ftrace_hash *hash;
	struct ftrace_func_entry *entry;
	int idx;
	enum graph_filter_type type;
	struct ftrace_hash *new_hash;
	const struct seq_operations *seq_ops;
	struct trace_parser parser;
};

struct ftrace_mod_func {
	struct list_head list;
	char *name;
	long unsigned int ip;
	unsigned int size;
};

struct ftrace_mod_map {
	struct callback_head rcu;
	struct list_head list;
	struct module *mod;
	long unsigned int start_addr;
	long unsigned int end_addr;
	struct list_head funcs;
	unsigned int num_funcs;
};

struct ftrace_init_func {
	struct list_head list;
	long unsigned int ip;
};

enum ring_buffer_type {
	RINGBUF_TYPE_DATA_TYPE_LEN_MAX = 28,
	RINGBUF_TYPE_PADDING = 29,
	RINGBUF_TYPE_TIME_EXTEND = 30,
	RINGBUF_TYPE_TIME_STAMP = 31,
};

enum ring_buffer_flags {
	RB_FL_OVERWRITE = 1,
};

struct ring_buffer_per_cpu;

struct buffer_page;

struct ring_buffer_iter {
	struct ring_buffer_per_cpu *cpu_buffer;
	long unsigned int head;
	long unsigned int next_event;
	struct buffer_page *head_page;
	struct buffer_page *cache_reader_page;
	long unsigned int cache_read;
	u64 read_stamp;
	u64 page_stamp;
	struct ring_buffer_event *event;
	int missed_events;
};

struct rb_irq_work {
	struct irq_work work;
	wait_queue_head_t waiters;
	wait_queue_head_t full_waiters;
	bool waiters_pending;
	bool full_waiters_pending;
	bool wakeup_full;
};

struct trace_buffer___2 {
	unsigned int flags;
	int cpus;
	atomic_t record_disabled;
	cpumask_var_t cpumask;
	struct lock_class_key *reader_lock_key;
	struct mutex mutex;
	struct ring_buffer_per_cpu **buffers;
	struct hlist_node node;
	u64 (*clock)();
	struct rb_irq_work irq_work;
	bool time_stamp_abs;
};

enum {
	RB_LEN_TIME_EXTEND = 8,
	RB_LEN_TIME_STAMP = 8,
};

struct buffer_data_page {
	u64 time_stamp;
	local_t commit;
	unsigned char data[0];
};

struct buffer_page {
	struct list_head list;
	local_t write;
	unsigned int read;
	local_t entries;
	long unsigned int real_end;
	struct buffer_data_page *page;
};

struct rb_event_info {
	u64 ts;
	u64 delta;
	u64 before;
	u64 after;
	long unsigned int length;
	struct buffer_page *tail_page;
	int add_timestamp;
};

enum {
	RB_ADD_STAMP_NONE = 0,
	RB_ADD_STAMP_EXTEND = 2,
	RB_ADD_STAMP_ABSOLUTE = 4,
	RB_ADD_STAMP_FORCE = 8,
};

enum {
	RB_CTX_TRANSITION = 0,
	RB_CTX_NMI = 1,
	RB_CTX_IRQ = 2,
	RB_CTX_SOFTIRQ = 3,
	RB_CTX_NORMAL = 4,
	RB_CTX_MAX = 5,
};

struct rb_time_struct {
	local64_t time;
};

typedef struct rb_time_struct rb_time_t;

struct ring_buffer_per_cpu {
	int cpu;
	atomic_t record_disabled;
	atomic_t resize_disabled;
	struct trace_buffer___2 *buffer;
	raw_spinlock_t reader_lock;
	arch_spinlock_t lock;
	struct lock_class_key lock_key;
	struct buffer_data_page *free_page;
	long unsigned int nr_pages;
	unsigned int current_context;
	struct list_head *pages;
	struct buffer_page *head_page;
	struct buffer_page *tail_page;
	struct buffer_page *commit_page;
	struct buffer_page *reader_page;
	long unsigned int lost_events;
	long unsigned int last_overrun;
	long unsigned int nest;
	local_t entries_bytes;
	local_t entries;
	local_t overrun;
	local_t commit_overrun;
	local_t dropped_events;
	local_t committing;
	local_t commits;
	local_t pages_touched;
	local_t pages_read;
	long int last_pages_touch;
	size_t shortest_full;
	long unsigned int read;
	long unsigned int read_bytes;
	rb_time_t write_stamp;
	rb_time_t before_stamp;
	u64 event_stamp[5];
	u64 read_stamp;
	long int nr_pages_to_update;
	struct list_head new_pages;
	struct work_struct update_pages_work;
	struct completion update_done;
	struct rb_irq_work irq_work;
};

typedef struct vfsmount * (*debugfs_automount_t)(struct dentry *, void *);

struct trace_export {
	struct trace_export *next;
	void (*write)(struct trace_export *, const void *, unsigned int);
	int flags;
};

enum fsnotify_data_type {
	FSNOTIFY_EVENT_NONE = 0,
	FSNOTIFY_EVENT_PATH = 1,
	FSNOTIFY_EVENT_INODE = 2,
	FSNOTIFY_EVENT_DENTRY = 3,
};

enum trace_iter_flags {
	TRACE_FILE_LAT_FMT = 1,
	TRACE_FILE_ANNOTATE = 2,
	TRACE_FILE_TIME_IN_NS = 4,
};

enum trace_flag_type {
	TRACE_FLAG_IRQS_OFF = 1,
	TRACE_FLAG_IRQS_NOSUPPORT = 2,
	TRACE_FLAG_NEED_RESCHED = 4,
	TRACE_FLAG_HARDIRQ = 8,
	TRACE_FLAG_SOFTIRQ = 16,
	TRACE_FLAG_PREEMPT_RESCHED = 32,
	TRACE_FLAG_NMI = 64,
	TRACE_FLAG_BH_OFF = 128,
};

enum trace_type {
	__TRACE_FIRST_TYPE = 0,
	TRACE_FN = 1,
	TRACE_CTX = 2,
	TRACE_WAKE = 3,
	TRACE_STACK = 4,
	TRACE_PRINT = 5,
	TRACE_BPRINT = 6,
	TRACE_MMIO_RW = 7,
	TRACE_MMIO_MAP = 8,
	TRACE_BRANCH = 9,
	TRACE_GRAPH_RET = 10,
	TRACE_GRAPH_ENT = 11,
	TRACE_USER_STACK = 12,
	TRACE_BLK = 13,
	TRACE_BPUTS = 14,
	TRACE_HWLAT = 15,
	TRACE_OSNOISE = 16,
	TRACE_TIMERLAT = 17,
	TRACE_RAW_DATA = 18,
	TRACE_FUNC_REPEATS = 19,
	__TRACE_LAST_TYPE = 20,
};

struct ftrace_entry {
	struct trace_entry ent;
	long unsigned int ip;
	long unsigned int parent_ip;
};

struct stack_entry {
	struct trace_entry ent;
	int size;
	long unsigned int caller[8];
};

struct bprint_entry {
	struct trace_entry ent;
	long unsigned int ip;
	const char *fmt;
	u32 buf[0];
};

struct print_entry {
	struct trace_entry ent;
	long unsigned int ip;
	char buf[0];
};

struct raw_data_entry {
	struct trace_entry ent;
	unsigned int id;
	char buf[0];
};

struct bputs_entry {
	struct trace_entry ent;
	long unsigned int ip;
	const char *str;
};

struct func_repeats_entry {
	struct trace_entry ent;
	long unsigned int ip;
	long unsigned int parent_ip;
	u16 count;
	u16 top_delta_ts;
	u32 bottom_delta_ts;
};

enum trace_iterator_flags {
	TRACE_ITER_PRINT_PARENT = 1,
	TRACE_ITER_SYM_OFFSET = 2,
	TRACE_ITER_SYM_ADDR = 4,
	TRACE_ITER_VERBOSE = 8,
	TRACE_ITER_RAW = 16,
	TRACE_ITER_HEX = 32,
	TRACE_ITER_BIN = 64,
	TRACE_ITER_BLOCK = 128,
	TRACE_ITER_PRINTK = 256,
	TRACE_ITER_ANNOTATE = 512,
	TRACE_ITER_USERSTACKTRACE = 1024,
	TRACE_ITER_SYM_USEROBJ = 2048,
	TRACE_ITER_PRINTK_MSGONLY = 4096,
	TRACE_ITER_CONTEXT_INFO = 8192,
	TRACE_ITER_LATENCY_FMT = 16384,
	TRACE_ITER_RECORD_CMD = 32768,
	TRACE_ITER_RECORD_TGID = 65536,
	TRACE_ITER_OVERWRITE = 131072,
	TRACE_ITER_STOP_ON_FREE = 262144,
	TRACE_ITER_IRQ_INFO = 524288,
	TRACE_ITER_MARKERS = 1048576,
	TRACE_ITER_EVENT_FORK = 2097152,
	TRACE_ITER_PAUSE_ON_TRACE = 4194304,
	TRACE_ITER_HASH_PTR = 8388608,
	TRACE_ITER_FUNCTION = 16777216,
	TRACE_ITER_FUNC_FORK = 33554432,
	TRACE_ITER_DISPLAY_GRAPH = 67108864,
	TRACE_ITER_STACKTRACE = 134217728,
};

struct trace_min_max_param {
	struct mutex *lock;
	u64 *val;
	u64 *min;
	u64 *max;
};

struct saved_cmdlines_buffer {
	unsigned int map_pid_to_cmdline[32769];
	unsigned int *map_cmdline_to_pid;
	unsigned int cmdline_num;
	int cmdline_idx;
	char *saved_cmdlines;
};

struct ftrace_stack {
	long unsigned int calls[16384];
};

struct ftrace_stacks {
	struct ftrace_stack stacks[4];
};

struct trace_buffer_struct {
	int nesting;
	char buffer[4096];
};

struct ftrace_buffer_info {
	struct trace_iterator iter;
	void *spare;
	unsigned int spare_cpu;
	unsigned int read;
};

struct err_info {
	const char **errs;
	u8 type;
	u8 pos;
	u64 ts;
};

struct tracing_log_err {
	struct list_head list;
	struct err_info info;
	char loc[128];
	char cmd[256];
};

struct buffer_ref {
	struct trace_buffer *buffer;
	void *page;
	int cpu;
	refcount_t refcount;
};

struct ftrace_func_mapper___2;

struct ctx_switch_entry {
	struct trace_entry ent;
	unsigned int prev_pid;
	unsigned int next_pid;
	unsigned int next_cpu;
	unsigned char prev_prio;
	unsigned char prev_state;
	unsigned char next_prio;
	unsigned char next_state;
};

struct userstack_entry {
	struct trace_entry ent;
	unsigned int tgid;
	long unsigned int caller[8];
};

struct hwlat_entry {
	struct trace_entry ent;
	u64 duration;
	u64 outer_duration;
	u64 nmi_total_ts;
	struct timespec64 timestamp;
	unsigned int nmi_count;
	unsigned int seqnum;
	unsigned int count;
};

struct osnoise_entry {
	struct trace_entry ent;
	u64 noise;
	u64 runtime;
	u64 max_sample;
	unsigned int hw_count;
	unsigned int nmi_count;
	unsigned int irq_count;
	unsigned int softirq_count;
	unsigned int thread_count;
};

struct timerlat_entry {
	struct trace_entry ent;
	unsigned int seqnum;
	int context;
	u64 timer_latency;
};

struct trace_mark {
	long long unsigned int val;
	char sym;
};

struct stat_node {
	struct rb_node node;
	void *stat;
};

struct stat_session {
	struct list_head session_list;
	struct tracer_stat *ts;
	struct rb_root stat_root;
	struct mutex stat_mutex;
	struct dentry *file;
};

struct trace_bprintk_fmt {
	struct list_head list;
	const char *fmt;
};

typedef int (*tracing_map_cmp_fn_t)(void *, void *);

struct tracing_map_field {
	tracing_map_cmp_fn_t cmp_fn;
	union {
		atomic64_t sum;
		unsigned int offset;
	};
};

struct tracing_map;

struct tracing_map_elt {
	struct tracing_map *map;
	struct tracing_map_field *fields;
	atomic64_t *vars;
	bool *var_set;
	void *key;
	void *private_data;
};

struct tracing_map_sort_key {
	unsigned int field_idx;
	bool descending;
};

struct tracing_map_array;

struct tracing_map_ops;

struct tracing_map {
	unsigned int key_size;
	unsigned int map_bits;
	unsigned int map_size;
	unsigned int max_elts;
	atomic_t next_elt;
	struct tracing_map_array *elts;
	struct tracing_map_array *map;
	const struct tracing_map_ops *ops;
	void *private_data;
	struct tracing_map_field fields[6];
	unsigned int n_fields;
	int key_idx[3];
	unsigned int n_keys;
	struct tracing_map_sort_key sort_key;
	unsigned int n_vars;
	atomic64_t hits;
	atomic64_t drops;
};

struct tracing_map_entry {
	u32 key;
	struct tracing_map_elt *val;
};

struct tracing_map_sort_entry {
	void *key;
	struct tracing_map_elt *elt;
	bool elt_copied;
	bool dup;
};

struct tracing_map_array {
	unsigned int entries_per_page;
	unsigned int entry_size_shift;
	unsigned int entry_shift;
	unsigned int entry_mask;
	unsigned int n_pages;
	void **pages;
};

struct tracing_map_ops {
	int (*elt_alloc)(struct tracing_map_elt *);
	void (*elt_free)(struct tracing_map_elt *);
	void (*elt_clear)(struct tracing_map_elt *);
	void (*elt_init)(struct tracing_map_elt *);
};

enum {
	TRACE_FUNC_NO_OPTS = 0,
	TRACE_FUNC_OPT_STACK = 1,
	TRACE_FUNC_OPT_NO_REPEATS = 2,
	TRACE_FUNC_OPT_HIGHEST_BIT = 4,
};

enum {
	MODE_NONE = 0,
	MODE_ROUND_ROBIN = 1,
	MODE_PER_CPU = 2,
	MODE_MAX = 3,
};

struct hwlat_kthread_data {
	struct task_struct *kthread;
	u64 nmi_ts_start;
	u64 nmi_total_ts;
	int nmi_count;
	int nmi_cpu;
};

struct hwlat_sample {
	u64 seqnum;
	u64 duration;
	u64 outer_duration;
	u64 nmi_total_ts;
	struct timespec64 timestamp;
	int nmi_count;
	int count;
};

struct hwlat_data {
	struct mutex lock;
	u64 count;
	u64 sample_window;
	u64 sample_width;
	int thread_mode;
};

struct trace_event_raw_thread_noise {
	struct trace_entry ent;
	char comm[16];
	u64 start;
	u64 duration;
	pid_t pid;
	char __data[0];
};

struct trace_event_raw_softirq_noise {
	struct trace_entry ent;
	u64 start;
	u64 duration;
	int vector;
	char __data[0];
};

struct trace_event_raw_irq_noise {
	struct trace_entry ent;
	u64 start;
	u64 duration;
	u32 __data_loc_desc;
	int vector;
	char __data[0];
};

struct trace_event_raw_nmi_noise {
	struct trace_entry ent;
	u64 start;
	u64 duration;
	char __data[0];
};

struct trace_event_raw_sample_threshold {
	struct trace_entry ent;
	u64 start;
	u64 duration;
	u64 interference;
	char __data[0];
};

struct trace_event_data_offsets_thread_noise {};

struct trace_event_data_offsets_softirq_noise {};

struct trace_event_data_offsets_irq_noise {
	u32 desc;
};

struct trace_event_data_offsets_nmi_noise {};

struct trace_event_data_offsets_sample_threshold {};

typedef void (*btf_trace_thread_noise)(void *, struct task_struct *, u64, u64);

typedef void (*btf_trace_softirq_noise)(void *, int, u64, u64);

typedef void (*btf_trace_irq_noise)(void *, int, const char *, u64, u64);

typedef void (*btf_trace_nmi_noise)(void *, u64, u64);

typedef void (*btf_trace_sample_threshold)(void *, u64, u64, u64);

struct osnoise_instance {
	struct list_head list;
	struct trace_array *tr;
};

struct osn_nmi {
	u64 count;
	u64 delta_start;
};

struct osn_irq {
	u64 count;
	u64 arrival_time;
	u64 delta_start;
};

struct osn_softirq {
	u64 count;
	u64 arrival_time;
	u64 delta_start;
};

struct osn_thread {
	u64 count;
	u64 arrival_time;
	u64 delta_start;
};

struct osnoise_variables {
	struct task_struct *kthread;
	bool sampling;
	pid_t pid;
	struct osn_nmi nmi;
	struct osn_irq irq;
	struct osn_softirq softirq;
	struct osn_thread thread;
	local_t int_counter;
};

struct timerlat_variables {
	struct task_struct *kthread;
	struct hrtimer timer;
	u64 rel_period;
	u64 abs_period;
	bool tracing_thread;
	u64 count;
};

struct osnoise_sample {
	u64 runtime;
	u64 noise;
	u64 max_sample;
	int hw_count;
	int nmi_count;
	int irq_count;
	int softirq_count;
	int thread_count;
};

struct timerlat_sample {
	u64 timer_latency;
	unsigned int seqnum;
	int context;
};

struct osnoise_data {
	u64 sample_period;
	u64 sample_runtime;
	u64 stop_tracing;
	u64 stop_tracing_total;
	u64 timerlat_period;
	u64 print_stack;
	int timerlat_tracer;
	bool tainted;
};

struct trace_stack {
	int stack_size;
	int nr_entries;
	long unsigned int calls[256];
};

enum {
	TRACE_NOP_OPT_ACCEPT = 1,
	TRACE_NOP_OPT_REFUSE = 2,
};

struct ftrace_graph_ent_entry {
	struct trace_entry ent;
	struct ftrace_graph_ent graph_ent;
} __attribute__((packed));

struct ftrace_graph_ret_entry {
	struct trace_entry ent;
	struct ftrace_graph_ret ret;
};

struct fgraph_cpu_data {
	pid_t last_pid;
	int depth;
	int depth_irq;
	int ignore;
	long unsigned int enter_funcs[50];
};

struct fgraph_data {
	struct fgraph_cpu_data *cpu_data;
	struct ftrace_graph_ent_entry ent;
	struct ftrace_graph_ret_entry ret;
	int failed;
	int cpu;
	int: 32;
} __attribute__((packed));

enum {
	FLAGS_FILL_FULL = 268435456,
	FLAGS_FILL_START = 536870912,
	FLAGS_FILL_END = 805306368,
};

enum req_flag_bits {
	__REQ_FAILFAST_DEV = 8,
	__REQ_FAILFAST_TRANSPORT = 9,
	__REQ_FAILFAST_DRIVER = 10,
	__REQ_SYNC = 11,
	__REQ_META = 12,
	__REQ_PRIO = 13,
	__REQ_NOMERGE = 14,
	__REQ_IDLE = 15,
	__REQ_INTEGRITY = 16,
	__REQ_FUA = 17,
	__REQ_PREFLUSH = 18,
	__REQ_RAHEAD = 19,
	__REQ_BACKGROUND = 20,
	__REQ_NOWAIT = 21,
	__REQ_CGROUP_PUNT = 22,
	__REQ_POLLED = 23,
	__REQ_ALLOC_CACHE = 24,
	__REQ_SWAP = 25,
	__REQ_DRV = 26,
	__REQ_NOUNMAP = 27,
	__REQ_NR_BITS = 28,
};

struct sbitmap_word {
	long unsigned int word;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long unsigned int cleared;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct sbitmap {
	unsigned int depth;
	unsigned int shift;
	unsigned int map_nr;
	bool round_robin;
	struct sbitmap_word *map;
	unsigned int *alloc_hint;
};

struct sbq_wait_state {
	atomic_t wait_cnt;
	wait_queue_head_t wait;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
	long: 64;
};

struct sbitmap_queue {
	struct sbitmap sb;
	unsigned int wake_batch;
	atomic_t wake_index;
	struct sbq_wait_state *ws;
	atomic_t ws_active;
	unsigned int min_shallow_depth;
};

typedef __u32 req_flags_t;

enum mq_rq_state {
	MQ_RQ_IDLE = 0,
	MQ_RQ_IN_FLIGHT = 1,
	MQ_RQ_COMPLETE = 2,
};

enum rq_end_io_ret {
	RQ_END_IO_NONE = 0,
	RQ_END_IO_FREE = 1,
};

typedef enum rq_end_io_ret rq_end_io_fn(struct request *, blk_status_t);

struct request {
	struct request_queue *q;
	struct blk_mq_ctx *mq_ctx;
	struct blk_mq_hw_ctx *mq_hctx;
	blk_opf_t cmd_flags;
	req_flags_t rq_flags;
	int tag;
	int internal_tag;
	unsigned int timeout;
	unsigned int __data_len;
	sector_t __sector;
	struct bio *bio;
	struct bio *biotail;
	union {
		struct list_head queuelist;
		struct request *rq_next;
	};
	struct block_device *part;
	u64 start_time_ns;
	u64 io_start_time_ns;
	short unsigned int wbt_flags;
	short unsigned int stats_sectors;
	short unsigned int nr_phys_segments;
	short unsigned int nr_integrity_segments;
	short unsigned int write_hint;
	short unsigned int ioprio;
	enum mq_rq_state state;
	atomic_t ref;
	long unsigned int deadline;
	union {
		struct hlist_node hash;
		struct llist_node ipi_list;
	};
	union {
		struct rb_node rb_node;
		struct bio_vec special_vec;
		void *completion_data;
		int error_count;
	};
	union {
		struct {
			struct io_cq *icq;
			void *priv[2];
		} elv;
		struct {
			unsigned int seq;
			struct list_head list;
			rq_end_io_fn *saved_end_io;
		} flush;
	};
	union {
		struct __call_single_data csd;
		u64 fifo_time;
	};
	rq_end_io_fn *end_io;
	void *end_io_data;
};

struct blk_mq_tags {
	unsigned int nr_tags;
	unsigned int nr_reserved_tags;
	atomic_t active_queues;
	struct sbitmap_queue bitmap_tags;
	struct sbitmap_queue breserved_tags;
	struct request **rqs;
	struct request **static_rqs;
	struct list_head page_list;
	spinlock_t lock;
};

struct blk_trace {
	int trace_state;
	struct rchan *rchan;
	long unsigned int *sequence;
	unsigned char *msg_data;
	u16 act_mask;
	u64 start_lba;
	u64 end_lba;
	u32 pid;
	u32 dev;
	struct dentry *dir;
	struct list_head running_list;
	atomic_t dropped;
};

struct blk_flush_queue {
	unsigned int flush_pending_idx: 1;
	unsigned int flush_running_idx: 1;
	blk_status_t rq_status;
	long unsigned int flush_pending_since;
	struct list_head flush_queue[2];
	struct list_head flush_data_in_flight;
	struct request *flush_rq;
	spinlock_t mq_flush_lock;
};

struct blk_mq_queue_map {
	unsigned int *mq_map;
	unsigned int nr_queues;
	unsigned int queue_offset;
};

struct blk_mq_tag_set {
	struct blk_mq_queue_map map[6];
	unsigned int nr_maps;
	const struct blk_mq_ops *ops;
	unsigned int nr_hw_queues;
	unsigned int queue_depth;
	unsigned int reserved_tags;
	unsigned int cmd_size;
	int numa_node;
	unsigned int timeout;
	unsigned int flags;
	void *driver_data;
	struct blk_mq_tags **tags;
	struct blk_mq_tags *shared_tags;
	struct mutex tag_list_lock;
	struct list_head tag_list;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	long unsigned int rh_reserved5;
	long unsigned int rh_reserved6;
	long unsigned int rh_reserved7;
	long unsigned int rh_reserved8;
};

struct blk_mq_hw_ctx {
	struct {
		spinlock_t lock;
		struct list_head dispatch;
		long unsigned int state;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
		long: 64;
	};
	struct delayed_work run_work;
	cpumask_var_t cpumask;
	int next_cpu;
	int next_cpu_batch;
	long unsigned int flags;
	void *sched_data;
	struct request_queue *queue;
	struct blk_flush_queue *fq;
	void *driver_data;
	struct sbitmap ctx_map;
	struct blk_mq_ctx *dispatch_from;
	unsigned int dispatch_busy;
	short unsigned int type;
	short unsigned int nr_ctx;
	struct blk_mq_ctx **ctxs;
	spinlock_t dispatch_wait_lock;
	wait_queue_entry_t dispatch_wait;
	atomic_t wait_index;
	struct blk_mq_tags *tags;
	struct blk_mq_tags *sched_tags;
	long unsigned int queued;
	long unsigned int run;
	unsigned int numa_node;
	unsigned int queue_num;
	atomic_t nr_active;
	struct hlist_node cpuhp_online;
	struct hlist_node cpuhp_dead;
	struct kobject kobj;
	struct dentry *debugfs_dir;
	struct dentry *sched_debugfs_dir;
	struct list_head hctx_list;
	long unsigned int rh_reserved1;
	long unsigned int rh_reserved2;
	long unsigned int rh_reserved3;
	long unsigned int rh_reserved4;
	long unsigned int rh_reserved5;
	long unsigned int rh_reserved6;
	long unsigned int rh_reserved7;
	long unsigned int rh_reserved8;
	long: 64;
};

struct blk_mq_queue_data {
	struct request *rq;
	bool last;
	long unsigned int rh_reserved1;
};

enum blktrace_cat {
	BLK_TC_READ = 1,
	BLK_TC_WRITE = 2,
	BLK_TC_FLUSH = 4,
	BLK_TC_SYNC = 8,
	BLK_TC_SYNCIO = 8,
	BLK_TC_QUEUE = 16,
	BLK_TC_REQUEUE = 32,
	BLK_TC_ISSUE = 64,
	BLK_TC_COMPLETE = 128,
	BLK_TC_FS = 256,
	BLK_TC_PC = 512,
	BLK_TC_NOTIFY = 1024,
	BLK_TC_AHEAD = 2048,
	BLK_TC_META = 4096,
	BLK_TC_DISCARD = 8192,
	BLK_TC_DRV_DATA = 16384,
	BLK_TC_FUA = 32768,
	BLK_TC_END = 32768,
};

enum blktrace_act {
	__BLK_TA_QUEUE = 1,
	__BLK_TA_BACKMERGE = 2,
	__BLK_TA_FRONTMERGE = 3,
	__BLK_TA_GETRQ = 4,
	__BLK_TA_SLEEPRQ = 5,
	__BLK_TA_REQUEUE = 6,
	__BLK_TA_ISSUE = 7,
	__BLK_TA_COMPLETE = 8,
	__BLK_TA_PLUG = 9,
	__BLK_TA_UNPLUG_IO = 10,
	__BLK_TA_UNPLUG_TIMER = 11,
	__BLK_TA_INSERT = 12,
	__BLK_TA_SPLIT = 13,
	__BLK_TA_BOUNCE = 14,
	__BLK_TA_REMAP = 15,
	__BLK_TA_ABORT = 16,
	__BLK_TA_DRV_DATA = 17,
	__BLK_TA_CGROUP = 256,
};

enum blktrace_notify {
	__BLK_TN_PROCESS = 0,
	__BLK_TN_TIMESTAMP = 1,
	__BLK_TN_MESSAGE = 2,
	__BLK_TN_CGROUP = 256,
};

struct blk_io_trace {
	__u32 magic;
	__u32 sequence;
	__u64 time;
	__u64 sector;
	__u32 bytes;
	__u32 action;
	__u32 pid;
	__u32 device;
	__u32 cpu;
	__u16 error;
	__u16 pdu_len;
};

struct blk_io_trace_remap {
	__be32 device_from;
	__be32 device_to;
	__be64 sector_from;
};

enum {
	Blktrace_setup = 1,
	Blktrace_running = 2,
	Blktrace_stopped = 3,
};

struct blk_user_trace_setup {
	char name[32];
	__u16 act_mask;
	__u32 buf_size;
	__u32 buf_nr;
	__u64 start_lba;
	__u64 end_lba;
	__u32 pid;
};

typedef void blk_log_action_t(struct trace_iterator *, const char *, bool);

struct ftrace_event_field {
	struct list_head link;
	const char *name;
	const char *type;
	int filter_type;
	int offset;
	int size;
	int is_signed;
};

enum {
	FORMAT_HEADER = 1,
	FORMAT_FIELD_SEPERATOR = 2,
	FORMAT_PRINTFMT = 3,
};

struct event_probe_data {
	struct trace_event_file *file;
	long unsigned int count;
	int ref;
	bool enable;
};

struct syscall_trace_enter {
	struct trace_entry ent;
	int nr;
	long unsigned int args[0];
};

struct syscall_trace_exit {
	struct trace_entry ent;
	int nr;
	long int ret;
};

struct syscall_tp_t {
	long long unsigned int regs;
	long unsigned int syscall_nr;
	long unsigned int ret;
};

struct syscall_tp_t___2 {
	long long unsigned int regs;
	long unsigned int syscall_nr;
	long unsigned int args[6];
};

typedef long unsigned int perf_trace_t[1024];

struct filter_pred;

struct prog_entry {
	int target;
	int when_to_branch;
	struct filter_pred *pred;
};

typedef int (*filter_pred_fn_t)(struct filter_pred *, void *);

struct regex;

typedef int (*regex_match_func)(char *, struct regex *, int);

struct regex {
	char pattern[256];
	int len;
	int field_len;
	regex_match_func match;
};

struct filter_pred {
	filter_pred_fn_t fn;
	u64 val;
	struct regex regex;
	short unsigned int *ops;
	struct ftrace_event_field *field;
	int offset;
	int not;
	int op;
};

enum filter_op_ids {
	OP_GLOB = 0,
	OP_NE = 1,
	OP_EQ = 2,
	OP_LE = 3,
	OP_LT = 4,
	OP_GE = 5,
	OP_GT = 6,
	OP_BAND = 7,
	OP_MAX = 8,
};

enum {
	FILT_ERR_NONE = 0,
	FILT_ERR_INVALID_OP = 1,
	FILT_ERR_TOO_MANY_OPEN = 2,
	FILT_ERR_TOO_MANY_CLOSE = 3,
	FILT_ERR_MISSING_QUOTE = 4,
	FILT_ERR_OPERAND_TOO_LONG = 5,
	FILT_ERR_EXPECT_STRING = 6,
	FILT_ERR_EXPECT_DIGIT = 7,
	FILT_ERR_ILLEGAL_FIELD_OP = 8,
	FILT_ERR_FIELD_NOT_FOUND = 9,
	FILT_ERR_ILLEGAL_INTVAL = 10,
	FILT_ERR_BAD_SUBSYS_FILTER = 11,
	FILT_ERR_TOO_MANY_PREDS = 12,
	FILT_ERR_INVALID_FILTER = 13,
	FILT_ERR_IP_FIELD_ONLY = 14,
	FILT_ERR_INVALID_VALUE = 15,
	FILT_ERR_ERRNO = 16,
	FILT_ERR_NO_FILTER = 17,
};

struct filter_parse_error {
	int lasterr;
	int lasterr_pos;
};

typedef int (*parse_pred_fn)(const char *, void *, int, struct filter_parse_error *, struct filter_pred **);

enum {
	INVERT = 1,
	PROCESS_AND = 2,
	PROCESS_OR = 4,
};

enum {
	TOO_MANY_CLOSE = 4294967295,
	TOO_MANY_OPEN = 4294967294,
	MISSING_QUOTE = 4294967293,
};

struct filter_list {
	struct list_head list;
	struct event_filter *filter;
};

struct function_filter_data {
	struct ftrace_ops *ops;
	int first_filter;
	int first_notrace;
};

struct event_trigger_ops;

struct event_command;

struct event_trigger_data {
	long unsigned int count;
	int ref;
	struct event_trigger_ops *ops;
	struct event_command *cmd_ops;
	struct event_filter *filter;
	char *filter_str;
	void *private_data;
	bool paused;
	bool paused_tmp;
	struct list_head list;
	char *name;
	struct list_head named_list;
	struct event_trigger_data *named_data;
};

struct event_trigger_ops {
	void (*func)(struct event_trigger_data *, struct trace_buffer *, void *, struct ring_buffer_event *);
	int (*init)(struct event_trigger_ops *, struct event_trigger_data *);
	void (*free)(struct event_trigger_ops *, struct event_trigger_data *);
	int (*print)(struct seq_file *, struct event_trigger_ops *, struct event_trigger_data *);
};

struct event_command {
	struct list_head list;
	char *name;
	enum event_trigger_type trigger_type;
	int flags;
	int (*func)(struct event_command *, struct trace_event_file *, char *, char *, char *);
	int (*reg)(char *, struct event_trigger_ops *, struct event_trigger_data *, struct trace_event_file *);
	void (*unreg)(char *, struct event_trigger_ops *, struct event_trigger_data *, struct trace_event_file *);
	void (*unreg_all)(struct trace_event_file *);
	int (*set_filter)(char *, struct event_trigger_data *, struct trace_event_file *);
	struct event_trigger_ops * (*get_trigger_ops)(char *, char *);
};

struct enable_trigger_data {
	struct trace_event_file *file;
	bool enable;
	bool hist;
};

enum event_command_flags {
	EVENT_CMD_FL_POST_TRIGGER = 1,
	EVENT_CMD_FL_NEEDS_REC = 2,
};

enum dynevent_type {
	DYNEVENT_TYPE_SYNTH = 1,
	DYNEVENT_TYPE_KPROBE = 2,
	DYNEVENT_TYPE_NONE = 3,
};

struct dynevent_cmd;

typedef int (*dynevent_create_fn_t)(struct dynevent_cmd *);

struct dynevent_cmd {
	struct seq_buf seq;
	const char *event_name;
	unsigned int n_fields;
	enum dynevent_type type;
	dynevent_create_fn_t run_command;
	void *private_data;
};

struct synth_field_desc {
	const char *type;
	const char *name;
};

struct synth_trace_event;

struct synth_event;

struct synth_event_trace_state {
	struct trace_event_buffer fbuffer;
	struct synth_trace_event *entry;
	struct trace_buffer *buffer;
	struct synth_event *event;
	unsigned int cur_field;
	unsigned int n_u64;
	bool disabled;
	bool add_next;
	bool add_name;
};

struct synth_trace_event {
	struct trace_entry ent;
	u64 fields[0];
};

struct dyn_event_operations;

struct dyn_event {
	struct list_head list;
	struct dyn_event_operations *ops;
};

struct synth_field;

struct synth_event {
	struct dyn_event devent;
	int ref;
	char *name;
	struct synth_field **fields;
	unsigned int n_fields;
	struct synth_field **dynamic_fields;
	unsigned int n_dynamic_fields;
	unsigned int n_u64;
	struct trace_event_class class;
	struct trace_event_call call;
	struct tracepoint *tp;
	struct module *mod;
};

struct dyn_event_operations {
	struct list_head list;
	int (*create)(const char *);
	int (*show)(struct seq_file *, struct dyn_event *);
	bool (*is_busy)(struct dyn_event *);
	int (*free)(struct dyn_event *);
	bool (*match)(const char *, const char *, int, const char **, struct dyn_event *);
};

typedef int (*dynevent_check_arg_fn_t)(void *);

struct dynevent_arg {
	const char *str;
	char separator;
};

struct dynevent_arg_pair {
	const char *lhs;
	const char *rhs;
	char operator;
	char separator;
};

struct synth_field {
	char *type;
	char *name;
	size_t size;
	unsigned int offset;
	unsigned int field_pos;
	bool is_signed;
	bool is_string;
	bool is_dynamic;
};

enum {
	SYNTH_ERR_BAD_NAME = 0,
	SYNTH_ERR_INVALID_CMD = 1,
	SYNTH_ERR_INVALID_DYN_CMD = 2,
	SYNTH_ERR_EVENT_EXISTS = 3,
	SYNTH_ERR_TOO_MANY_FIELDS = 4,
	SYNTH_ERR_INCOMPLETE_TYPE = 5,
	SYNTH_ERR_INVALID_TYPE = 6,
	SYNTH_ERR_INVALID_FIELD = 7,
	SYNTH_ERR_INVALID_ARRAY_SPEC = 8,
};

enum {
	HIST_ERR_NONE = 0,
	HIST_ERR_DUPLICATE_VAR = 1,
	HIST_ERR_VAR_NOT_UNIQUE = 2,
	HIST_ERR_TOO_MANY_VARS = 3,
	HIST_ERR_MALFORMED_ASSIGNMENT = 4,
	HIST_ERR_NAMED_MISMATCH = 5,
	HIST_ERR_TRIGGER_EEXIST = 6,
	HIST_ERR_TRIGGER_ENOENT_CLEAR = 7,
	HIST_ERR_SET_CLOCK_FAIL = 8,
	HIST_ERR_BAD_FIELD_MODIFIER = 9,
	HIST_ERR_TOO_MANY_SUBEXPR = 10,
	HIST_ERR_TIMESTAMP_MISMATCH = 11,
	HIST_ERR_TOO_MANY_FIELD_VARS = 12,
	HIST_ERR_EVENT_FILE_NOT_FOUND = 13,
	HIST_ERR_HIST_NOT_FOUND = 14,
	HIST_ERR_HIST_CREATE_FAIL = 15,
	HIST_ERR_SYNTH_VAR_NOT_FOUND = 16,
	HIST_ERR_SYNTH_EVENT_NOT_FOUND = 17,
	HIST_ERR_SYNTH_TYPE_MISMATCH = 18,
	HIST_ERR_SYNTH_COUNT_MISMATCH = 19,
	HIST_ERR_FIELD_VAR_PARSE_FAIL = 20,
	HIST_ERR_VAR_CREATE_FIND_FAIL = 21,
	HIST_ERR_ONX_NOT_VAR = 22,
	HIST_ERR_ONX_VAR_NOT_FOUND = 23,
	HIST_ERR_ONX_VAR_CREATE_FAIL = 24,
	HIST_ERR_FIELD_VAR_CREATE_FAIL = 25,
	HIST_ERR_TOO_MANY_PARAMS = 26,
	HIST_ERR_PARAM_NOT_FOUND = 27,
	HIST_ERR_INVALID_PARAM = 28,
	HIST_ERR_ACTION_NOT_FOUND = 29,
	HIST_ERR_NO_SAVE_PARAMS = 30,
	HIST_ERR_TOO_MANY_SAVE_ACTIONS = 31,
	HIST_ERR_ACTION_MISMATCH = 32,
	HIST_ERR_NO_CLOSING_PAREN = 33,
	HIST_ERR_SUBSYS_NOT_FOUND = 34,
	HIST_ERR_INVALID_SUBSYS_EVENT = 35,
	HIST_ERR_INVALID_REF_KEY = 36,
	HIST_ERR_VAR_NOT_FOUND = 37,
	HIST_ERR_FIELD_NOT_FOUND = 38,
	HIST_ERR_EMPTY_ASSIGNMENT = 39,
	HIST_ERR_INVALID_SORT_MODIFIER = 40,
	HIST_ERR_EMPTY_SORT_FIELD = 41,
	HIST_ERR_TOO_MANY_SORT_FIELDS = 42,
	HIST_ERR_INVALID_SORT_FIELD = 43,
	HIST_ERR_INVALID_STR_OPERAND = 44,
};

struct hist_field;

typedef u64 (*hist_field_fn_t)(struct hist_field *, struct tracing_map_elt *, struct trace_buffer *, struct ring_buffer_event *, void *);

struct hist_trigger_data;

struct hist_var {
	char *name;
	struct hist_trigger_data *hist_data;
	unsigned int idx;
};

enum field_op_id {
	FIELD_OP_NONE = 0,
	FIELD_OP_PLUS = 1,
	FIELD_OP_MINUS = 2,
	FIELD_OP_UNARY_MINUS = 3,
};

struct hist_field {
	struct ftrace_event_field *field;
	long unsigned int flags;
	hist_field_fn_t fn;
	unsigned int ref;
	unsigned int size;
	unsigned int offset;
	unsigned int is_signed;
	const char *type;
	struct hist_field *operands[2];
	struct hist_trigger_data *hist_data;
	struct hist_var var;
	enum field_op_id operator;
	char *system;
	char *event_name;
	char *name;
	unsigned int var_ref_idx;
	bool read_once;
	unsigned int var_str_idx;
};

struct hist_trigger_attrs;

struct action_data;

struct field_var;

struct field_var_hist;

struct hist_trigger_data {
	struct hist_field *fields[22];
	unsigned int n_vals;
	unsigned int n_keys;
	unsigned int n_fields;
	unsigned int n_vars;
	unsigned int n_var_str;
	unsigned int key_size;
	struct tracing_map_sort_key sort_keys[2];
	unsigned int n_sort_keys;
	struct trace_event_file *event_file;
	struct hist_trigger_attrs *attrs;
	struct tracing_map *map;
	bool enable_timestamps;
	bool remove;
	struct hist_field *var_refs[16];
	unsigned int n_var_refs;
	struct action_data *actions[8];
	unsigned int n_actions;
	struct field_var *field_vars[32];
	unsigned int n_field_vars;
	unsigned int n_field_var_str;
	struct field_var_hist *field_var_hists[32];
	unsigned int n_field_var_hists;
	struct field_var *save_vars[32];
	unsigned int n_save_vars;
	unsigned int n_save_var_str;
};

enum hist_field_flags {
	HIST_FIELD_FL_HITCOUNT = 1,
	HIST_FIELD_FL_KEY = 2,
	HIST_FIELD_FL_STRING = 4,
	HIST_FIELD_FL_HEX = 8,
	HIST_FIELD_FL_SYM = 16,
	HIST_FIELD_FL_SYM_OFFSET = 32,
	HIST_FIELD_FL_EXECNAME = 64,
	HIST_FIELD_FL_SYSCALL = 128,
	HIST_FIELD_FL_STACKTRACE = 256,
	HIST_FIELD_FL_LOG2 = 512,
	HIST_FIELD_FL_TIMESTAMP = 1024,
	HIST_FIELD_FL_TIMESTAMP_USECS = 2048,
	HIST_FIELD_FL_VAR = 4096,
	HIST_FIELD_FL_EXPR = 8192,
	HIST_FIELD_FL_VAR_REF = 16384,
	HIST_FIELD_FL_CPU = 32768,
	HIST_FIELD_FL_ALIAS = 65536,
};

struct var_defs {
	unsigned int n_vars;
	char *name[16];
	char *expr[16];
};

struct hist_trigger_attrs {
	char *keys_str;
	char *vals_str;
	char *sort_key_str;
	char *name;
	char *clock;
	bool pause;
	bool cont;
	bool clear;
	bool ts_in_usecs;
	unsigned int map_bits;
	char *assignment_str[16];
	unsigned int n_assignments;
	char *action_str[8];
	unsigned int n_actions;
	struct var_defs var_defs;
};

struct field_var {
	struct hist_field *var;
	struct hist_field *val;
};

struct field_var_hist {
	struct hist_trigger_data *hist_data;
	char *cmd;
};

enum handler_id {
	HANDLER_ONMATCH = 1,
	HANDLER_ONMAX = 2,
	HANDLER_ONCHANGE = 3,
};

enum action_id {
	ACTION_SAVE = 1,
	ACTION_TRACE = 2,
	ACTION_SNAPSHOT = 3,
};

typedef void (*action_fn_t)(struct hist_trigger_data *, struct tracing_map_elt *, struct trace_buffer *, void *, struct ring_buffer_event *, void *, struct action_data *, u64 *);

typedef bool (*check_track_val_fn_t)(u64, u64);

struct action_data {
	enum handler_id handler;
	enum action_id action;
	char *action_name;
	action_fn_t fn;
	unsigned int n_params;
	char *params[32];
	unsigned int var_ref_idx[16];
	struct synth_event *synth_event;
	bool use_trace_keyword;
	char *synth_event_name;
	union {
		struct {
			char *event;
			char *event_system;
		} match_data;
		struct {
			char *var_str;
			struct hist_field *var_ref;
			struct hist_field *track_var;
			check_track_val_fn_t check_val;
			action_fn_t save_data;
		} track_data;
	};
};

struct track_data {
	u64 track_val;
	bool updated;
	unsigned int key_len;
	void *key;
	struct tracing_map_elt elt;
	struct action_data *action_data;
	struct hist_trigger_data *hist_data;
};

struct hist_elt_data {
	char *comm;
	u64 *var_ref_vals;
	char *field_var_str[32];
};

struct snapshot_context {
	struct tracing_map_elt *elt;
	void *key;
};

typedef void (*synth_probe_func_t)(void *, u64 *, unsigned int *);

struct hist_var_data {
	struct list_head list;
	struct hist_trigger_data *hist_data;
};

enum bpf_func_id {
	BPF_FUNC_unspec = 0,
	BPF_FUNC_map_lookup_elem = 1,
	BPF_FUNC_map_update_elem = 2,
	BPF_FUNC_map_delete_elem = 3,
	BPF_FUNC_probe_read = 4,
	BPF_FUNC_ktime_get_ns = 5,
	BPF_FUNC_trace_printk = 6,
	BPF_FUNC_get_prandom_u32 = 7,
	BPF_FUNC_get_smp_processor_id = 8,
	BPF_FUNC_skb_store_bytes = 9,
	BPF_FUNC_l3_csum_replace = 10,
	BPF_FUNC_l4_csum_replace = 11,
	BPF_FUNC_tail_call = 12,
	BPF_FUNC_clone_redirect = 13,
	BPF_FUNC_get_current_pid_tgid = 14,
	BPF_FUNC_get_current_uid_gid = 15,
	BPF_FUNC_get_current_comm = 16,
	BPF_FUNC_get_cgroup_classid = 17,
	BPF_FUNC_skb_vlan_push = 18,
	BPF_FUNC_skb_vlan_pop = 19,