/*
 * macs.c
 *
 *  Created on: Jul 23, 2017
 *      Author: cem
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "macs.h"

macs_node *init_list() {
	macs_node * head = NULL;
	head = malloc(sizeof(macs_node));

	if (head == NULL) {
		return 1;
	}
	head->next = NULL;
	return head;
}

void push(macs_node * head, macs_node *node) {
	macs_node * current = head;
	while (current->next != NULL) {
		current = current->next;
	}

	current->next = node;
	node->next = NULL;
}
void print_list(macs_node * head) {
	macs_node * current = head->next;

    while (current->next!= NULL) {
        printf("%s\n", current->mac);
        printf("%s\n", current->name);
        printf("%s\n", current->surname);
        puts("  |\n  |\n  V");

        current = current->next;

    }
}

