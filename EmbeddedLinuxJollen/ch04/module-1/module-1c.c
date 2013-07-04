#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/config.h>

#ifdef CONFIG_SMP
# define __SMP__
#endif

int init_module(void)
{
   printk(KERN_ALERT "Hello, World.\n");

   return 0;
}

void cleanup_module(void)
{
   printk(KERN_ALERT "Goodbye...\n");
}
