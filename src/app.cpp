#include "app.h"
#include "parser.h"

#include <sstream>
#include <iostream>
#include <iomanip>

constexpr size_t MAX_COL_WIDTH = 70;
constexpr size_t COL_PADDING = 4;

App::App() : inventory_(Map<std::string, Product>()) {}
App::~App() {}

void App::PrintHelp()
{
    std::cout << "Supported list of commands: " << std::endl;
    std::cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << std::endl;
    std::cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
              << std::endl;
    std::cout << " Use :quit to quit the REPL" << std::endl;
}

List<size_t> GetColumnWidths(const List<Map<std::string, std::string>> &rows, const List<std::string> &headers)
{
    List<size_t> widths;
    for (const auto &header : headers)
    {
        size_t width = header.size();
        for (const auto &row : rows)
        {
            auto value_at_header = row[header];
            if (value_at_header != nullptr)
                width = std::max(width, std::min(MAX_COL_WIDTH, value_at_header->size()));
        }
        widths.Insert(std::min(MAX_COL_WIDTH, width));
    }
    return widths;
}

void DisplayHeader(const List<std::string> &headers, const List<size_t> &widths)
{
    for (size_t i = 0; i < headers.Size(); i++)
    {
        std::string header = headers[i];
        if (header.size() > widths[i])
            header = header.substr(0, widths[i] - 3) + "...";

        std::cout << std::left << std::setw(widths[i] + COL_PADDING) << header;
    }
    std::cout << std::endl;
}

void DisplaySeperators(const List<std::string> &headers, const List<size_t> &widths)
{
    for (size_t i = 0; i < headers.Size(); i++)
    {
        std::cout << std::string(widths[i] + COL_PADDING, '-');
        if (i < headers.Size() - 1)
            std::cout << "-+-";
    }
    std::cout << std::endl;
}

void DisplayRows(const List<std::string> &headers, const List<size_t> &widths, const List<Map<std::string, std::string>> &rows)
{
    for (size_t i = 0; i < rows.Size(); i++)
    {
        for (size_t j = 0; j < headers.Size(); j++)
        {
            const std::string *value = rows[i].Find(headers[j]);
            std::string display = value ? *value : "";

            if (display.size() > widths[j])
                display = display.substr(0, widths[j] - 3) + "...";

            std::cout << std::left << std::setw(widths[j] + COL_PADDING) << display;
            if (j < headers.Size() - 1)
                std::cout << " | ";
        }
        std::cout << std::endl;
    }
}
void DisplayTable(const List<Map<std::string, std::string>> &rows, const List<std::string> &headers)
{

    std::cout << std::endl
              << "\tProduct names longer than " << MAX_COL_WIDTH << " characters are truncated." << std::endl;

    auto widths = GetColumnWidths(rows, headers);

    DisplayHeader(headers, widths);
    DisplaySeperators(headers, widths);

    DisplayRows(headers, widths, rows);
}

bool App::ValidCommand(const std::string &line)
{
    std::istringstream iss(line);
    std::string command;
    iss >> command;

    const Map<std::string, int> valid_commands =  {
        {":help", 0},
        {"find", 0},
        {"listInventory", 0}
    };

    return valid_commands.Find(command) != nullptr;
}

void App::HandleFindCommand(std::istringstream &iss)
{
    std::string id;
    iss >> id;
    if (id.empty())
    {
        std::cout << "Error: No ID provided for find command." << std::endl;
        return;
    }

    Product *product = inventory_.FindProduct(id);
    if (product == nullptr)
    {
        std::cout << "Product not found" << std::endl;
        return;
    }

    List<Map<std::string, std::string>> rows;

    rows.Insert({{"ID", product->UniqId()},
                 {"Name", product->ProductName()}});

    DisplayTable(rows, {"ID", "Name"});
}

std::string App::ReadListInventoryArgument(std::istringstream &iss)
{
    std::string category;
    iss >> std::ws;

    if (iss.peek() == '"')
    {
        iss.get();
        std::getline(iss, category, '"');
        category = parser::StripLine(category);
    }
    else
    {
        std::getline(iss, category);
        category = parser::StripLine(category);
    }
    return category;
}

void App::HandleListInventoryCommand(std::istringstream &iss)
{
    auto category = ReadListInventoryArgument(iss);

    List<Product> products = inventory_.ListProductsByCategory(category);
    if (products.size() == 0)
    {
        std::cout << "Category is empty" << std::endl;
    }
    else
    {
        List<Map<std::string, std::string>> rows;
        for (const auto &product : products)
        {
            rows.Insert({{"ID", product.UniqId()},
                         {"Name", product.ProductName()}});
        }
        DisplayTable(rows, {"ID", "Name"});
    }
}
void App::EvalCommand(const std::string &line)
{
    std::istringstream iss(line);
    std::string command;
    iss >> command;

    if (command == ":help")
        PrintHelp();
    else if (command == "find")
        HandleFindCommand(iss);
    else if (command == "listInventory")
        HandleListInventoryCommand(iss);
}

void App::BootStrap()
{
    const auto products_data = "data/marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data.csv";

    const auto products = parser::ReadCsv(products_data);

    Map<std::string, Product> products_by_id;

    for (const auto &product_map : products)
    {
        Product product(product_map);
        products_by_id.Insert(product.UniqId(), product);
    }

    inventory_ = Inventory(products_by_id);

    std::cout << "\n Welcome to Amazon Inventory Query System" << std::endl;
    std::cout << " enter :quit to exit. or :help to list supported commands." << std::endl;
    std::cout << "\n> ";
}

void App::Run()
{
    std::string line;
    BootStrap();
    while (getline(std::cin, line) && line != ":quit")
    {
        if (ValidCommand(line))
        {
            EvalCommand(line);
        }
        else
        {
            std::cout << "Command not supported. Enter :help for list of supported commands" << std::endl;
        }
        std::cout << "> ";
    }
}
