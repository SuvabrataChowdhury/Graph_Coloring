#ifndef __FITNESS__
	#define __FITNESS__
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
#endif
