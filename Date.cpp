#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <ctime>
using namespace std;
#include "Date.h"
#include "POS.h"


namespace sict{
    
  void Date::set(){
    time_t t = time(NULL);
    tm lt = *localtime(&t);
    m_day = lt.tm_mday;
    m_mon = lt.tm_mon + 1;
    m_year = lt.tm_year + 1900;
    if (dateOnly()){
      m_hour = m_min = 0;
    }
    else{
      m_hour = lt.tm_hour;
      m_min = lt.tm_min;
    }
  }

  int Date::value()const{
    return m_year * 535680 + m_mon * 44640 + m_day * 1440 + m_hour * 60 + m_min;
  }

  int Date::mdays()const{
    int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
    int mon = m_mon >= 1 && m_mon <= 12 ? m_mon : 13;
    mon--;
    return days[mon] + int((mon == 1)*((m_year % 4 == 0) && (m_year % 100 != 0)) || (m_year % 400 == 0));
  }
 

    
void Date::errCode(int errorCode){

  if (errorCode==0){
      m_readErrorCode = NO_ERROR;
      
  }
    if (errorCode==1){
        m_readErrorCode = CIN_FAILED;
        
    }
    if (errorCode==2){
        m_readErrorCode = YEAR_ERROR;
        
    }
    if (errorCode==3){
        m_readErrorCode = MON_ERROR;
        
    }

    if (errorCode==4){
        m_readErrorCode = DAY_ERROR;
        
    }
    if (errorCode==5){
        m_readErrorCode = HOUR_ERROR;
        
    }
    if (errorCode==6){
        m_readErrorCode = MIN_ERROR;
        
    }

}
 
    void Date::set(int year, int mon, int day, int hour, int min){
        
        m_year = year;
        m_mon = mon;
        m_day = day;
        m_hour = hour;
        m_min = min;
        m_readErrorCode = NO_ERROR;
        
        
    }

    Date::Date(){
        
        m_dateOnly = false;
        
        set();
        
    }
    Date::Date(int year, int mon, int day){
        
        m_dateOnly = true;
        m_year = year;
        m_mon = mon;
        m_day = day;
        m_hour = 0;
        m_min = 0;
       
        m_readErrorCode = NO_ERROR;
        
    }
    
    Date::Date(int year, int mon, int day, int hour, int min){
        m_dateOnly = false;
        m_year = year;
        m_mon = mon;
        m_day = day;
        m_hour = hour;
        m_min = min;
        
        m_readErrorCode = NO_ERROR;

        
    }
    
    
    bool Date::operator==(const ict::Date &D)const{
        
        if(this->value() == D.value()){
            return true;
        }else
            return false;
        
    }
    
    bool Date::operator!=(const ict::Date &D)const{
        
        if(this->value() != D.value()){
            return true;
        }else
            return false;
        
    }
    
    bool Date::operator<(const ict::Date &D)const{
        
        if(this->value() < D.value()){
            return true;
        }else
            return false;
        
    }
   bool Date::operator>(const ict::Date &D)const{
        
        if(this->value() > D.value()){
            return true;
        }else
            return false;
        
    }
    bool Date::operator<=(const ict::Date &D)const{
        
        if(this->value() <= D.value()){
            return true;
        }else
            return false;
        
    }

   bool Date::operator>=(const ict::Date &D)const{
        
        if(this->value() >= D.value()){
            return true;
        }else
            return false;
        
    }

    int Date::errCode() const{
        
        return m_readErrorCode;
    }
    
    bool Date::bad() const{
        bool ret = false;
        if(m_readErrorCode!=0){
            ret = true;
        }else{
            ret = false;
        }
        return ret;
    }
    
    bool Date::dateOnly() const{
        
        
         return m_dateOnly;
    }
    
    void Date::dateOnly(bool value){
        
         m_dateOnly = value;
        
        if (value==true){
        
            m_hour = 0;
            m_min = 0;
            
         }
        
    }
    
    std::ostream& operator<<(std::ostream& ostr, const Date& d){
        
        d.write(ostr);
        
        return ostr;
        
    }

    std::istream& operator>>(std::istream& istr,  Date& d){
        
        d.read(istr);
        return istr;
                
        
    }
    
    std::istream& Date::read(std::istream& is){
        
        is >> m_year;
        is.ignore();
        is >> m_mon;
        is.ignore();
        is >> m_day;
        
        if (dateOnly()==true) {
            m_hour = m_min = 0;
        }
        else {
            is.ignore();
            is >> m_hour;
            is.ignore();
            is >> m_min;
        }
        
        if (is.fail()) {
            is.clear();
            errCode(CIN_FAILED);
        }
        else {
            if (m_year < MIN_YEAR || m_year > MAX_YEAR) {
                errCode(YEAR_ERROR);
            }
            else if (m_mon < 1 || m_mon > 12) {
                errCode(MON_ERROR);
            }
            else if (m_day < 1 || m_day > mdays()) {
                errCode(DAY_ERROR);
            }
            else if (m_hour < 0 || m_hour > 23) {
                errCode(HOUR_ERROR);
            }
            else if (m_min < 0 || m_min > 59) {
                errCode(MIN_ERROR);
            }
            else {
                errCode(NO_ERROR);
            }
         }
        
        return is;
        
    }
    
    std::ostream& Date::write(std::ostream& ostr)const{
        
        if(m_dateOnly==true){
            ostr << m_year << "/" << std::setw(2)<<std::setfill('0')<< m_mon << "/" << std::setw(2)<<std::setfill('0')<< m_day;
            
        }   if (m_dateOnly==false){
            ostr << m_year << "/" << std::setw(2)<<std::setfill('0')<< m_mon << "/" << std::setw(2)<<std::setfill('0')<< m_day<<", "<<m_hour <<":"<<m_min;
        }
        
        return ostr;
        
        
    }
    

}
