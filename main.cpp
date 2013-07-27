//#include <QCoreApplication>

#include "log_analysis_tool.h"

int main(int argc, const char *argv[])
{
//    QCoreApplication a(argc, argv);

//    return a.exec();

    log_analysis_tool lat(argc, argv);
    if ( argc > 3 )  lat.run_filter();
    return 0;
}
