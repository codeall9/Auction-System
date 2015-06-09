#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <iostream>

using std::cin;
using std::cout;

char get_Input(char L_Range, char H_Range);

inline char get_Input(char L_Range, char H_Range)
{
	char inChar;
	do {
		cin.sync();
		inChar = cin.get();
		if (inChar < L_Range || inChar > H_Range) {
			cout << "\nYou input a wrong number!\nPlease input again :";
		}
		else {
			break;
		}
	} while (true);
	return inChar;
}

#endif