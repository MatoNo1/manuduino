#ifndef ARROW_H
#define ARROW_H

#include "entity.h"

struct Arrow : public Entity {
public:
    Arrow(QWidget* parent = 0, QString _pixPath = "", direct _dir = UP, int _height = 0, int _width = 0);
    Arrow(const Arrow& _a);
    ~Arrow();
    void setDir(direct _dir);
    void setSize(int _height, int _width);
    direct getDir();
    int getHeight();
    int getWidth();

protected:
    direct dir;
    int height, width;
};

#endif // ARROW_H

