#include "titanium.h"
#include "ui_titanium.h"
#include <QMenu>
#include <QFileDialog>
#include <QTextStream>

titanium::titanium(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::titanium)
{
    ui->setupUi(this);


    QAction *openKBShortcut = new QAction(this);
    openKBShortcut->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    openKBShortcut->setShortcutContext(Qt::ApplicationShortcut);
    ui->centralWidget->addAction(openKBShortcut);
    connect(openKBShortcut, SIGNAL(triggered()), this, SLOT(open()));

    QAction *saveKBShortcut = new QAction(this);
    saveKBShortcut->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    saveKBShortcut->setShortcutContext(Qt::ApplicationShortcut);
    ui->centralWidget->addAction(saveKBShortcut);
    connect(saveKBShortcut, SIGNAL(triggered()), this, SLOT(save()));

    QAction *newKBShortcut = new QAction(this);
    newKBShortcut->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    newKBShortcut->setShortcutContext(Qt::ApplicationShortcut);
    ui->centralWidget->addAction(newKBShortcut);
    connect(newKBShortcut, SIGNAL(triggered()), this, SLOT(newDocument()));
}

titanium::~titanium()
{
    delete ui;
}

void titanium::on_fileButton_clicked()
{
    QMenu *menu=new QMenu();
    menu->setObjectName("fileMenu");
    menu->setStyleSheet("#fileMenu{ background-color: rgb(88, 88, 88); border:none; color:white; width:200px;} \n #fileMenu::item:selected {color:white; background-color: rgb(12, 94, 176); }");
    QPoint p = ui->fileButton->pos();

    QRect widgetRect = ui->centralWidget->geometry();
    widgetRect.moveTopLeft(ui->centralWidget->parentWidget()->mapToGlobal(widgetRect.topLeft()));

    menu->move(widgetRect.topLeft().x() + p.x(), widgetRect.topLeft().y()+ ui->frame->size().height()-2);
    QAction *newAction = menu->addAction("New");
    connect(newAction, SIGNAL(triggered()), this, SLOT(newDocument()));

    QAction *openAction =  menu->addAction("Open");
    connect(openAction, SIGNAL(triggered()), this, SLOT(open()));

    menu->addSeparator();

    QAction *saveAction = menu->addAction("Save");
    connect(saveAction, SIGNAL(triggered()), this, SLOT(save()));

    menu->show();
}
void titanium::save() {
    QFileDialog  *select = new QFileDialog();
    select->setLabelText(QFileDialog::Accept, QString("Save"));
    QString fileLocation = select->getSaveFileName(this,"Save","","TI-84+CE Programming (*.asm *.c *.txt *.h *.inc)");
    QFile data(fileLocation);
    if (data.open(QFile::WriteOnly)) {
        QTextStream out(&data);
        out << ui->textEdit->toPlainText();
    }
}
void titanium::open() {
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

    tabs->addTab(newTab,"Document");

}
void titanium::newDocument() {
    QFileDialog  *select = new QFileDialog();
    QTabWidget *tabs = ui->tabWidget;
    QWidget *newTab = new QWidget();
    QTextEdit *textEdit = new QTextEdit();
    QLayout *l = new QHBoxLayout (newTab);
    l->setContentsMargins(0,0,0,0);
    newTab->setStyleSheet("border 1px solid red;");
    textEdit->setParent(newTab);
    textEdit->setFocusPolicy(Qt::ClickFocus);
    textEdit->setStyleSheet("color:white;");
    newTab->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    textEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    newTab->setLayout(l);

    //textEdit->setFrameStyle(0);
    int tabNumber = tabs->addTab(newTab,"New Document");
    tabs->setCurrentIndex(tabNumber);
}
