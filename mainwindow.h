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
    void closeProject();
    QString projectDialog();
    int addFile(QString, QString);
    void renameFile();
    void closeEvent(QCloseEvent*);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
