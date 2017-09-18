#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/user.h>

// Initially inspired by: http://www.linuxjournal.com/article/6210

int main(int argc, char *argv[])
{
    // PID of the child process to debug
    pid_t target_pid;
    // 
    struct user_regs_struct regs;
    unsigned long ins;

    // Check if 
    if(argc != 2) {
        printf("Usage: %s <pid to be traced>\n", argv[0]);
        exit(1);
    }

    target_pid = atoi(argv[1]);

    ptrace(PTRACE_ATTACH, target_pid, NULL, NULL);

    wait(NULL);

    ptrace(PTRACE_GETREGS, target_pid, NULL, &regs);

    ins = ptrace(PTRACE_PEEKTEXT, target_pid, regs.rip, NULL);

    printf("EIP: %llx Instruction executed: %lx\n", regs.rip, ins);

    ptrace(PTRACE_DETACH, target_pid, NULL, NULL);
    return 0;
}
