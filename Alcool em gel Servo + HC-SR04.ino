#include <HCSR04.h>

#include <Servo.h>

#define pservo1 2

#define p_trigger 12
#define p_echo 11

Servo servo1;
Servo servo2;


int velocidade;
float dist_cm;


void setup() 
{
  velocidade=128;
  servo1.attach(2);

}
void loop()
{
  servo1.write(180);

  delay(1000);
  servo1.write(180);

  delay(1000);
}
