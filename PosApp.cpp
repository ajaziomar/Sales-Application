#define _CRT_SECURE_NO_WARNINGS

#include <cstring>
#include <iomanip>
#include <fstream>
#include "PosApp.h"
using namespace std;
namespace sict{
    // constructor
    
    PosApp::PosApp(const char* filename, const char* billfname) {
        
        strncpy(m_filename, filename, 128);
        m_filename[127]='\0'; //added by me
 
        strncpy(m_billfname, billfname, 128);
        m_billfname[127]='\0'; //added by me
 
        //Following was added by me
        count=0;

        deallocateItems();
        loadRecs();
 
 
    }
 
    int PosApp::menu() {
        int select;
 
        cin.clear();
 
        cout
        << "The Store" << endl
        << "1- List items" << endl
        << "2- Add Perishable item" << endl
        << "3- Add Non-Perishable item" << endl
        << "4- Update item quantity" << endl
        << "5- Show Item" << endl
        << "6- POS" << endl
        << "7- Sort" << endl
        << "0- exit program" << endl
        << "> ";
        cin >> select;
        cin.ignore(1000, '\n');
 
        if (cin.fail() || select > 7 || select < 0) {
            select = -1;
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cout<<endl;
         return select;
    }
 
 void PosApp::deallocateItems(){
 
     for (int i=0; i<m_noOfItems;i++){
         m_items[i]=nullptr;
     }
 
 m_noOfItems = 0;
 
 
 }
 
    void PosApp::loadRecs() {
     //structure obtained from pseudo code
        deallocateItems();
        fstream file;
        char id;
 
        file.open(m_filename, ios::in);
 
        if (file.fail()) {
            file.clear();
            file.close();
            file.open(m_filename, ios::out);
            file.close();
        }
        else {
            while (!file.fail()) {
                
 
                file >> id;
 
                if (!file.fail()){
                    file.ignore();
 
                    if (id == 'P') {
                        m_items[m_noOfItems] = new Perishable();
                    }
                    if (id == 'N') {
                       m_items[m_noOfItems] = new NonPerishable();
                    }
 
                    if (id == 'P' || id == 'N') {
 
                        m_items[m_noOfItems]->load(file);
                        m_noOfItems++;
                    }
 
                }
            }
        }
 
         file.close();
    }
 
    void PosApp::saveRecs() {
        fstream file;
 
        file.open(m_filename, ios::out);
        cout<<endl;
        for (int i = 0; i < m_noOfItems; i++) {
            if (m_items[i]->quantity() > 0) {
                m_items[i]->save(file);
            }
        }
 
        file.close();
        loadRecs();
    }
 
    int PosApp::searchItems(const char* sku) const {
        int index = -1;
 
        for (int i = 0;i < m_noOfItems; i++) {
            if (strcmp(m_items[i]->sku(), sku) == 0) {
                index = i;
            }
        }
 
        return index;


    }
 
    void PosApp::updateQty() {
        char sku[MAX_SKU_LEN + 1];
        int searchIndex = 0;
        int noOfItems = 0;
 
        cout << "Please enter the SKU: ";
        cin >> sku;
        cin.ignore();
 
        searchIndex = searchItems(sku);
 
        if (searchIndex == -1) {
            cout << "Not found!" << endl;
        }
        else {
            m_items[searchIndex]->write(cout, false);
 
            cout << endl << "Please enter the number of purchased items: ";
            cin >> noOfItems;
            cin.ignore();
            cout << "Updated!" << endl;

            (*m_items[searchIndex]) += noOfItems;
            saveRecs();
        }
 
    }
 
    void PosApp::addItem(bool isPerishable) {
        if (isPerishable==true) {
            m_items[m_noOfItems] = new Perishable();
        }
        else {
            m_items[m_noOfItems] = new NonPerishable();
        }
        
        cin >> *m_items[m_noOfItems];
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << *m_items[m_noOfItems] << endl;
        }
        else {
            cout << "Item added." << endl;

            m_noOfItems++;
            saveRecs();
        }
        
    }
    
    void PosApp::listItems() const {
        double totalasset = 0.0;
        
        cout
        << " Row | SKU    | Item Name          | Price |TX |Qty |   Total |" << endl
        << "-----|--------|--------------------|-------|---|----|---------|" << endl;
        
        for (int i = 0; i <m_noOfItems; i++) {
            
            if(m_items[i]->taxed()){
            
            totalasset += m_items[i]->price()*(TAX+1) * m_items[i]->quantity();
            }else{
                totalasset += m_items[i]->price() * m_items[i]->quantity();
            }

            cout << setfill(' ') << right << setw(4) << (i + 1) << " | " << *m_items[i] << endl;

        }
          
        
        cout
        << "-----^--------^--------------------^-------^---^----^---------^" << endl
        << "                               Total Asset: $  | "
        << fixed << setprecision(2)
        <<right<<setw(13)<<totalasset<<"|"<< endl;
    cout<< "-----------------------------------------------^--------------^" << endl;
        cout<<endl;
    }
 
 void PosApp::truncateBillFile(){
 
 fstream file;
 file.open(m_billfname,ios::out | ios::trunc);
 file.close();
 
 }
 
    void PosApp::showBill() {
        
        fstream file;
        double total = 0.0;
        cout
        << "v--------------------------------------------------------v" << endl
        << "| " << Date()  << "                                      |" << endl
        << "| SKU    | Item Name          | Price |TX |Qty |   Total |" << endl
        << "|--------|--------------------|-------|---|----|---------|" << endl;
        
        
        file.open(m_billfname, ios::in);
        
        //following was added for enhancement:
        for(int i=0;i<count;i++){
            total += bill[i]->cost();

           cout<<"| ";
            bill[i]->quantity(1);

            cout <<*bill[i]<<endl;
            
            
        }



        
        
       cout 
        << "^--------^--------------------^-------^---^----^---------^" << endl
        << "|                               Total: $  | "
        << fixed << setprecision(2)
        <<right<<setw(13)<<total<<"|"<< endl;
    cout<< "^-----------------------------------------^--------------^" << endl;
        file.close();
        truncateBillFile();
        cout<<endl;
    }
    
    void PosApp::addToBill(Item& I) {
        
        fstream file;
        file.open(m_billfname, ios::out | ios::app);
         int quan = 0;
        
        quan = I.quantity();
        I.quantity(1);
          bill[count]=&I; //added by me
        count++;          //added by me
        I.save(file);
        
        if(quan!=0){
            quan-=1;
        }
        
        
     
        
        I.quantity(quan);
        saveRecs();
        
         
    }
    
    void PosApp::POS() {
        
        char sku[MAX_SKU_LEN + 1];
        int searchIndex = 0;
        
        do {
            cout << "Sku: ";
            cin.getline(sku, MAX_SKU_LEN + 1);
            
            searchIndex = searchItems(sku);
            
            if (searchIndex != -1) {
                cout
                << "v------------------->" << endl
                << "| " << m_items[searchIndex]->name() << endl
                << "^------------------->";
                 addToBill(*m_items[searchIndex]);
                
            } else if (sku[0] != 0) {
                cout << "Not found!" << endl;
            }
            
        } while (strcmp(sku, "") != 0);
        
        showBill();

    }
    
    void PosApp::sort(){
        int sel=0;
        char asc;
        
        cout<<"Sort on:"<<endl;
        cout
        <<"1- Sku"<<endl
        <<"2- Item Name"<<endl
        <<"3- Price"<<endl
        <<"4- Quantity"<<endl
        <<"0- exit Sort"<<endl
        <<"> ";
        cin>>sel;
        
        
        //Sku
        if(sel==1){
            
            //assisted from http://www.cplusplus.com/forum/beginner/16476/
             cout<<"Ascending? (y/n) ";
             cin>>asc;

             if(asc=='y' || asc=='Y'){
 
             int result;
             for ( int x = 0; x < m_noOfItems - 1 ; x++ )
            {
                 for ( int i = 0; i < m_noOfItems - 1 - x; i++ )
                {
                     result = strcmp(m_items[i]->sku(), m_items[i+1]->sku());
                    
                     if (result > 0)
                        swap (m_items[i] , m_items[i+1]);
                    
                }
                
            }
        }
            if(asc=='n' || asc=='N'){
                 int result;
                for ( int x = 0; x < m_noOfItems-1 ; x++)
                {
                    for ( int i = 0; i < m_noOfItems-1-x; i++)
                    {
                        result = strcmp(m_items[i]->sku(), m_items[i+1]->sku());
                        
                        
                        if (result < 0)
                            swap ( m_items[i] , m_items[i+1]);
                        
                    }
                

                }
            }
            
            
        
        }
        
        //Item Name
        if (sel==2) {
            
            cout<<"Ascending? (y/n) ";
            cin>>asc;
            
            if(asc=='y' || asc=='Y'){
                
                
                int result;
                for ( int x = 0; x < m_noOfItems - 1 ; x++ )
                {
                    for ( int i = 0; i < m_noOfItems - 1 - x; i++ )
                    {
                        result = strcmp(m_items[i]->name(), m_items[i+1]->name());
                        
                         if (result > 0)
                            swap ( m_items[i] , m_items[i+1]);
                        
                    }
                }
            }else
            if(asc=='n' || asc=='N'){
                
                int result;
                for ( int x = 0; x < m_noOfItems - 1 ; x++ )
                {
                    for ( int i = 0; i < m_noOfItems - 1 - x; i++)
                    {
                        result = strcmp(m_items[i]->name(), m_items[i+1]->name());
                        
                         if (result < 0)
                            swap ( m_items[i] , m_items[i+1]);
                        
                    }
                    
                    
                }
            }
            
 
            
            
        }
        
        
        
        
        
        //Price
        if (sel==3) {
            
            cout<<"Ascending? (y/n) ";
            cin>>asc;
            
            if(asc=='y' || asc=='Y'){
            
             for ( int x = 0; x < m_noOfItems - 1 ; x++ )
            {
                for ( int i = 0; i < m_noOfItems - 1 - x; i++ )
                {
                   if(m_items[i]->price() > m_items[i+1]->price())
                    
                         swap ( m_items[i] , m_items[i+1]);
                    
                }
            }
            
        }else
            
            if(asc=='n' || asc=='N'){
                
                for ( int x = 0; x < m_noOfItems - 1 ; x++ )
                {
                    for ( int i = 0; i < m_noOfItems - 1 - x; i++ )
                    {
                        if(m_items[i]->price() < m_items[i+1]->price())
                            
                            swap ( m_items[i] , m_items[i+1]);
                        
                    }
                }
                
            }



        
        }
        
        //Quantity
        if(sel==4){
            
            cout<<"Ascending? (y/n) ";
            cin>>asc;
            
            if(asc=='y' || asc=='Y'){
             for ( int x = 0; x < m_noOfItems - 1 ; x++ )
            {
                for ( int i = 0; i < m_noOfItems - 1 - x; i++ )
                {
                    if(m_items[i]->quantity() > m_items[i+1]->quantity())
                        
                        swap ( m_items[i] , m_items[i+1]);
                    
                }
            }
            
        }else
        
            if(asc=='n' || asc=='N'){
                 for ( int x = 0; x < m_noOfItems - 1 ; x++ )
                {
                    for ( int i = 0; i < m_noOfItems - 1 - x; i++ )
                    {
                        if(m_items[i]->quantity() < m_items[i+1]->quantity())
                            
                            swap ( m_items[i] , m_items[i+1]);
                        
                    }
                }
                
            }
            
            
            
        }
        
        if(sel!=0){
            listItems();
        }else
        
        //exit sort
        if(sel==0){
            
            cout<<"Aborted!"<<endl<<endl;
            
        }
     
    }
        
    
    
    void PosApp::run() {
        
        char sku[MAX_SKU_LEN + 1];
        int select = 0;
        int found = 0;
        
        while ((select=menu())) {
            switch (select) {
                
                case 1: //list items
                    listItems();
                    break;
                
                case 2: //add items perishable
                    addItem(true);
                    break;
                
                case 3: //add items non perishable
                    addItem(false);
                    break;
                
                case 4: //update quantity of item
                    updateQty();
                    break;
              
                case 5: //select item based on sku and display items name
                    cout << "Please enter the SKU: ";
                    cin >> sku;
                    cin.ignore();
                    
                    found = searchItems(sku);
                    
                    if (found != -1) {
                        cout << "v-----------------------------------v" << endl;
                        m_items[found]->write(cout, false);
                        cout << "^-----------------------------------^" << endl << endl;
                    }
                    else {
                        cout << "Not found!" << endl;
                    }
                    
                    break;
                    
                case 6: //adds item to bill
                    POS();
                    break;
                    
                case 7: //sorts item list
                    sort();
                    break;
                    
                default:
                    cout << "===Invalid Selection, try again===" << endl<<endl;
            }
        }
        
        cout<< "Goodbye!" << endl;
    }
    
}

/*
 ouputs:
 -------------------------------------
 update:
 Please enter the SKU: 1313
 Name:
 Paper Tissue
 Sku: 1313
 Price: 1.22
 Price after tax: 1.38
 Quantity: 194
 Total Cost: 267.45
 Please enter the number of purchased items: 12
 Updated!
 ------------------------------
 Please enter the SKU: 3434
 Not found!
 -------------------------------------
 add item:
 Perishable Item Entry:
 Sku: 5656
 Name:
 Honey
 Price: 12.99
 Taxed: y
 Quantity: 12
 Expiry date (YYYY/MM/DD): 1200/10/12
 Invalid Year in Date Entry
 Perishable Item Entry:
 Sku: 5656
 Name:
 Honey
 Price: 12.99
 Taxed: y
 Quantity: 12
 Expiry date (YYYY/MM/DD): 2017/5/15
 Item added.
 --------------------------------------------
 list item:
 Row | SKU    | Item Name          | Price |TX |Qty |   Total |
 -----|--------|--------------------|-------|---|----|---------|
 1 | 1234   |Milk                |   3.99|  P|   2|     7.98|
 2 | 3456   |Paper Cups          |   5.99| TN|  38|   257.21|
 3 | 4567   |Butter              |   4.56| TP|   9|    46.38|
 4 | 1212   |Salted Butter       |   5.99|  P| 111|   664.89|
 5 | 1313   |Paper Tissue        |   1.22| TN| 206|   283.99|
 6 | 5656   |Honey               |  12.99| TP|  12|   176.14|
 -----^--------^--------------------^-------^---^----^---------^
 Total Asset: $  |       1436.59|
 -----------------------------------------------^--------------^
 --------------------------------------
 printbill:
 v--------------------------------------------------------v
 | 2017/04/02, 12:42                                      |
 | SKU    | Item Name          | Price |TX |Qty |   Total |
 |--------|--------------------|-------|---|----|---------|
 | 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
 | 1313   |Paper Tissue        |   1.22| TN|   1|     1.38|
 | 5656   |Honey               |  12.99| TP|   1|    14.68|
 ^--------^--------------------^-------^---^----^---------^
 |                               Total: $  |         22.05|
 ^-----------------------------------------^--------------^
 -------------------------------------------------------
 POS:
 Sku: 1212
 v------------------->
 | Salted Butter
 ^------------------->
 Sku: 1212
 v------------------->
 | Salted Butter
 ^------------------->
 Sku: 1313
 v------------------->
 | Paper Tissue
 ^------------------->
 Sku: 1234
 v------------------->
 | Milk
 ^------------------->
 Sku: 7654
 Not found!
 Sku: 5656
 v------------------->
 | Honey
 ^------------------->
 Sku:
 v--------------------------------------------------------v
 | 2017/04/02, 12:58                                      |
 | SKU    | Item Name          | Price |TX |Qty |   Total |
 |--------|--------------------|-------|---|----|---------|
 | 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
 | 1212   |Salted Butter       |   5.99|  P|   1|     5.99|
 | 1313   |Paper Tissue        |   1.22| TN|   1|     1.38|
 | 1234   |Milk                |   3.99|  P|   1|     3.99|
 | 5656   |Honey               |  12.99| TP|   1|    14.68|
 ^--------^--------------------^-------^---^----^---------^
 |                               Total: $  |         32.03|
 ^-----------------------------------------^--------------^
 ------------------------------------------------------
 run:
 The Sene-Store
 1- List items
 2- Add Perishable item
 3- Add Non-Perishable item
 4- Update item quantity
 5- Show Item
 6- POS
 0- exit program
 > 5
 Please enter the SKU: 5656
 v-----------------------------------v
 Name:
 Honey
 Sku: 5656
 Price: 12.99
 Price after tax: 14.68
 Quantity: 10
 Total Cost: 146.79
 Expiry date: 2017/05/15
 ^-----------------------------------^
 The Sene-Store
 1- List items
 2- Add Perishable item
 3- Add Non-Perishable item
 4- Update item quantity
 5- Show Item
 6- POS
 0- exit program
 > 5
 Please enter the SKU: 12345
 Not found!
 The Sene-Store
 1- List items
 2- Add Perishable item
 3- Add Non-Perishable item
 4- Update item quantity
 5- Show Item
 6- POS
 0- exit program
 > five
 ===Invalid Selection, try again===
 The Sene-Store
 1- List items
 2- Add Perishable item
 3- Add Non-Perishable item
 4- Update item quantity
 5- Show Item
 6- POS
 0- exit program
 > 0
 Goodbye!
 */
