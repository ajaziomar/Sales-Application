// compilation safegaurds
#ifndef sict_course_h
#define sict_course_h

#include <iostream>
#include <cstring>
#include "POS.h"

  // ict namespace
namespace sict {
   // Date defined Error values
   #define NO_ERROR 0 // no errors
   #define CIN_FAILED 1 //istream failed
   #define YEAR_ERROR 2
   #define MON_ERROR 3
   #define DAY_ERROR 4
   #define HOUR_ERROR 5
   #define MIN_ERROR 6




   class Date {
   private:
      // member variables
      int m_year;
      int m_mon;
      int m_day;
      int m_hour;
      int m_min;
      int m_readErrorCode;
      bool m_dateOnly;




     // private methods
      int value()const;
      void errCode(int errorCode);
      void set(int year, int mon, int day, int hour, int min);





   public:
      // constructors
      Date();
      Date(int year, int month, int day);
      Date(int year, int month, int day, int hour, int min=0);
       


      void set();
      // operator ovrloads
      bool operator==(const Date& D)const;
      bool operator!=(const Date& D)const;
      bool operator<(const Date& D)const;
      bool operator>(const Date& D)const;
      bool operator<=(const Date& D)const;
      bool operator>=(const Date& D)const;


      // methods
    int errCode()const;  
    bool bad()const;     
    bool dateOnly()const; 
    void dateOnly(bool value); 
 

      int mdays()const;

      // istream  and ostream read and write methods
       std::istream& read(std::istream& is = std::cin);
       std::ostream& write(std::ostream& ostr = std::cout)const;




   };
   // operator<< and >> overload prototypes for cout and cin
    std::ostream& operator<<(std::ostream&, const Date&);
    std::istream& operator>>(std::istream&,  Date&);

    


}

#endif
