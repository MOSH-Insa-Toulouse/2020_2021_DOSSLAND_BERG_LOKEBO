// v5 : implement gas sensor, send to gateway, with interrupt
#include <avr/interrupt.h>
#include <SoftwareSerial.h>
#include "analogComp.h"
#define ledPin 13
int luminosity;
int reference;

SoftwareSerial mySerial(10,11);
char response;
volatile int compteur = 0;
void isr()
{
   compteur++;
   digitalWrite(ledPin, HIGH);
}
void setup() {
  
  // put your setup code here, to run once:
  //pinMode(AIN0,INPUT);
  //pinMode(A1, INPUT);
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("Begin v5");

  String data = "";

  mySerial.begin(9600);


    
    Serial.println("Interrupt set");
    analogComparator.setOn(AIN0, A1);
    analogComparator.enableInterrupt(isr, CHANGE);
    Serial.println("Interrupt set fin");

    digitalWrite(ledPin, HIGH);
    delay(500);
    digitalWrite(ledPin, LOW);


   
  
// sys get vdd
  response = ' ';

  
  mySerial.print("sys get vdd");
  mySerial.print('\r');
  mySerial.print('\n');
  while(mySerial.available()>0)
  {
    response = mySerial.read();
    Serial.print(response);
  }

//initialize radio
//reset rn2483
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  delay(500);
  digitalWrite(12, HIGH);

  delay(100); //wait for the RN2xx3's startup message
  mySerial.flush();

//check communication with radio

// reset mac
  mySerial.println("mac reset 868");
  delay(500);

// set app id
  mySerial.println("mac set appeui 70B3D57ED0038A94");
  delay(500);

  // get id of app
  response = ' ';
  
  
  mySerial.println("mac get appeui");
  while(mySerial.available()>0)
  {
    response = mySerial.read();
    Serial.print(response);
  }
 
  delay(500);

// connection en mode abp
  response = ' ';
  mySerial.println("mac resume");
  delay(500);

  // set app session key
  mySerial.println("mac set devaddr 260139A7");
  delay(500);

  // set network session key
  mySerial.println("mac set nwkskey F4C3880066673F71706FD83CF401BBA2");
  delay(500);
  
  // set app session key
  mySerial.println("mac set appskey 3A8AF9D1DDBD5C250D327B260D94FF02");
  delay(500);

  

  

  mySerial.println("mac join abp");
  while(mySerial.available()>0)
  {
    response = mySerial.read();
    Serial.print(response);
  }
 
  delay(500);




}

void loop() {
  // put your main code here, to run repeatedly:

  

  // mac tx
  response = ' ';

float  gas;
gas = analogRead(A1);
reference = analogRead(AIN0);
float ref_volt;
float voltage;
ref_volt = reference/1024*5.0;
voltage = gas/1024*5.0;
  
  Serial.print("voltage = ");
  Serial.println(voltage);
  Serial.print("compteur = ");
  Serial.println(compteur);
  Serial.print("gas = ");
  Serial.println(gas);
  Serial.print("reference = ");
  Serial.println(reference);
  Serial.print("refvolt = ");
  Serial.println(ref_volt);
  if(luminosity < 500)
  {
    Serial.println("luminosity < 500");
    mySerial.print("mac tx uncnf 1 ");
    mySerial.println(luminosity);
  }
  while(mySerial.available()>0)
  {
    response = mySerial.read();
    Serial.print(response);
  }
 
  delay(1000);

  



  
  /*if (mySerial.available())
    Serial.write(mySerial.read());
   if (Serial.available())
    mySerial.write(Serial.read());
    */
}
