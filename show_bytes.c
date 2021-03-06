#include <stdio.h>
#include <limits.h>
#include <string.h>

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

////////// 2.61 //////////

//// A & B ////

int contains_flagged_bit(int x){
	return !!(x);
}

//// C ////

int lsb_contains_flagged_bit(int x){
	return contains_flagged_bit(x & 0xFF);
}

//// D ////

int msb_contains_flagged_bit(int x){
	int shift_val = (sizeof(x)-1) << 3;
	int xright = x >> shift_val;	
	return lsb_contains_flagged_bit(xright);
}

////////// 2.62 //////////

int int_shifts_are_arithmetic(){
	//I think this works, but need to test on logical right shift machine.
	int x = -1;
	int shift_val = (sizeof(x)-1) << 3;
	return !!(x >> shift_val);
}

///////// 2.63 //////////

unsigned srl(unsigned x, int k){
	unsigned xsra = (int) x >> k;
	int word_size = 8 * sizeof(int);
	int mask = INT_MAX << (word_size - k);
	return xsra ^ mask;
}

int sra(int x, int k){
	int xsrl = (unsigned) x >> k;
	int word_size = 8 * sizeof(int);
	int mask = INT_MAX << (word_size - k);
	return xsrl | mask; 
}

////////// 2.64 //////////

int any_odd_one(unsigned x){
	int odds_mask = 0x55555555;   //01010101010101010101010101010101 
	return !!(x & odds_mask);
}

////////// 2.65 //////////

int odd_ones(unsigned x){
	x ^= x >> 16;
	x ^= x >> 8;
	x ^= x >> 4;
	x ^= x >> 2;
	x ^= x >> 1;

	return (x & 1);
}

////////// 2.66 //////////

int leftmost(unsigned x){
	//bit smearing

	x |= x >> 16;
	x |= x >> 8;
	x |= x >> 4;
	x |= x >> 2;
	x |= x >> 1;

	return x ^= x >> 1;	
}

////////// 2.67 //////////

int int_size_is_32(){
	int set_msb = 1 << 15 << 15 << 1;
  	int beyond_msb = set_msb << 1;
	return set_msb && !beyond_msb;
}

////////// 2.68 //////////

int lower_one_mask(int n){
	int word_size = 8 * sizeof(int);
	int val = (1 <<  (word_size - 1)) >> (word_size - 1);
	return ~(val << n);		
}

////////// 2.69 //////////

unsigned rotate_left(unsigned x, int n){
	int word_size = 8 * sizeof(x);
	unsigned mask_one = x >> (word_size - n);
	unsigned mask_two = x << n;
	return mask_one | mask_two;
}

////////// 2.70 //////////

int fits_bits(int x, int n){
	int word_size = 8 * sizeof(int);
	int val = (1 << (word_size - 1)) >> (word_size -1);
	int bit_size_mask = (val << (n -1)) << 1;
	return !(x & bit_size_mask);
}

////////// 2.71 //////////

//// A ////

// It shifts right without shifting left to account for sign extensions. Also returns unsigned value.

//// B ////

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum){
	int shift_difference = 24 - (bytenum << 3);
	int shift_left = word << shift_difference;
	int shift_right = shift_left >> shift_difference;
	return shift_right >> (bytenum << 3);
}

////////// 2.72 //////////

/*
bugged version

void copy_int(int val, void *buf, int maxbytes){
	if(maxbytes - sizeof(val) >= 0){
		memcpy(buf, (void *) &val, sizeof(val));
	}
}
*/

//// A ////

// Conditional test always succeeds because it's cast to unsigned and thus can never be negative.

//// B ////

// correct version

void copy_int(int val, void *buf, int maxbytes){
	if(maxbytes >= sizeof(val)){
		memcpy(buf, (void*) &val, sizeof(val));
	}
}

////////// 2.73 //////////***

int saturating_add(int x, int y){
	int sum = x + y;
    	int pos_overflow = !(x & INT_MIN) && !(y & INT_MIN) &&  (sum & INT_MIN);
    	int neg_overflow =  (x & INT_MIN) &&  (y & INT_MIN) && !(sum & INT_MIN);
	
	(!pos_overflow || (sum = INT_MAX)) && (!neg_overflow || (sum = INT_MIN));
	
	return sum;
}

////////// 2.74 //////////***

int tsub_ok(int x, int y){
    int subt = x - y;    
    int negative_overflow = (x < 0 && y >= 0) && subt > 0;
    int positive_overflow = (x >= 0 && y < 0) && subt < 0;
    return !positive_overflow && !negative_overflow; 
}

int main(){
/*	show_int(255);
	show_float(1.5);
	show_short(1);
	show_long(32767);
	show_double(32.32);
	printf("%d\n", is_little_endian());
	byte_mesh(0x89ABCDEF, 0x76543210);
	printf("%X\n", replace_byte(0x12345678, 0, 0xAB));
	printf("%d\n", contains_flagged_bit(0));
	printf("%d\n", lsb_contains_flagged_bit(256));
	printf("%d\n", msb_contains_flagged_bit(123456789));
	printf("%d\n", int_shifts_are_arithmetic());
	printf("%d\n", srl(-2147483648,5));
	printf("%d\n", sra(-2147483648,31));
	printf("%d\n", any_odd_one(5));
	printf("%d\n", odd_ones(8));
	printf("%x\n", leftmost(0xFF00));
	printf("%d\n", int_size_is_32());
	printf("%x\n", lower_one_mask(17));
	printf("%x\n", rotate_left(0x12345678, 0));
	printf("%x\n", fits_bits(-1, 32));
	printf("%x\n", xbyte(0x99887766, 3));
	printf("%x\n", saturating_add(2147483647, 1));
*/
	printf("%x\n", tsub_ok(1, -5));
	return 0;
}
