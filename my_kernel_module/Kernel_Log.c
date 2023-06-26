#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void)
{
    printk(KERN_INFO "Hello, kernel module!\n");
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Goodbye, kernel module!\n");
}
