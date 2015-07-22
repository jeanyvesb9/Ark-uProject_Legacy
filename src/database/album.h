#ifndef ALBUM_H
#define ALBUM_H

#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <QByteArray>
#include <QtGlobal>
#include <QList>
#include <QImage>
#include "src/database/song.h"

class Album : public QObject
{
    Q_OBJECT
public:
    explicit Album(qint32 id, QString name, QString albumArtist, QObject *parent = 0);
    ~Album();

    void setId(qint32 id);
    qint32 getId() const { return id; }

    void setName(QString name);
    QString getName() const { return QString::fromUtf8(name); }

    void setAlbumArtist(QString albumArtist);
    QString getAlbumArtist() const { return QString::fromUtf8(albumArtist); }

    void setArtwork(QImage image);
    const QImage* getArtwork() const { return artwork.data(); }
    void removeArtwork();

    void setSongList(QList<qint32> songs);
    const QList<qint32> *getSongList() const { return &songList; }
    void addSong(qint16 possition, qint32 songNumber);
    void removeSong(qint16 possition);
    void moveSong(qint16 from, qint16 to);

    bool operator==(const Album &a) const { return this->id == a.id; }
    bool operator!=(const Album &a) const { return !( *this == a); }

private:
    qint32 id;
    QByteArray name;
    QByteArray albumArtist;
    QList<qint32> songList;
    QSharedPointer<QImage> artwork;

signals:
    void albumDeleted(Album *a);

public slots:
};

#endif // ALBUM_H
