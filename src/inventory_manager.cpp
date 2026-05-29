#include "inventory_manager.h"

InventoryManager::InventoryManager() {
    root = std::make_shared<CategoryNode>("All items");
    categoryRegistry["All items"] = root;
}

void InventoryManager::buildTree(const std::vector<ParsedRow>& data) {
    for (const auto& row : data) {
        auto item = std::make_shared<ItemNode>(row.itemName, row.quantity);
        itemRegistry[row.itemName] = item;

        root->addStock(row.quantity);
        root->addUniqueItem(1);

        std::shared_ptr<CategoryNode> currentCat = root;

        for (auto it = row.categories.rbegin(); it != row.categories.rend(); ++it) {
            std::string catName = *it;

            auto nextCat = currentCat->getOrAddSubcategory(catName);
            categoryRegistry[catName] = nextCat;

            nextCat->addStock(row.quantity);
            nextCat->addUniqueItem(1);

            currentCat = nextCat;
        }

        currentCat->addItem(item);
    }
}

int InventoryManager::getItemQuantity(const std::string& name) const {
    auto it = itemRegistry.find(name);
    return it != itemRegistry.end() ? it->second->getStockCount() : 0;
}

int InventoryManager::getCategoryQuantity(const std::string& name) const {
    auto it = categoryRegistry.find(name);
    return it != categoryRegistry.end() ? it->second->getStockCount() : 0;
}

int InventoryManager::getTotalWarehouseQuantity() const {
    return root->getStockCount();
}

int InventoryManager::getCategoryUniqueItems(const std::string& name) const {
    auto it = categoryRegistry.find(name);
    return it != categoryRegistry.end() ? it->second->getArticulCount() : 0;
}

int InventoryManager::getDirectSubcategoryCount(const std::string& name) const {
    auto it = categoryRegistry.find(name);
    return it != categoryRegistry.end() ? it->second->getDirectSubcategoryCount() : 0;
}