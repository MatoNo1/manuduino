#include <QFile>
#include <QTextStream>
#include <QProcessEnvironment>
#include <QMessageBox>
#include "RemoteManager.h"

RemoteManager *RemoteManager::instance = nullptr;

void RemoteManager::uploadCode(const QString &codeName, const QString &codeContent)
{
    QString localFileName = "/tmp/" + codeName + ".pde";
    QString remoteFileName = "/home/alarm/" + codeName + "/" + codeName + ".pde";
    QFile localTemporaryFile(localFileName);
    localTemporaryFile.open(QIODevice::WriteOnly);
    QTextStream text(&localTemporaryFile);
    text << codeContent;
    localTemporaryFile.close();
    auto environment = QProcessEnvironment::systemEnvironment();
    environment.insert("SSH_ASKPASS", "ksshaskpass");
    process.setEnvironment(environment.toStringList());
    QString command1 = "ssh alarm@183.172.217.2 mkdir -p /home/alarm/" + codeName;
    QString command2 = "scp " + localFileName + " alarm@183.172.217.2:" + remoteFileName;
    process.start("setsid sh -c \"" + command1 + " && " + command2 + "\"");
    connect(&process, SIGNAL(finished(int)), this, SLOT(onProcessFinished(int)));
}

void RemoteManager::executeCode(const QString &codeName)
{
    process.terminate();
    process.reset();
    auto environment = QProcessEnvironment::systemEnvironment();
    environment.insert("SSH_ASKPASS", "ksshaskpass");
    process.setEnvironment(environment.toStringList());
    process.start("setsid ssh alarm@183.172.217.2 DISPLAY=:0.0 screen -d -m "
                  "/home/alarm/processing-3.2.3/processing-java "
                  "--sketch=/home/alarm/" + codeName + " --run");
    connect(&process, SIGNAL(finished(int)), this, SLOT(onProcessFinished(int)));
}

int RemoteManager::onProcessFinished(int exitCode)
{
    process.terminate();
    process.reset();
    disconnect(&process);
    //TODO : Send signal
    QMessageBox::information(nullptr, "Done", "Done");
}

RemoteManager::RemoteManager()
{

}

RemoteManager *RemoteManager::getInstance()
{
    if(instance == nullptr)
    {
        instance = new RemoteManager();
    }
    return instance;
}
