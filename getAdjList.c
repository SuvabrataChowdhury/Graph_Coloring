/*
	Adjacency list representation of a graph is just a list of lists following the convention,
		adj[i]:= A list containing all vertex i's neighbours.
	As in C there exists no lists i.e. dynamic arrays, we need to define an array of linked lists to accomplish this task.
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"getAdjList.h"
/*
	addNode(int value,Node **head):
		Input: The insert value and the head pointer of the linked list
		Output: Inserts the given value if it was not inserted previously
*/
/*
	Note: addNode must be called with the reference to the head pointer, otherwise the changes will not be reflected
*/
void addNode(int value,Node **head){
	Node *nNode=(Node *)malloc(sizeof(Node *));	//Allocate memory for the new Node
	nNode->value=value;	//Add the value
	nNode->next=NULL;	//Set the next field to null as this node will be inserted at the very end
	
	if(*head==NULL){	//If linked list is empty then
		*head=nNode;	//Simply make the head point to the new node
	}
	else{
		Node *cNode=*head;	//Set cNode as the head for traversal
		
		//Traverse the linked list
		while(cNode->next!=NULL){
			//If the value is already included no need to include it again
			if(cNode->value==value){
				free(nNode);	//free the memory taken by nNode
				return ;
			}
			
			cNode=cNode->next;	//goto the next node
		}
		
		//After exiting the loop it is guranteed that the cNode points to the very last node of the linked list
		if(cNode->value!=value)	//if value is not present in the last node
			cNode->next=nNode;	//Include the last node
		//If value is present no need to do anything..
	}

	return ;
}

/*
	display(Node *adj[],int adjLength):
		Input: The adjacency list and the list's length i.e. the number of vertices.
		Output: Display of all the neighbours of the nodes.
*/
/*
	Note: Start the traversal of array adj[] from index 1 as vertex 0 does not exists in any of the GCP_DATASET graphs.
	Non existing vertices does not have any neighbour hence, their pointer value is set to NULL.
*/
void displayGraph(Node *adj[],int adjLength){
	Node *ptr=NULL;
	
	printf("Displaying the graph\n");
	for(int i=1;i<adjLength;i++){
		ptr=adj[i];	//Fetch the linked list head pointer of the ith node
		
		printf("Neighburs of %d are:\n",i);
		
		while(ptr!=NULL){	//Perform a normal linked list traversal
			printf("%d ",ptr->value);
			ptr=ptr->next;
		}
		
		printf("\n");
	}
	
	return ;
}

/*
	Driver Code:
		Input: To be given from the command line. 
		After the object file name write the graph's name with extension.
		Example:
			Compile: gcc getAdjList.c
			Run: ./a.out myciel3.col
		or,
			Compile: gcc -o opt getAdjList.c
			Run: ./opt myciel3.col

		Output: displayGraph's output after construction of the adjacency list of the given graph
*//*
int main(int argc,char *argv[]){
	if(argc<2){	//If argument count is less than 2 then
		printf("Please Provide the file name\n");

		exit(1);
	}
	
	//If the git repo is correctly cloned the graphs must be within the same directory.
	char filePath[100]="GCP_DATASET/";
	strcat(filePath,argv[1]);	//Hence the relative file is "GCP_DATASET/"+argv[1]
	
	FILE *file;
	file=fopen(filePath,"r");	//Open the file in read mode
	
	if(file==NULL){
		printf("Can not open file\n");

		exit(1);
	}
	
	//File has successfully been opened

	//Adjacency list construction begins..
	int knownChromaticNum,numVertices,numEdges;

	//The first line contains 3 quantities which are, known chromatic number, number of vertices and number of edges
	fscanf(file,"%d %d %d",&knownChromaticNum,&numVertices,&numEdges);	
	
	printf("Expected: %d\n",knownChromaticNum);
	printf("Number of vertices: %d\n",numVertices);
	printf("Number of edges: %d\n",numEdges);
	
	int v1,v2,index=0;
	
	Node *adj[1000]={NULL};
	int adjLength=numVertices+1;
	
	//Next line onwords the edge matrix is given
	while((fscanf(file,"%*s %d %d",&v1,&v2))==2){
		//As it is an undirected graph the existance of edge (vi,vj) => edge(vj,vi) also exists.
		addNode(v2,&adj[v1]);
		addNode(v1,&adj[v2]);
	}
	//Adjacency list construction is complete

	displayGraph(adj,adjLength);
	
	fclose(file);

	return 0;
}*/
