/* hello_param.c*/
/* Usage:
   sudo insmod module_param.ko

   OR

   sudo rmmod module_param.ko
 */

#include<linux/init.h>		/* to initiate a module */
#include<linux/module.h>	/* to recognise this module as a mmodule */

static char *whom = "Hello";
module_param(whom, charp, 0);
MODULE_PARM_DESC(whom, "Whom to greet?");

static int howmany = 3;
module_param(howmany, int, 0);
MODULE_PARM_DESC(howmany, "How many subjects?");

static int marks[3] = {18, 67, 90};
module_param_array(marks, int, &howmany, 0);
MODULE_PARM_DESC(marks, "Marks obtained");

static int __init hello_param_init(void) {
    /* entry point of the module */
    /* to register functionalities and to allocate resources */
    int i;
    printk(KERN_INFO "%s world", whom);
    for (i = 0; i < howmany; i++) {
	pr_alert("Subject-%d: %d\n", i, marks[i]);
    }

    return 0;
}

static void __exit hello_param_exit(void) {
    /* exit point of the module */
    /* to unregister functionalities and to deallocate resources */
    pr_alert(KERN_ALERT "GoodBye, cruel %s\n", whom);
}

module_init(hello_param_init);	/* whenever the module loads, just to
				   this line and start hello_init
				   function first */
module_exit(hello_param_exit);	/* when the module is removed,
				   initiate the function
				   hello_exit. And deallocate any
				   resources this module uses */

/* additional module info. Can be displayed when calling 'modinfo hello3.ko' */
MODULE_LICENSE("GPL");		/* license */
MODULE_AUTHOR("Tas Devil");	/* who wrote it */
MODULE_DESCRIPTION("hello3: Kernel module demo"); /* purpose of module */
MODULE_VERSION("0.9");
