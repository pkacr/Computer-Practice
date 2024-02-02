#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("LCD ON");
  lcd.setCursor(1,1);
  lcd.print("Press to start ");

  Wire.beginTransmission(0x21);
  Wire.write(0x06);
  Wire.write(0xE0);
  Wire.endTransmission();
  Serial.begin(115200);

   Wire.beginTransmission(0x21);
  Wire.write(0x00);
  Wire.write(0xE0);
  Wire.endTransmission();
  Serial.begin(115200);
  numwrite(0x00);
  
}
bool x =false;
bool y=false;
char num[]={0x02,0x04,0x08,0x10};
int i=0;

void loop() {
   
 
  if((readsw(0x21)&0x20)==0){
    while((readsw(0x21)&0x20)==0);
  if(x==false){
  lcd.init();
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("LED :)");
  lcd.setCursor(4,1);
  lcd.print("RUNNING!");
  x=true;
  }else{lcd.init();
  lcd.backlight();
  lcd.setCursor(5,0);
  lcd.print("LED :(");
  lcd.setCursor(6,1);
  lcd.print("STOP");
  x=false;}
  }
 if((readsw(0x21)&0x40)==0){
    while((readsw(0x21)&0x40)==0);
       if(y==false){
        lcd.init();
        lcd.backlight();
        lcd.setCursor(5,0);
        lcd.print("LED :)");
        lcd.setCursor(5,1);
        lcd.print("BLINK!");
        y=true; 
        
        }else{
          lcd.init();
          lcd.backlight();
          lcd.setCursor(5,0);
          lcd.print("LED :(");
          lcd.setCursor(6,1);
          lcd.print("STOP");
          y=false;}
      
    }
    if((readsw(0x21)&0x80)==0){
    while((readsw(0x21)&0x80)==0);
          lcd.init();
          lcd.backlight();
          lcd.setCursor(5,0);
          lcd.print("LED ON");
          lcd.setCursor(1,1);
          lcd.print("Press to start");
          numwrite(0x00);
          delay (100);
          x=false;
          y=false;
    }
    

 if(x==true){
    if(i<4){
      numwrite(num[i]);
      i++;
      delay(100);
  }else i=0;
 }

 if(y==true){
    numwrite(0x1E);
    delay (100);
    numwrite(0x00);
    delay (100);
 }else{y=false;}
 
}









void numwrite(char num){
  Wire.beginTransmission(0x21);
  Wire.write(0x09);
  Wire.write(num);
  Wire.endTransmission();
}
unsigned char readsw(char address){
  Wire.beginTransmission(address);
  Wire.write(0x09);
  Wire.endTransmission();
  Wire.requestFrom(address,1);
  return(Wire.read());
  }
