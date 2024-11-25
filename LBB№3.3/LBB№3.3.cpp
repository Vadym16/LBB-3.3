#include <iostream>

using namespace std;

class Vector {
public:

    Vector(int n = 5) : size(n), pel(new double[n]) {
        for (int i = 0; i < size; i++) {
            pel[i] = 0;
        }
    }

    Vector(const Vector& a) : size(a.size), pel(new double[a.size]) {
        for (int i = 0; i < size; i++) {
            pel[i] = a.pel[i];
        }
    }

    ~Vector() {
        delete[] pel;
    }

    double& operator[](int inx) {
        return pel[inx];
    }

    const double& operator[](int inx) const {
        return pel[inx];
    }

    int getS() const {
        return size;
    }

private:
    double* pel;
    int size;
};

class Matrix {
public:

    Matrix(int n = 5) : row_count(n), status(0), row(new Vector[n]) {
        ob_count++;
    }

    Matrix(int n, int m, int value) : row_count(m), status(0), row(new Vector[m]) {
        for (int i = 0; i < row_count; i++) {
            for (int j = 0; j < n; j++) {
                row[i][j] = value;
            }
        }
        ob_count++;
    }

    Matrix(const Matrix& a) : row_count(a.row_count), status(0), row(new Vector[a.row_count]) {
        for (int i = 0; i < row_count; i++) {
            row[i] = a.row[i];
        }
        ob_count++;
    }

    ~Matrix() {
        delete[] row;
        ob_count--;
    }



    void pel_set(int i, int j, double value) {
        if (i >= row_count or i >= row[0].getS()) {
            status = 1;
            return;
        }
        row[i][j] = value;
    }

    double pel_get(int i, int j) {
        if (i >= row_count or i >= row[0].getS()) {
            status = 1;
            return 0;
        }
        return row[i][j];
    }

    void view() {
        for (int i = 0; i < row_count; i++) {
            for (int j = 0; j < row[0].getS(); j++) {
                cout << row[i][j] << " ";
            }
            cout << endl;
         }
    }

    //Оператори дорівнює, +, -, *, /;

    Matrix& operator=(const Matrix& a) {
        if (this == &a) return *this;

        delete[] row;
        row_count = a.row_count;
        status = a.status;
        row = new Vector[row_count];
        for (int i = 0; i < row_count; i++) {
            row[i] = a.row[i];
        }
        return *this;
    }

    Matrix operator+(const Matrix& a) const {
        Matrix res(row_count, row[0].getS(), 0);
        if (row_count != a.row_count or row[0].getS() != a.row[0].getS()) {
            res.status = 1;
            return res;
        }
        else {
            for (int i=0; i < row_count; i++) {
                for (int j = 0; j < row[0].getS(); j++) {
                    res.row[i][j] = row[i][j] + a.row[i][j];
                }
            }
            return res;
        }
    }

    Matrix operator-(const Matrix& a) const {
        Matrix res(row_count, row[0].getS(), 0);
        if (row_count != a.row_count or row[0].getS() != a.row[0].getS()) {
            res.status = 1;
            return res;
        }
        else {
            for (int i = 0; i < row_count; i++) {
                for (int j = 0; j < row[0].getS(); j++) {
                    res.row[i][j] = row[i][j] - a.row[i][j];
                }
            }
            return res;
        }
    }

    Matrix operator*(const Matrix& a) const {
        Matrix res(row_count, row[0].getS(), 0);
        if (row_count != a.row_count or row[0].getS() != a.row[0].getS()) {
            res.status = 1;
            return res;
        }
        else {
            for (int i = 0; i < row_count; i++) {
                for (int j = 0; j < row[0].getS(); j++) {
                    for (int k = 0; k < row[0].getS(); k++) {
                        res.row[i][j] += row[i][k] * a.row[k][j];
                    }
                }
            }
        }
    }

    Matrix operator/(int a) const {
        Matrix res(row_count, row[0].getS(), 0);
        if (a == 0) {
            res.status = 1;
            return res;
        }
        else {
            for (int i = 0; i < row_count; i++) {
                for (int j = 0; j < row[0].getS(); j++) {
                    res.row[i][j] = row[i][j] / a;
                }
            }
            return res;
        }
    }

    //Оператори більше, менше, рівне, не рівне;

    bool operator==(const Matrix& a) const {
        if (row_count != a.row_count or row[0].getS() != a.row[0].getS()) {
            return false;
        }
        for (int i = 0; i < row_count; i++) {
            for (int j = 0; j < row[0].getS(); j++) {
                if (row[i][j] != a.row[i][j]) return false;
            }
        }
        return true;       
    }

    bool operator!=(const Matrix& a) const {
        return!(*this == a);
    }

    bool operator<(const Matrix& a) const {
        return sum_() < a.sum_();
    }

    bool operator>(const Matrix& a) const {
        return sum_() > a.sum_();
    }



private:
    Vector* row;
    int row_count;
    int status = 0;
    int ob_count = 0;

    double sum_() const {
        double sum = 0;
        for (int i = 0; i < row_count; i++) {
            for (int j = 0; j < row[i].getS(); j++) {
                sum += row[i][j];
            }
        }
        return sum;
    };
};

int main()
{
    setlocale(LC_ALL, "ukr");

    Matrix v1(5, 5, 5);
    Matrix v2(5, 5, 2);
    cout << "Матриця 1:" << endl;
    v1.view();
    cout << "Матриця 2:" << endl;
    v2.view();

    cout << "\nСума: "<<endl;
    Matrix sum = v1 + v2;
    sum.view();

    cout << "\nРізниця : "<<endl;
    Matrix min_ = v1 - v2;
    min_.view();

    cout << "\nДобуток: "<<endl;
    Matrix dob = v1 * v2;
    dob.view();

    cout << "\nДільник при діленні на 3: "<<endl;
    Matrix del = v1 / 3;
    del.view();

    cout << "Чи правдива вірність що v1 = v2: ";
    if (v1 == v2) cout << "Так" << endl;
    else cout << "НІ" << endl;
    cout << "Чи правдива вірність що v1 != v2: ";
    if (v1 != v2) cout << "Так" << endl;
    else cout << "НІ" << endl;
    cout << "Чи правдива вірність що v1 > v2: ";
    if (v1 > v2) cout << "Так" << endl;
    else cout << "НІ" << endl;
    cout << "Чи правдива вірність що v1 < v2: ";
    if (v1 < v2) cout << "Так" << endl;
    else cout << "НІ" << endl;

}

