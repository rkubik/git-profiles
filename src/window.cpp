#include <QtGui/qapplication.h>
#include <QtGui/qgridlayout.h>
#include <QtGui/qmessagebox.h>
#include <Qt/qevent.h>
#include <Qt/qsettings.h>
#include <Qt/qdir.h>
#include <Qt/qdebug.h>
#include <Qt/qprocess.h>

#include "window.h"

Window::Window() : windowTitle("Git Profiles")
{
    createProfileGroupBox();
    createSettingsGroupBox();

    createActions();
    createTrayIcon();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
    connect(profileComboBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(setProfile(int)));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(profileGroupBox);
    mainLayout->addWidget(settingsGroupBox);
    setLayout(mainLayout);

    trayIcon->show();

    //setWindowFlags(windowFlags() | ~Qt::WindowMaximizeButtonHint);
    loadProfiles();

    setWindowTitle(windowTitle);
    resize(400, 300);
}

void Window::setVisible(bool visible)
{
    QDialog::setVisible(visible);
}

void Window::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}

void Window::loadProfiles()
{
    const QString config = QDir::homePath() + QDir::separator() +
        ".git-profiles";

    qDebug() << "Reading configuration from: " << config;

    QSettings settings(config, QSettings::IniFormat);

    foreach (const QString &profileName, settings.childGroups()) {
        Profile profile(profileName);

        settings.beginGroup(profileName);
        foreach (const QString &profileSetting, settings.childKeys()) {
            profile.addSetting(profileSetting, settings.value(profileSetting, "").toString());
        }
        settings.endGroup();

        profiles.push_back(profile);

        profileComboBox->addItem(profileName);
    }
}

void Window::setProfile(int index)
{
    if (index < 0 || (unsigned int) index >= profiles.size())
        return;

    QProcess process;

    foreach (const QString &profileSetting, profiles[index].settings.keys()) {
        qDebug() << "Setting: " << profileSetting << " => " << profiles[index].settings[profileSetting];

        process.start("git", QStringList()
            << "config"
            << "--global"
            << profileSetting
            << profiles[index].settings[profileSetting]);

        if (!process.waitForFinished())
            qDebug() << "Failed to set: " << profileSetting;
    }

    const QString profileLabel = "Profile: " + profiles[index].name;

    trayIcon->setToolTip(profileLabel);
    restoreAction->setText(profileLabel);
}

void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
        case QSystemTrayIcon::Trigger:
        case QSystemTrayIcon::DoubleClick:
        case QSystemTrayIcon::MiddleClick:
            showNormal();
            break;
        default:
            break;
    }
}

void Window::createProfileGroupBox()
{
    profileGroupBox = new QGroupBox(tr("Current Profile"));

    profileComboBox = new QComboBox;

    QHBoxLayout *profileLayout = new QHBoxLayout;

    profileLayout->addWidget(profileComboBox);

    profileGroupBox->setLayout(profileLayout);
}

void Window::createSettingsGroupBox()
{
    settingsGroupBox = new QGroupBox(tr("Settings"));

    QHBoxLayout *profileLayout = new QHBoxLayout;

    settingsGroupBox->setLayout(profileLayout);
}

void Window::createActions()
{
    restoreAction = new QAction(tr("&Profile"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void Window::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    QIcon icon(":/resources/icons/person.svg");

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);

    trayIcon->setContextMenu(trayIconMenu);

    setWindowIcon(icon);
}
