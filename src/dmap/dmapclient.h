#ifndef DMAPCLIENT_H
#define DMAPCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QString>
#include <QByteArray>
#include <QUrl>
#include <QtGlobal>
#include <QFile>
#include "dmapstatement.h"


class DmapClient : public QObject
{
    Q_OBJECT
public:
    explicit DmapClient(QObject *parent = 0);
    explicit DmapClient(QString &host, quint16 &port, QObject *parent = 0);
    ~DmapClient();
    void setServerAddress(QString &host, quint16 &port);
    QString getHost() const { return this->host; }
    quint16 getPort() const { return this->port; }
    void setAuthenticationHeader(QString username, QString password);
    QString getAuthenticationHeader() const { return this->authenticationHeader; }

    void login();
    void update();
    void getDatabases();

private:
    QNetworkAccessManager *manager;
    QString host;
    quint16 port;
    QByteArray authenticationHeader;

    void toFile(QByteArray &array); //DEBUG
    void toFile(QByteArray &&array); //DEBUG

    QString getBaseUrl();
    QString getSid_formated();
    QString getRid_formated();
    QNetworkRequest getBaseRequest(QString arguments, bool sid = 1, bool rid = 1, bool header = 1);

    qint32 sid;
    qint32 rid;
    qint32 dbid;

    QNetworkReply *loginReply;
    QNetworkReply *updateReply;
    QNetworkReply *databaseReply;

signals:
    void loginCompleted();
    void updateCompleted();
    void getDatabasesCompleted();

private slots:
    void loginFinished();
    void updateFinished();
    void getDatabasesFinished();

public slots:

};

#endif // DMAPCLIENT_H
