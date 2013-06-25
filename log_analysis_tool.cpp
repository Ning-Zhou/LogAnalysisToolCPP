
/** @file log_analysis_tool.cpp
    @brief This is the file which contains log_analysis_tool class implementation
*/

#include "log_analysis_tool.h"

/** @brief log_analysis_tool constructor
*/
log_analysis_tool::log_analysis_tool(int argc, const char *argv[])
{
    if (argc == 1 ) cout<<"argc(parameters number) is 1, invalid input"<<endl;
    else    rgEprStr = argv[1];

    if (argc == 2 )  cout<<"argc(parameters number) is 2, invalid input"<<endl;
    else    filename = argv[2];

    if (argc > 3)
    {
        cout<<"argc(parameters number) more than 3, invalid input"<<endl;
    }
}

/** @brief filter the log with regular expression string
 *  [in] filename log file name
 *  [in] rgEprStr regular expression string
 *  [out] filtered_log filtered log string
*/
void log_analysis_tool::run_filter()
{
    ;
}

const char* log_analysis_tool::get_filename()
{
    return filename;
}

const char* log_analysis_tool::get_rgEprStr()
{
    return rgEprStr;
}

void log_analysis_tool::set_rgEprStr(const char* update_rgEprStr)
{
    rgEprStr = update_rgEprStr;
}

void log_analysis_tool::set_filename(const char* update_filename)
{
    filename = update_filename;
}
