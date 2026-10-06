# Source : https://github.com/digiampietro/arduino-makefile/

OSFAMILY    := $(shell ( uname | sed "s/-.*//" ))
MAKE_DIR    := $(PWD)
GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always --tags)
CFLAGS      := -D$(board)
CFLAGS      := --build-property build.extra_flags="$(CFLAGS)"

ifndef SERIAL_DEV
	ifneq (,$(wildcard /dev/ttyUSB0))
		SERIAL_DEV = /dev/ttyUSB0
	else ifneq (,$(wildcard /dev/ttyACM0))
		SERIAL_DEV = /dev/ttyACM0
	else
		SERIAL_DEV = unknown
	endif
endif

SRCINO     := $(wildcard *.ino)
SRC        := $(wildcard *.ino *.c *.cpp mylib/*/*.ino) 

ifeq ($(board), nanor4)
	FQBN := arduino:renesas_uno:nanor4
else ifeq ($(board), bluepill)
	FQBN := STMicroelectronics:stm32:GenF1
	OPTIONS = --board-options "pnum=BLUEPILL_F103CB"
	OPTIONS += --board-options "usb=CDCgen"
endif

BUILD_DIR  := $(subst :,.,build/$(FQBN))
BIN        := $(BUILD_DIR)/$(SRCINO).bin
HEX        := $(BUILD_DIR)/$(SRCINO).hex

all: compile upload

debug:
	$(info OSFAMILY    is [${OSFAMILY}])
	$(info GIT_VERSION is [${GIT_VERSION}])
	$(info FQBN        is [${FQBN}])
	$(info MAKE_DIR    is [${MAKE_DIR}])
	$(info BUILD_DIR   is [${BUILD_DIR}])
	$(info SRCINO      is [${SRCINO}])
	$(info SRC         is [${SRC}])
	$(info BIN         is [${BIN}])
	$(info HEX         is [${HEX}])
	$(info SERIAL_DEV  is [${SERIAL_DEV}])
	
compile:
	arduino-cli compile -b $(FQBN) $(CFLAGS) \
	$(OPTIONS) \
	--output-dir $(BUILD_DIR) \
	$(SRCINO) 
	
upload:
	arduino-cli upload -v -b $(FQBN) --input-file $(BIN) -p $(SERIAL_DEV)

test:
	$(shell ( sleep 1 ))
	arduino-cli monitor -p $(SERIAL_DEV) -b $(FQBN)
	
help:
	@echo "Usage: make board=<nanor4|bluepill> <compile|upload|test|debug>"
