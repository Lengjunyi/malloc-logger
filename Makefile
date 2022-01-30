malloc.so: malloc.c
	gcc -shared -o malloc.so -fPIC malloc.c -ldl
