#include <Servo.h> 
int servoPin1 = 9;
int servoPin2 = 10;
Servo servo1; 
Servo servo2; 

int min_value = 547;
int max_value = 2400;

void setup() 


{ 

 Serial.begin(9600); // 
 //servo1.attach(servoPin1);
 servo1.attach(servoPin1,min_value,max_value); 
  servo2.attach(servoPin2); 

} 

void loop() 

{ 

 int max;
 int val; 

  max = -1;
 val=analogRead(0);//Connect the sensor to analog pin 0 
Serial.println(val,DEC);// 
 

if(val > 10){
  while(val!=0){
  if(max <= val){
    max = val;
    Serial.println(max);
  }
     val=analogRead(0);//Connect the sensor to analog pin 0 
  }
}

   Serial.print("max: ");// 
   Serial.println(max,DEC);// 




if(max > 0){
    Serial.print("finmax: ");// 
    Serial.println(max,DEC);// 

if(max>=200){
  Serial.println(max,DEC);// 
  Serial.println("glass");//

   delay(1000);
   servo1.write(170); 
   delay(20);
  
}else if (max >= 40){
   Serial.println(max,DEC);// 
   Serial.println("plastic");//
    delay(1000);
    servo1.write(90);  
    delay(20);
}else if (max >= 5  ){
  Serial.println(max,DEC);// 
  Serial.println("etc");//
servo1.write(20); 
delay(1000); 
}

delay(2000);
servo2.write(0);
delay(2000);
servo2.write(50);
delay(2000);
//servo1.write(10); 
//delay(2000);
servo1.write(20); 
delay(2000);
}


} 
