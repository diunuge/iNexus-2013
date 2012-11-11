#ifndef diuTest
#define diuTest

#include "motion.h"
#include "sensorPanel.h"
#include "dataTypes.h"
#include "algorithm.h"


/************************** function prototypes ************************/

void testSerial();
void testImmediateStop();
void testGoTroughTGrid();
void testDirectionChange();


/************************** function definitions ************************/

void testSerial(){
	for(int counter=0; counter<5; counter++){
		Serial.write("Test");
		delay(1000);
	}
}

void testImmediateStop(){

	Serial.write("Foward");
	moveForward(200,200);
	delay(2000);
	Serial.write("Stop");
	stop();
	delay(1000);

	Serial.write("Foward");
	moveForward(200,200);
	delay(2000);
	Serial.write("Stop");
	stop();
	delay(1000);

	Serial.write("Foward");
	moveForward(200,200);
	delay(2000);
	Serial.write("Stop");
	stop();
	delay(1000);

	Serial.write("Foward");
	moveForward(200,200);
	delay(2000);
	Serial.write("Stop");
	stop();
	delay(1000);
}

void testGoTroughTGrid(){
	Serial.write("First node  ");
	gotoNextFrontNode();
	stop();
	Serial.write("node reached  ");
	delay(500);
	gotoNextFrontNode();
	stop();
	Serial.write("node reached  ");
	delay(500);
	gotoNextFrontNode();
	stop();
	Serial.write("node reached  ");
	delay(500);
	gotoNextFrontNode();
	stop();
	Serial.write("node reached  ");
	delay(500);
	rotateClockwise90();
	gotoNextFrontNode();
	stop();
	Serial.write("node reached  ");
	delay(500);
	rotateClockwise90();
	gotoNextFrontNode();
	stop();
	Serial.write("node reached  ");
	delay(500);
	gotoNextFrontNode();
	stop();
	Serial.write("node reached  ");
	delay(500);
	gotoNextFrontNode();
	stop();
	Serial.write("node reached  ");
	delay(500);
}

void testDirectionChange(){
	turnToDirection(EAST);
	delay(1000);
	turnToDirection(NORTH);
	delay(1000);
	turnToDirection(WEST);
	delay(1000);
	turnToDirection(EAST);
	delay(1000);
	turnToDirection(SOUTH);
	delay(1000);
	turnToDirection(EAST);
	delay(5000);
}

void testGridPathCreate(){

	node nodes[16];
	path aPath;
	aPath.nodes = nodes;
	createDryRunPath(&aPath);
	showPath(&aPath);
}

void testgoThroughGrid(){
	node node1 = {1,1};
	node node2 = {1,2};
	node node3 = {1,3};
	node node4 = {1,4};
	node node5 = {2,4};
	node node6 = {2,3};
	node node7 = {2,2};
	node node8 = {2,1};
	gotoAdjacentNode(node1);
	delay(1000);
	gotoAdjacentNode(node2);
	delay(1000);
	gotoAdjacentNode(node3);
	delay(1000);
	gotoAdjacentNode(node4);
	delay(1000);
	gotoAdjacentNode(node5);
	delay(1000);
	gotoAdjacentNode(node6);
	delay(1000);
	gotoAdjacentNode(node7);
	delay(1000);
	gotoAdjacentNode(node8);
	delay(1000);

	delay(10000);
}

#endif