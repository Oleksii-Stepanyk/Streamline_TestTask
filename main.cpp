#include <chrono>
#include <iostream>
#include <string>

#include "csv_parser.h"
#include "inventory_manager.h"

void displayMenu() {
    std::cout << "\n--- Inventory Management System ---\n";
    std::cout << "1. Get specific item quantity\n";
    std::cout << "2. Get total items in a category\n";
    std::cout << "3. Get total items in warehouse\n";
    std::cout << "4. Get unique item count in a category\n";
    std::cout << "5. Get direct subcategory count\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter your choice: ";
}

int main(int argc, char* argv[]) {
    std::string filename;

    if (argc > 1) {
        filename = argv[1];
    } else {
        std::cout << "Usage: " << argv[0] << " <path_to_csv_file>\n";
        std::cout << "No file provided. Defaulting to 'large_inventory.csv'...\n\n";
        filename = "large_inventory.csv";
    }
    
    std::cout << "Starting system boot sequence...\n";
    auto startBoot = std::chrono::high_resolution_clock::now();

    std::cout << "Reading " << filename << " from disk..." << std::endl;
    auto data = CSVParser::parseCSVFile(filename);
    if (data.empty()) {
        std::cerr << "CRITICAL: No data loaded. Please check the file path.\n";
        return 1;
    }

    InventoryManager manager;
    std::cout << "Building registry and dependency tree..." << std::endl;
    manager.buildTree(data);

    auto endBoot = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> bootTime = endBoot - startBoot;
    
    std::cout << "\n============================================\n";
    std::cout << "[SUCCESS] Boot sequence complete.\n";
    std::cout << "Total Rows Processed: " << data.size() << "\n";
    std::cout << "Total Boot Time: " << bootTime.count() << " seconds.\n";
    std::cout << "============================================\n";

    int choice;
    std::string input;

    while (true) {
        displayMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        std::cin.ignore();

        if (choice == 0) break;

        auto startQuery = std::chrono::high_resolution_clock::now();
        int result = 0;

        switch (choice) {
            case 1:
                std::cout << "Enter exact item name (e.g., item_0000001): ";
                std::getline(std::cin, input);
                startQuery = std::chrono::high_resolution_clock::now();
                result = manager.getItemQuantity(input);
                std::cout << "\nResult: Quantity for '" << input << "' is " << result << "\n";
                break;
            case 2:
                std::cout << "Enter exact category name (e.g., Clothes): ";
                std::getline(std::cin, input);
                startQuery = std::chrono::high_resolution_clock::now();
                result = manager.getCategoryQuantity(input);
                std::cout << "\nResult: Total items in '" << input << "' is " << result << "\n";
                break;
            case 3:
                startQuery = std::chrono::high_resolution_clock::now();
                result = manager.getTotalWarehouseQuantity();
                std::cout << "\nResult: Total warehouse quantity is " << result << "\n";
                break;
            case 4:
                std::cout << "Enter exact category name (e.g., Boots): ";
                std::getline(std::cin, input);
                startQuery = std::chrono::high_resolution_clock::now();
                result = manager.getCategoryUniqueItems(input);
                std::cout << "\nResult: Unique articul count in '" << input << "' is " << result << "\n";
                break;
            case 5:
                std::cout << "Enter exact category name (e.g., All items): ";
                std::getline(std::cin, input);
                startQuery = std::chrono::high_resolution_clock::now();
                result = manager.getDirectSubcategoryCount(input);
                std::cout << "\nResult: Direct subcategories of '" << input << "' is " << result << "\n";
                break;
            default:
                std::cout << "Invalid choice.\n";
                continue;
        }

        auto endQuery = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> queryTime = endQuery - startQuery;
        
        std::cout << "[Query executed in: " << queryTime.count() << " ms]\n";
    }

    std::cout << "Shutting down system. Goodbye.\n";
    return 0;
}