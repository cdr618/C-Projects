#include "../std_lib_facilities.h"

struct Name{
    string first, initial, last;
};


struct Date{
    int yy, mm, dd;

    Date() : dd(1){}; //default name
};


class CreditCard{

private:
    string credit_type;
    Name user_name;
    Date end_date = Date();
    string card_number;

public:
    class Invalid{};
    CreditCard(string ct, Name un, string cn) : credit_type(ct), user_name(un), card_number(cn){if(!valid_card(ct, cn)) throw Invalid();};
    
    //getters
    string get_credit_type(){return credit_type;}
    Name get_user_name(){return user_name;}
    Date get_end_date(){return end_date;}
    string get_card_number(){return card_number;}

    //other member functions
    bool valid_card(string ct, string cn);
    string blacknumb(string num);
};


string CreditCard :: blacknumb(string num){
    string black;
    vector<char> numbers;
    for(char& n : num){ //puts every digit of the umber in a vector
        numbers.push_back(n);
    }
    stringstream ss;
    ss << "************" << numbers[12] << numbers[13] << numbers[14] << numbers[15]; //prints the last 4 and converts the rest to *
    black = ss.str();
    return black;
}
    

bool CreditCard :: valid_card(string ct, string cn){
    if(cn.length() != 16){ //if the card number does not have 16 digits it is invalid
        return false;
    }
    for(char& c : cn){ //if any part of the number is not a digit it is invalid
        if(!isdigit(c)){
            return false;
        }
    }
    if(ct != "visa" && ct != "master" && ct != "ams"){  //if it does not have a recognized card type it is invalis
        return false;
    }
    return true;
}


class User{

    private:
    Name username;
    string userId, shipaddress, telenum, password;
    CreditCard cc;

    public:
    //constructor
    User(string ui, Name un, string sa, string tn, string pw, CreditCard card) : userId(ui), username(un), shipaddress(sa), telenum(tn), password(pw), cc(card) {};
    //getters
    string get_userId(){return userId;}
    Name get_username(){return username;}
    string get_shipaddress(){return shipaddress;}
    string get_telenum(){return telenum;}
    string get_password(){return password;}
    CreditCard get_cc(){return cc;}
};


struct Item{
    string prodnum, name;
    int quantity;
    double unitprice;

    Item(string p, string n, int q, double up) : prodnum(p), name(n), quantity(q), unitprice(up) {};

};


class Company{

    private:
    string cname, caddress, ctelenum;
    vector<Item> inventory;
    vector<User> users;
    static int idgen;
  
    public:
    //constructor
    Company(string n, string a, string t, vector<Item> i, vector<User> u) : cname(n), caddress(a), ctelenum(t), inventory(i), users(u) {};
    //getters
    string get_cname(){return cname;}
    string get_caddress(){return caddress;}
    string get_ctelenum(){return ctelenum;}
    vector<Item> get_inventory(){return inventory;}
    vector<User> get_users(){return users;}
    //other member functions
    string generateID(string cname);
    string generatePW();
};
    

string Company :: generateID(string cname){
    string firstname;
    string lastname;
    stringstream ss{cname};
    ss >> firstname;  //separate the first and last name
    ss >> lastname;
    char initial1 = firstname[0];  //take the first letters of each name
    char initial2 = lastname[0];
    stringstream gen;
    string numlength = to_string(idgen);
    gen << initial1 << initial2; //concatenate the initials
    int zeroes = 6 - numlength.length();  //calulate how many zeros are need before the static int
    for(int i = 0; i < zeroes; i++){
        gen << "0";
    }
    gen << idgen;   //concatenate the static int
    string id = gen.str();
    idgen++;
    return id;
};


string Company :: generatePW(){
    char s[6];
    for (int i=0; i<6; i++) s[i] = (char) randint(48, 122);
    return s;
};

int Company::idgen = 0;

int invoice(User cust, Company supp, vector<Item> custorder){
    double total = 0;
    double hst;
    double shipping;
    string confirmcharge;
    string confirmship;
    stringstream company;
    company << supp.get_cname() << "\n" << supp.get_caddress() << "\n" << supp.get_ctelenum();
    cout << company.str() << "\n\n";  //print company info
    cout << "Online Order Invoice/Receipt\n\nTransaction List:\n\n";
    cout << "Product Name\tQuantity\tPrice\n";
    for(Item i : custorder){  //list the products the customer is buying
        cout << i.name << "\t" << i.quantity << "\t\t" << i.unitprice << "\n";
        total += i.unitprice * i.quantity;  //calculate the subtotal
    }
    cout << "\t\tSUBTOTAL\t" << total << "\n";
    hst = total * 0.15; //calculate HST
    cout << "\t\tHST(15%)\t" << hst << "\n";
    cout << "Please confirm charge to your credit card (Y/N)\n";
    cin >> confirmcharge;
    if(confirmcharge != "Y"){
        return 0;
    }
    cout << "Please confirm to ship your goods (Y/N)\n";
    cin >> confirmship;
    if(confirmship != "Y"){
        return 0;
    }
    shipping = total * 0.05; //calculate the shipping costs
    cout << "\t\tSHIPPING (5%)\t" << shipping <<"\n";
    total = total + hst + shipping; //calculate the final total
    cout << "\t\tTOTAL\t\t" << total << "\n";
    cout << "has been charged to your credit card:\n";
    //print out the customer's credit card information with blacknumb
    CreditCard temp = cust.get_cc();
    string type = temp.get_credit_type();
    cout << type << "\t\t";
    string ccnumber = cust.get_cc().get_card_number();
    string blackedout = cust.get_cc().blacknumb(ccnumber);
    cout << blackedout << "\n\n";
    cout << "GOODS SHIP TO:\n\n";
    //print out the customer's information
    Name custname = cust.get_username();
    string custfirst = custname.first;
    string custlast = custname.last;
    cout << custfirst << " " << custlast << "\n";
    string custadd = cust.get_shipaddress();
    cout << custadd << "\n";
    string custtele = cust.get_telenum();
    cout << "Tel: " << custtele << "\n";
}
    
int main(){
    string b;
    Item lays{"1", "Lays chips", 5, 1.05};
    Item aero{"2", "Aero bar", 10, 1.5};
    Item smarties{"3", "Smarties", 10, 1.25};
    Name Peter{"Peter", "J", "Mansbridge"};
    Name Ian{"Ian", "J", "Hanomansing"};
    CreditCard card1("visa", Peter, "1234567890123456");
    CreditCard card2("visa", Ian, "6543210987654321");
    vector<Item> d_inven;
    vector<User> d_users;
    //fake company object used to generate ids and passwords
    Company dummy("dummy", "123 Rose Street", "1234567890", d_inven, d_users);
    string pw1 = dummy.generatePW();
    string pw2 = dummy.generatePW();
    string id1 = dummy.generateID("Peter Mansbridge");
    string id2 = dummy.generateID("Ian Hanomansing");
    cout << "ID for Peter Mansbridge: "<< id1 <<"\nID for Ian Hanomansing: " << id2 << "\n\n";
    User one{id1, Peter, "6 Clinton Pl, Mt. Pearl", "7093683882", pw1, card1};
    User two{id2, Ian, "21 Canada Drive, St. John's", "7097454540", pw2, card2};
    vector<Item> userorder = {lays, smarties};
    vector<Item> inventory = {lays, aero, smarties};
    vector<User> users{one, two};
    Company candy("Candy Supply", "37 Allandale Road", "7097471291", inventory, users);
    
    int close = invoice(one, candy, userorder);
    if(close == 0){return 0;}
}


    

