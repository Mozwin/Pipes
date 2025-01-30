#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "level.h"
#include "tester.h"
#include "solver.h"

#include <QFileInfo>

void writeLine(const QString& text)
{
    QTextStream(stdout) << text.toUtf8() << Qt::endl;
}

void overwrite(const QString& text)
{
    QTextStream(stdout) << text.toUtf8() << "\r";
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
/*
    Level level;
    Tester tester;
    Solver solver;
    if (!level.loadFromXML("c:\\Users\\Csenge\\Desktop\\Pipes\\hello_csap_IKEA\\hello_csap_IKEA_solved.xml")) {
        qDebug() << "Nem lehet beolvasni a megadott fájlt.";
        return 0;
    }

    solver.init(&level);
    Level* s = solver.getNextSolution();

    QString filename = "c:\\Users\\Csenge\\Desktop\\Pipes\\hello_csap_IKEA\\solution.png";

    if (tester.test(s, level.getPhases()->at(0))) {
        writeLine("OK\n");
    }

    s->saveToPNG(filename);

    return 0;
*/

    if (argc < 2) {
        writeLine("Nincs megadva bemeneti fájl.");
        return 0;
    }

    QString filename = argv[1];
    QFileInfo fi(filename);
    QString path = fi.absolutePath();

    Level level;
    Tester tester;
    Solver solver;
    if (!level.loadFromXML(filename.toStdString().c_str())) {
        writeLine("Nem lehet beolvasni a megadott fájlt: " + filename);
        return 0;
    }

    writeLine("Feldolgozás folyamatban...");

    int counter = 0;
    int solution = 0;

    for (int i = 0; i < level.getPhases()->length(); i++) {
        solver.init(&level);
        while (!solver.isFinished()) {
            Level* s = solver.getNextSolution();
            if (s != nullptr) {
                QString filename = path + "\\test" + QString::number(counter).rightJustified(5, '0') + ".png";
//                s->saveToPNG(filename);

                if (tester.test(s, level.getPhases()->at(i))) {
                    writeLine("Level " + QString::number(counter) + ":OK");

                    QString filename = path + "\\solution" + QString::number(solution + 1).rightJustified(2, '0') + ".png";
                    s->saveToPNG(filename);

                    solution++;
                }

                if (counter % 100000 == 0) {
                    overwrite("Counter: " + QString::number(counter));
                }

                counter++;
            }
        }
    }

    if (solution == 0) {
        writeLine("Nem található megoldás.");
    }

    return 0;
}
