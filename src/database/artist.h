#ifndef ARTIST_H
#define ARTIST_H

#include <QObject>
#include <QString>
#include <QByteArray>
#include <QtGlobal>

class Artist : public QObject
{
    Q_OBJECT
public:
    Artist(quint64 id, quint32 groupId, QByteArray name, QObject *parent = 0);
    ~Artist();

    void setId(quint64 id);
    quint64 getId() const { return id; }

    void setGroupId(quint32 groupId);
    quint32 getGroupId() const { return groupId; }

    void setName(QString name);
    QString getName() const { return QString::fromUtf8(name); }

    void setAlbumList(QList<quint64> albums);
    const QList<quint64> *getAlbumList() const { return &albumList; }
    void addAlbum(quint16 possition, quint64 albumNumber);
    void appendAlbum(quint64 albumNumber);
    void removeAlbum(quint16 possition);
    void moveAlbum(quint16 from, quint16 to);

    bool operator==(const Artist &a) const { return this->id == a.id; }
    bool operator!=(const Artist &a) const { return !( *this == a); }

private:
    quint64 id;
    quint32 groupId;
    QByteArray name;
    QList<quint64> albumList;

signals:
    void artistDeleted(Artist *artist);

public slots:
};

#endif // ARTIST_H
