#ifndef GOWIDGET_H
#define GOWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QInputDialog>
#include <QMessageBox>
#include "gomodel.h"
#include <QMouseEvent>
#include <QApplication>
#include "loadgamewidget.h"
#include "savegamewidget.h"

class GoWidget : public QWidget
{
    Q_OBJECT

public:
    GoWidget(QWidget *parent = nullptr);
    ~GoWidget();

protected:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    void map(int meret);

    GoModel _goModel;
    SaveGameWidget* _saveGameWidget; // a mentést biztosító ablak
    LoadGameWidget* _loadGameWidget; // a betöltést biztostó ablak

    int _size = 0;

    GridSizeDialog *gridsizedialog;

    QVector<QLineF> _tableGraphics;
    QVector<QPoint> _pointPlaces;
    QRectF _playerWGraphics;
    QRectF _playerBGraphics;

private slots:
    void model_fieldChanged(int x, int y, GoModel::Player);
    void model_gameOver();

    void loadGame();
    void saveGame();

};
#endif // GOWIDGET_H
