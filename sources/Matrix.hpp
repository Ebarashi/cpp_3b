#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

namespace zich 
{
    class Matrix 
    {
    private:

        int rows, cols, size;
        vector<double> values;

    public:

        int get_rows()const
        {
            return rows;
        }
        int get_cols()const
        {
            return cols;
        }
        
        int get_size()const
        {
            return size;
        }

        double get_value_at(const int i ) const
        {
            return values.at((unsigned long)i);
        }

        Matrix(const vector<double> &values, const int row, const int col);
        ~Matrix();

        //Add
        Matrix operator+(const Matrix& mat) const; 
        Matrix& operator+=(const Matrix& mat);      
        Matrix operator+() const;                   

        // Sub
        Matrix operator-(const Matrix& mat) const;  
        Matrix& operator-=(const Matrix& mat);      
        Matrix operator-() const;         

        // Inc and dec
        Matrix& operator++();    
        Matrix operator++(const int num);  
        Matrix& operator--();    
        Matrix operator--(const int num);   


        // Mult
        Matrix operator*(const Matrix& mat) const;                  
        Matrix& operator*=(const Matrix& mat);                      
        Matrix operator*(const double scalar) const;                        
        Matrix& operator*=(const double scalar);                            
        friend Matrix operator*(const double scalar, const Matrix& mat);             

        //Compare
        bool operator>(const Matrix& mat) const;   
        bool operator>=(const Matrix& mat) const;  
        bool operator<(const Matrix& mat) const;   
        bool operator<=(const Matrix& mat) const;  
        bool operator==(const Matrix& mat) const;  
        bool operator!=(const Matrix& mat) const;  


        // Input and Output
        friend std::ostream& operator<<(std::ostream& output, const Matrix& matrix);
        friend std::istream& operator>>(std::istream& is, Matrix& matrix);
    };
}  