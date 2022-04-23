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
    Human humans[] = {
        Human ("Hikmet", "Suicmez", 21),
        Human ("Hakan", "Aktas", 22, 1),
        Human ("Ahmet", "Yavuz", 69),
        Human ("Faruk", "Doner", 79, 1),
        Human ("Ayse", "Sonmez", 49, 1),
        Human ("Ugurcan", "Cakir", 65)
    };

    patientRegistration banko;
    banko.add(humans[0]);
    banko.add(humans[1]);
    banko.add(humans[3]);
    banko.add(humans[2]);
    banko.add(humans[4]);
    banko.add(humans[5]);
    banko.registrationOrderPrint();
    cout << endl;
    banko.inspectionOrderPrint();
    banko.callPatient();
    banko.callPatient();
    banko.callPatient();
    banko.callPatient();
    banko.callPatient();
    banko.callPatient();
    banko.callPatient();
    banko.registrationOrderPrint();
    cout << endl;
    banko.inspectionOrderPrint();

    return 0;
}