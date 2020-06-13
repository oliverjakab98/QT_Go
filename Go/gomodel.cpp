#include "gomodel.h"

GoModel::GoModel(QWidget *parent) : QObject(parent)
{
    newGame();

}

void GoModel::newGame()
{
    gridsizedialog = new GridSizeDialog();
    connect(gridsizedialog->_small,SIGNAL(clicked()),this,SLOT(small_slot()));
    connect(gridsizedialog->_medium,SIGNAL(clicked()),this,SLOT(medium_slot()));
    connect(gridsizedialog->_large,SIGNAL(clicked()),this,SLOT(large_slot()));
    _maxStepNumber = gridsizedialog->_max;
    gridsizedialog->exec();


    _gameTable = new Player*[_meret];
    for (int i = 0; i < _meret; i++)
    {
        _gameTable[i] = new Player[_meret];
    }

    for (int i = 0; i < _meret; ++i)
            for (int j = 0; j < _meret; ++j)
            {
                _gameTable[i][j] = NoPlayer; // a játékosok pozícióit töröljük
            }

        _stepNumber = 0;
        _currentPlayer = PlayerB;
        _whiteScore = 0;
        _blackScore = 0;
}

void GoModel::stepGame(int x, int y)
{


    if(_gameTable[x][y] != 0){return;}
    _gameTable[x][y] = _currentPlayer;
    fieldChanged(x,y, _currentPlayer);

    for (int i=0; i < _meret; i++)
    {
        for (int j=0; j < _meret; j++)
        {
            if(checkGameEnemy(i,j) == true)
            {
                _gameTable[i][j] = DeadPlayer;
            }
        }
    }

    for (int i=0; i < _meret; i++)
    {
        for (int j=0; j < _meret; j++)
        {
            if(_gameTable[i][j] == DeadPlayer)
            {
                _gameTable[i][j] = NoPlayer;
                if (_currentPlayer == PlayerW){_whiteScore++;}
                else if(_currentPlayer == PlayerB){_blackScore++;}
            }
        }
    }

    _stepNumber++;
    checkGameOver();
    _currentPlayer =(Player)(_currentPlayer % 2 + 1);

}

GoModel::Player GoModel::getField(int x, int y) const
{
    if(x < 0 || x >= _meret || y < 0 || y >= _meret)
    {
    return DeadPlayer;
    }
    return _gameTable[x][y];
}

int GoModel::getSize()
{
    return _meret;
}

QString GoModel::jatekos()
{
    if(_currentPlayer == PlayerB){ return "JÁTÉKOS: FEHÉR";}
    else if(_currentPlayer == PlayerW){return "JÁTÉKOS: FEKETE";}
}

void GoModel::checkGameOver()
{
    if(_stepNumber == _maxStepNumber)
    {
        gameOver();
    }
}

bool GoModel::loadGame(int gameIndex)
{
    QVector<int> saveGameData;

    if (!_dataAccess.loadGame(gameIndex, saveGameData)) // az adatelérés végzi a tevékenységeket
        return false;

    // feldolgozttuk a kapott vektort
     _meret = saveGameData[0];
     _gameTable = new Player*[_meret];
     for (int i = 0; i < _meret; i++)
     {
         _gameTable[i] = new Player[_meret];
     }

     for (int i = 0; i < _meret; ++i)
             for (int j = 0; j < _meret; ++j)
             {
                 _gameTable[i][j] = NoPlayer; // a játékosok pozícióit töröljük
             }

     fieldChanged(1,1,NoPlayer);
    _maxStepNumber = saveGameData[1];
    _stepNumber = saveGameData[2];
    _currentPlayer = Player(saveGameData[3]);
    for (int i = 0; i < _meret; ++i)
        for (int j = 0; j < _meret; ++j)
        {
            _gameTable[i][j] = (Player)saveGameData[4 + i * _meret + j];
        }

    return true;
}

bool GoModel::saveGame(int gameIndex)
{
    QVector<int> saveGameData;

    // összerakjuk a megfelelő tartalmat
    saveGameData.push_back(this->_meret);
    saveGameData.push_back(_maxStepNumber);
    saveGameData.push_back(_stepNumber);
    saveGameData.push_back((int)_currentPlayer);
    for (int i = 0; i < _meret; ++i)
        for (int j = 0; j < _meret; ++j)
        {
            saveGameData.push_back((int)_gameTable[i][j]);
        }

    return _dataAccess.saveGame(gameIndex, saveGameData); // az adatelérés végzi a tevékenységeket
}

QVector<QString> GoModel::saveGameList() const
{
    return _dataAccess.saveGameList();
}

bool GoModel::checkGameEnemy(int x, int y)
{
        if(getField(x, y) == NoPlayer)
            return false;
        if(getField(x + 1, y) == NoPlayer)
            return false;
        if(getField(x - 1, y) == NoPlayer)
            return false;
        if(getField(x, y + 1) == NoPlayer)
            return false;
        if(getField(x, y - 1) == NoPlayer)
            return false;

        bool result = true;
        Player player = getField(x, y);
        _gameTable[x][y] = DeadPlayer;
        if(getField(x + 1, y) == player)
            result = result && checkGameEnemy(x + 1, y);
        if(getField(x - 1, y) == player)
            result = result && checkGameEnemy(x - 1, y);
        if(getField(x, y + 1) == player)
            result = result && checkGameEnemy(x, y + 1);
        if(getField(x, y - 1) == player)
            result = result && checkGameEnemy(x, y - 1);
        _gameTable[x][y] = player;

        return result;
}

void GoModel::small_slot()
{
    _meret = 5;
    delete gridsizedialog;
}

void GoModel::medium_slot()
{
    _meret = 9;
    delete gridsizedialog;

}

void GoModel::large_slot()
{
    _meret = 19;
    delete gridsizedialog;
}
