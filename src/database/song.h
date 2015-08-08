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
    Song(quint32 id, QByteArray name, quint32 time, quint16 trackNumber = 1,
                  quint16 discNumber = 1, quint64 album = 0, bool diffArtist = 0, QByteArray artist = 0, QObject *parent = 0);
    ~Song();

    void setId(quint32 id);
    quint32 getId() const { return id; }

    void setName(QString name);
    QString getName() const { return QString::fromUtf8(name); }

    void setAlbum(quint64 album);
    quint64 getAlbum() const { return this->album; }

    void setTime(quint32 time);
    quint32 getTime() const { return time; }

    void setTrackNumber(quint16 trackNumber);
    quint16 getTrackNumber() const { return trackNumber; }

    void setDiscNumber(quint16 discNumber);
    quint16 getDiscNumber() const { return discNumber; }

    void setArtist(QString artist);
    void setDefaultArtist();
    QString getArtist() const;

    bool operator==(const Song &s) const { return this->id == s.id; }
    bool operator!=(const Song &s) const { return !( *this == s); }

private:

    quint32 id;
    QByteArray name;
    quint32 time;
    QByteArray *artistName;
    quint16 trackNumber;
    quint16 discNumber;
    quint64 album;
    
signals:
    void songDeleted(Song *s);

public slots:
};

#endif // SONG_H
