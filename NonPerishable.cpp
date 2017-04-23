#define _CRT_SECURE_NO_WARNINGS
// lib includes
#include <iostream>
#include <fstream>
#include <iomanip>
#include "NonPerishable.h"



using namespace std;
namespace ict {
    
    
    bool NonPerishable:: ok() const{
        bool val;
        
        if(m_err==nullptr){
            
            val = true;
        }else{
            val = false;
        }
        return val;
    }

    
    void NonPerishable::error(const char* message){
        
        m_err = message;
        
    }
    
    
      char NonPerishable::signature() const{
        return 'N';
        
    }
    
    fstream& NonPerishable::save(std::fstream& file)const{
    
        file << signature() << "," << sku() << "," << name() << ","
        << price() << "," << taxed() << ","<<quantity();
       
        if(signature()=='N'){
            file<<endl;
    
        }
        
        
        return file;
    }

    
    fstream& NonPerishable::load(std::fstream& file){
        
        char msku[MAX_SKU_LEN+1];
        char mname[81];
        double mprice;
        bool mtaxed;
        int mquan;
        
        
        file.get(msku, sizeof(msku), ',');
        file.ignore(); //ignore the comma
        file.get(mname, sizeof(mname), ',');
        file.ignore(); //ignore the comma
        file >> mprice;
        file.ignore(); //Ignore the comma
        file >> mtaxed;
        file.ignore(); //Ignore the comma
        file>>mquan;
        file.ignore(); //Ignore the newline
        
        sku(msku);
        name(mname);
        price(mprice);
        taxed(mtaxed);
        quantity(mquan);
        
        return file;
        
        
    }
    
    ostream& NonPerishable::write(std::ostream& os, bool linear) const{
        
        if(!ok()){
            os << m_err;
        }else
            if(linear==true){
         
            os<< setfill(' ') << left << setw(MAX_SKU_LEN) << sku() << "|" << left << setw(20)
            << name() << "|" << right << setw(7) << fixed << setprecision(2) << price() << "|";
            
            if (taxed()) {
                os<< " T" << signature() << "|"<< right << setw(4) << quantity() << "|" << right << setw(9)<< setprecision(2) << fixed << setprecision(2) << price() * (TAX + 1) * quantity();
            }
            else {
                os<< "  " << signature() <<"|"<< right << setw(4) << quantity() << "|" << right << setw(9)<< setprecision(2) << fixed << setprecision(2) << price() * quantity();
            }
            os << "|";
                
                
        }else {
            os<< "Name:\n" << name()  << endl<< "Sku: "<< sku()<< endl<< "Price: " << price() << endl;
            
            if (taxed()) {
                os<< "Price after tax: " << fixed << setprecision(2) << price() * (TAX + 1) << endl
                << "Quantity: " << quantity() << endl
                << "Total Cost: " << fixed << setprecision(2) << price() * (TAX + 1) * quantity() << endl;
            }
            else {
                os<< "Price after tax: N/A" << endl<< "Quantity: " << quantity() << endl
                << "Total Cost: " << fixed << setprecision(2) << price() * quantity() << endl;
            }
        }
        return os;
    }
    
    istream& NonPerishable::read(std::istream &is){
        
        
        char msku[MAX_SKU_LEN+1];
        char mname[81];
        double mprice;
        char mtaxed;
        int mquan;
        
        if(!is.fail()){
            m_err.clear();
            cout << "Item Entry:"<<endl;
            cout << "Sku: ";
            is >> msku;
            sku(msku);
            
            cout << "Name:\n";
            is >> mname;
            name(mname);
            
            cout << "Price: ";
            is >> mprice;
            
            if (!is.fail()) {
                price(mprice);
            }
            else {
                error("Invalid Price Entry");
            }
            
            if (m_err.isClear()) {
                cout << "Taxed: ";
                is >> mtaxed;
                
                if (mtaxed == 'Y' || mtaxed == 'y') {
                    taxed(true);
                }
                else if (mtaxed == 'N' || mtaxed == 'n') {
                    taxed(false);
                }
                else {
                    m_err="Invalid Taxed Entry, (y)es or (n)o";
                    is.setstate(ios::failbit);
                }
            }
            
            if (m_err.isClear()) {
                cout << "Quantity: ";
                is >> mquan;
                
                if (is.fail()) {
                    m_err = "Invalid Quantity Entry";
                }
                else {
                    quantity(mquan);
                }
            }
            
        }
        
        return is;
    }
            
        }


