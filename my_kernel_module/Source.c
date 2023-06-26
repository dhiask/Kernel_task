#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/timer.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/semaphore.h>

#define LOG_INTERVAL_MS 1000


struct my_data {
    int id;
    struct list_head list;
};

static LIST_HEAD(my_list);  // Linked list for storing data
static DEFINE_MUTEX(my_mutex);  // Mutex for synchronization
static DEFINE_SEMAPHORE(my_semaphore);  // Semaphore for synchronization



static struct workqueue_struct *my_workqueue;  // Workqueue for executing work

static void my_work_function(struct work_struct *work)
{
    printk(KERN_INFO "Work function executed\n");
    // Do the necessary work here
}





















//section Not sure

static struct workqueue_struct *my_workqueue;

static void my_work_function(struct work_struct *work)
{
    printk(KERN_INFO "Work function executed\n");
    // Do the necessary work here
}

DECLARE_DELAYED_WORK(my_work, my_work_function);

static int __init my_module_init(void)
{
    printk(KERN_INFO "Initializing my_module\n");

    my_workqueue = create_workqueue("my_workqueue");
    queue_delayed_work(my_workqueue, &my_work, msecs_to_jiffies(1000)); // Schedule the work after 1 second

    return 0;
}















int init_module(void)
{
    printk(KERN_INFO "Hello, kernel module Fährt Hoch !\n");
    return 0;
}

void cleanup_module(void)
{
    printk(KERN_INFO "Goodbye, kernel module fährt runter!\n");
}
