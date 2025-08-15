enum State {
  GREEN,
  YELLOW_COMING_FROM_GREEN,
  RED,
  YELLOW,
  REDFLICKERING
};

class TrafficLight {
private:
  const int greenPin = 9;
  const int yellowPin = 10;
  const int redPin = 11;
  const int buttonA = 2;
  const int buttonB = 4;
  int amount = 0;
  State currentState;
  unsigned long lastUpdate;

  void setGreen() {
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, HIGH);
  }

  void setYellow() {
    digitalWrite(redPin, LOW);
    digitalWrite(yellowPin, HIGH);
    digitalWrite(greenPin, LOW);
  }

  void setRed() {
    digitalWrite(redPin, HIGH);
    digitalWrite(yellowPin, LOW);
    digitalWrite(greenPin, LOW);
  }

  // void setFlickering(){
  //   digitalWrite(redPin, LOW);
  //   digitalWrite(yellowPin, HIGH);
  //   digitalWrite(greenPin, LOW);
  // }

public:
  TrafficLight()
    : currentState(GREEN), lastUpdate(0) {
    pinMode(greenPin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(buttonA, INPUT_PULLUP);
    pinMode(buttonB, INPUT_PULLUP);
    setGreen();
  }

  void update(unsigned long now) {
    bool buttonAPressed = !digitalRead(buttonA);
    bool buttonBPressed = !digitalRead(buttonB);
    switch (currentState) {
      case GREEN:
        if (buttonAPressed) {
          currentState = YELLOW_COMING_FROM_GREEN;
          setYellow();
          Serial.println("Set to yellow");
          amount = 0;
          lastUpdate = now;
        }
        break;
      case YELLOW_COMING_FROM_GREEN:
        if (now - lastUpdate >= 500) {
          currentState = RED;
          setRed();
          Serial.println("Set to red");
          lastUpdate = now;
        }
        break;

      case RED:
        if (buttonBPressed) {
          Serial.println("Button B has been pressed");
          currentState = YELLOW;
          setYellow();
          Serial.println("Set to yellow");
          lastUpdate = now;
        }
        break;

      case YELLOW:
        if (now - lastUpdate >= 500) {
          currentState = REDFLICKERING;
          setRed();
          Serial.println("Set to red");
          lastUpdate = now;
        }
        if (amount > 4) {
          currentState = GREEN;
          setGreen();
          Serial.println("Set to green");
          lastUpdate = now;
        }
        break;
      
      case REDFLICKERING:
        if (now - lastUpdate >= 500) {
          currentState = YELLOW;
          setYellow();
          Serial.println("Set to red");
          amount ++;
          lastUpdate = now;
        }
        break;
        
        

        //lastUpdate = now;
    }
  }
};

TrafficLight trafficLight;

void setup() {
  Serial.begin(9600);  // Open Serial port
}

void loop() {
  trafficLight.update(millis());
}