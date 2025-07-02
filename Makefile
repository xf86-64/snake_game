
ROOT_SOURCE_DIR  = src
COMPILE_FLAGS    = -Wall 
LIBS             = -lncurses
CC               = gcc
BUILD_DIR_NAME 	 = bin
PROGRAM_NAME 	 = snake

build:	
	@if [ ! -d $(BUILD_DIR_NAME) ] ; then echo "I'm creating build dir..."; mkdir $(BUILD_DIR_NAME); echo "Done"; else echo "Directory already exists"; fi
	@if [ ! -f $(BUILD_DIR_NAME)/$(PROGRAM_NAME) ]; then echo "Compiling... (default mode)"; $(CC) -o $(BUILD_DIR_NAME)/$(PROGRAM_NAME) ${LIBS} ${ROOT_SOURCE_DIR}/*.c; fi
debug_build:	
	@if [ ! -d $(BUILD_DIR_NAME) ] ; then echo "I'm creating build dir..."; mkdir $(BUILD_DIR_NAME); echo "Done"; else echo "Directory already exists"; fi
	@if [ ! -f $(BUILD_DIR_NAME)/$(PROGRAM_NAME) ]; then echo "Compiling... (debug mode)"; $(CC) -o $(BUILD_DIR_NAME)/$(PROGRAM_NAME) -g ${LIBS} ${ROOT_SOURCE_DIR}/*.c; fi

clean:
	@if [ ! -d $(BUILD_DIR_NAME) ] ; then echo "no such directory"; else echo "Clean up..."; rm -rf $(BUILD_DIR_NAME); fi

