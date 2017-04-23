#ifndef ICT_ITEM_H__
#define ICT_ITEM_H__

#include <iostream>
// inlcude PosIO and POS header files
#include "PosIO.h"
#include "POS.h"


namespace ict{
    // class Item
    class Item : public PosIO
    {
        char m_sku[MAX_SKU_LEN+1];
        char* m_name;
        double m_price;
        bool m_taxed;
        int m_quantity;
        
    public:
        Item();
        ~Item();
        Item(const char*, const char*, double, bool );
        Item(const Item&);
        
        //Setters
        void sku(const char* sku);
        void name(const char* name);
        void price(double price);
        void taxed(bool tax);
        void quantity(int quantity);
        
        //Getters
        const char* sku() const;
        const char* name() const;
        double price() const;
        int quantity() const;
        bool taxed() const;
        double cost() const;
        bool isEmpty() const;
        
        //Member Operators
        Item& operator=(const Item&);
        bool operator==(const char*);
        int operator+=(int);
        int operator-=(int);
        
    };
    
    // end class Item
    // operator +=
    double operator+=(double& d, const Item& I);
    // operator << and operator >>
    std::ostream& operator<<(std::ostream& cout, const Item& i);
    /*{
     return i.write(ostr, true);
     }*/
    
    std::istream& operator>>(std::istream& cin, Item& i);
    /*{
     return i.read(istr);
     }*/
    
}


#endif