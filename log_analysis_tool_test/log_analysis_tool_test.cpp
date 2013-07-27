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
    void run_filter_test();


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
    void create_test_input_file(const char *filename);

    stringstream ss4ut;
    streambuf *p_cout_streambuf;
};

void log_analysis_tool_test::create_test_input_file(const char *filename)
{
    
    char buffer[FILE_BUFFER_LENGTH+1];

    buffer[FILE_BUFFER_LENGTH]='\0';
  
    std::fstream fs;
    std::string matching_string("redyellowgreen-12345-redyellowgreen-45678-redyellowgreen");
    int matching_string_size = matching_string.size();
    int end_line_pos = 0;
    int expected_mbNum = 0;

    fs.open(filename, std::ios::out);
    if (fs.fail()) std::cout<<"file open failed\n";

    fs<<matching_string;
    expected_mbNum=0;//for check point 2 in run_filter description	 
    end_line_pos = FILE_BUFFER_LENGTH-1-matching_string_size-expected_mbNum;
    fill(&buffer[0], &buffer[end_line_pos],'0');
    buffer[end_line_pos] = '\n';
    buffer[end_line_pos+1] = '\0';
    fs<<buffer;

    fs<<matching_string;
    expected_mbNum=1; 	 //for check point 2 in run_filter description	 
    end_line_pos = FILE_BUFFER_LENGTH-1-matching_string_size-expected_mbNum;
    fill(&buffer[0], &buffer[end_line_pos],'0');
    buffer[end_line_pos] = '\n';
    buffer[end_line_pos+1] = '\0';
    fs<<buffer;

    fs<<matching_string;
    expected_mbNum=2;	 //for check point 2 in run_filter description
    end_line_pos = FILE_BUFFER_LENGTH-1-matching_string_size-expected_mbNum;
    fill(&buffer[0], &buffer[end_line_pos],'0');
    buffer[end_line_pos] = '\n';
    buffer[end_line_pos+1] = '\0';
    fs<<buffer;

    fs<<matching_string;
    expected_mbNum=10;	  //for check point 2 in run_filter description
    end_line_pos = FILE_BUFFER_LENGTH-1-matching_string_size-expected_mbNum;
    fill(&buffer[0], &buffer[end_line_pos],'0');
    buffer[end_line_pos] = '\n';
    buffer[end_line_pos+1] = '\0';
    fs<<buffer;

    fs<<matching_string;
    expected_mbNum=0;	 
    end_line_pos = FILE_BUFFER_LENGTH-1-matching_string_size-expected_mbNum;
    fill(&buffer[0], &buffer[end_line_pos],'0');
    buffer[end_line_pos] = '\0'; //for check point 3 in run_filter description
    buffer[end_line_pos+1] = '\0';
    fs<<buffer;

    fs.close();

}
/** Test run_filter in log_analysis_tool
 *  Check points:
 *  1. number of keywords is 1, 2, and 3
 *  2. mbnum is 0, 1, 2, 10
 *  3. file without a '\n' ending in last line
 */
void log_analysis_tool_test::run_filter_test()
{

    const char* filename = "run_filter_test_input.txt";//file to test run_filter 
    create_test_input_file(filename);

    fstream fs;
    fs.open(filename);
    
    char buffer[FILE_BUFFER_LENGTH*10];
    fs.read(buffer, FILE_BUFFER_LENGTH*10);
    
    int argc = 3;
    const char *argv[] = {"lat","red|yellow|green", filename};

    log_analysis_tool *lat_p= new log_analysis_tool(argc, argv);
    lat_p->run_filter();
    
    string formatter("\033[31m$1\033[0m\033[32m$2\033[0m\033[33m$3\033[0m");
    boost::regex expression("(red)|(yellow)|(green)");
    std::string line(buffer);
    std::string output = boost::regex_replace(line, expression, formatter)+'\n';
    std::string console_output = ss4ut.str();
    QCOMPARE(console_output, output);
 
    delete lat_p;
}

void log_analysis_tool_test::constructor_test()
{
    int argc = 3;
    const char *argv[4] = {"lat","green|yellow|blue","log.txt"};

    // test correct input
    log_analysis_tool *lat_p= new log_analysis_tool(argc, argv);
    QCOMPARE(lat_p->get_filename(),"log.txt");
    QCOMPARE(lat_p->get_rgEprStr(),"(green)|(yellow)|(blue)");
    delete lat_p;

    // test incorrect input: only 1 parameter
    argc = 1;
    lat_p= new log_analysis_tool(argc, argv);

    QCOMPARE(ss4ut.str(),string("Parameters not enough, should not < 3\n"));
    delete lat_p;
    ss4ut.str("");//clear the string date in ss4ut

    // test incorrect input: only 2 parameters
    argc = 2;
    lat_p= new log_analysis_tool(argc, argv);
    QCOMPARE(ss4ut.str(),string("Parameters not enough, should not < 3\n"));
    delete lat_p;
    ss4ut.str("");//clear the string date in ss4ut
    
    //test --help and -h
    argc = 2;
    argv[1] = "--help";
    lat_p= new log_analysis_tool(argc, argv);
    QCOMPARE(ss4ut.str(),string("Help info not complete\n"));
    delete lat_p;
    ss4ut.str("");

    argv[1] = "-h";
    lat_p= new log_analysis_tool(argc, argv);
    QCOMPARE(ss4ut.str(),string("Help info not complete\n"));
    delete lat_p;
    ss4ut.str("");

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
