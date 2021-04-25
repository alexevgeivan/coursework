#include "matrix.h"


matrix::matrix(const matrix &other) {
	n = other.high();
	m = other.width();
	data = new double*[n];
	for (int i = 0; i < n; i++) {
		data[i] = new double[m];
		for (int j = 0; j < m; j++)data[i][j] = other.data[i][j];
	}
}

matrix::matrix(int a, int b) {
	n = a;
	m = b;
	data = new double*[n];
	for (int i = 0; i < n; i++) { 
		data[i] = new double[m]; 
		for (int j = 0; j < m; j++)data[i][j] = 0;
	}
}

matrix::~matrix() {
	for (int i = 0; i < n; i++)delete[]data[i];
	delete[]data;
}

matrix& matrix::operator=(const matrix &other) {
	for (int i = 0; i < n; i++)delete[]data[i];
	delete[]data;
	n = other.high();
	m = other.width();
	data = new double*[n];
	for (int i = 0; i < n; i++) {
		data[i] = new double[m];
		for (int j = 0; j < m; j++)data[i][j] = other.data[i][j];
	}
	return *this;
}

int matrix::high() const {
	return n;
}

int matrix::width() const {
	return m;
}

matrix matrix::operator+(matrix other) {
	try {
		if ((this->high() != other.high()) || (this->width() != other.width()))throw 1;
	}
	catch (int a) {
		std::cerr << "ERROR : the dimensions of the matrices are not equivalent";
		return matrix(0, 0);
	}
	matrix tmp = *this;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			tmp.data[i][j] += other.data[i][j];
		}
	}
	return tmp;
}

matrix matrix::operator-(matrix other) {
	try {
		if ((this->high() != other.high()) || (this->width() != other.width()))throw 1;
	}
	catch (int a) {
		std::cerr << "ERROR : the dimensions of the matrices are not equivalent";
		return matrix(0, 0);
	}
	matrix tmp = *this;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)tmp.data[i][j] -= other.data[i][j];
	}
	return tmp;
}

matrix matrix::operator*(double other) {
	matrix tmp = *this;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)tmp.data[i][j] *= other;
	}
	return tmp;
}

matrix operator*(double left, matrix right) {
	matrix tmp = right;
	for (int i = 0; i < tmp.n; i++) {
		for (int j = 0; j < tmp.m; j++) tmp.data[i][j] *= left;
	}
	return tmp;
}

double& matrix::proxy::operator[](int col) {
	return parent.data[row][col];
}

matrix::proxy matrix::operator[](int row) {
	return proxy(*this, row);
}

std::istream& operator>>(std::istream& in, matrix &m) {
	for (int i = 0; i < m.high(); i++) {
		for (int j = 0; j < m.width(); j++)in >> m.data[i][j];
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, matrix &m) {
	for (int i = 0; i < m.high(); i++) {
		double *t = m.data[i];
		for (int j = 0; j < m.width(); j++)
			out << std::setw(12) << std::setprecision(4) << m.data[i][j];
		out << "\n";
	}
	return out;
}

void matrix::resize(int a, int b) {
	matrix tmp = *this;
	for (int i = 0; i < n; i++)delete[]data[i];
	delete[]data;
	n = a;
	m = b;
	data = new double*[a];
	if (a < tmp.n) {
		if (b < tmp.m) {
			for (int i = 0; i < a; i++) {
				data[i] = new double[b];
				for (int j = 0; j < b; j++) data[i][j] = tmp.data[i][j];
			}
		}
		else {
			for (int i = 0; i < a; i++) {
				data[i] = new double[b];
				for (int j = 0; j < tmp.m; j++) data[i][j] = tmp.data[i][j];
				for (int j = tmp.m; j < b; j++) data[i][j] = 0;
			}
		}
	}
	else {
		if (b < tmp.m) {
			for (int i = 0; i < tmp.n; i++) {
				data[i] = new double[b];
				for (int j = 0; j < b; j++) data[i][j] = tmp.data[i][j];
			}
		}
		else {
			for (int i = 0; i < tmp.n; i++) {
				data[i] = new double[b];
				for (int j = 0; j < tmp.m; j++) data[i][j] = tmp.data[i][j];
				for (int j = tmp.m; j < b; j++) data[i][j] = 0;
			}
		}
		for (int i = tmp.n; i < a; i++) {
			data[i] = new double[b];
			for (int j = 0; j < b; j++) data[i][j] = 0;
		}
	}
}

matrix matrix::trans() {
	matrix tmp(m, n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			tmp.data[i][j] = data[j][i];
	return tmp;
}

matrix mult(matrix left, matrix right) {
	matrix tmp(left.n, right.m);
	matrix r = right.trans();
	for (int i = 0; i < tmp.n; i++)
		for (int j = 0; j < tmp.m; j++) {
			tmp.data[i][j] = 0;
			for (int k = 0; k < r.m; k++) {
				tmp.data[i][j] += left.data[i][k] * r.data[j][k];
			}
		}
	return tmp;
}

void matrix::split(matrix &m11, matrix &m12, matrix &m21, matrix &m22) {
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < m/2; j++)
			m11.data[i][j] = data[i][j];
		for (int j = m / 2; j < m; j++)
			m12.data[i][j - m / 2] = data[i][j];
	}
	for (int i = n/2; i < n; i++) {
		for (int j = 0; j < m / 2; j++)
			m21.data[i - n / 2][j] = data[i][j];
		for (int j = m / 2; j < m; j++)
			m22.data[i - n / 2][j - m / 2] = data[i][j];
	}
}

void matrix::collect(matrix m11, matrix m12, matrix m21, matrix m22) {
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < m / 2; j++)
			data[i][j] = m11.data[i][j];
		for (int j = m / 2; j < m; j++)
			data[i][j] = m12.data[i][j - m / 2];
	}
	for (int i = n / 2; i < n; i++) {
		for (int j = 0; j < m / 2; j++)
			data[i][j] = m21.data[i - n / 2][j];
		for (int j = m / 2; j < m; j++)
			data[i][j] = m22.data[i - n / 2][j - m / 2];
	}
}

matrix matrix::operator*(matrix other) {
	try {
		if (m!=other.n)throw 1;
	}
	catch (int a) {
		std::cerr << "ERROR : the dimensions of the matrices are not equivalent";
		return matrix(0, 0);
	}
	if (this->n < 64 && other.m < 64 || this->n < 4 || other.m < 4) {
		return mult(*this, other);
	}
	matrix a = *this, b = other;
	if ((a.n & 1) | (a.m & 1))
		a.resize(a.n + (a.n & 1), a.m + (a.m & 1));
	if ((b.n & 1) | (b.m & 1))
		b.resize(b.n + (b.n & 1), b.m + (b.m & 1));
	matrix a11(a.n / 2, a.m / 2), a12(a.n / 2, a.m / 2), a21(a.n / 2, a.m / 2), a22(a.n / 2, a.m / 2), b11(b.n / 2, b.m / 2), b12(b.n / 2, b.m / 2), b21(b.n / 2, b.m / 2), b22(b.n / 2, b.m / 2);
	a.split(a11, a12, a21, a22);
	b.split(b11, b12, b21, b22);
	
	matrix
 		p1 = (a11 + a22)*(b11 + b22),
		p2 = (a21 + a22)*b11,
		p3 = a11*(b12 - b22),
		p4 = a22*(b21 - b11),
		p5 = (a11 + a12)*b22,
		p6 = (a21 - a11)*(b11 + b12),
		p7 = (a12 - a22)*(b21 + b22);
		matrix
		c11 = p1 + p4 - p5 + p7,
		c12 = p3 + p5,
		c21 = p2 + p4,
		c22 = p1 - p2 + p3 + p6;
	matrix c(a.n, b.m);
	c.collect(c11, c12, c21, c22);
	if ((this->n & 1) | (other.m & 1))c.resize(this->n, other.m);
	return c;
}
