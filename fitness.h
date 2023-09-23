#ifndef __FITNESS__
	#define __FITNESS__

	void findFitnesses(Node *graph[],int numVertices,int chromosomes[][numVertices],int numChromosomes,int fitnesses[]);
	void findRewards(int rewards[],int fitnesses[],int length);
#endif
