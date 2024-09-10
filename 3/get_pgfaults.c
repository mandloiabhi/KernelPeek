#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/cpu.h>
#include <linux/vmstat.h>

MODULE_DESCRIPTION("Procfs Module of Part3 Assignment1");
MODULE_AUTHOR("Abhijeet Singh");
MODULE_LICENSE("GPL");
// static int get_pagefault_show(struct seq_file *m, void *v); 

static int get_pagefault_show(struct seq_file *m, void *v) {
    unsigned long total_pgfaults=0;
   
    cpus_read_lock();
    int cpu;
    for_each_online_cpu(cpu) {
		struct vm_event_state *this = &per_cpu(vm_event_states, cpu);
			total_pgfaults += this->event[PGFAULT];
	}
    cpus_read_unlock();
    seq_printf(m, "total Page Faults are : %lu\n", total_pgfaults);
    return 0;
}

static int get_pgfaults_first(struct inode *inode, struct file *file) {
    return single_open(file, get_pagefault_show, NULL);
}

static const struct proc_ops get_pgfaults_second = {
    .proc_open = get_pgfaults_first,
    .proc_read = seq_read,
    .proc_lseek = seq_lseek,
    .proc_release = single_release,
};



static int __init get_pgfaults_init(void) {

    proc_create("get_pgfaults", 0, NULL, &get_pgfaults_second);
   
    printk(KERN_INFO "/proc/get_pgfaults created \n");
    return 0;
}

static void __exit get_pgfaults_exit(void) {

    remove_proc_entry("get_pgfaults", NULL);

    printk(KERN_INFO "/proc/get_pgfaults removed\n");
}


module_init(get_pgfaults_init);
module_exit(get_pgfaults_exit);


