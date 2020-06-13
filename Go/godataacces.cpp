#include "godataacces.h"
#include <QDateTime>
#include <QFileInfo>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

GoDataAcces::GoDataAcces()
{

}

QVector<QString> GoDataAcces::saveGameList() const
{
    QVector<QString> result(5);

    // végigmegyünk az 5 helyen
    for (int i = 0; i < 5; i++)
    {
        if (QFile::exists("game" + QString::number(i) + ".sav")) // ha az adott mentés létezik
        {
            QFileInfo info("game"+ QString::number(i) + ".sav");
            result[i] = "[" + QString::number(i + 1) + "] " + info.lastModified().toString("yyyy.MM.dd HH:mm:ss");
            // akkor betöltjük a fájl módosítás időpontját
        }
    }

    return result;
}

bool GoDataAcces::loadGame(int gameIndex, QVector<int> &saveGameData)
{
    QFile file("game" + QString::number(gameIndex) + ".sav");
    if (!file.open(QFile::ReadOnly))
        return false;

    QTextStream stream(&file);

    int size = stream.readLine().toInt();
    saveGameData.resize(size*size+4);
    saveGameData[0] = size;
    // soronként beolvassuk az adatokat a fájlból
    for (int i = 0; i < size*size+3; i++)
        saveGameData[i+1] = stream.readLine().toInt();

    file.close();

    return true;
}

bool GoDataAcces::saveGame(int gameIndex, const QVector<int> &saveGameData)
{
    QFile file("game" + QString::number(gameIndex) + ".sav");
    if (!file.open(QFile::WriteOnly))
        return false;

    QTextStream stream(&file);
    int size = saveGameData[0];

    // soronként egy adatot írunk ki
    for (int i = 0; i < size*size+4; i++)
        stream << saveGameData[i] << endl;

    file.close();

    return true;
}
