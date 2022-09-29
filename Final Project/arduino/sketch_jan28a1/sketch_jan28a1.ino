// SLAVE
#include <LiquidCrystal.h>
#include <Keypad.h>
#include<SPI.h>

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


bool processed = false;
void setup() {
  // put your setup code here, to run once:
 
  LCD.begin(16, 2);
  LCD.clear();
  LCD.setCursor(0, 0);
  
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT_PULLUP);
  pinMode(MOSI, INPUT);
  pinMode(MISO, OUTPUT);

  SPCR |= _BV(SPE);
  SPI.attachInterrupt();
}

ISR (SPI_STC_vect)
{
  processed = true;
} 


void loop(){
  LCD.clear();
  LCD.setCursor(0, 0);
  LCD.print("press to start:");
  char startingKey = keypad.waitForKey();
  if (startingKey == '#'){
    LCD.clear();
    LCD.setCursor(0, 0);
    char vote = keypad.waitForKey();
    while(!(vote == '0' || vote == '1')){
      LCD.clear();
      LCD.setCursor(0, 0);
      LCD.print("Enter 1 or 0 To");
      LCD.setCursor(0, 1);
      LCD.print("Like or Disslike");
      vote = keypad.waitForKey();
    }
    LCD.clear();
    LCD.setCursor(0, 0);
    LCD.print("my vote is:");
    LCD.setCursor(0, 1);
    LCD.print(vote);
    while(1){
      char x = keypad.getKey();
      if(isDigit(x)){
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("You Can't Vote");
        delay(2000);
        LCD.clear();
        LCD.setCursor(0, 0);
        LCD.print("my vote is:");
        LCD.setCursor(0, 1);
        LCD.print(vote);
      }
    }
    SPI.transfer(vote);
    processed = false;
    LCD.clear();
  }
}
