#ifndef DMAPCLIENT_H
#define DMAPCLIENT_H

#include <QObject>

class DmapClient : public QObject
{
    Q_OBJECT
public:
    explicit DmapClient(QObject *parent = 0);

signals:

public slots:
};

#endif // DMAPCLIENT_H
