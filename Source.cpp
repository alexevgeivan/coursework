#include "matrix.h"
#include <iostream>

using namespace std;

int main() {
	int n, m;
	setlocale(LC_ALL, "rus");
	cout << "Введите размеры первой матрицы: ";
	cin >> n >> m;
	if (n <= 0 || m <= 0) {
		cout << "Некорректные размеры матрицы";
		system("pause>nul");
		return 0;
	}
	matrix a(n, m);
	cout << "Введите первую матрицу\n";
	cin >> a;
	system("cls");
	cout << "Введите размеры второй матрицы: ";
	cin >> n >> m;
	if (n <= 0 || m <= 0 || a.high() != m) {
		cout << "Некорректные размеры матрицы";
		system("pause>nul");
		return 0;
	}
	matrix b(n, m);
	cout << "Введите вторую матрицу\n";
	cin >> b;
	system("cls");
	matrix c = a*b;
	cout << "Матрица A:\n" << a << "\nМатрица B:\n" << b << "\n\nМатрица C:\n" << c;
	system("pause>>nul");
}