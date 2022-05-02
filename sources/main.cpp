#include "Matrix.hpp"
#include <sstream>



using namespace std;
using namespace zich;


void actions(int flag, Matrix &mat, Matrix &mat2){

    bool temp;
    double scalar;

    switch (flag){
    case 0:
        exit(0);
    
    case 1:
        temp = (mat == mat2);
        if (temp){
            cout << "True\n";
        }
        else{
            cout << "False\n";
        }
        break;
    
    case 2:
        temp = (mat >= mat2);
        if (temp){
            cout << "True\n";
        }
        else{
            cout << "False\n";
        }
        break;
    
    case 3:
        cout << (mat * mat2) << "\n";
        break;
    
    case 4:
        cout << (mat*= mat2) <<'\n';
        break;
    
    case 5:
        cout << (mat-=mat2) << '\n';
        break;
    
    case 6:
       cout<< "Choose scalar\n";
        cin >> scalar;
        cout << (mat*= scalar) << '\n';
        break;
    
    case 7:
        cout<< "Choose scalar\n";
        cin >> scalar;
        cout << (scalar*mat) << '\n';
        break;
    
    case 8:
        cout << (-mat) << '\n';
        break;
    
    case 9:
        cout << mat++ << '\n';
        break;
    
    case 10:
        cout << ++mat << '\n';
        break;
    
    case 11:
        cout << mat-- << '\n';
        break; 
    
    case 12:
        cout << --mat << '\n';
        break;         
    
    default:
        cout << "Chose a num between 0 - 12\n";
        break;
    }
}


int main(){
    string data;
    
    Matrix a{{1,2,2,1},2,2};
    Matrix b{{1,0,0,0,1,0,0,0,1},3,3};

    cout << "Enter data for a 3x3 matrix in this format -> [? ? ?], [? ? ?], [? ? ?]\n";
    bool entry = false;

    do{
        getline(cin, data);
        data += '\n';
        stringstream is;
        is << data;
        try{
            is >> a;
            entry = false;
        }
        catch(const std::exception& e){
                entry = true;
                cout<< "---" << e.what() << "\n";
                cout << "Enter data for a 3x3 matrix in this format -> [? ? ?], [? ? ?], [? ? ?]\n" << endl;
        }

    }while(entry);
    while (1)
    { 
        cout << "****************************"
        cout << "Enter an action num:\n"
            << "0: exit\n"
            << "1: == \n"
            << "2: >= \n"
            << "3: mat*mat2\n"
            << "4: mat*=mat2\n"
            << "5: mat-=mat2\n"
            << "6: mat*=scalar\n"
            << "7: scalar*mat\n"
            << "8: -mat\n"
            << "9: mat++\n"
            << "10: ++mat\n"
            << "11: mat--\n" 
            << "12: --mat\n";
        
        int flag;
        
            cin >> flag;
            fflush(stdin);
            try{
                actions(flag,a,b);
            }
            catch(const std::exception& e){
                cout<< "Function " << flag <<  "---" << e.what();
                fflush(stdout);
            }
    }

    return 0;
}
