all: libSiUSBXp.so

clean:
	rm -f libSiUSBXp.so

libSiUSBXp.so: SiUSBXp.c
	$(CC) -shared -lusb -o $@ $^ -Wall -Wpedantic -fPIC
