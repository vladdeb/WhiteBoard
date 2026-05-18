#ifndef SAVETYPE_H
#define SAVETYPE_H

#include <QDialog>

enum class format {
    json,
    bmp
};

namespace Ui {
class saveType;
}

class saveType : public QDialog
{
    Q_OBJECT

public:
    explicit saveType(QWidget *parent = nullptr);
    ~saveType();
    format saveFormat;

private:
    Ui::saveType *ui;

private slots:
    void bmp();
    void json();
};

#endif // SAVETYPE_H
