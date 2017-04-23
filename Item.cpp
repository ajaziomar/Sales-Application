#define _CRT_SECURE_NO_WARNINGS
// Lib includes
#include <iostream>
#include <cstring>

// inlcude Item and POS header files
#include "Item.h"
#include "PosIO.h"



using namespace std;
namespace sict{
    // class Item implementaion
    Item::Item(){
        
        m_sku[0] = '\0';
        m_name = nullptr;
        m_price = 0;
        m_taxed = false;
        m_quantity = 0;
        
        
    }
     Item::Item(const char* s, const char* n, double p, bool tax){
        
        sku(s);
        name(n);
        price(p);
        taxed(tax);
         
        //just in case
         quantity(0);
        
        
    }
    
    
    Item::Item(const Item& i){
        //same as operator=
        //call operator=
        operator=(i);
        
    }
  
    
    Item& Item::operator=(const Item& src){
        if (this != &src){
            sku(src.m_sku); //reuse logic to set the new value into the current object
            name(src.m_name); //resuing logic
            price(src.m_price); //resuing logic
            quantity(src.m_quantity); //resuing logic
            taxed(src.m_taxed);
            
        }
        
        return *this;
    }
    
    Item::~Item(){
        delete [] m_name;
        
    }
    
    //Setters
    void Item::sku(const char *sku){
        if(sku != nullptr && sku[0] != '0'){
            strncpy(m_sku, sku, MAX_SKU_LEN + 1); //set current value to retrieved value
        }
    }
    void Item::name(const char* name){
        if(name != nullptr && name[0] != '0'){
            delete[] m_name; //De-allocate to prepare for new allocation
            m_name = new char[strlen(name) + 1]; //Allocate the memory
            strcpy(m_name, name); //copy value
        }
    }
    void Item::price(double price){
        m_price = price; //set current value to retrieved value
    }
    void Item::quantity(int quantity){
        m_quantity = quantity; //set current value to retrieved value
    }
    
    void Item::taxed(bool tax){
        
        m_taxed = tax;
    }
    //Getters
    const char* Item::sku() const{
        return m_sku;
    }
    const char* Item::name() const{
        return m_name;
    }
    double Item::price() const{
        return m_price;
    }
    int Item::quantity() const{
        return m_quantity;
    }
    
    bool Item::taxed() const{
        return m_taxed;
    }
    double Item::cost() const{
        
        if(m_taxed==true){
            
            
            double taxed = m_price * TAX;
            return  m_price + taxed;
            
            
        }else{
            return m_price;
        }
        
    }
    
    bool Item::isEmpty() const{
        return m_price == 0 && m_quantity == 0 && m_name == nullptr && m_sku[0] == '\0';
    }
    
    
    
    
    bool Item::operator==(const char* sku){
        int val = strcmp(m_sku, sku);
        bool outcome = false;
        if (val == 0){
            outcome = true;
        }
        return outcome;
    }
    
    
    int Item::operator+=(int quantity){
        int val = quantity + m_quantity; //Add both values together to get sum
        m_quantity += quantity; //Assign the quantity to the received integer value
        return val; //return the sum
    }
    
    int Item::operator-=(int quantity){
        int val = quantity - m_quantity; //Add both values together to get sum
        m_quantity -= quantity; //Assign the quantity to the received integer value
        return val; //return the sum
    }
    
    ostream& operator<<(std::ostream& cout, const Item& i){
        
        i.write(cout,true);
        return cout;
    }
    
    istream& operator>>(std::istream& cin, Item& i){
        
        i.read(cin);
        return cin;
    }
    double operator+=(double& d, const Item& i){
        double value = i.price() * i.quantity();
        
        d = d+value;
        
        return d;
    }
    
    
}
