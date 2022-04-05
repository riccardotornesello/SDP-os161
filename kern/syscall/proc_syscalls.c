#include <syscall.h>
#include <addrspace.h>
#include <thread.h>
#include <proc.h>
#include <current.h>
#include <types.h>

void sys__exit(int status)
{
    struct thread *curt = curthread;

    /* Save return value */
    curt->t_retvalue = status;
    if (curt->t_proc != NULL)
    {
        curt->t_proc->p_retvalue = status;
    }

    /* Destroy current process area */
    struct addrspace *as = proc_getas();
    as_destroy(as);

    /* Exit from thread */
    thread_exit();

    panic("This shouldn't happen\n");
}
