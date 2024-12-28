#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>

struct my_device {
    int id;
    struct list_head list; // Embedded list_head structure
};

static int __init example_init(void) {
    //struct my_device dev = { .id = 42 };
    struct my_device dev;
	dev.id = 20;
    struct list_head *list_ptr = &dev.list;

    // Use container_of to get the enclosing structure
//    struct my_device *device_ptr = container_of(list_ptr, struct my_device, list);

//    printk(KERN_INFO "Device ID: %d\n", device_ptr->id);
    printk(KERN_INFO "Device ID: %d\n", dev.id);

    return 0;
}

static void __exit example_exit(void) {
    printk(KERN_INFO "Goodbye, Kernel!\n");
}

module_init(example_init);
module_exit(example_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("An example module using container_of");

