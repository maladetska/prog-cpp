#pragma once

#include "cube_sweep.h"

//"Решатель" кубика с возможными сборками
class cube_solver {
    friend class cube_sweep;

public:
    bool _solve();
    cube_solver() = default;
    explicit cube_solver(cube_sweep *a) : _c(a) {}

private:
    cube_sweep *_c;

    void cross();              //Сборка креста для первого слоя.
    void first_layer();        //Первый слой.
    void second_layer();       //Второй слой.
    void last_layer(bool &tmp);//Последний слой.
    void last_cross(bool &tmp);//Крест в последнем слое.

    /*Правильный крест в последнем слое.
      1.Ребра совпадают рядом.
      2.Ребра совпадают напротив.
      3.Уже правильный. */
    void right_cross(bool &tmp);

    void swap_corners(bool &tmp);//Расстановка углов в последнем слое.
    void pif_paf();              //Средний и последний уровень. Вверх-вправо-вниз-влево
    void left_pif_paf();         //Левой рукой.
    void raise_ribs();           //Поднять ребра.
    void edge_to_left();         //Ребро идет вправо.
    void edge_to_right();        //Ребро идет влево.
    void nine_hours(int color);  //Точка → пол креста (девять часов) → палка → крест.
    void line(int color);        //F (пиф-паф) F'.

    int count_edge(int color, int &c);//Счёт цветов рёбер для понимания, как совпадают рёбра.

    void edge_near(int color);    //Ребра совпадают рядом.
    void edge_opposite(int color);//Ребра совпадают напротив.

    void switch_corner();//Для расстановки углов.

    int count_corners(int color);//Счёт цветов на грани для определения: нужно ли собирать крест.

    void one_corner(int color);//Для расстановки углов в последнем слое.
    void flip_corner();        //Разворот угла.
    void flip_corners();       //Разворот углов последнего слоя.

    ~cube_solver() = default;//Деструктор
};