#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cmath>  
#include <typeinfo>
#include <iomanip>
#include <algorithm>

using namespace std;

template< class BidirIt >
void reverse(BidirIt first, BidirIt last);

template <class T>
class Vector
{
private:

    unsigned int m_capacity;
    T* m_body;
    unsigned int m_length; ///по факту кол-во лежащих эл-тов

public:

    ~Vector() {
        if (m_length == 0);
        else {
            delete[] m_body;
        }
       
    }

    void alloc_body(unsigned int capacity) {
        m_capacity = capacity;
        if (capacity == 0)
            m_body = nullptr;
        else
            m_body = new T[capacity];
    }

    T& at(unsigned int position) {
        if (position >= m_capacity)
            throw std::out_of_range("ERROR");
        return m_body[position];
    }

    Vector() {
        m_length = 0;
        alloc_body(0);
    }

    Vector(unsigned int capacity) {
        alloc_body(capacity);
        m_length = 0;
    }

    void push_back(T symbol) {
        if (m_length == m_capacity) {
            unsigned int newCapacity;
            if (m_capacity == 0) {
                newCapacity = 1;
            }
            else {
                newCapacity = m_capacity * 2;
            }
            T* oldBody = m_body;
            alloc_body(newCapacity);
            for (unsigned int i = 0; i < m_length; ++i)
                at(i) = oldBody[i];
            delete[] oldBody;
        }
        ++m_length;
        at(m_length - 1) = symbol;
    }

    Vector& operator=(const Vector& other) {
        m_length = other.m_length;
        m_capacity = other.m_capacity;
        for (int i = 0; i < m_length; ++i) {
            m_body[i] = other.m_body[i];
        }
        
        return *this;
    }

    Vector(const Vector& orig) {
        Vector a = Vector(orig.m_capacity);
        for (int i = 0; i < orig.m_length; i++) {
            a.m_body[i] = orig[i];
        }
    }

    void del_elem(unsigned int index) {
        if (m_length <= index) {
            throw std::invalid_argument("ERROR");
        }
        Vector <T> result(m_length);
        for (unsigned int i = 0; i < m_length; ++i) {
            if (i == index) {
                continue;
            }
            else {
                result.push_back(at(i));
            }
        }
        *this = result;
    }

     T& operator[](unsigned int position) {
         if (m_length <= position) {
             throw std::invalid_argument("ERROR");
         }
         return at(position);
     }

     void fprint(ostream& out)  {
         for (unsigned int i = 0; i < m_length; ++i) {
             out << at(i) <<endl;
         }
     }

     void fprint_doub(ostream& out) {};


    
     void fread(istream& in) {
         while (!in.eof()) {
             T symbol;
            in >> symbol;
             if (symbol == '\n' || symbol == '\r' || symbol == EOF)
                 break;
             push_back(symbol);
         }
     }


     void reverse(int begin,int end) {
         int iter = (end - begin + 1) / 2;
         for (int i= 0; i < iter; ++i) {
             swap(m_body[end - i], m_body[begin + i]);
         }
     }
     
     void shift_l(int k) {
         k = k % m_length;  //12 345
        reverse(0, k-1);               // 21|345
        reverse(k, m_length - 1); // 21|543
        reverse(0, m_length-1); // 345 12
     }

     void shift_r(int k) {
         shift_l(m_length - k);
     }

};

template<>
void Vector<double>::fprint_doub(ostream& out) {
    out << std::fixed << std::setprecision(2) << std::endl;
}

template <typename T>
void www(ifstream &fin) {
    Vector <T> a;
    int j;
    T s;
    int w;
    unsigned int k;
    std:: string f; 
    std::ofstream fout("output.txt");
    fin >> j;
    for (int i = 0; i < j; ++i) {
        fin >> f;
        try {
            switch (f[0]) {  ///можно строку or not
            case 'A':
                fin >> s;
                a.push_back(s);
                break;

            case 'R':
                if (f[1] == 'E') {
                    fin >> k;
                    a.del_elem(k);
                    break;
                }
                else {
                    fin >> w;
                    a.shift_r(w);
                    break;
                }
            case 'P':
                fin >> k;
                fout << a[k] << endl;
                break;

            case 'U':
                fin >> k;
                fin >> s;
                a[k] = s;
                break;
            case 'L':
                fin >> w;
                a.shift_l(w);
                break;
            }
        
        }
        catch (const std::invalid_argument& ia) {
            fout << "ERROR" << endl;
        }

    }
    a.fprint_doub(fout);
    a.fprint(fout);
}


int main() {
    std::ifstream fin("input.txt");
    char t;
    char I, S, D;
    fin >> t;
   

    switch (t) {
    case 'I':
        www<int>(fin);
        break;
    case 'D':
        www<double>(fin);
        break;
    case 'S':
        www<std::string>(fin);
        break;
    }
  
   return 0;
}
