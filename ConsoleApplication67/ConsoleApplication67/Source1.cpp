#include<string>
class Client {
private:
    std::string firstName; 
    std::string lastName; 
    std::string passportData; 
    std::string address;

public:
 
    Client(const std::string& firstName, const std::string& lastName,
        const std::string& passportData = "", const std::string& address = "")
        : firstName(firstName), lastName(lastName),
        passportData(passportData), address(address) {
    }

    
    std::string getFullName() const {
        return firstName + " " + lastName;
    }
};