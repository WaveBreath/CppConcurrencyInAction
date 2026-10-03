//
// Created by happyend on 2026/9/27.
//

#ifndef CPPCONCURRENCYINACTION_ATOM_H
#define CPPCONCURRENCYINACTION_ATOM_H
#include <bits/stdc++.h>
using namespace std;
bool my_compare_exchange_weak(bool &val, bool &excepted, bool desired) {
    if (val == excepted && random()) {
        val = desired;
        return true;
    }
    else {
        excepted = val;
        return false;
    }
}
void testAtomicFlat() {
    atomic_bool atomicBool(false);
    // bool res;
    // res = atomicBool.exchange(true);// res=0,val=1
    bool excepted = false;
    // atomic=true, excepted=false -> return false, excepted = true  atomic = true -> break
    // atomic = false, excepted = false
    // case 1: return true atomic = true excepted = true -> break
    // case 2: return false automic = false excepted = false -> continue


    while (!atomicBool.compare_exchange_weak(excepted, true) && !excepted) {cout<<"X"<<endl;}
    cout << atomicBool <<','<<excepted<< endl;

}
class RW {
public:
    atomic_bool x,y;
    atomic_int z;
    memory_order mo;
    RW(memory_order m):mo(m) {
        x=false;
        y=false;
        z=0;
    }
    void write_x() {
        x.store(true, mo);
    }
    void write_y() {
        y.store(true, mo);
    }
    void read_x_then_y() {
        while (!x.load(mo)){}
        if (y.load(mo)) {
            ++z;
        }
    }
    void read_y_then_x() {
        while (!y.load(mo)){}
        if (x.load(mo)) {
            ++z;
        }
    }
    void write_x_then_y() {

        x.store(true, mo);
        y.store(true, mo);
    }
};
void run1() {
    RW rw(memory_order_seq_cst);
    thread a(&RW::write_x, &rw);
    thread b(&RW::write_y, &rw);
    thread c(&RW::read_x_then_y, &rw);
    thread d(&RW::read_y_then_x, &rw);
    a.join();
    b.join();
    c.join();
    d.join();
    assert(rw.z.load()!=0);
}
void run2() {
    RW rw(memory_order_relaxed);
    std::thread a(&RW::write_x_then_y, &rw);
    std::thread b(&RW::read_y_then_x, &rw);
    a.join();
    b.join();
    assert(rw.z.load()!=0);
}

#endif //CPPCONCURRENCYINACTION_ATOM_H
