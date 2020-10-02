unsigned long startTime;
unsigned long startTime_1;
unsigned long elapsedTime;
int flag = 0;
unsigned long elapsedTime_1;
unsigned long currentTime;
float microFarads, Resistance1 = 10000000;             // floating point variable to preserve precision, make calculations
float Resistance2 = 1000;
float nanoFarads;

/////////////////////////////////////////////////////////
float test, test1, Ana1, Ana2, resistance;
///////////////////////////////////////////////////////
#include <LiquidCrystal.h>

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
////////////////////////////////////////////////////////////
void setup()
{
  
  pinMode(13, OUTPUT);     // set chargePin to output
  pinMode(11, OUTPUT);
  pinMode(12, INPUT);
    pinMode(8, INPUT);
  pinMode(10, INPUT);

  digitalWrite(13, LOW);
  digitalWrite(12, LOW);
  digitalWrite(11, LOW);
  lcd.begin(16, 2);
  Serial.begin(9600);             // initialize serial transmission for debugging
  lcd.clear();
}
//////////////////////////////////////////////////////////////////////////////
void new_charge()
{
  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  startTime_1 = micros();
  while (analogRead(A0) < 648);

  elapsedTime_1 = micros() - startTime_1;


  microFarads = ((unsigned long)elapsedTime_1 / Resistance2 );
  Serial.print(microFarads, 6);          // print the value to serial port
  Serial.println(" microFarads");        // print units and carriage return
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(microFarads);
    lcd.setCursor(8, 1);
    lcd.print("uF");
   




}
///////////////////////////////////////////////////////////////////////////////
void capacitor()
{
  pinMode(11, INPUT);
  digitalWrite(13, HIGH);  // set chargePin HIGH and capacitor charging

  startTime = micros();

  while (analogRead(A0) < 647)
  {
    currentTime = micros() - startTime;

    if (currentTime > 1000000)
    {
      pinMode(13, INPUT);
      new_charge();
      flag = 1;
    }
  }

  if (flag != 1)
  {
    elapsedTime = micros() - startTime;
    microFarads = ((unsigned long)elapsedTime / Resistance1) * 1000;
    Serial.print(microFarads, 6);                        // print the value to serial port
    Serial.println(" nanoFarads");                       // print units and carriage return
     lcd.clear();
    lcd.setCursor(0,1);
    lcd.print(microFarads);
    lcd.setCursor(8, 1);
    lcd.print("nF");
   
    nanoFarads = 0;
    microFarads = 0;
  }

  digitalWrite(13, LOW);                               // set charge pin to  LOW
  digitalWrite(11, LOW);
  pinMode(12, OUTPUT);                                 // set discharge pin to output
  digitalWrite(12, LOW);                               // set discharge pin LOW
  while (analogRead(A0) > 0) {}                        // wait until capacitor is completely discharged }
  pinMode(12, INPUT);                                  // set discharge pin back to input
  flag = 0;

}

//////////////////////////////////////////////////////////////////
void resistor()
{
  Ana1 = analogRead(A4);
  Ana2 = analogRead(A5);
  test = (Ana1 * 5) / 1023;
  test1 = (Ana2 * 5) / 1023;

   
  if (test > 0)
  {
    if (test > 0.40)
    {
      resistance = 100 * ((5.0 / test) - 1.0);
      //Serial.println(resistance);
     lcd.clear();
    lcd.setCursor(1,0);
    lcd.print(resistance);
    lcd.setCursor(8, 0);
    lcd.print("Ohms");
  delay(10);
    }
    else
    {
      //Serial.println("Out of range");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("out of range");
    }
  }
  else if (test1 > 0)
  {
    if (test1 > 0.23 && test1 < 4.95)
    {
      resistance = 100000 * ((5.0 / test1) - 1.0);
      //Serial.println(resistance);
   
    lcd.clear();     
    lcd.setCursor(1,0);
    lcd.print(resistance);
    lcd.setCursor(8, 0);
    lcd.print("Ohms");
  delay(10);
    }
    else
    {
       lcd.clear();
      lcd.setCursor(1, 0);
    //  Serial.println("Out of Range");
      lcd.print("Out of Range");
    }
  }


}
/////////////////////////////////////////////////////////////////
void loop()
{
  pinMode(10,INPUT);
  pinMode(8,INPUT);
if(digitalRead(8)==0)
  {
pinMode(8,OUTPUT); 
digitalWrite(8,HIGH);
capacitor();
  }
else if(digitalRead(10)==0)
{
 pinMode(10,OUTPUT);
 digitalWrite(10,HIGH); 
  resistor();
}

  
else
{
  lcd.clear();
}
}
