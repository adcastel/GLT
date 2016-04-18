/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <glt.h>

 int glt_can_syscall_functions()
{
#ifdef CORE
    return 0;
#else
    return 1;
#endif
}

#ifndef CORE

 void glt_syscall_begin_blocking()
{
     qt_begin_blocking_action(); 
}

 void glt_syscall_end_blocking()
{
     qt_end_blocking_action(); 
}

 int glt_syscall_accept(int socket, 
        struct sockaddr *restrict address, socklen_t *restrict address_len)
{
    return qt_accept (socket, address, address_len);
}

 int glt_syscall_connect(int socket, 
        struct sockaddr *restrict address, socklen_t address_len)
{
    return qt_connect (socket, address, address_len);
}

 int glt_syscall_poll(struct pollfd fds[], nfds_t nfds, int timeout)
{
    return qt_poll (fds, nfds, timeout);
}

 size_t glt_syscall_pread(int filedes, void *buf, size_t nbyte, 
        off_t offset)
{
    return qt_pread (filedes, buf, nbyte, offset);
}

 size_t glt_syscall_read(int filedes, void *buf, size_t nbyte)
{
    return qt_read (filedes, buf, nbyte);
}

 size_t glt_syscall_pwrite(int filedes, void *buf, size_t nbyte, 
        off_t offset)
{
    return qt_pwrite (filedes, buf, nbyte, offset);
}

 size_t glt_syscall_write(int filedes, void *buf, size_t nbyte)
{
    return qt_write (filedes, buf, nbyte);
}

 int glt_syscall_select(int nfds, fd_set *restrict readfds, 
        fd_set *restrict writefds, fd_set *restrict errorfds, 
        struct timeval *restrict timeout)
{
    return qt_select (nfds, readfds, writefds, errorfds, timeout);
}

 int glt_syscall_system(const char * command)
{
    return qt_system(command);
}

 int glt_syscall_wait4 (pid_t pid, int *stat_loc, int options, 
        struct rusage *rusage)
{
    return qt_wait4 ( pid, stat_loc, options, rusage);
}

#endif