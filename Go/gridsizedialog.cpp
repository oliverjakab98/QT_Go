#include "gridsizedialog.h"

GridSizeDialog::GridSizeDialog(QWidget *parent) : QDialog(parent)
{
    setFixedSize(230,150);
    setWindowTitle(tr("Méret"));
    setModal(true);

    _max = QInputDialog::getInt(this,"Körök száma","Hány körig tartson a játék?",10,10,50);

    _small = new QPushButton("Small (5x5)");
    _medium = new QPushButton("Medium (9x9)");
    _large = new QPushButton("Large (19x19)");


    QVBoxLayout *mainLayout = new QVBoxLayout();

    _label = new QLabel("Válaszd ki hogy mekkora legyen a pálya!");
    mainLayout->addWidget(_label);

    mainLayout->addWidget(_small);
    mainLayout->addWidget(_medium);
    mainLayout->addWidget(_large);

    setLayout(mainLayout);

}
