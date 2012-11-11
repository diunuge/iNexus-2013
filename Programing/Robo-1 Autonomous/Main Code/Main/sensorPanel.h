#ifndef diuSensorPanel
#define diuSensorPanel

#include "configuration.h"

/************************** function prototypes ************************/

int sensorDigitalState(int analogPIN);
boolean isNode();
boolean isBlockedNode();
boolean isAllowedNode();
boolean isAllWhite();
boolean isAllBlack();


/************************** function definitions ************************/

/*!
 * @function    sensorDigitalState
 * @abstract    Convert analog sensor state to digital
 * @discussion  This function take a analog pin number, read analog value,
 *              compare it with given threshold values, convert to relevant digital state.
 *              This can use for digital PID or normal line following
 * @param       analogPIN    The analog pin number. This must be an Integer. EX: 0 for A0
 * @param       HIGH_THRESHOLD  threshold value for digital high
 * @param       LOW_THRESHOLD   threshold value for digital low 
 * @result      A integer which indicate digital state.
*/
int sensorDigitalState(int analogPIN){
	int analogValue = analogRead(analogPIN);
	if(analogValue> HIGH_THRESHOLD)
		return HIGH;
	else if(analogValue < LOW_THRESHOLD)
		return LOW;
	else
		return -1; // error status. this should be handled in future functions or remove this
}


boolean isNode(){
	if( Scout==WHITE && Sensor1==WHITE && Sensor2==WHITE && Sensor3==WHITE && Sensor7==WHITE && Sensor8==WHITE && Sensor9==WHITE){
		return true;
    }
    else
        return false;
}

boolean isBlockedNode(){
	if( isNode() ){
		if((Sensor4==BLACK && Sensor5==BLACK && Sensor6==BLACK) || (Sensor4==BLACK && Sensor5==BLACK && Sensor6==WHITE) || (Sensor4==WHITE && Sensor5==BLACK && Sensor6==BLACK))
			return true;
		else
			return false;
    }
    else
        return false;
}

boolean isAllowedNode(){
	if( isNode() ){
		if((Sensor4==WHITE && Sensor5==WHITE && Sensor6==WHITE) || (Sensor4==BLACK && Sensor5==WHITE && Sensor6==WHITE) || (Sensor4==WHITE && Sensor5==WHITE && Sensor6==BLACK))
			return true;
		else
			return false;
    }
    else
        return false;
}

boolean isAllBlack(){
      if( Scout==BLACK && Sensor1==BLACK && Sensor2==BLACK && Sensor3==BLACK && Sensor4==BLACK && Sensor5==BLACK && Sensor6==BLACK && Sensor7==BLACK && Sensor8==BLACK && Sensor9==BLACK){
            return true;
      }
      else
            return false;
}

boolean isAllWhite(){
      if( Scout==WHITE && Sensor1==WHITE && Sensor2==WHITE && Sensor3==WHITE && Sensor4==WHITE && Sensor5==WHITE && Sensor6==WHITE && Sensor7==WHITE && Sensor8==WHITE && Sensor9==WHITE){
            return true;
      }
      else
            return false;
}

#endif