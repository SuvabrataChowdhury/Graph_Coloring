#ifndef __ADJDEF__
	#define __ADJDEF__
	
	//Normal node structure of a singly linked list
	typedef struct Node{
		int value;
		struct Node *next;
	}Node;

	void addNode(int value,Node **head);
	void displayGraph(Node *adj[],int adjLength);
#endif
