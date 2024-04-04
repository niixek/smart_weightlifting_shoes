int s1 = A0;
int s1_val = 0;

int s2 = A1;
int s2_val = 0;

int s3 = A2;
int s3_val = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  s1_val = analogRead(s1);
  s2_val = analogRead(s2);
  s3_val = analogRead(s3);

  delay(100);
  Serial.print(s1_val);
  Serial.print(",");
  Serial.print(s2_val);
  Serial.print(",");
  Serial.println(s3_val);
}
