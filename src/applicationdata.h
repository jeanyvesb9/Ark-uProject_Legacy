#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include <QObject>
#include "src/database/library.h"

class ApplicationData : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationData(QObject *parent = 0);

private:


signals:

public slots:
};

#endif // APPLICATIONDATA_H
