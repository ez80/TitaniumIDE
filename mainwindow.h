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
    void saveFile(QString,QString);
    void saveProject();
    void openProject(QString);
    void closeProject();
    QString projectDialog();
    int addFile(QString, QString, bool);
    void renameFileDialog();
    void renameFile(QString);
    void closeEvent(QCloseEvent*);
private:
    Ui::MainWindow *ui;
};


struct TitaniumFile {
    QString fileName;
    QString filePath;
    bool saved;
    QString text;
    int lang; //0 is no lang, 1 is asm, 2 is c, 3 is ti-basic.
};
#endif // MAINWINDOW_H
