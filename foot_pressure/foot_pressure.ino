int s1 = A0;
int left = 0;

int s2 = A1;
int heel = 0;

int s3 = A2;
int right = 0;

int check(int a, int b, int c) {
  // float rat1 = abs((a/b) - 1);
  // float rat2 = abs((b/c) - 1);
  // float rat3 = abs((c/a) - 1);
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  left = analogRead(s1);
  heel = analogRead(s2);
  right = analogRead(s3);

  delay(100);
  Serial.print(direction(left, heel, right));
  Serial.print(",");
  Serial.print(left);
  Serial.print(",");
  Serial.print(heel);
  Serial.print(",");
  Serial.println(right);
}
