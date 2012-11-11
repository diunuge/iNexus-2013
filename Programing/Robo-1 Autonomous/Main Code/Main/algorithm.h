#ifndef diuAlgorithm
#define diuAlgorithm

#include "configuration.h"
#include "dataTypes.h"
#include "motion.h"


/************************** function prototypes ************************/

void createDryRunPath(path* dryRunPath);
void showPath(path* aPath);
node createNode(int x, int y);
void aStar();
void findPathDijkstra(node startingNode, node endNode, shortestPath* path);
void findPathCustom();


/************************** function definitions ************************/

/*!
 * @function    getDryRunPath
 * @abstract    Create dry run path
 * @discussion  This function take a path pointer variable which has assigned node array.
 *              this will create a node list and assign it to path->nodes and set path->length.
 * @param       dryRunPath    A pointer to a path struct variable which will be cunstruct in the function
 * @result      Construct the path variable. returns nothing.
*/
void createDryRunPath(path* dryRunPath){
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

/*!
 * @function    getDryRunPath
 * @abstract    Create dry run path
 * @discussion  This function take a path pointer variable which indicate real path in the grid.
 *              this will transmit via RS232 to computer with apropriate format.
 * @param       aPath    A pointer to a path struct variable which will be transmit in the function
 * @result      Transmit the path variable. returns nothing.
*/
void showPath(path* aPath){
	Serial.println("");
	for(int counter0=0; counter0<aPath->length; counter0++){
		
		Serial.print(" (");
		Serial.print(aPath->nodes[counter0].x);
		Serial.print(",");
		Serial.print(aPath->nodes[counter0].y);
		Serial.print(") ");

		Serial.print("-> ");
	}
}


/*!
 * @function    createNode
 * @abstract    Create node
 * @discussion  This creates node variable using coordinates.
 * @param       x    x coordinate
 * @param       y    y coordinate
 * @result      returns a cunstructed node.
*/
node createNode(int x, int y){
	node aNode = {x,y};
	return aNode;
}


void findPathDijkstra(node startingNode, node endNode, shortestPath* path){
	
}



#endif