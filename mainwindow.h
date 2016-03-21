#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void fileMenuClicked();
    void newDocument();
    void save();
    void openDialog();
    void newProject();
    void saveProject();
    void openProject(QString);
    QString projectDialog();
    void addFile(QString, QString);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
