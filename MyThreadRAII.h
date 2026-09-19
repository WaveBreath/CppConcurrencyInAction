//
// Created by happyend on 2026/9/19.
//

#ifndef CPPCONCURRENCYINACTION_MYTHREADRAII_H
#define CPPCONCURRENCYINACTION_MYTHREADRAII_H
#include <bits/stdc++.h>
using namespace std;

class MyThreadRAII {
private:
    thread t;
public:
    enum class DeconstructOption{
        join, detach
    }option;
    MyThreadRAII(thread& trd, DeconstructOption option= DeconstructOption::join):t(move(trd)), option(option)  {}
    MyThreadRAII(thread&& trd, DeconstructOption option= DeconstructOption::join):t(move(trd)), option(option)  {}
    MyThreadRAII(MyThreadRAII& trd, DeconstructOption option= DeconstructOption::join):t(move(trd.t)), option(option)  {}
    MyThreadRAII(MyThreadRAII&& trd, DeconstructOption option= DeconstructOption::join) noexcept :t(move(trd.t)), option(option) {}
    ~MyThreadRAII() {
        if (t.joinable()) {
            if (option == DeconstructOption::join) {t.join();}
            else {t.detach();}
        }
    }
    void operator=(MyThreadRAII&& trd) noexcept {
        option = trd.option;
        t=move(trd.t);
    }

};


#endif //CPPCONCURRENCYINACTION_MYTHREADRAII_H
