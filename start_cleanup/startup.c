#include <linux/kernel.h>
#include <linux/module.h>

static int __init hello_init(void) {
    printk(KERN_INFO "Function: %s from %s file\n", __func__, __FILE__);
    return 0;
}

module_init(hello_init);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tas Devil");
MODULE_DESCRIPTION("Startup module");
MODULE_VERSION("0.9");
