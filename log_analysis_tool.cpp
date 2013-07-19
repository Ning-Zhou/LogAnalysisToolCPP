
/** @file log_analysis_tool.cpp
    @brief This is the file which contains log_analysis_tool class implementation
*/

#include "log_analysis_tool.h"

/** @brief log_analysis_tool constructor
*/
log_analysis_tool::log_analysis_tool(int argc, const char *argv[])
{
    if (argc == 1 ) cout<<"argc(parameters number) is 1, invalid input"<<endl;
    else    set_rgEprStr(argv[1]);

    if (argc == 2 )  cout<<"argc(parameters number) is 2, invalid input"<<endl;
    else    filename = argv[2];

    if (argc > 3)
    {
        cout<<"argc(parameters number) more than 3, invalid input"<<endl;
    }
}



void log_analysis_tool::colored_print_matched_part(char buffer[])
{
  boost::regex expression(rgEprStr);
  std::string line(buffer);
  std::string output= boost::regex_replace(line, expression,
                                           formatter);
  std::cout<<output<<std::endl;
}

unsigned int log_analysis_tool::analyse_block_buffer(char *block_buffer)
{

    stringstream ss(block_buffer);
    char line_buffer[LINE_BUFFER_LENGTH+1];
    line_buffer[LINE_BUFFER_LENGTH]='\0';

    do
    {
      ss.getline(line_buffer, LINE_BUFFER_LENGTH);
      if(!ss.eof())colored_print_matched_part(line_buffer);
      else break;
    }while(true);

    return ss.gcount();

}

std::string log_analysis_tool::create_formatter()
{
  const char *colorCodes[]={"31", //red
                      "32", //green
                      "33", //yellow
                      "34", //blue
                      "35", //magenta
                      "36", //cyan
                      "4",  //underline
                      "4;31", //red with underline
                      "4;32",
                      "4;33",
                      "4;34",
                      "4;35",
                      "4;36",
                      };   
  std::string formatter;

  //create the formatter
  std::string prefix("\033[");
  std::string suffix("\033[0m");
  std::string colorCode;
  std::string brph;//backReferencePlaceHolder
  for (int i=0;i<numOfKeyword;i++){
    colorCode = "m";
    colorCode = colorCodes[i%sizeof(colorCodes)] + colorCode;
    brph = '1' + i;
    brph = "$" + brph;
    formatter = formatter + prefix + colorCode + brph  + suffix;
  }

  return formatter;
}


/** @brief filter the log with regular expression string
 *  [in] filename log file name
 *  [in] rgEprStr regular expression string
 *  [out] filtered_log filtered log string
*/
void log_analysis_tool::run_filter()
{
    formatter = create_formatter();//formatter used to color the keywords

    // open the file to be analysed
    fstream fs;
    fs.open(filename);
    if(!fs.is_open()) cout<<"can not find "<<filename<<endl;

    // processing the file with keyword
    char file_block_buffer[FILE_BUFFER_LENGTH+1];
    bool keep_reading_file = true;
    while(keep_reading_file)
    {
        fs.read(file_block_buffer, FILE_BUFFER_LENGTH);
        file_block_buffer[fs.gcount()] = '\0';

        if (fs.gcount() != FILE_BUFFER_LENGTH)// last block from the file
        {
            keep_reading_file = false;
            file_block_buffer[fs.gcount()] = '\n';
            file_block_buffer[fs.gcount()+1] = '\0';
        }

        int mbNum = - analyse_block_buffer(file_block_buffer);
        fs.seekg(mbNum, fs.cur);
    }

    fs.close();
}


const char* log_analysis_tool::get_filename()
{
    return filename;
}

const char* log_analysis_tool::get_rgEprStr()
{
  return rgEprStr.data();
}




void log_analysis_tool::set_rgEprStr(const char* update_rgEprStr)
{
    numOfKeyword = 1;
    for(int i=0; update_rgEprStr[i]!='\0'; i++){
      if(update_rgEprStr[i]=='|')numOfKeyword++;
    }

    string formatter_tmp("($1)");
    string partial_fmt;
    string backReference_tmp("(.+)");
    string another_backReference_tmp("\\|(.+)");
    string brph;
    for (int i = 1 ; i< numOfKeyword; i++)
    {
        backReference_tmp = backReference_tmp + another_backReference_tmp;
        partial_fmt = '1' + i;
        partial_fmt = "|($" + partial_fmt + ')';
        formatter_tmp     = formatter_tmp + partial_fmt;
    }

    // boost::regex expression_tmp("(green)|(yellow)|(blue)");
    boost::regex expression_tmp(backReference_tmp);
    string       line_tmp(update_rgEprStr);
    rgEprStr = boost::regex_replace(line_tmp, expression_tmp, formatter_tmp.data());

}



void log_analysis_tool::set_filename(const char* update_filename)
{
    filename = update_filename;
}
