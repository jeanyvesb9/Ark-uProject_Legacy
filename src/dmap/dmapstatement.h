#ifndef DMAPSTATEMENT_H
#define DMAPSTATEMENT_H

#include <QtGlobal>
#include <QtDebug>
#include <QList>
#include <QByteArray>
#include <QString>
#include <QtEndian>
#include <cstring>
#include "../global.h"

using byte = char;

class DmapStatement
{
public:
    DmapStatement(byte *statement, byte *end, bool parseList = 1);
    ~DmapStatement();

    DmapStatement *findValue(QString &name, QString &inside, QString &insideRefType,
                             QByteArray &insideRefValue) const;

    DmapStatement *findUniqueValue(QString &name, QString &inside) const;

    template <typename t> static t byteToInt(QByteArray &array)
    {
        return qFromBigEndian<t>(reinterpret_cast<unsigned char*>(array.data()));
    }

    template <typename t> static t byteToInt(QByteArray &&array)
    {
        return qFromBigEndian<t>(reinterpret_cast<unsigned char*>(array.data()));
    }

    template <typename t> static t byteToInt(byte *array)
    {
        return qFromBigEndian<t>(reinterpret_cast<unsigned char*>(array));
    }

    char *getName() const;

    quint32 getByteSize() const;

    byte *getData() const;

    const QList<DmapStatement> &getDictList() const;

private:
    char *name;
    quint32 byteSize;
    byte *data;

    byte *end;
    QList<DmapStatement> dictList;

    bool isList(char *name) const;
    bool _findValue(DmapStatement* &res, const char *name, const char *inside,
                    const char* insideRefType, QByteArray *insideRefValue) const;
    bool _findUniqueValue(DmapStatement* &res, const char *name, const char *inside) const;
};

#endif // DMAPSTATEMENT_H
