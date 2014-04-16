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

static struct usb_device *device;
 
static int pen_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
  struct usb_host_interface *iface_desc;
  struct usb_endpoint_descriptor *endpoint;
  int i;

  iface_desc = interface->cur_altsetting;
  printk(KERN_INFO "[PD]: device i/f %d, (%04X:%04X) plugged\n", 
	 iface_desc->desc.bInterfaceNumber, id->idVendor, id->idProduct);
  printk(KERN_INFO "ID->bNumEndpoints: %02X\n", 
	 iface_desc->desc.bNumEndpoints);
  printk(KERN_INFO "ID->bInterfaceClass: %02X\n",
	 iface_desc->desc.bInterfaceClass);

  for (i = 0; i < iface_desc->desc.bNumEndpoints; i++)
    {
      endpoint = &iface_desc->endpoint[i].desc;
      
      printk(KERN_INFO "ED[%d]->bEndpointAddress: 0x%02X\n",
	     i, endpoint->bEndpointAddress);
      printk(KERN_INFO "ED[%d]->bmAttributes: 0x%02X\n",
	     i, endpoint->bmAttributes);
      printk(KERN_INFO "ED[%d]->wMaxPacketSize: 0x%04X (%d)\n",
	     i, endpoint->wMaxPacketSize, endpoint->wMaxPacketSize);
    }
  //  device = interface_to_usbdev(interface);
  return 0;
}
 
static void pen_disconnect(struct usb_interface *interface)
{
  printk(KERN_INFO "[PD]: device disconnected\n");
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
