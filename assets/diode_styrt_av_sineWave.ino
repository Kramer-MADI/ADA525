#include <Wire.h>
#include <Adafruit_MCP23008.h>

unsigned long         currentTime;
unsigned long         prevTime = 0;
float                 analogValueNow;
float                 analogValuePrev;
int                   n = 0;
int                   j = 0;
int                   k = 2;


void setup() {
  Serial.begin(230400);                     // Baudrate 230400
  ADCSRA &= ~((1 << ADPS1) | (1 << ADPS0)); // For faster analog reads

  pinMode(13, OUTPUT);
 
}

void loop() {
  currentTime = micros();

  if (n == 0)
  {
    
  analogValueNow = analogRead(A0);
  analogValuePrev = analogValuePrev;

  prevTime = currentTime;
  n++;
  
  }

  if ((currentTime - prevTime) >= 50000 && n == 1) //20samples pr. periode
  {
    analogValueNow = analogRead(A0);
    
    if(analogValueNow > analogValuePrev && analogValuePrev < 512)
    {
      n++;
    }
    else
    {
      n = 0;
    }
    
    prevTime = currentTime;
  }


  if ((currentTime - prevTime) >= 50000 && n == 2)
  {
    analogValueNow = analogRead(A0);
    //Serial.println(analogValueNow);
    
    if(analogValueNow > 512 && j == 0)
    {
      j++;
    }
    if(analogValueNow < 512 && j == 1)
    {
      j++;
    }
    if(analogValueNow >= 512 && j == 2)
    {
      j=0;
      k++;
    }
    
    if(k % 2 == 0)
    {
      //Serial.println(k);
      digitalWrite(13,HIGH);
    }
    else
    {
      digitalWrite(13,LOW);
    }
    
    prevTime = currentTime;
    
  }

}
