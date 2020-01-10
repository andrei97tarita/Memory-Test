#include <IRremote.h>
#include <time.h>
#include <stdlib.h>
#include "TimerOne.h"
#include <SoftwareSerial.h> 
SoftwareSerial MyBlue(0, 1); // RX | TX 

unsigned long key_value = 0;
int IR[11];
int numbers[5];
int simplify[11];
int k = 0; //number of digits
int index = 0; 
long waitTime = 1000000;
//display
const int a = 2;
const int b = 3;
const int c = 4;
const int d = 5;
const int e = 6;
const int f = 7;
const int g = 8;
const int d4 = 11;
const int d2 = 10;
const int d1 = 9;
const int ir = 12;
int score = 0;
int del = 5;//Set del as 5; the value is the degree of fine tuning for the clock
int aux = 0;
int readIR = 1; // enable for reading
int digit0, digit1;
IRrecv irrecv(ir);
decode_results results;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  MyBlue.begin(9600); 
  irrecv.enableIRIn();
  irrecv.blink13(true);

  generate();
  decompose();
  Serial.println();

  Timer1.initialize(waitTime);
  Timer1.attachInterrupt(count);

  //set all the pins of the LED display as output
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);

}

void generate() {
  srand(millis());
  for (int i = 0; i < 5; i++) {
    numbers[i] = rand() % 100;
  }
}

void decompose() {
  k = 0;
  for (int i = 0; i < 5; i++) {
    Serial.print(numbers[i], DEC);
    Serial.print(F(" "));
    if (numbers[i] < 10) {
      simplify[k++] = numbers[i];
    }
    else {
      int a = numbers[i] % 10;
      int b = (numbers[i] / 10) % 10;

      simplify[k++] = b;
      simplify[k++] = a;
    }
  }
}

boolean test() {
  boolean ret = true;
  for (int i = 0; i < k; i++) {
    if (simplify[i] != IR[i]) {
      ret = false;
      break;
    }
  }
  return ret;
}

void decoder() {
  if (irrecv.decode(&results)) {
    if (results.value == 0XFFFFFFFF)
      results.value = key_value;
    switch (results.value) {
      case 0xFFE01F:
        //Serial.println("-");
        waitTime -= 100000;
        break;

      case 0xFFA857:
        //Serial.println("+");
        waitTime += 100000;
        break;

      case 0xFF6897:
        clearLEDs();//clear the 7-segment display screen
        pickDigit(4);//Light up 7-segment display d1
        pickNumber(0);// get the value of thousand
        delay(del);//delay 5ms
        IR[index++] = 0;
        break;

      case 0xFF30CF:
        clearLEDs();//clear the 7-segment display screen
        pickDigit(4);//Light up 7-segment display d1
        pickNumber(1);// get the value of thousand
        delay(del);//delay 5ms
        IR[index++] = 1;
        break;

      case 0xFF18E7:
        clearLEDs();//clear the 7-segment display screen
        pickDigit(4);//Light up 7-segment display d1
        pickNumber(2);// get the value of thousand
        delay(del);//delay 5ms
        IR[index++] = 2;
        break;

      case 0xFF7A85:
        clearLEDs();//clear the 7-segment display screen
        pickDigit(4);//Light up 7-segment display d1
        pickNumber(3);// get the value of thousand
        delay(del);//delay 5ms
        IR[index++] = 3;
        break;

      case 0xFF10EF:
        clearLEDs();//clear the 7-segment display screen
        pickDigit(4);//Light up 7-segment display d1
        pickNumber(4);// get the value of thousand
        delay(del);//delay 5ms
        IR[index++] = 4;
        break;

      case 0xFF38C7:
        clearLEDs();//clear the 7-segment display screen
        pickDigit(4);//Light up 7-segment display d1
        pickNumber(5);// get the value of thousand
        delay(del);//delay 5ms
        IR[index++] = 5;
        break;

      case 0xFF5AA5:
        clearLEDs();//clear the 7-segment display screen
        pickDigit(4);//Light up 7-segment display d1
        pickNumber(6);// get the value of thousand
        delay(del);//delay 5ms
        IR[index++] = 6;
        break;

      case 0xFF42BD:
        clearLEDs();//clear the 7-segment display screen
        pickDigit(4);//Light up 7-segment display d1
        pickNumber(7);// get the value of thousand
        delay(del);//delay 5ms
        IR[index++] = 7;
        break;

      case 0xFF4AB5:
        clearLEDs();//clear the 7-segment display screen
        pickDigit(4);//Light up 7-segment display d1
        pickNumber(8);// get the value of thousand
        delay(del);//delay 5ms
        IR[index++] = 8;
        break;

      case 0xFF52AD:
        clearLEDs();//clear the 7-segment display screen
        pickDigit(4);//Light up 7-segment display d1
        pickNumber(9);// get the value of thousand
        delay(del);//delay 5ms
        IR[index++] = 9;
        break;
    }
    key_value = results.value;
    delay(200);
    irrecv.resume();
  }
}

void clearIR() {
  index = 0;
  aux = 0;
}

void trueDisplay() {
  clearLEDs();//clear the 7-segment display screen
  pickDigit(4);//Light up 7-segment display d1
  pickNumber(score);// get the value of thousand
  delay(del);//delay 5ms
}

void wrongDisplay() {
  clearLEDs();
  pickDigit(4);//Light up 7-segment display d1
  pickNumber(0);// get the value of thousand
  delay(del);//delay 5ms
}

void writeBluetooth(int n) {
  byte h = highByte(n);
  byte l = lowByte(n);
  MyBlue.write(h);
  MyBlue.write(l);
}

void loop() {
  if (index == k) {
    readIR = 0;
    index = 0;
    int testValue = test();
    writeBluetooth(0);
    if (testValue == true) {
      Serial.println("True");
      score++;
      trueDisplay();
      writeBluetooth(1);
      clearIR();
      delay(2500);
      Serial.println();
      generate(); // generate randaom numbers 
      decompose(); //decompose the numbers in digits
      readIR = 1;
      aux = 0;
    }  
    else {
      wrongDisplay();
      readIR = 0;
      aux = 0;
      writeBluetooth(2);
      clearIR();
      delay(2500);
      Serial.println("Wrong");
      readIR = 1;
    }
  }
  else if(readIR = 1) {
    decoder(); //read from IR
  }

  clearLEDs();//clear the 7-segment display screen
  pickDigit(1);//Light up 7-segment display d1
  pickNumber(digit0);// get the value of thousand
  delay(del);//delay 5ms

  clearLEDs();//clear the 7-segment display screen
  pickDigit(0);//Light up 7-segment display d1
  pickNumber(digit1);// get the value of thousand
  delay(del);//delay 5ms
}

void pickDigit(int x) { //light up a 7-segment display
  //The 7-segment LED display is a common-cathode one. So also use digitalWrite to  set d1 as high and the LED will go out
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d4, LOW);
  switch (x)
  {
    case 0:
      digitalWrite(d1, HIGH);//Light d1 up
      break;
    case 1:
      digitalWrite(d2, HIGH); //Light d2 up
      break;
    case 4:
      digitalWrite(d4, HIGH);
      break;
  }
}

//The function is to control the 7-segment LED display to display numbers. Here x is the number to be displayed. It is an integer from 0 to 9
void pickNumber(int x) {
  switch (x)
  {
    default:
      zero();
      break;
    case 1:
      one();
      break;
    case 2:
      two();
      break;
    case 3:
      three();
      break;
    case 4:
      four();
      break;
    case 5:
      five();
      break;
    case 6:
      six();
      break;
    case 7:
      seven();
      break;
    case 8:
      eight();
      break;
    case 9:
      nine();
      break;
  }
}

void clearLEDs() {
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void zero(){ //the 7-segment led display 0
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void one() {//the 7-segment led display 1
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void two(){ //the 7-segment led display 2
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void three() {//the 7-segment led display 3
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void four() {//the 7-segment led display 4
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void five() { //the 7-segment led display 5
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void six() {//the 7-segment led display 6
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void seven() { //the 7-segment led display 7
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void eight() { //the 7-segment led display 8
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void nine() { //the 7-segment led display 9
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void count() {
  delay(1000);
  if(aux <= 5 && readIR == 1) {
    
    digit0 = numbers[aux] % 10;
    digit1 = numbers[aux] / 10 % 10;
    aux++;
  }
}
