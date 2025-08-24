#include<bits/stdc++.h>
#include <windows.h>
using namespace std;

class Inventory
{
private:
    string Item;
    int Rate, Quantity;

public:
    Inventory(){
        Item = "";
        Rate = 0;
        Quantity = 0;
    }

    void setItem(string item)
    {
        this->Item = item;
    }

    void setRate(int rate)
    {
        this->Rate = rate;
    }

    void setQuant(int quant)
    {
        this->Quantity = quant;
    }

    string getItem()
    {
        return this->Item;
    }

    int getRate()
    {
        return this->Rate;
    }

    int getQuant()
    {
        return this->Quantity;
    }
};

void addItem(Inventory b)
{
    bool close = false;
    while (!close)
    {
        int choice;
        cout << "\t1.Add." << endl;
        cout << "\t2.close." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            system("cls");
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate Of Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity Of Item: ";
            cin >> quant;
            b.setQuant(quant);

            // Step 1: Read all inventory into memory
            vector<Inventory> items;
            ifstream in("Inventory.txt");
            string line;

            while (getline(in, line))
            {
                if (line.empty()) continue;

                stringstream ss(line);
                string itemName;
                int itemRate, itemQuant;
                char colon;

                ss >> itemName >> colon >> itemRate >> colon >> itemQuant;

                Inventory temp;
                temp.setItem(itemName);
                temp.setRate(itemRate);
                temp.setQuant(itemQuant);
                items.push_back(temp);
            }
            in.close();

            // Step 2: Check if item exists → update quantity
            bool found = false;
            for (auto &it : items)
            {
                if (it.getItem() == b.getItem() && it.getRate() == b.getRate())
                {
                    it.setQuant(it.getQuant() + b.getQuant());
                    found = true;
                    break;
                }
            }

            // Step 3: If not found, add new item
            if (!found)
            {
                items.push_back(b);
            }

            // Step 4: Rewrite entire file
            ofstream out("Inventory.txt", ios::trunc);
            for (auto &it : items)
            {
                out << "\t" << it.getItem() << " : " << it.getRate()
                    << " : " << it.getQuant() << endl;
            }
            out.close();

            cout << "\tItem Added/Updated Successfully in your Inventory!" << endl;
            Sleep(2000);
        }
        else if (choice == 2)
        {
            system("cls");
            close = true;
            cout << "\tBack To Main Menu!" << endl;
            Sleep(2000);
        }
    }
}

void printBill()
{
    system("cls");
    int total = 0;
    bool close = false;

    while (!close)
    {
        system("cls");
        int choice;
        cout << "\t1.Print Bill." << endl;
        cout << "\t2.Close Session." << endl;
        cout << "\tEnter Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string item;
            int quant;
            cout << "\tEnter Item: ";
            cin >> item;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            // Step 1: Load inventory into memory
            vector<Inventory> items;
            ifstream in("Inventory.txt");
            string line;
            while (getline(in, line))
            {
                if (line.empty()) continue;

                stringstream ss(line);
                string itemName;
                int itemRate, itemQuant;
                char colon;
                ss >> itemName >> colon >> itemRate >> colon >> itemQuant;

                Inventory temp;
                temp.setItem(itemName);
                temp.setRate(itemRate);
                temp.setQuant(itemQuant);
                items.push_back(temp);
            }
            in.close();

            // Step 2: Search and update
            bool found = false;
            for (auto &it : items)
            {
                if (it.getItem() == item)
                {
                    found = true;
                    if (quant <= it.getQuant())
                    {
                        int amount = it.getRate() * quant;
                        cout << "\t Item | Rate | Quantity | Amount" << endl;
                        cout << "\t" << it.getItem() << "\t " << it.getRate()
                             << "\t " << quant << "\t " << amount << endl;

                        it.setQuant(it.getQuant() - quant); // 🔥 reduce quantity
                        total += amount;
                    }
                    else
                    {
                        cout << "\tSorry, not enough stock for " << item << "!" << endl;
                    }
                    break;
                }
            }

            if (!found)
            {
                cout << "\tItem Not Available!" << endl;
            }

            // Step 3: Rewrite the file with updated quantities
            ofstream out("Inventory.txt", ios::trunc);
            for (auto &it : items)
            {
                out << "\t" << it.getItem() << " : "
                    << it.getRate() << " : "
                    << it.getQuant() << endl;
            }
            out.close();
        }
        else if (choice == 2)
        {
            close = true;
            cout << "\tCounting Total Bill..." << endl;
        }
        Sleep(1000);
    }

    system("cls");
    cout << "\n\n";
    cout << "\t Total Bill ----------------- : " << total << endl << endl;
    cout << "\tThanks For Shopping!" << endl;
    Sleep(5000);
}

int main()
{
    Inventory b;

    bool exit = false;
    while (!exit)
    {
        system("cls");
        int val;

        cout << "\tWelcome To Super Market Billing System" << endl;
        cout << "\t**************************************" << endl;
        cout << "\t\t1.Add Item." << endl;
        cout << "\t\t2.Print Bill." << endl;
        cout << "\t\t3.Exit." << endl;
        cout << "\t\tEnter Choice: ";
        cin >> val;

        if (val == 1)
        {
            system("cls");
            addItem(b);
            Sleep(3000);
        }

        else if (val == 2)
        {
            printBill();
        }

        else if (val == 3)
        {
            system("cls");
            exit = true;
            cout << "\tGood Luck!" << endl;
            Sleep(3000);
        }
    }
}