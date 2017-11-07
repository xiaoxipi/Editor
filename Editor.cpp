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
			cout << "����Ҫǰ������������" << endl;
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
			cout << "����Ҫ�򿪵��ı�·����" << endl;
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
			cout << "����" << GetCharNumber() << "���ַ�" << endl;
			break;
		case 'e':
			cout << "����" << GetLineNumber() << "��" << endl;
			break;
		case 'q':
			break;
		case 'f':
			cout << "����Ҫ���ҵ��ַ�����" << endl;
			i = 0;
			while ((c = cin.get()) != '\n')
			{
				str[i++] = c;
			}
			str[i] = '\0';
			result = FindString(str);
			if (result == -1)
				cout << "No Find��" << endl;
			else
				cout << "��һ�γ�����" << curLineNo << "�е�" << result+1 << "���ַ���" << endl;
			break;
		case 't':
			cout << "����Ҫ��������ַ���" << endl;
			i = 0;
			while ((c = cin.get()) != '\n')
			{
				str[i++] = c;
			}
			str[i] = '\0';
			cout << "��������ַ���" << endl;
			i = 0;
			while ((c = cin.get()) != '\n')
			{
				str_t[i++] = c;
			}
			str_t[i] = '\0';
			if (!ChangeSubString(str, str_t))
				cout << "�滻ʧ�ܣ�" << endl;
			break;
		case 'b':
			cout << "����������е��ַ�����" << endl;
			i = 0;
			while ((c = cin.get()) != '\n')
			{
				str[i++] = c;
			}
			str[i++] = '\n';
			str[i] = '\0';
			if (!ChangeLine(str))
				cout << "�滻ʧ�ܣ�" << endl;
			break;
		case 'd':
			DeleteLine();
			break;
		case 'i':
			cout << "����Ҫ������ַ���:" << endl;
			i = 0;
			while ((c = cin.get()) != '\n')
			{
				str[i++] = c;
			}
			str[i++] = '\n';
			str[i] = '\0';
			if (!InsertLine(str))
				cout << "����ʧ��!" << endl;
			break;
		case 'h':
			cout << "s:" << "չʾ��ǰ���ַ���" <<endl;
			cout << "a:" << "չʾ�ı���������" << endl;
			cout << "p:" << "��ǰһ��" << endl;
			cout << "n:" << "����һ��" << endl;
			cout << "g:" << "��ָ����ĳһ��" << endl;
			cout << "o:" << "����һ��" << endl;
			cout << "l:" << "�����һ��" << endl;
			cout << "w:" << "���浱ǰ�ļ�" << endl;
			cout << "r:" << "���������ļ���" << endl;
			cout << "c:" << "����ı��ַ�����" << endl;
			cout << "e:" << "����ı�����" << endl;
			cout << "f:" << "ȫ�ı������ַ�����һ�γ��ֵ�λ��" << endl;
			cout << "t:" << "�滻��ǰ��ĳ���ַ���" << endl;
			cout << "b:" << "���浱ǰ�� " << endl;
			cout << "d:" << "ɾ����ǰ��" << endl;
			cout << "i:" << "�ڵ�ǰ�в���һ��" << endl;
			break;

		default:
			cout << "����������������h��ð�����������Ч�����ַ�:" << endl;
		}
	} while (userCommand != 'q');

}