/*
*lish.h
*The specification for linked list data structure
*@author: Ann Sung Phang (481605)
*@version: April 2019
*/

#pragma once

#include "bst.h"

typedef struct listNode
{
	char *data;
	AVL avl;
	struct listNode *next;
} *ListNodePtr;

typedef struct list
{
	ListNodePtr head;
} List;


List new_list(void);

void insert_at_front(List *self, AVL *avl, char *data);

ListNodePtr search_list_node(ListNodePtr self, char *data);

void free_list(ListNodePtr self);

void match_print_list_node(ListNodePtr self, long int data);

void print_list_avl_node(ListNodePtr self);