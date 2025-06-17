#include <string>
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int matrix_size = 16;
const int processor_count = 4;
const int block_size = matrix_size / processor_count;

bool solve_linear_system(double A[matrix_size][matrix_size], double b[matrix_size], double x[matrix_size]) {
    // Создаем копии матрицы и вектора
    double mat[matrix_size][matrix_size];
    double rhs[matrix_size];
    
    for (int i = 0; i < matrix_size; ++i) {
        rhs[i] = b[i];
        for (int j = 0; j < matrix_size; ++j) {
            mat[i][j] = A[i][j];
        }
    }

    // Прямой ход метода Гаусса
    for (int i = 0; i < matrix_size; ++i) {
        // Поиск ведущего элемента в столбце i
        int max_row = i;
        for (int k = i + 1; k < matrix_size; ++k) {
            if (std::fabs(mat[k][i]) > std::fabs(mat[max_row][i])) {
                max_row = k;
            }
        }

        // Перестановка строк, если необходимо
        if (max_row != i) {
            for (int j = 0; j < matrix_size; ++j) {
                std::swap(mat[i][j], mat[max_row][j]);
            }
            std::swap(rhs[i], rhs[max_row]);
        }

        // Проверка на вырожденность
        if (std::fabs(mat[i][i]) < 1e-15) {
            return false;
        }

        // Нормализация текущей строки
        for (int j = i + 1; j < matrix_size; ++j) {
            mat[i][j] /= mat[i][i];
        }
        rhs[i] /= mat[i][i];
        mat[i][i] = 1.0;

        // Исключение элементов в столбце i ниже текущей строки
        for (int k = i + 1; k < matrix_size; ++k) {
            double factor = mat[k][i];
            for (int j = i + 1; j < matrix_size; ++j) {
                mat[k][j] -= factor * mat[i][j];
            }
            rhs[k] -= factor * rhs[i];
            mat[k][i] = 0.0; // Явное обнуление элемента
        }
    }

    // Обратный ход метода Гаусса
    for (int i = matrix_size - 1; i >= 0; --i) {
        x[i] = rhs[i];
        for (int j = i + 1; j < matrix_size; ++j) {
            x[i] -= mat[i][j] * x[j];
        }
    }

    return true;
}
bool solve_linear_system(double A[block_size][block_size], double b[block_size], double x[block_size]) {
    // Создаем копии матрицы и вектора
    double mat[block_size][block_size];
    double rhs[block_size];
    
    for (int i = 0; i < block_size; ++i) {
        rhs[i] = b[i];
        for (int j = 0; j < block_size; ++j) {
            mat[i][j] = A[i][j];
        }
    }

    // Прямой ход метода Гаусса
    for (int i = 0; i < block_size; ++i) {
        // Поиск ведущего элемента в столбце i
        int max_row = i;
        for (int k = i + 1; k < block_size; ++k) {
            if (std::fabs(mat[k][i]) > std::fabs(mat[max_row][i])) {
                max_row = k;
            }
        }

        // Перестановка строк, если необходимо
        if (max_row != i) {
            for (int j = 0; j < block_size; ++j) {
                std::swap(mat[i][j], mat[max_row][j]);
            }
            std::swap(rhs[i], rhs[max_row]);
        }

        // Проверка на вырожденность
        if (std::fabs(mat[i][i]) < 1e-15) {
            return false;
        }

        // Нормализация текущей строки
        for (int j = i + 1; j < block_size; ++j) {
            mat[i][j] /= mat[i][i];
        }
        rhs[i] /= mat[i][i];
        mat[i][i] = 1.0;

        // Исключение элементов в столбце i ниже текущей строки
        for (int k = i + 1; k < block_size; ++k) {
            double factor = mat[k][i];
            for (int j = i + 1; j < block_size; ++j) {
                mat[k][j] -= factor * mat[i][j];
            }
            rhs[k] -= factor * rhs[i];
            mat[k][i] = 0.0; // Явное обнуление элемента
        }
    }

    // Обратный ход метода Гаусса
    for (int i = block_size - 1; i >= 0; --i) {
        x[i] = rhs[i];
        for (int j = i + 1; j < block_size; ++j) {
            x[i] -= mat[i][j] * x[j];
        }
    }

    return true;
}
class SystemBlock
{
    public:
    
    double system[block_size][block_size + 1];
    double coefs[block_size][block_size + 1];

    int block_number;

    void fill(double matrix[matrix_size][matrix_size])
    {
        for (int i = 0; i < block_size; i++)
        {
            for (int j = 0; j < matrix_size; j++)
            {
                system[i][j] = matrix[i][j];
            }
        }
    }

    void solve()
    {
        for (int i = 0; i < block_size; i++)
        {

        }
    }

    SystemBlock()
    {
        
    }
};

class Progonka
{
    private:
        double ps[matrix_size];
        double qs[matrix_size];
        double xs[matrix_size];
        double ps1[block_size];
        double qs1[block_size];
        double xs1[block_size];
    public:
        double as[matrix_size];
        double bs[matrix_size];
        double cs[matrix_size];
        double fs[matrix_size];
        double as1[block_size];
        double bs1[block_size];
        double cs1[block_size];
        double fs1[block_size];
        double a[matrix_size];
        double b[matrix_size];
        double c[matrix_size];
        double full_matrix[matrix_size][matrix_size];
        SystemBlock blocks[processor_count];

    void print(double arr[matrix_size][matrix_size]) 
    {
        for (int i = 0; i < matrix_size; i++) 
        {
            for (int j = 0; j < matrix_size; j++) 
            {
                cout << round(arr[i][j] * 10000.0) / 10000 << "\t";
            }
            cout << endl;
        }
    }
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
            cout << "x_" + to_string(i) + " = " + to_string(xs[i]) + "   error = ";
            if ((i + 1 < matrix_size) && (i > 0))
            {
                cout << to_string(- xs[i-1] * a[i] + xs[i] * b[i] - xs[i+1] * c[i] - fs[i]) + "\n";
            }
            else if (i+1<matrix_size)
            {
                cout << to_string(- xs[i+1] * c[i] + xs[i] * b[i] - fs[i]) + "\n";
            }
            else
            {
                cout << to_string(- xs[i-1] * a[i] + xs[i] * b[i] - fs[i])+ "\n";
            }
        }
    }
   void subprogonka()
{

    for (int i = 0; i < block_size - 1; i++)
    {
        if (i == 0)
        {
            ps1[0] = cs1[0] / bs1[0];
            qs1[0] = fs1[0] / bs1[0];
        }
        else
        {
            double denominator = (bs1[i] - as1[i] * ps1[i - 1]);
            ps1[i] = cs1[i] / denominator;
            qs1[i] = (fs1[i] + as1[i] * qs1[i - 1]) / denominator;
        }
    }

    for (int i = 1; i < block_size + 1; i++)
    {
        int n = block_size - i;
        if (i == 1)
        {
            xs1[n] = (fs1[n] + as1[n] * qs1[n - 1]) / (bs1[n] - as1[n] * ps1[n - 1]);
        }
        else
        {
            xs1[n] = ps1[n] * xs1[n + 1] + qs1[n];
        }
    }

    for (int i = 0; i < block_size; i++)
    {
        cout << "x_" << i << " = " << xs1[i] << "   error = ";
        if ((i + 1 < block_size) && (i > 0))
        {
            cout << (- xs1[i - 1] * as1[i] + xs1[i] * bs1[i] - xs1[i + 1] * cs1[i] - fs1[i]) << "\n";
        }
        else if (i + 1 < block_size)
        {
            cout << (- xs1[i + 1] * cs1[i] + xs1[i] * bs1[i] - fs1[i]) << "\n";
        }
        else
        {
            cout << (- xs1[i - 1] * as1[i] + xs1[i] * bs1[i] - fs1[i]) << "\n";
        }
    }
}


    void init_full_matrix()
    {
        for (int i = 0; i < matrix_size; i++)
        {
            for (int j = 0; j < matrix_size; j++)    
            {
                full_matrix[i][j] = 0;
            }
        }
            
        for (int i = 0; i < matrix_size; i++)
        {
            if (i == 0)
            {
                full_matrix[i][i] = bs[i];
                full_matrix[i][i+1] = -cs[i];
            }
            else if (i == matrix_size - 1)
            {
                full_matrix[i][i-1] = -as[i];
                full_matrix[i][i] = bs[i];
            }
            else
            {
                full_matrix[i][i-1] = -as[i];
                full_matrix[i][i] = bs[i];
                full_matrix[i][i+1] = -cs[i];
            }
        }
    }

    Progonka()
    {

    }

    void mirror(double matrix[matrix_size][matrix_size])
    {
        double matrix1[matrix_size][matrix_size];
        for (int i = 0; i < matrix_size; i++)
        {
            for (int j = 0; j < matrix_size; j++)
            {
                matrix1[i][j] = matrix[matrix_size - i - 1][matrix_size - j - 1];
            }
        }

        for (int i = 0; i < matrix_size; i++)
        {
            for (int j = 0; j < matrix_size; j++)
            {
                matrix[i][j] = matrix1[i][j];
            }
        }
    }
    void parametric_progonka(double full[matrix_size][matrix_size])
    {
        for (int proc = 0; proc < processor_count; proc++)
        {
            for (int row = proc * matrix_size / processor_count + 1; row < (proc + 1) * matrix_size / processor_count; row++)
            {
                double coef = full[row][row-1] * full[row - 1][row - 1];
                fs[row] = fs[row] - fs[row - 1] / coef;
                for (int i = 0; i < matrix_size; i++)
                {
                    full[row][i] = full[row][i] - full[row - 1][i] / coef;
                }
            }
        }

        
        for (int proc = 0; proc < processor_count; proc++)
        {
            int start = (proc) * matrix_size / processor_count;
            int end = (proc) * matrix_size / processor_count + block_size - 2;

            for (int row = end - 1; row >= start - 1; row--)
            {
                double coef = full[row][row + 1] / full[row + 1][row + 1];
                fs[row] = fs[row] - fs[row + 1] * coef;
                for (int i = 0; i < matrix_size; i++)
                {
                    full[row][i] = full[row][i] - full[row + 1][i] * coef;
                }
            }
        }

        // for (int i = 1; i < processor_count; i++)
        // {
        //     double coef = full[i * block_size - 1][i * block_size] / full[i * block_size][i * block_size];
        //     fs[i * block_size - 1] = fs[i * block_size - 1] - fs[i * block_size - 2] / coef;
        //     for (int j = 0; j < matrix_size; j++)
        //     {
        //         full[i * block_size - 1][j] = full[i * block_size - 1][j] - full[i * block_size][j] * coef;
        //     }
            
        // }
        
        for (int i = 1; i < processor_count + 1; i++)
        {
            if (i > 1)
            {
                as1[i-1] = - full[block_size * (i - 1) - 1][i * block_size - 1];
            }
            else
            {
                as1[i-1] = 0;
            }
            bs1[i-1] = full[block_size * i - 1][i * block_size - 1];
            if (i < processor_count + 1)
            {
                cs1[i-1] = - full[block_size * (i+ 1) - 1][i * block_size - 1];
            }
            else
            {
                cs1[i-1] = 0;
            }
            fs1[i-1] = fs[i * block_size - 1];
        }
        
        subprogonka();
        print(full);
        for (int i = 0; i < matrix_size; i++)
        {
            xs[i] = 0;
            if (i % block_size == 0)
            {
                xs[i] = xs1[i / block_size];
            }
        }
        for (int i = 0; i < matrix_size; i++)
        {
            if (xs[i] == 0 && i % processor_count != 0)
            {
                double sum = 0;
                for (int j = 0; j < matrix_size; j++)
                {
                    sum += xs[j] * full[i][j];
                }
                xs[i] = (fs[i] - sum) / bs[i];
            }
        }


        for (int i = 0; i < matrix_size; i++)
        {
            cout << "  x_" + to_string(i) + " = " << xs[i];
        }
        
    }
};

int main()
{
    Progonka prog;
    for (int i = 0; i < matrix_size; i++)
    {
        if (i != 0)
        {
            prog.as[i] = 1;
            prog.a[i] = 1;
        }
        else
        {
            prog.as[i] = 0.0;
            prog.a[i] = 0.0;
        }
        if (i != matrix_size - 1)
        {
            prog.cs[i] = 1;
            prog.c[i] = 1;
        }
        else
        {
            prog.cs[i] = 0.0;
            prog.c[i] = 0.0;
        }
        prog.bs[i] = 2;
        prog.b[i] = 2;
        prog.fs[i] = 1;
    }
    prog.init_full_matrix();
    // prog.print(prog.full_matrix);
    prog.parametric_progonka(prog.full_matrix);

    Progonka prog1;
    for (int i = 0; i < matrix_size; i++)
    {
        if (i != 0)
        {
            prog1.as[i] = 1;
            prog1.a[i] = 1;
        }
        else
        {
            prog1.as[i] = 0.0;
            prog1.a[i] = 0.0;
        }
        if (i != matrix_size - 1)
        {
            prog1.cs[i] = 1;
            prog1.c[i] = 1;
        }
        else
        {
            prog1.cs[i] = 0.0;
            prog1.c[i] = 0.0;
        }
        prog1.bs[i] = 2;
        prog1.b[i] = 2;
        prog1.fs[i] = 1;
    }
    prog1.init_full_matrix();
    double sol[matrix_size];

    // prog.print(prog.full_matrix);
    // prog1.progonka();

    return 0;
}


