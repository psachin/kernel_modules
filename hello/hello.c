#include<linux/init.h>		/* to initiate a module */
#include<linux/module.h>	/* to recognise this module as a mmodule */

/* The __init macro causes the init function to be discarded and its
   memory to be freed once the init function finishes for built-in
   drivers, but not for loadable modules */
static int __init hello_init(void) {
  /* entry point of the module */
  printk(KERN_INFO "Test: hello cruel world\n");
  return 0;
}

/* the __exit macro works the same way as __init, it causes the
   omission of the function when built into the kernel but not for
   loadable modules */
static void __exit hello_exit(void) {
  /* exit point of the module */
  printk(KERN_INFO "Test: GoodBye kernel\n");
  
}

module_init(hello_init);	/* whenever the module loads, just to
				   this line and start hello_init
				   function first */
module_exit(hello_exit);	/* when the module is removed,
				   initiate the function
				   hello_exit. And deallocate any
				   resources this module uses */
