#pragma once

#include <GLUT/glut.h>

//Маленькие кубики (всего 27), из которых состоит Кубик Рубика
class small_cube {
public:
    unsigned char _rgb[3]; //Для покраски кубиков с помощью функций "gl".
    unsigned int _color[6];//Цвета для метода "set" (вызываем в других файлах.(верх, низ, впереди, сзади, лево, право) )
    double size;           //Размер кубика.

    small_cube();

    //Меням цвета кубиков при повороте в разных осях.
    void XOY();
    void YOZ();
    void ZOX();

    unsigned char *RGB_(unsigned int a);//Записываем цвета в массив с помощью сдвига(8(char) и 32(int)).

    void draw(double x, double y, double z);//Рисование маленьких кубиков со смещением.
    void draw();                            //Рисуем.
    void set(int ind, unsigned int color);  //Меняем цвета.

    ~small_cube() = default;//Деструктор
};