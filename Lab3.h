#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <malloc.h>
#include <string>
#include <sstream>
using namespace std;


//typedef int(*IntFuncPtr1)(int);
//typedef long(*LongFuncPtr1)(long);
//typedef float(*FloatFuncPtr1)(float);
//typedef double(*DoubleFuncPtr1)(double);
//typedef string(*StringFuncPtr1)(string);


double doublerand(double min, double max)
{
    double f = (double)rand() / RAND_MAX;
    return min + f * (max - min);
}

float floatrand(float min, float max)
{
    float f = (float)rand() / RAND_MAX;
    return min + f * (max - min);
}


//template<typename T>
//class FuncArray
//{
//private:
//    T(**ptr)(T);
//    int size;
//public:
//    T(**GetArray())(T) { return ptr; }
//    int GetSize() { return size; }
//    FuncArray()
//    {
//        size = 0;
//        ptr = nullptr;
//    }
//    FuncArray(T(**other)(T), int len)
//    {
//        this->size = len;
//        this->ptr = malloc(len * sizeof(T(*)(T)));
//        for (int i = 0; i < len; i++)
//        {
//            this->ptr[i] = other[i];
//        }
//    }
//    FuncArray(T(*func)(T), int len)
//    {
//        this->size = len;
//        this->ptr = malloc(len * sizeof(T(*)(T)));
//        for (int i = 0; i < len; i++)
//        {
//            this->ptr[i] = &func;
//        }
//    }
//    FuncArray(int len)
//    {
//        this->size = len;
//        this->ptr = malloc(len * sizeof(T(*)(T)));
//        for (int i = 0; i < len; i++)
//        {
//            this->ptr[i] = &func<T>;
//        }
//    }
//    T(*operator[](int index))(T)
//    {
//        return ptr[index];
//    }
//};

//template <typename T>
//class FuncPtr1
//{
//private:
//    T(*ptr)(T);
//    static T CheckValue;
//public:
//    FuncPtr1()
//    {
//        this->ptr = nullptr;
//    }
//    FuncPtr1(T(*other)(T))
//    {
//        ptr = other;
//    }
//    FuncPtr1(FuncPtr1* other)
//    {
//        ptr = other->ptr;
//    }
//    T(*GetPtr())(T)
//    {
//        return ptr;
//    }
//    bool operator>(FuncPtr1* other)
//    {
//        if (this->GetPtr()(CheckValue) > other->GetPtr()(CheckValue)) return 1;
//        return 0;
//    }
//    bool operator<(FuncPtr1* other)
//    {
//        if (this->GetPtr()(CheckValue) < other->GetPtr()(CheckValue)) return 1;
//        return 0;
//    }
//    bool operator==(FuncPtr1* other)
//    {
//        if (this->GetPtr()(CheckValue) == other->GetPtr()(CheckValue)) return 1;
//        return 0;
//    }
//};


class Func
{
private:
    double* args;
    int len; // pow + 1
    double checkvalue;
public:
    Func()
    {
        args = nullptr;
        len = 0;
        checkvalue = 0;
    }

    Func(double* args, int len)
    {
        this->len = len;
        this->args = new double[len];
        for (int i = 0; i < len; i++)
        {
            this->args[i] = args[i];
        }
        checkvalue = doublerand(-1000, 1000);
    }

    friend istream& operator>>(istream& in, Func& c);
    friend ostream& operator<<(ostream& out, Func c);
    friend string to_string(Func f);

    Func(double* args, int len, double checkvalue) : Func(args, len)
    {
        this->checkvalue = checkvalue;
    }
    double GetY(double x)
    {
        double ret = 0;
        for (int i = 0; i < len; i++)
        {
            ret += args[i] * pow(x, i);
        }
        return ret;
    }

    double GetY()
    {
        double ret = 0;
        for (int i = 0; i < len; i++)
        {
            ret += args[i] * pow(this->checkvalue, i);
        }
        return ret;
    }

    bool operator>(Func other)
    {
        return (this->GetY() > other.GetY());
    }

    bool operator<(Func other)
    {
        return (this->GetY() < other.GetY());
    }

    bool operator==(Func other)
    {
        return (this->GetY() == other.GetY());
    }

    Func operator+(Func other)
    {
        int maxlen = max(this->len, other.len);
        int minlen = min(this->len, other.len);
        int deltalen = maxlen - minlen;
        double* dtemp = new double[maxlen];
        if (other.len > this->len)
        {
            for (int i = 0; i < deltalen; i++)
            {
                dtemp[maxlen - i - 1] = other.args[maxlen - i - 1];
            }
            for (int i = deltalen; i < maxlen; i++)
            {
                dtemp[maxlen - i - 1] = other.args[maxlen - i - 1] + this->args[maxlen - i - 1];
            }
        }
        else
        {
            for (int i = 0; i < deltalen; i++)
            {
                dtemp[maxlen - i - 1] = this->args[maxlen - i - 1];
            }
            for (int i = deltalen; i < maxlen; i++)
            {
                dtemp[maxlen - i - 1] = other.args[maxlen - i - 1] + this->args[maxlen - i - 1];
            }
        }
        return Func(dtemp, maxlen, this->checkvalue);
    }

    Func operator*(Func other)
    {
        int maxlen = max(this->len, other.len);
        int minlen = min(this->len, other.len);
        int deltalen = maxlen - minlen;
        double* dtemp = new double[maxlen];
        if (other.len > this->len)
        {
            for (int i = 0; i < deltalen; i++)
            {
                dtemp[maxlen - i - 1] = other.args[maxlen - i - 1];
            }
            for (int i = deltalen; i < maxlen; i++)
            {
                dtemp[maxlen - i - 1] = other.args[maxlen - i - 1] * this->args[maxlen - i - 1];
            }
        }
        else
        {
            for (int i = 0; i < deltalen; i++)
            {
                dtemp[maxlen - i - 1] = this->args[maxlen - i - 1];
            }
            for (int i = deltalen; i < maxlen; i++)
            {
                dtemp[maxlen - i - 1] = other.args[maxlen - i - 1] * this->args[maxlen - i - 1];
            }
        }
        return Func(dtemp, maxlen, this->checkvalue);
    }

};



int rand(int min, int max)
{
    return min + rand() % (max - min + 1);
}

class complex
{
public:

    complex()
    {
        this->Re = 0;
        this->Im = 0;
    }

    complex(double Re, double Im)
    {
        this->Re = Re;
        this->Im = Im;
    }

    friend ostream& operator<<(ostream& out, const complex c);

    friend istream& operator>>(istream& in, complex& c);

    complex operator=(const complex c1)
    {
        this->Im = c1.Im;
        this->Re = c1.Re;
        return complex(c1.Re, c1.Im);
    }

    double& GetRe()
    {
        return Re;
    }

    double& GetIm()
    {
        return Im;
    }

    bool operator==(const complex other)
    {
        if (this->Re == other.Re && this->Im == other.Im) return true;
        else return false;
    }

    bool operator>(complex other)
    {
        if (sqrt(this->GetRe() * this->GetRe() + this->GetIm() * this->GetIm()) > sqrt(other.GetRe() * other.GetRe() + other.GetIm() * other.GetIm())) return 1;
        return 0;
    }

    bool operator<(complex other)
    {
        if (sqrt(this->GetRe() * this->GetRe() + this->GetIm() * this->GetIm()) < sqrt(other.GetRe() * other.GetRe() + other.GetIm() * other.GetIm())) return 1;
        return 0;
    }

    void operator+=(const complex* other)
    {
        this->Re += other->Re;
        this->Im += other->Im;
    }

    void operator+=(const complex other)
    {
        this->Re += other.Re;
        this->Im += other.Im;
    }

    void operator*=(const complex other)
    {
        double ReStart = this->Re, ImStart = this->Im;
        this->Re = ReStart * other.Re - ImStart * other.Im;
        this->Im = ReStart * other.Im + ImStart * other.Re;
    }

    complex& operator=(const int i)
    {
        this->Im = this->Re = i;
        return *this;
    }

    complex& operator*(const complex other)
    {
        complex* temp = new complex();
        temp->Re = Re * other.Re - Im * other.Im;
        temp->Im = Re * other.Im + Im * other.Re;
        return *temp;
    }

    complex& operator+(const complex other)
    {
        complex* temp = new complex();
        temp->Re = Re + other.Re;
        temp->Im = Im + other.Im;
        return *temp;
    }

    void rand(double min = 0, double max = 1000)
    {
        Re = doublerand(min, max);
        Im = doublerand(min, max);
        //complex(doublerand(min, max), doublerand(min, max));
    }

    void Print()
    {
        cout << this->to_string() << endl;
    }

    string to_string()
    {
        return "Re: " + std::to_string(Re) + "     Im: " + std::to_string(Im);
    }
private:
    double Re;
    double Im;
};

//typedef complex(*ComplexFuncPtr1)(complex);

template<typename T>
void sort_arr(T* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (arr[i] < arr[j])
            {
                swap(arr[i], arr[j]);
            }
        }
    }
}

template<typename T>
void sort_arr(T* arr, long long size)
{
    for (long long i = 0; i < size; i++)
    {
        for (long long j = 0; j < size; j++)
        {
            if (arr[i] < arr[j])
            {
                swap(arr[i], arr[j]);
            }
        }
    }
}
template <typename T>
void qsortRecursive(T* mas, long long size) {
    //?????????????????? ?? ???????????? ?? ?? ?????????? ??????????????
    long long i = 0;
    long long j = size - 1;

    //?????????????????????? ?????????????? ??????????????
    long long mid = mas[size / 2];

    //?????????? ????????????
    do {
        //?????????????????? ????????????????, ???????? ????, ?????????????? ?????????? ???????????????????? ?? ???????????? ??????????
        //?? ?????????? ?????????? ?????????????? ????????????????????(?????????????????? ???? ??????????) ????????????????, ?????????????? ???????????? ????????????????????????
        while (mas[i] < mid) {
            i++;
        }
        //?? ???????????? ?????????? ???????????????????? ????????????????, ?????????????? ???????????? ????????????????????????
        while (mas[j] > mid) {
            j--;
        }

        //???????????? ???????????????? ??????????????
        if (i <= j) {
            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    //?????????????????????? ????????????, ???????? ????????????????, ?????? ??????????????????????
    if (j > 0) {
        //"?????????? ??????????"
        qsortRecursive(mas, j + 1);
    }
    if (i < size) {
        //"?????????? ??????????"
        qsortRecursive(&mas[i], size - i);
    }
}
istream& operator>>(istream& in, complex& c)
{
    cout << "Re: ";
    in >> c.GetRe();
    cout << "Im: ";
    in >> c.GetIm();
    return in;
}

istream& operator>>(istream& in, Func& c)
{
    c.len = 0;
    while (1)
    {
        cout << "len: ";
        in >> c.len;
        if (c.len <= 0)
        {
            cout << "???????????????? ????????.\n";
            in.clear();
            while (in.get() != '\n');
        }
        else
        {
            break;
        }
    }
    if (c.args != nullptr)
    {
        delete c.args;
    }
    c.args = new double[c.len];
    c.checkvalue = 0;
    for (int i = 0; i < c.len; i++)
    {
        cout << i + 1 << "?? ?????????????? ??????????????: ";
        in >> c.args[i];
    }

    cout << "?????????????? ???????????????? ?????? ????????????????: ";
    in >> c.checkvalue;

    return in;
}

ostream& operator<<(ostream& out, Func c)
{
    for (int i = 0; i < c.len; i++)
    {
        out << to_string(c.args[c.len - i - 1]) + "X^" + to_string(c.len - i - 1) + " + ";
    }
    //out << "0    checkvalue = " + to_string(c.checkvalue) + "    Y = " + to_string(c.GetY());
    out << "0    checkvalue = " + to_string(c.checkvalue);
    //out << to_string(c.GetY());
    return out;
}

ostream& operator<<(ostream& out, const complex c)
{
    out << to_string(c.Re) + "+" + to_string(c.Im) + "i";
    return out;
}

void swap(complex* c1, complex* c2)
{
    complex* temp = new complex();
    temp = c1;
    c1 = c2;
    c2 = temp;
}

double abs(complex num)
{
    return sqrt(num.GetRe() * num.GetRe() + num.GetIm() * num.GetIm());
}
template <typename T>
class BinaryTree;
template<typename T>
BinaryTree<T>* GenBalancedTree(T* bmass, int len);

string GenRandomString(const int len) {
    static const char alphanum[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

class Person
{
private:
    static int count;
    int ID;
    string FirstName;
    string MiddleName;
    string LastName;
    long long BirthDate;
public:
    Person()
    {
        ID = count;
        count++;
        FirstName = "-";//"????????";
        MiddleName = "-";//"????????????????";
        LastName = "-";//"????????????";
        BirthDate = time(NULL);//time(NULL) - rand();
    }
    Person(string FirstName, string MiddleName, string LastName, time_t BirthDate)
    {
        ID = count;
        count++;
        this->FirstName = FirstName;
        this->MiddleName = MiddleName;
        this->LastName = LastName;
        this->BirthDate = BirthDate;
    }

    Person(string FullName, time_t BirthDate)
    {
        ID = count;
        count++;
        istringstream iss(FullName);
        string temp;
        getline(iss, temp, ' ');
        this->MiddleName = temp;
        getline(iss, temp, ' ');
        this->FirstName = temp;
        getline(iss, temp, ' ');
        if (temp != FirstName) this->LastName = temp;
        this->BirthDate = BirthDate;
    }
    int& GetId() { return ID; }
    void SetID(int newid) { ID = newid; }
    void SetFirstName(string fname) { FirstName = fname; }
    void SetMiddleName(string mname) { MiddleName = mname; }
    void SetLastName(string lname) { LastName = lname; }
    void SetBirthDate(time_t date) { BirthDate = date; }
    string& GetFirstName() { return FirstName; }
    string& GetMiddleName() { return MiddleName; }
    string& GetLastName() { return LastName; }
    string GetFullName() { return MiddleName + " " + FirstName + " " + LastName; }
    string GetBirthDate()
    {
        /*string ret = asctime(gmtime(&BirthDate));
        ret.resize(ret.length() - 1);
        return ret; */
        return to_string(BirthDate);
    }
    time_t& GetBirthTime() { return BirthDate; }
    bool operator>(Person* other)
    {
        return this->GetFullName() > other->GetFullName();
        /*string name1 = this->GetFullName();
        string name2 = other->GetFullName();
        size_t len = min(name1.length(), name2.length()) - 1;
        for (size_t i = 0; i < len; i++)
        {
            if (name1[i] < name2[i]) return 1;
            if (name1[i] > name2[i]) return 0;
        }
        if (name1.length() > name2.length()) return 1;
        return 0;*/
    }
    bool operator<(Person other)
    {
        return this->GetFullName() < other.GetFullName();
    }
    bool operator>(Person other)
    {
        return this->GetFullName() > other.GetFullName();
    }
    bool operator==(Person other)
    {
        return this->GetFullName() == other.GetFullName();
    }
    bool operator<(Person* other)
    {
        return this->GetFullName() < other->GetFullName();
        /*string name1 = this->GetFullName();
        string name2 = other->GetFullName();
        size_t len = min(name1.length(), name2.length());
        for (size_t i = 0; i < len; i++)
        {
            if (name1[i] > name2[i]) return 0;
            if (name1[i] < name2[i]) return 1;
        }
        if (name1.length() < name2.length()) return 1;
        return 0;*/
    }
    bool operator==(Person* other)
    {
        return this->GetFullName() == other->GetFullName();
        /*string name1 = this->GetFullName();
        string name2 = other->GetFullName();
        size_t len = min(name1.length(), name2.length());
        for (size_t i = 0; i < len; i++)
        {
            if (name1[i] != name2[i]) return 0;
        }
        if (name1.length() ==  name2.length()) return 1;
        return 0;*/
    }
    /*bool operator>(Person* other)
    {
        if (this->GetBirthDate() > other->GetBirthDate()) return 1;
        if (this->GetBirthDate() < other->GetBirthDate()) return 0;
        return 0;
    }
    bool operator>=(Person* other)
    {
        if (this->GetBirthDate() > other->GetBirthDate()) return 1;
        if (this->GetBirthDate() < other->GetBirthDate()) return 0;
        return 1;
    }
    bool operator<(Person* other)
    {
        if (this->GetBirthDate() > other->GetBirthDate()) return 0;
        if (this->GetBirthDate() < other->GetBirthDate()) return 1;
        return 0;
    }
    bool operator<=(Person* other)
    {
        if (this->GetBirthDate() > other->GetBirthDate()) return 0;
        if (this->GetBirthDate() < other->GetBirthDate()) return 1;
        return 1;
    }
    bool operator==(Person* other)
    {
        if (this->GetId() == other->GetId() && this->GetFullName() == other->GetFullName()) return 1;
        else return 0;
    }*/
};

int Person::count = 0;

string to_string(Person* p)
{
    return p->GetFullName() + "_" + to_string(p->GetId()) + "_" + to_string(p->GetBirthTime());
}

class Student : public Person
{
private:
    string StudyCourse;
    int Year;
    string Group;
    string Institution;
public:
    Student() : Person()
    {
        StudyCourse = string(); // "Procrastination";
        Year = int();//rand(1, 5);
        Group = string(); //"G22-" + to_string(rand(100, 999));
        Institution = string();//"Institution";
    }
    Student(string student)
    {
        istringstream iss(student);
        string temp;
        getline(iss, temp, ' ');
        this->SetMiddleName(temp);
        getline(iss, temp, ' ');
        this->SetFirstName(temp);
        getline(iss, temp, ' ');
        this->SetLastName(temp);
        getline(iss, temp, ' ');
        this->SetID(atoi(temp.c_str()));
        getline(iss, temp, ' ');
        this->SetBirthDate(atoi(temp.c_str()));
        getline(iss, temp, ' ');
        this->SetGroup(temp);
        getline(iss, temp, ' ');
        this->SetInstitution(temp);
        getline(iss, temp, ' ');
        this->SetStudyCourse(temp);
        getline(iss, temp, ' ');
        this->SetYear(atoi(temp.c_str()));
    }
    Student(string FirstName, string MiddleName, string LastName, time_t BirthDate, string StudyCourse, string Group, string Institution, int Year) : Person(FirstName, MiddleName, LastName, BirthDate)
    {
        this->StudyCourse = StudyCourse;
        this->Group = Group;
        this->Institution = Institution;
        this->Year = Year;
    }
    bool operator==(Student* other)
    {
        return (this->GetId() == other->GetId() && this->GetFullName() == other->GetFullName() && this->GetStudyCourse() == other->GetStudyCourse() && this->GetInstitution() == other->GetInstitution() && this->GetGroup() == other->GetGroup() && this->GetYear() == other->GetYear());
    }

    bool operator==(Student other)
    {
        return (this->GetId() == other.GetId() && this->GetFullName() == other.GetFullName() && this->GetStudyCourse() == other.GetStudyCourse() && this->GetInstitution() == other.GetInstitution() && this->GetGroup() == other.GetGroup() && this->GetYear() == other.GetYear());
    }

    Student& operator+(Student other)
    {
        Student* temp = new Student();
        temp->SetBirthDate(this->GetBirthTime() + other.GetBirthTime());
        temp->SetYear(Year + other.Year);
        temp->SetFirstName(this->GetFirstName() + other.GetFirstName());
        temp->SetGroup(Group + other.GetGroup());
        temp->SetID(this->GetId() + other.GetId());
        temp->SetInstitution(Institution + other.Institution);
        temp->SetLastName(this->GetLastName() + other.GetLastName());
        temp->SetMiddleName(this->GetMiddleName() + other.GetMiddleName());
        temp->SetStudyCourse(StudyCourse + other.StudyCourse);
        temp->SetYear(Year + other.Year);
        return *temp;
    }
    Student& operator*(Student other)
    {
        Student* temp = new Student();
        temp->SetBirthDate(this->GetBirthTime() * other.GetBirthTime());
        temp->SetYear(Year * other.Year);
        temp->SetFirstName(this->GetFirstName());
        temp->SetGroup(Group);
        temp->SetID(this->GetId() * other.GetId());
        temp->SetInstitution(Institution);
        temp->SetLastName(this->GetLastName());
        temp->SetMiddleName(this->GetMiddleName());
        temp->SetStudyCourse(StudyCourse);
        temp->SetYear(Year * other.Year);
        return *temp;
    }
    void SetStudyCourse(string StudyCourse) { this->StudyCourse = StudyCourse; }
    void SetYear(int Year) { this->Year = Year; }
    void SetGroup(string Group) { this->Group = Group; }
    void SetInstitution(string Institution) { this->Institution = Institution; }
    string& GetStudyCourse() { return StudyCourse; }
    int& GetYear() { return Year; }
    string& GetGroup() { return Group; }
    string& GetInstitution() { return Institution; }
};

ostream& operator<<(ostream& out, Student& p)
{
    out << p.GetFullName() + " " + to_string(p.GetId()) + " " + p.GetBirthDate() + " " + p.GetGroup() + " " + p.GetInstitution() + " " + p.GetStudyCourse() + " " + to_string(p.GetYear());
    return out;
}



class Teacher : public Person
{
private:
    string Subject;
public:
    Teacher() : Person()
    {
        Subject = string();
    }

    Teacher(string teacher)
    {

    }

    bool operator==(Teacher other)
    {
        return (this->GetId() == other.GetId() && this->GetFullName() == other.GetFullName() && this->GetSubject() == other.GetSubject());
    }

    bool operator==(Teacher* other)
    {
        return (this->GetId() == other->GetId() && this->GetFullName() == other->GetFullName() && this->GetSubject() == other->GetSubject());
    }

    Teacher& operator+(Teacher other)
    {
        Teacher* temp = new Teacher();
        temp->SetBirthDate(this->GetBirthTime() + other.GetBirthTime());
        temp->SetFirstName(this->GetFirstName() + other.GetFirstName());
        temp->SetID(this->GetId() + other.GetId());
        temp->SetLastName(this->GetLastName() + other.GetLastName());
        temp->SetMiddleName(this->GetMiddleName() + other.GetMiddleName());
        temp->SetSubject(this->GetSubject() + other.GetSubject());
        return *temp;
    }

    Teacher& operator*(Teacher other)
    {
        Teacher* temp = new Teacher();
        temp->SetBirthDate(this->GetBirthTime() * other.GetBirthTime());
        temp->SetFirstName(this->GetFirstName());
        temp->SetID(this->GetId() * other.GetId());
        temp->SetLastName(this->GetLastName());
        temp->SetMiddleName(this->GetMiddleName());
        temp->SetSubject(this->GetSubject());
        return *temp;
    }

    Teacher(string FirstName, string MiddleName, string LastName, time_t BirthDate, string Subject) : Person(FirstName, MiddleName, LastName, BirthDate)
    {
        this->Subject = Subject;
    }
    void SetSubject(string Subject) { this->Subject = Subject; }
    string& GetSubject() { return Subject; }
};

//string to_string(Student* p)
//{
//    return p->GetFullName() + "_" + to_string(p->GetId()) + "_" + to_string(p->GetBirthTime()) + "_" + p->GetGroup() + "_" + p->GetInstitution() + "_" + p->GetStudyCourse() + "_" + to_string(p->GetYear());
//}

string to_string(Func c)
{
    string temp = string();
    for (int i = 0; i < c.len; i++)
    {
        temp += to_string(c.args[c.len - i - 1]) + "X^" + to_string(c.len - i - 1) + " + ";
    }
    temp += "0    checkvalue = " + to_string(c.checkvalue) + "    Y = " + to_string(c.GetY());
    return temp;
}

string to_string(string text)
{
    return text;
}

string to_string(complex num)
{
    return to_string(num.GetRe()) + "+" + to_string(num.GetIm()) + "i";
}

string to_string(Student p)
{
    return p.GetFullName() + "_" + to_string(p.GetId()) + "_" + to_string(p.GetBirthTime()) + "_" + p.GetGroup() + "_" + p.GetInstitution() + "_" + p.GetStudyCourse() + "_" + to_string(p.GetYear());
}

//string to_string(Teacher* p)
//{
//    return p->GetFullName() + "_" + to_string(p->GetId()) + "_" + p->GetBirthDate() + "_" + p->GetSubject();
//}

string to_string(Teacher p)
{
    return p.GetFullName() + "_" + to_string(p.GetId()) + "_" + p.GetBirthDate() + "_" + p.GetSubject();
}

ostream& operator<<(ostream& out, Teacher& p)
{
    out << p.GetFullName() + " " + to_string(p.GetId()) + " " + p.GetBirthDate() + " " + p.GetSubject();
    return out;
}

istream& operator>>(istream& in, Teacher& t)
{
    cout << "?????????????? ?????????? ???????????????? ?? ???????? time_t: ";
    in >> t.GetBirthTime();
    cout << "?????????????? ID(?????????????? ID = " << t.GetId() << "): ";
    in >> t.GetId();
    cout << "?????????????? ??????: ";
    in >> t.GetFirstName();
    cout << "?????????????? ??????????????: ";
    in >> t.GetMiddleName();
    cout << "?????????????? ????????????????: ";
    in >> t.GetLastName();
    cout << "?????????????? ?????????????????????????? ??????????????: ";
    in >> t.GetSubject();
    return in;
}

Student* StudentRand()
{
    Student* temp = new Student();
    time_t btime = rand(1, 1000000000);
    temp->SetBirthDate(btime);
    int itemp = rand(1, 5);
    temp->SetYear(itemp);
    string stemp = GenRandomString(rand(5, 20));
    temp->SetGroup(stemp);
    stemp = GenRandomString(rand(5, 20));
    temp->SetInstitution(stemp);
    stemp = GenRandomString(rand(5, 20));
    temp->SetFirstName(stemp);
    stemp = GenRandomString(rand(5, 20));
    temp->SetMiddleName(stemp);
    stemp = GenRandomString(rand(5, 20));
    temp->SetLastName(stemp);
    stemp = GenRandomString(rand(5, 20));
    temp->SetStudyCourse(stemp);
    return temp;
}

Teacher* TeacherRand()
{
    Teacher* temp = new Teacher();
    time_t btime = rand(1, 1000000000);
    temp->SetBirthDate(btime);
    int itemp = rand(1, 5);
    string stemp = GenRandomString(rand(5, 20));
    stemp = GenRandomString(rand(5, 20));
    temp->SetFirstName(stemp);
    stemp = GenRandomString(rand(5, 20));
    temp->SetMiddleName(stemp);
    stemp = GenRandomString(rand(5, 20));
    temp->SetLastName(stemp);
    stemp = GenRandomString(rand(5, 20));
    temp->SetSubject(stemp);
    return temp;
}
long long rand(long long min, long long max)
{
    return min + rand() % (max - min + 1);
}

double* GenMass(int len, int randmax = 1000, int randmin = -1000)
{
    double* mass = new double[len];
    for (int i = 0; i < len; i++)
    {
        mass[i] = doublerand(randmin, randmax);
    }
    return mass;
}

template<typename T>
void* TemplateRand(int randmax = 1000, int strmin = 5, int strmax = 20, int argmax = 10, int argmin = 1)
{
    if (typeid(T).name() == typeid(int).name())
    {
        return new int(rand(-randmax, randmax));
    }
    else if (typeid(T).name() == typeid(double).name())
    {
        return new double(doublerand(-randmax, randmax));
    }
    else if (typeid(T).name() == typeid(string).name())
    {
        return new string(GenRandomString(rand(strmin, strmax)));
    }
    else if (typeid(T).name() == typeid(complex).name())
    {
        return new complex(doublerand(-randmax, randmax), doublerand(-randmax, randmax));
    }
    else if (typeid(T).name() == typeid(Student).name())
    {
        return new Student(GenRandomString(rand(strmin, strmax)), GenRandomString(rand(strmin, strmax)), GenRandomString(rand(strmin, strmax)), 946080000 + rand(100000000, 157680000), GenRandomString(rand(strmin, strmax)), GenRandomString(1) + "-" + to_string(rand(100, 999)), GenRandomString(rand(strmin, strmax)), rand(1, 5));
    }
    else if (typeid(T).name() == typeid(Teacher).name())
    {
        return new Teacher(GenRandomString(rand(strmin, strmax)), GenRandomString(rand(strmin, strmax)), GenRandomString(rand(strmin, strmax)), rand(1, 1000000000), GenRandomString(rand(strmin, strmax)));
    }
    else if (typeid(T).name() == typeid(Func).name())
    {
        int len = rand(argmin, argmax);
        return new Func(GenMass(len), len, doublerand(-randmax, randmax));
    }
    else
    {
        return NULL;
    }
}

istream& operator>>(istream& in, Student& t)
{
    cout << "?????????????? ?????????? ???????????????? ?? ???????? time_t: ";
    in >> t.GetBirthTime();
    cout << "?????????????? ?????? ????????????????: ";
    in >> t.GetYear();
    cout << "?????????????? ????????????: ";
    in >> t.GetGroup();
    cout << "?????????????? ID(?????????????? ID = " << t.GetId() << "): ";
    in >> t.GetId();
    cout << "?????????????? ?????????? ????????????????: ";
    in >> t.GetInstitution();
    cout << "?????????????? ??????: ";
    in >> t.GetFirstName();
    cout << "?????????????? ??????????????: ";
    in >> t.GetMiddleName();
    cout << "?????????????? ????????????????: ";
    in >> t.GetLastName();
    cout << "?????????????? ?????????????????????? ????????????????: ";
    in >> t.GetStudyCourse();
    return in;
}


template<typename T>
class BinaryTree
{
public:

    BinaryTree()
    {
        LeftRoot = RightRoot = nullptr;
        Data = nullptr;
    }
    BinaryTree(BinaryTree<T>* other)
    {
        int len = other->GetSize();
        T* mass = new T[len];
        other->GetMass(mass);
        for (int i = 0; i < len; i++)
        {
            this->Insert(mass[i]);
        }
    }

    ~BinaryTree()
    {
        if (Data != nullptr) delete Data;
        if (LeftRoot != nullptr) delete LeftRoot;
        if (RightRoot != nullptr) delete RightRoot;
    }

    T& GetData()
    {
        return *Data;
    }

    BinaryTree<T>* GetLeftRoot()
    {
        return LeftRoot;
    }

    int GetMaxLVL()
    {
        static int LVL = 0;
        if (this == NULL) return LVL;
        return max(this->LeftRoot->GetMaxLVL(), this->RightRoot->GetMaxLVL());
    }

    int GetMinLVL()
    {
        static int LVL = 0;
        if (this == NULL) return LVL;
        return min(this->LeftRoot->GetMinLVL(), this->RightRoot->GetMinLVL());
    }

    BinaryTree<T>* DeleteElem(T elem)
    {
        int len = this->GetSize();
        T* mass = new T[len];
        this->GetMass(mass);
        BinaryTree<T>* newtree = new BinaryTree<T>();
        for (int i = 0; i < len; i++)
        {
            if (!(mass[i] == elem))
            {
                newtree->Insert(mass[i]);
            }
        }
        delete this;
        return newtree;
    }

    /*void DeleteElem(int value)
    {
        if (node == NULL)
            return;

        if (value < *this->Data)
            return this->LeftRoot->DeleteElem(value);
        else if (value > node->value)
            return this->RightRoot->DeleteElem(value);
        else {
            if (this->LeftRoot == NULL && this->RightRoot == NULL) {
                if (node->parent->leftChild == node)
                    node->parent->leftChild = NULL;
                else
                    node->parent->rightChild = NULL;
                delete node;
            }
            else {
                BinaryTreeNode* newnode = NULL;
                if (node->leftChild != NULL) {
                    newnode = Rightmost(node->leftChild);
                }
                else
                    newnode = Leftmost(node->rightChild);

                if (node->parent->leftChild == node)
                    node->parent->leftChild = newnode;
                else
                    node->parent->rightChild = newnode;

                newnode->parent = node->parent;
                newnode->rightChild = node->rightChild;
                newnode->leftChild = node->leftChild;

                delete node;
            }
        }
    }
    BinaryTree<T>* Leftmost() {
        if (this == NULL)
            return NULL;
        if (this->LeftRoot != NULL) {
            return Leftmost(this->LeftRoot);
        }
        return node;
    }
    BinaryTree<T>* Rightmost() {
        if (this == NULL)
            return NULL;
        if (this->RightRoot != NULL) {
            return Rightmost(this->RightRoot);
        }
        return node;
    }*/

    /*void BlanceTree()
    {
        int len = this->GetSize();
        T* mass = new T[len];
        this->GetMass(mass);
        sort_arr<T>(mass, len);
        BinaryTree<T>* newtree = GenBalancedTree(mass, len);
        delete this;
        this = newtree;
    }*/

    BinaryTree<T>* GetRightRoot()
    {
        return RightRoot;
    }



    BinaryTree<T>* GetLeftSubTree()
    {
        if (LeftRoot == nullptr) LeftRoot = new BinaryTree<T>();
        return LeftRoot;
    }

    BinaryTree<T>* GetRightSubTree()
    {
        if (RightRoot == nullptr) RightRoot = new BinaryTree<T>();
        return RightRoot;
    }

    BinaryTree(T* mass, int len)
    {
        for (int i = 0; i < len; i++)
        {
            this->Insert(mass[i]);
        }
    }

    BinaryTree(T* mass, long long len)
    {
        for (long long i = 0; i < len; i++)
        {
            this->Insert(mass[i]);
        }
    }

    BinaryTree(string String, string type = "RootLeftRight")
    {
        if (type == "LeftRightRoot")
        {

        }
        else if (type == "RightLeftRoot")
        {

        }
        else if (type == "LeftRootRight")
        {

        }
        else if (type == "RightRootLeft")
        {

        }
        //else if (type == "RootRightLeft")
        //{
        //    {
        //        while (1)
        //        {
        //            istringstream iss(String);
        //            string temp_s;
        //            string res;
        //            string* mass = new string[iss.str().length()]();
        //            getline(iss, temp_s, '\"');
        //            getline(iss, temp_s, '\"');
        //            for (int i = 0;; i++)
        //            {
        //                mass[i] = temp_s;
        //                getline(iss, temp_s, '\"');
        //                if (temp_s == string())
        //                {
        //                    mass->resize(i + 1);
        //                    break;
        //                }
        //            }
        //            int i1 = 0, i2 = 0;
        //            for (int i = 0;; i++)
        //            {
        //                if (mass[i] > mass[0])
        //            }
        //            string root = temp_s;
        //            getline(iss, temp_s, '\"');
        //            /*void* temp_t = new T();
        //            if (typeid(T).name() == typeid(double).name())
        //            {
        //                *(T*)temp_t = T(atof(temp_s.c_str()));
        //            }
        //            if (typeid(T).name() == typeid(string).name())
        //            {
        //                *(string*)temp_t = string(temp_s);
        //            }
        //            if (typeid(T).name() == typeid(Student).name())
        //            {
        //                *(Student*)temp_t = Student(temp_s);
        //            }
        //            if (typeid(T).name() == typeid(Teacher).name())
        //            {
        //                *(Teacher*)temp_t = Teacher(temp_s);
        //            }*/
        //        }
        //        istringstream iss(String);
        //        string temp_s;
        //        getline(iss, temp_s, '\"');
        //        getline(iss, temp_s, '\"');
        //        while (temp_s != string())
        //        {
        //            void* temp_t = new T();
        //            //cout << typeid(T).name()<<"  "<< atof(temp_s.c_str()) << endl;
        //            if (typeid(T).name() == typeid(double).name())
        //            {
        //                *(T*)temp_t = T(atof(temp_s.c_str()));
        //            }
        //            if (typeid(T).name() == typeid(string).name())
        //            {
        //                *(string*)temp_t = string(temp_s);
        //            }
        //            if (typeid(T).name() == typeid(Student).name())
        //            {
        //                *(Student*)temp_t = Student(temp_s);
        //            }
        //            if (typeid(T).name() == typeid(Teacher).name())
        //            {
        //                *(Teacher*)temp_t = Teacher(temp_s);
        //            }
        //            else T temp_t = T(atoi(temp_s.c_str()));
        //            this->Insert(*(T*)temp_t);
        //            getline(iss, temp_s, '\"');
        //        }
        //    }
        //}
        else if (type == "RootLeftRight")
        {
            istringstream iss(String);
            string temp_s;
            getline(iss, temp_s, '\"');
            getline(iss, temp_s, '\"');
            while (temp_s != string())
            {
                void* temp_t = new T();
                //cout << typeid(T).name()<<"  "<< atof(temp_s.c_str()) << endl;
                if (typeid(T).name() == typeid(double).name())
                {
                    *(T*)temp_t = atof(temp_s.c_str());
                }
                if (typeid(T).name() == typeid(string).name())
                {
                    *(string*)temp_t = string(temp_s);
                }
                if (typeid(T).name() == typeid(Student).name())
                {
                    *(Student*)temp_t = Student(temp_s);
                }
                if (typeid(T).name() == typeid(Teacher).name())
                {
                    *(Teacher*)temp_t = Teacher(temp_s);
                }
                else *(T*)temp_t = atoi(temp_s.c_str());
                this->Insert(*(T*)temp_t);
                getline(iss, temp_s, '\"');
            }
        }
        else cout << "ERROR Incorrect type  \"StringToTree\"  type: " + type << endl;
    }
    void Bypass(string type = "RootLeftRight")
    {
        if (type == "LeftRightRoot") this->BypassLeftRightRoot();
        else if (type == "RightLeftRoot") this->BypassRightLeftRoot();
        else if (type == "LeftRootRight") this->BypassLeftRootRight();
        else if (type == "RightRootLeft") this->BypassRightRootLeft();
        else if (type == "RootRightLeft") this->BypassRootRightLeft();
        else if (type == "RootLeftRight") this->BypassRootLeftRight();
        else cout << "ERROR Incorrect type  \"Bypass\"  type: " + type << endl;
    }

    int GetSize()
    {
        istringstream iss(this->ToString());
        string temp_s;
        getline(iss, temp_s, '\"');
        getline(iss, temp_s, '\"');
        int i = 0;
        while (temp_s != string())
        {
            i++;
            getline(iss, temp_s, '\"');
        }
        return i;
    }

    BinaryTree<T>* GetSubTreeFromPath(string path)
    {
        if (path.length() == 0 || path[0] == '\n')
        {
            int len = this->GetSize();
            T* mass = new T[len];
            this->GetMass(mass);
            BinaryTree<T>* newtree = new BinaryTree<T>(this);
            return newtree;
        }
        if (path[0] == 'r')
        {
            if (RightRoot == nullptr) return NULL;
            string path1 = string();
            int len = (int)path.length();
            path1.resize(len - 1);
            for (int i = 1; i < len; i++)
            {
                path1[i - 1] = path[i];
            }
            return RightRoot->GetSubTreeFromPath(path1);
        }
        if (path[0] == 'l')
        {
            if (LeftRoot == nullptr) return NULL;
            string path1 = string();
            int len = (int)path.length();
            path1.resize(len - 1);
            for (int i = 1; i < len; i++)
            {
                path1[i - 1] = path[i];
            }
            return LeftRoot->GetSubTreeFromPath(path1);
        }
        return NULL;
    }

    BinaryTree<T>* GetSubTree(T num)
    {
        if (num == *Data)
        {

            int len = this->GetSize();
            T* mass = new T[len];
            this->GetMass(mass);
            BinaryTree<T>* newtree = new BinaryTree<T>(this);
            return newtree;
        }
        if (num > *Data)
        {
            if (RightRoot == nullptr) return NULL;
            return RightRoot->GetSubTree(num);
        }
        if (num < *Data)
        {
            if (LeftRoot == nullptr) return NULL;
            return LeftRoot->GetSubTree(num);
        }
        return NULL;
    }


    void GetMass(T* mass, int* size = new int())
    {
        if (this != NULL)
        {
            if (Data != nullptr)
            {
                mass[*size] = *this->Data;
                (*size)++;
                RightRoot->GetMass(mass, size);
                LeftRoot->GetMass(mass, size);
            }
        }
    }
    void Insert(T item)
    {

        if (Data == nullptr)
        {
            Data = new T(item);
        }
        else
        {
            if (item > *Data)
            {
                if (RightRoot == nullptr) RightRoot = new BinaryTree<T>();
                RightRoot->Insert(item);
            }
            else if (item < *Data)
            {
                if (LeftRoot == nullptr) LeftRoot = new BinaryTree<T>();
                LeftRoot->Insert(item);
            }
            //else cout << "ERROR: item == root \"InsertRootLeftRight\""<<endl;
        }

    }

    void Insert(BinaryTree<T>* node)
    {
        if (node != NULL)
        {

            if (Data == nullptr)
            {
                Data = &node->GetData();
                LeftRoot = node->GetLeftSubTree();
                RightRoot = node->GetRightSubTree();
            }
            else
            {
                if (node->GetData() > *Data)
                {
                    if (RightRoot == nullptr) RightRoot = new BinaryTree<T>();
                    RightRoot->Insert(node);
                }
                else if (node->GetData() < *Data)
                {
                    if (LeftRoot == nullptr) LeftRoot = new BinaryTree<T>();
                    LeftRoot->Insert(node);
                }
            }
        }
    }

    bool operator==(BinaryTree<T>* other)
    {
        if (this == NULL && other == NULL)
            return true;
        else if (this == NULL || other == NULL)
            return false;
        else {
            if (*this->Data == *other->Data && this->LeftRoot->operator==(other->LeftRoot) && this->RightRoot->operator==(other->RightRoot))
                return true;
            else
                return false;
        }
    }

    /*bool CheckElement(T val)
    {
        string s1 = " " + this->ToString("RootLeftRight");
        return (s1.find(to_string(val)) > 0);
    }*/

    bool CheckElement(T val)
    {
        if (Data == nullptr) return 0;
        if (val == *Data) return true;
        if (val > *Data) return this->RightRoot->CheckElement(val);
        if (val < *Data) return this->LeftRoot->CheckElement(val);
    }

    bool CheckSubTree(BinaryTree<T>* other)
    {
        string s1 = string(), s2 = string();
        s1 = this->ToString("RootLeftRight");
        s2 = other->ToString("RootLeftRight");
        if (s1.find(s2) != string::npos)
        {
            return true;
        }
        return false;
    }

    string ToString(string type = "RootLeftRight", int mode = 0)
    {
        string temp = "";
        if (type == "LeftRightRoot")
        {
            this->ToStringLeftRightRoot(temp, mode);
            //return temp;
        }
        else if (type == "RightLeftRoot")
        {
            this->ToStringRightLeftRoot(temp, mode);
            //return temp;
        }
        else if (type == "LeftRootRight")
        {
            this->ToStringLeftRootRight(temp, mode);
            //return temp;
        }
        else if (type == "RightRootLeft")
        {
            this->ToStringRightRootLeft(temp, mode);
            //return temp;
        }
        else if (type == "RootRightLeft")
        {
            this->ToStringRootRightLeft(temp, mode);
            //return temp;
        }
        else if (type == "RootLeftRight")
        {
            this->ToStringRootLeftRight(temp, mode);
            //return temp;
        }
        else cout << "ERROR Incorrect type  \"ToString\"  type: " + type << endl;
        temp += "\"";
        return temp;
    }

    void Print(int lv = 0)
    {
        if (this != nullptr) if (Data != nullptr)
        {
            this->LeftRoot->Print(lv + 1);
            for (int i = 0; i < lv; i++)
            {
                cout << "   ";
            }
            cout << *Data << endl;
            this->RightRoot->Print(lv + 1);
        }
    }

    /*bool CheckSubTree(const BinaryTree<T>* other)
    {
        while (1)
        {
            if (other->Root > this->Root)
            {
                return this->RightRoot->CheckSubTree(other);
                break;
            }
            if (other->Root < this->Root)
            {
                return this->LeftRoot->CheckSubTree(other);
                break;
            }
            if (other->Root == this->Root)
            {
                if (this->LeftRoot != nullptr) return (this->RightRoot->CheckSubTree(other->RightRoot) && this->LeftRoot->CheckSubTree(other->LeftRoot));
                break;
            }
        }
    }

    bool operator== (const BinaryTree<T>* other)
    {
        if (this->Root == other->Root && this->LeftRoot == other->LeftRoot && this->RightRoot == other->RightRoot) return true;
        return false;
    }*/

private:

    /*void InsertRootLeftRight(T item)
    {
        if (root == nullptr)
        {
            root = new T(item);
        }
        else
        {
            if (item > *root) RightRoot->InsertRootLeftRight(item);
            else if (item < *root) LeftRoot->InsertRootLeftRight(item);
            else cout << "ERROR: item = root \"InsertRootLeftRight\"";
        }
    }

    void InsertRootRightLeft(T item)
    {
        if (root == nullptr)
        {
            root = new T(item);
        }
        else
        {
            if (item < *root) RightRoot->InsertRootLeftRight(item);
            else if (item > *root) LeftRoot->InsertRootLeftRight(item);
            else cout << "ERROR: item = root \"InsertRootLeftRight\"";
        }
    }

    void InsertRightRootLeft(T item)
    {
        if (RightRoot == nullptr)
        {
            RightRoot->root = new T(item);
        }
        else
        {
            if (item > *RightRoot->root) this->InsertRightRootLeft(item);
        }
    }*/

    void BypassRootLeftRight()
    {
        if (this != nullptr)
        {
            cout << *Data << endl;
            LeftRoot->BypassRootLeftRight();
            RightRoot->BypassRootLeftRight();
        }
    }

    void BypassRootRightLeft()
    {
        if (this != nullptr)
        {
            cout << *Data << endl;
            RightRoot->BypassRootRightLeft();
            LeftRoot->BypassRootRightLeft();
        }
    }

    void BypassRightRootLeft()
    {
        if (this != nullptr)
        {
            RightRoot->BypassRightRootLeft();
            cout << *Data << endl;
            LeftRoot->BypassRightRootLeft();
        }
    }

    void BypassLeftRootRight()
    {
        if (this != nullptr)
        {
            LeftRoot->BypassLeftRootRight();
            cout << *Data << endl;
            RightRoot->BypassLeftRootRight();
        }
    }

    void BypassRightLeftRoot()
    {
        if (this != nullptr)
        {
            RightRoot->BypassRightLeftRoot();
            LeftRoot->BypassRightLeftRoot();
            cout << *Data << endl;
        }
    }

    void BypassLeftRightRoot()
    {
        if (this != nullptr)
        {
            LeftRoot->BypassLeftRightRoot();
            RightRoot->BypassLeftRightRoot();
            cout << *Data << endl;
        }

    }

    void ToStringRootLeftRight(string& temp, int mode = 0)
    {
        if (this != nullptr && this != NULL)
        {
            if (Data != nullptr && Data != NULL)
            {
                temp += "\"";
                temp += to_string(*Data);
                //temp += " ";
                LeftRoot->ToStringRootLeftRight(temp, mode);
                RightRoot->ToStringRootLeftRight(temp, mode);
            }
        }
        else if (mode == 1)
        {
            temp += "\"";
            temp += "NULL";
            //temp += " ";
        }
    }

    void ToStringRootRightLeft(string& temp, int mode = 0)
    {
        if (this != nullptr)
        {
            temp += "\"";
            temp += to_string(*Data);
            //temp += " ";
            RightRoot->ToStringRootRightLeft(temp, mode);
            LeftRoot->ToStringRootRightLeft(temp, mode);
        }
        else if (mode == 1)
        {
            temp += "\"";
            temp += "NULL";
            //temp += " ";
        }
    }

    void ToStringRightRootLeft(string& temp, int mode = 0)
    {
        if (this != nullptr)
        {
            RightRoot->ToStringRightRootLeft(temp, mode);
            temp += "\"";
            temp += to_string(*Data);
            //temp += " ";
            LeftRoot->ToStringRightRootLeft(temp, mode);
        }
        else if (mode == 1)
        {
            temp += "\"";
            temp += "NULL";
            //temp += " ";
        }
    }

    void ToStringLeftRootRight(string& temp, int mode = 0)
    {
        if (this != nullptr)
        {
            LeftRoot->ToStringLeftRootRight(temp, mode);
            temp += "\"";
            temp += to_string(*Data);
            //temp += " ";
            RightRoot->ToStringLeftRootRight(temp, mode);
        }
        else if (mode == 1)
        {
            temp += "\"";
            temp += "NULL";
            //temp += " ";
        }
    }

    void ToStringRightLeftRoot(string& temp, int mode = 0)
    {
        if (this != nullptr)
        {
            RightRoot->ToStringRightLeftRoot(temp, mode);
            LeftRoot->ToStringRightLeftRoot(temp, mode);
            temp += "\"";
            temp += to_string(*Data);
            //temp += " ";
        }
        else if (mode == 1)
        {
            temp += "\"";
            temp += "NULL";
            //temp += " ";
        }
    }

    void ToStringLeftRightRoot(string& temp, int mode = 0)
    {
        if (this != nullptr)
        {
            LeftRoot->ToStringLeftRightRoot(temp, mode);
            RightRoot->ToStringLeftRightRoot(temp, mode);
            temp += "\"";
            temp += to_string(*Data);
            //temp += " ";
        }
        else if (mode == 1)
        {
            temp += "\"";
            temp += "NULL";
            //temp += " ";
        }
    }

    T* Data;
    BinaryTree* LeftRoot;
    BinaryTree* RightRoot;
};

template<typename T>
T sum(T num1, T num2)
{
    return num1 + num2;
}

template<typename T>
T mult(T num1, T num2)
{
    return num1 * num2;
}

template<typename T>
bool more_then(T num1, T num2)
{
    return num1 > num2;
}

template<typename T>
bool less_then(T num1, T num2)
{
    return num1 < num2;
}

template <typename T>
void where(BinaryTree<T>* tree, bool(*f)(T, T), T num, BinaryTree<T>* newtree)
{
    if (&tree->GetData() != nullptr)
    {
        if (f(tree->GetData(), num))
        {
            newtree->Insert(tree->GetData());
        }
    }
    if (tree->GetLeftRoot() != NULL)
    {
        where(tree->GetLeftSubTree(), f, num, newtree);
    }
    if (tree->GetRightRoot() != NULL)
    {
        where(tree->GetRightSubTree(), f, num, newtree);
    }
}

template<typename T>
void map(BinaryTree<T>* tree, T(*f)(T, T), T num, BinaryTree<T>* newtree)
{
    if (&tree->GetData() != NULL)
    {
        newtree->Insert(f(tree->GetData(), num));
    }
    if (tree->GetLeftRoot() != nullptr)
    {
        map(tree->GetLeftSubTree(), f, num, newtree);
    }
    if (tree->GetRightRoot() != nullptr)
    {
        map(tree->GetRightSubTree(), f, num, newtree);
    }
    /*while (1)
    {
        int choice1 = 0;
        cout << "???????????????? ?????? ????????????????????????????: \n1. ???????????????? ?? ????????????.\n2. ?????????????????? ???? ??????????.\n";
        cin >> choice1;
        if (choice1 == 1)
        {

            break;
        }
        else if (choice1 == 2)
        {

            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }*/
}




template<typename T>
BinaryTree<T>* _GenBalancedTree(T* barr, int start, int end)
{
    if (end < start)
    {
        return NULL;
    }
    //int mid = (int)floor((start + end) / 2);
    int mid = (start + end) / 2;
    BinaryTree<T>* Tree = new BinaryTree<T>(&barr[mid], 1);
    Tree->Insert(_GenBalancedTree(barr, start, mid - 1));
    Tree->Insert(_GenBalancedTree(barr, mid + 1, end));
    return Tree;
}

template<typename T>
T _GetBalancedArr(T* bmass, T* newmass, int start, int end)
{
    if (end < start)
    {
        return NULL;
    }
    int mid = (start + end) / 2;
    newmass[start] = _GetBalancedArr(bmass, newmass, start, mid - 1);
    newmass[mid + 1] = _GetBalancedArr(bmass, newmass, mid + 1, end);
    return bmass[mid];
}

template<typename T>
T* GetBalancedArr(T* bmass, int len)
{
    T* newmass = new T[len];
    _GetBalancedArr(bmass, newmass, 0, len - 1);
    return newmass;
}

template <typename T>
BinaryTree<T>* GenBalancedTree(T* bmass, int len)
{
    return _GenBalancedTree<T>(bmass, 0, len - 1);
}

template <typename T>
BinaryTree<T>* MergeTrees(BinaryTree<T>* tree1, BinaryTree<T>* tree2)
{
    int size1 = tree1->GetSize(), size2 = tree2->GetSize();
    T* mass1 = new T[size1];
    tree1->GetMass(mass1);
    T* mass2 = new T[size2];
    tree2->GetMass(mass2);
    int size = size1 + size2;
    T* mass = new T[size];
    for (int i = 0; i < size1; i++)
    {
        mass[i] = mass1[i];
    }
    for (int i = 0; i < size2; i++)
    {
        mass[size1 + i] = mass2[i];
    }
    sort_arr<T>(mass, size);
    /*for (int j = 0; j < size; j++)
    {
        cout << mass[j] << endl;
    }
    cout << endl;
    T* normmass = new T[size];*/
    /*for (int j = 0, j1 = 0, j2 = 1; j < i; j++)
    {
        if (j % 2 == 0)
        {
            normmass[j] = mass[i / 2 + j1];
            j1++;
        }
        else
        {
            normmass[j] = mass[i / 2 - j2];
            j2++;
        }
    }*/
    /*BalanceMass<T>(mass, size);
    for (int j = 0; j < size; j++)
    {
        cout << mass[j] << endl;
    }
    BinaryTree<T>* newtree = new BinaryTree<T>(mass, size1);
    return newtree;*/
    return GenBalancedTree(mass, size);
}

template<typename T>
void pretreetostring(BinaryTree<T>* tree)
{
    int choice = 0;
    while (1)
    {
        choice = 0;
        cout << "???????????????? ??????????: \n1. ??????.\n2. ??????.\n3. ??????.\n4. ??????.\n5. ??????.\n6. ??????.\n";
        cin >> choice;
        if (choice == 1)
        {
            cout << tree->ToString("RootLeftRight");
            break;
        }
        else if (choice == 2)
        {
            cout << tree->ToString("RootRightLeft");
            break;
        }
        else if (choice == 3)
        {
            cout << tree->ToString("RightLeftRoot");
            break;
        }
        else if (choice == 4)
        {
            cout << tree->ToString("RightRootLeft");
            break;
        }
        else if (choice == 5)
        {
            cout << tree->ToString("LeftRightRoot");
            break;
        }
        else if (choice == 6)
        {
            cout << tree->ToString("LeftRootRight");
            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
}
//8. ?????????? ???????? ???? ????????.\n9. ?????????????? ??????????????.\n10. ?????????????? ??????????????.\n11. ???????????????????????? ????????????.
template <typename T>
BinaryTree<T>* pregetnode(BinaryTree<T>* tree)
{
    string s1 = string();
    T* temp = new T();
    int num = -1;
    while (1)
    {
        cout << "???????????????? ???????????? ?????????????? ????????: \n1. ??????????????????.\n2. ????????????.\n";
        int choice = -1;
        cin >> choice;
        cout << "?????????????? ???????????? ????????(>=0): ";
        cin >> num;
        if (num < 0)
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
            continue;
        }
        if (choice == 1)
        {
            s1.resize(num);
            for (int i = 0; i < num; i++)
            {
                if (rand() % 2 == 1) s1[i] = 'l';
                if (rand() % 2 == 0) s1[i] = 'r';
            }
            break;
        }
        else if (choice == 2)
        {
            cout << "?????????????? ???????? ???? ????????(r - ?? ??????????, l - ?? ????????): ";
            cin >> s1;
            bool is_correct = true;
            for (int i = 0; i < num; i++)
            {
                if (s1[i] != 'r' && s1[i] != 'l')
                {
                    is_correct = false;
                }
            }
            if (!is_correct)
            {
                cout << "???????????????? ????????\n";
                cin.clear();
                while (cin.get() != '\n');
                continue;
            }
            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
    BinaryTree<T>* newtree = tree->GetSubTreeFromPath(s1);
    cout << "???????????????????? ????????(??????????????????):\n";
    newtree->Print();
    while (1)
    {
        cout << "???????????????? ???????? ?????????????? ?????????????????(y/n): ";
        string answ = "";
        cin >> answ;
        if (answ == "y")
        {
            delete tree;
            tree = nullptr;
            return newtree;
            break;
        }
        else if (answ == "n")
        {
            delete newtree;
            newtree = nullptr;
            return tree;
            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
}

template <typename T>
void precheckelem(BinaryTree<T>* tree)
{
    string s1 = tree->ToString();
    string s2 = string();
    T* temp = new T();
    while (1)
    {
        int choice;
        cout << "?????????????? ???????????? ??????????????: \n1. ??????????????????.\n2. ????????????.\n";
        cin >> choice;
        if (choice == 1)
        {
            temp = (T*)TemplateRand<T>();
            break;
        }
        else if (choice == 2)
        {
            cout << "?????????????? ?????????? ???????? " << typeid(T).name() << ": ";
            cin >> *temp;
            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
    cout << "??????????????: " << *temp << endl;
    s2 = to_string(*temp);
    if (s1.find(s2))
    {
        cout << "???????????? ?????????????? ???????????? ?? ????????????.\n";
    }
    else
    {
        cout << "???????????? ?????????????? ???? ???????????? ?? ????????????.\n";
    }
}

template <typename T>
void prechecksubtree(BinaryTree<T>* tree)
{
    T* temp = new T();
    int num = 0;
    T* mass;
    //int len = tree->GetSize();
    while (1)
    {
        cout << "???????????????? ???????????? ??????????????: \n1. ??????????????????.\n2. ????????????.\n";
        int choice = 0;
        num = 0;
        cin >> choice;
        cout << "?????????????? ???????????????????? ?????????????????? ??????????????????(>0): ";
        cin >> num;
        if (num <= 0)
        {
            cout << "???????????????? ????????.\n";
            cin.clear();
            while (cin.get() != '\n');
            continue;
        }
        mass = new T[num];
        if (choice == 1)
        {

            for (int i = 0; i < num; i++)
            {
                mass[i] = *(T*)TemplateRand<T>();
            }
            break;
        }
        else if (choice == 2)
        {
            cout << "?????????????? " << num << " ?????????????????? ???????? " << typeid(T).name() << ": ";

            for (int i = 0; i < num; i++)
            {
                cin >> *temp;
                mass[i] = *temp;
            }
            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
    BinaryTree<T>* newtree = new BinaryTree<T>(mass, num);
    cout << "?????????????????? ??????????????????: \n";
    newtree->Print();
    if (tree->CheckSubTree(newtree))
    {
        cout << "???????????? ?????????????????? ???????????????????? ?? ????????????.\n";
    }
    else
    {
        cout << "???????????? ?????????????????? ???? ???????????????????? ?? ????????????.\n";
    }
}

template <typename T>
BinaryTree<T>* prewhere(BinaryTree<T>* tree, bool(*f)(T, T), T num, BinaryTree<T>* newtree, int mode)
{
    if (mode == 1)
    {
        cout << "?????????????????? ????????????: " << num << endl;
    }
    where(tree, f, num, newtree);
    cout << "?????????? ???????????? :" << endl;
    newtree->Print();
    while (1)
    {
        cout << "???????????????? ???????? ?????????????? ?????????????????(y/n): ";
        string answ = "";
        cin >> answ;
        if (answ == "y")
        {
            delete tree;
            tree = nullptr;
            return newtree;
            break;
        }
        else if (answ == "n")
        {
            delete newtree;
            newtree = nullptr;
            return tree;
            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
}

template <typename T>
BinaryTree<T>* premap(BinaryTree<T>* tree, T(*f)(T, T), T num, BinaryTree<T>* newtree, int mode)
{
    if (mode == 1)
    {
        cout << "?????????????????? ????????????: " << num << endl;
    }
    map(tree, f, num, newtree);
    cout << "?????????? ???????????? :" << endl;
    newtree->Print();
    while (1)
    {
        cout << "???????????????? ???????? ?????????????? ?????????????????(y/n): ";
        string answ = "";
        cin >> answ;
        if (answ == "y")
        {
            delete tree;
            return newtree;
            break;
        }
        else if (answ == "n")
        {
            delete newtree;
            return tree;
            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
}

template <typename T>
BinaryTree<T>* pregetsubtree(BinaryTree<T>* tree)
{
    T* temp = new T();
    int len = tree->GetSize();
    while (1)
    {
        cout << "???????????????? ???????????? ??????????????: \n1. ??????????????????.\n2. ????????????.\n";
        int choice = 0;
        cin >> choice;
        if (choice == 1)
        {
            T* mass = new T[len];
            tree->GetMass(mass);
            *temp = mass[rand(0, len - 1)];
            cout << "?????????????????? ??????????????: " << *temp << endl;
            break;
        }
        else if (choice == 2)
        {
            cout << "?????????????? ??????????????: ";
            cin >> *temp;
            T* mass = new T[len];
            tree->GetMass(mass);
            bool is_in_tree = false;
            for (int i = 0; i < len; i++)
            {
                if (mass[i] == *temp) is_in_tree = true;
            }
            if (!is_in_tree)
            {
                cout << "?? ???????????? ???? ?????????? ?????????? ??????????????.\n";
                continue;
            }
            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
    BinaryTree<T>* newtree = tree->GetSubTree(*temp);
    cout << "?????????????????? ??????????????????: \n";
    newtree->Print();
    while (1)
    {
        cout << "???????????????? ???????? ?????????????? ?????????????????(y/n): ";
        string answ = "";
        cin >> answ;
        if (answ == "y")
        {
            delete tree;
            tree = nullptr;
            return newtree;
            break;
        }
        else if (answ == "n")
        {
            delete newtree;
            newtree = nullptr;
            return tree;
            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
}

template <typename T>
void predelteelem(BinaryTree<T>* tree)
{
    T* temp = new T();
    int num = -1;
    while (1)
    {
        cout << "???????????????? ???????????? ??????????????: \n1. ??????????????????.\n2. ????????????.\n";
        int choice = -1;
        cin >> choice;
        if (choice == 1)
        {
            *temp = *(T*)TemplateRand<T>();
            break;
        }
        else if (choice == 2)
        {
            cout << "?????????????? ???????????? ???????????? " << typeid(T).name() << ": ";
            cin >> *temp;
            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
    cout << "????????????: " << *temp << endl;
    int len = tree->GetSize();
    T* mass = new T[len];
    tree->GetMass(mass);
    bool is_found = false;
    for (int i = 0; i < len; i++)
    {
        if (*temp == mass[i])
        {
            is_found = true;
        }
    }
    if (!is_found)
    {
        cout << "???????? ???????????? ???? ???????????? ?? ????????????.\n";
    }
    else
    {
        tree = tree->DeleteElem(*temp);
    }
}

template <typename T>
BinaryTree<T>* prebalance(BinaryTree<T>* tree)
{
    int len = tree->GetSize();
    T* mass = new T[len];
    tree->GetMass(mass);
    sort_arr<T>(mass, len);
    BinaryTree<T>* newtree = GenBalancedTree(mass, len);
    cout << "???????????????????????? ????????????:\n";
    newtree->Print();
    while (1)
    {
        cout << "???????????????? ???????? ?????????????? ?????????????????(y/n): ";
        string answ = "";
        cin >> answ;
        if (answ == "y")
        {
            delete tree;
            return newtree;
            break;
        }
        else if (answ == "n")
        {
            delete newtree;
            return tree;
            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
}

template <typename T>
void preinsert(BinaryTree<T>* tree)
{
    T* temp = new T();
    int num = -1;
    while (1)
    {
        cout << "???????????????? ???????????? ??????????????: \n1. ??????????????????.\n2. ????????????.\n";
        int choice = -1;
        cin >> choice;
        if (choice == 1)
        {
            *temp = *(T*)TemplateRand<T>();
            break;
        }
        else if (choice == 2)
        {
            cout << "?????????????? ???????????? ???????????? " << typeid(T).name() << ": ";
            cin >> *temp;
            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
    cout << "????????????: " << *temp << endl;
    tree->Insert(*temp);
    cout << "???????????????????????? ????????????:\n";
    tree->Print();
}

template <typename T>
BinaryTree<T>* premerge(BinaryTree<T>* tree1)
{
    BinaryTree<T>* tree2 = new BinaryTree<T>();

    while (1)
    {
        cout << "???????????????? ???????????? ?????????? ????????????: \n1. ????????????????.\n2. ????????????.\n";
        int choice1 = 0, num = 0;
        cin >> choice1;
        while (1)
        {

            cout << "?????????????? ???????????????????? ?????????????????? ????????????: ";
            cin >> num;
            if (num <= 0)
            {
                cout << "???????????????? ????????." << endl;
            }
            else
            {
                break;
            }
        }
        if (choice1 == 1)
        {
            T* temp = new T();
            for (int i = 0; i < num; i++)
            {
                temp = (T*)TemplateRand<T>();
                tree2->Insert(*temp);
            }
            cout << "???????????? ?????? ??????????????: \n";
            tree2->Print();
            break;
        }
        else if (choice1 == 2)
        {

            cout << "?????????????? " << num << " ???????????????? ???????? " << typeid(T).name();
            T temp = T();
            for (int i = 0; i < num; i++)
            {
                cin >> temp;
                tree2->Insert(temp);
            }
            cout << "???????????? ?????? ??????????????: \n";
            tree2->Print();
            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
    BinaryTree<T>* newtree = MergeTrees(tree1, tree2);
    cout << "???????????????????????? ????????????:\n";
    newtree->Print();
    while (1)
    {
        cout << "???????????????? ???????? ?????????????? ?????????????????(y/n): ";
        string answ = "";
        cin >> answ;
        if (answ == "y")
        {
            delete tree1;
            return newtree;
            break;
        }
        else if (answ == "n")
        {
            delete newtree;
            return tree1;
            break;
        }
        else
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
}

void Interface()
{
    int choice1 = 0, choice2 = 0, choice3 = 0;
    string typeofdata = "";
    void* Tree = nullptr;
    while (choice1 != 5) {
    start:
        choice1 = choice2 = choice3 = 0;
        cout << "???????????????? ????????????????: \n1. ???????????????? ????????????.\n2. ???????????????? ?????? ??????????????.\n3. ???????????????? ????????????.\n4. ?????????????????????? ????????????.\n5. ?????????? ??????????????????.\n";
        cin >> choice1;
        if (choice1 == 1)
        {
            if (Tree != nullptr)
            {
                while (1)
                {
                    cout << "?????? ???????????????? ???????????? ???????????? ?????????? ???????????? ????????????, ?????????????????????(y/n): ";
                    string answ = "";
                    cin >> answ;
                    if (answ == "y")
                    {
                        delete Tree;
                        Tree = nullptr;
                        break;
                    }
                    else if (answ == "n")
                    {
                        goto start;
                    }
                    else
                    {
                        cout << "???????????????? ????????\n";
                        cin.clear();
                        while (cin.get() != '\n');
                    }
                }
            }
            cout << "???????????????? ?????? ???????????? ?????? ?????????????????? ????????????: \n1. ?????????? ??????????.\n2. ???????????????????????? ??????????.\n3. ?????????????????????? ??????????.\n4. ????????????.\n5. ??????????????.\n6. ????????????????.\n7. ??????????????????????????.\n";
            cin >> choice2;
            if (choice2 == 1)
            {
                Tree = new BinaryTree<int>();
                typeofdata = typeid(int).name();
                int num = 0, temp = 0;
                cout << "???????????????? ?????? ??????????: \n1. ????????????.\n2. ??????????????????.\n";
                cin >> choice3;
                while (1)
                {
                    cout << "?????????????? ???????????????????? ??????????????????(>0): ";
                    cin >> num;
                    if (num <= 0)
                    {
                        cout << "???????????????? ????????.\n";
                        cin.clear();
                        while (cin.get() != '\n');
                    }
                    else break;
                }
                if (choice3 == 1)
                {
                    cout << "?????????????? " << num << " ?????????????????? ???????? " + typeofdata << endl;
                    for (int i = 0; i < num; i++)
                    {
                        cin >> temp;
                        ((BinaryTree<int>*)Tree)->Insert(temp);
                    }
                }
                if (choice3 == 2)
                {
                    for (int i = 0; i < num; i++)
                    {
                        temp = rand(-1000, 1000);
                        ((BinaryTree<int>*)Tree)->Insert(temp);
                    }

                }
            }
            else if (choice2 == 2)
            {
                Tree = new BinaryTree<double>();
                typeofdata = typeid(double).name();
                int num = 0;
                double temp = 0;
                cout << "???????????????? ?????? ??????????: \n1. ????????????.\n2. ??????????????????.\n";
                cin >> choice3;
                while (1)
                {
                    cout << "?????????????? ???????????????????? ??????????????????(>0): ";
                    cin >> num;
                    if (num <= 0)
                    {
                        cout << "???????????????? ????????.\n";
                        cin.clear();
                        while (cin.get() != '\n');
                    }
                    else break;
                }
                if (choice3 == 1)
                {
                    cout << "?????????????? " << num << " ?????????????????? ???????? " + typeofdata << endl;
                    for (int i = 0; i < num; i++)
                    {
                        cin >> temp;
                        ((BinaryTree<double>*)Tree)->Insert(temp);
                    }
                }
                if (choice3 == 2)
                {
                    for (int i = 0; i < num; i++)
                    {
                        temp = doublerand(-1000, 1000);
                        ((BinaryTree<double>*)Tree)->Insert(temp);
                    }
                }
            }
            else if (choice2 == 3)
            {
                Tree = new BinaryTree<complex>();
                typeofdata = typeid(complex).name();
                int num = 0;
                complex temp = complex();
                cout << "???????????????? ?????? ??????????: \n1. ????????????.\n2. ??????????????????.\n";
                cin >> choice3;
                while (1)
                {
                    cout << "?????????????? ???????????????????? ??????????????????(>0): ";
                    cin >> num;
                    if (num <= 0)
                    {
                        cout << "???????????????? ????????.\n";
                        cin.clear();
                        while (cin.get() != '\n');
                    }
                    else break;
                }
                if (choice3 == 1)
                {
                    cout << "?????????????? " << num << " ?????????????????? ???????? " + typeofdata << endl;
                    for (int i = 0; i < num; i++)
                    {
                        cin >> temp;
                        ((BinaryTree<complex>*)Tree)->Insert(temp);
                    }
                }
                if (choice3 == 2)
                {
                    for (int i = 0; i < num; i++)
                    {
                        temp.GetRe() = doublerand(-1000, 1000);
                        temp.GetIm() = doublerand(-1000, 1000);
                        ((BinaryTree<complex>*)Tree)->Insert(temp);
                    }
                }
            }
            else if (choice2 == 4)
            {
                Tree = new BinaryTree<string>();
                typeofdata = typeid(string).name();
                int num = 0;
                string temp = string();
                cout << "???????????????? ?????? ??????????: \n1. ????????????.\n2. ??????????????????.\n";
                cin >> choice3;
                while (1)
                {
                    cout << "?????????????? ???????????????????? ??????????????????(>0): ";
                    cin >> num;
                    if (num <= 0)
                    {
                        cout << "???????????????? ????????.\n";
                        cin.clear();
                        while (cin.get() != '\n');
                    }
                    else break;
                }
                if (choice3 == 1)
                {
                    cout << "?????????????? " << num << " ?????????????????? ???????? " + typeofdata << endl;
                    for (int i = 0; i < num; i++)
                    {
                        cin >> temp;
                        ((BinaryTree<string>*)Tree)->Insert(temp);
                    }
                }
                if (choice3 == 2)
                {
                    //int len = rand(1, 20);
                    for (int i = 0; i < num; i++)
                    {
                        temp = GenRandomString(rand(5, 20));
                        ((BinaryTree<string>*)Tree)->Insert(temp);
                    }
                }
            }
            /*else if (choice2 == 5)

            {
            cout << "???????????????? ?????? ??????????????: \n1. int.\n2. double.\n3. complex.\n";
            while (1)
            {
                cin >> choice3;
                if (choice3 == 1)
                {
                    typeofdata = "function<int>";
                    Tree = new BinaryTree<FuncPtr1<int>>();
                    break;
                }
                else if (choice3 == 2)
                {
                    typeofdata = "function<double>";
                    Tree = new BinaryTree<FuncPtr1<double>>();
                    break;
                }
                else if (choice3 == 3)
                {
                    typeofdata = "function<complex>";
                    Tree = new BinaryTree<FuncPtr1<complex>>();
                    break;
                }
                else
                {
                    cout << "???????????????? ????????\n";
                    cin.clear();
                    while (cin.get() != '\n');
                }
            }
            int num = 0;
            string temp = string();
            cout << "???????????????? ?????? ??????????: \n1. ????????????.\n2. ??????????????????.\n";
            cin >> choice3;
            while (1)
            {
                cout << "?????????????? ???????????????????? ??????????????????(>0): ";
                cin >> num;
                if (num <= 0)
                {
                    cout << "???????????????? ????????\n";
                    cin.clear();
                    while (cin.get() != '\n');
                }
                else break;
            }
            if (choice3 == 1)
            {
                cout << "?????????????? " << num << " ?????????????????? ???????? " + typeofdata << endl;
                for (int i = 0; i < num; i++)
                {
                    cin >> temp;
                    ((BinaryTree<string>*)Tree)->Insert(temp);
                }
            }
            if (choice3 == 2)
            {
                int len = rand(1, randmax);
                temp = GenRandomString(len);
                for (int i = 0; i < num; i++)
                {
                    ((BinaryTree<string>*)Tree)->Insert(temp);
                }
            }
            }*/
            else if (choice2 == 5)
            {
                Tree = new BinaryTree<Func>();
                typeofdata = typeid(Func).name();
                int num = 0;
                Func temp = Func();
                cout << "???????????????? ?????? ??????????: \n1. ????????????.\n2. ??????????????????.\n";
                cin >> choice3;
                while (1)
                {
                    cout << "?????????????? ???????????????????? ??????????????????(>0): ";
                    cin >> num;
                    if (num <= 0)
                    {
                        cout << "???????????????? ????????.\n";
                        cin.clear();
                        while (cin.get() != '\n');
                    }
                    else
                    {
                        break;
                    }
                }
                if (choice3 == 1)
                {
                    cout << "?????????????? " << num << " ?????????????????? ???????? " + typeofdata << endl;
                    for (int i = 0; i < num; i++)
                    {
                        cin >> temp;
                        ((BinaryTree<Func>*)Tree)->Insert(temp);
                    }
                }
                if (choice3 == 2)
                {
                    for (int i = 0; i < num; i++)
                    {
                        temp = *(Func*)TemplateRand<Func>();
                        ((BinaryTree<Func>*)Tree)->Insert(temp);
                    }
                }
            }
            else if (choice2 == 6)
            {
                Tree = new BinaryTree<Student>();
                typeofdata = typeid(Student).name();
                int num = 0;
                Student temp = Student();
                cout << "???????????????? ?????? ??????????: \n1. ????????????.\n2. ??????????????????.\n";
                cin >> choice3;
                while (1)
                {
                    cout << "?????????????? ???????????????????? ??????????????????(>0): ";
                    cin >> num;
                    if (num <= 0)
                    {
                        cout << "???????????????? ????????.\n";
                        cin.clear();
                        while (cin.get() != '\n');
                    }
                    else break;
                }
                string temp1 = string();
                if (choice3 == 1)
                {

                    cout << "?????????????? " << num << " ?????????????????? ???????? " + typeofdata << endl;
                    for (int i = 0; i < num; i++)
                    {

                        cout << "??????: ";
                        cin >> temp1;
                        temp.SetFirstName(temp1);
                        cout << "??????????????: ";
                        cin >> temp1;
                        temp.SetMiddleName(temp1);
                        cout << "????????????????: ";
                        cin >> temp1;
                        temp.SetLastName(temp1);
                        cout << "??????????????????????: ";
                        cin >> temp1;
                        temp.SetStudyCourse(temp1);
                        time_t temp_t = 0;
                        cout << "?????????????? ?????????? ???????????????? ?? ???????????????? ?? 1970??. : ";
                        cin >> temp1;
                        temp_t = atoi(temp1.c_str());
                        /*cout << "?????????????? ?????? ????????????????: ";
                        cin >> temp1;
                        time_t temp_t = 0;
                        temp_t += atoi(temp1.c_str() - 1970) * 60 * 60 * 24 * 365;
                        cout << "?????????????? ?????????? ????????????????(????????????): ";
                        cin >> temp1;
                        temp_t += atoi(temp1.c_str()) * 60 * 60 * 30;
                        cout << "?????????????? ???????? ????????????????: ";
                        cin >> temp1;
                        temp_t += atoi(temp1.c_str()) * 60 * 60 * 24;*/
                        temp.SetBirthDate(temp_t);
                        cout << "?????????????? ???????????????? ???????????????? ??????????????????: ";
                        cin >> temp1;
                        temp.SetInstitution(temp1);
                        cout << "?????????????? ?????????? ????????????: ";
                        cin >> temp1;
                        temp.SetGroup(temp1);
                        cout << "?????????????? ?????? ????????????????: ";
                        cin >> temp1;
                        temp.SetYear(atoi(temp1.c_str()));
                        temp1 = string();
                        ((BinaryTree<Student>*)Tree)->Insert(temp);
                    }
                }
                if (choice3 == 2)
                {
                    for (int i = 0; i < num; i++)
                    {

                        temp1 = GenRandomString(rand(1, 15));
                        temp.SetFirstName(temp1);
                        temp1 = GenRandomString(rand(1, 15));
                        temp.SetMiddleName(temp1);
                        temp1 = GenRandomString(rand(1, 15));
                        temp.SetLastName(temp1);
                        temp1 = GenRandomString(rand(1, 15));
                        temp.SetStudyCourse(temp1);
                        temp1 = GenRandomString(rand(1, 15));
                        temp.SetBirthDate(static_cast<time_t>(946080000) + rand(100000000, 157680000));
                        temp.SetInstitution(temp1);
                        temp.SetGroup(GenRandomString(1) + "-" + to_string(rand(100, 999)));
                        temp.SetYear(rand(1, 5));
                        temp1 = string();
                        ((BinaryTree<Student>*)Tree)->Insert(temp);
                        temp = Student();
                    }
                }
            }
            else if (choice2 == 7)
            {
                Tree = new BinaryTree<Teacher>();
                typeofdata = typeid(Teacher).name();
                int num = 0;
                Teacher temp = Teacher();
                cout << "???????????????? ?????? ??????????: \n1. ????????????.\n2. ??????????????????.\n";
                cin >> choice3;
                while (1)
                {
                    cout << "?????????????? ???????????????????? ??????????????????(>0): ";
                    cin >> num;
                    if (num <= 0)
                    {
                        cout << "???????????????? ????????.\n";
                        cin.clear();
                        while (cin.get() != '\n');
                    }
                    else break;
                }
                string temp1 = string();
                if (choice3 == 1)
                {

                    cout << "?????????????? " << num << " ?????????????????? ???????? " + typeofdata << endl;
                    for (int i = 0; i < num; i++)
                    {

                        cout << "??????: ";
                        cin >> temp1;
                        temp.SetFirstName(temp1);
                        cout << "??????????????: ";
                        cin >> temp1;
                        temp.SetMiddleName(temp1);
                        cout << "????????????????: ";
                        cin >> temp1;
                        temp.SetLastName(temp1);
                        cout << "??????????????: ";
                        cin >> temp1;
                        temp.SetSubject(temp1);
                        time_t temp_t = 0;
                        cout << "?????????????? ?????????? ???????????????? ?? ???????????????? ?? 1970??. : ";
                        cin >> temp1;
                        temp_t = atoi(temp1.c_str());
                        /*cout << "?????????????? ?????? ????????????????: ";
                        cin >> temp1;
                        time_t temp_t = 0;
                        temp_t += atoi(temp1.c_str() - 1970) * 60 * 60 * 24 * 365;
                        cout << "?????????????? ?????????? ????????????????(????????????): ";
                        cin >> temp1;
                        temp_t += atoi(temp1.c_str()) * 60 * 60 * 30;
                        cout << "?????????????? ???????? ????????????????: ";
                        cin >> temp1;
                        temp_t += atoi(temp1.c_str()) * 60 * 60 * 24;*/
                        temp.SetBirthDate(temp_t);
                        temp1 = string();
                        ((BinaryTree<Teacher>*)Tree)->Insert(temp);
                    }
                }
                if (choice3 == 2)
                {
                    for (int i = 0; i < num; i++)
                    {

                        temp1 = GenRandomString(rand(1, 15));
                        temp.SetFirstName(temp1);
                        temp1 = GenRandomString(rand(1, 15));
                        temp.SetMiddleName(temp1);
                        temp1 = GenRandomString(rand(1, 15));
                        temp.SetLastName(temp1);
                        temp1 = GenRandomString(rand(1, 15));
                        temp.SetSubject(temp1);
                        temp1 = GenRandomString(rand(1, 15));
                        temp.SetBirthDate(time(NULL) - rand());
                        temp1 = string();
                        ((BinaryTree<Teacher>*)Tree)->Insert(temp);
                        temp = Teacher();
                    }
                }
            }
            else
            {
                cout << "???????????????? ????????.\n";
                cin.clear();
                while (cin.get() != '\n');
            }
        }
        else if (choice1 == 2)
        {
            if (Tree == nullptr)
            {
                cout << "???????????????? ???????????? ???? ????????????????????.\n";
            }
            else
            {
                cout << "???????????????? ????????????????: \n1. ?????????????????? ?????????? ???????????? ???????????????????????? ??????????????????????????????.\n2. ?????????????????? ?????????? ????????????, ?? ?????????????? ???????????? ???????? ???? ???????? ??????????????????, ?????????????? ?????????????????????????? ?????????????????? ??????????????.\n3. ?????????????? ????????????????.\n4. ???????????????????? ??????????????????(???? ?????????????????? ????????????????).\n5. ?????????? ???? ?????????????????? ??????????????????.\n6. ?????????? ???????????????? ???? ??????????????????.\n7. ???????????????????? ?? ???????????? ?? ???????????????????????? ?? ??????????????.\n8. ?????????? ???????? ???? ????????.\n9. ?????????????? ??????????????.\n10. ?????????????? ??????????????.\n11. ???????????????????????? ????????????.\n";
                cin >> choice2;
                if (choice2 == 1)
                {
                    while (1)
                    {
                        cout << "???????????????? ?????? ????????????????????????????: \n1. ???????????????? ?? ????????????.\n2. ?????????????????? ???? ??????????.\n";
                        cin >> choice3;
                        if (choice3 == 1)
                        {
                            while (1)
                            {
                                cout << "???????????????? ?????? ??????????: \n1. ??????????????????.\n2. ????????????.\n";
                                int choice4 = 0;
                                cin >> choice4;
                                if (choice4 == 1)
                                {
                                    if (typeofdata == typeid(int).name())
                                    {
                                        BinaryTree<int>* newtree = new BinaryTree<int>();
                                        Tree = premap((BinaryTree<int>*)Tree, sum, *(int*)TemplateRand<int>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(double).name())
                                    {
                                        BinaryTree<double>* newtree = new BinaryTree<double>();
                                        Tree = premap((BinaryTree<double>*)Tree, sum, *(double*)TemplateRand<double>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(complex).name())
                                    {
                                        BinaryTree<complex>* newtree = new BinaryTree<complex>();
                                        Tree = premap((BinaryTree<complex>*)Tree, sum, *(complex*)TemplateRand<complex>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(string).name())
                                    {
                                        BinaryTree<string>* newtree = new BinaryTree<string>();
                                        Tree = premap((BinaryTree<string>*)Tree, sum, *(string*)TemplateRand<string>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(Student).name())
                                    {
                                        BinaryTree<Student>* newtree = new BinaryTree<Student>();
                                        Tree = premap((BinaryTree<Student>*)Tree, sum, *(Student*)TemplateRand<Student>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(Func).name())
                                    {
                                        BinaryTree<Func>* newtree = new BinaryTree<Func>();
                                        Tree = premap((BinaryTree<Func>*)Tree, sum, *(Func*)TemplateRand<Func>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(Teacher).name())
                                    {
                                        BinaryTree<Teacher>* newtree = new BinaryTree<Teacher>();
                                        Tree = premap((BinaryTree<Teacher>*)Tree, sum, *(Teacher*)TemplateRand<Teacher>(), newtree, 1);
                                    }
                                    break;
                                }
                                else if (choice4 == 2)
                                {
                                    cout << "?????????????? ???????????? ???????? " << typeofdata << " ?????? ???????????????? : ";
                                    if (typeofdata == typeid(int).name())
                                    {
                                        BinaryTree<int>* newtree = new BinaryTree<int>();
                                        int temp = int();
                                        cin >> temp;
                                        Tree = premap((BinaryTree<int>*)Tree, sum, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(double).name())
                                    {
                                        BinaryTree<double>* newtree = new BinaryTree<double>();
                                        double temp = double();
                                        cin >> temp;
                                        Tree = premap((BinaryTree<double>*)Tree, sum, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(complex).name())
                                    {
                                        BinaryTree<complex>* newtree = new BinaryTree<complex>();
                                        complex temp = complex();
                                        cin >> temp;
                                        Tree = premap((BinaryTree<complex>*)Tree, sum, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(Func).name())
                                    {
                                        BinaryTree<Func>* newtree = new BinaryTree<Func>();
                                        Func temp = Func();
                                        cin >> temp;
                                        Tree = premap((BinaryTree<Func>*)Tree, sum, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(string).name())
                                    {
                                        BinaryTree<string>* newtree = new BinaryTree<string>();
                                        string temp = string();
                                        cin >> temp;
                                        Tree = premap((BinaryTree<string>*)Tree, sum, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(Student).name())
                                    {
                                        BinaryTree<Student>* newtree = new BinaryTree<Student>();
                                        Student temp = Student();
                                        cin >> temp;
                                        Tree = premap((BinaryTree<Student>*)Tree, sum, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(Teacher).name())
                                    {
                                        BinaryTree<Teacher>* newtree = new BinaryTree<Teacher>();
                                        Teacher temp = Teacher();
                                        cin >> temp;
                                        Tree = premap((BinaryTree<Teacher>*)Tree, sum, temp, newtree, 2);
                                    }
                                    break;
                                }
                                else
                                {
                                    cout << "???????????????? ????????.\n";
                                    cin.clear();
                                    while (cin.get() != '\n');
                                }
                            }
                            break;
                        }
                        else if (choice3 == 2)
                        {
                            while (1)
                            {
                                cout << "???????????????? ?????? ??????????: \n1. ??????????????????.\n2. ????????????.\n";
                                int choice4 = 0;
                                cin >> choice4;
                                if (choice4 == 1)
                                {
                                    if (typeofdata == typeid(int).name())
                                    {
                                        BinaryTree<int>* newtree = new BinaryTree<int>();
                                        Tree = premap((BinaryTree<int>*)Tree, mult, *(int*)TemplateRand<int>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(double).name())
                                    {
                                        BinaryTree<double>* newtree = new BinaryTree<double>();
                                        Tree = premap((BinaryTree<double>*)Tree, mult, *(double*)TemplateRand<double>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(complex).name())
                                    {
                                        BinaryTree<complex>* newtree = new BinaryTree<complex>();
                                        Tree = premap((BinaryTree<complex>*)Tree, mult, *(complex*)TemplateRand<complex>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(Func).name())
                                    {
                                        BinaryTree<Func>* newtree = new BinaryTree<Func>();
                                        Tree = premap((BinaryTree<Func>*)Tree, mult, *(Func*)TemplateRand<complex>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(string).name())
                                    {
                                        cout << "?????????????????? ???? ???????????????????? ?????? ??????????\n";
                                        /*BinaryTree<string>* newtree = new BinaryTree<string>();
                                        premap((BinaryTree<string>*)Tree, mult, *(string*)TemplateRand<string>(), newtree, 1);*/
                                    }
                                    if (typeofdata == typeid(Student).name())
                                    {
                                        BinaryTree<Student>* newtree = new BinaryTree<Student>();
                                        Tree = premap((BinaryTree<Student>*)Tree, mult, *(Student*)TemplateRand<Student>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(Teacher).name())
                                    {
                                        BinaryTree<Teacher>* newtree = new BinaryTree<Teacher>();
                                        Tree = premap((BinaryTree<Teacher>*)Tree, mult, *(Teacher*)TemplateRand<Teacher>(), newtree, 1);
                                    }
                                    break;
                                }
                                else if (choice4 == 2)
                                {
                                    cout << "?????????????? ???????????? ???????? " << typeofdata << " ?????? ???????????????? : ";
                                    if (typeofdata == typeid(int).name())
                                    {
                                        BinaryTree<int>* newtree = new BinaryTree<int>();
                                        int temp = int();
                                        cin >> temp;
                                        Tree = premap((BinaryTree<int>*)Tree, mult, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(Func).name())
                                    {
                                        BinaryTree<Func>* newtree = new BinaryTree<Func>();
                                        Func temp = Func();
                                        cin >> temp;
                                        Tree = premap((BinaryTree<Func>*)Tree, mult, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(double).name())
                                    {
                                        BinaryTree<double>* newtree = new BinaryTree<double>();
                                        double temp = double();
                                        cin >> temp;
                                        Tree = premap((BinaryTree<double>*)Tree, mult, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(complex).name())
                                    {
                                        BinaryTree<complex>* newtree = new BinaryTree<complex>();
                                        complex temp = complex();
                                        cin >> temp;
                                        Tree = premap((BinaryTree<complex>*)Tree, mult, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(string).name())
                                    {
                                        cout << "?????????????????? ???? ???????????????????? ?????? ??????????\n";
                                        /*BinaryTree<string>* newtree = new BinaryTree<string>();
                                        string temp = string();
                                        cin >> temp;
                                        premap((BinaryTree<string>*)Tree, mult, temp, newtree, 2);*/
                                    }
                                    if (typeofdata == typeid(Student).name())
                                    {
                                        BinaryTree<Student>* newtree = new BinaryTree<Student>();
                                        Student temp = Student();
                                        cin >> temp;
                                        Tree = premap((BinaryTree<Student>*)Tree, mult, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(Teacher).name())
                                    {
                                        BinaryTree<Teacher>* newtree = new BinaryTree<Teacher>();
                                        Teacher temp = Teacher();
                                        cin >> temp;
                                        Tree = premap((BinaryTree<Teacher>*)Tree, mult, temp, newtree, 2);
                                    }
                                    break;
                                }
                                else
                                {
                                    cout << "???????????????? ????????.\n";
                                    cin.clear();
                                    while (cin.get() != '\n');
                                }
                            }
                            break;
                        }
                        else
                        {
                            cout << "???????????????? ????????.\n";
                            cin.clear();
                            while (cin.get() != '\n');
                        }
                    }
                }
                else if (choice2 == 2)
                {
                    while (1)
                    {
                        cout << "???????????????? ??????????????: \n1. ????????????.\n2. ????????????.\n";
                        cin >> choice3;
                        if (choice3 == 1)
                        {
                            while (1)
                            {
                                cout << "???????????????? ?????? ??????????: \n1. ??????????????????.\n2. ????????????.\n";
                                int choice4 = 0;
                                cin >> choice4;
                                if (choice4 == 1)
                                {
                                    if (typeofdata == typeid(int).name())
                                    {
                                        BinaryTree<int>* newtree = new BinaryTree<int>();
                                        Tree = prewhere((BinaryTree<int>*)Tree, more_then, *(int*)TemplateRand<int>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(double).name())
                                    {
                                        BinaryTree<double>* newtree = new BinaryTree<double>();
                                        Tree = prewhere((BinaryTree<double>*)Tree, more_then, *(double*)TemplateRand<double>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(Func).name())
                                    {
                                        BinaryTree<Func>* newtree = new BinaryTree<Func>();
                                        Tree = prewhere((BinaryTree<Func>*)Tree, more_then, *(Func*)TemplateRand<Func>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(complex).name())
                                    {
                                        BinaryTree<complex>* newtree = new BinaryTree<complex>();
                                        Tree = prewhere((BinaryTree<complex>*)Tree, more_then, *(complex*)TemplateRand<complex>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(string).name())
                                    {
                                        BinaryTree<string>* newtree = new BinaryTree<string>();
                                        Tree = prewhere((BinaryTree<string>*)Tree, more_then, *(string*)TemplateRand<string>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(Student).name())
                                    {
                                        BinaryTree<Student>* newtree = new BinaryTree<Student>();
                                        Tree = prewhere((BinaryTree<Student>*)Tree, more_then, *(Student*)TemplateRand<Student>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(Teacher).name())
                                    {
                                        BinaryTree<Teacher>* newtree = new BinaryTree<Teacher>();
                                        Tree = prewhere((BinaryTree<Teacher>*)Tree, more_then, *(Teacher*)TemplateRand<Teacher>(), newtree, 1);
                                    }
                                    break;
                                }
                                else if (choice4 == 2)
                                {
                                    cout << "?????????????? ???????????? ???????? " << typeofdata << " ?????? ?????????????????? : ";
                                    if (typeofdata == typeid(int).name())
                                    {
                                        BinaryTree<int>* newtree = new BinaryTree<int>();
                                        int temp = int();
                                        cin >> temp;
                                        Tree = prewhere((BinaryTree<int>*)Tree, more_then, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(Func).name())
                                    {
                                        BinaryTree<Func>* newtree = new BinaryTree<Func>();
                                        Func temp = Func();
                                        cin >> temp;
                                        Tree = prewhere((BinaryTree<Func>*)Tree, more_then, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(double).name())
                                    {
                                        BinaryTree<double>* newtree = new BinaryTree<double>();
                                        double temp = double();
                                        cin >> temp;
                                        Tree = prewhere((BinaryTree<double>*)Tree, more_then, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(complex).name())
                                    {
                                        BinaryTree<complex>* newtree = new BinaryTree<complex>();
                                        complex temp = complex();
                                        cin >> temp;
                                        Tree = prewhere((BinaryTree<complex>*)Tree, more_then, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(string).name())
                                    {
                                        BinaryTree<string>* newtree = new BinaryTree<string>();
                                        string temp = string();
                                        cin >> temp;
                                        Tree = prewhere((BinaryTree<string>*)Tree, more_then, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(Student).name())
                                    {
                                        BinaryTree<Student>* newtree = new BinaryTree<Student>();
                                        Student temp = Student();
                                        cin >> temp;
                                        Tree = prewhere((BinaryTree<Student>*)Tree, more_then, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(Teacher).name())
                                    {
                                        BinaryTree<Teacher>* newtree = new BinaryTree<Teacher>();
                                        Teacher temp = Teacher();
                                        cin >> temp;
                                        Tree = prewhere((BinaryTree<Teacher>*)Tree, more_then, temp, newtree, 2);
                                    }
                                    break;
                                }
                                else
                                {
                                    cout << "???????????????? ????????.\n";
                                    cin.clear();
                                    while (cin.get() != '\n');
                                }
                            }
                            break;
                        }
                        else if (choice3 == 2)
                        {
                            while (1)
                            {
                                cout << "?????????????? ?????? ??????????: \n1. ??????????????????.\n2. ????????????.\n";
                                int choice4 = 0;
                                cin >> choice4;
                                if (choice4 == 1)
                                {
                                    if (typeofdata == typeid(int).name())
                                    {
                                        BinaryTree<int>* newtree = new BinaryTree<int>();
                                        prewhere((BinaryTree<int>*)Tree, less_then, *(int*)TemplateRand<int>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(Func).name())
                                    {
                                        BinaryTree<Func>* newtree = new BinaryTree<Func>();
                                        prewhere((BinaryTree<Func>*)Tree, less_then, *(Func*)TemplateRand<Func>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(double).name())
                                    {
                                        BinaryTree<double>* newtree = new BinaryTree<double>();
                                        prewhere((BinaryTree<double>*)Tree, less_then, *(double*)TemplateRand<double>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(complex).name())
                                    {
                                        BinaryTree<complex>* newtree = new BinaryTree<complex>();
                                        prewhere((BinaryTree<complex>*)Tree, less_then, *(complex*)TemplateRand<complex>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(string).name())
                                    {
                                        BinaryTree<string>* newtree = new BinaryTree<string>();
                                        prewhere((BinaryTree<string>*)Tree, less_then, *(string*)TemplateRand<string>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(Student).name())
                                    {
                                        BinaryTree<Student>* newtree = new BinaryTree<Student>();
                                        prewhere((BinaryTree<Student>*)Tree, less_then, *(Student*)TemplateRand<Student>(), newtree, 1);
                                    }
                                    if (typeofdata == typeid(Teacher).name())
                                    {
                                        BinaryTree<Teacher>* newtree = new BinaryTree<Teacher>();
                                        prewhere((BinaryTree<Teacher>*)Tree, less_then, *(Teacher*)TemplateRand<Teacher>(), newtree, 1);
                                    }
                                    break;
                                }
                                else if (choice4 == 2)
                                {
                                    cout << "?????????????? ???????????? ???????? " << typeofdata << " ?????? ?????????????????? : ";
                                    if (typeofdata == typeid(int).name())
                                    {
                                        BinaryTree<int>* newtree = new BinaryTree<int>();
                                        int temp = int();
                                        cin >> temp;
                                        prewhere((BinaryTree<int>*)Tree, less_then, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(Func).name())
                                    {
                                        BinaryTree<Func>* newtree = new BinaryTree<Func>();
                                        Func temp = Func();
                                        cin >> temp;
                                        prewhere((BinaryTree<Func>*)Tree, less_then, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(double).name())
                                    {
                                        BinaryTree<double>* newtree = new BinaryTree<double>();
                                        double temp = double();
                                        cin >> temp;
                                        prewhere((BinaryTree<double>*)Tree, less_then, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(complex).name())
                                    {
                                        BinaryTree<complex>* newtree = new BinaryTree<complex>();
                                        complex temp = complex();
                                        cin >> temp;
                                        prewhere((BinaryTree<complex>*)Tree, less_then, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(string).name())
                                    {
                                        BinaryTree<string>* newtree = new BinaryTree<string>();
                                        string temp = string();
                                        cin >> temp;
                                        prewhere((BinaryTree<string>*)Tree, less_then, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(Student).name())
                                    {
                                        BinaryTree<Student>* newtree = new BinaryTree<Student>();
                                        Student temp = Student();
                                        cin >> temp;
                                        prewhere((BinaryTree<Student>*)Tree, less_then, temp, newtree, 2);
                                    }
                                    if (typeofdata == typeid(Teacher).name())
                                    {
                                        BinaryTree<Teacher>* newtree = new BinaryTree<Teacher>();
                                        Teacher temp = Teacher();
                                        cin >> temp;
                                        prewhere((BinaryTree<Teacher>*)Tree, less_then, temp, newtree, 2);
                                    }
                                    break;
                                }
                                else
                                {
                                    cout << "???????????????? ????????.\n";
                                    cin.clear();
                                    while (cin.get() != '\n');
                                }
                            }
                            break;
                        }
                        else
                        {
                            cout << "???????????????? ????????.\n";
                            cin.clear();
                            while (cin.get() != '\n');
                        }
                    }
                }
                else if (choice2 == 3)
                {
                    if (typeid(int).name() == typeofdata)
                    {
                        Tree = premerge<int>((BinaryTree<int>*)Tree);
                    }
                    else if (typeid(double).name() == typeofdata)
                    {
                        Tree = premerge<double>((BinaryTree<double>*)Tree);
                    }
                    else if (typeid(complex).name() == typeofdata)
                    {
                        Tree = premerge<complex>((BinaryTree<complex>*)Tree);
                    }
                    else if (typeid(string).name() == typeofdata)
                    {
                        Tree = premerge<string>((BinaryTree<string>*)Tree);
                    }
                    else if (typeid(Func).name() == typeofdata)
                    {
                        Tree = premerge<Func>((BinaryTree<Func>*)Tree);
                    }
                    else if (typeid(Student).name() == typeofdata)
                    {
                        Tree = premerge<Student>((BinaryTree<Student>*)Tree);
                    }
                    else if (typeid(Teacher).name() == typeofdata)
                    {
                        Tree = premerge<Teacher>((BinaryTree<Teacher>*)Tree);
                    }
                }
                else if (choice2 == 4)
                {
                    {
                        if (typeid(int).name() == typeofdata)
                        {
                            Tree = pregetsubtree<int>((BinaryTree<int>*)Tree);
                        }
                        else if (typeid(double).name() == typeofdata)
                        {
                            Tree = pregetsubtree<double>((BinaryTree<double>*)Tree);
                        }
                        else if (typeid(complex).name() == typeofdata)
                        {
                            Tree = pregetsubtree<complex>((BinaryTree<complex>*)Tree);
                        }
                        else if (typeid(string).name() == typeofdata)
                        {
                            Tree = pregetsubtree<string>((BinaryTree<string>*)Tree);
                        }
                        else if (typeid(Func).name() == typeofdata)
                        {
                            Tree = pregetsubtree<Func>((BinaryTree<Func>*)Tree);
                        }
                        else if (typeid(Student).name() == typeofdata)
                        {
                            Tree = pregetsubtree<Student>((BinaryTree<Student>*)Tree);
                        }
                        else if (typeid(Teacher).name() == typeofdata)
                        {
                            Tree = pregetsubtree<Teacher>((BinaryTree<Teacher>*)Tree);
                        }
                    }
                }
                else if (choice2 == 5)
                {
                    if (typeid(int).name() == typeofdata)
                    {
                        prechecksubtree<int>((BinaryTree<int>*)Tree);
                    }
                    else if (typeid(double).name() == typeofdata)
                    {
                        prechecksubtree<double>((BinaryTree<double>*)Tree);
                    }
                    else if (typeid(complex).name() == typeofdata)
                    {
                        prechecksubtree<complex>((BinaryTree<complex>*)Tree);
                    }
                    else if (typeid(string).name() == typeofdata)
                    {
                        prechecksubtree<string>((BinaryTree<string>*)Tree);
                    }
                    else if (typeid(Func).name() == typeofdata)
                    {
                        prechecksubtree<Func>((BinaryTree<Func>*)Tree);
                    }
                    else if (typeid(Student).name() == typeofdata)
                    {
                        prechecksubtree<Student>((BinaryTree<Student>*)Tree);
                    }
                    else if (typeid(Teacher).name() == typeofdata)
                    {
                        prechecksubtree<Teacher>((BinaryTree<Teacher>*)Tree);
                    }
                }
                else if (choice2 == 6)
                {
                    if (typeid(int).name() == typeofdata)
                    {
                        precheckelem<int>((BinaryTree<int>*)Tree);
                    }
                    else if (typeid(double).name() == typeofdata)
                    {
                        precheckelem<double>((BinaryTree<double>*)Tree);
                    }
                    else if (typeid(complex).name() == typeofdata)
                    {
                        precheckelem<complex>((BinaryTree<complex>*)Tree);
                    }
                    else if (typeid(string).name() == typeofdata)
                    {
                        precheckelem<string>((BinaryTree<string>*)Tree);
                    }
                    else if (typeid(Func).name() == typeofdata)
                    {
                        precheckelem<Func>((BinaryTree<Func>*)Tree);
                    }
                    else if (typeid(Student).name() == typeofdata)
                    {
                        precheckelem<Student>((BinaryTree<Student>*)Tree);
                    }
                    else if (typeid(Teacher).name() == typeofdata)
                    {
                        precheckelem<Teacher>((BinaryTree<Teacher>*)Tree);
                    }
                }
                else if (choice2 == 7)
                {
                    if (typeid(int).name() == typeofdata)
                    {
                        pretreetostring<int>((BinaryTree<int>*)Tree);
                    }
                    else if (typeid(double).name() == typeofdata)
                    {
                        pretreetostring<double>((BinaryTree<double>*)Tree);
                    }
                    else if (typeid(complex).name() == typeofdata)
                    {
                        pretreetostring<complex>((BinaryTree<complex>*)Tree);
                    }
                    else if (typeid(string).name() == typeofdata)
                    {
                        pretreetostring<string>((BinaryTree<string>*)Tree);
                    }
                    else if (typeid(Func).name() == typeofdata)
                    {
                        pretreetostring<Func>((BinaryTree<Func>*)Tree);
                    }
                    else if (typeid(Student).name() == typeofdata)
                    {
                        pretreetostring<Student>((BinaryTree<Student>*)Tree);
                    }
                    else if (typeid(Teacher).name() == typeofdata)
                    {
                        pretreetostring<Teacher>((BinaryTree<Teacher>*)Tree);
                    }
                }
                else if (choice2 == 8)
                {
                    if (typeid(int).name() == typeofdata)
                    {
                        Tree = pregetnode<int>((BinaryTree<int>*)Tree);
                    }
                    else if (typeid(double).name() == typeofdata)
                    {
                        Tree = pregetnode<double>((BinaryTree<double>*)Tree);
                    }
                    else if (typeid(complex).name() == typeofdata)
                    {
                        Tree = pregetnode<complex>((BinaryTree<complex>*)Tree);
                    }
                    else if (typeid(string).name() == typeofdata)
                    {
                        Tree = pregetnode<string>((BinaryTree<string>*)Tree);
                    }
                    else if (typeid(Student).name() == typeofdata)
                    {
                        Tree = pregetnode<Student>((BinaryTree<Student>*)Tree);
                    }
                    else if (typeid(Teacher).name() == typeofdata)
                    {
                        Tree = pregetnode<Teacher>((BinaryTree<Teacher>*)Tree);
                    }
                    else if (typeid(Func).name() == typeofdata)
                    {
                        Tree = pregetnode<Func>((BinaryTree<Func>*)Tree);
                    }
                }
                else if (choice2 == 9)
                {
                    if (typeid(int).name() == typeofdata)
                    {
                        preinsert<int>((BinaryTree<int>*)Tree);
                    }
                    else if (typeid(double).name() == typeofdata)
                    {
                        preinsert<double>((BinaryTree<double>*)Tree);
                    }
                    else if (typeid(complex).name() == typeofdata)
                    {
                        preinsert<complex>((BinaryTree<complex>*)Tree);
                    }
                    else if (typeid(string).name() == typeofdata)
                    {
                        preinsert<string>((BinaryTree<string>*)Tree);
                    }
                    else if (typeid(Student).name() == typeofdata)
                    {
                        preinsert<Student>((BinaryTree<Student>*)Tree);
                    }
                    else if (typeid(Teacher).name() == typeofdata)
                    {
                        preinsert<Teacher>((BinaryTree<Teacher>*)Tree);
                    }
                    else if (typeid(Func).name() == typeofdata)
                    {
                        preinsert<Func>((BinaryTree<Func>*)Tree);
                    }

                }
                else if (choice2 == 10)
                {
                    if (typeid(int).name() == typeofdata)
                    {
                        predelteelem<int>((BinaryTree<int>*)Tree);
                    }
                    else if (typeid(double).name() == typeofdata)
                    {
                        predelteelem<double>((BinaryTree<double>*)Tree);
                    }
                    else if (typeid(complex).name() == typeofdata)
                    {
                        predelteelem<complex>((BinaryTree<complex>*)Tree);
                    }
                    else if (typeid(string).name() == typeofdata)
                    {
                        predelteelem<string>((BinaryTree<string>*)Tree);
                    }
                    else if (typeid(Student).name() == typeofdata)
                    {
                        predelteelem<Student>((BinaryTree<Student>*)Tree);
                    }
                    else if (typeid(Teacher).name() == typeofdata)
                    {
                        predelteelem<Teacher>((BinaryTree<Teacher>*)Tree);
                    }
                    else if (typeid(Func).name() == typeofdata)
                    {
                        predelteelem<Func>((BinaryTree<Func>*)Tree);
                    }
                }
                else if (choice2 == 11)
                {
                    if (typeid(int).name() == typeofdata)
                    {
                        Tree = prebalance<int>((BinaryTree<int>*)Tree);
                    }
                    else if (typeid(double).name() == typeofdata)
                    {
                        Tree = prebalance<double>((BinaryTree<double>*)Tree);
                    }
                    else if (typeid(complex).name() == typeofdata)
                    {
                        Tree = prebalance<complex>((BinaryTree<complex>*)Tree);
                    }
                    else if (typeid(string).name() == typeofdata)
                    {
                        Tree = prebalance<string>((BinaryTree<string>*)Tree);
                    }
                    else if (typeid(Student).name() == typeofdata)
                    {
                        Tree = prebalance<Student>((BinaryTree<Student>*)Tree);
                    }
                    else if (typeid(Teacher).name() == typeofdata)
                    {
                        Tree = prebalance<Teacher>((BinaryTree<Teacher>*)Tree);
                    }
                    else if (typeid(Func).name() == typeofdata)
                    {
                        Tree = prebalance<Func>((BinaryTree<Func>*)Tree);
                    }
                }
                else
                {
                    cout << "???????????????? ????????\n";
                    cin.clear();
                    while (cin.get() != '\n');
                }
            }
        }
        else if (choice1 == 3)
        {
            if (Tree == nullptr)
            {
                cout << "???? ?????????????? ???????????? ?????? ????????????????.\n";
            }
            else
            {
                delete Tree;
                Tree = nullptr;
                typeofdata = "";
                cout << "???????????? ?????????????? ??????????????.\n";
            }
        }
        else if (choice1 == 4)
        {
            if (typeofdata == typeid(int).name())
            {
                ((BinaryTree<int>*)Tree)->Print();
            }
            if (typeofdata == typeid(double).name())
            {
                ((BinaryTree<double>*)Tree)->Print();
            }
            if (typeofdata == typeid(complex).name())
            {
                ((BinaryTree<complex>*)Tree)->Print();
            }
            if (typeofdata == typeid(string).name())
            {
                ((BinaryTree<string>*)Tree)->Print();
            }
            if (typeofdata == typeid(Func).name())
            {
                ((BinaryTree<Func>*)Tree)->Print();
            }
            if (typeofdata == typeid(Student).name())
            {
                ((BinaryTree<Student>*)Tree)->Print();
            }
            if (typeofdata == typeid(Teacher).name())
            {
                ((BinaryTree<Teacher>*)Tree)->Print();
            }
        }
        else if (choice1 != 5)
        {
            cout << "???????????????? ????????\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }
}
