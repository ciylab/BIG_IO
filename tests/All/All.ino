#include <U8x8lib.h>
#include <SPI.h>
#include <MIDI.h>
#include <Versatile_RotaryEncoder.h>

#define CLOCK_OUT PB3
#define GATE_1 PB5
#define GATE_2 PB4
#define TRIGGER_1 PB8
#define TRIGGER_2 PB9
#define CLOCK_IN PA3 
#define CS1 PA4
#define CS2 PC15

#define l_clk PB0
#define l_dt PB1
#define l_sw PB10
#define r_clk PA1
#define r_dt PA0
#define r_sw PA2
#define GATE_TIME 100
#define CV_TIME 1000
#define MIDI_TIME 1000

MIDI_CREATE_DEFAULT_INSTANCE();
U8X8_SSD1306_128X64_NONAME_HW_I2C u8x8(U8X8_PIN_NONE);
Versatile_RotaryEncoder *left;
Versatile_RotaryEncoder *right;


const byte pins[] = {
    CLOCK_OUT, GATE_2, GATE_1, TRIGGER_1, TRIGGER_2};
int gate_num;
unsigned long now;
unsigned long gate_past;
unsigned long cv_past;
unsigned long midi_past;
int cv_value;
bool note_on;
bool clock_in;

void dac_write(int ch, int cv) {
    if (ch == 0) {
        digitalWrite(CS1, LOW);
        SPI.transfer((cv >> 8) | 0x30);  // H0x30=OUTA/1x
        SPI.transfer(cv & 0xff);
        digitalWrite(CS1, HIGH);
    } else if(ch == 1) {
        digitalWrite(CS1, LOW);
        SPI.transfer((cv >> 8) | 0xB0);  // H0xB0=OUTB/1x
        SPI.transfer(cv & 0xff);
        digitalWrite(CS1, HIGH);
    } else if(ch == 2) { // MCP4921
        digitalWrite(CS2, LOW);
        SPI.transfer((cv >> 8) | 0x30);  // H0x30=OUTA/1x
        SPI.transfer(cv & 0xff);
        digitalWrite(CS2, HIGH);    
    }
}

void gates_init() {
    gate_num = 0;
    for(int i = 0; i < 5; i++) {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], HIGH);
    }
    digitalWrite(pins[0], LOW);
    gate_past = millis();
}

void CV_init() {
    pinMode(CS1, OUTPUT);
    pinMode(CS2, OUTPUT);
    digitalWrite(CS1, HIGH);
    digitalWrite(CS2, HIGH);
    SPI.begin();
    dac_write(0, 4095);
    dac_write(1, 4095);
    dac_write(2, 4095);
    cv_past = millis();
    cv_value = 4095;
}

void oled_init() {
    u8x8.begin();
    u8x8.setFont(u8x8_font_7x14_1x2_r);
    u8x8.drawString(0,0,"  BIG InOut");
    u8x8.drawString(0,2,"  MIDI/CV/GATE");
    u8x8.drawString(0,4,"  by CIYLab");
    u8x8.drawString(0,6,"  v0.0.0");    
}

void midi_init() {
    MIDI.begin(MIDI_CHANNEL_OMNI);
    note_on = true;
}

void encoder_init() {
	left = new Versatile_RotaryEncoder(l_clk, l_dt, l_sw);
    left->setHandlePress(l_handlePress);
	right = new Versatile_RotaryEncoder(r_clk, r_dt, r_sw);
    right->setHandlePress(r_handlePress);
}

void l_handlePress() {
	Serial.println("Left Pressed");
}

void r_handlePress() {
	Serial.println("Right Pressed");
}

void clock_in_init() {
    clock_in = false;
}

void test_gates() {
    if (now - gate_past > GATE_TIME) {
        digitalWrite(pins[gate_num], HIGH);
        gate_num = (gate_num + 1) % 5;
        digitalWrite(pins[gate_num], LOW);
        gate_past += GATE_TIME;
    }
}

void test_CV() {
    if (now - cv_past > CV_TIME) {
        dac_write(0, cv_value);
        dac_write(1, cv_value);
        dac_write(2, cv_value);
        cv_value = 4095 - cv_value;
        cv_past += CV_TIME;
    }
}

void test_midi_in() {
    if (MIDI.read()) {

    } 
}

void test_clock_in () {
    int value = analogRead(CLOCK_IN);
    if(value < 100 && clock_in) {
        clock_in = false;
        Serial.println("STOP");
    } else if (value > 900 && !clock_in) {
        clock_in = true;
        Serial.println("START");
    }
}

void test_midi_out() {
    if (now - midi_past > MIDI_TIME) {
        if (!note_on) {
            MIDI.sendNoteOn(42, 127, 1);
        } else {
            MIDI.sendNoteOff(42, 0, 1);
        }
        midi_past += MIDI_TIME;
        note_on = !note_on;
    } 
}

void test_encoder() {
    if (left->ReadEncoder() || right->ReadEncoder()) {
        // Do something here whenever an encoder action is read
    }
}
    
void setup() {
    Serial.begin(9600);
    gates_init();
    oled_init();
    CV_init();
    midi_init();
    clock_in_init();
    encoder_init();
    now = millis();
}

void loop() {
    now = millis();
    test_gates();
    test_CV();
    test_midi_in();
    test_midi_out();
    test_encoder();
    test_clock_in();
}
