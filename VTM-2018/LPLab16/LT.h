#pragma once
#include"Error.h"
#include <string>

#define	LEXEMA_FIXSIZE	1			// Фиксированный размер таблицы лексем
#define	LT_MAXSIZE		65536		// Максимальный размер таблицы лексем
#define	LT_TI_NULLDX	0xffffffff	// Пустота в таблице лексем
#define	LEX_INT		    't'			// Целый
#define	LEX_STRING		't'			// Строка
#define LEX_OBJECT      't'			// Обьект
#define	LEX_ID			'i'			// Индентификатор
#define	LEX_LITERAL		'l'			// Литерал
#define	LEX_FUNC		'f'			// Функция
#define	LEX_LET		    'd'			// Let
#define LEX_LIBRVTM     'B'         // Объявления встроенной библиотеки
#define LEX_LENGTH      'e'         // Встроенная библиотека length
#define LEX_POW		    'p'         // Встроенная библиотека pow
#define	LEX_RETURN		'b'			// Return
#define	LEX_ECHO	    'o'			// Echo
#define	LEX_MAIN		'g'			// Main
#define	LEX_SEPARATOR	';'			// ;
#define	LEX_COMMA		','			// ,
#define	LEX_LEFTBRACE	'{'			// {
#define	LEX_BRACELET	'}'			// }
#define	LEX_LEFTHESIS	'('			// (
#define	LEX_RIGHTTHESIS	')'			// )
#define	LEX_PLUS		'+'			// +
#define	LEX_MINUS		'-'			// -
#define	LEX_STAR		'*'			// *
#define	LEX_DIRSLASH	'/'			// /	
#define	LEX_BACKSLASH	'\\'		// 
#define	LEX_EQUAL		'='			// =
#define	LEX_TYPE_NUM	    "int"	
#define	LEX_TYPE_STR	    "string"	
#define	LEX_TYPE_FUNCTION	"function"	
#define	LEX_TYPE_VARIABLE	"variable"	
#define LEX_TYPE_PARAMETR	"parametr"	
#define LEX_TYPE_LITERAL	"literal"
#define LEX_TYPE_STANDART	"library"


namespace LT
{
	struct Entry
	{
		char lexema;			// Лексема
		int sn;					// Номер строки в исходном тексте
		int idxTI;				// Индекс в таблице идентификаторов или LT_TI_NULLIDX
		int tokenId = 0;        // Номер токена
		char operation;         // Операция
		std::string value;
		Entry() {};             // Конструктор по умолчанию
		Entry(char lexema, int snn, int idxti = LT_TI_NULLDX);	// Конструктор
		Entry(char lexema, int snn, char v, int idxti = LT_TI_NULLDX); // Конструктор

	};
	struct LexTable						// Экземпляр таблицы лексем
	{
		int maxsize;					// Ёмкость таблицы лексем
		int size;						// Текущий размер таблицы лексем
		Entry* table;					// Массив строк таблицы лексем
	};
	LexTable Create(int size);			// Ёмкость < LT_MAXSIZE
	void Add(LexTable &lextable, Entry entry);	// Экземпляр таблицы лексем, строка таблицы лексем
	Entry GetEntry(LexTable &lextable, int n);	// Экземпляр таблицы лексем, номер получаемой строки
	void Delete(LexTable &lextable);	// Удалить таблицу лексем (освободить память)
}