# Source : https://github.com/digiampietro/arduino-makefile/

ifeq ($(board), nanor4)
	FQBN := arduino:renesas_uno:nanor4
	BOARD := NANOR4
else ifeq ($(board), bluepill)
	FQBN := STMicroelectronics:stm32:GenF1
	BOARD := STM32F103C8T6
	OPTIONS = --board-options "pnum=BLUEPILL_F103CB"
	OPTIONS += --board-options "usb=CDCgen"
endif

ifneq (,$(wildcard Doxyfile))
	DOXYFILE    := Doxyfile
endif

ifneq (,$(wildcard ../ciylab.github.io))
	JEKYLL_DIR  := ../ciylab.github.io
endif

ifndef PORT
	ifneq (,$(wildcard /dev/ttyUSB0))
		PORT = /dev/ttyUSB0
	else ifneq (,$(wildcard /dev/ttyACM0))
		PORT = /dev/ttyACM0
	else
		PORT = unknown
	endif
endif

OSFAMILY    := $(shell ( uname | sed "s/-.*//" ))
PROJECT     := $(notdir $(CURDIR))
VERSION     := $(shell git describe --abbrev=0)
CFLAGS      := -DDEBUG -DVERSION=\"$(VERSION)\" -D$(board)
CFLAGS      := --build-property build.extra_flags="$(CFLAGS)"
BIN_DIR     := $(subst :,.,bin/$(FQBN))
SRCINO      := $(PROJECT).ino
BIN         := $(BIN_DIR)/$(SRCINO).bin
DOCS        := docs
MODULES     := $(wildcard $(DOCS)/modules/*.md)
SRC	        := src
HEADERS     := $(wildcard $(SRC)/*.h)
HEADERS     := $(HEADERS) $(wildcard $(SRC)/modules/*.h)
METADATA    = $(DOCS)/metadata.yaml
MAN         = $(DOCS)/MANUAL_FR.md
MANIFEST    := ../arduino-manifest/arduino-manifest.pl

all: debug compile upload clean docs
	
compile: $(SRCINO)
	$(info **************** build $(VERSION))
	@arduino-cli compile --warnings more \
	-b $(FQBN) $(CFLAGS) \
	$(OPTIONS) \
	--output-dir $(BIN_DIR) \
	$(SRCINO)
	@cp $(BIN) bin/firmware_$(BOARD).bin
	 
clean: 
	$(info **************** delete unused binaries files) 
	@rm -fr $(BIN_DIR)
		
upload:
	arduino-cli upload -v -b $(FQBN) \
	--input-file $(BIN) -p $(PORT)
	
doxygen: 
	$(info **************** create html)
	@doxygen $(DOXYFILE) 1> /dev/null 2>&1
	
test:
	$(shell ( sleep 1 ))
	arduino-cli monitor -p $(PORT) -b $(FQBN)
	
.PHONY: tags
tags:
	$(info **************** create tags)
	@ctags -R $(SRCINO) src
	
metadata:
	$(info **************** create metadata.yaml)
	@echo "---\nlayout: page" > $(METADATA)
	@echo "title: $(PROJECT)\nsubtitle: version $(VERSION)" >> $(METADATA)
	@echo "author: Pierrick MEIGNEN" >> $(METADATA)
	@echo "email: contact@ciylab.com" >> $(METADATA)
	@echo "lang: fr-FR\nfontfamily: times" >> $(METADATA)
	@echo "header-includes:" >> $(METADATA)
	@echo '  - \\renewcommand{\\familydefault}{\sfdefault}' >> $(METADATA)
	@echo "---\n" >> $(METADATA)
	@echo "![Paramètres](assets/images/$(PROJECT)_menus.png)\n" >> $(METADATA)	

.PHONY: man
man: metadata
	$(info **************** create MANUAL_FR.md)
	@cat $(METADATA) > $(MAN)
	@cat $(DOCS)/Main.md >> $(MAN)
	@cat $(MODULES) >> $(MAN)
	@cat $(DOCS)/Tech.md >> $(MAN)
	@soffice --convert-to png --outdir docs docs/menus.odg 1> /dev/null 2>&1
	@mogrify -resize 75% docs/menus.png
	@cp docs/menus.png docs/assets/images/$(PROJECT)_menus.png
	@mv docs/menus.png $(JEKYLL_DIR)/assets/images/$(PROJECT)_menus.png
	@cd docs; \
	pandoc MANUAL_FR.md -V geometry:margin=2cm -o ../man/$(PROJECT)_MANUAL_FR.pdf
	@mv docs/MANUAL_FR.md $(JEKYLL_DIR)/$(PROJECT)_MANUAL_FR.md
	
manifest:
	$(info **************** create requirements.txt)
	@$(MANIFEST) -v -r -b $(FQBN) $(SRCINO) $(HEADERS) > requirements.txt
	
.PHONY: docs
docs: doxygen tags man manifest
	
help:
	@echo "Usage: make OPTION where OPTION is"
	@echo "    - all"
	@echo "    - compile"
	@echo "    - clean"
	@echo "    - upload"
	@echo "    - docs"
	@echo "    - help"
	@echo "    - debug"
	@echo "    - test"
		
debug:
	$(info **************** infos)
	@echo projet = $(PROJECT)
	@echo version = $(VERSION)
	@echo fqbn = $(FQBN)
	@echo board = $(BOARD)
	@echo cflags = $(CFLAGS)
	@echo bin_dir = $(BIN_DIR)
	@echo srcino = $(SRCINO)
	@echo bin = $(BIN)
	@echo port = $(PORT)
	@echo doxyfile = $(DOXYFILE)
	@echo docs = $(DOCS)
	@echo src = $(SRC)
	@echo headers = $(HEADERS)
	@echo modules = $(MODULES)
	@echo metada = $(METADATA)
	@echo manual = $(MAN)
	@echo jekyll = $(JEKYLL_DIR)
	@echo manifest = $(MANIFEST)

