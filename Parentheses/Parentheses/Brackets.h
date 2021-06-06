#ifndef Header_H
#define Header_H

enum operation {
	null,
	plus,
	minus,
	multiply,
	divide
};

bool isPlusMinusExpression(char input[]);
char* PlaceBrackets(char input[], int maxIndex);
int CountingTheNumberOfOperation(char input[]);
float ConvertFromString(char input[]);
float CalculatingMaxValue(char input[], operation op);
int CalculatingMaxIndex(char input[], operation op);
void DeleteSpace(char input[]);
bool CheckingForCorrectness(char input[]); 

using namespace std;

/*
 true - if the input string consists only of numbers, arithmetic signs and spaces
*/
bool CheckingForCorrectness(char input[]) {
	bool isCorrect = true;
	for (int i = 0; i < strlen(input); i++)	{
		if ((((input[i] < 42 && input[i] != 32) || input[i] > 57) || input[i] == 44 || input[i] == 46) || 
			((input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') && input[i] == input[i + 1]) ||
			(input[0] == '+' || input[0] == '-' || input[0] == '*' || input[0] == '/')) {
			isCorrect = false;
			break;
		}
	}
	return isCorrect;
}

/*
  removes all spaces
*/
void DeleteSpace(char input[]) {
	for (int i = 0; i < strlen(input); i++)	{
		if (input[i] == ' ') {
			for (int j = i; j < strlen(input); j++) {
				input[j] = input[j + 1];
			}
		}
	}
}

/*
Counts the index of the operation with respect to which the expression of input will take its maximum value
op -- is the operation with respect to which we are looking for the maximum or minimum value of the expression of input
at op:
-plus, multiply, null looks for the maximum value;
-minus, divide looks for the minimum value.
*/
int CalculatingMaxIndex(char input[], operation op) {
	int opNumber = CountingTheNumberOfOperation(input);
	if (opNumber == 0) {
		return ConvertFromString(input);
	}
	bool isNegative = false;	//variable to determine the sign of the result
	if (op == operation::minus || op == operation::divide)
		isNegative = true;
	char a[50], b[50];
	int opCounter = 0;	
	float* rez;		//an array of results to determine the maximum index
	rez = (float*)calloc(opNumber, sizeof(float));
	operation currentOp = operation::null;
	float A, B;
	for (int i = 0; i < strlen(input); i++) {
		switch (input[i]) { 
		case '+':
			currentOp = operation::plus;
			strncpy_s(a, input, i);		//dividing the line into two: before the sign and after the sign
			strncpy_s(b, input + i + 1, strlen(input) - i - 1);
			A = CalculatingMaxValue(a, operation::null);	//determination of the maximum value
			B = CalculatingMaxValue(b, currentOp);			//first and second lines 
			if (A == 3.14e-58 || B == 3.14e-58)		//division by 0 test 
				return 3.14e-58;
			rez[opCounter++] = A + B;		
			break;
		case '-':
			currentOp = operation::minus;	
			strncpy_s(a, input, i);		//dividing the line into two: before the sign and after the sign
			strncpy_s(b, input + i + 1, strlen(input) - i - 1);
			A = CalculatingMaxValue(a, operation::null);	//determination of the maximum value 
			B = CalculatingMaxValue(b, currentOp);			//first and second lines 
			if (A == 3.14e-58 || B == 3.14e-58)		//division by 0 test 
				return 3.14e-58;
			rez[opCounter++] = A - B;
			break;
		case '*':
			currentOp = operation::multiply;
			strncpy_s(a, input, i);		//dividing the line into two: before the sign and after the sign
			strncpy_s(b, input + i + 1, strlen(input) - i - 1);
			A = CalculatingMaxValue(a, operation::null);	//determination of the maximum value
			B = CalculatingMaxValue(b, currentOp);			//first and second lines
			if (A == 3.14e-58 || B == 3.14e-58)		//division by 0 test 
				return 3.14e-58;
			rez[opCounter++] = A * B;
			break;
		case '/':
			currentOp = operation::divide;
			strncpy_s(a, input, i);		//dividing the line into two: before the sign and after the sign
			strncpy_s(b, input + i + 1, strlen(input) - i - 1);
			A = CalculatingMaxValue(a, operation::null);	//determination of the maximum value
			B = CalculatingMaxValue(b, currentOp);			//first and second lines
			if (A == 3.14e-58 || B == 3.14e-58)		//division by 0 test 
				return 3.14e-58;
			rez[opCounter++] = A / B;	
			break;
		default:
			continue;
		}
	}
	float extr;
	for (int i = 0; i < opNumber; i++) {	//protect against the appearance of the inf value as a result
		if (rez[i] <= 3.14e58) {
			extr = rez[i];
			break;
		}
		else
			extr = 3.14e-58;
	}
	int MaxIndex = 0;
	for (int i = 0; i < opNumber; i++) {	//search for the desired value
		if (!isNegative && rez[i] > extr && rez[i] != 0 && rez[i] <= 3.14e58) {
			extr = rez[i];
			MaxIndex = i;
		}
		if (isNegative && rez[i] < extr && rez[i] != 0 && rez[i] <= 3.14e58) {
			extr = rez[i];
			MaxIndex = i;
		}
	}
	return MaxIndex;
}


/*
Calculates the maximum or minimum value of the expression of input
op -- is the operation with respect to which we are looking for the maximum or minimum value of the expression of input
at op:
-plus, multiply, null looks for the maximum value;
-minus, divide looks for the minimum value;
*/
float CalculatingMaxValue(char input[], operation op) {
	int opNumber = CountingTheNumberOfOperation(input);
	if (opNumber == 0) {
		return ConvertFromString(input);
	}
	bool isNegative = false;	//variable to determine the sign of the result
	if (op == operation::minus || op == operation::divide)
		isNegative = true;
	char a[50], b[50];
	int opCounter = 0;
	float* rez;		//an array of results to determine the maximum value
	rez = (float*)calloc(opNumber, sizeof(float));
	operation currentOp = operation::null;
	float A, B;
	for (int i = 0; i < strlen(input); i++) {
		switch (input[i]) {
		case '+':
			currentOp = operation::plus;
			strncpy_s(a, input, i);		//dividing the line into two: before the sign and after the sign
			strncpy_s(b, input + i + 1, strlen(input) - i - 1);
			A = CalculatingMaxValue(a, operation::null);	//determination of the maximum value 
			B = CalculatingMaxValue(b, currentOp);			//first and second lines
			if (A == 3.14e-58 || B == 3.14e-58)		//division by 0 test
				return 3.14e-58;
			rez[opCounter++] = A + B;
			break;
		case '-':
			currentOp = operation::minus;
			strncpy_s(a, input, i);		//dividing the line into two: before the sign and after the sign
			strncpy_s(b, input + i + 1, strlen(input) - i - 1);
			A = CalculatingMaxValue(a, operation::null);	//determination of the maximum value 
			B = CalculatingMaxValue(b, currentOp);			//first and second lines
			if (A == 3.14e-58 || B == 3.14e-58)		//division by 0 test
				return 3.14e-58;
			rez[opCounter++] = A - B;
			break;
		case '*':
			currentOp = operation::multiply;
			strncpy_s(a, input, i);		//dividing the line into two: before the sign and after the sign
			strncpy_s(b, input + i + 1, strlen(input) - i - 1);
			A = CalculatingMaxValue(a, operation::null);	//determination of the maximum value
			B = CalculatingMaxValue(b, currentOp);			//first and second lines
			if (A == 3.14e-58 || B == 3.14e-58)		//division by 0 test
				return 3.14e-58;
			rez[opCounter++] = A * B;
			break;
		case '/':
			currentOp = operation::divide;
			strncpy_s(a, input, i);		//dividing the line into two: before the sign and after the sign
			strncpy_s(b, input + i + 1, strlen(input) - i - 1);
			A = CalculatingMaxValue(a, operation::null);	//determination of the maximum value
			B = CalculatingMaxValue(b, currentOp);			//first and second lines
			if (A < abs(3.14e-58) || B < (3.14e-58) || B == 0 || A / B < abs(3.14e-58))	//division by 0 test
				rez[opCounter++] = -2e40;
			else
				rez[opCounter++] = A / B;
			break;
		default:
			continue;
		}
	}
	float extr;
	for (int i = 0; i < opNumber; i++) {	//protection against inf value appearing as a result
		if (rez[i] <= 3.14e58) {
			extr = rez[i];
			break;
		}
		else
			extr = 3.14e-58;
	}
	for (int i = 0; i < opNumber; i++) {	//search for the desired value
		if (!isNegative && rez[i] > extr && rez[i] != 0 && rez[i] <= 3.14e58)
			extr = rez[i];
		if (isNegative && rez[i] < extr && rez[i] != 0 && rez[i] <= 3.14e58)
			extr = rez[i];
	}
	return extr;
}

/*
 A string containing only numbers must come here
*/
float ConvertFromString(char input[]) {
	float rez = 0;
	for (int i = 0; i < strlen(input); i++) {
		rez *= 10;
		rez += ((int)input[i] - 48);
	}
	return rez;
}

/*
 Counts the number of operations in the expression of input
*/
int CountingTheNumberOfOperation(char input[]) {
	int numberOfOperation = 0;
	for (int i = 0; i < strlen(input) - 1; i++)
		if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
			numberOfOperation++;
	return numberOfOperation;
}

/*
 returns the expression input with placed brackets 
 maxIndex -- the ordinal number of the operation in the expression, relative to which the value of the expression is maximal
*/
char* PlaceBrackets(char input[], int maxIndex) {
	int opNumber = CountingTheNumberOfOperation(input);
	if (opNumber <= 1) {
		return input;
	}
	int opCounter = 0;	//current operation number
	char* a = (char*)calloc(200, sizeof(char));
	char* b = (char*)calloc(200, sizeof(char));
	char rez[100];
	for (int i = 0; i < strlen(input) - 1; i++){
		if (opCounter == maxIndex && (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')) {
			switch (input[i]) {
			case '+':
				strncat(a, input, i);								//dividing an expression into two parts
				strncat(b, (input)+i + 1, strlen(input) - i - 1);	//regarding the desired operation
				strcpy(a, PlaceBrackets(a, CalculatingMaxIndex(a, null)));	//getting strings with bracketed brackets
				if (CountingTheNumberOfOperation(a) != 0) {
					strcpy(rez, "(");
					strcat(rez, a);
					strcpy(a, rez);
				}
				strcpy(b, PlaceBrackets(b, CalculatingMaxIndex(b, null)));	//getting strings with bracketed brackets
				if (CountingTheNumberOfOperation(b) != 0) {
					strcpy(rez, "+(");
					strcat(rez, b);
					strcpy(b, rez);
				}
				else {
					strcpy(rez, "+");
					strcat(rez, b);
					strcpy(b, rez);
				}
				i += 2;
				if (CountingTheNumberOfOperation(a) != 0)
					strcat(a, ")");
				if (CountingTheNumberOfOperation(b) != 1)
					strcat(b, ")");
				strcpy(rez, a);
				strcat(rez, b);
				opCounter++;
				break;
			case '-':
				strncat(a, input, i);								//dividing an expression into two parts
				strncat(b, (input)+i + 1, strlen(input) - i - 1);	//regarding the desired operation
				strcpy(a, PlaceBrackets(a, CalculatingMaxIndex(a, null)));	//getting strings with bracketed brackets
				if (CountingTheNumberOfOperation(a) != 0) {
					strcpy(rez, "(");
					strcat(rez, a);
					strcpy(a, rez);
				}
				strcpy(b, PlaceBrackets(b, CalculatingMaxIndex(b, operation::minus)));	//getting strings with bracketed brackets
				if (CountingTheNumberOfOperation(b) != 0) {
					strcpy(rez, "-(");
					strcat(rez, b);
					strcpy(b, rez);
				}
				else {
					strcpy(rez, "-");
					strcat(rez, b);
					strcpy(b, rez);
				}
				i += 2;
				if (CountingTheNumberOfOperation(a) != 0)
					strcat(a, ")");
				if (CountingTheNumberOfOperation(b) != 1)
					strcat(b, ")");
				strcpy(rez, a);
				strcat(rez, b);
				opCounter++;
				break;
			case '*':
				strncat(a, input, i);								//dividing an expression into two parts
				strncat(b, (input)+i + 1, strlen(input) - i - 1);	//regarding the desired operation
				strcpy(a, PlaceBrackets(a, CalculatingMaxIndex(a, null)));	//getting strings with bracketed brackets
				if (CountingTheNumberOfOperation(a) != 0) {
					strcpy(rez, "(");
					strcat(rez, a);
					strcpy(a, rez);
				}
				strcpy(b, PlaceBrackets(b, CalculatingMaxIndex(b, null)));	//getting strings with bracketed brackets
				if (CountingTheNumberOfOperation(b) != 0) {
					strcpy(rez, "*(");
					strcat(rez, b);
					strcpy(b, rez);
				}
				else {
					strcpy(rez, "*");
					strcat(rez, b);
					strcpy(b, rez);
				}
				i += 2;
				if (CountingTheNumberOfOperation(a) != 0)
					strcat(a, ")");
				if (CountingTheNumberOfOperation(b) != 1)
					strcat(b, ")");
				strcpy(rez, a);
				strcat(rez, b);
				opCounter++;
				break;
			case '/':
				strncat(a, input, i);								//dividing an expression into two parts
				strncat(b, (input)+i + 1, strlen(input) - i - 1);	//regarding the desired operation
				strcpy(a, PlaceBrackets(a, CalculatingMaxIndex(a, null)));	//getting strings with bracketed brackets
				if (CountingTheNumberOfOperation(a) != 0) {
					strcpy(rez, "(");
					strcat(rez, a);
					strcpy(a, rez);
				}
				strcpy(b, PlaceBrackets(b, CalculatingMaxIndex(b, operation::minus)));	//getting strings with bracketed brackets
				if (CountingTheNumberOfOperation(b) != 0) {
					strcpy(rez, "/(");
					strcat(rez, b);
					strcpy(b, rez);
				}
				else {
					strcpy(rez, "/");
					strcat(rez, b);
					strcpy(b, rez);
				}
				i += 2;
				if (CountingTheNumberOfOperation(a) != 0)
					strcat(a, ")");
				if (CountingTheNumberOfOperation(b) != 1)
					strcat(b, ")");
				strcpy(rez, a);
				strcat(rez, b);
				opCounter++;
				break;
			}

		}
		if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/')
			opCounter++;
	}
	return rez;
}

/*
 Returns true if the expression contains only + and - operations
*/
bool isPlusMinusExpression(char input[]) {
	bool isPMExpr = true;
	for (int i = 0; i < strlen(input); i++) {
		if (input[i] == '*' || input[i] == '/') {
			isPMExpr = false;
			break;
		}
	}
	return isPMExpr;
}

#endif // !Header_H

