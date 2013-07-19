#include <QtTest/QtTest>
#include "log_analysis_tool.h"
#include <sstream>

class log_analysis_tool_test: public QObject
{
    Q_OBJECT	

private slots:
    void constructor_test();
    void set_rgEprStr_test();
    void set_filename_test();

    void initTestCase()
    {
      p_cout_streambuf = cout.rdbuf();
      cout.rdbuf(ss4ut.rdbuf());
    }

    void cleanupTestCase()
    {
      cout.rdbuf(p_cout_streambuf);
    }
private:
    stringstream ss4ut;
    streambuf *p_cout_streambuf;
};

void log_analysis_tool_test::constructor_test()
{
  int argc = 3;
  const char *argv[] = {"lat","green|yellow|blue","log.txt"};

  // test correct input
  log_analysis_tool *lat_p= new log_analysis_tool(argc, argv);
  QCOMPARE(lat_p->get_filename(),"log.txt");
  QCOMPARE(lat_p->get_rgEprStr(),"(green)|(yellow)|(blue)");
  delete lat_p;

  // test incorrect input: only 1 parameter
  argc = 1;
  lat_p= new log_analysis_tool(argc, argv);

  QCOMPARE(ss4ut.str(),string("argc(parameters number) is 1, invalid input\n"));
  delete lat_p;
  ss4ut.str("");//clear the string date in ss4ut

  // test incorrect input: only 2 parameters
  argc = 2;
  lat_p= new log_analysis_tool(argc, argv);
  QCOMPARE(ss4ut.str(),string("argc(parameters number) is 2, invalid input\n"));
  delete lat_p;
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
    QCOMPARE(lat_p->get_rgEprStr(),"(red)|(underline)");
    lat_p->set_rgEprStr("red");
    QCOMPARE(lat_p->get_rgEprStr(),"(red)");

}


QTEST_MAIN(log_analysis_tool_test)
#include "log_analysis_tool_test.moc"
