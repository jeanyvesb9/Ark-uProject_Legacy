#include "src/dmap/dmapclient.h"

DmapClient::DmapClient(QObject *parent) : QObject(parent),
    manager{new QNetworkAccessManager(this)}
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

void DmapClient::setAuthenticationHeader(QString &username, QString &password)
{
    authenticationHeader.clear();
    authenticationHeader.append(username);
    authenticationHeader.append(':');
    authenticationHeader.append(password);
    authenticationHeader = authenticationHeader.toBase64();
    authenticationHeader.insert(0, "Authentication: Basic ");
}

void DmapClient::setLibrary(Library *lib)
{
    library = lib;
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

void DmapClient::printName(char *name)
{
    qDebug() <<name[0] <<name[1] <<name[2] <<name[3];
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

void DmapClient::getLibraryContainer()
{
    containersReply = manager->get(getBaseRequest("/databases/" + QString::number(dbid) +
                                   "/containers?meta=dmap.itemname,dmap.itemid," +
                                   "dmap.persistentid,daap.baseplaylist," +
                                   "dmap.parentcontainerid,daap.songcontentdescription," +
                                   "daap.songtrackcount"));
    connect(containersReply, &QNetworkReply::finished, this, &DmapClient::getLibraryContainerFinished);
}

void DmapClient::getArtists()
{
    artistsReply = manager->get(getBaseRequest("/databases/" + QString::number(dbid) + "/groups?" +
                                "meta=dmap.itemname,dmap.itemid,dmap.persistentid" +
                                "&type=music&group-type=artists&sort=name"));
    connect(artistsReply, &QNetworkReply::finished, this, &DmapClient::getArtistsFinished);
}

void DmapClient::getAlbums()
{
    albumsReply = manager->get(getBaseRequest("/databases/" + QString::number(dbid) + "/groups?" +
                               "meta=dmap.itemname,dmap.itemid,dmap.persistentid," +
                               "daap.songartistid" +
                               "&type=music&group-type=album&sort=name"));
    connect(albumsReply, &QNetworkReply::finished, this, &DmapClient::getAlbumsFinished);
}

void DmapClient::getSongs()
{
    songsReply = manager->get(getBaseRequest("/databases/" + QString::number(dbid) + "/containers/" +
                              QString::number(libid) + "/items?meta=dmap.itemid,dmap.itemname," +
                              "daap.songalbumid,daap.songartist,daap.songalbumartist,daap.songdiscnumber," +
                              "daap.songtime,daap.songtracknumber&type=music&sort=name"));
    connect(songsReply, &QNetworkReply::finished, this, &DmapClient::getSongsFinished);
}

void DmapClient::toFile(QByteArray &array)
{
    QFile file("C:/prog/data.txt");
    if(file.exists())
    {
        file.remove();
    }
    file.open(QIODevice::ReadWrite);
    QTextStream ts(&file);
    ts << array;
}

void DmapClient::toFile(QByteArray &&array)
{
    QFile file("C:/prog/data.txt");
    if(file.exists())
    {
        file.remove();
    }
    file.open(QIODevice::ReadWrite);
    QTextStream ts(&file);
    ts << array;
}

void DmapClient::loginFinished()
{
    QByteArray array = loginReply->readAll();

    DmapStatement statement(array.data(), array.data() + (array.size() - 1), 1);

    QString name("mlid");
    QString inside("mlog");
    DmapStatement *session = statement.findUniqueValue(name, inside);

    sid = DmapStatement::byteToInt<quint32>(session->getData());

    loginReply->deleteLater();
    emit loginCompleted();
}

void DmapClient::updateFinished()
{
    QByteArray array = updateReply->readAll();

    DmapStatement statement(array.data(), array.data() + (array.size() - 1), 1);

    QString name("musr");
    QString inside("mupd");
    DmapStatement *session = statement.findUniqueValue(name, inside);

    rid = DmapStatement::byteToInt<quint32>(session->getData());

    updateReply->deleteLater();
    emit updateCompleted();
}

void DmapClient::getDatabasesFinished()
{
    QByteArray array = databaseReply->readAll();

    DmapStatement statement(array.data(), array.data() + (array.size() - 1), 1);

    QString name("miid");
    QString inside("mlit");
    QString insideRef("minm");
    QByteArray dataArray = libraryName.toUtf8();
    DmapStatement *session = statement.findValue(name, inside, insideRef, dataArray);

    dbid = DmapStatement::byteToInt<quint32>(session->getData());

    databaseReply->deleteLater();
    emit getDatabasesCompleted();
}

void DmapClient::getLibraryContainerFinished()
{
    QByteArray array = containersReply->readAll();

    DmapStatement statement(array.data(), array.data() + (array.size() - 1), 1);

    QString name("miid");
    QString inside("mlit");
    QString insideRef("abpl");
    char c = 0x01;
    QByteArray dataArray(1, c);
    DmapStatement *number = statement.findValue(name, inside, insideRef, dataArray);

    libid  = DmapStatement::byteToInt<quint32>(number->getData());
    containersReply->deleteLater();
    emit getLibraryContainerCompleted();
}

char *DmapClient::adjustStatementBorder(char *data, const char name[], int len)
{
    char *originalData = data;

    if(std::memcmp(data, name, len))
    {
        for(int i = 4; i > 5; i--)
        {
            data--;
            if(!std::memcmp(data, name, len))
            {
                return data;
            }
        }

        data = originalData;
        for(int i = 0; i < 5; i++)
        {
            data++;
            if(!std::memcmp(data, name, len))
            {
                return data;
            }
        }

        //THROW EXCEPTION
    }

    return originalData;
}

void DmapClient::getArtistsFinished()
{
    QByteArray array = artistsReply->readAll();
    parseArtists(array);

    artistsReply->deleteLater();
    emit getArtistsCompleted();
}

void DmapClient::parseArtists(QByteArray &array)
{
    char *data = array.data();
    char *end = data + (array.size() - 1);

    for(;std::memcmp(data, "mlit", 4); data++);

    for(int place = 0; data < end; place++)
    {
        data = adjustStatementBorder(data, "mlit", 4);
        data += 8;

        data = adjustStatementBorder(data, "minm", 4);
        data += 4;
        int nameSize = DmapStatement::byteToInt<quint32>(data);
        data += 4;
        QByteArray name(data, nameSize);

        data += nameSize;
        data = adjustStatementBorder(data, "mper", 4);
        data += 8;
        quint64 persistentId = DmapStatement::byteToInt<quint64>(data);

        data += 20;
        data = adjustStatementBorder(data, "miid", 4);
        data += 8;
        quint32 groupId = DmapStatement::byteToInt<quint32>(data);

        library->addArtist(QSharedPointer<Artist>(new Artist(persistentId, groupId, name)), place);

        data += 4;
    }
}

void DmapClient::getAlbumsFinished()
{
    QByteArray array = albumsReply->readAll();
    parseAlbums(array);

    albumsReply->deleteLater();
    emit getAlbumsCompleted();
}

void DmapClient::parseAlbums(QByteArray &array)
{
    char *data = array.data();
    char *end = data + (array.size() - 1);

    for(;std::memcmp(data, "mlit", 4); data++);

    for(int place = 0; data < end; place++)
    {
        data = adjustStatementBorder(data, "mlit", 4);
        data += 8;

        data = adjustStatementBorder(data, "minm", 4);
        data += 4;
        int nameSize = DmapStatement::byteToInt<quint32>(data);
        data += 4;
        QByteArray name(data, nameSize);

        data += nameSize;
        data = adjustStatementBorder(data, "mper", 4);
        data += 8;
        quint64 persistentId = DmapStatement::byteToInt<quint64>(data);

        data += 8;
        data = adjustStatementBorder(data, "asri", 4);
        data += 8;
        quint64 artistId = DmapStatement::byteToInt<quint64>(data);

        for(;std::memcmp(data, "miid", 4); data++);
        data += 8;
        quint32 groupId = DmapStatement::byteToInt<quint32>(data);

        library->addAlbum(QSharedPointer<Album>(new Album(persistentId, groupId, name, artistId)), place);
        library->getArtist(artistId).lock()->appendAlbum(persistentId);

        data += 4;
    }
}

void DmapClient::getSongsFinished()
{
    QByteArray array = songsReply->readAll();
//    toFile(array);
    parseSongs(array);

    songsReply->deleteLater();
    emit getSongsCompleted();
}

void DmapClient::parseSongs(QByteArray &array)
{
    char *data = array.data();
    char *end = data + (array.size() - 1);

    for(;std::memcmp(data, "mlit", 4); data++);

    for(int place = 0; data < end; place++)
    {
        data = adjustStatementBorder(data, "mlit", 4);
        data += 8;

        data = adjustStatementBorder(data, "miid", 4);
        data += 8;
        quint32 id = DmapStatement::byteToInt<quint32>(data);

        data = adjustStatementBorder(data, "minm", 4);
        data += 4;
        int nameSize = DmapStatement::byteToInt<quint32>(data);
        data += 4;
        QByteArray name(data, nameSize);

        data += nameSize;
        data = adjustStatementBorder(data, "asai", 4);
        data += 8;
        quint64 albumId = DmapStatement::byteToInt<quint64>(data);

        data += 8;
        data = adjustStatementBorder(data, "asar", 4);
        data += 4;
        int songArtistSize = DmapStatement::byteToInt<quint32>(data);
        data += 4;
        QByteArray songArtist(data, songArtistSize);

        data += songArtistSize;
        data = adjustStatementBorder(data, "asaa", 4);
        data += 4;
        int songAlbumArtistSize = DmapStatement::byteToInt<quint32>(data);
        data += 4;
        QByteArray songAlbumArtist(data, songAlbumArtistSize);

        data += songAlbumArtistSize;
        data = adjustStatementBorder(data, "as", 2);

        quint16 discNumber = 1;
        if(!std::memcmp(data, "asdn", 4))
        {
            data += 8;
            discNumber = DmapStatement::byteToInt<quint16>(data);
            data += 2;
            data = adjustStatementBorder(data, "astm", 4);
        }

        data += 8;
        quint32 songTime = DmapStatement::byteToInt<quint32>(data);

        data += 4;
        quint16 trackNumber;
        if(!std::memcmp(data, "astn", 4))
        {
            data += 8;
            trackNumber = DmapStatement::byteToInt<quint16>(data);
            data += 2;
        }
        else
        {
            trackNumber = library->getAlbum(albumId).lock()->getSongListLenght() + 1;
        }

        if(songArtist.size() != songAlbumArtist.size() || std::memcmp(songArtist, songAlbumArtist, songArtist.size()))
            library->addSong(QSharedPointer<Song>(new Song(id, name, songTime, trackNumber, discNumber, albumId, 1, songArtist)), place);
        else
            library->addSong(QSharedPointer<Song>(new Song(id, name, songTime, trackNumber, discNumber, albumId)), place);
        library->getAlbum(albumId).lock()->addSong(discNumber, trackNumber, id);

    }

    auto artistPtr = library->getArtistList();
    auto artistOrdered = library->getOrderedArtistList();
    auto albumPtr = library->getAlbumList();
    auto songPtr = library->getSongList();

    for(auto artist : *artistOrdered)
    {
        qDebug() << artistPtr->value(artist)->getId() << " : " << artistPtr->value(artist)->getName();

        for(auto album : *(artistPtr->value(artist)->getAlbumList()))
        {
            qDebug() << "\t" <<albumPtr->value(album)->getId() << " : " << albumPtr->value(album)->getName() <<" - " << albumPtr->value(album)->getSongListLenght();

            for(auto cd : *(albumPtr->value(album)->getSongList()))
            {
                qDebug() <<"\t\tCD";
                for(auto song : cd)
                {
                    qDebug() << "\t\t" <<songPtr->value(song)->getId() << " : " << songPtr->value(song)->getName() <<" - " << songPtr->value(song)->getDiscNumber() <<" - " << songPtr->value(song)->getTrackNumber();
                }
            }
        }
    }
}
