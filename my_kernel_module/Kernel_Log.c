#include <linux/module.h>
#include <linux/kernel.h>
#include "Source.h"

int init_module(void)
{
    printk(KERN_INFO "Hello, kernel module fährt hoch!\n");
    return my_module_init();
}

void cleanup_module(void)
{
    printk(KERN_INFO "Goodbye, kernel module fährt runter !\n");
    my_module_exit();
}
