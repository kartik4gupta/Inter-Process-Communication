Implemented a kernel system call as a module. The task of the system call
is to read the entries of the process task_struct corresponding to any
given process (supplied as input via command line argument) and prints the
values of the following field: pid, user id, process group id (pgid) and command
path in the kernel log. 


Following are the commands for execution :
make // makes kernel_module.ko ie kernel object file
insmod kernel_module.ko process_name="udevd"
dmesg // takes user to kernel log where requested information is printed
use ps -ef to cross check the information.

