#include <iostream>
#include <queue>
#include <list>
using namespace std;

class Human
{
protected:
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

class Patient : public Human
{
    int patientNo;
    int priorityScore;

public:
    Patient(int patientNo, Human &h) : patientNo(patientNo), Human(h), priorityScore(0)
    {
        priorityScoreCalculate();
    }

    Patient(int patientNo, string firstName, string lastName, int age, bool isDisabled = false) : patientNo(patientNo), Human(firstName, lastName, age, isDisabled), priorityScore(0)
    {
        priorityScoreCalculate();
    }

    void priorityScoreCalculate()
    {
        if (isDisabled)
            priorityScore += 30;
        if (age > 65)
            priorityScore += age - 65;
    }

    bool operator<(const Patient &p) const
    {
        return priorityScore < p.priorityScore;
    }

    void print() const
    {
        cout << "Patient No : " << patientNo << endl;
        Human::print();
        cout << "Priority Score : " << priorityScore << endl;
    }
};
int main()
{

    Human human("hikmet", "suicmez", 21);
    Human human2("hakan", "aktas", 22, 1);
    // human.print();
    // human2.print();

    Patient p(1, human);
    p.print();

    return 0;
}