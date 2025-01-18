#include "tablemodel.h"
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>

int TableModel::rowCount(const QModelIndex&) const
{
    return 3;
}

int TableModel::columnCount(const QModelIndex&) const
{
    return 2;
}

QString TableModel::getName() const
{
    return QString(name.c_str());
}

void TableModel::setName(QString newName)
{
    name = newName.toStdString();
    emit nameChanged(QString(name.c_str()));
}

QVariant TableModel::data(const QModelIndex& index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole:
        if (index.column() == 1)
        {
            switch (index.row())
            {
            case 0: return QString("%1").arg(height);
            case 1: return QString("%1").arg(weight);
            case 2: return QString("%1").arg(experience);
            default: return QVariant();
            }
        }
        else
        {
            switch (index.row())
            {
            case 0: return QString("Height");
            case 1: return QString("Weight");
            case 2: return QString("Experience");
            default: return QVariant();
            }
        }
    default:
        break;
    }

    return QVariant();
}

QHash<int, QByteArray> TableModel::roleNames() const
{
    return {{Qt::DisplayRole, "display"}};
}

void TableModel::searchStats(const QString& name)
{
    if (!name.trimmed().isEmpty())
    {
        if (reply)
        {
            reply->abort();
            reply->deleteLater();
            reply = nullptr;
        }
        const QString& queryUrlStr = "https://pokeapi.co/api/v2/pokemon/";

        QUrlQuery query;
        query.addQueryItem("format", "json");
        reply = networkManager.get(QNetworkRequest(queryUrlStr + name.trimmed().toLower()));
        connect(reply, &QNetworkReply::finished, this, &TableModel::parseData);
    }
}

void TableModel::parseData()
{
    if (reply->error() == QNetworkReply::NoError)
    {
        beginResetModel();
        weight = 0;
        height = 0;
        experience = 0;
        QByteArray data = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(data);
        weight = jsonDocument["weight"].toInt();
        height = jsonDocument["height"].toInt();
        experience = jsonDocument["base_experience"].toInt();
        name = jsonDocument["name"].toString().toStdString();
        endResetModel();
        emit nameChanged(QString{name.c_str()});
    }
    else
    {
        beginResetModel();
        weight = 0;
        height = 0;
        experience = 0;
        name = "Pokemon not found :(";
        endResetModel();
        emit nameChanged(QString{name.c_str()});
    }
    reply->deleteLater();
    reply = nullptr;
}

void TableModel::onUpdate(QString name)
{
    searchStats(name);
}
