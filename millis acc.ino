// these constants describe the pins. They won't change:
//const int groundpin = A1;             // ground
//const int powerpin = A5;              // voltage
const int xpin = A0;                  // x-axis of the accelerometer
const int ypin = A1;                  // y-axis
const int zpin = A2;                  // z-axis (only on 3-axis models)

float filterVal = 0.2;       // this determines smoothness  - .0001 is max  1 is off (no smoothing)

//smoothed value of respective axis
float sVx = 0; 
float sVy = 0;
float sVz = 0;

float aV = 0; //acceleration vector
float aMax = 0;

void setup() {
  
  
}

void loop() {
  //smoothen the analog input from axis
  sVx = smooth(analogRead(xpin), sVx);
  sVy = smooth(analogRead(ypin), sVy);
  sVz = smooth(analogRead(zpin), sVz);
  
  aMax = (sVx>sVy?sVx:sVy)>sVz?(sVx>sVy?sVx:sVy):sVz; //select largest axis
  
  aV = sqrt(sq(sVx) + sq(sVy) + sq(sVz)); //acceleration vector
  aV = aMax<0?-aV:aV; //adjust direction of acceleration vector according to aMax
}

int smooth(int data, float smoothedVal){
  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);
  return (int)smoothedVal;
}
