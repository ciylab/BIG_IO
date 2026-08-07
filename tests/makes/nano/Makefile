# Source : https://github.com/digiampietro/arduino-makefile/

OSFAMILY    := $(shell ( uname | sed "s/-.*//" ))
MAKE_DIR    := $(PWD)
# GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always --tags)

FQBN        ?= arduino:avr:nano
ifndef SERIAL_DEV
	ifneq (,$(wildcard /dev/ttyUSB0))
		SERIAL_DEV = /dev/ttyUSB0
	else ifneq (,$(wildcard /dev/ttyACM0))
		SERIAL_DEV = /dev/ttyACM0
	else
		SERIAL_DEV = unknown
	endif
endif

BUILD_DIR  := $(subst :,.,build/$(FQBN))

SRCINO     := $(wildcard *.ino)
SRC        := $(wildcard *.ino *.c *.cpp mylib/*/*.ino) 
HDRS       := $(wildcard *.h mylib/*/*.h)
BIN        := $(BUILD_DIR)/$(SRCINO).bin
HEX        := $(BUILD_DIR)/$(SRCINO).hex
ELF        := $(BUILD_DIR)/$(SRCINO).elf

$(info OSFAMILY    is [${OSFAMILY}])
$(info GIT_VERSION is [${GIT_VERSION}])
$(info FQBN        is [${FQBN}])
$(info IOT_NAME    is [${IOT_NAME}])
$(info IOT_IP      is [${IOT_IP}])
$(info OTA_PORT    is [${OTA_PORT}])
$(info OTA_PASS    is [${OTA_PASS}])
$(info V           is [${V}])
$(info VFLAG       is [${VFLAG}])
$(info MAKE_DIR    is [${MAKE_DIR}])
$(info BUILD_DIR   is [${BUILD_DIR}])
$(info SRCINO      is [${SRCINO}])
$(info SRC         is [${SRC}])
$(info HDRS        is [${HDRS}])
$(info BIN         is [${BIN}])
$(info HEX         is [${HEX}])
$(info SERIAL_DEV  is [${SERIAL_DEV}])
$(info CUSTOM_LIBS is [${CUSTOM_LIBS}])
$(info SPEEDLABEL  is [${SPEEDLABEL}])

all: compile upload

compile:
	arduino-cli compile -b $(FQBN) $(SRCINO) --output-dir $(BUILD_DIR)
	
upload:
	arduino-cli upload -p $(SERIAL_DEV) -b $(FQBN) -i $(HEX)

test:
	$(shell ( sleep 1 ))
	arduino-cli monitor -p $(SERIAL_DEV) -b $(FQBN)
	

