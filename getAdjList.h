#ifndef __ADJDEF__
	#define __ADJDEF__
	
	typedef struct Node{
		int value;
		struct Node *next;
	}Node;
	
	void addNode(int value,Node **head);
	void displayGraph(Node *adj[],int adjLength);
	void buildGraph(FILE *file,Node *adj[],int *knownChromaticNum,int *numVertices,int *numEdges);
#endif
