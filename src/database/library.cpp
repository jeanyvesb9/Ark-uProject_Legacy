#include "src/database/library.h"

Library::Library(QObject *parent) : QObject(parent)
{

}

Library::~Library()
{

}

void Library::setSongList(QHash<qint32, QSharedPointer<Song>> songList)
{
    this->songList = songList;
}

void Library::setAlbumList(QHash<qint32, QSharedPointer<Album>> albumList)
{
    this->albumList = albumList;
}

void Library::setPlaylistList(QHash<qint32, QSharedPointer<Playlist> > playlistList)
{
    this->playlistList = playlistList;
}

void Library::setArtistList(QHash<qint32, QSharedPointer<Artist>> artistList)
{
    this->artistList = artistList;
}

void Library::addSong(QSharedPointer<Song> song)
{
    this->songList.insert(song->getId(), song);
}

void Library::addAlbum(QSharedPointer<Album> album)
{
    this->albumList.insert(album->getId(), album);
}

void Library::addPlaylist(QSharedPointer<Playlist> playlist)
{
    this->playlistList.insert(playlist->getId(), playlist);
}

void Library::addArtist(QSharedPointer<Artist> artist)
{
    this->artistList.insert(artist->getId(), artist);
}

void Library::removeSong(qint32 id)
{
    this->songList.remove(id);
}

void Library::removeAlbum(qint32 id)
{
    this->albumList.remove(id);
}

void Library::removePlaylist(qint32 id)
{
    this->playlistList.remove(id);
}

void Library::removeArtist(qint32 id)
{
    this->artistList.remove(id);
}
