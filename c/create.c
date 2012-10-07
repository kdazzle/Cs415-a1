/* create.c : create a process
 */

#include <xeroskernel.h>

/* Your code goes here. */
int create(void (*func)(), int stackSize);
struct pcb* allocatePcb();


extern struct pcb;
extern struct processStack;

/**
	Takes two parameters, a reference (function pointer) to the start 
	of the process, and an integer denoting the amount of stack to allocate for the 
	process. Returns the new process’ pid on success and −1 on failure

*/
int create(void (*func)(), int stackSize) {
	// Allocate a free pcb from the process table
	struct pcb* process = kmalloc(sizeof(struct pcb));
	
	// Allocate the stack using kmalloc()
	struct processStack* stack = kmalloc(stackSize + sizeof(struct processStack));
	
	// Initialize the pcb and the stack
	stack->size = stackSize;
	stack->cs = getCS();
	process->stack = stack;
	// Place the process on the ready queue
	ready(process);

	//TODO: pid?
	kprintf("int process: %d\n", (int) process);
	return (int) process;
}
