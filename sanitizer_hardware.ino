//Watersensor
const int watersensor = A0;
int WaterLevel = 0;
int sensorValue;

//IR detection
const int IRdetection = A5;
int IRvalue = HIGH;
unsigned long timer; // (store the timer count, only postive numbers)
int interval = 10000;
int lastIRvalue;
int count10 =0; // set count

//ButtonISR
const int buttonPin = 3; //setting of button pin
int flag = 0; //setting initial condition
int flag_Status = 0;
int ButtonState = 0;


//Relay
const int RELAY_PIN = 6;
int PumpDelay = 150; //User can change this value to determine the volume to dispend.

//LED
const int LED = 13;

//Dispender counter
int DispCount = 0;

void setup()
{
  pinMode(buttonPin, INPUT); //default LOW, but must connect it to 5V, Button Pin to Ground
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH);  // turn off pump 5 seconds
  pinMode (LED, OUTPUT); // Led pin OUTPUT
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), ButtonISR, RISING); //interrupt when countup button pressed  (to trigger the interrupt whenever the pin is low,)
  Serial.begin(9600);
  initial();
}

void loop()
{
  unsigned long currentMillis = millis();
  sensorValue = analogRead(watersensor);
  IRvalue = digitalRead(IRdetection);
  ButtonState = digitalRead(buttonPin);

  if (IRvalue == 0)  //If sense until hand , detected
    count10++; //count up
  else
    count10 = 0;  //nobody activate the count is 0
  if (count10 == interval )    //If meet the interval, carry out this function
  {
    flag_Status = 1; //(status switched to high)
    Serial.println("IR_detect");
    digitalWrite(LED, HIGH); // LED LOW
    IRdetect(); //(call IRdetect function)
    count10 = 0;
  }
  else
    flag_Status = 0;
  if (flag == 1)
  {
    Pump(PumpDelay); //(call IRdetect function)
    flag = 0; //(switches flag state back to low)
  }
  if (flag == 0 && flag_Status == 0) // (for resetting device back to receive new input again??)
  {
    attachInterrupt(digitalPinToInterrupt(buttonPin), ButtonISR, LOW); // (defines when to trigger the interrupt whenever the pin is low)
    digitalWrite(LED, LOW); // LED LOW
  }
}


void initial()
{
  //Serial.print("Welcome\n");
  digitalWrite(LED, LOW);
  //waterLevel();
}


void Pump(int pumpdlay)
{
  detachInterrupt(digitalPinToInterrupt(buttonPin)); // (turn off given interrupt)
  digitalWrite(RELAY_PIN, LOW); // turn on pump 
  delay(pumpdlay);
  digitalWrite(RELAY_PIN, HIGH);  // turn off pump 
  DispCount++;
  Serial.println("DispC");
  delay(pumpdlay);
  waterLevel();
  flag_Status = 0;
  flag = 0;
  detachInterrupt(digitalPinToInterrupt(buttonPin));
}


void IRdetect()
{
  Serial.println("Dispensing");
  Pump(PumpDelay);  //(call pump function to pump water)
}


void ButtonISR()
{
  static unsigned long last_interrupt_time = 0;  // (create variables that are visible to only one function)
  if ((millis() - last_interrupt_time > 1000) && (flag_Status == 0) && (flag == 0))
  {
    Serial.println("Dispensing");
    Serial.println ("Button pressed");
    digitalWrite(LED, HIGH); // LED LOW  
    flag = 1;
    last_interrupt_time = millis();
  }
}


void waterLevel()
{
  if (sensorValue >= 675)
  {
    Serial.println(sensorValue);
    Serial.println("Water Level: Full");
  }
  else if (sensorValue < 675 && sensorValue >= 450)
  {
    Serial.println(sensorValue);
    Serial.println("Water Level: Medium");
  }
  else if (sensorValue < 450 )
  {
    Serial.println(sensorValue);
    Serial.println("Water Level: Empty. Please refill.");
  }
}