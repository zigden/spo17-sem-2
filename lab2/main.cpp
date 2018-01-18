#include <iostream>
#include <conio.h>     //Для оформления программы
#include <windows.h>
#include <string>  //Класс строки
#include <cstdlib>
#include <math.h>

using namespace std;
typedef unsigned int uni;   //Вводим собственное обозначение типа данных (unsigned int = uni)

//Класс строки представленной в виде двочного кода для русского алфавита
//******************************************************************************
class cystr
{
public:
	int dem;    //размерность строки
	int **s_c;  //шифрованная строка в двоичном коде
	int **open; //открытая строка в двоичном коде
	static string alph; //статическая поле класса (алфавит) (string - тип данных)
	cystr();
	cystr(int **, int);
	~cystr();
};
//******************************************************************************

//Описание статического поля класса и методов
//******************************************************************************
string cystr::alph = "АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюя";
cystr::cystr() {}
cystr::cystr(int **p, int n)
{
	dem = n;
	s_c = new int *[n];
	open = new int *[n];
	for (int i = 0; i < n; i++)
	{
		s_c[i] = p[i];
		open[i] = p[i];
	}
}
cystr::~cystr()
{
	dem = 0;
	delete[] open;
	delete[] s_c;
}
//******************************************************************************

//Класс ключа для шифровки и дешифровки
//******************************************************************************
class key
{
	int dem;
	int **s_k;  // Строка ключа в двоичном коде
public:
	key();
	key(int **, int);
	~key();
	void enc(cystr &);  //Метод шифрования строки (ничего не возвращает просто шифрует строку)
	void dec(cystr &);  //передаём в функцию значения по адресу
	friend int ** encode(string);
};
//******************************************************************************

//Описание методов шифровани и дешифрования
//******************************************************************************
key::key(int **p, int n)
{
	dem = n;
	s_k = new int *[n];
	for (int i = 0; i < n; i++)
		s_k[i] = p[i];
}
key::~key()
{
	dem = 0;
	delete[] s_k;
}
void key::enc(cystr &toc)
{
	for (int i = 0; i < dem; i++)
		for (int j = 0; j < 6; j++)
			toc.s_c[i][j] = (toc.open[i][j] + s_k[i][j]) % 2;
}
void key::dec(cystr &tod)
{
	for (int i = 0; i < dem; i++)
		for (int j = 0; j < 6; j++)
			tod.open[i][j] = (tod.s_c[i][j] + s_k[i][j]) % 2;
}
//******************************************************************************

//Функциии кодирования в двоичный код строки и обратно
//******************************************************************************
int ** encode(string s)
{
	char err[] = "Ошибка кодирования. Неизвестный символ";
	CharToOem(err, err);
	int *temp; // временная переменная для хранения промежуточных результатов
	temp = new int[s.size()];
	for (uni i = 0; i < s.size(); i++)
	{
		temp[i] = cystr::alph.find(s[i], 0); //temp - одномерный массив для хранения строки в виде десятичных чисел (от 0 до 63)
		if (temp[i] == -1)
		{
			cout << err << endl;
			system("pause");
			abort();
		}
	}
	int **p;
	p = new int *[s.size()];
	for (uni i = 0; i < s.size(); i++)
		p[i] = new int[6];
	for (uni i = 0; i < s.size(); i++)
		for (int j = 0; j < 6; j++)
		{
			p[i][5 - j] = temp[i] % 2;
			temp[i] = int(temp[i] / 2);
		}
	return p;
}

char * decode(int **p, int n)
{
	int *temp;
	temp = new int[n];

	for (int i = 0; i < n; i++)
	{
		temp[i] = 0;
		for (int j = 0; j < 6; j++)
			temp[i] += p[i][j] * pow(2.0, (5 - j));
	}

	char * s;
	s = new char[n + 1];
	for (int i = 0; i < n; i++)
		s[i] = cystr::alph[temp[i]];
	s[n] = '\0';
	return s;
}
//******************************************************************************

//Функция управления шифрованием (интерфейс)
//******************************************************************************
void action1()
{
	char *p;
	uni q;
	char buf[256];
	string s;
	char instr[] = "Введите строку без пробелов";
	char inkey1[] = "Введите ключ шифрования такой же длинны";
	char encyp_suc[] = "Строка зашифрована";
	char iner[] = "Ошибка при вводе. Привышена размерность";
	CharToOem(iner, iner);
	CharToOem(encyp_suc, encyp_suc);
	CharToOem(inkey1, inkey1);
	CharToOem(instr, instr);
	cout << instr << endl;
	cin >> buf;
	OemToChar(buf, buf);
	s = buf;
	q = s.size();
	cystr sc1(encode(s), s.size());   //sc1 - объект класса  cystr
	cout << inkey1 << endl;
	cin >> buf;
	OemToChar(buf, buf);
	s = buf;
	if (q != s.size())
	{
		cout << iner << endl;
		system("pause");
		abort();
	}
	key o(encode(s), s.size());  //o - объект класа key
	o.enc(sc1);
	cout << encyp_suc << endl;
	p = decode(sc1.s_c, sc1.dem);
	CharToOem(p, p);
	cout << p << endl;
	system("pause");
	system("cls");  //очистка экрана
}
//******************************************************************************

//Функция управления дешифрованием (интерфейс)
//******************************************************************************
void action2()
{
	uni q;
	char *p;
	char buf[256];
	string s;
	char decyp_suc[] = "Строка дешифрована";
	char instr[] = "Введите строку без пробелов";
	char inkey2[] = "Введите ключ дешифрования такой же длинны";
	char iner[] = "Ошибка при вводе. Привышена размерность";
	CharToOem(iner, iner);
	CharToOem(inkey2, inkey2);
	CharToOem(instr, instr);
	CharToOem(decyp_suc, decyp_suc);
	cout << instr << endl;
	cin >> buf;
	OemToChar(buf, buf);
	s = buf;
	q = s.size();
	cystr sc1(encode(s), s.size());
	cout << inkey2 << endl;
	cin >> buf;
	OemToChar(buf, buf);
	s = buf;
	if (q != s.size())
	{
		cout << iner << endl;
		system("pause");
		abort();
	}
	key o(encode(s), s.size());
	o.dec(sc1);
	cout << decyp_suc << endl;
	p = decode(sc1.open, sc1.dem);
	CharToOem(p, p);
	cout << p << endl;
	system("pause");
	system("cls");
}
//******************************************************************************

//Главная функция
//******************************************************************************
int main()
{
	int q = 0;
	char buf[256];
	char welcome[] = "Здрасте\n";
	char qes[] = "Выбирите действие\n1 - Шифрование\n2 - Дешифрование\n3 - Выход";
	char er[] = "Неверно";
	CharToOem(welcome, welcome);
	CharToOem(qes, qes);
	CharToOem(er, er);
	cout << welcome << endl << endl;
	while (q != '3')
	{
		cout << qes << endl;
		cin >> q;
		getchar();
		switch (q)
		{
		case 1: action1(); break;
		case 2: action2(); break;
		case 3: return 0;
		default: cout << er << endl; system("pause"); system("cls");
		}
	}
}
//******************************************************************************


