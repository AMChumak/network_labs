#include <iostream>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "QFontDatabase"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    //auto font_url = QStringLiteral("qrc:/snake_gui/images/retro.ttf");

    int fontId = QFontDatabase::addApplicationFont("qrc:/snake_gui/images/retro.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/snake_gui/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
