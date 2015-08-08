#ifndef SONGVIEWMODEL_H
#define SONGVIEWMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QtGlobal>
#include <QPointer>
#include "database/library.h"

class SongViewModel : public QAbstractListModel
{
    Q_OBJECT
public:
    SongViewModel(QObject *parent = 0);

    enum SongRoles {
        IDRole = Qt::UserRole + 1, NameRole, AlbumIdRole, AlbumNameRole, ArtistRole
    };

    void addSong();

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<quint32>songId;
    QSharedPointer<Library> library;
};

#endif // SONGVIEWMODEL_H
