
#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include <iostream>
#include "NonPerishable.h"
#include "Perishable.h"

using namespace std;
namespace ict {
    
    Perishable::Perishable(){
        m_expiry.dateOnly(true);
    }
    
    fstream& Perishable::save(fstream& file)const{
      
        NonPerishable::save(file)<<","<<m_expiry<<endl;
        return file;
    }
    
    fstream& Perishable::load(fstream &file){
 
        NonPerishable::load(file);
        file>>m_expiry;
         file.ignore();
       
          return file;
        
    
    }
    
    ostream& Perishable::write(ostream &os, bool linear)const{
        
        NonPerishable::write(os, linear);
        
        if(ok() && linear==false){
            os << "Expiry date: " << m_expiry<<endl;
            
        }
        return os;
    }
    
    istream& Perishable::read(std::istream &is){
    
        
        
        //if(!is.fail()){
        
        m_err.clear();
        cout<<"Perishable ";
        NonPerishable::read(is);
        
            if(!is.fail()){
        cout<<"Expiry date (YYYY/MM/DD): ";
        is>>m_expiry;
            }
        
        if (m_expiry.errCode() == CIN_FAILED) {
            error("Invalid Date Entry");
        }
        is.clear();
        if (m_expiry.errCode() == YEAR_ERROR) {
            error("Invalid Year in Date Entry");
        }
        is.clear();
        if (m_expiry.errCode() == MON_ERROR) {
            error("Invalid Month in Date Entry");
        }
        is.clear();
        if (m_expiry.errCode() == DAY_ERROR) {
            error("Invalid Day in Date Entry");
        }
        is.clear();
    
        
        if (m_expiry.bad()) {
            is.setstate(ios::failbit);
        }
            //}
           // }
        return is;
    }
    

}