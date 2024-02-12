#include "recordtable.h"
#include <QHBoxLayout>

recordTable::recordTable(QWidget *parent)
    : QWidget(parent)
    , record(new QTableWidget)
{
    initalRecord();
}

recordTable::~recordTable()
{
    /* 释放 */
    delete record;
}

/* 返回记录的总数 */
int recordTable::count() const
{
    return sumOfRecords;
}

/* 添加记录 */
void recordTable::addRecord(const QStringList &record)
{
    if(record.isEmpty())
        return;
    this->record->setRowCount(sumOfRecords+1);
    for(int i=0;i<record.length()&&i<coloumns;i++)
        this->record->setItem(sumOfRecords,i,new QTableWidgetItem(record[i]));
    sumOfRecords++;
}

/* 设置记录的列标题 */
void recordTable::setTableTitle(const QStringList& title)
{
    if(title.isEmpty())
        return;
    titleList=title;
    coloumns=title.length();
    record->setColumnCount(coloumns);
    record->setHorizontalHeaderLabels(title);
}

/* 初始化记录 */
void recordTable::initalRecord()
{
    QHBoxLayout* layout=new QHBoxLayout(this);
    layout->addWidget(record);
    record->setEditTriggers(QAbstractItemView::NoEditTriggers);
    sumOfRecords=0;
}

/* 清空记录 */
void recordTable::clear()
{
    record->clear();
    record->setHorizontalHeaderLabels(titleList);
    sumOfRecords=0;
    record->setRowCount(sumOfRecords);
}