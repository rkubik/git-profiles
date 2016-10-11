#include "config.h"
#include "window.h"

#if QT5
#   include <QtWidgets/qapplication.h>
#   include <QtWidgets/qmessagebox.h>
#elif QT4
#   include <QtGui/qapplication.h>
#   include <QtGui/qmessagebox.h>
#endif

int main(int argc, char *argv[])
{
    // Q_INIT_RESOURCE(systray);

    QApplication app(argc, argv);

    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
            QObject::tr("I couldn't detect any system tray on this system."));
        return 1;
    }
    QApplication::setQuitOnLastWindowClosed(false);

    Window window;
    return app.exec();
}
