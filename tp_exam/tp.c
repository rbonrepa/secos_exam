/* GPLv2 (c) Airbus */
#include "print.c"
#include "header.c"
 
/*
** Global variables
*/
seg_desc_t gdt[GDT_SIZE];
tss_t tss;
idt_reg_t idtr;
uint32_t tasks[4] = {};
unsigned int number_tasks = 0;
int current_task = -1;

/*
** Define the userland
*/
__attribute__((section(".sys_count"))) void sys_counter(uint32_t*counter){
    asm volatile("int $80"::"S"(counter));
}
 
/*
** Task 1: counteur in shared memory.
*/
__attribute__((section(".user1"))) void increment_counter(){
    uint32_t *shared_mem = (uint32_t *)0x800000;
    *shared_mem = 0;
    while (1)
      (*shared_mem)++;
}

/*
** Task 2: print counteur in shared memory.
*/ 
__attribute__((section(".user2"))) void print_counter(){
    uint32_t *shared_mem = (uint32_t *)0x801000;
    while (1)
      sys_counter(shared_mem);
}

/*
** Pagination
** This function creates one pgd and 2 ptb of 1024 entries.
*/

/*
** Initialisation of segment descriptor.
*/

void tp(){
    debug("|------   Work demonstration   ------|\n");
    print_memory_cartography(idtr, (uint32_t)increment_counter, (uint32_t)print_counter);

    // Set up kernel: init gdt, tss, register and pagination

    // Set up 2 tasks: init pagination, kernel stack and shared memory

    	
    // Start task: init idt and records handlers
    
    
    debug("\n|------------     Fin     -----------|\n");

    while(1);
}
