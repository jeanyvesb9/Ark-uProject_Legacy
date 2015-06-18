#include <QApplication>
#include <QDir>
#include <QDebug>
#include <QQmlApplicationEngine>

void copyFolders(const QString sourceDirec, const QStringList sourceFolders, const QString destBaseFolder)
{
    foreach(QString sourceFolder, sourceFolders)
    {
        sourceFolder = sourceDirec + sourceFolder + "/";
        QDir sourceDir(sourceFolder);
        if(!sourceDir.exists())
            return;
        QStringList source= sourceFolder.split('/');
        QString destFolder = destBaseFolder + "/" + source.at(source.size() - 2);
        QDir destDir(destFolder);
        if(destDir.exists())
        {
            destDir.removeRecursively();
        }
        destDir.mkdir(destFolder);
        QStringList files = sourceDir.entryList(QDir::Files);
        for(int i = 0; i< files.count(); i++)
        {
            QString srcName = sourceFolder + "/" + files[i];
            QString destName = destFolder + "/" + files[i];
            QFile::copy(srcName, destName);
        }
        files.clear();
        files = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
        for(int i = 0; i< files.count(); i++)
        {
            QString srcName = sourceFolder + "/" + files[i];
            QString destName = destFolder + "/" + files[i];
            copyFolders(sourceDirec, QStringList(srcName), destName);
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QStringList sourceFolders = {"qml", "images"};
    copyFolders("C:/prog/QtQML/Interface_1/Interface/", sourceFolders, app.applicationDirPath());

    QQmlApplicationEngine engine;
    engine.load(app.applicationDirPath().append("/qml/main.qml"));

    return app.exec();
}
