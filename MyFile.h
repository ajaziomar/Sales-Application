#ifndef SICT_MYFILE_H__
#define SICT_MYFILE_H__
#include "PosIO.h"
namespace sict{
    class MyFile : public PosIO {
        char _fname[256];
        char _text[10000];
    public:
        MyFile(const char* fname);
        std::fstream& save(std::fstream& file)const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& os, bool linear)const;
        std::istream& read(std::istream& is);
        void print();
    };
    std::ostream& operator<<(std::ostream& ostr, const MyFile& mf);
    std::istream& operator>>(std::istream& istr, MyFile& mf);
}
#endif
