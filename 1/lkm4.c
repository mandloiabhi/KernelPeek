/*to run this :  sudo insmod lkm4.ko process_pid=<given_pid>   */
#include <linux/kernel.h>
#include<linux/init.h>
#include<linux/sched/signal.h> 
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/mm.h>

MODULE_DESCRIPTION("My kernel module");
MODULE_AUTHOR("Me");
MODULE_LICENSE("GPL");


static pid_t process_pid = 42;
module_param(process_pid, int, S_IRUGO);




void print_children_info(struct task_struct *process_task)
{
    struct mm_struct *mm = NULL;
    struct vm_area_struct *vma;
     if (process_task) {
        mm = process_task->mm;
    }
    
    unsigned long total_pages_mapped= mm->total_vm;
    unsigned long total_vma_space=0;
    printk(KERN_INFO "total vma mapped: %u\n", total_pages_mapped*4096);
    
    unsigned long anon = get_mm_counter(mm, MM_ANONPAGES);
	unsigned long file = get_mm_counter(mm, MM_FILEPAGES);
	unsigned long shmem = get_mm_counter(mm, MM_SHMEMPAGES);
    total_vma_space=anon+file+shmem;
    printk(KERN_INFO "total vma present in physical memory : %d\n", total_vma_space*4096);

}
void process_info(void)
{

    struct task_struct *task;
    for_each_process(task)
    {
        if(task->pid==process_pid)
         { 
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