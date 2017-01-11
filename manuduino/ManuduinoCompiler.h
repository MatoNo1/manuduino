#ifndef MANUDUINOCOMPILER_H
#define MANUDUINOCOMPILER_H

class QTextStream;

class ManuduinoCompiler
{
protected:
    static ManuduinoCompiler *instance;
    ManuduinoCompiler();
public:
    static ManuduinoCompiler* getInstance();
    void compile(QTextStream &outputStream);
};

#endif // MANUDUINOCOMPILER_H
