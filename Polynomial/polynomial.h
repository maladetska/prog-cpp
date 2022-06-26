#pragma once

#include <cmath>
#include <iostream>
#include <vector>

class PolynomialElement {
private:
    double coefficient{};
    int power{};

public:
    PolynomialElement() = default;
    PolynomialElement(double k, int pow) : coefficient(k), power(pow) {}

    [[nodiscard]] double getCoefficient() const {
        return coefficient;
    }
    [[nodiscard]] int getPower() const {
        return power;
    }
    void setCoefficient(double k) {
        coefficient = k;
    }
    [[maybe_unused]] void setPower(int pow) {
        power = pow;
    }

    void operator=(const PolynomialElement &elem) {
        coefficient = elem.getCoefficient();
        power = elem.getPower();
    }

    ~PolynomialElement() = default;
};

class Polynomial {
private:
    std::vector<PolynomialElement> elements;// вектор элементов полинома
public:
    Polynomial() = default;
    ;
    Polynomial(std::vector<PolynomialElement>);// конструктор

    [[maybe_unused]] [[nodiscard]] int getSize() const;// геттер размера

    /* Опертаор... */
    Polynomial &operator=(const Polynomial &);// ...присваивания
    bool operator==(const Polynomial &);      // ...равенства
    bool operator!=(const Polynomial &);      // ...неравенства

    Polynomial operator+(const Polynomial &);  // ...сложения
    Polynomial operator-(const Polynomial &);  // ...вычитания
    Polynomial &operator+=(const Polynomial &);// ...сложения этого полинома с другим
    Polynomial &operator-=(const Polynomial &);// ...вычитания этого полинома с другим

    Polynomial operator*(const Polynomial &); // ...умножения полинома на другой
    Polynomial operator*(double);             // ...умножения на число
    Polynomial operator*=(const Polynomial &);// ...умножения полинома на другой
    Polynomial operator*=(double);            // ...умножения на число


    Polynomial operator/(double); // ...деления на число
    Polynomial operator/=(double);// ...деления на число

    PolynomialElement operator[](int i) {
        return elements[i];
    }

    friend std::ostream &operator<<(std::ostream &, const Polynomial &);// ...ввода

    friend Polynomial operator>>(std::istream &in, Polynomial &Polynomial_) {

        double k;
        int pow;

        std::cin >> k >> pow;
        std::vector<PolynomialElement> ans;

        for (const auto &element: Polynomial_.elements) {
            ans.push_back(element);
        }

        ans.emplace_back(k, pow);
        Polynomial_ = ans;
        return Polynomial(Polynomial_);
    }

    ~Polynomial() = default;
};
