#include <QApplication>

#include <string>

#include "MainWindow.hpp"
#include "MainWindowController.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    
    // Create the window and controller
    MainWindow* window = new MainWindow();
    MainWindowController* controller = new MainWindowController(window);

    // Pass all events to the controller
    app.installEventFilter(controller);

    // Show the window
    window->resize(1350, 850);
    window->setWindowTitle("Path Tracer");
    window->show();
    
    return app.exec();
}
