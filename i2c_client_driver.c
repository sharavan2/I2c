#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/init.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/i2c.h>

static struct i2c_data
{
	struct i2c_client *cli;
	struct cdev c;
	dev_t dev;
	u16 value;
	u8 *buf;
	struct class *cls;
};

static struct file_operation  fops =
{
	.open = i2c_open,
	.release = i2c_release,
	.write = i2c_write,
	.read = i2c_read
};
static struct file_operationf ops =
{
	.open     = i2c_open,
	.release  = i2c_release,
	.wrire    = i2c_write,
	.read     = i2c_read
};
static struct i2c_device_id id[] =
{
	{"sharavan", 0},
	{"damo", 0},
	{}
};

MUDULE_DEVICE_TABLE(i2c, id);

/* Remove function */

static int i2c_remove(struct i2c_client *client)
{
	struct i2c_data *data;
	printk(KERN_INFO "Remove function is invoked....\n");
	data = i2c_get_clientdata(client);
	cdev_del(&data->c);
	class_destroy(data->cls);
	unregister_chrdev_region(data->dev, 1);
	return 0;
}

/* probe function is to invoked i2c driver */

static int i2c_probe(struct client *client, const struct i2c_device_id *id)
{
	struct i2c_data *data;
	int r;
	printk(KERN_INFO "Probe function is invoked...\n");
	data = devm_kzalloc(&client->dev, sizeof(struct i2c_data), GFP_KERNEL);
	data->value = 20;
	data->buf = devm_kzalloc(&client->dev, data->value, GFP_KERNEL);
	i2c_set_clientdata(client, data);
	r = alloc_chrdev_region(&data->dev, 0, 1, "i2c_shrv_drv");
	if(r < 0)
	{
		printk(KERN_ALERT "Device registration is failed....\n");
		unregister_chrdev_region(data->dev, 1);
		return -1;
	}
	printk(KERN_INFO "Major number = %d\n", MAJOR(data->dev));
	printk(KERN_INFO "Manor number = %d\n", MINOR(data->dev));
	if(data->cls = create_class(THIS_MODULE, "i2c_driver") == NULL)
	{
		printk(KERN_ALERT "Create class is failed....\n");
		unregister_chrdev_region(data->dev, 1);
		return -1;
	}
	if(device_create(data->cls, NULL, data->dev, NULL, "i2c_drv%d", 0) == NULL)
	{
		printk(KERN_ALERT "device Create is failed....\n");
		class_destroy(data->cls);
		unregister_chrdev_region(data->dev, 1);
		return -1;
	}
	cdev_init(&data->c, fops);
	if(cdev_add(&data->c, data->dev, 1)< 0)
	{
		printk(KERN_ALERT "cdev add is failed....\n");
		class_destroy(data->cls);
		unregister_chrdev_region(data->dev, 1);
		return -1;

	}
	return 0;
}
static struct i2c_driver i2c_drv
{
	.drvier = {
		.name = "i2c_shrvn",
		.owner = THIS_MODULE
	},
	.probe = i2c_probe,
	.remove = i2c_remove,
	id_table = id
};

static int __init init_cli_dri(void)
{
	/* Register i2c_core */
	return i2c_add_driver(&i2c_data);
}
static void __exit exit_cli_dri(int)
{
	/* unregister i2c_core */
	i2c_del_driver(&i2c_data);
}

module_init(init_cli_dri);
module_init(exit_cli_dri);

MODULE_AUTHOR("sharavan");
MODULE_LICENSE("gpl");
MODULE_DESCRIPTION("I2c client driver code");
