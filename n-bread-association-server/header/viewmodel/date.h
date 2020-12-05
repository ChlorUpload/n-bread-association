#ifndef __H_DATE__
#define __H_DATE__

#include <string>
#include <iomanip>
#include <sstream>

class Date
{
  private:
    std::tm _tm;

  public:
    static std::tm str_to_time(std::string const& time)
    {
        std::tm            t;
        std::istringstream ss(time);
        ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");
        return t;
    }

    static std::string time_to_str(std::tm const& time)
    {
        std::string        str;
        std::ostringstream ss;
        ss << std::put_time(&time, "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

  public:
    std::string to_string() const
    {
        return time_to_str(_tm);
    }

    std::tm get_tm() const
    {
        return _tm;
    }

    Date& operator=(std::string const& str) {
        _tm = str_to_time(str);
        return *this;
    }
};

#endif