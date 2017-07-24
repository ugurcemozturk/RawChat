/*
 * m.c
 *
 *  Created on: Jul 21, 2017
 *      Author: ubuntu
 */

/*
 * recv.c
 *
 *  Created on: Jul 21, 2017
 *      Author: ubuntu
 */

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <linux/ip.h>
#include <linux/udp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/ether.h>

#include "packets.h"
#include "macs.h"
#include "utils.h"

#define DEST_MAC0    0xff
#define DEST_MAC1    0xff
#define DEST_MAC2    0xff
#define DEST_MAC3    0xff
#define DEST_MAC4    0xff
#define DEST_MAC5    0xff

#define ETHER_TYPE    0x1234
#define DEFAULT_IF    "enx0080c9000702"
#define BUF_SIZ        1024

int append(char*s, char c) {
	int len = strlen(s);
	s[len] = c;
	s[len + 1] = '\0';
	return 0;
}

void print_bcast(struct query_bcast *q) {
	printf("%02X \n", q->mac);
	printf("%s \n", q->name);
	printf("%s \n", q->surname);
}
void macInfo(macs_node *m) {
	printf("%s \n", m->mac);
	printf("%s \n", m->name);
	printf("%s \n", m->surname);
}
void init_nodes() {
	FILE f;

}
void fetch_fromFile(FILE *fp, macs_node *head) {
	size_t len = 0;
	ssize_t read;
	char * line = NULL;
	char *split;

	fp = fopen("filee.txt", "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	/*Satir satir oku ve yeni node init. et*/
	while ((read = getline(&line, &len, fp)) != -1) {
		macs_node *mac = malloc(sizeof(macs_node));

		split = strtok(line, " ");
		strcpy(mac->mac, split);

		split = strtok(NULL, " ");
		strcpy(mac->name, split);

		split = strtok(NULL, " ");
		strcpy(mac->surname, split);

		push(head, mac);
	}

	fclose(fp);
	if (line)
		free(line);
}
void write2file(FILE *f, uint8_t buf[60]) {
	int k;

	for (k = 6; k < 12; k++) {
		fprintf(f, "%02X", buf[k]);
	}
	fprintf(f, "%s", " ");

	for (k = 15; k < 25; k++) {
		if (buf[k] == 0x00) {
			k++;
			continue;
		}
		fprintf(f, "%c", buf[k]);
	}

	fprintf(f, " %s", " ");

	for (k = 25; k < 35; k++) {
		if (buf[k] == 0x00) {
			k++;
			continue;
		}
		fprintf(f, "%c", buf[k]);
	}

	fprintf(f, " %s", " \n");
	fclose(f);
}
macs_node *getMacDetails(char *mac,macs_node *head){
	macs_node *curr = malloc(sizeof(macs_node));
	curr=head;

	while(curr->name!=mac && curr!=NULL){
		curr=curr->next;
	}
	return curr;
}


	/*uint8_t buf[60] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x88, 0x41, 0xfc,
			0xa5, 0xc4, 0xf2, 0x12, 0x34, 0x00, 0x6b, 0x69, 0x76, 0x61, 0x6e,
			0x63, 0x00, 0x00, 0x00, 0x00, 0x63, 0x61, 0x6b, 0x6d, 0x61, 0x6b,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };*/



