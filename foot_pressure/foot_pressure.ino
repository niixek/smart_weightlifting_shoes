#include <string.h>
#include <FastLED.h>

#define LX   -1
#define LY  0.5
#define RX    1
#define RY  0.5
#define HY   -1
#define BRIGHT 10

#define LED_PIN     6
#define NUM_LEDS    12

CRGB leds[NUM_LEDS];

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


vector_t vec;

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

/*char* direction(int a, int b, int c) {
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
*/

void vectorize(float left, float heel, float right, vector_t *vec) {
  float norm = sqrt(left*left + heel*heel + right*right);
  float lnorm = left / norm;
  float hnorm = heel / norm;
  float rnorm = right / norm;
  vec->x = LX*lnorm + RX*rnorm;
  vec->y = LY*lnorm + RY*rnorm + HY*hnorm;
}

//0 = center
//1 = left
//2 = right
//3 = forward
//4 = backward
int direction(vector_t opt, vector_t vec, float threshold) {
  float resx = opt.x - vec.x;
  float resy = opt.y - vec.y;

  if ((abs(resx) < threshold) && (abs(resy) < threshold)) {
    return 0;
  }

  float rad = atan2(resy, resx);
  Serial.print(rad);

  if ((rad >= 2.35619 && rad <= 3.14159) || (rad >= -3.14159 && rad <= -2.35619)) {
    return 1;
  }

  if ((rad >= 0 && rad <= 0.785398) || (rad <= 0 && rad >= -0.785398)) {
    return 2;
  }

  if (rad >= 0.785398 && rad <= 2.35619) {
    return 3;
  }

  if (rad <= -0.785398 && rad >= -2.35619) {
    return 4;
  }

}

char* printdir(int code) {
  if (code == 0) { 
    return "centered";
  }
  if (code == 1) { 
    return "left";
  }
  if (code == 2) { 
    return "right";
  }
  if (code == 3) { 
    return "forward";
  }
  if (code == 4) { 
    return "backward";
  }
}

void lightHelper(int dir) {

    int start, end;
    CRGB color;

    start = 0;
    end = NUM_LEDS;
    color = CRGB(0, BRIGHT, 0);

    FastLED.clear();
    
    if (dir == 3) {
        start = 0;
        end = start + NUM_LEDS / 4;
        color = CRGB(BRIGHT, 0, 0);
    } 

    if (dir == 2) {
        start = NUM_LEDS / 4;
        end = start + NUM_LEDS / 4;
        color = CRGB(BRIGHT, 0, 0);
    } 

    if (dir == 4) {
        start = 2 * (NUM_LEDS / 4);
        end = start + NUM_LEDS / 4;
        color = CRGB(BRIGHT, 0, 0);
    } 

    if (dir == 1) {
        start = 3 * (NUM_LEDS / 4);
        end = start + NUM_LEDS / 4;
        color = CRGB(BRIGHT, 0, 0);
    } 

    for (int i = start; i < end; i++) {
        leds[i] = color;
    }

    FastLED.show(); // Show the updated LED colors
}

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear(); // Clear all LEDs
  FastLED.show();  // Make sure to call show() to update the LEDs
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Initialize all readings to 0
  // for (int i = 0; i < numReadings; i++) {
  //   readings_s1[i] = 0;
  //   readings_s2[i] = 0;
  //   readings_s3[i] = 0;
  // }
}

void loop() {
  vector_t o_vec;
  o_vec.x = -0.45;
  o_vec.y = 0.40;
  // adding one to prevent divide by 0
  int left = analogRead(s1) + 1;
  int heel = analogRead(s2) + 1;
  int right = analogRead(s3) + 1;

  int dir = -1;

  // if((left + heel + right) - (average_s1 + average_s2 + average_s3) > 100 && (average_s1 + average_s2 + average_s3) > 150) {
  //vectorize(average_s1, average_s2, average_s3, &o_vec);
  // Serial.print("n,");

  vectorize(left, heel, right, &vec);

  dir = direction(o_vec, vec, 0.2);
  lightHelper(dir);
  Serial.print(printdir(dir));
  // } else {
    // Serial.print("u,");
    // Serial.print(vec.x);
    // Serial.print(",");
    // Serial.print(vec.y);
    // Serial.print(",");
    // Serial.print(average_s1);
    // Serial.print(",");
    // Serial.print(average_s2);
    // Serial.print(",");
    // Serial.print(average_s3);
    Serial.print(",");
    Serial.print(left);
    Serial.print(",");
    Serial.print(heel);
    Serial.print(",");
    Serial.println(right);
  //   update_moving_avg(left, heel, right);
  // }

  delay(110);
    // Serial.print(left);
    // Serial.print(",");
    // Serial.print(heel);
    // Serial.print(",");
    // Serial.println(right);
    Serial.print(vec.x);
    Serial.print(",");
    Serial.println(vec.y);
  
}
