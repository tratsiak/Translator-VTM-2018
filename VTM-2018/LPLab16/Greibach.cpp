#include "stdafx.h"
#define GRB_ERROR_SERIES 600


namespace GRB
{
	Greibach greibach(NS('S'), TS('$'), 6,
		Rule(NS('S'), GRB_ERROR_SERIES + 0, 5,   //  ��������� ���������
			Rule::Chain(3, TS('B'), TS(';'), NS('S')),
			Rule::Chain(10,TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), NS('S')),
			Rule::Chain(11,TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(9, TS('t'), TS('f'), TS('i'), TS('('), TS(')'), TS('{'), NS('N'), TS('}'), NS('S')),
			Rule::Chain(4, TS('g'), TS('{'), NS('N'), TS('}'))
		),
		Rule(NS('F'), GRB_ERROR_SERIES + 3, 2,
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F')),  // ��������� �-��
			Rule::Chain(2, TS('t'), TS('i'))   
		),
		Rule(NS('N'), GRB_ERROR_SERIES + 4, 7,  // ��������� ����������� � �-���
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(6, TS('o'), TS('('), NS('E'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(5, TS('o'), TS('('), NS('E'), TS(')'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(3, TS('b'), NS('E'), TS(';'))
		),
		Rule(NS('E'), GRB_ERROR_SERIES + 2, 18, // ���������
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(2, TS('-'), TS('l')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('i'), NS('E')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(3, TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(4, TS('s'), TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('e'), TS('('), NS('W'), TS(')')),
			Rule::Chain(4, TS('p'), TS('('), NS('W'), TS(')')),
			Rule::Chain(5, TS('e'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(5, TS('s'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('p'), TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('('), NS('W'), TS(')'), NS('M')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')'))
		),
		Rule(NS('W'), GRB_ERROR_SERIES + 5, 4, // ����������� ��������� �-��
			Rule::Chain(1, TS('l')),
			Rule::Chain(1, TS('i')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(NS('M'), GRB_ERROR_SERIES + 1, 8, // �����
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(2, TS('/'), NS('E')),
			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(3, TS('+'), NS('E'), NS('M')),
			Rule::Chain(3, TS('-'), NS('E'), NS('M')),
			Rule::Chain(3, TS('*'), NS('E'), NS('M')),
			Rule::Chain(3, TS('/'), NS('E'), NS('M'))
		)
	);

	Rule::Chain::Chain(short psize, GRBALPHABET s, ...)  //����������� ������� - ������ ����� �������(���-�� �������� � �������, �������� ��� ����������...)
	{
		nt = new GRBALPHABET[size = psize];    //������� ����������
		int*p = (int*)&s;     //����������� ������ ��������� �
		for (short i = 0; i < psize; ++i)
			nt[i] = (GRBALPHABET)p[i]; //��������� ������� ����������
	};

	Rule::Rule(GRBALPHABET pnn, int piderror, short psize, Chain c, ...) //����������� �������
	{															//(����������, ������������� ���������������� ���������, ���������� �������(������ ������ �������), ��������� ������� (������ ������ �������)
		nn = pnn;    //����������
		iderror = piderror; //�������������
		chains = new Chain[size = psize]; //����� ��� �������
		Chain* p = &c;
		for (int i = 0; i < size; i++)
			chains[i] = p[i]; //��������� ��������� �������
	};

	Greibach::Greibach(GRBALPHABET pstartN, GRBALPHABET pstbottom, short psize, Rule r, ...)//����������� ���������� ��������(��������� ������, ��� �����, ���������� ������, �������...)
	{
		startN = pstartN; //��������� ������
		stbottomT = pstbottom;//��� �����
		rules = new Rule[size = psize];//�������� ������
		Rule*p = &r;
		for (int i = 0; i < size; i++) 
			rules[i] = p[i];//��������� �������
	};
	Greibach getGreibach() { return greibach; }; //�������� ����������

	short Greibach::getRule(GRBALPHABET pnn, Rule& prule) //�������� ������� (����� ������ �������, ������������ ������� ����������)
	{
		short rc = -1;
		short k = 0;
		while (k < size&&rules[k].nn != pnn)
			k++;   //���� � ������ ���������� ������ � ���� ����� ������ ������� �� ����� �������� �-���
		if (k < size)
			prule = rules[rc = k];    //������������ ������� ��������� ����� ������� � �������� �
		return rc; //������������ ����� ������� ��� -1
	};

	Rule Greibach::getRule(short n) //�������� ������� �� ������
	{
		Rule rc;      //������ ������� ��
		if (n < size)
			rc = rules[n];  //����������� ������� �� ������� �
		return rc; //���������� ��������� �������
	};

	char*Rule::getCRule(char*b, short nchain) //�������� ������� � ���� N->������� (�����, ����� �������(������ �����) � �������)
	{
		char bchain[200]; //������
		b[0] = Chain::alphabet_to_char(nn); b[1] = '-'; b[2] = '>'; b[3] = 0x00; //�������� -> 
		chains[nchain].getCChain(bchain); //�������� ������ ������� �������
		strcat_s(b, sizeof(bchain) + 5, bchain);//��������� ������ (����, � ������ ��������, ������)
		return b;
	};

	short Rule::getNextChain(GRBALPHABET t, Rule::Chain& pchain, short j) //�������� ��������� �� j ���������� �������, ������� � ����� ��� -1 
	{                                                                //(������ ������ �������, ������������ �������, ����� �������)
		short rc = -1;
		while (j < size&&chains[j].nt[0] != t)
			++j;
		rc = (j < size ? j : -1);
		if (rc >= 0)
			pchain = chains[rc];
		return rc;
	};

	char* Rule::Chain::getCChain(char* b) //�������� ������ ������� �������
	{
		for (int i = 0; i < size; i++)
			b[i] = Chain::alphabet_to_char(nt[i]);
		b[size] = 0x00;
		return b;
	};
};