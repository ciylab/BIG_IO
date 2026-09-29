#!/usr/bin/bash

FQBN=arduino:renesas_uno:nanor4
BUILD_DIR=build/${FQBN//:/.}
SERIAL_DEV=/dev/ttyACM0

if [[ "$1" == "compile" ]]
then
    arduino-cli compile -b $FQBN --output-dir $BUILD_DIR
elif [[ "$1" == "upload" ]]
then
    arduino-cli upload -v -b $FQBN --input-dir $BUILD_DIR -p $SERIAL_DEV
elif [[ "$1" == "test" ]]
then
    arduino-cli monitor -p $SERIAL_DEV -b $FQBN
fi
