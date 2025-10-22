#if !defined(APP_H_PA3)
#define APP_H_PA3

#include "inventory.h"

class App
{
private:
    Inventory inventory_;
    void PrintHelp();
    bool ValidCommand(const std::string &line);
    void HandleFindCommand(std::istringstream &iss);
    std::string ReadListInventoryArgument(std::istringstream &iss);
    void HandleListInventoryCommand(std::istringstream &iss);
    void EvalCommand(const std::string &line);
    void BootStrap();

public:
    App();
    ~App();

    void Run();
};

#endif // APP_H_PA3
