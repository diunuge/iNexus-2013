#ifndef diuStatus
#define diuStatus


#define RUN_TYPE_UNAVAILABLE 0
#define RUN_TYPE_STARTED 1
#define RUN_TYPE_FINISHED 2

#define NODE_NOT_DEFINED -1
#define NODE_IS_ALLOWED 0
#define NODE_IS_BLOCKED 1

int DRY_RUN_STATE = RUN_TYPE_UNAVAILABLE;
int RUN_STATE = RUN_TYPE_UNAVAILABLE;

/*!
 * @var         currentDirection
 * @abstract    Indicate current bot direction.
 * @discussion  Stores direction of the autonomus robot which used to navigate through grid
*/
int currentDirection;

/*!
 * @var         currentPosition
 * @abstract    Indicate current bot position.
 * @discussion  Stores position of the autonomus robot using node datatype which used to navigate through grid
*/
node currentPosition;

/*!
 * @var         grid
 * @abstract    Status of the grid nodes.
 * @discussion  Stores data about status of the grid nodes.
 *              whether is it blocked or not.
*/
int grid[NO_OF_GRID_ROWS+1][NO_OF_GRID_COLUMNS+1] = {-1};

/************************** function prototypes ************************/

boolean isDryRun();
void updateState(int direction, node newPosition);

/************************** function definitions ************************/

boolean isDryRun(){
	//read external signal: Probably from a switch
	return true;
}

void updateState(int direction, node newPosition){
	currentDirection = direction;
	currentPosition = newPosition;
}

#endif