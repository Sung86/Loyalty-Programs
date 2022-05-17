/*
*bst.c
*The implementation for AVL tree ADT
*
*@author: Ann Sung Phang (481605)
*@version: April 2019
*/

#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

/*
* AVL tree Constructor
*
*@return AVL // new AVL tree
*/
AVL new_avl(void)
{
	AVL temp;
	temp.root = NULL;
	return temp;
}

/*
*Count the total number of AVL tree nodes
*
*@param self //the root of AVL tree
*@return int //the current number of nodes in the AVL tree
*/
int count_avl_node(AVLNodePtr self)
{
	if (self == NULL)
		return 0;

	return 1 + count_avl_node(self->left) + count_avl_node(self->right);
}

/*
*Count the AVL tree nodes
*
*@param self // the whole AVL tree
*@return int // the total number of nodes in the AVL tree
*/
int count_avl(AVL *self)
{
	return count_avl_node(self->root);
}

/*
*Height of AVL sub-tree
*
*@param self //the root of AVL sub-tree
*@return //the height 
*/
int height_avl(AVLNodePtr self)
{
	if (self == NULL)
		return 0;

	return self->height;
}

/*
*To get the Balance Factor for AVL tree
*
*@param self //the root of AVL tree
*@return int //the Balance Factor
*/
int get_bal_factor(AVLNodePtr self)
{
	if (self == NULL)
		return 0;

	return height_avl(self->left) - height_avl(self->right);
}

/*
*Get the larger value from two given values
*
*@param a //the first given value
*@param b //the second given value
*@return int //the larger value
*/
int max_val(int a, int b)
{
	if (a > b)
		return a;

	return b;
}

/*
*Perform Left rotation for the given AVL tree node
*
*Right Right Case
*@param self //the given node
*@return AVLNodePtr // the new root
*/
AVLNodePtr left_rotate(AVLNodePtr self)
{
	AVLNodePtr x = self, y = x->right, b = y->left;

	//Perform the rotation
	y->left = x;
	x->right = b;

	//Make the sub-tree height up to date
	x->height = max_val(height_avl(x->left), height_avl(x->right)) + 1;
	y->height = max_val(height_avl(y->left), height_avl(y->right)) + 1;

	return y;
}

/*
*Perform right rotation for the given AVL tree node
*
*Left Left Case
*@param self //the given node
*@return AVLNodePtr // the new root
*/
AVLNodePtr right_rotate(AVLNodePtr self)
{
	AVLNodePtr y = self, x = y->left, b = x->right;

	//Perform the rotation
	x->right = y;
	y->left = b;

	//Make the sub-tree height up to date
	x->height = max_val(height_avl(x->left), height_avl(x->right)) + 1;
	y->height = max_val(height_avl(y->left), height_avl(y->right)) + 1;

	return x;
}


/*
*Perform rotation for keeping the tree balance
*
*@param self //the given node
*@param bal_factor //balance factor
*@return AVLNodePtr // the new root
*/
AVLNodePtr perform_avl_rotate(AVLNodePtr self, int bal_factor) 
{
	//Left Left Case
	if (bal_factor > 1 && get_bal_factor(self->left) >= 0)
		return right_rotate(self);

	//Left Right Case
	if (bal_factor > 1 && get_bal_factor(self->left) < 0)
	{
		self->left = left_rotate(self->left);
		return right_rotate(self);
	}

	//Right Right Case
	if (bal_factor < -1 && get_bal_factor(self->right) <= 0)
		return left_rotate(self);

	//Right Left Case
	if (bal_factor < -1 && get_bal_factor(self->right) > 0)
	{
		self->right = right_rotate(self->right);
		return left_rotate(self);
	}
	return self;
}

/*
*AVL Tree Insertion
*Insert data into the data field of AVL tree
*
*@param self // the root of the AVL tree
*@param data // the given data value
*@return AVLNodePtr // the root 
*/
AVLNodePtr insert_avl_node(AVLNodePtr self, long int data)
{
	int bal_factor = 0;//balance factor

	// Perform BST insertion //
	if (self == NULL)
	{ /* found where to put it*/
		self = malloc(sizeof *self);
		self->data = data;
		self->left = self->right = NULL;
		self->height = 1;
	}
	else if (data < self->data)
		self->left = insert_avl_node(self->left, data);

	else if (data > self->data)
		self->right = insert_avl_node(self->right, data);

	//Make the height of ancestor node up to date //
	self->height = 1 + max_val(height_avl(self->left), height_avl(self->right));

	//Check whether the tree is balanced or not//
	bal_factor = get_bal_factor(self);

	//Perform AVL rotation to keep the tree balance//
	return perform_avl_rotate(self, bal_factor);
}

/*
*Insert data into the data field of AVL tree node
*
*@param self // the whole AVL tree
*@param data //the given data value 
*/
void insert_avl(AVL *self, long int data)
{
	self->root = insert_avl_node(self->root, data);
}

/*
* Get the lowest level and value AVL tree node
*
* @param self //the AVL tree root
* @return AVLNodePtr //the minimum or lowest level of AVL tree node
*/
AVLNodePtr min_node(AVLNodePtr self)
{
	if (self->left != NULL)
	{
		self = self->left;
		min_node(self);
	}
	return self;
}

/*
*AVL Deletion
*Remove // Delete a AVL tree node 
*if the given data value matched with a data field
*
*@param self // the tree root
*@param data // the given data value
*@return AVLNodePtr // the AVL node
*/
AVLNodePtr delete_avl_node(AVLNodePtr self, long int data)
{
	int bal_factor = 0; //balance factor

	// Perform BST Deletion //
	if (self != NULL)
	{
		if (data == self->data)
		{ // found item
			if (self->left != NULL && self->right != NULL)
			{
				// two child case
				AVLNodePtr successor = min_node(self->right);
				self->data = successor->data;
				self->right = delete_avl_node(self->right, self->data);
			}
			else
			{ // one or zero child case
				AVLNodePtr temp = self;
				if (self->left) 
					self = self->left;

				else
					self = self->right;

				free(temp);
			}
		}
		else if (data < self->data)
			self->left = delete_avl_node(self->left, data);

		else
			self->right = delete_avl_node(self->right, data);
	}
	if (self == NULL) // if the root is empty
		return self;

	//Make the height up to date //
	self->height = 1 + max_val(height_avl(self->left), height_avl(self->right));

	//Check whether the tree is balanced or not//
	bal_factor = get_bal_factor(self);

	//Perform AVL rotation to keep the tree balance//
	return perform_avl_rotate(self, bal_factor);
}

/*
*Remove or Delete a data field from the AVL
*
*@param self // the whole AVL tree
*@param data // the given data value
*/
void delete_avl(AVL *self, long int data)
{
	self->root = delete_avl_node(self->root, data);
}

/*
*Print all data field of AVL tree using in order traversal
*
*@param self //the AVL root
*/
void print_in_order_avl(AVLNodePtr self)
{
	if (self != NULL)
	{
		print_in_order_avl(self->left);
		printf("%lu\n", self->data);
		print_in_order_avl(self->right);
	}
}

/*
*Search the data field in the each node of AVL tree
*Check whether the data value given is matched with the data field
*
*@param self // the AVL tree root
*@param data // the given data value
*@return AVLNodePtr // the found node
*/
AVLNodePtr search_avl_node(AVLNodePtr self, long int data)
{
	if (self == NULL || self->data == data)
		return self;

	else if (self->data < data)
		return search_avl_node(self->right, data);

	return search_avl_node(self->left, data);
}

/*
*Search the given data value in the AVL tree
*
*@param  self // the whole AVL tree
*@param id // the given data value
*@return AVLNodePtr // the found node
*/
AVLNodePtr search_avl(AVL *self, long int data)
{
	return search_avl_node(self->root, data);
}

/*
*To free dynamically allocated memory for all nodes of the given AVL tree root 
*using Depth First Search approach 
*
*@param self //root of given AVL tree root
*/
void free_avl(AVLNodePtr self) 
{
	if (self != NULL) 
	{
		if (self->left)
			free_avl(self->left);

		if (self->right)
			free_avl(self->right);
		
		free(self);
	}
}


