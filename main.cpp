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

class patientRegistration
{
    list<Patient> registrationOrder;
    priority_queue<Patient> inspectionOrder;

public:
    void add(Human &h)
    {
        Patient patient(registrationOrder.size() + 1, h);
        registrationOrder.push_back(patient);
        inspectionOrder.push(patient);
    }

    void registrationOrderPrint()
    {
        cout << " ### Patient Registration Order ###" << endl;
        if (registrationOrder.empty())
            cout << "No registered patients." << endl;
        else
        {
            list<Patient>::iterator iter = registrationOrder.begin();
            while (iter != registrationOrder.end())
            {
                Patient patient = *iter;
                patient.print();
                iter++;
                if (iter != registrationOrder.end())
                    cout << endl;
            }
        }
        cout << " ### End of Patient Registration Order ###" << endl;
    }

    void inspectionOrderPrint()
    {
        cout << " ### Inspection Order ###" << endl;
        if (inspectionOrder.empty())
            cout << "No patients waiting for examination." << endl;
        else
        {
            priority_queue<Patient> queue = inspectionOrder;
            while (!queue.empty())
            {
                Patient patient = queue.top();
                patient.print();
                queue.pop();
                if (!queue.empty())
                    cout << endl;
            }
        }
        cout << " ### End of Inspection Order ###" << endl;
    }

    void callPatient()
    {
        if (inspectionOrder.empty())
            cout << "No patients waiting for examination queue." << endl;
        else
        {
            cout << "-- Patient information called for examination.-- " << endl;
            Patient patient = inspectionOrder.top();
            patient.print();
            inspectionOrder.pop();
        }
        cout << endl;
    }
};

int main()
{

    Human human("hikmet", "suicmez", 21);
    Human human2("hakan", "aktas", 22, 1);
    patientRegistration banko;
    banko.add(human);
    banko.add(human2);
    banko.registrationOrderPrint();
    cout << endl;
    banko.inspectionOrderPrint();
    banko.callPatient();
    banko.callPatient();
    banko.callPatient();
    return 0;
}