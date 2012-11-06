// Authors: Diunuge Buddhika Wijesinghe
// Competition iNexus 2013
// version: 1.0v: Not Optimized
// Last mod: 03-09-2012

/********************* include libraries *******************************/
#include <Servo.h>
#include <LiquidCrystal.h>

/* pin naming */
#define Scout_PIN   31
#define Sensor1_PIN 33
#define Sensor2_PIN 32
#define Sensor3_PIN 28
#define Sensor4_PIN 25
#define Sensor5_PIN 24
#define Sensor6_PIN 23
#define Sensor7_PIN 22
#define Sensor8_PIN 26
#define Sensor9_PIN 30

#define Motor_Left_Forward  34 	//orange
#define Mortor_Left_Reverse 35
#define Motor_Left_Enable   9	//yellow
#define Motor_Right_Forward 36
#define Motor_Right_Reverse 37
#define Motor_Right_Enable  10	//Green

#define EncoderL
#define EncoderR

/*  define variables status  */
#define RUN_TYPE_UNAVAILABLE 0
#define RUN_TYPE_STARTED 1
#define RUN_TYPE_FINISHED 2

#define NO_OF_GRID_ROWS 7
#define NO_OF_GRID_COLUMNS 8

#define BLACK HIGH
#define WHITE LOW

#define SLOW_PWM 180
#define MID_PWM  200
#define FAST_PWM 200

#define Scout   digitalRead(Scout_PIN)
#define Sensor1 digitalRead(33)
#define Sensor2 digitalRead(32)
#define Sensor3 digitalRead(28)
#define Sensor4 digitalRead(25)
#define Sensor5 digitalRead(24)
#define Sensor6 digitalRead(23)
#define Sensor7 digitalRead(22)
#define Sensor8 digitalRead(26)
#define Sensor9 digitalRead(30)


/* globle variables */
int grid[NO_OF_GRID_ROWS][NO_OF_GRID_COLUMNS] = {-1};

int DRY_RUN_STATE = RUN_TYPE_UNAVAILABLE;
int RUN_STATE = RUN_TYPE_UNAVAILABLE;

float Kp, Ki, Kd;
int deviation, previousDeviation;
float correction, totalError;

int MIN_RPM, MID_RPM, MAX_RPM, TEST_RPM, PID_RightRPM, PID_LeftRPM;


/* function prototypes */
int isDryRun();
void simple_path_follow();
void setPID();
void path_follow_PID();
int isOnThePath();
int isAllWhite();
int isAllBlack();

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

void serialTest(); 
void sendSensorStatus();
void movingTest();


/**********************************************************************/
/* setup code goes here */
void setup()
{
	//Do common initialization which is not dependable of type of run
	Serial.begin(9600);

	setPID();
	
	//Serial.write("hello");

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
	
	//if this is dry run: find and save grid parameters: initialize variables
	if(isDryRun){
		//initialize the grid parameters
		for(int counter0=0; counter0<NO_OF_GRID_ROWS; counter0++)
			for(int counter1=0; counter1<NO_OF_GRID_COLUMNS; counter1++)
				grid[counter0][counter1] = 0;
		
	}
	//if this is main run: load the parameters from dry run
	else{

	}
	
}

/****************    end of setup()   ***************************/

/* main loop after setup code */
void loop()
{
	//test
	//serialTest(); 
	//sendSensorStatus();
	//delay(1000);
	
	Serial.write("Starting..");
	if(isDryRun()){ //this is dry run
		while(1){
			//simple_path_follow();
			path_follow_PID();
		}
	}
	else{
		while(1){

		}
	}
	
}

/******************   end of loop()   ********************************/

int isDryRun(){
	//read external signal: Probably from a switch
	return 1;
}

void path_follow_PID(){
	  //calculate daviation
      if( Sensor3==WHITE && Sensor4==BLACK && Sensor5==BLACK && Sensor6==BLACK && Sensor7==BLACK)
          deviation = 15;
      if( Sensor3==WHITE && Sensor4==WHITE && Sensor5==BLACK && Sensor6==BLACK && Sensor7==BLACK)
          deviation = 10;
      if( Sensor3==WHITE && Sensor4==WHITE && Sensor5==WHITE && Sensor6==BLACK && Sensor7==BLACK)
          deviation = 4;
      if( Sensor3==BLACK && Sensor4==WHITE && Sensor5==BLACK && Sensor6==BLACK && Sensor7==BLACK)
          deviation = 1;

      if( Sensor3==BLACK && Sensor4==WHITE && Sensor5==WHITE && Sensor6==BLACK && Sensor7==BLACK)
          deviation = 0;
      if( Sensor3==BLACK && Sensor4==WHITE && Sensor5==WHITE && Sensor6==WHITE && Sensor7==BLACK)
          deviation = 0;
      if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==WHITE && Sensor6==BLACK && Sensor7==BLACK)
          deviation = 0;
      if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==WHITE && Sensor6==WHITE && Sensor7==BLACK)
          deviation = 0;

      if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==BLACK && Sensor6==WHITE && Sensor7==BLACK)
          deviation = -1;
      if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==WHITE && Sensor6==WHITE && Sensor7==WHITE)
          deviation = -4;
      if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==BLACK && Sensor6==WHITE && Sensor7==WHITE)
          deviation = -10;
      if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==BLACK && Sensor6==BLACK && Sensor7==WHITE)
          deviation = -15;

      correction =  Kp*deviation + Ki*totalError + Kd*(deviation-previousDeviation);
      totalError += correction;
      previousDeviation = deviation;

      PID_LeftRPM = MID_RPM - correction;
      PID_RightRPM = MID_RPM + correction;

      moveForward(PID_LeftRPM, PID_RightRPM);

      //}
      //correction = 0;
      //totalError = 0;
      //sendSensorStatus();
}

void setPID(){
      MIN_RPM = 145;       //155
      MID_RPM = 200;
      MAX_RPM = 255;
      TEST_RPM = 200;

      Kp = 3;
      Ki = 0;
      Kd = 0;

      totalError = 0;
      previousDeviation = 0;
      PID_LeftRPM = 0;
      PID_RightRPM = 0;
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
                        //while(!isOnThePath())
                              turnLeft(FAST_PWM);
                  else if( Sensor3==WHITE && Sensor4==WHITE && Sensor5==BLACK && Sensor6==BLACK && Sensor7==BLACK)
                        //while(!isOnThePath())
                              turnLeft(FAST_PWM);
                  else if( Sensor3==WHITE && Sensor4==WHITE && Sensor5==WHITE && Sensor6==BLACK && Sensor7==BLACK)
                        //while(!isOnThePath())
                              turnLeft(FAST_PWM);
                  else if( Sensor3==BLACK && Sensor4==WHITE && Sensor5==BLACK && Sensor6==BLACK && Sensor7==BLACK)
                        //while(!isOnThePath())
                              turnLeft(FAST_PWM);

                             //turn to right
                  else if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==BLACK && Sensor6==WHITE && Sensor7==BLACK)
                        //while(!isOnThePath())
                              turnRight(FAST_PWM);
                  else if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==WHITE && Sensor6==WHITE && Sensor7==WHITE)
                        //while(!isOnThePath())
                              turnRight(FAST_PWM);
                  else if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==BLACK && Sensor6==WHITE && Sensor7==WHITE)
                        //while(!isOnThePath())
                              turnRight(FAST_PWM);
                  else if( Sensor3==BLACK && Sensor4==BLACK && Sensor5==BLACK && Sensor6==BLACK && Sensor7==WHITE)
                        //while(!isOnThePath())
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
				  Serial.write("Stopping..");
                  sendSensorStatus();
				  delay(1000);
            }
            else{
                  stop();
                  //reverse(220,220);
				  Serial.write("Stopping..");
                  sendSensorStatus();
                  delay(1000);
            }
      }
}

int isOnThePath(){
      if(((Sensor3==BLACK && Sensor4==WHITE && Sensor5==WHITE && Sensor6==BLACK && Sensor7==BLACK) || ( Sensor3==BLACK && Sensor4==WHITE && Sensor5==WHITE && Sensor6==WHITE && Sensor7==BLACK) || ( Sensor3==BLACK && Sensor4==BLACK && Sensor5==WHITE && Sensor6==BLACK && Sensor7==BLACK) || ( Sensor3==BLACK && Sensor4==BLACK && Sensor5==WHITE && Sensor6==WHITE && Sensor7==BLACK)) && Sensor1==BLACK && Sensor2==BLACK && Sensor8==BLACK && Sensor9==BLACK)
            return 1;
      else
            return 0;
}

int isAllBlack(){
      if( Scout==BLACK && Sensor1==BLACK && Sensor2==BLACK && Sensor3==BLACK && Sensor4==BLACK && Sensor5==BLACK && Sensor6==BLACK && Sensor7==BLACK && Sensor8==BLACK && Sensor9==BLACK){
            return 1;
      }
      else
            return 0;
}

int isAllWhite(){
      if( Scout==WHITE && Sensor1==WHITE && Sensor2==WHITE && Sensor3==WHITE && Sensor4==WHITE && Sensor5==WHITE && Sensor6==WHITE && Sensor7==WHITE && Sensor8==WHITE && Sensor9==WHITE){
            return 1;
      }
      else
            return 0;
}

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

/*********************   debug functions   ********************************/

void serialTest(){
	for(int counter=0; counter<5; counter++){
		Serial.write("Test");
		delay(1000);
	}
}

void sendSensorStatus(){
      if( Sensor1 == 1){
		  Serial.write("1");
      }
      else if( Sensor1 == 0){
            Serial.write("0");
      }

      if( Sensor2 == 1){
            Serial.write("1");
      }
      else if( Sensor2 == 0){
            Serial.write("0");
      }

      if( Sensor3 == 1){
            Serial.write("1");
      }
      else if( Sensor3 == 0){
            Serial.write("0");
      }

      if( Sensor4 == 1){
            Serial.write("1");
      }
      else if( Sensor4 == 0){
            Serial.write("0");
      }

      if( Sensor5 == 1){
            Serial.write("1");
      }
      else if( Sensor5 == 0){
            Serial.write("0");
      }

      if( Sensor6 == 1){
            Serial.write("1");
      }
      else if( Sensor6 == 0){
            Serial.write("0");
      }

      if( Sensor7 == 1){
            Serial.write("1");
      }
      else if( Sensor7 == 0){
            Serial.write("0");
      }

      if( Sensor8 == 1){
            Serial.write("1");
      }
      else if( Sensor8 == 0){
            Serial.write("0");
      }

      if( Sensor9 == 1){
            Serial.write("1");
      }
      else if( Sensor9 == 0){
            Serial.write("0");
      }
	  Serial.write(" ");

      if( Scout == 1){
            Serial.write("1");
      }
      else if( Scout == 0){
            Serial.write("0");
      }
	  Serial.write("  ");
}

void movingTest(){

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