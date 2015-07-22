#ifndef SONG_H
#define SONG_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QtGlobal>
#include "src/global.h"

class Song : public QObject
{
    Q_OBJECT
public:
    explicit Song(qint32 id, QString name, qint32 time, qint32 artist,
                  qint16 trackNumber = 1, qint16 discNumber = 1, qint32 album = 0, QObject *parent = 0);
    ~Song();

    void setId(qint32 id);
    qint32 getId() const { return id; }
    void setName(QString name);
    QString getName() const { return QString::fromUtf8(name); }
    void setAlbum(qint32 album);
    qint32 getAlbum() const { return this->album; }
    void setTime(qint32 time);
    qint32 getTime() const { return time; }
    void setTrackNumber(qint16 trackNumber);
    qint16 getTrackNumber() const { return trackNumber; }
    void setDiscNumber(qint16 discNumber);
    qint16 getDiscNumber() const { return discNumber; }
    void setArtist(qint32 artist);
    qint32 getArtist() const { return artist; }

    bool operator==(const Song &s) const { return this->id == s.id; }
    bool operator!=(const Song &s) const { return !( *this == s); }

private:
    qint32 id;
    QByteArray name;
    qint32 time;
    qint32 artist;
    qint16 trackNumber;
    qint16 discNumber;
    qint32 album;
    
signals:
    void songDeleted(Song *s);

public slots:
};

#endif // SONG_H
