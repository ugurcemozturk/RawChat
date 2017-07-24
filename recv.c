#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/ether.h>

#include "packets.h"
#include "utils.h"
#include "macs.h"

#define DEST_MAC0    0xff
#define DEST_MAC1    0xff
#define DEST_MAC2    0xff
#define DEST_MAC3    0xff
#define DEST_MAC4    0xff
#define DEST_MAC5    0xff

#define ETHER_TYPE    0x1234
#define DEFAULT_IF    "enx0080c9000702"
#define BUF_SIZ        1024




//TODO: Struclari dosyaya object olarak kaydet.
int main(int argc, char *argv[]) {

	int sockfd, ret, i;
	int sockopt;
	ssize_t numbytes;
	struct ifreq ifopts; /* set promiscuous mode */
	struct ifreq if_ip; /* get ip addr */
	uint8_t buf[BUF_SIZ];
	uint64_t temp[BUF_SIZ];
	char ifName[IFNAMSIZ];

	/* Get interface name */
	if (argc > 1)
		strcpy(ifName, argv[1]);
	else
		strcpy(ifName, DEFAULT_IF);

	/* Header structures */
	struct ether_header *eh = (struct ether_header *) buf;

	memset(&if_ip, 0, sizeof(struct ifreq));

	/* Open PF_PACKET socket, listening for EtherType ETHER_TYPE */
	if ((sockfd = socket(PF_PACKET, SOCK_RAW, htons(ETHER_TYPE))) == -1) {
		perror("listener: socket");
		return -1;
	}

	/* Set interface to promiscuous mode - do we need to do this every time? */
	strncpy(ifopts.ifr_name, ifName, IFNAMSIZ - 1);
	ioctl(sockfd, SIOCGIFFLAGS, &ifopts);
	ifopts.ifr_flags |= IFF_PROMISC;
	ioctl(sockfd, SIOCSIFFLAGS, &ifopts);
	/* Allow the socket to be reused - incase connection is closed prematurely */
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof sockopt)
			== -1) {
		perror("setsockopt");
		close(sockfd);
		exit(EXIT_FAILURE);
	}
	/* Bind to device */
	if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, ifName, IFNAMSIZ - 1)
			== -1) {
		perror("SO_BINDTODEVICE");
		close(sockfd);
		exit(EXIT_FAILURE);
	}

	repeat: printf("listener: Waiting to recvfrom...\n");
	numbytes = recvfrom(sockfd, buf, BUF_SIZ, 0, NULL, NULL);
	printf("listener: got packet %lu bytes\n", numbytes);

	/* Check the packet is for me */
	if (eh->ether_dhost[0] == DEST_MAC0 && eh->ether_dhost[1] == DEST_MAC1
			&& eh->ether_dhost[2] == DEST_MAC2
			&& eh->ether_dhost[3] == DEST_MAC3
			&& eh->ether_dhost[4] == DEST_MAC4
			&& eh->ether_dhost[5] == DEST_MAC5) {
		printf("Correct destination MAC address\n");
	} else {
		printf("Wrong destination MAC: %x:%x:%x:%x:%x:%x\n", eh->ether_dhost[0],
				eh->ether_dhost[1], eh->ether_dhost[2], eh->ether_dhost[3],
				eh->ether_dhost[4], eh->ether_dhost[5]);
		ret = -1;
		goto done;
	}


	memcpy(temp,buf,60);
	FILE *f= fopen("file.txt","ab");

	write2file(f,temp);

	macs_node *head = init_list();

	fetch_fromFile(f, head);
	print_list(head);
	getMacDetails("cem",head);

	done: goto repeat;

	close(sockfd);
	return ret;
}

