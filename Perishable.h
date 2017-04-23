#ifndef SICT_PERISHABLE_H__
#define SICT_PERISHABLE_H__

#include <iostream>

#include "NonPerishable.h"
#include "Date.h"
#include "PosIO.h"

namespace sict {
    class Perishable : public NonPerishable{
        Error m_err;
        Date m_expiry;
        
    protected:
        char signature() const{return 'P';}
        
    public:
        Perishable();

        std::fstream& save(std::fstream& file)const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& os, bool linear)const;
        std::istream& read(std::istream& is);

        
        
    };
}
#endif
