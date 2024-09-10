
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>



#define PROCFS_NAME "hello_procfs"

MODULE_DESCRIPTION("Procfs Module of Part3 Assignment1");
MODULE_AUTHOR("Abhijeet Singh");
MODULE_LICENSE("GPL");


static int hello_third(struct seq_file *mqr, void *v) {
    seq_printf(mqr, "Hello World!\n");
    return 0;
}

static int hello_second(struct inode *inode, struct file *file_a) {
    return single_open(file_a, hello_third, NULL);
}

static const struct proc_ops hello_first = {
    .proc_open = hello_second,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};

static int __init procfs_init(void) {
    proc_create(PROCFS_NAME, 0, NULL, &hello_first);

    printk(KERN_INFO "/proc/%s created\n", PROCFS_NAME);
    return 0;
}

static void __exit procfs_exit(void) {

    remove_proc_entry(PROCFS_NAME, NULL);

    printk(KERN_INFO "/proc/%s removed\n", PROCFS_NAME);
}


module_init(procfs_init);
module_exit(procfs_exit);





