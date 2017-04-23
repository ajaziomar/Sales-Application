
//
//  PosApp.h
//  M5
//
//  Created by User on 2017-04-07.
//  Copyright © 2017 User. All rights reserved.
//

#ifndef PosApp_h
#define PosApp_h

#include "NonPerishable.h"
#include "Perishable.h"
#include "POS.h"


namespace ict {
    class PosApp{
        
        //private member variables (attributes)
        char m_filename[128];
        char m_billfname[128];
        Item* m_items[MAX_NO_ITEMS];
        int m_noOfItems;
        Item* bill[MAX_NO_ITEMS];
        int count;
        //private member functions (methods)
        int menu();
        //Data management member functions (methods)
        void deallocateItems();
        void loadRecs();
        void saveRecs();
        int searchItems(const char* sku)const;
        void updateQty();
        void addItem(bool isPerishable);
        void listItems()const;
        void truncateBillFile();
        void showBill();
        void addToBill(Item& I);
        void POS();
        void sort();
    public:
       //cannot be coppied or assigned to another PosApp
        PosApp(const PosApp& P) = delete;
        PosApp& operator=(const PosApp& Po) = delete;

        PosApp(const char* filename,const char* billname);

        void run();
        
        
        
    };
}


#endif /* PosApp_h */
