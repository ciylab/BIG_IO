#ifdef bluepill
#define CLOCK_OUT PB14
#define GATE_1    PB13
#define GATE_2    PA11
#define GATE_3    PB15
#define DRUM      PB12
#define LED       PB9
#elif nanor4
#define CLOCK_OUT D6
#define GATE_1    D5
#define GATE_2    D4
#define TRIGGER_1 D3
#define TRIGGER_2 D2
#define LED A7
#endif

const byte pins[] = {
    CLOCK_OUT, DRUM, GATE_1, GATE_2, GATE_3, LED};

void pin_init() {
    for(int i = 0; i < 6; i++) {
        pinMode(pins[i], OUTPUT);
    }
}

void test() {
    for(int i = 0; i < 6; i++) {
        digitalWrite(pins[i], HIGH);
    }
    delay(500);
    for(int i = 0; i < 6; i++) {
        digitalWrite(pins[i], LOW);
    }
    delay(500);
}

void setup() {
    Serial.end();
    pin_init();
}

void loop() {
    test();
}
