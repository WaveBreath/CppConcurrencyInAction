//
// Created by happyend on 2026/9/19.
//

#ifndef CPPCONCURRENCYINACTION_MYSTACKMUTEX_H
#define CPPCONCURRENCYINACTION_MYSTACKMUTEX_H
#include<bits/stdc++.h>
#include "MyThreadRAII.h"
#include "MyInt.h"
using namespace std;
template<class T>
class MyStackMutex {
    stack<T> st;
public:
    mutex m;
    MyStackMutex() {}
    void push(T &&x) {
        lock_guard<mutex> lk(m);
        st.push(forward<T>(x));
    }
    void push(const T &x) {
        lock_guard<mutex> lk(m);
        st.push(x);
    }
    shared_ptr<T> pop(){
        lock_guard<mutex> lk(m);
        if (st.empty()) {
            return nullptr;
        }
        shared_ptr<T> ret = make_shared<T>(move(st.top()));
        st.pop();
        return ret;
    }
    int pop(T& t) {
        lock_guard<mutex> lk(m);
        if (st.empty()) {
            return 0;
        }
        t = move(st.top());
        st.pop();
        return 0;
    }
    bool empty() {
        lock_guard<mutex> lk(m);
        return st.empty();
    }

};
void addRemoveStack1(MyStackMutex<MyInt> &stk) {
    for (int i =0; i < 10 ;i++) {
        stk.push(MyInt(i*2));
        cout<<"XXX\n";
        sleep(2);
        stk.pop()->show();
    }
}
void addRemoveStack2(MyStackMutex<MyInt> &stk) {
    MyInt res(0);
    for (int i =0; i < 10 ;i++) {
        stk.push(i*2+1);
        sleep(2);
        stk.pop(res);
        res.show();
    }
}

void testMyStackMutex() {
    MyStackMutex<MyInt> st;
    MyThreadRAII t(
        thread(addRemoveStack1, ref(st))
    );
    MyThreadRAII t2(
        thread(addRemoveStack2, ref(st))
    );
}
void avoidDeadLock() {
    MyStackMutex<int> a,b;
    for (int i=0;i<10;i++) {
        a.push(i);
        b.push(10+i);
    }
    lock(a.m,b.m);
    lock_guard<mutex> lk(a.m,adopt_lock);
    lock_guard<mutex> lk2(b.m,adopt_lock);

}
#endif //CPPCONCURRENCYINACTION_MYSTACKMUTEX_H
