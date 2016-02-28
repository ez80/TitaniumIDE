#include <QtWidgets/QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName(QStringLiteral("titanium-dev"));
    QCoreApplication::setApplicationName(QStringLiteral("TitaniumIDE"));
    app.setAttribute(Qt::AA_UseHighDpiPixmaps);

    MainWindow TitaniumIDE;
    TitaniumIDE.show();

    return app.exec();
}
