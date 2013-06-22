#ifndef LOG_ANALYSIS_TOOL_H
#define LOG_ANALYSIS_TOOL_H

#include <iostream>
using namespace std;

/** @file log_analysis_tool.h
    @brief This is the file which contains log_analysis_tool class definition
*/

class log_analysis_tool
{
public:
    log_analysis_tool(int argc, char *argv[]);
    void run_filter();
    const char* get_filename();
    const char* get_rgEprStr();

private:
    const char *filename;
    const char *rgEprStr;
    const char *filtered_log;
};

#endif // LOG_ANALYSIS_TOOL_H
