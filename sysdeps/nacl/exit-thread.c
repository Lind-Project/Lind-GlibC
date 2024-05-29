#include <atomic.h>
#include <irt_syscalls.h>
#include <nptl/pthreadP.h>
#include <unistd.h>
#include <stdio.h>

void __exit_thread (int val)
{
  /*
      * The NaCl IRT fork function copies the process memory as a whole to the child, so we need to
      * flush the stdio buffers before calling it.
      * Issue #12:https://github.com/Lind-Project/native_client/issues/12
  */
  fflush(stdout);
  fflush(stderr);

  /* We are about to die: make our pd "almost free" and wake up waiter. */
  struct pthread* pd = THREAD_SELF;
  int count;
  pd->tid = -2;
  __nacl_futex_wake (&pd->tid, INT_MAX, __FUTEX_BITSET_MATCH_ANY, &count);
  __nacl_irt_thread_exit (&pd->tid);
  /* Not reached */
  __asm__ ("hlt");
}