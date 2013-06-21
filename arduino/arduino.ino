#define rightEyeRed 5 // Define pinout for right eye
#define leftEyeRed 6 // Define pinout for left eye

int waittime = 100;
int alt = 3;

void setup() {                
  pinMode(rightEyeRed, OUTPUT); // Pin output at rightEyeRed
  pinMode(leftEyeRed, OUTPUT); // Pin output at leftEyeRed 
  Serial.begin(9600);  
}

// the loop routine runs over and over again forever:
void loop() {
  while (Serial.available() > 0) {
    waittime = Serial.parseInt();
    alt = Serial.parseInt();
    if (Serial.read() == '\n') {
      Serial.println(waittime);
      Serial.println(alt);

    }
  }
  if(alt==0){ // normal blink
    analogWrite(rightEyeRed, 0); 
    analogWrite(leftEyeRed, 0); 
    delay(waittime); 
  
    analogWrite(rightEyeRed, 255);
    analogWrite(leftEyeRed, 255);
    delay(waittime); 
  } else if(alt==1) { //alt blink
    analogWrite(rightEyeRed, 0); 
    analogWrite(leftEyeRed, 255);   
    delay(waittime);     
  
    analogWrite(rightEyeRed, 255); 
    analogWrite(leftEyeRed, 0); 
    delay(waittime); 
  } else {
    analogWrite(rightEyeRed, 255); 
    analogWrite(leftEyeRed, 255); 
  }
   
}
