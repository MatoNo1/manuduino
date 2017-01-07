#include "entity.h"

Entity::Entity(QWidget* parent, QString _pixPath):
    QWidget(parent), pixPath(_pixPath)
{
    QPixmap pix(_pixPath);
    label.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label.clear();
    label.setPixmap(pix);
    //label.show();
    tempLayout.setSpacing(0);
    tempLayout.setMargin(0);
    tempLayout.addWidget(&label, 0, 0);
    setLayout(&tempLayout);
}

Entity::Entity(const Entity &_e)
{
    label.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label.clear();
    label.setPixmap(*(_e.label.pixmap()));
    //label.show();
    pixPath = _e.pixPath;
}

Entity::~Entity()
{
    label.clear();
}

void Entity::operator=(const Entity &_e)
{
    label.clear();
    label.setPixmap(*(_e.label.pixmap()));
    //label.show();
    pixPath = _e.pixPath;
}

void Entity::setPixPath(QString _pixPath)
{
    QPixmap pix(_pixPath);
    label.clear();
    label.setPixmap(pix);
}
