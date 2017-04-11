

// these constants describe the pins. They won't change:
const int groundpin = A0;             // ground
const int powerpin = A4;              // voltage
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)

float filterVal = 0.25;       // this determines smoothness  - .0001 is max  1 is off (no smoothing)

//smoothed value of respective axis
float sVx = 0; 
float sVy = 0;
float sVz = 0;

float aV = 0; //acceleration vector
float aMax = 0;

void setup() {
  Serial.begin(9600);
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
  
}

void loop() {
  //smoothen the analog input from axis
  sVx = smooth(analogRead(xpin), sVx);
  sVy = smooth(analogRead(ypin), sVy);
  sVz = smooth(analogRead(zpin), sVz);
  
  aMax = (sVx>sVy?sVx:sVy)>sVz?(sVx>sVy?sVx:sVy):sVz; //select largest axis
  
  aV = sqrt(sq(sVx) + sq(sVy) + sq(sVz)); //acceleration vector
  aV = aMax<0?-aV:aV; //adjust direction of acceleration vector according to aMax

  Serial.print(aMax);
  Serial.print("\t");
  Serial.print(aV);
  Serial.println("");
  delay(50);
}

int smooth(int data, float smoothedVal){
  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);
  return (int)smoothedVal;
}



int dynamicAcc(int acc[], int accRead){
  int d = 0;
  acc[accIndex] = accRead;
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