
/*to run this :  sudo insmod lkm3.ko process_pid=<given_pid> user_vaddr=<given virtual address>   */
#include <linux/module.h> 
#include <linux/init.h>
#include <linux/kernel.h>       
#include <linux/sched/signal.h> 
#include <linux/mm.h>           
#include <linux/pgtable.h>
#include <linux/pid.h>
#include <linux/mm_types.h>
#include <linux/io.h>

// #include <asm/mmu.h>

MODULE_DESCRIPTION("My kernel module");
MODULE_AUTHOR("Me");
MODULE_LICENSE("GPL");

static pid_t process_pid = 1;
unsigned long user_vaddr = 0000000000;
module_param(process_pid, int, S_IRUGO);
module_param(user_vaddr, ulong, S_IRUGO);
MODULE_PARM_DESC(process_pid, "process_pid");
MODULE_PARM_DESC(user_vaddr, "user_vaddr");

static int print_children_info(struct task_struct *process_task)
{
    struct mm_struct *mm = NULL;

    if (process_task)
    {
        mm = process_task->mm;
    }
    if (mm == NULL)
    {
        printk(KERN_INFO "The process's identifier is : %d   Process : %s \n", process_task->pid, process_task->comm);
    }
    unsigned long vaddr = user_vaddr;
    struct page *page;
    // printk(KERN_INFO " 1st\n");
    pgd_t *pgd;
    p4d_t *p4d;
    pmd_t *pmd;
    pud_t *pud;
    pte_t *pte;


// pagetable walking 
    pgd = pgd_offset(mm, (unsigned long)vaddr);
    
    if (pgd_none(*pgd) || pgd_bad(*pgd))
    {
        printk(KERN_ERR "lkm3: PGD entry not found\n");
        printk("Control reached till pgd\n");
        return -1;
    }
    p4d = p4d_offset(pgd, (unsigned long)vaddr);
    // printk(KERN_INFO " 3st\n");
    if (p4d_none(*p4d) || p4d_bad(*p4d))
    {
        printk(KERN_ERR "lkm3: P4D entry not found\n");
        printk("Control reached till pgd\n");
        return -1;
    }
    pud = pud_offset(p4d, (unsigned long)vaddr);
    // printk(KERN_INFO " 4st\n");
    if (pud_none(*pud) || pud_bad(*pud))
    {
        printk(KERN_ERR "lkm3: PuD entry not found\n");
        printk("Control reached till pud\n");
        return -1;
    }
    pmd = pmd_offset(pud, (unsigned long)vaddr);
    // printk(KERN_INFO " 5st\n");
    if (pmd_none(*pmd) || pmd_bad(*pmd))
    {
        printk(KERN_ERR "lkm3: PmD entry not found\n");
        printk("Control reached till pgd\n");
        return -1;
    }
    pte = pte_offset_map(pmd, (unsigned long)vaddr);
    // printk(KERN_INFO " 6st\n");
    if (pte_none(*pte) )
    {
        printk(KERN_ERR "lkm3: Pte entry not found\n");
        printk("Control reached till pgd\n");
        return -1;
    }
    // pte_t my_pte;
    int is_present = 1 ; //pte_val(pte) & 0x1;

   
    if (is_present)
    {
        printk("The page is present.\n");
        page = pte_page(*pte);
        // printk(KERN_INFO " 8st\n");
         unsigned long paddr = page_to_phys(page);
        //  printk(KERN_INFO " 9st\n");
        printk(KERN_INFO "Process PID: %d | Virtual address: %lu | Physical_addr: %lu\n", process_pid, vaddr, (unsigned long )paddr);
    }
    else
    {
        printk("The page is absent.\n");
    }
    return 0;
}

void process_info(void)
{

    struct task_struct *task;
    for_each_process(task)
    {
        if (task->pid == process_pid)
        {
            print_children_info(task);
            break;
        }
    }
    // print_children_info(task);
}
static int dummy_init(void)
{
    pr_info("Hi I am ABhijeet\n");
    printk(KERN_INFO "Hello, Welcome to LKM\n");
    process_info();

    return 0;
    // return 0;
}

static void dummy_exit(void)
{
    pr_info("Bye Abhijeet\n");
}

module_init(dummy_init);
module_exit(dummy_exit);