#ifndef EMPTYENTITY_H
#define EMPTYENTITY_H

#include "entity.h"

struct EmptyEntity : public Entity {
public:
    EmptyEntity (QWidget* parent = 0, QString _pixPath = "", int _height = 0, int _width = 0);
    EmptyEntity (const EmptyEntity& _e);
    ~EmptyEntity ();
    void setSize(int _height, int _width);
    int getHeight();
    int getWidth();

protected:
    int height, width;
};

#endif // EMPTYENTITY_H

