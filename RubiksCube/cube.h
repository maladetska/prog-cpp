#pragma once

#include "cube_sweep.h"
#include "small_cube.h"
#include <GLUT/glut.h>
#include <fstream>

class cube {
    small_cube _cube[3][3][3];//Кубик из 27 кубиков.
    double size{};
    int color[6]{};// Цвета граней.
    cube_sweep _2d;//Развёртка.
    //Все цвета.
    unsigned int _correct_color[6] = {0xFFFFFF,
                                      0xFF9900,
                                      0x0000FF,
                                      0xFF0000,
                                      0x00FF00,
                                      0xFFFF00};

public:
    cube() = default;
    int rotated = -1;                         //Храним номер грани, которая в данный момент поварачивается, или -1 если ничего не поварачивается.
    int angle[7]{};                           //Храним угол поворота каждой грани.
    [[maybe_unused]] cube(cube const &a);                      //Конструктор.
    cube(cube_sweep const &Cur, double _size);//Конструктор для цветов.
    cube(std::ifstream &F, double size);      //Считываем развёртку куба в 'С'.
    void draw();                              //Рисуем.
    void full_turn(int idx, int sign);        //Поворот на 90 градусов грани.
    void small_turn(int idx, int _angle);     //Крутит грань под номером idx на угол _angle (в градусах).
    void swapper();                           //Поворот всего кубика на 90 градусов.
    cube_sweep solve();                       //Переводим кубик-рубик в развёртку.

private:
    small_cube tmp[4][4];
    //Перевод цветов в числа, для облегчения сборки.
    void switcher(std::vector<brink> &br,
                  int a, int b, int c, int i, int j, int k);
    bool check[3][3][3]{true};
};
