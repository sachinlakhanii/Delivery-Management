/*
--------------------------------------------- Explanation of Program ---------------------------------------------

The Smart Package Delivery System program is structured around the management of packages, returns, and orders, leveraging three distinct classes—Delivery, Return, and Order. The core data structure is defined by the Package struct, which encapsulates vital attributes such as package ID, weight, destination, and a pointer to the next package, enabling the implementation of linked lists.

The Delivery class is responsible for managing the delivery packages using a linked list approach. It provides several methods: addPackage, which allows the user to add a new package after checking for unique IDs; deletePackage, which removes a package based on its ID; modifyPackage, enabling updates to a package’s weight and destination; and displayPackages, which lists all packages currently in the delivery system.

The Return class implements a stack structure to manage returned packages. It includes the push method for adding a package to the stack, the pop method for processing the most recent return, and displayReturns to show all returns in the system.

The Order class employs a queue to manage outgoing orders. Its methods include enqueue, which adds a new order to the end of the queue; dequeue, which processes the first order in line; and displayOrders, which presents all active orders.

The program's main function creates instances of these classes and provides a menu-driven interface for users. This interface allows users to navigate between managing deliveries, returns, and orders seamlessly, performing various operations such as adding, deleting, updating, and displaying relevant package details.

------------------------------------------------------------------------------------------------------------------
*/

#include<iostream>
#include<string>

using namespace std;

struct Package
{
    int id;
    double weight;
    string destination;
    Package* next;
};

class Delivery
{
    public:
        Package* head = NULL;

        bool idExist(int id)
        {
            Package* temp = head;
            while (temp != NULL)
            {
                if (temp->id == id) return true;
                temp = temp->next;
            }
            return false;
        }

        void addPackage(int id, double weight, string destination)
        {
            cout << endl << "Enter Package ID: ";
            cin >> id;
            if (idExist(id))
            {
                cout << "ID already exists. Please enter a unique ID." << endl << endl;
                return;
            }

            Package* package = new Package();
            package->id = id;
            cout << "Enter Package Weight (In Grams): ";
            cin >> package->weight;
            cin.ignore();
            cout << "Enter Package Destination: ";
            getline(cin, package->destination);
            package->next = head;
            head = package;
            cout << endl << "Package has been Successfully Added!" << endl << endl;
        }

        void deletePackage(int id)
        {
            Package* temp = head;
            Package* prev = NULL;

            while (temp != NULL && temp->id != id)
            {
                prev = temp;
                temp = temp->next;
            }

            if (temp == NULL)
            {
                cout << "Package not found!" << endl << endl;
                return;
            }

            if (prev == NULL)
            {
                head = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }

            delete temp;
            cout << "Package has been Successfully Removed!" << endl << endl;
        }

        void modifyPackage(int id)
        {
            Package* temp = head;

            while (temp != NULL && temp->id != id)
            {
                temp = temp->next;
            }

            if (temp == NULL)
            {
                cout << "Package not found!" << endl << endl;
                return;
            }

            cout << "Enter new destination: ";
            cin.ignore();
            getline(cin, temp->destination);
            cout << "Enter new weight: ";
            cin >> temp->weight;
            cout << "Package has been Successfully Updated!" << endl << endl;
        }

        void displayPackages()
        {
            Package* temp = head;

            while (temp != NULL)
            {
                cout << endl << "ID: " << temp->id << endl << "Weight: " << temp->weight << endl << "Destination: " << temp->destination << endl;
                temp = temp->next;
            }
            cout << endl;
        }
};

class Return
{
    public:
        Package* top = NULL;

        bool idExist(int id)
        {
            Package* temp = top;
            while (temp != NULL)
            {
                if (temp->id == id) return true;
                temp = temp->next;
            }
            return false;
        }

        void push(int id, double weight, string destination)
        {
            cout << endl << "Enter Package ID: ";
            cin >> id;
            if (idExist(id))
            {
                cout << "ID already exists. Please enter a unique ID." << endl << endl;
                return;
            }

            Package* package = new Package();
            package->id = id;
            cout << "Enter Package Weight (In Grams): ";
            cin >> package->weight;
            cin.ignore();
            cout << "Enter Package Destination: ";
            getline(cin, package->destination);
            package->next = top;
            top = package;
            cout << "Package has been Successfully added to Returns!" << endl << endl;
        }

        void pop()
        {
            if (top == NULL)
            {
                cout << "No returns to process." << endl << endl;
                return;
            }

            Package* temp = top;
            top = top->next;
            cout << "Processing return ID: " << temp->id << endl;
            delete temp;
            cout << endl;
        }

        void displayReturns()
        {
            Package* temp = top;

            while (temp != NULL)
            {
                cout << endl << "ID: " << temp->id << endl << "Weight: " << temp->weight << endl << "Destination: " << temp->destination << endl;
                temp = temp->next;
            }
            cout << endl;
        }
};

class Order
{
    public:
        Package* front = NULL;
        Package* rear = NULL;

        bool idExist(int id)
        {
            Package* temp = front;
            while (temp != NULL)
            {
                if (temp->id == id) return true;
                temp = temp->next;
            }
            return false;
        }

        void enqueue(int id, double weight, string destination)
        {
            cout << endl << "Enter Package ID: ";
            cin >> id;
            if (idExist(id))
            {
                cout << "ID already exists. Please enter a unique ID." << endl << endl;
                return;
            }

            Package* package = new Package();
            package->id = id;
            cout << "Enter Package Weight (In Grams): ";
            cin >> package->weight;
            cin.ignore();
            cout << "Enter Package Destination: ";
            getline(cin, package->destination);
            package->next = NULL;

            if (rear == NULL)
            {
                front = rear = package;
            }
            else
            {
                rear->next = package;
                rear = package;
            }

            cout << "Order has been Successfully Placed!" << endl << endl;
        }

        void dequeue()
        {
            if (front == NULL)
            {
                cout << "No orders to process." << endl << endl;
                return;
            }

            Package* temp = front;
            cout << "Processing order ID: " << temp->id << endl;
            front = front->next;

            if (front == NULL)
            {
                rear = NULL;
            }

            delete temp;
            cout << endl;
        }

        void displayOrders()
        {
            Package* temp = front;

            while (temp != NULL)
            {
                cout << endl << "ID: " << temp->id << endl << "Weight: " << temp->weight << endl << "Destination: " << temp->destination << endl;
                temp = temp->next;
            }
            cout << endl;
        }
};

int main()
{
    Delivery deliveries;
    Return returns;
    Order orders;

    int ch1, ch2, id;
    double weight;
    string destination;

    do
    {
        cout << "----------------------------------- Smart Package Delivery System -----------------------------------" << endl << endl;
        cout << "Enter an Option to Open a Menu: " << endl;
        cout << "1. Package Menu" << endl;
        cout << "2. Return Menu" << endl;
        cout << "3. Orders Menu" << endl;
        cout << "4. Display All Details" << endl;
        cout << "0. Exit" << endl;
        cout << endl << "Enter your Choice: ";
        cin >> ch1;

        switch (ch1)
        {
            case 1:
            {
                do
                {
                    cout << endl << "----------------------------------- Package Menu -----------------------------------" << endl << endl;
                    cout << "1. Add Delivery for Package" << endl;
                    cout << "2. Remove Delivered Package" << endl;
                    cout << "3. Update Package" << endl;
                    cout << "4. Display Packages" << endl;
                    cout << "0. Return to Main Menu" << endl;
                    cout << endl << "Enter your Choice: ";
                    cin >> ch2;

                    switch (ch2)
                    {
                        case 1:
                            deliveries.addPackage(id, weight, destination);
                            break;

                        case 2:
                            cout << "Enter Package ID to remove: ";
                            cin >> id;
                            deliveries.deletePackage(id);
                            break;

                        case 3:
                            cout << "Enter Package ID to search and update: ";
                            cin >> id;
                            deliveries.modifyPackage(id);
                            break;

                        case 4:
                            deliveries.displayPackages();
                            break;
                    }
                } 
                while (ch2 != 0);
                break;
            }

            case 2:
            {
                do
                {
                    cout << endl << "----------------------------------- Return Menu -----------------------------------" << endl << endl;
                    cout << "1. Add Package to Returns" << endl;
                    cout << "2. Process Return" << endl;
                    cout << "3. Display Returns" << endl;
                    cout << "0. Return to Main Menu" << endl;
                    cout << endl << "Enter your Choice: ";
                    cin >> ch2;

                    switch (ch2)
                    {
                        case 1:
                            returns.push(id, weight, destination);
                            break;

                        case 2:
                            returns.pop();
                            break;

                        case 3:
                            returns.displayReturns();
                            break;
                    }
                } 
                while (ch2 != 0);
                break;
            }

            case 3: 
            {
                do
                {
                    cout << endl << "----------------------------------- Orders Menu -----------------------------------" << endl << endl;
                    cout << "1. Place Order" << endl;
                    cout << "2. Process Order" << endl;
                    cout << "3. Display Orders" << endl;
                    cout << "0. Return to Main Menu" << endl;
                    cout << endl << "Enter your Choice: ";
                    cin >> ch2;

                    switch (ch2)
                    {
                        case 1:
                            orders.enqueue(id, weight, destination);
                            break;

                        case 2:
                            orders.dequeue();
                            break;

                        case 3:
                            orders.displayOrders();
                            break;
                    }
                } 
                while (ch2 != 0);
                break;
            }

            case 4: 
            {
                cout << endl << "----------------------------------- All Packages -----------------------------------" << endl;
                deliveries.displayPackages();
                cout << endl << "----------------------------------- All Returns -----------------------------------" << endl;
                returns.displayReturns();
                cout << endl << "----------------------------------- All Orders -----------------------------------" << endl;
                orders.displayOrders();
                break;
            }

            case 0:
                cout << "Exiting the system. Thank you!" << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } 
    while (ch1 != 0);

    return 0;
}