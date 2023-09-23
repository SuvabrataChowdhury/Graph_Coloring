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

void findRewards(int rewards[],int fitnesses[],int length){
	int maxFitness=fitnesses[0];
	
	for(int i=1;i<length;i++){
		if(fitnesses[i]>maxFitness)
			maxFitness=fitnesses[i];
	}
	
	//printf("%d\n",maxFitness);
	
	for(int i=0;i<length;i++){
		rewards[i]=maxFitness-fitnesses[i];
	}
	
	return ;
}

