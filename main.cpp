#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "level.h"
#include "tester.h"
#include "solver.h"

#include <QDebug>

//  9:17 - 12:00
// 13:06 - 15:30

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    Level level;
    Tester tester;
    Solver solver;
    level.loadFromXML("c:\\Users\\PZsol\\Desktop\\Pipes\\level2_solved.xml");
    solver.setLevel(&level);
    Level* s = solver.getNextSolution();
    s->saveToPNG("c:\\Users\\PZsol\\Desktop\\Pipes\\output.png");
    if (tester.test(s, "red")) {
        qDebug() << "Jó!";
    } else {
        qDebug() << "Nem jó... :(";
    }

//    QList<Level*> solutions;
//    Level s = solver.getNextSolution();
//    while(s != nullptr) {
//        if (tester.test(s)) {
//            solutions.append(s);
//        }

//        s = solver.getNextSolution();
//    }

    // TODO: megnézni, hogy melyik a legjobb


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
