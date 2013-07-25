/* passing arrays to a module */
/* Usage:
   sudo insmod hello3.ko

   OR

    sudo insmod hello3.ko param_var=45,61,90
 */

#include<linux/init.h>		/* to initiate a module */
#include<linux/module.h>	/* to recognise this module as a mmodule */
#include<linux/moduleparam.h>	/* needed for passsing params to a module */

/* additional module info. Can be displayed when calling 'modinfo hello3.ko' */
MODULE_LICENSE("GPL");		/* license */
MODULE_AUTHOR("Tas Devil");	/* who wrote it */
MODULE_DESCRIPTION("Kernel module demo"); /* purpose of module */

/* deaclare a variable */
int param_var[3] = {0,0,0};

/* register an array variable */
/* SYNTAX: module_param_array(var_name, type, total_number_of_parameters, permissions) */
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
module_param_array(param_var, int, NULL, S_IRUSR | S_IRUSR);

/* some custom function */
void display() {
  /* prints the value of parameters */
  printk(KERN_ALERT "HELLO3: param1 = %d",param_var[0]);
  printk(KERN_ALERT "HELLO3: param2 = %d",param_var[1]);
  printk(KERN_ALERT "HELLO3: param3 = %d",param_var[2]);
}

static int hello3_init(void) {
  /* entry point of the module */
  /* to register functionalities and to allocate resources */
  printk(KERN_ALERT "HELLO3: module inserted\n");
  display();			/* calls display() */
  return 0;
}

static void hello3_exit(void) {
  /* exit point of the module */
  /* to unregister functionalities and to deallocate resources */
  printk(KERN_ALERT "HELLO3: GoodBye kernel\n");
  
}

module_init(hello3_init);	/* whenever the module loads, just to
				   this line and start hello_init
				   function first */
module_exit(hello3_exit);	/* when the module is removed,
				   initiate the function
				   hello_exit. And deallocate any
				   resources this module uses */

