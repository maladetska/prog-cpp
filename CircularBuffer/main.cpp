#include <algorithm>
#include <iostream>

template<class T>
class CircularBuffer {
private:
    int capacity{};
    int fullness = 0;
    T *data;
    int head = 0;
    int tail = 0;

public:
    class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
    private:
        T *ptr;

    public:
        Iterator() : ptr(nullptr) {}
        explicit Iterator(T *ptr) : ptr(ptr) {}
        Iterator(const Iterator &iter) : ptr(iter.ptr) {}

        Iterator operator++() {
            ptr++;
            return *this;
        }

        Iterator operator++(T) {
            Iterator tmp(*this);
            ++ptr;
            return tmp;
        }

        Iterator &operator--() {
            ptr--;
            return *this;
        }

        Iterator operator--(T) {
            Iterator tmp(*this);
            --ptr;
            return tmp;
        }

        Iterator operator+(int elem) {
            return Iterator(ptr + elem);
        }

        T operator-(const Iterator &iter) {
            return (ptr - iter.ptr);
        }

        Iterator operator-(int elem) {
            return Iterator(ptr - elem);
        }

        Iterator &operator+=(T elem) {
            ptr += elem;
            return *this;
        }

        Iterator &operator-=(T elem) {
            ptr -= elem;
            return *this;
        }
        T &operator*() const {
            return *ptr;
        }

        T *operator->() const {
            return ptr;
        }

        T &operator[](const int elem) {
            return ptr[elem];
        }

        bool operator==(const Iterator &elem) const {
            return elem.ptr == this->ptr;
        }

        bool operator!=(const Iterator &elem) const {
            return elem.ptr != this->ptr;
        }

        bool operator<(const Iterator &elem) const {
            return elem.ptr < this->ptr;
        }

        bool operator>(const Iterator &elem) const {
            return elem.ptr > this->ptr;
        }

        bool operator>=(const Iterator &elem) const {
            return elem.ptr >= this->ptr;
        }

        bool operator<=(const Iterator &elem) const {
            return elem.ptr <= this->ptr;
        }
    };

    CircularBuffer() = default;
    ;

    explicit CircularBuffer(int cap) : capacity(cap) {
        head = 0;
        tail = 0;
        data = new T[capacity];
    }

    [[nodiscard]] Iterator begin() const {
        return Iterator(data + head);
    }

    [[nodiscard]] Iterator end() const {
        return Iterator(data + tail + 1);
    }

    [[nodiscard]] Iterator first() const {
        return Iterator(data);
    }

    [[nodiscard]] Iterator last() const {
        return Iterator(data + capacity);
    }

    T &operator[](int index) {
        return data[index % capacity];
    }

    void push_front(const T &elem) {
        fullness++;
        if (fullness == 1) {
            tail = capacity - 1;
            head = tail;
            data[tail] = elem;
        } else if (fullness > capacity) {
            data[tail] = elem;
            head = tail;
            tail--;
            if (tail == -1) {
                tail = capacity - 1;
            }
            fullness--;
        } else {
            head--;
            if (head == -1) {
                head = capacity - 1;
            }
            data[head] = elem;
        }
    }

    void push_back(const T &elem) {
        fullness++;
        if (fullness == 1) {
            tail = capacity - 1;
            head = tail;
            data[tail] = elem;
        } else if (fullness > capacity) {
            data[head] = elem;
            tail = head;
            head++;
            if (head == capacity) {
                head = 0;
            }
            fullness = capacity;
        } else {
            tail++;
            if (tail == capacity) {
                tail = 0;
            }
            data[tail] = elem;
        }
    }

    void pop_front() {
        fullness--;
        data[head] = 0;
        if (head == capacity - 1) {
            head = 0;
        } else {
            head++;
        }
    }

    [[maybe_unused]] void pop_back() {
        fullness--;
        data[tail] = 0;
        if (tail == 0) {
            tail = capacity - 1;
        } else {
            tail--;
        }
    }

    void resize(const int &n) {
        T *tmp = new T[n];

        for (int i = 0; i < capacity; i++) {
            tmp[i] = data[i];
        }

        for (int i = capacity; i < n; i++) {
            tmp[i] = 0;
        }

        delete[] data;
        data = tmp;
        capacity = n;

        if (fullness > capacity) {
            fullness = capacity;
        }
    }

    void print() {
        int count = 0;
        if (head <= tail) {
            for (Iterator iter = begin(); iter != end(); iter++) {
                std::cout << *iter << " ";
            }
            std::cout << std::endl;
            return;
        }
        for (Iterator iter = begin(); iter != last(); iter++) {
            count++;
            std::cout << *iter << " ";
        }
        if (count < fullness) {
            for (Iterator iter = first(); iter != end(); iter++) {
                std::cout << *iter << " ";
            }
        }

        std::cout << std::endl;
    }

    ~CircularBuffer() {
        delete[] data;
    }
};

int main() {
    CircularBuffer<int> buffer(3);

    buffer.push_front(1);
    buffer.push_front(3);
    buffer.push_front(2);

    buffer.print();

    buffer.resize(7);

    buffer.push_back(11);
    buffer.push_back(5);
    buffer.push_back(4);
    buffer.print();

    buffer.push_back(7);
    buffer.print();

    buffer.push_front(-1);
    buffer.print();
    buffer.pop_front();
    buffer.print();

    std::cout << "Max: " << *max_element(buffer.first(), buffer.last()) << std::endl;

    return 0;
}
