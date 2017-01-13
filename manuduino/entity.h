#ifndef ENTITY_H
#define ENTITY_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include "const.h"

struct Entity : public QWidget {
public:
    Entity(QWidget* parent = 0, QString _pixPath = "");
    Entity(const Entity& _e);
    ~Entity();
    void operator= (const Entity& _e);
    void setPixPath(QString _pixPath);
    QString getPixPath();

protected:
    QLabel label;
    QString pixPath;
    QGridLayout tempLayout;
};

#endif // ENTITY_H

