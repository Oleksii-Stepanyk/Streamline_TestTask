#include "nodes.h"

BaseNode::BaseNode(const std::string& n, int count) : name(n), stockCount(count) {}

const std::string& BaseNode::getName() const { return name; }
int BaseNode::getStockCount() const { return stockCount; }
void BaseNode::addStock(int amount) { stockCount += amount; }

ItemNode::ItemNode(const std::string& n, int quantity) : BaseNode(n, quantity) {}

CategoryNode::CategoryNode(const std::string& n) : BaseNode(n, 0) {}

void CategoryNode::addUniqueItem(int count) { articulCount += count; }
int CategoryNode::getArticulCount() const { return articulCount; }
int CategoryNode::getDirectSubcategoryCount() const {
    return static_cast<int>(subcategories.size());
}

std::shared_ptr<CategoryNode> CategoryNode::getOrAddSubcategory(const std::string& subName) {
    auto it = subcategories.find(subName);
    if (it == subcategories.end()) {
        auto created = std::make_shared<CategoryNode>(subName);
        it = subcategories.emplace(subName, created).first;
    }
    return it->second;
}

void CategoryNode::addItem(std::shared_ptr<ItemNode> item) {
    items[item->getName()] = item;
}