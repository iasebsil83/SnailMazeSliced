#executable
run: sms.o S2DE.o
	gcc -Wall -o run sms.o S2DE.o -lm -lglut -lGL -lX11 -O2
	rm -f *.o



#sms
sms.o: src/sms.c lib/S2DE.h src/img.c
	gcc -Wall -c src/sms.c -O2 -I/usr/include/GL



#S2DE
S2DE.o: lib/S2DE.c lib/S2DE.h
	gcc -Wall -c lib/S2DE.c -O2 -I/usr/include/GL
