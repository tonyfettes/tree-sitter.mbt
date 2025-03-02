typedef signed char           __int8_t;
typedef unsigned char           __uint8_t;
typedef short                   __int16_t;
typedef unsigned short          __uint16_t;
typedef int                     __int32_t;
typedef unsigned int            __uint32_t;
typedef long long               __int64_t;
typedef unsigned long long      __uint64_t;
typedef long                    __darwin_intptr_t;
typedef unsigned int            __darwin_natural_t;
typedef int                     __darwin_ct_rune_t;
typedef union {
	char            __mbstate8[128];
	long long       _mbstateL;
} __mbstate_t;
typedef __mbstate_t             __darwin_mbstate_t;
typedef long        __darwin_ptrdiff_t;
typedef unsigned long           __darwin_size_t;
typedef __builtin_va_list       __darwin_va_list;
typedef int          __darwin_wchar_t;
typedef __darwin_wchar_t        __darwin_rune_t;
typedef int           __darwin_wint_t;
typedef unsigned long           __darwin_clock_t;
typedef __uint32_t              __darwin_socklen_t;
typedef long                    __darwin_ssize_t;
typedef long                    __darwin_time_t;
typedef __int64_t       __darwin_blkcnt_t;
typedef __int32_t       __darwin_blksize_t;
typedef __int32_t       __darwin_dev_t;
typedef unsigned int    __darwin_fsblkcnt_t;
typedef unsigned int    __darwin_fsfilcnt_t;
typedef __uint32_t      __darwin_gid_t;
typedef __uint32_t      __darwin_id_t;
typedef __uint64_t      __darwin_ino64_t;
typedef __darwin_ino64_t __darwin_ino_t;
typedef __darwin_natural_t __darwin_mach_port_name_t;
typedef __darwin_mach_port_name_t __darwin_mach_port_t;
typedef __uint16_t      __darwin_mode_t;
typedef __int64_t       __darwin_off_t;
typedef __int32_t       __darwin_pid_t;
typedef __uint32_t      __darwin_sigset_t;
typedef __int32_t       __darwin_suseconds_t;
typedef __uint32_t      __darwin_uid_t;
typedef __uint32_t      __darwin_useconds_t;
typedef unsigned char   __darwin_uuid_t[16];
typedef char    __darwin_uuid_string_t[37];
struct __darwin_pthread_handler_rec {
	void (*__routine)(void *);
	void *__arg;
	struct __darwin_pthread_handler_rec *__next;
};
struct _opaque_pthread_attr_t {
	long __sig;
	char __opaque[56];
};
struct _opaque_pthread_cond_t {
	long __sig;
	char __opaque[40];
};
struct _opaque_pthread_condattr_t {
	long __sig;
	char __opaque[8];
};
struct _opaque_pthread_mutex_t {
	long __sig;
	char __opaque[56];
};
struct _opaque_pthread_mutexattr_t {
	long __sig;
	char __opaque[8];
};
struct _opaque_pthread_once_t {
	long __sig;
	char __opaque[8];
};
struct _opaque_pthread_rwlock_t {
	long __sig;
	char __opaque[192];
};
struct _opaque_pthread_rwlockattr_t {
	long __sig;
	char __opaque[16];
};
struct _opaque_pthread_t {
	long __sig;
	struct __darwin_pthread_handler_rec  *__cleanup_stack;
	char __opaque[8176];
};
typedef struct _opaque_pthread_attr_t __darwin_pthread_attr_t;
typedef struct _opaque_pthread_cond_t __darwin_pthread_cond_t;
typedef struct _opaque_pthread_condattr_t __darwin_pthread_condattr_t;
typedef unsigned long __darwin_pthread_key_t;
typedef struct _opaque_pthread_mutex_t __darwin_pthread_mutex_t;
typedef struct _opaque_pthread_mutexattr_t __darwin_pthread_mutexattr_t;
typedef struct _opaque_pthread_once_t __darwin_pthread_once_t;
typedef struct _opaque_pthread_rwlock_t __darwin_pthread_rwlock_t;
typedef struct _opaque_pthread_rwlockattr_t __darwin_pthread_rwlockattr_t;
typedef struct _opaque_pthread_t *__darwin_pthread_t;
typedef	int		__darwin_nl_item;
typedef	int		__darwin_wctrans_t;
typedef	__uint32_t	__darwin_wctype_t;
typedef signed char           int8_t;
typedef short                   int16_t;
typedef int                     int32_t;
typedef long long               int64_t;
typedef unsigned char           u_int8_t;
typedef unsigned short                  u_int16_t;
typedef unsigned int            u_int32_t;
typedef unsigned long long      u_int64_t;
typedef int64_t                 register_t;
typedef __darwin_intptr_t       intptr_t;
typedef unsigned long           uintptr_t;
typedef u_int64_t               user_addr_t;
typedef u_int64_t               user_size_t;
typedef int64_t                 user_ssize_t;
typedef int64_t                 user_long_t;
typedef u_int64_t               user_ulong_t;
typedef int64_t                 user_time_t;
typedef int64_t                 user_off_t;
typedef u_int64_t               syscall_arg_t;
typedef __darwin_va_list va_list;
typedef __darwin_size_t        size_t;
int     renameat(int, const char *, int, const char *) ;
int renamex_np(const char *, const char *, unsigned int)    ;
int renameatx_np(int, const char *, int, const char *, unsigned int)    ;
int	 printf(const char * restrict, ...) __attribute__((__format__ (__printf__, 1, 2)));
typedef __darwin_off_t		fpos_t;
struct __sbuf {
	unsigned char	*_base;
	int		_size;
};
struct __sFILEX;
typedef	struct __sFILE {
	unsigned char *_p;
	int	_r;
	int	_w;
	short	_flags;
	short	_file;
	struct	__sbuf _bf;
	int	_lbfsize;
	void	*_cookie;
	int	(*  _close)(void *);
	int	(*  _read) (void *, char *, int);
	fpos_t	(*  _seek) (void *, fpos_t, int);
	int	(*  _write)(void *, const char *, int);
	struct	__sbuf _ub;
	struct __sFILEX *_extra;
	int	_ur;
	unsigned char _ubuf[3];
	unsigned char _nbuf[1];
	struct	__sbuf _lb;
	int	_blksize;
	fpos_t	_offset;
} FILE;
extern FILE *__stdinp ;
extern FILE *__stdoutp ;
extern FILE *__stderrp ;
void	 clearerr(FILE *);
int	 fclose(FILE *);
int	 feof(FILE *);
int	 ferror(FILE *);
int	 fflush(FILE *);
int	 fgetc(FILE *);
int	 fgetpos(FILE * restrict, fpos_t *);
char	*fgets(char * restrict, int, FILE *);
FILE	*fopen(const char * restrict __filename, const char * restrict __mode) __asm("_" "fopen" );
int	 fprintf(FILE * restrict, const char * restrict, ...) __attribute__((__format__ (__printf__, 2, 3)));
int	 fputc(int, FILE *);
int	 fputs(const char * restrict, FILE * restrict) __asm("_" "fputs" );
size_t	 fread(void * restrict __ptr, size_t __size, size_t __nitems, FILE * restrict __stream);
FILE	*freopen(const char * restrict, const char * restrict,
				 FILE * restrict) __asm("_" "freopen" );
int	 fscanf(FILE * restrict, const char * restrict, ...) __attribute__((__format__ (__scanf__, 2, 3)));
int	 fseek(FILE *, long, int);
int	 fsetpos(FILE *, const fpos_t *);
long	 ftell(FILE *);
size_t	 fwrite(const void * restrict __ptr, size_t __size, size_t __nitems, FILE * restrict __stream) __asm("_" "fwrite" );
int	 getc(FILE *);
int	 getchar(void);
__attribute__((__deprecated__))
char	*gets(char *);
void	 perror(const char *) ;
int	 putc(int, FILE *);
int	 putchar(int);
int	 puts(const char *);
int	 remove(const char *);
int	 rename (const char *__old, const char *__new);
void	 rewind(FILE *);
int	 scanf(const char * restrict, ...) __attribute__((__format__ (__scanf__, 1, 2)));
void	 setbuf(FILE * restrict, char * restrict);
int	 setvbuf(FILE * restrict, char * restrict, int, size_t);
__attribute__((__deprecated__))
int	 sprintf(char * restrict, const char * restrict, ...) __attribute__((__format__ (__printf__, 2, 3)));
int	 sscanf(const char * restrict, const char * restrict, ...) __attribute__((__format__ (__scanf__, 2, 3)));
FILE	*tmpfile(void);
__attribute__((__deprecated__))
char	*tmpnam(char *);
int	 ungetc(int, FILE *);
int	 vfprintf(FILE * restrict, const char * restrict, va_list) __attribute__((__format__ (__printf__, 2, 0)));
int	 vprintf(const char * restrict, va_list) __attribute__((__format__ (__printf__, 1, 0)));
__attribute__((__deprecated__))
int	 vsprintf(char * restrict, const char * restrict, va_list) __attribute__((__format__ (__printf__, 2, 0)));
char    *ctermid(char *);
FILE	*fdopen(int, const char *) __asm("_" "fdopen" );
int	 fileno(FILE *);
int	 pclose(FILE *) ;
FILE	*popen(const char *, const char *) __asm("_" "popen" ) ;
int	__srget(FILE *);
int	__svfscanf(FILE *, const char *, va_list) __attribute__((__format__ (__scanf__, 2, 0)));
int	__swbuf(int, FILE *);
extern __inline __attribute__ ((__always_inline__)) int __sputc(int _c, FILE *_p) {
	if (--_p->_w >= 0 || (_p->_w >= _p->_lbfsize && (char)_c != '\n'))
		return (*_p->_p++ = _c);
	else
		return (__swbuf(_c, _p));
}
void	 flockfile(FILE *);
int	 ftrylockfile(FILE *);
void	 funlockfile(FILE *);
int	 getc_unlocked(FILE *);
int	 getchar_unlocked(void);
int	 putc_unlocked(int, FILE *);
int	 putchar_unlocked(int);
int	 getw(FILE *);
int	 putw(int, FILE *);
__attribute__((__deprecated__))
char	*tempnam(const char *__dir, const char *__prefix) __asm("_" "tempnam" );
typedef __darwin_off_t          off_t;
int	 fseeko(FILE * __stream, off_t __offset, int __whence);
off_t	 ftello(FILE * __stream);
int	 snprintf(char * restrict __str, size_t __size, const char * restrict __format, ...) __attribute__((__format__ (__printf__, 3, 4)));
int	 vfscanf(FILE * restrict __stream, const char * restrict __format, va_list) __attribute__((__format__ (__scanf__, 2, 0)));
int	 vscanf(const char * restrict __format, va_list) __attribute__((__format__ (__scanf__, 1, 0)));
int	 vsnprintf(char * restrict __str, size_t __size, const char * restrict __format, va_list) __attribute__((__format__ (__printf__, 3, 0)));
int	 vsscanf(const char * restrict __str, const char * restrict __format, va_list) __attribute__((__format__ (__scanf__, 2, 0)));
typedef __darwin_ssize_t        ssize_t;
int	dprintf(int, const char * restrict, ...) __attribute__((__format__ (__printf__, 2, 3))) ;
int	vdprintf(int, const char * restrict, va_list) __attribute__((__format__ (__printf__, 2, 0))) ;
ssize_t getdelim(char ** restrict __linep, size_t * restrict __linecapp, int __delimiter, FILE * restrict __stream) ;
ssize_t getline(char ** restrict __linep, size_t * restrict __linecapp, FILE * restrict __stream) ;
FILE *fmemopen(void * restrict __buf, size_t __size, const char * restrict __mode) ;
FILE *open_memstream(char **__bufp, size_t *__sizep) ;
extern const int sys_nerr;
extern const char *const sys_errlist[];
int	 asprintf(char ** restrict, const char * restrict, ...) __attribute__((__format__ (__printf__, 2, 3)));
char	*ctermid_r(char *);
char	*fgetln(FILE *, size_t *);
const char *fmtcheck(const char *, const char *) __attribute__((format_arg(2)));
int	 fpurge(FILE *);
void	 setbuffer(FILE *, char *, int);
int	 setlinebuf(FILE *);
int	 vasprintf(char ** restrict, const char * restrict, va_list) __attribute__((__format__ (__printf__, 2, 0)));
FILE	*funopen(const void *,
				 int (* )(void *, char *, int),
				 int (* )(void *, const char *, int),
				 fpos_t (* )(void *, fpos_t, int),
				 int (* )(void *));
typedef enum {
	P_ALL,
	P_PID,
	P_PGID
} idtype_t;
typedef __darwin_pid_t        pid_t;
typedef __darwin_id_t   id_t;
typedef int sig_atomic_t;
struct __darwin_arm_exception_state
{
	__uint32_t __exception;
	__uint32_t __fsr;
	__uint32_t __far;
};
struct __darwin_arm_exception_state64
{
	__uint64_t __far;
	__uint32_t __esr;
	__uint32_t __exception;
};
struct __darwin_arm_exception_state64_v2
{
	__uint64_t __far;
	__uint64_t __esr;
};
struct __darwin_arm_thread_state
{
	__uint32_t __r[13];
	__uint32_t __sp;
	__uint32_t __lr;
	__uint32_t __pc;
	__uint32_t __cpsr;
};
struct __darwin_arm_thread_state64
{
	__uint64_t __x[29];
	__uint64_t __fp;
	__uint64_t __lr;
	__uint64_t __sp;
	__uint64_t __pc;
	__uint32_t __cpsr;
	__uint32_t __pad;
};
struct __darwin_arm_vfp_state
{
	__uint32_t __r[64];
	__uint32_t __fpscr;
};
struct __darwin_arm_neon_state64
{
	__uint128_t __v[32];
	__uint32_t  __fpsr;
	__uint32_t  __fpcr;
};
struct __darwin_arm_neon_state
{
	__uint128_t __v[16];
	__uint32_t  __fpsr;
	__uint32_t  __fpcr;
};
struct __arm_pagein_state
{
	int __pagein_error;
};
struct __arm_legacy_debug_state
{
	__uint32_t __bvr[16];
	__uint32_t __bcr[16];
	__uint32_t __wvr[16];
	__uint32_t __wcr[16];
};
struct __darwin_arm_debug_state32
{
	__uint32_t __bvr[16];
	__uint32_t __bcr[16];
	__uint32_t __wvr[16];
	__uint32_t __wcr[16];
	__uint64_t __mdscr_el1;
};
struct __darwin_arm_debug_state64
{
	__uint64_t __bvr[16];
	__uint64_t __bcr[16];
	__uint64_t __wvr[16];
	__uint64_t __wcr[16];
	__uint64_t __mdscr_el1;
};
struct __darwin_arm_cpmu_state64
{
	__uint64_t __ctrs[16];
};
struct __darwin_mcontext32
{
	struct __darwin_arm_exception_state     __es;
	struct __darwin_arm_thread_state        __ss;
	struct __darwin_arm_vfp_state           __fs;
};
struct __darwin_mcontext64
{
	struct __darwin_arm_exception_state64   __es;
	struct __darwin_arm_thread_state64      __ss;
	struct __darwin_arm_neon_state64        __ns;
};
typedef struct __darwin_mcontext64      *mcontext_t;
typedef __darwin_pthread_attr_t pthread_attr_t;
struct __darwin_sigaltstack
{
	void            *ss_sp;
	__darwin_size_t ss_size;
	int             ss_flags;
};
typedef struct __darwin_sigaltstack     stack_t;
struct __darwin_ucontext
{
	int                     uc_onstack;
	__darwin_sigset_t       uc_sigmask;
	struct __darwin_sigaltstack     uc_stack;
	struct __darwin_ucontext        *uc_link;
	__darwin_size_t         uc_mcsize;
	struct __darwin_mcontext64        *uc_mcontext;
};
typedef struct __darwin_ucontext        ucontext_t;
typedef __darwin_sigset_t               sigset_t;
typedef __darwin_uid_t        uid_t;
union sigval {
	int     sival_int;
	void    *sival_ptr;
};
struct sigevent {
	int                             sigev_notify;
	int                             sigev_signo;
	union sigval    sigev_value;
	void                    (*sigev_notify_function)(union sigval);
	pthread_attr_t  *sigev_notify_attributes;
};
typedef struct __siginfo {
	int     si_signo;
	int     si_errno;
	int     si_code;
	pid_t   si_pid;
	uid_t   si_uid;
	int     si_status;
	void    *si_addr;
	union sigval si_value;
	long    si_band;
	unsigned long   __pad[7];
} siginfo_t;
union __sigaction_u {
	void    (*__sa_handler)(int);
	void    (*__sa_sigaction)(int, struct __siginfo *,
	    void *);
};
struct  __sigaction {
	union __sigaction_u __sigaction_u;
	void    (*sa_tramp)(void *, int, int, siginfo_t *, void *);
	sigset_t sa_mask;
	int     sa_flags;
};
struct  sigaction {
	union __sigaction_u __sigaction_u;
	sigset_t sa_mask;
	int     sa_flags;
};
typedef void (*sig_t)(int);
struct  sigvec {
	void    (*sv_handler)(int);
	int     sv_mask;
	int     sv_flags;
};
struct  sigstack {
	char    *ss_sp;
	int     ss_onstack;
};
void(*signal(int, void (*)(int)))(int);
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;
typedef int8_t           int_least8_t;
typedef int16_t         int_least16_t;
typedef int32_t         int_least32_t;
typedef int64_t         int_least64_t;
typedef uint8_t         uint_least8_t;
typedef uint16_t       uint_least16_t;
typedef uint32_t       uint_least32_t;
typedef uint64_t       uint_least64_t;
typedef int8_t            int_fast8_t;
typedef int16_t          int_fast16_t;
typedef int32_t          int_fast32_t;
typedef int64_t          int_fast64_t;
typedef uint8_t          uint_fast8_t;
typedef uint16_t        uint_fast16_t;
typedef uint32_t        uint_fast32_t;
typedef uint64_t        uint_fast64_t;
typedef long int intmax_t;
typedef long unsigned int uintmax_t;
struct timeval
{
	__darwin_time_t         tv_sec;
	__darwin_suseconds_t    tv_usec;
};
typedef __uint64_t      rlim_t;
struct  rusage {
	struct timeval ru_utime;
	struct timeval ru_stime;
	long    ru_maxrss;
	long    ru_ixrss;
	long    ru_idrss;
	long    ru_isrss;
	long    ru_minflt;
	long    ru_majflt;
	long    ru_nswap;
	long    ru_inblock;
	long    ru_oublock;
	long    ru_msgsnd;
	long    ru_msgrcv;
	long    ru_nsignals;
	long    ru_nvcsw;
	long    ru_nivcsw;
};
typedef void *rusage_info_t;
struct rusage_info_v0 {
	uint8_t  ri_uuid[16];
	uint64_t ri_user_time;
	uint64_t ri_system_time;
	uint64_t ri_pkg_idle_wkups;
	uint64_t ri_interrupt_wkups;
	uint64_t ri_pageins;
	uint64_t ri_wired_size;
	uint64_t ri_resident_size;
	uint64_t ri_phys_footprint;
	uint64_t ri_proc_start_abstime;
	uint64_t ri_proc_exit_abstime;
};
struct rusage_info_v1 {
	uint8_t  ri_uuid[16];
	uint64_t ri_user_time;
	uint64_t ri_system_time;
	uint64_t ri_pkg_idle_wkups;
	uint64_t ri_interrupt_wkups;
	uint64_t ri_pageins;
	uint64_t ri_wired_size;
	uint64_t ri_resident_size;
	uint64_t ri_phys_footprint;
	uint64_t ri_proc_start_abstime;
	uint64_t ri_proc_exit_abstime;
	uint64_t ri_child_user_time;
	uint64_t ri_child_system_time;
	uint64_t ri_child_pkg_idle_wkups;
	uint64_t ri_child_interrupt_wkups;
	uint64_t ri_child_pageins;
	uint64_t ri_child_elapsed_abstime;
};
struct rusage_info_v2 {
	uint8_t  ri_uuid[16];
	uint64_t ri_user_time;
	uint64_t ri_system_time;
	uint64_t ri_pkg_idle_wkups;
	uint64_t ri_interrupt_wkups;
	uint64_t ri_pageins;
	uint64_t ri_wired_size;
	uint64_t ri_resident_size;
	uint64_t ri_phys_footprint;
	uint64_t ri_proc_start_abstime;
	uint64_t ri_proc_exit_abstime;
	uint64_t ri_child_user_time;
	uint64_t ri_child_system_time;
	uint64_t ri_child_pkg_idle_wkups;
	uint64_t ri_child_interrupt_wkups;
	uint64_t ri_child_pageins;
	uint64_t ri_child_elapsed_abstime;
	uint64_t ri_diskio_bytesread;
	uint64_t ri_diskio_byteswritten;
};
struct rusage_info_v3 {
	uint8_t  ri_uuid[16];
	uint64_t ri_user_time;
	uint64_t ri_system_time;
	uint64_t ri_pkg_idle_wkups;
	uint64_t ri_interrupt_wkups;
	uint64_t ri_pageins;
	uint64_t ri_wired_size;
	uint64_t ri_resident_size;
	uint64_t ri_phys_footprint;
	uint64_t ri_proc_start_abstime;
	uint64_t ri_proc_exit_abstime;
	uint64_t ri_child_user_time;
	uint64_t ri_child_system_time;
	uint64_t ri_child_pkg_idle_wkups;
	uint64_t ri_child_interrupt_wkups;
	uint64_t ri_child_pageins;
	uint64_t ri_child_elapsed_abstime;
	uint64_t ri_diskio_bytesread;
	uint64_t ri_diskio_byteswritten;
	uint64_t ri_cpu_time_qos_default;
	uint64_t ri_cpu_time_qos_maintenance;
	uint64_t ri_cpu_time_qos_background;
	uint64_t ri_cpu_time_qos_utility;
	uint64_t ri_cpu_time_qos_legacy;
	uint64_t ri_cpu_time_qos_user_initiated;
	uint64_t ri_cpu_time_qos_user_interactive;
	uint64_t ri_billed_system_time;
	uint64_t ri_serviced_system_time;
};
struct rusage_info_v4 {
	uint8_t  ri_uuid[16];
	uint64_t ri_user_time;
	uint64_t ri_system_time;
	uint64_t ri_pkg_idle_wkups;
	uint64_t ri_interrupt_wkups;
	uint64_t ri_pageins;
	uint64_t ri_wired_size;
	uint64_t ri_resident_size;
	uint64_t ri_phys_footprint;
	uint64_t ri_proc_start_abstime;
	uint64_t ri_proc_exit_abstime;
	uint64_t ri_child_user_time;
	uint64_t ri_child_system_time;
	uint64_t ri_child_pkg_idle_wkups;
	uint64_t ri_child_interrupt_wkups;
	uint64_t ri_child_pageins;
	uint64_t ri_child_elapsed_abstime;
	uint64_t ri_diskio_bytesread;
	uint64_t ri_diskio_byteswritten;
	uint64_t ri_cpu_time_qos_default;
	uint64_t ri_cpu_time_qos_maintenance;
	uint64_t ri_cpu_time_qos_background;
	uint64_t ri_cpu_time_qos_utility;
	uint64_t ri_cpu_time_qos_legacy;
	uint64_t ri_cpu_time_qos_user_initiated;
	uint64_t ri_cpu_time_qos_user_interactive;
	uint64_t ri_billed_system_time;
	uint64_t ri_serviced_system_time;
	uint64_t ri_logical_writes;
	uint64_t ri_lifetime_max_phys_footprint;
	uint64_t ri_instructions;
	uint64_t ri_cycles;
	uint64_t ri_billed_energy;
	uint64_t ri_serviced_energy;
	uint64_t ri_interval_max_phys_footprint;
	uint64_t ri_runnable_time;
};
struct rusage_info_v5 {
	uint8_t  ri_uuid[16];
	uint64_t ri_user_time;
	uint64_t ri_system_time;
	uint64_t ri_pkg_idle_wkups;
	uint64_t ri_interrupt_wkups;
	uint64_t ri_pageins;
	uint64_t ri_wired_size;
	uint64_t ri_resident_size;
	uint64_t ri_phys_footprint;
	uint64_t ri_proc_start_abstime;
	uint64_t ri_proc_exit_abstime;
	uint64_t ri_child_user_time;
	uint64_t ri_child_system_time;
	uint64_t ri_child_pkg_idle_wkups;
	uint64_t ri_child_interrupt_wkups;
	uint64_t ri_child_pageins;
	uint64_t ri_child_elapsed_abstime;
	uint64_t ri_diskio_bytesread;
	uint64_t ri_diskio_byteswritten;
	uint64_t ri_cpu_time_qos_default;
	uint64_t ri_cpu_time_qos_maintenance;
	uint64_t ri_cpu_time_qos_background;
	uint64_t ri_cpu_time_qos_utility;
	uint64_t ri_cpu_time_qos_legacy;
	uint64_t ri_cpu_time_qos_user_initiated;
	uint64_t ri_cpu_time_qos_user_interactive;
	uint64_t ri_billed_system_time;
	uint64_t ri_serviced_system_time;
	uint64_t ri_logical_writes;
	uint64_t ri_lifetime_max_phys_footprint;
	uint64_t ri_instructions;
	uint64_t ri_cycles;
	uint64_t ri_billed_energy;
	uint64_t ri_serviced_energy;
	uint64_t ri_interval_max_phys_footprint;
	uint64_t ri_runnable_time;
	uint64_t ri_flags;
};
struct rusage_info_v6 {
	uint8_t  ri_uuid[16];
	uint64_t ri_user_time;
	uint64_t ri_system_time;
	uint64_t ri_pkg_idle_wkups;
	uint64_t ri_interrupt_wkups;
	uint64_t ri_pageins;
	uint64_t ri_wired_size;
	uint64_t ri_resident_size;
	uint64_t ri_phys_footprint;
	uint64_t ri_proc_start_abstime;
	uint64_t ri_proc_exit_abstime;
	uint64_t ri_child_user_time;
	uint64_t ri_child_system_time;
	uint64_t ri_child_pkg_idle_wkups;
	uint64_t ri_child_interrupt_wkups;
	uint64_t ri_child_pageins;
	uint64_t ri_child_elapsed_abstime;
	uint64_t ri_diskio_bytesread;
	uint64_t ri_diskio_byteswritten;
	uint64_t ri_cpu_time_qos_default;
	uint64_t ri_cpu_time_qos_maintenance;
	uint64_t ri_cpu_time_qos_background;
	uint64_t ri_cpu_time_qos_utility;
	uint64_t ri_cpu_time_qos_legacy;
	uint64_t ri_cpu_time_qos_user_initiated;
	uint64_t ri_cpu_time_qos_user_interactive;
	uint64_t ri_billed_system_time;
	uint64_t ri_serviced_system_time;
	uint64_t ri_logical_writes;
	uint64_t ri_lifetime_max_phys_footprint;
	uint64_t ri_instructions;
	uint64_t ri_cycles;
	uint64_t ri_billed_energy;
	uint64_t ri_serviced_energy;
	uint64_t ri_interval_max_phys_footprint;
	uint64_t ri_runnable_time;
	uint64_t ri_flags;
	uint64_t ri_user_ptime;
	uint64_t ri_system_ptime;
	uint64_t ri_pinstructions;
	uint64_t ri_pcycles;
	uint64_t ri_energy_nj;
	uint64_t ri_penergy_nj;
	uint64_t ri_secure_time_in_system;
	uint64_t ri_secure_ptime_in_system;
	uint64_t ri_neural_footprint;
	uint64_t ri_lifetime_max_neural_footprint;
	uint64_t ri_interval_max_neural_footprint;
	uint64_t ri_reserved[9];
};
typedef struct rusage_info_v6 rusage_info_current;
struct rlimit {
	rlim_t  rlim_cur;
	rlim_t  rlim_max;
};
struct proc_rlimit_control_wakeupmon {
	uint32_t wm_flags;
	int32_t wm_rate;
};
int     getpriority(int, id_t);
int     getiopolicy_np(int, int) ;
int     getrlimit(int, struct rlimit *) __asm("_" "getrlimit" );
int     getrusage(int, struct rusage *);
int     setpriority(int, id_t, int);
int     setiopolicy_np(int, int, int) ;
int     setrlimit(int, const struct rlimit *) __asm("_" "setrlimit" );
static inline
__uint16_t
_OSSwapInt16(
	__uint16_t        _data
	)
{
	return (__uint16_t)(_data << 8 | _data >> 8);
}
static inline
__uint32_t
_OSSwapInt32(
	__uint32_t        _data
	)
{
	_data = (((_data ^ (_data >> 16 | (_data << 16))) & 0xFF00FFFF) >> 8) ^ (_data >> 8 | _data << 24);
	return _data;
}
static inline
__uint64_t
_OSSwapInt64(
	__uint64_t        _data
	)
{
	union {
		__uint64_t _ull;
		__uint32_t _ul[2];
	} _u;
	_u._ul[0] = (__uint32_t)(_data >> 32);
	_u._ul[1] = (__uint32_t)(_data & 0xffffffff);
	_u._ul[0] = _OSSwapInt32(_u._ul[0]);
	_u._ul[1] = _OSSwapInt32(_u._ul[1]);
	return _u._ull;
}
union wait {
	int     w_status;
	struct {
		unsigned int    w_Termsig:7,
		    w_Coredump:1,
		    w_Retcode:8,
		    w_Filler:16;
	} w_T;
	struct {
		unsigned int    w_Stopval:8,
		    w_Stopsig:8,
		    w_Filler:16;
	} w_S;
};
pid_t   wait(int *) __asm("_" "wait" );
pid_t   waitpid(pid_t, int *, int) __asm("_" "waitpid" );
int     waitid(idtype_t, id_t, siginfo_t *, int) __asm("_" "waitid" );
pid_t   wait3(int *, int, struct rusage *);
pid_t   wait4(pid_t, int *, int, struct rusage *);
void	*alloca(size_t);
typedef __darwin_ct_rune_t ct_rune_t;
typedef __darwin_rune_t rune_t;
typedef __darwin_wchar_t wchar_t;
typedef struct {
	int quot;
	int rem;
} div_t;
typedef struct {
	long quot;
	long rem;
} ldiv_t;
typedef struct {
	long long quot;
	long long rem;
} lldiv_t;
extern int __mb_cur_max;
typedef unsigned long long malloc_type_id_t;
 void *  malloc_type_malloc(size_t size, malloc_type_id_t type_id)  ;
 void *  malloc_type_calloc(size_t count, size_t size, malloc_type_id_t type_id)  ;
 void  malloc_type_free(void *  ptr, malloc_type_id_t type_id);
 void *  malloc_type_realloc(void *  ptr, size_t size, malloc_type_id_t type_id)  ;
 void *  malloc_type_valloc(size_t size, malloc_type_id_t type_id)  ;
 void *  malloc_type_aligned_alloc(size_t alignment, size_t size, malloc_type_id_t type_id)  ;
 int   malloc_type_posix_memalign(void *  *memptr, size_t alignment, size_t size, malloc_type_id_t type_id)  ;
typedef struct _malloc_zone_t malloc_zone_t;
 void *  malloc_type_zone_malloc(malloc_zone_t *zone, size_t size, malloc_type_id_t type_id)  ;
 void *  malloc_type_zone_calloc(malloc_zone_t *zone, size_t count, size_t size, malloc_type_id_t type_id)  ;
 void  malloc_type_zone_free(malloc_zone_t *zone, void *  ptr, malloc_type_id_t type_id);
 void *  malloc_type_zone_realloc(malloc_zone_t *zone, void *  ptr, size_t size, malloc_type_id_t type_id)  ;
 void * malloc_type_zone_valloc(malloc_zone_t *zone, size_t size, malloc_type_id_t type_id)  ;
 void * malloc_type_zone_memalign(malloc_zone_t *zone, size_t alignment, size_t size, malloc_type_id_t type_id)  ;
void *  malloc(size_t __size)   ;
void *  calloc(size_t __count, size_t __size)   ;
void  free(void * );
void *  realloc(void *  __ptr, size_t __size)   ;
void *  reallocf(void *  __ptr, size_t __size)  ;
void *  valloc(size_t __size)   ;
void *  aligned_alloc(size_t __alignment, size_t __size)        ;
int   posix_memalign(void *  *__memptr, size_t __alignment, size_t __size)   ;
void	 abort(void)  __attribute__((__noreturn__));
int	 abs(int) __attribute__((__const__));
int	 atexit(void (* )(void));
int	at_quick_exit(void (*)(void));
double	 atof(const char *);
int	 atoi(const char *);
long	 atol(const char *);
long long
	 atoll(const char *);
void	*bsearch(const void *__key, const void *__base, size_t __nel,
	    size_t __width, int (*  __compar)(const void *, const void *));
div_t	 div(int, int) __attribute__((__const__));
void	 exit(int) __attribute__((__noreturn__));
char	*getenv(const char *);
long	 labs(long) __attribute__((__const__));
ldiv_t	 ldiv(long, long) __attribute__((__const__));
long long
	 llabs(long long);
lldiv_t	 lldiv(long long, long long);
int	 mblen(const char *__s, size_t __n);
size_t	 mbstowcs(wchar_t * restrict , const char * restrict, size_t);
int	 mbtowc(wchar_t * restrict, const char * restrict, size_t);
void	 qsort(void *__base, size_t __nel, size_t __width,
	    int (*  __compar)(const void *, const void *));
void	quick_exit(int) __attribute__((__noreturn__));
int	 rand(void) ;
void	 srand(unsigned) ;
double	 strtod(const char *, char **) __asm("_" "strtod" );
float	 strtof(const char *, char **) __asm("_" "strtof" );
long	 strtol(const char *__str, char **__endptr, int __base);
long double
	 strtold(const char *, char **);
long long
	 strtoll(const char *__str, char **__endptr, int __base);
unsigned long
	 strtoul(const char *__str, char **__endptr, int __base);
unsigned long long
	 strtoull(const char *__str, char **__endptr, int __base);
int	 system(const char *) __asm("_" "system" );
size_t	 wcstombs(char * restrict, const wchar_t * restrict, size_t);
int	 wctomb(char *, wchar_t);
void	_Exit(int) __attribute__((__noreturn__));
long	 a64l(const char *);
double	 drand48(void);
char	*ecvt(double, int, int *restrict, int *restrict);
double	 erand48(unsigned short[3]);
char	*fcvt(double, int, int *restrict, int *restrict);
char	*gcvt(double, int, char *);
int	 getsubopt(char **, char * const *, char **);
int	 grantpt(int);
char	*initstate(unsigned, char *, size_t);
long	 jrand48(unsigned short[3]) ;
char	*l64a(long);
void	 lcong48(unsigned short[7]);
long	 lrand48(void) ;
__attribute__((__deprecated__))
char	*mktemp(char *);
int	 mkstemp(char *);
long	 mrand48(void) ;
long	 nrand48(unsigned short[3]) ;
int	 posix_openpt(int);
char	*ptsname(int);
int ptsname_r(int fildes, char *buffer, size_t buflen) ;
int	 putenv(char *) __asm("_" "putenv" );
long	 random(void) ;
int	 rand_r(unsigned *) ;
char	*realpath(const char * restrict, char * restrict) __asm("_" "realpath" "$DARWIN_EXTSN");
unsigned short
	*seed48(unsigned short[3]);
int	 setenv(const char * __name, const char * __value, int __overwrite) __asm("_" "setenv" );
void	 setkey(const char *) __asm("_" "setkey" );
char	*setstate(const char *);
void	 srand48(long);
void	 srandom(unsigned);
int	 unlockpt(int);
int	 unsetenv(const char *) __asm("_" "unsetenv" );
typedef __darwin_dev_t        dev_t;
typedef __darwin_mode_t         mode_t;
uint32_t arc4random(void);
void	 arc4random_addrandom(unsigned char *  , int  )
    ;
void	 arc4random_buf(void * __buf, size_t __nbytes) ;
void	 arc4random_stir(void);
uint32_t
	 arc4random_uniform(uint32_t __upper_bound) ;
char	*cgetcap(char *, const char *, int);
int	 cgetclose(void);
int	 cgetent(char **, char **, const char *);
int	 cgetfirst(char **, char **);
int	 cgetmatch(const char *, const char *);
int	 cgetnext(char **, char **);
int	 cgetnum(char *, const char *, long *);
int	 cgetset(const char *);
int	 cgetstr(char *, const char *, char **);
int	 cgetustr(char *, const char *, char **);
int	 daemon(int, int) __asm("_" "daemon" )   ;
char	*devname(dev_t, mode_t);
char	*devname_r(dev_t, mode_t, char *buf, int len);
char	*getbsize(int *, long *);
int	 getloadavg(double [], int);
const char
	*getprogname(void);
void	 setprogname(const char *);
int	 heapsort(void *__base, size_t __nel, size_t __width,
	    int (*  __compar)(const void *, const void *));
int	 mergesort(void *__base, size_t __nel, size_t __width,
	    int (*  __compar)(const void *, const void *));
void	 psort(void *__base, size_t __nel, size_t __width,
	    int (*  __compar)(const void *, const void *))
	    ;
void	 psort_r(void *__base, size_t __nel, size_t __width, void *,
	    int (*  __compar)(void *, const void *, const void *))
	    ;
void	 qsort_r(void *__base, size_t __nel, size_t __width, void *,
	    int (*  __compar)(void *, const void *, const void *));
int	 radixsort(const unsigned char **__base, int __nel, const unsigned char *__table,
	    unsigned __endbyte);
int	rpmatch(const char *)
	;
int	 sradixsort(const unsigned char **__base, int __nel, const unsigned char *__table,
	    unsigned __endbyte);
void	 sranddev(void);
void	 srandomdev(void);
long long
	strtonum(const char *__numstr, long long __minval, long long __maxval, const char **__errstrp)
	;
long long
	 strtoq(const char *__str, char **__endptr, int __base);
unsigned long long
	 strtouq(const char *__str, char **__endptr, int __base);
extern char *suboptarg;
__attribute__((visibility("default"))) extern void *(*ts_current_malloc)(size_t size);
__attribute__((visibility("default"))) extern void *(*ts_current_calloc)(size_t count, size_t size);
__attribute__((visibility("default"))) extern void *(*ts_current_realloc)(void *ptr, size_t size);
__attribute__((visibility("default"))) extern void (*ts_current_free)(void *ptr);
#pragma GCC visibility push(default)
typedef uint16_t TSStateId;
typedef uint16_t TSSymbol;
typedef uint16_t TSFieldId;
typedef struct TSLanguage TSLanguage;
typedef struct TSLanguageMetadata TSLanguageMetadata;
typedef struct TSParser TSParser;
typedef struct TSTree TSTree;
typedef struct TSQuery TSQuery;
typedef struct TSQueryCursor TSQueryCursor;
typedef struct TSLookaheadIterator TSLookaheadIterator;
typedef uint32_t (*DecodeFunction)(
  const uint8_t *string,
  uint32_t length,
  int32_t *code_point
);
typedef enum TSInputEncoding {
  TSInputEncodingUTF8,
  TSInputEncodingUTF16LE,
  TSInputEncodingUTF16BE,
  TSInputEncodingCustom
} TSInputEncoding;
typedef enum TSSymbolType {
  TSSymbolTypeRegular,
  TSSymbolTypeAnonymous,
  TSSymbolTypeSupertype,
  TSSymbolTypeAuxiliary,
} TSSymbolType;
typedef struct TSPoint {
  uint32_t row;
  uint32_t column;
} TSPoint;
typedef struct TSRange {
  TSPoint start_point;
  TSPoint end_point;
  uint32_t start_byte;
  uint32_t end_byte;
} TSRange;
typedef struct TSInput {
  void *payload;
  const char *(*read)(void *payload, uint32_t byte_index, TSPoint position, uint32_t *bytes_read);
  TSInputEncoding encoding;
  DecodeFunction decode;
} TSInput;
typedef struct TSParseState {
  void *payload;
  uint32_t current_byte_offset;
  _Bool has_error;
} TSParseState;
typedef struct TSParseOptions {
  void *payload;
  _Bool (*progress_callback)(TSParseState *state);
} TSParseOptions;
typedef enum TSLogType {
  TSLogTypeParse,
  TSLogTypeLex,
} TSLogType;
typedef struct TSLogger {
  void *payload;
  void (*log)(void *payload, TSLogType log_type, const char *buffer);
} TSLogger;
typedef struct TSInputEdit {
  uint32_t start_byte;
  uint32_t old_end_byte;
  uint32_t new_end_byte;
  TSPoint start_point;
  TSPoint old_end_point;
  TSPoint new_end_point;
} TSInputEdit;
typedef struct TSNode {
  uint32_t context[4];
  const void *id;
  const TSTree *tree;
} TSNode;
typedef struct TSTreeCursor {
  const void *tree;
  const void *id;
  uint32_t context[3];
} TSTreeCursor;
typedef struct TSQueryCapture {
  TSNode node;
  uint32_t index;
} TSQueryCapture;
typedef enum TSQuantifier {
  TSQuantifierZero = 0,
  TSQuantifierZeroOrOne,
  TSQuantifierZeroOrMore,
  TSQuantifierOne,
  TSQuantifierOneOrMore,
} TSQuantifier;
typedef struct TSQueryMatch {
  uint32_t id;
  uint16_t pattern_index;
  uint16_t capture_count;
  const TSQueryCapture *captures;
} TSQueryMatch;
typedef enum TSQueryPredicateStepType {
  TSQueryPredicateStepTypeDone,
  TSQueryPredicateStepTypeCapture,
  TSQueryPredicateStepTypeString,
} TSQueryPredicateStepType;
typedef struct TSQueryPredicateStep {
  TSQueryPredicateStepType type;
  uint32_t value_id;
} TSQueryPredicateStep;
typedef enum TSQueryError {
  TSQueryErrorNone = 0,
  TSQueryErrorSyntax,
  TSQueryErrorNodeType,
  TSQueryErrorField,
  TSQueryErrorCapture,
  TSQueryErrorStructure,
  TSQueryErrorLanguage,
} TSQueryError;
typedef struct TSQueryCursorState {
  void *payload;
  uint32_t current_byte_offset;
} TSQueryCursorState;
typedef struct TSQueryCursorOptions {
  void *payload;
  _Bool (*progress_callback)(TSQueryCursorState *state);
} TSQueryCursorOptions;
typedef struct TSLanguageMetadata {
  uint8_t major_version;
  uint8_t minor_version;
  uint8_t patch_version;
} TSLanguageMetadata;
TSParser *ts_parser_new(void);
void ts_parser_delete(TSParser *self);
const TSLanguage *ts_parser_language(const TSParser *self);
_Bool ts_parser_set_language(TSParser *self, const TSLanguage *language);
_Bool ts_parser_set_included_ranges(
  TSParser *self,
  const TSRange *ranges,
  uint32_t count
);
const TSRange *ts_parser_included_ranges(
  const TSParser *self,
  uint32_t *count
);
TSTree *ts_parser_parse(
  TSParser *self,
  const TSTree *old_tree,
  TSInput input
);
TSTree* ts_parser_parse_with_options(
  TSParser *self,
  const TSTree *old_tree,
  TSInput input,
  TSParseOptions parse_options
);
TSTree *ts_parser_parse_string(
  TSParser *self,
  const TSTree *old_tree,
  const char *string,
  uint32_t length
);
TSTree *ts_parser_parse_string_encoding(
  TSParser *self,
  const TSTree *old_tree,
  const char *string,
  uint32_t length,
  TSInputEncoding encoding
);
void ts_parser_reset(TSParser *self);
void ts_parser_set_timeout_micros(TSParser *self, uint64_t timeout_micros);
uint64_t ts_parser_timeout_micros(const TSParser *self);
void ts_parser_set_cancellation_flag(TSParser *self, const size_t *flag);
const size_t *ts_parser_cancellation_flag(const TSParser *self);
void ts_parser_set_logger(TSParser *self, TSLogger logger);
TSLogger ts_parser_logger(const TSParser *self);
void ts_parser_print_dot_graphs(TSParser *self, int fd);
TSTree *ts_tree_copy(const TSTree *self);
void ts_tree_delete(TSTree *self);
TSNode ts_tree_root_node(const TSTree *self);
TSNode ts_tree_root_node_with_offset(
  const TSTree *self,
  uint32_t offset_bytes,
  TSPoint offset_extent
);
const TSLanguage *ts_tree_language(const TSTree *self);
TSRange *ts_tree_included_ranges(const TSTree *self, uint32_t *length);
void ts_tree_edit(TSTree *self, const TSInputEdit *edit);
TSRange *ts_tree_get_changed_ranges(
  const TSTree *old_tree,
  const TSTree *new_tree,
  uint32_t *length
);
void ts_tree_print_dot_graph(const TSTree *self, int file_descriptor);
const char *ts_node_type(TSNode self);
TSSymbol ts_node_symbol(TSNode self);
const TSLanguage *ts_node_language(TSNode self);
const char *ts_node_grammar_type(TSNode self);
TSSymbol ts_node_grammar_symbol(TSNode self);
uint32_t ts_node_start_byte(TSNode self);
TSPoint ts_node_start_point(TSNode self);
uint32_t ts_node_end_byte(TSNode self);
TSPoint ts_node_end_point(TSNode self);
char *ts_node_string(TSNode self);
_Bool ts_node_is_null(TSNode self);
_Bool ts_node_is_named(TSNode self);
_Bool ts_node_is_missing(TSNode self);
_Bool ts_node_is_extra(TSNode self);
_Bool ts_node_has_changes(TSNode self);
_Bool ts_node_has_error(TSNode self);
_Bool ts_node_is_error(TSNode self);
TSStateId ts_node_parse_state(TSNode self);
TSStateId ts_node_next_parse_state(TSNode self);
TSNode ts_node_parent(TSNode self);
TSNode ts_node_child_with_descendant(TSNode self, TSNode descendant);
TSNode ts_node_child(TSNode self, uint32_t child_index);
const char *ts_node_field_name_for_child(TSNode self, uint32_t child_index);
const char *ts_node_field_name_for_named_child(TSNode self, uint32_t named_child_index);
uint32_t ts_node_child_count(TSNode self);
TSNode ts_node_named_child(TSNode self, uint32_t child_index);
uint32_t ts_node_named_child_count(TSNode self);
TSNode ts_node_child_by_field_name(
  TSNode self,
  const char *name,
  uint32_t name_length
);
TSNode ts_node_child_by_field_id(TSNode self, TSFieldId field_id);
TSNode ts_node_next_sibling(TSNode self);
TSNode ts_node_prev_sibling(TSNode self);
TSNode ts_node_next_named_sibling(TSNode self);
TSNode ts_node_prev_named_sibling(TSNode self);
TSNode ts_node_first_child_for_byte(TSNode self, uint32_t byte);
TSNode ts_node_first_named_child_for_byte(TSNode self, uint32_t byte);
uint32_t ts_node_descendant_count(TSNode self);
TSNode ts_node_descendant_for_byte_range(TSNode self, uint32_t start, uint32_t end);
TSNode ts_node_descendant_for_point_range(TSNode self, TSPoint start, TSPoint end);
TSNode ts_node_named_descendant_for_byte_range(TSNode self, uint32_t start, uint32_t end);
TSNode ts_node_named_descendant_for_point_range(TSNode self, TSPoint start, TSPoint end);
void ts_node_edit(TSNode *self, const TSInputEdit *edit);
_Bool ts_node_eq(TSNode self, TSNode other);
TSTreeCursor ts_tree_cursor_new(TSNode node);
void ts_tree_cursor_delete(TSTreeCursor *self);
void ts_tree_cursor_reset(TSTreeCursor *self, TSNode node);
void ts_tree_cursor_reset_to(TSTreeCursor *dst, const TSTreeCursor *src);
TSNode ts_tree_cursor_current_node(const TSTreeCursor *self);
const char *ts_tree_cursor_current_field_name(const TSTreeCursor *self);
TSFieldId ts_tree_cursor_current_field_id(const TSTreeCursor *self);
_Bool ts_tree_cursor_goto_parent(TSTreeCursor *self);
_Bool ts_tree_cursor_goto_next_sibling(TSTreeCursor *self);
_Bool ts_tree_cursor_goto_previous_sibling(TSTreeCursor *self);
_Bool ts_tree_cursor_goto_first_child(TSTreeCursor *self);
_Bool ts_tree_cursor_goto_last_child(TSTreeCursor *self);
void ts_tree_cursor_goto_descendant(TSTreeCursor *self, uint32_t goal_descendant_index);
uint32_t ts_tree_cursor_current_descendant_index(const TSTreeCursor *self);
uint32_t ts_tree_cursor_current_depth(const TSTreeCursor *self);
int64_t ts_tree_cursor_goto_first_child_for_byte(TSTreeCursor *self, uint32_t goal_byte);
int64_t ts_tree_cursor_goto_first_child_for_point(TSTreeCursor *self, TSPoint goal_point);
TSTreeCursor ts_tree_cursor_copy(const TSTreeCursor *cursor);
TSQuery *ts_query_new(
  const TSLanguage *language,
  const char *source,
  uint32_t source_len,
  uint32_t *error_offset,
  TSQueryError *error_type
);
void ts_query_delete(TSQuery *self);
uint32_t ts_query_pattern_count(const TSQuery *self);
uint32_t ts_query_capture_count(const TSQuery *self);
uint32_t ts_query_string_count(const TSQuery *self);
uint32_t ts_query_start_byte_for_pattern(const TSQuery *self, uint32_t pattern_index);
uint32_t ts_query_end_byte_for_pattern(const TSQuery *self, uint32_t pattern_index);
const TSQueryPredicateStep *ts_query_predicates_for_pattern(
  const TSQuery *self,
  uint32_t pattern_index,
  uint32_t *step_count
);
_Bool ts_query_is_pattern_rooted(const TSQuery *self, uint32_t pattern_index);
_Bool ts_query_is_pattern_non_local(const TSQuery *self, uint32_t pattern_index);
_Bool ts_query_is_pattern_guaranteed_at_step(const TSQuery *self, uint32_t byte_offset);
const char *ts_query_capture_name_for_id(
  const TSQuery *self,
  uint32_t index,
  uint32_t *length
);
TSQuantifier ts_query_capture_quantifier_for_id(
  const TSQuery *self,
  uint32_t pattern_index,
  uint32_t capture_index
);
const char *ts_query_string_value_for_id(
  const TSQuery *self,
  uint32_t index,
  uint32_t *length
);
void ts_query_disable_capture(TSQuery *self, const char *name, uint32_t length);
void ts_query_disable_pattern(TSQuery *self, uint32_t pattern_index);
TSQueryCursor *ts_query_cursor_new(void);
void ts_query_cursor_delete(TSQueryCursor *self);
void ts_query_cursor_exec(TSQueryCursor *self, const TSQuery *query, TSNode node);
void ts_query_cursor_exec_with_options(
  TSQueryCursor *self,
  const TSQuery *query,
  TSNode node,
  const TSQueryCursorOptions *query_options
);
_Bool ts_query_cursor_did_exceed_match_limit(const TSQueryCursor *self);
uint32_t ts_query_cursor_match_limit(const TSQueryCursor *self);
void ts_query_cursor_set_match_limit(TSQueryCursor *self, uint32_t limit);
void ts_query_cursor_set_timeout_micros(TSQueryCursor *self, uint64_t timeout_micros);
uint64_t ts_query_cursor_timeout_micros(const TSQueryCursor *self);
_Bool ts_query_cursor_set_byte_range(TSQueryCursor *self, uint32_t start_byte, uint32_t end_byte);
_Bool ts_query_cursor_set_point_range(TSQueryCursor *self, TSPoint start_point, TSPoint end_point);
_Bool ts_query_cursor_next_match(TSQueryCursor *self, TSQueryMatch *match);
void ts_query_cursor_remove_match(TSQueryCursor *self, uint32_t match_id);
_Bool ts_query_cursor_next_capture(
  TSQueryCursor *self,
  TSQueryMatch *match,
  uint32_t *capture_index
);
void ts_query_cursor_set_max_start_depth(TSQueryCursor *self, uint32_t max_start_depth);
const TSLanguage *ts_language_copy(const TSLanguage *self);
void ts_language_delete(const TSLanguage *self);
uint32_t ts_language_symbol_count(const TSLanguage *self);
uint32_t ts_language_state_count(const TSLanguage *self);
TSSymbol ts_language_symbol_for_name(
  const TSLanguage *self,
  const char *string,
  uint32_t length,
  _Bool is_named
);
uint32_t ts_language_field_count(const TSLanguage *self);
const char *ts_language_field_name_for_id(const TSLanguage *self, TSFieldId id);
TSFieldId ts_language_field_id_for_name(const TSLanguage *self, const char *name, uint32_t name_length);
const TSSymbol *ts_language_supertypes(const TSLanguage *self, uint32_t *length);
const TSSymbol *ts_language_subtypes(
  const TSLanguage *self,
  TSSymbol supertype,
  uint32_t *length
);
const char *ts_language_symbol_name(const TSLanguage *self, TSSymbol symbol);
TSSymbolType ts_language_symbol_type(const TSLanguage *self, TSSymbol symbol);
uint32_t ts_language_version(const TSLanguage *self);
uint32_t ts_language_abi_version(const TSLanguage *self);
const TSLanguageMetadata *ts_language_metadata(const TSLanguage *self);
TSStateId ts_language_next_state(const TSLanguage *self, TSStateId state, TSSymbol symbol);
const char *ts_language_name(const TSLanguage *self);
TSLookaheadIterator *ts_lookahead_iterator_new(const TSLanguage *self, TSStateId state);
void ts_lookahead_iterator_delete(TSLookaheadIterator *self);
_Bool ts_lookahead_iterator_reset_state(TSLookaheadIterator *self, TSStateId state);
_Bool ts_lookahead_iterator_reset(TSLookaheadIterator *self, const TSLanguage *language, TSStateId state);
const TSLanguage *ts_lookahead_iterator_language(const TSLookaheadIterator *self);
_Bool ts_lookahead_iterator_next(TSLookaheadIterator *self);
TSSymbol ts_lookahead_iterator_current_symbol(const TSLookaheadIterator *self);
const char *ts_lookahead_iterator_current_symbol_name(const TSLookaheadIterator *self);
typedef struct wasm_engine_t TSWasmEngine;
typedef struct TSWasmStore TSWasmStore;
typedef enum {
  TSWasmErrorKindNone = 0,
  TSWasmErrorKindParse,
  TSWasmErrorKindCompile,
  TSWasmErrorKindInstantiate,
  TSWasmErrorKindAllocate,
} TSWasmErrorKind;
typedef struct {
  TSWasmErrorKind kind;
  char *message;
} TSWasmError;
TSWasmStore *ts_wasm_store_new(
  TSWasmEngine *engine,
  TSWasmError *error
);
void ts_wasm_store_delete(TSWasmStore *);
const TSLanguage *ts_wasm_store_load_language(
  TSWasmStore *,
  const char *name,
  const char *wasm,
  uint32_t wasm_len,
  TSWasmError *error
);
size_t ts_wasm_store_language_count(const TSWasmStore *);
_Bool ts_language_is_wasm(const TSLanguage *);
void ts_parser_set_wasm_store(TSParser *, TSWasmStore *);
TSWasmStore *ts_parser_take_wasm_store(TSParser *);
void ts_set_allocator(
  void *(*new_malloc)(size_t),
	void *(*new_calloc)(size_t, size_t),
	void *(*new_realloc)(void *, size_t),
	void (*new_free)(void *)
);
#pragma GCC visibility pop
static void *ts_malloc_default(size_t size) {
  void *result = malloc(size);
  if (size > 0 && !result) {
    fprintf(__stderrp, "tree-sitter failed to allocate %zu bytes", size);
    abort();
  }
  return result;
}
static void *ts_calloc_default(size_t count, size_t size) {
  void *result = calloc(count, size);
  if (count > 0 && !result) {
    fprintf(__stderrp, "tree-sitter failed to allocate %zu bytes", count * size);
    abort();
  }
  return result;
}
static void *ts_realloc_default(void *buffer, size_t size) {
  void *result = realloc(buffer, size);
  if (size > 0 && !result) {
    fprintf(__stderrp, "tree-sitter failed to reallocate %zu bytes", size);
    abort();
  }
  return result;
}
__attribute__((visibility("default"))) void *(*ts_current_malloc)(size_t) = ts_malloc_default;
__attribute__((visibility("default"))) void *(*ts_current_calloc)(size_t, size_t) = ts_calloc_default;
__attribute__((visibility("default"))) void *(*ts_current_realloc)(void *, size_t) = ts_realloc_default;
__attribute__((visibility("default"))) void (*ts_current_free)(void *) = free;
void ts_set_allocator(
  void *(*new_malloc)(size_t size),
  void *(*new_calloc)(size_t count, size_t size),
  void *(*new_realloc)(void *ptr, size_t size),
  void (*new_free)(void *ptr)
) {
  ts_current_malloc = new_malloc ? new_malloc : ts_malloc_default;
  ts_current_calloc = new_calloc ? new_calloc : ts_calloc_default;
  ts_current_realloc = new_realloc ? new_realloc : ts_realloc_default;
  ts_current_free = new_free ? new_free : free;
}
static inline TSPoint point__new(unsigned row, unsigned column) {
  TSPoint result = {row, column};
  return result;
}
static inline TSPoint point_add(TSPoint a, TSPoint b) {
  if (b.row > 0)
    return point__new(a.row + b.row, b.column);
  else
    return point__new(a.row, a.column + b.column);
}
static inline TSPoint point_sub(TSPoint a, TSPoint b) {
  if (a.row > b.row)
    return point__new(a.row - b.row, a.column);
  else
    return point__new(0, (a.column >= b.column) ? a.column - b.column : 0);
}
static inline _Bool point_lte(TSPoint a, TSPoint b) {
  return (a.row < b.row) || (a.row == b.row && a.column <= b.column);
}
static inline _Bool point_lt(TSPoint a, TSPoint b) {
  return (a.row < b.row) || (a.row == b.row && a.column < b.column);
}
static inline _Bool point_gt(TSPoint a, TSPoint b) {
  return (a.row > b.row) || (a.row == b.row && a.column > b.column);
}
static inline _Bool point_gte(TSPoint a, TSPoint b) {
  return (a.row > b.row) || (a.row == b.row && a.column >= b.column);
}
static inline _Bool point_eq(TSPoint a, TSPoint b) {
  return a.row == b.row && a.column == b.column;
}
typedef struct {
  uint32_t bytes;
  TSPoint extent;
} Length;
static const Length LENGTH_UNDEFINED = {0, {0, 1}};
static const Length LENGTH_MAX = {4294967295U, {4294967295U, 4294967295U}};
static inline _Bool length_is_undefined(Length length) {
  return length.bytes == 0 && length.extent.column != 0;
}
static inline Length length_min(Length len1, Length len2) {
  return (len1.bytes < len2.bytes) ? len1 : len2;
}
static inline Length length_add(Length len1, Length len2) {
  Length result;
  result.bytes = len1.bytes + len2.bytes;
  result.extent = point_add(len1.extent, len2.extent);
  return result;
}
static inline Length length_sub(Length len1, Length len2) {
  Length result;
  result.bytes = (len1.bytes >= len2.bytes) ? len1.bytes - len2.bytes : 0;
  result.extent = point_sub(len1.extent, len2.extent);
  return result;
}
static inline Length length_zero(void) {
  Length result = {0, {0, 0}};
  return result;
}
static inline Length length_saturating_sub(Length len1, Length len2) {
  if (len1.bytes > len2.bytes) {
    return length_sub(len1, len2);
  } else {
    return length_zero();
  }
}
void __assert_rtn(const char *, const char *, int, const char *) __attribute__((__noreturn__))  ;
void	*memchr(const void *__s, int __c, size_t __n);
int	 memcmp(const void *__s1, const void *__s2, size_t __n);
void	*memcpy(void *__dst, const void *__src, size_t __n);
void	*memmove(void *__dst, const void *__src, size_t __len);
void	*memset(void *__b, int __c, size_t __len);
char	*strcat(char *__s1, const char *__s2);
char	*strchr(const char *__s, int __c);
int	 strcmp(const char *__s1, const char *__s2);
int	 strcoll(const char *__s1, const char *__s2);
char	*strcpy(char *__dst, const char *__src);
size_t	 strcspn(const char *__s, const char *__charset);
char	*strerror(int __errnum) __asm("_" "strerror" );
size_t	 strlen(const char *__s);
char	*strncat(char *__s1, const char *__s2, size_t __n);
int	 strncmp(const char *__s1, const char *__s2, size_t __n);
char	*strncpy(char *__dst, const char *__src, size_t __n);
char	*strpbrk(const char *__s, const char *__charset);
char	*strrchr(const char *__s, int __c);
size_t	 strspn(const char *__s, const char *__charset);
char	*strstr(const char *__big, const char *__little);
char	*strtok(char *__str, const char *__sep);
size_t	 strxfrm(char *__s1, const char *__s2, size_t __n);
char	*strtok_r(char *__str, const char *__sep, char **__lasts);
int	 strerror_r(int __errnum, char *__strerrbuf, size_t __buflen);
char	*strdup(const char *__s1);
void	*memccpy(void *__dst, const void *__src, int __c, size_t __n);
char	*stpcpy(char *__dst, const char *__src);
char    *stpncpy(char *__dst, const char *__src, size_t __n) ;
char	*strndup(const char *__s1, size_t __n) ;
size_t   strnlen(const char *__s1, size_t __n) ;
char	*strsignal(int __sig);
typedef __darwin_size_t        rsize_t;
typedef int                    errno_t;
errno_t	memset_s(void *__s, rsize_t __smax, int __c, rsize_t __n) ;
void	*memmem(const void *__big, size_t __big_len, const void *__little, size_t __little_len) ;
void     memset_pattern4(void *__b, const void *__pattern4, size_t __len) ;
void     memset_pattern8(void *__b, const void *__pattern8, size_t __len) ;
void     memset_pattern16(void *__b, const void *__pattern16, size_t __len) ;
char	*strcasestr(const char *__big, const char *__little);
char	*strnstr(const char *__big, const char *__little, size_t __len);
size_t	 strlcat(char *__dst, const char *__source, size_t __size);
size_t	 strlcpy(char *__dst, const char *__source, size_t __size);
void	 strmode(int __mode, char *__bp);
char	*strsep(char **__stringp, const char *__delim);
void	 swab(const void * restrict, void * restrict, ssize_t);
int	timingsafe_bcmp(const void *__b1, const void *__b2, size_t __len);
int 	 strsignal_r(int __sig, char *__strsignalbuf, size_t __buflen);
int	 bcmp(const void *, const void *, size_t) ;
void	 bcopy(const void *, void *, size_t) ;
void	 bzero(void *, size_t) ;
char	*index(const char *, int) ;
char	*rindex(const char *, int) ;
int	 ffs(int);
int	 strcasecmp(const char *, const char *);
int	 strncasecmp(const char *, const char *, size_t);
int	 ffsl(long) ;
int	 ffsll(long long) ;
int	 fls(int) ;
int	 flsl(long) ;
int	 flsll(long long) ;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
typedef struct { void *contents; uint32_t size; uint32_t capacity; } Array;
static inline void _array__delete(Array *self) {
  if (self->contents) {
    ts_current_free(self->contents);
    self->contents = ((void *)0);
    self->size = 0;
    self->capacity = 0;
  }
}
static inline void _array__erase(Array *self, size_t element_size,
                                uint32_t index) {
  (__builtin_expect(!(index < self->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./././././array.h", 175, "index < self->size") : (void)0);
  char *contents = (char *)self->contents;
  memmove(contents + index * element_size, contents + (index + 1) * element_size,
          (self->size - index - 1) * element_size);
  self->size--;
}
static inline void _array__reserve(Array *self, size_t element_size, uint32_t new_capacity) {
  if (new_capacity > self->capacity) {
    if (self->contents) {
      self->contents = ts_current_realloc(self->contents, new_capacity * element_size);
    } else {
      self->contents = ts_current_malloc(new_capacity * element_size);
    }
    self->capacity = new_capacity;
  }
}
static inline void _array__assign(Array *self, const Array *other, size_t element_size) {
  _array__reserve(self, element_size, other->size);
  self->size = other->size;
  memcpy(self->contents, other->contents, self->size * element_size);
}
static inline void _array__swap(Array *self, Array *other) {
  Array swap = *other;
  *other = *self;
  *self = swap;
}
static inline void _array__grow(Array *self, uint32_t count, size_t element_size) {
  uint32_t new_size = self->size + count;
  if (new_size > self->capacity) {
    uint32_t new_capacity = self->capacity * 2;
    if (new_capacity < 8) new_capacity = 8;
    if (new_capacity < new_size) new_capacity = new_size;
    _array__reserve(self, element_size, new_capacity);
  }
}
static inline void _array__splice(Array *self, size_t element_size,
                                 uint32_t index, uint32_t old_count,
                                 uint32_t new_count, const void *elements) {
  uint32_t new_size = self->size + new_count - old_count;
  uint32_t old_end = index + old_count;
  uint32_t new_end = index + new_count;
  (__builtin_expect(!(old_end <= self->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./././././array.h", 226, "old_end <= self->size") : (void)0);
  _array__reserve(self, element_size, new_size);
  char *contents = (char *)self->contents;
  if (self->size > old_end) {
    memmove(
      contents + new_end * element_size,
      contents + old_end * element_size,
      (self->size - old_end) * element_size
    );
  }
  if (new_count > 0) {
    if (elements) {
      memcpy(
        (contents + index * element_size),
        elements,
        new_count * element_size
      );
    } else {
      memset(
        (contents + index * element_size),
        0,
        new_count * element_size
      );
    }
  }
  self->size += new_count - old_count;
}
#pragma GCC diagnostic pop
typedef struct {
  TSFieldId field_id;
  uint8_t child_index;
  _Bool inherited;
} TSFieldMapEntry;
typedef struct {
  uint16_t index;
  uint16_t length;
} TSMapSlice;
typedef struct {
  _Bool visible;
  _Bool named;
  _Bool supertype;
} TSSymbolMetadata;
typedef struct TSLexer TSLexer;
struct TSLexer {
  int32_t lookahead;
  TSSymbol result_symbol;
  void (*advance)(TSLexer *, _Bool);
  void (*mark_end)(TSLexer *);
  uint32_t (*get_column)(TSLexer *);
  _Bool (*is_at_included_range_start)(const TSLexer *);
  _Bool (*eof)(const TSLexer *);
  void (*log)(const TSLexer *, const char *, ...);
};
typedef enum {
  TSParseActionTypeShift,
  TSParseActionTypeReduce,
  TSParseActionTypeAccept,
  TSParseActionTypeRecover,
} TSParseActionType;
typedef union {
  struct {
    uint8_t type;
    TSStateId state;
    _Bool extra;
    _Bool repetition;
  } shift;
  struct {
    uint8_t type;
    uint8_t child_count;
    TSSymbol symbol;
    int16_t dynamic_precedence;
    uint16_t production_id;
  } reduce;
  uint8_t type;
} TSParseAction;
typedef struct {
  uint16_t lex_state;
  uint16_t external_lex_state;
} TSLexMode;
typedef struct {
  uint16_t lex_state;
  uint16_t external_lex_state;
  uint16_t reserved_word_set_id;
} TSLexerMode;
typedef union {
  TSParseAction action;
  struct {
    uint8_t count;
    _Bool reusable;
  } entry;
} TSParseActionEntry;
typedef struct {
  int32_t start;
  int32_t end;
} TSCharacterRange;
struct TSLanguage {
  uint32_t abi_version;
  uint32_t symbol_count;
  uint32_t alias_count;
  uint32_t token_count;
  uint32_t external_token_count;
  uint32_t state_count;
  uint32_t large_state_count;
  uint32_t production_id_count;
  uint32_t field_count;
  uint16_t max_alias_sequence_length;
  const uint16_t *parse_table;
  const uint16_t *small_parse_table;
  const uint32_t *small_parse_table_map;
  const TSParseActionEntry *parse_actions;
  const char * const *symbol_names;
  const char * const *field_names;
  const TSMapSlice *field_map_slices;
  const TSFieldMapEntry *field_map_entries;
  const TSSymbolMetadata *symbol_metadata;
  const TSSymbol *public_symbol_map;
  const uint16_t *alias_map;
  const TSSymbol *alias_sequences;
  const TSLexerMode *lex_modes;
  _Bool (*lex_fn)(TSLexer *, TSStateId);
  _Bool (*keyword_lex_fn)(TSLexer *, TSStateId);
  TSSymbol keyword_capture_token;
  struct {
    const _Bool *states;
    const TSSymbol *symbol_map;
    void *(*create)(void);
    void (*destroy)(void *);
    _Bool (*scan)(void *, TSLexer *, const _Bool *symbol_whitelist);
    unsigned (*serialize)(void *, char *);
    void (*deserialize)(void *, const char *, unsigned);
  } external_scanner;
  const TSStateId *primary_state_ids;
  const char *name;
  const TSSymbol *reserved_words;
  uint16_t max_reserved_word_set_size;
  uint32_t supertype_count;
  const TSSymbol *supertype_symbols;
  const TSMapSlice *supertype_map_slices;
  const TSSymbol *supertype_map_entries;
  TSLanguageMetadata metadata;
};
static inline _Bool set_contains(const TSCharacterRange *ranges, uint32_t len, int32_t lookahead) {
  uint32_t index = 0;
  uint32_t size = len - index;
  while (size > 1) {
    uint32_t half_size = size / 2;
    uint32_t mid_index = index + half_size;
    const TSCharacterRange *range = &ranges[mid_index];
    if (lookahead >= range->start && lookahead <= range->end) {
      return 1;
    } else if (lookahead > range->end) {
      index = mid_index;
    }
    size -= half_size;
  }
  const TSCharacterRange *range = &ranges[index];
  return (lookahead >= range->start && lookahead <= range->end);
}
typedef struct {
  union {
    char *long_data;
    char short_data[24];
  };
  uint32_t length;
} ExternalScannerState;
typedef struct SubtreeInlineData SubtreeInlineData;
struct SubtreeInlineData {
  _Bool is_inline : 1;
  _Bool visible : 1; _Bool named : 1; _Bool extra : 1; _Bool has_changes : 1; _Bool is_missing : 1; _Bool is_keyword : 1;
  uint8_t symbol;
  uint16_t parse_state;
  uint8_t padding_columns; uint8_t padding_rows : 4; uint8_t lookahead_bytes : 4; uint8_t padding_bytes; uint8_t size_bytes;
};
typedef struct {
  volatile uint32_t ref_count;
  Length padding;
  Length size;
  uint32_t lookahead_bytes;
  uint32_t error_cost;
  uint32_t child_count;
  TSSymbol symbol;
  TSStateId parse_state;
  _Bool visible : 1;
  _Bool named : 1;
  _Bool extra : 1;
  _Bool fragile_left : 1;
  _Bool fragile_right : 1;
  _Bool has_changes : 1;
  _Bool has_external_tokens : 1;
  _Bool has_external_scanner_state_change : 1;
  _Bool depends_on_column: 1;
  _Bool is_missing : 1;
  _Bool is_keyword : 1;
  union {
    struct {
      uint32_t visible_child_count;
      uint32_t named_child_count;
      uint32_t visible_descendant_count;
      int32_t dynamic_precedence;
      uint16_t repeat_depth;
      uint16_t production_id;
      struct {
        TSSymbol symbol;
        TSStateId parse_state;
      } first_leaf;
    };
    ExternalScannerState external_scanner_state;
    int32_t lookahead_char;
  };
} SubtreeHeapData;
typedef union {
  SubtreeInlineData data;
  const SubtreeHeapData *ptr;
} Subtree;
typedef union {
  SubtreeInlineData data;
  SubtreeHeapData *ptr;
} MutableSubtree;
typedef struct { Subtree *contents; uint32_t size; uint32_t capacity; } SubtreeArray;
typedef struct { MutableSubtree *contents; uint32_t size; uint32_t capacity; } MutableSubtreeArray;
typedef struct {
  MutableSubtreeArray free_trees;
  MutableSubtreeArray tree_stack;
} SubtreePool;
void ts_external_scanner_state_init(ExternalScannerState *self, const char *data, unsigned length);
const char *ts_external_scanner_state_data(const ExternalScannerState *self);
_Bool ts_external_scanner_state_eq(const ExternalScannerState *self, const char *buffer, unsigned length);
void ts_external_scanner_state_delete(ExternalScannerState *self);
void ts_subtree_array_copy(SubtreeArray self, SubtreeArray *dest);
void ts_subtree_array_clear(SubtreePool *pool, SubtreeArray *self);
void ts_subtree_array_delete(SubtreePool *pool, SubtreeArray *self);
void ts_subtree_array_remove_trailing_extras(SubtreeArray *self, SubtreeArray *destination);
void ts_subtree_array_reverse(SubtreeArray *self);
SubtreePool ts_subtree_pool_new(uint32_t capacity);
void ts_subtree_pool_delete(SubtreePool *self);
Subtree ts_subtree_new_leaf(
  SubtreePool *pool, TSSymbol symbol, Length padding, Length size,
  uint32_t lookahead_bytes, TSStateId parse_state,
  _Bool has_external_tokens, _Bool depends_on_column,
  _Bool is_keyword, const TSLanguage *language
);
Subtree ts_subtree_new_error(
  SubtreePool *pool, int32_t lookahead_char, Length padding, Length size,
  uint32_t bytes_scanned, TSStateId parse_state, const TSLanguage *language
);
MutableSubtree ts_subtree_new_node(
  TSSymbol symbol,
  SubtreeArray *chiildren,
  unsigned production_id,
  const TSLanguage *language
);
Subtree ts_subtree_new_error_node(
  SubtreeArray *children,
  _Bool extra,
  const TSLanguage * language
);
Subtree ts_subtree_new_missing_leaf(
  SubtreePool *pool,
  TSSymbol symbol,
  Length padding,
  uint32_t lookahead_bytes,
  const TSLanguage *language
);
MutableSubtree ts_subtree_make_mut(SubtreePool *pool, Subtree self);
void ts_subtree_retain(Subtree self);
void ts_subtree_release(SubtreePool *pool, Subtree self);
int ts_subtree_compare(Subtree left, Subtree right, SubtreePool *pool);
void ts_subtree_set_symbol(MutableSubtree *self, TSSymbol symbol, const TSLanguage *language);
void ts_subtree_compress(MutableSubtree self, unsigned count, const TSLanguage *language, MutableSubtreeArray *stack);
void ts_subtree_summarize_children(MutableSubtree self, const TSLanguage *language);
Subtree ts_subtree_edit(Subtree self, const TSInputEdit *edit, SubtreePool *pool);
char *ts_subtree_string(Subtree self, TSSymbol alias_symbol, _Bool alias_is_named, const TSLanguage *language, _Bool include_all);
void ts_subtree_print_dot_graph(Subtree self, const TSLanguage *language, FILE *f);
Subtree ts_subtree_last_external_token(Subtree tree);
const ExternalScannerState *ts_subtree_external_scanner_state(Subtree self);
_Bool ts_subtree_external_scanner_state_eq(Subtree self, Subtree other);
static inline TSSymbol ts_subtree_symbol(Subtree self) { return ((self).data.is_inline ? (self).data.symbol : (self).ptr->symbol); }
static inline _Bool ts_subtree_visible(Subtree self) { return ((self).data.is_inline ? (self).data.visible : (self).ptr->visible); }
static inline _Bool ts_subtree_named(Subtree self) { return ((self).data.is_inline ? (self).data.named : (self).ptr->named); }
static inline _Bool ts_subtree_extra(Subtree self) { return ((self).data.is_inline ? (self).data.extra : (self).ptr->extra); }
static inline _Bool ts_subtree_has_changes(Subtree self) { return ((self).data.is_inline ? (self).data.has_changes : (self).ptr->has_changes); }
static inline _Bool ts_subtree_missing(Subtree self) { return ((self).data.is_inline ? (self).data.is_missing : (self).ptr->is_missing); }
static inline _Bool ts_subtree_is_keyword(Subtree self) { return ((self).data.is_inline ? (self).data.is_keyword : (self).ptr->is_keyword); }
static inline TSStateId ts_subtree_parse_state(Subtree self) { return ((self).data.is_inline ? (self).data.parse_state : (self).ptr->parse_state); }
static inline uint32_t ts_subtree_lookahead_bytes(Subtree self) { return ((self).data.is_inline ? (self).data.lookahead_bytes : (self).ptr->lookahead_bytes); }
static inline size_t ts_subtree_alloc_size(uint32_t child_count) {
  return child_count * sizeof(Subtree) + sizeof(SubtreeHeapData);
}
static inline void ts_subtree_set_extra(MutableSubtree *self, _Bool is_extra) {
  if (self->data.is_inline) {
    self->data.extra = is_extra;
  } else {
    self->ptr->extra = is_extra;
  }
}
static inline TSSymbol ts_subtree_leaf_symbol(Subtree self) {
  if (self.data.is_inline) return self.data.symbol;
  if (self.ptr->child_count == 0) return self.ptr->symbol;
  return self.ptr->first_leaf.symbol;
}
static inline TSStateId ts_subtree_leaf_parse_state(Subtree self) {
  if (self.data.is_inline) return self.data.parse_state;
  if (self.ptr->child_count == 0) return self.ptr->parse_state;
  return self.ptr->first_leaf.parse_state;
}
static inline Length ts_subtree_padding(Subtree self) {
  if (self.data.is_inline) {
    Length result = {self.data.padding_bytes, {self.data.padding_rows, self.data.padding_columns}};
    return result;
  } else {
    return self.ptr->padding;
  }
}
static inline Length ts_subtree_size(Subtree self) {
  if (self.data.is_inline) {
    Length result = {self.data.size_bytes, {0, self.data.size_bytes}};
    return result;
  } else {
    return self.ptr->size;
  }
}
static inline Length ts_subtree_total_size(Subtree self) {
  return length_add(ts_subtree_padding(self), ts_subtree_size(self));
}
static inline uint32_t ts_subtree_total_bytes(Subtree self) {
  return ts_subtree_total_size(self).bytes;
}
static inline uint32_t ts_subtree_child_count(Subtree self) {
  return self.data.is_inline ? 0 : self.ptr->child_count;
}
static inline uint32_t ts_subtree_repeat_depth(Subtree self) {
  return self.data.is_inline ? 0 : self.ptr->repeat_depth;
}
static inline uint32_t ts_subtree_is_repetition(Subtree self) {
  return self.data.is_inline
    ? 0
    : !self.ptr->named && !self.ptr->visible && self.ptr->child_count != 0;
}
static inline uint32_t ts_subtree_visible_descendant_count(Subtree self) {
  return (self.data.is_inline || self.ptr->child_count == 0)
    ? 0
    : self.ptr->visible_descendant_count;
}
static inline uint32_t ts_subtree_visible_child_count(Subtree self) {
  if (ts_subtree_child_count(self) > 0) {
    return self.ptr->visible_child_count;
  } else {
    return 0;
  }
}
static inline uint32_t ts_subtree_error_cost(Subtree self) {
  if (ts_subtree_missing(self)) {
    return 110 + 500;
  } else {
    return self.data.is_inline ? 0 : self.ptr->error_cost;
  }
}
static inline int32_t ts_subtree_dynamic_precedence(Subtree self) {
  return (self.data.is_inline || self.ptr->child_count == 0) ? 0 : self.ptr->dynamic_precedence;
}
static inline uint16_t ts_subtree_production_id(Subtree self) {
  if (ts_subtree_child_count(self) > 0) {
    return self.ptr->production_id;
  } else {
    return 0;
  }
}
static inline _Bool ts_subtree_fragile_left(Subtree self) {
  return self.data.is_inline ? 0 : self.ptr->fragile_left;
}
static inline _Bool ts_subtree_fragile_right(Subtree self) {
  return self.data.is_inline ? 0 : self.ptr->fragile_right;
}
static inline _Bool ts_subtree_has_external_tokens(Subtree self) {
  return self.data.is_inline ? 0 : self.ptr->has_external_tokens;
}
static inline _Bool ts_subtree_has_external_scanner_state_change(Subtree self) {
  return self.data.is_inline ? 0 : self.ptr->has_external_scanner_state_change;
}
static inline _Bool ts_subtree_depends_on_column(Subtree self) {
  return self.data.is_inline ? 0 : self.ptr->depends_on_column;
}
static inline _Bool ts_subtree_is_fragile(Subtree self) {
  return self.data.is_inline ? 0 : (self.ptr->fragile_left || self.ptr->fragile_right);
}
static inline _Bool ts_subtree_is_error(Subtree self) {
  return ts_subtree_symbol(self) == ((TSSymbol)-1);
}
static inline _Bool ts_subtree_is_eof(Subtree self) {
  return ts_subtree_symbol(self) == 0;
}
static inline Subtree ts_subtree_from_mut(MutableSubtree self) {
  Subtree result;
  result.data = self.data;
  return result;
}
static inline MutableSubtree ts_subtree_to_mut_unsafe(Subtree self) {
  MutableSubtree result;
  result.data = self.data;
  return result;
}
typedef struct {
  const Subtree *subtree;
  Length position;
  uint32_t child_index;
  uint32_t structural_child_index;
  uint32_t descendant_index;
} TreeCursorEntry;
typedef struct {
  const TSTree *tree;
  struct { TreeCursorEntry *contents; uint32_t size; uint32_t capacity; } stack;
  TSSymbol root_alias_symbol;
} TreeCursor;
typedef enum {
  TreeCursorStepNone,
  TreeCursorStepHidden,
  TreeCursorStepVisible,
} TreeCursorStep;
void ts_tree_cursor_init(TreeCursor *self, TSNode node);
void ts_tree_cursor_current_status(
  const TSTreeCursor *_self,
  TSFieldId *field_id,
  _Bool *has_later_siblings,
  _Bool *has_later_named_siblings,
  _Bool *can_have_later_siblings_with_this_field,
  TSSymbol *supertypes,
  unsigned *supertype_count
);
TreeCursorStep ts_tree_cursor_goto_first_child_internal(TSTreeCursor *_self);
TreeCursorStep ts_tree_cursor_goto_next_sibling_internal(TSTreeCursor *_self);
static inline Subtree ts_tree_cursor_current_subtree(const TSTreeCursor *_self) {
  const TreeCursor *self = (const TreeCursor *)_self;
  TreeCursorEntry *last_entry = ((__builtin_expect(!((uint32_t)((&self->stack)->size - 1) < (&self->stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./././tree_cursor.h", 42, "(uint32_t)((&self->stack)->size - 1) < (&self->stack)->size") : (void)0), &(&self->stack)->contents[(&self->stack)->size - 1]);
  return *last_entry->subtree;
}
TSNode ts_tree_cursor_parent_node(const TSTreeCursor *_self);
typedef struct { TSRange *contents; uint32_t size; uint32_t capacity; } TSRangeArray;
void ts_range_array_get_changed_ranges(
  const TSRange *old_ranges, unsigned old_range_count,
  const TSRange *new_ranges, unsigned new_range_count,
  TSRangeArray *differences
);
_Bool ts_range_array_intersects(
  const TSRangeArray *self, unsigned start_index,
  uint32_t start_byte, uint32_t end_byte
);
unsigned ts_subtree_get_changed_ranges(
  const Subtree *old_tree, const Subtree *new_tree,
  TreeCursor *cursor1, TreeCursor *cursor2,
  const TSLanguage *language,
  const TSRangeArray *included_range_differences,
  TSRange **ranges
);
typedef struct {
  const TSParseAction *actions;
  uint32_t action_count;
  _Bool is_reusable;
} TableEntry;
typedef struct {
  const TSLanguage *language;
  const uint16_t *data;
  const uint16_t *group_end;
  TSStateId state;
  uint16_t table_value;
  uint16_t section_index;
  uint16_t group_count;
  _Bool is_small_state;
  const TSParseAction *actions;
  TSSymbol symbol;
  TSStateId next_state;
  uint16_t action_count;
} LookaheadIterator;
void ts_language_table_entry(const TSLanguage *self, TSStateId state, TSSymbol symbol, TableEntry *result);
TSLexerMode ts_language_lex_mode_for_state(const TSLanguage *self, TSStateId state);
_Bool ts_language_is_reserved_word(const TSLanguage *self, TSStateId state, TSSymbol symbol);
TSSymbolMetadata ts_language_symbol_metadata(const TSLanguage *self, TSSymbol symbol);
TSSymbol ts_language_public_symbol(const TSLanguage *self, TSSymbol symbol);
static inline const TSParseAction *ts_language_actions(
  const TSLanguage *self,
  TSStateId state,
  TSSymbol symbol,
  uint32_t *count
) {
  TableEntry entry;
  ts_language_table_entry(self, state, symbol, &entry);
  *count = entry.action_count;
  return entry.actions;
}
static inline _Bool ts_language_has_reduce_action(
  const TSLanguage *self,
  TSStateId state,
  TSSymbol symbol
) {
  TableEntry entry;
  ts_language_table_entry(self, state, symbol, &entry);
  return entry.action_count > 0 && entry.actions[0].type == TSParseActionTypeReduce;
}
static inline uint16_t ts_language_lookup(
  const TSLanguage *self,
  TSStateId state,
  TSSymbol symbol
) {
  if (state >= self->large_state_count) {
    uint32_t index = self->small_parse_table_map[state - self->large_state_count];
    const uint16_t *data = &self->small_parse_table[index];
    uint16_t group_count = *(data++);
    for (unsigned i = 0; i < group_count; i++) {
      uint16_t section_value = *(data++);
      uint16_t symbol_count = *(data++);
      for (unsigned j = 0; j < symbol_count; j++) {
        if (*(data++) == symbol) return section_value;
      }
    }
    return 0;
  } else {
    return self->parse_table[state * self->symbol_count + symbol];
  }
}
static inline _Bool ts_language_has_actions(
  const TSLanguage *self,
  TSStateId state,
  TSSymbol symbol
) {
  return ts_language_lookup(self, state, symbol) != 0;
}
static inline LookaheadIterator ts_language_lookaheads(
  const TSLanguage *self,
  TSStateId state
) {
  _Bool is_small_state = state >= self->large_state_count;
  const uint16_t *data;
  const uint16_t *group_end = ((void *)0);
  uint16_t group_count = 0;
  if (is_small_state) {
    uint32_t index = self->small_parse_table_map[state - self->large_state_count];
    data = &self->small_parse_table[index];
    group_end = data + 1;
    group_count = *data;
  } else {
    data = &self->parse_table[state * self->symbol_count] - 1;
  }
  return (LookaheadIterator) {
    .language = self,
    .data = data,
    .group_end = group_end,
    .group_count = group_count,
    .is_small_state = is_small_state,
    .symbol = 65535,
    .next_state = 0,
  };
}
static inline _Bool ts_lookahead_iterator__next(LookaheadIterator *self) {
  if (self->is_small_state) {
    self->data++;
    if (self->data == self->group_end) {
      if (self->group_count == 0) return 0;
      self->group_count--;
      self->table_value = *(self->data++);
      unsigned symbol_count = *(self->data++);
      self->group_end = self->data + symbol_count;
      self->symbol = *self->data;
    } else {
      self->symbol = *self->data;
      return 1;
    }
  }
  else {
    do {
      self->data++;
      self->symbol++;
      if (self->symbol >= self->language->symbol_count) return 0;
      self->table_value = *self->data;
    } while (!self->table_value);
  }
  if (self->symbol < self->language->token_count) {
    const TSParseActionEntry *entry = &self->language->parse_actions[self->table_value];
    self->action_count = entry->entry.count;
    self->actions = (const TSParseAction *)(entry + 1);
    self->next_state = 0;
  } else {
    self->action_count = 0;
    self->next_state = self->table_value;
  }
  return 1;
}
static inline _Bool ts_language_state_is_primary(
  const TSLanguage *self,
  TSStateId state
) {
  if (self->abi_version >= 14) {
    return state == self->primary_state_ids[state];
  } else {
    return 1;
  }
}
static inline const _Bool *ts_language_enabled_external_tokens(
  const TSLanguage *self,
  unsigned external_scanner_state
) {
  if (external_scanner_state == 0) {
    return ((void *)0);
  } else {
    return self->external_scanner.states + self->external_token_count * external_scanner_state;
  }
}
static inline const TSSymbol *ts_language_alias_sequence(
  const TSLanguage *self,
  uint32_t production_id
) {
  return production_id ?
    &self->alias_sequences[production_id * self->max_alias_sequence_length] :
    ((void *)0);
}
static inline TSSymbol ts_language_alias_at(
  const TSLanguage *self,
  uint32_t production_id,
  uint32_t child_index
) {
  return production_id ?
    self->alias_sequences[production_id * self->max_alias_sequence_length + child_index] :
    0;
}
static inline void ts_language_field_map(
  const TSLanguage *self,
  uint32_t production_id,
  const TSFieldMapEntry **start,
  const TSFieldMapEntry **end
) {
  if (self->field_count == 0) {
    *start = ((void *)0);
    *end = ((void *)0);
    return;
  }
  TSMapSlice slice = self->field_map_slices[production_id];
  *start = &self->field_map_entries[slice.index];
  *end = &self->field_map_entries[slice.index] + slice.length;
}
static inline void ts_language_aliases_for_symbol(
  const TSLanguage *self,
  TSSymbol original_symbol,
  const TSSymbol **start,
  const TSSymbol **end
) {
  *start = &self->public_symbol_map[original_symbol];
  *end = *start + 1;
  unsigned idx = 0;
  for (;;) {
    TSSymbol symbol = self->alias_map[idx++];
    if (symbol == 0 || symbol > original_symbol) break;
    uint16_t count = self->alias_map[idx++];
    if (symbol == original_symbol) {
      *start = &self->alias_map[idx];
      *end = &self->alias_map[idx + count];
      break;
    }
    idx += count;
  }
}
static inline void ts_language_write_symbol_as_dot_string(
  const TSLanguage *self,
  FILE *f,
  TSSymbol symbol
) {
  const char *name = ts_language_symbol_name(self, symbol);
  for (const char *chr = name; *chr; chr++) {
    switch (*chr) {
      case '"':
      case '\\':
        fputc('\\', f);
        fputc(*chr, f);
        break;
      case '\n':
        fputs("\\n", f);
        break;
      case '\t':
        fputs("\\t", f);
        break;
      default:
        fputc(*chr, f);
        break;
    }
  }
}
static void ts_range_array_add(
  TSRangeArray *self,
  Length start,
  Length end
) {
  if (self->size > 0) {
    TSRange *last_range = ((__builtin_expect(!((uint32_t)((self)->size - 1) < (self)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./get_changed_ranges.c", 16, "(uint32_t)((self)->size - 1) < (self)->size") : (void)0), &(self)->contents[(self)->size - 1]);
    if (start.bytes <= last_range->end_byte) {
      last_range->end_byte = end.bytes;
      last_range->end_point = end.extent;
      return;
    }
  }
  if (start.bytes < end.bytes) {
    TSRange range = { start.extent, end.extent, start.bytes, end.bytes };
    (_array__grow((Array *)(self), 1, (sizeof *(self)->contents)), (self)->contents[(self)->size++] = (range));
  }
}
_Bool ts_range_array_intersects(
  const TSRangeArray *self,
  unsigned start_index,
  uint32_t start_byte,
  uint32_t end_byte
) {
  for (unsigned i = start_index; i < self->size; i++) {
    TSRange *range = &self->contents[i];
    if (range->end_byte > start_byte) {
      if (range->start_byte >= end_byte) break;
      return 1;
    }
  }
  return 0;
}
void ts_range_array_get_changed_ranges(
  const TSRange *old_ranges, unsigned old_range_count,
  const TSRange *new_ranges, unsigned new_range_count,
  TSRangeArray *differences
) {
  unsigned new_index = 0;
  unsigned old_index = 0;
  Length current_position = length_zero();
  _Bool in_old_range = 0;
  _Bool in_new_range = 0;
  while (old_index < old_range_count || new_index < new_range_count) {
    const TSRange *old_range = &old_ranges[old_index];
    const TSRange *new_range = &new_ranges[new_index];
    Length next_old_position;
    if (in_old_range) {
      next_old_position = (Length) {old_range->end_byte, old_range->end_point};
    } else if (old_index < old_range_count) {
      next_old_position = (Length) {old_range->start_byte, old_range->start_point};
    } else {
      next_old_position = LENGTH_MAX;
    }
    Length next_new_position;
    if (in_new_range) {
      next_new_position = (Length) {new_range->end_byte, new_range->end_point};
    } else if (new_index < new_range_count) {
      next_new_position = (Length) {new_range->start_byte, new_range->start_point};
    } else {
      next_new_position = LENGTH_MAX;
    }
    if (next_old_position.bytes < next_new_position.bytes) {
      if (in_old_range != in_new_range) {
        ts_range_array_add(differences, current_position, next_old_position);
      }
      if (in_old_range) old_index++;
      current_position = next_old_position;
      in_old_range = !in_old_range;
    } else if (next_new_position.bytes < next_old_position.bytes) {
      if (in_old_range != in_new_range) {
        ts_range_array_add(differences, current_position, next_new_position);
      }
      if (in_new_range) new_index++;
      current_position = next_new_position;
      in_new_range = !in_new_range;
    } else {
      if (in_old_range != in_new_range) {
        ts_range_array_add(differences, current_position, next_new_position);
      }
      if (in_old_range) old_index++;
      if (in_new_range) new_index++;
      in_old_range = !in_old_range;
      in_new_range = !in_new_range;
      current_position = next_new_position;
    }
  }
}
typedef struct {
  TreeCursor cursor;
  const TSLanguage *language;
  unsigned visible_depth;
  _Bool in_padding;
} Iterator;
static Iterator iterator_new(
  TreeCursor *cursor,
  const Subtree *tree,
  const TSLanguage *language
) {
  ((&cursor->stack)->size = 0);
  (_array__grow((Array *)(&cursor->stack), 1, (sizeof *(&cursor->stack)->contents)), (&cursor->stack)->contents[(&cursor->stack)->size++] = (((TreeCursorEntry) { .subtree = tree, .position = length_zero(), .child_index = 0, .structural_child_index = 0, })));
  return (Iterator) {
    .cursor = *cursor,
    .language = language,
    .visible_depth = 1,
    .in_padding = 0,
  };
}
static _Bool iterator_done(Iterator *self) {
  return self->cursor.stack.size == 0;
}
static Length iterator_start_position(Iterator *self) {
  TreeCursorEntry entry = *((__builtin_expect(!((uint32_t)((&self->cursor.stack)->size - 1) < (&self->cursor.stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./get_changed_ranges.c", 138, "(uint32_t)((&self->cursor.stack)->size - 1) < (&self->cursor.stack)->size") : (void)0), &(&self->cursor.stack)->contents[(&self->cursor.stack)->size - 1]);
  if (self->in_padding) {
    return entry.position;
  } else {
    return length_add(entry.position, ts_subtree_padding(*entry.subtree));
  }
}
static Length iterator_end_position(Iterator *self) {
  TreeCursorEntry entry = *((__builtin_expect(!((uint32_t)((&self->cursor.stack)->size - 1) < (&self->cursor.stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./get_changed_ranges.c", 147, "(uint32_t)((&self->cursor.stack)->size - 1) < (&self->cursor.stack)->size") : (void)0), &(&self->cursor.stack)->contents[(&self->cursor.stack)->size - 1]);
  Length result = length_add(entry.position, ts_subtree_padding(*entry.subtree));
  if (self->in_padding) {
    return result;
  } else {
    return length_add(result, ts_subtree_size(*entry.subtree));
  }
}
static _Bool iterator_tree_is_visible(const Iterator *self) {
  TreeCursorEntry entry = *((__builtin_expect(!((uint32_t)((&self->cursor.stack)->size - 1) < (&self->cursor.stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./get_changed_ranges.c", 157, "(uint32_t)((&self->cursor.stack)->size - 1) < (&self->cursor.stack)->size") : (void)0), &(&self->cursor.stack)->contents[(&self->cursor.stack)->size - 1]);
  if (ts_subtree_visible(*entry.subtree)) return 1;
  if (self->cursor.stack.size > 1) {
    Subtree parent = *self->cursor.stack.contents[self->cursor.stack.size - 2].subtree;
    return ts_language_alias_at(
      self->language,
      parent.ptr->production_id,
      entry.structural_child_index
    ) != 0;
  }
  return 0;
}
static void iterator_get_visible_state(
  const Iterator *self,
  Subtree *tree,
  TSSymbol *alias_symbol,
  uint32_t *start_byte
) {
  uint32_t i = self->cursor.stack.size - 1;
  if (self->in_padding) {
    if (i == 0) return;
    i--;
  }
  for (; i + 1 > 0; i--) {
    TreeCursorEntry entry = self->cursor.stack.contents[i];
    if (i > 0) {
      const Subtree *parent = self->cursor.stack.contents[i - 1].subtree;
      *alias_symbol = ts_language_alias_at(
        self->language,
        parent->ptr->production_id,
        entry.structural_child_index
      );
    }
    if (ts_subtree_visible(*entry.subtree) || *alias_symbol) {
      *tree = *entry.subtree;
      *start_byte = entry.position.bytes;
      break;
    }
  }
}
static void iterator_ascend(Iterator *self) {
  if (iterator_done(self)) return;
  if (iterator_tree_is_visible(self) && !self->in_padding) self->visible_depth--;
  if (((__builtin_expect(!((uint32_t)((&self->cursor.stack)->size - 1) < (&self->cursor.stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./get_changed_ranges.c", 206, "(uint32_t)((&self->cursor.stack)->size - 1) < (&self->cursor.stack)->size") : (void)0), &(&self->cursor.stack)->contents[(&self->cursor.stack)->size - 1])->child_index > 0) self->in_padding = 0;
  self->cursor.stack.size--;
}
static _Bool iterator_descend(Iterator *self, uint32_t goal_position) {
  if (self->in_padding) return 0;
  _Bool did_descend = 0;
  do {
    did_descend = 0;
    TreeCursorEntry entry = *((__builtin_expect(!((uint32_t)((&self->cursor.stack)->size - 1) < (&self->cursor.stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./get_changed_ranges.c", 216, "(uint32_t)((&self->cursor.stack)->size - 1) < (&self->cursor.stack)->size") : (void)0), &(&self->cursor.stack)->contents[(&self->cursor.stack)->size - 1]);
    Length position = entry.position;
    uint32_t structural_child_index = 0;
    for (uint32_t i = 0, n = ts_subtree_child_count(*entry.subtree); i < n; i++) {
      const Subtree *child = &((*entry.subtree).data.is_inline ? ((void *)0) : (Subtree *)((*entry.subtree).ptr) - (*entry.subtree).ptr->child_count)[i];
      Length child_left = length_add(position, ts_subtree_padding(*child));
      Length child_right = length_add(child_left, ts_subtree_size(*child));
      if (child_right.bytes > goal_position) {
        (_array__grow((Array *)(&self->cursor.stack), 1, (sizeof *(&self->cursor.stack)->contents)), (&self->cursor.stack)->contents[(&self->cursor.stack)->size++] = (((TreeCursorEntry) { .subtree = child, .position = position, .child_index = i, .structural_child_index = structural_child_index, })));
        if (iterator_tree_is_visible(self)) {
          if (child_left.bytes > goal_position) {
            self->in_padding = 1;
          } else {
            self->visible_depth++;
          }
          return 1;
        }
        did_descend = 1;
        break;
      }
      position = child_right;
      if (!ts_subtree_extra(*child)) structural_child_index++;
    }
  } while (did_descend);
  return 0;
}
static void iterator_advance(Iterator *self) {
  if (self->in_padding) {
    self->in_padding = 0;
    if (iterator_tree_is_visible(self)) {
      self->visible_depth++;
    } else {
      iterator_descend(self, 0);
    }
    return;
  }
  for (;;) {
    if (iterator_tree_is_visible(self)) self->visible_depth--;
    TreeCursorEntry entry = ((&self->cursor.stack)->contents[--(&self->cursor.stack)->size]);
    if (iterator_done(self)) return;
    const Subtree *parent = ((__builtin_expect(!((uint32_t)((&self->cursor.stack)->size - 1) < (&self->cursor.stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./get_changed_ranges.c", 269, "(uint32_t)((&self->cursor.stack)->size - 1) < (&self->cursor.stack)->size") : (void)0), &(&self->cursor.stack)->contents[(&self->cursor.stack)->size - 1])->subtree;
    uint32_t child_index = entry.child_index + 1;
    if (ts_subtree_child_count(*parent) > child_index) {
      Length position = length_add(entry.position, ts_subtree_total_size(*entry.subtree));
      uint32_t structural_child_index = entry.structural_child_index;
      if (!ts_subtree_extra(*entry.subtree)) structural_child_index++;
      const Subtree *next_child = &((*parent).data.is_inline ? ((void *)0) : (Subtree *)((*parent).ptr) - (*parent).ptr->child_count)[child_index];
      (_array__grow((Array *)(&self->cursor.stack), 1, (sizeof *(&self->cursor.stack)->contents)), (&self->cursor.stack)->contents[(&self->cursor.stack)->size++] = (((TreeCursorEntry) { .subtree = next_child, .position = position, .child_index = child_index, .structural_child_index = structural_child_index, })));
      if (iterator_tree_is_visible(self)) {
        if (ts_subtree_padding(*next_child).bytes > 0) {
          self->in_padding = 1;
        } else {
          self->visible_depth++;
        }
      } else {
        iterator_descend(self, 0);
      }
      break;
    }
  }
}
typedef enum {
  IteratorDiffers,
  IteratorMayDiffer,
  IteratorMatches,
} IteratorComparison;
static IteratorComparison iterator_compare(
  const Iterator *old_iter,
  const Iterator *new_iter
) {
  Subtree old_tree = ((Subtree) {.ptr = ((void *)0)});
  Subtree new_tree = ((Subtree) {.ptr = ((void *)0)});
  uint32_t old_start = 0;
  uint32_t new_start = 0;
  TSSymbol old_alias_symbol = 0;
  TSSymbol new_alias_symbol = 0;
  iterator_get_visible_state(old_iter, &old_tree, &old_alias_symbol, &old_start);
  iterator_get_visible_state(new_iter, &new_tree, &new_alias_symbol, &new_start);
  if (!old_tree.ptr && !new_tree.ptr) return IteratorMatches;
  if (!old_tree.ptr || !new_tree.ptr) return IteratorDiffers;
  if (
    old_alias_symbol == new_alias_symbol &&
    ts_subtree_symbol(old_tree) == ts_subtree_symbol(new_tree)
  ) {
    if (old_start == new_start &&
        !ts_subtree_has_changes(old_tree) &&
        ts_subtree_symbol(old_tree) != ((TSSymbol)-1) &&
        ts_subtree_size(old_tree).bytes == ts_subtree_size(new_tree).bytes &&
        ts_subtree_parse_state(old_tree) != 65535 &&
        ts_subtree_parse_state(new_tree) != 65535 &&
        (ts_subtree_parse_state(old_tree) == 0) ==
        (ts_subtree_parse_state(new_tree) == 0)) {
      return IteratorMatches;
    } else {
      return IteratorMayDiffer;
    }
  }
  return IteratorDiffers;
}
unsigned ts_subtree_get_changed_ranges(
  const Subtree *old_tree, const Subtree *new_tree,
  TreeCursor *cursor1, TreeCursor *cursor2,
  const TSLanguage *language,
  const TSRangeArray *included_range_differences,
  TSRange **ranges
) {
  TSRangeArray results = { ((void *)0), 0, 0 };
  Iterator old_iter = iterator_new(cursor1, old_tree, language);
  Iterator new_iter = iterator_new(cursor2, new_tree, language);
  unsigned included_range_difference_index = 0;
  Length position = iterator_start_position(&old_iter);
  Length next_position = iterator_start_position(&new_iter);
  if (position.bytes < next_position.bytes) {
    ts_range_array_add(&results, position, next_position);
    position = next_position;
  } else if (position.bytes > next_position.bytes) {
    ts_range_array_add(&results, next_position, position);
    next_position = position;
  }
  do {
    IteratorComparison comparison = iterator_compare(&old_iter, &new_iter);
    if (comparison == IteratorMatches && ts_range_array_intersects(
      included_range_differences,
      included_range_difference_index,
      position.bytes,
      iterator_end_position(&old_iter).bytes
    )) {
      comparison = IteratorMayDiffer;
    }
    _Bool is_changed = 0;
    switch (comparison) {
      case IteratorMatches:
        next_position = iterator_end_position(&old_iter);
        break;
      case IteratorMayDiffer:
        if (iterator_descend(&old_iter, position.bytes)) {
          if (!iterator_descend(&new_iter, position.bytes)) {
            is_changed = 1;
            next_position = iterator_end_position(&old_iter);
          }
        } else if (iterator_descend(&new_iter, position.bytes)) {
          is_changed = 1;
          next_position = iterator_end_position(&new_iter);
        } else {
          next_position = length_min(
            iterator_end_position(&old_iter),
            iterator_end_position(&new_iter)
          );
        }
        break;
      case IteratorDiffers:
        is_changed = 1;
        next_position = length_min(
          iterator_end_position(&old_iter),
          iterator_end_position(&new_iter)
        );
        break;
    }
    while (
      !iterator_done(&old_iter) &&
      iterator_end_position(&old_iter).bytes <= next_position.bytes
    ) iterator_advance(&old_iter);
    while (
      !iterator_done(&new_iter) &&
      iterator_end_position(&new_iter).bytes <= next_position.bytes
    ) iterator_advance(&new_iter);
    while (old_iter.visible_depth > new_iter.visible_depth) {
      iterator_ascend(&old_iter);
    }
    while (new_iter.visible_depth > old_iter.visible_depth) {
      iterator_ascend(&new_iter);
    }
    if (is_changed) {
      ts_range_array_add(&results, position, next_position);
    }
    position = next_position;
    while (included_range_difference_index < included_range_differences->size) {
      const TSRange *range = &included_range_differences->contents[
        included_range_difference_index
      ];
      if (range->end_byte <= position.bytes) {
        included_range_difference_index++;
      } else {
        break;
      }
    }
  } while (!iterator_done(&old_iter) && !iterator_done(&new_iter));
  Length old_size = ts_subtree_total_size(*old_tree);
  Length new_size = ts_subtree_total_size(*new_tree);
  if (old_size.bytes < new_size.bytes) {
    ts_range_array_add(&results, old_size, new_size);
  } else if (new_size.bytes < old_size.bytes) {
    ts_range_array_add(&results, new_size, old_size);
  }
  *cursor1 = old_iter.cursor;
  *cursor2 = new_iter.cursor;
  *ranges = results.contents;
  return results.size;
}
_Bool ts_wasm_store_start(TSWasmStore *self, TSLexer *lexer, const TSLanguage *language);
void ts_wasm_store_reset(TSWasmStore *self);
_Bool ts_wasm_store_has_error(const TSWasmStore *self);
_Bool ts_wasm_store_call_lex_main(TSWasmStore *self, TSStateId state);
_Bool ts_wasm_store_call_lex_keyword(TSWasmStore *self, TSStateId state);
uint32_t ts_wasm_store_call_scanner_create(TSWasmStore *self);
void ts_wasm_store_call_scanner_destroy(TSWasmStore *self, uint32_t scanner_address);
_Bool ts_wasm_store_call_scanner_scan(TSWasmStore *self, uint32_t scanner_address, uint32_t valid_tokens_ix);
uint32_t ts_wasm_store_call_scanner_serialize(TSWasmStore *self, uint32_t scanner_address, char *buffer);
void ts_wasm_store_call_scanner_deserialize(TSWasmStore *self, uint32_t scanner, const char *buffer, unsigned length);
void ts_wasm_language_retain(const TSLanguage *self);
void ts_wasm_language_release(const TSLanguage *self);
const TSLanguage *ts_language_copy(const TSLanguage *self) {
  if (self && ts_language_is_wasm(self)) {
    ts_wasm_language_retain(self);
  }
  return self;
}
void ts_language_delete(const TSLanguage *self) {
  if (self && ts_language_is_wasm(self)) {
    ts_wasm_language_release(self);
  }
}
uint32_t ts_language_symbol_count(const TSLanguage *self) {
  return self->symbol_count + self->alias_count;
}
uint32_t ts_language_state_count(const TSLanguage *self) {
  return self->state_count;
}
const TSSymbol *ts_language_supertypes(const TSLanguage *self, uint32_t *length) {
  if (self->abi_version >= 15) {
    *length = self->supertype_count;
    return self->supertype_symbols;
  } else {
    *length = 0;
    return ((void *)0);
  }
}
const TSSymbol *ts_language_subtypes(
  const TSLanguage *self,
  TSSymbol supertype,
  uint32_t *length
) {
  if (self->abi_version < 15 || !ts_language_symbol_metadata(self, supertype).supertype) {
    *length = 0;
    return ((void *)0);
  }
  TSMapSlice slice = self->supertype_map_slices[supertype];
  *length = slice.length;
  return &self->supertype_map_entries[slice.index];
}
uint32_t ts_language_version(const TSLanguage *self) {
  return self->abi_version;
}
uint32_t ts_language_abi_version(const TSLanguage *self) {
  return self->abi_version;
}
const TSLanguageMetadata *ts_language_metadata(const TSLanguage *self) {
    return self->abi_version >= 15 ? &self->metadata : ((void *)0);
}
const char *ts_language_name(const TSLanguage *self) {
  return self->abi_version >= 15 ? self->name : ((void *)0);
}
uint32_t ts_language_field_count(const TSLanguage *self) {
  return self->field_count;
}
void ts_language_table_entry(
  const TSLanguage *self,
  TSStateId state,
  TSSymbol symbol,
  TableEntry *result
) {
  if (symbol == ((TSSymbol)-1) || symbol == (((TSSymbol)-1) - 1)) {
    result->action_count = 0;
    result->is_reusable = 0;
    result->actions = ((void *)0);
  } else {
    (__builtin_expect(!(symbol < self->token_count), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./language.c", 83, "symbol < self->token_count") : (void)0);
    uint32_t action_index = ts_language_lookup(self, state, symbol);
    const TSParseActionEntry *entry = &self->parse_actions[action_index];
    result->action_count = entry->entry.count;
    result->is_reusable = entry->entry.reusable;
    result->actions = (const TSParseAction *)(entry + 1);
  }
}
TSLexerMode ts_language_lex_mode_for_state(
   const TSLanguage *self,
   TSStateId state
) {
  if (self->abi_version < 15) {
    TSLexMode mode = ((const TSLexMode *)self->lex_modes)[state];
    return (TSLexerMode) {
      .lex_state = mode.lex_state,
      .external_lex_state = mode.external_lex_state,
      .reserved_word_set_id = 0,
    };
  } else {
    return self->lex_modes[state];
  }
}
_Bool ts_language_is_reserved_word(
  const TSLanguage *self,
  TSStateId state,
  TSSymbol symbol
) {
  TSLexerMode lex_mode = ts_language_lex_mode_for_state(self, state);
  if (lex_mode.reserved_word_set_id > 0) {
    unsigned start = lex_mode.reserved_word_set_id * self->max_reserved_word_set_size;
    unsigned end = start + self->max_reserved_word_set_size;
    for (unsigned i = start; i < end; i++) {
      if (self->reserved_words[i] == symbol) return 1;
      if (self->reserved_words[i] == 0) break;
    }
  }
  return 0;
}
TSSymbolMetadata ts_language_symbol_metadata(
  const TSLanguage *self,
  TSSymbol symbol
) {
  if (symbol == ((TSSymbol)-1))  {
    return (TSSymbolMetadata) {.visible = 1, .named = 1};
  } else if (symbol == (((TSSymbol)-1) - 1)) {
    return (TSSymbolMetadata) {.visible = 0, .named = 0};
  } else {
    return self->symbol_metadata[symbol];
  }
}
TSSymbol ts_language_public_symbol(
  const TSLanguage *self,
  TSSymbol symbol
) {
  if (symbol == ((TSSymbol)-1)) return symbol;
  return self->public_symbol_map[symbol];
}
TSStateId ts_language_next_state(
  const TSLanguage *self,
  TSStateId state,
  TSSymbol symbol
) {
  if (symbol == ((TSSymbol)-1) || symbol == (((TSSymbol)-1) - 1)) {
    return 0;
  } else if (symbol < self->token_count) {
    uint32_t count;
    const TSParseAction *actions = ts_language_actions(self, state, symbol, &count);
    if (count > 0) {
      TSParseAction action = actions[count - 1];
      if (action.type == TSParseActionTypeShift) {
        return action.shift.extra ? state : action.shift.state;
      }
    }
    return 0;
  } else {
    return ts_language_lookup(self, state, symbol);
  }
}
const char *ts_language_symbol_name(
  const TSLanguage *self,
  TSSymbol symbol
) {
  if (symbol == ((TSSymbol)-1)) {
    return "ERROR";
  } else if (symbol == (((TSSymbol)-1) - 1)) {
    return "_ERROR";
  } else if (symbol < ts_language_symbol_count(self)) {
    return self->symbol_names[symbol];
  } else {
    return ((void *)0);
  }
}
TSSymbol ts_language_symbol_for_name(
  const TSLanguage *self,
  const char *string,
  uint32_t length,
  _Bool is_named
) {
  if (!strncmp(string, "ERROR", length)) return ((TSSymbol)-1);
  uint16_t count = (uint16_t)ts_language_symbol_count(self);
  for (TSSymbol i = 0; i < count; i++) {
    TSSymbolMetadata metadata = ts_language_symbol_metadata(self, i);
    if ((!metadata.visible && !metadata.supertype) || metadata.named != is_named) continue;
    const char *symbol_name = self->symbol_names[i];
    if (!strncmp(symbol_name, string, length) && !symbol_name[length]) {
      return self->public_symbol_map[i];
    }
  }
  return 0;
}
TSSymbolType ts_language_symbol_type(
  const TSLanguage *self,
  TSSymbol symbol
) {
  TSSymbolMetadata metadata = ts_language_symbol_metadata(self, symbol);
  if (metadata.named && metadata.visible) {
    return TSSymbolTypeRegular;
  } else if (metadata.visible) {
    return TSSymbolTypeAnonymous;
  } else if (metadata.supertype) {
    return TSSymbolTypeSupertype;
  } else {
    return TSSymbolTypeAuxiliary;
  }
}
const char *ts_language_field_name_for_id(
  const TSLanguage *self,
  TSFieldId id
) {
  uint32_t count = ts_language_field_count(self);
  if (count && id <= count) {
    return self->field_names[id];
  } else {
    return ((void *)0);
  }
}
TSFieldId ts_language_field_id_for_name(
  const TSLanguage *self,
  const char *name,
  uint32_t name_length
) {
  uint16_t count = (uint16_t)ts_language_field_count(self);
  for (TSSymbol i = 1; i < count + 1; i++) {
    switch (strncmp(name, self->field_names[i], name_length)) {
      case 0:
        if (self->field_names[i][name_length] == 0) return i;
        break;
      case -1:
        return 0;
      default:
        break;
    }
  }
  return 0;
}
TSLookaheadIterator *ts_lookahead_iterator_new(const TSLanguage *self, TSStateId state) {
  if (state >= self->state_count) return ((void *)0);
  LookaheadIterator *iterator = ts_current_malloc(sizeof(LookaheadIterator));
  *iterator = ts_language_lookaheads(self, state);
  return (TSLookaheadIterator *)iterator;
}
void ts_lookahead_iterator_delete(TSLookaheadIterator *self) {
  ts_current_free(self);
}
_Bool ts_lookahead_iterator_reset_state(TSLookaheadIterator * self, TSStateId state) {
  LookaheadIterator *iterator = (LookaheadIterator *)self;
  if (state >= iterator->language->state_count) return 0;
  *iterator = ts_language_lookaheads(iterator->language, state);
  return 1;
}
const TSLanguage *ts_lookahead_iterator_language(const TSLookaheadIterator *self) {
  const LookaheadIterator *iterator = (const LookaheadIterator *)self;
  return iterator->language;
}
_Bool ts_lookahead_iterator_reset(TSLookaheadIterator *self, const TSLanguage *language, TSStateId state) {
  if (state >= language->state_count) return 0;
  LookaheadIterator *iterator = (LookaheadIterator *)self;
  *iterator = ts_language_lookaheads(language, state);
  return 1;
}
_Bool ts_lookahead_iterator_next(TSLookaheadIterator *self) {
  LookaheadIterator *iterator = (LookaheadIterator *)self;
  return ts_lookahead_iterator__next(iterator);
}
TSSymbol ts_lookahead_iterator_current_symbol(const TSLookaheadIterator *self) {
  const LookaheadIterator *iterator = (const LookaheadIterator *)self;
  return iterator->symbol;
}
const char *ts_lookahead_iterator_current_symbol_name(const TSLookaheadIterator *self) {
  const LookaheadIterator *iterator = (const LookaheadIterator *)self;
  return ts_language_symbol_name(iterator->language, iterator->symbol);
}
typedef struct {
  uint32_t value;
  _Bool valid;
} ColumnData;
typedef struct {
  TSLexer data;
  Length current_position;
  Length token_start_position;
  Length token_end_position;
  TSRange *included_ranges;
  const char *chunk;
  TSInput input;
  TSLogger logger;
  uint32_t included_range_count;
  uint32_t current_included_range_index;
  uint32_t chunk_start;
  uint32_t chunk_size;
  uint32_t lookahead_size;
  _Bool did_get_column;
  ColumnData column_data;
  char debug_buffer[1024];
} Lexer;
void ts_lexer_init(Lexer *self);
void ts_lexer_delete(Lexer *self);
void ts_lexer_set_input(Lexer *self, TSInput input);
void ts_lexer_reset(Lexer *self, Length position);
void ts_lexer_start(Lexer *self);
void ts_lexer_finish(Lexer *self, uint32_t *lookahead_end_byte);
void ts_lexer_mark_end(Lexer *self);
_Bool ts_lexer_set_included_ranges(Lexer *self, const TSRange *ranges, uint32_t count);
TSRange *ts_lexer_included_ranges(const Lexer *self, uint32_t *count);
typedef __darwin_ptrdiff_t ptrdiff_t;
typedef __darwin_wint_t wint_t;
typedef long double max_align_t;
typedef int8_t UBool;
    typedef uint16_t UChar;
    typedef uint16_t OldUChar;
typedef int32_t UChar32;
extern UChar32
utf8_nextCharSafeBody(const uint8_t *s, int32_t *pi, int32_t length, UChar32 c, UBool strict);
extern int32_t
utf8_appendCharSafeBody(uint8_t *s, int32_t i, int32_t length, UChar32 c, UBool *pIsError);
extern UChar32
utf8_prevCharSafeBody(const uint8_t *s, int32_t start, int32_t *pi, UChar32 c, UBool strict);
extern int32_t
utf8_back1SafeBody(const uint8_t *s, int32_t start, int32_t i);
struct _OSUnalignedU16 {
	volatile uint16_t __val;
} __attribute__((__packed__));
struct _OSUnalignedU32 {
	volatile uint32_t __val;
} __attribute__((__packed__));
struct _OSUnalignedU64 {
	volatile uint64_t __val;
} __attribute__((__packed__));
static inline
uint16_t
OSReadSwapInt16(
	const volatile void   * _base,
	uintptr_t       _offset
	)
{
	return _OSSwapInt16(((struct _OSUnalignedU16 *)((uintptr_t)_base + _offset))->__val);
}
static inline
uint32_t
OSReadSwapInt32(
	const volatile void   * _base,
	uintptr_t       _offset
	)
{
	return _OSSwapInt32(((struct _OSUnalignedU32 *)((uintptr_t)_base + _offset))->__val);
}
static inline
uint64_t
OSReadSwapInt64(
	const volatile void   * _base,
	uintptr_t       _offset
	)
{
	return _OSSwapInt64(((struct _OSUnalignedU64 *)((uintptr_t)_base + _offset))->__val);
}
static inline
void
OSWriteSwapInt16(
	volatile void   * _base,
	uintptr_t       _offset,
	uint16_t        _data
	)
{
	((struct _OSUnalignedU16 *)((uintptr_t)_base + _offset))->__val = _OSSwapInt16(_data);
}
static inline
void
OSWriteSwapInt32(
	volatile void   * _base,
	uintptr_t       _offset,
	uint32_t        _data
	)
{
	((struct _OSUnalignedU32 *)((uintptr_t)_base + _offset))->__val = _OSSwapInt32(_data);
}
static inline
void
OSWriteSwapInt64(
	volatile void    * _base,
	uintptr_t        _offset,
	uint64_t         _data
	)
{
	((struct _OSUnalignedU64 *)((uintptr_t)_base + _offset))->__val = _OSSwapInt64(_data);
}
enum {
	OSUnknownByteOrder,
	OSLittleEndian,
	OSBigEndian
};
static inline
int32_t
OSHostByteOrder(void)
{
	return OSLittleEndian;
}
static inline
uint16_t
_OSReadInt16(
	const volatile void               * base,
	uintptr_t                     byteOffset
	)
{
	return *(volatile uint16_t *)((uintptr_t)base + byteOffset);
}
static inline
uint32_t
_OSReadInt32(
	const volatile void               * base,
	uintptr_t                     byteOffset
	)
{
	return *(volatile uint32_t *)((uintptr_t)base + byteOffset);
}
static inline
uint64_t
_OSReadInt64(
	const volatile void               * base,
	uintptr_t                     byteOffset
	)
{
	return *(volatile uint64_t *)((uintptr_t)base + byteOffset);
}
static inline
void
_OSWriteInt16(
	volatile void               * base,
	uintptr_t                     byteOffset,
	uint16_t                      data
	)
{
	*(volatile uint16_t *)((uintptr_t)base + byteOffset) = data;
}
static inline
void
_OSWriteInt32(
	volatile void               * base,
	uintptr_t                     byteOffset,
	uint32_t                      data
	)
{
	*(volatile uint32_t *)((uintptr_t)base + byteOffset) = data;
}
static inline
void
_OSWriteInt64(
	volatile void               * base,
	uintptr_t                     byteOffset,
	uint64_t                      data
	)
{
	*(volatile uint64_t *)((uintptr_t)base + byteOffset) = data;
}
static const int32_t TS_DECODE_ERROR = (-1);
static inline uint32_t ts_decode_utf8(
  const uint8_t *string,
  uint32_t length,
  int32_t *code_point
) {
  uint32_t i = 0;
  do { (*code_point)=(uint8_t)(string)[(i)++]; if(!(((*code_point)&0x80)==0)) { uint8_t __t = 0; if((i)!=(length) && ((*code_point)>=0xe0 ? ((*code_point)<0xf0 ? "\x20\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x10\x30\x30"[(*code_point)&=0xf]&(1<<((__t=(string)[i])>>5)) && (__t&=0x3f, 1) : ((*code_point)-=0xf0)<=4 && "\x00\x00\x00\x00\x00\x00\x00\x00\x1E\x0F\x0F\x0F\x00\x00\x00\x00"[(__t=(string)[i])>>4]&(1<<(*code_point)) && ((*code_point)=((*code_point)<<6)|(__t&0x3f), ++(i)!=(length)) && (__t=(string)[i]-0x80)<=0x3f) && ((*code_point)=((*code_point)<<6)|__t, ++(i)!=(length)) : (*code_point)>=0xc2 && ((*code_point)&=0x1f, 1)) && (__t=(string)[i]-0x80)<=0x3f && ((*code_point)=((*code_point)<<6)|__t, ++(i), 1)) { } else { (*code_point)=((-1)); } } } while (0);
  return i;
}
static inline uint32_t ts_decode_utf16_le(
  const uint8_t *string,
  uint32_t length,
  int32_t *code_point
) {
  uint32_t i = 0;
  do { (*code_point)=((uint16_t)((((uint16_t *)string))[(i)++])); if((((*code_point)&0xfffffc00)==0xd800)) { uint16_t __c2; if((i)!=(length) && (((__c2=(((uint16_t *)string))[(i)])&0xfffffc00)==0xdc00)) { ++(i); (*code_point)=(((UChar32)((*code_point))<<10UL)+(UChar32)(__c2)-((0xd800<<10UL)+0xdc00-0x10000)); } } } while (0);
  return i * 2;
}
static inline uint32_t ts_decode_utf16_be(
  const uint8_t *string,
  uint32_t length,
  int32_t *code_point
) {
  uint32_t i = 0;
  do { (*code_point)=((__uint16_t)(__builtin_constant_p((((uint16_t *)string))[(i)++]) ? ((__uint16_t)((((__uint16_t)((((uint16_t *)string))[(i)++]) & 0xff00U) >> 8) | (((__uint16_t)((((uint16_t *)string))[(i)++]) & 0x00ffU) << 8))) : _OSSwapInt16((((uint16_t *)string))[(i)++]))); if((((*code_point)&0xfffffc00)==0xd800)) { uint16_t __c2; if((i)!=(length) && (((__c2=(((uint16_t *)string))[(i)])&0xfffffc00)==0xdc00)) { ++(i); (*code_point)=(((UChar32)((*code_point))<<10UL)+(UChar32)(__c2)-((0xd800<<10UL)+0xdc00-0x10000)); } } } while (0);
  return i * 2;
}
typedef __builtin_va_list va_list;
typedef va_list __gnuc_va_list;
static const int32_t BYTE_ORDER_MARK = 0xFEFF;
static const TSRange DEFAULT_RANGE = {
  .start_point = {
    .row = 0,
    .column = 0,
  },
  .end_point = {
    .row = 4294967295U,
    .column = 4294967295U,
  },
  .start_byte = 0,
  .end_byte = 4294967295U
};
static void ts_lexer__set_column_data(Lexer *self, uint32_t val) {
  self->column_data.valid = 1;
  self->column_data.value = val;
}
static void ts_lexer__increment_column_data(Lexer *self) {
  if (self->column_data.valid) {
    self->column_data.value++;
  }
}
static void ts_lexer__invalidate_column_data(Lexer *self) {
  self->column_data.valid = 0;
  self->column_data.value = 0;
}
static _Bool ts_lexer__eof(const TSLexer *_self) {
  Lexer *self = (Lexer *)_self;
  return self->current_included_range_index == self->included_range_count;
}
static void ts_lexer__clear_chunk(Lexer *self) {
  self->chunk = ((void *)0);
  self->chunk_size = 0;
  self->chunk_start = 0;
}
static void ts_lexer__get_chunk(Lexer *self) {
  self->chunk_start = self->current_position.bytes;
  self->chunk = self->input.read(
    self->input.payload,
    self->current_position.bytes,
    self->current_position.extent,
    &self->chunk_size
  );
  if (!self->chunk_size) {
    self->current_included_range_index = self->included_range_count;
    self->chunk = ((void *)0);
  }
}
static void ts_lexer__get_lookahead(Lexer *self) {
  uint32_t position_in_chunk = self->current_position.bytes - self->chunk_start;
  uint32_t size = self->chunk_size - position_in_chunk;
  if (size == 0) {
    self->lookahead_size = 1;
    self->data.lookahead = '\0';
    return;
  }
  const uint8_t *chunk = (const uint8_t *)self->chunk + position_in_chunk;
  DecodeFunction decode =
    self->input.encoding == TSInputEncodingUTF8    ? ts_decode_utf8     :
    self->input.encoding == TSInputEncodingUTF16LE ? ts_decode_utf16_le :
    self->input.encoding == TSInputEncodingUTF16BE ? ts_decode_utf16_be : self->input.decode;
  self->lookahead_size = decode(chunk, size, &self->data.lookahead);
  if (self->data.lookahead == TS_DECODE_ERROR && size < 4) {
    ts_lexer__get_chunk(self);
    chunk = (const uint8_t *)self->chunk;
    size = self->chunk_size;
    self->lookahead_size = decode(chunk, size, &self->data.lookahead);
  }
  if (self->data.lookahead == TS_DECODE_ERROR) {
    self->lookahead_size = 1;
  }
}
static void ts_lexer_goto(Lexer *self, Length position) {
  if (position.bytes != self->current_position.bytes) {
    ts_lexer__invalidate_column_data(self);
  }
  self->current_position = position;
  _Bool found_included_range = 0;
  for (unsigned i = 0; i < self->included_range_count; i++) {
    TSRange *included_range = &self->included_ranges[i];
    if (
      included_range->end_byte > self->current_position.bytes &&
      included_range->end_byte > included_range->start_byte
    ) {
      if (included_range->start_byte >= self->current_position.bytes) {
        self->current_position = (Length) {
          .bytes = included_range->start_byte,
          .extent = included_range->start_point,
        };
      }
      self->current_included_range_index = i;
      found_included_range = 1;
      break;
    }
  }
  if (found_included_range) {
    if (self->chunk && (
      self->current_position.bytes < self->chunk_start ||
      self->current_position.bytes >= self->chunk_start + self->chunk_size
    )) {
      ts_lexer__clear_chunk(self);
    }
    self->lookahead_size = 0;
    self->data.lookahead = '\0';
  }
  else {
    self->current_included_range_index = self->included_range_count;
    TSRange *last_included_range = &self->included_ranges[self->included_range_count - 1];
    self->current_position = (Length) {
      .bytes = last_included_range->end_byte,
      .extent = last_included_range->end_point,
    };
    ts_lexer__clear_chunk(self);
    self->lookahead_size = 1;
    self->data.lookahead = '\0';
  }
}
static void ts_lexer__do_advance(Lexer *self, _Bool skip) {
  if (self->lookahead_size) {
    if (self->data.lookahead == '\n') {
      self->current_position.extent.row++;
      self->current_position.extent.column = 0;
      ts_lexer__set_column_data(self, 0);
    } else {
      _Bool is_bom = self->current_position.bytes == 0 &&
        self->data.lookahead == BYTE_ORDER_MARK;
      if (!is_bom) ts_lexer__increment_column_data(self);
      self->current_position.extent.column += self->lookahead_size;
    }
    self->current_position.bytes += self->lookahead_size;
  }
  const TSRange *current_range = &self->included_ranges[self->current_included_range_index];
  while (
    self->current_position.bytes >= current_range->end_byte ||
    current_range->end_byte == current_range->start_byte
  ) {
    if (self->current_included_range_index < self->included_range_count) {
      self->current_included_range_index++;
    }
    if (self->current_included_range_index < self->included_range_count) {
      current_range++;
      self->current_position = (Length) {
        current_range->start_byte,
        current_range->start_point,
      };
    } else {
      current_range = ((void *)0);
      break;
    }
  }
  if (skip) self->token_start_position = self->current_position;
  if (current_range) {
    if (
      self->current_position.bytes < self->chunk_start ||
      self->current_position.bytes >= self->chunk_start + self->chunk_size
    ) {
      ts_lexer__get_chunk(self);
    }
    ts_lexer__get_lookahead(self);
  } else {
    ts_lexer__clear_chunk(self);
    self->data.lookahead = '\0';
    self->lookahead_size = 1;
  }
}
static void ts_lexer__advance(TSLexer *_self, _Bool skip) {
  Lexer *self = (Lexer *)_self;
  if (!self->chunk) return;
  if (skip) {
    if (self->logger.log) { snprintf( self->debug_buffer, 1024, 32 <= self->data.lookahead && self->data.lookahead < 127 ? "skip" " character:'%c'" : "skip" " character:%d", self->data.lookahead ); self->logger.log( self->logger.payload, TSLogTypeLex, self->debug_buffer ); }
  } else {
    if (self->logger.log) { snprintf( self->debug_buffer, 1024, 32 <= self->data.lookahead && self->data.lookahead < 127 ? "consume" " character:'%c'" : "consume" " character:%d", self->data.lookahead ); self->logger.log( self->logger.payload, TSLogTypeLex, self->debug_buffer ); }
  }
  ts_lexer__do_advance(self, skip);
}
static void ts_lexer__mark_end(TSLexer *_self) {
  Lexer *self = (Lexer *)_self;
  if (!ts_lexer__eof(&self->data)) {
    TSRange *current_included_range = &self->included_ranges[
      self->current_included_range_index
    ];
    if (
      self->current_included_range_index > 0 &&
      self->current_position.bytes == current_included_range->start_byte
    ) {
      TSRange *previous_included_range = current_included_range - 1;
      self->token_end_position = (Length) {
        previous_included_range->end_byte,
        previous_included_range->end_point,
      };
      return;
    }
  }
  self->token_end_position = self->current_position;
}
static uint32_t ts_lexer__get_column(TSLexer *_self) {
  Lexer *self = (Lexer *)_self;
  self->did_get_column = 1;
  if (!self->column_data.valid) {
    uint32_t goal_byte = self->current_position.bytes;
    Length start_of_col = {
      self->current_position.bytes - self->current_position.extent.column,
      {self->current_position.extent.row, 0},
    };
    ts_lexer_goto(self, start_of_col);
    ts_lexer__set_column_data(self, 0);
    ts_lexer__get_chunk(self);
    if (!ts_lexer__eof(_self)) {
      ts_lexer__get_lookahead(self);
      while (self->current_position.bytes < goal_byte && !ts_lexer__eof(_self) && self->chunk) {
        ts_lexer__do_advance(self, 0);
        if (ts_lexer__eof(_self)) break;
      }
    }
  }
  return self->column_data.value;
}
static _Bool ts_lexer__is_at_included_range_start(const TSLexer *_self) {
  const Lexer *self = (const Lexer *)_self;
  if (self->current_included_range_index < self->included_range_count) {
    TSRange *current_range = &self->included_ranges[self->current_included_range_index];
    return self->current_position.bytes == current_range->start_byte;
  } else {
    return 0;
  }
}
static void ts_lexer__log(const TSLexer *_self, const char *fmt, ...) {
  Lexer *self = (Lexer *)_self;
  va_list args;
  __builtin_va_start(args, fmt);
  if (self->logger.log) {
    vsnprintf(self->debug_buffer, 1024, fmt, args);
    self->logger.log(self->logger.payload, TSLogTypeLex, self->debug_buffer);
  }
  __builtin_va_end(args);
}
void ts_lexer_init(Lexer *self) {
  *self = (Lexer) {
    .data = {
      .advance = ts_lexer__advance,
      .mark_end = ts_lexer__mark_end,
      .get_column = ts_lexer__get_column,
      .is_at_included_range_start = ts_lexer__is_at_included_range_start,
      .eof = ts_lexer__eof,
      .log = ts_lexer__log,
      .lookahead = 0,
      .result_symbol = 0,
    },
    .chunk = ((void *)0),
    .chunk_size = 0,
    .chunk_start = 0,
    .current_position = {0, {0, 0}},
    .logger = {
      .payload = ((void *)0),
      .log = ((void *)0)
    },
    .included_ranges = ((void *)0),
    .included_range_count = 0,
    .current_included_range_index = 0,
    .did_get_column = 0,
    .column_data = {
      .valid = 0,
      .value = 0
    }
  };
  ts_lexer_set_included_ranges(self, ((void *)0), 0);
}
void ts_lexer_delete(Lexer *self) {
  ts_current_free(self->included_ranges);
}
void ts_lexer_set_input(Lexer *self, TSInput input) {
  self->input = input;
  ts_lexer__clear_chunk(self);
  ts_lexer_goto(self, self->current_position);
}
void ts_lexer_reset(Lexer *self, Length position) {
  if (position.bytes != self->current_position.bytes) {
    ts_lexer_goto(self, position);
  }
}
void ts_lexer_start(Lexer *self) {
  self->token_start_position = self->current_position;
  self->token_end_position = LENGTH_UNDEFINED;
  self->data.result_symbol = 0;
  self->did_get_column = 0;
  if (!ts_lexer__eof(&self->data)) {
    if (!self->chunk_size) ts_lexer__get_chunk(self);
    if (!self->lookahead_size) ts_lexer__get_lookahead(self);
    if (self->current_position.bytes == 0) {
      if (self->data.lookahead == BYTE_ORDER_MARK) {
        ts_lexer__advance(&self->data, 1);
      }
      ts_lexer__set_column_data(self, 0);
    }
  }
}
void ts_lexer_finish(Lexer *self, uint32_t *lookahead_end_byte) {
  if (length_is_undefined(self->token_end_position)) {
    ts_lexer__mark_end(&self->data);
  }
  if (self->token_end_position.bytes < self->token_start_position.bytes) {
    self->token_start_position = self->token_end_position;
  }
  uint32_t current_lookahead_end_byte = self->current_position.bytes + 1;
  if (self->data.lookahead == TS_DECODE_ERROR) {
    current_lookahead_end_byte += 4;
  }
  if (current_lookahead_end_byte > *lookahead_end_byte) {
    *lookahead_end_byte = current_lookahead_end_byte;
  }
}
void ts_lexer_mark_end(Lexer *self) {
  ts_lexer__mark_end(&self->data);
}
_Bool ts_lexer_set_included_ranges(
  Lexer *self,
  const TSRange *ranges,
  uint32_t count
) {
  if (count == 0 || !ranges) {
    ranges = &DEFAULT_RANGE;
    count = 1;
  } else {
    uint32_t previous_byte = 0;
    for (unsigned i = 0; i < count; i++) {
      const TSRange *range = &ranges[i];
      if (
        range->start_byte < previous_byte ||
        range->end_byte < range->start_byte
      ) return 0;
      previous_byte = range->end_byte;
    }
  }
  size_t size = count * sizeof(TSRange);
  self->included_ranges = ts_current_realloc(self->included_ranges, size);
  memcpy(self->included_ranges, ranges, size);
  self->included_range_count = count;
  ts_lexer_goto(self, self->current_position);
  return 1;
}
TSRange *ts_lexer_included_ranges(const Lexer *self, uint32_t *count) {
  *count = self->included_range_count;
  return self->included_ranges;
}
typedef struct {
  const Subtree *child;
  const Subtree *parent;
  Length position;
  TSSymbol alias_symbol;
} ParentCacheEntry;
struct TSTree {
  Subtree root;
  const TSLanguage *language;
  TSRange *included_ranges;
  unsigned included_range_count;
};
TSTree *ts_tree_new(Subtree root, const TSLanguage *language, const TSRange *included_ranges, unsigned included_range_count);
TSNode ts_node_new(const TSTree *tree, const Subtree *subtree, Length position, TSSymbol alias);
typedef struct {
  Subtree parent;
  const TSTree *tree;
  Length position;
  uint32_t child_index;
  uint32_t structural_child_index;
  const TSSymbol *alias_sequence;
} NodeChildIterator;
static inline _Bool ts_node__is_relevant(TSNode self, _Bool include_anonymous);
TSNode ts_node_new(
  const TSTree *tree,
  const Subtree *subtree,
  Length position,
  TSSymbol alias
) {
  return (TSNode) {
    {position.bytes, position.extent.row, position.extent.column, alias},
    subtree,
    tree,
  };
}
static inline TSNode ts_node__null(void) {
  return ts_node_new(((void *)0), ((void *)0), length_zero(), 0);
}
uint32_t ts_node_start_byte(TSNode self) {
  return self.context[0];
}
TSPoint ts_node_start_point(TSNode self) {
  return (TSPoint) {self.context[1], self.context[2]};
}
static inline uint32_t ts_node__alias(const TSNode *self) {
  return self->context[3];
}
static inline Subtree ts_node__subtree(TSNode self) {
  return *(const Subtree *)self.id;
}
static inline NodeChildIterator ts_node_iterate_children(const TSNode *node) {
  Subtree subtree = ts_node__subtree(*node);
  if (ts_subtree_child_count(subtree) == 0) {
    return (NodeChildIterator) {((Subtree) {.ptr = ((void *)0)}), node->tree, length_zero(), 0, 0, ((void *)0)};
  }
  const TSSymbol *alias_sequence = ts_language_alias_sequence(
    node->tree->language,
    subtree.ptr->production_id
  );
  return (NodeChildIterator) {
    .tree = node->tree,
    .parent = subtree,
    .position = {ts_node_start_byte(*node), ts_node_start_point(*node)},
    .child_index = 0,
    .structural_child_index = 0,
    .alias_sequence = alias_sequence,
  };
}
static inline _Bool ts_node_child_iterator_done(NodeChildIterator *self) {
  return self->child_index == self->parent.ptr->child_count;
}
static inline _Bool ts_node_child_iterator_next(
  NodeChildIterator *self,
  TSNode *result
) {
  if (!self->parent.ptr || ts_node_child_iterator_done(self)) return 0;
  const Subtree *child = &((self->parent).data.is_inline ? ((void *)0) : (Subtree *)((self->parent).ptr) - (self->parent).ptr->child_count)[self->child_index];
  TSSymbol alias_symbol = 0;
  if (!ts_subtree_extra(*child)) {
    if (self->alias_sequence) {
      alias_symbol = self->alias_sequence[self->structural_child_index];
    }
    self->structural_child_index++;
  }
  if (self->child_index > 0) {
    self->position = length_add(self->position, ts_subtree_padding(*child));
  }
  *result = ts_node_new(
    self->tree,
    child,
    self->position,
    alias_symbol
  );
  self->position = length_add(self->position, ts_subtree_size(*child));
  self->child_index++;
  return 1;
}
static inline _Bool ts_node__is_relevant(TSNode self, _Bool include_anonymous) {
  Subtree tree = ts_node__subtree(self);
  if (include_anonymous) {
    return ts_subtree_visible(tree) || ts_node__alias(&self);
  } else {
    TSSymbol alias = ts_node__alias(&self);
    if (alias) {
      return ts_language_symbol_metadata(self.tree->language, alias).named;
    } else {
      return ts_subtree_visible(tree) && ts_subtree_named(tree);
    }
  }
}
static inline uint32_t ts_node__relevant_child_count(
  TSNode self,
  _Bool include_anonymous
) {
  Subtree tree = ts_node__subtree(self);
  if (ts_subtree_child_count(tree) > 0) {
    if (include_anonymous) {
      return tree.ptr->visible_child_count;
    } else {
      return tree.ptr->named_child_count;
    }
  } else {
    return 0;
  }
}
static inline TSNode ts_node__child(
  TSNode self,
  uint32_t child_index,
  _Bool include_anonymous
) {
  TSNode result = self;
  _Bool did_descend = 1;
  while (did_descend) {
    did_descend = 0;
    TSNode child;
    uint32_t index = 0;
    NodeChildIterator iterator = ts_node_iterate_children(&result);
    while (ts_node_child_iterator_next(&iterator, &child)) {
      if (ts_node__is_relevant(child, include_anonymous)) {
        if (index == child_index) {
          return child;
        }
        index++;
      } else {
        uint32_t grandchild_index = child_index - index;
        uint32_t grandchild_count = ts_node__relevant_child_count(child, include_anonymous);
        if (grandchild_index < grandchild_count) {
          did_descend = 1;
          result = child;
          child_index = grandchild_index;
          break;
        }
        index += grandchild_count;
      }
    }
  }
  return ts_node__null();
}
static _Bool ts_subtree_has_trailing_empty_descendant(
  Subtree self,
  Subtree other
) {
  for (unsigned i = ts_subtree_child_count(self) - 1; i + 1 > 0; i--) {
    Subtree child = ((self).data.is_inline ? ((void *)0) : (Subtree *)((self).ptr) - (self).ptr->child_count)[i];
    if (ts_subtree_total_bytes(child) > 0) break;
    if (child.ptr == other.ptr || ts_subtree_has_trailing_empty_descendant(child, other)) {
      return 1;
    }
  }
  return 0;
}
static inline TSNode ts_node__prev_sibling(TSNode self, _Bool include_anonymous) {
  Subtree self_subtree = ts_node__subtree(self);
  _Bool self_is_empty = ts_subtree_total_bytes(self_subtree) == 0;
  uint32_t target_end_byte = ts_node_end_byte(self);
  TSNode node = ts_node_parent(self);
  TSNode earlier_node = ts_node__null();
  _Bool earlier_node_is_relevant = 0;
  while (!ts_node_is_null(node)) {
    TSNode earlier_child = ts_node__null();
    _Bool earlier_child_is_relevant = 0;
    _Bool found_child_containing_target = 0;
    TSNode child;
    NodeChildIterator iterator = ts_node_iterate_children(&node);
    while (ts_node_child_iterator_next(&iterator, &child)) {
      if (child.id == self.id) break;
      if (iterator.position.bytes > target_end_byte) {
        found_child_containing_target = 1;
        break;
      }
      if (iterator.position.bytes == target_end_byte &&
          (!self_is_empty ||
           ts_subtree_has_trailing_empty_descendant(ts_node__subtree(child), self_subtree))) {
        found_child_containing_target = 1;
        break;
      }
      if (ts_node__is_relevant(child, include_anonymous)) {
        earlier_child = child;
        earlier_child_is_relevant = 1;
      } else if (ts_node__relevant_child_count(child, include_anonymous) > 0) {
        earlier_child = child;
        earlier_child_is_relevant = 0;
      }
    }
    if (found_child_containing_target) {
      if (!ts_node_is_null(earlier_child)) {
        earlier_node = earlier_child;
        earlier_node_is_relevant = earlier_child_is_relevant;
      }
      node = child;
    } else if (earlier_child_is_relevant) {
      return earlier_child;
    } else if (!ts_node_is_null(earlier_child)) {
      node = earlier_child;
    } else if (earlier_node_is_relevant) {
      return earlier_node;
    } else {
      node = earlier_node;
      earlier_node = ts_node__null();
      earlier_node_is_relevant = 0;
    }
  }
  return ts_node__null();
}
static inline TSNode ts_node__next_sibling(TSNode self, _Bool include_anonymous) {
  uint32_t target_end_byte = ts_node_end_byte(self);
  TSNode node = ts_node_parent(self);
  TSNode later_node = ts_node__null();
  _Bool later_node_is_relevant = 0;
  while (!ts_node_is_null(node)) {
    TSNode later_child = ts_node__null();
    _Bool later_child_is_relevant = 0;
    TSNode child_containing_target = ts_node__null();
    TSNode child;
    NodeChildIterator iterator = ts_node_iterate_children(&node);
    while (ts_node_child_iterator_next(&iterator, &child)) {
      if (iterator.position.bytes <= target_end_byte) continue;
      uint32_t start_byte = ts_node_start_byte(self);
      uint32_t child_start_byte = ts_node_start_byte(child);
      _Bool is_empty = start_byte == target_end_byte;
      _Bool contains_target = is_empty ?
        child_start_byte < start_byte :
        child_start_byte <= start_byte;
      if (contains_target) {
        if (ts_node__subtree(child).ptr != ts_node__subtree(self).ptr) {
          child_containing_target = child;
        }
      } else if (ts_node__is_relevant(child, include_anonymous)) {
        later_child = child;
        later_child_is_relevant = 1;
        break;
      } else if (ts_node__relevant_child_count(child, include_anonymous) > 0) {
        later_child = child;
        later_child_is_relevant = 0;
        break;
      }
    }
    if (!ts_node_is_null(child_containing_target)) {
      if (!ts_node_is_null(later_child)) {
        later_node = later_child;
        later_node_is_relevant = later_child_is_relevant;
      }
      node = child_containing_target;
    } else if (later_child_is_relevant) {
      return later_child;
    } else if (!ts_node_is_null(later_child)) {
      node = later_child;
    } else if (later_node_is_relevant) {
      return later_node;
    } else {
      node = later_node;
    }
  }
  return ts_node__null();
}
static inline TSNode ts_node__first_child_for_byte(
  TSNode self,
  uint32_t goal,
  _Bool include_anonymous
) {
  TSNode node = self;
  _Bool did_descend = 1;
  NodeChildIterator last_iterator;
  _Bool has_last_iterator = 0;
  while (did_descend) {
    did_descend = 0;
    TSNode child;
    NodeChildIterator iterator = ts_node_iterate_children(&node);
  loop:
    while (ts_node_child_iterator_next(&iterator, &child)) {
      if (ts_node_end_byte(child) > goal) {
        if (ts_node__is_relevant(child, include_anonymous)) {
          return child;
        } else if (ts_node_child_count(child) > 0) {
          if (iterator.child_index < ts_subtree_child_count(ts_node__subtree(child))) {
            last_iterator = iterator;
            has_last_iterator = 1;
          }
          did_descend = 1;
          node = child;
          break;
        }
      }
    }
    if (!did_descend && has_last_iterator) {
      iterator = last_iterator;
      has_last_iterator = 0;
      goto loop;
    }
  }
  return ts_node__null();
}
static inline TSNode ts_node__descendant_for_byte_range(
  TSNode self,
  uint32_t range_start,
  uint32_t range_end,
  _Bool include_anonymous
) {
  if (range_start > range_end) {
    return ts_node__null();
  }
  TSNode node = self;
  TSNode last_visible_node = self;
  _Bool did_descend = 1;
  while (did_descend) {
    did_descend = 0;
    TSNode child;
    NodeChildIterator iterator = ts_node_iterate_children(&node);
    while (ts_node_child_iterator_next(&iterator, &child)) {
      uint32_t node_end = iterator.position.bytes;
      if (node_end < range_end) continue;
      _Bool is_empty = ts_node_start_byte(child) == node_end;
      if (is_empty ? node_end < range_start : node_end <= range_start) continue;
      if (range_start < ts_node_start_byte(child)) break;
      node = child;
      if (ts_node__is_relevant(node, include_anonymous)) {
        last_visible_node = node;
      }
      did_descend = 1;
      break;
    }
  }
  return last_visible_node;
}
static inline TSNode ts_node__descendant_for_point_range(
  TSNode self,
  TSPoint range_start,
  TSPoint range_end,
  _Bool include_anonymous
) {
  if (point_gt(range_start, range_end)) {
    return ts_node__null();
  }
  TSNode node = self;
  TSNode last_visible_node = self;
  _Bool did_descend = 1;
  while (did_descend) {
    did_descend = 0;
    TSNode child;
    NodeChildIterator iterator = ts_node_iterate_children(&node);
    while (ts_node_child_iterator_next(&iterator, &child)) {
      TSPoint node_end = iterator.position.extent;
      if (point_lt(node_end, range_end)) continue;
      _Bool is_empty =  point_eq(ts_node_start_point(child), node_end);
      if (is_empty ? point_lt(node_end, range_start) : point_lte(node_end, range_start)) {
        continue;
      }
      if (point_lt(range_start, ts_node_start_point(child))) break;
      node = child;
      if (ts_node__is_relevant(node, include_anonymous)) {
        last_visible_node = node;
      }
      did_descend = 1;
      break;
    }
  }
  return last_visible_node;
}
uint32_t ts_node_end_byte(TSNode self) {
  return ts_node_start_byte(self) + ts_subtree_size(ts_node__subtree(self)).bytes;
}
TSPoint ts_node_end_point(TSNode self) {
  return point_add(ts_node_start_point(self), ts_subtree_size(ts_node__subtree(self)).extent);
}
TSSymbol ts_node_symbol(TSNode self) {
  TSSymbol symbol = ts_node__alias(&self);
  if (!symbol) symbol = ts_subtree_symbol(ts_node__subtree(self));
  return ts_language_public_symbol(self.tree->language, symbol);
}
const char *ts_node_type(TSNode self) {
  TSSymbol symbol = ts_node__alias(&self);
  if (!symbol) symbol = ts_subtree_symbol(ts_node__subtree(self));
  return ts_language_symbol_name(self.tree->language, symbol);
}
const TSLanguage *ts_node_language(TSNode self) {
  return self.tree->language;
}
TSSymbol ts_node_grammar_symbol(TSNode self) {
  return ts_subtree_symbol(ts_node__subtree(self));
}
const char *ts_node_grammar_type(TSNode self) {
  TSSymbol symbol = ts_subtree_symbol(ts_node__subtree(self));
  return ts_language_symbol_name(self.tree->language, symbol);
}
char *ts_node_string(TSNode self) {
  TSSymbol alias_symbol = ts_node__alias(&self);
  return ts_subtree_string(
    ts_node__subtree(self),
    alias_symbol,
    ts_language_symbol_metadata(self.tree->language, alias_symbol).visible,
    self.tree->language,
    0
  );
}
_Bool ts_node_eq(TSNode self, TSNode other) {
  return self.tree == other.tree && self.id == other.id;
}
_Bool ts_node_is_null(TSNode self) {
  return self.id == 0;
}
_Bool ts_node_is_extra(TSNode self) {
  return ts_subtree_extra(ts_node__subtree(self));
}
_Bool ts_node_is_named(TSNode self) {
  TSSymbol alias = ts_node__alias(&self);
  return alias
    ? ts_language_symbol_metadata(self.tree->language, alias).named
    : ts_subtree_named(ts_node__subtree(self));
}
_Bool ts_node_is_missing(TSNode self) {
  return ts_subtree_missing(ts_node__subtree(self));
}
_Bool ts_node_has_changes(TSNode self) {
  return ts_subtree_has_changes(ts_node__subtree(self));
}
_Bool ts_node_has_error(TSNode self) {
  return ts_subtree_error_cost(ts_node__subtree(self)) > 0;
}
_Bool ts_node_is_error(TSNode self) {
  TSSymbol symbol = ts_node_symbol(self);
  return symbol == ((TSSymbol)-1);
}
uint32_t ts_node_descendant_count(TSNode self) {
  return ts_subtree_visible_descendant_count(ts_node__subtree(self)) + 1;
}
TSStateId ts_node_parse_state(TSNode self) {
  return ts_subtree_parse_state(ts_node__subtree(self));
}
TSStateId ts_node_next_parse_state(TSNode self) {
  const TSLanguage *language = self.tree->language;
  uint16_t state = ts_node_parse_state(self);
  if (state == 65535) {
    return 65535;
  }
  uint16_t symbol = ts_node_grammar_symbol(self);
  return ts_language_next_state(language, state, symbol);
}
TSNode ts_node_parent(TSNode self) {
  TSNode node = ts_tree_root_node(self.tree);
  if (node.id == self.id) return ts_node__null();
  while (1) {
    TSNode next_node = ts_node_child_with_descendant(node, self);
    if (next_node.id == self.id || ts_node_is_null(next_node)) break;
    node = next_node;
  }
  return node;
}
TSNode ts_node_child_with_descendant(TSNode self, TSNode descendant) {
  uint32_t start_byte = ts_node_start_byte(descendant);
  uint32_t end_byte = ts_node_end_byte(descendant);
  _Bool is_empty = start_byte == end_byte;
  do {
    NodeChildIterator iter = ts_node_iterate_children(&self);
    do {
      if (
        !ts_node_child_iterator_next(&iter, &self)
        || ts_node_start_byte(self) > start_byte
      ) {
        return ts_node__null();
      }
      if (self.id == descendant.id) {
        return self;
      }
      if (is_empty && iter.position.bytes >= end_byte && ts_node_child_count(self) > 0) {
        TSNode child = ts_node_child_with_descendant(self, descendant);
        if (!ts_node_is_null(child)) {
          return ts_node__is_relevant(self, 1) ? self : child;
        }
      }
    } while ((is_empty ? iter.position.bytes <= end_byte : iter.position.bytes < end_byte) || ts_node_child_count(self) == 0);
  } while (!ts_node__is_relevant(self, 1));
  return self;
}
TSNode ts_node_child(TSNode self, uint32_t child_index) {
  return ts_node__child(self, child_index, 1);
}
TSNode ts_node_named_child(TSNode self, uint32_t child_index) {
  return ts_node__child(self, child_index, 0);
}
TSNode ts_node_child_by_field_id(TSNode self, TSFieldId field_id) {
recur:
  if (!field_id || ts_node_child_count(self) == 0) return ts_node__null();
  const TSFieldMapEntry *field_map, *field_map_end;
  ts_language_field_map(
    self.tree->language,
    ts_node__subtree(self).ptr->production_id,
    &field_map,
    &field_map_end
  );
  if (field_map == field_map_end) return ts_node__null();
  while (field_map->field_id < field_id) {
    field_map++;
    if (field_map == field_map_end) return ts_node__null();
  }
  while (field_map_end[-1].field_id > field_id) {
    field_map_end--;
    if (field_map == field_map_end) return ts_node__null();
  }
  TSNode child;
  NodeChildIterator iterator = ts_node_iterate_children(&self);
  while (ts_node_child_iterator_next(&iterator, &child)) {
    if (!ts_subtree_extra(ts_node__subtree(child))) {
      uint32_t index = iterator.structural_child_index - 1;
      if (index < field_map->child_index) continue;
      if (field_map->inherited) {
        if (field_map + 1 == field_map_end) {
          self = child;
          goto recur;
        }
        else {
          TSNode result = ts_node_child_by_field_id(child, field_id);
          if (result.id) return result;
          field_map++;
          if (field_map == field_map_end) return ts_node__null();
        }
      }
      else if (ts_node__is_relevant(child, 1)) {
        return child;
      }
      else if (ts_node_child_count(child) > 0 ) {
        return ts_node_child(child, 0);
      }
      else {
        field_map++;
        if (field_map == field_map_end) return ts_node__null();
      }
    }
  }
  return ts_node__null();
}
static inline const char *ts_node__field_name_from_language(TSNode self, uint32_t structural_child_index) {
    const TSFieldMapEntry *field_map, *field_map_end;
    ts_language_field_map(
      self.tree->language,
      ts_node__subtree(self).ptr->production_id,
      &field_map,
      &field_map_end
    );
    for (; field_map != field_map_end; field_map++) {
      if (!field_map->inherited && field_map->child_index == structural_child_index) {
        return self.tree->language->field_names[field_map->field_id];
      }
    }
    return ((void *)0);
}
const char *ts_node_field_name_for_child(TSNode self, uint32_t child_index) {
  TSNode result = self;
  _Bool did_descend = 1;
  const char *inherited_field_name = ((void *)0);
  while (did_descend) {
    did_descend = 0;
    TSNode child;
    uint32_t index = 0;
    NodeChildIterator iterator = ts_node_iterate_children(&result);
    while (ts_node_child_iterator_next(&iterator, &child)) {
      if (ts_node__is_relevant(child, 1)) {
        if (index == child_index) {
          if (ts_node_is_extra(child)) {
            return ((void *)0);
          }
          const char *field_name = ts_node__field_name_from_language(result, iterator.structural_child_index - 1);
          if (field_name) return field_name;
          return inherited_field_name;
        }
        index++;
      } else {
        uint32_t grandchild_index = child_index - index;
        uint32_t grandchild_count = ts_node__relevant_child_count(child, 1);
        if (grandchild_index < grandchild_count) {
          const char *field_name = ts_node__field_name_from_language(result, iterator.structural_child_index - 1);
          if (field_name) inherited_field_name = field_name;
          did_descend = 1;
          result = child;
          child_index = grandchild_index;
          break;
        }
        index += grandchild_count;
      }
    }
  }
  return ((void *)0);
}
const char *ts_node_field_name_for_named_child(TSNode self, uint32_t named_child_index) {
  TSNode result = self;
  _Bool did_descend = 1;
  const char *inherited_field_name = ((void *)0);
  while (did_descend) {
    did_descend = 0;
    TSNode child;
    uint32_t index = 0;
    NodeChildIterator iterator = ts_node_iterate_children(&result);
    while (ts_node_child_iterator_next(&iterator, &child)) {
      if (ts_node__is_relevant(child, 0)) {
        if (index == named_child_index) {
          if (ts_node_is_extra(child)) {
            return ((void *)0);
          }
          const char *field_name = ts_node__field_name_from_language(result, iterator.structural_child_index - 1);
          if (field_name) return field_name;
          return inherited_field_name;
        }
        index++;
      } else {
        uint32_t named_grandchild_index = named_child_index - index;
        uint32_t grandchild_count = ts_node__relevant_child_count(child, 0);
        if (named_grandchild_index < grandchild_count) {
          const char *field_name = ts_node__field_name_from_language(result, iterator.structural_child_index - 1);
          if (field_name) inherited_field_name = field_name;
          did_descend = 1;
          result = child;
          named_child_index = named_grandchild_index;
          break;
        }
        index += grandchild_count;
      }
    }
  }
  return ((void *)0);
}
TSNode ts_node_child_by_field_name(
  TSNode self,
  const char *name,
  uint32_t name_length
) {
  TSFieldId field_id = ts_language_field_id_for_name(
    self.tree->language,
    name,
    name_length
  );
  return ts_node_child_by_field_id(self, field_id);
}
uint32_t ts_node_child_count(TSNode self) {
  Subtree tree = ts_node__subtree(self);
  if (ts_subtree_child_count(tree) > 0) {
    return tree.ptr->visible_child_count;
  } else {
    return 0;
  }
}
uint32_t ts_node_named_child_count(TSNode self) {
  Subtree tree = ts_node__subtree(self);
  if (ts_subtree_child_count(tree) > 0) {
    return tree.ptr->named_child_count;
  } else {
    return 0;
  }
}
TSNode ts_node_next_sibling(TSNode self) {
  return ts_node__next_sibling(self, 1);
}
TSNode ts_node_next_named_sibling(TSNode self) {
  return ts_node__next_sibling(self, 0);
}
TSNode ts_node_prev_sibling(TSNode self) {
  return ts_node__prev_sibling(self, 1);
}
TSNode ts_node_prev_named_sibling(TSNode self) {
  return ts_node__prev_sibling(self, 0);
}
TSNode ts_node_first_child_for_byte(TSNode self, uint32_t byte) {
  return ts_node__first_child_for_byte(self, byte, 1);
}
TSNode ts_node_first_named_child_for_byte(TSNode self, uint32_t byte) {
  return ts_node__first_child_for_byte(self, byte, 0);
}
TSNode ts_node_descendant_for_byte_range(
  TSNode self,
  uint32_t start,
  uint32_t end
) {
  return ts_node__descendant_for_byte_range(self, start, end, 1);
}
TSNode ts_node_named_descendant_for_byte_range(
  TSNode self,
  uint32_t start,
  uint32_t end
) {
  return ts_node__descendant_for_byte_range(self, start, end, 0);
}
TSNode ts_node_descendant_for_point_range(
  TSNode self,
  TSPoint start,
  TSPoint end
) {
  return ts_node__descendant_for_point_range(self, start, end, 1);
}
TSNode ts_node_named_descendant_for_point_range(
  TSNode self,
  TSPoint start,
  TSPoint end
) {
  return ts_node__descendant_for_point_range(self, start, end, 0);
}
void ts_node_edit(TSNode *self, const TSInputEdit *edit) {
  uint32_t start_byte = ts_node_start_byte(*self);
  TSPoint start_point = ts_node_start_point(*self);
  if (start_byte >= edit->old_end_byte) {
    start_byte = edit->new_end_byte + (start_byte - edit->old_end_byte);
    start_point = point_add(edit->new_end_point, point_sub(start_point, edit->old_end_point));
  } else if (start_byte > edit->start_byte) {
    start_byte = edit->new_end_byte;
    start_point = edit->new_end_point;
  }
  self->context[0] = start_byte;
  self->context[1] = start_point.row;
  self->context[2] = start_point.column;
}
typedef __darwin_clock_t        clock_t;
typedef __darwin_time_t         time_t;
struct timespec
{
	__darwin_time_t tv_sec;
	long            tv_nsec;
};
struct tm {
	int	tm_sec;
	int	tm_min;
	int	tm_hour;
	int	tm_mday;
	int	tm_mon;
	int	tm_year;
	int	tm_wday;
	int	tm_yday;
	int	tm_isdst;
	long	tm_gmtoff;
	char	*tm_zone;
};
extern char *tzname[];
extern int getdate_err;
extern long timezone __asm("_" "timezone" );
extern int daylight;
char *asctime(const struct tm *);
clock_t clock(void) __asm("_" "clock" );
char *ctime(const time_t *);
double difftime(time_t, time_t);
struct tm *getdate(const char *);
struct tm *gmtime(const time_t *);
struct tm *localtime(const time_t *);
time_t mktime(struct tm *) __asm("_" "mktime" );
size_t strftime(char * restrict, size_t, const char * restrict, const struct tm * restrict) __asm("_" "strftime" );
char *strptime(const char * restrict, const char * restrict, struct tm * restrict) __asm("_" "strptime" );
time_t time(time_t *);
void tzset(void);
char *asctime_r(const struct tm * restrict, char * restrict);
char *ctime_r(const time_t *, char *);
struct tm *gmtime_r(const time_t * restrict, struct tm * restrict);
struct tm *localtime_r(const time_t * restrict, struct tm * restrict);
time_t posix2time(time_t);
void tzsetwall(void);
time_t time2posix(time_t);
time_t timelocal(struct tm * const);
time_t timegm(struct tm * const);
int nanosleep(const struct timespec *__rqtp, struct timespec *__rmtp) __asm("_" "nanosleep" );
typedef enum {
_CLOCK_REALTIME  = 0,
_CLOCK_MONOTONIC  = 6,
_CLOCK_MONOTONIC_RAW  = 4,
_CLOCK_MONOTONIC_RAW_APPROX  = 5,
_CLOCK_UPTIME_RAW  = 8,
_CLOCK_UPTIME_RAW_APPROX  = 9,
_CLOCK_PROCESS_CPUTIME_ID  = 12,
_CLOCK_THREAD_CPUTIME_ID  = 16
} clockid_t;
int clock_getres(clockid_t __clock_id, struct timespec *__res);
int clock_gettime(clockid_t __clock_id, struct timespec *__tp);
__uint64_t clock_gettime_nsec_np(clockid_t __clock_id);
int clock_settime(clockid_t __clock_id, const struct timespec *__tp);
int timespec_get(struct timespec *ts, int base);
extern intmax_t
imaxabs(intmax_t j);
typedef struct {
	intmax_t quot;
	intmax_t rem;
} imaxdiv_t;
extern imaxdiv_t
imaxdiv(intmax_t __numer, intmax_t __denom);
extern intmax_t
strtoimax(const char * restrict __nptr,
	  char ** restrict __endptr,
	  int __base);
extern uintmax_t
strtoumax(const char * restrict __nptr,
	  char ** restrict __endptr,
	  int __base);
extern intmax_t
wcstoimax(const wchar_t * restrict __nptr,
	  wchar_t ** restrict __endptr,
	  int __base);
extern uintmax_t
wcstoumax(const wchar_t * restrict __nptr,
	  wchar_t ** restrict __endptr,
	  int __base);
static inline size_t atomic_load(const volatile size_t *p) {
  return *p;
}
static inline uint32_t atomic_inc(volatile uint32_t *p) {
  *p += 1;
  return *p;
}
static inline uint32_t atomic_dec(volatile uint32_t *p) {
  *p-= 1;
  return *p;
}
typedef uint64_t TSDuration;
typedef struct timespec TSClock;
static inline TSDuration duration_from_micros(uint64_t micros) {
  return micros;
}
static inline uint64_t duration_to_micros(TSDuration self) {
  return self;
}
static inline TSClock clock_now(void) {
  TSClock result;
  clock_gettime(_CLOCK_MONOTONIC, &result);
  return result;
}
static inline TSClock clock_null(void) {
  return (TSClock) {0, 0};
}
static inline TSClock clock_after(TSClock base, TSDuration duration) {
  TSClock result = base;
  result.tv_sec += duration / 1000000;
  result.tv_nsec += (duration % 1000000) * 1000;
  if (result.tv_nsec >= 1000000000) {
    result.tv_nsec -= 1000000000;
    ++(result.tv_sec);
  }
  return result;
}
static inline _Bool clock_is_null(TSClock self) {
  return !self.tv_sec && !self.tv_nsec;
}
static inline _Bool clock_is_gt(TSClock self, TSClock other) {
  if (self.tv_sec > other.tv_sec) return 1;
  if (self.tv_sec < other.tv_sec) return 0;
  return self.tv_nsec > other.tv_nsec;
}
typedef struct {
  uint32_t count;
  TSSymbol symbol;
  int dynamic_precedence;
  unsigned short production_id;
} ReduceAction;
typedef struct { ReduceAction *contents; uint32_t size; uint32_t capacity; } ReduceActionSet;
static inline void ts_reduce_action_set_add(ReduceActionSet *self,
                                            ReduceAction new_action) {
  for (uint32_t i = 0; i < self->size; i++) {
    ReduceAction action = self->contents[i];
    if (action.symbol == new_action.symbol && action.count == new_action.count)
      return;
  }
  (_array__grow((Array *)(self), 1, (sizeof *(self)->contents)), (self)->contents[(self)->size++] = (new_action));
}
typedef struct {
  Subtree tree;
  uint32_t child_index;
  uint32_t byte_offset;
} StackEntry;
typedef struct {
  struct { StackEntry *contents; uint32_t size; uint32_t capacity; } stack;
  Subtree last_external_token;
} ReusableNode;
static inline ReusableNode reusable_node_new(void) {
  return (ReusableNode) {{ ((void *)0), 0, 0 }, ((Subtree) {.ptr = ((void *)0)})};
}
static inline void reusable_node_clear(ReusableNode *self) {
  ((&self->stack)->size = 0);
  self->last_external_token = ((Subtree) {.ptr = ((void *)0)});
}
static inline Subtree reusable_node_tree(ReusableNode *self) {
  return self->stack.size > 0
    ? self->stack.contents[self->stack.size - 1].tree
    : ((Subtree) {.ptr = ((void *)0)});
}
static inline uint32_t reusable_node_byte_offset(ReusableNode *self) {
  return self->stack.size > 0
    ? self->stack.contents[self->stack.size - 1].byte_offset
    : 4294967295U;
}
static inline void reusable_node_delete(ReusableNode *self) {
  _array__delete((Array *)(&self->stack));
}
static inline void reusable_node_advance(ReusableNode *self) {
  StackEntry last_entry = *((__builtin_expect(!((uint32_t)((&self->stack)->size - 1) < (&self->stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/././reusable_node.h", 40, "(uint32_t)((&self->stack)->size - 1) < (&self->stack)->size") : (void)0), &(&self->stack)->contents[(&self->stack)->size - 1]);
  uint32_t byte_offset = last_entry.byte_offset + ts_subtree_total_bytes(last_entry.tree);
  if (ts_subtree_has_external_tokens(last_entry.tree)) {
    self->last_external_token = ts_subtree_last_external_token(last_entry.tree);
  }
  Subtree tree;
  uint32_t next_index;
  do {
    StackEntry popped_entry = ((&self->stack)->contents[--(&self->stack)->size]);
    next_index = popped_entry.child_index + 1;
    if (self->stack.size == 0) return;
    tree = ((__builtin_expect(!((uint32_t)((&self->stack)->size - 1) < (&self->stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/././reusable_node.h", 52, "(uint32_t)((&self->stack)->size - 1) < (&self->stack)->size") : (void)0), &(&self->stack)->contents[(&self->stack)->size - 1])->tree;
  } while (ts_subtree_child_count(tree) <= next_index);
  (_array__grow((Array *)(&self->stack), 1, (sizeof *(&self->stack)->contents)), (&self->stack)->contents[(&self->stack)->size++] = (((StackEntry) { .tree = ((tree).data.is_inline ? ((void *)0) : (Subtree *)((tree).ptr) - (tree).ptr->child_count)[next_index], .child_index = next_index, .byte_offset = byte_offset, })));
}
static inline _Bool reusable_node_descend(ReusableNode *self) {
  StackEntry last_entry = *((__builtin_expect(!((uint32_t)((&self->stack)->size - 1) < (&self->stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/././reusable_node.h", 63, "(uint32_t)((&self->stack)->size - 1) < (&self->stack)->size") : (void)0), &(&self->stack)->contents[(&self->stack)->size - 1]);
  if (ts_subtree_child_count(last_entry.tree) > 0) {
    (_array__grow((Array *)(&self->stack), 1, (sizeof *(&self->stack)->contents)), (&self->stack)->contents[(&self->stack)->size++] = (((StackEntry) { .tree = ((last_entry.tree).data.is_inline ? ((void *)0) : (Subtree *)((last_entry.tree).ptr) - (last_entry.tree).ptr->child_count)[0], .child_index = 0, .byte_offset = last_entry.byte_offset, })));
    return 1;
  } else {
    return 0;
  }
}
static inline void reusable_node_advance_past_leaf(ReusableNode *self) {
  while (reusable_node_descend(self)) {}
  reusable_node_advance(self);
}
static inline void reusable_node_reset(ReusableNode *self, Subtree tree) {
  reusable_node_clear(self);
  (_array__grow((Array *)(&self->stack), 1, (sizeof *(&self->stack)->contents)), (&self->stack)->contents[(&self->stack)->size++] = (((StackEntry) { .tree = tree, .child_index = 0, .byte_offset = 0, })));
  if (!reusable_node_descend(self)) {
    reusable_node_clear(self);
  }
}
typedef struct Stack Stack;
typedef unsigned StackVersion;
typedef struct {
  SubtreeArray subtrees;
  StackVersion version;
} StackSlice;
typedef struct { StackSlice *contents; uint32_t size; uint32_t capacity; } StackSliceArray;
typedef struct {
  Length position;
  unsigned depth;
  TSStateId state;
} StackSummaryEntry;
typedef struct { StackSummaryEntry *contents; uint32_t size; uint32_t capacity; } StackSummary;
Stack *ts_stack_new(SubtreePool *subtree_pool);
void ts_stack_delete(Stack *self);
uint32_t ts_stack_version_count(const Stack *self);
TSStateId ts_stack_state(const Stack *self, StackVersion version);
Subtree ts_stack_last_external_token(const Stack *self, StackVersion version);
void ts_stack_set_last_external_token(Stack *self, StackVersion version, Subtree token);
Length ts_stack_position(const Stack *, StackVersion);
void ts_stack_push(Stack *self, StackVersion version, Subtree subtree, _Bool pending, TSStateId state);
StackSliceArray ts_stack_pop_count(Stack *self, StackVersion version, uint32_t count);
SubtreeArray ts_stack_pop_error(Stack *self, StackVersion version);
StackSliceArray ts_stack_pop_pending(Stack *self, StackVersion version);
StackSliceArray ts_stack_pop_all(Stack *self, StackVersion version);
unsigned ts_stack_node_count_since_error(const Stack *self, StackVersion version);
int ts_stack_dynamic_precedence(Stack *self, StackVersion version);
_Bool ts_stack_has_advanced_since_error(const Stack *self, StackVersion version);
void ts_stack_record_summary(Stack *self, StackVersion version, unsigned max_depth);
StackSummary *ts_stack_get_summary(Stack *self, StackVersion version);
unsigned ts_stack_error_cost(const Stack *self, StackVersion version);
_Bool ts_stack_merge(Stack *self, StackVersion version1, StackVersion version2);
_Bool ts_stack_can_merge(Stack *self, StackVersion version1, StackVersion version2);
Subtree ts_stack_resume(Stack *self, StackVersion version);
void ts_stack_pause(Stack *self, StackVersion version, Subtree lookahead);
void ts_stack_halt(Stack *self, StackVersion version);
_Bool ts_stack_is_active(const Stack *self, StackVersion version);
_Bool ts_stack_is_paused(const Stack *self, StackVersion version);
_Bool ts_stack_is_halted(const Stack *self, StackVersion version);
void ts_stack_renumber_version(Stack *self, StackVersion v1, StackVersion v2);
void ts_stack_swap_versions(Stack *, StackVersion v1, StackVersion v2);
StackVersion ts_stack_copy_version(Stack *self, StackVersion version);
void ts_stack_remove_version(Stack *self, StackVersion version);
void ts_stack_clear(Stack *self);
_Bool ts_stack_print_dot_graph(Stack *self, const TSLanguage *language, FILE *f);
static const unsigned MAX_VERSION_COUNT = 6;
static const unsigned MAX_VERSION_COUNT_OVERFLOW = 4;
static const unsigned MAX_SUMMARY_DEPTH = 16;
static const unsigned MAX_COST_DIFFERENCE = 18 * 100;
static const unsigned OP_COUNT_PER_PARSER_TIMEOUT_CHECK = 100;
typedef struct {
  Subtree token;
  Subtree last_external_token;
  uint32_t byte_index;
} TokenCache;
struct TSParser {
  Lexer lexer;
  Stack *stack;
  SubtreePool tree_pool;
  const TSLanguage *language;
  TSWasmStore *wasm_store;
  ReduceActionSet reduce_actions;
  Subtree finished_tree;
  SubtreeArray trailing_extras;
  SubtreeArray trailing_extras2;
  SubtreeArray scratch_trees;
  TokenCache token_cache;
  ReusableNode reusable_node;
  void *external_scanner_payload;
  FILE *dot_graph_file;
  TSClock end_clock;
  TSDuration timeout_duration;
  unsigned accept_count;
  unsigned operation_count;
  const volatile size_t *cancellation_flag;
  Subtree old_tree;
  TSRangeArray included_range_differences;
  TSParseOptions parse_options;
  TSParseState parse_state;
  unsigned included_range_difference_index;
  _Bool has_scanner_error;
  _Bool canceled_balancing;
  _Bool has_error;
};
typedef struct {
  unsigned cost;
  unsigned node_count;
  int dynamic_precedence;
  _Bool is_in_error;
} ErrorStatus;
typedef enum {
  ErrorComparisonTakeLeft,
  ErrorComparisonPreferLeft,
  ErrorComparisonNone,
  ErrorComparisonPreferRight,
  ErrorComparisonTakeRight,
} ErrorComparison;
typedef struct {
  const char *string;
  uint32_t length;
} TSStringInput;
static const char *ts_string_input_read(
  void *_self,
  uint32_t byte,
  TSPoint point,
  uint32_t *length
) {
  (void)point;
  TSStringInput *self = (TSStringInput *)_self;
  if (byte >= self->length) {
    *length = 0;
    return "";
  } else {
    *length = self->length - byte;
    return self->string + byte;
  }
}
static void ts_parser__log(TSParser *self) {
  if (self->lexer.logger.log) {
    self->lexer.logger.log(
      self->lexer.logger.payload,
      TSLogTypeParse,
      self->lexer.debug_buffer
    );
  }
  if (self->dot_graph_file) {
    fprintf(self->dot_graph_file, "graph {\nlabel=\"");
    for (char *chr = &self->lexer.debug_buffer[0]; *chr != 0; chr++) {
      if (*chr == '"' || *chr == '\\') fputc('\\', self->dot_graph_file);
      fputc(*chr, self->dot_graph_file);
    }
    fprintf(self->dot_graph_file, "\"\n}\n\n");
  }
}
static _Bool ts_parser__breakdown_top_of_stack(
  TSParser *self,
  StackVersion version
) {
  _Bool did_break_down = 0;
  _Bool pending = 0;
  do {
    StackSliceArray pop = ts_stack_pop_pending(self->stack, version);
    if (!pop.size) break;
    did_break_down = 1;
    pending = 0;
    for (uint32_t i = 0; i < pop.size; i++) {
      StackSlice slice = pop.contents[i];
      TSStateId state = ts_stack_state(self->stack, slice.version);
      Subtree parent = *((__builtin_expect(!((uint32_t)(0) < (&slice.subtrees)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./parser.c", 198, "(uint32_t)(0) < (&slice.subtrees)->size") : (void)0), &(&slice.subtrees)->contents[0]);
      for (uint32_t j = 0, n = ts_subtree_child_count(parent); j < n; j++) {
        Subtree child = ((parent).data.is_inline ? ((void *)0) : (Subtree *)((parent).ptr) - (parent).ptr->child_count)[j];
        pending = ts_subtree_child_count(child) > 0;
        if (ts_subtree_is_error(child)) {
          state = 0;
        } else if (!ts_subtree_extra(child)) {
          state = ts_language_next_state(self->language, state, ts_subtree_symbol(child));
        }
        ts_subtree_retain(child);
        ts_stack_push(self->stack, slice.version, child, pending, state);
      }
      for (uint32_t j = 1; j < slice.subtrees.size; j++) {
        Subtree tree = slice.subtrees.contents[j];
        ts_stack_push(self->stack, slice.version, tree, 0, state);
      }
      ts_subtree_release(&self->tree_pool, parent);
      _array__delete((Array *)(&slice.subtrees));
      if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "breakdown_top_of_stack tree:%s", ts_language_symbol_name(self->language, ts_subtree_symbol(parent))); ts_parser__log(self); };
      if (self->dot_graph_file) { ts_stack_print_dot_graph(self->stack, self->language, self->dot_graph_file); fputs("\n\n", self->dot_graph_file); };
    }
  } while (pending);
  return did_break_down;
}
static void ts_parser__breakdown_lookahead(
  TSParser *self,
  Subtree *lookahead,
  TSStateId state,
  ReusableNode *reusable_node
) {
  _Bool did_descend = 0;
  Subtree tree = reusable_node_tree(reusable_node);
  while (ts_subtree_child_count(tree) > 0 && ts_subtree_parse_state(tree) != state) {
    if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "state_mismatch sym:%s", ts_language_symbol_name(self->language, ts_subtree_symbol(tree))); ts_parser__log(self); };
    reusable_node_descend(reusable_node);
    tree = reusable_node_tree(reusable_node);
    did_descend = 1;
  }
  if (did_descend) {
    ts_subtree_release(&self->tree_pool, *lookahead);
    *lookahead = tree;
    ts_subtree_retain(*lookahead);
  }
}
static ErrorComparison ts_parser__compare_versions(
  TSParser *self,
  ErrorStatus a,
  ErrorStatus b
) {
  (void)self;
  if (!a.is_in_error && b.is_in_error) {
    if (a.cost < b.cost) {
      return ErrorComparisonTakeLeft;
    } else {
      return ErrorComparisonPreferLeft;
    }
  }
  if (a.is_in_error && !b.is_in_error) {
    if (b.cost < a.cost) {
      return ErrorComparisonTakeRight;
    } else {
      return ErrorComparisonPreferRight;
    }
  }
  if (a.cost < b.cost) {
    if ((b.cost - a.cost) * (1 + a.node_count) > MAX_COST_DIFFERENCE) {
      return ErrorComparisonTakeLeft;
    } else {
      return ErrorComparisonPreferLeft;
    }
  }
  if (b.cost < a.cost) {
    if ((a.cost - b.cost) * (1 + b.node_count) > MAX_COST_DIFFERENCE) {
      return ErrorComparisonTakeRight;
    } else {
      return ErrorComparisonPreferRight;
    }
  }
  if (a.dynamic_precedence > b.dynamic_precedence) return ErrorComparisonPreferLeft;
  if (b.dynamic_precedence > a.dynamic_precedence) return ErrorComparisonPreferRight;
  return ErrorComparisonNone;
}
static ErrorStatus ts_parser__version_status(
  TSParser *self,
  StackVersion version
) {
  unsigned cost = ts_stack_error_cost(self->stack, version);
  _Bool is_paused = ts_stack_is_paused(self->stack, version);
  if (is_paused) cost += 100;
  return (ErrorStatus) {
    .cost = cost,
    .node_count = ts_stack_node_count_since_error(self->stack, version),
    .dynamic_precedence = ts_stack_dynamic_precedence(self->stack, version),
    .is_in_error = is_paused || ts_stack_state(self->stack, version) == 0
  };
}
static _Bool ts_parser__better_version_exists(
  TSParser *self,
  StackVersion version,
  _Bool is_in_error,
  unsigned cost
) {
  if (self->finished_tree.ptr && ts_subtree_error_cost(self->finished_tree) <= cost) {
    return 1;
  }
  Length position = ts_stack_position(self->stack, version);
  ErrorStatus status = {
    .cost = cost,
    .is_in_error = is_in_error,
    .dynamic_precedence = ts_stack_dynamic_precedence(self->stack, version),
    .node_count = ts_stack_node_count_since_error(self->stack, version),
  };
  for (StackVersion i = 0, n = ts_stack_version_count(self->stack); i < n; i++) {
    if (i == version ||
        !ts_stack_is_active(self->stack, i) ||
        ts_stack_position(self->stack, i).bytes < position.bytes) continue;
    ErrorStatus status_i = ts_parser__version_status(self, i);
    switch (ts_parser__compare_versions(self, status, status_i)) {
      case ErrorComparisonTakeRight:
        return 1;
      case ErrorComparisonPreferRight:
        if (ts_stack_can_merge(self->stack, i, version)) return 1;
        break;
      default:
        break;
    }
  }
  return 0;
}
static _Bool ts_parser__call_main_lex_fn(TSParser *self, TSLexerMode lex_mode) {
  if (ts_language_is_wasm(self->language)) {
    return ts_wasm_store_call_lex_main(self->wasm_store, lex_mode.lex_state);
  } else {
    return self->language->lex_fn(&self->lexer.data, lex_mode.lex_state);
  }
}
static _Bool ts_parser__call_keyword_lex_fn(TSParser *self) {
  if (ts_language_is_wasm(self->language)) {
    return ts_wasm_store_call_lex_keyword(self->wasm_store, 0);
  } else {
    return self->language->keyword_lex_fn(&self->lexer.data, 0);
  }
}
static void ts_parser__external_scanner_create(
  TSParser *self
) {
  if (self->language && self->language->external_scanner.states) {
    if (ts_language_is_wasm(self->language)) {
      self->external_scanner_payload = (void *)(uintptr_t)ts_wasm_store_call_scanner_create(
        self->wasm_store
      );
      if (ts_wasm_store_has_error(self->wasm_store)) {
        self->has_scanner_error = 1;
      }
    } else if (self->language->external_scanner.create) {
      self->external_scanner_payload = self->language->external_scanner.create();
    }
  }
}
static void ts_parser__external_scanner_destroy(
  TSParser *self
) {
  if (
    self->language &&
    self->external_scanner_payload &&
    self->language->external_scanner.destroy &&
    !ts_language_is_wasm(self->language)
  ) {
    self->language->external_scanner.destroy(
      self->external_scanner_payload
    );
  }
  self->external_scanner_payload = ((void *)0);
}
static unsigned ts_parser__external_scanner_serialize(
  TSParser *self
) {
  if (ts_language_is_wasm(self->language)) {
    return ts_wasm_store_call_scanner_serialize(
      self->wasm_store,
      (uintptr_t)self->external_scanner_payload,
      self->lexer.debug_buffer
    );
  } else {
    uint32_t length = self->language->external_scanner.serialize(
      self->external_scanner_payload,
      self->lexer.debug_buffer
    );
    (__builtin_expect(!(length <= 1024), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./parser.c", 410, "length <= 1024") : (void)0);
    return length;
  }
}
static void ts_parser__external_scanner_deserialize(
  TSParser *self,
  Subtree external_token
) {
  const char *data = ((void *)0);
  uint32_t length = 0;
  if (external_token.ptr) {
    data = ts_external_scanner_state_data(&external_token.ptr->external_scanner_state);
    length = external_token.ptr->external_scanner_state.length;
  }
  if (ts_language_is_wasm(self->language)) {
    ts_wasm_store_call_scanner_deserialize(
      self->wasm_store,
      (uintptr_t)self->external_scanner_payload,
      data,
      length
    );
    if (ts_wasm_store_has_error(self->wasm_store)) {
      self->has_scanner_error = 1;
    }
  } else {
    self->language->external_scanner.deserialize(
      self->external_scanner_payload,
      data,
      length
    );
  }
}
static _Bool ts_parser__external_scanner_scan(
  TSParser *self,
  TSStateId external_lex_state
) {
  if (ts_language_is_wasm(self->language)) {
    _Bool result = ts_wasm_store_call_scanner_scan(
      self->wasm_store,
      (uintptr_t)self->external_scanner_payload,
      external_lex_state * self->language->external_token_count
    );
    if (ts_wasm_store_has_error(self->wasm_store)) {
      self->has_scanner_error = 1;
    }
    return result;
  } else {
    const _Bool *valid_external_tokens = ts_language_enabled_external_tokens(
      self->language,
      external_lex_state
    );
    return self->language->external_scanner.scan(
      self->external_scanner_payload,
      &self->lexer.data,
      valid_external_tokens
    );
  }
}
static _Bool ts_parser__can_reuse_first_leaf(
  TSParser *self,
  TSStateId state,
  Subtree tree,
  TableEntry *table_entry
) {
  TSSymbol leaf_symbol = ts_subtree_leaf_symbol(tree);
  TSStateId leaf_state = ts_subtree_leaf_parse_state(tree);
  TSLexerMode current_lex_mode = ts_language_lex_mode_for_state(self->language, state);
  TSLexerMode leaf_lex_mode = ts_language_lex_mode_for_state(self->language, leaf_state);
  if (current_lex_mode.lex_state == (uint16_t)(-1)) return 0;
  if (
    table_entry->action_count > 0 &&
    memcmp(&leaf_lex_mode, &current_lex_mode, sizeof(TSLexerMode)) == 0 &&
    (
      leaf_symbol != self->language->keyword_capture_token ||
      (!ts_subtree_is_keyword(tree) && ts_subtree_parse_state(tree) == state)
    )
  ) return 1;
  if (ts_subtree_size(tree).bytes == 0 && leaf_symbol != 0) return 0;
  return current_lex_mode.external_lex_state == 0 && table_entry->is_reusable;
}
static Subtree ts_parser__lex(
  TSParser *self,
  StackVersion version,
  TSStateId parse_state
) {
  TSLexerMode lex_mode = ts_language_lex_mode_for_state(self->language, parse_state);
  if (lex_mode.lex_state == (uint16_t)-1) {
    if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "no_lookahead_after_non_terminal_extra"); ts_parser__log(self); };
    return ((Subtree) {.ptr = ((void *)0)});
  }
  const Length start_position = ts_stack_position(self->stack, version);
  const Subtree external_token = ts_stack_last_external_token(self->stack, version);
  _Bool found_external_token = 0;
  _Bool error_mode = parse_state == 0;
  _Bool skipped_error = 0;
  _Bool called_get_column = 0;
  int32_t first_error_character = 0;
  Length error_start_position = length_zero();
  Length error_end_position = length_zero();
  uint32_t lookahead_end_byte = 0;
  uint32_t external_scanner_state_len = 0;
  _Bool external_scanner_state_changed = 0;
  ts_lexer_reset(&self->lexer, start_position);
  for (;;) {
    _Bool found_token = 0;
    Length current_position = self->lexer.current_position;
    ColumnData column_data = self->lexer.column_data;
    if (lex_mode.external_lex_state != 0) {
      if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "lex_external state:%d, row:%u, column:%u", lex_mode.external_lex_state, current_position.extent.row, current_position.extent.column); ts_parser__log(self); };
      ts_lexer_start(&self->lexer);
      ts_parser__external_scanner_deserialize(self, external_token);
      found_token = ts_parser__external_scanner_scan(self, lex_mode.external_lex_state);
      if (self->has_scanner_error) return ((Subtree) {.ptr = ((void *)0)});
      ts_lexer_finish(&self->lexer, &lookahead_end_byte);
      if (found_token) {
        external_scanner_state_len = ts_parser__external_scanner_serialize(self);
        external_scanner_state_changed = !ts_external_scanner_state_eq(
          ts_subtree_external_scanner_state(external_token),
          self->lexer.debug_buffer,
          external_scanner_state_len
        );
        if (
          self->lexer.token_end_position.bytes <= current_position.bytes &&
          !external_scanner_state_changed
        ) {
          TSSymbol symbol = self->language->external_scanner.symbol_map[self->lexer.data.result_symbol];
          TSStateId next_parse_state = ts_language_next_state(self->language, parse_state, symbol);
          _Bool token_is_extra = (next_parse_state == parse_state);
          if (error_mode || !ts_stack_has_advanced_since_error(self->stack, version) || token_is_extra) {
            if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "ignore_empty_external_token symbol:%s", ts_language_symbol_name(self->language, self->language->external_scanner.symbol_map[self->lexer.data.result_symbol])); ts_parser__log(self); };
            found_token = 0;
          }
        }
      }
      if (found_token) {
        found_external_token = 1;
        called_get_column = self->lexer.did_get_column;
        break;
      }
      ts_lexer_reset(&self->lexer, current_position);
      self->lexer.column_data = column_data;
    }
    if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "lex_internal state:%d, row:%u, column:%u", lex_mode.lex_state, current_position.extent.row, current_position.extent.column); ts_parser__log(self); };
    ts_lexer_start(&self->lexer);
    found_token = ts_parser__call_main_lex_fn(self, lex_mode);
    ts_lexer_finish(&self->lexer, &lookahead_end_byte);
    if (found_token) break;
    if (!error_mode) {
      error_mode = 1;
      lex_mode = ts_language_lex_mode_for_state(self->language, 0);
      ts_lexer_reset(&self->lexer, start_position);
      continue;
    }
    if (!skipped_error) {
      if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "skip_unrecognized_character"); ts_parser__log(self); };
      skipped_error = 1;
      error_start_position = self->lexer.token_start_position;
      error_end_position = self->lexer.token_start_position;
      first_error_character = self->lexer.data.lookahead;
    }
    if (self->lexer.current_position.bytes == error_end_position.bytes) {
      if (self->lexer.data.eof(&self->lexer.data)) {
        self->lexer.data.result_symbol = ((TSSymbol)-1);
        break;
      }
      self->lexer.data.advance(&self->lexer.data, 0);
    }
    error_end_position = self->lexer.current_position;
  }
  Subtree result;
  if (skipped_error) {
    Length padding = length_sub(error_start_position, start_position);
    Length size = length_sub(error_end_position, error_start_position);
    uint32_t lookahead_bytes = lookahead_end_byte - error_end_position.bytes;
    result = ts_subtree_new_error(
      &self->tree_pool,
      first_error_character,
      padding,
      size,
      lookahead_bytes,
      parse_state,
      self->language
    );
  } else {
    _Bool is_keyword = 0;
    TSSymbol symbol = self->lexer.data.result_symbol;
    Length padding = length_sub(self->lexer.token_start_position, start_position);
    Length size = length_sub(self->lexer.token_end_position, self->lexer.token_start_position);
    uint32_t lookahead_bytes = lookahead_end_byte - self->lexer.token_end_position.bytes;
    if (found_external_token) {
      symbol = self->language->external_scanner.symbol_map[symbol];
    } else if (symbol == self->language->keyword_capture_token && symbol != 0) {
      uint32_t end_byte = self->lexer.token_end_position.bytes;
      ts_lexer_reset(&self->lexer, self->lexer.token_start_position);
      ts_lexer_start(&self->lexer);
      is_keyword = ts_parser__call_keyword_lex_fn(self);
      if (
        is_keyword &&
        self->lexer.token_end_position.bytes == end_byte &&
        (
          ts_language_has_actions(self->language, parse_state, self->lexer.data.result_symbol) ||
          ts_language_is_reserved_word(self->language, parse_state, self->lexer.data.result_symbol)
        )
      ) {
        symbol = self->lexer.data.result_symbol;
      }
    }
    result = ts_subtree_new_leaf(
      &self->tree_pool,
      symbol,
      padding,
      size,
      lookahead_bytes,
      parse_state,
      found_external_token,
      called_get_column,
      is_keyword,
      self->language
    );
    if (found_external_token) {
      MutableSubtree mut_result = ts_subtree_to_mut_unsafe(result);
      ts_external_scanner_state_init(
        &mut_result.ptr->external_scanner_state,
        self->lexer.debug_buffer,
        external_scanner_state_len
      );
      mut_result.ptr->has_external_scanner_state_change = external_scanner_state_changed;
    }
  }
  if (self->lexer.logger.log || self->dot_graph_file) { char *buf = self->lexer.debug_buffer; const char *symbol = ts_language_symbol_name(self->language, ts_subtree_symbol(result)); int off = snprintf( buf, 1024, "lexed_lookahead sym:" ); for ( int i = 0; symbol[i] != '\0' && off < 1024; i++ ) { switch (symbol[i]) { case '\t': buf[off++] = '\\'; buf[off++] = 't'; break; case '\n': buf[off++] = '\\'; buf[off++] = 'n'; break; case '\v': buf[off++] = '\\'; buf[off++] = 'v'; break; case '\f': buf[off++] = '\\'; buf[off++] = 'f'; break; case '\r': buf[off++] = '\\'; buf[off++] = 'r'; break; case '\\': buf[off++] = '\\'; buf[off++] = '\\'; break; default: buf[off++] = symbol[i]; break; } } snprintf( buf + off, 1024 - off, ", size:%u", ts_subtree_total_size(result).bytes ); ts_parser__log(self); };
  return result;
}
static Subtree ts_parser__get_cached_token(
  TSParser *self,
  TSStateId state,
  size_t position,
  Subtree last_external_token,
  TableEntry *table_entry
) {
  TokenCache *cache = &self->token_cache;
  if (
    cache->token.ptr && cache->byte_index == position &&
    ts_subtree_external_scanner_state_eq(cache->last_external_token, last_external_token)
  ) {
    ts_language_table_entry(self->language, state, ts_subtree_symbol(cache->token), table_entry);
    if (ts_parser__can_reuse_first_leaf(self, state, cache->token, table_entry)) {
      ts_subtree_retain(cache->token);
      return cache->token;
    }
  }
  return ((Subtree) {.ptr = ((void *)0)});
}
static void ts_parser__set_cached_token(
  TSParser *self,
  uint32_t byte_index,
  Subtree last_external_token,
  Subtree token
) {
  TokenCache *cache = &self->token_cache;
  if (token.ptr) ts_subtree_retain(token);
  if (last_external_token.ptr) ts_subtree_retain(last_external_token);
  if (cache->token.ptr) ts_subtree_release(&self->tree_pool, cache->token);
  if (cache->last_external_token.ptr) ts_subtree_release(&self->tree_pool, cache->last_external_token);
  cache->token = token;
  cache->byte_index = byte_index;
  cache->last_external_token = last_external_token;
}
static _Bool ts_parser__has_included_range_difference(
  const TSParser *self,
  uint32_t start_position,
  uint32_t end_position
) {
  return ts_range_array_intersects(
    &self->included_range_differences,
    self->included_range_difference_index,
    start_position,
    end_position
  );
}
static Subtree ts_parser__reuse_node(
  TSParser *self,
  StackVersion version,
  TSStateId *state,
  uint32_t position,
  Subtree last_external_token,
  TableEntry *table_entry
) {
  Subtree result;
  while ((result = reusable_node_tree(&self->reusable_node)).ptr) {
    uint32_t byte_offset = reusable_node_byte_offset(&self->reusable_node);
    uint32_t end_byte_offset = byte_offset + ts_subtree_total_bytes(result);
    if (ts_subtree_is_eof(result)) end_byte_offset = 4294967295U;
    if (byte_offset > position) {
      if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "before_reusable_node symbol:%s", ts_language_symbol_name(self->language, ts_subtree_symbol(result))); ts_parser__log(self); };
      break;
    }
    if (byte_offset < position) {
      if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "past_reusable_node symbol:%s", ts_language_symbol_name(self->language, ts_subtree_symbol(result))); ts_parser__log(self); };
      if (end_byte_offset <= position || !reusable_node_descend(&self->reusable_node)) {
        reusable_node_advance(&self->reusable_node);
      }
      continue;
    }
    if (!ts_subtree_external_scanner_state_eq(self->reusable_node.last_external_token, last_external_token)) {
      if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "reusable_node_has_different_external_scanner_state symbol:%s", ts_language_symbol_name(self->language, ts_subtree_symbol(result))); ts_parser__log(self); };
      reusable_node_advance(&self->reusable_node);
      continue;
    }
    const char *reason = ((void *)0);
    if (ts_subtree_has_changes(result)) {
      reason = "has_changes";
    } else if (ts_subtree_is_error(result)) {
      reason = "is_error";
    } else if (ts_subtree_missing(result)) {
      reason = "is_missing";
    } else if (ts_subtree_is_fragile(result)) {
      reason = "is_fragile";
    } else if (ts_parser__has_included_range_difference(self, byte_offset, end_byte_offset)) {
      reason = "contains_different_included_range";
    }
    if (reason) {
      if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "cant_reuse_node_%s tree:%s", reason, ts_language_symbol_name(self->language, ts_subtree_symbol(result))); ts_parser__log(self); };
      if (!reusable_node_descend(&self->reusable_node)) {
        reusable_node_advance(&self->reusable_node);
        ts_parser__breakdown_top_of_stack(self, version);
        *state = ts_stack_state(self->stack, version);
      }
      continue;
    }
    TSSymbol leaf_symbol = ts_subtree_leaf_symbol(result);
    ts_language_table_entry(self->language, *state, leaf_symbol, table_entry);
    if (!ts_parser__can_reuse_first_leaf(self, *state, result, table_entry)) {
      if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "cant_reuse_node symbol:%s, first_leaf_symbol:%s", ts_language_symbol_name(self->language, ts_subtree_symbol(result)), ts_language_symbol_name(self->language, leaf_symbol)); ts_parser__log(self); };
      reusable_node_advance_past_leaf(&self->reusable_node);
      break;
    }
    if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "reuse_node symbol:%s", ts_language_symbol_name(self->language, ts_subtree_symbol(result))); ts_parser__log(self); };
    ts_subtree_retain(result);
    return result;
  }
  return ((Subtree) {.ptr = ((void *)0)});
}
static _Bool ts_parser__select_tree(TSParser *self, Subtree left, Subtree right) {
  if (!left.ptr) return 1;
  if (!right.ptr) return 0;
  if (ts_subtree_error_cost(right) < ts_subtree_error_cost(left)) {
    if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "select_smaller_error symbol:%s, over_symbol:%s", ts_language_symbol_name(self->language, ts_subtree_symbol(right)), ts_language_symbol_name(self->language, ts_subtree_symbol(left))); ts_parser__log(self); };
    return 1;
  }
  if (ts_subtree_error_cost(left) < ts_subtree_error_cost(right)) {
    if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "select_smaller_error symbol:%s, over_symbol:%s", ts_language_symbol_name(self->language, ts_subtree_symbol(left)), ts_language_symbol_name(self->language, ts_subtree_symbol(right))); ts_parser__log(self); };
    return 0;
  }
  if (ts_subtree_dynamic_precedence(right) > ts_subtree_dynamic_precedence(left)) {
    if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "select_higher_precedence symbol:%s, prec:%" "d" ", over_symbol:%s, other_prec:%" "d", ts_language_symbol_name(self->language, ts_subtree_symbol(right)), ts_subtree_dynamic_precedence(right), ts_language_symbol_name(self->language, ts_subtree_symbol(left)), ts_subtree_dynamic_precedence(left)); ts_parser__log(self); };
    return 1;
  }
  if (ts_subtree_dynamic_precedence(left) > ts_subtree_dynamic_precedence(right)) {
    if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "select_higher_precedence symbol:%s, prec:%" "d" ", over_symbol:%s, other_prec:%" "d", ts_language_symbol_name(self->language, ts_subtree_symbol(left)), ts_subtree_dynamic_precedence(left), ts_language_symbol_name(self->language, ts_subtree_symbol(right)), ts_subtree_dynamic_precedence(right)); ts_parser__log(self); };
    return 0;
  }
  if (ts_subtree_error_cost(left) > 0) return 1;
  int comparison = ts_subtree_compare(left, right, &self->tree_pool);
  switch (comparison) {
    case -1:
      if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "select_earlier symbol:%s, over_symbol:%s", ts_language_symbol_name(self->language, ts_subtree_symbol(left)), ts_language_symbol_name(self->language, ts_subtree_symbol(right))); ts_parser__log(self); };
      return 0;
      break;
    case 1:
      if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "select_earlier symbol:%s, over_symbol:%s", ts_language_symbol_name(self->language, ts_subtree_symbol(right)), ts_language_symbol_name(self->language, ts_subtree_symbol(left))); ts_parser__log(self); };
      return 1;
    default:
      if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "select_existing symbol:%s, over_symbol:%s", ts_language_symbol_name(self->language, ts_subtree_symbol(left)), ts_language_symbol_name(self->language, ts_subtree_symbol(right))); ts_parser__log(self); };
      return 0;
  }
}
static _Bool ts_parser__select_children(
  TSParser *self,
  Subtree left,
  const SubtreeArray *children
) {
  _array__assign((Array *)(&self->scratch_trees), (const Array *)(children), (sizeof *(&self->scratch_trees)->contents));
  MutableSubtree scratch_tree = ts_subtree_new_node(
    ts_subtree_symbol(left),
    &self->scratch_trees,
    0,
    self->language
  );
  return ts_parser__select_tree(
    self,
    left,
    ts_subtree_from_mut(scratch_tree)
  );
}
static void ts_parser__shift(
  TSParser *self,
  StackVersion version,
  TSStateId state,
  Subtree lookahead,
  _Bool extra
) {
  _Bool is_leaf = ts_subtree_child_count(lookahead) == 0;
  Subtree subtree_to_push = lookahead;
  if (extra != ts_subtree_extra(lookahead) && is_leaf) {
    MutableSubtree result = ts_subtree_make_mut(&self->tree_pool, lookahead);
    ts_subtree_set_extra(&result, extra);
    subtree_to_push = ts_subtree_from_mut(result);
  }
  ts_stack_push(self->stack, version, subtree_to_push, !is_leaf, state);
  if (ts_subtree_has_external_tokens(subtree_to_push)) {
    ts_stack_set_last_external_token(
      self->stack, version, ts_subtree_last_external_token(subtree_to_push)
    );
  }
}
static StackVersion ts_parser__reduce(
  TSParser *self,
  StackVersion version,
  TSSymbol symbol,
  uint32_t count,
  int dynamic_precedence,
  uint16_t production_id,
  _Bool is_fragile,
  _Bool end_of_non_terminal_extra
) {
  uint32_t initial_version_count = ts_stack_version_count(self->stack);
  StackSliceArray pop = ts_stack_pop_count(self->stack, version, count);
  uint32_t removed_version_count = 0;
  for (uint32_t i = 0; i < pop.size; i++) {
    StackSlice slice = pop.contents[i];
    StackVersion slice_version = slice.version - removed_version_count;
    if (slice_version > MAX_VERSION_COUNT + MAX_VERSION_COUNT_OVERFLOW) {
      ts_stack_remove_version(self->stack, slice_version);
      ts_subtree_array_delete(&self->tree_pool, &slice.subtrees);
      removed_version_count++;
      while (i + 1 < pop.size) {
        StackSlice next_slice = pop.contents[i + 1];
        if (next_slice.version != slice.version) break;
        ts_subtree_array_delete(&self->tree_pool, &next_slice.subtrees);
        i++;
      }
      continue;
    }
    SubtreeArray children = slice.subtrees;
    ts_subtree_array_remove_trailing_extras(&children, &self->trailing_extras);
    MutableSubtree parent = ts_subtree_new_node(
      symbol, &children, production_id, self->language
    );
    while (i + 1 < pop.size) {
      StackSlice next_slice = pop.contents[i + 1];
      if (next_slice.version != slice.version) break;
      i++;
      SubtreeArray next_slice_children = next_slice.subtrees;
      ts_subtree_array_remove_trailing_extras(&next_slice_children, &self->trailing_extras2);
      if (ts_parser__select_children(
        self,
        ts_subtree_from_mut(parent),
        &next_slice_children
      )) {
        ts_subtree_array_clear(&self->tree_pool, &self->trailing_extras);
        ts_subtree_release(&self->tree_pool, ts_subtree_from_mut(parent));
        _array__swap((Array *)(&self->trailing_extras), (Array *)(&self->trailing_extras2));
        parent = ts_subtree_new_node(
          symbol, &next_slice_children, production_id, self->language
        );
      } else {
        ((&self->trailing_extras2)->size = 0);
        ts_subtree_array_delete(&self->tree_pool, &next_slice.subtrees);
      }
    }
    TSStateId state = ts_stack_state(self->stack, slice_version);
    TSStateId next_state = ts_language_next_state(self->language, state, symbol);
    if (end_of_non_terminal_extra && next_state == state) {
      parent.ptr->extra = 1;
    }
    if (is_fragile || pop.size > 1 || initial_version_count > 1) {
      parent.ptr->fragile_left = 1;
      parent.ptr->fragile_right = 1;
      parent.ptr->parse_state = 65535;
    } else {
      parent.ptr->parse_state = state;
    }
    parent.ptr->dynamic_precedence += dynamic_precedence;
    ts_stack_push(self->stack, slice_version, ts_subtree_from_mut(parent), 0, next_state);
    for (uint32_t j = 0; j < self->trailing_extras.size; j++) {
      ts_stack_push(self->stack, slice_version, self->trailing_extras.contents[j], 0, next_state);
    }
    for (StackVersion j = 0; j < slice_version; j++) {
      if (j == version) continue;
      if (ts_stack_merge(self->stack, j, slice_version)) {
        removed_version_count++;
        break;
      }
    }
  }
  return ts_stack_version_count(self->stack) > initial_version_count
    ? initial_version_count
    : ((StackVersion)-1);
}
static void ts_parser__accept(
  TSParser *self,
  StackVersion version,
  Subtree lookahead
) {
  (__builtin_expect(!(ts_subtree_is_eof(lookahead)), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./parser.c", 1053, "ts_subtree_is_eof(lookahead)") : (void)0);
  ts_stack_push(self->stack, version, lookahead, 0, 1);
  StackSliceArray pop = ts_stack_pop_all(self->stack, version);
  for (uint32_t i = 0; i < pop.size; i++) {
    SubtreeArray trees = pop.contents[i].subtrees;
    Subtree root = ((Subtree) {.ptr = ((void *)0)});
    for (uint32_t j = trees.size - 1; j + 1 > 0; j--) {
      Subtree tree = trees.contents[j];
      if (!ts_subtree_extra(tree)) {
        (__builtin_expect(!(!tree.data.is_inline), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./parser.c", 1064, "!tree.data.is_inline") : (void)0);
        uint32_t child_count = ts_subtree_child_count(tree);
        const Subtree *children = ((tree).data.is_inline ? ((void *)0) : (Subtree *)((tree).ptr) - (tree).ptr->child_count);
        for (uint32_t k = 0; k < child_count; k++) {
          ts_subtree_retain(children[k]);
        }
        _array__splice( (Array *)(&trees), (sizeof *(&trees)->contents), j, 1, child_count, children );
        root = ts_subtree_from_mut(ts_subtree_new_node(
          ts_subtree_symbol(tree),
          &trees,
          tree.ptr->production_id,
          self->language
        ));
        ts_subtree_release(&self->tree_pool, tree);
        break;
      }
    }
    (__builtin_expect(!(root.ptr), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./parser.c", 1082, "root.ptr") : (void)0);
    self->accept_count++;
    if (self->finished_tree.ptr) {
      if (ts_parser__select_tree(self, self->finished_tree, root)) {
        ts_subtree_release(&self->tree_pool, self->finished_tree);
        self->finished_tree = root;
      } else {
        ts_subtree_release(&self->tree_pool, root);
      }
    } else {
      self->finished_tree = root;
    }
  }
  ts_stack_remove_version(self->stack, pop.contents[0].version);
  ts_stack_halt(self->stack, version);
}
static _Bool ts_parser__do_all_potential_reductions(
  TSParser *self,
  StackVersion starting_version,
  TSSymbol lookahead_symbol
) {
  uint32_t initial_version_count = ts_stack_version_count(self->stack);
  _Bool can_shift_lookahead_symbol = 0;
  StackVersion version = starting_version;
  for (unsigned i = 0; 1; i++) {
    uint32_t version_count = ts_stack_version_count(self->stack);
    if (version >= version_count) break;
    _Bool merged = 0;
    for (StackVersion j = initial_version_count; j < version; j++) {
      if (ts_stack_merge(self->stack, j, version)) {
        merged = 1;
        break;
      }
    }
    if (merged) continue;
    TSStateId state = ts_stack_state(self->stack, version);
    _Bool has_shift_action = 0;
    ((&self->reduce_actions)->size = 0);
    TSSymbol first_symbol, end_symbol;
    if (lookahead_symbol != 0) {
      first_symbol = lookahead_symbol;
      end_symbol = lookahead_symbol + 1;
    } else {
      first_symbol = 1;
      end_symbol = self->language->token_count;
    }
    for (TSSymbol symbol = first_symbol; symbol < end_symbol; symbol++) {
      TableEntry entry;
      ts_language_table_entry(self->language, state, symbol, &entry);
      for (uint32_t j = 0; j < entry.action_count; j++) {
        TSParseAction action = entry.actions[j];
        switch (action.type) {
          case TSParseActionTypeShift:
          case TSParseActionTypeRecover:
            if (!action.shift.extra && !action.shift.repetition) has_shift_action = 1;
            break;
          case TSParseActionTypeReduce:
            if (action.reduce.child_count > 0)
              ts_reduce_action_set_add(&self->reduce_actions, (ReduceAction) {
                .symbol = action.reduce.symbol,
                .count = action.reduce.child_count,
                .dynamic_precedence = action.reduce.dynamic_precedence,
                .production_id = action.reduce.production_id,
              });
            break;
          default:
            break;
        }
      }
    }
    StackVersion reduction_version = ((StackVersion)-1);
    for (uint32_t j = 0; j < self->reduce_actions.size; j++) {
      ReduceAction action = self->reduce_actions.contents[j];
      reduction_version = ts_parser__reduce(
        self, version, action.symbol, action.count,
        action.dynamic_precedence, action.production_id,
        1, 0
      );
    }
    if (has_shift_action) {
      can_shift_lookahead_symbol = 1;
    } else if (reduction_version != ((StackVersion)-1) && i < MAX_VERSION_COUNT) {
      ts_stack_renumber_version(self->stack, reduction_version, version);
      continue;
    } else if (lookahead_symbol != 0) {
      ts_stack_remove_version(self->stack, version);
    }
    if (version == starting_version) {
      version = version_count;
    } else {
      version++;
    }
  }
  return can_shift_lookahead_symbol;
}
static _Bool ts_parser__recover_to_state(
  TSParser *self,
  StackVersion version,
  unsigned depth,
  TSStateId goal_state
) {
  StackSliceArray pop = ts_stack_pop_count(self->stack, version, depth);
  StackVersion previous_version = ((StackVersion)-1);
  for (unsigned i = 0; i < pop.size; i++) {
    StackSlice slice = pop.contents[i];
    if (slice.version == previous_version) {
      ts_subtree_array_delete(&self->tree_pool, &slice.subtrees);
      _array__erase((Array *)(&pop), (sizeof *(&pop)->contents), i--);
      continue;
    }
    if (ts_stack_state(self->stack, slice.version) != goal_state) {
      ts_stack_halt(self->stack, slice.version);
      ts_subtree_array_delete(&self->tree_pool, &slice.subtrees);
      _array__erase((Array *)(&pop), (sizeof *(&pop)->contents), i--);
      continue;
    }
    SubtreeArray error_trees = ts_stack_pop_error(self->stack, slice.version);
    if (error_trees.size > 0) {
      (__builtin_expect(!(error_trees.size == 1), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./parser.c", 1218, "error_trees.size == 1") : (void)0);
      Subtree error_tree = error_trees.contents[0];
      uint32_t error_child_count = ts_subtree_child_count(error_tree);
      if (error_child_count > 0) {
        _array__splice( (Array *)(&slice.subtrees), (sizeof *(&slice.subtrees)->contents), 0, 0, error_child_count, ((error_tree).data.is_inline ? ((void *)0) : (Subtree *)((error_tree).ptr) - (error_tree).ptr->child_count) );
        for (unsigned j = 0; j < error_child_count; j++) {
          ts_subtree_retain(slice.subtrees.contents[j]);
        }
      }
      ts_subtree_array_delete(&self->tree_pool, &error_trees);
    }
    ts_subtree_array_remove_trailing_extras(&slice.subtrees, &self->trailing_extras);
    if (slice.subtrees.size > 0) {
      Subtree error = ts_subtree_new_error_node(&slice.subtrees, 1, self->language);
      ts_stack_push(self->stack, slice.version, error, 0, goal_state);
    } else {
      _array__delete((Array *)(&slice.subtrees));
    }
    for (unsigned j = 0; j < self->trailing_extras.size; j++) {
      Subtree tree = self->trailing_extras.contents[j];
      ts_stack_push(self->stack, slice.version, tree, 0, goal_state);
    }
    previous_version = slice.version;
  }
  return previous_version != ((StackVersion)-1);
}
static void ts_parser__recover(
  TSParser *self,
  StackVersion version,
  Subtree lookahead
) {
  _Bool did_recover = 0;
  unsigned previous_version_count = ts_stack_version_count(self->stack);
  Length position = ts_stack_position(self->stack, version);
  StackSummary *summary = ts_stack_get_summary(self->stack, version);
  unsigned node_count_since_error = ts_stack_node_count_since_error(self->stack, version);
  unsigned current_error_cost = ts_stack_error_cost(self->stack, version);
  if (summary && !ts_subtree_is_error(lookahead)) {
    for (unsigned i = 0; i < summary->size; i++) {
      StackSummaryEntry entry = summary->contents[i];
      if (entry.state == 0) continue;
      if (entry.position.bytes == position.bytes) continue;
      unsigned depth = entry.depth;
      if (node_count_since_error > 0) depth++;
      _Bool would_merge = 0;
      for (unsigned j = 0; j < previous_version_count; j++) {
        if (
          ts_stack_state(self->stack, j) == entry.state &&
          ts_stack_position(self->stack, j).bytes == position.bytes
        ) {
          would_merge = 1;
          break;
        }
      }
      if (would_merge) continue;
      unsigned new_cost =
        current_error_cost +
        entry.depth * 100 +
        (position.bytes - entry.position.bytes) * 1 +
        (position.extent.row - entry.position.extent.row) * 30;
      if (ts_parser__better_version_exists(self, version, 0, new_cost)) break;
      if (ts_language_has_actions(self->language, entry.state, ts_subtree_symbol(lookahead))) {
        if (ts_parser__recover_to_state(self, version, depth, entry.state)) {
          did_recover = 1;
          if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "recover_to_previous state:%u, depth:%u", entry.state, depth); ts_parser__log(self); };
          if (self->dot_graph_file) { ts_stack_print_dot_graph(self->stack, self->language, self->dot_graph_file); fputs("\n\n", self->dot_graph_file); };
          break;
        }
      }
    }
  }
  for (unsigned i = previous_version_count; i < ts_stack_version_count(self->stack); i++) {
    if (!ts_stack_is_active(self->stack, i)) {
      ts_stack_remove_version(self->stack, i--);
    }
  }
  if (did_recover && ts_stack_version_count(self->stack) > MAX_VERSION_COUNT) {
    ts_stack_halt(self->stack, version);
    ts_subtree_release(&self->tree_pool, lookahead);
    return;
  }
  if (
    did_recover &&
    ts_subtree_has_external_scanner_state_change(lookahead)
  ) {
    ts_stack_halt(self->stack, version);
    ts_subtree_release(&self->tree_pool, lookahead);
    return;
  }
  if (ts_subtree_is_eof(lookahead)) {
    if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "recover_eof"); ts_parser__log(self); };
    SubtreeArray children = { ((void *)0), 0, 0 };
    Subtree parent = ts_subtree_new_error_node(&children, 0, self->language);
    ts_stack_push(self->stack, version, parent, 0, 1);
    ts_parser__accept(self, version, lookahead);
    return;
  }
  unsigned new_cost =
    current_error_cost + 100 +
    ts_subtree_total_bytes(lookahead) * 1 +
    ts_subtree_total_size(lookahead).extent.row * 30;
  if (ts_parser__better_version_exists(self, version, 0, new_cost)) {
    ts_stack_halt(self->stack, version);
    ts_subtree_release(&self->tree_pool, lookahead);
    return;
  }
  unsigned n;
  const TSParseAction *actions = ts_language_actions(self->language, 1, ts_subtree_symbol(lookahead), &n);
  if (n > 0 && actions[n - 1].type == TSParseActionTypeShift && actions[n - 1].shift.extra) {
    MutableSubtree mutable_lookahead = ts_subtree_make_mut(&self->tree_pool, lookahead);
    ts_subtree_set_extra(&mutable_lookahead, 1);
    lookahead = ts_subtree_from_mut(mutable_lookahead);
  }
  if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "skip_token symbol:%s", ts_language_symbol_name(self->language, ts_subtree_symbol(lookahead))); ts_parser__log(self); };
  SubtreeArray children = { ((void *)0), 0, 0 };
  _array__reserve((Array *)(&children), (sizeof *(&children)->contents), 1);
  (_array__grow((Array *)(&children), 1, (sizeof *(&children)->contents)), (&children)->contents[(&children)->size++] = (lookahead));
  MutableSubtree error_repeat = ts_subtree_new_node(
    (((TSSymbol)-1) - 1),
    &children,
    0,
    self->language
  );
  if (node_count_since_error > 0) {
    StackSliceArray pop = ts_stack_pop_count(self->stack, version, 1);
    if (pop.size > 1) {
      for (unsigned i = 1; i < pop.size; i++) {
        ts_subtree_array_delete(&self->tree_pool, &pop.contents[i].subtrees);
      }
      while (ts_stack_version_count(self->stack) > pop.contents[0].version + 1) {
        ts_stack_remove_version(self->stack, pop.contents[0].version + 1);
      }
    }
    ts_stack_renumber_version(self->stack, pop.contents[0].version, version);
    (_array__grow((Array *)(&pop.contents[0].subtrees), 1, (sizeof *(&pop.contents[0].subtrees)->contents)), (&pop.contents[0].subtrees)->contents[(&pop.contents[0].subtrees)->size++] = (ts_subtree_from_mut(error_repeat)));
    error_repeat = ts_subtree_new_node(
      (((TSSymbol)-1) - 1),
      &pop.contents[0].subtrees,
      0,
      self->language
    );
  }
  ts_stack_push(self->stack, version, ts_subtree_from_mut(error_repeat), 0, 0);
  if (ts_subtree_has_external_tokens(lookahead)) {
    ts_stack_set_last_external_token(
      self->stack, version, ts_subtree_last_external_token(lookahead)
    );
  }
  _Bool has_error = 1;
  for (unsigned i = 0; i < ts_stack_version_count(self->stack); i++) {
    ErrorStatus status = ts_parser__version_status(self, i);
    if (!status.is_in_error) {
      has_error = 0;
      break;
    }
  }
  self->has_error = has_error;
}
static void ts_parser__handle_error(
  TSParser *self,
  StackVersion version,
  Subtree lookahead
) {
  uint32_t previous_version_count = ts_stack_version_count(self->stack);
  ts_parser__do_all_potential_reductions(self, version, 0);
  uint32_t version_count = ts_stack_version_count(self->stack);
  Length position = ts_stack_position(self->stack, version);
  _Bool did_insert_missing_token = 0;
  for (StackVersion v = version; v < version_count;) {
    if (!did_insert_missing_token) {
      TSStateId state = ts_stack_state(self->stack, v);
      for (
        TSSymbol missing_symbol = 1;
        missing_symbol < (uint16_t)self->language->token_count;
        missing_symbol++
      ) {
        TSStateId state_after_missing_symbol = ts_language_next_state(
          self->language, state, missing_symbol
        );
        if (state_after_missing_symbol == 0 || state_after_missing_symbol == state) {
          continue;
        }
        if (ts_language_has_reduce_action(
          self->language,
          state_after_missing_symbol,
          ts_subtree_leaf_symbol(lookahead)
        )) {
          ts_lexer_reset(&self->lexer, position);
          ts_lexer_mark_end(&self->lexer);
          Length padding = length_sub(self->lexer.token_end_position, position);
          uint32_t lookahead_bytes = ts_subtree_total_bytes(lookahead) + ts_subtree_lookahead_bytes(lookahead);
          StackVersion version_with_missing_tree = ts_stack_copy_version(self->stack, v);
          Subtree missing_tree = ts_subtree_new_missing_leaf(
            &self->tree_pool, missing_symbol,
            padding, lookahead_bytes,
            self->language
          );
          ts_stack_push(
            self->stack, version_with_missing_tree,
            missing_tree, 0,
            state_after_missing_symbol
          );
          if (ts_parser__do_all_potential_reductions(
            self, version_with_missing_tree,
            ts_subtree_leaf_symbol(lookahead)
          )) {
            if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "recover_with_missing symbol:%s, state:%u", ts_language_symbol_name(self->language, missing_symbol), ts_stack_state(self->stack, version_with_missing_tree)); ts_parser__log(self); };
            did_insert_missing_token = 1;
            break;
          }
        }
      }
    }
    ts_stack_push(self->stack, v, ((Subtree) {.ptr = ((void *)0)}), 0, 0);
    v = (v == version) ? previous_version_count : v + 1;
  }
  for (unsigned i = previous_version_count; i < version_count; i++) {
    _Bool did_merge = ts_stack_merge(self->stack, version, previous_version_count);
    (__builtin_expect(!(did_merge), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./parser.c", 1516, "did_merge") : (void)0);
  }
  ts_stack_record_summary(self->stack, version, MAX_SUMMARY_DEPTH);
  if (ts_subtree_child_count(lookahead) > 0) {
    ts_parser__breakdown_lookahead(self, &lookahead, 0, &self->reusable_node);
  }
  ts_parser__recover(self, version, lookahead);
  if (self->dot_graph_file) { ts_stack_print_dot_graph(self->stack, self->language, self->dot_graph_file); fputs("\n\n", self->dot_graph_file); };
}
static _Bool ts_parser__check_progress(TSParser *self, Subtree *lookahead, const uint32_t *position, unsigned operations) {
  self->operation_count += operations;
  if (self->operation_count >= OP_COUNT_PER_PARSER_TIMEOUT_CHECK) {
    self->operation_count = 0;
  }
  if (self->parse_options.progress_callback && position != ((void *)0)) {
    self->parse_state.current_byte_offset = *position;
    self->parse_state.has_error = self->has_error;
  }
  if (
    self->operation_count == 0 &&
    (
      (self->cancellation_flag && atomic_load(self->cancellation_flag)) ||
      (!clock_is_null(self->end_clock) && clock_is_gt(clock_now(), self->end_clock)) ||
      (self->parse_options.progress_callback && self->parse_options.progress_callback(&self->parse_state))
    )
  ) {
    if (lookahead && lookahead->ptr) {
      ts_subtree_release(&self->tree_pool, *lookahead);
    }
    return 0;
  }
  return 1;
}
static _Bool ts_parser__advance(
  TSParser *self,
  StackVersion version,
  _Bool allow_node_reuse
) {
  TSStateId state = ts_stack_state(self->stack, version);
  uint32_t position = ts_stack_position(self->stack, version).bytes;
  Subtree last_external_token = ts_stack_last_external_token(self->stack, version);
  _Bool did_reuse = 1;
  Subtree lookahead = ((Subtree) {.ptr = ((void *)0)});
  TableEntry table_entry = {.action_count = 0};
  if (allow_node_reuse) {
    lookahead = ts_parser__reuse_node(
      self, version, &state, position, last_external_token, &table_entry
    );
  }
  if (!lookahead.ptr) {
    did_reuse = 0;
    lookahead = ts_parser__get_cached_token(
      self, state, position, last_external_token, &table_entry
    );
  }
  _Bool needs_lex = !lookahead.ptr;
  for (;;) {
    if (needs_lex) {
      needs_lex = 0;
      lookahead = ts_parser__lex(self, version, state);
      if (self->has_scanner_error) return 0;
      if (lookahead.ptr) {
        ts_parser__set_cached_token(self, position, last_external_token, lookahead);
        ts_language_table_entry(self->language, state, ts_subtree_symbol(lookahead), &table_entry);
      }
      else {
        ts_language_table_entry(self->language, state, 0, &table_entry);
      }
    }
    if (!ts_parser__check_progress(self, &lookahead, &position, 1)) {
      return 0;
    }
    StackVersion last_reduction_version = ((StackVersion)-1);
    for (uint32_t i = 0; i < table_entry.action_count; i++) {
      TSParseAction action = table_entry.actions[i];
      switch (action.type) {
        case TSParseActionTypeShift: {
          if (action.shift.repetition) break;
          TSStateId next_state;
          if (action.shift.extra) {
            next_state = state;
            if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "shift_extra"); ts_parser__log(self); };
          } else {
            next_state = action.shift.state;
            if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "shift state:%u", next_state); ts_parser__log(self); };
          }
          if (ts_subtree_child_count(lookahead) > 0) {
            ts_parser__breakdown_lookahead(self, &lookahead, state, &self->reusable_node);
            next_state = ts_language_next_state(self->language, state, ts_subtree_symbol(lookahead));
          }
          ts_parser__shift(self, version, next_state, lookahead, action.shift.extra);
          if (did_reuse) reusable_node_advance(&self->reusable_node);
          return 1;
        }
        case TSParseActionTypeReduce: {
          _Bool is_fragile = table_entry.action_count > 1;
          _Bool end_of_non_terminal_extra = lookahead.ptr == ((void *)0);
          if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "reduce sym:%s, child_count:%u", ts_language_symbol_name(self->language, action.reduce.symbol), action.reduce.child_count); ts_parser__log(self); };
          StackVersion reduction_version = ts_parser__reduce(
            self, version, action.reduce.symbol, action.reduce.child_count,
            action.reduce.dynamic_precedence, action.reduce.production_id,
            is_fragile, end_of_non_terminal_extra
          );
          if (reduction_version != ((StackVersion)-1)) {
            last_reduction_version = reduction_version;
          }
          break;
        }
        case TSParseActionTypeAccept: {
          if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "accept"); ts_parser__log(self); };
          ts_parser__accept(self, version, lookahead);
          return 1;
        }
        case TSParseActionTypeRecover: {
          if (ts_subtree_child_count(lookahead) > 0) {
            ts_parser__breakdown_lookahead(self, &lookahead, 0, &self->reusable_node);
          }
          ts_parser__recover(self, version, lookahead);
          if (did_reuse) reusable_node_advance(&self->reusable_node);
          return 1;
        }
      }
    }
    if (last_reduction_version != ((StackVersion)-1)) {
      ts_stack_renumber_version(self->stack, last_reduction_version, version);
      if (self->dot_graph_file) { ts_stack_print_dot_graph(self->stack, self->language, self->dot_graph_file); fputs("\n\n", self->dot_graph_file); };
      state = ts_stack_state(self->stack, version);
      if (!lookahead.ptr) {
        needs_lex = 1;
      } else {
        ts_language_table_entry(
          self->language,
          state,
          ts_subtree_leaf_symbol(lookahead),
          &table_entry
        );
      }
      continue;
    }
    if (!lookahead.ptr) {
      ts_stack_halt(self->stack, version);
      return 1;
    }
    if (
      ts_subtree_is_keyword(lookahead) &&
      ts_subtree_symbol(lookahead) != self->language->keyword_capture_token &&
      !ts_language_is_reserved_word(self->language, state, ts_subtree_symbol(lookahead))
    ) {
      ts_language_table_entry(
        self->language,
        state,
        self->language->keyword_capture_token,
        &table_entry
      );
      if (table_entry.action_count > 0) {
        if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "switch from_keyword:%s, to_word_token:%s", ts_language_symbol_name(self->language, ts_subtree_symbol(lookahead)), ts_language_symbol_name(self->language, self->language->keyword_capture_token)); ts_parser__log(self); };
        MutableSubtree mutable_lookahead = ts_subtree_make_mut(&self->tree_pool, lookahead);
        ts_subtree_set_symbol(&mutable_lookahead, self->language->keyword_capture_token, self->language);
        lookahead = ts_subtree_from_mut(mutable_lookahead);
        continue;
      }
    }
    if (ts_parser__breakdown_top_of_stack(self, version)) {
      state = ts_stack_state(self->stack, version);
      ts_subtree_release(&self->tree_pool, lookahead);
      needs_lex = 1;
      continue;
    }
    if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "detect_error"); ts_parser__log(self); };
    ts_stack_pause(self->stack, version, lookahead);
    return 1;
  }
}
static unsigned ts_parser__condense_stack(TSParser *self) {
  _Bool made_changes = 0;
  unsigned min_error_cost = 0xffffffff;
  for (StackVersion i = 0; i < ts_stack_version_count(self->stack); i++) {
    if (ts_stack_is_halted(self->stack, i)) {
      ts_stack_remove_version(self->stack, i);
      i--;
      continue;
    }
    ErrorStatus status_i = ts_parser__version_status(self, i);
    if (!status_i.is_in_error && status_i.cost < min_error_cost) {
      min_error_cost = status_i.cost;
    }
    for (StackVersion j = 0; j < i; j++) {
      ErrorStatus status_j = ts_parser__version_status(self, j);
      switch (ts_parser__compare_versions(self, status_j, status_i)) {
        case ErrorComparisonTakeLeft:
          made_changes = 1;
          ts_stack_remove_version(self->stack, i);
          i--;
          j = i;
          break;
        case ErrorComparisonPreferLeft:
        case ErrorComparisonNone:
          if (ts_stack_merge(self->stack, j, i)) {
            made_changes = 1;
            i--;
            j = i;
          }
          break;
        case ErrorComparisonPreferRight:
          made_changes = 1;
          if (ts_stack_merge(self->stack, j, i)) {
            i--;
            j = i;
          } else {
            ts_stack_swap_versions(self->stack, i, j);
          }
          break;
        case ErrorComparisonTakeRight:
          made_changes = 1;
          ts_stack_remove_version(self->stack, j);
          i--;
          j--;
          break;
      }
    }
  }
  while (ts_stack_version_count(self->stack) > MAX_VERSION_COUNT) {
    ts_stack_remove_version(self->stack, MAX_VERSION_COUNT);
    made_changes = 1;
  }
  if (ts_stack_version_count(self->stack) > 0) {
    _Bool has_unpaused_version = 0;
    for (StackVersion i = 0, n = ts_stack_version_count(self->stack); i < n; i++) {
      if (ts_stack_is_paused(self->stack, i)) {
        if (!has_unpaused_version && self->accept_count < MAX_VERSION_COUNT) {
          if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "resume version:%u", i); ts_parser__log(self); };
          min_error_cost = ts_stack_error_cost(self->stack, i);
          Subtree lookahead = ts_stack_resume(self->stack, i);
          ts_parser__handle_error(self, i, lookahead);
          has_unpaused_version = 1;
        } else {
          ts_stack_remove_version(self->stack, i);
          i--;
          n--;
        }
      } else {
        has_unpaused_version = 1;
      }
    }
  }
  if (made_changes) {
    if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "condense"); ts_parser__log(self); };
    if (self->dot_graph_file) { ts_stack_print_dot_graph(self->stack, self->language, self->dot_graph_file); fputs("\n\n", self->dot_graph_file); };
  }
  return min_error_cost;
}
static _Bool ts_parser__balance_subtree(TSParser *self) {
  Subtree finished_tree = self->finished_tree;
  if (!self->canceled_balancing) {
    ((&self->tree_pool.tree_stack)->size = 0);
    if (ts_subtree_child_count(finished_tree) > 0 && finished_tree.ptr->ref_count == 1) {
      (_array__grow((Array *)(&self->tree_pool.tree_stack), 1, (sizeof *(&self->tree_pool.tree_stack)->contents)), (&self->tree_pool.tree_stack)->contents[(&self->tree_pool.tree_stack)->size++] = (ts_subtree_to_mut_unsafe(finished_tree)));
    }
  }
  while (self->tree_pool.tree_stack.size > 0) {
    if (!ts_parser__check_progress(self, ((void *)0), ((void *)0), 1)) {
      return 0;
    }
    MutableSubtree tree = self->tree_pool.tree_stack.contents[
      self->tree_pool.tree_stack.size - 1
    ];
    if (tree.ptr->repeat_depth > 0) {
      Subtree child1 = ((tree).data.is_inline ? ((void *)0) : (Subtree *)((tree).ptr) - (tree).ptr->child_count)[0];
      Subtree child2 = ((tree).data.is_inline ? ((void *)0) : (Subtree *)((tree).ptr) - (tree).ptr->child_count)[tree.ptr->child_count - 1];
      long repeat_delta = (long)ts_subtree_repeat_depth(child1) - (long)ts_subtree_repeat_depth(child2);
      if (repeat_delta > 0) {
        unsigned n = (unsigned)repeat_delta;
        for (unsigned i = n / 2; i > 0; i /= 2) {
          ts_subtree_compress(tree, i, self->language, &self->tree_pool.tree_stack);
          n -= i;
          uint8_t operations = i >> 4 > 0 ? i >> 4 : 1;
          if (!ts_parser__check_progress(self, ((void *)0), ((void *)0), operations)) {
            return 0;
          }
        }
      }
    }
    (void)((&self->tree_pool.tree_stack)->contents[--(&self->tree_pool.tree_stack)->size]);
    for (uint32_t i = 0; i < tree.ptr->child_count; i++) {
      Subtree child = ((tree).data.is_inline ? ((void *)0) : (Subtree *)((tree).ptr) - (tree).ptr->child_count)[i];
      if (ts_subtree_child_count(child) > 0 && child.ptr->ref_count == 1) {
        (_array__grow((Array *)(&self->tree_pool.tree_stack), 1, (sizeof *(&self->tree_pool.tree_stack)->contents)), (&self->tree_pool.tree_stack)->contents[(&self->tree_pool.tree_stack)->size++] = (ts_subtree_to_mut_unsafe(child)));
      }
    }
  }
  return 1;
}
static _Bool ts_parser_has_outstanding_parse(TSParser *self) {
  return (
    self->canceled_balancing ||
    self->external_scanner_payload ||
    ts_stack_state(self->stack, 0) != 1 ||
    ts_stack_node_count_since_error(self->stack, 0) != 0
  );
}
TSParser *ts_parser_new(void) {
  TSParser *self = ts_current_calloc(1, sizeof(TSParser));
  ts_lexer_init(&self->lexer);
  ((&self->reduce_actions)->size = 0, (&self->reduce_actions)->capacity = 0, (&self->reduce_actions)->contents = ((void *)0));
  _array__reserve((Array *)(&self->reduce_actions), (sizeof *(&self->reduce_actions)->contents), 4);
  self->tree_pool = ts_subtree_pool_new(32);
  self->stack = ts_stack_new(&self->tree_pool);
  self->finished_tree = ((Subtree) {.ptr = ((void *)0)});
  self->reusable_node = reusable_node_new();
  self->dot_graph_file = ((void *)0);
  self->cancellation_flag = ((void *)0);
  self->timeout_duration = 0;
  self->language = ((void *)0);
  self->has_scanner_error = 0;
  self->has_error = 0;
  self->canceled_balancing = 0;
  self->external_scanner_payload = ((void *)0);
  self->end_clock = clock_null();
  self->operation_count = 0;
  self->old_tree = ((Subtree) {.ptr = ((void *)0)});
  self->included_range_differences = (TSRangeArray) { ((void *)0), 0, 0 };
  self->included_range_difference_index = 0;
  ts_parser__set_cached_token(self, 0, ((Subtree) {.ptr = ((void *)0)}), ((Subtree) {.ptr = ((void *)0)}));
  return self;
}
void ts_parser_delete(TSParser *self) {
  if (!self) return;
  ts_parser_set_language(self, ((void *)0));
  ts_stack_delete(self->stack);
  if (self->reduce_actions.contents) {
    _array__delete((Array *)(&self->reduce_actions));
  }
  if (self->included_range_differences.contents) {
    _array__delete((Array *)(&self->included_range_differences));
  }
  if (self->old_tree.ptr) {
    ts_subtree_release(&self->tree_pool, self->old_tree);
    self->old_tree = ((Subtree) {.ptr = ((void *)0)});
  }
  ts_wasm_store_delete(self->wasm_store);
  ts_lexer_delete(&self->lexer);
  ts_parser__set_cached_token(self, 0, ((Subtree) {.ptr = ((void *)0)}), ((Subtree) {.ptr = ((void *)0)}));
  ts_subtree_pool_delete(&self->tree_pool);
  reusable_node_delete(&self->reusable_node);
  _array__delete((Array *)(&self->trailing_extras));
  _array__delete((Array *)(&self->trailing_extras2));
  _array__delete((Array *)(&self->scratch_trees));
  ts_current_free(self);
}
const TSLanguage *ts_parser_language(const TSParser *self) {
  return self->language;
}
_Bool ts_parser_set_language(TSParser *self, const TSLanguage *language) {
  ts_parser_reset(self);
  ts_language_delete(self->language);
  self->language = ((void *)0);
  if (language) {
    if (
      language->abi_version > 15 ||
      language->abi_version < 13
    ) return 0;
    if (ts_language_is_wasm(language)) {
      if (
        !self->wasm_store ||
        !ts_wasm_store_start(self->wasm_store, &self->lexer.data, language)
      ) return 0;
    }
  }
  self->language = ts_language_copy(language);
  return 1;
}
TSLogger ts_parser_logger(const TSParser *self) {
  return self->lexer.logger;
}
void ts_parser_set_logger(TSParser *self, TSLogger logger) {
  self->lexer.logger = logger;
}
void ts_parser_print_dot_graphs(TSParser *self, int fd) {
  if (self->dot_graph_file) {
    fclose(self->dot_graph_file);
  }
  if (fd >= 0) {
    self->dot_graph_file = fdopen(fd, "a");
  } else {
    self->dot_graph_file = ((void *)0);
  }
}
const size_t *ts_parser_cancellation_flag(const TSParser *self) {
  return (const size_t *)self->cancellation_flag;
}
void ts_parser_set_cancellation_flag(TSParser *self, const size_t *flag) {
  self->cancellation_flag = (const volatile size_t *)flag;
}
uint64_t ts_parser_timeout_micros(const TSParser *self) {
  return duration_to_micros(self->timeout_duration);
}
void ts_parser_set_timeout_micros(TSParser *self, uint64_t timeout_micros) {
  self->timeout_duration = duration_from_micros(timeout_micros);
}
_Bool ts_parser_set_included_ranges(
  TSParser *self,
  const TSRange *ranges,
  uint32_t count
) {
  return ts_lexer_set_included_ranges(&self->lexer, ranges, count);
}
const TSRange *ts_parser_included_ranges(const TSParser *self, uint32_t *count) {
  return ts_lexer_included_ranges(&self->lexer, count);
}
void ts_parser_reset(TSParser *self) {
  ts_parser__external_scanner_destroy(self);
  if (self->wasm_store) {
    ts_wasm_store_reset(self->wasm_store);
  }
  if (self->old_tree.ptr) {
    ts_subtree_release(&self->tree_pool, self->old_tree);
    self->old_tree = ((Subtree) {.ptr = ((void *)0)});
  }
  reusable_node_clear(&self->reusable_node);
  ts_lexer_reset(&self->lexer, length_zero());
  ts_stack_clear(self->stack);
  ts_parser__set_cached_token(self, 0, ((Subtree) {.ptr = ((void *)0)}), ((Subtree) {.ptr = ((void *)0)}));
  if (self->finished_tree.ptr) {
    ts_subtree_release(&self->tree_pool, self->finished_tree);
    self->finished_tree = ((Subtree) {.ptr = ((void *)0)});
  }
  self->accept_count = 0;
  self->has_scanner_error = 0;
  self->has_error = 0;
  self->canceled_balancing = 0;
  self->parse_options = (TSParseOptions) {0};
  self->parse_state = (TSParseState) {0};
}
TSTree *ts_parser_parse(
  TSParser *self,
  const TSTree *old_tree,
  TSInput input
) {
  TSTree *result = ((void *)0);
  if (!self->language || !input.read) return ((void *)0);
  if (ts_language_is_wasm(self->language)) {
    if (!self->wasm_store) return ((void *)0);
    ts_wasm_store_start(self->wasm_store, &self->lexer.data, self->language);
  }
  ts_lexer_set_input(&self->lexer, input);
  ((&self->included_range_differences)->size = 0);
  self->included_range_difference_index = 0;
  self->operation_count = 0;
  if (self->timeout_duration) {
    self->end_clock = clock_after(clock_now(), self->timeout_duration);
  } else {
    self->end_clock = clock_null();
  }
  if (ts_parser_has_outstanding_parse(self)) {
    if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "resume_parsing"); ts_parser__log(self); };
    if (self->canceled_balancing) goto balance;
  } else {
    ts_parser__external_scanner_create(self);
    if (self->has_scanner_error) goto exit;
    if (old_tree) {
      ts_subtree_retain(old_tree->root);
      self->old_tree = old_tree->root;
      ts_range_array_get_changed_ranges(
        old_tree->included_ranges, old_tree->included_range_count,
        self->lexer.included_ranges, self->lexer.included_range_count,
        &self->included_range_differences
      );
      reusable_node_reset(&self->reusable_node, old_tree->root);
      if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "parse_after_edit"); ts_parser__log(self); };
      if (self->dot_graph_file) { ts_subtree_print_dot_graph(self->old_tree, self->language, self->dot_graph_file); fputs("\n", self->dot_graph_file); };
      for (unsigned i = 0; i < self->included_range_differences.size; i++) {
        TSRange *range = &self->included_range_differences.contents[i];
        if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "different_included_range %u - %u", range->start_byte, range->end_byte); ts_parser__log(self); };
      }
    } else {
      reusable_node_clear(&self->reusable_node);
      if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "new_parse"); ts_parser__log(self); };
    }
  }
  uint32_t position = 0, last_position = 0, version_count = 0;
  do {
    for (
      StackVersion version = 0;
      version_count = ts_stack_version_count(self->stack),
      version < version_count;
      version++
    ) {
      _Bool allow_node_reuse = version_count == 1;
      while (ts_stack_is_active(self->stack, version)) {
        if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "process version:%u, version_count:%u, state:%d, row:%u, col:%u", version, ts_stack_version_count(self->stack), ts_stack_state(self->stack, version), ts_stack_position(self->stack, version).extent.row, ts_stack_position(self->stack, version).extent.column); ts_parser__log(self); };
        if (!ts_parser__advance(self, version, allow_node_reuse)) {
          if (self->has_scanner_error) goto exit;
          return ((void *)0);
        }
        if (self->dot_graph_file) { ts_stack_print_dot_graph(self->stack, self->language, self->dot_graph_file); fputs("\n\n", self->dot_graph_file); };
        position = ts_stack_position(self->stack, version).bytes;
        if (position > last_position || (version > 0 && position == last_position)) {
          last_position = position;
          break;
        }
      }
    }
    unsigned min_error_cost = ts_parser__condense_stack(self);
    if (self->finished_tree.ptr && ts_subtree_error_cost(self->finished_tree) < min_error_cost) {
      ts_stack_clear(self->stack);
      break;
    }
    while (self->included_range_difference_index < self->included_range_differences.size) {
      TSRange *range = &self->included_range_differences.contents[self->included_range_difference_index];
      if (range->end_byte <= position) {
        self->included_range_difference_index++;
      } else {
        break;
      }
    }
  } while (version_count != 0);
balance:
  (__builtin_expect(!(self->finished_tree.ptr), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./parser.c", 2200, "self->finished_tree.ptr") : (void)0);
  if (!ts_parser__balance_subtree(self)) {
    self->canceled_balancing = 1;
    return 0;
  }
  self->canceled_balancing = 0;
  if (self->lexer.logger.log || self->dot_graph_file) { snprintf(self->lexer.debug_buffer, 1024, "done"); ts_parser__log(self); };
  if (self->dot_graph_file) { ts_subtree_print_dot_graph(self->finished_tree, self->language, self->dot_graph_file); fputs("\n", self->dot_graph_file); };
  result = ts_tree_new(
    self->finished_tree,
    self->language,
    self->lexer.included_ranges,
    self->lexer.included_range_count
  );
  self->finished_tree = ((Subtree) {.ptr = ((void *)0)});
exit:
  ts_parser_reset(self);
  return result;
}
TSTree *ts_parser_parse_with_options(
  TSParser *self,
  const TSTree *old_tree,
  TSInput input,
  TSParseOptions parse_options
) {
  self->parse_options = parse_options;
  self->parse_state.payload = parse_options.payload;
  TSTree *result = ts_parser_parse(self, old_tree, input);
  return result;
}
TSTree *ts_parser_parse_string(
  TSParser *self,
  const TSTree *old_tree,
  const char *string,
  uint32_t length
) {
  return ts_parser_parse_string_encoding(self, old_tree, string, length, TSInputEncodingUTF8);
}
TSTree *ts_parser_parse_string_encoding(
  TSParser *self,
  const TSTree *old_tree,
  const char *string,
  uint32_t length,
  TSInputEncoding encoding
) {
  TSStringInput input = {string, length};
  return ts_parser_parse(self, old_tree, (TSInput) {
    &input,
    ts_string_input_read,
    encoding,
    ((void *)0),
  });
}
void ts_parser_set_wasm_store(TSParser *self, TSWasmStore *store) {
  if (self->language && ts_language_is_wasm(self->language)) {
    const TSLanguage *copy = ts_language_copy(self->language);
    ts_parser_set_language(self, copy);
    ts_language_delete(copy);
  }
  ts_wasm_store_delete(self->wasm_store);
  self->wasm_store = store;
}
TSWasmStore *ts_parser_take_wasm_store(TSParser *self) {
  if (self->language && ts_language_is_wasm(self->language)) {
    ts_parser_set_language(self, ((void *)0));
  }
  TSWasmStore *result = self->wasm_store;
  self->wasm_store = ((void *)0);
  return result;
}
typedef	__darwin_wctrans_t wctrans_t;
typedef __darwin_wctype_t wctype_t;
typedef struct {
	__darwin_rune_t	__min;
	__darwin_rune_t	__max;
	__darwin_rune_t	__map;
	__uint32_t	*__types;
} _RuneEntry;
typedef struct {
	int		__nranges;
	_RuneEntry	*__ranges;
} _RuneRange;
typedef struct {
	char		__name[14];
	__uint32_t	__mask;
} _RuneCharClass;
typedef struct {
	char		__magic[8];
	char		__encoding[32];
	__darwin_rune_t	(*__sgetrune)(const char *, __darwin_size_t, char const **);
	int		(*__sputrune)(__darwin_rune_t, char *, __darwin_size_t, char **);
	__darwin_rune_t	__invalid_rune;
	__uint32_t	__runetype[(1 <<8 )];
	__darwin_rune_t	__maplower[(1 <<8 )];
	__darwin_rune_t	__mapupper[(1 <<8 )];
	_RuneRange	__runetype_ext;
	_RuneRange	__maplower_ext;
	_RuneRange	__mapupper_ext;
	void		*__variable;
	int		__variable_len;
	int		__ncharclasses;
	_RuneCharClass	*__charclasses;
} _RuneLocale;
extern _RuneLocale _DefaultRuneLocale;
extern _RuneLocale *_CurrentRuneLocale;
int     isalnum(int);
int     isalpha(int);
int     isblank(int);
int     iscntrl(int);
int     isdigit(int);
int     isgraph(int);
int     islower(int);
int     isprint(int);
int     ispunct(int);
int     isspace(int);
int     isupper(int);
int     isxdigit(int);
int     tolower(int);
int     toupper(int);
int     isascii(int);
int     toascii(int);
int     _tolower(int);
int     _toupper(int);
int     digittoint(int);
int     ishexnumber(int);
int     isideogram(int);
int     isnumber(int);
int     isphonogram(int);
int     isrune(int);
int     isspecial(int);
int	iswalnum(wint_t);
int	iswalpha(wint_t);
int	iswcntrl(wint_t);
int	iswctype(wint_t, wctype_t);
int	iswdigit(wint_t);
int	iswgraph(wint_t);
int	iswlower(wint_t);
int	iswprint(wint_t);
int	iswpunct(wint_t);
int	iswspace(wint_t);
int	iswupper(wint_t);
int	iswxdigit(wint_t);
wint_t	towlower(wint_t);
wint_t	towupper(wint_t);
wctype_t
	wctype(const char *);
int	iswblank(wint_t);
wint_t	iswascii(wint_t);
wint_t	iswhexnumber(wint_t);
wint_t	iswideogram(wint_t);
wint_t	iswnumber(wint_t);
wint_t	iswphonogram(wint_t);
wint_t	iswrune(wint_t);
wint_t	iswspecial(wint_t);
wint_t	nextwctype(wint_t, wctype_t);
wint_t	towctrans(wint_t, wctrans_t);
wctrans_t
	wctrans(const char *);
typedef struct {
  const char *input;
  const char *start;
  const char *end;
  int32_t next;
  uint8_t next_size;
} Stream;
typedef struct {
  TSSymbol symbol;
  TSSymbol supertype_symbol;
  TSFieldId field;
  uint16_t capture_ids[3];
  uint16_t depth;
  uint16_t alternative_index;
  uint16_t negated_field_list_id;
  _Bool is_named: 1;
  _Bool is_immediate: 1;
  _Bool is_last_child: 1;
  _Bool is_pass_through: 1;
  _Bool is_dead_end: 1;
  _Bool alternative_is_immediate: 1;
  _Bool contains_captures: 1;
  _Bool root_pattern_guaranteed: 1;
  _Bool parent_pattern_guaranteed: 1;
  _Bool is_missing: 1;
} QueryStep;
typedef struct {
  uint32_t offset;
  uint32_t length;
} Slice;
typedef struct {
  struct { char *contents; uint32_t size; uint32_t capacity; } characters;
  struct { Slice *contents; uint32_t size; uint32_t capacity; } slices;
} SymbolTable;
typedef struct { uint8_t *contents; uint32_t size; uint32_t capacity; } CaptureQuantifiers;
typedef struct {
  uint16_t step_index;
  uint16_t pattern_index;
  _Bool is_rooted;
} PatternEntry;
typedef struct {
  Slice steps;
  Slice predicate_steps;
  uint32_t start_byte;
  uint32_t end_byte;
  _Bool is_non_local;
} QueryPattern;
typedef struct {
  uint32_t byte_offset;
  uint16_t step_index;
} StepOffset;
typedef struct {
  uint32_t id;
  uint32_t capture_list_id;
  uint16_t start_depth;
  uint16_t step_index;
  uint16_t pattern_index;
  uint16_t consumed_capture_count: 12;
  _Bool seeking_immediate_match: 1;
  _Bool has_in_progress_alternatives: 1;
  _Bool dead: 1;
  _Bool needs_parent: 1;
} QueryState;
typedef struct { TSQueryCapture *contents; uint32_t size; uint32_t capacity; } CaptureList;
typedef struct {
  struct { CaptureList *contents; uint32_t size; uint32_t capacity; } list;
  CaptureList empty_list;
  uint32_t max_capture_list_count;
  uint32_t free_capture_list_count;
} CaptureListPool;
typedef struct {
  TSStateId parse_state;
  TSSymbol parent_symbol;
  uint16_t child_index;
  TSFieldId field_id: 15;
  _Bool done: 1;
} AnalysisStateEntry;
typedef struct {
  AnalysisStateEntry stack[8];
  uint16_t depth;
  uint16_t step_index;
  TSSymbol root_symbol;
} AnalysisState;
typedef struct { AnalysisState * *contents; uint32_t size; uint32_t capacity; } AnalysisStateSet;
typedef struct {
  AnalysisStateSet states;
  AnalysisStateSet next_states;
  AnalysisStateSet deeper_states;
  AnalysisStateSet state_pool;
  struct { uint16_t *contents; uint32_t size; uint32_t capacity; } final_step_indices;
  struct { TSSymbol *contents; uint32_t size; uint32_t capacity; } finished_parent_symbols;
  _Bool did_abort;
} QueryAnalysis;
typedef struct {
  TSStateId state;
  uint16_t production_id;
  uint8_t child_index: 7;
  _Bool done: 1;
} AnalysisSubgraphNode;
typedef struct {
  TSSymbol symbol;
  struct { TSStateId *contents; uint32_t size; uint32_t capacity; } start_states;
  struct { AnalysisSubgraphNode *contents; uint32_t size; uint32_t capacity; } nodes;
} AnalysisSubgraph;
typedef struct { AnalysisSubgraph *contents; uint32_t size; uint32_t capacity; } AnalysisSubgraphArray;
typedef struct {
  TSStateId *contents;
} StatePredecessorMap;
struct TSQuery {
  SymbolTable captures;
  SymbolTable predicate_values;
  struct { CaptureQuantifiers *contents; uint32_t size; uint32_t capacity; } capture_quantifiers;
  struct { QueryStep *contents; uint32_t size; uint32_t capacity; } steps;
  struct { PatternEntry *contents; uint32_t size; uint32_t capacity; } pattern_map;
  struct { TSQueryPredicateStep *contents; uint32_t size; uint32_t capacity; } predicate_steps;
  struct { QueryPattern *contents; uint32_t size; uint32_t capacity; } patterns;
  struct { StepOffset *contents; uint32_t size; uint32_t capacity; } step_offsets;
  struct { TSFieldId *contents; uint32_t size; uint32_t capacity; } negated_fields;
  struct { char *contents; uint32_t size; uint32_t capacity; } string_buffer;
  struct { TSSymbol *contents; uint32_t size; uint32_t capacity; } repeat_symbols_with_rootless_patterns;
  const TSLanguage *language;
  uint16_t wildcard_root_pattern_count;
};
struct TSQueryCursor {
  const TSQuery *query;
  TSTreeCursor cursor;
  struct { QueryState *contents; uint32_t size; uint32_t capacity; } states;
  struct { QueryState *contents; uint32_t size; uint32_t capacity; } finished_states;
  CaptureListPool capture_list_pool;
  uint32_t depth;
  uint32_t max_start_depth;
  uint32_t start_byte;
  uint32_t end_byte;
  TSPoint start_point;
  TSPoint end_point;
  uint32_t next_state_id;
  TSClock end_clock;
  TSDuration timeout_duration;
  const TSQueryCursorOptions *query_options;
  TSQueryCursorState query_state;
  unsigned operation_count;
  _Bool on_visible_node;
  _Bool ascending;
  _Bool halted;
  _Bool did_exceed_match_limit;
};
static const TSQueryError PARENT_DONE = -1;
static const uint16_t PATTERN_DONE_MARKER = 65535;
static const uint16_t NONE = 65535;
static const TSSymbol WILDCARD_SYMBOL = 0;
static const unsigned OP_COUNT_PER_QUERY_TIMEOUT_CHECK = 100;
static _Bool stream_advance(Stream *self) {
  self->input += self->next_size;
  if (self->input < self->end) {
    uint32_t size = ts_decode_utf8(
      (const uint8_t *)self->input,
      (uint32_t)(self->end - self->input),
      &self->next
    );
    if (size > 0) {
      self->next_size = size;
      return 1;
    }
  } else {
    self->next_size = 0;
    self->next = '\0';
  }
  return 0;
}
static void stream_reset(Stream *self, const char *input) {
  self->input = input;
  self->next_size = 0;
  stream_advance(self);
}
static Stream stream_new(const char *string, uint32_t length) {
  Stream self = {
    .next = 0,
    .input = string,
    .start = string,
    .end = string + length,
  };
  stream_advance(&self);
  return self;
}
static void stream_skip_whitespace(Stream *self) {
  for (;;) {
    if (iswspace(self->next)) {
      stream_advance(self);
    } else if (self->next == ';') {
      stream_advance(self);
      while (self->next && self->next != '\n') {
        if (!stream_advance(self)) break;
      }
    } else {
      break;
    }
  }
}
static _Bool stream_is_ident_start(Stream *self) {
  return iswalnum(self->next) || self->next == '_' || self->next == '-';
}
static void stream_scan_identifier(Stream *stream) {
  do {
    stream_advance(stream);
  } while (
    iswalnum(stream->next) ||
    stream->next == '_' ||
    stream->next == '-' ||
    stream->next == '.' ||
    stream->next == '?' ||
    stream->next == '!'
  );
}
static uint32_t stream_offset(Stream *self) {
  return (uint32_t)(self->input - self->start);
}
static CaptureListPool capture_list_pool_new(void) {
  return (CaptureListPool) {
    .list = { ((void *)0), 0, 0 },
    .empty_list = { ((void *)0), 0, 0 },
    .max_capture_list_count = 4294967295U,
    .free_capture_list_count = 0,
  };
}
static void capture_list_pool_reset(CaptureListPool *self) {
  for (uint16_t i = 0; i < (uint16_t)self->list.size; i++) {
    self->list.contents[i].size = 4294967295U;
  }
  self->free_capture_list_count = self->list.size;
}
static void capture_list_pool_delete(CaptureListPool *self) {
  for (uint16_t i = 0; i < (uint16_t)self->list.size; i++) {
    _array__delete((Array *)(&self->list.contents[i]));
  }
  _array__delete((Array *)(&self->list));
}
static const CaptureList *capture_list_pool_get(const CaptureListPool *self, uint16_t id) {
  if (id >= self->list.size) return &self->empty_list;
  return &self->list.contents[id];
}
static CaptureList *capture_list_pool_get_mut(CaptureListPool *self, uint16_t id) {
  (__builtin_expect(!(id < self->list.size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 458, "id < self->list.size") : (void)0);
  return &self->list.contents[id];
}
static _Bool capture_list_pool_is_empty(const CaptureListPool *self) {
  return self->free_capture_list_count == 0 && self->list.size >= self->max_capture_list_count;
}
static uint16_t capture_list_pool_acquire(CaptureListPool *self) {
  if (self->free_capture_list_count > 0) {
    for (uint16_t i = 0; i < (uint16_t)self->list.size; i++) {
      if (self->list.contents[i].size == 4294967295U) {
        ((&self->list.contents[i])->size = 0);
        self->free_capture_list_count--;
        return i;
      }
    }
  }
  uint32_t i = self->list.size;
  if (i >= self->max_capture_list_count) {
    return NONE;
  }
  CaptureList list;
  ((&list)->size = 0, (&list)->capacity = 0, (&list)->contents = ((void *)0));
  (_array__grow((Array *)(&self->list), 1, (sizeof *(&self->list)->contents)), (&self->list)->contents[(&self->list)->size++] = (list));
  return i;
}
static void capture_list_pool_release(CaptureListPool *self, uint16_t id) {
  if (id >= self->list.size) return;
  self->list.contents[id].size = 4294967295U;
  self->free_capture_list_count++;
}
static TSQuantifier quantifier_mul(
  TSQuantifier left,
  TSQuantifier right
) {
  switch (left)
  {
    case TSQuantifierZero:
      return TSQuantifierZero;
    case TSQuantifierZeroOrOne:
      switch (right) {
        case TSQuantifierZero:
          return TSQuantifierZero;
        case TSQuantifierZeroOrOne:
        case TSQuantifierOne:
          return TSQuantifierZeroOrOne;
        case TSQuantifierZeroOrMore:
        case TSQuantifierOneOrMore:
          return TSQuantifierZeroOrMore;
      };
      break;
    case TSQuantifierZeroOrMore:
      switch (right) {
        case TSQuantifierZero:
          return TSQuantifierZero;
        case TSQuantifierZeroOrOne:
        case TSQuantifierZeroOrMore:
        case TSQuantifierOne:
        case TSQuantifierOneOrMore:
          return TSQuantifierZeroOrMore;
      };
      break;
    case TSQuantifierOne:
      return right;
    case TSQuantifierOneOrMore:
      switch (right) {
        case TSQuantifierZero:
          return TSQuantifierZero;
        case TSQuantifierZeroOrOne:
        case TSQuantifierZeroOrMore:
          return TSQuantifierZeroOrMore;
        case TSQuantifierOne:
        case TSQuantifierOneOrMore:
          return TSQuantifierOneOrMore;
      };
      break;
  }
  return TSQuantifierZero;
}
static TSQuantifier quantifier_join(
  TSQuantifier left,
  TSQuantifier right
) {
  switch (left)
  {
    case TSQuantifierZero:
      switch (right) {
        case TSQuantifierZero:
          return TSQuantifierZero;
        case TSQuantifierZeroOrOne:
        case TSQuantifierOne:
          return TSQuantifierZeroOrOne;
        case TSQuantifierZeroOrMore:
        case TSQuantifierOneOrMore:
          return TSQuantifierZeroOrMore;
      };
      break;
    case TSQuantifierZeroOrOne:
      switch (right) {
        case TSQuantifierZero:
        case TSQuantifierZeroOrOne:
        case TSQuantifierOne:
          return TSQuantifierZeroOrOne;
          break;
        case TSQuantifierZeroOrMore:
        case TSQuantifierOneOrMore:
          return TSQuantifierZeroOrMore;
          break;
      };
      break;
    case TSQuantifierZeroOrMore:
      return TSQuantifierZeroOrMore;
    case TSQuantifierOne:
      switch (right) {
        case TSQuantifierZero:
        case TSQuantifierZeroOrOne:
          return TSQuantifierZeroOrOne;
        case TSQuantifierZeroOrMore:
          return TSQuantifierZeroOrMore;
        case TSQuantifierOne:
          return TSQuantifierOne;
        case TSQuantifierOneOrMore:
          return TSQuantifierOneOrMore;
      };
      break;
    case TSQuantifierOneOrMore:
      switch (right) {
        case TSQuantifierZero:
        case TSQuantifierZeroOrOne:
        case TSQuantifierZeroOrMore:
          return TSQuantifierZeroOrMore;
        case TSQuantifierOne:
        case TSQuantifierOneOrMore:
          return TSQuantifierOneOrMore;
      };
      break;
  }
  return TSQuantifierZero;
}
static TSQuantifier quantifier_add(
  TSQuantifier left,
  TSQuantifier right
) {
  switch (left)
  {
    case TSQuantifierZero:
      return right;
    case TSQuantifierZeroOrOne:
      switch (right) {
        case TSQuantifierZero:
          return TSQuantifierZeroOrOne;
        case TSQuantifierZeroOrOne:
        case TSQuantifierZeroOrMore:
          return TSQuantifierZeroOrMore;
        case TSQuantifierOne:
        case TSQuantifierOneOrMore:
          return TSQuantifierOneOrMore;
      };
      break;
    case TSQuantifierZeroOrMore:
      switch (right) {
        case TSQuantifierZero:
          return TSQuantifierZeroOrMore;
        case TSQuantifierZeroOrOne:
        case TSQuantifierZeroOrMore:
          return TSQuantifierZeroOrMore;
        case TSQuantifierOne:
        case TSQuantifierOneOrMore:
          return TSQuantifierOneOrMore;
      };
      break;
    case TSQuantifierOne:
      switch (right) {
        case TSQuantifierZero:
          return TSQuantifierOne;
        case TSQuantifierZeroOrOne:
        case TSQuantifierZeroOrMore:
        case TSQuantifierOne:
        case TSQuantifierOneOrMore:
          return TSQuantifierOneOrMore;
      };
      break;
    case TSQuantifierOneOrMore:
      return TSQuantifierOneOrMore;
  }
  return TSQuantifierZero;
}
static CaptureQuantifiers capture_quantifiers_new(void) {
  return (CaptureQuantifiers) { ((void *)0), 0, 0 };
}
static void capture_quantifiers_delete(
  CaptureQuantifiers *self
) {
  _array__delete((Array *)(self));
}
static void capture_quantifiers_clear(
  CaptureQuantifiers *self
) {
  ((self)->size = 0);
}
static void capture_quantifiers_replace(
  CaptureQuantifiers *self,
  CaptureQuantifiers *quantifiers
) {
  ((self)->size = 0);
  _array__splice( (Array *)((self)), (sizeof *((self))->contents), ((self))->size, 0, (quantifiers)->size, (quantifiers)->contents );
}
static TSQuantifier capture_quantifier_for_id(
  const CaptureQuantifiers *self,
  uint16_t id
) {
  return (self->size <= id) ? TSQuantifierZero : (TSQuantifier) *((__builtin_expect(!((uint32_t)(id) < (self)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 694, "(uint32_t)(id) < (self)->size") : (void)0), &(self)->contents[id]);
}
static void capture_quantifiers_add_for_id(
  CaptureQuantifiers *self,
  uint16_t id,
  TSQuantifier quantifier
) {
  if (self->size <= id) {
    do { if ((id + 1 - self->size) == 0) break; _array__grow((Array *)(self), id + 1 - self->size, (sizeof *(self)->contents)); memset((self)->contents + (self)->size, 0, (id + 1 - self->size) * (sizeof *(self)->contents)); (self)->size += (id + 1 - self->size); } while (0);
  }
  uint8_t *own_quantifier = ((__builtin_expect(!((uint32_t)(id) < (self)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 706, "(uint32_t)(id) < (self)->size") : (void)0), &(self)->contents[id]);
  *own_quantifier = (uint8_t) quantifier_add((TSQuantifier) *own_quantifier, quantifier);
}
static void capture_quantifiers_add_all(
  CaptureQuantifiers *self,
  CaptureQuantifiers *quantifiers
) {
  if (self->size < quantifiers->size) {
    do { if ((quantifiers->size - self->size) == 0) break; _array__grow((Array *)(self), quantifiers->size - self->size, (sizeof *(self)->contents)); memset((self)->contents + (self)->size, 0, (quantifiers->size - self->size) * (sizeof *(self)->contents)); (self)->size += (quantifiers->size - self->size); } while (0);
  }
  for (uint16_t id = 0; id < (uint16_t)quantifiers->size; id++) {
    uint8_t *quantifier = ((__builtin_expect(!((uint32_t)(id) < (quantifiers)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 719, "(uint32_t)(id) < (quantifiers)->size") : (void)0), &(quantifiers)->contents[id]);
    uint8_t *own_quantifier = ((__builtin_expect(!((uint32_t)(id) < (self)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 720, "(uint32_t)(id) < (self)->size") : (void)0), &(self)->contents[id]);
    *own_quantifier = (uint8_t) quantifier_add((TSQuantifier) *own_quantifier, (TSQuantifier) *quantifier);
  }
}
static void capture_quantifiers_mul(
  CaptureQuantifiers *self,
  TSQuantifier quantifier
) {
  for (uint16_t id = 0; id < (uint16_t)self->size; id++) {
    uint8_t *own_quantifier = ((__builtin_expect(!((uint32_t)(id) < (self)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 731, "(uint32_t)(id) < (self)->size") : (void)0), &(self)->contents[id]);
    *own_quantifier = (uint8_t) quantifier_mul((TSQuantifier) *own_quantifier, quantifier);
  }
}
static void capture_quantifiers_join_all(
  CaptureQuantifiers *self,
  CaptureQuantifiers *quantifiers
) {
  if (self->size < quantifiers->size) {
    do { if ((quantifiers->size - self->size) == 0) break; _array__grow((Array *)(self), quantifiers->size - self->size, (sizeof *(self)->contents)); memset((self)->contents + (self)->size, 0, (quantifiers->size - self->size) * (sizeof *(self)->contents)); (self)->size += (quantifiers->size - self->size); } while (0);
  }
  for (uint32_t id = 0; id < quantifiers->size; id++) {
    uint8_t *quantifier = ((__builtin_expect(!((uint32_t)(id) < (quantifiers)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 745, "(uint32_t)(id) < (quantifiers)->size") : (void)0), &(quantifiers)->contents[id]);
    uint8_t *own_quantifier = ((__builtin_expect(!((uint32_t)(id) < (self)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 746, "(uint32_t)(id) < (self)->size") : (void)0), &(self)->contents[id]);
    *own_quantifier = (uint8_t) quantifier_join((TSQuantifier) *own_quantifier, (TSQuantifier) *quantifier);
  }
  for (uint32_t id = quantifiers->size; id < self->size; id++) {
    uint8_t *own_quantifier = ((__builtin_expect(!((uint32_t)(id) < (self)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 750, "(uint32_t)(id) < (self)->size") : (void)0), &(self)->contents[id]);
    *own_quantifier = (uint8_t) quantifier_join((TSQuantifier) *own_quantifier, TSQuantifierZero);
  }
}
static SymbolTable symbol_table_new(void) {
  return (SymbolTable) {
    .characters = { ((void *)0), 0, 0 },
    .slices = { ((void *)0), 0, 0 },
  };
}
static void symbol_table_delete(SymbolTable *self) {
  _array__delete((Array *)(&self->characters));
  _array__delete((Array *)(&self->slices));
}
static int symbol_table_id_for_name(
  const SymbolTable *self,
  const char *name,
  uint32_t length
) {
  for (unsigned i = 0; i < self->slices.size; i++) {
    Slice slice = self->slices.contents[i];
    if (
      slice.length == length &&
      !strncmp(&self->characters.contents[slice.offset], name, length)
    ) return i;
  }
  return -1;
}
static const char *symbol_table_name_for_id(
  const SymbolTable *self,
  uint16_t id,
  uint32_t *length
) {
  Slice slice = self->slices.contents[id];
  *length = slice.length;
  return &self->characters.contents[slice.offset];
}
static uint16_t symbol_table_insert_name(
  SymbolTable *self,
  const char *name,
  uint32_t length
) {
  int id = symbol_table_id_for_name(self, name, length);
  if (id >= 0) return (uint16_t)id;
  Slice slice = {
    .offset = self->characters.size,
    .length = length,
  };
  do { if ((length + 1) == 0) break; _array__grow((Array *)(&self->characters), length + 1, (sizeof *(&self->characters)->contents)); memset((&self->characters)->contents + (&self->characters)->size, 0, (length + 1) * (sizeof *(&self->characters)->contents)); (&self->characters)->size += (length + 1); } while (0);
  memcpy(&self->characters.contents[slice.offset], name, length);
  self->characters.contents[self->characters.size - 1] = 0;
  (_array__grow((Array *)(&self->slices), 1, (sizeof *(&self->slices)->contents)), (&self->slices)->contents[(&self->slices)->size++] = (slice));
  return self->slices.size - 1;
}
static QueryStep query_step__new(
  TSSymbol symbol,
  uint16_t depth,
  _Bool is_immediate
) {
  QueryStep step = {
    .symbol = symbol,
    .depth = depth,
    .field = 0,
    .alternative_index = NONE,
    .negated_field_list_id = 0,
    .contains_captures = 0,
    .is_last_child = 0,
    .is_named = 0,
    .is_pass_through = 0,
    .is_dead_end = 0,
    .root_pattern_guaranteed = 0,
    .is_immediate = is_immediate,
    .alternative_is_immediate = 0,
  };
  for (unsigned i = 0; i < 3; i++) {
    step.capture_ids[i] = NONE;
  }
  return step;
}
static void query_step__add_capture(QueryStep *self, uint16_t capture_id) {
  for (unsigned i = 0; i < 3; i++) {
    if (self->capture_ids[i] == NONE) {
      self->capture_ids[i] = capture_id;
      break;
    }
  }
}
static void query_step__remove_capture(QueryStep *self, uint16_t capture_id) {
  for (unsigned i = 0; i < 3; i++) {
    if (self->capture_ids[i] == capture_id) {
      self->capture_ids[i] = NONE;
      while (i + 1 < 3) {
        if (self->capture_ids[i + 1] == NONE) break;
        self->capture_ids[i] = self->capture_ids[i + 1];
        self->capture_ids[i + 1] = NONE;
        i++;
      }
      break;
    }
  }
}
static inline StatePredecessorMap state_predecessor_map_new(
  const TSLanguage *language
) {
  return (StatePredecessorMap) {
    .contents = ts_current_calloc(
      (size_t)language->state_count * (256 + 1),
      sizeof(TSStateId)
    ),
  };
}
static inline void state_predecessor_map_delete(StatePredecessorMap *self) {
  ts_current_free(self->contents);
}
static inline void state_predecessor_map_add(
  StatePredecessorMap *self,
  TSStateId state,
  TSStateId predecessor
) {
  size_t index = (size_t)state * (256 + 1);
  TSStateId *count = &self->contents[index];
  if (
    *count == 0 ||
    (*count < 256 && self->contents[index + *count] != predecessor)
  ) {
    (*count)++;
    self->contents[index + *count] = predecessor;
  }
}
static inline const TSStateId *state_predecessor_map_get(
  const StatePredecessorMap *self,
  TSStateId state,
  unsigned *count
) {
  size_t index = (size_t)state * (256 + 1);
  *count = self->contents[index];
  return &self->contents[index + 1];
}
static unsigned analysis_state__recursion_depth(const AnalysisState *self) {
  unsigned result = 0;
  for (unsigned i = 0; i < self->depth; i++) {
    TSSymbol symbol = self->stack[i].parent_symbol;
    for (unsigned j = 0; j < i; j++) {
      if (self->stack[j].parent_symbol == symbol) {
        result++;
        break;
      }
    }
  }
  return result;
}
static inline int analysis_state__compare_position(
  AnalysisState *const *self,
  AnalysisState *const *other
) {
  for (unsigned i = 0; i < (*self)->depth; i++) {
    if (i >= (*other)->depth) return -1;
    if ((*self)->stack[i].child_index < (*other)->stack[i].child_index) return -1;
    if ((*self)->stack[i].child_index > (*other)->stack[i].child_index) return 1;
  }
  if ((*self)->depth < (*other)->depth) return 1;
  if ((*self)->step_index < (*other)->step_index) return -1;
  if ((*self)->step_index > (*other)->step_index) return 1;
  return 0;
}
static inline int analysis_state__compare(
  AnalysisState *const *self,
  AnalysisState *const *other
) {
  int result = analysis_state__compare_position(self, other);
  if (result != 0) return result;
  for (unsigned i = 0; i < (*self)->depth; i++) {
    if ((*self)->stack[i].parent_symbol < (*other)->stack[i].parent_symbol) return -1;
    if ((*self)->stack[i].parent_symbol > (*other)->stack[i].parent_symbol) return 1;
    if ((*self)->stack[i].parse_state < (*other)->stack[i].parse_state) return -1;
    if ((*self)->stack[i].parse_state > (*other)->stack[i].parse_state) return 1;
    if ((*self)->stack[i].field_id < (*other)->stack[i].field_id) return -1;
    if ((*self)->stack[i].field_id > (*other)->stack[i].field_id) return 1;
  }
  return 0;
}
static inline AnalysisStateEntry *analysis_state__top(AnalysisState *self) {
  if (self->depth == 0) {
    return &self->stack[0];
  }
  return &self->stack[self->depth - 1];
}
static inline _Bool analysis_state__has_supertype(AnalysisState *self, TSSymbol symbol) {
  for (unsigned i = 0; i < self->depth; i++) {
    if (self->stack[i].parent_symbol == symbol) return 1;
  }
  return 0;
}
static inline AnalysisState *analysis_state_pool__clone_or_reuse(
  AnalysisStateSet *self,
  AnalysisState *borrowed_item
) {
  AnalysisState *new_item;
  if (self->size) {
    new_item = ((self)->contents[--(self)->size]);
  } else {
    new_item = ts_current_malloc(sizeof(AnalysisState));
  }
  *new_item = *borrowed_item;
  return new_item;
}
static inline void analysis_state_set__insert_sorted(
  AnalysisStateSet *self,
  AnalysisStateSet *pool,
  AnalysisState *borrowed_item
) {
  unsigned index, exists;
  do { *(&index) = 0; *(&exists) = 0; uint32_t size = (self)->size - *(&index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&index) + half_size; comparison = analysis_state__compare(&((self)->contents[mid_index] ), (&borrowed_item)); if (comparison <= 0) *(&index) = mid_index; size -= half_size; } comparison = analysis_state__compare(&((self)->contents[*(&index)] ), (&borrowed_item)); if (comparison == 0) *(&exists) = 1; else if (comparison < 0) *(&index) += 1; } while (0);
  if (!exists) {
    AnalysisState *new_item = analysis_state_pool__clone_or_reuse(pool, borrowed_item);
    _array__splice((Array *)(self), (sizeof *(self)->contents), index, 0, 1, &(new_item));
  }
}
static inline void analysis_state_set__push(
  AnalysisStateSet *self,
  AnalysisStateSet *pool,
  AnalysisState *borrowed_item
) {
  AnalysisState *new_item = analysis_state_pool__clone_or_reuse(pool, borrowed_item);
  (_array__grow((Array *)(self), 1, (sizeof *(self)->contents)), (self)->contents[(self)->size++] = (new_item));
}
static inline void analysis_state_set__clear(AnalysisStateSet *self, AnalysisStateSet *pool) {
  _array__splice( (Array *)((pool)), (sizeof *((pool))->contents), ((pool))->size, 0, (self)->size, (self)->contents );
  ((self)->size = 0);
}
static inline void analysis_state_set__delete(AnalysisStateSet *self) {
  for (unsigned i = 0; i < self->size; i++) {
    ts_current_free(self->contents[i]);
  }
  _array__delete((Array *)(self));
}
static inline QueryAnalysis query_analysis__new(void) {
  return (QueryAnalysis) {
    .states = { ((void *)0), 0, 0 },
    .next_states = { ((void *)0), 0, 0 },
    .deeper_states = { ((void *)0), 0, 0 },
    .state_pool = { ((void *)0), 0, 0 },
    .final_step_indices = { ((void *)0), 0, 0 },
    .finished_parent_symbols = { ((void *)0), 0, 0 },
    .did_abort = 0,
  };
}
static inline void query_analysis__delete(QueryAnalysis *self) {
  analysis_state_set__delete(&self->states);
  analysis_state_set__delete(&self->next_states);
  analysis_state_set__delete(&self->deeper_states);
  analysis_state_set__delete(&self->state_pool);
  _array__delete((Array *)(&self->final_step_indices));
  _array__delete((Array *)(&self->finished_parent_symbols));
}
static inline int analysis_subgraph_node__compare(const AnalysisSubgraphNode *self, const AnalysisSubgraphNode *other) {
  if (self->state < other->state) return -1;
  if (self->state > other->state) return 1;
  if (self->child_index < other->child_index) return -1;
  if (self->child_index > other->child_index) return 1;
  if (self->done < other->done) return -1;
  if (self->done > other->done) return 1;
  if (self->production_id < other->production_id) return -1;
  if (self->production_id > other->production_id) return 1;
  return 0;
}
static inline _Bool ts_query__pattern_map_search(
  const TSQuery *self,
  TSSymbol needle,
  uint32_t *result
) {
  uint32_t base_index = self->wildcard_root_pattern_count;
  uint32_t size = self->pattern_map.size - base_index;
  if (size == 0) {
    *result = base_index;
    return 0;
  }
  while (size > 1) {
    uint32_t half_size = size / 2;
    uint32_t mid_index = base_index + half_size;
    TSSymbol mid_symbol = self->steps.contents[
      self->pattern_map.contents[mid_index].step_index
    ].symbol;
    if (needle > mid_symbol) base_index = mid_index;
    size -= half_size;
  }
  TSSymbol symbol = self->steps.contents[
    self->pattern_map.contents[base_index].step_index
  ].symbol;
  if (needle > symbol) {
    base_index++;
    if (base_index < self->pattern_map.size) {
      symbol = self->steps.contents[
        self->pattern_map.contents[base_index].step_index
      ].symbol;
    }
  }
  *result = base_index;
  return needle == symbol;
}
static inline void ts_query__pattern_map_insert(
  TSQuery *self,
  TSSymbol symbol,
  PatternEntry new_entry
) {
  uint32_t index;
  ts_query__pattern_map_search(self, symbol, &index);
  while (index < self->pattern_map.size) {
    PatternEntry *entry = &self->pattern_map.contents[index];
    if (
      self->steps.contents[entry->step_index].symbol == symbol &&
      entry->pattern_index < new_entry.pattern_index
    ) {
      index++;
    } else {
      break;
    }
  }
  _array__splice((Array *)(&self->pattern_map), (sizeof *(&self->pattern_map)->contents), index, 0, 1, &(new_entry));
}
static void ts_query__perform_analysis(
  TSQuery *self,
  const AnalysisSubgraphArray *subgraphs,
  QueryAnalysis *analysis
) {
  unsigned recursion_depth_limit = 0;
  unsigned prev_final_step_count = 0;
  ((&analysis->final_step_indices)->size = 0);
  ((&analysis->finished_parent_symbols)->size = 0);
  for (unsigned iteration = 0;; iteration++) {
    if (iteration == 256) {
      analysis->did_abort = 1;
      break;
    }
    if (analysis->states.size == 0) {
      if (
        analysis->deeper_states.size > 0 &&
        analysis->final_step_indices.size > prev_final_step_count
      ) {
        prev_final_step_count = analysis->final_step_indices.size;
        recursion_depth_limit++;
        AnalysisStateSet _states = analysis->states;
        analysis->states = analysis->deeper_states;
        analysis->deeper_states = _states;
        continue;
      }
      break;
    }
    analysis_state_set__clear(&analysis->next_states, &analysis->state_pool);
    for (unsigned j = 0; j < analysis->states.size; j++) {
      AnalysisState * const state = analysis->states.contents[j];
      if (analysis->next_states.size > 0) {
        int comparison = analysis_state__compare_position(
          &state,
          ((__builtin_expect(!((uint32_t)((&analysis->next_states)->size - 1) < (&analysis->next_states)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 1252, "(uint32_t)((&analysis->next_states)->size - 1) < (&analysis->next_states)->size") : (void)0), &(&analysis->next_states)->contents[(&analysis->next_states)->size - 1])
        );
        if (comparison == 0) {
          analysis_state_set__insert_sorted(&analysis->next_states, &analysis->state_pool, state);
          continue;
        } else if (comparison > 0) {
          while (j < analysis->states.size) {
            analysis_state_set__push(
              &analysis->next_states,
              &analysis->state_pool,
              analysis->states.contents[j]
            );
            j++;
          }
          break;
        }
      }
      const TSStateId parse_state = analysis_state__top(state)->parse_state;
      const TSSymbol parent_symbol = analysis_state__top(state)->parent_symbol;
      const TSFieldId parent_field_id = analysis_state__top(state)->field_id;
      const unsigned child_index = analysis_state__top(state)->child_index;
      const QueryStep * const step = &self->steps.contents[state->step_index];
      unsigned subgraph_index, exists;
      do { *(&subgraph_index) = 0; *(&exists) = 0; uint32_t size = (subgraphs)->size - *(&subgraph_index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&subgraph_index) + half_size; comparison = ((int)*(&((subgraphs)->contents[mid_index] .symbol)) - (int)((parent_symbol))); if (comparison <= 0) *(&subgraph_index) = mid_index; size -= half_size; } comparison = ((int)*(&((subgraphs)->contents[*(&subgraph_index)] .symbol)) - (int)((parent_symbol))); if (comparison == 0) *(&exists) = 1; else if (comparison < 0) *(&subgraph_index) += 1; } while (0);
      if (!exists) continue;
      const AnalysisSubgraph *subgraph = &subgraphs->contents[subgraph_index];
      LookaheadIterator lookahead_iterator = ts_language_lookaheads(self->language, parse_state);
      while (ts_lookahead_iterator__next(&lookahead_iterator)) {
        TSSymbol sym = lookahead_iterator.symbol;
        AnalysisSubgraphNode successor = {
          .state = parse_state,
          .child_index = child_index,
        };
        if (lookahead_iterator.action_count) {
          const TSParseAction *action = &lookahead_iterator.actions[lookahead_iterator.action_count - 1];
          if (action->type == TSParseActionTypeShift) {
            if (!action->shift.extra) {
              successor.state = action->shift.state;
              successor.child_index++;
            }
          } else {
            continue;
          }
        } else if (lookahead_iterator.next_state != 0) {
          successor.state = lookahead_iterator.next_state;
          successor.child_index++;
        } else {
          continue;
        }
        unsigned node_index;
        do { *(&node_index) = 0; *(&exists) = 0; uint32_t size = (&subgraph->nodes)->size - *(&node_index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&node_index) + half_size; comparison = analysis_subgraph_node__compare(&((&subgraph->nodes)->contents[mid_index] ), (&successor)); if (comparison <= 0) *(&node_index) = mid_index; size -= half_size; } comparison = analysis_subgraph_node__compare(&((&subgraph->nodes)->contents[*(&node_index)] ), (&successor)); if (comparison == 0) *(&exists) = 1; else if (comparison < 0) *(&node_index) += 1; } while (0);
        while (node_index < subgraph->nodes.size) {
          AnalysisSubgraphNode *node = &subgraph->nodes.contents[node_index++];
          if (node->state != successor.state || node->child_index != successor.child_index) break;
          TSSymbol alias = ts_language_alias_at(self->language, node->production_id, child_index);
          TSSymbol visible_symbol = alias
            ? alias
            : self->language->symbol_metadata[sym].visible
              ? self->language->public_symbol_map[sym]
              : 0;
          TSFieldId field_id = parent_field_id;
          if (!field_id) {
            const TSFieldMapEntry *field_map, *field_map_end;
            ts_language_field_map(self->language, node->production_id, &field_map, &field_map_end);
            for (; field_map != field_map_end; field_map++) {
              if (!field_map->inherited && field_map->child_index == child_index) {
                field_id = field_map->field_id;
                break;
              }
            }
          }
          AnalysisState next_state = *state;
          AnalysisStateEntry *next_state_top = analysis_state__top(&next_state);
          next_state_top->child_index = successor.child_index;
          next_state_top->parse_state = successor.state;
          if (node->done) next_state_top->done = 1;
          _Bool does_match = 0;
          if (visible_symbol) {
            does_match = 1;
            if (step->symbol == WILDCARD_SYMBOL) {
              if (
                step->is_named &&
                !self->language->symbol_metadata[visible_symbol].named
              ) does_match = 0;
            } else if (step->symbol != visible_symbol) {
              does_match = 0;
            }
            if (step->field && step->field != field_id) {
              does_match = 0;
            }
            if (
              step->supertype_symbol &&
              !analysis_state__has_supertype(state, step->supertype_symbol)
            ) does_match = 0;
          }
          else if (sym >= self->language->token_count) {
            if (!next_state_top->done) {
              if (next_state.depth + 1 >= 8) {
                analysis->did_abort = 1;
                continue;
              }
              next_state.depth++;
              next_state_top = analysis_state__top(&next_state);
            }
            *next_state_top = (AnalysisStateEntry) {
              .parse_state = parse_state,
              .parent_symbol = sym,
              .child_index = 0,
              .field_id = field_id,
              .done = 0,
            };
            if (analysis_state__recursion_depth(&next_state) > recursion_depth_limit) {
              analysis_state_set__insert_sorted(
                &analysis->deeper_states,
                &analysis->state_pool,
                &next_state
              );
              continue;
            }
          }
          while (next_state.depth > 0 && next_state_top->done) {
            next_state.depth--;
            next_state_top = analysis_state__top(&next_state);
          }
          const QueryStep *next_step = step;
          if (does_match) {
            for (;;) {
              next_state.step_index++;
              next_step = &self->steps.contents[next_state.step_index];
              if (
                next_step->depth == PATTERN_DONE_MARKER ||
                next_step->depth <= step->depth
              ) break;
            }
          } else if (successor.state == parse_state) {
            continue;
          }
          for (;;) {
            if (next_step->is_pass_through) {
              next_state.step_index++;
              next_step++;
              continue;
            }
            if (!next_step->is_dead_end) {
              _Bool did_finish_pattern = self->steps.contents[next_state.step_index].depth != step->depth;
              if (did_finish_pattern) {
                do { unsigned _index, _exists; do { *(&_index) = 0; *(&_exists) = 0; uint32_t size = (&analysis->finished_parent_symbols)->size - *(&_index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&_index) + half_size; comparison = ((int)*(&((&analysis->finished_parent_symbols)->contents[mid_index] )) - (int)(((state->root_symbol)))); if (comparison <= 0) *(&_index) = mid_index; size -= half_size; } comparison = ((int)*(&((&analysis->finished_parent_symbols)->contents[*(&_index)] )) - (int)(((state->root_symbol)))); if (comparison == 0) *(&_exists) = 1; else if (comparison < 0) *(&_index) += 1; } while (0); if (!_exists) _array__splice((Array *)(&analysis->finished_parent_symbols), (sizeof *(&analysis->finished_parent_symbols)->contents), _index, 0, 1, &(state->root_symbol)); } while (0);
              } else if (next_state.depth == 0) {
                do { unsigned _index, _exists; do { *(&_index) = 0; *(&_exists) = 0; uint32_t size = (&analysis->final_step_indices)->size - *(&_index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&_index) + half_size; comparison = ((int)*(&((&analysis->final_step_indices)->contents[mid_index] )) - (int)(((next_state.step_index)))); if (comparison <= 0) *(&_index) = mid_index; size -= half_size; } comparison = ((int)*(&((&analysis->final_step_indices)->contents[*(&_index)] )) - (int)(((next_state.step_index)))); if (comparison == 0) *(&_exists) = 1; else if (comparison < 0) *(&_index) += 1; } while (0); if (!_exists) _array__splice((Array *)(&analysis->final_step_indices), (sizeof *(&analysis->final_step_indices)->contents), _index, 0, 1, &(next_state.step_index)); } while (0);
              } else {
                analysis_state_set__insert_sorted(&analysis->next_states, &analysis->state_pool, &next_state);
              }
            }
            if (
              does_match &&
              next_step->alternative_index != NONE &&
              next_step->alternative_index > next_state.step_index
            ) {
              next_state.step_index = next_step->alternative_index;
              next_step = &self->steps.contents[next_state.step_index];
            } else {
              break;
            }
          }
        }
      }
    }
    AnalysisStateSet _states = analysis->states;
    analysis->states = analysis->next_states;
    analysis->next_states = _states;
  }
}
static _Bool ts_query__analyze_patterns(TSQuery *self, unsigned *error_offset) {
  struct { uint16_t *contents; uint32_t size; uint32_t capacity; } non_rooted_pattern_start_steps = { ((void *)0), 0, 0 };
  for (unsigned i = 0; i < self->pattern_map.size; i++) {
    PatternEntry *pattern = &self->pattern_map.contents[i];
    if (!pattern->is_rooted) {
      QueryStep *step = &self->steps.contents[pattern->step_index];
      if (step->symbol != WILDCARD_SYMBOL) {
        (_array__grow((Array *)(&non_rooted_pattern_start_steps), 1, (sizeof *(&non_rooted_pattern_start_steps)->contents)), (&non_rooted_pattern_start_steps)->contents[(&non_rooted_pattern_start_steps)->size++] = (i));
      }
    }
  }
  struct { uint32_t *contents; uint32_t size; uint32_t capacity; } parent_step_indices = { ((void *)0), 0, 0 };
  for (unsigned i = 0; i < self->steps.size; i++) {
    QueryStep *step = &self->steps.contents[i];
    if (step->depth == PATTERN_DONE_MARKER) {
      step->parent_pattern_guaranteed = 1;
      step->root_pattern_guaranteed = 1;
      continue;
    }
    _Bool has_children = 0;
    _Bool is_wildcard = step->symbol == WILDCARD_SYMBOL;
    step->contains_captures = step->capture_ids[0] != NONE;
    for (unsigned j = i + 1; j < self->steps.size; j++) {
      QueryStep *next_step = &self->steps.contents[j];
      if (
        next_step->depth == PATTERN_DONE_MARKER ||
        next_step->depth <= step->depth
      ) break;
      if (next_step->capture_ids[0] != NONE) {
        step->contains_captures = 1;
      }
      if (!is_wildcard) {
        next_step->root_pattern_guaranteed = 1;
        next_step->parent_pattern_guaranteed = 1;
      }
      has_children = 1;
    }
    if (has_children && !is_wildcard) {
      (_array__grow((Array *)(&parent_step_indices), 1, (sizeof *(&parent_step_indices)->contents)), (&parent_step_indices)->contents[(&parent_step_indices)->size++] = (i));
    }
  }
  AnalysisSubgraphArray subgraphs = { ((void *)0), 0, 0 };
  for (unsigned i = 0; i < parent_step_indices.size; i++) {
    uint32_t parent_step_index = parent_step_indices.contents[i];
    TSSymbol parent_symbol = self->steps.contents[parent_step_index].symbol;
    AnalysisSubgraph subgraph = { .symbol = parent_symbol };
    do { unsigned _index, _exists; do { *(&_index) = 0; *(&_exists) = 0; uint32_t size = (&subgraphs)->size - *(&_index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&_index) + half_size; comparison = ((int)*(&((&subgraphs)->contents[mid_index] .symbol)) - (int)(((subgraph) .symbol))); if (comparison <= 0) *(&_index) = mid_index; size -= half_size; } comparison = ((int)*(&((&subgraphs)->contents[*(&_index)] .symbol)) - (int)(((subgraph) .symbol))); if (comparison == 0) *(&_exists) = 1; else if (comparison < 0) *(&_index) += 1; } while (0); if (!_exists) _array__splice((Array *)(&subgraphs), (sizeof *(&subgraphs)->contents), _index, 0, 1, &(subgraph)); } while (0);
  }
  for (TSSymbol sym = (uint16_t)self->language->token_count; sym < (uint16_t)self->language->symbol_count; sym++) {
    if (!ts_language_symbol_metadata(self->language, sym).visible) {
      AnalysisSubgraph subgraph = { .symbol = sym };
      do { unsigned _index, _exists; do { *(&_index) = 0; *(&_exists) = 0; uint32_t size = (&subgraphs)->size - *(&_index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&_index) + half_size; comparison = ((int)*(&((&subgraphs)->contents[mid_index] .symbol)) - (int)(((subgraph) .symbol))); if (comparison <= 0) *(&_index) = mid_index; size -= half_size; } comparison = ((int)*(&((&subgraphs)->contents[*(&_index)] .symbol)) - (int)(((subgraph) .symbol))); if (comparison == 0) *(&_exists) = 1; else if (comparison < 0) *(&_index) += 1; } while (0); if (!_exists) _array__splice((Array *)(&subgraphs), (sizeof *(&subgraphs)->contents), _index, 0, 1, &(subgraph)); } while (0);
    }
  }
  StatePredecessorMap predecessor_map = state_predecessor_map_new(self->language);
  for (TSStateId state = 1; state < (uint16_t)self->language->state_count; state++) {
    unsigned subgraph_index, exists;
    LookaheadIterator lookahead_iterator = ts_language_lookaheads(self->language, state);
    while (ts_lookahead_iterator__next(&lookahead_iterator)) {
      if (lookahead_iterator.action_count) {
        for (unsigned i = 0; i < lookahead_iterator.action_count; i++) {
          const TSParseAction *action = &lookahead_iterator.actions[i];
          if (action->type == TSParseActionTypeReduce) {
            const TSSymbol *aliases, *aliases_end;
            ts_language_aliases_for_symbol(
              self->language,
              action->reduce.symbol,
              &aliases,
              &aliases_end
            );
            for (const TSSymbol *symbol = aliases; symbol < aliases_end; symbol++) {
              do { *(&subgraph_index) = 0; *(&exists) = 0; uint32_t size = (&subgraphs)->size - *(&subgraph_index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&subgraph_index) + half_size; comparison = ((int)*(&((&subgraphs)->contents[mid_index] .symbol)) - (int)((*symbol))); if (comparison <= 0) *(&subgraph_index) = mid_index; size -= half_size; } comparison = ((int)*(&((&subgraphs)->contents[*(&subgraph_index)] .symbol)) - (int)((*symbol))); if (comparison == 0) *(&exists) = 1; else if (comparison < 0) *(&subgraph_index) += 1; } while (0);
              if (exists) {
                AnalysisSubgraph *subgraph = &subgraphs.contents[subgraph_index];
                if (subgraph->nodes.size == 0 || ((__builtin_expect(!((uint32_t)((&subgraph->nodes)->size - 1) < (&subgraph->nodes)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 1580, "(uint32_t)((&subgraph->nodes)->size - 1) < (&subgraph->nodes)->size") : (void)0), &(&subgraph->nodes)->contents[(&subgraph->nodes)->size - 1])->state != state) {
                  (_array__grow((Array *)(&subgraph->nodes), 1, (sizeof *(&subgraph->nodes)->contents)), (&subgraph->nodes)->contents[(&subgraph->nodes)->size++] = (((AnalysisSubgraphNode) { .state = state, .production_id = action->reduce.production_id, .child_index = action->reduce.child_count, .done = 1, })));
                }
              }
            }
          } else if (action->type == TSParseActionTypeShift && !action->shift.extra) {
            TSStateId next_state = action->shift.state;
            state_predecessor_map_add(&predecessor_map, next_state, state);
          }
        }
      } else if (lookahead_iterator.next_state != 0) {
        if (lookahead_iterator.next_state != state) {
          state_predecessor_map_add(&predecessor_map, lookahead_iterator.next_state, state);
        }
        if (ts_language_state_is_primary(self->language, state)) {
          const TSSymbol *aliases, *aliases_end;
          ts_language_aliases_for_symbol(
            self->language,
            lookahead_iterator.symbol,
            &aliases,
            &aliases_end
          );
          for (const TSSymbol *symbol = aliases; symbol < aliases_end; symbol++) {
            do { *(&subgraph_index) = 0; *(&exists) = 0; uint32_t size = (&subgraphs)->size - *(&subgraph_index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&subgraph_index) + half_size; comparison = ((int)*(&((&subgraphs)->contents[mid_index] .symbol)) - (int)((*symbol))); if (comparison <= 0) *(&subgraph_index) = mid_index; size -= half_size; } comparison = ((int)*(&((&subgraphs)->contents[*(&subgraph_index)] .symbol)) - (int)((*symbol))); if (comparison == 0) *(&exists) = 1; else if (comparison < 0) *(&subgraph_index) += 1; } while (0);
            if (exists) {
              AnalysisSubgraph *subgraph = &subgraphs.contents[subgraph_index];
              if (
                subgraph->start_states.size == 0 ||
                *((__builtin_expect(!((uint32_t)((&subgraph->start_states)->size - 1) < (&subgraph->start_states)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 1619, "(uint32_t)((&subgraph->start_states)->size - 1) < (&subgraph->start_states)->size") : (void)0), &(&subgraph->start_states)->contents[(&subgraph->start_states)->size - 1]) != state
              )
              (_array__grow((Array *)(&subgraph->start_states), 1, (sizeof *(&subgraph->start_states)->contents)), (&subgraph->start_states)->contents[(&subgraph->start_states)->size++] = (state));
            }
          }
        }
      }
    }
  }
  struct { AnalysisSubgraphNode *contents; uint32_t size; uint32_t capacity; } next_nodes = { ((void *)0), 0, 0 };
  for (unsigned i = 0; i < subgraphs.size; i++) {
    AnalysisSubgraph *subgraph = &subgraphs.contents[i];
    if (subgraph->nodes.size == 0) {
      _array__delete((Array *)(&subgraph->start_states));
      _array__erase((Array *)(&subgraphs), (sizeof *(&subgraphs)->contents), i);
      i--;
      continue;
    }
    _array__assign((Array *)(&next_nodes), (const Array *)(&subgraph->nodes), (sizeof *(&next_nodes)->contents));
    while (next_nodes.size > 0) {
      AnalysisSubgraphNode node = ((&next_nodes)->contents[--(&next_nodes)->size]);
      if (node.child_index > 1) {
        unsigned predecessor_count;
        const TSStateId *predecessors = state_predecessor_map_get(
          &predecessor_map,
          node.state,
          &predecessor_count
        );
        for (unsigned j = 0; j < predecessor_count; j++) {
          AnalysisSubgraphNode predecessor_node = {
            .state = predecessors[j],
            .child_index = node.child_index - 1,
            .production_id = node.production_id,
            .done = 0,
          };
          unsigned index, exists;
          do { *(&index) = 0; *(&exists) = 0; uint32_t size = (&subgraph->nodes)->size - *(&index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&index) + half_size; comparison = analysis_subgraph_node__compare(&((&subgraph->nodes)->contents[mid_index] ), (&predecessor_node)); if (comparison <= 0) *(&index) = mid_index; size -= half_size; } comparison = analysis_subgraph_node__compare(&((&subgraph->nodes)->contents[*(&index)] ), (&predecessor_node)); if (comparison == 0) *(&exists) = 1; else if (comparison < 0) *(&index) += 1; } while (0);
          if (!exists) {
            _array__splice((Array *)(&subgraph->nodes), (sizeof *(&subgraph->nodes)->contents), index, 0, 1, &(predecessor_node));
            (_array__grow((Array *)(&next_nodes), 1, (sizeof *(&next_nodes)->contents)), (&next_nodes)->contents[(&next_nodes)->size++] = (predecessor_node));
          }
        }
      }
    }
  }
  _Bool all_patterns_are_valid = 1;
  QueryAnalysis analysis = query_analysis__new();
  for (unsigned i = 0; i < parent_step_indices.size; i++) {
    uint16_t parent_step_index = parent_step_indices.contents[i];
    uint16_t parent_depth = self->steps.contents[parent_step_index].depth;
    TSSymbol parent_symbol = self->steps.contents[parent_step_index].symbol;
    if (parent_symbol == ((TSSymbol)-1)) continue;
    unsigned subgraph_index, exists;
    do { *(&subgraph_index) = 0; *(&exists) = 0; uint32_t size = (&subgraphs)->size - *(&subgraph_index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&subgraph_index) + half_size; comparison = ((int)*(&((&subgraphs)->contents[mid_index] .symbol)) - (int)((parent_symbol))); if (comparison <= 0) *(&subgraph_index) = mid_index; size -= half_size; } comparison = ((int)*(&((&subgraphs)->contents[*(&subgraph_index)] .symbol)) - (int)((parent_symbol))); if (comparison == 0) *(&exists) = 1; else if (comparison < 0) *(&subgraph_index) += 1; } while (0);
    if (!exists) {
      unsigned first_child_step_index = parent_step_index + 1;
      uint32_t j, child_exists;
      do { *(&j) = 0; *(&child_exists) = 0; uint32_t size = (&self->step_offsets)->size - *(&j); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&j) + half_size; comparison = ((int)*(&((&self->step_offsets)->contents[mid_index] .step_index)) - (int)((first_child_step_index))); if (comparison <= 0) *(&j) = mid_index; size -= half_size; } comparison = ((int)*(&((&self->step_offsets)->contents[*(&j)] .step_index)) - (int)((first_child_step_index))); if (comparison == 0) *(&child_exists) = 1; else if (comparison < 0) *(&j) += 1; } while (0);
      (__builtin_expect(!(child_exists), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 1711, "child_exists") : (void)0);
      *error_offset = self->step_offsets.contents[j].byte_offset;
      all_patterns_are_valid = 0;
      break;
    }
    AnalysisSubgraph *subgraph = &subgraphs.contents[subgraph_index];
    analysis_state_set__clear(&analysis.states, &analysis.state_pool);
    analysis_state_set__clear(&analysis.deeper_states, &analysis.state_pool);
    for (unsigned j = 0; j < subgraph->start_states.size; j++) {
      TSStateId parse_state = subgraph->start_states.contents[j];
      analysis_state_set__push(&analysis.states, &analysis.state_pool, &((AnalysisState) {
        .step_index = parent_step_index + 1,
        .stack = {
          [0] = {
            .parse_state = parse_state,
            .parent_symbol = parent_symbol,
            .child_index = 0,
            .field_id = 0,
            .done = 0,
          },
        },
        .depth = 1,
        .root_symbol = parent_symbol,
      }));
    }
    analysis.did_abort = 0;
    ts_query__perform_analysis(self, &subgraphs, &analysis);
    if (analysis.did_abort) {
      for (unsigned j = parent_step_index + 1; j < self->steps.size; j++) {
        QueryStep *step = &self->steps.contents[j];
        if (
          step->depth <= parent_depth ||
          step->depth == PATTERN_DONE_MARKER
        ) break;
        if (!step->is_dead_end) {
          step->parent_pattern_guaranteed = 0;
          step->root_pattern_guaranteed = 0;
        }
      }
      continue;
    }
    if (analysis.finished_parent_symbols.size == 0) {
      (__builtin_expect(!(analysis.final_step_indices.size > 0), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 1770, "analysis.final_step_indices.size > 0") : (void)0);
      uint16_t impossible_step_index = *((__builtin_expect(!((uint32_t)((&analysis.final_step_indices)->size - 1) < (&analysis.final_step_indices)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 1771, "(uint32_t)((&analysis.final_step_indices)->size - 1) < (&analysis.final_step_indices)->size") : (void)0), &(&analysis.final_step_indices)->contents[(&analysis.final_step_indices)->size - 1]);
      uint32_t j, impossible_exists;
      do { *(&j) = 0; *(&impossible_exists) = 0; uint32_t size = (&self->step_offsets)->size - *(&j); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&j) + half_size; comparison = ((int)*(&((&self->step_offsets)->contents[mid_index] .step_index)) - (int)((impossible_step_index))); if (comparison <= 0) *(&j) = mid_index; size -= half_size; } comparison = ((int)*(&((&self->step_offsets)->contents[*(&j)] .step_index)) - (int)((impossible_step_index))); if (comparison == 0) *(&impossible_exists) = 1; else if (comparison < 0) *(&j) += 1; } while (0);
      if (j >= self->step_offsets.size) j = self->step_offsets.size - 1;
      *error_offset = self->step_offsets.contents[j].byte_offset;
      all_patterns_are_valid = 0;
      break;
    }
    for (unsigned j = 0; j < analysis.final_step_indices.size; j++) {
      uint32_t final_step_index = analysis.final_step_indices.contents[j];
      QueryStep *step = &self->steps.contents[final_step_index];
      if (
        step->depth != PATTERN_DONE_MARKER &&
        step->depth > parent_depth &&
        !step->is_dead_end
      ) {
        step->parent_pattern_guaranteed = 0;
        step->root_pattern_guaranteed = 0;
      }
    }
  }
  struct { uint16_t *contents; uint32_t size; uint32_t capacity; } predicate_capture_ids = { ((void *)0), 0, 0 };
  for (unsigned i = 0; i < self->patterns.size; i++) {
    QueryPattern *pattern = &self->patterns.contents[i];
    ((&predicate_capture_ids)->size = 0);
    for (
      unsigned start = pattern->predicate_steps.offset,
      end = start + pattern->predicate_steps.length,
      j = start; j < end; j++
    ) {
      TSQueryPredicateStep *step = &self->predicate_steps.contents[j];
      if (step->type == TSQueryPredicateStepTypeCapture) {
        uint16_t value_id = step->value_id;
        do { unsigned _index, _exists; do { *(&_index) = 0; *(&_exists) = 0; uint32_t size = (&predicate_capture_ids)->size - *(&_index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&_index) + half_size; comparison = ((int)*(&((&predicate_capture_ids)->contents[mid_index] )) - (int)(((value_id)))); if (comparison <= 0) *(&_index) = mid_index; size -= half_size; } comparison = ((int)*(&((&predicate_capture_ids)->contents[*(&_index)] )) - (int)(((value_id)))); if (comparison == 0) *(&_exists) = 1; else if (comparison < 0) *(&_index) += 1; } while (0); if (!_exists) _array__splice((Array *)(&predicate_capture_ids), (sizeof *(&predicate_capture_ids)->contents), _index, 0, 1, &(value_id)); } while (0);
      }
    }
    for (
      unsigned start = pattern->steps.offset,
      end = start + pattern->steps.length,
      j = start; j < end; j++
    ) {
      QueryStep *step = &self->steps.contents[j];
      for (unsigned k = 0; k < 3; k++) {
        uint16_t capture_id = step->capture_ids[k];
        if (capture_id == NONE) break;
        unsigned index, exists;
        do { *(&index) = 0; *(&exists) = 0; uint32_t size = (&predicate_capture_ids)->size - *(&index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&index) + half_size; comparison = ((int)*(&((&predicate_capture_ids)->contents[mid_index] )) - (int)((capture_id))); if (comparison <= 0) *(&index) = mid_index; size -= half_size; } comparison = ((int)*(&((&predicate_capture_ids)->contents[*(&index)] )) - (int)((capture_id))); if (comparison == 0) *(&exists) = 1; else if (comparison < 0) *(&index) += 1; } while (0);
        if (exists) {
          step->root_pattern_guaranteed = 0;
          break;
        }
      }
    }
  }
  _Bool done = self->steps.size == 0;
  while (!done) {
    done = 1;
    for (unsigned i = self->steps.size - 1; i > 0; i--) {
      QueryStep *step = &self->steps.contents[i];
      if (step->depth == PATTERN_DONE_MARKER) continue;
      _Bool parent_pattern_guaranteed = 0;
      for (;;) {
        if (step->root_pattern_guaranteed) {
          parent_pattern_guaranteed = 1;
          break;
        }
        if (step->alternative_index == NONE || step->alternative_index < i) {
          break;
        }
        step = &self->steps.contents[step->alternative_index];
      }
      if (!parent_pattern_guaranteed) {
        QueryStep *prev_step = &self->steps.contents[i - 1];
        if (
          !prev_step->is_dead_end &&
          prev_step->depth != PATTERN_DONE_MARKER &&
          prev_step->root_pattern_guaranteed
        ) {
          prev_step->root_pattern_guaranteed = 0;
          done = 0;
        }
      }
    }
  }
  analysis.did_abort = 0;
  for (uint32_t i = 0; i < non_rooted_pattern_start_steps.size; i++) {
    uint16_t pattern_entry_index = non_rooted_pattern_start_steps.contents[i];
    PatternEntry *pattern_entry = &self->pattern_map.contents[pattern_entry_index];
    analysis_state_set__clear(&analysis.states, &analysis.state_pool);
    analysis_state_set__clear(&analysis.deeper_states, &analysis.state_pool);
    for (unsigned j = 0; j < subgraphs.size; j++) {
      AnalysisSubgraph *subgraph = &subgraphs.contents[j];
      TSSymbolMetadata metadata = ts_language_symbol_metadata(self->language, subgraph->symbol);
      if (metadata.visible || metadata.named) continue;
      for (uint32_t k = 0; k < subgraph->start_states.size; k++) {
        TSStateId parse_state = subgraph->start_states.contents[k];
        analysis_state_set__push(&analysis.states, &analysis.state_pool, &((AnalysisState) {
          .step_index = pattern_entry->step_index,
          .stack = {
            [0] = {
              .parse_state = parse_state,
              .parent_symbol = subgraph->symbol,
              .child_index = 0,
              .field_id = 0,
              .done = 0,
            },
          },
          .root_symbol = subgraph->symbol,
          .depth = 1,
        }));
      }
    }
    ts_query__perform_analysis(
      self,
      &subgraphs,
      &analysis
    );
    if (analysis.finished_parent_symbols.size > 0) {
      self->patterns.contents[pattern_entry->pattern_index].is_non_local = 1;
    }
    for (unsigned k = 0; k < analysis.finished_parent_symbols.size; k++) {
      TSSymbol symbol = analysis.finished_parent_symbols.contents[k];
      do { unsigned _index, _exists; do { *(&_index) = 0; *(&_exists) = 0; uint32_t size = (&self->repeat_symbols_with_rootless_patterns)->size - *(&_index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&_index) + half_size; comparison = ((int)*(&((&self->repeat_symbols_with_rootless_patterns)->contents[mid_index] )) - (int)(((symbol)))); if (comparison <= 0) *(&_index) = mid_index; size -= half_size; } comparison = ((int)*(&((&self->repeat_symbols_with_rootless_patterns)->contents[*(&_index)] )) - (int)(((symbol)))); if (comparison == 0) *(&_exists) = 1; else if (comparison < 0) *(&_index) += 1; } while (0); if (!_exists) _array__splice((Array *)(&self->repeat_symbols_with_rootless_patterns), (sizeof *(&self->repeat_symbols_with_rootless_patterns)->contents), _index, 0, 1, &(symbol)); } while (0);
    }
  }
  for (unsigned i = 0; i < subgraphs.size; i++) {
    _array__delete((Array *)(&subgraphs.contents[i].start_states));
    _array__delete((Array *)(&subgraphs.contents[i].nodes));
  }
  _array__delete((Array *)(&subgraphs));
  query_analysis__delete(&analysis);
  _array__delete((Array *)(&next_nodes));
  _array__delete((Array *)(&non_rooted_pattern_start_steps));
  _array__delete((Array *)(&parent_step_indices));
  _array__delete((Array *)(&predicate_capture_ids));
  state_predecessor_map_delete(&predecessor_map);
  return all_patterns_are_valid;
}
static void ts_query__add_negated_fields(
  TSQuery *self,
  uint16_t step_index,
  TSFieldId *field_ids,
  uint16_t field_count
) {
  QueryStep *step = &self->steps.contents[step_index];
  _Bool failed_match = 0;
  unsigned match_count = 0;
  unsigned start_i = 0;
  for (unsigned i = 0; i < self->negated_fields.size; i++) {
    TSFieldId existing_field_id = self->negated_fields.contents[i];
    if (existing_field_id == 0) {
      if (match_count == field_count) {
        step->negated_field_list_id = start_i;
        return;
      } else {
        start_i = i + 1;
        match_count = 0;
        failed_match = 0;
      }
    }
    else if (
      match_count < field_count &&
      existing_field_id == field_ids[match_count] &&
      !failed_match
    ) {
      match_count++;
    }
    else {
      match_count = 0;
      failed_match = 1;
    }
  }
  step->negated_field_list_id = self->negated_fields.size;
  _array__splice( (Array *)(&self->negated_fields), (sizeof *(&self->negated_fields)->contents), (&self->negated_fields)->size, 0, field_count, field_ids );
  (_array__grow((Array *)(&self->negated_fields), 1, (sizeof *(&self->negated_fields)->contents)), (&self->negated_fields)->contents[(&self->negated_fields)->size++] = (0));
}
static TSQueryError ts_query__parse_string_literal(
  TSQuery *self,
  Stream *stream
) {
  const char *string_start = stream->input;
  if (stream->next != '"') return TSQueryErrorSyntax;
  stream_advance(stream);
  const char *prev_position = stream->input;
  _Bool is_escaped = 0;
  ((&self->string_buffer)->size = 0);
  for (;;) {
    if (is_escaped) {
      is_escaped = 0;
      switch (stream->next) {
        case 'n':
          (_array__grow((Array *)(&self->string_buffer), 1, (sizeof *(&self->string_buffer)->contents)), (&self->string_buffer)->contents[(&self->string_buffer)->size++] = ('\n'));
          break;
        case 'r':
          (_array__grow((Array *)(&self->string_buffer), 1, (sizeof *(&self->string_buffer)->contents)), (&self->string_buffer)->contents[(&self->string_buffer)->size++] = ('\r'));
          break;
        case 't':
          (_array__grow((Array *)(&self->string_buffer), 1, (sizeof *(&self->string_buffer)->contents)), (&self->string_buffer)->contents[(&self->string_buffer)->size++] = ('\t'));
          break;
        case '0':
          (_array__grow((Array *)(&self->string_buffer), 1, (sizeof *(&self->string_buffer)->contents)), (&self->string_buffer)->contents[(&self->string_buffer)->size++] = ('\0'));
          break;
        default:
          _array__splice( (Array *)(&self->string_buffer), (sizeof *(&self->string_buffer)->contents), (&self->string_buffer)->size, 0, stream->next_size, stream->input );
          break;
      }
      prev_position = stream->input + stream->next_size;
    } else {
      if (stream->next == '\\') {
        _array__splice( (Array *)(&self->string_buffer), (sizeof *(&self->string_buffer)->contents), (&self->string_buffer)->size, 0, (uint32_t)(stream->input - prev_position), prev_position );
        prev_position = stream->input + 1;
        is_escaped = 1;
      } else if (stream->next == '"') {
        _array__splice( (Array *)(&self->string_buffer), (sizeof *(&self->string_buffer)->contents), (&self->string_buffer)->size, 0, (uint32_t)(stream->input - prev_position), prev_position );
        stream_advance(stream);
        return TSQueryErrorNone;
      } else if (stream->next == '\n') {
        stream_reset(stream, string_start);
        return TSQueryErrorSyntax;
      }
    }
    if (!stream_advance(stream)) {
      stream_reset(stream, string_start);
      return TSQueryErrorSyntax;
    }
  }
}
static TSQueryError ts_query__parse_predicate(
  TSQuery *self,
  Stream *stream
) {
  if (!stream_is_ident_start(stream)) return TSQueryErrorSyntax;
  const char *predicate_name = stream->input;
  stream_scan_identifier(stream);
  uint32_t length = (uint32_t)(stream->input - predicate_name);
  uint16_t id = symbol_table_insert_name(
    &self->predicate_values,
    predicate_name,
    length
  );
  (_array__grow((Array *)(&self->predicate_steps), 1, (sizeof *(&self->predicate_steps)->contents)), (&self->predicate_steps)->contents[(&self->predicate_steps)->size++] = (((TSQueryPredicateStep) { .type = TSQueryPredicateStepTypeString, .value_id = id, })));
  stream_skip_whitespace(stream);
  for (;;) {
    if (stream->next == ')') {
      stream_advance(stream);
      stream_skip_whitespace(stream);
      (_array__grow((Array *)(&self->predicate_steps), 1, (sizeof *(&self->predicate_steps)->contents)), (&self->predicate_steps)->contents[(&self->predicate_steps)->size++] = (((TSQueryPredicateStep) { .type = TSQueryPredicateStepTypeDone, .value_id = 0, })));
      break;
    }
    else if (stream->next == '@') {
      stream_advance(stream);
      if (!stream_is_ident_start(stream)) return TSQueryErrorSyntax;
      const char *capture_name = stream->input;
      stream_scan_identifier(stream);
      uint32_t capture_length = (uint32_t)(stream->input - capture_name);
      int capture_id = symbol_table_id_for_name(
        &self->captures,
        capture_name,
        capture_length
      );
      if (capture_id == -1) {
        stream_reset(stream, capture_name);
        return TSQueryErrorCapture;
      }
      (_array__grow((Array *)(&self->predicate_steps), 1, (sizeof *(&self->predicate_steps)->contents)), (&self->predicate_steps)->contents[(&self->predicate_steps)->size++] = (((TSQueryPredicateStep) { .type = TSQueryPredicateStepTypeCapture, .value_id = capture_id, })));
    }
    else if (stream->next == '"') {
      TSQueryError e = ts_query__parse_string_literal(self, stream);
      if (e) return e;
      uint16_t query_id = symbol_table_insert_name(
        &self->predicate_values,
        self->string_buffer.contents,
        self->string_buffer.size
      );
      (_array__grow((Array *)(&self->predicate_steps), 1, (sizeof *(&self->predicate_steps)->contents)), (&self->predicate_steps)->contents[(&self->predicate_steps)->size++] = (((TSQueryPredicateStep) { .type = TSQueryPredicateStepTypeString, .value_id = query_id, })));
    }
    else if (stream_is_ident_start(stream)) {
      const char *symbol_start = stream->input;
      stream_scan_identifier(stream);
      uint32_t symbol_length = (uint32_t)(stream->input - symbol_start);
      uint16_t query_id = symbol_table_insert_name(
        &self->predicate_values,
        symbol_start,
        symbol_length
      );
      (_array__grow((Array *)(&self->predicate_steps), 1, (sizeof *(&self->predicate_steps)->contents)), (&self->predicate_steps)->contents[(&self->predicate_steps)->size++] = (((TSQueryPredicateStep) { .type = TSQueryPredicateStepTypeString, .value_id = query_id, })));
    }
    else {
      return TSQueryErrorSyntax;
    }
    stream_skip_whitespace(stream);
  }
  return 0;
}
static TSQueryError ts_query__parse_pattern(
  TSQuery *self,
  Stream *stream,
  uint32_t depth,
  _Bool is_immediate,
  CaptureQuantifiers *capture_quantifiers
) {
  if (stream->next == 0) return TSQueryErrorSyntax;
  if (stream->next == ')' || stream->next == ']') return PARENT_DONE;
  const uint32_t starting_step_index = self->steps.size;
  if (
    self->step_offsets.size == 0 ||
    ((__builtin_expect(!((uint32_t)((&self->step_offsets)->size - 1) < (&self->step_offsets)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 2206, "(uint32_t)((&self->step_offsets)->size - 1) < (&self->step_offsets)->size") : (void)0), &(&self->step_offsets)->contents[(&self->step_offsets)->size - 1])->step_index != starting_step_index
  ) {
    (_array__grow((Array *)(&self->step_offsets), 1, (sizeof *(&self->step_offsets)->contents)), (&self->step_offsets)->contents[(&self->step_offsets)->size++] = (((StepOffset) { .step_index = starting_step_index, .byte_offset = stream_offset(stream), })));
  }
  if (stream->next == '[') {
    stream_advance(stream);
    stream_skip_whitespace(stream);
    struct { uint32_t *contents; uint32_t size; uint32_t capacity; } branch_step_indices = { ((void *)0), 0, 0 };
    CaptureQuantifiers branch_capture_quantifiers = capture_quantifiers_new();
    for (;;) {
      uint32_t start_index = self->steps.size;
      TSQueryError e = ts_query__parse_pattern(
        self,
        stream,
        depth,
        is_immediate,
        &branch_capture_quantifiers
      );
      if (e == PARENT_DONE) {
        if (stream->next == ']' && branch_step_indices.size > 0) {
          stream_advance(stream);
          break;
        }
        e = TSQueryErrorSyntax;
      }
      if (e) {
        capture_quantifiers_delete(&branch_capture_quantifiers);
        _array__delete((Array *)(&branch_step_indices));
        return e;
      }
      if (start_index == starting_step_index) {
        capture_quantifiers_replace(capture_quantifiers, &branch_capture_quantifiers);
      } else {
        capture_quantifiers_join_all(capture_quantifiers, &branch_capture_quantifiers);
      }
      (_array__grow((Array *)(&branch_step_indices), 1, (sizeof *(&branch_step_indices)->contents)), (&branch_step_indices)->contents[(&branch_step_indices)->size++] = (start_index));
      (_array__grow((Array *)(&self->steps), 1, (sizeof *(&self->steps)->contents)), (&self->steps)->contents[(&self->steps)->size++] = (query_step__new(0, depth, 0)));
      capture_quantifiers_clear(&branch_capture_quantifiers);
    }
    (void)((&self->steps)->contents[--(&self->steps)->size]);
    for (unsigned i = 0; i < branch_step_indices.size - 1; i++) {
      uint32_t step_index = branch_step_indices.contents[i];
      uint32_t next_step_index = branch_step_indices.contents[i + 1];
      QueryStep *start_step = &self->steps.contents[step_index];
      QueryStep *end_step = &self->steps.contents[next_step_index - 1];
      start_step->alternative_index = next_step_index;
      end_step->alternative_index = self->steps.size;
      end_step->is_dead_end = 1;
    }
    capture_quantifiers_delete(&branch_capture_quantifiers);
    _array__delete((Array *)(&branch_step_indices));
  }
  else if (stream->next == '(') {
    stream_advance(stream);
    stream_skip_whitespace(stream);
    if (stream->next == '(' || stream->next == '"' || stream->next == '[') {
      _Bool child_is_immediate = is_immediate;
      CaptureQuantifiers child_capture_quantifiers = capture_quantifiers_new();
      for (;;) {
        if (stream->next == '.') {
          child_is_immediate = 1;
          stream_advance(stream);
          stream_skip_whitespace(stream);
        }
        TSQueryError e = ts_query__parse_pattern(
          self,
          stream,
          depth,
          child_is_immediate,
          &child_capture_quantifiers
        );
        if (e == PARENT_DONE) {
          if (stream->next == ')') {
            stream_advance(stream);
            break;
          }
          e = TSQueryErrorSyntax;
        }
        if (e) {
          capture_quantifiers_delete(&child_capture_quantifiers);
          return e;
        }
        capture_quantifiers_add_all(capture_quantifiers, &child_capture_quantifiers);
        capture_quantifiers_clear(&child_capture_quantifiers);
        child_is_immediate = 0;
      }
      capture_quantifiers_delete(&child_capture_quantifiers);
    }
    else if (stream->next == '.' || stream->next == '#') {
      stream_advance(stream);
      return ts_query__parse_predicate(self, stream);
    }
    else {
      TSSymbol symbol;
      _Bool is_missing = 0;
      const char *node_name = stream->input;
      if (stream_is_ident_start(stream)) {
        stream_scan_identifier(stream);
        uint32_t length = (uint32_t)(stream->input - node_name);
        if (length == 1 && node_name[0] == '_') {
          symbol = WILDCARD_SYMBOL;
        } else if (!strncmp(node_name, "MISSING", length)) {
          is_missing = 1;
          stream_skip_whitespace(stream);
          if (stream_is_ident_start(stream)) {
            const char *missing_node_name = stream->input;
            stream_scan_identifier(stream);
            uint32_t missing_node_length = (uint32_t)(stream->input - missing_node_name);
            symbol = ts_language_symbol_for_name(
              self->language,
              missing_node_name,
              missing_node_length,
              1
            );
            if (!symbol) {
              stream_reset(stream, missing_node_name);
              return TSQueryErrorNodeType;
            }
          }
          else if (stream->next == '"') {
            const char *string_start = stream->input;
            TSQueryError e = ts_query__parse_string_literal(self, stream);
            if (e) return e;
            symbol = ts_language_symbol_for_name(
              self->language,
              self->string_buffer.contents,
              self->string_buffer.size,
              0
            );
            if (!symbol) {
              stream_reset(stream, string_start + 1);
              return TSQueryErrorNodeType;
            }
          }
          else if (stream->next == ')') {
            symbol = WILDCARD_SYMBOL;
          }
          else {
            stream_reset(stream, stream->input);
            return TSQueryErrorSyntax;
          }
        }
        else {
          symbol = ts_language_symbol_for_name(
            self->language,
            node_name,
            length,
            1
          );
          if (!symbol) {
            stream_reset(stream, node_name);
            return TSQueryErrorNodeType;
          }
        }
      } else {
        return TSQueryErrorSyntax;
      }
      (_array__grow((Array *)(&self->steps), 1, (sizeof *(&self->steps)->contents)), (&self->steps)->contents[(&self->steps)->size++] = (query_step__new(symbol, depth, is_immediate)));
      QueryStep *step = ((__builtin_expect(!((uint32_t)((&self->steps)->size - 1) < (&self->steps)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 2403, "(uint32_t)((&self->steps)->size - 1) < (&self->steps)->size") : (void)0), &(&self->steps)->contents[(&self->steps)->size - 1]);
      if (ts_language_symbol_metadata(self->language, symbol).supertype) {
        step->supertype_symbol = step->symbol;
        step->symbol = WILDCARD_SYMBOL;
      }
      if (is_missing) {
        step->is_missing = 1;
      }
      if (symbol == WILDCARD_SYMBOL) {
        step->is_named = 1;
      }
      stream_skip_whitespace(stream);
      if (stream->next == '/') {
        if (!step->supertype_symbol) {
          stream_reset(stream, node_name - 1);
          return TSQueryErrorStructure;
        }
        stream_advance(stream);
        if (!stream_is_ident_start(stream)) {
          return TSQueryErrorSyntax;
        }
        const char *subtype_node_name = stream->input;
        stream_scan_identifier(stream);
        uint32_t length = (uint32_t)(stream->input - subtype_node_name);
        step->symbol = ts_language_symbol_for_name(
          self->language,
          subtype_node_name,
          length,
          1
        );
        if (!step->symbol) {
          stream_reset(stream, subtype_node_name);
          return TSQueryErrorNodeType;
        }
        if (self->language->abi_version >= 15) {
          uint32_t subtype_length;
          const TSSymbol *subtypes = ts_language_subtypes(
            self->language,
            step->supertype_symbol,
            &subtype_length
          );
          _Bool subtype_is_valid = 0;
          for (uint32_t i = 0; i < subtype_length; i++) {
            if (subtypes[i] == step->symbol) {
              subtype_is_valid = 1;
              break;
            }
          }
          if (!subtype_is_valid) {
            stream_reset(stream, node_name - 1);
            return TSQueryErrorStructure;
          }
        }
        stream_skip_whitespace(stream);
      }
      _Bool child_is_immediate = 0;
      uint16_t last_child_step_index = 0;
      uint16_t negated_field_count = 0;
      TSFieldId negated_field_ids[8];
      CaptureQuantifiers child_capture_quantifiers = capture_quantifiers_new();
      for (;;) {
        if (stream->next == '!') {
          stream_advance(stream);
          stream_skip_whitespace(stream);
          if (!stream_is_ident_start(stream)) {
            capture_quantifiers_delete(&child_capture_quantifiers);
            return TSQueryErrorSyntax;
          }
          const char *field_name = stream->input;
          stream_scan_identifier(stream);
          uint32_t length = (uint32_t)(stream->input - field_name);
          stream_skip_whitespace(stream);
          TSFieldId field_id = ts_language_field_id_for_name(
            self->language,
            field_name,
            length
          );
          if (!field_id) {
            stream->input = field_name;
            capture_quantifiers_delete(&child_capture_quantifiers);
            return TSQueryErrorField;
          }
          if (negated_field_count < 8) {
            negated_field_ids[negated_field_count] = field_id;
            negated_field_count++;
          }
          continue;
        }
        if (stream->next == '.') {
          child_is_immediate = 1;
          stream_advance(stream);
          stream_skip_whitespace(stream);
        }
        uint16_t step_index = self->steps.size;
        TSQueryError e = ts_query__parse_pattern(
          self,
          stream,
          depth + 1,
          child_is_immediate,
          &child_capture_quantifiers
        );
        if (e == PARENT_DONE) {
          if (stream->next == ')') {
            if (child_is_immediate) {
              if (last_child_step_index == 0) {
                capture_quantifiers_delete(&child_capture_quantifiers);
                return TSQueryErrorSyntax;
              }
              QueryStep *last_child_step = &self->steps.contents[last_child_step_index];
              last_child_step->is_last_child = 1;
              if (
                last_child_step->alternative_index != NONE &&
                last_child_step->alternative_index < self->steps.size
              ) {
                QueryStep *alternative_step = &self->steps.contents[last_child_step->alternative_index];
                alternative_step->is_last_child = 1;
                while (
                  alternative_step->alternative_index != NONE &&
                  alternative_step->alternative_index < self->steps.size
                ) {
                  alternative_step = &self->steps.contents[alternative_step->alternative_index];
                  alternative_step->is_last_child = 1;
                }
              }
            }
            if (negated_field_count) {
              ts_query__add_negated_fields(
                self,
                starting_step_index,
                negated_field_ids,
                negated_field_count
              );
            }
            stream_advance(stream);
            break;
          }
          e = TSQueryErrorSyntax;
        }
        if (e) {
          capture_quantifiers_delete(&child_capture_quantifiers);
          return e;
        }
        capture_quantifiers_add_all(capture_quantifiers, &child_capture_quantifiers);
        last_child_step_index = step_index;
        child_is_immediate = 0;
        capture_quantifiers_clear(&child_capture_quantifiers);
      }
      capture_quantifiers_delete(&child_capture_quantifiers);
    }
  }
  else if (stream->next == '_') {
    stream_advance(stream);
    stream_skip_whitespace(stream);
    (_array__grow((Array *)(&self->steps), 1, (sizeof *(&self->steps)->contents)), (&self->steps)->contents[(&self->steps)->size++] = (query_step__new(WILDCARD_SYMBOL, depth, is_immediate)));
  }
  else if (stream->next == '"') {
    const char *string_start = stream->input;
    TSQueryError e = ts_query__parse_string_literal(self, stream);
    if (e) return e;
    TSSymbol symbol = ts_language_symbol_for_name(
      self->language,
      self->string_buffer.contents,
      self->string_buffer.size,
      0
    );
    if (!symbol) {
      stream_reset(stream, string_start + 1);
      return TSQueryErrorNodeType;
    }
    (_array__grow((Array *)(&self->steps), 1, (sizeof *(&self->steps)->contents)), (&self->steps)->contents[(&self->steps)->size++] = (query_step__new(symbol, depth, is_immediate)));
  }
  else if (stream_is_ident_start(stream)) {
    const char *field_name = stream->input;
    stream_scan_identifier(stream);
    uint32_t length = (uint32_t)(stream->input - field_name);
    stream_skip_whitespace(stream);
    if (stream->next != ':') {
      stream_reset(stream, field_name);
      return TSQueryErrorSyntax;
    }
    stream_advance(stream);
    stream_skip_whitespace(stream);
    CaptureQuantifiers field_capture_quantifiers = capture_quantifiers_new();
    TSQueryError e = ts_query__parse_pattern(
      self,
      stream,
      depth,
      is_immediate,
      &field_capture_quantifiers
    );
    if (e) {
      capture_quantifiers_delete(&field_capture_quantifiers);
      if (e == PARENT_DONE) e = TSQueryErrorSyntax;
      return e;
    }
    TSFieldId field_id = ts_language_field_id_for_name(
      self->language,
      field_name,
      length
    );
    if (!field_id) {
      stream->input = field_name;
      return TSQueryErrorField;
    }
    uint32_t step_index = starting_step_index;
    QueryStep *step = &self->steps.contents[step_index];
    for (;;) {
      step->field = field_id;
      if (
        step->alternative_index != NONE &&
        step->alternative_index > step_index &&
        step->alternative_index < self->steps.size
      ) {
        step_index = step->alternative_index;
        step = &self->steps.contents[step_index];
      } else {
        break;
      }
    }
    capture_quantifiers_add_all(capture_quantifiers, &field_capture_quantifiers);
    capture_quantifiers_delete(&field_capture_quantifiers);
  }
  else {
    return TSQueryErrorSyntax;
  }
  stream_skip_whitespace(stream);
  TSQuantifier quantifier = TSQuantifierOne;
  for (;;) {
    if (stream->next == '+') {
      quantifier = quantifier_join(TSQuantifierOneOrMore, quantifier);
      stream_advance(stream);
      stream_skip_whitespace(stream);
      QueryStep repeat_step = query_step__new(WILDCARD_SYMBOL, depth, 0);
      repeat_step.alternative_index = starting_step_index;
      repeat_step.is_pass_through = 1;
      repeat_step.alternative_is_immediate = 1;
      (_array__grow((Array *)(&self->steps), 1, (sizeof *(&self->steps)->contents)), (&self->steps)->contents[(&self->steps)->size++] = (repeat_step));
    }
    else if (stream->next == '*') {
      quantifier = quantifier_join(TSQuantifierZeroOrMore, quantifier);
      stream_advance(stream);
      stream_skip_whitespace(stream);
      QueryStep repeat_step = query_step__new(WILDCARD_SYMBOL, depth, 0);
      repeat_step.alternative_index = starting_step_index;
      repeat_step.is_pass_through = 1;
      repeat_step.alternative_is_immediate = 1;
      (_array__grow((Array *)(&self->steps), 1, (sizeof *(&self->steps)->contents)), (&self->steps)->contents[(&self->steps)->size++] = (repeat_step));
      QueryStep *step = &self->steps.contents[starting_step_index];
      while (step->alternative_index != NONE && step->alternative_index < self->steps.size - 1) {
        step = &self->steps.contents[step->alternative_index];
      }
      step->alternative_index = self->steps.size;
    }
    else if (stream->next == '?') {
      quantifier = quantifier_join(TSQuantifierZeroOrOne, quantifier);
      stream_advance(stream);
      stream_skip_whitespace(stream);
      QueryStep *step = &self->steps.contents[starting_step_index];
      while (step->alternative_index != NONE && step->alternative_index < self->steps.size) {
        step = &self->steps.contents[step->alternative_index];
      }
      step->alternative_index = self->steps.size;
    }
    else if (stream->next == '@') {
      stream_advance(stream);
      if (!stream_is_ident_start(stream)) return TSQueryErrorSyntax;
      const char *capture_name = stream->input;
      stream_scan_identifier(stream);
      uint32_t length = (uint32_t)(stream->input - capture_name);
      stream_skip_whitespace(stream);
      uint16_t capture_id = symbol_table_insert_name(
        &self->captures,
        capture_name,
        length
      );
      capture_quantifiers_add_for_id(capture_quantifiers, capture_id, TSQuantifierOne);
      uint32_t step_index = starting_step_index;
      for (;;) {
        QueryStep *step = &self->steps.contents[step_index];
        query_step__add_capture(step, capture_id);
        if (
          step->alternative_index != NONE &&
          step->alternative_index > step_index &&
          step->alternative_index < self->steps.size
        ) {
          step_index = step->alternative_index;
        } else {
          break;
        }
      }
    }
    else {
      break;
    }
  }
  capture_quantifiers_mul(capture_quantifiers, quantifier);
  return 0;
}
TSQuery *ts_query_new(
  const TSLanguage *language,
  const char *source,
  uint32_t source_len,
  uint32_t *error_offset,
  TSQueryError *error_type
) {
  if (
    !language ||
    language->abi_version > 15 ||
    language->abi_version < 13
  ) {
    *error_type = TSQueryErrorLanguage;
    return ((void *)0);
  }
  TSQuery *self = ts_current_malloc(sizeof(TSQuery));
  *self = (TSQuery) {
    .steps = { ((void *)0), 0, 0 },
    .pattern_map = { ((void *)0), 0, 0 },
    .captures = symbol_table_new(),
    .capture_quantifiers = { ((void *)0), 0, 0 },
    .predicate_values = symbol_table_new(),
    .predicate_steps = { ((void *)0), 0, 0 },
    .patterns = { ((void *)0), 0, 0 },
    .step_offsets = { ((void *)0), 0, 0 },
    .string_buffer = { ((void *)0), 0, 0 },
    .negated_fields = { ((void *)0), 0, 0 },
    .repeat_symbols_with_rootless_patterns = { ((void *)0), 0, 0 },
    .wildcard_root_pattern_count = 0,
    .language = ts_language_copy(language),
  };
  (_array__grow((Array *)(&self->negated_fields), 1, (sizeof *(&self->negated_fields)->contents)), (&self->negated_fields)->contents[(&self->negated_fields)->size++] = (0));
  Stream stream = stream_new(source, source_len);
  stream_skip_whitespace(&stream);
  while (stream.input < stream.end) {
    uint32_t pattern_index = self->patterns.size;
    uint32_t start_step_index = self->steps.size;
    uint32_t start_predicate_step_index = self->predicate_steps.size;
    (_array__grow((Array *)(&self->patterns), 1, (sizeof *(&self->patterns)->contents)), (&self->patterns)->contents[(&self->patterns)->size++] = (((QueryPattern) { .steps = (Slice) {.offset = start_step_index}, .predicate_steps = (Slice) {.offset = start_predicate_step_index}, .start_byte = stream_offset(&stream), .is_non_local = 0, })));
    CaptureQuantifiers capture_quantifiers = capture_quantifiers_new();
    *error_type = ts_query__parse_pattern(self, &stream, 0, 0, &capture_quantifiers);
    (_array__grow((Array *)(&self->steps), 1, (sizeof *(&self->steps)->contents)), (&self->steps)->contents[(&self->steps)->size++] = (query_step__new(0, PATTERN_DONE_MARKER, 0)));
    QueryPattern *pattern = ((__builtin_expect(!((uint32_t)((&self->patterns)->size - 1) < (&self->patterns)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 2829, "(uint32_t)((&self->patterns)->size - 1) < (&self->patterns)->size") : (void)0), &(&self->patterns)->contents[(&self->patterns)->size - 1]);
    pattern->steps.length = self->steps.size - start_step_index;
    pattern->predicate_steps.length = self->predicate_steps.size - start_predicate_step_index;
    pattern->end_byte = stream_offset(&stream);
    if (*error_type) {
      if (*error_type == PARENT_DONE) *error_type = TSQueryErrorSyntax;
      *error_offset = stream_offset(&stream);
      capture_quantifiers_delete(&capture_quantifiers);
      ts_query_delete(self);
      return ((void *)0);
    }
    (_array__grow((Array *)(&self->capture_quantifiers), 1, (sizeof *(&self->capture_quantifiers)->contents)), (&self->capture_quantifiers)->contents[(&self->capture_quantifiers)->size++] = (capture_quantifiers));
    uint16_t wildcard_root_alternative_index = NONE;
    for (;;) {
      QueryStep *step = &self->steps.contents[start_step_index];
      if (step->symbol == WILDCARD_SYMBOL && step->depth == 0 && !step->field) {
        QueryStep *second_step = &self->steps.contents[start_step_index + 1];
        if (second_step->symbol != WILDCARD_SYMBOL && second_step->depth == 1 && !second_step->is_immediate) {
          wildcard_root_alternative_index = step->alternative_index;
          start_step_index += 1;
          step = second_step;
        }
      }
      uint32_t start_depth = step->depth;
      _Bool is_rooted = start_depth == 0;
      for (uint32_t step_index = start_step_index + 1; step_index < self->steps.size; step_index++) {
        QueryStep *child_step = &self->steps.contents[step_index];
        if (child_step->is_dead_end) break;
        if (child_step->depth == start_depth) {
          is_rooted = 0;
          break;
        }
      }
      ts_query__pattern_map_insert(self, step->symbol, (PatternEntry) {
        .step_index = start_step_index,
        .pattern_index = pattern_index,
        .is_rooted = is_rooted
      });
      if (step->symbol == WILDCARD_SYMBOL) {
        self->wildcard_root_pattern_count++;
      }
      if (step->alternative_index != NONE) {
        start_step_index = step->alternative_index;
      } else if (wildcard_root_alternative_index != NONE) {
        start_step_index = wildcard_root_alternative_index;
        wildcard_root_alternative_index = NONE;
      } else {
        break;
      }
    }
  }
  if (!ts_query__analyze_patterns(self, error_offset)) {
    *error_type = TSQueryErrorStructure;
    ts_query_delete(self);
    return ((void *)0);
  }
  _array__delete((Array *)(&self->string_buffer));
  return self;
}
void ts_query_delete(TSQuery *self) {
  if (self) {
    _array__delete((Array *)(&self->steps));
    _array__delete((Array *)(&self->pattern_map));
    _array__delete((Array *)(&self->predicate_steps));
    _array__delete((Array *)(&self->patterns));
    _array__delete((Array *)(&self->step_offsets));
    _array__delete((Array *)(&self->string_buffer));
    _array__delete((Array *)(&self->negated_fields));
    _array__delete((Array *)(&self->repeat_symbols_with_rootless_patterns));
    ts_language_delete(self->language);
    symbol_table_delete(&self->captures);
    symbol_table_delete(&self->predicate_values);
    for (uint32_t index = 0; index < self->capture_quantifiers.size; index++) {
      CaptureQuantifiers *capture_quantifiers = ((__builtin_expect(!((uint32_t)(index) < (&self->capture_quantifiers)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 2926, "(uint32_t)(index) < (&self->capture_quantifiers)->size") : (void)0), &(&self->capture_quantifiers)->contents[index]);
      capture_quantifiers_delete(capture_quantifiers);
    }
    _array__delete((Array *)(&self->capture_quantifiers));
    ts_current_free(self);
  }
}
uint32_t ts_query_pattern_count(const TSQuery *self) {
  return self->patterns.size;
}
uint32_t ts_query_capture_count(const TSQuery *self) {
  return self->captures.slices.size;
}
uint32_t ts_query_string_count(const TSQuery *self) {
  return self->predicate_values.slices.size;
}
const char *ts_query_capture_name_for_id(
  const TSQuery *self,
  uint32_t index,
  uint32_t *length
) {
  return symbol_table_name_for_id(&self->captures, index, length);
}
TSQuantifier ts_query_capture_quantifier_for_id(
  const TSQuery *self,
  uint32_t pattern_index,
  uint32_t capture_index
) {
  CaptureQuantifiers *capture_quantifiers = ((__builtin_expect(!((uint32_t)(pattern_index) < (&self->capture_quantifiers)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 2959, "(uint32_t)(pattern_index) < (&self->capture_quantifiers)->size") : (void)0), &(&self->capture_quantifiers)->contents[pattern_index]);
  return capture_quantifier_for_id(capture_quantifiers, capture_index);
}
const char *ts_query_string_value_for_id(
  const TSQuery *self,
  uint32_t index,
  uint32_t *length
) {
  return symbol_table_name_for_id(&self->predicate_values, index, length);
}
const TSQueryPredicateStep *ts_query_predicates_for_pattern(
  const TSQuery *self,
  uint32_t pattern_index,
  uint32_t *step_count
) {
  Slice slice = self->patterns.contents[pattern_index].predicate_steps;
  *step_count = slice.length;
  if (self->predicate_steps.contents == ((void *)0)) {
    return ((void *)0);
  }
  return &self->predicate_steps.contents[slice.offset];
}
uint32_t ts_query_start_byte_for_pattern(
  const TSQuery *self,
  uint32_t pattern_index
) {
  return self->patterns.contents[pattern_index].start_byte;
}
uint32_t ts_query_end_byte_for_pattern(
  const TSQuery *self,
  uint32_t pattern_index
) {
  return self->patterns.contents[pattern_index].end_byte;
}
_Bool ts_query_is_pattern_rooted(
  const TSQuery *self,
  uint32_t pattern_index
) {
  for (unsigned i = 0; i < self->pattern_map.size; i++) {
    PatternEntry *entry = &self->pattern_map.contents[i];
    if (entry->pattern_index == pattern_index) {
      if (!entry->is_rooted) return 0;
    }
  }
  return 1;
}
_Bool ts_query_is_pattern_non_local(
  const TSQuery *self,
  uint32_t pattern_index
) {
  if (pattern_index < self->patterns.size) {
    return self->patterns.contents[pattern_index].is_non_local;
  } else {
    return 0;
  }
}
_Bool ts_query_is_pattern_guaranteed_at_step(
  const TSQuery *self,
  uint32_t byte_offset
) {
  uint32_t step_index = 4294967295U;
  for (unsigned i = 0; i < self->step_offsets.size; i++) {
    StepOffset *step_offset = &self->step_offsets.contents[i];
    if (step_offset->byte_offset > byte_offset) break;
    step_index = step_offset->step_index;
  }
  if (step_index < self->steps.size) {
    return self->steps.contents[step_index].root_pattern_guaranteed;
  } else {
    return 0;
  }
}
_Bool ts_query__step_is_fallible(
  const TSQuery *self,
  uint16_t step_index
) {
  (__builtin_expect(!((uint32_t)step_index + 1 < self->steps.size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./query.c", 3043, "(uint32_t)step_index + 1 < self->steps.size") : (void)0);
  QueryStep *step = &self->steps.contents[step_index];
  QueryStep *next_step = &self->steps.contents[step_index + 1];
  return (
    next_step->depth != PATTERN_DONE_MARKER &&
    next_step->depth > step->depth &&
    (!next_step->parent_pattern_guaranteed || step->symbol == WILDCARD_SYMBOL)
  );
}
void ts_query_disable_capture(
  TSQuery *self,
  const char *name,
  uint32_t length
) {
  int id = symbol_table_id_for_name(&self->captures, name, length);
  if (id != -1) {
    for (unsigned i = 0; i < self->steps.size; i++) {
      QueryStep *step = &self->steps.contents[i];
      query_step__remove_capture(step, id);
    }
  }
}
void ts_query_disable_pattern(
  TSQuery *self,
  uint32_t pattern_index
) {
  for (unsigned i = 0; i < self->pattern_map.size; i++) {
    PatternEntry *pattern = &self->pattern_map.contents[i];
    if (pattern->pattern_index == pattern_index) {
      _array__erase((Array *)(&self->pattern_map), (sizeof *(&self->pattern_map)->contents), i);
      i--;
    }
  }
}
TSQueryCursor *ts_query_cursor_new(void) {
  TSQueryCursor *self = ts_current_malloc(sizeof(TSQueryCursor));
  *self = (TSQueryCursor) {
    .did_exceed_match_limit = 0,
    .ascending = 0,
    .halted = 0,
    .states = { ((void *)0), 0, 0 },
    .finished_states = { ((void *)0), 0, 0 },
    .capture_list_pool = capture_list_pool_new(),
    .start_byte = 0,
    .end_byte = 4294967295U,
    .start_point = {0, 0},
    .end_point = ((TSPoint) {4294967295U, 4294967295U}),
    .max_start_depth = 4294967295U,
    .timeout_duration = 0,
    .end_clock = clock_null(),
    .operation_count = 0,
  };
  _array__reserve((Array *)(&self->states), (sizeof *(&self->states)->contents), 8);
  _array__reserve((Array *)(&self->finished_states), (sizeof *(&self->finished_states)->contents), 8);
  return self;
}
void ts_query_cursor_delete(TSQueryCursor *self) {
  _array__delete((Array *)(&self->states));
  _array__delete((Array *)(&self->finished_states));
  ts_tree_cursor_delete(&self->cursor);
  capture_list_pool_delete(&self->capture_list_pool);
  ts_current_free(self);
}
_Bool ts_query_cursor_did_exceed_match_limit(const TSQueryCursor *self) {
  return self->did_exceed_match_limit;
}
uint32_t ts_query_cursor_match_limit(const TSQueryCursor *self) {
  return self->capture_list_pool.max_capture_list_count;
}
void ts_query_cursor_set_match_limit(TSQueryCursor *self, uint32_t limit) {
  self->capture_list_pool.max_capture_list_count = limit;
}
uint64_t ts_query_cursor_timeout_micros(const TSQueryCursor *self) {
  return duration_to_micros(self->timeout_duration);
}
void ts_query_cursor_set_timeout_micros(TSQueryCursor *self, uint64_t timeout_micros) {
  self->timeout_duration = duration_from_micros(timeout_micros);
}
void ts_query_cursor_exec(
  TSQueryCursor *self,
  const TSQuery *query,
  TSNode node
) {
  if (query) {
    ;
    for (unsigned i = 0; i < query->steps.size; i++) {
      QueryStep *step = &query->steps.contents[i];
      ;
      if (step->depth == PATTERN_DONE_MARKER) {
        ;
      } else if (step->is_dead_end) {
        ;
      } else if (step->is_pass_through) {
        ;
      } else if (step->symbol != WILDCARD_SYMBOL) {
        ;
      } else {
        ;
      }
      if (step->field) {
        ;
      }
      if (step->alternative_index != NONE) {
        ;
      }
      ;
    }
  }
  ((&self->states)->size = 0);
  ((&self->finished_states)->size = 0);
  ts_tree_cursor_reset(&self->cursor, node);
  capture_list_pool_reset(&self->capture_list_pool);
  self->on_visible_node = 1;
  self->next_state_id = 0;
  self->depth = 0;
  self->ascending = 0;
  self->halted = 0;
  self->query = query;
  self->did_exceed_match_limit = 0;
  self->operation_count = 0;
  if (self->timeout_duration) {
    self->end_clock = clock_after(clock_now(), self->timeout_duration);
  } else {
    self->end_clock = clock_null();
  }
  self->query_options = ((void *)0);
  self->query_state = (TSQueryCursorState) {0};
}
void ts_query_cursor_exec_with_options(
  TSQueryCursor *self,
  const TSQuery *query,
  TSNode node,
  const TSQueryCursorOptions *query_options
) {
  ts_query_cursor_exec(self, query, node);
  if (query_options) {
    self->query_options = query_options;
    self->query_state = (TSQueryCursorState) {
      .payload = query_options->payload
    };
  }
}
_Bool ts_query_cursor_set_byte_range(
  TSQueryCursor *self,
  uint32_t start_byte,
  uint32_t end_byte
) {
  if (end_byte == 0) {
    end_byte = 4294967295U;
  }
  if (start_byte > end_byte) {
    return 0;
  }
  self->start_byte = start_byte;
  self->end_byte = end_byte;
  return 1;
}
_Bool ts_query_cursor_set_point_range(
  TSQueryCursor *self,
  TSPoint start_point,
  TSPoint end_point
) {
  if (end_point.row == 0 && end_point.column == 0) {
    end_point = ((TSPoint) {4294967295U, 4294967295U});
  }
  if (point_gt(start_point, end_point)) {
    return 0;
  }
  self->start_point = start_point;
  self->end_point = end_point;
  return 1;
}
static _Bool ts_query_cursor__first_in_progress_capture(
  TSQueryCursor *self,
  uint32_t *state_index,
  uint32_t *byte_offset,
  uint32_t *pattern_index,
  _Bool *is_definite
) {
  _Bool result = 0;
  *state_index = 4294967295U;
  *byte_offset = 4294967295U;
  *pattern_index = 4294967295U;
  for (unsigned i = 0; i < self->states.size; i++) {
    QueryState *state = &self->states.contents[i];
    if (state->dead) continue;
    const CaptureList *captures = capture_list_pool_get(
      &self->capture_list_pool,
      state->capture_list_id
    );
    if (state->consumed_capture_count >= captures->size) {
      continue;
    }
    TSNode node = captures->contents[state->consumed_capture_count].node;
    if (
      ts_node_end_byte(node) <= self->start_byte ||
      point_lte(ts_node_end_point(node), self->start_point)
    ) {
      state->consumed_capture_count++;
      i--;
      continue;
    }
    uint32_t node_start_byte = ts_node_start_byte(node);
    if (
      !result ||
      node_start_byte < *byte_offset ||
      (node_start_byte == *byte_offset && state->pattern_index < *pattern_index)
    ) {
      QueryStep *step = &self->query->steps.contents[state->step_index];
      if (is_definite) {
        *is_definite = step->root_pattern_guaranteed && !step->is_immediate;
      } else if (step->root_pattern_guaranteed) {
        continue;
      }
      result = 1;
      *state_index = i;
      *byte_offset = node_start_byte;
      *pattern_index = state->pattern_index;
    }
  }
  return result;
}
int ts_query_cursor__compare_nodes(TSNode left, TSNode right) {
  if (left.id != right.id) {
    uint32_t left_start = ts_node_start_byte(left);
    uint32_t right_start = ts_node_start_byte(right);
    if (left_start < right_start) return -1;
    if (left_start > right_start) return 1;
    uint32_t left_node_count = ts_node_end_byte(left);
    uint32_t right_node_count = ts_node_end_byte(right);
    if (left_node_count > right_node_count) return -1;
    if (left_node_count < right_node_count) return 1;
  }
  return 0;
}
void ts_query_cursor__compare_captures(
  TSQueryCursor *self,
  QueryState *left_state,
  QueryState *right_state,
  _Bool *left_contains_right,
  _Bool *right_contains_left
) {
  const CaptureList *left_captures = capture_list_pool_get(
    &self->capture_list_pool,
    left_state->capture_list_id
  );
  const CaptureList *right_captures = capture_list_pool_get(
    &self->capture_list_pool,
    right_state->capture_list_id
  );
  *left_contains_right = 1;
  *right_contains_left = 1;
  unsigned i = 0, j = 0;
  for (;;) {
    if (i < left_captures->size) {
      if (j < right_captures->size) {
        TSQueryCapture *left = &left_captures->contents[i];
        TSQueryCapture *right = &right_captures->contents[j];
        if (left->node.id == right->node.id && left->index == right->index) {
          i++;
          j++;
        } else {
          switch (ts_query_cursor__compare_nodes(left->node, right->node)) {
            case -1:
              *right_contains_left = 0;
              i++;
              break;
            case 1:
              *left_contains_right = 0;
              j++;
              break;
            default:
              *right_contains_left = 0;
              *left_contains_right = 0;
              i++;
              j++;
              break;
          }
        }
      } else {
        *right_contains_left = 0;
        break;
      }
    } else {
      if (j < right_captures->size) {
        *left_contains_right = 0;
      }
      break;
    }
  }
}
static void ts_query_cursor__add_state(
  TSQueryCursor *self,
  const PatternEntry *pattern
) {
  QueryStep *step = &self->query->steps.contents[pattern->step_index];
  uint32_t start_depth = self->depth - step->depth;
  uint32_t index = self->states.size;
  while (index > 0) {
    QueryState *prev_state = &self->states.contents[index - 1];
    if (prev_state->start_depth < start_depth) break;
    if (prev_state->start_depth == start_depth) {
      if (
        prev_state->pattern_index == pattern->pattern_index &&
        prev_state->step_index == pattern->step_index
      ) return;
      if (prev_state->pattern_index <= pattern->pattern_index) break;
    }
    index--;
  }
  ;
  _array__splice((Array *)(&self->states), (sizeof *(&self->states)->contents), index, 0, 1, &(((QueryState) { .id = 4294967295U, .capture_list_id = NONE, .step_index = pattern->step_index, .pattern_index = pattern->pattern_index, .start_depth = start_depth, .consumed_capture_count = 0, .seeking_immediate_match = 1, .has_in_progress_alternatives = 0, .needs_parent = step->depth == 1, .dead = 0, })));
}
static CaptureList *ts_query_cursor__prepare_to_capture(
  TSQueryCursor *self,
  QueryState *state,
  unsigned state_index_to_preserve
) {
  if (state->capture_list_id == NONE) {
    state->capture_list_id = capture_list_pool_acquire(&self->capture_list_pool);
    if (state->capture_list_id == NONE) {
      self->did_exceed_match_limit = 1;
      uint32_t state_index, byte_offset, pattern_index;
      if (
        ts_query_cursor__first_in_progress_capture(
          self,
          &state_index,
          &byte_offset,
          &pattern_index,
          ((void *)0)
        ) &&
        state_index != state_index_to_preserve
      ) {
        ;
        QueryState *other_state = &self->states.contents[state_index];
        state->capture_list_id = other_state->capture_list_id;
        other_state->capture_list_id = NONE;
        other_state->dead = 1;
        CaptureList *list = capture_list_pool_get_mut(
          &self->capture_list_pool,
          state->capture_list_id
        );
        ((list)->size = 0);
        return list;
      } else {
        ;
        return ((void *)0);
      }
    }
  }
  return capture_list_pool_get_mut(&self->capture_list_pool, state->capture_list_id);
}
static void ts_query_cursor__capture(
  TSQueryCursor *self,
  QueryState *state,
  QueryStep *step,
  TSNode node
) {
  if (state->dead) return;
  CaptureList *capture_list = ts_query_cursor__prepare_to_capture(self, state, 4294967295U);
  if (!capture_list) {
    state->dead = 1;
    return;
  }
  for (unsigned j = 0; j < 3; j++) {
    uint16_t capture_id = step->capture_ids[j];
    if (step->capture_ids[j] == NONE) break;
    (_array__grow((Array *)(capture_list), 1, (sizeof *(capture_list)->contents)), (capture_list)->contents[(capture_list)->size++] = (((TSQueryCapture) { node, capture_id })));
    ;
  }
}
static QueryState *ts_query_cursor__copy_state(
  TSQueryCursor *self,
  QueryState **state_ref
) {
  const QueryState *state = *state_ref;
  uint32_t state_index = (uint32_t)(state - self->states.contents);
  QueryState copy = *state;
  copy.capture_list_id = NONE;
  if (state->capture_list_id != NONE) {
    CaptureList *new_captures = ts_query_cursor__prepare_to_capture(self, &copy, state_index);
    if (!new_captures) return ((void *)0);
    const CaptureList *old_captures = capture_list_pool_get(
      &self->capture_list_pool,
      state->capture_list_id
    );
    _array__splice( (Array *)((new_captures)), (sizeof *((new_captures))->contents), ((new_captures))->size, 0, (old_captures)->size, (old_captures)->contents );
  }
  _array__splice((Array *)(&self->states), (sizeof *(&self->states)->contents), state_index + 1, 0, 1, &(copy));
  *state_ref = &self->states.contents[state_index];
  return &self->states.contents[state_index + 1];
}
static inline _Bool ts_query_cursor__should_descend(
  TSQueryCursor *self,
  _Bool node_intersects_range
) {
  if (node_intersects_range && self->depth < self->max_start_depth) {
    return 1;
  }
  for (unsigned i = 0; i < self->states.size; i++) {
    QueryState *state = &self->states.contents[i];;
    QueryStep *next_step = &self->query->steps.contents[state->step_index];
    if (
      next_step->depth != PATTERN_DONE_MARKER &&
      state->start_depth + next_step->depth > self->depth
    ) {
      return 1;
    }
  }
  if (self->depth >= self->max_start_depth) {
    return 0;
  }
  if (!self->on_visible_node) {
    Subtree subtree = ts_tree_cursor_current_subtree(&self->cursor);
    if (ts_subtree_is_repetition(subtree)) {
      _Bool exists;
      uint32_t index;
      do { *(&index) = 0; *(&exists) = 0; uint32_t size = (&self->query->repeat_symbols_with_rootless_patterns)->size - *(&index); if (size == 0) break; int comparison; while (size > 1) { uint32_t half_size = size / 2; uint32_t mid_index = *(&index) + half_size; comparison = ((int)*(&((&self->query->repeat_symbols_with_rootless_patterns)->contents[mid_index] )) - (int)((ts_subtree_symbol(subtree)))); if (comparison <= 0) *(&index) = mid_index; size -= half_size; } comparison = ((int)*(&((&self->query->repeat_symbols_with_rootless_patterns)->contents[*(&index)] )) - (int)((ts_subtree_symbol(subtree)))); if (comparison == 0) *(&exists) = 1; else if (comparison < 0) *(&index) += 1; } while (0);
      return exists;
    }
    return 1;
  }
  return 0;
}
static inline _Bool ts_query_cursor__advance(
  TSQueryCursor *self,
  _Bool stop_on_definite_step
) {
  _Bool did_match = 0;
  for (;;) {
    if (self->halted) {
      while (self->states.size > 0) {
        QueryState state = ((&self->states)->contents[--(&self->states)->size]);
        capture_list_pool_release(
          &self->capture_list_pool,
          state.capture_list_id
        );
      }
    }
    if (++self->operation_count == OP_COUNT_PER_QUERY_TIMEOUT_CHECK) {
      self->operation_count = 0;
    }
    if (self->query_options && self->query_options->progress_callback) {
      self->query_state.current_byte_offset = ts_node_start_byte(ts_tree_cursor_current_node(&self->cursor));
    }
    if (
      did_match ||
      self->halted ||
      (
        self->operation_count == 0 &&
        (
          (!clock_is_null(self->end_clock) && clock_is_gt(clock_now(), self->end_clock)) ||
          (self->query_options && self->query_options->progress_callback && self->query_options->progress_callback(&self->query_state))
        )
      )
    ) {
      return did_match;
    }
    if (self->ascending) {
      if (self->on_visible_node) {
        ;
        uint32_t deleted_count = 0;
        for (unsigned i = 0, n = self->states.size; i < n; i++) {
          QueryState *state = &self->states.contents[i];
          QueryStep *step = &self->query->steps.contents[state->step_index];
          if (
            step->depth == PATTERN_DONE_MARKER &&
            (state->start_depth > self->depth || self->depth == 0)
          ) {
            ;
            (_array__grow((Array *)(&self->finished_states), 1, (sizeof *(&self->finished_states)->contents)), (&self->finished_states)->contents[(&self->finished_states)->size++] = (*state));
            did_match = 1;
            deleted_count++;
          }
          else if (
            step->depth != PATTERN_DONE_MARKER &&
            (uint32_t)state->start_depth + (uint32_t)step->depth > self->depth
          ) {
            ;
            capture_list_pool_release(
              &self->capture_list_pool,
              state->capture_list_id
            );
            deleted_count++;
          }
          else if (deleted_count > 0) {
            self->states.contents[i - deleted_count] = *state;
          }
        }
        self->states.size -= deleted_count;
      }
      switch (ts_tree_cursor_goto_next_sibling_internal(&self->cursor)) {
        case TreeCursorStepVisible:
          if (!self->on_visible_node) {
            self->depth++;
            self->on_visible_node = 1;
          }
          self->ascending = 0;
          break;
        case TreeCursorStepHidden:
          if (self->on_visible_node) {
            self->depth--;
            self->on_visible_node = 0;
          }
          self->ascending = 0;
          break;
        default:
          if (ts_tree_cursor_goto_parent(&self->cursor)) {
            self->depth--;
          } else {
            ;
            self->halted = 1;
          }
      }
    }
    else {
      TSNode node = ts_tree_cursor_current_node(&self->cursor);
      TSNode parent_node = ts_tree_cursor_parent_node(&self->cursor);
      uint32_t start_byte = ts_node_start_byte(node);
      uint32_t end_byte = ts_node_end_byte(node);
      TSPoint start_point = ts_node_start_point(node);
      TSPoint end_point = ts_node_end_point(node);
      _Bool is_empty = start_byte == end_byte;
      _Bool parent_precedes_range = !ts_node_is_null(parent_node) && (
        ts_node_end_byte(parent_node) <= self->start_byte ||
        point_lte(ts_node_end_point(parent_node), self->start_point)
      );
      _Bool parent_follows_range = !ts_node_is_null(parent_node) && (
        ts_node_start_byte(parent_node) >= self->end_byte ||
        point_gte(ts_node_start_point(parent_node), self->end_point)
      );
      _Bool node_precedes_range =
        parent_precedes_range ||
        end_byte < self->start_byte ||
        point_lt(end_point, self->start_point) ||
        (!is_empty && end_byte == self->start_byte) ||
        (!is_empty && point_eq(end_point, self->start_point));
      _Bool node_follows_range = parent_follows_range || (
        start_byte >= self->end_byte ||
        point_gte(start_point, self->end_point)
      );
      _Bool parent_intersects_range = !parent_precedes_range && !parent_follows_range;
      _Bool node_intersects_range = !node_precedes_range && !node_follows_range;
      if (self->on_visible_node) {
        TSSymbol symbol = ts_node_symbol(node);
        _Bool is_named = ts_node_is_named(node);
        _Bool is_missing = ts_node_is_missing(node);
        _Bool has_later_siblings;
        _Bool has_later_named_siblings;
        _Bool can_have_later_siblings_with_this_field;
        TSFieldId field_id = 0;
        TSSymbol supertypes[8] = {0};
        unsigned supertype_count = 8;
        ts_tree_cursor_current_status(
          &self->cursor,
          &field_id,
          &has_later_siblings,
          &has_later_named_siblings,
          &can_have_later_siblings_with_this_field,
          supertypes,
          &supertype_count
        );
        ;
        _Bool node_is_error = symbol == ((TSSymbol)-1);
        _Bool parent_is_error =
          !ts_node_is_null(parent_node) &&
          ts_node_symbol(parent_node) == ((TSSymbol)-1);
        if (!node_is_error) {
          for (unsigned i = 0; i < self->query->wildcard_root_pattern_count; i++) {
            PatternEntry *pattern = &self->query->pattern_map.contents[i];
            QueryStep *step = &self->query->steps.contents[pattern->step_index];
            uint32_t start_depth = self->depth - step->depth;
            if (
              (pattern->is_rooted ?
                node_intersects_range :
                (parent_intersects_range && !parent_is_error)) &&
              (!step->field || field_id == step->field) &&
              (!step->supertype_symbol || supertype_count > 0) &&
              (start_depth <= self->max_start_depth)
            ) {
              ts_query_cursor__add_state(self, pattern);
            }
          }
        }
        unsigned i;
        if (ts_query__pattern_map_search(self->query, symbol, &i)) {
          PatternEntry *pattern = &self->query->pattern_map.contents[i];
          QueryStep *step = &self->query->steps.contents[pattern->step_index];
          uint32_t start_depth = self->depth - step->depth;
          do {
            if (
              (pattern->is_rooted ?
                node_intersects_range :
                (parent_intersects_range && !parent_is_error)) &&
              (!step->field || field_id == step->field) &&
              (start_depth <= self->max_start_depth)
            ) {
              ts_query_cursor__add_state(self, pattern);
            }
            i++;
            if (i == self->query->pattern_map.size) break;
            pattern = &self->query->pattern_map.contents[i];
            step = &self->query->steps.contents[pattern->step_index];
          } while (step->symbol == symbol);
        }
        for (unsigned j = 0, copy_count = 0; j < self->states.size; j += 1 + copy_count) {
          QueryState *state = &self->states.contents[j];
          QueryStep *step = &self->query->steps.contents[state->step_index];
          state->has_in_progress_alternatives = 0;
          copy_count = 0;
          if ((uint32_t)state->start_depth + (uint32_t)step->depth != self->depth) continue;
          _Bool node_does_match = 0;
          if (step->symbol == WILDCARD_SYMBOL) {
            if (step->is_missing) {
              node_does_match = is_missing;
            } else {
              node_does_match = !node_is_error && (is_named || !step->is_named);
            }
          } else {
            node_does_match = symbol == step->symbol && (!step->is_missing || is_missing);
          }
          _Bool later_sibling_can_match = has_later_siblings;
          if ((step->is_immediate && is_named) || state->seeking_immediate_match) {
            later_sibling_can_match = 0;
          }
          if (step->is_last_child && has_later_named_siblings) {
            node_does_match = 0;
          }
          if (step->supertype_symbol) {
            _Bool has_supertype = 0;
            for (unsigned k = 0; k < supertype_count; k++) {
              if (supertypes[k] == step->supertype_symbol) {
                has_supertype = 1;
                break;
              }
            }
            if (!has_supertype) node_does_match = 0;
          }
          if (step->field) {
            if (step->field == field_id) {
              if (!can_have_later_siblings_with_this_field) {
                later_sibling_can_match = 0;
              }
            } else {
              node_does_match = 0;
            }
          }
          if (step->negated_field_list_id) {
            TSFieldId *negated_field_ids = &self->query->negated_fields.contents[step->negated_field_list_id];
            for (;;) {
              TSFieldId negated_field_id = *negated_field_ids;
              if (negated_field_id) {
                negated_field_ids++;
                if (ts_node_child_by_field_id(node, negated_field_id).id) {
                  node_does_match = 0;
                  break;
                }
              } else {
                break;
              }
            }
          }
          if (!node_does_match) {
            if (!later_sibling_can_match) {
              ;
              capture_list_pool_release(
                &self->capture_list_pool,
                state->capture_list_id
              );
              _array__erase((Array *)(&self->states), (sizeof *(&self->states)->contents), j);
              j--;
            }
            continue;
          }
          if (later_sibling_can_match && (
            step->contains_captures ||
            ts_query__step_is_fallible(self->query, state->step_index)
          )) {
            if (ts_query_cursor__copy_state(self, &state)) {
              ;
              copy_count++;
            }
          }
          if (state->needs_parent) {
            TSNode parent = ts_tree_cursor_parent_node(&self->cursor);
            if (ts_node_is_null(parent)) {
              ;
              state->dead = 1;
            } else {
              state->needs_parent = 0;
              QueryStep *skipped_wildcard_step = step;
              do {
                skipped_wildcard_step--;
              } while (
                skipped_wildcard_step->is_dead_end ||
                skipped_wildcard_step->is_pass_through ||
                skipped_wildcard_step->depth > 0
              );
              if (skipped_wildcard_step->capture_ids[0] != NONE) {
                ;
                ts_query_cursor__capture(
                  self,
                  state,
                  skipped_wildcard_step,
                  parent
                );
              }
            }
          }
          if (step->capture_ids[0] != NONE) {
            ts_query_cursor__capture(self, state, step, node);
          }
          if (state->dead) {
            _array__erase((Array *)(&self->states), (sizeof *(&self->states)->contents), j);
            j--;
            continue;
          }
          state->step_index++;
          ;
          QueryStep *next_step = &self->query->steps.contents[state->step_index];
          if (step->symbol == WILDCARD_SYMBOL && !step->is_named && next_step->is_immediate) {
              state->seeking_immediate_match = 1;
          } else {
              state->seeking_immediate_match = 0;
          }
          if (stop_on_definite_step && next_step->root_pattern_guaranteed) did_match = 1;
          unsigned end_index = j + 1;
          for (unsigned k = j; k < end_index; k++) {
            QueryState *child_state = &self->states.contents[k];
            QueryStep *child_step = &self->query->steps.contents[child_state->step_index];
            if (child_step->alternative_index != NONE) {
              if (child_step->is_dead_end) {
                child_state->step_index = child_step->alternative_index;
                k--;
                continue;
              }
              if (child_step->is_pass_through) {
                child_state->step_index++;
                k--;
              }
              QueryState *copy = ts_query_cursor__copy_state(self, &child_state);
              if (copy) {
                ;
                end_index++;
                copy_count++;
                copy->step_index = child_step->alternative_index;
                if (child_step->alternative_is_immediate) {
                  copy->seeking_immediate_match = 1;
                }
              }
            }
          }
        }
        for (unsigned j = 0; j < self->states.size; j++) {
          QueryState *state = &self->states.contents[j];
          if (state->dead) {
            _array__erase((Array *)(&self->states), (sizeof *(&self->states)->contents), j);
            j--;
            continue;
          }
          _Bool did_remove = 0;
          for (unsigned k = j + 1; k < self->states.size; k++) {
            QueryState *other_state = &self->states.contents[k];
            if (
              other_state->start_depth != state->start_depth ||
              other_state->pattern_index != state->pattern_index
            ) break;
            _Bool left_contains_right, right_contains_left;
            ts_query_cursor__compare_captures(
              self,
              state,
              other_state,
              &left_contains_right,
              &right_contains_left
            );
            if (left_contains_right) {
              if (state->step_index == other_state->step_index) {
                ;
                capture_list_pool_release(&self->capture_list_pool, other_state->capture_list_id);
                _array__erase((Array *)(&self->states), (sizeof *(&self->states)->contents), k);
                k--;
                continue;
              }
              other_state->has_in_progress_alternatives = 1;
            }
            if (right_contains_left) {
              if (state->step_index == other_state->step_index) {
                ;
                capture_list_pool_release(&self->capture_list_pool, state->capture_list_id);
                _array__erase((Array *)(&self->states), (sizeof *(&self->states)->contents), j);
                j--;
                did_remove = 1;
                break;
              }
              state->has_in_progress_alternatives = 1;
            }
          }
          if (!did_remove) {
            ;
            QueryStep *next_step = &self->query->steps.contents[state->step_index];
            if (next_step->depth == PATTERN_DONE_MARKER) {
              if (state->has_in_progress_alternatives) {
                ;
              } else {
                ;
                (_array__grow((Array *)(&self->finished_states), 1, (sizeof *(&self->finished_states)->contents)), (&self->finished_states)->contents[(&self->finished_states)->size++] = (*state));
                _array__erase((Array *)(&self->states), (sizeof *(&self->states)->contents), (uint32_t)(state - self->states.contents));
                did_match = 1;
                j--;
              }
            }
          }
        }
      }
      if (ts_query_cursor__should_descend(self, node_intersects_range)) {
        switch (ts_tree_cursor_goto_first_child_internal(&self->cursor)) {
          case TreeCursorStepVisible:
            self->depth++;
            self->on_visible_node = 1;
            continue;
          case TreeCursorStepHidden:
            self->on_visible_node = 0;
            continue;
          default:
            break;
        }
      }
      self->ascending = 1;
    }
  }
}
_Bool ts_query_cursor_next_match(
  TSQueryCursor *self,
  TSQueryMatch *match
) {
  if (self->finished_states.size == 0) {
    if (!ts_query_cursor__advance(self, 0)) {
      return 0;
    }
  }
  QueryState *state = &self->finished_states.contents[0];
  if (state->id == 4294967295U) state->id = self->next_state_id++;
  match->id = state->id;
  match->pattern_index = state->pattern_index;
  const CaptureList *captures = capture_list_pool_get(
    &self->capture_list_pool,
    state->capture_list_id
  );
  match->captures = captures->contents;
  match->capture_count = captures->size;
  capture_list_pool_release(&self->capture_list_pool, state->capture_list_id);
  _array__erase((Array *)(&self->finished_states), (sizeof *(&self->finished_states)->contents), 0);
  return 1;
}
void ts_query_cursor_remove_match(
  TSQueryCursor *self,
  uint32_t match_id
) {
  for (unsigned i = 0; i < self->finished_states.size; i++) {
    const QueryState *state = &self->finished_states.contents[i];
    if (state->id == match_id) {
      capture_list_pool_release(
        &self->capture_list_pool,
        state->capture_list_id
      );
      _array__erase((Array *)(&self->finished_states), (sizeof *(&self->finished_states)->contents), i);
      return;
    }
  }
  for (unsigned i = 0; i < self->states.size; i++) {
    const QueryState *state = &self->states.contents[i];
    if (state->id == match_id) {
      capture_list_pool_release(
        &self->capture_list_pool,
        state->capture_list_id
      );
      _array__erase((Array *)(&self->states), (sizeof *(&self->states)->contents), i);
      return;
    }
  }
}
_Bool ts_query_cursor_next_capture(
  TSQueryCursor *self,
  TSQueryMatch *match,
  uint32_t *capture_index
) {
  for (;;) {
    uint32_t first_unfinished_capture_byte;
    uint32_t first_unfinished_pattern_index;
    uint32_t first_unfinished_state_index;
    _Bool first_unfinished_state_is_definite = 0;
    _Bool found_unfinished_state = ts_query_cursor__first_in_progress_capture(
      self,
      &first_unfinished_state_index,
      &first_unfinished_capture_byte,
      &first_unfinished_pattern_index,
      &first_unfinished_state_is_definite
    );
    QueryState *first_finished_state = ((void *)0);
    uint32_t first_finished_capture_byte = first_unfinished_capture_byte;
    uint32_t first_finished_pattern_index = first_unfinished_pattern_index;
    for (unsigned i = 0; i < self->finished_states.size;) {
      QueryState *state = &self->finished_states.contents[i];
      const CaptureList *captures = capture_list_pool_get(
        &self->capture_list_pool,
        state->capture_list_id
      );
      if (state->consumed_capture_count >= captures->size) {
        capture_list_pool_release(
          &self->capture_list_pool,
          state->capture_list_id
        );
        _array__erase((Array *)(&self->finished_states), (sizeof *(&self->finished_states)->contents), i);
        continue;
      }
      TSNode node = captures->contents[state->consumed_capture_count].node;
      _Bool node_precedes_range = (
        ts_node_end_byte(node) <= self->start_byte ||
        point_lte(ts_node_end_point(node), self->start_point)
      );
      _Bool node_follows_range = (
        ts_node_start_byte(node) >= self->end_byte ||
        point_gte(ts_node_start_point(node), self->end_point)
      );
      _Bool node_outside_of_range = node_precedes_range || node_follows_range;
      if (node_outside_of_range) {
        state->consumed_capture_count++;
        continue;
      }
      uint32_t node_start_byte = ts_node_start_byte(node);
      if (
        node_start_byte < first_finished_capture_byte ||
        (
          node_start_byte == first_finished_capture_byte &&
          state->pattern_index < first_finished_pattern_index
        )
      ) {
        first_finished_state = state;
        first_finished_capture_byte = node_start_byte;
        first_finished_pattern_index = state->pattern_index;
      }
      i++;
    }
    QueryState *state;
    if (first_finished_state) {
      state = first_finished_state;
    } else if (first_unfinished_state_is_definite) {
      state = &self->states.contents[first_unfinished_state_index];
    } else {
      state = ((void *)0);
    }
    if (state) {
      if (state->id == 4294967295U) state->id = self->next_state_id++;
      match->id = state->id;
      match->pattern_index = state->pattern_index;
      const CaptureList *captures = capture_list_pool_get(
        &self->capture_list_pool,
        state->capture_list_id
      );
      match->captures = captures->contents;
      match->capture_count = captures->size;
      *capture_index = state->consumed_capture_count;
      state->consumed_capture_count++;
      return 1;
    }
    if (capture_list_pool_is_empty(&self->capture_list_pool) && found_unfinished_state) {
      ;
      capture_list_pool_release(
        &self->capture_list_pool,
        self->states.contents[first_unfinished_state_index].capture_list_id
      );
      _array__erase((Array *)(&self->states), (sizeof *(&self->states)->contents), first_unfinished_state_index);
    }
    if (
      !ts_query_cursor__advance(self, 1) &&
      self->finished_states.size == 0
    ) return 0;
  }
}
void ts_query_cursor_set_max_start_depth(
  TSQueryCursor *self,
  uint32_t max_start_depth
) {
  self->max_start_depth = max_start_depth;
}
typedef struct StackNode StackNode;
typedef struct {
  StackNode *node;
  Subtree subtree;
  _Bool is_pending;
} StackLink;
struct StackNode {
  TSStateId state;
  Length position;
  StackLink links[8];
  short unsigned int link_count;
  uint32_t ref_count;
  unsigned error_cost;
  unsigned node_count;
  int dynamic_precedence;
};
typedef struct {
  StackNode *node;
  SubtreeArray subtrees;
  uint32_t subtree_count;
  _Bool is_pending;
} StackIterator;
typedef struct { StackNode * *contents; uint32_t size; uint32_t capacity; } StackNodeArray;
typedef enum {
  StackStatusActive,
  StackStatusPaused,
  StackStatusHalted,
} StackStatus;
typedef struct {
  StackNode *node;
  StackSummary *summary;
  unsigned node_count_at_last_error;
  Subtree last_external_token;
  Subtree lookahead_when_paused;
  StackStatus status;
} StackHead;
struct Stack {
  struct { StackHead *contents; uint32_t size; uint32_t capacity; } heads;
  StackSliceArray slices;
  struct { StackIterator *contents; uint32_t size; uint32_t capacity; } iterators;
  StackNodeArray node_pool;
  StackNode *base_node;
  SubtreePool *subtree_pool;
};
typedef unsigned StackAction;
enum {
  StackActionNone,
  StackActionStop = 1,
  StackActionPop = 2,
};
typedef StackAction (*StackCallback)(void *, const StackIterator *);
static void stack_node_retain(StackNode *self) {
  if (!self)
    return;
  (__builtin_expect(!(self->ref_count > 0), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 85, "self->ref_count > 0") : (void)0);
  self->ref_count++;
  (__builtin_expect(!(self->ref_count != 0), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 87, "self->ref_count != 0") : (void)0);
}
static void stack_node_release(
  StackNode *self,
  StackNodeArray *pool,
  SubtreePool *subtree_pool
) {
recur:
  (__builtin_expect(!(self->ref_count != 0), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 96, "self->ref_count != 0") : (void)0);
  self->ref_count--;
  if (self->ref_count > 0) return;
  StackNode *first_predecessor = ((void *)0);
  if (self->link_count > 0) {
    for (unsigned i = self->link_count - 1; i > 0; i--) {
      StackLink link = self->links[i];
      if (link.subtree.ptr) ts_subtree_release(subtree_pool, link.subtree);
      stack_node_release(link.node, pool, subtree_pool);
    }
    StackLink link = self->links[0];
    if (link.subtree.ptr) ts_subtree_release(subtree_pool, link.subtree);
    first_predecessor = self->links[0].node;
  }
  if (pool->size < 50) {
    (_array__grow((Array *)(pool), 1, (sizeof *(pool)->contents)), (pool)->contents[(pool)->size++] = (self));
  } else {
    ts_current_free(self);
  }
  if (first_predecessor) {
    self = first_predecessor;
    goto recur;
  }
}
static uint32_t stack__subtree_node_count(Subtree subtree) {
  uint32_t count = ts_subtree_visible_descendant_count(subtree);
  if (ts_subtree_visible(subtree)) count++;
  if (ts_subtree_symbol(subtree) == (((TSSymbol)-1) - 1)) count++;
  return count;
}
static StackNode *stack_node_new(
  StackNode *previous_node,
  Subtree subtree,
  _Bool is_pending,
  TSStateId state,
  StackNodeArray *pool
) {
  StackNode *node = pool->size > 0
    ? ((pool)->contents[--(pool)->size])
    : ts_current_malloc(sizeof(StackNode));
  *node = (StackNode) {
    .ref_count = 1,
    .link_count = 0,
    .state = state
  };
  if (previous_node) {
    node->link_count = 1;
    node->links[0] = (StackLink) {
      .node = previous_node,
      .subtree = subtree,
      .is_pending = is_pending,
    };
    node->position = previous_node->position;
    node->error_cost = previous_node->error_cost;
    node->dynamic_precedence = previous_node->dynamic_precedence;
    node->node_count = previous_node->node_count;
    if (subtree.ptr) {
      node->error_cost += ts_subtree_error_cost(subtree);
      node->position = length_add(node->position, ts_subtree_total_size(subtree));
      node->node_count += stack__subtree_node_count(subtree);
      node->dynamic_precedence += ts_subtree_dynamic_precedence(subtree);
    }
  } else {
    node->position = length_zero();
    node->error_cost = 0;
  }
  return node;
}
static _Bool stack__subtree_is_equivalent(Subtree left, Subtree right) {
  if (left.ptr == right.ptr) return 1;
  if (!left.ptr || !right.ptr) return 0;
  if (ts_subtree_symbol(left) != ts_subtree_symbol(right)) return 0;
  if (ts_subtree_error_cost(left) > 0 && ts_subtree_error_cost(right) > 0) return 1;
  return (
    ts_subtree_padding(left).bytes == ts_subtree_padding(right).bytes &&
    ts_subtree_size(left).bytes == ts_subtree_size(right).bytes &&
    ts_subtree_child_count(left) == ts_subtree_child_count(right) &&
    ts_subtree_extra(left) == ts_subtree_extra(right) &&
    ts_subtree_external_scanner_state_eq(left, right)
  );
}
static void stack_node_add_link(
  StackNode *self,
  StackLink link,
  SubtreePool *subtree_pool
) {
  if (link.node == self) return;
  for (int i = 0; i < self->link_count; i++) {
    StackLink *existing_link = &self->links[i];
    if (stack__subtree_is_equivalent(existing_link->subtree, link.subtree)) {
      if (existing_link->node == link.node) {
        if (
          ts_subtree_dynamic_precedence(link.subtree) >
          ts_subtree_dynamic_precedence(existing_link->subtree)
        ) {
          ts_subtree_retain(link.subtree);
          ts_subtree_release(subtree_pool, existing_link->subtree);
          existing_link->subtree = link.subtree;
          self->dynamic_precedence =
            link.node->dynamic_precedence + ts_subtree_dynamic_precedence(link.subtree);
        }
        return;
      }
      if (
        existing_link->node->state == link.node->state &&
        existing_link->node->position.bytes == link.node->position.bytes &&
        existing_link->node->error_cost == link.node->error_cost
      ) {
        for (int j = 0; j < link.node->link_count; j++) {
          stack_node_add_link(existing_link->node, link.node->links[j], subtree_pool);
        }
        int32_t dynamic_precedence = link.node->dynamic_precedence;
        if (link.subtree.ptr) {
          dynamic_precedence += ts_subtree_dynamic_precedence(link.subtree);
        }
        if (dynamic_precedence > self->dynamic_precedence) {
          self->dynamic_precedence = dynamic_precedence;
        }
        return;
      }
    }
  }
  if (self->link_count == 8) return;
  stack_node_retain(link.node);
  unsigned node_count = link.node->node_count;
  int dynamic_precedence = link.node->dynamic_precedence;
  self->links[self->link_count++] = link;
  if (link.subtree.ptr) {
    ts_subtree_retain(link.subtree);
    node_count += stack__subtree_node_count(link.subtree);
    dynamic_precedence += ts_subtree_dynamic_precedence(link.subtree);
  }
  if (node_count > self->node_count) self->node_count = node_count;
  if (dynamic_precedence > self->dynamic_precedence) self->dynamic_precedence = dynamic_precedence;
}
static void stack_head_delete(
  StackHead *self,
  StackNodeArray *pool,
  SubtreePool *subtree_pool
) {
  if (self->node) {
    if (self->last_external_token.ptr) {
      ts_subtree_release(subtree_pool, self->last_external_token);
    }
    if (self->lookahead_when_paused.ptr) {
      ts_subtree_release(subtree_pool, self->lookahead_when_paused);
    }
    if (self->summary) {
      _array__delete((Array *)(self->summary));
      ts_current_free(self->summary);
    }
    stack_node_release(self->node, pool, subtree_pool);
  }
}
static StackVersion ts_stack__add_version(
  Stack *self,
  StackVersion original_version,
  StackNode *node
) {
  StackHead head = {
    .node = node,
    .node_count_at_last_error = self->heads.contents[original_version].node_count_at_last_error,
    .last_external_token = self->heads.contents[original_version].last_external_token,
    .status = StackStatusActive,
    .lookahead_when_paused = ((Subtree) {.ptr = ((void *)0)}),
  };
  (_array__grow((Array *)(&self->heads), 1, (sizeof *(&self->heads)->contents)), (&self->heads)->contents[(&self->heads)->size++] = (head));
  stack_node_retain(node);
  if (head.last_external_token.ptr) ts_subtree_retain(head.last_external_token);
  return (StackVersion)(self->heads.size - 1);
}
static void ts_stack__add_slice(
  Stack *self,
  StackVersion original_version,
  StackNode *node,
  SubtreeArray *subtrees
) {
  for (uint32_t i = self->slices.size - 1; i + 1 > 0; i--) {
    StackVersion version = self->slices.contents[i].version;
    if (self->heads.contents[version].node == node) {
      StackSlice slice = {*subtrees, version};
      _array__splice((Array *)(&self->slices), (sizeof *(&self->slices)->contents), i + 1, 0, 1, &(slice));
      return;
    }
  }
  StackVersion version = ts_stack__add_version(self, original_version, node);
  StackSlice slice = { *subtrees, version };
  (_array__grow((Array *)(&self->slices), 1, (sizeof *(&self->slices)->contents)), (&self->slices)->contents[(&self->slices)->size++] = (slice));
}
static StackSliceArray stack__iter(
  Stack *self,
  StackVersion version,
  StackCallback callback,
  void *payload,
  int goal_subtree_count
) {
  ((&self->slices)->size = 0);
  ((&self->iterators)->size = 0);
  StackHead *head = ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 334, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version]);
  StackIterator new_iterator = {
    .node = head->node,
    .subtrees = { ((void *)0), 0, 0 },
    .subtree_count = 0,
    .is_pending = 1,
  };
  _Bool include_subtrees = 0;
  if (goal_subtree_count >= 0) {
    include_subtrees = 1;
    _array__reserve((Array *)(&new_iterator.subtrees), (sizeof *(&new_iterator.subtrees)->contents), (uint32_t)ts_subtree_alloc_size(goal_subtree_count) / sizeof(Subtree));
  }
  (_array__grow((Array *)(&self->iterators), 1, (sizeof *(&self->iterators)->contents)), (&self->iterators)->contents[(&self->iterators)->size++] = (new_iterator));
  while (self->iterators.size > 0) {
    for (uint32_t i = 0, size = self->iterators.size; i < size; i++) {
      StackIterator *iterator = &self->iterators.contents[i];
      StackNode *node = iterator->node;
      StackAction action = callback(payload, iterator);
      _Bool should_pop = action & StackActionPop;
      _Bool should_stop = action & StackActionStop || node->link_count == 0;
      if (should_pop) {
        SubtreeArray subtrees = iterator->subtrees;
        if (!should_stop) {
          ts_subtree_array_copy(subtrees, &subtrees);
        }
        ts_subtree_array_reverse(&subtrees);
        ts_stack__add_slice(
          self,
          version,
          node,
          &subtrees
        );
      }
      if (should_stop) {
        if (!should_pop) {
          ts_subtree_array_delete(self->subtree_pool, &iterator->subtrees);
        }
        _array__erase((Array *)(&self->iterators), (sizeof *(&self->iterators)->contents), i);
        i--, size--;
        continue;
      }
      for (uint32_t j = 1; j <= node->link_count; j++) {
        StackIterator *next_iterator;
        StackLink link;
        if (j == node->link_count) {
          link = node->links[0];
          next_iterator = &self->iterators.contents[i];
        } else {
          if (self->iterators.size >= 64) continue;
          link = node->links[j];
          StackIterator current_iterator = self->iterators.contents[i];
          (_array__grow((Array *)(&self->iterators), 1, (sizeof *(&self->iterators)->contents)), (&self->iterators)->contents[(&self->iterators)->size++] = (current_iterator));
          next_iterator = ((__builtin_expect(!((uint32_t)((&self->iterators)->size - 1) < (&self->iterators)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 393, "(uint32_t)((&self->iterators)->size - 1) < (&self->iterators)->size") : (void)0), &(&self->iterators)->contents[(&self->iterators)->size - 1]);
          ts_subtree_array_copy(next_iterator->subtrees, &next_iterator->subtrees);
        }
        next_iterator->node = link.node;
        if (link.subtree.ptr) {
          if (include_subtrees) {
            (_array__grow((Array *)(&next_iterator->subtrees), 1, (sizeof *(&next_iterator->subtrees)->contents)), (&next_iterator->subtrees)->contents[(&next_iterator->subtrees)->size++] = (link.subtree));
            ts_subtree_retain(link.subtree);
          }
          if (!ts_subtree_extra(link.subtree)) {
            next_iterator->subtree_count++;
            if (!link.is_pending) {
              next_iterator->is_pending = 0;
            }
          }
        } else {
          next_iterator->subtree_count++;
          next_iterator->is_pending = 0;
        }
      }
    }
  }
  return self->slices;
}
Stack *ts_stack_new(SubtreePool *subtree_pool) {
  Stack *self = ts_current_calloc(1, sizeof(Stack));
  ((&self->heads)->size = 0, (&self->heads)->capacity = 0, (&self->heads)->contents = ((void *)0));
  ((&self->slices)->size = 0, (&self->slices)->capacity = 0, (&self->slices)->contents = ((void *)0));
  ((&self->iterators)->size = 0, (&self->iterators)->capacity = 0, (&self->iterators)->contents = ((void *)0));
  ((&self->node_pool)->size = 0, (&self->node_pool)->capacity = 0, (&self->node_pool)->contents = ((void *)0));
  _array__reserve((Array *)(&self->heads), (sizeof *(&self->heads)->contents), 4);
  _array__reserve((Array *)(&self->slices), (sizeof *(&self->slices)->contents), 4);
  _array__reserve((Array *)(&self->iterators), (sizeof *(&self->iterators)->contents), 4);
  _array__reserve((Array *)(&self->node_pool), (sizeof *(&self->node_pool)->contents), 50);
  self->subtree_pool = subtree_pool;
  self->base_node = stack_node_new(((void *)0), ((Subtree) {.ptr = ((void *)0)}), 0, 1, &self->node_pool);
  ts_stack_clear(self);
  return self;
}
void ts_stack_delete(Stack *self) {
  if (self->slices.contents)
    _array__delete((Array *)(&self->slices));
  if (self->iterators.contents)
    _array__delete((Array *)(&self->iterators));
  stack_node_release(self->base_node, &self->node_pool, self->subtree_pool);
  for (uint32_t i = 0; i < self->heads.size; i++) {
    stack_head_delete(&self->heads.contents[i], &self->node_pool, self->subtree_pool);
  }
  ((&self->heads)->size = 0);
  if (self->node_pool.contents) {
    for (uint32_t i = 0; i < self->node_pool.size; i++)
      ts_current_free(self->node_pool.contents[i]);
    _array__delete((Array *)(&self->node_pool));
  }
  _array__delete((Array *)(&self->heads));
  ts_current_free(self);
}
uint32_t ts_stack_version_count(const Stack *self) {
  return self->heads.size;
}
TSStateId ts_stack_state(const Stack *self, StackVersion version) {
  return ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 464, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version])->node->state;
}
Length ts_stack_position(const Stack *self, StackVersion version) {
  return ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 468, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version])->node->position;
}
Subtree ts_stack_last_external_token(const Stack *self, StackVersion version) {
  return ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 472, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version])->last_external_token;
}
void ts_stack_set_last_external_token(Stack *self, StackVersion version, Subtree token) {
  StackHead *head = ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 476, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version]);
  if (token.ptr) ts_subtree_retain(token);
  if (head->last_external_token.ptr) ts_subtree_release(self->subtree_pool, head->last_external_token);
  head->last_external_token = token;
}
unsigned ts_stack_error_cost(const Stack *self, StackVersion version) {
  StackHead *head = ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 483, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version]);
  unsigned result = head->node->error_cost;
  if (
    head->status == StackStatusPaused ||
    (head->node->state == 0 && !head->node->links[0].subtree.ptr)) {
    result += 500;
  }
  return result;
}
unsigned ts_stack_node_count_since_error(const Stack *self, StackVersion version) {
  StackHead *head = ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 494, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version]);
  if (head->node->node_count < head->node_count_at_last_error) {
    head->node_count_at_last_error = head->node->node_count;
  }
  return head->node->node_count - head->node_count_at_last_error;
}
void ts_stack_push(
  Stack *self,
  StackVersion version,
  Subtree subtree,
  _Bool pending,
  TSStateId state
) {
  StackHead *head = ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 508, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version]);
  StackNode *new_node = stack_node_new(head->node, subtree, pending, state, &self->node_pool);
  if (!subtree.ptr) head->node_count_at_last_error = new_node->node_count;
  head->node = new_node;
}
static inline __attribute__((always_inline)) StackAction pop_count_callback(void *payload, const StackIterator *iterator) {
  unsigned *goal_subtree_count = payload;
  if (iterator->subtree_count == *goal_subtree_count) {
    return StackActionPop | StackActionStop;
  } else {
    return StackActionNone;
  }
}
StackSliceArray ts_stack_pop_count(Stack *self, StackVersion version, uint32_t count) {
  return stack__iter(self, version, pop_count_callback, &count, (int)count);
}
static inline __attribute__((always_inline)) StackAction pop_pending_callback(void *payload, const StackIterator *iterator) {
  (void)payload;
  if (iterator->subtree_count >= 1) {
    if (iterator->is_pending) {
      return StackActionPop | StackActionStop;
    } else {
      return StackActionStop;
    }
  } else {
    return StackActionNone;
  }
}
StackSliceArray ts_stack_pop_pending(Stack *self, StackVersion version) {
  StackSliceArray pop = stack__iter(self, version, pop_pending_callback, ((void *)0), 0);
  if (pop.size > 0) {
    ts_stack_renumber_version(self, pop.contents[0].version, version);
    pop.contents[0].version = version;
  }
  return pop;
}
static inline __attribute__((always_inline)) StackAction pop_error_callback(void *payload, const StackIterator *iterator) {
  if (iterator->subtrees.size > 0) {
    _Bool *found_error = payload;
    if (!*found_error && ts_subtree_is_error(iterator->subtrees.contents[0])) {
      *found_error = 1;
      return StackActionPop | StackActionStop;
    } else {
      return StackActionStop;
    }
  } else {
    return StackActionNone;
  }
}
SubtreeArray ts_stack_pop_error(Stack *self, StackVersion version) {
  StackNode *node = ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 564, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version])->node;
  for (unsigned i = 0; i < node->link_count; i++) {
    if (node->links[i].subtree.ptr && ts_subtree_is_error(node->links[i].subtree)) {
      _Bool found_error = 0;
      StackSliceArray pop = stack__iter(self, version, pop_error_callback, &found_error, 1);
      if (pop.size > 0) {
        (__builtin_expect(!(pop.size == 1), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 570, "pop.size == 1") : (void)0);
        ts_stack_renumber_version(self, pop.contents[0].version, version);
        return pop.contents[0].subtrees;
      }
      break;
    }
  }
  return (SubtreeArray) {.size = 0};
}
static inline __attribute__((always_inline)) StackAction pop_all_callback(void *payload, const StackIterator *iterator) {
  (void)payload;
  return iterator->node->link_count == 0 ? StackActionPop : StackActionNone;
}
StackSliceArray ts_stack_pop_all(Stack *self, StackVersion version) {
  return stack__iter(self, version, pop_all_callback, ((void *)0), 0);
}
typedef struct {
  StackSummary *summary;
  unsigned max_depth;
} SummarizeStackSession;
static inline __attribute__((always_inline)) StackAction summarize_stack_callback(void *payload, const StackIterator *iterator) {
  SummarizeStackSession *session = payload;
  TSStateId state = iterator->node->state;
  unsigned depth = iterator->subtree_count;
  if (depth > session->max_depth) return StackActionStop;
  for (unsigned i = session->summary->size - 1; i + 1 > 0; i--) {
    StackSummaryEntry entry = session->summary->contents[i];
    if (entry.depth < depth) break;
    if (entry.depth == depth && entry.state == state) return StackActionNone;
  }
  (_array__grow((Array *)(session->summary), 1, (sizeof *(session->summary)->contents)), (session->summary)->contents[(session->summary)->size++] = (((StackSummaryEntry) { .position = iterator->node->position, .depth = depth, .state = state, })));
  return StackActionNone;
}
void ts_stack_record_summary(Stack *self, StackVersion version, unsigned max_depth) {
  SummarizeStackSession session = {
    .summary = ts_current_malloc(sizeof(StackSummary)),
    .max_depth = max_depth
  };
  ((session.summary)->size = 0, (session.summary)->capacity = 0, (session.summary)->contents = ((void *)0));
  stack__iter(self, version, summarize_stack_callback, &session, -1);
  StackHead *head = &self->heads.contents[version];
  if (head->summary) {
    _array__delete((Array *)(head->summary));
    ts_current_free(head->summary);
  }
  head->summary = session.summary;
}
StackSummary *ts_stack_get_summary(Stack *self, StackVersion version) {
  return ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 628, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version])->summary;
}
int ts_stack_dynamic_precedence(Stack *self, StackVersion version) {
  return ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 632, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version])->node->dynamic_precedence;
}
_Bool ts_stack_has_advanced_since_error(const Stack *self, StackVersion version) {
  const StackHead *head = ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 636, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version]);
  const StackNode *node = head->node;
  if (node->error_cost == 0) return 1;
  while (node) {
    if (node->link_count > 0) {
      Subtree subtree = node->links[0].subtree;
      if (subtree.ptr) {
        if (ts_subtree_total_bytes(subtree) > 0) {
          return 1;
        } else if (
          node->node_count > head->node_count_at_last_error &&
          ts_subtree_error_cost(subtree) == 0
        ) {
          node = node->links[0].node;
          continue;
        }
      }
    }
    break;
  }
  return 0;
}
void ts_stack_remove_version(Stack *self, StackVersion version) {
  stack_head_delete(((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 660, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version]), &self->node_pool, self->subtree_pool);
  _array__erase((Array *)(&self->heads), (sizeof *(&self->heads)->contents), version);
}
void ts_stack_renumber_version(Stack *self, StackVersion v1, StackVersion v2) {
  if (v1 == v2) return;
  (__builtin_expect(!(v2 < v1), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 666, "v2 < v1") : (void)0);
  (__builtin_expect(!((uint32_t)v1 < self->heads.size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 667, "(uint32_t)v1 < self->heads.size") : (void)0);
  StackHead *source_head = &self->heads.contents[v1];
  StackHead *target_head = &self->heads.contents[v2];
  if (target_head->summary && !source_head->summary) {
    source_head->summary = target_head->summary;
    target_head->summary = ((void *)0);
  }
  stack_head_delete(target_head, &self->node_pool, self->subtree_pool);
  *target_head = *source_head;
  _array__erase((Array *)(&self->heads), (sizeof *(&self->heads)->contents), v1);
}
void ts_stack_swap_versions(Stack *self, StackVersion v1, StackVersion v2) {
  StackHead temporary_head = self->heads.contents[v1];
  self->heads.contents[v1] = self->heads.contents[v2];
  self->heads.contents[v2] = temporary_head;
}
StackVersion ts_stack_copy_version(Stack *self, StackVersion version) {
  (__builtin_expect(!(version < self->heads.size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 686, "version < self->heads.size") : (void)0);
  (_array__grow((Array *)(&self->heads), 1, (sizeof *(&self->heads)->contents)), (&self->heads)->contents[(&self->heads)->size++] = (self->heads.contents[version]));
  StackHead *head = ((__builtin_expect(!((uint32_t)((&self->heads)->size - 1) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 688, "(uint32_t)((&self->heads)->size - 1) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[(&self->heads)->size - 1]);
  stack_node_retain(head->node);
  if (head->last_external_token.ptr) ts_subtree_retain(head->last_external_token);
  head->summary = ((void *)0);
  return self->heads.size - 1;
}
_Bool ts_stack_merge(Stack *self, StackVersion version1, StackVersion version2) {
  if (!ts_stack_can_merge(self, version1, version2)) return 0;
  StackHead *head1 = &self->heads.contents[version1];
  StackHead *head2 = &self->heads.contents[version2];
  for (uint32_t i = 0; i < head2->node->link_count; i++) {
    stack_node_add_link(head1->node, head2->node->links[i], self->subtree_pool);
  }
  if (head1->node->state == 0) {
    head1->node_count_at_last_error = head1->node->node_count;
  }
  ts_stack_remove_version(self, version2);
  return 1;
}
_Bool ts_stack_can_merge(Stack *self, StackVersion version1, StackVersion version2) {
  StackHead *head1 = &self->heads.contents[version1];
  StackHead *head2 = &self->heads.contents[version2];
  return
    head1->status == StackStatusActive &&
    head2->status == StackStatusActive &&
    head1->node->state == head2->node->state &&
    head1->node->position.bytes == head2->node->position.bytes &&
    head1->node->error_cost == head2->node->error_cost &&
    ts_subtree_external_scanner_state_eq(head1->last_external_token, head2->last_external_token);
}
void ts_stack_halt(Stack *self, StackVersion version) {
  ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 722, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version])->status = StackStatusHalted;
}
void ts_stack_pause(Stack *self, StackVersion version, Subtree lookahead) {
  StackHead *head = ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 726, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version]);
  head->status = StackStatusPaused;
  head->lookahead_when_paused = lookahead;
  head->node_count_at_last_error = head->node->node_count;
}
_Bool ts_stack_is_active(const Stack *self, StackVersion version) {
  return ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 733, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version])->status == StackStatusActive;
}
_Bool ts_stack_is_halted(const Stack *self, StackVersion version) {
  return ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 737, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version])->status == StackStatusHalted;
}
_Bool ts_stack_is_paused(const Stack *self, StackVersion version) {
  return ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 741, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version])->status == StackStatusPaused;
}
Subtree ts_stack_resume(Stack *self, StackVersion version) {
  StackHead *head = ((__builtin_expect(!((uint32_t)(version) < (&self->heads)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 745, "(uint32_t)(version) < (&self->heads)->size") : (void)0), &(&self->heads)->contents[version]);
  (__builtin_expect(!(head->status == StackStatusPaused), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 746, "head->status == StackStatusPaused") : (void)0);
  Subtree result = head->lookahead_when_paused;
  head->status = StackStatusActive;
  head->lookahead_when_paused = ((Subtree) {.ptr = ((void *)0)});
  return result;
}
void ts_stack_clear(Stack *self) {
  stack_node_retain(self->base_node);
  for (uint32_t i = 0; i < self->heads.size; i++) {
    stack_head_delete(&self->heads.contents[i], &self->node_pool, self->subtree_pool);
  }
  ((&self->heads)->size = 0);
  (_array__grow((Array *)(&self->heads), 1, (sizeof *(&self->heads)->contents)), (&self->heads)->contents[(&self->heads)->size++] = (((StackHead) { .node = self->base_node, .status = StackStatusActive, .last_external_token = ((Subtree) {.ptr = ((void *)0)}), .lookahead_when_paused = ((Subtree) {.ptr = ((void *)0)}), })));
}
_Bool ts_stack_print_dot_graph(Stack *self, const TSLanguage *language, FILE *f) {
  _array__reserve((Array *)(&self->iterators), (sizeof *(&self->iterators)->contents), 32);
  if (!f) f = __stderrp;
  fprintf(f, "digraph stack {\n");
  fprintf(f, "rankdir=\"RL\";\n");
  fprintf(f, "edge [arrowhead=none]\n");
  struct { StackNode * *contents; uint32_t size; uint32_t capacity; } visited_nodes = { ((void *)0), 0, 0 };
  ((&self->iterators)->size = 0);
  for (uint32_t i = 0; i < self->heads.size; i++) {
    StackHead *head = &self->heads.contents[i];
    if (head->status == StackStatusHalted) continue;
    fprintf(f, "node_head_%u [shape=none, label=\"\"]\n", i);
    fprintf(f, "node_head_%u -> node_%p [", i, (void *)head->node);
    if (head->status == StackStatusPaused) {
      fprintf(f, "color=red ");
    }
    fprintf(f,
      "label=%u, fontcolor=blue, weight=10000, labeltooltip=\"node_count: %u\nerror_cost: %u",
      i,
      ts_stack_node_count_since_error(self, i),
      ts_stack_error_cost(self, i)
    );
    if (head->summary) {
      fprintf(f, "\nsummary:");
      for (uint32_t j = 0; j < head->summary->size; j++) fprintf(f, " %u", head->summary->contents[j].state);
    }
    if (head->last_external_token.ptr) {
      const ExternalScannerState *state = &head->last_external_token.ptr->external_scanner_state;
      const char *data = ts_external_scanner_state_data(state);
      fprintf(f, "\nexternal_scanner_state:");
      for (uint32_t j = 0; j < state->length; j++) fprintf(f, " %2X", data[j]);
    }
    fprintf(f, "\"]\n");
    (_array__grow((Array *)(&self->iterators), 1, (sizeof *(&self->iterators)->contents)), (&self->iterators)->contents[(&self->iterators)->size++] = (((StackIterator) { .node = head->node })));
  }
  _Bool all_iterators_done = 0;
  while (!all_iterators_done) {
    all_iterators_done = 1;
    for (uint32_t i = 0; i < self->iterators.size; i++) {
      StackIterator iterator = self->iterators.contents[i];
      StackNode *node = iterator.node;
      for (uint32_t j = 0; j < visited_nodes.size; j++) {
        if (visited_nodes.contents[j] == node) {
          node = ((void *)0);
          break;
        }
      }
      if (!node) continue;
      all_iterators_done = 0;
      fprintf(f, "node_%p [", (void *)node);
      if (node->state == 0) {
        fprintf(f, "label=\"?\"");
      } else if (
        node->link_count == 1 &&
        node->links[0].subtree.ptr &&
        ts_subtree_extra(node->links[0].subtree)
      ) {
        fprintf(f, "shape=point margin=0 label=\"\"");
      } else {
        fprintf(f, "label=\"%d\"", node->state);
      }
      fprintf(
        f,
        " tooltip=\"position: %u,%u\nnode_count:%u\nerror_cost: %u\ndynamic_precedence: %d\"];\n",
        node->position.extent.row + 1,
        node->position.extent.column,
        node->node_count,
        node->error_cost,
        node->dynamic_precedence
      );
      for (int j = 0; j < node->link_count; j++) {
        StackLink link = node->links[j];
        fprintf(f, "node_%p -> node_%p [", (void *)node, (void *)link.node);
        if (link.is_pending) fprintf(f, "style=dashed ");
        if (link.subtree.ptr && ts_subtree_extra(link.subtree)) fprintf(f, "fontcolor=gray ");
        if (!link.subtree.ptr) {
          fprintf(f, "color=red");
        } else {
          fprintf(f, "label=\"");
          _Bool quoted = ts_subtree_visible(link.subtree) && !ts_subtree_named(link.subtree);
          if (quoted) fprintf(f, "'");
          ts_language_write_symbol_as_dot_string(language, f, ts_subtree_symbol(link.subtree));
          if (quoted) fprintf(f, "'");
          fprintf(f, "\"");
          fprintf(
            f,
            "labeltooltip=\"error_cost: %u\ndynamic_precedence: %" "d" "\"",
            ts_subtree_error_cost(link.subtree),
            ts_subtree_dynamic_precedence(link.subtree)
          );
        }
        fprintf(f, "];\n");
        StackIterator *next_iterator;
        if (j == 0) {
          next_iterator = &self->iterators.contents[i];
        } else {
          (_array__grow((Array *)(&self->iterators), 1, (sizeof *(&self->iterators)->contents)), (&self->iterators)->contents[(&self->iterators)->size++] = (iterator));
          next_iterator = ((__builtin_expect(!((uint32_t)((&self->iterators)->size - 1) < (&self->iterators)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./stack.c", 884, "(uint32_t)((&self->iterators)->size - 1) < (&self->iterators)->size") : (void)0), &(&self->iterators)->contents[(&self->iterators)->size - 1]);
        }
        next_iterator->node = link.node;
      }
      (_array__grow((Array *)(&visited_nodes), 1, (sizeof *(&visited_nodes)->contents)), (&visited_nodes)->contents[(&visited_nodes)->size++] = (node));
    }
  }
  fprintf(f, "}\n");
  _array__delete((Array *)(&visited_nodes));
  return 1;
}
typedef struct {
  Length start;
  Length old_end;
  Length new_end;
} Edit;
void ts_external_scanner_state_init(ExternalScannerState *self, const char *data, unsigned length) {
  self->length = length;
  if (length > sizeof(self->short_data)) {
    self->long_data = ts_current_malloc(length);
    memcpy(self->long_data, data, length);
  } else {
    memcpy(self->short_data, data, length);
  }
}
ExternalScannerState ts_external_scanner_state_copy(const ExternalScannerState *self) {
  ExternalScannerState result = *self;
  if (self->length > sizeof(self->short_data)) {
    result.long_data = ts_current_malloc(self->length);
    memcpy(result.long_data, self->long_data, self->length);
  }
  return result;
}
void ts_external_scanner_state_delete(ExternalScannerState *self) {
  if (self->length > sizeof(self->short_data)) {
    ts_current_free(self->long_data);
  }
}
const char *ts_external_scanner_state_data(const ExternalScannerState *self) {
  if (self->length > sizeof(self->short_data)) {
    return self->long_data;
  } else {
    return self->short_data;
  }
}
_Bool ts_external_scanner_state_eq(const ExternalScannerState *self, const char *buffer, unsigned length) {
  return
    self->length == length &&
    memcmp(ts_external_scanner_state_data(self), buffer, length) == 0;
}
void ts_subtree_array_copy(SubtreeArray self, SubtreeArray *dest) {
  dest->size = self.size;
  dest->capacity = self.capacity;
  dest->contents = self.contents;
  if (self.capacity > 0) {
    dest->contents = ts_current_calloc(self.capacity, sizeof(Subtree));
    memcpy(dest->contents, self.contents, self.size * sizeof(Subtree));
    for (uint32_t i = 0; i < self.size; i++) {
      ts_subtree_retain(dest->contents[i]);
    }
  }
}
void ts_subtree_array_clear(SubtreePool *pool, SubtreeArray *self) {
  for (uint32_t i = 0; i < self->size; i++) {
    ts_subtree_release(pool, self->contents[i]);
  }
  ((self)->size = 0);
}
void ts_subtree_array_delete(SubtreePool *pool, SubtreeArray *self) {
  ts_subtree_array_clear(pool, self);
  _array__delete((Array *)(self));
}
void ts_subtree_array_remove_trailing_extras(
  SubtreeArray *self,
  SubtreeArray *destination
) {
  ((destination)->size = 0);
  while (self->size > 0) {
    Subtree last = self->contents[self->size - 1];
    if (ts_subtree_extra(last)) {
      self->size--;
      (_array__grow((Array *)(destination), 1, (sizeof *(destination)->contents)), (destination)->contents[(destination)->size++] = (last));
    } else {
      break;
    }
  }
  ts_subtree_array_reverse(destination);
}
void ts_subtree_array_reverse(SubtreeArray *self) {
  for (uint32_t i = 0, limit = self->size / 2; i < limit; i++) {
    size_t reverse_index = self->size - 1 - i;
    Subtree swap = self->contents[i];
    self->contents[i] = self->contents[reverse_index];
    self->contents[reverse_index] = swap;
  }
}
SubtreePool ts_subtree_pool_new(uint32_t capacity) {
  SubtreePool self = {{ ((void *)0), 0, 0 }, { ((void *)0), 0, 0 }};
  _array__reserve((Array *)(&self.free_trees), (sizeof *(&self.free_trees)->contents), capacity);
  return self;
}
void ts_subtree_pool_delete(SubtreePool *self) {
  if (self->free_trees.contents) {
    for (unsigned i = 0; i < self->free_trees.size; i++) {
      ts_current_free(self->free_trees.contents[i].ptr);
    }
    _array__delete((Array *)(&self->free_trees));
  }
  if (self->tree_stack.contents) _array__delete((Array *)(&self->tree_stack));
}
static SubtreeHeapData *ts_subtree_pool_allocate(SubtreePool *self) {
  if (self->free_trees.size > 0) {
    return ((&self->free_trees)->contents[--(&self->free_trees)->size]).ptr;
  } else {
    return ts_current_malloc(sizeof(SubtreeHeapData));
  }
}
static void ts_subtree_pool_free(SubtreePool *self, SubtreeHeapData *tree) {
  if (self->free_trees.capacity > 0 && self->free_trees.size + 1 <= 32) {
    (_array__grow((Array *)(&self->free_trees), 1, (sizeof *(&self->free_trees)->contents)), (&self->free_trees)->contents[(&self->free_trees)->size++] = ((MutableSubtree) {.ptr = tree}));
  } else {
    ts_current_free(tree);
  }
}
static inline _Bool ts_subtree_can_inline(Length padding, Length size, uint32_t lookahead_bytes) {
  return
    padding.bytes < 255 &&
    padding.extent.row < 16 &&
    padding.extent.column < 255 &&
    size.bytes < 255 &&
    size.extent.row == 0 &&
    size.extent.column < 255 &&
    lookahead_bytes < 16;
}
Subtree ts_subtree_new_leaf(
  SubtreePool *pool, TSSymbol symbol, Length padding, Length size,
  uint32_t lookahead_bytes, TSStateId parse_state,
  _Bool has_external_tokens, _Bool depends_on_column,
  _Bool is_keyword, const TSLanguage *language
) {
  TSSymbolMetadata metadata = ts_language_symbol_metadata(language, symbol);
  _Bool extra = symbol == 0;
  _Bool is_inline = (
    symbol <= 255 &&
    !has_external_tokens &&
    ts_subtree_can_inline(padding, size, lookahead_bytes)
  );
  if (is_inline) {
    return (Subtree) {{
      .parse_state = parse_state,
      .symbol = symbol,
      .padding_bytes = padding.bytes,
      .padding_rows = padding.extent.row,
      .padding_columns = padding.extent.column,
      .size_bytes = size.bytes,
      .lookahead_bytes = lookahead_bytes,
      .visible = metadata.visible,
      .named = metadata.named,
      .extra = extra,
      .has_changes = 0,
      .is_missing = 0,
      .is_keyword = is_keyword,
      .is_inline = 1,
    }};
  } else {
    SubtreeHeapData *data = ts_subtree_pool_allocate(pool);
    *data = (SubtreeHeapData) {
      .ref_count = 1,
      .padding = padding,
      .size = size,
      .lookahead_bytes = lookahead_bytes,
      .error_cost = 0,
      .child_count = 0,
      .symbol = symbol,
      .parse_state = parse_state,
      .visible = metadata.visible,
      .named = metadata.named,
      .extra = extra,
      .fragile_left = 0,
      .fragile_right = 0,
      .has_changes = 0,
      .has_external_tokens = has_external_tokens,
      .has_external_scanner_state_change = 0,
      .depends_on_column = depends_on_column,
      .is_missing = 0,
      .is_keyword = is_keyword,
      {{.first_leaf = {.symbol = 0, .parse_state = 0}}}
    };
    return (Subtree) {.ptr = data};
  }
}
void ts_subtree_set_symbol(
  MutableSubtree *self,
  TSSymbol symbol,
  const TSLanguage *language
) {
  TSSymbolMetadata metadata = ts_language_symbol_metadata(language, symbol);
  if (self->data.is_inline) {
    (__builtin_expect(!(symbol < 255), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./subtree.c", 233, "symbol < 255") : (void)0);
    self->data.symbol = symbol;
    self->data.named = metadata.named;
    self->data.visible = metadata.visible;
  } else {
    self->ptr->symbol = symbol;
    self->ptr->named = metadata.named;
    self->ptr->visible = metadata.visible;
  }
}
Subtree ts_subtree_new_error(
  SubtreePool *pool, int32_t lookahead_char, Length padding, Length size,
  uint32_t bytes_scanned, TSStateId parse_state, const TSLanguage *language
) {
  Subtree result = ts_subtree_new_leaf(
    pool, ((TSSymbol)-1), padding, size, bytes_scanned,
    parse_state, 0, 0, 0, language
  );
  SubtreeHeapData *data = (SubtreeHeapData *)result.ptr;
  data->fragile_left = 1;
  data->fragile_right = 1;
  data->lookahead_char = lookahead_char;
  return result;
}
MutableSubtree ts_subtree_clone(Subtree self) {
  size_t alloc_size = ts_subtree_alloc_size(self.ptr->child_count);
  Subtree *new_children = ts_current_malloc(alloc_size);
  Subtree *old_children = ((self).data.is_inline ? ((void *)0) : (Subtree *)((self).ptr) - (self).ptr->child_count);
  memcpy(new_children, old_children, alloc_size);
  SubtreeHeapData *result = (SubtreeHeapData *)&new_children[self.ptr->child_count];
  if (self.ptr->child_count > 0) {
    for (uint32_t i = 0; i < self.ptr->child_count; i++) {
      ts_subtree_retain(new_children[i]);
    }
  } else if (self.ptr->has_external_tokens) {
    result->external_scanner_state = ts_external_scanner_state_copy(
      &self.ptr->external_scanner_state
    );
  }
  result->ref_count = 1;
  return (MutableSubtree) {.ptr = result};
}
MutableSubtree ts_subtree_make_mut(SubtreePool *pool, Subtree self) {
  if (self.data.is_inline) return (MutableSubtree) {self.data};
  if (self.ptr->ref_count == 1) return ts_subtree_to_mut_unsafe(self);
  MutableSubtree result = ts_subtree_clone(self);
  ts_subtree_release(pool, self);
  return result;
}
void ts_subtree_compress(
  MutableSubtree self,
  unsigned count,
  const TSLanguage *language,
  MutableSubtreeArray *stack
) {
  unsigned initial_stack_size = stack->size;
  MutableSubtree tree = self;
  TSSymbol symbol = tree.ptr->symbol;
  for (unsigned i = 0; i < count; i++) {
    if (tree.ptr->ref_count > 1 || tree.ptr->child_count < 2) break;
    MutableSubtree child = ts_subtree_to_mut_unsafe(((tree).data.is_inline ? ((void *)0) : (Subtree *)((tree).ptr) - (tree).ptr->child_count)[0]);
    if (
      child.data.is_inline ||
      child.ptr->child_count < 2 ||
      child.ptr->ref_count > 1 ||
      child.ptr->symbol != symbol
    ) break;
    MutableSubtree grandchild = ts_subtree_to_mut_unsafe(((child).data.is_inline ? ((void *)0) : (Subtree *)((child).ptr) - (child).ptr->child_count)[0]);
    if (
      grandchild.data.is_inline ||
      grandchild.ptr->child_count < 2 ||
      grandchild.ptr->ref_count > 1 ||
      grandchild.ptr->symbol != symbol
    ) break;
    ((tree).data.is_inline ? ((void *)0) : (Subtree *)((tree).ptr) - (tree).ptr->child_count)[0] = ts_subtree_from_mut(grandchild);
    ((child).data.is_inline ? ((void *)0) : (Subtree *)((child).ptr) - (child).ptr->child_count)[0] = ((grandchild).data.is_inline ? ((void *)0) : (Subtree *)((grandchild).ptr) - (grandchild).ptr->child_count)[grandchild.ptr->child_count - 1];
    ((grandchild).data.is_inline ? ((void *)0) : (Subtree *)((grandchild).ptr) - (grandchild).ptr->child_count)[grandchild.ptr->child_count - 1] = ts_subtree_from_mut(child);
    (_array__grow((Array *)(stack), 1, (sizeof *(stack)->contents)), (stack)->contents[(stack)->size++] = (tree));
    tree = grandchild;
  }
  while (stack->size > initial_stack_size) {
    tree = ((stack)->contents[--(stack)->size]);
    MutableSubtree child = ts_subtree_to_mut_unsafe(((tree).data.is_inline ? ((void *)0) : (Subtree *)((tree).ptr) - (tree).ptr->child_count)[0]);
    MutableSubtree grandchild = ts_subtree_to_mut_unsafe(((child).data.is_inline ? ((void *)0) : (Subtree *)((child).ptr) - (child).ptr->child_count)[child.ptr->child_count - 1]);
    ts_subtree_summarize_children(grandchild, language);
    ts_subtree_summarize_children(child, language);
    ts_subtree_summarize_children(tree, language);
  }
}
void ts_subtree_summarize_children(
  MutableSubtree self,
  const TSLanguage *language
) {
  (__builtin_expect(!(!self.data.is_inline), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./subtree.c", 343, "!self.data.is_inline") : (void)0);
  self.ptr->named_child_count = 0;
  self.ptr->visible_child_count = 0;
  self.ptr->error_cost = 0;
  self.ptr->repeat_depth = 0;
  self.ptr->visible_descendant_count = 0;
  self.ptr->has_external_tokens = 0;
  self.ptr->depends_on_column = 0;
  self.ptr->has_external_scanner_state_change = 0;
  self.ptr->dynamic_precedence = 0;
  uint32_t structural_index = 0;
  const TSSymbol *alias_sequence = ts_language_alias_sequence(language, self.ptr->production_id);
  uint32_t lookahead_end_byte = 0;
  const Subtree *children = ((self).data.is_inline ? ((void *)0) : (Subtree *)((self).ptr) - (self).ptr->child_count);
  for (uint32_t i = 0; i < self.ptr->child_count; i++) {
    Subtree child = children[i];
    if (
      self.ptr->size.extent.row == 0 &&
      ts_subtree_depends_on_column(child)
    ) {
      self.ptr->depends_on_column = 1;
    }
    if (ts_subtree_has_external_scanner_state_change(child)) {
      self.ptr->has_external_scanner_state_change = 1;
    }
    if (i == 0) {
      self.ptr->padding = ts_subtree_padding(child);
      self.ptr->size = ts_subtree_size(child);
    } else {
      self.ptr->size = length_add(self.ptr->size, ts_subtree_total_size(child));
    }
    uint32_t child_lookahead_end_byte =
      self.ptr->padding.bytes +
      self.ptr->size.bytes +
      ts_subtree_lookahead_bytes(child);
    if (child_lookahead_end_byte > lookahead_end_byte) {
      lookahead_end_byte = child_lookahead_end_byte;
    }
    if (ts_subtree_symbol(child) != (((TSSymbol)-1) - 1)) {
      self.ptr->error_cost += ts_subtree_error_cost(child);
    }
    uint32_t grandchild_count = ts_subtree_child_count(child);
    if (
      self.ptr->symbol == ((TSSymbol)-1) ||
      self.ptr->symbol == (((TSSymbol)-1) - 1)
    ) {
      if (!ts_subtree_extra(child) && !(ts_subtree_is_error(child) && grandchild_count == 0)) {
        if (ts_subtree_visible(child)) {
          self.ptr->error_cost += 100;
        } else if (grandchild_count > 0) {
          self.ptr->error_cost += 100 * child.ptr->visible_child_count;
        }
      }
    }
    self.ptr->dynamic_precedence += ts_subtree_dynamic_precedence(child);
    self.ptr->visible_descendant_count += ts_subtree_visible_descendant_count(child);
    if (alias_sequence && alias_sequence[structural_index] != 0 && !ts_subtree_extra(child)) {
      self.ptr->visible_descendant_count++;
      self.ptr->visible_child_count++;
      if (ts_language_symbol_metadata(language, alias_sequence[structural_index]).named) {
        self.ptr->named_child_count++;
      }
    } else if (ts_subtree_visible(child)) {
      self.ptr->visible_descendant_count++;
      self.ptr->visible_child_count++;
      if (ts_subtree_named(child)) self.ptr->named_child_count++;
    } else if (grandchild_count > 0) {
      self.ptr->visible_child_count += child.ptr->visible_child_count;
      self.ptr->named_child_count += child.ptr->named_child_count;
    }
    if (ts_subtree_has_external_tokens(child)) self.ptr->has_external_tokens = 1;
    if (ts_subtree_is_error(child)) {
      self.ptr->fragile_left = self.ptr->fragile_right = 1;
      self.ptr->parse_state = 65535;
    }
    if (!ts_subtree_extra(child)) structural_index++;
  }
  self.ptr->lookahead_bytes = lookahead_end_byte - self.ptr->size.bytes - self.ptr->padding.bytes;
  if (
    self.ptr->symbol == ((TSSymbol)-1) ||
    self.ptr->symbol == (((TSSymbol)-1) - 1)
  ) {
    self.ptr->error_cost +=
      500 +
      1 * self.ptr->size.bytes +
      30 * self.ptr->size.extent.row;
  }
  if (self.ptr->child_count > 0) {
    Subtree first_child = children[0];
    Subtree last_child = children[self.ptr->child_count - 1];
    self.ptr->first_leaf.symbol = ts_subtree_leaf_symbol(first_child);
    self.ptr->first_leaf.parse_state = ts_subtree_leaf_parse_state(first_child);
    if (ts_subtree_fragile_left(first_child)) self.ptr->fragile_left = 1;
    if (ts_subtree_fragile_right(last_child)) self.ptr->fragile_right = 1;
    if (
      self.ptr->child_count >= 2 &&
      !self.ptr->visible &&
      !self.ptr->named &&
      ts_subtree_symbol(first_child) == self.ptr->symbol
    ) {
      if (ts_subtree_repeat_depth(first_child) > ts_subtree_repeat_depth(last_child)) {
        self.ptr->repeat_depth = ts_subtree_repeat_depth(first_child) + 1;
      } else {
        self.ptr->repeat_depth = ts_subtree_repeat_depth(last_child) + 1;
      }
    }
  }
}
MutableSubtree ts_subtree_new_node(
  TSSymbol symbol,
  SubtreeArray *children,
  unsigned production_id,
  const TSLanguage *language
) {
  TSSymbolMetadata metadata = ts_language_symbol_metadata(language, symbol);
  _Bool fragile = symbol == ((TSSymbol)-1) || symbol == (((TSSymbol)-1) - 1);
  size_t new_byte_size = ts_subtree_alloc_size(children->size);
  if (children->capacity * sizeof(Subtree) < new_byte_size) {
    children->contents = ts_current_realloc(children->contents, new_byte_size);
    children->capacity = (uint32_t)(new_byte_size / sizeof(Subtree));
  }
  SubtreeHeapData *data = (SubtreeHeapData *)&children->contents[children->size];
  *data = (SubtreeHeapData) {
    .ref_count = 1,
    .symbol = symbol,
    .child_count = children->size,
    .visible = metadata.visible,
    .named = metadata.named,
    .has_changes = 0,
    .has_external_scanner_state_change = 0,
    .fragile_left = fragile,
    .fragile_right = fragile,
    .is_keyword = 0,
    {{
      .visible_descendant_count = 0,
      .production_id = production_id,
      .first_leaf = {.symbol = 0, .parse_state = 0},
    }}
  };
  MutableSubtree result = {.ptr = data};
  ts_subtree_summarize_children(result, language);
  return result;
}
Subtree ts_subtree_new_error_node(
  SubtreeArray *children,
  _Bool extra,
  const TSLanguage *language
) {
  MutableSubtree result = ts_subtree_new_node(
    ((TSSymbol)-1), children, 0, language
  );
  result.ptr->extra = extra;
  return ts_subtree_from_mut(result);
}
Subtree ts_subtree_new_missing_leaf(
  SubtreePool *pool,
  TSSymbol symbol,
  Length padding,
  uint32_t lookahead_bytes,
  const TSLanguage *language
) {
  Subtree result = ts_subtree_new_leaf(
    pool, symbol, padding, length_zero(), lookahead_bytes,
    0, 0, 0, 0, language
  );
  if (result.data.is_inline) {
    result.data.is_missing = 1;
  } else {
    ((SubtreeHeapData *)result.ptr)->is_missing = 1;
  }
  return result;
}
void ts_subtree_retain(Subtree self) {
  if (self.data.is_inline) return;
  (__builtin_expect(!(self.ptr->ref_count > 0), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./subtree.c", 555, "self.ptr->ref_count > 0") : (void)0);
  atomic_inc((volatile uint32_t *)&self.ptr->ref_count);
  (__builtin_expect(!(self.ptr->ref_count != 0), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./subtree.c", 557, "self.ptr->ref_count != 0") : (void)0);
}
void ts_subtree_release(SubtreePool *pool, Subtree self) {
  if (self.data.is_inline) return;
  ((&pool->tree_stack)->size = 0);
  (__builtin_expect(!(self.ptr->ref_count > 0), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./subtree.c", 564, "self.ptr->ref_count > 0") : (void)0);
  if (atomic_dec((volatile uint32_t *)&self.ptr->ref_count) == 0) {
    (_array__grow((Array *)(&pool->tree_stack), 1, (sizeof *(&pool->tree_stack)->contents)), (&pool->tree_stack)->contents[(&pool->tree_stack)->size++] = (ts_subtree_to_mut_unsafe(self)));
  }
  while (pool->tree_stack.size > 0) {
    MutableSubtree tree = ((&pool->tree_stack)->contents[--(&pool->tree_stack)->size]);
    if (tree.ptr->child_count > 0) {
      Subtree *children = ((tree).data.is_inline ? ((void *)0) : (Subtree *)((tree).ptr) - (tree).ptr->child_count);
      for (uint32_t i = 0; i < tree.ptr->child_count; i++) {
        Subtree child = children[i];
        if (child.data.is_inline) continue;
        (__builtin_expect(!(child.ptr->ref_count > 0), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./subtree.c", 576, "child.ptr->ref_count > 0") : (void)0);
        if (atomic_dec((volatile uint32_t *)&child.ptr->ref_count) == 0) {
          (_array__grow((Array *)(&pool->tree_stack), 1, (sizeof *(&pool->tree_stack)->contents)), (&pool->tree_stack)->contents[(&pool->tree_stack)->size++] = (ts_subtree_to_mut_unsafe(child)));
        }
      }
      ts_current_free(children);
    } else {
      if (tree.ptr->has_external_tokens) {
        ts_external_scanner_state_delete(&tree.ptr->external_scanner_state);
      }
      ts_subtree_pool_free(pool, tree.ptr);
    }
  }
}
int ts_subtree_compare(Subtree left, Subtree right, SubtreePool *pool) {
  (_array__grow((Array *)(&pool->tree_stack), 1, (sizeof *(&pool->tree_stack)->contents)), (&pool->tree_stack)->contents[(&pool->tree_stack)->size++] = (ts_subtree_to_mut_unsafe(left)));
  (_array__grow((Array *)(&pool->tree_stack), 1, (sizeof *(&pool->tree_stack)->contents)), (&pool->tree_stack)->contents[(&pool->tree_stack)->size++] = (ts_subtree_to_mut_unsafe(right)));
  while (pool->tree_stack.size > 0) {
    right = ts_subtree_from_mut(((&pool->tree_stack)->contents[--(&pool->tree_stack)->size]));
    left = ts_subtree_from_mut(((&pool->tree_stack)->contents[--(&pool->tree_stack)->size]));
    int result = 0;
    if (ts_subtree_symbol(left) < ts_subtree_symbol(right)) result = -1;
    else if (ts_subtree_symbol(right) < ts_subtree_symbol(left)) result = 1;
    else if (ts_subtree_child_count(left) < ts_subtree_child_count(right)) result = -1;
    else if (ts_subtree_child_count(right) < ts_subtree_child_count(left)) result = 1;
    if (result != 0) {
      ((&pool->tree_stack)->size = 0);
      return result;
    }
    for (uint32_t i = ts_subtree_child_count(left); i > 0; i--) {
      Subtree left_child = ((left).data.is_inline ? ((void *)0) : (Subtree *)((left).ptr) - (left).ptr->child_count)[i - 1];
      Subtree right_child = ((right).data.is_inline ? ((void *)0) : (Subtree *)((right).ptr) - (right).ptr->child_count)[i - 1];
      (_array__grow((Array *)(&pool->tree_stack), 1, (sizeof *(&pool->tree_stack)->contents)), (&pool->tree_stack)->contents[(&pool->tree_stack)->size++] = (ts_subtree_to_mut_unsafe(left_child)));
      (_array__grow((Array *)(&pool->tree_stack), 1, (sizeof *(&pool->tree_stack)->contents)), (&pool->tree_stack)->contents[(&pool->tree_stack)->size++] = (ts_subtree_to_mut_unsafe(right_child)));
    }
  }
  return 0;
}
static inline void ts_subtree_set_has_changes(MutableSubtree *self) {
  if (self->data.is_inline) {
    self->data.has_changes = 1;
  } else {
    self->ptr->has_changes = 1;
  }
}
Subtree ts_subtree_edit(Subtree self, const TSInputEdit *input_edit, SubtreePool *pool) {
  typedef struct {
    Subtree *tree;
    Edit edit;
  } EditEntry;
  struct { EditEntry *contents; uint32_t size; uint32_t capacity; } stack = { ((void *)0), 0, 0 };
  (_array__grow((Array *)(&stack), 1, (sizeof *(&stack)->contents)), (&stack)->contents[(&stack)->size++] = (((EditEntry) { .tree = &self, .edit = (Edit) { .start = {input_edit->start_byte, input_edit->start_point}, .old_end = {input_edit->old_end_byte, input_edit->old_end_point}, .new_end = {input_edit->new_end_byte, input_edit->new_end_point}, }, })));
  while (stack.size) {
    EditEntry entry = ((&stack)->contents[--(&stack)->size]);
    Edit edit = entry.edit;
    _Bool is_noop = edit.old_end.bytes == edit.start.bytes && edit.new_end.bytes == edit.start.bytes;
    _Bool is_pure_insertion = edit.old_end.bytes == edit.start.bytes;
    _Bool parent_depends_on_column = ts_subtree_depends_on_column(*entry.tree);
    _Bool column_shifted = edit.new_end.extent.column != edit.old_end.extent.column;
    Length size = ts_subtree_size(*entry.tree);
    Length padding = ts_subtree_padding(*entry.tree);
    Length total_size = length_add(padding, size);
    uint32_t lookahead_bytes = ts_subtree_lookahead_bytes(*entry.tree);
    uint32_t end_byte = total_size.bytes + lookahead_bytes;
    if (edit.start.bytes > end_byte || (is_noop && edit.start.bytes == end_byte)) continue;
    if (edit.old_end.bytes <= padding.bytes) {
      padding = length_add(edit.new_end, length_sub(padding, edit.old_end));
    }
    else if (edit.start.bytes < padding.bytes) {
      size = length_saturating_sub(size, length_sub(edit.old_end, padding));
      padding = edit.new_end;
    }
    else if (
      edit.start.bytes < total_size.bytes ||
      (edit.start.bytes == total_size.bytes && is_pure_insertion)
    ) {
      size = length_add(
        length_sub(edit.new_end, padding),
        length_saturating_sub(total_size, edit.old_end)
      );
    }
    MutableSubtree result = ts_subtree_make_mut(pool, *entry.tree);
    if (result.data.is_inline) {
      if (ts_subtree_can_inline(padding, size, lookahead_bytes)) {
        result.data.padding_bytes = padding.bytes;
        result.data.padding_rows = padding.extent.row;
        result.data.padding_columns = padding.extent.column;
        result.data.size_bytes = size.bytes;
      } else {
        SubtreeHeapData *data = ts_subtree_pool_allocate(pool);
        data->ref_count = 1;
        data->padding = padding;
        data->size = size;
        data->lookahead_bytes = lookahead_bytes;
        data->error_cost = 0;
        data->child_count = 0;
        data->symbol = result.data.symbol;
        data->parse_state = result.data.parse_state;
        data->visible = result.data.visible;
        data->named = result.data.named;
        data->extra = result.data.extra;
        data->fragile_left = 0;
        data->fragile_right = 0;
        data->has_changes = 0;
        data->has_external_tokens = 0;
        data->depends_on_column = 0;
        data->is_missing = result.data.is_missing;
        data->is_keyword = result.data.is_keyword;
        result.ptr = data;
      }
    } else {
      result.ptr->padding = padding;
      result.ptr->size = size;
    }
    ts_subtree_set_has_changes(&result);
    *entry.tree = ts_subtree_from_mut(result);
    Length child_left, child_right = length_zero();
    for (uint32_t i = 0, n = ts_subtree_child_count(*entry.tree); i < n; i++) {
      Subtree *child = &((*entry.tree).data.is_inline ? ((void *)0) : (Subtree *)((*entry.tree).ptr) - (*entry.tree).ptr->child_count)[i];
      Length child_size = ts_subtree_total_size(*child);
      child_left = child_right;
      child_right = length_add(child_left, child_size);
      if (child_right.bytes + ts_subtree_lookahead_bytes(*child) < edit.start.bytes) continue;
      if ((
        (child_left.bytes > edit.old_end.bytes) ||
        (child_left.bytes == edit.old_end.bytes && child_size.bytes > 0 && i > 0)
      ) && (
        !parent_depends_on_column ||
        child_left.extent.row > padding.extent.row
      ) && (
        !ts_subtree_depends_on_column(*child) ||
        !column_shifted ||
        child_left.extent.row > edit.old_end.extent.row
      )) {
        break;
      }
      Edit child_edit = {
        .start = length_saturating_sub(edit.start, child_left),
        .old_end = length_saturating_sub(edit.old_end, child_left),
        .new_end = length_saturating_sub(edit.new_end, child_left),
      };
      if (
        child_right.bytes > edit.start.bytes ||
        (child_right.bytes == edit.start.bytes && is_pure_insertion)
      ) {
        edit.new_end = edit.start;
      }
      else {
        child_edit.old_end = child_edit.start;
        child_edit.new_end = child_edit.start;
      }
      (_array__grow((Array *)(&stack), 1, (sizeof *(&stack)->contents)), (&stack)->contents[(&stack)->size++] = (((EditEntry) { .tree = child, .edit = child_edit, })));
    }
  }
  _array__delete((Array *)(&stack));
  return self;
}
Subtree ts_subtree_last_external_token(Subtree tree) {
  if (!ts_subtree_has_external_tokens(tree)) return ((Subtree) {.ptr = ((void *)0)});
  while (tree.ptr->child_count > 0) {
    for (uint32_t i = tree.ptr->child_count - 1; i + 1 > 0; i--) {
      Subtree child = ((tree).data.is_inline ? ((void *)0) : (Subtree *)((tree).ptr) - (tree).ptr->child_count)[i];
      if (ts_subtree_has_external_tokens(child)) {
        tree = child;
        break;
      }
    }
  }
  return tree;
}
static size_t ts_subtree__write_char_to_string(char *str, size_t n, int32_t chr) {
  if (chr == -1)
    return snprintf(str, n, "INVALID");
  else if (chr == '\0')
    return snprintf(str, n, "'\\0'");
  else if (chr == '\n')
    return snprintf(str, n, "'\\n'");
  else if (chr == '\t')
    return snprintf(str, n, "'\\t'");
  else if (chr == '\r')
    return snprintf(str, n, "'\\r'");
  else if (0 < chr && chr < 128 && isprint(chr))
    return snprintf(str, n, "'%c'", chr);
  else
    return snprintf(str, n, "%d", chr);
}
static const char *const ROOT_FIELD = "__ROOT__";
static size_t ts_subtree__write_to_string(
  Subtree self, char *string, size_t limit,
  const TSLanguage *language, _Bool include_all,
  TSSymbol alias_symbol, _Bool alias_is_named, const char *field_name
) {
  if (!self.ptr) return snprintf(string, limit, "(NULL)");
  char *cursor = string;
  char **writer = (limit > 1) ? &cursor : &string;
  _Bool is_root = field_name == ROOT_FIELD;
  _Bool is_visible =
    include_all ||
    ts_subtree_missing(self) ||
    (
      alias_symbol
        ? alias_is_named
        : ts_subtree_visible(self) && ts_subtree_named(self)
    );
  if (is_visible) {
    if (!is_root) {
      cursor += snprintf(*writer, limit, " ");
      if (field_name) {
        cursor += snprintf(*writer, limit, "%s: ", field_name);
      }
    }
    if (ts_subtree_is_error(self) && ts_subtree_child_count(self) == 0 && self.ptr->size.bytes > 0) {
      cursor += snprintf(*writer, limit, "(UNEXPECTED ");
      cursor += ts_subtree__write_char_to_string(*writer, limit, self.ptr->lookahead_char);
    } else {
      TSSymbol symbol = alias_symbol ? alias_symbol : ts_subtree_symbol(self);
      const char *symbol_name = ts_language_symbol_name(language, symbol);
      if (ts_subtree_missing(self)) {
        cursor += snprintf(*writer, limit, "(MISSING ");
        if (alias_is_named || ts_subtree_named(self)) {
          cursor += snprintf(*writer, limit, "%s", symbol_name);
        } else {
          cursor += snprintf(*writer, limit, "\"%s\"", symbol_name);
        }
      } else {
        cursor += snprintf(*writer, limit, "(%s", symbol_name);
      }
    }
  } else if (is_root) {
    TSSymbol symbol = alias_symbol ? alias_symbol : ts_subtree_symbol(self);
    const char *symbol_name = ts_language_symbol_name(language, symbol);
    if (ts_subtree_child_count(self) > 0) {
      cursor += snprintf(*writer, limit, "(%s", symbol_name);
    } else if (ts_subtree_named(self)) {
      cursor += snprintf(*writer, limit, "(%s)", symbol_name);
    } else {
      cursor += snprintf(*writer, limit, "(\"%s\")", symbol_name);
    }
  }
  if (ts_subtree_child_count(self)) {
    const TSSymbol *alias_sequence = ts_language_alias_sequence(language, self.ptr->production_id);
    const TSFieldMapEntry *field_map, *field_map_end;
    ts_language_field_map(
      language,
      self.ptr->production_id,
      &field_map,
      &field_map_end
    );
    uint32_t structural_child_index = 0;
    for (uint32_t i = 0; i < self.ptr->child_count; i++) {
      Subtree child = ((self).data.is_inline ? ((void *)0) : (Subtree *)((self).ptr) - (self).ptr->child_count)[i];
      if (ts_subtree_extra(child)) {
        cursor += ts_subtree__write_to_string(
          child, *writer, limit,
          language, include_all,
          0, 0, ((void *)0)
        );
      } else {
        TSSymbol subtree_alias_symbol = alias_sequence
          ? alias_sequence[structural_child_index]
          : 0;
        _Bool subtree_alias_is_named = subtree_alias_symbol
          ? ts_language_symbol_metadata(language, subtree_alias_symbol).named
          : 0;
        const char *child_field_name = is_visible ? ((void *)0) : field_name;
        for (const TSFieldMapEntry *map = field_map; map < field_map_end; map++) {
          if (!map->inherited && map->child_index == structural_child_index) {
            child_field_name = language->field_names[map->field_id];
            break;
          }
        }
        cursor += ts_subtree__write_to_string(
          child, *writer, limit,
          language, include_all,
          subtree_alias_symbol, subtree_alias_is_named, child_field_name
        );
        structural_child_index++;
      }
    }
  }
  if (is_visible) cursor += snprintf(*writer, limit, ")");
  return cursor - string;
}
char *ts_subtree_string(
  Subtree self,
  TSSymbol alias_symbol,
  _Bool alias_is_named,
  const TSLanguage *language,
  _Bool include_all
) {
  char scratch_string[1];
  size_t size = ts_subtree__write_to_string(
    self, scratch_string, 1,
    language, include_all,
    alias_symbol, alias_is_named, ROOT_FIELD
  ) + 1;
  char *result = ts_current_malloc(size * sizeof(char));
  ts_subtree__write_to_string(
    self, result, size,
    language, include_all,
    alias_symbol, alias_is_named, ROOT_FIELD
  );
  return result;
}
void ts_subtree__print_dot_graph(const Subtree *self, uint32_t start_offset,
                                 const TSLanguage *language, TSSymbol alias_symbol,
                                 FILE *f) {
  TSSymbol subtree_symbol = ts_subtree_symbol(*self);
  TSSymbol symbol = alias_symbol ? alias_symbol : subtree_symbol;
  uint32_t end_offset = start_offset + ts_subtree_total_bytes(*self);
  fprintf(f, "tree_%p [label=\"", (void *)self);
  ts_language_write_symbol_as_dot_string(language, f, symbol);
  fprintf(f, "\"");
  if (ts_subtree_child_count(*self) == 0) fprintf(f, ", shape=plaintext");
  if (ts_subtree_extra(*self)) fprintf(f, ", fontcolor=gray");
  if (ts_subtree_has_changes(*self)) fprintf(f, ", color=green, penwidth=2");
  fprintf(f, ", tooltip=\""
    "range: %u - %u\n"
    "state: %d\n"
    "error-cost: %u\n"
    "has-changes: %u\n"
    "depends-on-column: %u\n"
    "descendant-count: %u\n"
    "repeat-depth: %u\n"
    "lookahead-bytes: %u",
    start_offset, end_offset,
    ts_subtree_parse_state(*self),
    ts_subtree_error_cost(*self),
    ts_subtree_has_changes(*self),
    ts_subtree_depends_on_column(*self),
    ts_subtree_visible_descendant_count(*self),
    ts_subtree_repeat_depth(*self),
    ts_subtree_lookahead_bytes(*self)
  );
  if (ts_subtree_is_error(*self) && ts_subtree_child_count(*self) == 0 && self->ptr->lookahead_char != 0) {
    fprintf(f, "\ncharacter: '%c'", self->ptr->lookahead_char);
  }
  fprintf(f, "\"]\n");
  uint32_t child_start_offset = start_offset;
  uint32_t child_info_offset =
    language->max_alias_sequence_length *
    ts_subtree_production_id(*self);
  for (uint32_t i = 0, n = ts_subtree_child_count(*self); i < n; i++) {
    const Subtree *child = &((*self).data.is_inline ? ((void *)0) : (Subtree *)((*self).ptr) - (*self).ptr->child_count)[i];
    TSSymbol subtree_alias_symbol = 0;
    if (!ts_subtree_extra(*child) && child_info_offset) {
      subtree_alias_symbol = language->alias_sequences[child_info_offset];
      child_info_offset++;
    }
    ts_subtree__print_dot_graph(child, child_start_offset, language, subtree_alias_symbol, f);
    fprintf(f, "tree_%p -> tree_%p [tooltip=%u]\n", (void *)self, (void *)child, i);
    child_start_offset += ts_subtree_total_bytes(*child);
  }
}
void ts_subtree_print_dot_graph(Subtree self, const TSLanguage *language, FILE *f) {
  fprintf(f, "digraph tree {\n");
  fprintf(f, "edge [arrowhead=none]\n");
  ts_subtree__print_dot_graph(&self, 0, language, 0, f);
  fprintf(f, "}\n");
}
const ExternalScannerState *ts_subtree_external_scanner_state(Subtree self) {
  static const ExternalScannerState empty_state = {{.short_data = {0}}, .length = 0};
  if (
    self.ptr &&
    !self.data.is_inline &&
    self.ptr->has_external_tokens &&
    self.ptr->child_count == 0
  ) {
    return &self.ptr->external_scanner_state;
  } else {
    return &empty_state;
  }
}
_Bool ts_subtree_external_scanner_state_eq(Subtree self, Subtree other) {
  const ExternalScannerState *state_self = ts_subtree_external_scanner_state(self);
  const ExternalScannerState *state_other = ts_subtree_external_scanner_state(other);
  return ts_external_scanner_state_eq(
    state_self,
    ts_external_scanner_state_data(state_other),
    state_other->length
  );
}
typedef struct {
  Subtree parent;
  const TSTree *tree;
  Length position;
  uint32_t child_index;
  uint32_t structural_child_index;
  uint32_t descendant_index;
  const TSSymbol *alias_sequence;
} CursorChildIterator;
static inline _Bool ts_tree_cursor_is_entry_visible(const TreeCursor *self, uint32_t index) {
  TreeCursorEntry *entry = &self->stack.contents[index];
  if (index == 0 || ts_subtree_visible(*entry->subtree)) {
    return 1;
  } else if (!ts_subtree_extra(*entry->subtree)) {
    TreeCursorEntry *parent_entry = &self->stack.contents[index - 1];
    return ts_language_alias_at(
      self->tree->language,
      parent_entry->subtree->ptr->production_id,
      entry->structural_child_index
    );
  } else {
    return 0;
  }
}
static inline CursorChildIterator ts_tree_cursor_iterate_children(const TreeCursor *self) {
  TreeCursorEntry *last_entry = ((__builtin_expect(!((uint32_t)((&self->stack)->size - 1) < (&self->stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./tree_cursor.c", 35, "(uint32_t)((&self->stack)->size - 1) < (&self->stack)->size") : (void)0), &(&self->stack)->contents[(&self->stack)->size - 1]);
  if (ts_subtree_child_count(*last_entry->subtree) == 0) {
    return (CursorChildIterator) {((Subtree) {.ptr = ((void *)0)}), self->tree, length_zero(), 0, 0, 0, ((void *)0)};
  }
  const TSSymbol *alias_sequence = ts_language_alias_sequence(
    self->tree->language,
    last_entry->subtree->ptr->production_id
  );
  uint32_t descendant_index = last_entry->descendant_index;
  if (ts_tree_cursor_is_entry_visible(self, self->stack.size - 1)) {
    descendant_index += 1;
  }
  return (CursorChildIterator) {
    .tree = self->tree,
    .parent = *last_entry->subtree,
    .position = last_entry->position,
    .child_index = 0,
    .structural_child_index = 0,
    .descendant_index = descendant_index,
    .alias_sequence = alias_sequence,
  };
}
static inline _Bool ts_tree_cursor_child_iterator_next(
  CursorChildIterator *self,
  TreeCursorEntry *result,
  _Bool *visible
) {
  if (!self->parent.ptr || self->child_index == self->parent.ptr->child_count) return 0;
  const Subtree *child = &((self->parent).data.is_inline ? ((void *)0) : (Subtree *)((self->parent).ptr) - (self->parent).ptr->child_count)[self->child_index];
  *result = (TreeCursorEntry) {
    .subtree = child,
    .position = self->position,
    .child_index = self->child_index,
    .structural_child_index = self->structural_child_index,
    .descendant_index = self->descendant_index,
  };
  *visible = ts_subtree_visible(*child);
  _Bool extra = ts_subtree_extra(*child);
  if (!extra) {
    if (self->alias_sequence) {
      *visible |= self->alias_sequence[self->structural_child_index];
    }
    self->structural_child_index++;
  }
  self->descendant_index += ts_subtree_visible_descendant_count(*child);
  if (*visible) {
    self->descendant_index += 1;
  }
  self->position = length_add(self->position, ts_subtree_size(*child));
  self->child_index++;
  if (self->child_index < self->parent.ptr->child_count) {
    Subtree next_child = ((self->parent).data.is_inline ? ((void *)0) : (Subtree *)((self->parent).ptr) - (self->parent).ptr->child_count)[self->child_index];
    self->position = length_add(self->position, ts_subtree_padding(next_child));
  }
  return 1;
}
static inline Length length_backtrack(Length a, Length b) {
  if (length_is_undefined(a) || b.extent.row != 0) {
    return LENGTH_UNDEFINED;
  }
  Length result;
  result.bytes = a.bytes - b.bytes;
  result.extent.row = a.extent.row;
  result.extent.column = a.extent.column - b.extent.column;
  return result;
}
static inline _Bool ts_tree_cursor_child_iterator_previous(
  CursorChildIterator *self,
  TreeCursorEntry *result,
  _Bool *visible
) {
  if (!self->parent.ptr || (int8_t)self->child_index == -1) return 0;
  const Subtree *child = &((self->parent).data.is_inline ? ((void *)0) : (Subtree *)((self->parent).ptr) - (self->parent).ptr->child_count)[self->child_index];
  *result = (TreeCursorEntry) {
    .subtree = child,
    .position = self->position,
    .child_index = self->child_index,
    .structural_child_index = self->structural_child_index,
  };
  *visible = ts_subtree_visible(*child);
  _Bool extra = ts_subtree_extra(*child);
  if (!extra && self->alias_sequence) {
    *visible |= self->alias_sequence[self->structural_child_index];
    self->structural_child_index--;
  }
  self->position = length_backtrack(self->position, ts_subtree_padding(*child));
  self->child_index--;
  if (self->child_index < self->parent.ptr->child_count) {
    Subtree previous_child = ((self->parent).data.is_inline ? ((void *)0) : (Subtree *)((self->parent).ptr) - (self->parent).ptr->child_count)[self->child_index];
    Length size = ts_subtree_size(previous_child);
    self->position = length_backtrack(self->position, size);
  }
  return 1;
}
TSTreeCursor ts_tree_cursor_new(TSNode node) {
  TSTreeCursor self = {((void *)0), ((void *)0), {0, 0, 0}};
  ts_tree_cursor_init((TreeCursor *)&self, node);
  return self;
}
void ts_tree_cursor_reset(TSTreeCursor *_self, TSNode node) {
  ts_tree_cursor_init((TreeCursor *)_self, node);
}
void ts_tree_cursor_init(TreeCursor *self, TSNode node) {
  self->tree = node.tree;
  self->root_alias_symbol = node.context[3];
  ((&self->stack)->size = 0);
  (_array__grow((Array *)(&self->stack), 1, (sizeof *(&self->stack)->contents)), (&self->stack)->contents[(&self->stack)->size++] = (((TreeCursorEntry) { .subtree = (const Subtree *)node.id, .position = { ts_node_start_byte(node), ts_node_start_point(node) }, .child_index = 0, .structural_child_index = 0, .descendant_index = 0, })));
}
void ts_tree_cursor_delete(TSTreeCursor *_self) {
  TreeCursor *self = (TreeCursor *)_self;
  _array__delete((Array *)(&self->stack));
}
TreeCursorStep ts_tree_cursor_goto_first_child_internal(TSTreeCursor *_self) {
  TreeCursor *self = (TreeCursor *)_self;
  _Bool visible;
  TreeCursorEntry entry;
  CursorChildIterator iterator = ts_tree_cursor_iterate_children(self);
  while (ts_tree_cursor_child_iterator_next(&iterator, &entry, &visible)) {
    if (visible) {
      (_array__grow((Array *)(&self->stack), 1, (sizeof *(&self->stack)->contents)), (&self->stack)->contents[(&self->stack)->size++] = (entry));
      return TreeCursorStepVisible;
    }
    if (ts_subtree_visible_child_count(*entry.subtree) > 0) {
      (_array__grow((Array *)(&self->stack), 1, (sizeof *(&self->stack)->contents)), (&self->stack)->contents[(&self->stack)->size++] = (entry));
      return TreeCursorStepHidden;
    }
  }
  return TreeCursorStepNone;
}
_Bool ts_tree_cursor_goto_first_child(TSTreeCursor *self) {
  for (;;) {
    switch (ts_tree_cursor_goto_first_child_internal(self)) {
      case TreeCursorStepHidden:
        continue;
      case TreeCursorStepVisible:
        return 1;
      default:
        return 0;
    }
  }
}
TreeCursorStep ts_tree_cursor_goto_last_child_internal(TSTreeCursor *_self) {
  TreeCursor *self = (TreeCursor *)_self;
  _Bool visible;
  TreeCursorEntry entry;
  CursorChildIterator iterator = ts_tree_cursor_iterate_children(self);
  if (!iterator.parent.ptr || iterator.parent.ptr->child_count == 0) return TreeCursorStepNone;
  TreeCursorEntry last_entry = {0};
  TreeCursorStep last_step = TreeCursorStepNone;
  while (ts_tree_cursor_child_iterator_next(&iterator, &entry, &visible)) {
    if (visible) {
      last_entry = entry;
      last_step = TreeCursorStepVisible;
    }
    else if (ts_subtree_visible_child_count(*entry.subtree) > 0) {
      last_entry = entry;
      last_step = TreeCursorStepHidden;
    }
  }
  if (last_entry.subtree) {
    (_array__grow((Array *)(&self->stack), 1, (sizeof *(&self->stack)->contents)), (&self->stack)->contents[(&self->stack)->size++] = (last_entry));
    return last_step;
  }
  return TreeCursorStepNone;
}
_Bool ts_tree_cursor_goto_last_child(TSTreeCursor *self) {
  for (;;) {
    switch (ts_tree_cursor_goto_last_child_internal(self)) {
      case TreeCursorStepHidden:
        continue;
      case TreeCursorStepVisible:
        return 1;
      default:
        return 0;
    }
  }
}
static inline int64_t ts_tree_cursor_goto_first_child_for_byte_and_point(
  TSTreeCursor *_self,
  uint32_t goal_byte,
  TSPoint goal_point
) {
  TreeCursor *self = (TreeCursor *)_self;
  uint32_t initial_size = self->stack.size;
  uint32_t visible_child_index = 0;
  _Bool did_descend;
  do {
    did_descend = 0;
    _Bool visible;
    TreeCursorEntry entry;
    CursorChildIterator iterator = ts_tree_cursor_iterate_children(self);
    while (ts_tree_cursor_child_iterator_next(&iterator, &entry, &visible)) {
      Length entry_end = length_add(entry.position, ts_subtree_size(*entry.subtree));
      _Bool at_goal = entry_end.bytes > goal_byte && point_gt(entry_end.extent, goal_point);
      uint32_t visible_child_count = ts_subtree_visible_child_count(*entry.subtree);
      if (at_goal) {
        if (visible) {
          (_array__grow((Array *)(&self->stack), 1, (sizeof *(&self->stack)->contents)), (&self->stack)->contents[(&self->stack)->size++] = (entry));
          return visible_child_index;
        }
        if (visible_child_count > 0) {
          (_array__grow((Array *)(&self->stack), 1, (sizeof *(&self->stack)->contents)), (&self->stack)->contents[(&self->stack)->size++] = (entry));
          did_descend = 1;
          break;
        }
      } else if (visible) {
        visible_child_index++;
      } else {
        visible_child_index += visible_child_count;
      }
    }
  } while (did_descend);
  self->stack.size = initial_size;
  return -1;
}
int64_t ts_tree_cursor_goto_first_child_for_byte(TSTreeCursor *self, uint32_t goal_byte) {
  return ts_tree_cursor_goto_first_child_for_byte_and_point(self, goal_byte, ((TSPoint) {0, 0}));
}
int64_t ts_tree_cursor_goto_first_child_for_point(TSTreeCursor *self, TSPoint goal_point) {
  return ts_tree_cursor_goto_first_child_for_byte_and_point(self, 0, goal_point);
}
TreeCursorStep ts_tree_cursor_goto_sibling_internal(
    TSTreeCursor *_self,
    _Bool (*advance)(CursorChildIterator *, TreeCursorEntry *, _Bool *)) {
  TreeCursor *self = (TreeCursor *)_self;
  uint32_t initial_size = self->stack.size;
  while (self->stack.size > 1) {
    TreeCursorEntry entry = ((&self->stack)->contents[--(&self->stack)->size]);
    CursorChildIterator iterator = ts_tree_cursor_iterate_children(self);
    iterator.child_index = entry.child_index;
    iterator.structural_child_index = entry.structural_child_index;
    iterator.position = entry.position;
    iterator.descendant_index = entry.descendant_index;
    _Bool visible = 0;
    advance(&iterator, &entry, &visible);
    if (visible && self->stack.size + 1 < initial_size) break;
    while (advance(&iterator, &entry, &visible)) {
      if (visible) {
        (_array__grow((Array *)(&self->stack), 1, (sizeof *(&self->stack)->contents)), (&self->stack)->contents[(&self->stack)->size++] = (entry));
        return TreeCursorStepVisible;
      }
      if (ts_subtree_visible_child_count(*entry.subtree)) {
        (_array__grow((Array *)(&self->stack), 1, (sizeof *(&self->stack)->contents)), (&self->stack)->contents[(&self->stack)->size++] = (entry));
        return TreeCursorStepHidden;
      }
    }
  }
  self->stack.size = initial_size;
  return TreeCursorStepNone;
}
TreeCursorStep ts_tree_cursor_goto_next_sibling_internal(TSTreeCursor *_self) {
  return ts_tree_cursor_goto_sibling_internal(_self, ts_tree_cursor_child_iterator_next);
}
_Bool ts_tree_cursor_goto_next_sibling(TSTreeCursor *self) {
  switch (ts_tree_cursor_goto_next_sibling_internal(self)) {
    case TreeCursorStepHidden:
      ts_tree_cursor_goto_first_child(self);
      return 1;
    case TreeCursorStepVisible:
      return 1;
    default:
      return 0;
  }
}
TreeCursorStep ts_tree_cursor_goto_previous_sibling_internal(TSTreeCursor *_self) {
  TreeCursor *self = (TreeCursor *)_self;
  TreeCursorStep step = ts_tree_cursor_goto_sibling_internal(
      _self, ts_tree_cursor_child_iterator_previous);
  if (step == TreeCursorStepNone)
    return step;
  if (!length_is_undefined(((__builtin_expect(!((uint32_t)((&self->stack)->size - 1) < (&self->stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./tree_cursor.c", 369, "(uint32_t)((&self->stack)->size - 1) < (&self->stack)->size") : (void)0), &(&self->stack)->contents[(&self->stack)->size - 1])->position))
    return step;
  const TreeCursorEntry *parent = &self->stack.contents[self->stack.size - 2];
  Length position = parent->position;
  uint32_t child_index = ((__builtin_expect(!((uint32_t)((&self->stack)->size - 1) < (&self->stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./tree_cursor.c", 375, "(uint32_t)((&self->stack)->size - 1) < (&self->stack)->size") : (void)0), &(&self->stack)->contents[(&self->stack)->size - 1])->child_index;
  const Subtree *children = (((*(parent->subtree))).data.is_inline ? ((void *)0) : (Subtree *)(((*(parent->subtree))).ptr) - ((*(parent->subtree))).ptr->child_count);
  if (child_index > 0) {
    position = length_add(position, ts_subtree_size(children[0]));
    for (uint32_t i = 1; i < child_index; ++i) {
      position = length_add(position, ts_subtree_total_size(children[i]));
    }
    position = length_add(position, ts_subtree_padding(children[child_index]));
  }
  ((__builtin_expect(!((uint32_t)((&self->stack)->size - 1) < (&self->stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./tree_cursor.c", 387, "(uint32_t)((&self->stack)->size - 1) < (&self->stack)->size") : (void)0), &(&self->stack)->contents[(&self->stack)->size - 1])->position = position;
  return step;
}
_Bool ts_tree_cursor_goto_previous_sibling(TSTreeCursor *self) {
  switch (ts_tree_cursor_goto_previous_sibling_internal(self)) {
    case TreeCursorStepHidden:
      ts_tree_cursor_goto_last_child(self);
      return 1;
    case TreeCursorStepVisible:
      return 1;
    default:
      return 0;
  }
}
_Bool ts_tree_cursor_goto_parent(TSTreeCursor *_self) {
  TreeCursor *self = (TreeCursor *)_self;
  for (unsigned i = self->stack.size - 2; i + 1 > 0; i--) {
    if (ts_tree_cursor_is_entry_visible(self, i)) {
      self->stack.size = i + 1;
      return 1;
    }
  }
  return 0;
}
void ts_tree_cursor_goto_descendant(
  TSTreeCursor *_self,
  uint32_t goal_descendant_index
) {
  TreeCursor *self = (TreeCursor *)_self;
  for (;;) {
    uint32_t i = self->stack.size - 1;
    TreeCursorEntry *entry = &self->stack.contents[i];
    uint32_t next_descendant_index =
      entry->descendant_index +
      (ts_tree_cursor_is_entry_visible(self, i) ? 1 : 0) +
      ts_subtree_visible_descendant_count(*entry->subtree);
    if (
      (entry->descendant_index <= goal_descendant_index) &&
      (next_descendant_index > goal_descendant_index)
    ) {
      break;
    } else if (self->stack.size <= 1) {
      return;
    } else {
      self->stack.size--;
    }
  }
  _Bool did_descend = 1;
  do {
    did_descend = 0;
    _Bool visible;
    TreeCursorEntry entry;
    CursorChildIterator iterator = ts_tree_cursor_iterate_children(self);
    if (iterator.descendant_index > goal_descendant_index) {
      return;
    }
    while (ts_tree_cursor_child_iterator_next(&iterator, &entry, &visible)) {
      if (iterator.descendant_index > goal_descendant_index) {
        (_array__grow((Array *)(&self->stack), 1, (sizeof *(&self->stack)->contents)), (&self->stack)->contents[(&self->stack)->size++] = (entry));
        if (visible && entry.descendant_index == goal_descendant_index) {
          return;
        } else {
          did_descend = 1;
          break;
        }
      }
    }
  } while (did_descend);
}
uint32_t ts_tree_cursor_current_descendant_index(const TSTreeCursor *_self) {
  const TreeCursor *self = (const TreeCursor *)_self;
  TreeCursorEntry *last_entry = ((__builtin_expect(!((uint32_t)((&self->stack)->size - 1) < (&self->stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./tree_cursor.c", 468, "(uint32_t)((&self->stack)->size - 1) < (&self->stack)->size") : (void)0), &(&self->stack)->contents[(&self->stack)->size - 1]);
  return last_entry->descendant_index;
}
TSNode ts_tree_cursor_current_node(const TSTreeCursor *_self) {
  const TreeCursor *self = (const TreeCursor *)_self;
  TreeCursorEntry *last_entry = ((__builtin_expect(!((uint32_t)((&self->stack)->size - 1) < (&self->stack)->size), 0) ? __assert_rtn(__func__, "src/tree-sitter/lib/src/./tree_cursor.c", 474, "(uint32_t)((&self->stack)->size - 1) < (&self->stack)->size") : (void)0), &(&self->stack)->contents[(&self->stack)->size - 1]);
  _Bool is_extra = ts_subtree_extra(*last_entry->subtree);
  TSSymbol alias_symbol = is_extra ? 0 : self->root_alias_symbol;
  if (self->stack.size > 1 && !is_extra) {
    TreeCursorEntry *parent_entry = &self->stack.contents[self->stack.size - 2];
    alias_symbol = ts_language_alias_at(
      self->tree->language,
      parent_entry->subtree->ptr->production_id,
      last_entry->structural_child_index
    );
  }
  return ts_node_new(
    self->tree,
    last_entry->subtree,
    last_entry->position,
    alias_symbol
  );
}
void ts_tree_cursor_current_status(
  const TSTreeCursor *_self,
  TSFieldId *field_id,
  _Bool *has_later_siblings,
  _Bool *has_later_named_siblings,
  _Bool *can_have_later_siblings_with_this_field,
  TSSymbol *supertypes,
  unsigned *supertype_count
) {
  const TreeCursor *self = (const TreeCursor *)_self;
  unsigned max_supertypes = *supertype_count;
  *field_id = 0;
  *supertype_count = 0;
  *has_later_siblings = 0;
  *has_later_named_siblings = 0;
  *can_have_later_siblings_with_this_field = 0;
  for (unsigned i = self->stack.size - 1; i > 0; i--) {
    TreeCursorEntry *entry = &self->stack.contents[i];
    TreeCursorEntry *parent_entry = &self->stack.contents[i - 1];
    const TSSymbol *alias_sequence = ts_language_alias_sequence(
      self->tree->language,
      parent_entry->subtree->ptr->production_id
    );
    TSSymbol entry_symbol = (( !ts_subtree_extra(*entry->subtree) && alias_sequence && alias_sequence[entry->structural_child_index] ) ? alias_sequence[entry->structural_child_index] : ts_subtree_symbol(*entry->subtree));
    TSSymbolMetadata entry_metadata = ts_language_symbol_metadata(
      self->tree->language,
      entry_symbol
    );
    if (i != self->stack.size - 1 && entry_metadata.visible) break;
    if (entry_metadata.supertype && *supertype_count < max_supertypes) {
      supertypes[*supertype_count] = entry_symbol;
      (*supertype_count)++;
    }
    if (!*has_later_siblings) {
      unsigned sibling_count = parent_entry->subtree->ptr->child_count;
      unsigned structural_child_index = entry->structural_child_index;
      if (!ts_subtree_extra(*entry->subtree)) structural_child_index++;
      for (unsigned j = entry->child_index + 1; j < sibling_count; j++) {
        Subtree sibling = ((*parent_entry->subtree).data.is_inline ? ((void *)0) : (Subtree *)((*parent_entry->subtree).ptr) - (*parent_entry->subtree).ptr->child_count)[j];
        TSSymbolMetadata sibling_metadata = ts_language_symbol_metadata(
          self->tree->language,
          (( !ts_subtree_extra(sibling) && alias_sequence && alias_sequence[structural_child_index] ) ? alias_sequence[structural_child_index] : ts_subtree_symbol(sibling))
        );
        if (sibling_metadata.visible) {
          *has_later_siblings = 1;
          if (*has_later_named_siblings) break;
          if (sibling_metadata.named) {
            *has_later_named_siblings = 1;
            break;
          }
        } else if (ts_subtree_visible_child_count(sibling) > 0) {
          *has_later_siblings = 1;
          if (*has_later_named_siblings) break;
          if (sibling.ptr->named_child_count > 0) {
            *has_later_named_siblings = 1;
            break;
          }
        }
        if (!ts_subtree_extra(sibling)) structural_child_index++;
      }
    }
    if (!ts_subtree_extra(*entry->subtree)) {
      const TSFieldMapEntry *field_map, *field_map_end;
      ts_language_field_map(
        self->tree->language,
        parent_entry->subtree->ptr->production_id,
        &field_map, &field_map_end
      );
      if (!*field_id) {
        for (const TSFieldMapEntry *map = field_map; map < field_map_end; map++) {
          if (!map->inherited && map->child_index == entry->structural_child_index) {
            *field_id = map->field_id;
            break;
          }
        }
      }
      if (*field_id) {
        for (const TSFieldMapEntry *map = field_map; map < field_map_end; map++) {
          if (
            map->field_id == *field_id &&
            map->child_index > entry->structural_child_index
          ) {
            *can_have_later_siblings_with_this_field = 1;
            break;
          }
        }
      }
    }
  }
}
uint32_t ts_tree_cursor_current_depth(const TSTreeCursor *_self) {
  const TreeCursor *self = (const TreeCursor *)_self;
  uint32_t depth = 0;
  for (unsigned i = 1; i < self->stack.size; i++) {
    if (ts_tree_cursor_is_entry_visible(self, i)) {
      depth++;
    }
  }
  return depth;
}
TSNode ts_tree_cursor_parent_node(const TSTreeCursor *_self) {
  const TreeCursor *self = (const TreeCursor *)_self;
  for (int i = (int)self->stack.size - 2; i >= 0; i--) {
    TreeCursorEntry *entry = &self->stack.contents[i];
    _Bool is_visible = 1;
    TSSymbol alias_symbol = 0;
    if (i > 0) {
      TreeCursorEntry *parent_entry = &self->stack.contents[i - 1];
      alias_symbol = ts_language_alias_at(
        self->tree->language,
        parent_entry->subtree->ptr->production_id,
        entry->structural_child_index
      );
      is_visible = (alias_symbol != 0) || ts_subtree_visible(*entry->subtree);
    }
    if (is_visible) {
      return ts_node_new(
        self->tree,
        entry->subtree,
        entry->position,
        alias_symbol
      );
    }
  }
  return ts_node_new(((void *)0), ((void *)0), length_zero(), 0);
}
TSFieldId ts_tree_cursor_current_field_id(const TSTreeCursor *_self) {
  const TreeCursor *self = (const TreeCursor *)_self;
  for (unsigned i = self->stack.size - 1; i > 0; i--) {
    TreeCursorEntry *entry = &self->stack.contents[i];
    TreeCursorEntry *parent_entry = &self->stack.contents[i - 1];
    if (
      i != self->stack.size - 1 &&
      ts_tree_cursor_is_entry_visible(self, i)
    ) break;
    if (ts_subtree_extra(*entry->subtree)) break;
    const TSFieldMapEntry *field_map, *field_map_end;
    ts_language_field_map(
      self->tree->language,
      parent_entry->subtree->ptr->production_id,
      &field_map, &field_map_end
    );
    for (const TSFieldMapEntry *map = field_map; map < field_map_end; map++) {
      if (!map->inherited && map->child_index == entry->structural_child_index) {
        return map->field_id;
      }
    }
  }
  return 0;
}
const char *ts_tree_cursor_current_field_name(const TSTreeCursor *_self) {
  TSFieldId id = ts_tree_cursor_current_field_id(_self);
  if (id) {
    const TreeCursor *self = (const TreeCursor *)_self;
    return self->tree->language->field_names[id];
  } else {
    return ((void *)0);
  }
}
TSTreeCursor ts_tree_cursor_copy(const TSTreeCursor *_cursor) {
  const TreeCursor *cursor = (const TreeCursor *)_cursor;
  TSTreeCursor res = {((void *)0), ((void *)0), {0, 0}};
  TreeCursor *copy = (TreeCursor *)&res;
  copy->tree = cursor->tree;
  copy->root_alias_symbol = cursor->root_alias_symbol;
  ((&copy->stack)->size = 0, (&copy->stack)->capacity = 0, (&copy->stack)->contents = ((void *)0));
  _array__splice( (Array *)((&copy->stack)), (sizeof *((&copy->stack))->contents), ((&copy->stack))->size, 0, (&cursor->stack)->size, (&cursor->stack)->contents );
  return res;
}
void ts_tree_cursor_reset_to(TSTreeCursor *_dst, const TSTreeCursor *_src) {
  const TreeCursor *cursor = (const TreeCursor *)_src;
  TreeCursor *copy = (TreeCursor *)_dst;
  copy->tree = cursor->tree;
  copy->root_alias_symbol = cursor->root_alias_symbol;
  ((&copy->stack)->size = 0);
  _array__splice( (Array *)((&copy->stack)), (sizeof *((&copy->stack))->contents), ((&copy->stack))->size, 0, (&cursor->stack)->size, (&cursor->stack)->contents );
}
TSTree *ts_tree_new(
  Subtree root, const TSLanguage *language,
  const TSRange *included_ranges, unsigned included_range_count
) {
  TSTree *result = ts_current_malloc(sizeof(TSTree));
  result->root = root;
  result->language = ts_language_copy(language);
  result->included_ranges = ts_current_calloc(included_range_count, sizeof(TSRange));
  memcpy(result->included_ranges, included_ranges, included_range_count * sizeof(TSRange));
  result->included_range_count = included_range_count;
  return result;
}
TSTree *ts_tree_copy(const TSTree *self) {
  ts_subtree_retain(self->root);
  return ts_tree_new(self->root, self->language, self->included_ranges, self->included_range_count);
}
void ts_tree_delete(TSTree *self) {
  if (!self) return;
  SubtreePool pool = ts_subtree_pool_new(0);
  ts_subtree_release(&pool, self->root);
  ts_subtree_pool_delete(&pool);
  ts_language_delete(self->language);
  ts_current_free(self->included_ranges);
  ts_current_free(self);
}
TSNode ts_tree_root_node(const TSTree *self) {
  return ts_node_new(self, &self->root, ts_subtree_padding(self->root), 0);
}
TSNode ts_tree_root_node_with_offset(
  const TSTree *self,
  uint32_t offset_bytes,
  TSPoint offset_extent
) {
  Length offset = {offset_bytes, offset_extent};
  return ts_node_new(self, &self->root, length_add(offset, ts_subtree_padding(self->root)), 0);
}
const TSLanguage *ts_tree_language(const TSTree *self) {
  return self->language;
}
void ts_tree_edit(TSTree *self, const TSInputEdit *edit) {
  for (unsigned i = 0; i < self->included_range_count; i++) {
    TSRange *range = &self->included_ranges[i];
    if (range->end_byte >= edit->old_end_byte) {
      if (range->end_byte != 4294967295U) {
        range->end_byte = edit->new_end_byte + (range->end_byte - edit->old_end_byte);
        range->end_point = point_add(
          edit->new_end_point,
          point_sub(range->end_point, edit->old_end_point)
        );
        if (range->end_byte < edit->new_end_byte) {
          range->end_byte = 4294967295U;
          range->end_point = ((TSPoint) {4294967295U, 4294967295U});
        }
      }
    } else if (range->end_byte > edit->start_byte) {
      range->end_byte = edit->start_byte;
      range->end_point = edit->start_point;
    }
    if (range->start_byte >= edit->old_end_byte) {
      range->start_byte = edit->new_end_byte + (range->start_byte - edit->old_end_byte);
      range->start_point = point_add(
        edit->new_end_point,
        point_sub(range->start_point, edit->old_end_point)
      );
      if (range->start_byte < edit->new_end_byte) {
        range->start_byte = 4294967295U;
        range->start_point = ((TSPoint) {4294967295U, 4294967295U});
      }
    } else if (range->start_byte > edit->start_byte) {
      range->start_byte = edit->start_byte;
      range->start_point = edit->start_point;
    }
  }
  SubtreePool pool = ts_subtree_pool_new(0);
  self->root = ts_subtree_edit(self->root, edit, &pool);
  ts_subtree_pool_delete(&pool);
}
TSRange *ts_tree_included_ranges(const TSTree *self, uint32_t *length) {
  *length = self->included_range_count;
  TSRange *ranges = ts_current_calloc(self->included_range_count, sizeof(TSRange));
  memcpy(ranges, self->included_ranges, self->included_range_count * sizeof(TSRange));
  return ranges;
}
TSRange *ts_tree_get_changed_ranges(const TSTree *old_tree, const TSTree *new_tree, uint32_t *length) {
  TreeCursor cursor1 = {((void *)0), { ((void *)0), 0, 0 }, 0};
  TreeCursor cursor2 = {((void *)0), { ((void *)0), 0, 0 }, 0};
  ts_tree_cursor_init(&cursor1, ts_tree_root_node(old_tree));
  ts_tree_cursor_init(&cursor2, ts_tree_root_node(new_tree));
  TSRangeArray included_range_differences = { ((void *)0), 0, 0 };
  ts_range_array_get_changed_ranges(
    old_tree->included_ranges, old_tree->included_range_count,
    new_tree->included_ranges, new_tree->included_range_count,
    &included_range_differences
  );
  TSRange *result;
  *length = ts_subtree_get_changed_ranges(
    &old_tree->root, &new_tree->root, &cursor1, &cursor2,
    old_tree->language, &included_range_differences, &result
  );
  _array__delete((Array *)(&included_range_differences));
  _array__delete((Array *)(&cursor1.stack));
  _array__delete((Array *)(&cursor2.stack));
  return result;
}
struct accessx_descriptor {
	unsigned int ad_name_offset;
	int ad_flags;
	int ad_pad[2];
};
int     getattrlistbulk(int, void *, void *, size_t, uint64_t) ;
int     getattrlistat(int, const char *, void *, void *, size_t, unsigned long) ;
int     setattrlistat(int, const char *, void *, void *, size_t, uint32_t)    ;
ssize_t freadlink(int, char * restrict, size_t) ;
typedef __darwin_gid_t  gid_t;
int     faccessat(int, const char *, int, int) ;
int     fchownat(int, const char *, uid_t, gid_t, int)  ;
int     linkat(int, const char *, int, const char *, int)       ;
ssize_t readlinkat(int, const char *, char *, size_t)   ;
int     symlinkat(const char *, int, const char *) ;
int     unlinkat(int, const char *, int) ;
typedef __darwin_useconds_t     useconds_t;
void	 _exit(int) __attribute__((__noreturn__));
int	 access(const char *, int);
unsigned int
	 alarm(unsigned int);
int	 chdir(const char *);
int	 chown(const char *, uid_t, gid_t);
int	 close(int) __asm("_" "close" );
int	 dup(int);
int	 dup2(int, int);
int	 execl(const char * __path, const char * __arg0, ...)  ;
int	 execle(const char * __path, const char * __arg0, ...)  ;
int	 execlp(const char * __file, const char * __arg0, ...)  ;
int	 execv(const char * __path, char * const * __argv)  ;
int	 execve(const char * __file, char * const * __argv, char * const * __envp)  ;
int	 execvp(const char * __file, char * const * __argv)  ;
pid_t	 fork(void)  ;
long	 fpathconf(int, int);
char	*getcwd(char *, size_t);
gid_t	 getegid(void);
uid_t	 geteuid(void);
gid_t	 getgid(void);
int	 getgroups(int, gid_t []);
char	*getlogin(void);
pid_t	 getpgrp(void);
pid_t	 getpid(void);
pid_t	 getppid(void);
uid_t	 getuid(void);
int	 isatty(int);
int	 link(const char *, const char *);
off_t	 lseek(int, off_t, int);
long	 pathconf(const char *, int);
int	 pause(void) __asm("_" "pause" );
int	 pipe(int [2]);
ssize_t	 read(int, void *, size_t) __asm("_" "read" );
int	 rmdir(const char *);
int	 setgid(gid_t);
int	 setpgid(pid_t, pid_t);
pid_t	 setsid(void);
int	 setuid(uid_t);
unsigned int
	 sleep(unsigned int) __asm("_" "sleep" );
long	 sysconf(int);
pid_t	 tcgetpgrp(int);
int	 tcsetpgrp(int, pid_t);
char	*ttyname(int);
int	 ttyname_r(int, char *, size_t) __asm("_" "ttyname_r" );
int	 unlink(const char *);
ssize_t	 write(int __fd, const void * __buf, size_t __nbyte) __asm("_" "write" );
size_t	 confstr(int, char *, size_t) __asm("_" "confstr" );
int	 getopt(int, char * const [], const char *) __asm("_" "getopt" );
extern char *optarg;
extern int optind, opterr, optopt;
__attribute__((__deprecated__))
void	*brk(const void *);
int	 chroot(const char *) ;
char	*crypt(const char *, const char *);
void	 encrypt(char *, int) __asm("_" "encrypt" );
int	 fchdir(int);
long	 gethostid(void);
pid_t	 getpgid(pid_t);
pid_t	 getsid(pid_t);
int	 getdtablesize(void) ;
int	 getpagesize(void) __attribute__((__const__)) ;
char	*getpass(const char *) ;
char	*getwd(char *) ;
int	 lchown(const char *, uid_t, gid_t) __asm("_" "lchown" );
int	 lockf(int, int, off_t) __asm("_" "lockf" );
int	 nice(int) __asm("_" "nice" );
ssize_t	 pread(int __fd, void * __buf, size_t __nbyte, off_t __offset) __asm("_" "pread" );
ssize_t	 pwrite(int __fd, const void * __buf, size_t __nbyte, off_t __offset) __asm("_" "pwrite" );
__attribute__((__deprecated__))
void	*sbrk(int);
pid_t	 setpgrp(void) __asm("_" "setpgrp" );
int	 setregid(gid_t, gid_t) __asm("_" "setregid" );
int	 setreuid(uid_t, uid_t) __asm("_" "setreuid" );
void     swab(const void * restrict, void * restrict, ssize_t);
void	 sync(void);
int	 truncate(const char *, off_t);
useconds_t	 ualarm(useconds_t, useconds_t);
int	 usleep(useconds_t) __asm("_" "usleep" );
__attribute__((__deprecated__))
pid_t	 vfork(void)  ;
int	 fsync(int) __asm("_" "fsync" );
int	 ftruncate(int, off_t);
int	 getlogin_r(char *, size_t);
int	 fchown(int, uid_t, gid_t);
int	 gethostname(char *, size_t);
ssize_t  readlink(const char * restrict, char * restrict, size_t);
int	 setegid(gid_t);
int	 seteuid(uid_t);
int	 symlink(const char *, const char *);
typedef struct fd_set {
	__int32_t       fds_bits[((((1024) % ((sizeof(__int32_t) * 8))) == 0) ? ((1024) / ((sizeof(__int32_t) * 8))) : (((1024) / ((sizeof(__int32_t) * 8))) + 1))];
} fd_set;
int __darwin_check_fd_set_overflow(int, const void *, int) ;
extern __inline __attribute__ ((__always_inline__)) int
__darwin_check_fd_set(int _a, const void *_b)
{
	if ((uintptr_t)&__darwin_check_fd_set_overflow != (uintptr_t) 0) {
		return __darwin_check_fd_set_overflow(_a, _b, 0);
	} else {
		return 1;
	}
}
extern __inline __attribute__ ((__always_inline__)) int
__darwin_fd_isset(int _fd, const struct fd_set *_p)
{
	if (__darwin_check_fd_set(_fd, (const void *) _p)) {
		return _p->fds_bits[(unsigned long)_fd / (sizeof(__int32_t) * 8)] & ((__int32_t)(((unsigned long)1) << ((unsigned long)_fd % (sizeof(__int32_t) * 8))));
	}
	return 0;
}
extern __inline __attribute__ ((__always_inline__)) void
__darwin_fd_set(int _fd, struct fd_set *const _p)
{
	if (__darwin_check_fd_set(_fd, (const void *) _p)) {
		(_p->fds_bits[(unsigned long)_fd / (sizeof(__int32_t) * 8)] |= ((__int32_t)(((unsigned long)1) << ((unsigned long)_fd % (sizeof(__int32_t) * 8)))));
	}
}
extern __inline __attribute__ ((__always_inline__)) void
__darwin_fd_clr(int _fd, struct fd_set *const _p)
{
	if (__darwin_check_fd_set(_fd, (const void *) _p)) {
		(_p->fds_bits[(unsigned long)_fd / (sizeof(__int32_t) * 8)] &= ~((__int32_t)(((unsigned long)1) << ((unsigned long)_fd % (sizeof(__int32_t) * 8)))));
	}
}
typedef __darwin_suseconds_t    suseconds_t;
int      pselect(int, fd_set * restrict, fd_set * restrict,
    fd_set * restrict, const struct timespec * restrict,
    const sigset_t * restrict)
__asm("_" "pselect" )
;
int      select(int, fd_set * restrict, fd_set * restrict,
    fd_set * restrict, struct timeval * restrict)
__asm("_" "select" )
;
typedef __darwin_uuid_t uuid_t;
void	 _Exit(int) __attribute__((__noreturn__));
int	 accessx_np(const struct accessx_descriptor *, size_t, int *, uid_t);
int	 acct(const char *);
int	 add_profil(char *, size_t, unsigned long, unsigned int)  ;
void	 endusershell(void);
int	 execvP(const char * __file, const char * __searchpath, char * const * __argv)   ;
char	*fflagstostr(unsigned long);
int	 getdomainname(char *, int);
int	 getgrouplist(const char *, int, int *, int *);
int gethostuuid(uuid_t, const struct timespec *)  ;
mode_t	 getmode(const void *, mode_t);
int	 getpeereid(int, uid_t *, gid_t *);
int	 getsgroups_np(int *, uuid_t);
char	*getusershell(void);
int	 getwgroups_np(int *, uuid_t);
int	 initgroups(const char *, int);
int	 issetugid(void);
char	*mkdtemp(char *);
int	 mknod(const char *, mode_t, dev_t);
int	 mkpath_np(const char *path, mode_t omode) ;
int	 mkpathat_np(int dfd, const char *path, mode_t omode)
		 ;
int	 mkstemp(char *);
int	 mkstemps(char *, int);
char	*mktemp(char *);
int	 mkostemp(char *path, int oflags)
		 ;
int	 mkostemps(char *path, int slen, int oflags)
		 ;
int	 mkstemp_dprotected_np(char *path, int dpclass, int dpflags)
		 ;
char   *mkdtempat_np(int dfd, char *path)
		 ;
int     mkstempsat_np(int dfd, char *path, int slen)
		 ;
int     mkostempsat_np(int dfd, char *path, int slen, int oflags)
		 ;
int	 nfssvc(int, void *);
int	 profil(char *, size_t, unsigned long, unsigned int);
__attribute__((__deprecated__))
int	 pthread_setugid_np(uid_t, gid_t);
int	 pthread_getugid_np( uid_t *, gid_t *);
int	 reboot(int);
int	 revoke(const char *);
__attribute__((__deprecated__)) int	 rcmd(char **, int, const char *, const char *, const char *, int *);
__attribute__((__deprecated__)) int	 rcmd_af(char **, int, const char *, const char *, const char *, int *,
		int);
__attribute__((__deprecated__)) int	 rresvport(int *);
__attribute__((__deprecated__)) int	 rresvport_af(int *, int);
__attribute__((__deprecated__)) int	 iruserok(unsigned long, int, const char *, const char *);
__attribute__((__deprecated__)) int	 iruserok_sa(const void *, int, int, const char *, const char *);
__attribute__((__deprecated__)) int	 ruserok(const char *, int, const char *, const char *);
int	 setdomainname(const char *, int);
int	 setgroups(int, const gid_t *);
void	 sethostid(long);
int	 sethostname(const char *, int);
void	 setkey(const char *) __asm("_" "setkey" );
int	 setlogin(const char *);
void	*setmode(const char *) __asm("_" "setmode" );
int	 setrgid(gid_t);
int	 setruid(uid_t);
int	 setsgroups_np(int, const uuid_t);
void	 setusershell(void);
int	 setwgroups_np(int, const uuid_t);
int	 strtofflags(char **, unsigned long *, unsigned long *);
int	 swapon(const char *);
int	 ttyslot(void);
int	 undelete(const char *);
int	 unwhiteout(const char *);
void	*valloc(size_t);
int	 syscall(int, ...);
extern char *suboptarg;
int	 getsubopt(char **, char * const *, char **);
int    fgetattrlist(int,void*,void*,size_t,unsigned int) ;
int    fsetattrlist(int,void*,void*,size_t,unsigned int) ;
int    getattrlist(const char*,void*,void*,size_t,unsigned int) __asm("_" "getattrlist" );
int    setattrlist(const char*,void*,void*,size_t,unsigned int) __asm("_" "setattrlist" );
int exchangedata(const char*,const char*,unsigned int)  ;
int    getdirentriesattr(int,void*,void*,size_t,unsigned int*,unsigned int*,unsigned int*,unsigned int)  ;
struct fssearchblock;
struct searchstate;
int	 searchfs(const char *, struct fssearchblock *, unsigned long *, unsigned int, unsigned int, struct searchstate *)  ;
int	 fsctl(const char *,unsigned long,void*,unsigned int);
int	 ffsctl(int,unsigned long,void*,unsigned int) ;
int	fsync_volume_np(int, int) ;
int	sync_volume_np(const char *, int) ;
extern int optreset;
int _ts_dup(int file_descriptor) {
  return dup(file_descriptor);
}
void ts_tree_print_dot_graph(const TSTree *self, int file_descriptor) {
  FILE *file = fdopen(_ts_dup(file_descriptor), "a");
  ts_subtree_print_dot_graph(self->root, self->language, file);
  fclose(file);
}
void ts_wasm_store_delete(TSWasmStore *self) {
  (void)self;
}
_Bool ts_wasm_store_start(
  TSWasmStore *self,
  TSLexer *lexer,
  const TSLanguage *language
) {
  (void)self;
  (void)lexer;
  (void)language;
  return 0;
}
void ts_wasm_store_reset(TSWasmStore *self) {
  (void)self;
}
_Bool ts_wasm_store_call_lex_main(TSWasmStore *self, TSStateId state) {
  (void)self;
  (void)state;
  return 0;
}
_Bool ts_wasm_store_call_lex_keyword(TSWasmStore *self, TSStateId state) {
  (void)self;
  (void)state;
  return 0;
}
uint32_t ts_wasm_store_call_scanner_create(TSWasmStore *self) {
  (void)self;
  return 0;
}
void ts_wasm_store_call_scanner_destroy(
  TSWasmStore *self,
  uint32_t scanner_address
) {
  (void)self;
  (void)scanner_address;
}
_Bool ts_wasm_store_call_scanner_scan(
  TSWasmStore *self,
  uint32_t scanner_address,
  uint32_t valid_tokens_ix
) {
  (void)self;
  (void)scanner_address;
  (void)valid_tokens_ix;
  return 0;
}
uint32_t ts_wasm_store_call_scanner_serialize(
  TSWasmStore *self,
  uint32_t scanner_address,
  char *buffer
) {
  (void)self;
  (void)scanner_address;
  (void)buffer;
  return 0;
}
void ts_wasm_store_call_scanner_deserialize(
  TSWasmStore *self,
  uint32_t scanner_address,
  const char *buffer,
  unsigned length
) {
  (void)self;
  (void)scanner_address;
  (void)buffer;
  (void)length;
}
_Bool ts_wasm_store_has_error(const TSWasmStore *self) {
  (void)self;
  return 0;
}
_Bool ts_language_is_wasm(const TSLanguage *self) {
  (void)self;
  return 0;
}
void ts_wasm_language_retain(const TSLanguage *self) {
  (void)self;
}
void ts_wasm_language_release(const TSLanguage *self) {
  (void)self;
}
typedef struct dl_info {
        const char      *dli_fname;
        void            *dli_fbase;
        const char      *dli_sname;
        void            *dli_saddr;
} Dl_info;
extern int dladdr(const void *, Dl_info *);
extern int dlclose(void * __handle) ;
extern char * dlerror(void) ;
extern void * dlopen(const char * __path, int __mode) ;
extern void * dlsym(void * __handle, const char * __symbol);
extern _Bool dlopen_preflight(const char* __path)  ;
    typedef float float_t;
    typedef double double_t;
extern int __math_errhandling(void);
extern int __fpclassifyf(float);
extern int __fpclassifyd(double);
extern int __fpclassifyl(long double);
extern int __isnormalf(float);
extern int __isnormald(double);
extern int __isnormall(long double);
extern int __isfinitef(float);
extern int __isfinited(double);
extern int __isfinitel(long double);
extern int __isinff(float);
extern int __isinfd(double);
extern int __isinfl(long double);
extern int __isnanf(float);
extern int __isnand(double);
extern int __isnanl(long double);
extern int __signbitf(float);
extern int __signbitd(double);
extern int __signbitl(long double);
extern float acosf(float);
extern double acos(double);
extern long double acosl(long double);
extern float asinf(float);
extern double asin(double);
extern long double asinl(long double);
extern float atanf(float);
extern double atan(double);
extern long double atanl(long double);
extern float atan2f(float, float);
extern double atan2(double, double);
extern long double atan2l(long double, long double);
extern float cosf(float);
extern double cos(double);
extern long double cosl(long double);
extern float sinf(float);
extern double sin(double);
extern long double sinl(long double);
extern float tanf(float);
extern double tan(double);
extern long double tanl(long double);
extern float acoshf(float);
extern double acosh(double);
extern long double acoshl(long double);
extern float asinhf(float);
extern double asinh(double);
extern long double asinhl(long double);
extern float atanhf(float);
extern double atanh(double);
extern long double atanhl(long double);
extern float coshf(float);
extern double cosh(double);
extern long double coshl(long double);
extern float sinhf(float);
extern double sinh(double);
extern long double sinhl(long double);
extern float tanhf(float);
extern double tanh(double);
extern long double tanhl(long double);
extern float expf(float);
extern double exp(double);
extern long double expl(long double);
extern float exp2f(float);
extern double exp2(double);
extern long double exp2l(long double);
extern float expm1f(float);
extern double expm1(double);
extern long double expm1l(long double);
extern float logf(float);
extern double log(double);
extern long double logl(long double);
extern float log10f(float);
extern double log10(double);
extern long double log10l(long double);
extern float log2f(float);
extern double log2(double);
extern long double log2l(long double);
extern float log1pf(float);
extern double log1p(double);
extern long double log1pl(long double);
extern float logbf(float);
extern double logb(double);
extern long double logbl(long double);
extern float modff(float, float *);
extern double modf(double, double *);
extern long double modfl(long double, long double *);
extern float ldexpf(float, int);
extern double ldexp(double, int);
extern long double ldexpl(long double, int);
extern float frexpf(float, int *);
extern double frexp(double, int *);
extern long double frexpl(long double, int *);
extern int ilogbf(float);
extern int ilogb(double);
extern int ilogbl(long double);
extern float scalbnf(float, int);
extern double scalbn(double, int);
extern long double scalbnl(long double, int);
extern float scalblnf(float, long int);
extern double scalbln(double, long int);
extern long double scalblnl(long double, long int);
extern float fabsf(float);
extern double fabs(double);
extern long double fabsl(long double);
extern float cbrtf(float);
extern double cbrt(double);
extern long double cbrtl(long double);
extern float hypotf(float, float);
extern double hypot(double, double);
extern long double hypotl(long double, long double);
extern float powf(float, float);
extern double pow(double, double);
extern long double powl(long double, long double);
extern float sqrtf(float);
extern double sqrt(double);
extern long double sqrtl(long double);
extern float erff(float);
extern double erf(double);
extern long double erfl(long double);
extern float erfcf(float);
extern double erfc(double);
extern long double erfcl(long double);
extern float lgammaf(float);
extern double lgamma(double);
extern long double lgammal(long double);
extern float tgammaf(float);
extern double tgamma(double);
extern long double tgammal(long double);
extern float ceilf(float);
extern double ceil(double);
extern long double ceill(long double);
extern float floorf(float);
extern double floor(double);
extern long double floorl(long double);
extern float nearbyintf(float);
extern double nearbyint(double);
extern long double nearbyintl(long double);
extern float rintf(float);
extern double rint(double);
extern long double rintl(long double);
extern long int lrintf(float);
extern long int lrint(double);
extern long int lrintl(long double);
extern float roundf(float);
extern double round(double);
extern long double roundl(long double);
extern long int lroundf(float);
extern long int lround(double);
extern long int lroundl(long double);
extern long long int llrintf(float);
extern long long int llrint(double);
extern long long int llrintl(long double);
extern long long int llroundf(float);
extern long long int llround(double);
extern long long int llroundl(long double);
extern float truncf(float);
extern double trunc(double);
extern long double truncl(long double);
extern float fmodf(float, float);
extern double fmod(double, double);
extern long double fmodl(long double, long double);
extern float remainderf(float, float);
extern double remainder(double, double);
extern long double remainderl(long double, long double);
extern float remquof(float, float, int *);
extern double remquo(double, double, int *);
extern long double remquol(long double, long double, int *);
extern float copysignf(float, float);
extern double copysign(double, double);
extern long double copysignl(long double, long double);
extern float nanf(const char *);
extern double nan(const char *);
extern long double nanl(const char *);
extern float nextafterf(float, float);
extern double nextafter(double, double);
extern long double nextafterl(long double, long double);
extern double nexttoward(double, long double);
extern float nexttowardf(float, long double);
extern long double nexttowardl(long double, long double);
extern float fdimf(float, float);
extern double fdim(double, double);
extern long double fdiml(long double, long double);
extern float fmaxf(float, float);
extern double fmax(double, double);
extern long double fmaxl(long double, long double);
extern float fminf(float, float);
extern double fmin(double, double);
extern long double fminl(long double, long double);
extern float fmaf(float, float, float);
extern double fma(double, double, double);
extern long double fmal(long double, long double, long double);
extern float __exp10f(float) ;
extern double __exp10(double) ;
extern __inline __attribute__ ((__always_inline__)) void __sincosf(float __x, float *__sinp, float *__cosp);
extern __inline __attribute__ ((__always_inline__)) void __sincos(double __x, double *__sinp, double *__cosp);
extern float __cospif(float) ;
extern double __cospi(double) ;
extern float __sinpif(float) ;
extern double __sinpi(double) ;
extern float __tanpif(float) ;
extern double __tanpi(double) ;
extern _Float16 __fabsf16(_Float16) ;
extern _Float16 __hypotf16(_Float16, _Float16) ;
extern _Float16 __sqrtf16(_Float16) ;
extern _Float16 __ceilf16(_Float16) ;
extern _Float16 __floorf16(_Float16) ;
extern _Float16 __rintf16(_Float16) ;
extern _Float16 __roundf16(_Float16) ;
extern _Float16 __truncf16(_Float16) ;
extern _Float16 __copysignf16(_Float16, _Float16) ;
extern _Float16 __nextafterf16(_Float16, _Float16) ;
extern _Float16 __fmaxf16(_Float16, _Float16) ;
extern _Float16 __fminf16(_Float16, _Float16) ;
extern _Float16 __fmaf16(_Float16, _Float16, _Float16) ;
extern __inline __attribute__ ((__always_inline__)) void __sincospif(float __x, float *__sinp, float *__cosp);
extern __inline __attribute__ ((__always_inline__)) void __sincospi(double __x, double *__sinp, double *__cosp);
struct __float2 { float __sinval; float __cosval; };
struct __double2 { double __sinval; double __cosval; };
extern struct __float2 __sincosf_stret(float);
extern struct __double2 __sincos_stret(double);
extern struct __float2 __sincospif_stret(float);
extern struct __double2 __sincospi_stret(double);
extern __inline __attribute__ ((__always_inline__)) void __sincosf(float __x, float *__sinp, float *__cosp) {
    const struct __float2 __stret = __sincosf_stret(__x);
    *__sinp = __stret.__sinval; *__cosp = __stret.__cosval;
}
extern __inline __attribute__ ((__always_inline__)) void __sincos(double __x, double *__sinp, double *__cosp) {
    const struct __double2 __stret = __sincos_stret(__x);
    *__sinp = __stret.__sinval; *__cosp = __stret.__cosval;
}
extern __inline __attribute__ ((__always_inline__)) void __sincospif(float __x, float *__sinp, float *__cosp) {
    const struct __float2 __stret = __sincospif_stret(__x);
    *__sinp = __stret.__sinval; *__cosp = __stret.__cosval;
}
extern __inline __attribute__ ((__always_inline__)) void __sincospi(double __x, double *__sinp, double *__cosp) {
    const struct __double2 __stret = __sincospi_stret(__x);
    *__sinp = __stret.__sinval; *__cosp = __stret.__cosval;
}
extern double j0(double) ;
extern double j1(double) ;
extern double jn(int, double) ;
extern double y0(double) ;
extern double y1(double) ;
extern double yn(int, double) ;
extern double scalb(double, double);
extern int signgam;
struct exception {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
};
enum moonbit_block_kind {
  moonbit_BLOCK_KIND_REGULAR = 0,
  moonbit_BLOCK_KIND_REF_ARRAY = 1,
  moonbit_BLOCK_KIND_VAL_ARRAY = 2
};
struct moonbit_object {
  int32_t rc;
  uint32_t meta;
};
void *moonbit_malloc(size_t size);
void moonbit_incref(void *obj);
void moonbit_decref(void *obj);
typedef uint16_t *moonbit_string_t;
typedef uint8_t *moonbit_bytes_t;
moonbit_string_t moonbit_make_string(int32_t size, uint16_t value);
moonbit_bytes_t moonbit_make_bytes(int32_t size, int value);
int32_t *moonbit_make_int32_array(int32_t len, int32_t value);
void **moonbit_make_ref_array(int32_t len, void *value);
int64_t *moonbit_make_int64_array(int32_t len, int64_t value);
double *moonbit_make_double_array(int32_t len, double value);
float *moonbit_make_float_array(int32_t len, float value);
void **moonbit_make_extern_ref_array(int32_t len, void *value);
void *
moonbit_c_null() {
  return ((void *)0);
}
_Bool
moonbit_c_is_null(void *ptr) {
  return ptr == ((void *)0);
}
TSLanguage *
moonbit_ts_language_load(moonbit_bytes_t pathname, moonbit_bytes_t symbol) {
  void *handle = dlopen((const char *)pathname, 0x2);
  if (!handle) {
    moonbit_decref(pathname);
    moonbit_decref(symbol);
    return ((void *)0);
  }
  TSLanguage *(*load)(void) = dlsym(handle, (const char *)symbol);
  moonbit_decref(pathname);
  moonbit_decref(symbol);
  if (!load) {
    dlclose(handle);
    return ((void *)0);
  }
  return load();
}
const TSLanguage *
moonbit_ts_language_copy(TSLanguage *self) {
  return ts_language_copy(self);
}
void
moonbit_ts_language_delete(TSLanguage *self) {
  ts_language_delete(self);
}
uint32_t
moonbit_ts_language_symbol_count(TSLanguage *self) {
  return ts_language_symbol_count(self);
}
uint32_t
moonbit_ts_language_state_count(TSLanguage *self) {
  return ts_language_state_count(self);
}
_Static_assert( _Generic((TSSymbol)0, uint16_t: 1, default: 0), "TSSymbol" " is not " "uint16_t" );
TSSymbol
moonbit_ts_language_symbol_for_name(
  TSLanguage *self,
  moonbit_bytes_t name,
  _Bool is_named
) {
  uint32_t length = (((struct moonbit_object*)(name) - 1)->meta & (((uint32_t)1 << 28) - 1));
  TSSymbol symbol =
    ts_language_symbol_for_name(self, (const char *)name, length, is_named);
  moonbit_decref(name);
  return symbol;
}
uint32_t
moonbit_ts_language_field_count(TSLanguage *self) {
  return ts_language_field_count(self);
}
moonbit_bytes_t
moonbit_ts_language_field_name_for_id(TSLanguage *self, TSFieldId id) {
  const char *name = ts_language_field_name_for_id(self, id);
  size_t length = strlen(name);
  moonbit_bytes_t bytes = moonbit_make_bytes(length, 0);
  memcpy(bytes, name, length);
  return bytes;
}
TSFieldId
moonbit_ts_language_field_id_for_name(TSLanguage *self, moonbit_bytes_t name) {
  uint32_t length = (((struct moonbit_object*)(name) - 1)->meta & (((uint32_t)1 << 28) - 1));
  TSFieldId id =
    ts_language_field_id_for_name(self, (const char *)name, length);
  moonbit_decref(name);
  return id;
}
TSSymbol *
moonbit_ts_language_supertypes(TSLanguage *self) {
  uint32_t length;
  const TSSymbol *supertypes = ts_language_supertypes(self, &length);
  TSSymbol *copy = (TSSymbol *)moonbit_malloc(length * sizeof(TSSymbol));
  memcpy(copy, supertypes, length * sizeof(TSSymbol));
  return copy;
}
TSSymbol *
moonbit_ts_language_subtypes(TSLanguage *self, TSSymbol supertype) {
  uint32_t length;
  const TSSymbol *subtypes = ts_language_subtypes(self, supertype, &length);
  TSSymbol *copy = (TSSymbol *)moonbit_malloc(length * sizeof(TSSymbol));
  memcpy(copy, subtypes, length * sizeof(TSSymbol));
  return copy;
}
moonbit_bytes_t
moonbit_ts_language_symbol_name(TSLanguage *self, TSSymbol symbol) {
  const char *name = ts_language_symbol_name(self, symbol);
  size_t length = strlen(name);
  moonbit_bytes_t bytes = moonbit_make_bytes(length, 0);
  memcpy(bytes, name, length);
  return bytes;
}
_Static_assert( _Generic((TSSymbolType)0, uint32_t: 1, default: 0), "TSSymbolType" " is not " "uint32_t" );
TSSymbolType
moonbit_ts_language_symbol_type(TSLanguage *self, TSSymbol symbol) {
  return ts_language_symbol_type(self, symbol);
}
uint32_t
moonbit_ts_language_version(TSLanguage *self) {
  return ts_language_version(self);
}
uint32_t
moonbit_ts_language_abi_version(TSLanguage *self) {
  return ts_language_abi_version(self);
}
moonbit_bytes_t
moonbit_ts_language_metadata(TSLanguage *self) {
  const TSLanguageMetadata *metadata = ts_language_metadata(self);
  moonbit_bytes_t bytes = moonbit_make_bytes(3, 0);
  bytes[0] = metadata->major_version;
  bytes[1] = metadata->minor_version;
  bytes[2] = metadata->patch_version;
  return bytes;
}
_Static_assert( _Generic((TSStateId)0, uint16_t: 1, default: 0), "TSStateId" " is not " "uint16_t" );
TSStateId
moonbit_ts_language_next_state(
  TSLanguage *self,
  TSStateId state,
  TSSymbol symbol
) {
  return ts_language_next_state(self, state, symbol);
}
moonbit_bytes_t
moonbit_ts_language_name(TSLanguage *self) {
  const char *name = ts_language_name(self);
  size_t length = strlen(name);
  moonbit_bytes_t bytes = moonbit_make_bytes(length, 0);
  memcpy(bytes, name, length);
  return bytes;
}
TSParser *
moonbit_ts_parser_new() {
  return ts_parser_new();
}
void
moonbit_ts_parser_delete(TSParser *parser) {
  ts_parser_delete(parser);
}
const TSLanguage *
moonbit_ts_parser_language(const TSParser *parser) {
  return ts_parser_language(parser);
}
_Bool
moonbit_ts_parser_set_language(TSParser *parser, TSLanguage *language) {
  return ts_parser_set_language(parser, language);
}
void
moonbit_ts_parser_set_included_ranges(TSParser *parser, TSRange *ranges) {
  size_t length = (((struct moonbit_object*)(ranges) - 1)->meta & (((uint32_t)1 << 28) - 1));
  ts_parser_set_included_ranges(
    parser, ranges, length * sizeof(uint32_t) / sizeof(TSRange)
  );
}
TSRange *
moonbit_ts_parser_included_ranges(const TSParser *self) {
  uint32_t count = 0;
  const TSRange *ranges = ts_parser_included_ranges(self, &count);
  TSRange *copy = (TSRange *)moonbit_malloc(count * sizeof(TSRange));
  memcpy(copy, ranges, count * sizeof(TSRange));
  return copy;
}
struct MoonBitTSInputRead {
  moonbit_bytes_t (*read)(
    struct MoonBitTSInputRead *payload,
    uint32_t byte,
    TSPoint *position
  );
};
const char *
moonbit_ts_input_read(
  void *payload,
  uint32_t byte,
  TSPoint position,
  uint32_t *bytes_read
) {
  struct MoonBitTSInputRead *input = (struct MoonBitTSInputRead *)payload;
  TSPoint *point = (TSPoint *)moonbit_malloc(sizeof(struct TSPoint));
  *point = position;
  moonbit_bytes_t bytes = input->read(input, byte, point);
  *bytes_read = (((struct moonbit_object*)(bytes) - 1)->meta & (((uint32_t)1 << 28) - 1));
  return (const char *)bytes;
}
TSTree *
moonbit_ts_parser_parse(
  TSParser *self,
  TSTree *old_tree,
  struct MoonBitTSInputRead *input,
  TSInputEncoding encoding,
  DecodeFunction decode
) {
  TSInput ts_input = {
    .payload = input,
    .read = moonbit_ts_input_read,
    .encoding = encoding,
    .decode = decode
  };
  return ts_parser_parse(self, old_tree, ts_input);
}
struct MoonBitTSParseOptionsProgressCallback {
  _Bool (*progress_callback)(
    struct MoonBitTSParseOptionsProgressCallback *callback,
    uint32_t current_byte_offset,
    _Bool has_error
  );
};
_Bool
moonbit_ts_parse_options_progress_callback(TSParseState *state) {
  struct MoonBitTSParseOptionsProgressCallback *callback =
    (struct MoonBitTSParseOptionsProgressCallback *)state->payload;
  return callback->progress_callback(
    callback, state->current_byte_offset, state->has_error
  );
}
TSTree *
moonbit_ts_parser_parse_with_options(
  TSParser *self,
  TSTree *old_tree,
  struct MoonBitTSInputRead *input,
  TSInputEncoding encoding,
  DecodeFunction decode,
  struct MoonBitTSParseOptionsProgressCallback *callback
) {
  TSInput ts_input = {
    .payload = input,
    .read = moonbit_ts_input_read,
    .encoding = encoding,
    .decode = decode
  };
  TSParseOptions options = {
    .payload = callback,
    .progress_callback = moonbit_ts_parse_options_progress_callback
  };
  return ts_parser_parse_with_options(self, old_tree, ts_input, options);
}
TSTree *
moonbit_ts_parser_parse_string(
  TSParser *parser,
  TSTree *old_tree,
  moonbit_bytes_t bytes
) {
  uint32_t length = (((struct moonbit_object*)(bytes) - 1)->meta & (((uint32_t)1 << 28) - 1));
  TSTree *tree =
    ts_parser_parse_string(parser, old_tree, (const char *)bytes, length);
  moonbit_decref(bytes);
  return tree;
}
TSTree *
moonbit_ts_parser_parse_string_encoding(
  TSParser *parser,
  TSTree *old_tree,
  moonbit_bytes_t bytes,
  TSInputEncoding encoding
) {
  uint32_t length = (((struct moonbit_object*)(bytes) - 1)->meta & (((uint32_t)1 << 28) - 1));
  TSTree *tree =
    ts_parser_parse_string(parser, old_tree, (const char *)bytes, length);
  moonbit_decref(bytes);
  return tree;
}
void
moonbit_ts_parser_reset(TSParser *self) {
  ts_parser_reset(self);
}
struct MoonBitTSLogger {
  void (*log)(
    struct MoonBitTSLogger *payload,
    TSLogType log_type,
    moonbit_bytes_t buffer
  );
};
void
moonbit_ts_logger_log(void *payload, TSLogType log_type, const char *buffer) {
  struct MoonBitTSLogger *logger = (struct MoonBitTSLogger *)payload;
  size_t length = strlen(buffer);
  moonbit_bytes_t bytes = moonbit_make_bytes(length, 0);
  memcpy(bytes, buffer, length);
  logger->log(logger, log_type, bytes);
}
void
moonbit_ts_parser_set_logger(TSParser *self, struct MoonBitTSLogger *logger) {
  TSLogger ts_logger = {.payload = logger, .log = moonbit_ts_logger_log};
  ts_parser_set_logger(self, ts_logger);
}
struct MoonBitTSLogger *
moonbit_ts_parser_logger(const TSParser *self) {
  TSLogger logger = ts_parser_logger(self);
  return logger.payload;
}
void
moonbit_ts_tree_edit(TSTree *tree, TSInputEdit *edit) {
  ts_tree_edit(tree, edit);
  moonbit_decref(edit);
}
void
moonbit_ts_tree_delete(TSTree *tree) {
  ts_tree_delete(tree);
}
TSNode *
moonbit_ts_tree_root_node(TSTree *tree) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_tree_root_node(tree);
  return node;
}
TSTree *
moonbit_ts_tree_copy(TSTree *self) {
  return ts_tree_copy(self);
}
TSNode *
moonbit_ts_node_child(TSNode *self, uint32_t child_index) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_child(*self, child_index);
  moonbit_decref(self);
  return node;
}
TSNode *
moonbit_ts_node_named_child(TSNode *self, uint32_t child_index) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_named_child(*self, child_index);
  moonbit_decref(self);
  return node;
}
uint32_t
moonbit_ts_node_child_count(TSNode *self) {
  int count = ts_node_child_count(*self);
  moonbit_decref(self);
  return count;
}
uint32_t
moonbit_ts_node_named_child_count(TSNode *self) {
  int count = ts_node_named_child_count(*self);
  moonbit_decref(self);
  return count;
}
moonbit_bytes_t
moonbit_ts_node_string(TSNode *self) {
  char *string = ts_node_string(*self);
  moonbit_decref(self);
  size_t length = strlen(string);
  moonbit_bytes_t bytes = moonbit_make_bytes(length, 0);
  memcpy(bytes, string, length);
  free(string);
  return bytes;
}
moonbit_bytes_t
moonbit_ts_node_type(TSNode *self) {
  const char *type = ts_node_type(*self);
  moonbit_decref(self);
  moonbit_bytes_t bytes = moonbit_make_bytes(strlen(type), 0);
  memcpy(bytes, type, strlen(type));
  return bytes;
}
uint32_t
moonbit_ts_node_start_byte(TSNode *self) {
  uint32_t byte = ts_node_start_byte(*self);
  moonbit_decref(self);
  return byte;
}
uint32_t
moonbit_ts_node_end_byte(TSNode *self) {
  uint32_t byte = ts_node_end_byte(*self);
  moonbit_decref(self);
  return byte;
}
TSPoint *
moonbit_ts_node_start_point(TSNode *self) {
  TSPoint *point = (TSPoint *)moonbit_malloc(sizeof(struct TSPoint));
  *point = ts_node_start_point(*self);
  moonbit_decref(self);
  return point;
}
TSPoint *
moonbit_ts_node_end_point(TSNode *self) {
  TSPoint *point = (TSPoint *)moonbit_malloc(sizeof(struct TSPoint));
  *point = ts_node_end_point(*self);
  moonbit_decref(self);
  return point;
}
TSNode *
moonbit_ts_node_next_sibling(TSNode *self) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_next_sibling(*self);
  moonbit_decref(self);
  return node;
}
TSNode *
moonbit_ts_node_prev_sibling(TSNode *self) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_prev_sibling(*self);
  moonbit_decref(self);
  return node;
}
TSNode *
moonbit_ts_node_next_named_sibling(TSNode *self) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_next_named_sibling(*self);
  moonbit_decref(self);
  return node;
}
TSNode *
moonbit_ts_node_prev_named_sibling(TSNode *self) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_prev_named_sibling(*self);
  moonbit_decref(self);
  return node;
}
_Bool
moonbit_ts_node_is_null(TSNode *self) {
  _Bool is_null = ts_node_is_null(*self);
  moonbit_decref(self);
  return is_null;
}
_Bool
moonbit_ts_node_is_named(TSNode *self) {
  _Bool is_named = ts_node_is_named(*self);
  moonbit_decref(self);
  return is_named;
}
TSNode *
moonbit_ts_node_parent(TSNode *self) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_parent(*self);
  moonbit_decref(self);
  return node;
}
TSNode *
moonbit_ts_node_child_by_field_name(TSNode *self, moonbit_bytes_t name) {
  uint32_t length = (((struct moonbit_object*)(name) - 1)->meta & (((uint32_t)1 << 28) - 1));
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_child_by_field_name(*self, (const char *)name, length);
  moonbit_decref(self);
  moonbit_decref(name);
  return node;
}
TSNode *
moonbit_ts_node_child_by_field_id(TSNode *self, TSFieldId field_id) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_node_child_by_field_id(*self, field_id);
  moonbit_decref(self);
  return node;
}
void
moonbit_ts_node_edit(TSNode *self, TSInputEdit *edit) {
  ts_node_edit(self, edit);
  moonbit_decref(self);
  moonbit_decref(edit);
}
TSTreeCursor *
moonbit_ts_tree_cursor_new(TSNode *node) {
  TSTreeCursor *cursor =
    (TSTreeCursor *)moonbit_malloc(sizeof(struct TSTreeCursor));
  *cursor = ts_tree_cursor_new(*node);
  moonbit_decref(node);
  return cursor;
}
_Bool
moonbit_ts_tree_cursor_goto_parent(TSTreeCursor *self) {
  _Bool result = ts_tree_cursor_goto_parent(self);
  moonbit_decref(self);
  return result;
}
_Bool
moonbit_ts_tree_cursor_goto_next_sibling(TSTreeCursor *self) {
  _Bool result = ts_tree_cursor_goto_next_sibling(self);
  moonbit_decref(self);
  return result;
}
_Bool
moonbit_ts_tree_cursor_goto_first_child(TSTreeCursor *self) {
  _Bool result = ts_tree_cursor_goto_first_child(self);
  moonbit_decref(self);
  return result;
}
TSNode *
moonbit_ts_tree_cursor_current_node(TSTreeCursor *self) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = ts_tree_cursor_current_node(self);
  moonbit_decref(self);
  return node;
}
moonbit_bytes_t
moonbit_ts_tree_cursor_current_field_name(TSTreeCursor *self) {
  const char *name = ts_tree_cursor_current_field_name(self);
  size_t length = strlen(name);
  moonbit_bytes_t bytes = moonbit_make_bytes(length, 0);
  memcpy(bytes, name, length);
  moonbit_decref(self);
  return bytes;
}
TSFieldId
moonbit_ts_tree_cursor_current_field_id(TSTreeCursor *self) {
  TSFieldId id = ts_tree_cursor_current_field_id(self);
  moonbit_decref(self);
  return id;
}
void
moonbit_ts_tree_cursor_delete(TSTreeCursor *self) {
  ts_tree_cursor_delete(self);
  moonbit_decref(self);
}
TSQuery *
moonbit_ts_query_new(
  TSLanguage *language,
  moonbit_bytes_t source,
  uint32_t *error
) {
  uint32_t length = (((struct moonbit_object*)(source) - 1)->meta & (((uint32_t)1 << 28) - 1));
  TSQuery *query =
    ts_query_new(language, (const char *)source, length, error, error + 1);
  moonbit_decref(source);
  return query;
}
void
moonbit_ts_query_delete(TSQuery *self) {
  ts_query_delete(self);
}
TSQueryCursor *
moonbit_ts_query_cursor_new() {
  return ts_query_cursor_new();
}
void
moonbit_ts_query_cursor_exec(
  TSQueryCursor *self,
  TSQuery *query,
  TSNode *node
) {
  ts_query_cursor_exec(self, query, *node);
  moonbit_decref(node);
}
void
moonbit_ts_query_cursor_set_byte_range(
  TSQueryCursor *self,
  uint32_t start_byte,
  uint32_t end_byte
) {
  ts_query_cursor_set_byte_range(self, start_byte, end_byte);
}
void
moonbit_ts_query_cursor_set_point_range(
  TSQueryCursor *self,
  TSPoint *start_point,
  TSPoint *end_point
) {
  ts_query_cursor_set_point_range(self, *start_point, *end_point);
  moonbit_decref(start_point);
  moonbit_decref(end_point);
}
uint32_t
moonbit_ts_query_match_id(TSQueryMatch *self) {
  uint32_t id = self->id;
  moonbit_decref(self);
  return id;
}
uint16_t
moonbit_ts_query_match_pattern_index(TSQueryMatch *self) {
  uint16_t index = self->pattern_index;
  moonbit_decref(self);
  return index;
}
uint16_t
moonbit_ts_query_match_capture_count(TSQueryMatch *self) {
  uint16_t count = self->capture_count;
  moonbit_decref(self);
  return count;
}
TSNode *
moonbit_ts_query_match_captures_get_node(TSQueryMatch *self, uint32_t index) {
  TSNode *node = (TSNode *)moonbit_malloc(sizeof(struct TSNode));
  *node = self->captures[index].node;
  moonbit_decref(self);
  return node;
}
uint32_t
moonbit_ts_query_match_captures_get_index(TSQueryMatch *self, uint32_t index) {
  uint32_t i = self->captures[index].index;
  moonbit_decref(self);
  return i;
}
TSQueryMatch *
moonbit_ts_query_cursor_next_match(TSQueryCursor *self) {
  TSQueryMatch *match =
    (TSQueryMatch *)moonbit_malloc(sizeof(struct TSQueryMatch));
  _Bool has_match = ts_query_cursor_next_match(self, match);
  if (has_match) {
    return match;
  } else {
    return ((void *)0);
  }
}
void
moonbit_ts_query_cursor_delete(TSQueryCursor *self) {
  ts_query_cursor_delete(self);
}
