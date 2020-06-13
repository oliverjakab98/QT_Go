#include <QtTest>
#include "gomodel.h"
#include "GoDataAccesMock.h"


class GoTest : public QObject
{
    Q_OBJECT

public:
    GoModel* _model;
    GoDataAcces *_dataAccess;

private slots:
    void initTestCase();
    void cleanupTestCase();
    void testNewGame();
    void testStepGame();
    void testStepGameErrors();
    void testLoadGame();

};



void GoTest::initTestCase()
{
    _dataAccess = new GoDataAccesMock();
    _model = new GoModel(_dataAccess);
}

void GoTest::cleanupTestCase()
{
    delete _model;
}

void GoTest::testNewGame()
{
    _model->newGame();
    QCOMPARE(_model->stepNumber(), 0);
    for (int i = 0; i < _model->_meret; i++)
        for (int j = 0; j < _model->_meret; j++)
            QCOMPARE(_model->getField(i, j), GoModel::NoPlayer);
}

void GoTest::testStepGame()
{
    _model->newGame();
    _model->stepGame(0, 0);

    // ellenőrizzük, hogy a lépésszám 1, és az X lépett először
    QCOMPARE(_model->stepNumber(), 1);
    QCOMPARE(_model->getField(0, 0), GoModel::PlayerB);

    // ellenőrizzük, hogy közben más mező nem változott
    for (int i = 0; i < _model->_meret; i++)
        for (int j = 0; j < _model->_meret; j++)
            QVERIFY((i == 0 && j == 0) || (_model->getField(i, j) == GoModel::NoPlayer));

    // ellenőrizzük, hogy ezután a O következik
    _model->stepGame(0, 1);
    QCOMPARE(_model->stepNumber(), 2);
    QCOMPARE(_model->getField(0, 1), GoModel::PlayerW);

    // majd ismét az X
    _model->stepGame(0, 2);
    QCOMPARE(_model->stepNumber(), 3);
    QCOMPARE(_model->getField(0, 2), GoModel::PlayerB);
}

void GoTest::testStepGameErrors()
{
    _model->newGame();

    // ellenőrizzük, hogy kétszer nem tudunk lépni ugyanarra a mezőre
    _model->stepGame(0, 0);
    _model->stepGame(0, 0);
    QCOMPARE(_model->stepNumber(), 1);
    QCOMPARE(_model->getField(0, 0), GoModel::PlayerB);
}

void GoTest::testLoadGame()
{
    _model->newGame();

    _model->stepGame(1, 0);

    _model->loadGame(0);
    // ellenőrizzük, hogy a lépésszám 0, még senki sem lépett, és az X jön
    QCOMPARE(_model->stepNumber(), 0);
    QCOMPARE(_model->currentPlayer(), GoModel::PlayerB);

    for (int i = 0; i < _model->_meret; i++)
        for (int j = 0; j < _model->_meret; j++)
            QVERIFY((_model->getField(i, j) == GoModel::NoPlayer));
}


QTEST_APPLESS_MAIN(GoTest)

#include "tst_gotest.moc"
