#include <SoftwareSerial.h>   //TODO need to set due to some weird wire language linker, should we absorb this whole library into smartthings
#include <SmartThings.h>


#define PIN_THING_RX    3
#define PIN_THING_TX    2


SmartThingsCallout_t messageCallout;    // call out function forward decalaration
SmartThings smartthing(PIN_THING_RX, PIN_THING_TX, messageCallout);  // constructor

int Led_Pin = 13;        // choose the pin for the LED
int Sensor_Pin = 6;      // choose the Sensor_Pin
int val = 0;             // variable for reading the Sensor_Pin status
int old_val = -1;
int count = 0;
bool isDebugEnabled;     // enable or disable debug

void setup() {
  pinMode(Led_Pin, OUTPUT);    // declare Led_Pin as output
  pinMode(Sensor_Pin, INPUT);  // declare Sensor_Pin as input
  isDebugEnabled = true;
  if (isDebugEnabled) {         // setup debug serial port, if debug is enabled
    Serial.begin(9600);         // setup serial with a baud rate of 9600
    Serial.println("Debugging is enabled!");
  }
}

void loop(){
  smartthing.run();
  val = digitalRead(Sensor_Pin);  // read Sensor_Pin

  if (val == LOW) {
    digitalWrite(Led_Pin, LOW);   //Set Led on
  } else {
    digitalWrite(Led_Pin, HIGH);  //Set Led off
    if(old_val != val){
      count = count + 1;
      if(isDebugEnabled){
        Serial.print("Doorbell pushed ");
        Serial.print(count);
        Serial.println(" times");
      }
      smartthing.send("ring");
    }
  }
  old_val = val;
}
void messageCallout(String message){
  // if debug is enabled print out the received message
  if (isDebugEnabled){
    Serial.print("Received message: '");
    Serial.print(message);
    Serial.println("' ");
  }
  if (message.equals("ok")) {
    //the cloud has ack'ed us, hurray!
  }
}


