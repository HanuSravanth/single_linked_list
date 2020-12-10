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
	//list to store union
	Slist u = slist_new();
	Slist *list = &u;
	// temp variable
	Node *cur = list1->head;
	// first copy a  list
	for (cur = list1->head; cur != NULL; cur = cur->next)
	{
		slist_addnode_tail(list, cur->data)
	}

	Node *cur = list1->head;
	for (cur = list1->head; cur != NULL; cur = cur->next)
	{
		if (slist_lookup(list2, cur->data) != 1)
		{
			slist_addnode_tail(list, cur->data)
		}
	}
	return list;
}

Slist* slist_intersection(Slist *list1, Slist *list2)
{
	assert(list1 != NULL);
	assert(list2 != NULL);
	//new list to store intersection
	Slist i = slist_new();
	Slist *list = &i;
	// temp variable
	Node *cur = list1->head;
	for (cur = list1->head; cur != NULL; cur = cur->next)
	{
		if (slist_lookup(list2, cur->data) == 1)
		{
			slist_addnode_tail(list, cur->data);
		}
	}
	return list;
}

int8_t slist_unique(const Slist *list)
{
	assert(list != NULL);
	// length of intersection of a list after intersection with itself will remain same
	// if the elements are unique. same is true for union as well
	return (slist_length(slist_intersection(list, list)) == slist_length(list));
}


























