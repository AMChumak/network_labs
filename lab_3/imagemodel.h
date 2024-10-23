#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include <QObject>
#include <QQmlEngine>

class ImageModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit ImageModel(QObject *parent = nullptr);    

signals:
    void imageUpdated();
};

#endif // IMAGEMODEL_H
