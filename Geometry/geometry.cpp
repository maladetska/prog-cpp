#include "geometry.h"

/* МЕТОДЫ ТОЧКИ */

// новая точка с новыми координатами
Point::Point(const int &new_x, const int &new_y) : x(new_x), y(new_y) {}

// уже заданная точка
Point::Point(const Point &other) : x(other.x), y(other.y) {}

Point &Point::operator=(const Point &other) {
    x = other.x;
    y = other.y;
    return *this;
}

// getter для точки
int Point::get_x() const { return x; }

int Point::get_y() const { return y; }

/* МЕТОДЫ ЛОМАННОЙ */

// новая ломанная, заданная точками
PolygonalChain::PolygonalChain(const int &new_k, Point *new_points) {
    k = new_k;
    points = new Point[k];
    for (int i = 0; i < k; ++i) {
        points[i] = new_points[i];
    }
}

// уже заданная ломанная
[[maybe_unused]] PolygonalChain::PolygonalChain(const PolygonalChain &other) {
    k = other.k;
    points = new Point[k];
    for (int i = 0; i < k; ++i) {
        points[i] = other.points[i];
    }
}

PolygonalChain &PolygonalChain::operator=(const PolygonalChain &other) {
    if (this != &other) {
        delete[] points;

        k = other.k;
        points = new Point[k];

        for (int i = 0; i < k; ++i) {
            points[i] = other.points[i];
        }
    }

    return *this;
}

// деструктор
PolygonalChain::~PolygonalChain() { delete[] points; }

// getter для ломанной: кол-во точек и сами точки
int PolygonalChain::get_k() const { return k; }

Point PolygonalChain::get_point(const int &i) const { return points[i]; }

// расстояние между точками
double distance(const Point &p1, const Point &p2) {
    return sqrt(
            pow(static_cast<double>(p1.get_x()) - static_cast<double>(p2.get_x()),
                2) +
            pow(static_cast<double>(p1.get_y()) - static_cast<double>(p2.get_y()),
                2));
}

// периметр ломанной
double PolygonalChain::perimeter() const {
    double perimeter0 = 0;
    for (int i = 0; i < this->k - 1; ++i) {
        perimeter0 += distance(points[i], points[i + 1]);
    }
    return perimeter0;
}

/* МЕТОДЫ ЗАМКНУТОЙ ЛОМАННОЙ */

// новая замкнутая ломанная
ClosedPolygonalChain::ClosedPolygonalChain(const int &new_k, Point *new_points)
    : PolygonalChain(new_k, new_points) {}

// периметр замкнутой ломанной
double ClosedPolygonalChain::perimeter() const {
    double perimeter0 = 0;
    perimeter0 += this->PolygonalChain::perimeter();

    Point p1 = this->get_point(0);
    Point p2 = this->get_point(this->get_k() - 1);

    perimeter0 += distance(p1, p2);
    return perimeter0;
}

/* МЕТОДЫ МНОГОУГОЛЬНИКА */

// новый многоугольник, заданный кол-вом точек и самими точками
Polygon::Polygon(const int &new_k, Point *new_points)
    : ClosedPolygonalChain(new_k, new_points) {}

// площадь многоугольника
double Polygon::area() const {
    double area0 = 0;

    for (int i = 0; i < this->get_k() - 1; ++i) {
        area0 += (static_cast<double>(this->get_point(i).get_x()) *
                          static_cast<double>(this->get_point(i + 1).get_y()) -
                  static_cast<double>(this->get_point(i + 1).get_x()) *
                          static_cast<double>(this->get_point(i).get_y()));
    }

    area0 +=
            (static_cast<double>(this->get_point(this->get_k() - 1).get_x()) *
                     static_cast<double>(this->get_point(0).get_y()) -
             static_cast<double>(this->get_point(0).get_x()) *
                     static_cast<double>(this->get_point(this->get_k() - 1).get_y()));

    return fabs(area0) / 2;
}

/* МЕТОДЫ ТРЕУГОЛЬНИКА */

// новый треугольник, заданный кол-вом точек и самими точками
Triangle::Triangle(const int &new_n, Point *new_points)
    : Polygon(new_n, new_points) {}

// угол между отрезками с точками p1, p2 и общей вершиной vertex (через
// скалярное произведение)
bool angle(const Point &vertex, const Point &p1, const Point &p2) {
    int dp = (p1.get_x() - vertex.get_x()) * (p2.get_x() - vertex.get_x()) +
             (p1.get_y() - vertex.get_y()) * (p2.get_y() - vertex.get_y());
    double angle0 = cos((static_cast<double>(dp)) /
                        (distance(vertex, p1) * distance(vertex, p2)));

    return angle0 == 1;
}

// проверка на прямоугольный треугольник
bool Triangle::hasRightAngle() const {
    Point p1 = this->get_point(0);
    Point p2 = this->get_point(1);
    Point p3 = this->get_point(2);

    if (angle(p1, p2, p3) || angle(p2, p1, p3) || angle(p3, p2, p1)) {
        return true;
    } else {
        return false;
    }
}

/* МЕТОДЫ ТРАПЕЦИИ */

// новая трапеция, заданная кол-вом точек и самими точками
Trapezoid::Trapezoid(const int &new_k, Point *new_points)
    : Polygon(new_k, new_points) {}

// высота трапеции
double Trapezoid::heightOfTrapezoid() const {
    Point p1 = this->get_point(0);
    Point p2 = this->get_point(1);
    Point p3 = this->get_point(2);
    Point p4 = this->get_point(3);

    double base1 = distance(p2, p3);
    double base2 = distance(p4, p1);
    double area0 = this->area();
    double h = (2 * area0) / (base1 + base2);

    return h;
}

/* МЕТОДЫ ПРАВИЛЬНОГО МНОГОУГОЛЬНИКА */

// новый правильный многоугольник, заданный кол-вом точек и самими точками
RegularPolygon::RegularPolygon(const int &new_k, Point *new_points)
    : Polygon(new_k, new_points) {}

// периметр правильного многоугольника
double RegularPolygon::perimeter() const {
    double side = distance(get_point(0), get_point(1));
    double k = get_k();

    return side * k;
}

// площадь правильного многоугольника
double RegularPolygon::area() const {
    double pi = 3.1415926535;
    double side = distance(get_point(0), get_point(1));
    double k = get_k();

    return (k * pow(side, 2)) / (4 * tan(pi / k));
}
