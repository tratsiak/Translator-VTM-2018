#include "stdafx.h"
#include "Generation.h"


ofstream outfile("C://Users//User//Desktop//KP//VTM-2018//Generation.js");
ofstream dopfile("C://Users//User//Desktop//KP//VTM-2018//output.html");
bool isFunction = false;
bool isReturn = false;
int idFunc;
int buf;


void Generation(LT::LexTable &Lextable, In::StToken *tokens, IT::IdTable &idtable)
{
	dopfile << "<script src='isNumber.js'></script>";
	for (int i = 0; i < Lextable.size; i++)
	{
		switch (Lextable.table[i].lexema)
		{
		case LEX_INT:
			break;
		case LEX_MAIN:
		{
			isFunction = true;
			outfile << "\nfunction main()";
			break;
		}
		case LEX_FUNC:
		{
			isFunction = true;
			idFunc = Lextable.table[i + 1].idxTI;
			buf = Lextable.table[i + 1].idxTI;
			outfile << "function " << idtable.table[buf].id;
			i++;
			break;
		}
		case LEX_LEFTBRACE:
		{
			outfile<<" {";
			break;
		}
		case LEX_BRACELET:
		{
			if (isFunction) 
			    outfile << "\n}\n";
			break;
		}
		case LEX_LET:
		{
			outfile << "\nvar ";
			break;
		}
		case LEX_LIBRVTM:
		{
			dopfile << "<script src='LIBRVTM.js'></script>";
			break;
		}
		case LEX_ID:
		{
			int y;
			y = Lextable.table[i].idxTI;
			if (Lextable.table[i - 2].lexema == LEX_ECHO) {
				outfile << idtable.table[y].id;
			}
			else
			{
				if (idtable.table[y].iddatatype == IT::STR || IT::NUM && Lextable.table[i - 2].lexema != LEX_ECHO)
					outfile << idtable.table[y].id;
			}
			break;
		}
		case LEX_EQUAL:
		{
			outfile << " = ";
			break;
		}
		case LEX_SEPARATOR:
		{
			if (Lextable.table[i - 1].lexema == LEX_LIBRVTM) {
				break;
			}
			outfile << ";";
			break;
		}
		case LEX_LENGTH:
		{
			outfile << "strlen";
			break;
		}
		case LEX_LITERAL:
		{
			if (tokens[i].isLiteral == true)
			{
				if (tokens[i].isStr == true)
					outfile << tokens[i].token;
				else
				{
					int tp;
					tp = atoi(tokens[i].token);
					if (tp > INT_MAXSIZE)
					{
						throw ERROR_THROW(6);
					}
					else
					{
						if (tp < INT_MIN)
							throw ERROR_THROW(6);
					}
					outfile << tp;
					break;
				}
			}
			break;
		}
		case LEX_ECHO:
		{
			outfile << "\ndocument.writeln";
			break;
		}
		case LEX_LEFTHESIS:
		{
			if (tokens[i + 1].isLiteral != true && Lextable.table[i - 1].lexema == LEX_ECHO)
			{
					outfile << "(isN(";
					break;
			}
			outfile << "(";
			break;
		}
		case LEX_RIGHTTHESIS:
		{
			if (tokens[i - 1].isLiteral != true && Lextable.table[i - 3].lexema == LEX_ECHO)
			{
					outfile << "))";
					break;
			}
			outfile << ")";
			break;
		}
		case LEX_PLUS:
		{
			outfile << "+";
			break;
		}
		case LEX_STAR:
		{
			outfile << "*";
			break;
		}
		case LEX_MINUS:
		{
			outfile << "-";
			break;
		}
		case LEX_DIRSLASH:
		{
			outfile << "/";
			break;
		}
		case LEX_COMMA:
		{
			outfile << ",";
			break;
		}
		case LEX_RETURN:
		{
			isReturn = true;
			if (isFunction) {
				outfile << "\nreturn ";
			}
			break;
		}
		case LEX_POW:
		{
			outfile << "pow";
			break;
		}
		default:
		{
			outfile << tokens[i].token;
			break;
		}
		}
	}
	outfile << "\nmain();";
	dopfile << "<script src='Generation.js'></script>";
	dopfile.close();
	outfile.close();
}