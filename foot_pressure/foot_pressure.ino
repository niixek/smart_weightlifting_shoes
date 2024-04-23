#define LX   -1
#define LY  0.5
#define RX    1
#define RY  0.5
#define HY   -1

const int numReadings = 10;   // Number of readings to average
int readings_s1[numReadings];    // Array to store the readings
int readings_s2[numReadings];    // Array to store the readings
int readings_s3[numReadings];    // Array to store the readings
int index = 0;                // Current index in the array
int total_s1 = 0;                // Running total of all readings
int total_s2 = 0;                // Running total of all readings
int total_s3 = 0;                // Running total of all readings
int average_s1 = 0;              // Moving average
int average_s2 = 0;              // Moving average
int average_s3 = 0;              // Moving average

typedef struct {
  float x;
  float y;
} vector_t;

// Ports
int s1 = A0;
int s2 = A1;
int s3 = A2;

// optimal vector
vector_t o_vec;

void update_moving_avg(float left, float heel, float right) {
  // Read a new value
  int sensorValue_s1 = left;
  int sensorValue_s2 = heel;
  int sensorValue_s3 = right;

  // Subtract the oldest reading from the total
  total_s1 -= readings_s1[index];
  total_s2 -= readings_s2[index];
  total_s3 -= readings_s3[index];
  
  // Store the new reading in the array
  readings_s1[index] = sensorValue_s1;
  readings_s2[index] = sensorValue_s2;
  readings_s3[index] = sensorValue_s3;

  // Add the new reading to the total
  total_s1 += sensorValue_s1;
  total_s2 += sensorValue_s2;
  total_s3 += sensorValue_s3;

  // Increment the index
  index = (index + 1) % numReadings;

  // Calculate the moving average
  average_s1 = total_s1 / numReadings;
  average_s2 = total_s2 / numReadings;
  average_s3 = total_s3 / numReadings;

  // Print the average
  // Serial.println(average_s1);
  // Serial.println(average_s2);
  // Serial.println(average_s3);

  // Delay for stability
  //delay(100);
}

int check(int a, int b, int c) {
  float rat1 = abs(a-b);
  float rat2 = abs(b-c);
  float rat3 = abs(c-a);
  return (rat1 + rat2 + rat3) < 50;
}

char* direction(int a, int b, int c) {
  if (a > 700 && b < 20 && c > 700)
    return "forward";
  if (a < 20 && b > 200 && c < 100)
    return "backward";
  if (a < 50 && b < 200 && c > 700)
    return "right";
  if (a > 700 && b < 200 && c < 500)
    return "left";
  return "center";
}

void vectorize(float left, float heel, float right, vector_t *vec) {
  float norm = sqrt(left*left + heel*heel + right*right);
  float lnorm = left / norm;
  float hnorm = heel / norm;
  float rnorm = right / norm;
  vec->x = LX*lnorm + RX*rnorm;
  vec->y = LY*lnorm + RY*rnorm + HY*hnorm;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Initialize all readings to 0
  for (int i = 0; i < numReadings; i++) {
    readings_s1[i] = 0;
    readings_s2[i] = 0;
    readings_s3[i] = 0;
  }
}

void loop() {
  // adding one to prevent divide by 0
  int left = analogRead(s1) + 1;
  int heel = analogRead(s2) + 1;
  int right = analogRead(s3) + 1;

  if((left + heel + right) - (average_s1 + average_s2 + average_s3) > 100 && (average_s1 + average_s2 + average_s3) > 150) {
    vectorize(average_s1, average_s2, average_s3, &o_vec);
    Serial.print("u,");
  } else {
    Serial.print("n,");
    update_moving_avg(left, heel, right);
  }

  vector_t vec;
  vectorize(left, heel, right, &vec);

  delay(110);
  //Serial.print(direction(left, heel, right));
  Serial.print(vec.x);
  Serial.print(",");
  Serial.print(vec.y);
  Serial.print(",");
  Serial.print(left);
  Serial.print(",");
  Serial.print(heel);
  Serial.print(",");
  Serial.println(right);
}
