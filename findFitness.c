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
#include"chromosome.h"

#define NUM_CHROMOSOMES 100

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

int findConflict(Node *graph[],int numVertices,int color[]){
	int currentVertex;
	int conflict = 0;	//It is assumed that the graph is colored correctly at the beginning
	
	bool *checked=(bool *)calloc(numVertices,sizeof(bool));

	Node *neighbour = NULL;

	addQ(0);

	while(!isEmptyQ()){	//While there exists vertices to be checked do
		currentVertex = removeQ();	//set the current vertex as the first vertex in the queue

		if(!checked[currentVertex]){	//If the currentVertex has not been checked then
			neighbour = graph[currentVertex];
			
			while(neighbour != NULL){	//Check all the neighbours of the current vertex for conflicts
				if(!checked[neighbour->value] && color[neighbour->value] == color[currentVertex]) // Conflict has occurred
					conflict++;
				
				addQ(neighbour->value);
				
				neighbour = neighbour->next;
			}

			checked[currentVertex] = true;
		}
	}

	return conflict;
}

void findConflicts(Node *graph[],int numVertices,Chromosome chromosomes[],int numChromosomes){
	for(int i=0;i<numChromosomes;i++){
		chromosomes[i].numConflicts = findConflict(graph,numVertices,chromosomes[i].sequence);
	}

	return ;
}

void findFitnesses(Chromosome chromosomes[],int numChromosomes){
	int maxConflicts=chromosomes[0].numConflicts;
	
	for(int i=1;i<numChromosomes;i++){
		if(chromosomes[i].numConflicts > maxConflicts)
			maxConflicts = chromosomes[i].numConflicts;
	}
	
	//printf("%d\n",maxFitness);
	
	for(int i=0;i<numChromosomes;i++){
		chromosomes[i].fitness = maxConflicts-chromosomes[i].numConflicts;
	}
	
	return ;
}

void findConflictsAndFitnesses(Node *graph[],int numVertices,Chromosome chromosomes[],int numChromosomes){
	findConflicts(graph,numVertices,chromosomes,numChromosomes);
	findFitnesses(chromosomes,numChromosomes);
	
	return ;
}
/*
//Dummy driver code
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

	int knownChromaticNum,numVertices,numEdges;

	Node *adj[1000]={NULL};
	int adjLength;

	buildGraph(file,adj,&knownChromaticNum,&numVertices,&numEdges);
	adjLength=numVertices;
	displayGraph(adj,adjLength,knownChromaticNum,numVertices,numEdges);

	Chromosome chromosomes[NUM_CHROMOSOMES];

	srand((unsigned)time(NULL));
	getRandomChromosomes(chromosomes,NUM_CHROMOSOMES,numVertices,knownChromaticNum);
	
	findConflictsAndFitnesses(adj,numVertices,chromosomes,NUM_CHROMOSOMES);
	
	displayChromosomes(chromosomes,NUM_CHROMOSOMES);

	return 0;
}
*/
