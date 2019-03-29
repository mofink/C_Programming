#include <stdio.h>
#include<stdlib.h>

struct Node  
{
	int val;
	struct Node* next;
};

typedef struct Node Node; //typedefing directly caused some issues because of recursive struct. have to look more into it

typedef struct 
{
	Node* head;
	int len;
} LinkedList;


void print_list(LinkedList*);
int get(LinkedList*, int index); //get value at index, -1 if doesn't exist
void add(LinkedList*, int val); //add val to front of list
void remove_node(LinkedList*, int index); //remove node at index, print message if node doesn't exist
void append(LinkedList*, int val); //append val to the end of list

int main(void)
{
	LinkedList* mylist = malloc(sizeof(LinkedList));
	mylist->head = NULL;
	mylist->len = 0;
	
	add(mylist,4);
	add(mylist,6);
	add(mylist,3);
	append(mylist,10);
	printf("%d\n",get(mylist,2));
	print_list(mylist);
	remove_node(mylist,0);
	print_list(mylist);

	return 0;
}

void print_list(LinkedList* mylist)
{
	Node* head = mylist->head;
	while (head)
	{
		printf("%d ", head->val);
		head = head->next;
	}
	printf("\n");
}

int get(LinkedList *mylist, int index)
{
	if (mylist->len < index)
	{
		return -1;
	}
	else
	{
		int i;
		Node* some_node = mylist->head; 
		for (i = 0; i < index; ++i)
		{
			some_node = some_node->next;
		}
		return some_node->val;
	}
}

void add(LinkedList *mylist, int val)
{
	Node* temp_node = (Node *) malloc(sizeof(Node));
	temp_node->val = val;
	temp_node->next = mylist->head;
	mylist->head = temp_node;

	mylist->len += 1;

}

void append(LinkedList *mylist, int val)
{
	Node* some_node = mylist->head;
	while (some_node != NULL && some_node->next != NULL)
	{
		some_node = some_node->next;
	}
	if (some_node == NULL)
	{
		add(mylist, val);
	}
	else
	{
		Node* new_node = (Node *) malloc(sizeof(Node));
		new_node->val = val;
		new_node->next = NULL;
		some_node->next = new_node;
	}
	mylist->len += 1;
}

void remove_node(LinkedList *mylist, int index)
{
	if (mylist->len < index)
	{
		printf("NO NODE AT INDEX %d\n",index);
	}
	else
	{
		int i;
		Node** pp = &mylist->head;
		Node* some_node = mylist->head;

		for (i = 0; i < index; ++i)
		{
			*pp = some_node;
			some_node = some_node->next;
		}
		printf("PING %d\n",some_node->val);
		(*pp)->next = some_node->next->next;

		free(some_node);
		mylist->len -= 1;
	}
}
