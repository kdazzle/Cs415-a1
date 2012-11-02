/* xeroskernel.h - disable, enable, halt, restore, isodd, min, max */

/* Symbolic constants used throughout Xinu */

typedef	char		Bool;		/* Boolean type			*/
#define	FALSE		0		/* Boolean constants		*/
#define	TRUE		1
#define	EMPTY		(-1)		/* an illegal gpq		*/
#define	NULL		0		/* Null pointer for linked lists*/
#define	NULLCH		'\0'		/* The null character		*/


/* Universal return constants */

#define	OK		 1		/* system call ok		*/
#define	SYSERR		-1		/* system call failed		*/
#define	EOF		-2		/* End-of-file (usu. from read)	*/
#define	TIMEOUT		-3		/* time out  (usu. recvtim)	*/
#define	INTRMSG		-4		/* keyboard "intr" key pressed	*/
					/*  (usu. defined as ^B)	*/
#define	BLOCKERR	-5		/* non-blocking op would block	*/

/* Functions defined by startup code */


void bzero(void *base, int cnt);
void bcopy(const void *src, void *dest, unsigned int n);
int kprintf(char * fmt, ...);
void lidt(void);
void init8259(void);
void disable(void);
void outb(unsigned int, unsigned char);
unsigned char inb(unsigned int);

extern void kmeminit(void);
extern void *kmalloc(int size);
extern void kfree(void *ptr);

#define MAX_PROC        64
#define KERNEL_INT      80
#define TIMER_INT       32
#define PROC_STACK      (4096 * 4)

#define STATE_STOPPED   0
#define STATE_READY     1
#define STATE_BLOCKED   4

#define SYS_STOP        0
#define SYS_YIELD       1
#define SYS_CREATE      2
#define SYS_TIMER       3
#define SYS_BLOCK       4
#define SYS_SEND        5
#define SYS_RECEIVE     6

typedef void    (*funcptr)(void);

typedef struct struct_pcb pcb;
struct struct_pcb {
    long        esp;
    pcb         *next;
    pcb* prev;
    int         state;
    unsigned int pid;
    pcb* senderQueue;
    int         ret;
    long        args;
    unsigned int stackSize;
};

typedef struct messageData {
    unsigned int messagePid;
    void* buffer;
    int buffer_len;
} messageData;

extern pcb     proctab[MAX_PROC];
#pragma pack(1)

typedef struct context_frame {
  unsigned int        edi;
  unsigned int        esi;
  unsigned int        ebp;
  unsigned int        esp;
  unsigned int        ebx;
  unsigned int        edx;
  unsigned int        ecx;
  unsigned int        eax;
  unsigned int        iret_eip;
  unsigned int        iret_cs;
  unsigned int        eflags;
  unsigned int        stackSlots[0];
} context_frame;

extern pcb      proctab[MAX_PROC];

extern unsigned short getCS(void);
extern void     kmeminit( void );
extern void     *kmalloc( int size );
extern void     dispatch( void );
extern void     dispatchinit( void );
extern void     ready( pcb *p );
extern pcb      *next( void );
extern void block(pcb *p);
extern void     contextinit( void );
extern int      contextswitch( pcb *p );
extern int      create( funcptr fp, int stack );
extern void     set_evec(unsigned int xnum, unsigned long handler);
extern int      syscreate( funcptr fp, int stack );
extern int      sysyield( void );
extern int      sysstop( void );
extern int systimerint();
extern unsigned int sysgetpid();
extern unsigned int getCurrentPid();
extern pcb* getCurrentProcess();
extern unsigned int getSysStopAddr();
extern void sysputs(char *str);
extern int syssend(unsigned int dest_pid, void *buffer, int buffer_len);
extern int sysrecv(unsigned int *from_pid, void *buffer, int buffer_len);
extern pcb* getProcessByPid(unsigned int pid);
extern context_frame* getProcessContext(pcb* proc);

extern void idleproc( void );


extern int send(unsigned int dest_pid, void *buffer, int buffer_len, pcb* sndProc);
extern int recv(pcb* receiver, unsigned int* from_pid, void* buffer, int buffer_len);

extern void     root( void );

void printCF (void * stack);

int syscall(int call, ...);
/* int syscreate(void (*func)(), int stack); */
int sysyield(void);
int sysstop(void);

