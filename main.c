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

int main()
{
	test_Slist();
    /*printf("Hello World!");*/
	return 0;
}

