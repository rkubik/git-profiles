#include "config.h"
#include "window.h"

#if QT == 5
#   include <QtWidgets/qapplication.h>
#   include <QtGui/qevent.h>
#   include <QtCore/qsettings.h>
#   include <QtCore/qdir.h>
#   include <QtCore/qdebug.h>
#   include <QtCore/qprocess.h>
#elif QT == 4
#   include <QtGui/qapplication.h>
#   include <QtGui/qgridlayout.h>
#   include <QtGui/qmessagebox.h>
#   include <Qt/qevent.h>
#   include <Qt/qsettings.h>
#   include <Qt/qdir.h>
#   include <Qt/qdebug.h>
#   include <Qt/qprocess.h>
#endif

static QIcon _select_icon;

Window::Window()
{
    createActions();
    createTrayMenu();
    createProfiles();
    createTrayIcon();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    connect(trayIconMenu, SIGNAL(triggered(QAction*)),
            this, SLOT(actionSelected(QAction*)));

    setProfile(0);

    trayIcon->show();
}

Window::~Window()
{
}

void Window::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}

void Window::createProfiles()
{
    const QString config = QDir::homePath() + QDir::separator() +
        ".git-profiles";

    qDebug() << "Reading configuration from:" << config;

    QSettings settings(config, QSettings::IniFormat);

    _select_icon = QIcon(":/resources/icons/select.svg");

    foreach (const QString &profileName, settings.childGroups()) {
        Profile profile(profileName);

        settings.beginGroup(profileName);
        foreach (const QString &profileSetting, settings.childKeys()) {
            profile.addSetting(profileSetting, settings.value(profileSetting, "").toString());
        }
        settings.endGroup();

        QAction *action = new QAction(tr("&Quit"), this);
#if QT == 5
        action->setIcon(_select_icon);
#endif
	action->setIconVisibleInMenu(false);
        action->setText(profileName);
        action->setData(profiles.size());

        trayIconMenu->addAction(action);
        profiles.push_back(profile);
        profileActions.push_back(action);
    }

    qDebug() << "Loaded" << profiles.size() << "profiles";
}

void Window::clearProfileIcon()
{
    foreach (QAction *profileAction, profileActions) {
#if QT == 4
        profileAction->setIcon(QIcon());
#endif
        profileAction->setIconVisibleInMenu(false);
    }
}

void Window::actionSelected(QAction *action)
{
    if (action->data().isNull()) {
        return;
    }

    setProfile(action->data().toInt());
}

void Window::setProfile(int index)
{
    QProcess process;

    if (index < 0 || index >= profiles.size()) {
        return;
    }

    qDebug() << "Selecting profile" << index << profiles[index].name;

    foreach (const QString &profileSetting, profiles[index].settings.keys()) {
        process.start("git", QStringList()
            << "config"
            << "--global"
            << profileSetting
            << profiles[index].settings[profileSetting]);

        if (!process.waitForFinished()) {
            qDebug() << "Failed setting:" << profileSetting;
        }
    }

    clearProfileIcon();
#if QT == 4
    profileActions[index]->setIcon(_select_icon);
#endif
    profileActions[index]->setIconVisibleInMenu(true);
    trayIcon->setToolTip(profiles[index].name);
}

void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
        case QSystemTrayIcon::MiddleClick:
        default:
            break;
    }
}

void Window::createActions()
{
    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void Window::createTrayMenu()
{
    trayIconMenu = new QMenu(this);
}

void Window::createTrayIcon()
{
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    QIcon icon(":/resources/icons/person.svg");

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);

    trayIcon->setContextMenu(trayIconMenu);

    setWindowIcon(icon);
}
