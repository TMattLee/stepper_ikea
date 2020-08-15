#define setEnabledPin 8
#define dirPin 4
#define pulsePin 3

uint32_t stepsPerRevolution  = 200;
uint32_t rpm = 400;

uint32_t timeDivisionMicros = 0;
uint32_t delayTime = 0;
uint32_t prevTime = 0;

bool stepDirectionChange = 0;

bool check = 1;

bool cantRun = false;
bool turnDirOne = false;
bool turnDirTwo = false;


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  uint32_t pulses = stepsPerRevolution * rpm;
  uint32_t divisionTime = 60000000;
  Serial.println(pulses);
  Serial.println("");
  timeDivisionMicros = divisionTime / pulses;
  delayTime = timeDivisionMicros / ((uint32_t)2);
  Serial.print("\n Time info: ");
  Serial.print(timeDivisionMicros);
  Serial.print(" ");
  Serial.println(delayTime);
  Serial.println("cat");
  pinMode(pulsePin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(setEnabledPin,OUTPUT);
  pinMode(11,INPUT);   // step direciton 0
  pinMode(12,INPUT);  // step direction 1
  prevTime = micros();
  digitalWrite(setEnabledPin, HIGH);
  digitalWrite(dirPin,LOW);
  digitalWrite(pulsePin,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if(micros() - prevTime >= timeDivisionMicros){
    cantRun = digitalRead(setEnabledPin);
    turnDirOne = digitalRead(11);
    turnDirTwo = digitalRead(12);
    stepDirectionChange = digitalRead(dirPin);
    if((turnDirOne || turnDirTwo)){
      if(turnDirOne && !turnDirTwo) {
        if(stepDirectionChange) {
          digitalWrite(dirPin, LOW);
        }
        
      } 
      
      if(!turnDirOne && turnDirTwo){
        if(!stepDirectionChange) {
          digitalWrite(dirPin, HIGH);
        }
      } 
      
      if(cantRun == HIGH) digitalWrite(setEnabledPin, LOW);
    } else {
      if(cantRun == LOW) digitalWrite(setEnabledPin, HIGH);
    }

    
    if(check){
      digitalWrite(pulsePin,LOW);
    } else {
      digitalWrite(pulsePin,HIGH);
    }
    //digitalWrite(pulsePin,HIGH);
    //delayMicroseconds(timeDivisionMicros / 2);
    check = !check;
    prevTime = micros();
  }
}
