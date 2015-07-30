#include "src/dmap/dmapclient.h"

DmapClient::DmapClient(QObject *parent) : QObject(parent),
    manager{new QNetworkAccessManager(this)}
{

}

DmapClient::DmapClient(QString &host, quint16 &port, QObject *parent) : QObject(parent),
    manager{new QNetworkAccessManager(this)}, host{host}, port{port}
{

}

DmapClient::~DmapClient()
{
    manager->deleteLater();
}

void DmapClient::setServerAddress(QString &host, quint16 &port)
{
    this->host = host;
    this->port = port;
}

void DmapClient::setAuthenticationHeader(QString username, QString password)
{
    authenticationHeader.clear();
    authenticationHeader.append(username);
    authenticationHeader.append(':');
    authenticationHeader.append(password);
    authenticationHeader = authenticationHeader.toBase64();
    authenticationHeader.insert(0, "Authentication: Basic ");
}

QString DmapClient::getBaseUrl()
{
    QString url("http://");
    url.append(host);
    url.append(':').append(QString::number(port));
    return url;
}

QString DmapClient::getSid_formated()
{
    return QString("session-id=" + QString::number(sid));
}

QString DmapClient::getRid_formated()
{
    return QString("revision-id=" + QString::number(rid));
}

QNetworkRequest DmapClient::getBaseRequest(QString arguments, bool sid, bool rid, bool header)
{
    QString url = getBaseUrl();
    url.append(arguments);
    if (sid)
    {
        if(!url.endsWith('?'))
        {
            url.append('&');
        }
        url.append(getSid_formated());
    }
    if (rid)
    {
        if(!url.endsWith('?'))
        {
            url.append('&');
        }
        url.append(getRid_formated());
    }
    QNetworkRequest request;
    if (header)
    {
        request.setRawHeader("Authorization", authenticationHeader);
    }
    request.setUrl(QUrl(url));
    return request;
}

void DmapClient::login()
{
    loginReply = manager->get(getBaseRequest("/login", 0, 0, 1));
    connect(loginReply, &QNetworkReply::finished, this, &DmapClient::loginFinished);
}

void DmapClient::update()
{
    updateReply = manager->get(getBaseRequest("/update?", 1, 0));
    connect(updateReply, &QNetworkReply::finished, this, &DmapClient::updateFinished);
}

void DmapClient::getDatabases()
{
    databaseReply = manager->get(getBaseRequest("/databases?"));
    connect(databaseReply, &QNetworkReply::finished, this, &DmapClient::getDatabasesFinished);
}

void DmapClient::toFile(QByteArray &array)
{
    QFile file("C:/prog/data.txt");
    file.open(QIODevice::ReadWrite);
    QTextStream ts(&file);
    ts << array;
}

void DmapClient::toFile(QByteArray &&array)
{
    QFile file("C:/prog/data.txt");
    file.open(QIODevice::ReadWrite);
    QTextStream ts(&file);
    ts << array;
}

void DmapClient::loginFinished()
{
    //sid = DmapStatement::byteToInt<quint32>(loginReply->readAll().mid(28));
    QByteArray array = loginReply->readAll();
    qDebug() << DmapStatement::byteToInt<quint32>(array.mid(28));


    DmapStatement statement()

    loginReply->deleteLater();
    emit loginCompleted();
}

void DmapClient::updateFinished()
{
    rid = DmapStatement::byteToInt<quint32>(updateReply->readAll().mid(28));
    updateReply->deleteLater();
    emit updateCompleted();
}

void DmapClient::getDatabasesFinished()
{
    QByteArray array = databaseReply->readAll();

    //toFile(array);
    databaseReply->deleteLater();
    emit getDatabasesCompleted();
}
