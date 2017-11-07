#include"DLL.h"
#include"Editor.h"

/*void print(const  char& c)
{
	cout << c;
}*/

int main()
{
	char* s1, *s2;
	s1 = new char[100];
	s2 = new char[100];
	cout << "输入要打开的文本路径：" << endl;
	cin.getline(s1, '\n');
	cout << "输入保存文本所在路径：" << endl;
	cin.getline(s2, '\n');
	EasyEditor a(s1,s2);
	a.Run();
	//a.Show();
	//a.WriteFile();
	/*DblLinkList<char> a,b;
	for (int i = 1; i <10; i++)
	{
		a.Insert(i, 48 + i);
	}
	cout << b.Empty() << endl;
	b = a;
	DblLinkList<char> cs(a);
	char c;
	b.GetElem(1,c);
	cs.Traverse(print);
	cout << endl;
	cout << c <<b.Length()<<" "<<b.Empty()<< endl;*/
	//cout << '\n' << '\n';
	//system("pause");
	return 0;
}