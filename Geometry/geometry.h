/*
Создайте класс Point с конструктором по умолчанию и конструктором от координат. Гарантируется, что координаты целые. Реализуйте getter.
Создайте класс PolygonalChain с конструктором от количества точек и динамического массива точек. Реализуйте getter количества точек и конкретной точки.
Создайте класс ClosedPolygonalChain.
Создайте класс Polygon.
Создайте класс Triangle. Реализуйте метод hasRightAngle на проверку, является ли данный треугольник прямоугольным.
Создайте класс Trapezoid. Реализуйте метод нахождения высоты трапеции.
Гарантируется, что первый отрезок не основание.
Создайте класс RegularPolygon.*/

#pragma once

#include <cmath>

/* ТОЧКА */

struct Point {
public:
    Point() = default;

    Point(const int &new_x, const int &new_y);// конструктор
    Point(const Point &other);                // конструктор копирования
    Point &operator=(const Point &other);     //

    [[nodiscard]] int get_x() const;// getter x
    [[nodiscard]] int get_y() const;// getter y

private:// по умолчанию
    int x = 0;
    int y = 0;
};

// Расстояние между точками
double distance(const Point &p1, const Point &p2);

// Угол между отрезками с точками p1, p2 и общей вершиной vertex (через
// скалярное произведение)
bool angle(const Point &vertex, const Point &p1, const Point &p2);

/* ЛОМАННАЯ */

struct PolygonalChain {
public:
    PolygonalChain(const int &new_k, Point *new_points);// конструктор
    [[maybe_unused]] PolygonalChain(
            const PolygonalChain &other);// конструктор копирования - p(other)
    PolygonalChain &
    operator=(const PolygonalChain &other);// конструктор копирования - p = orher
    ~PolygonalChain();                     // деструктор

    [[nodiscard]] Point get_point(const int &i) const;// getter точки
    [[nodiscard]] int get_k() const;                  // getter количества
    [[nodiscard]] virtual double perimeter() const;   // периметр (виртуальный метод)

private:
    int k = 0;              // кол-во точек
    Point *points = nullptr;// нулевой указатель
};

/* ЗАМКНУТАЯ ЛОМАННАЯ */

struct ClosedPolygonalChain : public PolygonalChain {
public:
    ClosedPolygonalChain(const int &new_k,
                         Point *new_points);// (собственный) конструктор

    [[nodiscard]] double perimeter() const override;// периметр
};

/* МНОГОУГОЛЬНИК */

struct Polygon : public ClosedPolygonalChain {
public:
    Polygon(const int &new_k, Point *new_points);// конструктор
    [[nodiscard]] double area() const;           // площадь
};

/* ТРЕУГОЛЬНИК */

struct Triangle : public Polygon {
public:
    Triangle(const int &new_k, Point *new_points);// конструктор
    [[nodiscard]] bool hasRightAngle() const;     // является ли данный треугольник прямоугольным?
};

/* ТРАПЕЦИЯ */

struct Trapezoid : public Polygon {
public:
    Trapezoid(const int &new_k, Point *new_points);// конструктор
    [[nodiscard]] double heightOfTrapezoid() const;// метод нахождения высоты трапеции
};

/* ПРАВИЛЬНЫЙ МНОГОУГОЛЬНИК */

struct RegularPolygon : public Polygon {
public:
    RegularPolygon(const int &new_k, Point *new_points);// конструктор
    [[nodiscard]] double perimeter() const override;    // периметр
    [[nodiscard]] double area() const;                  // площадь
};