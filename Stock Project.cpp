//CPP
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class StockItem {
public:
    int id;
    string name;
    string category;
    string subcategory;
    int quantity;
    double price;

    StockItem(int id, string name, string category, string subcategory, int quantity, double price)
        : id(id), name(name), category(category), subcategory(subcategory), quantity(quantity), price(price) {}
};

class StockManagementSystem {
private:
    StockItem** stockItems;
    int capacity;
    int count;

    void resize() {
        capacity *= 2;
        StockItem** newStockItems = new StockItem*[capacity];
        for (int i = 0; i < count; ++i) {
            newStockItems[i] = stockItems[i];
        }
        delete[] stockItems;
        stockItems = newStockItems;
    }

    int findIndexById(int id) {
        for (int i = 0; i < count; ++i) {
            if (stockItems[i]->id == id) {
                return i;
            }
        }
        return -1;
    }

public:
    StockManagementSystem() {
        capacity = 10;
        count = 0;
        stockItems = new StockItem*[capacity];
    }

    ~StockManagementSystem() {
        for (int i = 0; i < count; ++i) {
            delete stockItems[i];
        }
        delete[] stockItems;
    }

    void addStockItem(int id, string name, string category, string subcategory, int quantity, double price) {
        if (quantity <= 0 || price <= 0) {
            cout << "Invalid quantity or price. Both should be positive values." << endl;
            return;
        }

        if (findIndexById(id) != -1) {
            cout << "Item with ID " << id << " already exists." << endl;
            return;
        }
        if (count == capacity) {
            resize();
        }
        stockItems[count++] = new StockItem(id, name, category, subcategory, quantity, price);
        cout << "Item added successfully." << endl;
    }

    void updateStockItem(int id, int quantity, double price) {
        if (quantity <= 0 || price <= 0) {
            cout << "Invalid quantity or price. Both should be positive values." << endl;
            return;
        }

        int index = findIndexById(id);
        if (index == -1) {
            cout << "Item with ID " << id << " not found." << endl;
            return;
        }
        stockItems[index]->quantity = quantity;
        stockItems[index]->price = price;
        cout << "Item updated successfully." << endl;
    }

    void deleteStockItem(int id) {
        int index = findIndexById(id);
        if (index == -1) {
            cout << "Item with ID " << id << " not found." << endl;
            return;
        }
        delete stockItems[index];
        for (int i = index; i < count - 1; ++i) {
            stockItems[i] = stockItems[i + 1];
        }
        --count;
        cout << "Item deleted successfully." << endl;
    }

    void viewAllStockItems() {
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Category" << setw(15) << "Subcategory" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
        for (int i = 0; i < count; ++i) {
            cout << left << setw(10) << stockItems[i]->id << setw(20) << stockItems[i]->name << setw(15) << stockItems[i]->category << setw(15) << stockItems[i]->subcategory << setw(10) << stockItems[i]->quantity << setw(10) << stockItems[i]->price << endl;
        }
    }

    void searchStockItemsByCategory(string category, string subcategory) {
        cout << "Search results for Category: " << category << ", Subcategory: " << subcategory << endl;
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Category" << setw(15) << "Subcategory" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
        for (int i = 0; i < count; ++i) {
            if (stockItems[i]->category == category && stockItems[i]->subcategory == subcategory) {
                cout << left << setw(10) << stockItems[i]->id << setw(20) << stockItems[i]->name << setw(15) << stockItems[i]->category << setw(15) << stockItems[i]->subcategory << setw(10) << stockItems[i]->quantity << setw(10) << stockItems[i]->price << endl;
            }
        }
    }

    void alertLowStockItems(int threshold) {
        cout << "Low stock items (Threshold: " << threshold << ")" << endl;
        cout << left << setw(10) << "ID" << setw(20) << "Name" << setw(15) << "Category" << setw(15) << "Subcategory" << setw(10) << "Quantity" << setw(10) << "Price" << endl;
        for (int i = 0; i < count; ++i) {
            if (stockItems[i]->quantity < threshold) {
                cout << left << setw(10) << stockItems[i]->id << setw(20) << stockItems[i]->name << setw(15) << stockItems[i]->category << setw(15) << stockItems[i]->subcategory << setw(10) << stockItems[i]->quantity << setw(10) << stockItems[i]->price << endl;
            }
        }
    }

    void viewStockTrends() {
        cout << "Stock Trends and Analysis" << endl;
        int totalItems = 0;
        double totalValue = 0.0;
        for (int i = 0; i < count; ++i) {
            totalItems += stockItems[i]->quantity;
            totalValue += stockItems[i]->quantity * stockItems[i]->price;
        }
        cout << "Total Items in Stock: " << totalItems << endl;
        cout << "Total Stock Value: $" << totalValue << endl;
    }
};

void displayMenu() {
    cout << "Stock Management System" << endl;
    cout << "1. Add Stock Item" << endl;
    cout << "2. Update Stock Item" << endl;
    cout << "3. Delete Stock Item" << endl;
    cout << "4. View All Stock Items" << endl;
    cout << "5. Search Stock Items by Category" << endl;
    cout << "6. Alert for Low Stock Items" << endl;
    cout << "7. View Stock Trends and Analysis" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    StockManagementSystem sms;
    int choice, id, quantity, threshold;
    string name, category, subcategory;
    double price;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Category: ";
            getline(cin, category);
            cout << "Enter Subcategory: ";
            getline(cin, subcategory);
            cout << "Enter Quantity: ";
            cin >> quantity;
            cout << "Enter Price: ";
            cin >> price;
            sms.addStockItem(id, name, category, subcategory, quantity, price);
            break;
        case 2:
            cout << "Enter ID: ";
            cin >> id;
            cout << "Enter New Quantity: ";
            cin >> quantity;
            cout << "Enter New Price: ";
            cin >> price;
            sms.updateStockItem(id, quantity, price);
            break;
        case 3:
            cout << "Enter ID: ";
            cin >> id;
            sms.deleteStockItem(id);
            break;
        case 4:
            sms.viewAllStockItems();
            break;
        case 5:
            cout << "Enter Category: ";
            cin.ignore();
            getline(cin, category);
            cout << "Enter Subcategory: ";
            getline(cin, subcategory);
            sms.searchStockItemsByCategory(category, subcategory);
            break;
        case 6:
            cout << "Enter Low Stock Threshold: ";
            cin >> threshold;
            sms.alertLowStockItems(threshold);
            break;
        case 7:
            sms.viewStockTrends();
            break;
        case 8:
            cout << "Exiting..." << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
