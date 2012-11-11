#ifndef diuMotion
#define diuMotion


#include "dataTypes.h"
#include "configuration.h"
#include "debug.h"
#include "sensorPanel.h"
#include "status.h"

/************************** function prototypes *************************/

//motion control functions
void motorLeft_foward(int pwm);
void motorRight_foward(int pwm);
void motorLeft_reverse(int pwm);
void motorRight_reverse(int pwm);
void motorLeft_stop();
void motorRight_stop();

void moveForward(int leftpwm,int rightpwm);
void turnRight(int pwm);
void turnLeft(int pwm);
void rotateClockwise(int leftpwm,int rightpwm);
void rotateAntiClockwise(int leftpwm,int rightpwm);
void stop();
void stop(int delayms);
void turn90toLeft();
void turn90toRight();
void rotateClockwise90();
void rotateClockwise180();
void rotateAntiClockwise90();

void gotoNextFrontNode();
void turnTowardNode(node currentNode, node nextNode);
boolean turnToDirection(int direction);
void turnTowardAdjacentNode(node currentNode, node adjacentNode);
int  isAdjacent(node node1, node node2);
void setPID();
void calibrateSensors();
void line_following_pd();
void path_follow_PID();
void simple_path_follow();


/************************** function definitions ************************/

void setPID(){
      MIN_RPM = 155;       //155
      MID_RPM = 205;
      MAX_RPM = 255;
	  MAX_CORRECTION = 100;

      TEST_RPM = 200;

      Kp = 0.1;
      Ki = 0;
      Kd = 2;

      totalError = 0;
      previousDeviation = 0;

	  lastError =0;

      PID_LeftRPM = 0;
      PID_RightRPM = 0;
}

void line_following_pd()
{
  position = sensorPannel.readLine(sensors);
  error = position - 4000;

  //Serial.println(error);
  
  motorSpeed = Kp * error + Kd * (error - lastError);
  lastError = error;
 

  
 PID_RightRPM = MAX_RPM + motorSpeed;
 PID_LeftRPM = MAX_RPM - motorSpeed;

  if (PID_RightRPM < 0)
    PID_RightRPM = 0;
  if (PID_LeftRPM < 0)
    PID_LeftRPM = 0;
 
 if (PID_RightRPM > 255)
    PID_RightRPM = 255;
    
  if (PID_LeftRPM > 255)
    PID_LeftRPM = 255;
 
  moveForward(PID_LeftRPM, PID_RightRPM);
}

void calibrateSensors(){
	Serial.write("Calibrating start..");
	int i;
	#define motionSpeed 100
	rotateAntiClockwise(motionSpeed,motionSpeed);
	for (i = 0; i < 10; i++)
		sensorPannel.calibrate();
	stop(20);
	rotateClockwise(motionSpeed,motionSpeed);
	for (i = 0; i < 10; i++)
		sensorPannel.calibrate();
	stop(500);
	rotateClockwise(motionSpeed,motionSpeed);
	for (i = 0; i < 10; i++)
		sensorPannel.calibrate();
	stop(20);
	rotateAntiClockwise(motionSpeed,motionSpeed);
	for (i = 0; i < 10; i++)
		sensorPannel.calibrate();
	stop(2000);
	/*
	rotateAntiClockwise90();
	
	moveForward(calibrateMotionSpeed,calibrateMotionSpeed);
	for (i = 0; i < 10; i++)  // make the calibration take about 5 seconds
	{
		sensorPannel.calibrate();
		//delay(2);
	}
	stop(20);
	reverse(calibrateMotionSpeed,calibrateMotionSpeed);
	for (i = 0; i < 10; i++)  // make the calibration take about 100ms
	{
		sensorPannel.calibrate();
		//delay(2);
	}
	stop(20);
	reverse(calibrateMotionSpeed,calibrateMotionSpeed);
	for (i = 0; i < 10; i++)  // make the calibration take about 100ms
	{
		sensorPannel.calibrate();
		//delay(2);
	}
	stop(20);
	moveForward(calibrateMotionSpeed,calibrateMotionSpeed);
	for (i = 0; i < 10; i++)  // make the calibration take about 5 seconds
	{
		sensorPannel.calibrate();
		//delay(2);
	}
	stop(20);
	rotateClockwise90();
	stop(50);*/
	Serial.println("Calibrating end..");
}

void path_follow_PID(){
	int Sens3 = Sensor3;
	int Sens4 = Sensor4;
	int Sens5 = Sensor5;
	int Sens6 = Sensor6;
	int Sens7 = Sensor7;

	  //calculate daviation
      if( Sens3==WHITE && Sens4==BLACK && Sens5==BLACK && Sens6==BLACK && Sens7==BLACK)
          deviation = 5;
      if( Sens3==WHITE && Sens4==WHITE && Sens5==BLACK && Sens6==BLACK && Sens7==BLACK)
          deviation = 4;
      if( Sens3==WHITE && Sens4==WHITE && Sens5==WHITE && Sens6==BLACK && Sens7==BLACK)
          deviation = 3;
      if( Sens3==BLACK && Sens4==WHITE && Sens5==BLACK && Sens6==BLACK && Sens7==BLACK)
          deviation = 2;

      if( Sens3==BLACK && Sens4==WHITE && Sens5==WHITE && Sens6==BLACK && Sens7==BLACK)
          deviation = 1;
      if( Sens3==BLACK && Sens4==WHITE && Sens5==WHITE && Sens6==WHITE && Sens7==BLACK)
          deviation = 0;
      if( Sens3==BLACK && Sens4==BLACK && Sens5==WHITE && Sens6==BLACK && Sens7==BLACK)
          deviation = 0;
      if( Sens3==BLACK && Sens4==BLACK && Sens5==WHITE && Sens6==WHITE && Sens7==BLACK)
          deviation = -1;

      if( Sens3==BLACK && Sens4==BLACK && Sens5==BLACK && Sens6==WHITE && Sens7==BLACK)
          deviation = -2;
      if( Sens3==BLACK && Sens4==BLACK && Sens5==WHITE && Sens6==WHITE && Sens7==WHITE)
          deviation = -3;
      if( Sens3==BLACK && Sens4==BLACK && Sens5==BLACK && Sens6==WHITE && Sens7==WHITE)
          deviation = -4;
      if( Sens3==BLACK && Sens4==BLACK && Sens5==BLACK && Sens6==BLACK && Sens7==WHITE)
          deviation = -5;

      correction =  Kp*deviation + Ki*totalError + Kd*(deviation-previousDeviation);
      totalError += correction;
      previousDeviation = deviation;

      PID_LeftRPM = MID_RPM + correction;
      PID_RightRPM = MID_RPM - correction;

      moveForward(PID_LeftRPM, PID_RightRPM);

      //}
      //correction = 0;
      //totalError = 0;
      //sendSensorStatus();
}

void lineFollowPID(){

	int Sens3 = Sensor3;
	int Sens4 = Sensor4;
	int Sens5 = Sensor5;
	int Sens6 = Sensor6;
	int Sens7 = Sensor7;

      	  //calculate daviation
      if( Sens3==WHITE && Sens4==BLACK && Sens5==BLACK && Sens6==BLACK && Sens7==BLACK)
          deviation = 5;
      if( Sens3==WHITE && Sens4==WHITE && Sens5==BLACK && Sens6==BLACK && Sens7==BLACK)
          deviation = 4;
      if( Sens3==WHITE && Sens4==WHITE && Sens5==WHITE && Sens6==BLACK && Sens7==BLACK)
          deviation = 3;
      if( Sens3==BLACK && Sens4==WHITE && Sens5==BLACK && Sens6==BLACK && Sens7==BLACK)
          deviation = 2;

      if( Sens3==BLACK && Sens4==WHITE && Sens5==WHITE && Sens6==BLACK && Sens7==BLACK)
          deviation = 1;
      if( Sens3==BLACK && Sens4==WHITE && Sens5==WHITE && Sens6==WHITE && Sens7==BLACK)
          deviation = 0;
      if( Sens3==BLACK && Sens4==BLACK && Sens5==WHITE && Sens6==BLACK && Sens7==BLACK)
          deviation = 0;
      if( Sens3==BLACK && Sens4==BLACK && Sens5==WHITE && Sens6==WHITE && Sens7==BLACK)
          deviation = -1;

      if( Sens3==BLACK && Sens4==BLACK && Sens5==BLACK && Sens6==WHITE && Sens7==BLACK)
          deviation = -2;
      if( Sens3==BLACK && Sens4==BLACK && Sens5==WHITE && Sens6==WHITE && Sens7==WHITE)
          deviation = -3;
      if( Sens3==BLACK && Sens4==BLACK && Sens5==BLACK && Sens6==WHITE && Sens7==WHITE)
          deviation = -4;
      if( Sens3==BLACK && Sens4==BLACK && Sens5==BLACK && Sens6==BLACK && Sens7==WHITE)
          deviation = -5;

      integral_correction = Ki*totalError;
      if(integral_correction > 100)
            integral_correction = 100;
      if(integral_correction < -100)
            integral_correction = -100;
      
      correction =  Kp*deviation + integral_correction + Kd*(deviation-previousDeviation);
      totalError += correction;
      previousDeviation = deviation;

      if(correction > MAX_CORRECTION)
            correction = MAX_CORRECTION;
      if(correction < -MAX_CORRECTION)
            correction = -MAX_CORRECTION;
            
      PID_LeftRPM = MAX_RPM;
      PID_RightRPM = MAX_RPM + (int)correction;
      
      if(correction > 0)
      {
           PID_LeftRPM  = MAX_RPM - (int)correction;
           PID_RightRPM = MAX_RPM;
      }
      
      /*if(PID_LeftRPM - PID_RightRPM > max_diffrence)
      {
           PID_LeftRPM -= (PID_LeftRPM - PID_RightRPM)/factor_diffrence;
      }
      else if(PID_RightRPM - PID_LeftRPM > max_diffrence)
      {
           PID_RightRPM -= (PID_RightRPM - PID_LeftRPM)/factor_diffrence;
      }*/

      moveForward(PID_LeftRPM,PID_RightRPM);
      
      /*PID_LeftRPM = MID_RPM + (int)correction;
      if(PID_LeftRPM > MAX_RPM)
           PID_LeftRPM = MAX_RPM;

      PID_RightRPM = MID_RPM - (int)correction;
      if(PID_RightRPM > MAX_RPM)
           PID_RightRPM = MAX_RPM;
      moveForward(PID_LeftRPM, PID_RightRPM);*/

}

void simple_path_follow(){
	if(Scout == WHITE){
                  //on the path
                  if( Sensor3==BLACK && Sensor4==WHITE && Sensor5==WHITE && Sensor6==BLACK && Sensor7==BLACK)
                        moveForward(SLOW_PWM,FAST_PWM);
                  else if( Sensor3==BLACK && Sensor4==WHITE && Sensor5==WHITE && Sensor6==WHITE && Sensor7==BLACK)
                        moveForward(FAST_PWM,FAST_PWM);
                  else if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==WHITE && Sensor6==BLACK && Sensor7==BLACK)
                        moveForward(FAST_PWM,FAST_PWM);
                  else if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==WHITE && Sensor6==WHITE && Sensor7==BLACK)
                        moveForward(FAST_PWM,SLOW_PWM);


                  //out of pat; have to turn
                            //turn to left
                  else if( Sensor3==WHITE && Sensor4==BLACK && Sensor5==BLACK && Sensor6==BLACK && Sensor7==BLACK)
                              turnLeft(FAST_PWM);
                  else if( Sensor3==WHITE && Sensor4==WHITE && Sensor5==BLACK && Sensor6==BLACK && Sensor7==BLACK)
                              turnLeft(FAST_PWM);
                  else if( Sensor3==WHITE && Sensor4==WHITE && Sensor5==WHITE && Sensor6==BLACK && Sensor7==BLACK)
                              turnLeft(FAST_PWM);
                  else if( Sensor3==BLACK && Sensor4==WHITE && Sensor5==BLACK && Sensor6==BLACK && Sensor7==BLACK)
                              turnLeft(FAST_PWM);

                             //turn to right
                  else if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==BLACK && Sensor6==WHITE && Sensor7==BLACK)
                              turnRight(FAST_PWM);
                  else if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==WHITE && Sensor6==WHITE && Sensor7==WHITE)
                              turnRight(FAST_PWM);
                  else if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==BLACK && Sensor6==WHITE && Sensor7==WHITE)
                              turnRight(FAST_PWM);
                  else if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==BLACK && Sensor6==BLACK && Sensor7==WHITE)
                              turnRight(FAST_PWM);

				  /*
                  //special
                  else if( Sensor3==WHITE && Sensor4==WHITE && Sensor5==WHITE && Sensor6==WHITE && Sensor7==BLACK)
                        moveForward(FAST_PWM,FAST_PWM);
                  else if( Sensor3==BLACK && Sensor4==WHITE && Sensor5==WHITE && Sensor6==WHITE && Sensor7==WHITE)
                        moveForward(FAST_PWM,FAST_PWM);
                  else if( Sensor1==BLACK && Sensor2==BLACK && Sensor3==BLACK && Sensor4==BLACK && Sensor5==BLACK && Sensor6==BLACK && Sensor7==BLACK && Sensor8==BLACK && Sensor9==BLACK)
                        moveForward(255,255);
				  */

            else if(isAllBlack()){
                  // all black
                  stop();
				  Serial.write("Stopping.. ");
                  sendSensorStatus();
				  delay(1000);
            }
            else{
                  stop();
                  //reverse(220,220);
				  Serial.write("Stopping.. ");
                  sendSensorStatus();
                  delay(1000);
            }
      }
	else{
		stop();
			Serial.write("Stopping.. ");
            sendSensorStatus();
			delay(1000);
	}
}


//motion control functions

void motorLeft_foward(int leftpwm){
    digitalWrite(Motor_Left_Forward,HIGH);
	digitalWrite(Mortor_Left_Reverse,LOW);
	analogWrite(Motor_Left_Enable,leftpwm);
}

void motorLeft_reverse(int leftpwm){
    digitalWrite(Motor_Left_Forward,LOW);
	digitalWrite(Mortor_Left_Reverse,HIGH);
	analogWrite(Motor_Left_Enable,leftpwm);
}


void motorRight_foward(int rightpwm){
	digitalWrite(Motor_Right_Forward,HIGH);
	digitalWrite(Motor_Right_Reverse,LOW);
	analogWrite(Motor_Right_Enable,rightpwm);
}

void motorRight_reverse(int rightpwm){
	digitalWrite(Motor_Right_Forward,LOW);
	digitalWrite(Motor_Right_Reverse,HIGH);
	analogWrite(Motor_Right_Enable,rightpwm);
}

void motorLeft_stop(){
	analogWrite(Motor_Left_Enable,255);
	digitalWrite(Motor_Left_Forward,HIGH);
	digitalWrite(Mortor_Left_Reverse,HIGH);
}

void motorRight_stop(){
	analogWrite(Motor_Right_Enable,255);
	digitalWrite(Motor_Right_Forward,HIGH);
	digitalWrite(Motor_Right_Reverse,HIGH);
}


void moveForward(int leftpwm,int rightpwm){
	motorLeft_foward(leftpwm);
    motorRight_foward(rightpwm);
}

void reverse(int leftpwm,int rightpwm){
	motorLeft_reverse(leftpwm);
	motorRight_reverse(rightpwm);
}

void turnRight(int pwm){
	motorLeft_foward(pwm);
	motorRight_stop();
}

void turnLeft(int pwm){
	motorRight_foward(pwm);
	motorLeft_stop();
}

void rotateClockwise(int leftpwm,int rightpwm){
	motorLeft_foward(leftpwm);
	motorRight_reverse(rightpwm);
}


void rotateAntiClockwise(int leftpwm,int rightpwm){
	motorLeft_reverse(leftpwm);
	motorRight_foward(rightpwm);
}

void stop(){
	motorLeft_stop();
    motorRight_stop();
}

void stop(int delayms){
	motorLeft_stop();
    motorRight_stop();
	delay(delayms);
}

void rotateAntiClockwise90(){
	rotateAntiClockwise(255,255);
	delay(230);
	stop();
	delay(20);
}

void rotateClockwise90(){
	rotateClockwise(255,255);
	delay(230);
	stop();
	delay(20);
}

void rotateClockwise180(){ 
	rotateClockwise90();
	stop();
	delay(20);
	rotateClockwise90();
	stop();
	delay(20);
}

boolean gotoAdjacentNode(node nextNode){

	int direction = isAdjacent(currentPosition, nextNode);

	if(turnToDirection(direction)){
		gotoNextFrontNode();
		updateState(direction,nextNode);
		return true;
	}
	return false;
}

void gotoNextFrontNode(){
	if(isNode())
		while(isNode())
			moveForward(200,200);

	while(!isNode())
		line_following_pd();
	stop();
	//now robot at on a node
}

boolean turnToDirection(int direction){

	if(direction == -1)
		return false;
	
	switch(turningAngles[currentDirection][direction]){
		case  0: 
			break;
		case  1: 
			Serial.write("90 ");
			rotateClockwise90(); 
			break;
		case -1: 
			Serial.write("-90 ");
			rotateAntiClockwise90(); 
			break;
		case  2: 
			Serial.write("180 ");
			rotateClockwise180(); 
			break;
		default: 
			break;
	}
	currentDirection = direction;
	return true;
}

/*!
 * @function    turnTowardAdjacentNode
 * @abstract    turn toward a adjacent node.
 * @discussion  turn the autonomous bot toward given adjacent node,
 *              if they are adjacent.
 * @param       currentNode    The current node that autonomous bot is standing.
 * @param       adjacentNode   The adjacent node that autonomous bot should turn towards.
 * @result      If they are not adjacent returns -1. if they are adjacent returns the direction of node2 with respect to node1
*/
void turnTowardAdjacentNode(node currentNode, node adjacentNode){

	int newDirection = isAdjacent(currentNode,adjacentNode);

	if( newDirection != -1 ){
		turnToDirection(newDirection);
	}
	else{
		return;
	}
}

/*!
 * @function    isAdjacent
 * @abstract    check that if two nodes are adjacent
 * @discussion  This function take a two nodes.
 *              Check whether they are adjacent.
 * @param       node1    first node of node couple. reference direction will be with respect to this node.
 * @param       node2    second node of node couple
 * @result      If they are not adjacent returns -1. if they are adjacent returns the direction of node2 with respect to node1
*/

int isAdjacent(node node1, node node2){
	if(node1.x == node2.x){
		if(node1.y-node2.y==1){
			return WEST;
		}
		else if(node1.y-node2.y==-1){
			return EAST;
		}
		else{
			return -1;
		}
	}else if(node1.y == node2.y){
		if(node1.x-node2.x==1){
			return NORTH;
		}
		else if(node1.x-node2.x==-1){
			return SOUTH;
		}
		else{
			return -1;
		}
	}else{
		return -1;
	}
}


#endif