/* fake char device */
/* Usage:
   % make 
   % insmod testCharDevice.ko
   % sudo mknod /dev/testCharDevice c major_number minor_number
 */

#include<linux/init.h>		/* to initiate a module */
#include<linux/module.h>	/* to recognise this module as a mmodule */
#include<linux/fs.h>		/* file operation structure, which
				   allows to use to open/close and
				   read/write the device */
#include<linux/cdev.h>		/* needed for char device, make cdev
				   available. userspace to kernel
				   space */
#include<linux/semaphore.h>	/* used acces to semaphore, process management
				   syncronization behaviour */
#include<asm/uaccess.h>		/* copy_to_user;copy_from_user */
#include<linux/device.h>

/* (1)create structure for fake char device */
struct fake_device
{
  char data[100];
  struct semaphore sem;
} virtual_device;

/* (2) to register our device */
/* we need a cdev object and some other variables */
struct cdev *mcdev;		/* m --> my */
int major_number, minor_number; /* will store a major and minor number extracted
				 from dev_t using macro 
				 mknod /dev/file c major minor */

int ret; 			/* will hold return value of the
				   function; this is because the
				   kernel stack is very small so
				   declaring variable will eat up the
				   stack very fast */
dev_t dev_num;			/* will hold the device number that
				   the kernel gives; name appears in
				   /proc/devices */
static struct class *cl; // Global variable for the device class
#define DEVICE_NAME "testCharDevice"

/* (7) called on device_open
   inode refer to file in disk 
   and contains info about that file
   struct file : is refer to an abstract open file
 */
int device_open(struct inode *inode, struct file *filp) {
  /* only allow one person to open this device by using a semaphore as
     mutual exclusive lock - mutex */
  if(down_interruptible(&virtual_device.sem) != 0) {
    printk(KERN_ALERT "testCharDevice: could not lock device during open");
    return -1;
  }

  printk(KERN_INFO "testCharDevice: opened device");
  return 0;
}

/* (8) called when user want to get information about device */
ssize_t device_read(struct file *filp, char *bufStoreData,
		    size_t bufCount, loff_t* curOffset) 
{
  /* take data from kernel(device) to user space(process) */
  /* copy_to_user(destination, source, sizeToTransfer) */
  printk(KERN_INFO "testCharDevice: reading from device");
  ret = copy_to_user(bufStoreData, virtual_device.data, bufCount);
  return ret;
}

/* (9) called when user wants to send information to device */
ssize_t device_write(struct file *filp, const char *bufSourceData, 
		     size_t bufCount, loff_t* curOffset)
{
  /* send data from user to kernel */
  /* copy_from_user(dest, source, count) */
  printk(KERN_INFO "testCharDevice: writing to device");
  ret = copy_from_user(virtual_device.data, bufSourceData, bufCount);
  return ret;
}

/* (10) called upon user close */
int device_close(struct inode *inode, struct file *filp) 
{
  /* by calling up, which is opposite to down of semaphore, we release
     the mutex that we obtained at device open. This has the effect of
     other process can access thr device now */
  up(&virtual_device.sem);
  printk(KERN_INFO "testCharDevice: closed device");
  return 0;
}

/* (6)tells the kernel which function to call when user operates on our
   device file */
struct file_operations fops =
{
  .owner = THIS_MODULE,		/* prevent unloading of this module when operatons are in use */
  .open = device_open,		/* points to the method to call opening the device */
  .release = device_close,	/* closing the device */
  .write = device_write,	/* writing a device */
  .read = device_read		/* reading from device */
};

static int driver_entry(void) {
  /* (3) r3gister device isa two step process: */

  /* ---------(1)----------- */
  /* use dynamic allocation to assign our device a major number
     -- 
     alloc_chrdev_region(dev_t*,unsigned int dev_num_minor, unsigned int count, char* name);
   */

  ret = alloc_chrdev_region(&dev_num, 0, 3, DEVICE_NAME);
  /* arg1: dev_name will hold both major number and minor number */
  /* arg2: start from minor 0 and loop till 3(will allocates minor number
     in the range 0-3) */
  /* arg3: DEVICE_NAME */
  if(ret<0) {
    /* if kernel returns a negative number, means failed to allocate
       major number */
    printk(KERN_ALERT "testCharDevice: failed to allocate major number");
    return ret;			/* error */
  }
  major_number = MAJOR(dev_num); /* extract major number from dev_num
				    and store it in our variable */
  minor_number = MINOR(dev_num); /* minor number */
  printk(KERN_INFO "testCharDevice: module loaded, device is: /dev/%s", 
	 DEVICE_NAME);
  printk(KERN_INFO "testCharDevice: major number is: %d, minor number is: %d",
	 major_number,
	 minor_number);

  /* ----------(2)---------- */
  mcdev = cdev_alloc();		/* create our cdev structure;
				   initialize cdev and allocate using
				   cdev_alloc() */
  mcdev->ops = &fops;		/* struct file operation */
  mcdev->owner = THIS_MODULE;	

  /* populate sysfs entries under /sys/class/chardev/ */
  if ((cl = class_create(THIS_MODULE, "chardev")) == NULL)
    {
      unregister_chrdev_region(dev_num, 1);
      return -1;
    }
  /* create /dev/testCharDevice node */
  if (device_create(cl, NULL, dev_num, NULL, DEVICE_NAME) == NULL)
    {
      class_destroy(cl);
      unregister_chrdev_region(dev_num, 1);
      return -1;
    }

  /* now that we have created our cdev, we have to add it to kernel */
  /* int cdev_add(struct cdev*, dev, dev_t num, unsigned int count) */
  ret = cdev_add(mcdev, dev_num, 1);
  if(ret<0) {
    /* check errors */
    printk(KERN_ALERT "testCharDevice: unable to add cdev to kernel");
    return ret;
  }
  
  /* (4) Initialize our semaphore */
  sema_init(&virtual_device.sem,1); /* initial value of one */
  return 0;
}

static void driver_exit(void) {
  /* (5) unregister everything in reverse order */
  // (a)
  cdev_del(mcdev);
  device_destroy(cl, dev_num);	/* delete node /dev/testCharDevice */
  class_destroy(cl);		/* delete sysfs */
  // (b)
  unregister_chrdev_region(dev_num, 1);
  printk(KERN_INFO "testCharDevice: module unloaded");
    
}

/* inform kernel wher to start and stop our module */
module_init(driver_entry);	
module_exit(driver_exit); 

/* additional module info. Can be displayed when calling 'modinfo' */
MODULE_LICENSE("GPL");		/* license */
MODULE_AUTHOR("Tas Devil");	/* who wrote it */
MODULE_DESCRIPTION("Kernel module for character device"); /* purpose of module */
