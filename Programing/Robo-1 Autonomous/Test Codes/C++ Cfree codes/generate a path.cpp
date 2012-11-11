/*! @define   NO_OF_GRID_ROWS    Number of rows that grid has */
#define NO_OF_GRID_ROWS 5 //7
/*! @define   NO_OF_GRID_COLUMNS    Number of columns that grid has */
#define NO_OF_GRID_COLUMNS 5 //7

#include <stdio.h>

typedef struct _node{
	int x;
	int y;
}node;


typedef struct _path{
	int length;
	node* nodes;
}path,shortestPath;

node nodes[5];

node createNode(int x, int y);
void showPath(path aPath);

void getDryRunPath(path* dryRunPath){
	int counter1=1;
	int counter3=0;

	dryRunPath->length = (NO_OF_GRID_ROWS-1)*(NO_OF_GRID_COLUMNS-1);

	for(int counter0=1; counter0<NO_OF_GRID_ROWS; counter0++){
		//dryRunPath->nodes[counter3] = createNode(1, 1);
		
		if(counter0%2==1){
			for(; counter1<NO_OF_GRID_COLUMNS; counter1++){

				dryRunPath->nodes[counter3] = createNode(counter0, counter1);
				counter3++;
			}
			counter1 = NO_OF_GRID_COLUMNS-1;
		}
		else{
			for(; counter1>0; counter1--){

				dryRunPath->nodes[counter3] = createNode(counter0, counter1);
				counter3++;
			}
			counter1 = 1;
		}
	}
}

void asd(path* aPath){
	
	int counter1=0;
		for(; counter1<NO_OF_GRID_COLUMNS; counter1++)
			aPath->nodes[counter1] = createNode(counter1+15, counter1+15);

		aPath->length = 5;
		//showPath(*aPath);
}

int main(){
	node nodes[5];
	path aPath;
	int counter1=0;
		for(; counter1<NO_OF_GRID_COLUMNS; counter1++)
			nodes[counter1] = createNode(counter1+15, counter1+15);

		aPath.nodes = nodes;
		aPath.length = 5;

	path newPath;
	node newnodes[100];
	newPath.nodes = newnodes;
	getDryRunPath(&newPath);
	
	showPath(newPath);
}




void showPath(path aPath){
	printf("\n");
	for(int counter0=0; counter0<aPath.length; counter0++){
		
		printf(" (");
		printf("%d",aPath.nodes[counter0].x);
		printf(",");
		printf("%d",aPath.nodes[counter0].y);
		printf(") ");

		printf("-> ");
	}
	
	printf("lenth=%d ",aPath.length);
}

node createNode(int x, int y){
	node aNode = {x,y};
	return aNode;
}
