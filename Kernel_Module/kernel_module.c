#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/sched.h>




static char *process_name = NULL;
module_param(process_name, charp, S_IRUGO);
MODULE_PARM_DESC(process_name, "The name of the process ");

static int __init process_info_init(void)
{
    if (input_process == NULL) {
        return -1;
    }

    struct task_struct *task;

    for_each_process(task) {
        if (0==strcmp(process_name,task->comm)) {
            printk(KERN_INFO "PID of process %s: %d\n", input_process, task->pid);
            printk(KERN_INFO "PGID of process %s: %d\n", input_process, task->tgid);
            printk(KERN_INFO "Command path of process %s: %s\n", input_process, task->mm->exe_file->f_path.dentry->d_iname);
            printk(KERN_INFO "UID of process %s: %d\n", input_process, task->cred->uid);
            return 0;
        }
    }

    printk(KERN_INFO "Error in finding process with name %s\n", input_process);
    return -1;
}

static void __exit process_info_exit(void)
{
    printk(KERN_INFO "Exiting process_info\n");
}

module_init(process_info_init);
module_exit(process_info_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Kartik Gupta");
MODULE_DESCRIPTION("A kernel module that prints the PID, UID, UGID and path of a requested process");
