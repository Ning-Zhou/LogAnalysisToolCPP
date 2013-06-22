
#include <QtTest/QtTest>
#include "log_analysis_tool.h"

class log_analysis_tool_test: public QObject
{
    Q_OBJECT

private slots:
    void constructor_test();
};

void log_analysis_tool_test::constructor_test()
{
  int argc = 3;
  char *argv[] = {"lat","green|yellow|blue","log.txt"};
  log_analysis_tool *lat_p= new log_analysis_tool(argc, argv);
  QCOMPARE(lat_p->get_filename(),"log.txt");
  QCOMPARE(lat_p->get_rgEprStr(),"green|yellow|blue");
}

QTEST_MAIN(log_analysis_tool_test)
#include "log_analysis_tool_test.moc"
