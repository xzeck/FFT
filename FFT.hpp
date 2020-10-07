#ifndef FFT_HPP
#define FFT_HPP

#include <bits/stdc++.h>
#include <QVector>
#include <QRegularExpression>
#include <QStringList>
#include <QMessageBox>

using ld = long double;
using ul = unsigned long;
using Complex = std::complex<ld>;

class EmptyInput {
};

class InputLnegthMisMatch{

};

class RandomInputEmpty{

};

void Calculate(Complex *A, ul N);

double findMin(QVector<double>& y_real, QVector<double>& y_imag);

double findMax(QVector<double>& y_real, QVector<double>& y_imag);

std::vector<Complex> parseInput(QString InputReal, QString InputImag);

bool checkIfIntegers();

unsigned long findLength(QString input);

void showMessage(const char* message, const char* title);
#endif // FFT_HPP
