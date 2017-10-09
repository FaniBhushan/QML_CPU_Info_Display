/**
* @brief strinlistgmodel.cpp
* This is the source file which contains the definitions of the functions of the StringListModel class.
*/

#include "stringlistmodel.h"

/**
* @brief StringListModel
* This is the constructor for the StringListModel class
* @return
* none
*/
StringListModel::StringListModel()
{
    m_cpuInfoList = new QStringListModel;
}

/**
* @brief getListModel
* This is the get function which reads the property value
* @return
* QStringListModel* : pointer the QStringListModel which acts as the value of property
*/
QStringListModel* StringListModel::getListModel()const
{
   return m_cpuInfoList;
}

/**
* @brief fetchCPUInfo
* This is a utility function which reads the "/proc/cpuinfo" file line by line, formats it and stores the contents in the return list
* @param
* fileName: file name to be read to create the resultant list
* @return
* QStringList: list of CPU Info file entries
*/
bool StringListModel::fetchCPUInfoList(QString fileName)
{
    bool l_status = true;
    QStringList l_listCPUInfo;
    QFile l_procCPUInfo(fileName); //file handle for cpuinfo file
    if(l_procCPUInfo.open(QIODevice::ReadOnly))
    {
        QTextStream l_dataStream(&l_procCPUInfo);
        QString l_line;
        do
        {
            /*This loop reads each line from cpuinfo file ata a time.
            format it by separating it as property of the CPU vs it's value.
            Once formatted, it stores it in the listCPUInfo*/
            l_line = l_dataStream.readLine(); //read line
            QStringList l_lineSplitData = l_line.split(":"); //split each line based on ":" into proerty vs value
            QString l_property,l_value;
            if(l_lineSplitData.length() == 2)
            {
                l_property = l_lineSplitData[0].trimmed();
                l_value = l_lineSplitData[1].trimmed();
            }
            else if(l_lineSplitData.length() == 1)
            {
                l_property = l_lineSplitData[0].trimmed();
                l_value = "";
            }
            if(!l_property.isEmpty())
            {
                l_property.append(QString("").fill(' ',MAXWIDTH-l_property.length())); //fill the trailing empty spaces for better view
                l_listCPUInfo << l_property+"\t"+":"+"\t"+l_value; //Format the display string and insert it in the return list
            }
        }while(!l_line.isNull());
        l_procCPUInfo.close();
    }
    else
    {
        l_status = false;
        l_listCPUInfo<<"ERROR IN OPENING FILE: " << l_procCPUInfo.errorString();
    }

    m_cpuInfoList->setStringList(l_listCPUInfo);
    return l_status;
}

