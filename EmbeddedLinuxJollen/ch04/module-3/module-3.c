#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/config.h>

#ifdef CONFIG_SMP
# define __SMP__
#endif

int my_init_module(void)
{
   printk(KERN_ALERT "Hello, World.\n");

   return 0;
}

void my_cleanup_module(void)
{
   printk(KERN_ALERT "Goodbye...\n");
}

module_init(my_init_module);
module_exit(my_cleanup_module);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jollen <jollen@o3.net>");
MODULE_DESCRIPTION("A Linux kernel module programming example");
MODULE_SUPPORTED_DEVICE("testdevice");
