/*
 * utils.h
 *
 *  Created on: Jul 24, 2017
 *      Author: cem
 */

#ifndef UTILS_H_
#define UTILS_H_
#import "macs.h"


int append(char*s, char c);
void print_bcast(struct query_bcast *q);
void macInfo(macs_node *m);
void init_nodes();
void fetch_fromFile(FILE *fp, macs_node *head);
void write2file(FILE *f, uint8_t buf[60]);
macs_node *getMacDetails(char *mac, macs_node *head);

#endif /* UTILS_H_ */
