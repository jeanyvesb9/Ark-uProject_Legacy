#include "applicationlogic.h"

ApplicationLogic::ApplicationLogic(QObject *parent)
    : QObject(parent), client{new DmapClient()}, library{new Library()}
{

}

ApplicationLogic::~ApplicationLogic()
{
    client->deleteLater();
    library->deleteLater();
}

void ApplicationLogic::setClient(QString &host, quint16 &port, QString &username, QString &password)
{
    client->setServerAddress(host, port);
    client->setAuthenticationHeader(username, password);
    client->setLibrary(library);

    connect(client, &DmapClient::loginCompleted, this, &ApplicationLogic::loginFinished);
    connect(client, &DmapClient::updateCompleted, this, &ApplicationLogic::updateFinished);
    connect(client, &DmapClient::getDatabasesCompleted, this, &ApplicationLogic::getDatabasesFinished);
    connect(client, &DmapClient::getLibraryContainerCompleted, this, &ApplicationLogic::getLibraryContainerFinished);
    connect(client, &DmapClient::getArtistsCompleted, this, &ApplicationLogic::getArtistsFinished);
    connect(client, &DmapClient::getAlbumsCompleted, this, &ApplicationLogic::getAlbumsFinished);
    connect(client, &DmapClient::getSongsCompleted, this, &ApplicationLogic::getSongsFinished);
}

void ApplicationLogic::setClientAddress(QString &host, quint16 &port)
{
    client->setServerAddress(host, port);
}

void ApplicationLogic::executeInitSequence()
{
    client->login();
}

void ApplicationLogic::loginFinished()
{
    client->update();
}

void ApplicationLogic::updateFinished()
{
    client->getDatabases();
}

void ApplicationLogic::getDatabasesFinished()
{
    client->getLibraryContainer();
}

void ApplicationLogic::getLibraryContainerFinished()
{
    client->getArtists();
}

void ApplicationLogic::getArtistsFinished()
{
    client->getAlbums();
}

void ApplicationLogic::getAlbumsFinished()
{
    client->getSongs();
}

void ApplicationLogic::getSongsFinished()
{
    emit initSequenceCompleted();
}
