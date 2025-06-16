#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>

using namespace std;

const int matrix_size = 7;

class Progonka
{
    private:
        double ps[matrix_size];
        double qs[matrix_size];
        double xs[matrix_size];
    public:
        double as[matrix_size];
        double bs[matrix_size];
        double cs[matrix_size];
        double fs[matrix_size];
        double a[matrix_size];
        double b[matrix_size];
        double c[matrix_size];
    

    void progonka()
    {
        for (int i = 0; i < matrix_size - 1; i++)
        {
            if (i == 0)
            {
                ps[0] = cs[0] / bs[0];
                qs[0] = fs[0] / bs[0];
            }
            else
            {
                double denominator = (bs[i] - as[i] * ps[i-1]);
                ps[i] = cs[i] / denominator;
                qs[i] = (fs[i] + as[i] * qs[i-1]) / denominator;
            }
            cout << (to_string(qs[i]) + "   " + to_string(ps[i]) + "\n");
        }
        for (int i = 1; i < matrix_size + 1; i++)
        {
            int n = matrix_size - i;
            if (i == 1)
            {
                xs[n] = (fs[n] + as[n] * qs[n - 1]) / (bs[n] - as[n] * ps[n - 1]);
            }
            else
            {
                xs[n] = ps[n] * xs[n+1] + qs[n];
            }
        }
        for (int i = 0; i < matrix_size; i++)
        {
            cout << "!!!" + to_string(xs[i]) + "!!!   ";
            if ((i + 1 < matrix_size) && (i - 1 >= 0))
            {
                
                cout << to_string(xs[i-1] * a[i] + xs[i] * b[i] + xs[i+1] * c[i] - fs[i]) + "\n";
            }
            else if (i+1<matrix_size)
            {
                cout << to_string(xs[i+1] * c[i] + xs[i] * b[i] - fs[i]) + "\n";
            }
            else
            {
                cout << to_string(xs[i-1] * a[i] + xs[i] * b[i] - fs[i])+ "\n";
            }
        }
    }
};