#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <map>

#include <QtGui/qsystemtrayicon.h>
#include <QtGui/qdialog.h>
#include <QtGui/qaction.h>
#include <QtGui/qcheckbox.h>
#include <QtGui/qcombobox.h>
#include <QtGui/qgroupbox.h>
#include <QtGui/qlabel.h>
#include <QtGui/qlineedit.h>
#include <QtGui/qmenu.h>
#include <QtGui/qpushbutton.h>
#include <QtGui/qspinbox.h>
#include <QtGui/qtextedit.h>
#include <QtGui/qtextedit.h>
#include <Qt/qstring.h>
#include <Qt/qmap.h>

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
    virtual ~Window() {};

    void setVisible(bool visible);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void setProfile(int index);

private:
    void loadProfiles();
    void createProfileGroupBox();
    void createSettingsGroupBox();
    void createActions();
    void createTrayIcon();

    QGroupBox *profileGroupBox;
    QComboBox *profileComboBox;

    QGroupBox *settingsGroupBox;

    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    QString windowTitle;

    std::vector<Profile> profiles;
};

#endif
