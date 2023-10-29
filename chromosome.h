#ifndef __CHROMOSOME__
	#define __CHROMOSOME__
	//Structure for each chromosome
	typedef struct Chromosome{
		int seqLength;	//Length of the sequence
		int *sequence;	//An array of length seqLength. Defines a coloration of the graph
		int numConflicts;	//number of conflicting edges for the given coloring
		double fitness;	//fitness based on the number of conflicting edges
	}Chromosome;
	
	void swap(int *num1,int *num2){
		int t=*num1;
		*num1=*num2;
		*num2=t;

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

			printf("\t%d\t%lf\n",chromosomes[i].numConflicts,chromosomes[i].fitness);
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

	void selection(Chromosome chromosomes[],Chromosome matingPool[],int numChromosomes,double eliProbability,double toleranceFitness){
		//index is the insertion location at the matingPool and i is index of chromosomes
		int index=0,i=0;
		double r=0.0;	//r is a random variable
		
		//while we have not filled the mating pool do,
		while(index!=numChromosomes){
			//if the ith chromosomes fitness is less than the tolerance fitness, it may get eliminated
			//based on the elimination probability
			if(chromosomes[i].fitness<toleranceFitness){
				r=1.0*rand()/RAND_MAX;
				
				//If randomly generated value is less than the selection probability,
				//i.e. 1-P(Elimination), then select the chromosome.
				if(r<(1-eliProbability)){
					copyChromosome(&chromosomes[i],&matingPool[index]);
					index++;
				}
			}
			else{
					copyChromosome(&chromosomes[i],&matingPool[index]);
					index++;
			}
			
			//After every cycle through the chromosome pool lower the dificulty level
			//so that the unfilled positions in the mating pool gets filled
			if((i+1)==numChromosomes)
				eliProbability/=2;

			i=(i+1)%numChromosomes;
		}
	}

	/*
		selectChromosomes():
			Input: The fitnesses of chromosomes and the number of chromosomes
			Output: A selection/ mating pool of chromosomes based on their fitness values
		[Selection is done using Roulette Wheel method]
	*/
	/*
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
		
	void eliminateChromosomes(Chromosome matingPool[],Chromosome fittestChromosome,int numChromosomes,int toleranceConflict,double replaceProbability){
		
		for(int i=0;i<numChromosomes;i++){
			if(matingPool[i].numConflicts>toleranceConflict){
				if((1.0*rand()/RAND_MAX)<replaceProbability){
					copyChromosome(&fittestChromosome,&matingPool[i]);
				}
			}
		}
	}
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

		//printf("Crossover happened %d times\n",numCrossover);

		return ;
	}
		
	void mutate(Chromosome chromosome,int numGenes){
		int rand1=0,rand2=0;
		
		while(chromosome.sequence[rand1]==chromosome.sequence[rand2]){
			rand1=rand()%numGenes;
			rand2=rand()%numGenes;
		}
		
		swap(&chromosome.sequence[rand1],&chromosome.sequence[rand2]);
		
		return ;
	}

	void mutate1(Chromosome chromosome,int numGenes,int chromaticNum){
		int randIndex=rand()%numGenes;
		
		int randGene=chromosome.sequence[randIndex];
		while(randGene==chromosome.sequence[randIndex]){
			randGene=rand()%chromaticNum+1;
		}
		
		chromosome.sequence[randIndex]=randGene;

		return ;
	}

	void mutateChromosomes(Chromosome chromosomes[],int numChromosomes,double probability,int chromaticNum){
		int chromosome;
		int numMutation=0;

		for(int i=0;i<numChromosomes;i++){
			double random=1.0*rand()/RAND_MAX;
			
			chromosome=0;

			if(random<=probability){
				chromosome=rand()%numChromosomes;

				//mutate(chromosomes[chromosome],chromosomes[chromosome].seqLength);
				mutate1(chromosomes[chromosome],chromosomes[chromosome].seqLength,chromaticNum);
				numMutation++;
			}
		}

		//printf("Mutation happened %d times\n",numMutation);

		return ;
	}

#endif
