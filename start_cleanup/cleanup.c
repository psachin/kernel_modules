#include <linux/kernel.h>
#include <linux/module.h>

static void __exit hello_exit(void) {
    printk(KERN_INFO "Function: %s from %s file", __func__, __FILE__);
}

module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tas Devil");
MODULE_DESCRIPTION("Cleanup module");
MODULE_VERSION("0.9");

