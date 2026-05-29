#ifndef NODES_H
#define NODES_H

#include <memory>
#include <string>
#include <unordered_map>

class INode {
public:
    virtual ~INode() = default;
    virtual const std::string& getName() const = 0;
    virtual int getStockCount() const = 0;
};

class BaseNode : public INode {
protected:
    std::string name;
    int stockCount{0};

public:
    BaseNode(const std::string& n, int count = 0);

    const std::string& getName() const override;
    int getStockCount() const override;
    virtual void addStock(int amount);
};

class ItemNode : public BaseNode {
public:
    ItemNode(const std::string& n, int quantity);
};

class CategoryNode : public BaseNode {
private:
    int articulCount{0};
    std::unordered_map<std::string, std::shared_ptr<CategoryNode>> subcategories;
    std::unordered_map<std::string, std::shared_ptr<ItemNode>> items;

public:
    CategoryNode(const std::string& n);

    void addUniqueItem(int count = 1);
    int getArticulCount() const;
    int getDirectSubcategoryCount() const;

    std::shared_ptr<CategoryNode> getOrAddSubcategory(const std::string& subName);
    void addItem(std::shared_ptr<ItemNode> item);
};

#endif
