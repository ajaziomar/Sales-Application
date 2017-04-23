#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include "Error.h"

 
namespace ict{
    
    Error::Error(){
        
        
        m_message = nullptr;
    }
    
    
    Error::Error(const char* errMessage){
        
        strcpy(m_message, errMessage);
        
        
    }
    
    void Error::operator=(const char *errorMessage){
        
        delete [] m_message;

       
        m_message = new char [strlen(errorMessage+1)];
    
        
        clear();
        
        message(errorMessage);
 
        

    }
    
      Error::~Error(){
        
         delete [] m_message;
        
    }
    
    void Error::clear(){
        
        delete [] m_message;
        m_message = nullptr;
        
    }
    
    bool Error::isClear()const{
        
        bool retVal = false;
        
        if(m_message == nullptr){
            
            retVal = true;
        }else{
            
            retVal = false;
        }
        return retVal;
    }
    
    void Error::message(const char *value){
        
        delete [] m_message;
        
       m_message = new char [strlen(value+1)];
        

        
        if (value!=nullptr){
            
            strcpy(m_message, value);
        }
     }
    
    Error::operator const char *() const{
       
        return this->m_message;
        
        
        
    }
    
    Error::operator bool()const{
        
        bool retVal = false;
        
        if(m_message == nullptr){
            
            retVal = true;
        }else{
            
            retVal = false;
        }
        return retVal;
   
    }
    
    std::ostream& operator<<(std::ostream& cout, const Error& m)
    {
        
        m.write(cout);
        
        return cout; 
    
}
}
