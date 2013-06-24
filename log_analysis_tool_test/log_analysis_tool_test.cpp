#include <QtTest/QtTest>
#include "log_analysis_tool.h"

class log_analysis_tool_test: public QObject
{
    Q_OBJECT

private slots:
    void constructor_test();
    void set_rgEprStr_test();
    void set_filename_test();

    void initTestCase()
    {

    }

    void cleanupTestCase()
    {

    }
};

void log_analysis_tool_test::constructor_test()
{
  int argc = 3;
  const char *argv[] = {"lat","green|yellow|blue","log.txt"};
  log_analysis_tool *lat_p= new log_analysis_tool(argc, argv);
  QCOMPARE(lat_p->get_filename(),"log.txt");
  QCOMPARE(lat_p->get_rgEprStr(),"green|yellow|blue");

}

void log_analysis_tool_test::set_filename_test()
{
    int argc = 3;
    const char *argv[] = {"lat","green|yellow|blue","log.txt"};
    log_analysis_tool *lat_p= new log_analysis_tool(argc, argv);
    lat_p->set_filename("log1.txt");
    QCOMPARE(lat_p->get_filename(),"log1.txt");
}


void log_analysis_tool_test::set_rgEprStr_test()
{
    int argc = 3;
    const char *argv[] = {"lat","green|yellow|blue","log.txt"};
    log_analysis_tool *lat_p= new log_analysis_tool(argc, argv);
    lat_p->set_rgEprStr("red|underline");
    QCOMPARE(lat_p->get_rgEprStr(),"red|underline");
}


QTEST_MAIN(log_analysis_tool_test)
#include "log_analysis_tool_test.moc"
