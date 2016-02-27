#ifndef TITANIUM_H
#define TITANIUM_H

#include <QMainWindow>

namespace Ui {
class titanium;
}

class titanium : public QMainWindow
{
    Q_OBJECT

public:
    explicit titanium(QWidget *parent = 0);
    ~titanium();

private slots:
    void on_fileButton_clicked();
    void save();
    void open();
    void newDocument();

private:
    Ui::titanium *ui;
};

#endif // TITANIUM_H
