#ifndef WINDOW_H
#define WINDOW_H

#include "config.h"

#if QT == 5
#   include <QtWidgets/qsystemtrayicon.h>
#   include <QtWidgets/qdialog.h>
#   include <QtWidgets/qaction.h>
#   include <QtWidgets/qcheckbox.h>
#   include <QtWidgets/qcombobox.h>
#   include <QtWidgets/qgroupbox.h>
#   include <QtWidgets/qlabel.h>
#   include <QtWidgets/qlineedit.h>
#   include <QtWidgets/qmenu.h>
#   include <QtWidgets/qpushbutton.h>
#   include <QtWidgets/qspinbox.h>
#   include <QtWidgets/qtextedit.h>
#   include <QtWidgets/qtextedit.h>
#   include <QtCore/qobjectdefs.h>
#   include <QtCore/qstring.h>
#   include <QtCore/qmap.h>
#   include <QtCore/qvector.h>
#elif QT == 4
#   include <QtGui/qsystemtrayicon.h>
#   include <QtGui/qdialog.h>
#   include <QtGui/qaction.h>
#   include <QtGui/qcheckbox.h>
#   include <QtGui/qcombobox.h>
#   include <QtGui/qgroupbox.h>
#   include <QtGui/qlabel.h>
#   include <QtGui/qlineedit.h>
#   include <QtGui/qmenu.h>
#   include <QtGui/qpushbutton.h>
#   include <QtGui/qspinbox.h>
#   include <QtGui/qtextedit.h>
#   include <QtGui/qtextedit.h>
#   include <Qt/qstring.h>
#   include <Qt/qmap.h>
#   include <Qt/qvector.h>
#endif

class QAction;
class QCheckBox;
class QComboBox;
class QGroupBox;
class QLabel;
class QLineEdit;
class QMenu;
class QPushButton;
class QSpinBox;
class QTextEdit;

struct Profile {
    QString name;
    QMap<QString, QString> settings;

    Profile()
    {
    }

    Profile(QString n) : name(n)
    {
    }

    void addSetting(const QString &key, const QString &value)
    {
        settings[key] = value;
    }
};

class Window : public QDialog
{
    Q_OBJECT

public:
    Window();
    virtual ~Window();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void setProfile(int index);
    void actionSelected(QAction *action);

private:
    void clearProfileIcon();
    void createProfiles();
    void createActions();
    void createTrayMenu();
    void createTrayIcon();

    QVector<QAction*> profileActions;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QVector<Profile> profiles;
};

#endif
