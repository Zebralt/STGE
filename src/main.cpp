#include "textgame.h"
#include "textgamecontroller.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    ///
    /// \brief registering everything
    ///
    ///

    qmlRegisterType<TextGameController>("textGame", 1, 0, "TextGame");

    ///

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();

//    TextGame tg;
//    if (tg.load("../scenes")) {

//        int i = 0;
//        tg.display();
//        tg.initialize();
//        while (tg.running()) {
//          tg.scene();
//          std::cout << ">";
//          std::cin >> i;
//          tg.proceed(i);
//        }
//    }

}
