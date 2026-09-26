//
// Created by happyend on 2026/9/20.
//

#ifndef CPPCONCURRENCYINACTION_MYQUEUE_H
#define CPPCONCURRENCYINACTION_MYQUEUE_H
#include <bits/stdc++.h>
using namespace std;
template <typename T>
class MyQueue {
    queue<T> data;
    mutable mutex mtx;
    condition_variable cond;

public:
    MyQueue(){}
    MyQueue(const MyQueue<T>& q) {
        lock_guard<mutex> lk(q.mtx); // set mtx mutable, so can lock here
        data = q.data;
    }
    MyQueue& operator=(const MyQueue& q) = delete;
    template<class... Args>
    void emplace_back(Args... args) {
        lock_guard<mutex> lk(mtx);
        data.emplace(args...);
    }
    void push(const T& value) {
        lock_guard<mutex> lk(mtx);
        data.push(value);
        cond.notify_all();
    }
    shared_ptr<T> try_pop() {
        lock_guard<mutex> lk(mtx);
        if (data.empty()) {return nullptr;}
        shared_ptr<T> ptr = data.front();
        data.pop();
        return ptr;
    }
    bool try_pop(T& value) {
        lock_guard<mutex> lk(mtx);
        if (data.empty()) {return false;}
        value = data.front();
        data.pop();
    }
    void wait_and_pop(T& value) {
        unique_lock<mutex> lk(mtx);
        cond.wait(lk, [this]{return !this->data.empty();});
        /*
         * while(!cond())wait(lock);
         * if condition good, not wait
         */
        value = data.front();
        data.pop();
    }
    shared_ptr<T> try_wait_and_pop() {
        unique_lock<mutex> lk(mtx);
        cond.wait(lk, [this]{return !this->data.empty();});
        shared_ptr<T> ptr = make_shared(data.front());
        data.pop();
        return ptr;

    }
    bool empty() const{
        lock_guard<mutex> lk(mtx);
        return data.empty();
    }
};
void producer(MyQueue<int> &queue) {
    sleep(200);
    queue.push(123);
    cout<<"put"<<123<<endl;
}
void consumer(MyQueue<int> &queue) {
    int v;
    cout<<"start get"<<endl;
    queue.wait_and_pop(v);
    cout<<"get"<<v<<endl;
}

void testQueue() {
    MyQueue<int> que;
    thread p(producer, ref(que));
    thread c(consumer, ref(que));
    cout<<p.get_id()<<"---"<<c.get_id()<<endl;
    p.join();
    c.join();

}

void testWaitUnlock() {
    mutex mtx;
    condition_variable cond;
    thread a([&mtx, &cond] {
        unique_lock<mutex> lk(mtx);
        cout<<"a start wait"<<endl;
        cond.wait(lk);
    });
    thread b([&mtx, &cond] {
        cout<<"b start sleep"<<endl;
        sleep(10);
        cout<<"b end sleep"<<endl;
        unique_lock<mutex> lk(mtx);
        cout<<"b get lock"<<endl;
        cond.notify_one();
    });
    a.join();
    b.join();

}


#endif //CPPCONCURRENCYINACTION_MYQUEUE_H
