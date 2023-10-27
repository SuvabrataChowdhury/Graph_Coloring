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
#define MUTATE_PROBABILITY 0.06
#define NUM_GENERATIONS 10000

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

	fscanf(file,"%d %d %d",&knownChromaticNum,&numVertices,&numEdges);
	int edges[numEdges][2];
	buildEdgeMatrix(file,edges,&numEdges,numVertices);
	
	//displayEdges(edges,numEdges);

	Chromosome chromosomes[NUM_CHROMOSOMES];

	getRandomChromosomes(chromosomes,NUM_CHROMOSOMES,numVertices,knownChromaticNum);

	findConflictsAndFitnesses(edges,numEdges,chromosomes,NUM_CHROMOSOMES);
	//displayChromosomes(chromosomes,NUM_CHROMOSOMES);

	int maxConflictIndex=0,minConflictIndex=0,minConflict=-1,maxConflict=-1;
	double sumConflict,avgConflict=0.0;

	double toleranceFitness=0.0;
	double eliProbability=0.0;

	Chromosome matingPool[NUM_CHROMOSOMES];
	
	//displayChromosomes(chromosomes,NUM_CHROMOSOMES);
	printf("Generation,Min Conflict,Max Conflict,Avg Conflict\n");
	for(int i=1;i<=NUM_GENERATIONS && (minConflict!=0);i++){
		maxConflictIndex=0;
		minConflictIndex=0;
		sumConflict=0.0;

		for(int j=0;j<NUM_CHROMOSOMES;j++){
			if(chromosomes[j].numConflicts<chromosomes[minConflictIndex].numConflicts)
				minConflictIndex=j;
			
			if(chromosomes[j].numConflicts>chromosomes[maxConflictIndex].numConflicts)
				maxConflictIndex=j;

			sumConflict+=chromosomes[j].numConflicts;
		}
		
		minConflict=chromosomes[minConflictIndex].numConflicts;
		maxConflict=chromosomes[maxConflictIndex].numConflicts;
		avgConflict=sumConflict/NUM_CHROMOSOMES;

		printf("%d,%d,%d,%lf\n",i,minConflict,maxConflict,avgConflict);
		
		//Natural Selection begins
		//Select fittest chromosomes
		selection(chromosomes,matingPool,NUM_CHROMOSOMES,eliProbability,toleranceFitness);
		
		eliProbability=1.0*i/NUM_GENERATIONS;
		toleranceFitness=1.0*i/NUM_GENERATIONS;

		//Perform crossover to create next generations
		crossChromosomes(matingPool,NUM_CHROMOSOMES,CROSS_PROBABILITY);
		
		//Mutate newly born chromosomes to maintain diversity
		mutateChromosomes(matingPool,NUM_CHROMOSOMES,MUTATE_PROBABILITY,knownChromaticNum);
		
		//Update the children's conflicts and fitnesses as crossover and mutation has happened
		findConflictsAndFitnesses(edges,numEdges,matingPool,NUM_CHROMOSOMES);

		//displayChromosomes(matingPool,NUM_CHROMOSOMES);
		
		//Copy each chromosomes back to the original pool to prepare for next generations
		for(int j=0;j<NUM_CHROMOSOMES;j++){
			copyChromosome(&matingPool[j],&chromosomes[j]);
		}

		//displayChromosomes(chromosomes,NUM_CHROMOSOMES);
	}
/*
	for(int i=0;i<numVertices;i++){
		printf("%d ",chromosomes[minConflictIndex].sequence[i]);
	}
	printf("\n");
*/
	return 0;
}
