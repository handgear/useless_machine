#include <Servo.h>
#define OFF false
#define ON true
#define SERVO_PIN 9
#define SW_PIN 2 //interrupt pin is 2,3 (int.0, int.1)
#define INIT_POS 90 //off position //angle
#define ON_POS 115
#define NOT_HIT_POS 110 //position which dosn't hit the switch
#define DELAY_HIT 300
#define DELAY_INTERVAL 7 //delay between 1degree
#define TOTAL_MODE_NUM 2 //change this number after all modes are complete

Servo servo1;

int pos = INIT_POS;
int init_check = 0;
bool switch_state = OFF;
int mode_num;

void setup(){
	Serial.begin(9600);
	randomSeed(analogRead(0));
	servo1.attach(SERVO_PIN);
	pinMode(SW_PIN, INPUT_PULLUP);
	attachInterrupt(0, switch_update, CHANGE);
	delay(1000);//stablize
	pos = INIT_POS;
	servo1.write(pos);
	
}

void loop(){

	switch_state = digitalRead(SW_PIN);
	initialize();
	//random mode
	mode_num = random(1000);
	Serial.println(mode_num);
	delay(500);
	
	 if(mode_num < 700){
	 	Serial.println("1======");
	 	case_simple();
	 }
	 else if(mode_num >= 700 && mode_num < 800){
	 	Serial.println("2======");
	 	case_wait();
	 }	
	 else if(mode_num >=800 && mode_num < 900){
	 	case_notTurningOff();
	 	Serial.println("3======");
	 }
	 else if(mode_num >=900 && mode_num <1000){
	 	case_TurningOnLater();
	 	Serial.println("4======");
	 }
	//debuging mode
  	// case_simple();
	// case_wait();
	// case_notTurningOff();
	// case_TurningOnLater();

}
void switch_update(){
	switch_state = digitalRead(SW_PIN);
}
void initialize(){
	if(init_check == 0){
		delay(1000);
		servo1.write(INIT_POS);
		init_check = 1;	
	}
	
}
void case_simple(){//slow on, slow off
	while(true){
		if(pos < ON_POS && switch_state == ON){
		pos += 1;
		servo1.write(pos);
		delay(DELAY_INTERVAL);
		}
		if(pos > INIT_POS && switch_state == OFF){
		pos -= 1;
		servo1.write(pos);
		delay(DELAY_INTERVAL);
		}
		if(pos == INIT_POS){ //pos == ON_POS ||
			break;
		}
	}
}
void case_wait(){
	if(switch_state == ON){
		delay(2000);
		case_simple();
	}
	else
		case_simple();
}
void case_notTurningOff(){
	while(true){
		if(pos < NOT_HIT_POS && switch_state == ON){
		pos += 1;
		servo1.write(pos);
		delay(15);
		}
		if(pos == NOT_HIT_POS){
			break;
		}
	}
	while(true){
		if(pos > INIT_POS && switch_state == ON){
		pos -= 1;
		servo1.write(pos);
		delay(DELAY_INTERVAL);
		}
		if(pos == INIT_POS){
			break;
		}
	}
}
void case_TurningOnLater(){
	while(true){
		if(pos < NOT_HIT_POS && switch_state == ON){
		pos += 1;
		servo1.write(pos);
		delay(DELAY_INTERVAL);
		}
		if(pos == NOT_HIT_POS){
			break;
		}
	}
	delay(1000);
	case_simple();
}
