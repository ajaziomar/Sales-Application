
// compilation safegaurds

#ifndef Error_h
#define Error_h

#include <iostream>

 namespace ict {
    class Error {
        char* m_message;
    public:
        // constructors
        Error();
        Error(const char* errorMessage);
        Error(const Error& em) = delete;
        
        // destructor
       virtual ~Error();
        // deleted constructor and operator=
        Error& operator=(const Error& em) = delete;

        
        // operator= for c-style strings
        void operator=(const char* errorMessage);

        // methods
        void clear();
        bool isClear()const;
        void message(const char* value);


         // cast overloads
        operator const char*() const;
        operator bool()const;

        
        std::ostream& write(std::ostream& ostr = std::cout)const{
            
            if(isClear()==true){
                
                
            }else{
                ostr << m_message;
            }
            return ostr;
        }
      
    };
    // operator << overload prototype for cout

         
std::ostream& operator<<(std::ostream& cout, const Error& m);
 
    }



#endif /* Error_h */
