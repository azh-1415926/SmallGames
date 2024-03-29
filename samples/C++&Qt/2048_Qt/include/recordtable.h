#pragma once
#include <QWidget>
#include <QTableWidget>

class recordTable : public QWidget {
    Q_OBJECT

    public:
        explicit recordTable(QWidget* parent=nullptr);
        ~recordTable();
        int count() const;

    public slots:
        void setTableTitle(const QStringList& title);
        void addRecord(const QStringList& record);
        void clear();
    
    signals:
        ;

    private:
        QStringList titleList;
        QTableWidget* record;
        int sumOfRecords;
        int coloumns;
        void initalRecord();
};