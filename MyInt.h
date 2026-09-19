//
// Created by happyend on 2026/9/19.
//

#ifndef CPPCONCURRENCYINACTION_MYINT_H
#define CPPCONCURRENCYINACTION_MYINT_H
#include<bits/stdc++.h>
using namespace std;
class MyInt {
public:
    int it;
    MyInt(const int &a):it(a) {cout<<"Construction 1"<<endl;}
    MyInt(const MyInt &a):it(a.it) {cout<<"Copy Construction"<<endl;}
    MyInt(const MyInt&& a):it(a.it) {cout<<"Move Construction"<<endl;}
    MyInt& operator=(const MyInt& a) {cout<<"Operator = LValue"<<endl;it  = a.it; return *this;}
    MyInt& operator=(MyInt&& a) {cout<<"Operator = RValue"<<endl;it=a.it; return *this;}
    void show(){cout<<it<<endl;}
};


#endif //CPPCONCURRENCYINACTION_MYINT_H
