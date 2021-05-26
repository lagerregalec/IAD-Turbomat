#define schacht1Pin 2

int schachtAnzahl = 5;
int booleanDenoiseAmount = 500; //in milliseconds

boolean schacht[5];
int activeSchacht;
boolean changeDetected = false;
int timer;

void setup() {
  // put your setup code here, to run once:
  for (int k=0;k<schachtAnzahl;k++){
    pinMode(k+2,INPUT_PULLUP);
  }
  timer = 0;
  
  Serial.begin(9600);
}

void loop() {
  /*
  if(digitalRead(schacht1Pin)!=schacht1ButtonState){
    schacht1WasActive = true;
    if(schacht1WasActive==true&&messageSent==false){
  //Serial.println("Schacht1 was active!");
  messageSent = true;
}
  }
  messageSent = false;

  activeSchacht = schachtDetection();
  Serial.println(activeSchacht);
  if(activeSchacht<0){
    Serial.println(activeSchacht+"was Active!");
  }
  */ 

 schachtDetection();

 //Serial.println(activeSchacht);
 
 
}



void schachtDetection(){

for (int k=0;k<schachtAnzahl;k++){
 if(schacht[k]!=digitalRead(k+2)){
  timer++;
  if(timer <=1){
  changeDetected = true;
  activeSchacht = k+1;
  String toPrint = String(k+1)+" was active";
  Serial.println(toPrint);
  }
  if (timer>booleanDenoiseAmount){
    timer = 0;
  }
 }
  changeDetected = false;
 
  
  schacht[k] = digitalRead(k+2);
 }
 
}
  
