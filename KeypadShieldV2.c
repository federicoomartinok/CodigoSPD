#define BTN_RIGHT  0
#define BTN_UP     1
#define BTN_DOWN   2
#define BTN_LEFT   3
#define BTN_SELECT 4
#define BTN_NONE   5
#include <LiquidCrystal.h>

#define STATE_CONFIG 0
#define STATE_CLOCK  1

//LiquidCrystal lcd(8,9,4,5,6,7);
LiquidCrystal lcd(4,5,6,7,8,9);

// funcion que devuelve el estado de la botonera
int readButton()
{

  int value = analogRead(A0);
  if(value<72)
    return BTN_RIGHT;
  if(value<237)
    return BTN_UP;
  if(value<419)
    return BTN_DOWN;
  if(value<625)
    return BTN_LEFT;
  if(value<883)
    return BTN_SELECT;
  return BTN_NONE;

}

void setup() 
{
    lcd.begin(16,2);
    Serial.begin(9600);
    lcd.print("00:00");
}

int estado;
int flag = 1;
int lugar = 0;
int minutos=0;
int segundos=0;
int tiempoTotal = 0;
long t;
int state = STATE_CONFIG;

void loop() 
{

  switch(state)
  {
	case STATE_CONFIG:  
    estadoConfig();
    break;
	case STATE_CLOCK:
	estadoClock();
  }
  
lcd.setCursor(0, 0);
// para el simulador se pone el delay
delay (50);
}


void estadoConfig()
{
  
   estado = readButton();
   
  switch(estado)
  {
    case BTN_RIGHT:
        if(estado == BTN_RIGHT && flag)
        {
            if(lugar < 4)
            {
              lugar++;
              if(lugar == 2)
              {
                lugar++;
                lcd.setCursor(1,1);
                lcd.print(" ");
              }
              lcd.setCursor(lugar-1,1);
              lcd.print(" ^");
            }
            flag = 0;
        }
     break;
    
    case BTN_UP:
     if(estado == BTN_UP && flag)
    {
     switch(lugar)
     {
      case 0:
     
      minutos += 10;
      if(minutos>99)
      {
        minutos=0;
        }
       
      break;
      
      case 1:

      
        minutos++;
        if(minutos>99)
      {
        minutos=0;
        }
        
  
      break;
      case 3:
      segundos += 10;
      if(segundos>59)
      {
        segundos=0;
        }
      

      break;
      case 4:
      segundos++;
      if(segundos>59)
      {
        segundos=0;
        }

      break;
      
      }
    flag=0;

    if(minutos<10)
    {
      lcd.setCursor(0,0);
      lcd.print(0);
      lcd.setCursor(1,0);
     lcd.print(minutos);
    }else
    {
     lcd.setCursor(0,0);
     lcd.print(minutos);
    }

  if(segundos<10)
  {
    lcd.setCursor(3,0);
      lcd.print(0);
     lcd.setCursor(4,0);
     lcd.print(segundos);
  } else
  {
    lcd.setCursor(3,0);
     lcd.print(segundos);
  }
  

    }
    
    break;
    case BTN_DOWN:
    if(estado == BTN_DOWN && flag)
    {
     switch(lugar)
     {
      case 0:
      minutos -= 10;
      if(minutos<0)
      {
        minutos=99;
        }
      
        break;
      case 1:
        minutos--;
        if(minutos<0)
      {
        minutos=99;
        }

  
      break;
      case 3:
      segundos -=10;
      if(segundos<0)
      {
        segundos=59;
        }
      break;
      case 4:
      segundos--;
      if(segundos<0)
      {
        segundos=59;
        }
 
      break;
      
      }
    flag=0;
     if(minutos<10)
    {
      lcd.setCursor(0,0);
      lcd.print(0);
      lcd.setCursor(1,0);
     lcd.print(minutos);
    }else
    {
     lcd.setCursor(0,0);
     lcd.print(minutos);
    }

  if(segundos<10)
  {
    lcd.setCursor(3,0);
      lcd.print(0);
     lcd.setCursor(4,0);
     lcd.print(segundos);
  } else
  {
    lcd.setCursor(3,0);
     lcd.print(segundos);
  }

    }
    break;
    case BTN_LEFT:
    if(estado == BTN_LEFT && flag)
    {
        
        
        if(lugar > 0)
        {
          lugar--;
          if(lugar == 2)
          {
            lcd.setCursor(3,1);
            lcd.print(" ");
            lugar--;
          }
          lcd.setCursor(lugar,1);
          lcd.print("^ ");
        }
        flag = 0;
    }
    break;
    case BTN_SELECT:
     state=STATE_CLOCK;
	 
	 tiempoTotal = (minutos*60)+segundos;
	 t = millis();
	 //tiempoTotal = tiempoTotal/60;	 
    break;
    case BTN_NONE:
    lcd.setCursor(lugar,1);
    lcd.print("^");
    flag = 1;
    break;
    default:
    break;
    }
  
}

void estadoClock ()
{
	long tActual = millis();
	
	if(tActual - t >= 1000){
		tiempoTotal--;
	//Mostrar en la pantalla el tiempo total que queda	
		
	lcd.setCursor(0,0);	
	int minutes = tiempoTotal/60;
	int seconds = tiempoTotal%60;
	char bomb[10];	
	sprintf(bomb,"%02d:%02d",minutes,seconds);
		lcd.print(bomb);
	
	if (tiempoTotal == 0)
	{
		//Vuelvo al estado config
		state=STATE_CONFIG;	
		
	}
	
	t=tActual;
	
	}
}


//https://www.tinkercad.com/things/1Avob3JM2LK-display-lcd-botones
