#include "gowidget.h"


GoWidget::GoWidget(QWidget *parent)
    : QWidget(parent)
{


    setMinimumSize(400, 400);
    setWindowTitle("Go Game  JÁTÉKOS: FEKETE");

    _size = _goModel.getSize();
    map(_size);

    connect(&_goModel, SIGNAL(fieldChanged(int, int, GoModel::Player)), this, SLOT(model_fieldChanged(int, int, GoModel::Player)));
    connect(&_goModel, SIGNAL(gameOver()), this, SLOT(model_gameOver()));

    //mentések
    _loadGameWidget = nullptr;
    _saveGameWidget = nullptr;


}

GoWidget::~GoWidget()
{
}

void GoWidget::paintEvent(QPaintEvent *)
{
    if(_size == 0 || _size == 16){exit(1);}

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.scale(width() / 200.0, height() / 200.0);

    painter.setPen(QPen(Qt::black, 1));
    painter.drawLines(_tableGraphics);

    if(_size == 9)
    {
        _playerBGraphics = QRectF(2.0, 2.0, 10.0, 10.0);
        _playerWGraphics = QRectF(2.0, 2.0, 10.0, 10.0);
        for(int i = 0; i < _size; i++)
        {
            for(int j = 0; j < _size; j++)
            {
                painter.save(); // elmentjük a rajztulajdonságokat
                painter.translate((125+i * 180) / _size ,(115+j * 180)  / _size); // elmozdítjuk a rajzpontot a megfelelő mezőre

                // mező kirajzolása a játékos függvényében
                switch (_goModel.getField(i, j))
                {
                case GoModel::PlayerW:
                    painter.setPen(QPen(Qt::black, 1)); // toll beállítása
                    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                    painter.drawEllipse(_playerWGraphics); // megfelelõ grafika kirajzolása
                    break;
                case GoModel::PlayerB:
                    painter.setPen(QPen(Qt::black, 1)); // toll beállítása
                    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
                    painter.drawEllipse(_playerBGraphics);
                    break;
                }
                painter.restore(); // visszatöltjük a korábbi állapotot
            }
        }
    }

    else if(_size == 19)
    {
        _playerBGraphics = QRectF(1.0, 1.0, 4.0, 4.0);
        _playerWGraphics = QRectF(1.0, 1.0, 4.0, 4.0);
        for(int i = 0; i < _size; i++)
        {
            for(int j = 0; j < _size; j++)
            {
                painter.save(); // elmentjük a rajztulajdonságokat
                painter.translate((150+i * 190) / _size ,(150+j * 190)  / _size); // elmozdítjuk a rajzpontot a megfelelő mezőre

                // mező kirajzolása a játékos függvényében
                switch (_goModel.getField(i, j))
                {
                case GoModel::PlayerW:
                    painter.setPen(QPen(Qt::black, 1)); // toll beállítása
                    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                    painter.drawEllipse(_playerWGraphics); // megfelelõ grafika kirajzolása
                    break;
                case GoModel::PlayerB:
                    painter.setPen(QPen(Qt::black, 1)); // toll beállítása
                    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
                    painter.drawEllipse(_playerBGraphics);
                    break;
                }
                painter.restore(); // visszatöltjük a korábbi állapotot
            }
        }
    }
    else
    {
        _playerBGraphics = QRectF(2.0, 2.0, 12.0, 12.0);
        _playerWGraphics = QRectF(2.0, 2.0, 12.0, 12.0);
        for(int i = 0; i < _size; i++)
        {
            for(int j = 0; j < _size; j++)
            {
                painter.save(); // elmentjük a rajztulajdonságokat
                painter.translate((60+i * 200) / _size ,(60+j * 200)  / _size); // elmozdítjuk a rajzpontot a megfelelő mezőre

                // mező kirajzolása a játékos függvényében
                switch (_goModel.getField(i, j))
                {
                case GoModel::PlayerW:
                    painter.setPen(QPen(Qt::black, 1)); // toll beállítása
                    painter.setBrush(QBrush(Qt::white, Qt::SolidPattern));
                    painter.drawEllipse(_playerWGraphics); // megfelelõ grafika kirajzolása
                    break;
                case GoModel::PlayerB:
                    painter.setPen(QPen(Qt::black, 1)); // toll beállítása
                    painter.setBrush(QBrush(Qt::black, Qt::SolidPattern));
                    painter.drawEllipse(_playerBGraphics);
                    break;
                }
                painter.restore(); // visszatöltjük a korábbi állapotot
            }
        }
    }

}

void GoWidget::mousePressEvent(QMouseEvent *event)
{

    // az event->pos() megadja az egérpozíciót, ami QPoint típusú, ebbõl kiszámolható, melyik mezőn vagyunk:

    if(_size == 9)
    {
        int x = event->pos().x() *9 / width();
        int y = event->pos().y() *9 / height();
        /*QMessageBox click;
        click.setText(QString::number(event->pos().x() *9 / width())+","+QString::number(event->pos().y() * 9 / height()));
        click.exec();*/
        _goModel.stepGame(x,y);
    }
    else if(_size == 19)
    {
        int x = event->pos().x() *19 / width();
        int y = event->pos().y() *19 / height();
        /*QMessageBox click;
        click.setText(QString::number(event->pos().x() *19 / width())+","+QString::number(event->pos().y() * 19 / height()));
        click.exec();*/
         _goModel.stepGame(x,y);
    }
    else
    {
        int x = event->pos().x() *5 / width();
        int y = event->pos().y() *5 / height();
        QMessageBox click;
        /*click.setText(QString::number(event->pos().x() *5 / width())+","+QString::number(event->pos().y() * 5 / height()));
        click.exec();*/
        _goModel.stepGame(x,y);
    }

}

void GoWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_N && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        // lekezeljük a Ctrl+N kombinációt
        _goModel.newGame();
        _size = _goModel.getSize();
        map(_size);
        update();
    }

    // játék betöltése
    if (event->key() == Qt::Key_L && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        if (_loadGameWidget == nullptr) // ha még egyszer sem nyitották meg az ablakot
        {
            _loadGameWidget = new LoadGameWidget();
            connect(_loadGameWidget, SIGNAL(accepted()), this, SLOT(loadGame()));
        }

        // beállítjuk a listát, és megnyitjuk az ablakot
        _loadGameWidget->setGameList(_goModel.saveGameList());
        _loadGameWidget->open();

    }

    if (event->key() == Qt::Key_S && QApplication::keyboardModifiers() == Qt::ControlModifier)
    {
        if (_saveGameWidget == nullptr) // ha még egyszer sem nyitották meg az ablakot
        {
            _saveGameWidget = new SaveGameWidget();
            connect(_saveGameWidget, SIGNAL(accepted()), this, SLOT(saveGame()));
        }

        // beállítjuk a listát, és megnyitjuk az ablakot
        _saveGameWidget->setGameList(_goModel.saveGameList());
        _saveGameWidget->open();
    }
}
void GoWidget::map(int meret) //n-1 kis kocka
{
    if(meret == 5)
    {
        //palya grafikája
         //small 5x5

        _tableGraphics.clear();

        _tableGraphics.append(QLineF(20, 20, 180, 20));
        _tableGraphics.append(QLineF(20, 60, 180, 60));
        _tableGraphics.append(QLineF(20, 100, 180, 100));
        _tableGraphics.append(QLineF(20, 140, 180, 140));
        _tableGraphics.append(QLineF(20, 180, 180, 180));

        _tableGraphics.append(QLineF(20,20,20,180));
        _tableGraphics.append(QLineF(60,20,60,180));
        _tableGraphics.append(QLineF(100,20,100,180));
        _tableGraphics.append(QLineF(140,20,140,180));
        _tableGraphics.append(QLineF(180,20,180,180));

        QWidget::repaint();
    }
    else if (meret == 9)
    {
        //palya grafika
         //medium 9x9
        _tableGraphics.clear();

        _tableGraphics.append(QLineF(20, 20, 180, 20));
        _tableGraphics.append(QLineF(20, 40, 180, 40));
        _tableGraphics.append(QLineF(20, 60, 180, 60));
        _tableGraphics.append(QLineF(20, 80, 180, 80));
        _tableGraphics.append(QLineF(20, 100, 180, 100));
        _tableGraphics.append(QLineF(20, 120, 180, 120));
        _tableGraphics.append(QLineF(20, 140, 180, 140));
        _tableGraphics.append(QLineF(20, 160, 180, 160));
        _tableGraphics.append(QLineF(20, 180, 180, 180));

        _tableGraphics.append(QLineF(20,20,20,180));
        _tableGraphics.append(QLineF(40,20,40,180));
        _tableGraphics.append(QLineF(60,20,60,180));
        _tableGraphics.append(QLineF(80,20,80,180));
        _tableGraphics.append(QLineF(100,20,100,180));
        _tableGraphics.append(QLineF(120,20,120,180));
        _tableGraphics.append(QLineF(140,20,140,180));
        _tableGraphics.append(QLineF(160,20,160,180));
        _tableGraphics.append(QLineF(180,20,180,180));

        QWidget::repaint();
    }
    else if(meret == 19)
    {
        //palya grafika
         //large 19x19
        _tableGraphics.clear();

        _tableGraphics.append(QLineF(10, 10, 190, 10));
        _tableGraphics.append(QLineF(10, 20, 190, 20));
        _tableGraphics.append(QLineF(10, 30, 190, 30));
        _tableGraphics.append(QLineF(10, 40, 190, 40));
        _tableGraphics.append(QLineF(10, 50, 190, 50));
        _tableGraphics.append(QLineF(10, 60, 190, 60));
        _tableGraphics.append(QLineF(10, 70, 190, 70));
        _tableGraphics.append(QLineF(10, 80, 190, 80));
        _tableGraphics.append(QLineF(10, 90, 190, 90));
        _tableGraphics.append(QLineF(10, 100, 190, 100));
        _tableGraphics.append(QLineF(10, 110, 190, 110));
        _tableGraphics.append(QLineF(10, 120, 190, 120));
        _tableGraphics.append(QLineF(10, 130, 190, 130));
        _tableGraphics.append(QLineF(10, 140, 190, 140));
        _tableGraphics.append(QLineF(10, 150, 190, 150));
        _tableGraphics.append(QLineF(10, 160, 190, 160));
        _tableGraphics.append(QLineF(10, 170, 190, 170));
        _tableGraphics.append(QLineF(10, 180, 190, 180));
        _tableGraphics.append(QLineF(10, 190, 190, 190));

        _tableGraphics.append(QLineF(10,10,10,190));
        _tableGraphics.append(QLineF(20,10,20,190));
        _tableGraphics.append(QLineF(30,10,30,190));
        _tableGraphics.append(QLineF(40,10,40,190));
        _tableGraphics.append(QLineF(50,10,50,190));
        _tableGraphics.append(QLineF(60,10,60,190));
        _tableGraphics.append(QLineF(70,10,70,190));
        _tableGraphics.append(QLineF(80,10,80,190));
        _tableGraphics.append(QLineF(90,10,90,190));
        _tableGraphics.append(QLineF(100,10,100,190));
        _tableGraphics.append(QLineF(110,10,110,190));
        _tableGraphics.append(QLineF(120,10,120,190));
        _tableGraphics.append(QLineF(130,10,130,190));
        _tableGraphics.append(QLineF(140,10,140,190));
        _tableGraphics.append(QLineF(150,10,150,190));
        _tableGraphics.append(QLineF(160,10,160,190));
        _tableGraphics.append(QLineF(170,10,170,190));
        _tableGraphics.append(QLineF(180,10,180,190));
        _tableGraphics.append(QLineF(190,10,190,190));

        QWidget::repaint();
    }
}

void GoWidget::model_fieldChanged(int x, int y, GoModel::Player)
{

    _size = _goModel.getSize();
    map(_size);
    setWindowTitle("Go Game  "+_goModel.jatekos()+"     Hátralévő lépések száma: "+QString::number(_goModel._maxStepNumber-1 - _goModel._stepNumber));
    update();
}

void GoWidget::model_gameOver()
{
    QMessageBox msg;
    if (_goModel._blackScore == _goModel._whiteScore)
    {
        msg.setText("Döntetlen!\nFekete pont: "+QString::number(_goModel._blackScore)+"\nFehér pont: "+QString::number(_goModel._whiteScore));
    }
    else if(_goModel._blackScore > _goModel._whiteScore)
    {
        msg.setText("A fekete nyert!\nFekete pont: "+QString::number(_goModel._blackScore)+"\nFehér pont: "+QString::number(_goModel._whiteScore));
    }
    else
    {
        msg.setText("A fehér nyert!\nFekete pont: "+QString::number(_goModel._blackScore)+"\nFehér pont: "+QString::number(_goModel._whiteScore));
    }
    msg.exec();
    _goModel.newGame();
    _size = _goModel.getSize();
    map(_size);
    update();
}

void GoWidget::loadGame()
{
    // betöltjük a kiválasztott játékot
    if (_goModel.loadGame(_loadGameWidget->selectedGame()))
    {
        update();
        QMessageBox::information(this, tr("Go Game"), tr("Játék betöltve, következik: ") + ((_goModel.currentPlayer() == GoModel::PlayerB) ? "Fekete" : "Fehér") + "!\n A maradék lépések száma: "+QString::number(_goModel._maxStepNumber-1 - _goModel._stepNumber));
    }
    else
    {
        QMessageBox::warning(this, tr("Go Game"), tr("A játék betöltése sikertelen!"));
    }
}

void GoWidget::saveGame()
{
    if (_goModel.saveGame(_saveGameWidget->selectedGame()))
    {
        update();
        QMessageBox::information(this, tr("Go Game"), tr("Játék sikeresen mentve!"));
    }
    else
    {
        QMessageBox::warning(this, tr("Go Game"), tr("A játék mentése sikertelen!"));
    }
}

