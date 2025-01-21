/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>



#if !defined(QT_STATIC)
#define Q_QMLTYPE_EXPORT Q_DECL_EXPORT
#else
#define Q_QMLTYPE_EXPORT
#endif
Q_QMLTYPE_EXPORT void qml_register_types_snake_gui()
{
    QT_WARNING_PUSH QT_WARNING_DISABLE_DEPRECATED
    QT_WARNING_POP
    qmlRegisterModule("snake_gui", 1, 0);
}

static const QQmlModuleRegistration snakeguiRegistration("snake_gui", qml_register_types_snake_gui);
