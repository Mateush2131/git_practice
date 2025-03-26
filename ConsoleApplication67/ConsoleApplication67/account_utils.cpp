#include<string>
#include <random> 

std::string generateAccountId() {
    static std::random_device rd; 
    static std::mt19937 gen(rd()); 
    static std::uniform_int_distribution<> dis(1000, 9999); 

    return "ACC" + std::to_string(dis(gen)); 
}