#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include "list.h"
#include "map.h"
class Product
{
private:
    std::string uniq_id_;
    std::string product_name_;
    std::string brand_name_;
    std::string asin_;
    List<std::string> categories_;
    std::string upc_ean_code_;
    std::string list_price_;
    std::string selling_price_;
    std::string quantity_;
    std::string model_number_;
    std::string about_product_;
    std::string product_specification_;
    std::string technical_details_;
    std::string shipping_weight_;
    std::string product_dimensions_;
    std::string image_;
    std::string variants_;
    std::string sku_;
    std::string product_url_;
    std::string stock_;
    std::string product_details_;
    std::string dimensions_;
    std::string color_;
    std::string ingredients_;
    std::string direction_to_use_;
    std::string is_amazon_seller_;
    std::string size_quantity_variant_;
    std::string product_description_;

public:
    Product() = default;
    Product(const Map<std::string, std::string> &fieldMap);

    std::string UniqId() const;
    void SetUniqId(const std::string &uniq_id);

    std::string ProductName() const;
    void SetProductName(const std::string &product_name);

    std::string BrandName() const;
    void SetBrandName(const std::string &brand_name);

    std::string Asin() const;
    void SetAsin(const std::string &asin);

    const List<std::string> &Categories() const;
    void SetCategories(const List<std::string> &categories);

    std::string UpcEanCode() const;
    void SetUpcEanCode(const std::string &upc_ean_code);

    std::string ListPrice() const;
    void SetListPrice(const std::string &list_price);

    std::string SellingPrice() const;
    void SetSellingPrice(const std::string &selling_price);

    std::string Quantity() const;
    void SetQuantity(const std::string &quantity);

    std::string ModelNumber() const;
    void SetModelNumber(const std::string &model_number);

    std::string AboutProduct() const;
    void SetAboutProduct(const std::string &about_product);

    std::string ProductSpecification() const;
    void SetProductSpecification(const std::string &product_specification);

    std::string TechnicalDetails() const;
    void SetTechnicalDetails(const std::string &technical_details);

    std::string ShippingWeight() const;
    void SetShippingWeight(const std::string &shipping_weight);

    std::string ProductDimensions() const;
    void SetProductDimensions(const std::string &product_dimensions);

    std::string Image() const;
    void SetImage(const std::string &image);

    std::string Variants() const;
    void SetVariants(const std::string &variants);

    std::string Sku() const;
    void SetSku(const std::string &sku);

    std::string ProductUrl() const;
    void SetProductUrl(const std::string &product_url);

    std::string Stock() const;
    void SetStock(const std::string &stock);

    std::string ProductDetails() const;
    void SetProductDetails(const std::string &product_details);

    std::string Dimensions() const;
    void SetDimensions(const std::string &dimensions);

    std::string Color() const;
    void SetColor(const std::string &color);

    std::string Ingredients() const;
    void SetIngredients(const std::string &ingredients);

    std::string DirectionToUse() const;
    void SetDirectionToUse(const std::string &direction_to_use);

    std::string IsAmazonSeller() const;
    void SetIsAmazonSeller(const std::string &is_amazon_seller);

    std::string SizeQuantityVariant() const;
    void SetSizeQuantityVariant(const std::string &size_quantity_variant);

    std::string ProductDescription() const;
    void SetProductDescription(const std::string &product_description);
};

#endif