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
    
    Matrix::~Matrix() {}

    //new_mat = this + mat
    Matrix Matrix::operator+(const Matrix &mat) const
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        
        vector<double> new_values;
        new_values.resize((unsigned int)(size));
        for (unsigned int i = 0; i < size; i++)
        {
                new_values.at(i) = this->values.at(i) + mat.values.at(i);
            }
        
        Matrix new_mat(new_values, mat.rows, mat.cols);
        return new_mat;
    }

    //this = this + mat
    Matrix &Matrix::operator+=(const Matrix &mat)
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        for (unsigned int i = 0; i < size; i++)
        {
                this->values.at(i) += mat.values.at(i);
        }
        return *this;
    }
    
    //new_mat = +this  (unary)
    Matrix Matrix::operator+() const
    {
        vector<double> new_values;
        new_values.resize((unsigned int)(size));
        for (unsigned int i = 0; i < size; i++)
        {
                new_values.at(i) = this->values.at(i);
        }
        Matrix new_mat (new_values,rows,cols);
        return new_mat;
    }
   
    //new_mat = this - mat
    Matrix Matrix::operator-(const Matrix &mat) const
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        
        vector<double> new_values;
        new_values.resize((unsigned int)(size));
        for (unsigned int i = 0; i < size; i++)
        {
                new_values.at(i) = this->values.at(i) - mat.values.at(i);
        }
        Matrix new_mat(new_values, this->rows, this->cols);
        return new_mat;
    }

    //this = this - mat 
    Matrix &Matrix::operator-=(const Matrix &mat)
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        for (unsigned int i = 0; i < size; i++)
        {
                this->values.at(i) -= mat.values.at(i);
        }
        return *this;
    }

    //new_mat = -this
    Matrix Matrix::operator-() const {
        vector<double> new_values;
        new_values.resize((unsigned int)(size));
        for (unsigned int i = 0; i < size; i++)
        {
                new_values.at(i) = this->values.at(i);
        }
        Matrix new_mat(new_values,this->rows,this->cols);
        return new_mat *=(-1);
    }

    //this++
    Matrix &Matrix::operator++()
    {
        (*this)++;
        return *this;
    }

    //mat_copy = this++
    Matrix Matrix::operator++(const int num)
    {
        Matrix mat_copy = *this;
        for (unsigned int i = 0; i < this->size; i++)
        {
                this->values.at(i) ++;
        }
        return mat_copy;
    }
    
    
    //this--
    Matrix &Matrix::operator--()
    {
        (*this)--;
        return *this;
    }

    //mat_copy = this--
    Matrix Matrix::operator--(const int num)
    {
        Matrix mat_copy = *this;
        for (unsigned int i = 0; i < this->size; i++)
        {
                this->values.at(i) --;
        }
        return mat_copy;
    }
    
   // sum of (row i(n) with col j(m))
    double multiplication(const Matrix &matA,const Matrix &matB, const int n, const int m)
    {
        double sum = 0;
        for (int i = 0; i < matA.get_cols(); i++)
        {
            sum += matA.get_value_at(matA.get_cols() * n + i) * matB.get_value_at(matB.get_cols() * i + m);
        }
        return sum;
    }

    //new_mat = this * mat
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
    
    //this = this * mat
    Matrix &Matrix::operator*=(const Matrix &mat)
    {
        if (this->cols != mat.rows)
        {
            throw invalid_argument("wrong size, the matrices cannot be multiply");
        }
        *this = (*this) * mat;
        return *this;
    }

    //new_mat = this * scalar
    Matrix Matrix::operator*(const double scalar) const
    {
        vector<double> new_values;
        new_values.resize((unsigned int)(size));
        
        for (unsigned int i = 0; i < this->size; i++)
        {
                new_values.at(i) =  this->values.at(i) * scalar ;
        }
        Matrix new_mat(new_values, this->rows, this->cols);
        return new_mat;
    }

    //this = this * scalar
    Matrix &Matrix::operator*=(const double scalar)
    {
        *this  = (*this) * scalar;
        return *this;
    }

    //new_mat = mat * scalar
    Matrix operator*(const double scalar, const Matrix &mat)
    {
        return mat * scalar;

    }

    //this > mat
    bool Matrix::operator>(const Matrix &mat) const
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        return (!(*this < mat)) && ((*this) != mat);
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

    //this >= mat
    bool Matrix::operator>=(const Matrix &mat) const
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        return SUM(*this) >= SUM(mat);
    }
    
    //this < mat
    bool Matrix::operator<(const Matrix &mat) const
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        return !(*this >= mat);
    }
    
    //this <= mat
    bool Matrix::operator<=(const Matrix &mat) const
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        return !(*this > mat);
    }
    
    //this == mat
    bool Matrix::operator==(const Matrix &mat) const
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
        for (unsigned int i = 0; i < size; i++)
        {
            if (this->values.at(i) != mat.values.at(i))
                {
                    return false;
                }
        }
        return true;
    }
    
    //this != mat
    bool Matrix::operator!=( const Matrix &mat) const 
    {
        if (this->rows != mat.rows || this->cols != mat.cols)
        {
            throw invalid_argument("the matrices sizes must be equal");
        }
      return !(*this == mat);
    }
    
    //output
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
   
    //input 
    istream &operator>>(istream &is, Matrix &mat)
    {
        string input;
        getline(is, input);

        int row = 0;
        int col = 1;
        bool first = true;
        bool begin = false;
        
        for (unsigned int i = 0; i < input.size(); i++){
                      
            char curr_data = input.at(i);
            

            if (input[i] == ',')
            {
                
                if (i + 1 < input.size() && input[i + 1] != ' ') {
                    
                    throw invalid_argument("bad input");
                }
            }
            
            if (curr_data == '[')
            {
                if (i + 1 < input.size() && isdigit(input.at(i + 1)) == 0)
                {

                    throw invalid_argument("invalid input");
                }
                
                row++;
                begin = true;
            }
            if (curr_data == ']')
            {
                if ( (i + 1 < input.size() && input[i + 1] != ','))
                {
                        
                    throw invalid_argument("invalid input");
                }
                first = false;
                begin = false;

            }
            if(begin && first && curr_data == ' '){
                col++;
                    
            }
        }


        mat.values.resize((unsigned long)(row)*(unsigned long)col);
        mat.size = row*col;
        mat.cols = col;
        mat.rows = row;

        if (row <= 0 || col <= 0)
        {
            throw invalid_argument("negative values - row/col");
        }
        if (mat.values.size() != row * col)
        {
            throw invalid_argument("the size of the matrix not matches");
        }

        //string to vector
        int count = 0;
        std::string curr_data_str;
        for (int i = 0; i < input.size(); i++){

            char curr_data = input.at((unsigned long)i);

            if (isdigit(curr_data)!=0){
                curr_data_str += curr_data;
            }
            else if(!(curr_data_str.empty())){

                double curr_val = std::stod(curr_data_str);
                mat.values[(unsigned long)count++] = curr_val;
                curr_data_str = "";
            } 
        }
        return is;
    }

}
  

