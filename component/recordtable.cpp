#include "recordtable.h"
#include <QHBoxLayout>

recordTable::recordTable(QWidget *parent)
    : QWidget(parent)
    , record(new QTableWidget)
    , sumOfRecords(0)
{
    initalRecord();
}

recordTable::~recordTable()
{
    delete record;
}

int recordTable::count() const
{
    return sumOfRecords;
}

void recordTable::clear()
{
    record->clear();
    record->setHorizontalHeaderLabels(titleList);
    sumOfRecords=0;
    record->setRowCount(sumOfRecords);
}

void recordTable::addRecord(const QStringList &record)
{
    if(record.isEmpty())
        return;
    this->record->setRowCount(sumOfRecords+1);
    for(int i=0;i<record.length()&&i<coloumns;i++)
        this->record->setItem(sumOfRecords,i,new QTableWidgetItem(record[i]));
    sumOfRecords++;
}

void recordTable::setTableTitle(const QStringList& title)
{
    if(title.isEmpty())
        return;
    titleList=title;
    coloumns=title.length();
    record->setColumnCount(coloumns);
    record->setHorizontalHeaderLabels(title);
}

void recordTable::initalRecord()
{
    QHBoxLayout* layout=new QHBoxLayout(this);
    layout->addWidget(record);
    record->setEditTriggers(QAbstractItemView::NoEditTriggers);
}