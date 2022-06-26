#include "geometry.h"

#include <cassert>
#include <iostream>

using namespace std;

const double EPS = 1e-9;

void PointCheck() {
    const Point p1;
    assert(p1.get_x() == 0 && p1.get_y() == 0);
    const Point p2(3, 4);
    assert(p2.get_x() == 3 && p2.get_y() == 4);
}

void InheritancePolygonalChainCheck(const PolygonalChain *pc,
                                    const PolygonalChain *cpc) {
    assert(pc->perimeter() == 9);
    assert(cpc->perimeter() == 12);
}

void PolygonsCheck() {
    auto *a = new Point[3]{Point(0, 0), Point(3, 4), Point(3, 0)};
    auto *b = new Point[4]{Point(0, 0), Point(1, 4), Point(3, 4), Point(3, 0)};
    const Polygon p(3, a);
    const Triangle t(3, a);
    const Trapezoid tr(4, b);
    const PolygonalChain pc(3, a);
    assert(pc.get_k() == 3 && pc.get_point(1).get_x() == 3 &&
           pc.get_point(1).get_y() == 4);
    assert(pc.perimeter() == 9);
    const ClosedPolygonalChain cpc(3, a);
    a[1] = Point();
    assert(cpc.get_k() == 3 && cpc.get_point(1).get_x() == 3 &&
           cpc.get_point(1).get_y() == 4);
    assert(cpc.perimeter() == 12);
    InheritancePolygonalChainCheck(&pc, &cpc);
    assert(p.area() == 6);
    assert(abs(tr.heightOfTrapezoid() - 4) < EPS);
    assert(t.hasRightAngle());
    Triangle trSharpestAsMyHand(
            3, new Point[3]{Point(0, 0), Point(1, 1), Point(0, 100)});
    assert(!trSharpestAsMyHand.hasRightAngle());
    RegularPolygon rp(
            4, new Point[4]{Point(0, 0), Point(0, 2), Point(2, 2), Point(2, 0)});
    assert(abs(rp.area() - 4) < EPS && abs(rp.perimeter() - 8) < EPS);
    Trapezoid tra(4, b);
    tra = tr;
    assert(abs(tra.heightOfTrapezoid() - 4) < EPS);
    auto *trap = new Trapezoid(4, b);
    Trapezoid trCopy(*trap);
    delete trap;
    assert(abs(trCopy.heightOfTrapezoid() - 4) < EPS);
}

int main() {
    PointCheck();
    PolygonsCheck();
}
