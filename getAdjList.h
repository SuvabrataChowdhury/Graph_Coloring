#ifndef __ADJDEF__
	#define __ADJDEF__
	
	typedef struct Node{
		int value;
		struct Node *next;
	}Node;
	
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

	void displayGraph(Node *adj[],int adjLength,int knownChromaticNum,int numVertices,int numEdges){
		printf("Known Chromatic number: %d\n",knownChromaticNum);
		printf("Number of Vertices: %d\n",numVertices);
		printf("Number of Edges: %d\n",numEdges);

		Node *ptr=NULL;
		
		printf("Displaying the graph\n");
		for(int i=0;i<adjLength;i++){
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
		buildGraph():
			Input: A file pointer to the file containing the graph
			Output: A adjacency list representation of the input graph
		
		[Note: As more than one quantity is associated with a graph (like chromatic number,number 
		of vertices and number of edges), send the references to the variables knownChromaticNum, numVertices and numEdges
		to buildGraph for storing purposes]
	*/

	void buildGraph(FILE *file,Node *adj[],int *knownChromaticNum,int *numVertices,int *numEdges){
		//The first line contains 3 quantities which are, known chromatic number, number of vertices and number of edges
		fscanf(file,"%d %d %d",knownChromaticNum,numVertices,numEdges);	
		int v1,v2;
		
		//Next line onwords the edge matrix is given
		while((fscanf(file,"%*s %d %d",&v1,&v2))==2){
			//As it is an undirected graph the existance of edge (vi,vj) => edge(vj,vi) also exists.
			addNode(v2-1,&adj[v1-1]);
			addNode(v1-1,&adj[v2-1]);
		}
		//Adjacency list construction is complete
		
		return ;
	}
#endif
