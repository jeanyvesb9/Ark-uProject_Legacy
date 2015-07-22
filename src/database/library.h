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

    void setSongList(QHash<qint32, QSharedPointer<Song>> songList);
    const QHash<qint32, QSharedPointer<Song>> *getSongList() const { return &songList; }

    void setAlbumList(QHash<qint32, QSharedPointer<Album>> albumList);
    const QHash<qint32, QSharedPointer<Album>> *getAlbumList() const { return &albumList; }

    void setPlaylistList(QHash<qint32, QSharedPointer<Playlist>> playlistList);
    const QHash<qint32, QSharedPointer<Playlist>> *getPlaylistList() const { return &playlistList; }

    void setArtistList(QHash<qint32, QSharedPointer<Artist>> artistList);
    const QHash<qint32, QSharedPointer<Artist>> *getArtistList() const { return &artistList; }

    void addSong(QSharedPointer<Song> song);
    void addAlbum(QSharedPointer<Album> album);
    void addPlaylist(QSharedPointer<Playlist> playlist);
    void addArtist(QSharedPointer<Artist> artist);

    void removeSong(qint32 id);
    void removeAlbum(qint32 id);
    void removePlaylist(qint32 id);
    void removeArtist(qint32 id);

    QWeakPointer<Song> getSong(qint32 songId) const { return songList.value(songId).toWeakRef(); }
    QWeakPointer<Album> getAlbum(qint32 albumId) const { return albumList.value(albumId).toWeakRef(); }
    QWeakPointer<Playlist> getPlaylist(qint32 playlistId) const { return playlistList.value(playlistId).toWeakRef(); }
    QWeakPointer<Artist> getArtist(qint32 artistId) const { return artistList.value(artistId).toWeakRef(); }

private:
    QHash<qint32, QSharedPointer<Song>> songList;
    QHash<qint32, QSharedPointer<Album>> albumList;
    QHash<qint32, QSharedPointer<Playlist>> playlistList;
    QHash<qint32, QSharedPointer<Artist>> artistList;

signals:
    void updated();

public slots:

};

#endif // LIBRARY_H
