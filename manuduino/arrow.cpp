#include "arrow.h"

Arrow::Arrow(QWidget* parent, QString _pixPath, direct _dir, int _height, int _width):
    Entity(parent, _pixPath), dir(_dir), height(_height), width(_width)
{
    label.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    label.setFixedSize(_width, _height);
}

Arrow::Arrow(const Arrow &_a):
    Entity(_a)
{
    dir = _a.dir;
    height = _a.height;
    width = _a.width;
}

Arrow::~Arrow() {}

void Arrow::setDir(direct _dir)
{
    dir = _dir;
}

void Arrow::setSize(int _height, int _width)
{
    height = _height;
    width = _width;
    label.setFixedSize(_width, _height);
}

direct Arrow::getDir()
{
    return dir;
}

int Arrow::getHeight()
{
    return height;
}

int Arrow::getWidth()
{
    return width;
}
