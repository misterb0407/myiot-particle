# Makefile for the Particle Workbench
# Supports local compile and local flash for Particle projects
#
# Inputs:
# PARTICLE_CLI_PATH: path to the Particle CLI executable
# APPDIR: path to the user application sources
# DEVICE_OS_PATH: path to the source code of the Particle DeviceOS
# PLATFORM: the name of the Particle platform to compile for
# PLATFORM_ID: the id of the Particle platform to compile for

version = 1.9.2
all: flash-all

# Set target build output directory
export TARGET_DIR = $(value APPDIR)/target/$(value DEVICE_OS_VERSION)/$(value PLATFORM)

# Convert Wiring files (ino) files to C++ files (cpp)
INO_FILES := $(wildcard $(value APPDIR)/*.ino) $(wildcard $(value APPDIR)/src/*.ino)
PREPROCESSED_FILES := $(patsubst %.ino,%.cpp,$(value INO_FILES))

preprocess: $(value PREPROCESSED_FILES)
$(value PREPROCESSED_FILES): %.cpp: %.ino
	@"$(value PARTICLE_CLI_PATH)" preprocess $< --no-update-check --quiet

dfu:
	$(call print_stage,PUTTING DEVICE INTO DFU MODE)
	-@"$(value PARTICLE_CLI_PATH)" usb dfu $(value PARTICLE_DEVICE_ID) --no-update-check --quiet
	@sleep 2

# Get rid of compiled files in the user part
clean-user: preprocess
	$(call print_stage,CLEANING APPLICATION)
	cd "$(value DEVICE_OS_PATH)/main" && make clean
	$(call print_success,CLEANED SUCCESSFULLY)

# Get rid of compiled files in the user and system parts
clean-all: preprocess
	$(call print_stage,CLEANING APPLICATION & DEVICE OS)
	cd "$(value DEVICE_OS_PATH)/modules" && make clean
	$(call print_success,CLEANED SUCCESSFULLY)

# Get rid of compiled files for debug build
clean-debug: preprocess
	$(call print_stage,CLEANING APPLICATION FOR DEBUG)
	cd "$(value DEVICE_OS_PATH)/main" && make clean MODULAR=n USE_SWD_JTAG=y DEBUG_BUILD=y
	$(call print_success,CLEANED SUCCESSFULLY)

# Get rid of everything
sanitize: | clean-debug clean-all

# Compile the user part
compile-user: preprocess
	$(call print_stage,COMPILING APPLICATION)
	cd "$(value DEVICE_OS_PATH)/main" && make all
	$(call print_success,COMPILED SUCCESSFULLY)

# Compile the user and system parts
compile-all: preprocess
	$(call print_stage,COMPILING APPLICATION & DEVICE OS)
	cd "$(value DEVICE_OS_PATH)/modules" && make all
	$(call print_success,COMPILED SUCCESSFULLY)

# Compile debug build
compile-debug: preprocess
	$(call print_stage,COMPILING APPLICATION FOR DEBUG)
	cd "$(value DEVICE_OS_PATH)/main" && make all MODULAR=n USE_SWD_JTAG=y DEBUG_BUILD=y
	$(call print_success,COMPILED SUCCESSFULLY)

# Compile and flash the user part
flash-user: dfu preprocess
	$(call print_stage,FLASHING APPLICATION)
	cd "$(value DEVICE_OS_PATH)/main" && make all program-dfu
	$(call print_success,FLASHED SUCCESSFULLY)

# Compile and flash the user and system parts
flash-all: dfu preprocess
	$(call print_stage,FLASHING APPLICATION & DEVICE OS)
	cd "$(value DEVICE_OS_PATH)/modules" && make all program-dfu
	$(call print_success,FLASHED SUCCESSFULLY)

# Compile and flash debug build
flash-debug: dfu preprocess
	$(call print_stage,FLASHING APPLICATION FOR DEBUG)
	cd "$(value DEVICE_OS_PATH)/main" && make all program-dfu MODULAR=n USE_SWD_JTAG=y DEBUG_BUILD=y
	$(call print_notice,ONCE YOU ARE FINISHED DEBUGGING REMEMBER TO RUN `Particle: Flash application & DeviceOS (local)`)
	$(call print_success,FLASHED SUCCESSFULLY)

help:
	@echo '┌──────────++++'
	@echo '│ Particle Local Compiler'
	@echo '│'
	@echo '│ Current Configuration'
	@echo '│   $$PLATFORM - $(value PLATFORM)'
	@echo '│   $$PLATFORM_ID - $(value PLATFORM_ID)'
	@echo '│   $$APPDIR - $(value APPDIR)'
	@echo '│   $$EXTRA_CFLAGS - $(value EXTRA_CFLAGS)'
	@echo '│   $$DEVICE_OS_PATH - $(value DEVICE_OS_PATH)'
	@echo '│   $$PARTICLE_DEVICE_ID - $(value PARTICLE_DEVICE_ID)'
	@echo '│'
	@echo '│ Available Environment Variables'
	@echo '│   PLATFORM - type of hardware (e.g. photon)'
	@echo '│   PLATFORM_ID - hardware id (e.g. 6)'
	@echo '│   APPDIR - path to your project source files'
	@echo '│   EXTRA_CFLAGS - custom symbols to pass to your application source code'
	@echo '│   DEVICE_OS_PATH - path to device os you are building against'
	@echo '│   PARTICLE_DEVICE_ID - name or id of your device'
	@echo '│   PARTICLE_MAKEFILE - path to main build script'
	@echo '│'
	@echo '│ Available Targets'
	@echo '│   clean-user - clean user application build'
	@echo '│   clean-all - clean user application and device os builds'
	@echo '│   clean-debug - clean monolithic debug build'
	@echo '│   compile-user - compile user application'
	@echo '│   compile-all - compile user application and device os'
	@echo '│   compile-debug - compile monolithic user application and device os in debug mode'
	@echo '│   flash-user - flash user application'
	@echo '│   flash-all - flash user application and device os'
	@echo '│   flash-debug - flash monolithic user application and device os in debug mode'
	@echo '│'
	@echo '│ Usage'
	@echo '│   make -f $$PARTICLE_MAKEFILE compile-user'
	@echo '│   make -f $$PARTICLE_MAKEFILE compile-user PLATFORM=electron'
	@echo '│   make -f $$PARTICLE_MAKEFILE flash-user EXTRA_CFLAGS="-DFLAG_ONE=abc -DFLAG_TWO=123"'
	@echo '│   DEVICE_OS_PATH=/path/to/device-os make -f $$PARTICLE_MAKEFILE flash-user'
	@echo '│'
	@echo '├─────++++'
	@echo '│ NOTE: THIS TERMINAL WILL RELAUNCH AFTER CHANGING PROJECT SETTINGS'
	@echo '└─────++++'

.PHONY: all preprocess clean-user clean-all clean-debug compile-user compile-all compile-debug flash-user flash-all flash-debug help

define print_stage
	@echo ''
	@echo ':::: $(1)'
	@echo ''
endef

define print_notice
	@echo ''
	@echo '> $(1) <'
	@echo ''
endef

define print_success
	@echo ''
	@echo '*** $(1) ***'
	@echo ''
endef

