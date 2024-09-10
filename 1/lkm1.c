
  /* To run it run the command on terminal :  sudo  insmod lkm1.ko  */

#include <linux/kernel.h>
#include<linux/init.h>
#include<linux/sched/signal.h> 
#include <linux/module.h>



MODULE_DESCRIPTION("My kernel module");
MODULE_AUTHOR("Me");
MODULE_LICENSE("GPL");

void process_info(void)
{

    
    struct task_struct *task;
    for_each_process(task)
    {
        if(task->__state>=0)
        printk(KERN_INFO "PID: %d | PROCESS: %s | STATE: %ld\n", task->pid,task->comm, task->__state);
    }
    
}
static int dummy_init(void)
{
    pr_info("Hi I am ABhijeet\n");
    printk(KERN_INFO "Hello, Welcome to LKM\n");
    process_info();
    printk(KERN_INFO "Listing process kernel module loaded\n");
    return 0;
    //return 0;
}

static void dummy_exit(void)
{
    pr_info("Bye Abhijeet\n");
}

module_init(dummy_init);
module_exit(dummy_exit);