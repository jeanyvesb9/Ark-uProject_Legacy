#ifndef ALBUM_H
#define ALBUM_H

#include <QObject>
#include <QtDebug>
#include <QString>
#include <QSharedPointer>
#include <QByteArray>
#include <QtGlobal>
#include <QMap>
#include <QImage>

class Album : public QObject
{
    Q_OBJECT
public:
    Album(quint64 id, quint32 groupId, QByteArray name, quint64 albumArtist, QObject *parent = 0);
    ~Album();

    void setId(quint64 id);
    quint64 getId() const { return id; }

    void setGroupId(quint32 groupId);
    quint32 getGroupId() const { return groupId; }

    void setName(QString name);
    QString getName() const { return QString::fromUtf8(name); }

    void setAlbumArtist(quint64 albumArtist);
    quint64 getAlbumArtist() const { return albumArtist; }

    void setSongList(QMap<quint16, QMap<quint16, quint32> > songs);
    const QMap<quint16, QMap<quint16, quint32> > *getSongList() const { return &songList; }
    quint16 getSongListLenght() const;
    void addSong(quint16 disc, quint16 possition, quint32 songNumber);
    void removeSong(quint16 disc, quint16 possition);
    void moveSong(quint16 discFrom, quint16 from, quint16 discTo, quint16 to);

    void setAlbumLenght(quint32 lenght);
    quint32 getAlbumLenght() const { return albumLenght; }
    void reduceAlbumLenght(quint32 lenght) { this->albumLenght -= lenght; }
    void increaseAlbumLenght(quint32 lenght) { this->albumLenght += lenght; }

    bool operator==(const Album &a) const { return this->id == a.id; }
    bool operator!=(const Album &a) const { return !( *this == a); }
    
private:
    quint64 id;
    quint32 groupId;
    QByteArray name;
    quint64 albumArtist;
    quint32 albumLenght;
    QMap<quint16, QMap<quint16, quint32> > songList;

signals:
    void albumDeleted(Album *a);

public slots:
};

#endif // ALBUM_H
