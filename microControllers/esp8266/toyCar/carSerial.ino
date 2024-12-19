/* 
  Controls a toy car using ESP8266
  Developer: Somnath Das
*/

// Define Motor PINs
#define fwdPin 13   //D7
#define bckPin 15   //D8
#define leftPin 14  //D5
#define rightPin 12 //D6

// Define LED PINs
#define fLight 5  //D1
#define bLight 4  //D2
#define leftInd 0 //D3
#define rigtInd 2 //D4

// Define variables
int carSpeed = 150;
bool fwdFlag = true; // Goes back for false
bool dirChng = false;
bool lftTurn = false;
bool rgtTurn = false;

String ctlMsg; // Inputs from User

unsigned long oldLeftMillis = 0;
unsigned long oldRghtMillis = 0;
const int interval = 500; // Blink interval in milliseconds
bool lftInFlag = false;
bool rghtInFlag = false;
bool frntLiFlag = false;
bool backLiFlag = false;

bool frntLiChg = false;
bool backLiChg = false;
int beamIntensity = 120; // Low beam and high beam
bool indiChg = false;

// Set the board
void  setup() {
  Serial.begin(115200);

  pinMode(fwdPin, OUTPUT);
  pinMode(bckPin, OUTPUT);
  pinMode(leftPin, OUTPUT);
  pinMode(rightPin, OUTPUT);

  pinMode(fLight, OUTPUT);
  pinMode(bLight, OUTPUT);
  pinMode(leftInd, OUTPUT);
  pinMode(rigtInd, OUTPUT);

  Serial.println("Initializing...");
  Serial.println("Setup Complete!");
}

//The loop or the main brain
void loop() {
  if (Serial.available()) {
    ctlMsg = Serial.readStringUntil('\n'); // Read until newline
    ctlMsg.trim();

    if(ctlMsg == "fwd"){
      fwdFlag = true;
      dirChng = true;
      backLiFlag = false;
      backLiChg = true;
      Serial.println("forward received");
    }
    else if(ctlMsg == "bck"){
      fwdFlag = false;
      dirChng = true;
      backLiFlag = true;
      backLiChg = true;
      Serial.println("backward received");
    }
    else if(ctlMsg == "left"){
      lftTurn = true;
      rgtTurn = false;
      Serial.println("left turn received");
    }
    else if(ctlMsg == "right"){
      rgtTurn = true;
      lftTurn = false;
      Serial.println("right turn received");
    }
    else if(ctlMsg == "speed1"){
      carSpeed = 80;
      dirChng = true;
      Serial.println("gear 1 received");
    }
    else if(ctlMsg == "speed2"){
      carSpeed = 140;
      dirChng = true;
      Serial.println("gear 2 received");
    }
    else if(ctlMsg == "speed3"){
      carSpeed = 200;
      dirChng = true;
      Serial.println("gear 3 received");
    }
    else if(ctlMsg == "speed4"){
      carSpeed = 250;
      dirChng = true;
      Serial.println("gear 4 received");
    }
    else if(ctlMsg == "stop"){
      analogWrite(bckPin, 0);
      analogWrite(fwdPin, 0);
      backLiFlag = true;
      backLiChg = true;
      Serial.println("stop received");
    }
    else if(ctlMsg == "hbeam"){
      frntLiFlag = true;
      frntLiChg = true;
      beamIntensity = 250;
      Serial.println("high beam received");
    }
    else if(ctlMsg == "lbeam"){
      frntLiFlag = true;
      frntLiChg = true;
      beamIntensity = 120;
      Serial.println("low beam received");
    }
    else if(ctlMsg == "floff"){
      frntLiFlag = false;
      frntLiChg = true;
      beamIntensity = 120;
      Serial.println("front light off received");
    }
    else if(ctlMsg == "lftind"){
      lftInFlag = true;
      rghtInFlag = false;
      indiChg = true;
      Serial.println("left indicator received");
    }
    else if(ctlMsg == "rgtind"){
      lftInFlag = false;
      rghtInFlag = true;
      indiChg = true;
      Serial.println("right indicator received");
    }
    else if(ctlMsg == "park"){
      lftInFlag = true;
      rghtInFlag = true;
      indiChg = true;
      Serial.println("park indicator received");
    }
    else if(ctlMsg == "indoff"){
      lftInFlag = false;
      rghtInFlag = false;
      indiChg = true;
      Serial.println("indicator off received");
    }
  }

  // Car Direction & Speed
  if(dirChng) {
    if(fwdFlag) {
      analogWrite(bckPin, 0); //Stop the other pin
      analogWrite(fwdPin, carSpeed);
    }
    else {
      analogWrite(fwdPin, 0); // Stop the other pin
      analogWrite(bckPin, carSpeed);
    }
    dirChng = false;
  }

  // Car Left & Right Turns
  if(lftTurn) {
    analogWrite(leftPin, 80);
    delay(30);
    analogWrite(leftPin, 0);
    lftTurn = false;
  }
  if(rgtTurn) {
    analogWrite(rightPin, 80);
    delay(30);
    analogWrite(rightPin, 0);
    rgtTurn = false;
  }

  // Front & Back LED
  if(frntLiChg) {
    if(frntLiFlag) {
      analogWrite(fLight, beamIntensity);
    }
    else {
      analogWrite(fLight, 0);
    }
  }
  if(backLiChg) {
    if(backLiFlag) {
      analogWrite(bLight, 100);
    }
    else {
      analogWrite(bLight, 0);
    }
  }

  // Control indicators
  if(indiChg) {
    if(lftInFlag) {
      unsigned long leftMillis = millis();
      if (leftMillis - oldLeftMillis >= interval) {
        digitalWrite(leftInd, !digitalRead(leftInd));
        oldLeftMillis = leftMillis;
      }
    }
    else {
      digitalWrite(leftInd, LOW);
    }

    if(rghtInFlag) {
      unsigned long rghtMillis = millis();
      if (rghtMillis - oldRghtMillis >= interval) {
        digitalWrite(rigtInd, !digitalRead(rigtInd));
        oldRghtMillis = rghtMillis;
      }
    }
    else {
      digitalWrite(rigtInd, LOW);
    }

    if(!rghtInFlag && !lftInFlag) {
      indiChg = false;
      Serial.println("Indicators turned off!");
    }
  }

}
