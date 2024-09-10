# KernelPeek


# Linux Kernel Modules and IOCTL Project

This project consists of a series of Linux Kernel Modules (LKMs) and an IOCTL device driver that interact with various aspects of the Linux kernel. The project covers topics such as process state tracking, virtual-to-physical memory address mapping, and process signals, leveraging kernel capabilities for low-level system interactions.


## Features

This project includes the following components:

1. **Hello World LKM**: A basic kernel module that prints messages when loaded and unloaded.
2. **Process Information Modules**:
    - List all processes in the running or runnable state.
    - Given a process ID, list all its child processes and their state.
    - Map virtual addresses to physical addresses for a specific process.
    - Monitor memory allocation and display virtual and physical memory statistics.
3. **IOCTL Device Driver**:
    - Query physical addresses from virtual addresses.
    - Write to physical memory via IOCTL.
    - Signal parent process upon child process exit via IOCTL.
4. **/proc Filesystem Interaction**:
    - A `/proc` entry that prints "Hello World!".
    - A `/proc` entry that displays page fault statistics since system boot.

## Setup

To ensure compatibility, this project must be run on a **Linux machine with kernel version 6.1.0**. You can verify your kernel version using the following command:
```bash
uname -r

structure of project 
├──── 1/

│        ├── lkm1.c

│        ├── lkm2.c

│        ├── lkm3.c

│        ├── lkm4.c

│        ├── Makefile

│        

│

├──── 2_I/

│        ├── spock.sh

│        └── ... <solution specific files/dirs>

│

├──── 2_II/

│        ├── control_station.c

│        ├── soldier.c

│        ├── run_dr_doom.sh

│        ├── Makefile

│        └── ... <solution specific files/dirs>

│

└──── 3/

        ├── hello_procfs.c

        ├── get_pgfaults.c

        ├── Makefile

    

# It seems there was a reset, so I'll recreate the content and save it to the file again.


How It Works

Kernel Modules: The LKMs interact with kernel data structures such as task_struct and mm_struct to gather process information, handle memory translation, and monitor memory allocation.
IOCTL Driver: The IOCTL driver enables communication between user-space programs and kernel-space memory, allowing direct memory access and modification.
/proc Filesystem: The /proc modules expose kernel information to user-space programs through a pseudo-file system interface.


Key Kernel Structures:
task_struct: Used to represent a process in Linux.
mm_struct: Used to represent a process’s memory layout.
vm_area_struct: Describes memory regions within the address space.