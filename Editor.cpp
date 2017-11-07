#include"Editor.h"
#include"other.h"

EasyEditor::EasyEditor(char infName[], char outfName[]) 
{
	inFile.open(infName);
	assert(inFile.is_open());

	ReadFile();

	outFile.open(outfName);
	assert(outFile.is_open());

}

void EasyEditor::ReadFile()
{
	while(!textBuffer.Empty())
	{
		GotoFirstLine();
		DeleteLine();
	}
	char s[1000],c;
	int char_number = 0;
	while (!inFile.eof())
	{
		//inFile >> c;
		//inFile >> noskipws;//!
		c = inFile.get();
		if (c != '\n')
		{
			s[char_number] = c;
			char_number++;
		}
		else
		{
			s[char_number++] = '\n';
			s[char_number++] = '\0';
			char* str = new char[char_number];
			for (int i = 0; i < char_number; i++)
				str[i] = s[i];
			textBuffer.Insert(textBuffer.Length() + 1, str);
			char_number = 0;
		}
	}
	if (char_number != 0)
	{
		char *str = new char[char_number+1];
		for (int i = 0; i < char_number; i++)
			str[i] = s[i];
		str[char_number] = '\0';
		textBuffer.Insert(textBuffer.Length() + 1, str);
		//cout << textBuffer.Length() << endl;
	}
}

void EasyEditor::Show()
{
	textBuffer.Traverse(print);
}

void EasyEditor::WriteFile()
{
	char *str;
	for (int i = 1; i <= textBuffer.Length(); i++)
	{
		if (textBuffer.GetElem(i, str))
			outFile << str;
	}
	outFile << "\n";
}



char EasyEditor::GetChar()
{
	char answer;
	cin >> answer;
	while (answer == ' ' || answer == '\t' || answer == '\n')
		cin >> answer;
	return answer;
}

bool EasyEditor::GotoFirstLine()
{
	if (textBuffer.Empty())
		return  false;
	else
	{
		curLineNo = 1;
		return true;
	}
}

bool EasyEditor::GotoLastLine()
{
	if (textBuffer.Empty())
		return false;
	else
	{
		curLineNo = textBuffer.Length();
		return true;
	}
}

bool EasyEditor::PreviousLine()
{
	if (curLineNo <= 1)
		return false;
	else
	{
		curLineNo--;
		return true;
	}
		
}

bool EasyEditor::NextLine()
{
	if (curLineNo >= textBuffer.Length())
		return false;
	else
	{
		curLineNo++;
		return true;
	}
}

bool EasyEditor::Gotoline(int n)
{
	if (textBuffer.Empty())
		return false;
	else
	{
		if (n<1 || n>textBuffer.Length())
			return false;
		else
		{
			curLineNo = n;
			return true;
		}
	}
}


EasyEditor::~EasyEditor()
{
	inFile.close();
	outFile.close();
	while (!textBuffer.Empty())
	{
		GotoFirstLine();
		DeleteLine();
	}
	textBuffer.~DblLinkList();
}

int EasyEditor::GetLineNumber()
{
	return textBuffer.Length();
}

int EasyEditor::GetCharNumber()
{
	int char_number = 0;
	if (!textBuffer.Empty())
	{
		char* str;
		for (int i = 1; i <= GetLineNumber(); i++)
		{
			textBuffer.GetElem(i, str);
			char_number += Length(str);
		}
	}
	return char_number;
}

bool EasyEditor::InsertLine(char* str)
{
	int len=Length(str);
	char *newstr = new char[len + 1];
	for (int i = 0; i < len; i++)
	{
		newstr[i] = str[i];
	}
	newstr[len] = '\0';
	return textBuffer.Insert(curLineNo, newstr);
}

bool EasyEditor::ChangeLine(char *str)
{
	int len = Length(str);
	char* newstr = new char[len + 1];
	char *oldstr;
	if (!textBuffer.GetElem(curLineNo, oldstr))
		return false;
	//delete []oldstr;
	for (int i = 0; i < len; i++)
	{
		newstr[i] = str[i];
	}
	newstr[len] = '\0';

	return textBuffer.SetElem(curLineNo, newstr);
}

bool EasyEditor::DeleteLine()
{
	char *str;
	if (textBuffer.GetElem(curLineNo, str))
	{
		delete[] str;
		textBuffer.Delete(curLineNo, str);
		return true;
	}
	return false;
}

int EasyEditor::FindString(char *str)
{
	int result = -1;
	char *T;
	for (curLineNo = 1; curLineNo <= textBuffer.Length(); curLineNo++)
	{
		if (textBuffer.GetElem(curLineNo, T))
		{
			result = KMPIndex(T, str, 0);
			if (result != -1)
				break;
		}
	}
	return result;
}

bool  EasyEditor::ChangeSubString(char *str_init,char *str_targ)
{
	char *T;
	if (textBuffer.GetElem(curLineNo, T))
	{
		int result = KMPIndex(T, str_init, 0);
		if (result == -1)
			return false;
		else
		{
			int str_init_len = Length(str_init);
			int str_targ_len = Length(str_targ);
			int Tlen = Length(T);
			char *newstr = new char[Tlen - str_init_len + str_targ_len + 1];
			int i = 0;
			for (; i < result; i++)
			{
				newstr[i] = T[i];
			}
			for (int j = 0; i < result + str_targ_len; i++, j++)
			{
				newstr[i] = str_targ[j];
			}
			for (int j=0; i < Tlen - str_init_len + str_targ_len + 1; i++,j++)
			{
				newstr[i] = T[result + str_init_len + j];
			}
			newstr[i] = '\0';
			textBuffer.SetElem(curLineNo, newstr);
			//delete[] T;
			//T = NULL;
			//textBuffer.SetElem(curLineNo, newstr);
		}
		return true;
	}
	return false;
}

void EasyEditor::ShowCurLine()
{
	char *str;
	if (textBuffer.GetElem(curLineNo, str))
	{
		//cout << str << endl;
		cout << curLineNo << ": " << str ;
	}
}

void EasyEditor::Run()
{
	char* str = new char[100];
	char* str_t = new char[100];
	int result,i;
	char c;
	do
	{
		userCommand = GetChar();
		userCommand = tolower(userCommand);
		while (cin.get() != '\n');
		switch (userCommand)
		{
		case 's':
			ShowCurLine();
			break;
		case 'a':
			Show();
			break;
		case'p':
			PreviousLine();
			break;
		case'n':
			NextLine();
			break;
		case 'g':
			cout << "输入要前进到的行数：" << endl;
			cin >> result;
			Gotoline(result);
			break; 
		case 'o':
			GotoFirstLine();
			break;
		case 'l':
			GotoLastLine();
			break;
		case 'w':
			WriteFile();
			break;
		case 'r':
			cout << "输入要打开的文本路径：" << endl;
			i = 0;
			while ((c = cin.get()) != '\n')
			{
				str[i++] = c;
			}
			str[i] = '\0';
			inFile.close();
			inFile.open(str);
			assert(inFile.is_open());
			ReadFile();
			break;
		case 'c':
			cout << "共有" << GetCharNumber() << "个字符" << endl;
			break;
		case 'e':
			cout << "共有" << GetLineNumber() << "行" << endl;
			break;
		case 'q':
			break;
		case 'f':
			cout << "输入要查找的字符串：" << endl;
			i = 0;
			while ((c = cin.get()) != '\n')
			{
				str[i++] = c;
			}
			str[i] = '\0';
			result = FindString(str);
			if (result == -1)
				cout << "No Find！" << endl;
			else
				cout << "第一次出现于" << curLineNo << "行第" << result+1 << "个字符处" << endl;
			break;
		case 't':
			cout << "输入要被替代的字符：" << endl;
			i = 0;
			while ((c = cin.get()) != '\n')
			{
				str[i++] = c;
			}
			str[i] = '\0';
			cout << "输入替代字符：" << endl;
			i = 0;
			while ((c = cin.get()) != '\n')
			{
				str_t[i++] = c;
			}
			str_t[i] = '\0';
			if (!ChangeSubString(str, str_t))
				cout << "替换失败！" << endl;
			break;
		case 'b':
			cout << "输入替代该行的字符串：" << endl;
			i = 0;
			while ((c = cin.get()) != '\n')
			{
				str[i++] = c;
			}
			str[i++] = '\n';
			str[i] = '\0';
			if (!ChangeLine(str))
				cout << "替换失败！" << endl;
			break;
		case 'd':
			DeleteLine();
			break;
		case 'i':
			cout << "输入要插入的字符串:" << endl;
			i = 0;
			while ((c = cin.get()) != '\n')
			{
				str[i++] = c;
			}
			str[i++] = '\n';
			str[i] = '\0';
			if (!InsertLine(str))
				cout << "插入失败!" << endl;
			break;
		case 'h':
			cout << "s:" << "展示当前行字符串" <<endl;
			cout << "a:" << "展示文本所有内容" << endl;
			cout << "p:" << "到前一行" << endl;
			cout << "n:" << "到下一行" << endl;
			cout << "g:" << "到指定的某一行" << endl;
			cout << "o:" << "到第一行" << endl;
			cout << "l:" << "到最后一行" << endl;
			cout << "w:" << "保存当前文件" << endl;
			cout << "r:" << "重新载入文件：" << endl;
			cout << "c:" << "获得文本字符个数" << endl;
			cout << "e:" << "获得文本行数" << endl;
			cout << "f:" << "全文本查找字符串第一次出现的位置" << endl;
			cout << "t:" << "替换当前行某个字符串" << endl;
			cout << "b:" << "代替当前行 " << endl;
			cout << "d:" << "删除当前行" << endl;
			cout << "i:" << "在当前行插入一行" << endl;
			break;

		default:
			cout << "输入命令有误，输入h获得帮助或输入有效命令字符:" << endl;
		}
	} while (userCommand != 'q');

}