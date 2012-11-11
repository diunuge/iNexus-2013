#ifndef diuConfiguration
#define diuConfiguration


#include <wprogram.h>

/********************* pin naming ***************************************/

/*! @define   Scout_PIN    Analog pin number which connected to SCOUT(front) sensor */
#define Scout_PIN    9 
#define Sensor1_PIN 11
#define Sensor2_PIN 10
#define Sensor3_PIN  6 
#define Sensor4_PIN  3 
#define Sensor5_PIN  2 
#define Sensor6_PIN  1 
#define Sensor7_PIN  0 
#define Sensor8_PIN  4 
#define Sensor9_PIN  8 

#define Motor_Left_Forward  34 	//orange
#define Mortor_Left_Reverse 35
#define Motor_Left_Enable   9	//yellow
#define Motor_Right_Forward 36
#define Motor_Right_Reverse 37
#define Motor_Right_Enable  10	//Green


/*! @define EncoderL  Left Motor Encoder PIN number */
#define EncoderL
/*! @define EncoderR  Right Motor Encoder PIN number */
#define EncoderR



/****************** coding helping definitions ********************/

/*! @define   Scout    Returns relevent digital state of Scout sensor from it's analog reading */
#define Scout   sensorDigitalState(Scout_PIN)
#define Sensor1 sensorDigitalState(Sensor1_PIN)
#define Sensor2 sensorDigitalState(Sensor2_PIN)
#define Sensor3 sensorDigitalState(Sensor3_PIN)
#define Sensor4 sensorDigitalState(Sensor4_PIN)
#define Sensor5 sensorDigitalState(Sensor5_PIN)
#define Sensor6 sensorDigitalState(Sensor6_PIN)
#define Sensor7 sensorDigitalState(Sensor7_PIN)
#define Sensor8 sensorDigitalState(Sensor8_PIN)
#define Sensor9 sensorDigitalState(Sensor9_PIN)



/******************  define variables status  ********************/

/*! @define   NO_OF_GRID_ROWS    Number of rows that grid has */
#define NO_OF_GRID_ROWS 5 //7
/*! @define   NO_OF_GRID_COLUMNS    Number of columns that grid has */
#define NO_OF_GRID_COLUMNS 5 //7


/*! @define   BLACK    Sensor input state for the darker color of the path */
#define BLACK HIGH
/*! @define   BLACK    Sensor input state for the lighter color of the path */
#define WHITE LOW

/*! @define   HIGH_THRESHOLD    Threshold value(0-1024) of input 'HIGH' for convert analog sensor pannel values to digital */
#define HIGH_THRESHOLD 408 // ~2.5v
/*! @define   LOW_THRESHOLD     Threshold value(0-1024) of input 'LOW' for convert analog sensor pannel values to digital */
#define LOW_THRESHOLD  408 // ~1v

#define SLOW_PWM 180
#define MID_PWM  200
#define FAST_PWM 200

/*! @define NORTH  Indicate the reference north which uses to navigate autonomus robot */
#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3


/********************* globle variables ***********************/

/*!
 * @var         sensorPannel
 * @abstract    create a object of QTRSensorsAnalog.
 * @discussion  create a object of QTRSensorsAnalog to use analog pid.
*/
QTRSensorsAnalog sensorPannel((unsigned char[]) {11, 10, 6, 3, 2, 1, 0, 4, 8}, 9);

/*!
 * @var         sensors
 * @abstract    store analog values of sensor panel.
 * @discussion  Stores analog values(0-1024) of main sensor panel. this gets update from sensorPanel.readLine()
*/
unsigned int sensors[9];

int position,error,lastError,error_reverse,motorSpeed,position_reverse;

/*!
 * @var         turningAngles
 * @abstract    Stores the rotation angle to change direction.
 * @discussion  This gives rotation angles as encoded integer for change direstion.
 *              Used in "turnToDirection(int direction)" function.
 *              Angles  0=> 0;  1=> 90;  2=> 180;  -1=> 90 
*/
const int turningAngles[4][4] = {{0,1,2,-1}, 
								 {-1,0,1,2}, 
								 {2,-1,0,1}, 
								 {1,2,-1,0}};


float Kp, Ki, Kd;
int deviation, previousDeviation;
float correction, totalError, integral_correction;

int MIN_RPM, MID_RPM, MAX_RPM, MAX_CORRECTION, TEST_RPM, PID_RightRPM, PID_LeftRPM;


#endif