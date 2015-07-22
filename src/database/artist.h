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
    explicit Artist(qint32 id, QString name, QObject *parent = 0);
    ~Artist();

    void setId(qint32 id);
    qint32 getId() const { return id; }
    void setName(QString name);
    QString getName() const { return QString::fromUtf8(name); }

    bool operator==(const Artist &a) const { return this->id == a.id; }
    bool operator!=(const Artist &a) const { return !( *this == a); }

private:
    qint32 id;
    QByteArray name;

signals:
    void artistDeleted(Artist *artist);

public slots:
};

#endif // ARTIST_H
