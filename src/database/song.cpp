#include "src/database/song.h"

Song::Song(quint32 id, QByteArray name, quint32 time, quint16 trackNumber, quint16 discNumber,
           quint64 album, bool diffArtist, QByteArray artist, QObject *parent)
    : QObject(parent), id{id}, name{name}, time{time}, trackNumber{trackNumber},
      discNumber{discNumber}, album{album}
{
    if(diffArtist)
    {
        this->artistName = new QByteArray(artist);
    }
}

Song::~Song()
{
    if(artistName)
    {
        delete artistName;
    }
    emit songDeleted(this);
}

void Song::setId(quint32 id)
{
    this->id = id;
}

void Song::setName(QString name)
{
    this->name = name.toUtf8();
}

void Song::setAlbum(quint64 album)
{
    this->album = album;
}

void Song::setTime(quint32 time)
{
    this->time = time;
}

void Song::setTrackNumber(quint16 trackNumber)
{
    this->trackNumber = trackNumber;
}

void Song::setDiscNumber(quint16 discNumber)
{
    this->discNumber = discNumber;
}

void Song::setDefaultArtist()
{
    delete this->artistName;
}

QString Song::getArtist() const
{
    if(this->artistName)
    {
        return QString::fromUtf8(*(this->artistName));
    }
    return QString("NULL");
}

void Song::setArtist(QString artist)
{
    if(this->artistName)
    {
        this->artistName->clear();
        *(this->artistName) = artist.toUtf8();
    }
}
