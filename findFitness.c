/*
	findFitness():
		Input: A graph G [stored as adjacency list] and a chromosome [chromosome[i]=> the color of ith vertex].
		Output: A fitness score depending on the coloring of each vertices.
	[Note: A lower fitness score is better]
*/
/*
	Algorithm findFitness(G,color){
		fitness:=0;

		toBeChecked.add(1);

		while !isEmpty(toBeChecked) do{
			currentVertex:=toBeChecked.removed();

			if !checked[currentVertex] then{
				for vertex in G[currentVertex] do{
					if !checked[vertex] && color[vertex] == color[currentVertex] then{
						fitness++;
					}

					toBeChecked.add(vertex);
				}

				checked[currentVertex]:=true;
			}
		}

		return fitness;
	}
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>
#include"getAdjList.h"

#define NUM_CHROMOSOMES 50

Node *frontQ=NULL;
Node *rearQ=NULL;

bool isEmptyQ(){
	return (frontQ == NULL);
}

void displayQ(){
	Node *temp=frontQ;

	while(temp!=NULL){
		printf("%d ",temp->value);
		temp=temp->next;
	}

	printf("\n");
}

void addQ(int value){
	Node *temp = (Node *)calloc(1,sizeof(Node *));
	
	temp->value = value;
	temp->next = NULL;

	if(frontQ == NULL){
		frontQ = temp;
		rearQ = temp;
	}
	else{
		rearQ->next = temp;
		rearQ = temp;
	}

	return;
}

int removeQ(){
	int value = frontQ->value;

	if(frontQ==rearQ){
		rearQ=NULL;
	}

	frontQ = frontQ->next;

	return value;
}

int findFitness(Node *graph[],int numVertices,int color[]){
	int currentVertex;
	int fitness = 0;	//It is assumed that the graph is colored correctly at the beginning
	
	bool *checked=(bool *)calloc(numVertices+1,sizeof(bool));

	Node *neighbour = NULL;

	addQ(1);

	while(!isEmptyQ()){	//While there exists vertices to be checked do
		currentVertex = removeQ();	//set the current vertex as the first vertex in the queue

		if(!checked[currentVertex]){	//If the currentVertex has not been checked then
			neighbour = graph[currentVertex];
			
			while(neighbour != NULL){	//Check all the neighbours of the current vertex for conflicts
				if(!checked[neighbour->value] && color[neighbour->value] == color[currentVertex]) // Conflict has occurred
					fitness++;
				
				addQ(neighbour->value);
				
				neighbour = neighbour->next;
			}

			checked[currentVertex] = true;
		}
	}

	return fitness;
}

void findFitnesses(Node *graph[],int numVertices,int chromosomes[][numVertices],int numChromosomes,int fitnesses[]){
	for(int i=0;i<numChromosomes;i++){
		fitnesses[i] = findFitness(graph,numVertices,chromosomes[i]);
	}

	return ;
}

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

	int chromosomes[NUM_CHROMOSOMES][numVertices];

	srand(time(0));
	for(int i=0;i<NUM_CHROMOSOMES;i++){
		for(int j=0;j<numVertices;j++){
			chromosomes[i][j]=rand()%knownChromaticNum+1;
		}
	}
	
	int fitnesses[NUM_CHROMOSOMES];
	
	findFitnesses(adj,numVertices,chromosomes,NUM_CHROMOSOMES,fitnesses);
	
	for(int i=0;i<NUM_CHROMOSOMES;i++){
		printf("The fitness of %dth chromosomes is: %d\n",i,fitnesses[i]);
	}

	return 0;
}
