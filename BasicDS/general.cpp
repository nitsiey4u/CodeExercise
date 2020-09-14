/***********************************************/
/*********** General Basic Problems	 ***********/
/***********************************************/
#include <iostream>
#include "stdio.h"
using namespace std;

void print_multibyte_data() {
	unsigned int data_value = 0x12345678;
	printf("\nActual value:%.2x", data_value);
	const char* byte_val = (char*)&data_value;
	const int byte_count = sizeof(data_value);
	printf("\nStored:");
	for(int index = 0; index < byte_count; index++) {
		printf("\t\t\t%.2x", byte_val[index]);
	}
	printf("\nAddress:");
	for(int index = 0; index < byte_count; index++) {
		printf("\t%p", &byte_val[index]);
	}
}

void endian_byte_order() {
	short int value = 0x00FF;
	char* byte = (char*)&value;
	if(byte[0]) {
		printf("\nLittle endian");
	} else {
		printf("\nBig endian");
	}

	short int word = 0x1234;
	if((*((char*)&word) & word) == 0x34) {
		printf("\nLittle endian");
	} else {
		printf("\nBig endian");
	}
}

void validate_constant_pointer() {
	int val1 = 10;
	int val2 = 20;
	printf("\nPointer to constant value - 10");
	const int* ptr1 = &val1;
	printf("\nBefore %d", *ptr1);
	printf("\nValue updated by variable - 11");
	val1 = 11;
	printf("\nAfter %d", *ptr1);
	ptr1 = &val2;
	printf("\nPointer to constant value - 20");
	printf("\nNext %d", *ptr1);

	printf("\nConstant pointer to value - 10");
	int* const ptr2 = &val1;
	printf("\nBefore %d", *ptr2);
	val1 = 15;
	printf("\nValue updated by pointer - 15");
	printf("\nAfter %d", *ptr2);


}

// Check direction of stack (downwards or upwards)
void check_stack_direction(int* caller_addr) {
	int func_temp = 22;
	int* callee_addr = &func_temp;
	cout << "\nCaller Address (Main): " << caller_addr;
	cout << "\nCallee Address (This): " << callee_addr;
	//  main function (caller) --> this function (callee)
	if(caller_addr > callee_addr) {
		// If address of Main > This = stack grows downwards
		cout << "\nStack grows downwards";
	} else
	{
		// If address of Main < This = stack grows upwards
		cout << "\nStack grows upwards";
	}
}

int main(int argc, char* argv[]) {

	// int main_temp = 11;
	// check_stack_direction(&main_temp);

	validate_constant_pointer();

	// print_multibyte_data();
	// print_system_endian();

	short int i1;
	unsigned int i2;
	unsigned long l1;
	unsigned long long l2;
	float f1;
	double f2;
	// cout << "\nSize of short int: " << sizeof(i1);
	// cout << "\nSize of unsigned int: " << sizeof(i2);
	// cout << "\nSize of unsigned long: " << sizeof(l1);
	// cout << "\nSize of unsigned long long: " << sizeof(l2);
	// cout << "\nSize of float: " << sizeof(f1);
	// cout << "\nSize of double: " << sizeof(f2);
	return 0;
}
