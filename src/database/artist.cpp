#include "artist.h"

Artist::Artist(quint64 id, quint32 groupId, QByteArray name, QObject *parent)
    : QObject(parent), id{id}, groupId{groupId}, name{name}
{

}

Artist::~Artist()
{
    emit artistDeleted(this);
}
void Artist::setId(quint64 id)
{
    this->id = id;
}

void Artist::setName(QString name)
{
    this->name = name.toUtf8();
}

void Artist::setGroupId(quint32 groupId)
{
    this->groupId = groupId;
}

void Artist::setAlbumList(QList<quint64> albums)
{
    this->albumList = albums;
}

void Artist::addAlbum(quint16 possition, quint64 albumNumber)
{
    this->albumList.insert(possition, albumNumber);
}

void Artist::appendAlbum(quint64 albumNumber)
{
    this->albumList.append(albumNumber);
}

void Artist::removeAlbum(quint16 possition)
{
    this->albumList.removeAt(possition);
}

void Artist::moveAlbum(quint16 from, quint16 to)
{
    this->albumList.move(from, to);
}
