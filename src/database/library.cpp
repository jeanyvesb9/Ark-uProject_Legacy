#include "src/database/library.h"

Library::Library(QObject *parent) : QObject(parent)
{

}

Library::~Library()
{

}

void Library::setSongList(QHash<quint32, QSharedPointer<Song>> songList, QList<quint32> orderedList)
{
    this->songList = songList;
    this->orderedSongList = orderedList;
}

void Library::setAlbumList(QHash<quint64, QSharedPointer<Album>> albumList, QList<quint64> orderedList)
{
    this->albumList = albumList;
    this->orderedAlbumList = orderedList;
}

void Library::setPlaylistList(QHash<quint32, QSharedPointer<Playlist> > playlistList, QList<quint32> orderedList)
{
    this->playlistList = playlistList;
    this->orderedPlaylistList = orderedList;
}

void Library::setArtistList(QHash<quint64, QSharedPointer<Artist>> artistList, QList<quint64> orderedList)
{
    this->artistList = artistList;
    this->orderedArtistList = orderedList;
}

void Library::addSong(QSharedPointer<Song> song, quint32 place)
{
    this->songList.insert(song->getId(), song);
    this->orderedSongList.insert(place, song->getId());
}

void Library::addAlbum(QSharedPointer<Album> album, quint32 place)
{
    this->albumList.insert(album->getId(), album);
    this->orderedAlbumList.insert(place, album->getId());
}

void Library::addPlaylist(QSharedPointer<Playlist> playlist, quint32 place)
{
    this->playlistList.insert(playlist->getId(), playlist);
    this->orderedPlaylistList.insert(place, playlist->getId());
}

void Library::addArtist(QSharedPointer<Artist> artist, quint32 place)
{
    this->artistList.insert(artist->getId(), artist);
    this->orderedArtistList.insert(place, artist->getId());
}

void Library::removeSong(quint32 id, qint32 place)
{
    this->songList.remove(id);
    if(place == -1)
    {
        for(int i = 0; i < orderedSongList.size(); i++)
        {
            if(orderedSongList.at(i) == id)
            {
                orderedSongList.removeAt(i);
                break;
            }
        }
    }
    else
    {
        orderedSongList.removeAt(place);
    }
}

void Library::removeAlbum(quint64 id, qint32 place)
{
    this->albumList.remove(id);
    if(place == -1)
    {
        for(int i = 0; i < orderedAlbumList.size(); i++)
        {
            if(orderedAlbumList.at(i) == id)
            {
                orderedAlbumList.removeAt(i);
                break;
            }
        }
    }
    else
    {
        orderedAlbumList.removeAt(place);
    }
}

void Library::removePlaylist(quint32 id, qint32 place)
{
    this->playlistList.remove(id);
    if(place == -1)
    {
        for(int i = 0; i < orderedPlaylistList.size(); i++)
        {
            if(orderedPlaylistList.at(i) == id)
            {
                orderedPlaylistList.removeAt(i);
                break;
            }
        }
    }
    else
    {
        orderedPlaylistList.removeAt(place);
    }
}

void Library::removeArtist(quint64 id, qint32 place)
{
    this->artistList.remove(id);
    if(place == -1)
    {
        for(int i = 0; i < orderedArtistList.size(); i++)
        {
            if(orderedArtistList.at(i) == id)
            {
                orderedArtistList.removeAt(i);
                break;
            }
        }
    }
    else
    {
        orderedArtistList.removeAt(place);
    }
}
