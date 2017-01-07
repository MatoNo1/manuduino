#include "texteditor.h"

TextEditor::TextEditor(QWidget* parent, QString text):
    QTextEdit(parent)
{
    setPlainText(text);
}

TextEditor::~TextEditor()
{
    setPlainText("");
    for (int i=0; i<ROW; ++i)
        for (int j=0; j<COL; ++j)
            textGrid[i][j] = 0;
}

void TextEditor::clear()
{
    setPlainText("");
}

void TextEditor::textChangedHandler()
{
    QString curText = toPlainText();
    int len = curText.length();
    Pos p(0, 0);
    p.setMaxY(COL);

    QChar ch;
    for (int i=0; i<len && p.x<ROW; ++i) {
        ch = curText[i];
        if (ch == 13 || ch == 10) {
            for (; p.y<COL-1; ++p) textGrid[p.x][p.y] = 0;
            ++p;
        } else {
            textGrid[p.x][p.y] = ch;
            ++p;
        }
    }

    for (; p.x<ROW; ++p)
        textGrid[p.x][p.y] = 0;
}
