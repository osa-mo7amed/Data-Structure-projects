#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

// ---------------- Dish Linked List Functions ----------------

static int dishesCount;

class Dish
{
public:
    string dishID;
    int type;
    string name;
    double price;
    double calories;
};

class DishNode
{
public:
    Dish dish;
    DishNode* next;
    DishNode* prev;
};

static vector<Dish> specialsVec;

// Function to create a Dish object
Dish createDish()
{
    Dish dish;
    char option;

    cin.ignore();

    cout << "Enter dish item name: ";
    getline(cin, dish.name);

    cout << "Enter dish item price: RM";
    cin >> dish.price;

    cout << "Enter dish item calories: ";
    cin >> dish.calories;

    cout << "Enter dish item type: (1 = Ala Carte, 2 = Set Meal): ";
    cin >> dish.type;

    cout << "Dish is daily special/promotion item? [Y/N]: ";
    cin >> option;

    while (option != 'Y' && option != 'y' && option != 'N' && option != 'n')
    {
        cout << "[!] Invalid option, please enter either Y or N!" << endl;
        cout << "Dish is daily special/promotion item? [Y/N]: ";
        cin >> option;
    }

    // The three lines below are to create a string stream
    // that we convert to a normal string. We used this
    // approach to auto increment the dishID everytime an
    // order is created.
    ostringstream oss;
    oss << right << setw(5) << setfill('0') << (dishesCount + 1);
    dish.dishID = "DSH#" + oss.str();
    dishesCount++;

    if (option == 'Y' || option == 'y')
        specialsVec.push_back(dish);

    return dish;
}

// Function to update dish's information
Dish updateDish(Dish& dish)
{
    Dish n;

    cin.ignore();

    n.dishID = dish.dishID;

    cout << "Enter dish item name: ";
    getline(cin, n.name);

    cout << "Enter dish item price: RM";
    cin >> n.price;

    cout << "Enter dish item calories: ";
    cin >> n.calories;

    cout << "Enter dish item type: (1 = Ala Carte, 2 = Set Meal): ";
    cin >> n.type;

    return n;
}

// Function to insert a Dish node at the beginning of the double linked list
void insertAtBeginning(DishNode*& head, DishNode*& tail, DishNode* n)
{
    head = n;
    tail = n;
}

// Function to insert a Dish node at the end of the double linked list
void insertAtEnd(DishNode*& tail, DishNode* n)
{
    tail->next = n;
    n->prev = tail;
    tail = n;
}

// Function to delete a Dish node from the beginning of the double linked list
void deleteFromBeginning(DishNode*& head)
{
    DishNode* n = head;
    head = head->next;
    n->next = n->prev = NULL;
    free(n);
}

// Function to delete a Dish node from the beginning of the double linked list
void deleteFromEnd(DishNode*& tail)
{
    DishNode* n = tail;
    tail = tail->prev;
    n->prev = n->next = NULL;
    free(n);
}

// Function to be called to insert order into double linked list
void insertDishItem(DishNode*& menuHead, DishNode*& menuTail, Dish& dish)
{
    DishNode* n = new DishNode();
    n->dish = dish;
    n->next = NULL;
    n->prev = NULL;

    if (menuHead == NULL && menuTail == NULL)
    {
        insertAtBeginning(menuHead, menuTail, n);
        cout << "[+] Added dish item (" << n->dish.dishID << ") successfully!" << endl;
    }

    else
    {
        insertAtEnd(menuTail, n);
        cout << "[+] Added dish item (" << n->dish.dishID << ") successfully!" << endl;
    }
    cout << '\n';
}

// Function to delete Dish from the double linked list
void deleteDishItem(DishNode*& menuHead, DishNode*& menuTail, string dishID)
{
    DishNode* tmp = menuHead;
    int match = 0;

    if (menuHead == NULL && menuTail == NULL)
    {
        cout << "[!] There are no dish items in the menu to delete!" << endl;
        return;
    }

    while (tmp != NULL)
    {
        if (tmp->dish.dishID == dishID)
        {
            match = 1;

            // Check if the node to be deleted is the only node
            // in the double linked list.
            if (tmp == menuHead && tmp == menuTail)
            {
                cout << "[X] Deleted dish item (" << tmp->dish.dishID << ") successfully!" << endl;
                deleteFromBeginning(menuHead);
                break;
            }

            // If it is not the only node but it is the first
            // node to be deleted from the double linked list.
            else if (tmp == menuHead)
            {
                deleteFromEnd(menuTail);
                cout << "[X] Deleted dish item (" << tmp->dish.dishID << ") successfully!" << endl;
                break;
            }

            // If it is not the only node but it is the last
            // node to be deleted from the double linked list.
            else if (tmp == menuTail)
            {
                cout << "[X] Deleted dish item (" << tmp->dish.dishID << ") successfully!" << endl;
                tmp->prev->next = NULL;
                tmp->prev = NULL;
                free(tmp);
                break;
            }

            // If it is in the middle of the double linked
            // list.
            else
            {
                tmp->prev->next = tmp->next;
                tmp->next->prev = tmp->prev;
                tmp->next = tmp->prev = NULL;
                cout << "[X] Deleted dish item (" << tmp->dish.dishID << ") successfully!" << endl;
                free(tmp);
                break;
            }
        }

        else
            tmp = tmp->next;
    }

    if (match == 0)
        cout << "[!] No dish with dish ID (" << dishID << ") exists!" << endl;
}

// Function to be called to update a dish item in the menu
void updateDishItem(DishNode*& menuHead, DishNode*& menuTail, string dishID)
{
    DishNode* tmp = menuHead;
    int match = 0;

    while (tmp != NULL)
    {
        if (tmp->dish.dishID == dishID)
        {
            match = 1;
            tmp->dish = updateDish(tmp->dish);
            cout << "[*] Updated dish item (" << dishID << ") successfully!" << endl;
            break;
        }

        else
            tmp = tmp->next;
    }

    if (match == 0)
        cout << "[!] No dish with dish ID (" << dishID << ") exists!" << endl;

    cout << '\n';
}

// Function to retrieve Dish object based on dishID
Dish getDishItem(DishNode* menuHead, DishNode* menuTail, string dishID)
{
    DishNode* tmp = menuHead;
    int match = 0;

    while (tmp != NULL)
    {
        if (tmp->dish.dishID == dishID)
        {
            match = 1;
            return tmp->dish;
        }

        tmp = tmp->next;
    }

    if (match == 0)
    {
        Dish nullDish;
        nullDish.dishID = "N/A";
        cout << "[!] No dish with dish ID (" << dishID << ") exists!" << endl;
        return nullDish;
    }
}

void sortDishes(DishNode* head, DishNode* tail);
// Function to display main menu
void displayMenu(DishNode* menuHead, DishNode* menuTail)
{
    int option = 0;

    if (menuHead == NULL && menuTail == NULL)
    {
        cout << "[!] No dishes are in the menu!" << endl;
        return;
    }

    DishNode* tmp = menuHead;

    cout << fixed;
    cout << setprecision(2);
    cout << "============ Restaurant Menu ============" << endl;
    while (tmp != menuTail)
    {
        cout << "-----------------------------------------" << endl;
        cout << "Item ID: " << tmp->dish.dishID << endl;
        cout << "Item name: " << tmp->dish.name << endl;
        cout << "Item price: RM" << tmp->dish.price << endl;
        cout << "Item calories: " << tmp->dish.calories << "kcal" << endl;
        cout << "Item type: " << ((tmp->dish.type == 1) ? "Ala Carte" : "Set Meal") << endl;
        cout << "-----------------------------------------" << endl;
        cout << "\n" << endl;
        tmp = tmp->next;
    }

    cout << "-----------------------------------------" << endl;
    cout << "Item ID: " << tmp->dish.dishID << endl;
    cout << "Item name: " << tmp->dish.name << endl;
    cout << "Item price: RM" << tmp->dish.price << endl;
    cout << "Item calories: " << tmp->dish.calories << "kcal" << endl;
    cout << "Item type: " << ((tmp->dish.type == 1) ? "Ala Carte" : "Set Meal") << endl;
    cout << "-----------------------------------------" << endl;
    cout << "\n" << endl;

    sortDishes(menuHead, menuTail);
}

// ---------------- Order Linked List Functions ----------------

static int ordersCount;

class Order
{
public:
    string orderID;
    vector<Dish> dishesVec;
    double totalPrice;
};

class OrderNode
{
public:
    Order order;
    OrderNode* next;
    OrderNode* prev;
};

// Function to display dishes that are daily special or promotions
void displaySpecials()
{
    cout << fixed;
    cout << setprecision(2);

    cout << "====================== Daily Special / Promotions ======================" << endl;

    for (auto item : specialsVec)
    {
        cout << "-----------------------------------------" << endl;
        cout << "Item ID: " << item.dishID << endl;
        cout << "Item name: " << item.name << endl;
        cout << "Item price: RM" << item.price << endl;
        cout << "Item calories: " << item.calories << "kcal" << endl;
        cout << "Item type: " << ((item.type == 1) ? "Ala Carte" : "Set Meal") << endl;
        cout << "-----------------------------------------" << endl;
        cout << "\n" << endl;
    }
}

void displayOrderPrompt()
{
    cout << "1. Add more dish items to order" << endl;
    cout << "2. Remove item dish from order" << endl;
    cout << "3. Confirm Order" << endl;
    cout << "> ";
}

// This is a function to create an Order object;
Order createOrder(DishNode* menuHead, DishNode* menuTail)
{
    Order ord;
    Dish dish;
    string dishID;
    int option = 0;

    // The three lines below are to create a string stream
    // that we convert to a normal string. We used this
    // approach to auto increment the orderID everytime an
    // order is created.
    ostringstream oss;
    oss << right << setw(5) << setfill('0') << (ordersCount + 1);
    ord.orderID = "ORD#" + oss.str();
    ordersCount++;

    displayMenu(menuHead, menuTail);

    cout << "Enter dishID to add to order: ";
    cin >> dishID;

    dish = getDishItem(menuHead, menuTail, dishID);

    while (dish.dishID == "N/A")
    {
        displayMenu(menuHead, menuTail);

        cout << "Enter dishID to add to order: ";
        cin >> dishID;

        dish = getDishItem(menuHead, menuTail, dishID);
    }

    ord.dishesVec.push_back(dish);

    displayOrderPrompt();
    cin >> option;
    cout << '\n';

    // while loop for input validation
    while (option != 3)
    {
        while (option < 1 || option > 3)
        {
            cout << "[!] Invalid option!" << endl;
            cout << "Please choose one of the options displayed" << endl;
            displayOrderPrompt();
            cin >> option;
            cout << '\n';
        }

        // User chose option to add another dish item
        // to the order.
        if (option == 1)
        {
            displayMenu(menuHead, menuTail);

            cout << "Enter dishID to add to order: ";
            cin >> dishID;

            dish = getDishItem(menuHead, menuTail, dishID);

            while (dish.dishID == "N/A")
            {
                displayMenu(menuHead, menuTail);

                cout << "Enter dishID to add to order: ";
                cin >> dishID;

                dish = getDishItem(menuHead, menuTail, dishID);
            }

            ord.dishesVec.push_back(dish);
        }

        // User chose option to delete a dish item
        // from the order.
        else
        {
            int match = 0;

            string dishID;
            cout << "Enter item ID to delete: ";
            cin >> dishID;

            auto iter = ord.dishesVec.begin();

            while (iter != ord.dishesVec.end())
            {
                if (iter->dishID == dishID)
                {
                    cout << "[X] Item (" << dishID << ") was removed!" << endl;
                    ord.dishesVec.erase(iter);
                    break;
                }

                iter++;
            }

            if (match == 0)
                cout << "[!] No item with itemID (" << dishID << ") is in the order!" << endl;

            cout << '\n';
        }

        displayOrderPrompt();
        cin >> option;
        cout << '\n';
    }

    cout << fixed;
    cout << setprecision(2);

    // Here we display the order's details
    cout << "=============== Order Details ===============" << endl;
    cout << "Order ID: " << ord.orderID << endl;
    for (auto dish : ord.dishesVec)
    {
        cout << "----------------------------" << endl;
        cout << "Item Name: " << dish.name << endl;
        cout << "Item Price: RM" << dish.price << endl;
        cout << "Item Calories: " << dish.calories << "kcal" << endl;
        cout << "Item Type: " << ((dish.type == 1) ? "Ala Carte" : "Set Meal") << endl;
        cout << "----------------------------" << endl;
        cout << '\n';

        ord.totalPrice += dish.price;
    }

    cout << "Total Price: RM" << ord.totalPrice << endl;
    cout << '\n';

    return ord;
}

// Function to insert an Order node at the beginning of the double linked list
void insertAtBeginning(OrderNode*& head, OrderNode*& tail, OrderNode* n)
{
    head = n;
    tail = n;
}

// Function to insert an Order node at the end of the double linked list
void insertAtEnd(OrderNode*& tail, OrderNode* n)
{
    tail->next = n;
    n->prev = tail;
    tail = n;
}

// Function to delete an Order node from the beginning of the double linked list
void deleteFromBeginning(OrderNode*& head)
{
    OrderNode* n = head;
    head = head->next;
    n->next = n->prev = NULL;
    free(n);
}

// Function to delete an Order node from the end of the double linked list
void deleteFromEnd(OrderNode*& tail)
{
    OrderNode* n = tail;
    tail = tail->prev;
    n->next = n->prev = NULL;
    free(n);
}

// Function to be called to insert an order into the linked list
void insertOrder(OrderNode*& orderHead, OrderNode*& orderTail, Order& order, queue<Order>& ordersQ, stack<Order>& recentOrders)
{
    OrderNode* n = new OrderNode();
    n->order = order;
    n->next = NULL;
    n->prev = NULL;

    if (orderHead == NULL && orderTail == NULL)
    {
        insertAtBeginning(orderHead, orderTail, n);
        cout << "[+] Added order (" << order.orderID << ") successfully!" << endl;
    }

    else
    {
        insertAtEnd(orderTail, n);
        cout << "[+] Added order (" << order.orderID << ") successfully!" << endl;
    }

    ordersQ.push(order);
    recentOrders.push(order);

    cout << '\n';
}

// Function to display the orders that are in queue to be served
void displayOrdersQueue(queue<Order> ordersQ)
{
    cout << "Orders Being Served" << endl;
    cout << "====================================" << endl;

    while (ordersQ.empty() == false)
    {
        cout << ordersQ.front().orderID << endl;
        ordersQ.pop();
    }

    cout << '\n';
}

// Function to display the most recently made orders
void showRecentOrders(stack<Order>& recentOrders, int n)
{
    if (recentOrders.empty() == true)
    {
        cout << "[!] There are no orders made!" << endl;
        cout << '\n';
        return;
    }

    stack<Order> tmpStack = recentOrders;

    // This condition checks if the stack has less
    // orders than the number of recent orders to be 
    // displayed then the set the number of orders 
    // to be displayed equal to the number of elements
    // in the stack.
    if (tmpStack.size() < n)
        n = tmpStack.size();

    // Display all the orders and their details
    for (int i = 0; i < n; i++)
    {
        Order ord = tmpStack.top();
        cout << "=============== Order Details ===============" << endl;
        cout << "Order ID: " << ord.orderID << endl;
        for (auto dish : ord.dishesVec)
        {
            cout << "----------------------------" << endl;
            cout << "Item Name: " << dish.name << endl;
            cout << "Item Price: RM" << dish.price << endl;
            cout << "Item Calories: " << dish.calories << "kcal" << endl;
            cout << "Item Type: " << ((dish.type == 1) ? "Ala Carte" : "Set Meal") << endl;
            cout << "----------------------------" << endl;
            cout << '\n';

            ord.totalPrice += dish.price;
        }

        tmpStack.pop();
    }

    cout << '\n';
}

// ---------------- Search and Sort Functions ----------------
// Function to sort the vector containing the dishes
void bubbleSort(vector<Dish>& v, int op)
{
    // If the op == 1, sort by name
    if (op == 1)
    {
        int n = v.size();
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (v[j].name > v[j + 1].name)
                    swap(v[j], v[j + 1]);
            }
        }
    }

    // If the op == 2, sort by price
    else if (op == 2)
    {
        int n = v.size();
        for (int i = 0; i < n - 1; i++)
        {
            for (int j = 0; j < n - i - 1; j++)
            {
                if (v[j].price > v[j + 1].price)
                    swap(v[j], v[j + 1]);
            }
        }
    }
}

// Function to display the sort prompt menu
void sortPrompt()
{
    cout << "Sort By:" << endl;
    cout << "1. Name" << endl;
    cout << "2. Price" << endl;
    cout << "3. Next" << endl;
    cout << "> ";
}

// Function to display the sorted the dishes
void sortDishes(DishNode* head, DishNode* tail)
{
    vector<Dish> dishesVec;
    int op;

    while (head != tail)
    {
        dishesVec.push_back(head->dish);
        head = head->next;
    }

    dishesVec.push_back(head->dish);

    // Here we call sortPrompt() which asks the user
    // if they want to sort the menu based on name or price.
    sortPrompt();
    cin >> op;
    cout << '\n';

    // while loop for input validation
    while (op != 3)
    {
        while (op != 1 && op != 2)
        {
            cout << "[!] Invalid option, choose an option from the menu" << endl;
            sortPrompt();
            cin >> op;
            cout << '\n';
        }

        switch (op)
        {
        case 1:
            bubbleSort(dishesVec, 1);
            break;

        case 2:
            bubbleSort(dishesVec, 2);
            break;
        }

        // Here we display each dish's details
        cout << "============ Restaurant Menu ============" << endl;
        for (auto dish : dishesVec)
        {
            cout << "-----------------------------------------" << endl;
            cout << "Item ID: " << dish.dishID << endl;
            cout << "Item name: " << dish.name << endl;
            cout << "Item price: RM" << dish.price << endl;
            cout << "Item calories: " << dish.calories << "kcal" << endl;
            cout << "Item type: " << ((dish.type == 1) ? "Ala Carte" : "Set Meal") << endl;
            cout << "-----------------------------------------" << endl;
            cout << "\n" << endl;
        }

        sortPrompt();
        cin >> op;
        cout << '\n';
    }
}

// Function to search a dish using the dish's name
void searchDishes(DishNode* head, DishNode* tail, string name)
{
    vector<Dish> dishesVec;
    vector<Dish> resVec;

    int match = 0;

    if (head == NULL && tail == NULL)
    {
        cout << "[!] There are no dishes in the menu, please add dishes to search!" << endl;
        return;
    }

    while (head != tail)
    {
        dishesVec.push_back(head->dish);
        head = head->next;
    }

    dishesVec.push_back(head->dish);

    for (auto dish : dishesVec)
    {
        // Here we check if each dish's name contains the string
        // name that we supplied as an argument. If the function
        // find does not return string::npos (null value) a dish
        // exists that contains the name provided as an argument.
        if (dish.name.find(name) != string::npos)
        {
            match = 1;
            resVec.push_back(dish);
        }
    }

    if (match == 0)
    {
        cout << "[!] No dish item with name (" << name << ") was found!" << endl;
        cout << '\n';
        return;
    }

    // Here we display all the dishes that had a match.
    cout << "============ Matching Dishes ============" << endl;
    for (auto item : resVec)
    {
        cout << "-----------------------------------------" << endl;
        cout << "Item ID: " << item.dishID << endl;
        cout << "Item name: " << item.name << endl;
        cout << "Item price: RM" << item.price << endl;
        cout << "Item calories: " << item.calories << "kcal" << endl;
        cout << "Item type: " << ((item.type == 1) ? "Ala Carte" : "Set Meal") << endl;
        cout << "-----------------------------------------" << endl;
        cout << "\n" << endl;
    }
}

// ---------------- Misc Functions ----------------
void displayMainPrompt()
{
    cout << "1. Add Dish Items to Menu" << endl;
    cout << "2. Search Dishes" << endl;
    cout << "3. Update Dish Item" << endl;
    cout << "4. Create Order" << endl;
    cout << "5. Display Order Queue" << endl;
    cout << "6. Display Daily Specials/Promotions" << endl;
    cout << "7. Show recent orders" << endl;
    cout << "8. Exit" << endl;
    cout << "> ";
}

int main()
{
    DishNode* menuHead = NULL;
    DishNode* menuTail = NULL;
    OrderNode* orderHead = NULL;
    OrderNode* orderTail = NULL;
    queue<Order> ordersQ;
    stack<Order> recentOrders;

    int option;

    displayMainPrompt();
    cin >> option;
    cout << '\n';

    // while loop for input validation
    while (option != 8)
    {
        if (option == 1)
        {
            Dish dish = createDish();
            insertDishItem(menuHead, menuTail, dish);
        }

        else if (option == 2)
        {
            cin.ignore();
            string name;
            cout << "Enter name of dish: ";
            getline(cin, name);

            searchDishes(menuHead, menuTail, name);
        }

        else if (option == 3)
        {
            string dishID;
            cout << "Enter dishID to be updated: ";
            cin >> dishID;

            updateDishItem(menuHead, menuTail, dishID);
        }

        else if (option == 4)
        {
            Order order = createOrder(menuHead, menuTail);
            insertOrder(orderHead, orderTail, order, ordersQ, recentOrders);
        }

        else if (option == 5)
        {
            displayOrdersQueue(ordersQ);
        }

        else if (option == 6)
        {
            displaySpecials();
        }

        else if (option == 7)
        {
            showRecentOrders(recentOrders, 3);
        }

        else
        {
            cout << "[!] Invalid option, please choose an option from the menu!" << endl;
            displayMainPrompt();
            cin >> option;
            cout << '\n';
        }

        displayMainPrompt();
        cin >> option;
        cout << '\n';
    }
}