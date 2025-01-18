#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "searchbtnmodel.h"
#include "tablemodel.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    qmlRegisterType<SearchBtnModel>("btnMdl", 1, 0, "SearchButtonModel");
    qmlRegisterType<TableModel>("tblMdl", 1, 0, "CustomTableModel");
    const QUrl url(QStringLiteral("qrc:/Pokemons/Main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app,
                     []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
