#include "pos.h"

Pos::Pos(int _x, int _y):
    x(_x), y(_y)
{}

Pos::Pos(const Pos& _p):
    x(_p.x), y(_p.y)
{}

bool Pos::operator==(Pos _p)
{
    return (x == _p.x) && (y == _p.y);
}

bool Pos::operator!=(Pos _p)
{
    return !(*this == _p);
}

bool Pos::operator<(Pos _p)
{
    return (x < _p.x) || (x == _p.x) && (y < _p.y);
}

bool Pos::operator<=(Pos _p)
{
    return (*this < _p) || (*this == _p);
}

bool Pos::operator>(Pos _p)
{
    return !(*this <= _p);
}

bool Pos::operator>=(Pos _p)
{
    return !(*this < _p);
}

Pos Pos::operator+(Pos _p)
{
    return Pos(x + _p.x, y + _p.y);
}

Pos Pos::operator-(Pos _p)
{
    return Pos(x - _p.x, y - _p.y);
}

Pos Pos::operator*(int k)
{
    return Pos(x * k, y * k);
}

void Pos::operator+=(Pos _p)
{
    x += _p.x; y += _p.y;
}

void Pos::operator-=(Pos _p)
{
    x -= _p.x; y -= _p.y;
}

void Pos::operator*=(int k)
{
    x *= k; y *= k;
}

Pos Pos::operator++()
{
    if (y >= maxY - 1) {
        ++x;
        y = 0;
    } else
        ++y;
}

Pos Pos::operator--()
{
    if (y)
        --y;
    else {
        --x;
        y = maxY - 1;
    }
}

void Pos::setMaxY(int _maxY)
{
    maxY = _maxY;
}
