#include "src/database/song.h"

Song::Song(qint32 id, QString name, qint32 time, qint32 artist, qint16 trackNumber, qint16 discNumber,
           qint32 album, QObject *parent)
    : QObject(parent), id{id}, name{name.toUtf8()}, time{time}, artist{artist}, trackNumber{trackNumber},
      discNumber{discNumber}, album{album}
{

}

Song::~Song()
{
    emit songDeleted(this);
}

void Song::setId(qint32 id)
{
    this->id = id;
}

void Song::setName(QString name)
{
    this->name = name.toUtf8();
}

void Song::setAlbum(qint32 album)
{
    this->album = album;
}

void Song::setTime(qint32 time)
{
    this->time = time;
}

void Song::setTrackNumber(qint16 trackNumber)
{
    this->trackNumber = trackNumber;
}

void Song::setDiscNumber(qint16 discNumber)
{
    this->discNumber = discNumber;
}

void Song::setArtist(qint32 artist)
{
    this->artist = artist;
}
