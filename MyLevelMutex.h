//
// Created by happyend on 2026/9/19.
//

#ifndef CPPCONCURRENCYINACTION_MYLEVELMUTEX_H
#define CPPCONCURRENCYINACTION_MYLEVELMUTEX_H
#include<bits/stdc++.h>

#include "MyThreadRAII.h"

class MyLevelMutex {
    static thread_local unsigned long threadLevel;
    mutex m;
    const  unsigned long level;
    unsigned long prvLevel;
public:
    MyLevelMutex( unsigned long x):level(x), prvLevel(0) {}
    void checkValid() {
        if ( level <= threadLevel) {
            throw std::logic_error("Lower than previous level");
        }
    }
    void lock() {
        checkValid();

        m.lock();
        // change order?
        // not change
        // 2 thread can modify prvLevel simultaneously
        // unlock can change thread local variable
        prvLevel = threadLevel;
        threadLevel = level;

    }
    void unlock() {
        m.unlock();
        threadLevel = prvLevel;
    }
    bool tryLock() {
        checkValid();
        if (!m.try_lock()) {
            return false;
        }
        prvLevel = threadLevel;
        threadLevel = level;
        return true;
    }
};

thread_local unsigned long MyLevelMutex::threadLevel = 0;
void newLock(MyLevelMutex &b) {
    // prv = 10, now = 0
    b.lock();// prv = 10, now=100
    cout<<"subthread lock b"<<endl;
    b.unlock(); // now = 10
    cout<<"subthread unlock b"<<endl;
    MyLevelMutex c(1);
    c.lock();
    cout<<"subthread lock c"<<endl;
    c.unlock();
    cout<<"subthread unlock c"<<endl;
}
void testMyLevelMutex() {
    MyLevelMutex a(10),b(100);
    a.lock();
    cout<<"main thread lock a"<<endl;
    b.lock();
    cout<<"main thread lock b"<<endl;// prv=10,now=100
    MyThreadRAII subThread(thread(newLock, ref(b)));
    b.unlock();// prv=0,now=10
    cout<<"main thread unlock b"<<endl;


}
#endif //CPPCONCURRENCYINACTION_MYLEVELMUTEX_H
