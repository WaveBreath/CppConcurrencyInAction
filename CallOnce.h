//
// Created by happyend on 2026/9/20.
//

#ifndef CPPCONCURRENCYINACTION_CALLONCE_H
#define CPPCONCURRENCYINACTION_CALLONCE_H
#include <bits/stdc++.h>

#include "MyThreadRAII.h"
#include <pthread.h>

using namespace std;
volatile int x;
once_flag calSuccess;
pthread_once_t once = PTHREAD_ONCE_INIT;

void longTimeCal() {
    sleep(10);
    x=10;
    cout<<"longTimeCal"<<endl;
}
void callOnce(){
    call_once(calSuccess,longTimeCal);
    cout<<x<<endl;
}
void testCallOnce() {
    vector<MyThreadRAII> t;
    for(int i=0;i<10;i++) {
        t.emplace_back(thread(callOnce));
    }
}
void* wapper(void* arg) {
    pthread_once(&once,longTimeCal);
    return nullptr;
}


void testCallOncePoxis() {
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,wapper,NULL);
    pthread_join(tid1, NULL);
}
#endif //CPPCONCURRENCYINACTION_CALLONCE_H
