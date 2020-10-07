#include "FFT.hpp"

// n = length(x)
// m = n/2
// X = x[2j] 0 < j < m - 1
// Y = y[2j + 1] 0 < j < m - 1

// Calculate X[n] * e ^ (-j * 2 * pi * k * 2r) / ( N / 2) -> cos( theta) - jsin( theta)
// Calculate Y[n] * e ^ (-j * 2 * pi * k * 2r) / ( N / 2)
// Calculate Y[n] * e ^ (-j * 2 * pi * k) / ( N )


// Calculating using divide and conquer rule
// func FFT(X[K], N)
//
//      for i <= N / 2
//           X_Even[i] = X[ 2 * i ]
//           X_Odd[i] = X[ 2 * i + 1 ]
//
//      FFT(X_Even, N / 2)
//      FFT(X_Odd, N / 2)
//
//      for k <= N / 2
//          t = exp(0, exp(-2 * pi * k / n) * odd [k]
//          A[N / 2 + k] = event[k] - t;
//


// Function takes in a Complex ( std::complex<long double>) and length N
// returns nothing if the length is less than or equal to 1
// Generates two arrays of N / 2 length which stores odd and even numbers
// Seperate input based on if their index is odd or even
// Recursively divide the array
// Caclculate FFT for two values
void Calculate(Complex *A, ul N)
{
    if(N <= 1)
        return;

    Complex odd[N/2];
    Complex even[N/2];

    for(ul i =0; i < N / 2; i++)
    {
        even[i] = A[i * 2];
        odd[i] = A[i * 2 + 1];
    }

    Calculate(even, N / 2);
    Calculate(odd, N / 2);

    for(ul k = 0; k < N / 2; k++)
    {
        Complex t = exp(Complex(0, -2 * M_PI * k /  N)) * odd[k];
        A[k] = even[k] + t;
        A[N / 2 + k] = even[k] - t;
    }
}

// Finds the minimum element between two vectors
// To get the lower bound of the graph
double findMin(QVector<double>& y_real, QVector<double>& y_imag)
{
    return std::min(*std::min_element(y_real.begin(), y_real.end()),
                    *std::min_element(y_imag.begin(), y_imag.end()));
}

// Finds the maximum element between two vectors
// To get the upper bound of the graph
double findMax(QVector<double>& y_real, QVector<double>& y_imag)
{
    return std::max(*std::max_element(y_real.begin(), y_real.end()),
                    *std::max_element(y_imag.begin(), y_imag.end()));
}

// Takes a QString and splits it by whitespace and returns its size
ul findLength(QString input)
{
    return input.split(QRegularExpression("\\s+")).size();
}

// Takes a QString and removes whitespace and returns the data
QStringList getInputNumbers(QString input)
{
    return input.split(QRegularExpression("\\s+"));
}


std::vector<Complex> parseInput(QString InputReal, QString InputImag)
{
    std::vector<Complex> C;
    QMessageBox msgBox;
    try
    {

        QStringList InputListReal = getInputNumbers(InputReal);
        QStringList InputListImag = getInputNumbers(InputImag);


        if (InputListReal.size() != InputListImag.size())
            throw InputLnegthMisMatch();

        if(InputListReal.size() < 1 || InputListImag.size() < 1)
            throw EmptyInput();

        ul inputSize = InputListImag.size();


        for(ul i = 0; i < inputSize; i++)
        {
            C.push_back(Complex(InputListReal[i].toDouble(), InputListImag[i].toDouble()));
        }
    }
    catch(InputLnegthMisMatch e)
    {
        showMessage("Real and Iamginary input do not have the same length", "Invalid input");
    }
    catch (EmptyInput e)
    {
        showMessage("Empty Input given", "Invalid input");
    }

    return C;
}

void showMessage(const char* message, const char* title)
{
    QMessageBox MsgBox;
    MsgBox.setWindowTitle(title);
    MsgBox.setText(message);
    MsgBox.button(MsgBox.Ok);
    MsgBox.exec();
}



