int redPin = 10;    // LED connected to digital pin 9
int greenPin = 6;
int bluePin  = 5;

long inhale = 2500;
int  hold = 500;
long exhale = 3000;
int  loopDelay = 30;

void setup()  {
  // nothing happens in setup
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void printRGB(int r, int g, int b){
  Serial.print(r);
  Serial.print(',');
  Serial.print(g);
  Serial.print(',');
  Serial.println(b);
}

void loop()  {
  int blueValue  = 0;
  int greenValue = 0;
  int redValue   = 0;

  int blueGrowth  = random(8);
  int greenGrowth = random(8);
  int redGrowth   = random(8);

  long time = millis();

  // fade in from min to max in increments of 5 points:
  while(true) {
    printRGB(blueValue, greenValue, redValue);

    // sets the value (range from 0 to 255):
    analogWrite(redPin, redValue);
    analogWrite(bluePin, blueValue);
    analogWrite(greenPin, greenValue);

    if(blueValue + blueGrowth < 255)   blueValue  += blueGrowth;
    if(greenValue + greenGrowth < 255) greenValue += greenGrowth;
    if(redValue + redGrowth < 255)     redValue   += redGrowth;

    if((millis() - time) > inhale) break;
    // wait for 30 milliseconds to see the dimming effect
    delay(loopDelay);
  }

  delay(hold);

  time = millis();

  // fade out from max to min in increments of 5 points:
  while(true) {
    if(blueValue > 0) blueValue -= blueGrowth;
    if(greenValue > 0) greenValue -= greenGrowth;
    if(redValue > 0) redValue -= redGrowth;
    printRGB(blueValue, greenValue, redValue);

    // sets the value (range from 0 to 255):
    analogWrite(redPin, redValue);
    analogWrite(bluePin, blueValue);
    analogWrite(greenPin, greenValue);

    if((millis() - time) > exhale) break;
    // wait for 30 milliseconds to see the dimming effect
    delay(loopDelay);
  }

  delay(hold);
}
