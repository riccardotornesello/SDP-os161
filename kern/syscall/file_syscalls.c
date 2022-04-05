#include <types.h>
#include <lib.h>
#include <kern/unistd.h>
#include <syscall.h>

ssize_t sys_read(int filehandle, void *buf, size_t size)
{
    char *p = (char *)buf;
    int i;

    if (filehandle != STDIN_FILENO)
    {
        kprintf("Only STDIN supported");
        return -1;
    }

    for (i = 0; i < (int)size; i++)
    {
        p[i] = getch();
        if (p[i] < 0)
            return i;
    }
    return size;
}

ssize_t sys_write(int filehandle, const void *buf, size_t size)
{
    char *p = (char *)buf;
    int i;

    if (filehandle != STDOUT_FILENO)
    {
        kprintf("Only STDOUT supported");
        return -1;
    }

    for (i = 0; i < (int)size; i++)
    {
        putch(p[i]);
    }
    return size;
}