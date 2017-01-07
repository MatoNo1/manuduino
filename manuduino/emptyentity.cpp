#include "emptyentity.h"

EmptyEntity::EmptyEntity(QWidget* parent, QString _pixPath, int _height, int _width):
    Entity(parent, _pixPath), height(_height), width(_width)
{
    label.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    label.setFixedSize(_width, _height);
}

EmptyEntity::EmptyEntity(const EmptyEntity &_e):
    Entity(_e)
{
    height = _e.height;
    width = _e.width;
}

EmptyEntity::~EmptyEntity() {}

void EmptyEntity::setSize(int _height, int _width)
{
    height = _height;
    width = _width;
    label.setFixedSize(_width, _height);
}

int EmptyEntity::getHeight()
{
    return height;
}

int EmptyEntity::getWidth()
{
    return width;
}
