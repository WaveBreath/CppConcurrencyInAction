//
// Created by happyend on 2026/9/26.
//

#ifndef CPPCONCURRENCYINACTION_FUTURE_H
#define CPPCONCURRENCYINACTION_FUTURE_H
#include <bits/stdc++.h>
using namespace std;
condition_variable cd;
mutex m;
template<typename T>
void showlist(list<T>& l) {
    for (auto re: l) {
        cout<<re<<",";
    }
    cout<<endl;
}

template <typename T>
list<T> MyQuickSort(list<T> t) {
    showlist(t);
    if (t.size()<2) {
        return t;
    }
    auto first = *t.begin();
    t.pop_front();
    list<T> l;
    auto devide=partition(t.begin(),t.end(), [&first](const T &item){return item < first;});
    l.splice(l.begin(),t,t.begin(),devide);
    future<list<T>> futl = async(MyQuickSort<T>,l);
    list<T> futr = MyQuickSort<T>(t);
    futr.push_front(first);
    futr.splice(futr.begin(),futl.get());
    return futr;
}
void test_quick_sort() {
    list<int> l={1,3,5,7,9,2,4,6,8,10};
    auto res = MyQuickSort(l);
    showlist(res);
}
#endif //CPPCONCURRENCYINACTION_FUTURE_H
