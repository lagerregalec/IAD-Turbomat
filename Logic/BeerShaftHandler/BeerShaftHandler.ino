#define shaft1 1
#define shaft2 2
#define shaft3 3
#define shaft4 4
#define shaft5 5

boolean StateShaft1, StateShaft2, StateShaft3, StateShaft4, StateShaft5;
boolean StateShaftBefore1, StateShaftBefore2, StateShaftBefore3, StateShaftBefore4, StateShaftBefore5;
int shaftQuantity = 5;
int InterferenceTimer = 20 ;
int timerCounter;


void setup() {
  Serial.begin(9600);

  for (int k = 0; k <= shaftQuantity; k++) {
    pinMode(k, INPUT_PULLUP);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  StateShaft1 = digitalRead(shaft1);
  StateShaft2 = digitalRead(shaft2);
  StateShaft3 = digitalRead(shaft3);
  StateShaft4 = digitalRead(shaft4);
  StateShaft5 = digitalRead(shaft5);

  if(timerCounter >= InterferenceTimer){
    StateShaftBefore1 = digitalRead(shaft1);
    timerCounter = 0;
  }

  if (StateShaft1 != StateShaftBefore1 ) {
    Serial.println(shaft1);
  }
  timerCounter ++;
  delay(1);
}
