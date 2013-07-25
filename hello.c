#include<linux/init.h>		/* to initiate a module */
#include<linux/module.h>	/* to recognise this module as a mmodule */


static int hello_init(void) {
  /* entry point of the module */
  printk(KERN_ALERT "Test: hello cruel world\n");
  return 0;
}

static void hello_exit(void) {
  /* exit point of the module */
  printk(KERN_ALERT "Test: GoodBye kernel\n");
  
}

module_init(hello_init);	/* whenever the module loads, just to
				   this line and start hello_init
				   function first */
module_exit(hello_exit);	/* when the module is removed,
				   initiate the function
				   hello_exit. And deallocate any
				   resources this module uses */
