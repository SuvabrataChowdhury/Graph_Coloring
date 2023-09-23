#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>
#include"getAdjList.h"
#include"fitness.h"

#define NUM_CHROMOSOMES 100

//Comparitive function for sorting purpose
int cmpFunc(const void *a,const void *b){
	return ( *(int *)a-*(int *)b);
}

/*
	selectChromosomes():
		Input: The fitnesses of chromosomes and the number of chromosomes
		Output: A selection/ mating pool of chromosomes based on their fitness values
	[Selection is done using Roulette Wheel method]
*/
void selectChromosomes(int fitnesses[],int selectedChromosomes[],int numChromosomes){
	int sumFitnesses=0;
	
	for(int i=0;i<numChromosomes;i++){
		sumFitnesses+=fitnesses[i];
	}
	
	int randSum,chromosome,sum;
	int selectIndex=0;

	for(int i=0;i<numChromosomes;i++){
		randSum=rand()%(sumFitnesses+1);
		
		chromosome=0;
		sum=0;
		
		while(sum<=randSum){
			sum+=fitnesses[chromosome];
			chromosome++;
		}
		
		selectedChromosomes[selectIndex++]=--chromosome;
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
	
	printf("Known Chromatic Number: %d\n",knownChromaticNum);
	printf("Number of Vertices: %d\n",numVertices);
	printf("Number of Edges: %d\n",numEdges);

	adjLength=numVertices;

	displayGraph(adj,adjLength);
	
	fclose(file);

	int chromosomes[NUM_CHROMOSOMES][numVertices];

	srand((unsigned)time(NULL));
	for(int i=0;i<NUM_CHROMOSOMES;i++){
		for(int j=0;j<numVertices;j++){
			chromosomes[i][j]=rand()%knownChromaticNum+1;
		}
	}
	
	int fitnesses[NUM_CHROMOSOMES];
	
	findFitnesses(adj,numVertices,chromosomes,NUM_CHROMOSOMES,fitnesses);
	
	int rewards[NUM_CHROMOSOMES];
	
	findRewards(rewards,fitnesses,NUM_CHROMOSOMES);
	
	printf("ChromosomeNo Fitness Reword\n");
	for(int i=0;i<NUM_CHROMOSOMES;i++){
		printf("%d\t%d\t%d\n",i,fitnesses[i],rewards[i]);
	}
	
	int selectedChromosomes[NUM_CHROMOSOMES];
	
	selectChromosomes(rewards,selectedChromosomes,NUM_CHROMOSOMES);
/*	
	for(int i=0;i<NUM_CHROMOSOMES;i++){
		printf("%d ",selectedChromosomes[i]);
	}
*/	
	printf("\n");
	
	qsort(selectedChromosomes,NUM_CHROMOSOMES,sizeof(int),cmpFunc);
	printf("The selected chromosomes are: \n");
	
	for(int i=0;i<NUM_CHROMOSOMES;i++){
		printf("%d ",selectedChromosomes[i]);
	}
	
	printf("\n");

	return 0;
}
