#pragma once
#include "stdafx.h"


struct PN
{
	LT::Entry result[10000]; // ������ ��������������� ��������� � �������� �������
	int size = 0;
	enum { LH = '(', RH = ')', PLUS = '+', MINUS = '-', MULT = '*', DEV = '/', EQUAL = '=' };

	int prior(char operation); // ��������� ��������
	int searchExpression(int number, LeX::LEX *tables); // ����� ������ ��������� � ������� ������
	bool CreatePolishNotation(LeX::LEX *tables);
};