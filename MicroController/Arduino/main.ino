/* Control Program Version 0.4.2

(C) Qian Cheng, 2014

The serial input is given by the keyboard through USB to the board.
The input signal assign a flag to be 1 (High) or 0 (Low).
The board controls the LED to output a High or Low.
Include the stopbit '#'
*/

const byte led = 13; //LED connected to digital pin 13

int flag;

boolean ledstate = false;

String readString, refstring1, refstring2, refstring3;


// What a nice code

// I agree: it is nice.

void setup() {
  
  // initialise serial communication at 9600 bits per second:
  
  Serial.begin(9600);
  
  //initialise the led pin as an output
  
  pinMode(led, OUTPUT);
  
  digitalWrite(led, LOW); //initial state of the switch is LOW
  
  //set reference string for comparison
  
//  refstring1 = String("I");
//  refstring2 = String("V");
//  refstring3 = String("-");
  
  //initialise serial communication
  
  while (! Serial);
  
  Serial.println("Enter a command:");
  
}


void loop() {
  
  while (Serial.available()) {
    
    
     char c = Serial.read(); //gets one byte from serial buffer
     
     //test when to stop by the stop sign #
     
     if (c != '#'){
     
     readString += c; //makes the string readString
    
     delay(3); //slow looping to allow buffer to fill with next character
     
     } else {
       
       break;
       
     }
     
     
  }
  
    
  if (readString.length() > 0) {
    
     Serial.println("\n");
     
     Serial.println("\n"+readString);  //so you can see the captured string 
     
     //set the flag change the polarity of the switch
     
     //test current or voltage first 
     
    if (readString.substring(0,1) == "I" && readString.substring(2,3) == " ") {
    
     if (readString.substring(3,4) == "-") {
       
       flag = 0;
       
     } else {
       
       flag = 1;
       
     }
    } else if (readString.substring(0,1) == "V" && readString.substring(2,3) == " ") {
      
      flag = 2;
      
    } else {
      
      flag =3;
      
    }
     
     Serial.print("flag is: ");
     Serial.print(flag);
     Serial.print("\n");
     
     //Then to see what value shall we change
    
    if (flag == 0) {
      
      //current to be 0 first
      
      refstring1 = readString;
      Serial.print(refstring1.charAt(0));
      Serial.print(refstring1.charAt(1));
      Serial.print(refstring1.charAt(2));
      Serial.print("0.001\n");
      
      delay(500);
      
      //change the polarity
  
      ledstate = HIGH;
      
      Serial.print("******LED on*****\n");
      
      Serial.println(led);
      
      digitalWrite(led, ledstate);
      
      refstring1 = readString;
      
      //refstring1.trim();
      
      //refstring1.replace('-','+');
      
      for (int i = 0; i < 3; i++){
      
      Serial.print(refstring1.charAt(i));
      
      }
      for (int i = 4; i < 9; i++){
      
      Serial.print(refstring1.charAt(i));
      
      }
     
      //Serial.write(10)
      

    }   else if (flag == 1) {
      
      ledstate = LOW; 
      
      Serial.print("******LED off*****\n");
      
      Serial.println(led);
      
      digitalWrite(led, ledstate);
      
      refstring2 = readString;
      
      for (int i = 0; i < 8; i++){
      
      Serial.print(refstring2.charAt(i));
      
      }     
      
      //Serial.write(10)
      
    }   else if (flag == 2) {
      
      ledstate = LOW; 
      
      Serial.print("******LED off*****\n");
      
      Serial.println(led);
      
      digitalWrite(led, ledstate);
      
      refstring3 = readString;
      
      for (int i = 0; i < 8; i++){
      
      Serial.print(refstring3.charAt(i));
      
      }     
      
      //Serial.write(10)
      
    } else {
      
      ledstate = LOW; 
      
      Serial.print("******Not a valid Command*****\n");
      
    }
    
    
    readString=""; //empty for next input
   
  }
  
  delay(1000);

}


