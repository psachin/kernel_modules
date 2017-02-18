/* pkt_drop.c
 * Author: Kiran Kankipati
 * Updated: 09-feb-2017
 * URL: http://the-linux-channel.the-toffee-project.org/index.php?page=38-videos-linux-kernel-programming
 */
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/udp.h>
#include <linux/ip.h>
#include <linux/in.h>
#include <linux/string.h>
#include <linux/init.h>
#include <linux/net.h>
#include <linux/netdevice.h>
#include <linux/socket.h>
#include <linux/sockios.h>
#include <linux/inet.h>
#include <linux/inetdevice.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/if_arp.h>
#include <linux/icmp.h>
#include <linux/netlink.h>
#include <linux/mroute.h>
#include <net/checksum.h>
#include <net/inet_ecn.h>
#include <net/xfrm.h>
#include <net/route.h>
#include <net/sock.h>
#include <net/ip.h>
#include <net/tcp.h>
#include <net/arp.h>
#include <net/udp.h>
#include <net/icmp.h>
#include <net/inetpeer.h>
#include <net/protocol.h>
#include <net/flow.h>
#include <asm/types.h>

static struct nf_hook_ops nfho_pre_routing;

unsigned int pre_routing_hook_func(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)
{
	//kfree_skb(skb);  //- dont do this, this will crash your system.
	return NF_DROP; //this will drop the packet

	//return NF_ACCEPT; //this will accept the packet
}


static int hello_init(void)
{
	//Packet RX
	nfho_pre_routing.hook = pre_routing_hook_func;
	nfho_pre_routing.hooknum = NF_INET_PRE_ROUTING;
	nfho_pre_routing.pf = PF_INET;
	nfho_pre_routing.priority = NF_IP_PRI_FIRST;
	nf_register_hook(&nfho_pre_routing);

	return 0;
}

static void hello_exit(void) { nf_unregister_hook(&nfho_pre_routing); }

module_init(hello_init);
module_exit(hello_exit);
