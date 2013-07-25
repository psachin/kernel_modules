/* passing parameter to a module */
/* Usage:
   sudo insmod hello2.ko

   OR

   sudo insmod hello2.ko param_var=54
 */
#include<linux/init.h>		/* to initiate a module */
#include<linux/module.h>	/* to recognise this module as a mmodule */
#include<linux/moduleparam.h>	/* needed for passsing params to a module */

/* deaclare a variable */
int param_var = 83434;

/* register a variable */
/* SYNTAX: module_param(var_name, type, permissions) */
/* 
   // permissions
   S_IRUSR: R-read, USR-user
   S_IWUSR: W-write,
   S_IXUSR: X-execute

   S_IWGRP: GRP-group
   S_IXGRP:

   // or combinations
   S_IRUSR | S_IWUSR
   
 */
module_param(param_var, int, S_IRUSR | S_IRUSR);

/* some custom function */
void display() {
  /* prints the value of parameters */
  printk(KERN_ALERT "HELLO2: param = %d",param_var);
}

static int hello2_init(void) {
  /* entry point of the module */
  /* to register functionalities and to allocate resources */
  printk(KERN_ALERT "HELLO2: cruel world\n");
  display();			/* calls display() */
  return 0;
}

static void hello2_exit(void) {
  /* exit point of the module */
  /* to unregister functionalities and to deallocate resources */
  printk(KERN_ALERT "HELLO2: GoodBye kernel\n");
  
}

module_init(hello2_init);	/* whenever the module loads, just to
				   this line and start hello_init
				   function first */
module_exit(hello2_exit);	/* when the module is removed,
				   initiate the function
				   hello_exit. And deallocate any
				   resources this module uses */

