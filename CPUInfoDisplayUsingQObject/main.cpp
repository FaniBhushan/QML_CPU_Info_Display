#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QDebug>
#include "stringlistmodel.h"

//Macro declaration
#define MAIN_QML_SOURCE_FILE "qrc:///main.qml"
#define CPU_INFO_LIST_FILE "/proc/cpuinfo"


int main(int argc, char *argv[])
{
    QGuiApplication mainGUIapp(argc, argv);
    QQmlApplicationEngine mainEngine;

    //Pointer to mainEngine's root using which the rootContext can be manipulated
    QQmlContext* engineRootContext = mainEngine.rootContext();

    //StringListModel instantiation to be used to red the cpuinfo file and constructs the QStringListModel object
    StringListModel listModel;
    bool status = listModel.fetchCPUInfo(CPU_INFO_LIST_FILE);//reading the cpuinfo file and constructing the QStringListModel object
    if(status)
    {
        engineRootContext->setContextObject(&listModel);  //settingthe context object for the mainEngine's rootContext

        mainEngine.load(QUrl(MAIN_QML_SOURCE_FILE));      //Loading the QML file

        return mainGUIapp.exec();
    }
    else
    {
        QDebug()<<"cpuinfo file could not be read sucessfully";
        return -1;
    }
}
