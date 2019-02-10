projet0: clean projet0.c
	gcc -g projet0.c -o projet0 -lpcap

clean:
	rm -rf *.o
	rm -rf projet0

