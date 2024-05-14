#include <iostream>
#include <string>

using namespace std;

struct Employee {
    static int nextId;
    int id;
    string name;
    string entryTime;
    string exitTime;
    string joiningDate;
    double salary;

    Employee(string empName, string date) : id(nextId++), name(empName), joiningDate(date), salary(1700) {}
};

int Employee::nextId = 1000;

class Node {
public:
    Employee emp;
    Node* next;

    Node(Employee empData) : emp(empData), next(nullptr) {}
};

class EmployeeList {
private:
    Node* head;

    void bubbleSortEmployeesByName() {
        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            while (current && current->next) {
                if (current->emp.name > current->next->emp.name) {
                    swap(current->emp, current->next->emp);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    void bubbleSortEmployeesByIdAndSalary() {
        bool swapped;
        do {
            swapped = false;
            Node* current = head;
            while (current && current->next) {
                if (current->emp.salary > current->next->emp.salary ||
                    (current->emp.salary == current->next->emp.salary && current->emp.id > current->next->emp.id)) {
                    swap(current->emp, current->next->emp);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

public:
    EmployeeList() : head(nullptr) {}

    void addEmployee(Employee newEmployee, double price) {
        if (!head) {
            head = new Node(newEmployee);
            head->emp.salary += price;
            return;
        }

        Node* temp = head;
        while (temp->next) {
            if (temp->emp.id == newEmployee.id) {
                cout << "Employee with ID " << newEmployee.id << " already exists." << endl;
                return;
            }
            temp = temp->next;
        }

        if (temp->emp.id == newEmployee.id) {
            cout << "Employee with ID " << newEmployee.id << " already exists." << endl;
            return;
        }

        temp->next = new Node(newEmployee);
        temp->next->emp.salary += price;
    }

    Employee* searchEmployee(int empId) {
        Node* temp = head;
        while (temp) {
            if (temp->emp.id == empId) {
                return &(temp->emp);
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void displayAllEmployees() {
        Node* temp = head;
        while (temp) {
            cout << "ID : " << temp->emp.id << "\n\t Name: " << temp->emp.name << "  , Salary: $" << temp->emp.salary << "  , Joining Date: " << temp->emp.joiningDate << "\n" << endl;
            cout << "_________*************************************_________________________" << endl;
            temp = temp->next;
        }
    }

    void displayLastEmployeeAdded() {
        if (!head) {
            cout << "No employees in the list." << endl;
            return;
        }

        Node* temp = head;
        while (temp->next) {
            temp = temp->next;
        }

        cout << "Last Employee Added:" << endl;
        cout << "ID : " << temp->emp.id << "\n\t Name: " << temp->emp.name << "  , Salary: $" << temp->emp.salary << "  , Joining Date: " << temp->emp.joiningDate << "\n" << endl;
        cout << "_________*************************************_________________________" << endl;
    }

    void removeEmployee(int empId) {
        if (!head) {
            cout << "No employees in the list." << endl;
            return;
        }

        Node* temp = head;
        Node* prev = nullptr;

        if (temp->emp.id == empId) {
            head = temp->next;
            delete temp;
            cout << "Employee with ID " << empId << " has been removed." << endl;
            return;
        }

        while (temp && temp->emp.id != empId) {
            prev = temp;
            temp = temp->next;
        }

        if (!temp) {
            cout << "Employee with ID " << empId << " not found." << endl;
            return;
        }

        prev->next = temp->next;
        delete temp;
        cout << "Employee with ID " << empId << " has been removed." << endl;
    }

    void displaySortedEmployeesByName() {
        bubbleSortEmployeesByName();

        cout << "Employees Sorted Alphabetically by Name:" << endl;
        displayAllEmployees();
        cout << "___________________________" << endl;
    }

    void displaySortedEmployeesByIdAndSalary() {
        bubbleSortEmployeesByIdAndSalary();

        cout << "Employees Sorted by ID and Salary:" << endl;
        displayAllEmployees();
        cout << "___________________________" << endl;
    }
};

int main() {
    cout << "\t\t\t\t**********************************************" << endl;
    cout << "\t\t\t\t*                                            *" << endl;
    cout << "\t\t\t\t*   Welcome to Our Company's Application!    *" << endl;
    cout << "\t\t\t\t*                                            *" << endl;
    cout << "\t\t\t\t**********************************************" << endl;
    EmployeeList employees;

    employees.addEmployee(Employee("ahmed hassan", "2023-01-01"), 0);
    employees.addEmployee(Employee("jane Smith", "2015-02-15"), 2000);
    employees.addEmployee(Employee("mai tarek", "2013-03-20"), 2100);
    employees.addEmployee(Employee("mahmoud Ali", "2023-04-05"), 0);
    employees.addEmployee(Employee("salah ebrahim", "2017-05-10"), 1900);
    employees.addEmployee(Employee("emad salah", "2023-07-01"), 0);
    employees.addEmployee(Employee("maryam atia", "2011-02-15"), 2200);
    employees.addEmployee(Employee("yousef mohamed", "2023-05-20"), 0);
    employees.addEmployee(Employee("menna ahmed", "2023-11-05"), 0);
    employees.addEmployee(Employee("shahd mohamed", "2019-05-10"), 1800);

    while (true) {
        int choice;
        cout << "\n\tEnter your choice:\n" << endl;
        cout << "\t1.View all employees\n" << endl;
        cout << "\t2.Search for an employee by ID\n" << endl;
        cout << "\t3.Add a new employee\n" << endl;
        cout << "\t4.View last employee added\n" << endl;
        cout << "\t5.Remove an employee by ID\n" << endl;
        cout << "\t6.Display employees sorted by name\n" << endl;
        cout << "\t7.Display employees sorted by salary\n" << endl;
        cout << "\t0.Exit\n" << endl;
        cout << "\t\t\t\t\t\tEnter choice: \n";
        cin >> choice;

        if (choice == 0) {
            break;
        }

        switch (choice) {
        case 1: {
            employees.displayAllEmployees();
            break;
        }
        case 2: {
            int searchId;
            cout << "Enter Employee ID to search: ";
            cin >> searchId;

            Employee* foundEmployee = employees.searchEmployee(searchId);
            if (foundEmployee != nullptr) {
                cout << "Employee found - ID: " << foundEmployee->id << ", Name: " << foundEmployee->name << ", Salary: $" << foundEmployee->salary << ", Joining Date: " << foundEmployee->joiningDate << endl;
            }
            else {
                cout << "Employee with ID " << searchId << " not found." << endl;
            }
            break;
        }
        case 3: {
            string name, joiningDate;
            double price;

            cout << "Enter Employee Name: ";
            cin.ignore();
            getline(cin, name);

            cout << "Enter Employee Joining Date (YYYY-MM-DD): ";
            cin >> joiningDate;

            cout << "Enter Additional Price: $";
            cin >> price;

            employees.addEmployee(Employee(name, joiningDate), price);
            break;
        }
        case 4: {
            employees.displayLastEmployeeAdded();
            break;
        }
        case 5: {
            int removeId;
            cout << "Enter Employee ID to remove: ";
            cin >> removeId;

            employees.removeEmployee(removeId);
            break;
        }
        case 6: {
            employees.displaySortedEmployeesByName();
            break;
        }
        case 7: {
            employees.displaySortedEmployeesByIdAndSalary();
            break;
        }
        default: {
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
        }
    }

    return 0;
}
