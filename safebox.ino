#include<EEPROM.h>
#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
//servo at 9
LiquidCrystal lcd(1, 2, 4, 5, 6, 7); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7) 
#include <Servo.h>
Servo servo;

  String name1="null",name2="null",name3="null";
  int lenght=0,i=0,index=0;
  int get_string_lenght(String);
  int  answer(String);
  void save_password();
  void close_safe_box(int);
  void check_the_answer();
  void start();
void setup() 
{
  // put your setup code here, to run once:
   Serial.begin(9600);
   lcd.begin(16,2); 
   servo.attach(9);
   servo.write(0);
   pinMode(0,INPUT);
   pinMode(1,OUTPUT);
   start();
   save_password();   
   Serial.println("enter the password in four digit");
   lcd.print("enter the pass");
}
void loop() 
{
   //int x=EEPROM.read(0);
    delay(1000);
  while(Serial.available()==0);
  name3=Serial.readString();
  int ans=answer(name3);
  check_the_answer(ans);
}

/*This function take no parametar and didnot return value
  this function check whether there is a saved password on eeprom or not   */
void save_password()
{ 
  //EEPROM.write(1,0);
    if(EEPROM.read(1)==0)
    {
    Serial.println("Enter new pass in four digit");
    while(Serial.available()==0);
        
      name1=Serial.readString();
      lenght=get_string_lenght(name1);
       if(lenght==4)
       {
          for(i=0;i<4;i++)
          {
            EEPROM.write(index+i,name1[i]);
          } 
       }else
       {
        
          Serial.println("password in four digit,please");
          save_password();
       }   
  }
}
/*This function take no parametar and return value
  this function make a comparison between the saved password and the Entered password*/
int  answer(String name33)
{  
    int z=0;

  /*delay(1000);
  while(Serial.available()==0);
  name3=Serial.readString();*/
  for(i=0;i<4;i++)
  {
    name2[i]=EEPROM.read(i);
  }
  int L=get_string_lenght(name33);
  for(int i=0;i<(L);i++) 
   {
     if(name2[i]==name33[i])
      {
          z++;
      }else
      {
          z--;       
      }
    }
    return z;
 
}
/*This function take one parametar and return value
  it return number of character in a string*/
int get_string_lenght(String name1)
{
  int i=0,lenght=0;
  while(name1[i] !='\0')
  {
    lenght++;
    i++;
  }
  return lenght;
}
/*This function take one parametar and didnot return value
  it take an integer and check check if that integer is the correct answer or not */
void check_the_answer(int answer)
{
   if(answer==4)
    {
       Serial.println("done");
       lcd.print("Right password");
       delay(2000); // 3 seconds delay 
       lcd.setCursor(2,1);
       //servo on
       servo.write(90); //here safe box is opend and i need to close it
       lcd.print("Safe box is opened ");
       //delay(3000);
       close_safe_box(); //this function to close safe box and the code cannot be continued whether the safebox closed
       delay(200);
       Serial.println("enter the password in four digit");
       lcd.print("enter the pass");
 
     }
     else
     {
         Serial.println("notdone");
         lcd.print("Wrong password");
        // delay(2000); // 3 seconds delay 
         lcd.setCursor(2,1);
         lcd.print("cannot open Safe box");
        // delay(3000);
         change_password();
         Serial.println("enter the password in four digit");
         lcd.print("enter the pass");
 
     }
}
/*this function didnot take parametar and didnot return vlue
  it to get the answer from user to close the safe box*/
void close_safe_box()
{
       int x=0;
       Serial.println("send y to close safebox");
       while(Serial.available()==0);
       x=Serial.read();
       if(x=='y')
       {
          //SERVO OFF
          servo.write(0);
          lcd.clear();
         // delay(5000);
          lcd.setCursor(1,1);
          Serial.println("Safebox closed");
          lcd.print("Safe box closed");
          
       }else if(x!='y')
       {
          x=5;
          lcd.clear();
          //delay(5000);
          lcd.setCursor(1,1);
          Serial.println("safe box still opened"); 
          close_safe_box();
       }
}
void change_password()
{
  int G=0,remeber_answer=0;
  String remember_password="null";
  Serial.println("If you want change the password send G");
  Serial.println("OR If you wantnot change the password send N");
  
  while(Serial.available()==0);
  G=Serial.read();
  if(G=='G')
  {
   Serial.println("Enter the password you remebmer ");
   while(Serial.available()==0);
   remember_password=Serial.readString();
   remeber_answer=answer(remember_password);
   if(remeber_answer ==2 || remeber_answer ==4)
    {
      Serial.println("now you can change the password");
      EEPROM.write(0,0);
      EEPROM.write(1,0);
      EEPROM.write(2,0);
      EEPROM.write(3,0);
      EEPROM.write(4,0);
      save_password();
    }else
    {
      Serial.println("Please,remember well");
      change_password(); 
    }
  }else if(G=='N')
    {
      
    }else
    {
      change_password();
    }
}

void start()
{
  int x;
  while(Serial.available()==0);
  x=Serial.read();
}
