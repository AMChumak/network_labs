/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#include <imagemodel.h>
#include <tablemodel.h>

#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif

Q_QMLTYPE_EXPORT void qml_register_types_Pokemons()
{
    qmlRegisterTypesAndRevisions<ImageModel>("Pokemons", 1);
    QMetaType::fromType<QAbstractTableModel *>().id();
    qmlRegisterTypesAndRevisions<TableModel>("Pokemons", 1);
    qmlRegisterAnonymousType<QAbstractItemModel, 254>("Pokemons", 1);
    qmlRegisterModule("Pokemons", 1, 0);
}

static const QQmlModuleRegistration registration("Pokemons", qml_register_types_Pokemons);
