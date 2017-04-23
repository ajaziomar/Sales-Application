
#ifndef ICT_NONPERISHABLE_H__
#define ICT_NONPERISHABLE_H__

#include <iomanip>
#include <cstring>

#include "Item.h"
#include "Error.h"
#include "PosIO.h"



namespace sict {
    
    class NonPerishable : public Item{
        
        Error m_err;
        
   
    protected:
        
        bool ok() const;
        
        void error(const char* message);
        
        virtual char signature() const;
        
   
    public:
        
        
        
          std::fstream& save(std::fstream& file)const;
          std::fstream& load(std::fstream& file);
          std::ostream& write(std::ostream& os, bool linear)const;
          std::istream& read(std::istream& is);
    };
}

#endif


