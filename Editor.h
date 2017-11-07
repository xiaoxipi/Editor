#pragma once
#include"DLL.h"
#include<fstream>
#include<cassert>

class EasyEditor
{
private:
	DblLinkList<char*> textBuffer;
	int curLineNo;
	ifstream inFile;
	ofstream outFile;
	char userCommand;

	char GetChar();
	void Show();
	bool GotoFirstLine();
	bool GotoLastLine();
	bool NextLine();
	bool PreviousLine();
	bool Gotoline(int n);
	bool InsertLine(char *str);
	bool DeleteLine();
	bool ChangeLine(char *str);
	void ReadFile();
	void WriteFile();
	int GetLineNumber();
	int GetCharNumber();
	bool ChangeSubString(char *str_init,char*str_targ);
	int FindString(char*  str);
	void ShowCurLine();
public:
	EasyEditor(char infName[], char outfName[]);
	~EasyEditor();
	//bool GetCommand();
	void Run();
	//void Show();
	//void WriteFile();
};


