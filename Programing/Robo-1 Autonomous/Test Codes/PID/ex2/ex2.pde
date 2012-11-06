
int sensor7 = 22; // sensor_right2
int sensor6 = 23; // sensor_right1
int sensor5 = 24; // sensor_middle
int sensor4 = 25; // sensor_left1
int sensor8 = 26; // sensor_right3
int sensor3 = 28; // sensor_left4
int sensor9 = 30; // sensor_right4
int scout = 31;  // sensor_front
int sensor2 = 32; // sensor_left3
int sensor1 = 33; // sensor_left4 


const int mat_row= 5;
const int mat_column =5;
int matrix[mat_row][mat_column];

int direction;
int row,column;

int Motor_Left_Forward=34;	//orange
int Mortor_Left_Reverse=35;
int Motor_Left_Enable=9;	//yellow
int Motor_Right_Forward=36;
int Motor_Right_Reverse=37;
int Motor_Right_Enable=10;	//Green

int SlOW_PWM,MID_PWM,FAST_PWM,SIDE;

void setup()
{
  Serial.begin(9600);

  pinMode(sensor1, INPUT);      
  pinMode(sensor2, INPUT);      
  pinMode(sensor3, INPUT);      
  pinMode(sensor4, INPUT);      
  pinMode(sensor5, INPUT);      
  pinMode(sensor6, INPUT);      
  pinMode(sensor7, INPUT);      
  pinMode(sensor8, INPUT);      
  pinMode(sensor9, INPUT);      
  pinMode(scout, INPUT);   

  pinMode(Motor_Left_Forward,OUTPUT);
  pinMode(Mortor_Left_Reverse,OUTPUT);
  pinMode(Motor_Right_Forward,OUTPUT);
  pinMode(Motor_Right_Reverse,OUTPUT);
 
  SlOW_PWM=150;
  MID_PWM=200;
  FAST_PWM=255;

  row=0;
  column=0;
  direction=1;

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

}

void loop()
{/*
   moveForward(FAST_PWM,FAST_PWM);
   delay(10000);
//  stop();
  turnRight(FAST_PWM);
  delay(10000);
 //stop();
 // delay(500);
  turnLeft(FAST_PWM);
  delay(10000);
 //stop();
 // delay(500);
  rotateClockwise(FAST_PWM,FAST_PWM);
  delay(20000);
//stop();
  rotateAntiClockwise(FAST_PWM,FAST_PWM);
   delay(20000);
  stop();
  delay(500);  
  */

/*	if(digitalRead(sensor1)==LOW){
		Serial.println("button33_sensor_left4");
		delay(500);
	}
	if(digitalRead(sensor2)==LOW){
		Serial.println("button32_sensor_left3");
		delay(500);
	}
	if(digitalRead(sensor3)==LOW){
		Serial.println("button28_sensor_left2");
		delay(500);
	}
	if(digitalRead(sensor4)==LOW){
		Serial.println("button25_sensor_left1");
		delay(500);
	}
	if(digitalRead(sensor5)==LOW){
		Serial.println("button24_sensor_middle");
		delay(500);
	}
	if(digitalRead(sensor6)==LOW){
		Serial.println("button23_sensor_right1");
		delay(500);
	}
	if(digitalRead(sensor7)==LOW){
		Serial.println("button22_sensor_right2");
		delay(500);
	}
	if(digitalRead(sensor8)==LOW){
		Serial.println("button26_sensor_right3");
		delay(500);
	}
	if(digitalRead(sensor9)==LOW){
		Serial.println("button30_sensor_right4");
		delay(500);
	}
	if(digitalRead(scout)==LOW){
		Serial.println("button31_sensor_scout");
		delay(500);
	}  
	
*/
	
/*		if(digitalRead(sensor5)==LOW && digitalRead(sensor3)==HIGH && digitalRead(sensor7)==HIGH){
			moveForward(198,198);
		}
		
		else if(digitalRead(sensor5)==LOW && digitalRead(sensor3)==LOW && digitalRead(sensor7)==LOW){
			if (direction==1){
				rotateClockwise(198,198);
				delay(1000);
				direction=0;
			}
			else if (direction==0){
				rotateAntiClockwise(198,198);
				delay(1000);
				direction=1;
			}
			
		}
		else if(digitalRead(sensor5)==LOW && digitalRead(sensor3)==HIGH && digitalRead(sensor7)==LOW){
			rotateClockwise(198,198);
		}
		else if(digitalRead(sensor5)==LOW && digitalRead(sensor3)==LOW && digitalRead(sensor7)==HIGH){
			rotateAntiClockwise(198,198);
		}


		if(digitalRead(sensor5)==HIGH && digitalRead(sensor3)==HIGH && digitalRead(sensor7)==LOW){
			rotateClockwise(198,198);
		}
		
		if(digitalRead(sensor5)==HIGH && digitalRead(sensor3)==LOW && digitalRead(sensor7)==HIGH){
			rotateAntiClockwise(198,198);
		}
*/


	if(digitalRead(sensor5)==LOW && digitalRead(sensor3)==HIGH && digitalRead(sensor7)==HIGH){
			moveForward(SlOW_PWM,SlOW_PWM);
		}
    else if(digitalRead(sensor5)==LOW && digitalRead(sensor3)==HIGH && digitalRead(sensor7)==LOW){
			rotateClockwise(SlOW_PWM,SlOW_PWM);
			delay(500);
		}
	else if(digitalRead(sensor5)==LOW && digitalRead(sensor3)==LOW && digitalRead(sensor7)==HIGH){
			rotateAntiClockwise(SlOW_PWM,SlOW_PWM);
			delay(500);
		}

/*   if(digitalRead(scout)==HIGH && digitalRead(sensor4)==HIGH && digitalRead(sensor5)==HIGH && digitalRead(sensor6)==HIGH){
		if(digitalRead(sensor1)==HIGH && digitalRead(sensor2)==HIGH && digitalRead(sensor3)==HIGH && digitalRead(sensor7)==HIGH && digitalRead(sensor8)==HIGH && digitalRead(sensor9)==HIGH){
			matrix[row][column]=1;
			row++;
		}
		else if(digitalRead(sensor1)==LOW && digitalRead(sensor2)==LOW && digitalRead(sensor3)==LOW && digitalRead(sensor7)==LOW && digitalRead(sensor8)==LOW && digitalRead(sensor9)==LOW){
			matrix[row][column]=0;
			row++;
	    }
		moveForward(FAST_PWM,FAST_PWM);
	}
		else if(digitalRead(scout)==LOW && digitalRead(sensor4)==HIGH && digitalRead(sensor5)==HIGH && digitalRead(sensor6)==HIGH){
			if(digitalRead(sensor1)==LOW && digitalRead(sensor2)==LOW && digitalRead(sensor3)==HIGH && digitalRead(sensor7)==HIGH && digitalRead(sensor8)==HIGH && digitalRead(sensor9)==HIGH){

			}
		}
	*/	 




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
	digitalWrite(Motor_Left_Forward,HIGH);
	digitalWrite(Mortor_Left_Reverse,HIGH);
	//analogWrite(Motor_Left_Enable,0);
}

void motorRight_stop(){
	digitalWrite(Motor_Right_Forward,HIGH);
	digitalWrite(Motor_Right_Reverse,HIGH);
	//analogWrite(Motor_Right_Enable,0);
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

void serialTest(){
	for(int counter=0; counter<5; counter++){
		Serial.write("Test");
	}
}