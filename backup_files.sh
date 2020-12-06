#!/bin/bash

echo "copying files from the different directories to project dir"
echo "backing up init_task.h"
cp /home/student/linux-4.15.18-custom/include/linux/init_task.h /home/student/hw2/
echo "backing up sched.h"
cp /home/student/linux-4.15.18-custom/include/linux/sched.h /home/student/hw2/
echo "backing up syscalls.h"
cp /home/student/linux-4.15.18-custom/include/linux/syscalls.h /home/student/hw2/
echo "backing up syscall_64.tbl"
cp /home/student/linux-4.15.18-custom/arch/x86/entry/syscalls/syscall_64.tbl /home/student/hw2/
echo "backing up hw2.c"
cp /home/student/linux-4.15.18-custom/kernel/hw2.c /home/student/hw2/
echo "backing up kernel Makefile"
cp /home/student/linux-4.15.18-custom/kernel/Makefile /home/student/hw2/

echo "Done copying files"
