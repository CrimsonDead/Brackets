#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <iostream>
#include <windows.h>
#include"Brackets.h"

void perform();
void about();

int main() {
	setlocale(LC_ALL, "RUS");
	SetConsoleOutputCP(1251); SetConsoleCP(1251);
	system("cls");
	char index;
	printf("Brackets: the program places brackets in the entered arithmetic expression in order to maximize its value\n");
	while (true) { //implementation of the main menu of the application 
		printf(" Menu:\n");
		printf(" 1. Execute \n");
		printf(" 2. About \n");
		printf(" 3. Exit \n");
		printf("Enter the number of the operation you want to perform (from 1 to 3)\t");
		while (true) { //waits for the user to enter a character from the keyboard without allowing multiple input 
			if (_kbhit()) {
				index = _getch();
				break;
			}
		}
		switch(index) {
			case '1':
				system("cls");
				perform();
				break;
			case '2':
				system("cls");
				about();
				break;
			case '3':
				return 0;
				break;
			default:
				system("cls");
				printf("Incorrectly entered operation, please try again \n\n");
				break;
		}
	}
}

/*
* Displays information about the program and developers 
*/
void about() {
	printf("Brackets v1.0.0\n");
	printf("The program places brackets in the entered arithmetic expression in order to maximize its value and also calculates this value \n");
	printf("The program is executed in the C programming language in the Microsoft Visual Studio 2019 development environment \n\n");
	printf("About the developer:\n");
	printf("2nd year student of the BSU\n\n");
}

/*
* executes the main algorithm of the program 
*/
void perform() {
	char* input = (char*)calloc(200, sizeof(char));
	char* output = (char*)calloc(200, sizeof(char));
	do {
		printf("Enter an arithmetic expression of integers without parentheses \n");
		fgets(input, 100, stdin); //reading a line from the console 
		input[strlen(input) - 1] = 0; //removing the null character at the end of the string
		DeleteSpace(input);	
		if (strlen(input) == 0) {
			fgets(input, 100, stdin);
			input[strlen(input) - 1] = 0;
			DeleteSpace(input);
		}
		printf("\n");
		if (CheckingForCorrectness(input)) {
			float maxValue = CalculatingMaxValue(input, null);
			if (maxValue <= -2e40)
				printf("Division by zero detected in expression!!!\n\n");
			else {
				if (!isPlusMinusExpression(input))
					strcpy(output, PlaceBrackets(input, CalculatingMaxIndex(input, null)));
				else
					strcpy(output, input);
				printf("Expression with parentheses in order to maximize its value %s\n", output);
				printf("Maximum expression result = %3.2f\n\n", maxValue);
			}
			break;
		}
		system("cls");
		printf("Invalid expression\n\n");
	} while (!CheckingForCorrectness(input));
}