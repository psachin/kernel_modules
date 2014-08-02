/* hello_param.c*/
/* Usage:
   sudo insmod hello_param.ko

   OR

   sudo rmmod hello_param.ko
 */

#include<linux/init.h>		/* to initiate a module */
#include<linux/module.h>	/* to recognise this module as a mmodule */

/* additional module info. Can be displayed when calling 'modinfo hello3.ko' */
MODULE_LICENSE("GPL");		/* license */
MODULE_AUTHOR("Tas Devil");	/* who wrote it */
MODULE_DESCRIPTION("hello3: Kernel module demo"); /* purpose of module */

static char *whom = "world";
module_param(whom, charp, 0);

static int howmany = 1;
module_param(howmany, int, 0);


static int __init hello_param_init(void) {
    /* entry point of the module */
    /* to register functionalities and to allocate resources */
    int i;
    for (i = 0; i < howmany; i++) {
	pr_alert("(%d) Hello, %s\n", i, whom);
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

