#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<string.h>
#include"getAdjList.h"
#include"chromosome.h"
#include"fitness.h"

#define NUM_CHROMOSOMES 50
#define CROSS_PROBABILITY 0.7
#define MUTATE_PROBABILITY 0.03

void swap(int *num1,int *num2){
	int t=*num1;
	*num1=*num2;
	*num2=t;

	return ;
}

void mutate(Chromosome chromosome,int numGenes){
	int rand1=0,rand2=0;
	
	while(rand1==rand2){
		rand1=rand()%numGenes;
		rand2=rand()%numGenes;
	}
	
	swap(&chromosome.sequence[rand1],&chromosome.sequence[rand2]);
	
	return ;
}

void mutateChromosomes(Chromosome chromosomes[],int numChromosomes,double probability){
	int chromosome;
	int numMutation=0;

	for(int i=0;i<numChromosomes;i++){
		double random=1.0*rand()/RAND_MAX;
		
		//printf("Rand number: %lf\n",random);
		chromosome=0;

		if(random<=probability){
			chromosome=rand()%numChromosomes;

			mutate(chromosomes[chromosome],chromosomes[chromosome].seqLength);
			numMutation++;

			//printf("Crossover between %d and %d\n",chromosome1,chromosome2);
		}
	}

	printf("Mutation happened %d times\n",numMutation);

	return ;
}

void crossover(Chromosome chromosome1,Chromosome chromosome2,int numGenes){
	int point1=0;
	int point2=0;

	while(point1>=point2){
		point1=rand()%numGenes;
		point2=rand()%numGenes;
	}
	
	for(int i=point1;i<=point2;i++){
		swap(&chromosome1.sequence[i],&chromosome2.sequence[i]);
	}
	
	return ;
}

void crossChromosomes(Chromosome chromosomes[],int numChromosomes,double probability){
	int index1,index2;
	int numCrossover=0;

	for(int i=0;i<numChromosomes/2;i++){
		double random=1.0*rand()/RAND_MAX;
		
		//printf("Rand number: %lf\n",random);
		
		index1=0;
		index2=0;

		if(random<=probability){
			while(index1==index2){
				index1=rand()%numChromosomes;
				index2=rand()%numChromosomes;
			}

			crossover(chromosomes[index1],chromosomes[index2],chromosomes[index1].seqLength);
			numCrossover++;

			//printf("Crossover between %d and %d\n",index1,index2);
		}
	}

	printf("Crossover happened %d times\n",numCrossover);

	return ;
}

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

void selectChromosomes(Chromosome chromosomes[],Chromosome matingPool[],int numChromosomes){
	int sumFitnesses=0;
	
	for(int i=0;i<numChromosomes;i++){
		sumFitnesses+=chromosomes[i].fitness;
	}

	int randSum,chromosome,sum;
	int index=0;

	for(int i=0;i<numChromosomes;i++){
		randSum=rand()%(sumFitnesses+1);
		
		chromosome=0;
		sum=0;
		
		while(chromosome<numChromosomes && sum<=randSum){
			sum+=chromosomes[chromosome].fitness;
			chromosome++;
		}
		
		//Copy the selected chromosome into the mating pool
		--chromosome;
		matingPool[index].seqLength=chromosomes[chromosome].seqLength;

		matingPool[index].sequence=calloc(matingPool[index].seqLength,sizeof(int));
		for(int j=0;j<chromosomes[chromosome].seqLength;j++){
			matingPool[index].sequence[j]=chromosomes[chromosome].sequence[j];
		}

		matingPool[index].numConflicts=chromosomes[chromosome].numConflicts;
		matingPool[index].fitness=chromosomes[chromosome].fitness;
		index++;
	}
	
	return ;
}

void display(int arr[],int length){
	for(int i=0;i<length;i++)
		printf("%d ",arr[i]);
	printf("\n");
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
	
	Chromosome matingPool[NUM_CHROMOSOMES];
	
	selectChromosomes(chromosomes,matingPool,NUM_CHROMOSOMES);
	printf("\n");
	
	//qsort(selectedChromosomes,NUM_CHROMOSOMES,sizeof(int),cmpFunc);
	printf("The selected chromosomes are: \n");
	
	displayChromosomes(matingPool,NUM_CHROMOSOMES);

	crossChromosomes(matingPool,NUM_CHROMOSOMES,CROSS_PROBABILITY);
	
	mutateChromosomes(matingPool,NUM_CHROMOSOMES,MUTATE_PROBABILITY);

	findConflictsAndFitnesses(adj,numVertices,matingPool,NUM_CHROMOSOMES);

	displayChromosomes(matingPool,NUM_CHROMOSOMES);

/*	findFitnesses(adj,numVertices,matingPool,NUM_CHROMOSOMES,fitnesses);
	findRewards(rewards,fitnesses,NUM_CHROMOSOMES);	
	
	int minIndex=0;
	int maxIndex=0;
	
	for(int i=1;i<NUM_CHROMOSOMES;i++){
		if(fitnesses[i]>fitnesses[maxIndex])
			maxIndex=i;
		
		if(fitnesses[i]<fitnesses[minIndex])
			minIndex=i;
	}
	
	printf("Min fitness: %d Max fitness:%d\n",fitnesses[minIndex],fitnesses[maxIndex]);
	printf("Fittest Chromosome:\n");
	display(chromosomes[minIndex],numVertices);
	printf("Worst Chromosome:\n");
	display(chromosomes[maxIndex],numVertices);
*/
	return 0;
}
