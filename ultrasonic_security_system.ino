#include <HCSR04.h>


#define NOTE_G4 392 // Frequency of G4 note in Hz


HCSR04 ultraSonic = HCSR04(11,  9 );

long dist;

int code[] = {1, 2, 3, 4}; //the desired code is entered  in this array,
//separated by commas

int entered[5]; //create a new empty  array for the code entered by
//the user (has 4 elements)

const int LED1  = 13;
const int LED2 = 3;
const int LED3 = 2;
const int buzzerPin = 8;
const  int button1 = 4;
const int button2 = 5;
const int button3 = 6;
const int  button4 = 7;
const int timerdelay = 250;

const int redLED = 12;
const  int greenLED = 10;
void checkEntered1(int button);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED1, OUTPUT);
  pinMode(LED2,  OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3,  LOW);
  delay(1000);
  Serial.begin(9600); //begin Serial

  pinMode  (button1, INPUT);
  pinMode (button2, INPUT);
  pinMode (button3, INPUT);
  pinMode (button4, INPUT);
  pinMode (greenLED, OUTPUT);
  pinMode (redLED,  OUTPUT);

  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  for (int i = 0; i < 4; i++) { //work through numbers 0-3
    Serial.println(code[i]);  //print each digit of the code
    Serial.println(entered[i]); //print each element  of the entered[]

  }
}

void loop() {
  // put your main code  here, to run repeatedly:
  dist = ultraSonic.dist();
  Serial.print(dist);
  Serial.println("cm");
  delay(100);
  if (dist > 100) {
    digitalWrite(LED1,  LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
  }
  if (dist > 2 && dist <= 25) {
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2,  LOW);
    digitalWrite(LED3, LOW);
    tone(buzzerPin, NOTE_G4, 15000);
  }
  else if (dist > 25 && dist <= 75) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, LOW);
  }
  else if  (dist > 75 && dist <= 100) {
    digitalWrite(LED1, LOW);
    digitalWrite(LED2,  LOW);
    digitalWrite(LED3, HIGH);
  }

  if (digitalRead(button1)  == HIGH) { //if button1 is pressed
    checkEntered1(1); //call checkEntered  and pass it a 1

    delay(timerdelay);//wait, needed for correct functioning,  otherwise
    //buttons are deemed to be pressed more than once

  }
  else if (digitalRead(button2) == HIGH) { //if button2 is pressed
    checkEntered1(2);  //call checkEntered1 and pass it a 2

    delay(timerdelay); //wait

  }
  else if (digitalRead(button3) == HIGH) { //if button3 is pressed
    checkEntered1(3);  //call checkEntered1 and pass it a 3

    delay(timerdelay); //wait

  }
  else if (digitalRead(button4) == HIGH) { //if button4 is pressed
    checkEntered1(4);  //call checkEntered1 and pass it a 4

    delay(timerdelay); //wait

  }
}

void checkEntered1(int button) { //check the first element of the  entered[] array
  if (entered[0] != 0) { //if it is not a zero, i.e. it has already  been inputted
    checkEntered2(button); //move on to checkEntered2, passing  it "button"
  }

  else if (entered[0] == 0) { //if it is zero, i.e.  if it hasn't been defined with a button yet
    entered[0] = button; //set the  first element as the button that has been pressed
    Serial.print("1: ");  Serial.println(entered[0]); //for debugging
  }

}

void checkEntered2(int  button) { //check the second element of the entered[] array

  if (entered[1]  != 0) { //if it is not a zero, i.e. it has already been inputted
    checkEntered3(button);  //move on to checkEntered3, passing it "button"
  }

  else if (entered[1]  == 0) { //if it is zero, i.e. if it hasn't been defined with a button yet
    entered[1]  = button; //set the second element as the button that has been pressed
    Serial.print("2:  "); Serial.println(entered[1]); //for debugging
  }

}

void checkEntered3(int  button) { //check the third element of the entered[] array
  if (entered[2] !=  0) { //if it is not a zero, i.e. it has already been inputted
    checkEntered4(button);  //move on to checkEntered4, passing it "button"
  }

  else if (entered[2]  == 0) { //if it is zero, i.e. if it hasn't been defined with a button yet
    entered[2]  = button; //set the third element as the button that has been pressed
    Serial.print("3:  "); Serial.println(entered[2]); //for debugging
  }

}

void checkEntered4(int  button) { //check the third element of the entered[] array
  if (entered[3] ==  0) { //if it is zero, i.e. if it hasn't been defined with a button yet
    entered[3]  = button; //set the final element as the button that has been pressed
    Serial.print("4:  "); Serial.println(entered[3]); //for debugging
    delay(100); //allow time  for processing
    compareCode(); //call the compareCode function
  }
}



void compareCode() {
  for (int i = 0; i < 4; i++) { // Loop through the entered[] array
    Serial.println(entered[i]); // Print each element for debugging
  }

  if ((entered[0]  == code[0]) && (entered[1] == code[1]) && (entered[2] == code[2]) && (entered[3]  == code[3])) { //if all the elements of each array are equal
    digitalWrite(redLED,  LOW); // turn the red LED off
    digitalWrite(greenLED, HIGH); //turn the green  LED on
    delay(1000); //wait for a bit
    digitalWrite(greenLED, LOW);  //turn the green LED off
    noTone(buzzerPin);



    for (int i  = 0; i < 5; i++) { //this next loop is for debugging
      entered[i] = 0;

    }

    //loop(); //return to loop() (not really necessary)

  }
  else { //if you (or the intruder) get the code wrong

    digitalWrite(redLED,  HIGH);
    delay(1000);
    digitalWrite(redLED, LOW);
    Serial.println("Red  on");
    for (int i = 0; i < 5; i++) { //this next loop is for debugging
      entered[i] = 0;

    }
  }
  }
