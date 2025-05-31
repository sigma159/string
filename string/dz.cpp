#include <iostream>
using namespace std;

template <typename T>
class Matrix {
private:
    T** data;
    int rows, cols;

    void allocateMemory() {
        data = new T * [rows];
        for (int i = 0; i < rows; ++i)
            data[i] = new T[cols];
    }

    void freeMemory() {
        for (int i = 0; i < rows; ++i)
            delete[] data[i];
        delete[] data;
    }

public:
    Matrix(int r = 2, int c = 2) : rows(r), cols(c) {
        allocateMemory();
    }

    ~Matrix() {
        freeMemory();
    }

    void input() {
        cout << "Введіть елементи матриці (" << rows << "x" << cols << "):\n";
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j) {
                cout << "[" << i << "][" << j << "] = ";
                cin >> data[i][j];
            }
    }

    void fillSimpleRandom() {
        int counter = 1;
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] = (T)(counter++ % 10);
    }

    void print() const {
        cout << "Матриця:\n";
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j)
                cout << data[i][j] << " ";
            cout << '\n';
        }
    }

    T maxElement() const {
        T maxVal = data[0][0];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (data[i][j] > maxVal)
                    maxVal = data[i][j];
        return maxVal;
    }

    T minElement() const {
        T minVal = data[0][0];
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                if (data[i][j] < minVal)
                    minVal = data[i][j];
        return minVal;
    }

    Matrix operator+(const Matrix& other) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] + other.data[i][j];
        return result;
    }

    Matrix operator-(const Matrix& other) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] - other.data[i][j];
        return result;
    }

    Matrix operator*(const Matrix& other) {
        Matrix result(rows, other.cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < other.cols; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < cols; ++k)
                    result.data[i][j] += data[i][k] * other.data[k][j];
            }
        return result;
    }

    Matrix operator/(T scalar) {
        Matrix result(rows, cols);
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                result.data[i][j] = data[i][j] / scalar;
        return result;
    }
};

int main() {
    Matrix<int> A(2, 2), B(2, 2);
    A.fillSimpleRandom();
    B.fillSimpleRandom();

    cout << "Матриця A:\n"; A.print();
    cout << "Матриця B:\n"; B.print();

    Matrix<int> C = A + B;
    cout << "A + B:\n"; C.print();

    Matrix<int> D = A * B;
    cout << "A * B:\n"; D.print();

    cout << "Максимум у A: " << A.maxElement() << endl;
    cout << "Мінімум у A: " << A.minElement() << endl;

    return 0;
}
