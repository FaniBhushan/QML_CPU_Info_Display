#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H

/**
* @brief stringlistmodel.h
* This is the header file for object class meant for instantiation of the QObject type
* Add this header to be able to use this class functions.
*/

#include <QObject>
#include <QtQml>

//Macro declaration
#define MAXWIDTH 20

class StringListModel : public QObject
{
Q_OBJECT

//declaration of properties
Q_PROPERTY(QAbstractItemModel *listModel READ getListModel NOTIFY modelChanged)

public:
    explicit StringListModel(void);             //Constructor
    QStringListModel* getListModel()const;      //Function for reading and returning the listmodel property
    bool fetchCPUInfoList(QString fileName);                    //Function for reading the cpuinfo file and constructing the Qstringlistmodel object

signals:
    void modelChanged();                        //notify signal for the lisModel property

private:
    QStringListModel* m_cpuInfoList;            //member variable to be used as the model to be exported to QML
};

#endif // STRINGLISTMODEL_H
