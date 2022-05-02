#include "doctest.h"
#include "Matrix.hpp"
#include <sstream>

using namespace std;
using namespace zich;


TEST_CASE("init tests")
{
    vector<double> v = {1,2,1,2};
    CHECK_NOTHROW(Matrix a(v,2,2));
   
    vector<double> v1;
        for (double i = 0; i < 9; i++)
        {
            v1.push_back(i);
        }

    CHECK_NOTHROW(Matrix a(v1, 3, 3));
    
    CHECK_THROWS(Matrix b(v1, -4, 3));
    CHECK_THROWS(Matrix c(v1,3,0)); 
}


TEST_CASE("Add and Sub tests")
{
    vector<double> a1 = {1,2,1,2,1,2,1,2};
    Matrix mat1(a1,2,4);
    
    vector<double> a2 = {1,3,4,5,6,7,8,9};
    Matrix mat2(a2,2,4);
    
    vector<double> a3 = {2,5,5,7,7,9,9,11};
    Matrix mat3(a3,2,4);
    
    Matrix sum12 = mat1+mat2;
    CHECK(mat3==sum12);

    //sub and add +1 -1 to the matrix values
    for(size_t i=0; i < a3.size(); i++){
        a3[i]++;
    }
    
    sum12++;
    CHECK(Matrix(a3,2,4)==sum12);
    
    sum12--;
    CHECK(mat3==sum12);
    
    ++sum12;
    CHECK(Matrix(a3,2,4)==sum12);
    
    --sum12;
    CHECK(mat3==sum12);
    
    //sub and add with matrix
    vector<double> one = {1,1,1,1,1,1,1,1};
    Matrix M1(one,2,4);
    sum12+=M1;
    CHECK(Matrix(a3,2,4)==sum12);
    sum12-=M1;
    CHECK(mat3==sum12);
    
    sum12+=M1;
    Matrix A = sum12-M1;
    CHECK(A==mat3);

    CHECK(A == +A);
    CHECK(M1 == -(-M1));

    //check throw Add & Sub - not in the same size
    vector<double> v = {1,2,1,2,1,2,1,2,1,2};
    Matrix b(v,5,2);
    vector<double> v1 = {2,1,2,1};
    Matrix c(v1,2,2);
    CHECK_THROWS(c + b);
    CHECK_THROWS(b -c);
    CHECK_THROWS(c+=b);
    CHECK_THROWS(b-=c);

}

TEST_CASE("Mult tests")
{
    vector<double> a1 = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    Matrix I(a1,4,4);
    
    vector<double> a2 = {1,2,2,1,1,2,2,1};
    Matrix mat1(a2,2,4);
    Matrix mat2(a2,4,2);
   
    CHECK(mat1==mat1*I);
    CHECK(mat2==I*mat2);
    
    vector<double> a3 = {11,3,7,11};
    Matrix A(a3,2,2);
    vector<double> a4 = {8,0,1,0,3,5};
    Matrix B(a4,2,3);
    vector<double> a5 = {88,9,26,56,33,62};
    Matrix C(a5,2,3);
    CHECK(A*B==C);
   
    
    const double two = 2;
    const double half =(1.0/2.0);
    Matrix I2 = I*two;
    CHECK(I==I2*half);
    CHECK(I2*half==I);
    

    //check throw Mult 
    vector<double> a6 = {1,1,1,1,1,1,1,1};
    Matrix mat3(a6,2,4);
    Matrix mat4(a6,1,8);
    CHECK_THROWS(mat3*mat4);
    CHECK_THROWS(mat4*mat3);
}


TEST_CASE("Compare tests")
{
    vector<double> v = {1,2,2,1,2,2,1,2,2};
    Matrix mat1(v,3,3);
    CHECK(mat1==mat1);
    Matrix mat2 = +mat1;
    mat1--;
    CHECK_FALSE(mat1>mat2);
    CHECK(mat2>mat1);
    CHECK_FALSE(mat1!=mat1);
    CHECK(mat1<mat2);
    CHECK_FALSE(mat1>=mat2);
   


    //check throw Compare
    vector<double> v1 = {2,2,3,2,2,3,2,2,3};
    Matrix a(v1,3,3);
    vector<double> v2 = {1,1,1,1};
    Matrix b(v2,2,2);

    bool c;
    CHECK_THROWS(c = a>=b);
    CHECK_THROWS(c = a>b);
    CHECK_THROWS(c = a!=b);  
    CHECK_THROWS(c  = a==b);
    CHECK_THROWS(c = a<b);
    CHECK_THROWS(c = a<=b);
}


TEST_CASE("Input and Output tests")
{
    Matrix m1{{2,1,2,2} , 1, 4};
    stringstream ss;
    ss << "[3 3], [2 2]";
    CHECK_NOTHROW(ss >> m1);

    stringstream s1{"[1 1 1 1],[1 1 1 1], [1 1 1 1]\n"};
    CHECK_THROWS(s1 >> m1);
    
    stringstream input("[1 1], [1 1], [1 1], [1 1]");
    input>>m1;
    vector<double> a = {1,1,1,1,1,1,1,1};
    Matrix A(a,4,2);
    CHECK(A==m1);
    stringstream output;
    output << m1;
    CHECK(output.str()=="[1 1]\n"
                        "[1 1]\n"
                        "[1 1]\n"
                        "[1 1]\n"); 

}


