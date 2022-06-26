#include "polynomial.h"

#include <utility>

/* ПОЛИНОМ */

Polynomial::Polynomial(std::vector<PolynomialElement> a) : elements(std::move(a)) {}

void Construct(std::vector<PolynomialElement> &elements) {
    if (!elements.empty()) {
        for (unsigned i = 0; i < elements.size(); i++) {
            for (unsigned j = (i + 1); j < elements.size(); j++) {
                if (elements[i].getPower() == elements[j].getPower()) {
                    elements[i].setCoefficient(elements[i].getCoefficient() + elements[j].getCoefficient());
                    elements.erase(elements.begin() + j);
                    --j;
                }
            }
        }
        for (unsigned i = 0; i < elements.size(); i++) {
            if (elements[i].getCoefficient() == 0) {
                elements.erase(elements.begin() + i);
                --i;
            }
        }
    }
}

[[maybe_unused]] int Polynomial::getSize() const {
    return elements.size();
}

/* ОПЕРАТОРЫ */

Polynomial &Polynomial::operator=(const Polynomial &Polynomial_) {
    elements.resize(Polynomial_.elements.size());
    for (unsigned i = 0; i < Polynomial_.elements.size(); ++i) {
        elements[i] = Polynomial_.elements[i];
    }
    Construct(elements);

    return *this;
}

bool Polynomial::operator==(const Polynomial &Polynomial_) {
    if (Polynomial_.elements.size() != elements.size()) {
        return false;
    }

    for (int i = 0; i < elements.size(); ++i) {
        if ((elements[i].getCoefficient() != Polynomial_.elements[i].getCoefficient()) || (elements[i].getPower() != Polynomial_.elements[i].getPower())) {
            return false;
        }
    }

    return true;
}

bool Polynomial::operator!=(const Polynomial &Polynomial_) {
    if (Polynomial_.elements.size() != elements.size()) {
        return true;
    }

    for (int i = 0; i < elements.size(); ++i) {
        if ((elements[i].getCoefficient() != Polynomial_.elements[i].getCoefficient()) || (elements[i].getPower() != Polynomial_.elements[i].getPower())) {
            return true;
        }
    }

    return false;
}

Polynomial Polynomial::operator+(const Polynomial &Polynomial_) {
    std::vector<PolynomialElement> ans;

    for (const auto &element: elements) {
        ans.push_back(element);
    }

    for (const auto &element: Polynomial_.elements) {
        ans.push_back(element);
    }

    Construct(ans);
    return {ans};
}

Polynomial Polynomial::operator-(const Polynomial &Polynomial_) {
    std::vector<PolynomialElement> ans;
    std::vector<PolynomialElement> invert = Polynomial_.elements;

    for (unsigned i = 0; i < Polynomial_.elements.size(); ++i) {
        double coefficient = (-1) * invert[i].getCoefficient();
        invert[i].setCoefficient(coefficient);
    }

    for (const auto &element: elements) {
        ans.push_back(element);
    }

    for (int i = 0; i < Polynomial_.elements.size(); ++i) {
        ans.push_back(invert[i]);
    }

    Construct(ans);
    return {ans};
}

Polynomial &Polynomial::operator+=(const Polynomial &Polynomial_) {
    for (const auto &element: Polynomial_.elements) {
        elements.push_back(element);
    }

    Construct(elements);
}

Polynomial &Polynomial::operator-=(const Polynomial &Polynomial_) {
    std::vector<PolynomialElement> invert = Polynomial_.elements;

    for (unsigned i = 0; i < Polynomial_.elements.size(); ++i) {
        double coefficient = (-1) * invert[i].getCoefficient();
        invert[i].setCoefficient(coefficient);
    }

    for (int i = 0; i < Polynomial_.elements.size(); ++i) {
        elements.push_back(invert[i]);
    }

    Construct(elements);
}

Polynomial Polynomial::operator*(const double num) {
    std::vector<PolynomialElement> ans;
    for (auto &element: elements) {
        ans.emplace_back(element.getCoefficient() * num, element.getPower());
    }

    Construct(ans);
    return {ans};
}

Polynomial Polynomial::operator*(const Polynomial &Polynomial_) {
    std::vector<PolynomialElement> ans;

    // перемножаем члены полиномов
    for (unsigned i = 0; i < elements.size(); ++i) {
        for (unsigned j = 0; j < Polynomial_.elements.size(); ++j) {
            ans.emplace_back(Polynomial_.elements[i].getCoefficient() * elements[j].getCoefficient(),
                             Polynomial_.elements[i].getPower() + elements[j].getPower());
        }
    }

    Construct(ans);

    return {ans};
}

Polynomial Polynomial::operator*=(const Polynomial &Polynomial_) {
    *this = *this * Polynomial_;
    return Polynomial(Polynomial_);
}

Polynomial Polynomial::operator*=(const double num) {
    return Polynomial(*this * num);
}

Polynomial Polynomial::operator/(const double num) {
    std::vector<PolynomialElement> ans;
    for (auto &element: elements) {
        ans.emplace_back(element.getCoefficient() / num, element.getPower());
    }

    Construct(ans);
    return {ans};
}

Polynomial Polynomial::operator/=(const double num) {
    return Polynomial(*this / num);
}

std::ostream &operator<<(std::ostream &out, const Polynomial &Polynomial_) {
    for (unsigned i = 0; i < Polynomial_.elements.size() - 1; ++i) {
        std::cout << Polynomial_.elements[i].getCoefficient() << " * x^" << Polynomial_.elements[i].getPower() << " + ";
    }
    std::cout << Polynomial_.elements[Polynomial_.elements.size() - 1].getCoefficient() << " * x^" << Polynomial_.elements[Polynomial_.elements.size() - 1].getPower() << std::endl;
}