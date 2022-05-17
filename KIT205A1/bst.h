/*
*bst.h
*The specification of AVL Tree data structure
*
*@author: Ann Sung Phang (481605)
*@version: April 2019
*/

#pragma once

typedef struct avlNode
{
	long int data;
	struct avlNode *left;
	struct avlNode *right;
	int height;
} *AVLNodePtr;

typedef struct avl
{
	AVLNodePtr root;
} AVL;

AVL new_avl(void);

void insert_avl(AVL *self, long int data);

void delete_avl(AVL *self, long int data);

void print_in_order_avl(AVLNodePtr self);

AVLNodePtr search_avl(AVL *self, long int data);

int count_avl(AVL *self);

int height_avl(AVLNodePtr self);

void free_avl(AVLNodePtr self);


