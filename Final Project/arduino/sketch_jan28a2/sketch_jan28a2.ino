// MASTER
#include <LiquidCrystal.h>
#include <Keypad.h>
#include<SPI.h>
#include<Wire.h>

# define ADDRESS 0b1010000
# define buzzer 0

# define LED_1 1
# define LED_2 2
# define LED_3 3
# define LED_4 4

# define RS_PIN 13
# define EN_PIN 12
# define D4_PIN 8
# define D5_PIN 9
# define D6_PIN 10
# define D7_PIN 11




LiquidCrystal LCD(RS_PIN, EN_PIN, D4_PIN, D5_PIN, D6_PIN, D7_PIN);

char keys[4][3] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte pin_rows[4] = {22, 23, 24, 25}; //connect to the row pinouts of the keypad
byte pin_columns[3] = {26, 27, 28}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_columns, 4, 3);


void setup() {
  // put your setup code here, to run once:
 
  LCD.begin(16, 2);
  LCD.clear();
  LCD.setCursor(0, 0);

  pinMode(buzzer, OUTPUT);
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  
  pinMode(14, OUTPUT);//ss1
  pinMode(15, OUTPUT);//ss2
  pinMode(16, OUTPUT);//ss3
  pinMode(17, OUTPUT);//ss4
  
  digitalWrite(14, HIGH);
  digitalWrite(15, HIGH);
  digitalWrite(16, HIGH);
  digitalWrite(17, HIGH);
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8);

  Wire.begin();
  
}


char slave_1;
char slave_2;
char slave_3;
char slave_4;

char savingData[7];

void loop(){

  Wire.beginTransmission(ADDRESS);
  Wire.write(0x00);
  Wire.write(0xAA);
  Wire.endTransmission();
  Wire.requestFrom(ADDRESS, 4);
  char data_1 = Wire.read();
  char data_2 = Wire.read();
  char data_3 = Wire.read();
  char data_4 = Wire.read();

  delay(200);
  
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("last election:");
  LCD.setCursor(0, 1);
  LCD.print(data_1);
  LCD.print("\t");
  LCD.print(data_2);
  LCD.print("\t");
  LCD.print(data_3);
  LCD.print("\t");
  LCD.print(data_4);
  
  // start getting votes via SPI
  digitalWrite(14, LOW);
  delay(500);
  LCD.clear();
  LCD.setCursor(0, 0);
  slave_1 =  SPI.transfer(0);
  digitalWrite(14, HIGH);
  LCD.print("slave 1 Done");
  LCD.setCursor(0, 1);
  LCD.print(slave_1);
  delay(100);
  LCD.clear();
  LCD.setCursor(0, 0);
  digitalWrite(LED_1, HIGH);
  
  //slave_1 done
  //============================
  digitalWrite(15, LOW);
  delay(500);
  slave_2 =  SPI.transfer(0);
  digitalWrite(15, HIGH);
  LCD.print("slave 2 Done");
  LCD.setCursor(0, 1);
  LCD.print(slave_2);
  delay(100);
  LCD.clear();
  LCD.setCursor(0, 0);
  digitalWrite(LED_2, HIGH);
  //slave_2 done
  //============================
  digitalWrite(16, LOW);
  delay(500);
  slave_3 =  SPI.transfer(0);
  digitalWrite(16, HIGH);
  LCD.print("slave 3 Done");
  LCD.setCursor(0, 1);
  LCD.print(slave_3);
  delay(100);
  LCD.clear();
  LCD.setCursor(0, 0);
  digitalWrite(LED_3, HIGH);
  //slave_3 done
  //============================
  digitalWrite(17, LOW);
  delay(500);
  slave_4 =  SPI.transfer(0);
  digitalWrite(17, HIGH);
  LCD.print("slave 4 Done");
  LCD.setCursor(0, 1);
  LCD.print(slave_4);
  delay(100);
  LCD.clear();
  LCD.setCursor(0, 0);
  digitalWrite(LED_4, HIGH);
  //slave_4 done
  //============================
  
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("Votes:");
  LCD.setCursor(0, 1);
  LCD.print(slave_1);
  LCD.print(slave_2);
  LCD.print(slave_3);
  LCD.print(slave_4);
  delay(200);

  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("saving");
  
  tone(buzzer, 1000);
  delay(100);
  noTone(buzzer);


  Wire.beginTransmission(ADDRESS);
  Wire.write(0x00);
  Wire.write(0xAA);
  Wire.write(slave_1);
  delay(50);
  Wire.write(slave_2);
  delay(50);
  Wire.write(slave_3);
  delay(50);
  Wire.write(slave_4);
  delay(50);
  Wire.endTransmission();
  delay(1000);
  LCD.clear();
  LCD.setCursor(0, 0);

  //delay(100);
  
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("DONE!");
  delay(200);
}
