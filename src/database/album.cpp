#include "src/database/album.h"

Album::Album(qint32 id, QString name, QString albumArtist, QObject *parent)
    :QObject {parent}, id{id}, name{name.toUtf8()}, albumArtist{albumArtist.toUtf8()}
{

}

Album::~Album()
{
    emit albumDeleted(this);
}

void Album::setId(qint32 id)
{
    this->id = id;
}

void Album::setName(QString name)
{
    this->name = name.toUtf8();
}

void Album::setAlbumArtist(QString albumArtist)
{
    this->albumArtist = albumArtist.toUtf8();
}

void Album::setArtwork(QImage image)
{
    this->artwork.reset(&image);
}

void Album::removeArtwork()
{
    this->artwork.reset();
}

void Album::setSongList(QList<qint32> songs)
{
    this->songList = songs;
}

void Album::addSong(qint16 possition, qint32 songNumber)
{
    this->songList.insert(possition, songNumber);
}

void Album::removeSong(qint16 possition)
{
    this->songList.removeAt(possition);
}

void Album::moveSong(qint16 from, qint16 to)
{
    this->songList.move(from, to);
}
