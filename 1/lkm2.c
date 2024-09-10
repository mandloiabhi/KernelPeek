/* to run this : sudo insmod lkm2.ko process_id_input=<pid> */

#include <linux/kernel.h>
#include<linux/init.h>
#include<linux/sched/signal.h> 
#include <linux/module.h>
#include <linux/sched.h>

MODULE_DESCRIPTION("My kernel module");
MODULE_AUTHOR("Me");
MODULE_LICENSE("GPL");


static pid_t process_id_input = 42;
module_param(process_id_input, int, S_IRUGO);



void print_children_info(struct task_struct *parent_task)
{
    struct task_struct *child_task;

    // Iterate through the list of children processes
    list_for_each_entry(child_task, &parent_task->children, sibling) {
        // Print information about each child process
        printk(KERN_INFO "Parent PID: %d | Child PID: %d | Child Process: %s\n",
               parent_task->pid, child_task->pid, child_task->comm);
    }
}
void process_info(void)
{

    struct task_struct *task;
    for_each_process(task)
    {

            //printk(KERN_INFO "Inside Task\n");
        if(task->pid==process_id_input)   // check if the process is given is match with current task process with help of pid 
         { 
            printk(KERN_INFO "Inside if task->child\n");
           print_children_info(task);
           break;
         }
    }
    //print_children_info(task);
    
    
}
static int dummy_init(void)
{
    pr_info("Hi I am ABhijeet\n");
    printk(KERN_INFO "Hello, Welcome to LKM\n");
    process_info();
    
    return 0;
    //return 0;
}

static void dummy_exit(void)
{
    pr_info("Bye Abhijeet\n");
}

module_init(dummy_init);
module_exit(dummy_exit);