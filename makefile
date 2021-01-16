#executable
run: sms.o libisentlib.a
	gcc -Wall -o run sms.o libisentlib.a -lm -lglut -lGL -lX11
	rm -f *.o libisentlib.a



#sms
sms.o: sms.c GfxLib.h ESLib.h
	gcc -Wall -c sms.c -O2



#GfxLib libraries
libisentlib.a: ESLib.o GfxLib.o
	ar r libisentlib.a ESLib.o GfxLib.o
	ranlib libisentlib.a

ESLib.o: ESLib.c ESLib.h ErreurLib.h
	gcc -Wall -O2 -c ESLib.c

GfxLib.o: GfxLib.c GfxLib.h ESLib.h
	gcc -Wall -O2 -c GfxLib.c -I/usr/include/GL
