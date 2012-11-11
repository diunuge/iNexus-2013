#ifndef diuDataTypes
#define diuDataTypes


/*!
 * @typedef     node
 *              Represent node of the grid.
 * @field       x     reference x coordinate.
 * @field       y     reference y coordinate.
*/
typedef struct _node{
	int x;
	int y;
}node;


/*!
 * @typedef     path
 *              Represent a path by list of arranged nodes.
 * @field       length     number of nodes included in the path.
 * @field       nodes      array of nodes.
*/
typedef struct _path{
	int length;
	node* nodes;
}path,shortestPath;


#endif