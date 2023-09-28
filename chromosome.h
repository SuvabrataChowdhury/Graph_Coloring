#ifndef __CHROMOSOME__
	#define __CHROMOSOME__
	//Structure for each chromosome
	typedef struct Chromosome{
		int seqLength;	//Length of the sequence
		int *sequence;	//An array of length seqLength. Defines a coloration of the graph
		int numConflicts;	//number of conflicting edges for the given coloring
		int fitness;	//fitness based on the number of conflicting edges
	}Chromosome;
	
	//Initiates each chromosomes in the given array
	void getRandomChromosomes(Chromosome chromosomes[],int numChromosomes,int numVertices,int highestColor){
		for(int i=0;i<numChromosomes;i++){
			chromosomes[i].seqLength=numVertices;
			chromosomes[i].sequence=(int *)calloc(numVertices,sizeof(int));

			for(int j=0;j<numVertices;j++){
				chromosomes[i].sequence[j]=rand()%highestColor+1;
			}
		}
	}

	void displayChromosomes(Chromosome chromosomes[],int numChromosomes){
		printf("Chromosome\tConflicts\tFitness\n");
		for(int i=0;i<numChromosomes;i++){
			for(int j=0;j<chromosomes[i].seqLength;j++){
				printf("%d ",chromosomes[i].sequence[j]);
			}

			printf("\t%d\t%d\n",chromosomes[i].numConflicts,chromosomes[i].fitness);
		}
	}
#endif
