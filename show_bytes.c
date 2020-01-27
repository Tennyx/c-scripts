#include <stdio.h>

typedef unsigned char *byte_pointer;

////////// 2.55 //////////

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

///////// 2.57 //////////

void show_short(short x){
	show_bytes((byte_pointer) &x, sizeof(short));
}

void show_long(long x){
	show_bytes((byte_pointer) &x, sizeof(long));
}

void show_double(double x){
	show_bytes((byte_pointer) &x, sizeof(double));
}

////////// 2.58 //////////

int is_little_endian(){
	short sample_byte = 1;
	return sample_byte;	
}

////////// 2.59 //////////

void byte_mesh(int x, int y){
	int x_masked = x & 0xFF;
	int y_masked = y & ~0xFF;
	int new_byte = x_masked | y_masked;
	printf("%x\n", new_byte);
}

////////// 2.60 //////////

unsigned replace_byte(unsigned x, int i, unsigned char b){
	unsigned int x_masked = x & ~(0xFF << (8 * i));
	unsigned int b_mask = b << (8 * i);	
	return x_masked | b_mask;	
}


int main(){
	show_int(255);
	show_float(1.5);
	show_short(1);
	show_long(32767);
	show_double(32.32);
	printf("%d\n", is_little_endian());
	byte_mesh(0x89ABCDEF, 0x76543210);
	printf("%X\n", replace_byte(0x12345678, 0, 0xAB));
	return 0;
}
