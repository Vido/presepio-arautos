const int STEP = 8;
const int DIRECTION = 9;
const int ENABLE = 10;

unsigned long intervalo;
byte dir = true;
byte step = false;

void setup()
{
  pinMode(STEP, OUTPUT);
  pinMode(DIRECTION, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  digitalWrite(STEP, LOW);
  digitalWrite(DIRECTION, HIGH);
  digitalWrite(ENABLE, HIGH);
}

void loop()
{
  intervalo = millis() + 1000;
  while(intervalo > millis())
  {
    step = !step;
    digitalWrite(STEP, step);
    delayMicroseconds(500);
  }
  dir = !dir;
  digitalWrite(DIRECTION, dir);
}
