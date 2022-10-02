#include "pitches.h"
//#include "jingle_bells.h"
//#include "ode_to_joy.h"
#include "imperial_march.h"
//#include "ey_iran.h"

float scale = 0;

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int note = 0; note < sizeof(melody)/sizeof(int); note++){
    scale = analogRead(A0)/512.0;
    int note_duration = 800/noteDurations[note];
    tone(8, (int)(melody[note]*scale), note_duration);
    delay((int)(note_duration * 1.3));
  }
}
