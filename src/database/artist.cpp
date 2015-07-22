#include "artist.h"

Artist::Artist(qint32 id, QString name, QObject *parent)
    : QObject(parent), id{id}, name{name.toUtf8()}
{

}

Artist::~Artist()
{
    emit artistDeleted(this);
}
void Artist::setId(qint32 id)
{
    this->id = id;
}

void Artist::setName(QString name)
{
    this->name = name.toUtf8();
}
