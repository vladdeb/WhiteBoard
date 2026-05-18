#include "savetype.h"
#include "ui_savetype.h"

saveType::saveType(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::saveType)
{
    ui->setupUi(this);
}

saveType::~saveType()
{
    delete ui;
}

void saveType::bmp() {
    saveFormat = format::bmp;
}

void saveType::json() {
    saveFormat = format::json;
}
