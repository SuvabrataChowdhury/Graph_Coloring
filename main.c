#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>
#include"getAdjList.h"
#include"chromosome.h"
#include"fitness.h"

#define NUM_CHROMOSOMES 100
#define CROSS_PROBABILITY 0.7
#define MUTATE_PROBABILITY 0.03
#define NUM_GENERATIONS 1000

void displayHavingConflict(Chromosome chromosomes[],int numChromosomes,int targetConflict){
	for(int i=0;i<numChromosomes;i++){
		if(chromosomes[i].numConflicts==targetConflict){
			for(int j=0;j<chromosomes[i].seqLength;j++){
				printf("%d ",chromosomes[i].sequence[j]);
			}

			printf("\n");
		}
	}
}

void copyChromosome(Chromosome *srcChromosome,Chromosome *destChromosome){
	destChromosome->numConflicts=srcChromosome->numConflicts;
	destChromosome->fitness=srcChromosome->fitness;

	destChromosome->seqLength=srcChromosome->seqLength;
	
	destChromosome->sequence=(int *)calloc(destChromosome->seqLength,sizeof(int));
	for(int i=0;i<srcChromosome->seqLength;i++){
		destChromosome->sequence[i]=srcChromosome->sequence[i];
	}
	
	return ;
}

/*
	Driver Code:
		Give input from the command line. 
		After the object file name write the graph's name with extension.

		Example:
			Compile: gcc -o opt selection.c findFitness.c getAdjList.c -lm
			Run: ./opt myciel3.col
*/

//Dummy driver code
int main(int argc,char *argv[]){
	srand((unsigned)time(NULL));

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
	//displayGraph(adj,adjLength,knownChromaticNum,numVertices,numEdges);

	Chromosome chromosomes[NUM_CHROMOSOMES];

	getRandomChromosomes(chromosomes,NUM_CHROMOSOMES,numVertices,knownChromaticNum);
	
	findConflictsAndFitnesses(adj,numVertices,chromosomes,NUM_CHROMOSOMES);
	
	//displayChromosomes(chromosomes,NUM_CHROMOSOMES);
	
	int maxConflict,minConflict;
	double sumConflict;
	Chromosome matingPool[NUM_CHROMOSOMES];
	
	//displayChromosomes(chromosomes,NUM_CHROMOSOMES);
	printf("Generation,Min Conflict,Max Conflict,Avg Conflict\n");
	for(int i=1;i<=NUM_GENERATIONS;i++){
		maxConflict=chromosomes[0].numConflicts;
		minConflict=chromosomes[0].numConflicts;
		sumConflict=0.0;

		for(int j=0;j<NUM_CHROMOSOMES;j++){
			if(chromosomes[j].numConflicts<minConflict)
				minConflict=chromosomes[j].numConflicts;
			
			if(chromosomes[j].numConflicts>maxConflict)
				maxConflict=chromosomes[j].numConflicts;

			sumConflict+=chromosomes[j].numConflicts;
		}

		printf("%d,%d,%d,%lf\n",i,minConflict,maxConflict,sumConflict/NUM_CHROMOSOMES);

		selectChromosomes(chromosomes,matingPool,NUM_CHROMOSOMES);
		
		crossChromosomes(matingPool,NUM_CHROMOSOMES,CROSS_PROBABILITY);
		
		mutateChromosomes(matingPool,NUM_CHROMOSOMES,MUTATE_PROBABILITY);

		findConflictsAndFitnesses(adj,numVertices,matingPool,NUM_CHROMOSOMES);

		//displayChromosomes(matingPool,NUM_CHROMOSOMES);

		for(int j=0;j<NUM_CHROMOSOMES;j++){
			copyChromosome(&matingPool[j],&chromosomes[j]);
		}

		//displayChromosomes(chromosomes,NUM_CHROMOSOMES);
	}
	return 0;
}
