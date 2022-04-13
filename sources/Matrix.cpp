#include <iostream>
#include <vector>
#include "Matrix.hpp"

using namespace std;
namespace zich
{

    Matrix::Matrix(const vector<double> &values, const int row, const int col)
    {
        if (row <= 0 || col <= 0)
        {
            throw invalid_argument("negative values - row/col");
        }
        if (values.size() != row * col)
        {
            throw invalid_argument("the size of the matrix not matches");
        }

        this->values = values;
        this->rows = row;
        this->cols = col;
        this->size = row * col;
    }
    Matrix::~Matrix()
    {
    }

    Matrix Matrix::operator+(const Matrix &mat) const
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        vector<double> new_values;
        new_values.resize((unsigned int)(rows * cols));
        for (int i = 0; i < mat.size; i++)
        {
                new_values[(unsigned int)(i )] = this->values[(unsigned int)(i)] + mat.values[(unsigned int)(i)];
            }
        
        Matrix new_mat(new_values, this->rows, mat.cols);
        return new_mat;
    }

    Matrix &Matrix::operator+=(const Matrix &mat)
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        for (int i = 0; i < this->size; i++)
        {
                this->values[(unsigned int)(i)] += mat.values[(unsigned int)(i)];
        }
        return *this;
    }
    
    Matrix Matrix::operator+() const
    {
        vector<double> new_values;
        new_values.resize((unsigned int)(rows* cols));
        for (int i = 0; i < size; i++)
        {
                new_values[(unsigned int)(i)] = this->values[(unsigned int)(i)];
        }
        Matrix ans (new_values,this->rows,this->cols);
        return ans;
    }
   

    Matrix Matrix::operator-(const Matrix &mat) const
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        vector<double> new_values;
        new_values.resize((unsigned int)(rows* cols));
        for (int i = 0; i < size; i++)
        {
                new_values[(unsigned int)(i)] = this->values[(unsigned int)(i)] - mat.values[(unsigned int)(i)];
        }
        Matrix mat3(new_values, this->rows, this->cols);
        return mat3;
    }

     Matrix &Matrix::operator-=(const Matrix &mat)
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrixes sizes must be equal");
        }
        for (int i = 0; i < size; i++)
        {
                this->values[(unsigned int)(i)] -= mat.values[(unsigned int)(i)];
        }
        return *this;
    }

    Matrix Matrix::operator-() const {
        vector<double> new_values;
        new_values.resize((unsigned int)(rows * cols));
        for (int i = 0; i < size; i++)
        {
                new_values[(unsigned int)(i)] = this->values[(unsigned int)(i)];
        }
        Matrix ans (new_values,this->rows,this->cols);
        return ans*=(-1);
    }

    Matrix &Matrix::operator++()
    {
        for (int i = 0; i < this->size; i++)
        {
                this->values[(unsigned int)(i)] += 1;
        }
        return *this;
    }

    Matrix Matrix::operator++(const int num)
    {
        Matrix mat_copy = *this;
        for (int i = 0; i < this->size; i++)
        {
                this->values[(unsigned int)(i)] += 1;
        }
        return mat_copy;
    }
    
    

    Matrix &Matrix::operator--()
    {
        for (int i = 0; i < this->size; i++)
        {
                this->values[(unsigned int)(i)] -= 1;
        }
        return *this;
    }


    Matrix Matrix::operator--(const int num)
    {
        Matrix mat_copy = *this;
        for (int i = 0; i < this->size; i++)
        {
                this->values[(unsigned int)(i)] -= 1;
        }
        return mat_copy;
    }
    
   
    double multiplication(const Matrix &matA,const Matrix &matB, const int m, const int n)
    {
        double sum = 0;
        for (int i = 0; i < matA.get_cols(); i++)
        {
            sum += matA.get_value_at(matA.get_cols() * m + i) * matB.get_value_at(matB.get_cols() * i + n);
        }
        return sum;
    }
   
    Matrix Matrix::operator*(const Matrix &mat) const
    {
        if (this->cols != mat.rows)
        {
            throw invalid_argument("wrong size, the matrices cannot be multiply");
        }
        vector<double> new_values;
        new_values.resize((unsigned int)(this->rows * mat.cols));
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < mat.cols; j++)
            {
                new_values[(unsigned int)(i * mat.cols + j)] = multiplication(*this,mat, i, j);
            }
        }
        Matrix new_mat(new_values, this->rows, mat.cols);
        return new_mat;
    }
    
    Matrix &Matrix::operator*=(const Matrix &mat)
    {
        if (this->cols != mat.rows)
        {
            throw invalid_argument("wrong size, the matrices cannot be multiply");
        }
        vector<double> new_values;
        new_values.resize((unsigned int)(this->rows * mat.cols));
        for (int i = 0; i < this->get_rows(); i++)
        {
            for (int j = 0; j < mat.cols; j++)
            {
                new_values[(unsigned int)(i * mat.cols + j)] = multiplication(*this, mat, i, j);
            }
        }
        this->cols = mat.cols;
        this->values = new_values;
        return *this;
    }

    Matrix Matrix::operator*(const double scalar) const
    {
        vector<double> new_values;
        new_values.resize((unsigned int)(rows * cols));
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                if (this->values[(unsigned int)(i * this->cols + j)] == 0)
                {
                    continue;
                }
                new_values[(unsigned int)(i * this->cols + j)] = this->values[(unsigned int)(i * this->cols + j)] * scalar;
            }
        }
        Matrix new_mat(new_values, this->rows, this->cols);
        return new_mat;
    }

    Matrix &Matrix::operator*=(const double scalar)
    {
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                if (this->values[(unsigned int)(i * this->cols + j)] == 0)
                {
                    continue;
                }
                this->values[(unsigned int)(i * this->cols + j)] *= scalar;
            }
        }
        return *this;
    }

    Matrix operator*(const double scalar, const Matrix &mat)
    {
        vector<double> matrix;

        for (unsigned long i = 0; i < mat.size; i++)
        {

            matrix.push_back( mat.values.at(i) * scalar );

        }

        Matrix new_mat = Matrix(matrix,mat.rows , mat.cols);
        return new_mat;

    }

    double SUM(const Matrix &mat)
    {
        double sum = 0;
        for (int i = 0; i < mat.get_size(); i++)
        {
                sum += mat.get_value_at(i);
        }
        return sum;
    }


    bool Matrix::operator>(const Matrix &mat) const
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        return SUM(*this) > SUM(mat);
    }
    
    bool Matrix::operator>=(const Matrix &mat) const
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        return SUM(*this) >= SUM(mat);
    }
    
    bool Matrix::operator<(const Matrix &mat) const
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        return SUM(*this) < SUM(mat);
    }
    
    bool Matrix::operator<=(const Matrix &mat) const
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        return SUM(*this) <= SUM(mat);
    }
    
    bool Matrix::operator==(const Matrix &mat) const
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                if (this->values[(unsigned int)(i * cols + j)] != mat.values[(unsigned int)(i * cols + j)])
                {
                    return false;
                }
            }
        }
        return true;
    }
    
    bool Matrix::operator!=( const Matrix &mat) const 
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->cols; j++)
            {
                if (this->values[(unsigned int)(i * cols + j)] != mat.values[(unsigned int)(i * cols + j)])
                {
                    return true;
                }
            }
        }
        return false;
    }
    
    ostream &operator<<(ostream &output, const Matrix &mat)
    {
        for (int i = 0; i < mat.rows; i++)
        {
            output << '[';
            for ( int j = 0; j < mat.cols; j++)
            {
                output << mat.values.at((unsigned int) (i * mat.cols + j));

                if (j != mat.cols - 1)
                {
                     output << ' ';
                }
               
            }

            output << ']';

            if (i != mat.rows -1)
            {
                output << '\n';
            }
        }
        return output;
    }
   
    
    istream &operator>>(istream &input, Matrix &mat)
    {
        string input_val;
        getline(input, input_val);

        int size = input_val.size();
        int row = 1;
        int col = 1;

        vector<double> matrix;
            
        for (unsigned int i = 0; i < size; i++){

            if (input_val[i] == '[')
            {
                    
                if (i + 1 < size && isdigit(input_val.at(i + 1)) == 0){

                    throw invalid_argument("invalid input");
                }
            }

            if (input_val[i] == ']')
            {

                if ( (i + 1 < size && input_val[i + 1] != ',' )){
                        
                    throw invalid_argument("invalid input");
                }
            }
            
            if (input_val[i] == ','){
                
                row++;
                    
                if (i + 1 < size && input_val[i + 1] != ' ') {
                        
                        throw invalid_argument("invalid input");
                    }
            }

            if (isdigit(input_val[i]) != 0){

                matrix.push_back(input_val[i]);
                col++;

            }
        }


        mat.values = matrix;
        mat.rows = row;
        mat.cols = col/row;
        
        return input; 
    }


  
}
