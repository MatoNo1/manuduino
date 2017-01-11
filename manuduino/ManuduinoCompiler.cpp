#include <QTextStream>
#include "ManuduinoCompiler.h"

ManuduinoCompiler *ManuduinoCompiler::instance = nullptr;

ManuduinoCompiler::ManuduinoCompiler()
{

}

ManuduinoCompiler *ManuduinoCompiler::getInstance()
{
    if(instance == nullptr)
    {
        instance = new ManuduinoCompiler();
    }
    return instance;
}

void ManuduinoCompiler::compile(QTextStream &outputStream)
{
    outputStream << "fullScreen();\n";
    outputStream << "background(255);\n";
    outputStream << "stroke(0);\n";
    outputStream << "fill(255, 0, 0);\n";
    outputStream << "rect(50, 50, 200, 200);\n";
}

void ManuduinoCompiler::compileText(QTextStream &outputStream, const QString& text)
{
    outputStream << "fullScreen();\n";
    outputStream << "background(255);\n";
    outputStream << "textSize(60);\n";
    outputStream << "fill(0);\n";
    outputStream << "text(\"" + text + "\", 100, 100);";
}
