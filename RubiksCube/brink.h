#pragma once

#include <vector>

//Грани.
//Потребуется для сборки методом слоёв.
class brink {
public:
    std::vector<std::vector<int>> _brink;//Вектор граней

    explicit brink();//Explicit позволяет избежать вызовов конструктора от одного подобного аргумента
    explicit brink(std::vector<std::vector<int>> const &obj);

    void create(int);

    std::vector<int> &operator[](int);

    void rightWise();//Поворот грани по часовой.

    void leftWise();//Поворот грани против часовой.

    bool operator==(brink const &) const;//Оператор равенства граней

    ~brink() = default;//Деструктор
};