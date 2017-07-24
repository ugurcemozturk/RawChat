/*
 * macs.h
 *
 *  Created on: Jul 23, 2017
 *      Author: cem
 */

#ifndef SRC_MACS_H_
#define SRC_MACS_H_

typedef struct Macs_List {
	char mac[12];
	char name[10];
	char surname[10];
	struct macs_node *next;
} macs_node;


macs_node *init_list();

void push(macs_node*, macs_node *);

void print_list(macs_node * head);

#endif /* SRC_MACS_H_ */
