#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

unsigned int* num_bit_view (unsigned int a) {
	unsigned int* ab = new unsigned int[32];
	for (int i = 0; i < 32; ++i) {
		if ((a > 0)) {
 			ab[i] = a % 2;
			a = a / 2;
		}
		else {
			ab[i] = 0;
		}
	}
	return ab;
}

class Set {

	unsigned int m_x; // ����� � �������� ������ �������� �����
public:
	Set() : m_x(0) {};
	Set(unsigned int a) : m_x(pow(2, a)) {};
	Set(unsigned int* arr, int n) {
		m_x = 0;
		for (int i = 0; i < n; ++i) {
			m_x += (pow(2, arr[i]));
		}
	}
	/*~Set() {
		delete ////??????
	}*/

	Set(const Set& orig) {
		m_x = orig.m_x;
	}

	Set operator +=(unsigned int a) {
		m_x += pow(2, a);
		return m_x;
	}
	Set operator+(unsigned int a) {
		unsigned int res;
		res = m_x;
		res += pow(2, a);
		return res;
	}

	Set operator-(unsigned int a) {
		m_x -= pow(2, a);
		return m_x;
	}
	Set& operator=(const Set& that) {
		if (this != &that) {
			m_x = that.m_x;
		}
		return *this;
	}

	

	Set operator&(Set a) {
		unsigned int cross = m_x & a.m_x; /// �����, ������� � ������ ������ ������� �������
		Set res;
		res.m_x = cross;
		return res;
	}


	Set operator&=(Set a) {
		unsigned int cross = m_x & a.m_x; /// �����, ������� � ������ ������ ������� �������
		this->m_x = cross;
		return *this;
	}

	Set operator|(Set a) {
		unsigned int cross = m_x | a.m_x; 
		Set res;
		res.m_x = cross;
		return res;
	}

	Set operator^(Set a) {
		unsigned int cross = m_x ^ a.m_x; 
		Set res;
		res.m_x = cross;
		return res;
	}

	bool operator[](unsigned int a) {
		unsigned int* v = num_bit_view(this->m_x);
		if (v[a] == 1) {
			return 1;
		}
		else return 0;
	}

	unsigned int* bit_view() {
		unsigned int* ab = new unsigned int[32];
		for (int i = 0; i < 32; ++i) {
			if ((m_x > 0)) {
				ab[i] = m_x % 2;
				m_x = m_x / 2;
			}
			else {
				ab[i] = 0;
			}
		}
		return ab;
	}

	void printSet() {
		unsigned int* s = bit_view();
		for (int i = 0; i < 32; ++i) {
			if (s[i] == 1) {
				cout << i << " ";
			}
		}
	}
	void readSet(std::istream& in) {
			int n, sym;
			in >> n;
			for (int i = 0; i < n; i++) {
				in >> sym;
				*this += sym;
			}
	}
	Set operator~() {
		unsigned int cross = ~m_x;
		Set res;
		res.m_x = cross;
		return res;
	}
};



int main() {
	std::ifstream fin("input.txt");
	Set a;
	a.readSet(fin);
	Set b;
	b.readSet(fin);
	Set c;
	c.readSet(fin);
	Set d;
	d.readSet(fin);
	Set k= (a & (b | c)) & ~d;
	k.printSet();
	fin.close();
	return 0;
}
