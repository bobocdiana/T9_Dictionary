build: tema4

tema4: 
	g++ -Wall -o tema4 tema4.cpp

.PHONY: clean
clean:
	rm tema4
