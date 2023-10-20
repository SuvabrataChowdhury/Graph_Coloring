#ifndef __CHROMOSOME__
	#define __CHROMOSOME__
	//Structure for each chromosome
	typedef struct Chromosome{
		int seqLength;	//Length of the sequence
		int *sequence;	//An array of length seqLength. Defines a coloration of the graph
		int numConflicts;	//number of conflicting edges for the given coloring
		int fitness;	//fitness based on the number of conflicting edges
	}Chromosome;
	
	void swap(int *num1,int *num2){
		int t=*num1;
		*num1=*num2;
		*num2=t;

		return ;
	}

	/*
		copyChromosome():
			Input: The source and destination chromosomes.
			Output: A deep copy of the source chromosome to the destination chromosome
	*/
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

			copyChromosome(&chromosomes[chromosome],&matingPool[index]);
			index++;
		}
		
		return ;
	}
	
	/*
		crossover():
			Input: Two chromosomes and their length i.e., number of genes
			Output: A two point crossover between the given chromosomes to produce two childrens
	*/
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

	/*
		crossChromosomes():
			Input: A list of chromosomes, the length of the list i.e., the number of chromosomes and crossover probability
			Output: Crossover between all the chromosomes based on the chrossover probability
	*/
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

			}
		}

		return ;
	}
	
	/*
		mutate():
			Input: A chromosome, length of that chromosome and the highest order gene
			Output: A single point change in the sequence of the chromosome
	*/
	void mutate(Chromosome chromosome,int numGenes,int highestGene){
		int randIndex=rand()%numGenes;
		
		int randGene=chromosome.sequence[randIndex];
		while(randGene==chromosome.sequence[randIndex]){
			randGene=rand()%highestGene+1;
		}
		
		chromosome.sequence[randIndex]=randGene;

		return ;
	}
	
	/*
		mutateChromosomes():
			Input: A list of chromosomes, length of that list, mutation probability, known chromatic number
			Output: Mutation of the chromosomes based on the mutation probability
	*/
	void mutateChromosomes(Chromosome chromosomes[],int numChromosomes,double probability,int chromaticNum){
		int chromosome;
		int numMutation=0;

		for(int i=0;i<numChromosomes;i++){
			double random=1.0*rand()/RAND_MAX;
			
			chromosome=0;

			if(random<=probability){
				chromosome=rand()%numChromosomes;

				mutate(chromosomes[chromosome],chromosomes[chromosome].seqLength,chromaticNum);
				numMutation++;
			}
		}

		return ;
	}

#endif
