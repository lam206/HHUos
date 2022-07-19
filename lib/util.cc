#include "kernel/Globals.h"

//
// Hilfsfunktion: Auf Return-Taste warten
void waitForReturn() {
	kout << endl;

	kout << "Press enter" << endl;

	Key k;
	while( !((k = kb.key_hit()).valid()) || k.ascii() != '\n') {

	}

	kout.clear();

}


int strlen(char* s) {
	int n = 0;
	while (*s != 0) {
		n++;
		s++;
	}
	return n;
}

char* rev(char* s) {
	int n;

	n = strlen(s);
	for (int i = 0; i < n / 2; i++) {
		char temp = s[i];
		s[i] = s[n-1-i];
		s[n-1-i] = temp;
	}

	return s;
}


// only accepts a positive x
char* strpos(unsigned int x) {
	int num;
	char* s = (char*)allocator.alloc(20);  // 20 enough for int

	int i = 0;
	while (x != 0) {
		num = x % 10;
		s[i] = num + 48;
		i++;

		x -= num;
		x /= 10;
	}
	
	return rev(s);
}

		
void strcpy(char* target, char* source) {
	int i = 0;
	while (source[i] != 0) {
		target[i] = source[i];
	}
}


char* str(int x) {
	if (x < 0) {
		char* absval = strpos(-x);

		char* s = (char*)allocator.alloc(20);  // 20 enough for int
		s[0] = '-';
		strcpy(s+1, absval);
		return s;

	} else {
		return strpos(x);
	}

}

char* str2cat(char* s1, char* s2) {
	char* s = (char*)allocator.alloc(strlen(s1) + strlen(s2) + 1);
	char* writer = s;

	for (int i = 0; i < strlen(s1); i++) {
		*writer = s1[i];
		writer++;
	}
	for (int i = 0; i < strlen(s2); i++) {
		*writer = s2[i];
		writer++;
	}
	*writer = 0;

	return s;
}



