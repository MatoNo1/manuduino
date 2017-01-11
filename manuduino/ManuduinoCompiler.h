#ifndef MANUDUINOCOMPILER_H
#define MANUDUINOCOMPILER_H

class QTextStream;
class QString;

class ManuduinoCompiler
{
protected:
    static ManuduinoCompiler *instance;
    ManuduinoCompiler();
public:
    static ManuduinoCompiler* getInstance();
    void compile(QTextStream &outputStream);
    void compileText(QTextStream &outputStream, const QString& text);
};

#endif // MANUDUINOCOMPILER_H
