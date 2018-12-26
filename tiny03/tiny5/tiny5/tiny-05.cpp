#include "tiny-05.hpp"

namespace pjc {
    

    complex::complex(double real, double imaginary) :
        m_real(real),
        m_imag(imaginary) {}

    double complex::real() const {
        return m_real;
    }

    void complex::real(double d) {
        m_real = d;
    }

    double complex::imag() const {
        return m_imag;
    }

    void complex::imag(double d) {
        m_imag = d;
    }

    complex complex::operator+(const complex& toAdd) const{
        return complex(m_real + toAdd.m_real, m_imag + toAdd.m_imag);
    }
    template <class Number>
    complex complex::operator+(const Number& toAdd) const{
        return complex(m_real + toAdd,m_imag);
    }
    
    template <class Number>
    complex operator+(Number num, const complex& toAdd){
        return complex(toAdd.m_real + num, toAdd.m_imag);
    }
    complex& complex::operator-(const complex& toAdd){
        return *this;
    }
    complex& complex::operator*(const complex& toAdd){
        return *this;
    }
}
