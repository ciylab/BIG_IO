#define CLOCK PB3
#define GATE_1 PB5
#define GATE_2 PB4
#define TRIGGER_1 PB8
#define TRIGGER_2 PB9

const byte pins[] = {
    CLOCK, GATE_2, GATE_1, TRIGGER_1, TRIGGER_2};

void pin_init() {
    for(int i = 0; i < 5; i++) {
        pinMode(pins[i], OUTPUT);
    }
}

void test() {
    for(int i = 0; i < 5; i++) {
        digitalWrite(pins[i], LOW);
        delay(500);
        digitalWrite(pins[i], HIGH);
    }
}

void setup() {
    pin_init();
}

void loop() {
    test();
}
