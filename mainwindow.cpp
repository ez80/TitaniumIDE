#include <QtWidgets/QShortcut>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QFileDialog>
#include <QtCore/QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *p) : QMainWindow(p), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    /* register the connections */
    connect(ui->fileButton, &QToolButton::clicked, this, &MainWindow::fileMenuClicked);

    /* populate the shortcuts */
    QShortcut *KBopenShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this);
    QShortcut *KBsaveShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this);
    QShortcut *KBnewDocShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_N), this);

    KBopenShortcut->setAutoRepeat(false);
    KBsaveShortcut->setAutoRepeat(false);
    KBnewDocShortcut->setAutoRepeat(false);

    connect(KBopenShortcut, &QShortcut::activated, this, &MainWindow::open);
    connect(KBsaveShortcut, &QShortcut::activated, this, &MainWindow::save);
    connect(KBnewDocShortcut, &QShortcut::activated, this, &MainWindow::newDocument);
    ui->tabWidget->removeTab(1);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::fileMenuClicked() {
    QMenu *menu=new QMenu();
    menu->setObjectName("fileMenu");
    menu->setStyleSheet("#fileMenu{ background-color: rgb(88, 88, 88); border:none; color:white; width:200px;} \n #fileMenu::item:selected {color:white; background-color: rgb(12, 94, 176); }");
    QPoint p = ui->fileButton->pos();

    QRect widgetRect = ui->centralwidget->geometry();
    widgetRect.moveTopLeft(ui->centralwidget->parentWidget()->mapToGlobal(widgetRect.topLeft()));

    menu->move(widgetRect.topLeft().x() + p.x(), widgetRect.topLeft().y()+ ui->frame->size().height()-2);
    QAction *newAction = menu->addAction("New");
    connect(newAction, &QAction::triggered, this, &MainWindow::newDocument);

    QAction *openAction =  menu->addAction("Open");
    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    menu->addSeparator();

    QAction *saveAction = menu->addAction("Save");
    connect(saveAction, &QAction::triggered, this, &MainWindow::save);

    menu->show();
}

void MainWindow::save() {
    QFileDialog *select = new QFileDialog();
    QString line;
    select->setLabelText(QFileDialog::Accept, QString("Save"));
    QString fileLocation = select->getSaveFileName(this,"Save","","TI-84+CE Programming (*.asm *.c *.txt *.h *.inc)");
    QFile data(fileLocation);
    ui->textEdit->clear();
    if (data.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&data);
        stream << ui->textEdit->toPlainText();
    }
}

void MainWindow::open() {
    QFileDialog  *select = new QFileDialog();
    QString fileLocation = select->getOpenFileName(this,"Save","","TI-84+CE Programming (*.asm *.c *.txt *.h *.inc)");
    QTabWidget *tabs = ui->tabWidget;
    QWidget *newTab = new QWidget();
    QTextEdit *textEdit = new QTextEdit();
    QLayout *l = new QGridLayout(newTab);
    l->setContentsMargins(0,0,0,0);
    textEdit->setParent(newTab);
    textEdit->setFocusPolicy(Qt::ClickFocus);
    textEdit->setStyleSheet("color:white;");
    newTab->setLayout(l);

    QFile file(fileLocation);

    if(file.open(QIODevice::ReadOnly)) {
        QTextStream instream(&file);
        QString line = instream.readAll();
        file.close();

        tabs->addTab(newTab,"Document");
        textEdit->setText(line);
    }
}

void MainWindow::newDocument() {
    QTabWidget *tabs = ui->tabWidget;
    QWidget *newTab = new QWidget();
    QTextEdit *textEdit = new QTextEdit();
    newTab->setStyleSheet("border 1px solid red;");
    newTab->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    textEdit->setStyleSheet("color:white;");
    textEdit->setFocusPolicy(Qt::ClickFocus);
    textEdit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    QLayout* layout = new QVBoxLayout(newTab);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(textEdit);

    int tabNumber = tabs->addTab(newTab,"New Document");
    tabs->setCurrentIndex(tabNumber);
}
