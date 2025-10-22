#include "inventory.h"
#include <iostream>


Inventory::Inventory(const Map<std::string, Product> &products) : products_(products), category_index_()
{
    category_index_ = BuildCategoryIndex();
}

Map<std::string, List<Product>> Inventory::BuildCategoryIndex()
{
    Map<std::string, List<Product>> index;
    for (auto &pair : products_)
    {
        const Product &product = pair.Value();
        for (const auto &category : product.Categories())
        {
            List<Product> *products_by_category = index.Find(category);
            if (products_by_category == nullptr)
            {
                List<Product> new_list;
                index.Insert(category, new_list);
                products_by_category = index.Find(category);
            }
            products_by_category->Insert(product);
        }
    }
    return index;
}

Product *Inventory::FindProduct(const std::string &id)
{
    return products_.Find(id);
}

List<Product> Inventory::ListProductsByCategory(const std::string &category)
{
    List<Product> products;
    List<Product> *products_ptr = category_index_.Find(category);
    if (products_ptr != nullptr)
    {
        products = *products_ptr;
    }
    return products;
}