#include "stdafx.h"


int PN::prior(char znak)
{
	switch (znak)
	{
	case '+':
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	default:
		return 0;
	}
}


int PN::searchExpression(int index, LeX::LEX *tables) //����� ���������
{
	for (int i = index; i < tables->Lextable.size; i++) //������� ������
	{
		if (tables->Lextable.table[i].lexema == PLUS || tables->Lextable.table[i].lexema == MINUS
			|| tables->Lextable.table[i].lexema == MULT || tables->Lextable.table[i].lexema == DEV) //������� ��������
		{
			for (; ; i--) //���������� ������� �������
			{
				if (tables->Lextable.table[i].lexema == EQUAL || tables->Lextable.table[i].lexema == RH)
					return i + 1;
			}
		}
	}
	return -1; //���� �� ����� ���������� ����� 1
}

bool PN::CreatePolishNotation(LeX::LEX *tables)
{
	stack <LT::Entry> stack_operators;// �������� ���������
	bool build = false;

	int i = 0;
	int j = 0;
	int k = 0;

	while (searchExpression(i, tables) != -1)
	{
		j = i = searchExpression(i, tables);//������ ������� ������� ����� �����
		bool isOne = false;
		for (; tables->Lextable.table[i].lexema != LEX_SEPARATOR; i++, k++) //������ �� ������� ����� ������, ���������� ������� �
		{
			if (tables->Lextable.table[i].lexema == LH || tables->Lextable.table[i].lexema == RH) //���� ����� ( ��� )
			{
				switch (tables->Lextable.table[i].lexema) //������� ����� �������
				{
				case LH:
				{
					if ((tables->Lextable.table[i - 1].idxTI != -1 && tables->IDtable.table[tables->Lextable.table[i - 1].idxTI].idtype == IT::F)
						|| tables->Lextable.table[i - 1].lexema == 'a' || tables->Lextable.table[i - 1].lexema == 's')  // ����� -1 ���� ��� �� ����� ������� ����������
					{
						while (tables->Lextable.table[i - 1].lexema != RH)
							i++;
						break;
					}
					stack_operators.push(tables->Lextable.table[i]);// ( ��������� � ���� ���������� ������� ������� ������
					break;
				}
				case RH:
					while (stack_operators.top().lexema != LH) // ) ���������� ������ ������� �� �����
					{
						result[size++] = stack_operators.top();
						stack_operators.pop(); //��������� ������� ����� ����������
					}
					stack_operators.pop(); //��������� ������� ����� ����������
					break;
				}
			}
			else
			{
				switch (tables->Lextable.table[i].lexema) //���� ��� �� ������()
				{
				case MULT:
				case DEV:
				{
					stack_operators.push(tables->Lextable.table[i]);//��������� � ���� ���������� ������� ������� ������
					break;
				}
				case PLUS:
				case MINUS:
					if (stack_operators.empty() || prior(tables->Lextable.table[i].lexema) == prior(stack_operators.top().lexema))//����
						stack_operators.push(tables->Lextable.table[i]);//��������� � ���� ���������� ������� ������� ������ 
					else //���� ���������� �� ������
					{
						while (!stack_operators.empty() && stack_operators.top().lexema != LH &&
							prior(tables->Lextable.table[i].lexema) < prior(stack_operators.top().lexema)) //���� ������� � ����� �� (, � ��������� �������� ������ ���� ����� ���������� �������� � ������ �����, ��..
						{
							result[size++] = stack_operators.top(); //������� �������� ����� � ���������
							stack_operators.pop();//��������� �������� �����
						}
						if (!stack_operators.empty() && stack_operators.top().lexema == LH)// ��������� �������� �����
							stack_operators.push(tables->Lextable.table[i]);//�������� � ���� ���������� ������� ������� ������
						if (stack_operators.empty())// ��������� �������� �����
							stack_operators.push(tables->Lextable.table[i]);//�������� � ���� ���������� ������� ������� ������
					}
					break;
				default:
				{
					result[size++] = tables->Lextable.table[i];//������� ������� ������ � ���������
					break;
				}
				}
			}
		}
		for (; !stack_operators.empty(); i++)	//������ ��� ��������� � �������� ����
		{
			result[size++] = stack_operators.top(); //������� ��� ��������� � ���������
			stack_operators.pop();// �������� �������� �����
		}
		for (int i = 0; i < size; j++, i++, k--) //���������� ������� ������, ��� ������� ���������
		{
			tables->Lextable.table[j].lexema = result[i].lexema;
			tables->Lextable.table[j].idxTI = result[i].idxTI;
			tables->Lextable.table[j].sn = result[i].sn; //����� ��� � ��� ���c�
			tables->IDtable.table[result[i].idxTI].idxfirstLE;
		}
		for (; k > 0; k--, j++)	//��������� ��� ��������, "�������� � �������� �������� ��������"
		{
			tables->Lextable.table[j].lexema = NULL;
			tables->Lextable.table[j].idxTI = NULL;
		}
		size = 0;
		build = true;
	}
	return build;
}