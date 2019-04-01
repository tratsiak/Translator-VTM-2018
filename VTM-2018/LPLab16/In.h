#pragma once
#define IN_MAX_LEN_TEXT 1024*1024  //��������� ��� ����������� ������������ ����� ������
#define IN_CODE_ENDL '\n'          //��������� ��� ����������� �������� �� ����� ������



#define IN_CODE_TABLE {\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::STAB, IN::T, IN::T, IN::T, IN::T, IN::T,\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::STAB, IN::T, IN::QUOTE, IN::T, IN::T, IN::T, IN::T, IN::T, IN::SEP, IN::SEP, IN::SEP, IN::SEP, IN::SEP, IN::SEP, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::SEP, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::SEP, IN::SEP, IN::SEP, IN::T, IN::T, \
	\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::F, IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T \
}


namespace In
{
	struct StToken //��������� ��� ������(�����)
	{
		int line;  // ������ � ������� ��������� �����
		char token[1024]; //������ ������� ���� char
		bool isLiteral; // �������� �� ���������
		bool isStr = false;// �������� �� ������� �������
	};

	struct IN //��������� ��� ������� ���������
	{
		enum { T = 1024, F = 2048, I = 4096, SEP = 8192, STAB = 16384, SEPS = 32768, QUOTE = 65536 };
		int code[256];
		int size = NULL;
		int lines = NULL;
		int ignor = NULL;
		int TokenCount;
		unsigned char* text;
		StToken *tokens;
	};
	IN getin(wchar_t infile[], wchar_t logfile[]);
	void add_token(IN &g, char* &buffer, int &pos_buf, bool &isLiteral, bool &isStr); //�������� ��� ���������� ������(�����) � �����������
}