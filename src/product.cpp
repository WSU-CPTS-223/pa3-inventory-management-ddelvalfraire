#include "product.h"
#include "parser.h"

Product::Product(const Map<std::string, std::string> &fieldMap)
{
    auto get_value = [&fieldMap](const std::string &key) -> std::string
    {
        const std::string *value = fieldMap.Find(key);
        return (value != nullptr) ? *value : "N/A";
    };

    uniq_id_ = get_value("Uniq Id");
    product_name_ = get_value("Product Name");
    brand_name_ = get_value("Brand Name");
    asin_ = get_value("Asin");

    std::string categoryStr = get_value("Category");
    categories_ = parser::SplitLine(categoryStr, '|');

    upc_ean_code_ = get_value("Upc Ean Code");
    list_price_ = get_value("List Price");
    selling_price_ = get_value("Selling Price");
    quantity_ = get_value("Quantity");
    model_number_ = get_value("Model Number");
    about_product_ = get_value("About Product");
    product_specification_ = get_value("Product Specification");
    technical_details_ = get_value("Technical Details");
    shipping_weight_ = get_value("Shipping Weight");
    product_dimensions_ = get_value("Product Dimensions");
    image_ = get_value("Image");
    variants_ = get_value("Variants");
    sku_ = get_value("Sku");
    product_url_ = get_value("Product Url");
    stock_ = get_value("Stock");
    product_details_ = get_value("Product Details");
    dimensions_ = get_value("Dimensions");
    color_ = get_value("Color");
    ingredients_ = get_value("Ingredients");
    direction_to_use_ = get_value("Direction To Use");
    is_amazon_seller_ = get_value("Is Amazon Seller");
    size_quantity_variant_ = get_value("Size Quantity Variant");
    product_description_ = get_value("Product Description");
}

std::string Product::UniqId() const
{
    return uniq_id_;
}

void Product::SetUniqId(const std::string &uniq_id)
{
    uniq_id_ = uniq_id;
}

std::string Product::ProductName() const
{
    return product_name_;
}

void Product::SetProductName(const std::string &product_name)
{
    product_name_ = product_name;
}

std::string Product::BrandName() const
{
    return brand_name_;
}

void Product::SetBrandName(const std::string &brand_name)
{
    brand_name_ = brand_name;
}

std::string Product::Asin() const
{
    return asin_;
}

void Product::SetAsin(const std::string &asin)
{
    asin_ = asin;
}

const List<std::string> &Product::Categories() const
{
    return categories_;
}

void Product::SetCategories(const List<std::string> &categories)
{
    categories_ = categories;
}

std::string Product::UpcEanCode() const
{
    return upc_ean_code_;
}

void Product::SetUpcEanCode(const std::string &upc_ean_code)
{
    upc_ean_code_ = upc_ean_code;
}

std::string Product::ListPrice() const
{
    return list_price_;
}

void Product::SetListPrice(const std::string &list_price)
{
    list_price_ = list_price;
}

std::string Product::SellingPrice() const
{
    return selling_price_;
}

void Product::SetSellingPrice(const std::string &selling_price)
{
    selling_price_ = selling_price;
}

std::string Product::Quantity() const
{
    return quantity_;
}

void Product::SetQuantity(const std::string &quantity)
{
    quantity_ = quantity;
}

std::string Product::ModelNumber() const
{
    return model_number_;
}

void Product::SetModelNumber(const std::string &model_number)
{
    model_number_ = model_number;
}

std::string Product::AboutProduct() const
{
    return about_product_;
}

void Product::SetAboutProduct(const std::string &about_product)
{
    about_product_ = about_product;
}

std::string Product::ProductSpecification() const
{
    return product_specification_;
}

void Product::SetProductSpecification(const std::string &product_specification)
{
    product_specification_ = product_specification;
}

std::string Product::TechnicalDetails() const
{
    return technical_details_;
}

void Product::SetTechnicalDetails(const std::string &technical_details)
{
    technical_details_ = technical_details;
}

std::string Product::ShippingWeight() const
{
    return shipping_weight_;
}

void Product::SetShippingWeight(const std::string &shipping_weight)
{
    shipping_weight_ = shipping_weight;
}

std::string Product::ProductDimensions() const
{
    return product_dimensions_;
}

void Product::SetProductDimensions(const std::string &product_dimensions)
{
    product_dimensions_ = product_dimensions;
}

std::string Product::Image() const
{
    return image_;
}

void Product::SetImage(const std::string &image)
{
    image_ = image;
}

std::string Product::Variants() const
{
    return variants_;
}

void Product::SetVariants(const std::string &variants)
{
    variants_ = variants;
}

std::string Product::Sku() const
{
    return sku_;
}

void Product::SetSku(const std::string &sku)
{
    sku_ = sku;
}

std::string Product::ProductUrl() const
{
    return product_url_;
}

void Product::SetProductUrl(const std::string &product_url)
{
    product_url_ = product_url;
}

std::string Product::Stock() const
{
    return stock_;
}

void Product::SetStock(const std::string &stock)
{
    stock_ = stock;
}

std::string Product::ProductDetails() const
{
    return product_details_;
}

void Product::SetProductDetails(const std::string &product_details)
{
    product_details_ = product_details;
}

std::string Product::Dimensions() const
{
    return dimensions_;
}

void Product::SetDimensions(const std::string &dimensions)
{
    dimensions_ = dimensions;
}

std::string Product::Color() const
{
    return color_;
}

void Product::SetColor(const std::string &color)
{
    color_ = color;
}

std::string Product::Ingredients() const
{
    return ingredients_;
}

void Product::SetIngredients(const std::string &ingredients)
{
    ingredients_ = ingredients;
}

std::string Product::DirectionToUse() const
{
    return direction_to_use_;
}

void Product::SetDirectionToUse(const std::string &direction_to_use)
{
    direction_to_use_ = direction_to_use;
}

std::string Product::IsAmazonSeller() const
{
    return is_amazon_seller_;
}

void Product::SetIsAmazonSeller(const std::string &is_amazon_seller)
{
    is_amazon_seller_ = is_amazon_seller;
}

std::string Product::SizeQuantityVariant() const
{
    return size_quantity_variant_;
}

void Product::SetSizeQuantityVariant(const std::string &size_quantity_variant)
{
    size_quantity_variant_ = size_quantity_variant;
}

std::string Product::ProductDescription() const
{
    return product_description_;
}

void Product::SetProductDescription(const std::string &product_description)
{
    product_description_ = product_description;
}
