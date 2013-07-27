#ifndef LOG_ANALYSIS_TOOL_H
#define LOG_ANALYSIS_TOOL_H

#include <iostream>
#include <boost/regex.hpp>
#include <sstream>
#include <fstream>

#define FILE_BUFFER_LENGTH (1024*24)
#define LINE_BUFFER_LENGTH FILE_BUFFER_LENGTH

using namespace std;

/** @file log_analysis_tool.h
    @brief This is the file which contains log_analysis_tool class definition
*/

class log_analysis_tool
{
public:
    log_analysis_tool(int argc, const char *argv[]);
    void run_filter();
    const char* get_filename();
    const char* get_rgEprStr();
    void set_rgEprStr(const char*);
    void set_filename(const char*);

private:
    string create_formatter();
    unsigned int analyse_block_buffer(char file_block_buffer[]);
    void colored_print_matched_part(char buffer[]);


private:
    const char *filename;
    const char *filtered_log;
    string      formatter;
    unsigned short numOfKeyword;
    string      rgEprStr;
    char line_buffer[LINE_BUFFER_LENGTH+1];
    bool also_print_unmatched_line;
};

#endif // LOG_ANALYSIS_TOOL_H
