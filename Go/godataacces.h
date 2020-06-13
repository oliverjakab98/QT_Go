#ifndef GODATAACCES_H
#define GODATAACCES_H

#include <QString>
#include <QVector>

class GoDataAcces
{
public:
    GoDataAcces();
    QVector<QString> saveGameList() const; // mentett játékok lekérdezése

    bool loadGame(int gameIndex, QVector<int> &saveGameData); // játék betöltése
    bool saveGame(int gameIndex, const QVector<int> &saveGameData); // játék mentése

};

#endif // GODATAACCES_H
