#ifdef bluebill
#define CLOCK_OUT PB3
#define GATE_1    PB5
#define GATE_2    PB4
#define TRIGGER_1 PB8
#define TRIGGER_2 PB9
#elif nanor4
#define CLOCK_OUT D6
#define GATE_1    D5
#define GATE_2    D4
#define TRIGGER_1 D3
#define TRIGGER_2 D2
#define LED A7
#endif

const byte pins[] = {
    CLOCK_OUT, GATE_2, GATE_1, TRIGGER_1, TRIGGER_2};

void pin_init() {
    pinMode(LED, OUTPUT);
    for(int i = 0; i < 5; i++) {
        pinMode(pins[i], OUTPUT);
    }
}

void test() {
    for(int i = 0; i < 5; i++) {
        digitalWrite(pins[i], HIGH);
        digitalWrite(LED, HIGH);
        delay(500);
        digitalWrite(pins[i], LOW);
        digitalWrite(LED, LOW);
        delay(500);
    }
}

void setup() {
    pin_init();
}

void loop() {
    test();
}
