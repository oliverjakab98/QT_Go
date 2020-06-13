#ifndef GODATAACCES_H
#define GODATAACCES_H

#include <QString>
#include <QVector>

class GoDataAcces
{
public:
    GoDataAcces() {}
    virtual QVector<QString> saveGameList() const = 0; // mentett játékok lekérdezése
    virtual bool isAvailable() const { return false; }
    virtual bool loadGame(int gameIndex, QVector<int> &saveGameData) = 0; // játék betöltése
    virtual bool saveGame(int gameIndex, const QVector<int> &saveGameData) = 0; // játék mentése

};

#endif // GODATAACCES_H
