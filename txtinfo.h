#ifndef TXTINFO_H
#define TXTINFO_H
#include <list>
#include <array>
#include <vector>


class txtinfo
{
private:
    std::string txt;

public:
    txtinfo();
    txtinfo(std::string donde);
    std:: array < int,3 >  info;
    void saveinfo();
    void addnew(int x);

};

#endif // TXTINFO_H
