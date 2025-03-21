.text
_start: .global _start

@ sys_write ( r0: fd, r1: pstr, r2: len ), r7 = 4
    mov r0, #1   @ fd <- 1 (stdout)
    adr r1, msg  @ pstr <- *msg
    mov r2, #14  @ len <- 14

    mov r7, #4   @ syscall <- sys_write
    swi 0        @ system call

@ sys_exit ( r0: exitcode ), r7 = 1
    mov r0, #0  @ exitcode <- 0

    mov r7, #1  @ syscall <- sys_exit
    swi 0       @ system call

msg:
    .asciz "Hello, world!\n"
    .end