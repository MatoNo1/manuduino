#ifndef REMOTEMANAGER_H
#define REMOTEMANAGER_H

#include <QProcess>

class QString;

class RemoteManager : public QObject
{
    Q_OBJECT
protected:
    static RemoteManager *instance;
    RemoteManager();
protected:
    QProcess process;
    int currentStep = 0;
public:
    static RemoteManager *getInstance();
    void uploadCode(const QString& codeName, const QString& codeContent);
    void executeCode(const QString& codeName);
public slots:
    int onProcessFinished(int exitCode);
};

#endif // REMOTEMANAGER_H
