#include <iostream>
#include <queue>
#include <list>
using namespace std;

class Human
{
private:
    string firstName;
    string lastName;
    int age;
    bool isDisabled;

public:
    Human(string firstName, string lastName, int age, bool isDisabled = false) : firstName(firstName), lastName(lastName), age(age), isDisabled(isDisabled) {}

    void print() const
    {
        cout << "First Name : " << firstName << endl
             << "Last Name : " << lastName << endl
             << "Disability Status : ";
        if (isDisabled)
            cout << "Yes";
        else
            cout << "No";
        cout << endl;
    }
};

int main()
{
    Human human("hikmet", "suicmez", 21);
    Human human2("hakan","aktas",22,1);
    human.print();
    human2.print();
    return 0;
}