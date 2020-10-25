#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>       // std::string
#include <sstream>      // std::ostringstream
#include <math.h>
#include <sys/stat.h>

#define WEEK "WEEK" // — неделя, начинающаяся в понедельник и заканчивающаяся в воскресенье.
#define MONTH "MONTH" // — месяц.
#define QUARTER "QUARTER" // — интервалы длительностью три месяца: январь–март, апрель–июнь, июль–сентябрь, октябрь–декабрь.
#define YEAR "YEAR" // — год c 1-го января по 31-е декабря.
#define FEBRUARY_THE_29TH "FEBRUARY_THE_29TH" // — интервал, начинающийся 29 февраля, а заканчивающийся ближайшим 28 февраля високосного года.

struct date {
 unsigned int year;
 unsigned int month;
 unsigned int day;
};

int main() {
 std::string periodtype;
 std::getline(std::cin, periodtype);

 date datestart, dateend;

 scanf("%u-%u-%u", &datestart.year, &datestart.month, &datestart.day);
 scanf("%u-%u-%u", &dateend.year, &dateend.month, &dateend.day);
 
 std::cout << "period type: " << periodtype.c_str() << std::endl;
 std::cout << "from: " << datestart.year << '-' << datestart.month << '-' << datestart.day << std::endl;
 std::cout << "to: " << dateend.year << '-' << dateend.month << '-' << dateend.day << std::endl;

 unsigned int yearcurstart, monthcurstart, daycurstart;
 unsigned int yearcurend, monthcurend, daycurend;
 
 date datecurstart = datestart;
 date datecurend;

 while (0) {
  if (periodtype == WEEK) {
   
  } else if (periodtype == MONTH) {

  } else if (periodtype == QUARTER) {

  } else if (periodtype == YEAR) {

  } else if (periodtype == FEBRUARY_THE_29TH) {

  }
 }
 return 0;
}