#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len){
	int i;
	for(i=0; i<len; i++){
		printf(" %.2x", start[i]);
	}
	printf("\n");
}

void show_int(int x){
	show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x){
	show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x){
	show_bytes((byte_pointer) &x, sizeof(void *));
}

void show_short(short x){
	show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long(long x){
	show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double(double x){
	show_bytes((byte_pointer) &x, sizeof(double));
}

int is_little_endian(){
	short sample_byte = 1;
	return sample_byte;	
}

void byte_mesh(int x, int y){
	// combines least significant byte of x with remaining bytes of y
	int *x_pointer = &x;
	printf("%x\n", *x_pointer);
}


int main(){
	show_int(255);
	show_float(1.5);
	show_short(1);
	show_long(32767);
	show_double(32.32);
	printf("%d\n", is_little_endian());
	byte_mesh(0x89ABCDEF,2);
	return 0;
}
