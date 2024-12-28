#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

// Declare a module parameter
static int my_param = 0;
module_param(my_param, int, 0444);
//MODULE_PARM_DESC(my_param, "An integer parameter");

// Initialize the module
static int __init init_cli_dri(void)
{
    printk(KERN_INFO "init_cli_dri: my_param = %d\n", my_param);
    return 0;
}

// Exit the module
static void __exit exit_cli_dri(void)
{
    printk(KERN_INFO "Exiting module\n");
}

module_init(init_cli_dri);
module_exit(exit_cli_dri);

//MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A kernel module that accepts a parameter");

