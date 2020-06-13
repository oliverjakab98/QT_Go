#ifndef GOMODEL_H
#define GOMODEL_H

#include <QObject>
#include <QPoint>
#include "godataacces.h"

class GoModel : public QObject
{
    Q_OBJECT
public:
    enum Player {NoPlayer, PlayerW, PlayerB, DeadPlayer};

     GoModel(GoDataAcces* dataAcces);


    void newGame();
    void stepGame(int x, int y);
    int stepNumber() const {return _stepNumber; }
    Player currentPlayer() const {return _currentPlayer; }
    Player getField(int x, int y) const;

    int getSize();

    int _meret = 5;
    int _whiteScore;
    int _blackScore;
    QString jatekos();
    void checkGameOver();

    bool loadGame(int gameIndex); // játék betöltése
    bool saveGame(int gameIndex); // játék mentése
    QVector<QString> saveGameList() const;

    int _stepNumber = 0 ;
    int _maxStepNumber = 10;

private:
    bool checkGameEnemy(int x, int y);



    Player _currentPlayer;
    Player** _gameTable;

    GoDataAcces* _dataAccess;

signals:
    void gameOver();
    void fieldChanged(int x, int y, GoModel::Player player);

};

#endif // GOMODEL_H
