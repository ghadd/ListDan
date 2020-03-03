#include "listdan.h"
#include "list.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ListDan w;
    w.show();

    return a.exec();
}
