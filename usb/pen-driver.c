/* 
   pen_driver.c
   Original author: Anil Kumar Pugalia <email_at_sarika-pugs_dot_com>

   Usage:
   % make
   % sudo insmod pen-driver.c
   % sudo rmmod pen-drive.c
 */
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>
 
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
  printk(KERN_INFO "[PD]: device (%04X:%04X) plugged\n", id->idVendor, id->idProduct);
  return 0;
}
 
static void pen_disconnect(struct usb_interface *interface)
{
  printk(KERN_INFO "[PD]: device removed\n");
}
 
static struct usb_device_id pen_table[] =
  {
    { USB_DEVICE(0x14cd, 0x125a) }, /* Super Top */
    { USB_DEVICE(0x054c, 0x0439) }, /* Sony Corp. */
    { USB_DEVICE(0x058F, 0x6387) },
    {} /* Terminating entry */
  };
MODULE_DEVICE_TABLE (usb, pen_table);
 
static struct usb_driver pen_driver =
  {
    .name = "pen-driver",
    .id_table = pen_table,
    .probe = pen_probe,
    .disconnect = pen_disconnect,
  };
 
static int __init pen_init(void)
{
  printk(KERN_INFO "[PD]: module loaded\n");
  return usb_register(&pen_driver);
}
 
static void __exit pen_exit(void)
{
  printk(KERN_INFO "[PD]: module unloaded\n");
  usb_deregister(&pen_driver);
}
 
module_init(pen_init);
module_exit(pen_exit);
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tas Devil");
MODULE_DESCRIPTION("USB Pen Registration Driver");
