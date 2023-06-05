# Enhancing XV-6

> ### Team : Ishit Bansal & Amogha A Halhalli
----
<br >

### Specification 1: System Calls
    System Call 1: trace
        1. Added a sys_trace() function in kernel/sysproc.c 
        2. Added a new variable mask in struct proc in kernel/proc.h
        3. Initialised the new variable in allocproc in kernal/proc.c
        4. Added a new user program which calls the trace system call.
        5. Modified the syscall.c to print the output of the trace syscall.
    
    System Call 2: sigalarm and sigreturn
        1. Added sys_sigalarm() and sys_sigreturn() in kernel/sysproc.c
        2. Added some new variables in struct proc in kernel/proc.h
        3. Initialised the new variables in allocproc in kernal/proc.c
        4. Modified the trap.c to handle the syscall sigalarm.

### Specification 2: Scheduling
    a. First Come First Serve (FCFS) --> Run as 'make qemu SCHEDULER=FCFS'
        1. Added new variables in struct proc in kernel/proc.h to store more information about the process.
        2. Modified the allocproc() function to set up the new values in kernel/proc.c
        3. Modified the scheduler() function in proc.c to separately handle the FCFS scheduling.
        4. Disabled the preemption of the process after the clock interrupts in kernel/trap.c

    b. Lottery Based Scheduler (LBS) --> Run as 'make qemu SCHEDULER=LBS'
        1. Added new variables in struct proc in kernel/proc.h to store more information about the process.
        2. Modified the allocproc() function to set up the new values in kernel/proc.c
        3. Modified the scheduler() function in proc.c to separately handle the LBS scheduling.
        4. Added a syscall sys_settickets() in kernel/sysproc.c which calls int settickets(int number)
        5. The function settickets sets the number of tickets of the calling process.

    c. Priority Based Scheduler (PBS) --> Run as 'make qemu SCHEDULER=PBS'
        1. Added new variables in struct proc in kernel/proc.h to store more information about the process.
        2. Modified the allocproc() function to set up the new values in kernel/proc.c
        3. Modified the scheduler() function in proc.c to separately handle the LBS scheduling.
        4. Added a syscall sys_set_priority which sets the static priority of the process.
        5. Added a user program setpriority.c which is used to set the priority of a process.

    d. Multi Level Feedback Queue (MLFQ) --> Run as 'make qemu SCHEDULER=MLFQ'
        1. Added new variables in struct proc in kernel/proc.h to store more information about the process.
        2. Modified the allocproc() function to set up the new values in kernel/proc.c
        3. Defined new struct _queue in kernel/proc.h to store information of the queues.
        4. Added new functions enque, deque & update to manipulate the struct _queue Queue[5]
        5. Modified the scheduler() function in proc.c to separately handle the MLFQ scheduling.
        6. Enabled the preemption of the process after the time slice in kernel/trap.c
        7. Each process is pushed to higher priority queue after 128 ticks to avoid aging.

### Specification 3: Copy-on-write fork
    1. Added new function uvmcopy_cow in kernel/vm.c which will map the addresses of child process          pagetable to that of old process.
    2. Added page_reference array in kernel/kalloc.c which keeps track of the number of processes sharing that same page.
    3. Initialised page_reference array in kernel/main.c
    4. Incremented page_reference of that pa in kalloc() in kernel/kalloc.c
    5. Decremented page_reference of that pa in kfree() in kernel/kalloc.c, if zero, that page is freed.
    6. Declared 6th bit as PTE_COW for addresses in kernel/riscv.h
    7. Modified copyout function in kernel/vm.c to use the same pages if is a COW page
    8. Modified usertrap function in kernel/trap.c. When a process tries to write on one of the COW pages, a page fault will be raised. The function will allocate it a page of physical memory, make the required changes and return to continue the process. 
    

### Specification 4: Performance Comparision
|         Scheduler          | Average run time | Average wait time |
| :------------------------: | :--------------: | :---------------: |
| Round Robin                | 14               | 114               |
| First Come First Serve     | 33               | 39                |
| Lottery Based Scheduler    | 6                | 109               |
| Priority Based Scheduler   | 17               | 107               |
| Multi-Level Feedback Queue | 14               | 143               |
    Used 1 CPU for Multi-Level Feedback Queue.

### Other Implementations:
    1. Edited the procdump() function in kernel/proc.c for debugging.
    2. Added a user program time.c and function update_time() in kernel/proc.c (tutorial)
    3. Implemented a system call sys_waitx which return runtime and wait time of child process.(tutorial)
    4. Added a user program schedulertest to test the running of scheduling algorithms.
    5. Added a user program alarmtest to test working of system call sigalarm & sigreturn.
    6. Added a user program cowtest to test working of copy on write.
