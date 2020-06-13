#ifndef GODATAACCESMOCK_H
#define GODATAACCESMOCK_H

#include "godataacces.h"
#include <QString>
#include <QVector>


class GoDataAccesMock : public GoDataAcces
{
public:
    bool isAvailable() const { return true; } // rendelkezésre állás lekérdezése
    QVector<QString> saveGameList() const // mentett játékok lekérdezése
    {
        return QVector<QString>(5); // üres listát adunk vissza
    }

    bool loadGame(int gameIndex, QVector<int> &saveGameData)
    {


        saveGameData.resize(29);
        saveGameData[3] = 2;

        return true;
    }

    bool saveGame(int gameIndex, const QVector<int> &saveGameData)
    {
       QVector<int> savedgame;
       savedgame.resize(29);
       for (int i = 0; i < 25+4;i++ )
       {
           savedgame.push_back(saveGameData[i]);
       }

        return true;
    }
};

#endif // GODATAACCESMOCK_H
