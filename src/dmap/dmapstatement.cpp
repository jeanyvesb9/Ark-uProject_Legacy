#include "dmapstatement.h"

DmapStatement::DmapStatement(byte *statement, byte *end, bool parseList)
    : name{statement}, byteSize{byteToInt<quint32>(statement + 4)},
      data{statement + 8}, end{end}
{
    if(parseList && isList(name))
    {
        byte *statementEnd = !std::memcmp(name, "mlcl", 4)? end : (data + byteSize - 1);
        byte *begin = data;
        for(int i = 0; begin < statementEnd; i++)
        {
            dictList.append(DmapStatement(begin, end, 1));
            begin += (8 + dictList.at(i).getByteSize());
        }
    }
}

DmapStatement::~DmapStatement()
{

}

DmapStatement *DmapStatement::findValue(QString &name, QString &inside, QString &insideRefType,
                                        QByteArray &insideRefValue) const
{
    DmapStatement *ret = nullptr;

    QByteArray _name = name.toUtf8();
    QByteArray _inside = inside.toUtf8();
    QByteArray _insideRefType = insideRefType.toUtf8();

    _findValue(ret, _name.data(), _inside.data(), _insideRefType.data(), &insideRefValue);

    return ret;
}

DmapStatement *DmapStatement::findUniqueValue(QString &name, QString &inside) const
{
    DmapStatement *ret = nullptr;

    QByteArray _name = name.toUtf8();
    QByteArray _inside = inside.toUtf8();

    _findUniqueValue(ret, _name.data(), _inside.data());

    return ret;
}

bool DmapStatement::_findValue(DmapStatement* &res, const char *name, const char *inside,
                                              const char *insideRefType, QByteArray *insideRefValue) const
{
    if(!std::memcmp(this->name, name, 4))
    {
        res = const_cast<DmapStatement*>(this);
        return true;
    }

    QList<const DmapStatement*> listTypes;

    if(!std::memcmp(this->name, inside, 4))
    {
        for(int i = 0; i < dictList.size(); i++)
        {
            const DmapStatement &ref = dictList.at(i);
            if ( (!std::memcmp(ref.name, insideRefType, 4)) &&
                    (!std::memcmp(ref.data, insideRefValue->data(), insideRefValue->size())) )
            {
                for(int b = 0; b < dictList.size(); b++)
                {
                    const DmapStatement &bRef = dictList.at(b);
                    if(!std::memcmp(bRef.name, name, 4))
                    {
                        const DmapStatement *ret = &bRef;
                        res = const_cast<DmapStatement*>(ret);
                        return true;
                    }
                }
            }
            if(isList(ref.name))
            {
                const DmapStatement *ap = &ref;
                listTypes.append(ap);
            }
        }
    }
    else
    {
        for(int i = 0; i < dictList.size(); i++)
        {
            const DmapStatement *ap = &dictList.at(i);
            if(isList(ap->getName()))
            {
                listTypes.append(ap);
            }
        }
    }

    for(auto elem : listTypes)
    {
        if(elem->_findValue(res, name, inside, insideRefType, insideRefValue))
        {
            return true;
        }
    }
    return false;
}

bool DmapStatement::_findUniqueValue(DmapStatement *&res, const char *name, const char *inside) const
{
    if(!std::memcmp(this->name, name, 4))
    {
        res = const_cast<DmapStatement*>(this);
        return true;
    }

    if(!std::memcmp(this->name, inside, 4))
    {
        for(int i = 0; i < dictList.size(); i++)
        {
            const DmapStatement &ref = dictList.at(i);
            if (!std::memcmp(ref.name, name, 4))
            {
                const DmapStatement *ret = &ref;
                res = const_cast<DmapStatement*>(ret);
                return true;
            }
        }
    }
    return false;
}

char *DmapStatement::getName() const
{
    return name;
}

quint32 DmapStatement::getByteSize() const
{
    return byteSize;
}
byte *DmapStatement::getData() const
{
    return data;
}
const QList<DmapStatement> &DmapStatement::getDictList() const
{
    return dictList;
}

bool DmapStatement::isList(char *name) const
{
    return  (!std::memcmp(name, "mcon", 4) || !std::memcmp(name, "mlcl", 4) ||
             !std::memcmp(name, "mlit", 4) || !std::memcmp(name, "mbcl", 4) ||
             !std::memcmp(name, "mdcl", 4) || !std::memcmp(name, "msrv", 4) ||
             !std::memcmp(name, "mlog", 4) || !std::memcmp(name, "mupd", 4) ||
             !std::memcmp(name, "mudl", 4) || !std::memcmp(name, "mccr", 4) ||
             !std::memcmp(name, "avdb", 4) || !std::memcmp(name, "abro", 4) ||
             !std::memcmp(name, "adbs", 4) || !std::memcmp(name, "aply", 4) ||
             !std::memcmp(name, "apso", 4) || !std::memcmp(name, "arsv", 4) ||
             !std::memcmp(name, "arif", 4) || !std::memcmp(name, "abal", 4) ||
             !std::memcmp(name, "abar", 4) || !std::memcmp(name, "abcp", 4) ||
             !std::memcmp(name, "abcp", 4) || !std::memcmp(name, "aeAD", 4)   );
}
