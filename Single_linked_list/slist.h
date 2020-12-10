/*
 * slist.h
 *
 *  Created on: Nov 26, 2020
 *      Author: hanus
 */

#ifndef SLIST_H_
#define SLIST_H_

#include <stdint.h>

typedef struct _node_ Node;
struct _node_
{
	int32_t data; /* data */
	Node *next; /* address of next node */
};


typedef struct _slist_ Slist;
struct _slist_
{
	Node *head;
	Node *tail;
	uint32_t length;
};

/*functions*/
Slist slist_new();
uint8_t slist_lookup(const Slist *list, int32_t key); /* read only operation */
uint32_t slist_length(const Slist *list);
Slist* slist_addnode_head(Slist *list, int32_t val);
Slist* slist_addnode_tail(Slist *list, int32_t val);
Slist* slist_delnode_head(Slist *list);
Slist* slist_delnode_tail(Slist *list);

// methods to find maximum and minimum elements in the list
int32_t slist_max(const Slist *list);
int32_t slist_min(const Slist *list);

//union, intersection and uniqueness
Slist* slist_union(Slist *list1, Slist *list1);
Slist* slist_intersection(Slist *list1, Slist *list1);
int32_t slist_unique(const Slist *list);

#endif /* SLIST_H_ */
