#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "csv_parser.h"
#include "nodes.h"

class InventoryManager {
private:
    std::shared_ptr<CategoryNode> root;
    std::unordered_map<std::string, std::shared_ptr<ItemNode>> itemRegistry;
    std::unordered_map<std::string, std::shared_ptr<CategoryNode>> categoryRegistry;

public:
    InventoryManager();

    void buildTree(const std::vector<ParsedRow>& data);

    int getItemQuantity(const std::string& name) const;
    int getCategoryQuantity(const std::string& name) const;
    int getTotalWarehouseQuantity() const;
    int getCategoryUniqueItems(const std::string& name) const;
    int getDirectSubcategoryCount(const std::string& name) const;
};

#endif
