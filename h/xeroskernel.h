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

/* Processes */
#define CREATE		1
#define YIELD		2
#define STOP		3

#define RUNNING		1
#define READY		2
#define BLOCKED		3
#define STOPPED		4		


/* structures */
struct processStack {
        int size;
        unsigned short cs;
        unsigned char dataStart[0];
};
struct pcb {
	int pid;
	struct processStack* stack;
	struct pcb* next;
	struct pcb* prev;
};

/* Functions defined by startup code */


void bzero(void *base, int cnt);
void bcopy(const void *src, void *dest, unsigned int n);
int kprintf(char * fmt, ...);
void lidt(void);
void init8259(void);
void disable(void);
void outb(unsigned int, unsigned char);
unsigned char inb(unsigned int);

// Memory Manager
extern void kmeminit(void);
extern void *kmalloc(int);
extern void kfree(void *ptr);

// Dispatcher
extern void initializeProcessQueue();
extern void dispatch();
extern void syscreate();
extern void sysstop();
extern void sysyield();
extern void ready(struct pcb* process);

extern void contextswitch();
extern void contextinit();
extern void setEvec(unsigned int, unsigned long);
extern int create(void (*func)(), int stackSize);


