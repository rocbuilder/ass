

// these constants describe the pins. They won't change:
const int groundpin = A0;             // ground
const int powerpin = A4;              // voltage
const int xpin = A3;                  // x-axis of the accelerometer
const int ypin = A2;                  // y-axis
const int zpin = A1;                  // z-axis (only on 3-axis models)
int x = 0;
int y = 0;
int z = 0;


float filterVal = 0.25;       // this determines smoothness  - .0001 is max  1 is off (no smoothing)

//smoothed value of respective axis
float sVx = 0; 
float sVy = 0;
float sVz = 0;

float aV = 0; //acceleration vector
float aMax = 0;

const int dnmcLen = 10; //how many values in dynamic array
int dnmcIndex =0
int dnmc[3];
unsigned long dnmcTimer = 0;
unsigned long dnmcDelay = 60000;
int dx = 0;
int dy = 0;
int dz = 0;

void setup() {
  Serial.begin(9600);
  pinMode(groundpin, OUTPUT);
  pinMode(powerpin, OUTPUT);
  digitalWrite(groundpin, LOW);
  digitalWrite(powerpin, HIGH);
  
}

void loop() {
  x = analogRead(xpin);
  y = analogRead(ypin);
  z = analogRead(zpin);

if () {//millis timer-dynamic timer > dynamic delay
  dnmc[0] += x;
  dnmc[1] += y;
  dnmc[2] += z;
  dnmcIndex ++;
  if () { //index > length
    //dynamic timer = millis
    dnmcIndex = 0;
    dx = dnmc[0]/dnmcLen;
    dy = dnmc[1]/dnmcLen;
    dz = dnmc[2]/dnmcLen;
  }
}


  //smoothen the analog input from axis
  sVx = smooth(x, sVx);
  sVy = smooth(y, sVy);
  sVz = smooth(z, sVz);
  
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