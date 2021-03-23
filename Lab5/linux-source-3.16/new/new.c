#include <linux/kernel.h>

asmlinkage long sys_new(void)
{
        printk(KERN_ALERT "Greeting from kernel and team 20!\n");
        return 0;
}