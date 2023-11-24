// Workbook5_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.


#include <iostream>
#include "TreeFile.h"
#include "SearchTree.h"
#include <iostream>
#include <chrono>
using namespace std;

int main()
{
	system("chcp 1251");

	string txt_name = "a.txt";
	string bin_name = "b.bin";
	int choice;
	int key;

	TreeFile obj;
	

	while (true)
	{
		cout << "Выберите действие: " << endl;
		cout << "1. Ввод имён текстового и бинарного файлов" << endl;
		cout << "2. Создание бинарного файла на основе текстового" << endl;
		cout << "3. Поиск ключа по индексу" << endl;
		cout << "4. Удалить запись" << endl;
		cout << "5. Вывод дерева поиска" << endl;
		cin >> choice;

		auto start = chrono::steady_clock::now();
		auto end = chrono::steady_clock::now();
		auto diff = end - start;
		cout << sizeof(Node);
		switch (choice)
		{
		case 1:
			cout << "Имя текстового файла: ";
			cin >> txt_name;
			cout << "Имя бинарного файла: ";
			cin >> bin_name;
			break;
		case 2:
			obj.createStruct(txt_name, bin_name);
			break;
		case 3:
			cout << "Введите номер рейса: ";
			cin >> key;
			start = chrono::steady_clock::now();
			if (obj.findRace(bin_name, key) == -1)
			{
				cout << "Рейса с стаким номером не существует" << endl;
			}
			end = chrono::steady_clock::now();
			diff = end - start;
			cout << chrono::duration <double, nano>(diff).count() << " ns" << endl;
			break;
		case 4:
			cout << "Введите номер рейса: ";
			cin >> key;
			if (obj.removeRace(bin_name, key) == -1)
			{
				cout << "Рейса с стаким номером не существует" << endl;
			}
			break;
		case 5:
			obj.root->printTree(0);
			break;
		default:
			cout << "Неверно введена опция" << endl;
			break;
		}
	}

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
