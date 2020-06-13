#ifndef GRIDSIZEDIALOG_H
#define GRIDSIZEDIALOG_H

#include <QDialog>
#include <QRadioButton>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QInputDialog>

class GridSizeDialog : public QDialog
{
    Q_OBJECT
public:
    GridSizeDialog(QWidget *parent = nullptr);

    QPushButton *_small;
    QPushButton *_medium;
    QPushButton *_large;

    int _max;
private:

    QLabel *_label;
signals:

protected slots:
};

#endif // GRIDSIZEDIALOG_H
