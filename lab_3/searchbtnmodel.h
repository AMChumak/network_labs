#ifndef SEARCHBTNMODEL_H
#define SEARCHBTNMODEL_H

#include <QObject>

class SearchBtnModel : public QObject
{
    Q_OBJECT
public:
    explicit SearchBtnModel(QObject *parent = nullptr);


public slots:
    void onSearchBtnPressed(QString arg);
signals:
    void update();
};

#endif // SEARCHBTNMODEL_H
