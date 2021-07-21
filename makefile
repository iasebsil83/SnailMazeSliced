#executable
run: sms.o libisentlib.a
	gcc -Wall -o run sms.o libisentlib.a -lm -lglut -lGL -lX11 -O2
	rm -f *.o libisentlib.a



#sms
sms.o: src/sms.c lib/GfxLib.h lib/ESLib.h
	gcc -Wall -c src/sms.c -O2



#GfxLib libraries
libisentlib.a: ESLib.o GfxLib.o
	ar r libisentlib.a ESLib.o GfxLib.o
	ranlib libisentlib.a

ESLib.o: lib/ESLib.c lib/ESLib.h lib/ErreurLib.h
	gcc -Wall -c lib/ESLib.c -O2

GfxLib.o: lib/GfxLib.c lib/GfxLib.h lib/ESLib.h
	gcc -Wall -c lib/GfxLib.c -I/usr/include/GL -O2
