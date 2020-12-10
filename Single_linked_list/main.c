/*
 * main.c
 *
 *  Created on: Nov 26, 2020
 *      Author: hanus
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "slist.h"

void test_Slist()
{
	Slist s1 = slist_new();
	Slist *list = &s1;
	assert(slist_length(list) == 0); // length function
	list = slist_addnode_head(list, 4); // addnode_head function
	assert(slist_length(list) == 1);
	list = slist_addnode_head(list, 5);
	list = slist_addnode_head(list, 6);
	assert(slist_length(list) == 3);
	assert(slist_lookup(list, 4) == 1); // lookup function
	list = slist_delnode_head(list); // delnode_head function
	assert(slist_length(list) == 2);
	assert(slist_lookup(list, 4) == 1);
	list = slist_delnode_tail(list); // delnode_tail function
	assert(slist_length(list) == 1);
	assert(slist_lookup(list, 5) == 1);
}

void test_min_max()
{
	Slist s2= slist_new();
	Slist *list1 = &s2;
	assert(slist_length(list1) == 0);
	list1 = slist_addnode_head(list1, 4);
	list1 = slist_addnode_head(list1, 5);
	list1 = slist_addnode_head(list1, 6);
	list1 = slist_addnode_head(list1, 7);
	assert(slist_length(list1) == 4);
	assert(slist_max(list1) == 7);
	assert(slist_min(list1) == 4);
}

void test_addnode_mid()
{
	Slist s2= slist_new();
	Slist *list1 = &s2;
	assert(slist_length(list1) == 0);
	list1 = slist_addnode_head(list1, 4);
	list1 = slist_addnode_head(list1, 5);
	//list1 = slist_addnode_head(list1, 6);
	list1 = slist_addnode_head(list1, 7);
	assert(slist_length(list1) == 3);
	slist_addnode_middle(list1, 6, 2);
	assert(slist_length(list1) == 4);
	assert(slist_lookup(list1, 6) == 2);
}

int main()
{
	//test_Slist();
	//test_min_max();
	test_addnode_mid();
	return 0;
}



/*
 * slist.c
 *
 *  Created on: Nov 26, 2020
 *      Author: hanus
 */

#include <stdlib.h> /* required for dunamic allocation of memory*/
#include <assert.h> /* required to write assert based tests*/
#include "slist.h"


Slist slist_new()
{
	Slist s1 = {NULL, NULL, 0};
	return s1;
}


uint8_t slist_lookup(const Slist *list, int32_t key)
{
	assert(list != NULL);
	Node *cur = list->head;
	for (cur = list->head; cur != NULL; cur = cur->next)
	{
		if (cur->data == key)
		{
			break;
		}
	}
	return (cur != NULL);
}

uint32_t slist_length(const Slist *list)
{
	assert(list != NULL);
	return list -> length;
}

// helper function to create a node
static Node* _get_new_node_ (int32_t val)
{
	Node *newnode = (Node*)malloc(sizeof(Node));
	newnode->data = val;
	newnode->next = NULL;

	return newnode;
}

Slist* slist_addnode_middle(Slist *list, int32_t val, int32_t key)
{
	assert(list != NULL);
	assert( key < slist_length(list));
	Node *temp, *p;
	int32_t i = 1;
	Node *newnode = _get_new_node_(val);

	p = list->head;
	while (i < key) //traverse till the node after which newnode to be inserted
	{
		p = p->next;
		i++;
	}

	temp->next = p->next;
	p->next = temp;

	++list->length;

	assert( (list->length == 1) && (list->head == list->tail)  || // @suppress("Suggested parenthesis around expression")
			(list->length > 1)  && (list->head != list->tail)  );

	return list;
}

Slist* slist_addnode_head(Slist *list, int32_t val)
{
	assert(list != NULL);
	Node *newnode = _get_new_node_(val);

	newnode->next = list->head;
	list->head = newnode;
	if (list->tail == NULL)
	{
		list->tail = newnode;
	}
	++list->length;

	assert( (list->length == 1) && (list->head == list->tail)  || // @suppress("Suggested parenthesis around expression")
			(list->length > 1)  && (list->head != list->tail)  );

	return list;
}

Slist* slist_addnode_tail(Slist *list, int32_t val)
{
	assert(list != NULL);
	Node *newnode = _get_new_node_(val);
	if (list->tail != NULL)
	{
			list->tail->next = newnode;
			list->tail = newnode;
	}
	else
	{
		list->head = list->tail = newnode;
	}

	++list->length;

	assert( (list->length == 1) && (list->head == list->tail)  || // @suppress("Suggested parenthesis around expression")
			(list->length > 1)  && (list->head != list->tail)  );

	return list;

}

Slist* slist_delnode_head(Slist *list)
{
	assert(list != NULL);
	Node *temp;
	if (list->head != NULL)
	{
		temp = list->head;
		list->head = list->head->next;
		if(list->head == NULL)
		{
			list->tail = NULL;
		}
		--list->length;
		free(temp);
	}
	return list;
}

Slist* slist_delnode_tail(Slist *list)
{
	assert(list != NULL);
	Node *last, *cur;

	if (list->tail != NULL)
	{
		last = list->tail;
		if (list->head == list->tail)
		{
			list->head = list->tail = NULL;
		}
		else
		{
			for (cur = list->head; cur->next != last; cur = cur->next);
				list->tail = cur;
				cur->next = NULL;
		}
		--list->length;
		free(last);
	}
	return list;
}


// methods to find maximum and minimum elements in the list
int32_t slist_max(const Slist *list)
{
	assert(list != NULL);
	int32_t max = 0;
	Node *cur = list->head;

	for (cur = list->head; cur != NULL; cur = cur->next)
	{
		if (cur->data > max)
		{
			max = cur->data;
		}
	}
	return max;
}

int32_t slist_min(const Slist *list)
{
	assert(list != NULL);
	int32_t min = slist_max(list); // initialize with high value
	Node *cur = list->head;

	for (cur = list->head; cur != NULL; cur = cur->next)
	{
		if (cur->data < min)
		{
			min = cur->data;
		}
	}
	return min;
}


//union, intersection and uniqueness
Slist* slist_union(Slist *list1, Slist *list2)
{
	assert(list1 != NULL);
	assert(list2 != NULL);



}
Slist* slist_intersection(Slist *list1, Slist *list2)
{

}
int32_t slist_unique(const Slist *list)
{

}

































































