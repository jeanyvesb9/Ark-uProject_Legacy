#ifndef APPLICATIONLOGIC_H
#define APPLICATIONLOGIC_H

#include <QObject>
#include <QtGlobal>
#include "dmap/dmapclient.h"
#include "database/library.h"

class ApplicationLogic : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationLogic(QObject *parent = 0);
    ~ApplicationLogic();

    void setClient(QString &host, quint16 &port, QString &username, QString &password);
    void setClientAddress(QString &host, quint16 &port);
    QString getClientHost() const { return client->getHost(); }
    quint16 getClientPort() const { return client->getPort(); }
    void executeInitSequence();

private:
    DmapClient *client;
    Library *library;

signals:
    void initSequenceCompleted();
public slots:

private slots:
    void loginFinished();
    void updateFinished();
    void getDatabasesFinished();
    void getLibraryContainerFinished();
    void getArtistsFinished();
    void getAlbumsFinished();
    void getSongsFinished();

};

#endif // APPLICATIONLOGIC_H
