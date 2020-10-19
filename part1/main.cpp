#include "IntMatrix.h"
#include "Auxiliaries.h"
#include <iostream>
#include <assert.h>
using std::cout;
using std::endl;
using namespace mtm;

int main() {
    Dimensions dims1(2,3); // c'tor test
    IntMatrix C(dims1);
    C(0,0)=1;
    cout<<all(C)<<endl;
    cout<<any(C)<<endl;
    return 0;
}

/*
cout<<const_C<<endl;
    cout<<*it_begin<<endl;
    IntMatrix::const_iterator it_some = it_begin++; 
    cout<<*it_some<<endl;
    cout<<*it_begin<<endl;
    *it_begin=1; //this line doesn't compile- good sign!!
Dimensions dims(3,3); // c'tor test
 IntMatrix C_Trans = C.transpose();   
    cout<<C_Trans<<endl;    
 test //passed
   IntMatrix A(dims);
    IntMatrix D = C;
IntMatrix B(dims, 1);
    A=B;
    cout<<A<<endl;
    IntMatrix identity_3 = IntMatrix::Identity(3);
    B=identity_3;
    */