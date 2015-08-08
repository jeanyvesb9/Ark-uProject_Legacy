#include "songviewmodel.h"

SongViewModel::SongViewModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

QHash<int, QByteArray> SongViewModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IDRole] = "id";
    roles[NameRole] = "name";
    roles[AlbumIdRole] = "albumId";
    roles[AlbumNameRole] = "albumName";
    roles[ArtistRole] = "artistName";

    return roles;
}
