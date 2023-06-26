#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/workqueue.h>
#include <linux/timer.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/semaphore.h>

#define LOG_INTERVAL_MS 1000


struct my_data {
    char *text;              // simple structe to store text data
    struct list_head list;   // Linked list structure for data storage
};

static LIST_HEAD(my_list);        // Linked list head for storing text data
static DEFINE_MUTEX(my_mutex);    // Mutex for synchronization
static DEFINE_SEMAPHORE(my_semaphore);    // Semaphore for synchronization

static struct workqueue_struct *my_workqueue;    // Workqueue for executing work
static struct timer_list my_timer;                // Timer for regular execution


static void my_work_function(struct work_struct *work)
{
    struct my_data *data;

    mutex_lock(&my_mutex);

    if (list_empty(&my_list)) {
        mutex_unlock(&my_mutex);
        return;
    }

    data = list_first_entry(&my_list, struct my_data, list);
    list_del(&data->list);

    mutex_unlock(&my_mutex);

    printk(KERN_INFO "Text: %s\n", data->text);   // Print the text to the kernel log

    kfree(data->text);
    kfree(data);
}


static void my_timer_function(struct timer_list *t)
{
    queue_work(my_workqueue, (struct work_struct *)&my_work);   // Queue the work to be executed
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000));     // Reschedule the timer for the next execution
}

DECLARE_WORK(my_work, my_work_function);           // Declare the work function
DEFINE_TIMER(my_timer, my_timer_function);         // Define the timer function

static int __init my_module_init(void)
{
    printk(KERN_INFO "Initializing my_module\n");

    my_workqueue = create_workqueue("my_workqueue");    // Create the workqueue

    setup_timer(&my_timer, my_timer_function, 0);       // Set up the timer
    mod_timer(&my_timer, jiffies + msecs_to_jiffies(1000));   // Start the timer

    return 0;
}

static void __exit my_module_exit(void)
{
    struct my_data *data, *tmp;

    flush_workqueue(my_workqueue);             // Flush the workqueue
    destroy_workqueue(my_workqueue);           // Destroy the workqueue

    del_timer_sync(&my_timer);                 // Delete the timer

    list_for_each_entry_safe(data, tmp, &my_list, list) {
        list_del(&data->list);
        kfree(data->text);
        kfree(data);
    }

    printk(KERN_INFO "Exiting my_module\n");
}

int my_module_add_text(const char *text)
{
    struct my_data *data;

    data = kmalloc(sizeof(struct my_data), GFP_KERNEL);     // Allocate memory for the data structure
    if (!data)
        return -ENOMEM;

    data->text = kstrdup(text, GFP_KERNEL);                 // Duplicate the text data
    if (!data->text) {
        kfree(data);
        return -ENOMEM;
    }

    mutex_lock(&my_mutex);
    list_add_tail(&data->list, &my_list);                    // Add the data to the linked list
    mutex_unlock(&my_mutex);

    return 0;
}

int my_module_get
