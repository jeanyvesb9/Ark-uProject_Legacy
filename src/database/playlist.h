#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QtGlobal>
#include <QList>
#include "song.h"

class Playlist : public QObject
{
    Q_OBJECT
public:
    explicit Playlist(qint32 id, QString name, QObject *parent = 0);
    ~Playlist();

    void setId(qint32 id);
    qint32 getId() const { return id; }

    void setName(QString name);
    QString getName() const {return QString::fromUtf8(name); }

    void setSongList(QList<qint32> songs);
    const QList<qint32> *getSongList() const { return &songList; }
    void addSong(qint16 possition, qint32 song);
    void removeSong(qint16 possition);
    void moveSong(qint16 from, qint16 to);

    bool operator==(const Playlist &p) const { return this->id == p.id; }
    bool operator!=(const Playlist &p) const { return !( *this == p); }

private:
    qint32 id;
    QByteArray name;
    QList<qint32> songList;

signals:
    void playlistDeleted(Playlist*);

public slots:
};

#endif // PLAYLIST_H
