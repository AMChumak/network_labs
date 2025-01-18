#include "searchbtnmodel.h"
#include <iostream>

SearchBtnModel::SearchBtnModel(QObject* parent)
    : QObject{parent}
{
}

void SearchBtnModel::onSearchBtnPressed(QString arg)
{
    std::cout << "Hello from btn" << std::endl;
    emit update();
}
