#ifndef LIBRARY_H
#define LIBRARY_H

#include <QObject>
#include <QtGlobal>
#include <QSharedPointer>
#include <QHash>
#include "src/database/song.h"
#include "src/database/album.h"
#include "src/database/playlist.h"
#include "src/database/artist.h"

class Library : public QObject
{
    Q_OBJECT
public:
    explicit Library(QObject *parent = 0);
    ~Library();

    void setSongList(QHash<quint32, QSharedPointer<Song>> songList, QList<quint32> orderedList);
    const QHash<quint32, QSharedPointer<Song>> *getSongList() const { return &songList; }
    const QList<quint32> *getOrderedSongList() const { return &orderedSongList; }

    void setAlbumList(QHash<quint64, QSharedPointer<Album>> albumList, QList<quint64> orderedList);
    const QHash<quint64, QSharedPointer<Album>> *getAlbumList() const { return &albumList; }
    const QList<quint64> *getOrderedAlbumList() const { return &orderedAlbumList; }

    void setPlaylistList(QHash<quint32, QSharedPointer<Playlist>> playlistList, QList<quint32> orderedList);
    const QHash<quint32, QSharedPointer<Playlist>> *getPlaylistList() const { return &playlistList; }
    const QList<quint32> *getOrderedPlaylistList() const { return &orderedPlaylistList; }

    void setArtistList(QHash<quint64, QSharedPointer<Artist>> artistList, QList<quint64> orderedList);
    const QHash<quint64, QSharedPointer<Artist>> *getArtistList() const { return &artistList; }
    const QList<quint64> *getOrderedArtistList() const { return &orderedArtistList; }

    void addSong(QSharedPointer<Song> song, quint32 place);
    void addAlbum(QSharedPointer<Album> album, quint32 place);
    void addPlaylist(QSharedPointer<Playlist> playlist, quint32 place);
    void addArtist(QSharedPointer<Artist> artist, quint32 place);

    void removeSong(quint32 id, qint32 place = -1);
    void removeAlbum(quint64 id, qint32 place = -1);
    void removePlaylist(quint32 id, qint32 place = -1);
    void removeArtist(quint64 id, qint32 place = -1);

    QWeakPointer<Song> getSong(quint32 songId) { return songList.value(songId).toWeakRef(); }
    quint32 getSongAtPlace(quint32 place) const { return orderedSongList.at(place); }
    QWeakPointer<Album> getAlbum(quint64 albumId) { return albumList.value(albumId).toWeakRef(); }
    quint32 getAlbumAtPlace(quint32 place) const { return orderedAlbumList.at(place); }
    QWeakPointer<Playlist> getPlaylist(quint32 playlistId) { return playlistList.value(playlistId).toWeakRef(); }
    quint32 getPlaylistAtPlace(quint32 place) const { return orderedPlaylistList.at(place); }
    QWeakPointer<Artist> getArtist(quint64 artistId) { return artistList.value(artistId).toWeakRef(); }
    quint32 getArtistAtPlace(quint32 place) const { return orderedArtistList.at(place); }

private:
    QHash<quint32, QSharedPointer<Song>> songList;
    QList<quint32> orderedSongList;
    QHash<quint64, QSharedPointer<Album>> albumList;
    QList<quint64> orderedAlbumList;
    QHash<quint32, QSharedPointer<Playlist>> playlistList;
    QList<quint32> orderedPlaylistList;
    QHash<quint64, QSharedPointer<Artist>> artistList;
    QList<quint64> orderedArtistList;

signals:
    void updated();

public slots:

};

#endif // LIBRARY_H
