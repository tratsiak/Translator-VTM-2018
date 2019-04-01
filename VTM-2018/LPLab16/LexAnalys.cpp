#include "stdafx.h"

namespace LeX
{
	Graph graph[] =                                       
	{   //������ ���������� ������� � ��������������� �� �����
		{ LEX_LIBRVTM, FST::FST(GRAPH_LIBRVTM) }, 
	    { LEX_INT, FST::FST(GRAPH_INT) },
		{ LEX_LENGTH, FST::FST(GRAPH_LENGTH) },
		{ LEX_POW, FST::FST(GRAPH_POW) },
		{ LEX_STRING, FST::FST(GRAPH_STRING) },
		{ LEX_FUNC, FST::FST(GRAPH_FUNC) },
		{ LEX_LET, FST::FST(GRAPH_LET) },
		{ LEX_RETURN, FST::FST(GRAPH_RETURN) },
		{ LEX_ECHO, FST::FST(GRAPH_ECHO) },
		{ LEX_MAIN, FST::FST(GRAPH_MAIN) },
		{ LEX_LITERAL, FST::FST(GRAPH_NUM_LITERAL) },
		{ LEX_LITERAL, FST::FST(GRAPH_STR_LITERAL) },
		{ LEX_ID, FST::FST(GRAPH_ID) },
		{ LEX_SEPARATOR, FST::FST(GRAPH_SEPARATOR) },
		{ LEX_COMMA, FST::FST(GRAPH_COMMA) },
		{ LEX_LEFTBRACE, FST::FST(GRAPH_LEFT_CURLY_BRACE) },
		{ LEX_BRACELET, FST::FST(GRAPH_RIGHT_CURLY_BRACE) },
		{ LEX_LEFTHESIS, FST::FST(GRAPH_OPEN_PARENTHESIS) },
		{ LEX_RIGHTTHESIS, FST::FST(GRAPH_CLOSE_PARENTHESIS) },
		{ LEX_PLUS, FST::FST(GRAPH_PLUS) },
		{ LEX_BACKSLASH, FST::FST(GRAPH_BACK_SLASH) },
		{ LEX_MINUS, FST::FST(GRAPH_MINUS) },
		{ LEX_STAR, FST::FST(GRAPH_ASTERISK) },
		{ LEX_DIRSLASH, FST::FST(GRAPH_FORWARD_SLASH) },
		{ LEX_EQUAL, FST::FST(GRAPH_EQUALS) }
	};
	LEX INITLEX(In::IN InStruct, Log::LOG &log) //������� ��� �������������� �� ������� � �������
	{
		LEX Tables;
		Tables.Lextable = LT::Create(InStruct.TokenCount); //������ ������� ������
		Tables.IDtable = IT::Create(65536); //������ ������� ���������������
		bool isDeclare, isParam, isMainFunc, isExecuted, isLiteral;
		isDeclare = isParam = isMainFunc = isExecuted = isLiteral = false;
		IT::IDDATATYPE funcType = IT::NUM;
		for (int i = 0; i < InStruct.TokenCount; i++) //���� ������� �� ���� �������(������)
		{
			for (int j = 0; j < LENGTH(graph); j++) //���� ������� �� ���� ������ 
			{
				FST::FST fstex(InStruct.tokens[i].token, graph[j].graph);
				if (FST::execute(fstex))//�������� �� ���������� ������
				{
					isExecuted = true;
					switch (graph[j].Lexema) //����� ������ �������
					{
					case LEX_LIBRVTM:
					{
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, Tables.IDtable.size - 1);
						entrylt.tokenId = i;
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_LENGTH:
					{
						IT::Entry entryit(InStruct.tokens[i].token, i, funcType = IT::NUM, IT::S);
						IT::Add(Tables.IDtable, entryit);
						LT::Entry entrylt(LEX_LENGTH, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_ID: //������� ��� ������ ��������������
					{
						if (Tables.Lextable.table[i - 2].lexema == LEX_LET && IT::IsId(Tables.IDtable, InStruct.tokens[i].token) != -1)
						{ 
							throw ERROR_THROW_IN(103, InStruct.tokens[i].line, NULL);
							break;
						}
						if (IT::IsId(Tables.IDtable, InStruct.tokens[i].token) == -1)
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_SEPARATOR || Tables.Lextable.table[i - 1].lexema == LEX_LEFTHESIS || Tables.Lextable.table[i - 1].lexema == LEX_COMMA || Tables.Lextable.table[i - 1].lexema == LEX_RETURN)
							{
								throw ERROR_THROW_IN(105, InStruct.tokens[i].line, NULL);
								break;
							}
							if (Tables.Lextable.table[i - 1].lexema == LEX_FUNC)
							{
								if (!strcmp(InStruct.tokens[i - 2].token, LEX_TYPE_NUM))
								{
									IT::Entry entryit(InStruct.tokens[i].token, i, funcType = IT::NUM, IT::F);
									IT::Add(Tables.IDtable, entryit);
								}
								else
									if (!strcmp(InStruct.tokens[i - 2].token, LEX_TYPE_STR))
									{
										IT::Entry entryit(InStruct.tokens[i].token, i, funcType = IT::STR, IT::F);
										IT::Add(Tables.IDtable, entryit);
									}
								LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, Tables.IDtable.size - 1);
								entrylt.tokenId = i;
								LT::Add(Tables.Lextable, entrylt);
								isParam = true;
								break;
							}
							else
								if (Tables.Lextable.table[i - 1].lexema == LEX_OBJECT)
								{
									if (isParam)
									{
										if (!strcmp(InStruct.tokens[i - 1].token, LEX_TYPE_NUM))
										{
											IT::Entry entryit(InStruct.tokens[i].token, i, IT::NUM, IT::P);
											IT::Add(Tables.IDtable, entryit);
										}
										else
											if (!strcmp(InStruct.tokens[i - 1].token, LEX_TYPE_STR))
											{
												IT::Entry entryit(InStruct.tokens[i].token, i, IT::STR, IT::P);
												IT::Add(Tables.IDtable, entryit);
											}

										if (InStruct.tokens[i + 1].token[0] == LEX_RIGHTTHESIS)
											isParam = false;
									}
									else
										if (isDeclare)
										{
											if (!strcmp(InStruct.tokens[i - 1].token, LEX_TYPE_NUM))
											{
												IT::Entry entryit(InStruct.tokens[i].token, i, IT::NUM, IT::V);
												IT::Add(Tables.IDtable, entryit);
											}
											else
												if (!strcmp(InStruct.tokens[i - 1].token, LEX_TYPE_STR))
												{
													IT::Entry entryit(InStruct.tokens[i].token, i, IT::STR, IT::V);
													IT::Add(Tables.IDtable, entryit);
												}
											if (InStruct.tokens[i + 1].token[0] == LEX_RIGHTTHESIS)
												isDeclare = false;
										}

									LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, Tables.IDtable.size - 1);
									entrylt.tokenId = i;
									LT::Add(Tables.Lextable, entrylt);
									break;
								}
						}
						else
						{
							LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token));
							entrylt.tokenId = i;
							LT::Add(Tables.Lextable, entrylt);
							break;
						}
					}
					case LEX_LITERAL: //������� ��� ������ �������
					{
						isLiteral = true;
						InStruct.tokens[i].isLiteral = true;
						break;
					}
					case LEX_POW:
					{
						IT::Entry entryit(InStruct.tokens[i].token, i, funcType = IT::NUM, IT::S);
						IT::Add(Tables.IDtable, entryit);
						LT::Entry entrylt(LEX_POW, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_PLUS:
					{
						LT::Entry entrylt(LEX_PLUS, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_MINUS:
					{
						LT::Entry entrylt(LEX_MINUS, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_STAR:
					{
						LT::Entry entrylt(LEX_STAR, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_DIRSLASH:
					{
						LT::Entry entrylt(LEX_DIRSLASH, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_SEPARATOR:
					{
						InStruct.tokens[i].isLiteral = false;
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_MAIN:
					{
						isMainFunc = true;
						funcType = IT::NUM;
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_LET:
					{
						isDeclare = true;
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_ECHO:
					{
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_COMMA:
					{
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					default:
					{
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					}
					break;
				}
			}
			if (!isExecuted || isLiteral)
			{
				if (InStruct.tokens[i].isLiteral || isLiteral)
				{
					switch (Tables.Lextable.table[i - 1].lexema)
					{
					case LEX_EQUAL: //������� ��� ������ �����
					{
						InStruct.tokens[i].isLiteral = true;
						LT::Entry entrylt(LEX_LITERAL, InStruct.tokens[i].line, Tables.IDtable.size);
						LT::Add(Tables.Lextable, entrylt);
						if (IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token) != -1)
							if ((Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::V ||
								Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::P))
							{
								IT::SetValue(Tables.IDtable, IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token), InStruct.tokens[i].token);
							}
						break;
					}

					case LEX_ECHO:
					{
						LT::Entry entrylt(LEX_LITERAL, InStruct.tokens[i].line, Tables.IDtable.size - 1);
						entrylt.tokenId = i;
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_RETURN:
					{
						LT::Entry entrylt(LEX_LITERAL, InStruct.tokens[i].line, Tables.IDtable.size - 1);
						entrylt.tokenId = i;
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_COMMA:
					{
						LT::Entry entrylt(LEX_LITERAL, InStruct.tokens[i].line, Tables.IDtable.size-1);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					default:
						LT::Entry entrylt(LEX_LITERAL, InStruct.tokens[i].line, Tables.IDtable.size-1);
						entrylt.tokenId = i;
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
				}
				else
					throw ERROR_THROW_IN(124, Tables.Lextable.table[i - 2].sn, NULL);
			}
			isExecuted = false;
			isLiteral = false;
		}
		return Tables; //���������� ������� ������
	}
}
