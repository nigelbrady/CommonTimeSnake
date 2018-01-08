SDL_CFLAGS := $(shell sdl2-config --cflags)
SDL_LDFLAGS := $(shell sdl2-config --libs)
SDL_EXT_LIBS := -lSDL2_image

APP_NAME := CommonTimeSnake

FILES := *.cpp

run: clean build
	./$(APP_NAME)
build:
	g++ $(FILES) -o $(APP_NAME) $(SDL_CFLAGS) $(SDL_LDFLAGS) $(SDL_EXT_LIBS)
clean:
	rm -f $(APP_NAME)