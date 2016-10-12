/******************************************************
An open-source binary clock for Arduino.

Customized by Justin Rains

Web: http://justinrains.com
GitHub: https://github.com/justinrains/binary-clock

******************************************************/

int second=0, minute=0, hour=0; //start the time on 00:00:00
int munit = 0;
int hunit = 0;
int valm=0;
int valh=0;
int ledstats = 0;
int i= 0;
boolean light = 1;

void setup() { //set outputs and inputs
  Serial.begin(9600); // for debugging

  pinMode(2, OUTPUT); //sb1
  pinMode(3, OUTPUT); //sb2
  pinMode(4, OUTPUT); //sb3
  pinMode(5, OUTPUT); //sb4
  pinMode(6, OUTPUT); //sa1
  pinMode(7, OUTPUT); //sa2
  pinMode(8, OUTPUT); //sa3
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  
  pinMode(14, INPUT);
  pinMode(18, INPUT);
  pinMode(19, INPUT);

  digitalWrite(14, HIGH);
  digitalWrite(18, HIGH);
  digitalWrite(19, HIGH);
}


void loop() {
  static unsigned long lastTick = 0; // set up a local variable to hold the last time we moved forward one second
  // (static variables are initialized once and keep their values between function calls)
  // move forward one second every 1000 milliseconds
  
  if (millis() - lastTick >= 1000) { // set to 1000 for production!
    lastTick = millis();
    second++;
  }

// move forward one minute every 60 seconds
if (second >= 60) {
  minute++;
  second = 0; // reset seconds to zero
}

// move forward one hour every 60 minutes
if (minute >=60) {
  hour++;
  minute = 0; // reset minutes to zero
}

if (hour >=24) {
  hour=0;
  minute = 0; // reset minutes to zero
}

  munit = minute%10; //sets the variable munit and hunit for the unit digits
  hunit = hour%10;

  ledstats = digitalRead(18);  // read input value, for setting leds off, but keeping count
  if (ledstats == LOW){
    light=!light;
    delay(250);
  }
    
    if (light == LOW){
      for (i=1;i<=13;i++) {
        digitalWrite(i, HIGH);
      }
    } else  {
  //minutes units
    if (munit == 0) {digitalWrite(1, LOW);}
    if (munit == 1 || munit == 3 || munit == 5 || munit == 7 || munit == 9) {  digitalWrite(2, HIGH);} else {digitalWrite(2, LOW);}
    if (munit == 2 || munit == 3 || munit == 6 || munit == 7) {digitalWrite(3, HIGH);} else {digitalWrite(3, LOW);}
    if (munit == 4 || munit == 5 || munit == 6 || munit == 7) {digitalWrite(4, HIGH);} else {digitalWrite(4, LOW);}
    if (munit == 8 || munit == 9) {digitalWrite(5, HIGH);} else {digitalWrite(5,LOW);}

  //minutes 
  if((minute >= 10 && minute < 20) || (minute >= 30 && minute < 40) || (minute >= 50 && minute < 60))  {digitalWrite(6, HIGH);} else {digitalWrite(6,LOW);}
  if(minute >= 20 && minute < 40)  {digitalWrite(7, HIGH);} else {digitalWrite(7,LOW);}
  if(minute >= 40 && minute < 60) {digitalWrite(8, HIGH);} else {digitalWrite(8,LOW);}

  //hour units
  if(hunit == 1 || hunit == 3 || hunit == 5 || hunit == 7 || hunit == 9) {digitalWrite(9, HIGH);} else {digitalWrite(9,LOW);}
  if(hunit == 2 || hunit == 3 || hunit == 6 || hunit == 7) {digitalWrite(10, HIGH);} else {digitalWrite(10,LOW);}
  if(hunit == 4 || hunit == 5 || hunit == 6 || hunit == 7) {digitalWrite(11, HIGH);} else {digitalWrite(11,LOW);}
  if(hunit == 8 || hunit == 9) {digitalWrite(12, HIGH);} else {digitalWrite(12,LOW);}

    //hour
    if(hour >= 10 && hour < 20)  {digitalWrite(A1, HIGH);} else {digitalWrite(A1,LOW);}
    if(hour >= 20 && hour < 24)  {digitalWrite(A2, HIGH);} else {digitalWrite(A2,LOW);}
  }

  valm = digitalRead(14);    // add one minute when pressed
  if(valm== LOW) {
    minute++;
    second=0;
    delay(250);
  }
  
  valh = digitalRead(19);    // add one hour when pressed
  if(valh==LOW) {
    hour++;
    second=0;
    delay(250);
  }
}
