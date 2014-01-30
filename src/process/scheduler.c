#include "common/string.h"
#include "common/stdio.h"
#include "process/scheduler.h"

extern void *tss0Label asm("tss0");
tss_t *gl_tss0 = (tss_t*)&tss0Label;

void userland(void)
{
  puts("In userland\n");
  asm volatile ("int $0x80");
  puts(WARN_COLOR "USERLAND WILL PAGE FAULT\n" DEF_COLOR);
  char *str = (char*)0xC03FF000;
  char c = *str; /* Will page fault */
  puts("After syscall\n");
  while (1);
}

void test_switch(void)
{
  puts("Test switch called\n");
  asm volatile("mov %%esp, %0": "=r"(gl_tss0->esp0));
  // Set up a stack structure for switching to user mode.
  asm volatile("cli;" 
	       "mov %1, %%ax;" 
	       "mov %%ax, %%ds;" 
	       "mov %%ax, %%es;" 
	       "mov %%ax, %%fs;" 
	       "mov %%ax, %%gs;" 
	       "mov %%esp, %%eax;" 
	       "pushl %1;" 
	       "pushl %%eax;" 
	       "pushf;"
	       "pop %%eax;"
	       "or %%eax, %2;"
	       "push %%eax;"
	       "pushl %0;" 
	       "push $toto;" 
	       "iret;" 
	       "toto: call userland" 
	       :: "N"(0x1b), "N"(0x23), "r"(0x200));
}
