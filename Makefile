COMPILER_FLAGS := -g -O2
DEBUG_COMPILER_FLAGS := -g
SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
SDL_EXT_LIBS := -lSDL2_image -lSDL2_ttf

APP_NAME := CommonTimeSnake

FILES := *.cpp

run: clean build
	./$(APP_NAME)
debug: clean debug-build
	lldb ./$(APP_NAME)
debug-build:
	g++ $(DEBUG_COMPILER_FLAGS) $(FILES) -o $(APP_NAME) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(SDL_EXT_LIBS)
build:
	g++ $(COMPILER_FLAGS) $(FILES) -o $(APP_NAME) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(SDL_EXT_LIBS)
clean:
	rm -f $(APP_NAME)