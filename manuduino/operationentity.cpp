#include "operationentity.h"
#include "selectordialog.h"
#include "boolcontrollerdialog.h"
#include "intcontrollerdialog.h"
#include "comparatordialog.h"
#include "bitsetterdialog.h"
#include "outputdialog.h"

OperationEntity::OperationEntity(QWidget *parent, operationType _type, QString _pixPath):
    Entity(parent, _pixPath), type(_type)
{
    label.setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    label.setFixedSize(WIDTH, HEIGHT);

    switch (_type) {
        case OP_SELECTOR: {
            selectorBoolVar = 0; selectorDir = 0;
            break;
        }
        case OP_BOOL_CONTROLLER: {
            boolControllerBoolVar = 0; boolControllerType = 0;
            break;
        }
        case OP_INT_CONTROLLER: {
            intControllerIntVar = 0; intControllerOperator = 0; intControllerVal = 0;
            break;
        }
        case OP_COMPARATOR: {
            comparatorBoolVar = 0; comparatorIntVar = 0; comparatorOperator = 0;
            break;
        }
        case OP_BIT_SETTER: {
            bitSetterIntVar = 0; bitSetterBit = 0; bitSetterBoolVar = 0;
            break;
        }
        case OP_OUTPUT: {
            outputFormat = 0; outputIntVar = 0;
            break;
        }
    }
}

OperationEntity::OperationEntity(const OperationEntity &_o):
    Entity(_o)
{
    type = _o.type;
}

OperationEntity::~OperationEntity() {}

int OperationEntity::getArg(int idx)
{
    switch (type) {
        case OP_SELECTOR: {
            if (idx == 0)
                return selectorBoolVar;
            else if (idx == 1)
                return selectorDir;
            else
                return 0;
            break;
        }
        case OP_BOOL_CONTROLLER: {
            if (idx == 0)
                return boolControllerBoolVar;
            else if (idx == 1)
                return boolControllerType;
            else
                return 0;
            break;
        }
        case OP_INT_CONTROLLER: {
            if (idx == 0)
                return intControllerIntVar;
            else if (idx == 1)
                return intControllerOperator;
            else if (idx == 2)
                return intControllerVal;
            else
                return 0;
            break;
        }
        case OP_COMPARATOR: {
            if (idx == 0)
                return comparatorBoolVar;
            else if (idx == 1)
                return comparatorIntVar;
            else if (idx == 2)
                return comparatorOperator;
            else
                return 0;
            break;
        }
        case OP_BIT_SETTER: {
            if (idx == 0)
                return bitSetterIntVar;
            else if (idx == 1)
                return bitSetterBit;
            else if (idx == 2)
                return bitSetterBoolVar;
            else
                return 0;
            break;
        }
        case OP_OUTPUT: {
            if (idx == 0)
                return outputFormat;
            else if (idx == 1)
                return outputIntVar;
            else
                return 0;
            break;
        }
        default: return 0;
    }
}

void OperationEntity::mousePressEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton)
        emit activate(type);

    QWidget::mousePressEvent(ev);
}

void OperationEntity::mouseDoubleClickEvent(QMouseEvent *ev)
{
    if (ev->button() == Qt::LeftButton) {
        switch (type) {
            case OP_SELECTOR: {
                SelectorDialog *dialog = new SelectorDialog(this, selectorBoolVar, selectorDir);
                if (dialog->getConfirmed()) {
                    selectorBoolVar = dialog->getSelectedBoolVar();
                    selectorDir = dialog->getSelectedDir();

                    QString _pixPath = "://Selector/";
                    _pixPath += (char) (selectorBoolVar + 48);
                    _pixPath += (char) (selectorDir + 48);
                    _pixPath += ".jpeg";
                    setPixPath(_pixPath);
                }
                break;
            }
            case OP_BOOL_CONTROLLER: {
                BoolControllerDialog *dialog = new BoolControllerDialog(this, boolControllerBoolVar, boolControllerType);
                if (dialog->getConfirmed()) {
                    boolControllerBoolVar = dialog->getSelectedBoolVar();
                    boolControllerType = dialog->getSelectedType();

                    QString _pixPath = "://BoolController/";
                    _pixPath += (char) (boolControllerBoolVar + 48);
                    _pixPath += (char) (boolControllerType + 48);
                    _pixPath += ".jpeg";
                    setPixPath(_pixPath);
                }
                break;
            }
            case OP_INT_CONTROLLER: {
                IntControllerDialog *dialog = new IntControllerDialog(this, intControllerIntVar, intControllerOperator, intControllerVal);
                if (dialog->getConfirmed()) {
                    intControllerIntVar = dialog->getSelectedIntVar();
                    intControllerOperator = dialog->getSelectedOperator();
                    intControllerVal = dialog->getSelectedVal();

                    QString _pixPath = "://IntController/";
                    _pixPath += (char) (intControllerIntVar + 48);
                    _pixPath += (char) (intControllerOperator + 48);
                    if (intControllerVal < 10)
                        _pixPath += (char) (intControllerVal + 48);
                    else if (intControllerVal < 16)
                        _pixPath += (char) (intControllerVal + 55);
                    else if (intControllerVal == 16)
                        _pixPath += "I";
                    else if (intControllerVal == 17)
                        _pixPath += "J";
                    else if (intControllerVal == 18)
                        _pixPath += "K";
                    _pixPath += ".jpeg";
                    setPixPath(_pixPath);
                }
                break;
            }
            case OP_COMPARATOR: {
                ComparatorDialog *dialog = new ComparatorDialog(this, comparatorBoolVar, comparatorIntVar, comparatorOperator);
                if (dialog->getConfirmed()) {
                    comparatorBoolVar = dialog->getSelectedBoolVar();
                    comparatorIntVar = dialog->getSelectedIntVar();
                    comparatorOperator = dialog->getSelectedOperator();

                    QString _pixPath = "://Comparator/";
                    _pixPath += (char) (comparatorBoolVar + 48);
                    _pixPath += (char) (comparatorIntVar + 48);
                    _pixPath += (char) (comparatorOperator + 48);
                    _pixPath += ".jpeg";
                    setPixPath(_pixPath);
                }
                break;
            }
            case OP_BIT_SETTER: {
                BitSetterDialog *dialog = new BitSetterDialog(this, bitSetterIntVar, bitSetterBit, bitSetterBoolVar);
                if (dialog->getConfirmed()) {
                    bitSetterIntVar = dialog->getSelectedIntVar();
                    bitSetterBit = dialog->getSelectedBit();
                    bitSetterBoolVar = dialog->getSelectedBoolVar();

                    QString _pixPath = "://BitSetter/";
                    _pixPath += (char) (bitSetterIntVar + 48);
                    _pixPath += (char) (bitSetterBit + 48);
                    _pixPath += (char) (bitSetterBoolVar + 48);
                    _pixPath += ".jpeg";
                    setPixPath(_pixPath);
                }
                break;
            }
            case OP_OUTPUT: {
                OutputDialog *dialog = new OutputDialog(this, outputFormat, outputIntVar);
                if (dialog->getConfirmed()) {
                    outputFormat = dialog->getSelectedFormat();
                    outputIntVar = dialog->getSelectedIntVar();

                    QString _pixPath = "://Output/";
                    _pixPath += (char) (outputFormat + 48);
                    _pixPath += (char) (outputIntVar + 48);
                    _pixPath += ".jpeg";
                    setPixPath(_pixPath);
                }
                break;
            }
        }
    }

    QWidget::mouseDoubleClickEvent(ev);
}

