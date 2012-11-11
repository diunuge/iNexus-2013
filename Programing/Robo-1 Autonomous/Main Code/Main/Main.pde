// Authors: Diunuge Buddhika Wijesinghe
// Competition iNexus 2013
// version: 2.0v: Not Optimized
// Last mod: 11-11-2012

/********************* include libraries *******************************/

#include <Servo.h>
#include <LiquidCrystal.h>
#include <QTRSensors.h>
#include "dataTypes.h"
#include "motion.h"
#include "configuration.h"
#include "debug.h"
#include "test.h"
#include "status.h"


/* setup code goes here */
void setup()
{
	//Do common initialization which is not dependable of type of run
	Serial.begin(9600);

	setPID();

	//pin configurations
	pinMode(Scout_PIN, INPUT);      
    pinMode(Sensor1_PIN, INPUT);      
	pinMode(Sensor2_PIN, INPUT);      
	pinMode(Sensor3_PIN, INPUT);      
	pinMode(Sensor4_PIN, INPUT);      
	pinMode(Sensor5_PIN, INPUT);      
	pinMode(Sensor6_PIN, INPUT);      
	pinMode(Sensor7_PIN, INPUT);      
	pinMode(Sensor8_PIN, INPUT);      
	pinMode(Sensor9_PIN, INPUT); 

	pinMode(Motor_Left_Forward,OUTPUT);
	pinMode(Mortor_Left_Reverse,OUTPUT);
	pinMode(Motor_Right_Forward,OUTPUT);
	pinMode(Motor_Right_Reverse,OUTPUT);

	currentDirection = 1;

	currentPosition.x = 1;
	currentPosition.y = 0;
	
	//if this is dry run: find and save grid parameters: initialize variables
	if(isDryRun()){
		//initialize the grid parameters
		for(int counter0=1; counter0<(NO_OF_GRID_ROWS); counter0++)
			for(int counter1=1; counter1<(NO_OF_GRID_COLUMNS); counter1++){
				if(counter0==0|| counter1==0 || counter0==NO_OF_GRID_ROWS || counter1==NO_OF_GRID_COLUMNS){
					grid[counter0][counter1] = NODE_NOT_DEFINED;
				}
				else
					grid[counter0][counter1] = NODE_IS_ALLOWED;
			}
		
	}
	//if this is main run: load the parameters from dry run
	else{
		
	}
	
}

/****************    end of setup()   ***************************/

/* main loop after setup code */
void loop()
{
	Serial.write("Starting..");
	delay(1000);

	calibrateSensors();

	//test codes goes here
	/*
	while(1){
		//testGoTroughTGrid();
		//line_following_pd();
		//simple_path_follow();
		//path_follow_PID();
		//sendSensorStatus();
		//lineFollowPID();
		//delay(1000);

		discoverGrid();
	}*/
	

	if(isDryRun()){ //this is dry run

		DRY_RUN_STATE = RUN_TYPE_STARTED;
		Serial.println("Starting the dry run.. ");
		while(1){

			if(DRY_RUN_STATE==RUN_TYPE_STARTED){
				discoverGrid();

				//for debug
				sendGridStatus();
			}

			else
				stop();
		}
	}
	else{
		while(1){
			Serial.println("competition");
		}
	}

	return;
}
/******************   end of loop()   ********************************/

void discoverGrid(){
	path dryRunPath;
	node dryRunNodes[(NO_OF_GRID_ROWS-1)*(NO_OF_GRID_COLUMNS-1)];
	dryRunPath.nodes = dryRunNodes;
	createDryRunPath(&dryRunPath);
	
	for(int counter0=0; counter0<dryRunPath.length; counter0++){

		gotoAdjacentNode(dryRunPath.nodes[counter0]);
		if(isBlockedNode())
			grid[dryRunPath.nodes[counter0].x][dryRunPath.nodes[counter0].y] = NODE_IS_BLOCKED;

		delay(1000);
	}
	DRY_RUN_STATE = RUN_TYPE_FINISHED;
}
