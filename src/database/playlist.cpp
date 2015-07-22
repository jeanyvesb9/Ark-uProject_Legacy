#include "src/database/playlist.h"

Playlist::Playlist(qint32 id, QString name, QObject *parent)
    :QObject(parent), id{id}, name{name.toUtf8()}
{

}

Playlist::~Playlist()
{
    emit playlistDeleted(this);
}

void Playlist::setId(qint32 id)
{
    this->id = id;
}

void Playlist::setName(QString name)
{
    this->name = name.toUtf8();
}

void Playlist::setSongList(QList<qint32> songs)
{
    this->songList = songs;
}

void Playlist::addSong(qint16 possition, qint32 song)
{
    this->songList.insert(possition, song);
}

void Playlist::removeSong(qint16 possition)
{
    return this->songList.removeAt(possition);
}

void Playlist::moveSong(qint16 from, qint16 to)
{
    this->songList.move(from, to);
}
