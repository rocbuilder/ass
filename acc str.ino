// these constants describe the pins. They won't change:
//const int groundpin = A1;             // ground
//const int powerpin = A5;              // voltage
const int xpin = A0;                  // x-axis of the accelerometer
const int ypin = A1;                  // y-axis
const int zpin = A2;                  // z-axis (only on 3-axis models)

const int accReadings = 10;
int accIndex = 0;
int xArray[accReadings];
int yArray[accReadings];
int zArray[accReadings];
int d[3];
int aV = 0;
int aMax = 0;
int aSum = 0;

int aVPrev = 0;
const int staticThreshold = 30;
int dThreshold = staticThreshold;

const int peakReadings = 5;
int peakIndex = 0;
int peak[peakReadings];
bool peakDetection = true;

const int rateReadings = 10;
int rateIndex = 0;
float strokeRate;
int strokePeriod[rateReadings];
float avgStrokePeriod = 0;
int relStrokePeriod = 0;

int pause = 50;

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);

  // Provide ground and power by using the analog inputs as normal
  // digital pins.
  //pinMode(groundpin, OUTPUT);
  //pinMode(powerpin, OUTPUT);
  //digitalWrite(groundpin, LOW);
  //digitalWrite(powerpin, HIGH);

  //set aoll values in array to 0
  clearArray(xArray, accReadings);
  clearArray(yArray, accReadings);
  clearArray(zArray, accReadings);
  clearArray(d, 3);
}

void loop() {
  d[0] = dynamicAcc(xArray, analogRead(xpin));
  d[1] = dynamicAcc(yArray, analogRead(ypin));
  d[2] = dynamicAcc(zArray, analogRead(zpin));
  aV = sqrt(sq(d[0]) + sq(d[1]) + sq(d[2]));
  aSum = d[0] + d[1] + d[2];
  if(analogRead(xpin)>analogRead(ypin) && analogRead(xpin)>analogRead(zpin)) {aMax = analogRead(xpin);}
  if(analogRead(ypin)>analogRead(xpin) && analogRead(ypin)>analogRead(zpin)) {aMax = analogRead(ypin);}
  if(analogRead(zpin)>analogRead(xpin) && analogRead(zpin)>analogRead(ypin)) {aMax = analogRead(zpin);}
  if (aMax<0){aV= -aV;}
  //arrayReset(accIndex, accReadings);
  accIndex++;
  if (accIndex >= accReadings) {accIndex = 0;}
  if (aVPrev < aV) {peakDetection = true;}
  if (aVPrev > dThreshold && aVPrev > aV && peakDetection) {
    peak[peakIndex] = aVPrev;
    //arrayReset(peakIndex, peakReadings);
    peakIndex++;
    if (peakIndex >= peakReadings) {peakIndex = 0;}
    dThreshold = avgArray(peak, peakReadings) * 0.6;
    //arrayReset(rateIndex, rateReadings);
    rateIndex++;
    if (rateIndex >= rateReadings) {rateIndex = 0;}
    strokePeriod[rateIndex] = 0;
    peakDetection = false;
  }
  aVPrev = aV;

  //strokeRate = (60000 / avgArray(strokePeriod, rateReadings)) / 50;
  relStrokePeriod = 0;
  avgStrokePeriod = 0;
  for (int i = 0; i<rateReadings; i++) {
    if(strokePeriod[i] != 0 && i != rateIndex) {
      avgStrokePeriod += strokePeriod[i];
      relStrokePeriod ++;
    }
  }
  avgStrokePeriod = avgStrokePeriod/relStrokePeriod;
  strokeRate = 60000/(avgStrokePeriod*pause);

  strokePeriod[rateIndex] ++;
  Serial.println(strokeRate);
  delay(pause);
}

//sets arrays values to 0
int clearArray (int a[], int num) {
  for (int thisReading = 0; thisReading < num; thisReading++) {a[thisReading] = 0;}
}

//calculates dynamic acceleration from an acceleration array
int dynamicAcc(int acc[], int accRead){
  int d = 0;
  acc[accIndex] = accRead;
  arrayReset(accIndex, accReadings);
  d = accRead - avgArray(acc, accReadings);
  return (d);
}

int avgArray(int a[], int num) {
  int result = 0;
  result = sumArray(a, num) / num;
  return (result);
}

int sumArray(int a[], int num) {
  int sum = 0;
  for (int i = 0; i<num; i++) {
    sum += a[i];
  }
  return (sum);
}

int arrayReset(int index, int readings) {
  index++;
  if (index >= readings) {index = 0;}
}
