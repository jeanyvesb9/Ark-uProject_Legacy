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
#include <cstring>
#include "dmapstatement.h"
#include "../database/library.h"


class DmapClient : public QObject
{
    Q_OBJECT
public:
    DmapClient(QObject *parent = 0);
    ~DmapClient();

    void setServerAddress(QString &host, quint16 &port);
    QString getHost() const { return this->host; }
    quint16 getPort() const { return this->port; }
    void setAuthenticationHeader(QString &username, QString &password);
    QString getAuthenticationHeader() const { return this->authenticationHeader; }
    void setLibrary(Library *lib);

    void login();
    void update();
    void getDatabases();
    void getLibraryContainer();
    void getArtists();
    void getAlbums();
    void getSongs();

private:
    QNetworkAccessManager *manager;
    QString host;
    quint16 port;
    QByteArray authenticationHeader;
    Library *library;

    void toFile(QByteArray &array); //DEBUG
    void toFile(QByteArray &&array); //DEBUG

    QString getBaseUrl();
    QString getSid_formated();
    QString getRid_formated();
    QNetworkRequest getBaseRequest(QString arguments, bool sid = 1, bool rid = 1, bool header = 1);

    quint32 sid;
    quint32 rid;
    quint32 dbid;
    quint32 libid;

    QNetworkReply *loginReply;
    QNetworkReply *updateReply;
    QNetworkReply *databaseReply;
    QNetworkReply *containersReply;
    QNetworkReply *artistsReply;
    QNetworkReply *albumsReply;
    QNetworkReply *songsReply;

    void parseArtists(QByteArray &array);
    void parseAlbums(QByteArray &array);
    void parseSongs(QByteArray &array);

    char *adjustStatementBorder(char *data, const char name[], int len); //ADD EXCEPTION OPTION INTO PARAMETERS
    void printName(char * name);

signals:
    void loginCompleted();
    void updateCompleted();
    void getDatabasesCompleted();
    void getLibraryContainerCompleted();
    void getArtistsCompleted();
    void getAlbumsCompleted();
    void getSongsCompleted();

private slots:
    void loginFinished();
    void updateFinished();
    void getDatabasesFinished();
    void getLibraryContainerFinished();
    void getArtistsFinished();
    void getAlbumsFinished();
    void getSongsFinished();

public slots:

};

#endif // DMAPCLIENT_H
