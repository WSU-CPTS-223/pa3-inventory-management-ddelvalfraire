#if !defined(INVENTORY_H_PA3)
#define INVENTORY_H_PA3

#include "list.h"
#include "product.h"

class Inventory
{
private:
    Map<std::string, Product> products_;
    Map<std::string, List<Product>> category_index_;

    Map<std::string, List<Product>> BuildCategoryIndex();

public:
    Inventory(const Map<std::string, Product> &products);

    Product *FindProduct(const std::string &id);

    List<Product> ListProductsByCategory(const std::string &category);
};

#endif // INVENTORY_H_PA3
