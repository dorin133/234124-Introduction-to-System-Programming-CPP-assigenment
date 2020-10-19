#include "Matrix.h"
//#include "Auxiliaries.h"
#include <iostream>
#include <assert.h>
#include <string>
using std::cout;
using std::endl;
using namespace mtm;

int main()
{
    Dimensions dims_1(0,0);
    Matrix<char> mat_1(dims_1);
    //mat_1(0,1) = "b";
    //Matrix<string> mat_2(dims_1, "c");
    //cout<<mat_2<<endl;
    //mat_2=mat_1;
    cout<<endl;
    //cout<<mat_1(0,0)<<endl;
    //cout<<mat_2<<endl;
    return 0;
}

//Matrix<int>::const_iterator it_begin = diag_1.begin(); // it_begin is a new iterator pointing to first element
    //(mat_3[0][0], which is equal to 1)
    //Matrix<int>::iterator it_end = mat_3.end(); // it_end points to one past last element
    // 2. dereference (operator*) returns the element pointed to by the iterator
    //cout << *(++it_begin) << endl; // prints out 2

    // 2a. dereference supports element assigment
    //it_begin;
    //cout << *it_begin << endl; // prints out 0.
    //Matrix<int>::const_iterator it  = diag_1.end();
    /*for (Matrix<int>::const_iterator it = diag_1.begin(); it != diag_1.end(); ++it)
    {
        cout << *it << endl;
        //prints 2 0 0 2
    }*/