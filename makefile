# Only X11 for now, wayland later
# uses opengl api by default

CC	= 	gcc -std=gnu11 -DUSE_OPENGL_API 
INC 	=	-Isrc/minifb/include -Isrc/minifb/src -Isrc/minifb/src/x11
LIN 	=	-lX11	

all:
	@mkdir -p build
	@$(CC) -c $(INC) $(LIN) src/minifb/src/MiniFB_common.c -o build/MiniFB_common.o
	@$(CC) -c $(INC) $(LIN) src/minifb/src/MiniFB_internal.c -o build/MiniFB_internal.o
	@$(CC) -c $(INC) $(LIN) src/minifb/src/MiniFB_linux.c -o build/MiniFB_linux.o 
	@$(CC) -c $(INC) $(LIN) src/minifb/src/MiniFB_timer.c -o build/MiniFB_timer.o
	@$(CC) -c $(INC) -Iinclude/gl -lGL -lglfw src/minifb/src/gl/MiniFB_GL.c -o build/MiniFB_GL.o
	@$(CC) -c $(INC) $(LIN) src/minifb/src/x11/X11MiniFB.c -o build/X11MiniFB.o
	@ar rcs build/libsyskFB.a build/*.o
	@echo "LIB miniFB.a"
	@gcc -Wall -Werror -pedantic -std=c11 src/cvis.c -Isrc/minifb/include build/libsyskFB.a -lGL -lX11 -lm -o build/cvis
	@echo "CC cvis.c"

clean: 
	rm -rf build
