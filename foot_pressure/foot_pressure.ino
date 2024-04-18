#define LX   -1
#define LY  0.5
#define RX    1
#define RY  0.5
#define HY   -1

typedef struct {
  float x;
  float y;
} vector_t;

// Ports
int s1 = A0;
int s2 = A1;
int s3 = A2;

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
}

void loop() {
  // adding one to prevent divide by 0
  int left = analogRead(s1) + 1;
  int heel = analogRead(s2) + 1;
  int right = analogRead(s3) + 1;

  vector_t vec;
  vectorize(left, heel, right, &vec);

  delay(120);
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
