#include "mainwindow.h"
#include <QApplication>
#include "./gamelogic/Controller_structs.h"
#include "./gamelogic/Controller.h"


Q_DECLARE_METATYPE(CPlayers);
int id1 = qRegisterMetaType<CPlayers>();

Q_DECLARE_METATYPE(CSessions);
int id2 = qRegisterMetaType<CSessions>();

Q_DECLARE_METATYPE(CMugs);
int id3 = qRegisterMetaType<CMugs>();

Q_DECLARE_METATYPE(Con::CLoopStates);
int id4 = qRegisterMetaType<Con::CLoopStates>();


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}


//#include <QCoreApplication>
//#include <iostream>
//#include "gamelogic/global_func.h"
//#include "gamelogic/Game.h"
//using namespace std;

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);


//    /*
//     * Das Game läuft eigentlich, aber QT verschluckt sich an dem 'SetCodePageGerman', welches
//     * auch an anderen Stellen der Programmes verwendet wird. Dabei terminiert es.
//     * Daher muß man dazu den Funktionsrumpf von 'SetCodePageGerman' auskommentieren.
//     * Aber jedes schreiben auf die Console erzeugt eine neue Console, daher blitzt es nur
//     * so durch die Gegend.
//     * Daran denken, daß die Konsole im Projekt aktiviert sein muß.
//     * Und außerdem
//     * CONFIG += console       // For Console Output in der *.pro - Datein einstellen.
//     */
//    cnst::ClearScreen();
//    cnst::SetCodePageGerman();
//    cout << "'Nimm-Spiel'" << endl;
//    Game* pGame = new Game();
//    pGame->Play();
//    delete pGame; pGame = nullptr;

//    return a.exec();
//}
