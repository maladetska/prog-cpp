#include <iostream>
#include <vector>

/* Возможные предикаты */

template<typename N>
bool compare(N first, N second) {
    return second > first;
}

template<typename N>
bool positiveNumbers(N num) { return num > 0; }

template<typename N>
[[maybe_unused]] bool negativeNumbers(N num) { return num < 0; }

template<typename N>
bool aLetter(N ch) {
    return (ch > 96) and (ch < 123) or (ch > 64) and (ch < 91);
}

template<typename N>
[[maybe_unused]] bool aDigit(N ch) { return (ch > 47) and (ch < 58); }

/* Обобщённые алгоритмы: */

template<typename T, typename Function>
bool all_of(const T &begin, const T &end, Function func) {
    for (T iter = begin; iter != end; ++iter)
        if (!func(*iter))
            return false;

    return true;
}

template<typename T, typename Function>
bool any_of(const T &begin, const T &end, Function func) {
    for (T iter = begin; iter != end; ++iter)
        if (func(*iter))
            return true;

    return false;
}

template<typename T, typename Function>
bool none_of(const T &begin, const T &end, Function func) {
    for (T iter = begin; iter != end; ++iter)
        if (func(*iter))
            return false;

    return true;
}

template<typename T, typename Function>
bool one_of(const T &begin, const T &end, Function func) {
    int count = 0;
    for (T iter = begin; iter != end; ++iter)
        if (func(*iter))
            ++count;

    return count == 1;
}

template<typename T, typename Function>
bool is_sorted(const T &begin, const T &end, Function func) {
    for (T iter = begin; iter != end; ++iter)
        if (func(*iter, *(iter - 1)))
            return false;

    return true;
}

template<typename T, typename Function>
bool is_partitioned(T first, T last, Function func) {
    for (; first != last; ++first)
        if (!func(*first))
            break;

    for (; first != last; ++first)
        if (func(*first))
            return false;

    return true;
}

template<typename T, typename Element>
int find_not(T begin, T end, Element elem) {
    int ind = 0;
    while (begin != end) {
        if (elem != *begin)
            return ind;
        ind++;
        begin++;
    }
    return Element();
}

template<typename T, typename Element>
int find_backward(T begin, T end, Element elem) {
    int ind = 0;

    for (T iter = begin; iter < end; iter++) {
        if (*iter == elem)
            return ind;
        ind++;
    }

    return *begin;
}

template<typename T, typename Function>
bool is_palindrome(const T &begin, const T &end, [[maybe_unused]] Function func) {
    T start, finish;

    for (start = begin, finish = end - 1; start != end && finish != begin; start++, finish--)
        if (*start != *finish)
            return false;

    return true;
}

int main() {

    /* ПОСЛЕДОАТЕЛЬНОСТЬ ЦЕЛЫХ ЧИСЕЛ */
    std::cout << " -Целые числа- " << std::endl;

    std::vector<int> vecNum = {8, 5, 1, 4, 2, -2};

    int predicateNum = 8;

    std::cout << "all of <predicate>: " << (all_of(vecNum.begin(), vecNum.end(), positiveNumbers<int>) ? "true" : "false") << std::endl;
    std::cout << "any of <predicate>: " << (any_of(vecNum.begin(), vecNum.end(), positiveNumbers<int>) ? "true" : "false") << std::endl;
    std::cout << "none of <predicate>: " << (none_of(vecNum.begin(), vecNum.end(), positiveNumbers<int>) ? "true" : "false") << std::endl;
    std::cout << "one of <predicate>: " << (one_of(vecNum.begin(), vecNum.end(), positiveNumbers<int>) ? "true" : "false") << std::endl;
    std::cout << "is sorted: " << (is_sorted(vecNum.begin(), vecNum.end(), compare<int>) ? "true" : "false") << std::endl;
    std::cout << "is partitioned <predicate>: " << (is_partitioned(vecNum.begin(), vecNum.end(), positiveNumbers<int>) ? "true" : "false") << std::endl;
    std::cout << "find not <predicate>: " << find_not(vecNum.begin(), vecNum.end(), predicateNum) << std::endl;
    std::cout << "find backward <predicate>: " << vecNum.size() - 1 - find_backward(vecNum.begin(), vecNum.end(), predicateNum) << std::endl;
    std::cout << "is palindrome: " << (is_palindrome(vecNum.begin(), vecNum.end(), positiveNumbers<int>) ? "true" : "false") << std::endl;
    std::cout << std::endl;

    /* ПОСЛЕДОВАТЕЛЬНОСТЬ ДРОБНЫХ ЧИСЕЛ */
    std::cout << " -Дроби- " << std::endl;

    std::vector<double> vecRat = {0, 1.22, 1.99, 2.0};

    double predicateRat = 2.0;

    std::cout << "all of <predicate>: " << (all_of(vecRat.begin(), vecRat.end(), positiveNumbers<int>) ? "true" : "false") << std::endl;
    std::cout << "any of <predicate>: " << (any_of(vecRat.begin(), vecRat.end(), positiveNumbers<int>) ? "true" : "false") << std::endl;
    std::cout << "none of <predicate>: " << (none_of(vecRat.begin(), vecRat.end(), positiveNumbers<int>) ? "true" : "false") << std::endl;
    std::cout << "one of <predicate>: " << (one_of(vecRat.begin(), vecRat.end(), positiveNumbers<int>) ? "true" : "false") << std::endl;
    std::cout << "is sorted: " << (is_sorted(vecRat.begin(), vecRat.end(), compare<int>) ? "true" : "false") << std::endl;
    std::cout << "is partitioned <predicate>: " << (is_partitioned(vecRat.begin(), vecRat.end(), positiveNumbers<int>) ? "true" : "false") << std::endl;
    std::cout << "find not <predicate>: " << find_not(vecRat.begin(), vecRat.end(), predicateRat) << std::endl;
    std::cout << "find backward <predicate>: " << vecRat.size() - 1 - find_backward(vecRat.begin(), vecRat.end(), predicateRat) << std::endl;
    std::cout << "is palindrome: " << (is_palindrome(vecRat.begin(), vecRat.end(), positiveNumbers<int>) ? "true" : "false") << std::endl;
    std::cout << std::endl;

    /* ПОСЛЕДОВАТЕЛЬНОСТЬ СИМВОЛОВ */
    std::cout << " -Символы- " << std::endl;

    vector<char> vecChar = {'a', '1', '1', 'a'};

    char predicateChar = '1';

    std::cout << "all of <predicate>: " << (all_of(vecChar.begin(), vecChar.end(), aLetter<char>) ? "true" : "false") << std::endl;
    std::cout << "any of <predicate>: " << (any_of(vecChar.begin(), vecChar.end(), aLetter<char>) ? "true" : "false") << std::endl;
    std::cout << "none of <predicate>: " << (none_of(vecChar.begin(), vecChar.end(), aLetter<char>) ? "true" : "false") << std::endl;
    std::cout << "one of <predicate>: " << (one_of(vecChar.begin(), vecChar.end(), aLetter<char>) ? "true" : "false") << std::endl;
    std::cout << "is sorted: " << (is_sorted(vecChar.begin(), vecChar.end(), compare<int>) ? "true" : "false") << std::endl;
    std::cout << "is partitioned <predicate>: " << (is_partitioned(vecChar.begin(), vecChar.end(), aLetter<char>) ? "true" : "false") << std::endl;
    std::cout << "find not <predicate>: " << find_not(vecChar.begin(), vecChar.end(), predicateChar) << std::endl;
    std::cout << "find backward <predicate>: " << vecChar.size() - 1 - find_backward(vecChar.begin(), vecChar.end(), predicateChar) << std::endl;
    std::cout << "is palindrome: " << (is_palindrome(vecChar.begin(), vecChar.end(), aLetter<char>) ? "true" : "false") << std::endl;
    std::cout << std::endl;

    return 0;
}
