/* USB storage driver */
/* It only register itself with the kernel and invokes when device is
   attached. No further operation on device is done */
/* usage:
   % make 
   % insmod stick_driver.ko
   
   insert your device
 */

#include<linux/kernel.h>
#include<linux/module.h>
#include<linux/usb.h>

/* Local vars */
USB_VENDOR_ID_SONY_16G = 0x054c
USB_DEVICE_ID_SONY_16G = 0x0439

USB_VENDOR_ID_SUPERTOP_CARD_READER = 0x14cd
USB_DEVICE_ID_SUPERTOP_CARD_READER = 0x125a


/* probe function */
/* called if the device is inserted if no other driver is handling the device */
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id){
  printk(KERN_INFO "SUPERTOP: Multi SDcard reader with %04x:%04x plugged\n", id->idVendor, id->idProduct);
  return 0;			/* device identified by THIS driver */
}

/* disconnect */
static void pen_disconnect(struct usb_interface *interface){
  printk(KERN_INFO "SUPERTOP: Multi SDcard reader removed\n");
}

// usb_device_id structure
static struct usb_device_id pen_table[] = 
  {
    // 054c:0439
    { USB_DEVICE(USB_VENDOR_ID_SONY_16G, USB_DEVICE_ID_SONY_16G)}, /* obtained from lsusb | SONY 16G pen drive */
    { USB_DEVICE(USB_VENDOR_ID_SUPERTOP_CARD_READER, USB_DEVICE_ID_SUPERTOP_CARD_READER)}, /* multi SDcard reader | SUPERTOP */
    {}				   /* terminating entry */
  };
MODULE_DEVICE_TABLE(usb, pen_table);

// structure of usb driver
static struct usb_driver pen_driver = 
  {
    .name = "SUPERTOP multi SDcard reader driver",
    .id_table = pen_table,	/* usb_device_id */
    .probe = pen_probe,		/* probe the device when attached */
    .disconnect = pen_disconnect, /* called when disconnected */
  };

static int __init pen_init(void){
  /* register device */
  int ret = -1;
  printk(KERN_INFO "SUPERTOP: Registering device with kernel");
  ret = usb_register(&pen_driver);
  printk(KERN_INFO "SUPERTOP: registration complete.");
  return ret;
}


static void __exit pen_exit(void){
  /* deregister device */
  printk(KERN_INFO"SUPERTOP: Deregistering device..");
  usb_deregister(&pen_driver);
  printk(KERN_INFO "SUPERTOP: Deregistration complete");
    
}

module_init(pen_init);
module_exit(pen_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tas Devil");
MODULE_DESCRIPTION("USB pen drive registration driver");

