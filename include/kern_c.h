#include "mmu.h"
#include "lib.h"

struct ipcmsg;

// console.c
void            consoleintr(int(*)(void));

// kbd.c
void            kbdintr(void);

// swtch.S
struct context;
void            swtch(struct context**, struct context*);

// trap.c
extern struct segdesc bootgdt[NSEGS];

// syscalls
struct stat;
struct sockaddr;

int sys_chdir(const char*);
int sys_close(int);
int sys_dup(int);
int sys_exec(const char*, u64);
int sys_exit(void) __attribute__((noreturn));
int sys_fork(int);
int sys_fstat(int, struct stat*);
int sys_getpid(void);
int sys_kill(int);
int sys_link(const char*, const char*);
int sys_mkdirat(int, const char*);
int sys_mknod(const char*, int, int);
int sys_openat(int, const char*, int);
int sys_pipe(int*);
ssize_t sys_read(int, void*, size_t);
char* sys_sbrk(int);
int sys_nsleep(u64);
int sys_unlink(const char*);
int sys_wait(void);
ssize_t sys_write(int, const void*, size_t);
u64 sys_uptime(void);
int sys_map(uptr, size_t);
int sys_unmap(uptr, size_t);
int sys_halt(void);
int sys_socket(int, int, int);
int sys_bind(int xsock, const struct sockaddr *xaddr, int xaddrlen);
int sys_listen(int, int);
int sys_accept(int, struct sockaddr*, int*);
ssize_t sys_pread(int fd, void *ubuf, size_t count, off_t offset);
long sys_async(int, size_t, off_t, u32, u32);
long sys_script(void *addr, u64 len, u64 chunk);
int sys_setfs(u64 base);
long sys_wqwait(void);
int sys_setaffinity(int cpu);
long sys_futex(const u64* addr, int op, u64 val, u64 timer);
extern long (*syscalls[])(u64, u64, u64, u64, u64);

// other exported/imported functions
void cmain(u64 mbmagic, u64 mbaddr);
void mpboot(void);
void trapret(void);
void threadstub(void);
void threadhelper(void (*fn)(void *), void *arg);

struct trapframe;
void trap(struct trapframe *tf);
void sysentry(void);
u64 sysentry_c(u64 a0, u64 a1, u64 a2, u64 a3, u64 a4, u64 num);
