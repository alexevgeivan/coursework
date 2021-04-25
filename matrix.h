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
	};//������������ ��� ����������� ������� � �������� ������� � ������� [][]
	void split(matrix &m11, matrix &m12, matrix &m21, matrix &m22);	//����� �������� ������� �� 4
	void collect(matrix m11, matrix m12, matrix m21, matrix m22);	//�������� ������� �� 4
public:
	matrix(const matrix &other);
	matrix(int a, int b);
	~matrix();
	matrix& operator= (const matrix &other);
	matrix operator+(matrix other);	//�������� ������
	matrix operator-(matrix other);	//��������� ������
	matrix operator*(matrix other);	//��������� ������ ���������� ���������
	matrix operator*(double other);	//��������� ������� �� �����
	proxy operator[](int row);	//������������ ��� ����������� ������� � �������� ������� � ������� [][]
	friend matrix operator*(double left, matrix right);	//��������� ����� �� �������
	friend std::istream& operator>>(std::istream& in, matrix &m);	//���� �������
	friend std::ostream& operator<<(std::ostream& out, matrix &m);	//����� �������
	void resize(int a, int b);	//��������� ������� �������, ���� �������� ������ ������, �� �������������� �������� ����������� ������, ���� �������� ������ ������, �� ������ �������� ���������
	int high()const;	//���������� ����� �������
	int width()const;	//���������� �������� �������
	matrix trans();	//����������������� �������
	friend matrix mult(matrix left, matrix right);	//��������� ������ �� �����������
};

