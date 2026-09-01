#!/bin/bash
font_name=my_u8x8_font_7x14_1x2_r
./bin/bdfconv -v\
    -f 2\
    -m "32-134"\
    -th 1\
    -tv 2\
    bdf/my_7x14.bdf -o $font_name.h -n $font_name

