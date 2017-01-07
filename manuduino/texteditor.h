#ifndef TEXTEDITOR_H
#define TEXTEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QString>
#include "const.h"

struct TextEditor : public QTextEdit {
    Q_OBJECT

public:
    TextEditor (QWidget* parent, QString text);
    ~TextEditor ();
    void clear();

private:
    static const int ROW = TEXT_EDITOR_ROW;
    static const int COL = TEXT_EDITOR_COL;

    QChar textGrid[ROW][COL];

private slots:
    void textChangedHandler();
};

#endif // TEXTEDITOR_H

