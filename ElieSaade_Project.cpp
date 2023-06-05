#include "C:\Users\Admin\Desktop\sha256.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <ctime>

using namespace std;
char v;
SHA256 sha;
fstream rooms, reservations, clients;
string admin_userName="ADMIN", admin_pass="ADMIN";
string feat;
int id;
typedef istringstream iss;
int j;

const double wTAX = 1.11;

struct date
{
    int day;
    int month;
    int year;
};

struct room
{
    int num;
    string address;
    string type;
    double price;
    string* options;
    date start_date;
    date end_date;
};

struct client
{
    int ID;
    string firstName;
    string lastName;
    string password;
    string address;
    string tel;
    room* r;
};

void sortPrice(room *i, int size)
{
    room temp;
    for (int j = 0; j < size; j++)
    {
        for (int k = j; k < size; k++)
        {
            if (i[j].price > i[k].price)
            {
                temp = i[j];
                i[j] = i[k];
                i[k] = temp;
            }
        }
    }
}

int daycount(date t)
{
    int days = 0;
    int monthDays[12] = { 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365 };
    if (t.year % 4 == 0)
    {
        for (int i = 1; i < 12; i++)
            monthDays[i]++;
    }
    days = (t.year) * monthDays[11] + monthDays[t.month - 1] + t.day;
    return days;
}

bool hasSpace(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == ' ')
            return true;
    }
    return false;
}

bool hasNum(string s)
{
    
    for (int i = 0; i < s.length(); i++)
    {
        if(isdigit(s.c_str()[i]))
            return true;
    }
    return false;
}

bool hasLetter(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (isalpha(s.c_str()[i]))
            return true;
    }
    return false;
}

bool gdLength(string s)
{
    if (s.length() >= 8)
        return true;
    else return false;
}

bool hasSpCh(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (!isalnum(s.c_str()[i]))
            return true;
    }
    return false;
}

bool gdFormatMail(string s)
{
    if (s.find('@') != string::npos && s.find(".com") != string::npos)
    {
        if (s.find(".com") - s.find('@') > 1)
            return true;
    }
    return false;
}

bool gdFormatTel(string s)
{
    if (s.length() == 8 && hasSpCh(s) == false && hasLetter(s) == false)
        return true;
    else return false;
}

void input(client &c)
{
    cout << "Please fill in the required information to continue ," << endl
        << "\nYour FIRST NAME : " << endl;

    do 
        getline(cin, c.firstName);
    while (hasNum(c.firstName) == true || hasSpCh(c.firstName) == true || hasSpace(c.firstName) == true);

    cout << "\nYour LAST NAME : " << endl;

    do
        getline(cin, c.lastName);
    while (hasNum(c.lastName) == true || hasSpCh(c.lastName) == true || hasSpace(c.lastName) == true);
   
    cout << "\nA PASSWORD that countains AT LEAST :" << endl
        << "\n8 characters including :" << endl
        << "1 Number " << endl
        << "1 Letter " << endl
        << "1 Special Character ( !,@,#,$,%,^,&,...)" << endl;

    do
        getline(cin, c.password);
    while (gdLength(c.password) == false || hasNum(c.password) == false || hasLetter(c.password) == false || hasSpCh(c.password) == false || hasSpace(c.password) == true);

    cout << "\nYour e-mail address ( user-name@example.com ) : " << endl;

    do
        getline(cin, c.address);
    while (gdFormatMail(c.address) == false || hasSpace(c.address) == true);

    cout << "\nYour phone number : (12345678) : " << endl;

    do
        getline(cin, c.tel);
    while (gdFormatTel(c.tel) == false || hasLetter(c.tel) == true || hasSpCh(c.tel) == true || hasSpace(c.tel) == true);

    c.tel.insert(2, 1, '-');
    
    c.ID = id;
    cout << "\nThank you !";

    clients.open("clients.txt", ios::app);
    if (clients.is_open())
    {
        clients << c.ID << "\t\t"
            << c.firstName << "\t\t"
            << c.lastName << "\t\t"
            << sha(c.password) << "\t\t"
            << c.address << "\t\t"
            << c.tel << endl;
    }
} 

void getID(int &x)
{
    ifstream ID;
    string str;
    ID.open("clients.txt");
    if (ID.is_open())
    {
        while (getline(ID, str))
            ID >> x;
        ++x;
    }
    ID.close();
}

void getRnum(int& x,int y)
{
    ifstream room;
    string str;
    //int x;
    room.open("rooms.txt");
    if (room.is_open())
    {
        while (getline(room, str))
        {
            room >> x;
            if (x == y)
                break;
        }
        //id = ++x;
        //++x;
    }

    //return id;
}

void fileCreation()
{
    fstream file;
    string s;
    int a = 0;
    file.open("clients.txt", ios::out);
    s = "\t\tFName\t\tLName\t\tPassword\t\tE-mail_Address\t\tNumber";
    file << a << s << endl;
    file.close();
    file.open("rooms.txt", ios::out);
    file.close();
    file.open("reservations.txt", ios::out);
    file.close();
    //file.open("AdminCred.txt", ios::out);
    //file<<"ADMIN"<<endl<<"ADMIN";
    //file.close();
}

void AUTH(string mail, string pass, string &str)
{
    //str = "fail";
    fstream clients;
   // bool a = false;
    istringstream y;

    clients.open("clients.txt", ios::in);
    if (mail == "ADMIN" && pass == sha("ADMIN"))
    {
        str = "ADMIN";
    }
    else if (clients.is_open())
    {
        //bool a = false;
        string s, passNmail, e, p;
        //iss y(email), z(password);
       // str = "fail";
        while (getline(clients, s))
        {
            if (s.find(mail) != string::npos && s.find(pass) != string::npos)
            {
               // email = s.substr(s.find(mail), s.length() - s.find(mail));
               // iss y(email);
               // y >> e;
                passNmail = s.substr(s.find(pass), s.length() - s.find(pass));
                iss z(passNmail);
                z >> p >> e;

                if (e == mail && p == pass)
                {
                    // a = true;
                    //cout << "A SHOULD BE TRUE NOW, IF CONDITIONS FULFILLED " << endl;
                    str = "success";
                    break;
                }
                else str = "fail";
            }
            str = "fail";
        }
        // return a;
    }
    clients.close();
   
}

void linedel(const char* file_name, int n)
{
    ifstream i;
    i.open(file_name, ios::in);
    ofstream o;
    o.open("temp.txt", ios::out);

    
    char c;
    int line = 1;
    while (i.get(c))
    {

        if (c == '\n')
            line++;

        if (line != n)
            o << c;
    }
    
    o.close();
    i.close();

    remove(file_name);

    rename("temp.txt", file_name);
}

void ResCancel(int n)
{
    fstream i, o, u;
    i.open("oneAccRes.txt", ios::in);
    
    //o.open("temp.txt", ios::out);

    string n1, sd, ed;
    string n2, SD, ED;
    string s, s1;
    int line = 1;
    while (getline(i,s))
    {
        if (line == n)
            break;
    }
    iss x(s);
    x >> n1 >> sd >> sd >> sd >> sd >> sd >> ed;
    //cout << n1 << sd << ed;


    //cout << s << endl;
    //o.close();
    i.close();

    //remove(file_name);
    //rename("temp.txt", file_name);
    
    u.open("TEMP.txt", ios::app);
    o.open("reservations.txt", ios::in);
    while (getline(o, s1))
    {
        iss y(s1);
        y >> n2 >> SD >> SD >> SD >> ED;
        //cout << s1 << endl;
        if (n1 == n2 && sd == SD && ed == ED)
            continue;

        u << s1 << endl;
    }o.close();
    u.close();

    remove("reservations.txt");
    rename("TEMP.txt", "reservations.txt");
}

void roomInput(room& ro) //with write
{
    int j, num1;
    rooms.open("rooms.txt", ios::app);
    if (rooms.is_open())
    {
        //ROOM NUMBER
        {
            cout << "\n\nEnter room number : ";
            cin >> ro.num;
            getRnum(num1, ro.num);
            while (num1 == ro.num)
            {
                cout << "Room number already exists\n"
                    << "Enter a valid one : ";
                cin >> ro.num;
                getRnum(num1, ro.num);

            }
            rooms << ro.num << "\t\t";
        }

        //ADDRESS
        {
            cout << "\nAddress : ";
            cin >> ro.address;
            rooms << ro.address << "\t\t";
        }

        //TYPE
        {
            cout << "\nType (1) for single , (2) for double , (3) for triple , \n     (4) for duplex , (5) for suite : ";
            do
            {
                cin >> j;
            } while (j != 1 && j != 2 && j != 3 && j != 4 && j != 5);

            if (j == 1)
                ro.type = "single";
            if (j == 2)
                ro.type = "double";
            if (j == 3)
                ro.type = "triple";
            if (j == 4)
                ro.type = "duplex";
            if (j == 5)
                ro.type = "suite";
            rooms << ro.type << "\t\t";
        }

        //PRICE
        {
            cout << "\nPrice : ";
            cin >> ro.price;
            rooms << ro.price << "\t\t";
        }

        //FEATURES
        {
            string feat;
            ro.options = &feat;

            cout << "\nAdditionnal features , if none hit enter key : ";

            cin.ignore(INT_MAX, '\n');

            getline(cin, *ro.options);
            rooms << *ro.options << "\n";
        }
    }rooms.close();
}

void roomInput1(room& ro) //without write
{
    int j, num1;
    rooms.open("rooms.txt", ios::app);
    if (rooms.is_open())
    {
        //ROOM NUMBER
        {
            cout << "\n\nEnter room number : ";
            cin >> ro.num;
            getRnum(num1, ro.num);
            
            while (num1 == ro.num)
            {
                cout << "Room number already exists\n"
                    << "Enter a valid one : ";
                cin >> ro.num;
                getRnum(num1, ro.num);

            }
            
            //else if(a=='y')
                
            //rooms << ro.num << "\t\t";
        }

        //ADDRESS
        {
            cout << "\nAddress : ";
            cin >> ro.address;
            //rooms << ro.address << "\t\t";
        }

        //TYPE
        {
            cout << "\nType (1) for single , (2) for double , (3) for triple , (4) for duplex , (5) for suite : ";
            do
            {
                cin >> j;
            } while (j != 1 && j != 2 && j != 3 && j != 4 && j != 5);

            if (j == 1)
                ro.type = "single";
            if (j == 2)
                ro.type = "double";
            if (j == 3)
                ro.type = "triple";
            if (j == 4)
                ro.type = "duplex";
            if (j == 5)
                ro.type = "suite";
            //rooms << ro.type << "\t\t";
        }

        //PRICE
        {
            cout << "\nPrice : ";
            cin >> ro.price;
            //rooms << ro.price << "\t\t";
        }

        //FEATURES
        {
            
            ro.options = &feat;

            cout << "\nAdditionnal features , if none hit enter key : ";

            cin.ignore(INT_MAX, '\n');

            getline(cin, feat);
            //rooms << *ro.options << "\n";
        }
    }rooms.close();
}

void lineMOD(const char* file_name, int n,room &a)
{
    //const char *file_name = "rooms.txt";
    ifstream i;
    i.open(file_name, ios::in);
    ofstream o;
    o.open("temp1.txt", ios::out);
    
    roomInput1(a);

    
   // string s = *a.options;
   // cout << s;
    char c;
    int line = 1;
    int counter = 0;
    while (i.get(c))
    {

        if (c == '\n')
            line++;

        if (line != n)
            o << c;

        if (line == n && counter == 0)
        //if (line == n)
        {
            if (n != 1)
                o << endl;
            o << a.num << "\t\t"
                << a.address << "\t\t"
                << a.type << "\t\t"
                << a.price << "\t\t"
                << *a.options;//<< endl;

            counter++;
            //line++;
        }
    }

    o.close();
    i.close();

    remove(file_name);

    rename("temp1.txt", file_name);
}

void showRooms()
{
    rooms.open("rooms.txt", ios::in);
    string s, s1;
    int rn = 1;
    if (rooms.is_open())
    {
        while (getline(rooms, s))
        {
            //getline(rooms, s);
            //s1 += s;
            //rooms >> rn;
            cout << rn << ") " << s << endl;
            rn++;
        }
    }rooms.close();
}

void admin_mode(room &ro)
{
    char a;
    int i;
    cout << "\n\n\n######################"
        << "    YOU ARE NOW USING ADMIN MODE    "
        << "######################\n";
    cout << "\nFirst time using our app ? (y/n) : ";
    cin >> a;
    if (a == 'y')
    {
        cout << "Alright then ! We'll get things up and running in no time !!\n"
            << "\nJust doing the 'usual' stuff you know ? :)\n.\n.\n.\n\n";
        fileCreation();
        cout << "Almost done , would you like to change your ADMIN MODE login info ? (y/n) : ";
        cin >> a;
        if (a == 'y')
        {
            cout << "New username : ";
            cin >> admin_userName;
            cout << "New password : ";
            cin >> admin_pass;
        }
        cout << "\nAll set ! Restart the app to apply the changes .\n";
    }
    else if (a == 'n')
    {
        cout << "\nChoose one of the options below : \n\n"
            << "1) Add a new room \n"
            << "2) Delete an existing room \n"
            << "3) Modify a room's data \n"
            << "4) Exit ADMIN mode \n\n"
            << "Your choice : ";
        cin >> i; cout << endl;

        if (i != 4)
        {
            showRooms();
            cout << endl;
        }

        if (i == 1)
        {
            int j,num1;
            rooms.open("rooms.txt", ios::app);
            if (rooms.is_open())
            {
                //ROOM NUMBER
                {
                    cout << "\n\nEnter room number : ";
                    cin >> ro.num;
                    getRnum(num1, ro.num);
                    while (num1 == ro.num)
                    {
                        cout << "Room number already exists\n"
                            << "Enter a valid one : ";
                        cin >> ro.num;
                        getRnum(num1, ro.num);

                    }
                    rooms << ro.num << "\t\t";
                }

                //ADDRESS
                {
                    cout << "\nAddress : ";
                    cin >> ro.address;
                    rooms << ro.address << "\t\t";
                }

                //TYPE
                {
                    cout << "\nType (1) for single , (2) for double , (3) for triple \n     (4) for duplex , (5) for suite : ";
                    do
                    {
                        cin >> j;
                    } while (j != 1 && j != 2 && j != 3 && j != 4 && j != 5);

                    if (j == 1)
                        ro.type = "single";
                    if (j == 2)
                        ro.type = "double";
                    if (j == 3)
                        ro.type = "triple";
                    if (j == 4)
                        ro.type = "duplex";
                    if (j == 5)
                        ro.type = "suite";
                    rooms << ro.type << "\t\t";
                }

                //PRICE
                {
                    cout << "\nPrice : ";
                    cin >> ro.price;
                    rooms << ro.price << "\t\t";
                }
                
                //FEATURES
                {
                    int i;
                    string feat;
                    ro.options = &feat;

                    cout << "\nAdditionnal features. \n(1) Free wifi\n(2) Free cancellation\n(3) Wifi + cancellation\n(4) none \n\nYour choice : ";

                    cin.ignore(INT_MAX, '\n');

                    cin >> i;
                    if (i == 1)
                        feat = "wifi";
                    else if (i == 2)
                        feat = "cancellation";
                    else if (i == 3)
                        feat = "wifi_cancel";
                    else if (i == 4)
                        feat = "none";
                    rooms << *ro.options << "\n";
                }
            }
        }

        else if (i == 2)
        {
            int rn1;
            
            cout << "\nSelect the option (1-X) from the list to delete it's information : ";
            cin >> rn1;
            
            linedel("rooms.txt", rn1);
            
        }

        else if (i == 3)
        {
            int rn1;
           
            cout << "\nSelect the option (1-X) from the list to modify it's information : ";
            cin >> rn1;
            lineMOD("rooms.txt", rn1, ro);
        }
        
    }
}

void login_fail(string &str)
{
    string s, s1;
    while (true)
    {
        cout << "\nWrong e-mail or password , please try again \n"
            << "\nE-mail : ";
        cin >> s;
        cout << "Password : ";
        cin >> s1;
        AUTH(s, s1, str);
        //cout << str;
        if (str == "success" || str == "ADMIN")
            break;
    }
}

void getClientInfo(string mail, string pass, client& c)
{
    clients.open("clients.txt", ios::in);

    while (clients >> c.ID >> c.firstName >> c.lastName >> c.password >> c.address >> c.tel)
    {
        if (c.address == mail && c.password == pass)
        {
            break;
        }
        //else
          //  break;
    }
    clients.close();
}

void getNbRes(int& x)
{
    x = 0;
    int num;
    string fname, lname, sd, ed;
    reservations.open("reservations.txt", ios::in);

    while (reservations >> num >> fname >> lname >> sd >> ed)
    {
        if (fname == "")
            break;
        x++;
    }
    reservations.close();
}

void getNbRooms(int& x)
{
    x = 0;
    int num;
    string address, type, price, feat;
    rooms.open("rooms.txt", ios::in);

    while (rooms >> num >> address >> type >> price >> feat)
    {
        if (address == "")
            break;
        x++;
    }
    rooms.close();
}

void noConflict(string date, string date1,int &n)
{
    fstream file;
    string num,num1;
    string  sd, ed, fname, lname;
    string line;

    file.open("avRoom.txt", ios::app);
    reservations.open("reservations.txt", ios::in);

    n = 1;
    int a;

    getNbRooms(a);
    bool* arr = new bool[a];

    for (int i = 0; i < a; i++)
    {
        arr[i] = false;
    }
    int i = 0;
    string* roomInfo = new string[a];
    rooms.open("rooms.txt", ios::in);
    while (getline(rooms, line))
    {

        roomInfo[i] = line;
        num = line.substr(0, line.find('\t'));
        reservations.close();
        reservations.open("reservations.txt", ios::in);
        while (reservations >> num1 >> fname >> lname >> sd >> ed) 
        {
            if (num == num1)
            {
                if (date > ed || date1 < sd)
                {
                    continue;
                }
                else
                {
                    arr[i] = true;
                    break;
                }
            }
        }
        reservations.close();
        if (arr[i] == false)
        {
            cout << n++ << ") " << roomInfo[i] << endl;
            file << roomInfo[i] << endl;
        }
        i++;
        if (i == a)
            break;
    }
    rooms.close();
    file.close();
}

void roomSelect(int n, client &c, string date, string date1)
{
    
    ifstream i;
    i.open("avRoom.txt", ios::in);
    ofstream o, u;
    o.open("oneAccRes.txt", ios::app);
    u.open("reservations.txt", ios::app);

    
    string s,s1;
    string num,price,address, type;
    int line = 1;
    while (getline(i, s))
    {
        iss x(s);
        x >> num >> address >> type >> price >> feat;
        c.r->num = stoi(num);
        c.r->address = address;
        c.r->type = type;
        c.r->price = stod(price);
        c.r->options = &feat;

        s1 = num + "\t\t" + c.firstName + "\t\t" + c.lastName + "\t\t" + date + "\t\t" + date1;
        if (line == n)
        {
            o << s1;
            o << s << endl;
            u << s1 << endl;
            break;
        }
        line++;
    }
    u.close();
    o.close();
    i.close();

}

void getUserRes(client& c,int&x)
{
    remove("oneAccRes.txt");
    x = 0;
    fstream i, o, u;
    string s;
    string num, fname, lname, sd, ed;
    string n, address, type, price;
    i.open("reservations.txt", ios::in);
    
    u.open("oneAccRes.txt", ios::app);

    while (i >> num >> fname >> lname >> sd >> ed)
    {
        if (c.firstName == fname && c.lastName == lname)
        {
            o.open("rooms.txt", ios::in);
            while (o >> n >> address >> type >> price >> feat)
            {
                if (num == n)
                {
                    u << num << "\t\t" << address << "\t\t" << type << "\t\t" << price << "\t\t" << feat << "\t\t" << sd << "\t\t" << ed << endl;
                    x++;
                }
            }o.close();
        }
    }u.close();

    u.open("oneAccRes.txt", ios::in);
    //cout << "\n\n" << x << "\n\n";
    room *k = new room[x];
    c.r = k;
    string s1, s2;
    int y, m, d;
    int y1, m1, d1;
    int b = 1;
    
    for (int l = 0; l < x; l++,b++)
    {
        u >> c.r[l].num >> c.r[l].address >> c.r[l].type >> c.r[l].price >> feat;
        u >> s1 >> s2;
        cout << b << ") " << c.r[l].num << "\t\t" << c.r[l].address << "\t\t" << c.r[l].type << "\t\t" << c.r[l].price << "\t\t" << feat <<"\t\t"<<s1<<"\t\t"<<s2<< endl;

        y = stoi(s1.substr(0, 4));
        m = stoi(s1.substr(5, 2));
        d = stoi(s1.substr(8, 2));

        y1 = stoi(s2.substr(0, 4));
        m1 = stoi(s2.substr(5, 2));
        d1 = stoi(s2.substr(8, 2));

        c.r[l].start_date.year = y;
        c.r[l].start_date.month = m;
        c.r[l].start_date.year = d;

        c.r[l].end_date.year = y1;
        c.r[l].end_date.month = m1;
        c.r[l].end_date.year = d1;

        //cout << y <<'-' << m <<'-' << d <<endl<< y1 <<'-' << m1<<'-' << d1<<endl;
    }
}



void login_success(string mail, string pass, client& c, room& ro)
{
    int i, NB_rooms, day, month, year, d1, m1, y1;
    string fname, lname;
    getClientInfo(mail, pass, c);
    string date, date1;
    fname = c.firstName;
    lname = c.lastName;

    cout << "\n\n\nWelcome " << c.firstName << " !\n\n";
    cout << "What are you here for ? \n\n"
        << "1) Reserve a room\n"
        << "2) Cancel reservation \n\n"
        << "Your choice : ";

    cin >> i;
    int cc;
    if (i == 1)
    {
        //time_t x;
        //time(&x);
        //struct tm y = *localtime(&x);

        cout << "\n\n\nWe are currently only accepting up to 5 rooms at a time ,\nBusiness reservation that require >5 rooms will be available soon !\n\n"//business reservations will benefit from a discount
            << "For now , pleasse contact 01-234-567 for such reservations .\n\n\n";
        cout << "How many rooms would you like to book ? (1-5): ";
        do
        {
            cin >> NB_rooms;
        } while (NB_rooms <= 0 || NB_rooms > 5);

       // if (NB_rooms == 1)
         //   c.r = &ro;

        room* ROO = new room[NB_rooms];
        //c.r = ROO;

        do
        {
            cout << "\nEnter the starting date : \n";
            cout << "Year (2022->2024) : ";
            do
            {
                cin >> year;
            } while (year < 2022 || year>2024 /* || (year < (y.tm_year + 1900))*/);
            

            cout << "Month : ";
            do
            {
                cin >> month;
            } while (month < 1 || month>12/* || (year == (y.tm_year + 1900) && (month < y.tm_mon + 1))*/);

            cout << "Day : ";
            do
            {
                cin >> day;
            } while (day < 1 || day>31/* || (year == (y.tm_year + 1900) && month == (y.tm_mon + 1) && (day < y.tm_mday))*/);

            date = to_string(year) + '-';
            if (month < 10)
                date += '0' + to_string(month) + '-';
            else
                date += to_string(month) + '-';

            if (day < 10)
                date += '0' + to_string(day);
            else
                date += to_string(day);
            


            cout << "\n\nEnter ending date : \n"
                << "Day : ";
            do
            {
                cin >> d1;
            } while (d1 < 1 || d1>31);

            cout << "Month : ";
            do
            {
                cin >> m1;
            } while (m1 < 1 || m1>12);

            cout << "Year (2022->2024) : ";
            do
            {
                cin >> y1;
            } while (y1 < 2022 || y1>2024);

            date1 = to_string(y1) + '-';

            if (m1 < 10)
                date1 += '0' + to_string(m1) + '-';
            else
                date1 += to_string(m1) + '-';

            if (d1 < 10)
                date1 += '0' + to_string(d1);
            else
                date1 += to_string(d1);


            if (date > date1)
                cout << "\n\nEnter valid dates !!\n";

        } while (date > date1);


        c.r->start_date.day = day;
        c.r->start_date.month = month;
        c.r->start_date.year = year;
        c.r->end_date.day = d1;
        c.r->end_date.month = m1;
        c.r->end_date.year = y1;

        int n;
        
        //string a;
        //rooms.open("rooms.txt", ios::in);
        reservations.open("reservations.txt", ios::in);
        string sd, ed;
        string i;
        getline(reservations, i);
        if (i == "")
        {
            cout << "\n\n";
            showRooms();
            reservations.close();
            getNbRooms(n);
        }
        reservations.close();



        
        int k, j = 0, l = 0, h = 0;
        
        cout << "\n\nAvailable rooms :\n\n";
        noConflict(date, date1, n);

        do
        {
            cout << "\n\nYour choice : ";
            cin >> cc;
            h++;
            roomSelect(cc, c, date, date1);
            ROO[l] = *c.r;
            *ROO[l].options = *c.r->options;
            

            l++;
        } while (cc<1 || cc>n /* || h < NB_rooms*/ || h < NB_rooms);
        c.r = ROO;

    }
    else if (i == 2)
    {
        
        cout << "\n\n";
        getUserRes(c,j);
        cout << "\n\nWhich reservation would you like to cancel ? ";
        cin >> cc;
        ResCancel(cc);
        cout << "\n\nReservations cancelled !\nBelow are your reservations : \n\n";
        getUserRes(c,j);
        //cout << c.r[0].price << endl << c.r[1].price;
    }
    cout << "\n\nWould u like to check out ? (y/n) : ";
    cin >> v;
    if (v == 'y')
    {
        cout << "\n\nThese are your reservations : \n\n";
        getUserRes(c, j);
        sortPrice(c.r, j);
        //cout << c.r[0].price << endl << c.r[1].price << endl << c.r[2].price << endl << c.r[3].price << endl;
    }
}

int main()
{   

    cout << "################################################" << endl
        << "WELCOME TO ELIE'S RESERVATION APP ! ";
    
    //string output = sha("hello");
    //cout << endl << output;
    remove("avRoom.txt");
    remove("oneAccRes.txt");
    int i;
    string s, s1;
    string str;
    char a;
    client c;
    room ro;
    c.r = &ro;


    cout << "\n\nAlready have an account ? (y/n) : ";

    cin >> a; cout << endl;
    if (a == 'y')
    {
        cout << "In order to login , fill the blanks with ur credentials : " << endl << endl
            << "\nE-mail address : ";
        cin.ignore(INT_MAX, '\n');
        getline(cin, s);   
        cout << "Password : ";
        getline(cin, s1);
        AUTH(s, sha(s1), str);
        
        if (str == "fail")
        {
            login_fail(str);
        }
        if (str == "success")
        {
            //getinfo(s, s1, c);
            login_success(s, s1, c, ro);
        }
        if (str == "ADMIN")
        {
            admin_mode(ro);
        }
    }
    else if (a == 'n')
    {
        cout << "\nLet's get you started ! " << endl;
        cin.ignore(INT_MAX, '\n');
        getID(id);
        cout << id << endl;

        input(c);
    }
    else
    {
        cout << "We'll consider this option in the future xD " << endl
            << "Back to the home page ! \n\n";
    }
}

