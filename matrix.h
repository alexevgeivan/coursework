#include <algorithm>
#include <iostream>
#include <iomanip>


#pragma once



class matrix{
private:
	double **data;
	int n, m;
	class proxy {
		friend class matrix;
	public:
		double& operator[](int col);
	private:
		proxy(matrix &parent_, int row_) :
			parent(parent_),
			row(row_)
		{}
		matrix& parent;
		int row;
	};//используется для возможности доступа к элементу матрицы с помощью [][]
	void split(matrix &m11, matrix &m12, matrix &m21, matrix &m22);	//делит исходную матрицу на 4
	void collect(matrix m11, matrix m12, matrix m21, matrix m22);	//собирает матрицу из 4
public:
	matrix(const matrix &other);
	matrix(int a, int b);
	~matrix();
	matrix& operator= (const matrix &other);
	matrix operator+(matrix other);	//сложение матриц
	matrix operator-(matrix other);	//вычитание матриц
	matrix operator*(matrix other);	//умножение матриц алгоритмом Штрассена
	matrix operator*(double other);	//умножение матрицы на число
	proxy operator[](int row);	//используется для возможности доступа к элементу матрицы с помощью [][]
	friend matrix operator*(double left, matrix right);	//умножение числа на матрицу
	friend std::istream& operator>>(std::istream& in, matrix &m);	//ввод матрицы
	friend std::ostream& operator<<(std::ostream& out, matrix &m);	//вывод матрицы
	void resize(int a, int b);	//изменение размера матрицы, если исходный размер меньше, то дополнительные элементы заполняются нулями, если исходный размер больше, то лишние элементы удаляются
	int high()const;	//количество строк матрицы
	int width()const;	//количество столбцов матрицы
	matrix trans();	//транспланирование матрицы
	friend matrix mult(matrix left, matrix right);	//умножение матриц по определению
};

