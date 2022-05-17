/*
*main.c
*Harness File for KIT205 Assignment 1 : Data Structures
*This program is designed to present the subscriptions between loyaty programs and customer IDs
*
*@author: Ann Sung Phang (481605)
*@version: April 2019
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"
#include "bst.h"

// Available options for the user to command //
#define CMD_QUIT 0
#define CMD_SUBSCRIBE 1
#define CMD_UNSUBSCRIBE 2
#define CMD_PRINT_SUMMARY 3
#define CMD_PRINT_SUBSRIBERS 4
#define CMD_PRINT_SUBSRIPTIONS 5

/**
*subscribe()
*Get user's customer id and loyalty program name
*Add those information given by user into database, if they cannot be found in the database
*Customer and program then get added into subcription
*
*@param db //database for storing subscriptions (program name and each of customer ID)
*@param id //customer id
*@param program //loyalty program name
*/
void subscribe(List *db, long int id, char *program)
{
	ListNodePtr current;
	//printf("\nPlease enter your customer id: ");
	scanf_s("%lu", &id);

	//printf("\nPlease enter a loyalty program name: ");
	scanf_s("%s", program, 101);

	current = search_list_node(db->head, program);//search whether program exists in database

	if (current != NULL)
		insert_avl(&current->avl, id);

	else
	{
		AVL avl = new_avl();
		insert_avl(&avl, id);
		insert_at_front(db, &avl, program);
	}
}

/**
*unsubscribe()
*Get user's customer id and loyalty program name
*Remove his/her subscription, and keep the id and loyalty program from the database
*
*@param db //database that is storing subscriptions (program name and each of customer ID)
*@param id //customer id
*@param program //loyalty program name
*/
void unsubscribe(List *db, long int id, char *program)
{
	ListNodePtr current; 

	//printf("\nPlease enter your customer id: ");
	scanf_s("%lu", &id);

	//printf("\nPlease enter a loyalty program name: ");
	scanf_s("%s", program, 101);

	current = search_list_node(db->head, program); // search whether program exits in database

	if (current)
		delete_avl(&current->avl, id); // delete cusrtomer id 
}

/**
*print_summary()
*Display each loyalty program
*For each display, program name followed by sum of subscribed customers
*
*@param db //database that is storing subscriptions (program name and each of customer ID)
*/
void print_summary(List *db)
{
	//printf("Summary: \n");
	print_list_avl_node(db->head);
	
	printf("\n");
}

/*
*print_subscribers()
*Get user's loyalty program name
*Display an ordered list of customer id(s) for all subscribers to the given program name
*
*@param db //database that is storing subscriptions (program name and each of customer ID)
*@param prorgam //loyalty program name
*/
void print_subsribers(List *db, char *program)
{
	ListNodePtr current;

	//printf("\nPlease enter a loyalty program name: ");
	scanf_s("%s", program, 101);
	printf("\n");

	current = search_list_node(db->head, program);//search and get for the given program name

	if (current != NULL)
	{
		//printf("\n\nSubscribers to %s:\n", program);
		print_in_order_avl(current->avl.root);
	}
	else
		printf("\nNo program named:  %s", program);

	printf("\n");
}

/*
*print_subscriptions()
*Get user's customer id
*Print all the loyalty program of this customer is subscribed to
*
*@param db //database that is storing subscriptions (program name and each of customer ID)
*@param id //customer id
*/
void subscriptions(List *db, long int id)
{
	//printf("Please enter your customer id: ");
	scanf_s("%lu", &id);
	printf("\n");

	match_print_list_node(db->head, id);
}

/**
*quit()
*Free all dynamically allocated memory
*Quit the program
*
*param db //the database that is storing subscriptions (program name and each of customer ID)
*/
void quit(List *db)
{
	printf("\n");

	free_avl(db->head->avl.root); // free dynamically allocated memory of all customer ids
	free_list(db->head); //free dynamically allocated memory of all programs

	getch();
	exit(1);
}

int main(int argc, const char *argv[])
{
	int command; //user conmmand to the program
	long int id = 0;  //user input for customer id
	List database = new_list(); // database for storing subscriptions (program name and each of customer ID)
	char program[101]; //user input for loyalty program name, 101 characters include '/0' character

	do
	{
	    //printf("\nAvailable Commands: \n\n%d \t\t Subcribe\n%d \t\t Unsubscribe\n%d \t\t Print Summary\n%d \t\t Print Subscribers\n%d \t\t Print Subscriptions\n%d \t\t Quit\n",
			//CMD_SUBSCRIBE, CMD_UNSUBSCRIBE, CMD_PRINT_SUMMARY, CMD_PRINT_SUBSRIBERS, CMD_PRINT_SUBSRIPTIONS, CMD_QUIT);

		//printf("\nPlease enter a command (0 - 5): ");
		scanf_s("%d", &command);
		
		switch (command)
		{
			case CMD_SUBSCRIBE:
				subscribe(&database, id, program);
				break;

			case CMD_UNSUBSCRIBE:
				unsubscribe(&database, id, program);
				break;

			case CMD_PRINT_SUMMARY:
				print_summary(&database);
				break;

			case  CMD_PRINT_SUBSRIBERS:
				print_subsribers(&database, program);
				break;

			case CMD_PRINT_SUBSRIPTIONS:
				subscriptions(&database, id);
				break;

			case CMD_QUIT:
				quit(&database);
				break;
	}
	} while (command != CMD_QUIT);

	return 0;
}