// Pins voor RGB LED
const int RED_PIN = 9;
const int GREEN_PIN = 10;
const int BLUE_PIN = 11;

class BreatheLED {
public:
    BreatheLED(int redPin, int greenPin, int bluePin);
    void begin();
    void update();

private:
    int _redPin, _greenPin, _bluePin;
    float _brightness;
    int _direction;
};

BreatheLED::BreatheLED(int redPin, int greenPin, int bluePin)
    : _redPin(redPin), _greenPin(greenPin), _bluePin(bluePin), _brightness(0), _direction(1) {}

void BreatheLED::begin() {
    pinMode(_redPin, OUTPUT);
    pinMode(_greenPin, OUTPUT);
    pinMode(_bluePin, OUTPUT);
}

void BreatheLED::update() {
    _brightness += _direction * 1; // 1 staat voor de grootte van de stap

    if (_brightness >= 255) _direction = -1;
    if (_brightness <= 0)   _direction = 1;


    analogWrite(_redPin, _brightness);
    analogWrite(_greenPin, _brightness);
    analogWrite(_bluePin, _brightness);

    delay(10); // Snelheid van breathing
}

BreatheLED led(RED_PIN, GREEN_PIN, BLUE_PIN);

void setup() {
    led.begin();
}

void loop() {
    led.update();
    delay(10); // Aanpasbare snelheid
}