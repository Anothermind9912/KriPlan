#ifndef DATATYPES_H
#define DATATYPES_H

#include <QString>
#include <QDate>
#include <QtTypes>
#include <QVector>

enum workType{
    plugType = 0,
    Course = 1,
    Diploma = 2,
    Other = 3
};

enum statusWork{
    plugWork = 0,
    NotStarted = 1,
    InDevelopment = 2,
    Finished = 3
};

enum statusPay{
    plugPay = 0,
    NotPaid = 1,
    Advance = 2,
    PaidInFull = 3,
};

struct AttachedFile{
    int id;
    QString fileName;
    QString filePath;
    qint64 fileSize;
    QDateTime uploadDate;
    QString mimeType;
};


struct Task{
    int id;
    QString title;
    workType type;
    int priority;
    QString description;
    QDateTime deadline;
    statusWork statuswork;
    statusPay statusPay;
    QString notes;
    QVector<AttachedFile> AttachedFiles;
};



#endif // DATATYPES_H
