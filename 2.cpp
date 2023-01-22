#include <deque>
#include <vector>
#include <stdexcept>

using namespace std;

// Насколько мне известно, существует два основных способа создания циклического буфера,
// а именно: 1. с помощью очереди (односвязной или двусвязной), 2. с помощью массива.

// Первая реализация (RingBuffer) в качестве хранилища использует ограниченную очередь,
// где доступ к произвольному элементу в худшем случае за линейное время от длины очереди.

// Вторая реализация (RingBuffer2) в качестве хранилища использует ограниченный массив
// (в данном случае vector), где доступ к произвольному элементу в худшем случае
// за константное время от длины массива.



class RingBuffer {
    int maxlen;
    deque<int> deck;

public:
    explicit RingBuffer(int maxlen) : maxlen(maxlen) {}

    unsigned long long size() {
        return deck.size();
    }

    int getitem(int ind) {
        if (ind < 0 or ind >= this->size()) {
            throw invalid_argument("index is out of range");
        }

        return deck[ind];
    }

    void append(int num) {
        deck.push_back(num);
        if (this->size() > maxlen) {
            deck.pop_front();
        }
    }

    deque<int> get() {
        return deck;
    }
};

class RingBuffer2 {
    int maxlen;
    vector<int> dynamic_array;
    int cur = 0;

public:
    explicit RingBuffer2(int maxlen) : maxlen(maxlen) {}

    unsigned long long size() {
        return dynamic_array.size();
    }

    bool full() {
        return size() == maxlen;
    }

    int getitem(int ind) {
        if (ind < 0 or ind >= this->size()) {
            throw invalid_argument("index is out of range");
        }

        return dynamic_array[(ind + cur) % maxlen];
    }

    void append(int num) {
        if (full()) {
            dynamic_array[cur] = num;
            cur = (cur + 1) % maxlen;
        }
        else {
            dynamic_array.push_back(num);
        }
    }

    vector<int> get() {
        if (size() == maxlen) {
            vector<int> nexus = {dynamic_array.begin() + cur, dynamic_array.end()};
            nexus.insert(nexus.end(), dynamic_array.begin(), dynamic_array.begin() + cur);
            return nexus;
        }
        return dynamic_array;
    }

};
