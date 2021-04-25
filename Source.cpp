#include "matrix.h"
#include <iostream>

using namespace std;

int main() {
	int n, m;
	setlocale(LC_ALL, "rus");
	cout << "������� ������� ������ �������: ";
	cin >> n >> m;
	if (n <= 0 || m <= 0) {
		cout << "������������ ������� �������";
		system("pause>nul");
		return 0;
	}
	matrix a(n, m);
	cout << "������� ������ �������\n";
	cin >> a;
	system("cls");
	cout << "������� ������� ������ �������: ";
	cin >> n >> m;
	if (n <= 0 || m <= 0 || a.high() != m) {
		cout << "������������ ������� �������";
		system("pause>nul");
		return 0;
	}
	matrix b(n, m);
	cout << "������� ������ �������\n";
	cin >> b;
	system("cls");
	matrix c = a*b;
	cout << "������� A:\n" << a << "\n������� B:\n" << b << "\n\n������� C:\n" << c;
	system("pause>>nul");
}