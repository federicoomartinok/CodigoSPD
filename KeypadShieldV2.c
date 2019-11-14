#define BTN_RIGHT  0
#define BTN_UP     1
#define BTN_DOWN   2
#define BTN_LEFT   3
#define BTN_SELECT 4
#define BTN_NONE   5

#define STATE_CONFIG 0
#define STATE_CLOCK  1

//La funcion readButton tiene que devolver en qué
//estado está la botonera.

int readButton(){
	int value = analogRead(A0);
	if(value<72)
		return BTN_RIGHT;
	if(value<237)
		return BTN_UP;
	if(value<419)
		return BTN_DOWN;
	if(value<625)
		return BTN_LEFT;
	if(value<882)
		return BTN_SELECT;
	return BTN_NONE;
}

LiquidCrystal lcd(8,9,4,5,6,7);
int state = STATE_CONFIG;
void setup(){
	Serial.begin(9600);
	lcd.begin(16,2);
	lcd.print("00:00");
	lcd.setCursor(0,1);
	lcd.print("^");
}

int pos = 0;
int previousButton = BTN_NONE;
void loop(){
	switch(state){
		case STATE_CONFIG:
		stateConfig();
		break;
		case STATE_CLOCK:
		stateClock();
		break;
	}
		
	
}

void stateConfig(){
	int button = readButton();
	if(previousButton == BTN_NONE && button != BTN_NONE){
		switch(button){
			case BTN_RIGHT:
			setCursor(pos, 1);
			lcd.print(" ");
			if(pos==1)
				pos+=2;
			else if(pos==4)
				pos=0;
			else
				pos++;
			setCursor(pos, 1);
			lcd.print("^");
			break;
			case BTN_LEFT:
			// PONGAN ACÁ EL CÓDIGO PARA QUE VAYA A LA IZQUIERDA. 
			break;
			case BTN_SELECT:
			state = STATE_CLOCK;
		}
	}
	previousButton = button;
}

void stateClock(){
	
}