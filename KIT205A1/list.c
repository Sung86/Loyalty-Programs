/*
*lish.c
*The implementation for list ADT
*
*@author: Ann Sung Phang (481605)
*@version: April 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "bst.h"

/*
*List Constructor
*
*@return List //new list
*/
List new_list(void)
{
	List temp;
	temp.head = NULL;
	return temp;
}

/*
*Insert the data into the front of the list and link the program to a AVL tree
*
*@param self //the given list
*@param avl //the given AVL tree to be linked to 
*@param data //the data to be inserted into the list
*/
void insert_at_front(List *self, AVL *avl, char *data)
{
	ListNodePtr new_node = malloc(sizeof *new_node); // new list node to store program name
	new_node->data = malloc(strlen(data) + 1); //storing given data into dynamically alocated memory

	strcpy_s(new_node->data,strlen(data) + 1 ,data);
	new_node->avl = *avl;
	new_node->next = self->head;
	self->head = new_node;
}

/*
*Search the nodes of list for the given data
*
*@param self //the given list
*@param data // the given data
*@return ListNodePtr //the found list node
*/
ListNodePtr search_list_node(ListNodePtr self, char* data)
{
	if (self == NULL || strcmp(self->data, data) == 0)
		return self;

	return search_list_node(self->next, data);
}

/*
*Match the given data value with each avl node that linked by the given list head 
*and print the data field node of list
*
*@param self //head of given list root
*@param data //given data value
*/
void match_print_list_node(ListNodePtr self, long int data) 
{
	if (self != NULL)
	{
		if(search_avl(&self->avl, data) != NULL)
			printf("%s\n", self->data);
		match_print_list_node(self->next, data);
	}	
}

/*
*Print all the list nodes and count nodes of the AVL tree
*
*@param self //head of given list
*/
void print_list_avl_node(ListNodePtr self)
{
	if (self != NULL)
	{
		printf("\n%s\t\t%d", self->data, count_avl(&self->avl));
		print_list_avl_node(self->next);
	}
}

/*
*Free the dynamically allocated memory of all the nodes of given list head
*
*@param *self //head of given list 
*/
void free_list(ListNodePtr self) 
{
	if (self->next)
		free_list(self->next);

	free(self);
}
