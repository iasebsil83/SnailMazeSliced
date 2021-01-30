#executable
run: sms.o libisentlib.a
	gcc -Wall -o run sms.o libisentlib.a -lm -lglut -lGL -lX11 -O2
	rm -f *.o libisentlib.a



#sms
sms.o: sms.c src/GfxLib.h src/ESLib.h
	gcc -Wall -c sms.c -O2



#GfxLib libraries
libisentlib.a: ESLib.o GfxLib.o
	ar r libisentlib.a ESLib.o GfxLib.o
	ranlib libisentlib.a

ESLib.o: src/ESLib.c src/ESLib.h src/ErreurLib.h
	gcc -Wall -c src/ESLib.c -O2

GfxLib.o: src/GfxLib.c src/GfxLib.h src/ESLib.h
	gcc -Wall -c src/GfxLib.c -I/usr/include/GL -O2
