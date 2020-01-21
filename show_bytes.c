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

void show_char(char x){
	show_bytes((byte_pointer) &x, sizeof(char));
}

int main(){
	show_int(255);
	show_float(1.5);
	show_char("a");
	return 0;
}
