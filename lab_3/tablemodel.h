#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QObject>
#include <QQmlEngine>
#include <qqml.h>
#include <QAbstractTableModel>
#include <QNetworkAccessManager>


class TableModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_PROPERTY(QString name  READ getName WRITE setName NOTIFY nameChanged)
    QML_ELEMENT

public:
    int rowCount(const QModelIndex & = QModelIndex()) const override;

    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QString getName() const;

    void setName(QString newName);

    QVariant data(const QModelIndex &index, int role) const override;

    QHash<int, QByteArray> roleNames() const override;


public slots:
    void searchStats(const QString &name);
    void parseData();
    void onUpdate(QString name);
signals:
    void nameChanged(QString);

private:
    int weight = 6;
    int height = 4;
    int experience = 112;
    QNetworkAccessManager networkManager;
    QNetworkReply *reply = nullptr;
    std::string name;

};

#endif // TABLEMODEL_H
