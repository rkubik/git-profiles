#include "config.h"
#include "window.h"

#include <QtWidgets>
#include <QtGui>
#include <QtCore>

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
    QIcon select_icon(":/resources/icons/select.svg");

    qDebug() << "Reading configuration from:" << config;

    QSettings settings(config, QSettings::IniFormat);

    foreach (const QString &profileName, settings.childGroups()) {
        Profile profile(profileName);
        QAction *action;

        settings.beginGroup(profileName);
        foreach (const QString &profileSetting, settings.childKeys()) {
            profile.addSetting(profileSetting, settings.value(profileSetting, "").toString());
        }
        settings.endGroup();

        action = new QAction(tr("&Quit"), this);
        action->setIcon(select_icon);
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
