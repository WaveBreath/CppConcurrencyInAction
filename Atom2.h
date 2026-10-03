//
// Created by happyend on 2026/9/27.
//

#ifndef CPPCONCURRENCYINACTION_ATOM_H
#define CPPCONCURRENCYINACTION_ATOM_H
#include <bits/stdc++.h>
using namespace std;
atomic_int x(0),y(0),z(0);
atomic_int go(false);
unsigned const loop_count=100;
const memory_order mo=memory_order_relaxed;
// const memory_order mo=memory_order_seq_cst;


struct read_values {
    int x,y,z;
};
read_values value1[loop_count], value2[loop_count], value3[loop_count], value4[loop_count], value5[loop_count];
void increment(atomic_int* var_to_inc, read_values* values) {
    while (!go) {
        this_thread::yield();
    }
    for (unsigned i = 0; i < loop_count; ++i) {
        values[i].x = x.load(mo);
        /**
         * x64
         * both is movl
         */
        /**
         * aarch64
         * ldr(memory_order_relaxed)->ldar(memory_order_seq_cst)
         * ldar add a hidden one way barriers before ldr
         */
        values[i].y = y.load(mo);
        values[i].z = z.load(mo);
        var_to_inc->store(i+1, mo);
        /**
         * x64
         * movl(memory_order_relaxed)->xchgl(memory_order_seq_cst)
         * xchgl is strong memory order
         * movl is not
         */
        /**
         * aarch64
         * str(memory_order_relaxed)->stlr(memory_order_seq_cst)
         * stlr add a hidden one way barriers after str
         * https://armv8-doc.readthedocs.io/en/latest/13.html#id2
         */
        this_thread::yield();
    }
}
void read_vals(read_values* values) {
    while (!go) {
        this_thread::yield();
    }
    for (unsigned i = 0; i < loop_count; ++i) {
        values[i].x = x.load(mo);
        values[i].y = y.load(mo);
        values[i].z = z.load(mo);
        this_thread::yield();
    }
}
void print(read_values values) {
    cout<<"("<<values.x<<","<<values.y<<","<<values.z<<")";
}
void print(read_values* v) {
    for (unsigned i = 0; i < loop_count; ++i) {
        if (i)cout<<",";
        print(v[i]);
    }
    cout<<endl;
}
void check_order() {
    cout<<"XXX"<<endl;
    vector<read_values> v;
    for (unsigned i = 0; i < loop_count; ++i) {
        v.push_back(value1[i]);
        v.push_back(value2[i]);
        v.push_back(value3[i]);
        v.push_back(value4[i]);
        v.push_back(value5[i]);
    }
    sort(v.begin(), v.end(),[] (read_values a, read_values b) {
        if ( a.x != b.x) return a.x < b.x;
        if ( a.y != b.y) return a.y < b.y;
        return a.z < b.z;
    });
    for (unsigned i = 1; i < v.size(); ++i) {
        if (v[i].y<v[i-1].y || v[i].z<v[i-1].z) {
            print(v[i]);
            print(v[i-1]);
            cout<<endl;
        }
    }
    sort(v.begin(), v.end(),[] (read_values a, read_values b) {
        if ( a.y != b.y) return a.y < b.y;
        if ( a.x != b.x) return a.x < b.x;
        return a.z < b.z;
    });
    for (unsigned i = 1; i < v.size(); ++i) {
        if (v[i].z<v[i-1].z) {
            print(v[i]);
            print(v[i-1]);
            cout<<endl;
        }
    }

}
void run() {
    thread t1(increment, &x, value1);
    thread t2(increment, &y, value2);
    thread t3(increment, &z, value3);
    thread t4(read_vals, value4);
    thread t5(read_vals, value5);
    go = true;
    t5.join();
    t4.join();
    t3.join();
    t2.join();
    t1.join();
    print(value1);
    print(value2);
    print(value3);
    print(value4);
    print(value5);
    check_order();
}
#endif //CPPCONCURRENCYINACTION_ATOM_H
