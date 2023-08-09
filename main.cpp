#include "mylineedit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyLineEdit lineedit(argv[1]);
    lineedit.show();

    return a.exec();
}
