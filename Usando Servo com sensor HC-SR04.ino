#include <HCSR04.h>

#include <Servo.h>

#define p_servo 10

#define p_trigger 9
#define p_echo 8

Servo servo;



int velocidade;
float dist_cm;


void setup() 
{
  velocidade = 128;
  servo.attach(10);
 
}
void loop()
{
  servo.write(0);
  delay(1000);
  servo.write(180);
  delay(1000);

}
