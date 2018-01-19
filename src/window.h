#ifndef WINDOW_H
#define WINDOW_H

#include "config.h"

#include <QtWidgets>
#include <QtCore>

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
