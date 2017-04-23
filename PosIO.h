
#ifndef SICT_POSIO_H__
#define SICT_POSIO_H__
// includes go here
#include <iostream>
#include <fstream>

namespace sict {
    


class PosIO{
public:
    // pure virutal methods go here
    virtual std::fstream& save(std::fstream& file)const = 0;
    virtual std::fstream& load(std::fstream& file) = 0;
    virtual std::ostream& write(std::ostream& os, bool linear)const = 0;
    virtual std::istream& read(std::istream& is) = 0;

};

}
#endif
