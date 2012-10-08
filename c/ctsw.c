/* ctsw.c : context switcher
 */

#include <i386.h>
#include <xeroskernel.h>

void contextinit();
int contextswitch(struct pcb*);
void _ISREntryPoint();
extern int set_evec(int, long);


static void *k_stack;
static unsigned int ESP;

/* Your code goes here - You will need to write some assembly code. You must
   use the gnu conventions for specifying the instructions. (i.e this is the
   format used in class and on the slides.) You are not allowed to change the
   compiler/assembler options or issue directives to permit usage of Intel's
   assembly language conventions.
*/

void contextinit() {
	// setEvec(unsigned int xnum, unsigned long handler)
	//set_evec(58);
}


extern int contextswitch(struct pcb* currProcess) { 
	kprintf("c");
	extern long initsp;
	k_stack = initsp;
	ESP = (int) &currProcess->stack;
	kprintf("\nEsp: %d, kstack: %d\n", ESP, k_stack);
	asm volatile("pushf\n \
		pusha\n \
		movl %%esp, k_stack\n \
		movl ESP, %%esp\n \
		popa\n \
		iret\n \
		\
		_ISREntryPoint:\n \
			pusha\n \
			movl	%%esp, ESP\n \
			movl	k_stack, %%esp\n \
			popa\n \
			popf\n \
		"
		:
		:
		: "%eax"
	);
	
	kprintf("C");
//	currProcess->esp = ESP;
	return ESP;
}
