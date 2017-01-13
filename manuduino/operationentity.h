#ifndef OPERATIONENTITY_H
#define OPERATIONENTITY_H

#include "entity.h"
#include <QMouseEvent>

struct OperationEntity : public Entity {
    Q_OBJECT

public:
    OperationEntity(QWidget* parent = 0, operationType _type = OP_SELECTOR, QString _pixPath = "");
    OperationEntity(const OperationEntity& _o);
    ~OperationEntity();
    int getArg(int idx);

protected:
    void mousePressEvent(QMouseEvent* ev);
    void mouseDoubleClickEvent(QMouseEvent* ev);

private:
    static const int HEIGHT = OPERATION_ENTITY_HEIGHT;
    static const int WIDTH = OPERATION_ENTITY_WIDTH;

    operationType type;
    int selectorBoolVar, selectorDir;
    int boolControllerBoolVar, boolControllerType;
    int intControllerIntVar, intControllerOperator, intControllerVal;
    int comparatorBoolVar, comparatorIntVar, comparatorOperator;
    int bitSetterIntVar, bitSetterBit, bitSetterBoolVar;
    int outputFormat, outputIntVar;

signals:
    void activate(operationType type);
};

#endif // OPERATIONENTITY_H

