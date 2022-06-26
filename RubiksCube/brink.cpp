#include "brink.h"

brink::brink() {
    _brink.resize(3, std::vector<int>(3));
}

brink::brink(std::vector<std::vector<int>> const &obj) {
    _brink = obj;
}

void brink::create(int color) {
    for (auto &i: _brink) {
        for (auto &j: i) {
            j = color;
        }
    }
}

std::vector<int> &brink::operator[](int ind) {
    return _brink[ind];
}

void brink::rightWise() {
    int t = _brink[0][0];
    _brink[0][0] = _brink[2][0];
    _brink[2][0] = _brink[2][2];
    _brink[2][2] = _brink[0][2];
    _brink[0][2] = t;
    t = _brink[0][1];
    _brink[0][1] = _brink[1][0];
    _brink[1][0] = _brink[2][1];
    _brink[2][1] = _brink[1][2];
    _brink[1][2] = t;
}

void brink::leftWise() {
    int t = _brink[0][0];
    _brink[0][0] = _brink[0][2];
    _brink[0][2] = _brink[2][2];
    _brink[2][2] = _brink[2][0];
    _brink[2][0] = t;
    t = _brink[0][1];
    _brink[0][1] = _brink[1][2];
    _brink[1][2] = _brink[2][1];
    _brink[2][1] = _brink[1][0];
    _brink[1][0] = t;
}

bool brink::operator==(brink const &element) const {
    return element._brink == _brink;
}