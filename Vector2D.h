#ifndef LINAL_VECTOR2D_H
#define LINAL_VECTOR2D_H

#include <iostream>

class Vector2D {
public:
    Vector2D() : x(0), y(0) {}

    Vector2D(double _x, double _y) : x(_x), y(_y) {}

    double getX() const;

    double getY() const;

    void setX(double _x);

    void setY(double _y);

    void rotate(double angle); //Поворачивает веткор на угол angle, заданный в градусах

    Vector2D& operator=(const Vector2D &v);

    bool operator==(const Vector2D &v2) const;

    bool operator!=(const Vector2D &v2) const;

    Vector2D operator+(const Vector2D &v2) const;

    Vector2D operator-(const Vector2D &v2) const;

    Vector2D operator*(const double a) const;

    double operator*(const Vector2D &v2) const; //Скалярное произведение векторов

private:
    double x, y;
};

Vector2D operator*(double a, const Vector2D &v);

std::ostream &operator<<(std::ostream &os, const Vector2D &v);

std::istream &operator>>(std::istream &is, Vector2D &v);


#endif //LINAL_VECTOR2D_H
