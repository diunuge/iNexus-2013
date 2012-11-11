#ifndef diuDebug
#define diuDebug

#include "status.h"
#include "dataTypes.h"
#include "configuration.h"
#include "sensorPanel.h"

/************************** function prototypes ************************/

void sendSensorStatus();
void showPath(path aPath);


/************************** function definitions ************************/

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

void sendGridStatus(){
	Serial.println("");
	Serial.println("Grid:");
	for(int counter0=0; counter0<(NO_OF_GRID_ROWS+1); counter0++){
		for(int counter1=0; counter1<(NO_OF_GRID_COLUMNS+1); counter1++){
			
			Serial.print(grid[counter0][counter1]);
			Serial.print(" ");
		}
		Serial.println("");
	}
}

#endif