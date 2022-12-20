#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>




static char *process_name = NULL;
module_param(process_name, charp, S_IRUGO);
MODULE_PARM_DESC(process_name, "The name of the process ");

static int __init process_info_init(void)
{
    if (process == NULL) {
        return -1;
    }

    struct task_struct *task;

    for_each_process(task) {
        if (0==strcmp(process_name,task->comm)) {
            printk("************************************************************\n");
            printk(KERN_INFO "Path of process : %s\n", task->comm);
            printk(KERN_INFO "PID of process : %d\n", task_pid_nr(task));
            printk(KERN_INFO "PGID of process : %d\n", (int)task_tgid_nr(task));
            printk(KERN_INFO "UID of process : %d\n", (int) task->cred->uid.val);
            printk("************************************************************\n");
            return 0;
        }
    }

    printk(KERN_INFO "Error in finding process with name %s\n", process_name);
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
