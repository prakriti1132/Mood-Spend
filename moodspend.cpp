#include <iostream>
using namespace std;
class Expense {
private:
    string category;
    float  amount;
    string mood;
    string date;
    string note;

public:
    Expense(string cat, float amt, string m, string d, string n) {
        category = cat;
        amount   = amt;
        mood     = m;
        date     = d;
        note     = n;
    }

    void setCategory(string cat) 
    { 
        category = cat; 
    }
    void setAmount(float amt)    
    { 
        amount = amt;  
    }
    void setMood(string m)       
    { 
        mood = m;       
    }
    void setDate(string d)       
    { 
        date = d;       
    }
    void setNote(string n)       
    { 
        note = n;       
    }

    string getCategory() 
    { 
        return category; 
    }
    float  getAmount()   
    { 
        return amount;   
    }
    string getMood()     
    { 
        return mood;     
    }
    string getDate()     
    { 
        return date;     
    }
    string getNote()     
    { 
        return note;     
    }

    virtual void display() = 0;

    virtual ~Expense() {}
};

class EssentialExpense : public Expense {
public:
    EssentialExpense(string cat, float amt, string m, string d, string n)
        : Expense(cat, amt, m, d, n) {}

    void display() override {
        cout << "  [ESSENTIAL EXPENSE]\n";
        cout << "  Category : " << getCategory() << "\n";
        cout << "  Amount   : NPR" << getAmount()  << "\n";
        cout << "  Mood     : " << getMood()     << "\n";
        cout << "  Date     : " << getDate()     << "\n";
        cout << "  Note     : " << getNote()     << "\n";
        cout << "  --------------------------\n";
    }
};

class EmotionalExpense : public Expense {
public:
    EmotionalExpense(string cat, float amt, string m, string d, string n)
        : Expense(cat, amt, m, d, n) {}

    void display() override {
        cout << "  [EMOTIONAL EXPENSE]\n";
        cout << "  Category : " << getCategory() << "\n";
        cout << "  Amount   : NPR" << getAmount()  << "\n";
        cout << "  Mood     : " << getMood()     << "\n";
        cout << "  Date     : " << getDate()     << "\n";
        cout << "  Note     : " << getNote()     << "\n";
        cout << "  --------------------------\n";
    }
};

class User {
private:
    string name;
    Expense* expenses[10];  
    int count;//

public:
    User(string n) {
        name  = n;
        count = 0;
    }

    string getName() 
    { 
        return name; 
    }

    void addExpense(Expense* e) 
    {
        if (count < 10) 
        {
            expenses[count] = e;
            count++;
            cout << "\n  Expense added!\n";
        } 
        else 
        {
            cout << "\n  Expense limit reached (max 10)!\n";
        }
    }

    void viewAll() 
    {
        if (count == 0)
        {
            cout << "\n  No expenses added yet.\n";
            return;
        }
        cout << "\n====== All Expenses ======\n";
        for (int i = 0; i < count; i++) 
        {
            cout << "\n  #" << i + 1 << "\n";
            expenses[i]->display();  
        }
    }

    void totalExpenses() 
    {
        if (count == 0) 
        {
            cout << "\n  No expenses added yet.\n";
            return;
        }
        float total = 0;
        for (int i = 0; i < count; i++)
            total += expenses[i]->getAmount();
        cout << "\n  OVERALL TOTAL : NPR" << total << "\n";
    }

    void byMood(string mood) 
    {
        if (count == 0) 
        {
            cout << "\n  No expenses added yet.\n";
            return;
        }
        float total = 0;
        cout << "\n====== Expenses for mood: " << mood << " ======\n";
        for (int i = 0; i < count; i++) 
        {
            if (expenses[i]->getMood() == mood) 
            {
                expenses[i]->display();
                total += expenses[i]->getAmount();
            }
        }
        cout << "  Total for " << mood << " : NPR" << total << "\n";
    }

    ~User() 
    {
        for (int i = 0; i < count; i++)
            delete expenses[i];
    }
};

int main() 
{
    cout << "==============================\n";
    cout << "  Mood-Based Expense Tracker  \n";
    cout << "==============================\n";

    string name;
    cout << "Enter your name: ";
    cin >> name;

    User user(name);
    int choice;

    do {
        cout << "\n------ MENU ------\n";
        cout << "1. Add Expense\n";
        cout << "2. View All Expenses\n";
        cout << "3. Total Expenses\n";
        cout << "4. Expenses by Mood\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1) 
        {
            cout << "\n  Categories:\n";
            cout << "  1. Food\n";
            cout << "  2. Shopping\n";
            cout << "  3. Transport\n";
            cout << "  4. Entertainment\n";
            cout << "  5. Health\n";
            cout << "  6. Other\n";
            cout << "  Choose (1-6): ";
            int c; cin >> c;
            string category;
            if      (c == 1) category = "Food";
            else if (c == 2) category = "Shopping";
            else if (c == 3) category = "Transport";
            else if (c == 4) category = "Entertainment";
            else if (c == 5) category = "Health";
            else             category = "Other";

            cout << "\n  Moods:\n";
            cout << "  1. Happy\n";
            cout << "  2. Sad\n";
            cout << "  3. Stressed\n";
            cout << "  4. Bored\n";
            cout << "  5. Excited\n";
            cout << "  Choose (1-5): ";
            int m; cin >> m;
            string mood;
            if      (m == 1) mood = "Happy";
            else if (m == 2) mood = "Sad";
            else if (m == 3) mood = "Stressed";
            else if (m == 4) mood = "Bored";
            else             mood = "Excited";

            float amt;
            string date, note;
            cout << "  Date (e.g. 2025-03-13): ";
            cin >> date;
            cout << "  Amount (NPR): ";
            cin >> amt;
            cout << "  Note: ";
            cin >> note;

            cout << "\n  Type:\n  1. Essential\n  2. Emotional\n  Choose: ";
            int type; cin >> type;

            if (type == 1)
                user.addExpense(new EssentialExpense(category, amt, mood, date, note));
            else
                user.addExpense(new EmotionalExpense(category, amt, mood, date, note));

        } else if (choice == 2) 
        {
            user.viewAll();

        } 
        else if (choice == 3) 
        {
            user.totalExpenses();

        } 
        else if (choice == 4) 
        {
            cout << "\n  Moods: Happy / Sad / Stressed / Bored / Excited\n";
            cout << "  Enter mood: ";
            string mood; cin >> mood;
            user.byMood(mood);

        } 
        else if (choice != 0) 
        {
            cout << "  Invalid choice.\n";
        }

    } 
    while (choice != 0);

    cout << "\nGoodbye, " << user.getName() << "!\n";
    return 0;
}
