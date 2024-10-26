#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

// Define a structure to hold the seller information
struct Seller {
    std::string lastName;
    std::string firstName;
    int id;
    std::string phone;
    double totalSales;
    double salesPercent;
};

// Function to print the header
const int LINE_WIDTH = 75;
const int NAME_WIDTH = 14;
const int ID_WIDTH = 14;
const int PHONE_WIDTH = 14;
const int SALES_WIDTH = 10;
void printHeader(const std::string &region)
{
    std::cout << std::setw((LINE_WIDTH + region.size()) / 2) << std::right << region << "\n\n";
    std::cout << std::string(LINE_WIDTH, '-') << "\n\n";
    std::cout << std::left << std::setw(NAME_WIDTH) << "*Last Name*" << std::setw(NAME_WIDTH)
              << "*First Name*" << std::setw(ID_WIDTH) << "*ID*" << std::setw(PHONE_WIDTH)
              << "*Phone*" << std::setw(SALES_WIDTH) << "*Sales*" << "*Percent*\n"
              << std::endl;
}

// Function to print the seller information
void printSeller(const Seller &seller)
{
    // std::cout.imbue(std::locale("en_US.utf8"));
    std::cout << std::setw(NAME_WIDTH) << seller.lastName << std::setw(NAME_WIDTH)
              << seller.firstName << std::setw(ID_WIDTH) << seller.id << std::setw(PHONE_WIDTH)
              << seller.phone << std::setw(10) << std::fixed << std::setprecision(2)
              << seller.totalSales << std::scientific << std::setprecision(2) << seller.salesPercent
              << "\n";
}

int main()
{
    std::ifstream file("Exercise15.txt");
    std::string line, region;
    std::vector<Seller> sellers;

    if (!file.is_open()) {
        std::cerr << "Error opening file\n";
        return 1;
    }

    while (getline(file, line)) {
        if (line.find("//") != std::string::npos) {
            continue;
        }

        if (line.find(',') == std::string::npos) { // This is a region line
            if (!region.empty()) {                 // Print previous region's sellers
                printHeader(region);
                for (const auto &seller : sellers) {
                    printSeller(seller);
                }
                sellers.clear();
                std::cout << std::endl;
            }
            region = line;
        } else {
            Seller seller;
            std::istringstream iss(line);
            std::string token;
            // ID
            char drop;
            iss >> std::hex >> seller.id >> drop;
            // PHONE_NUMBER
            std::getline(iss, token, ',');
            seller.phone = token;
            std::getline(iss, seller.lastName, ',');  // LAST_NAME
            std::getline(iss, seller.firstName, ','); // FIRST_NAME
            std::getline(iss, token, ',');            // TOTAL_SALES
            seller.totalSales = std::stod(token);
            std::getline(iss, token, ','); // PERCENT
            seller.salesPercent = std::stod(token);
            sellers.push_back(seller);
        }
    }

    // // Print the last region's sellers
    printHeader(region);
    for (const auto &seller : sellers) {
        printSeller(seller);
    }

    file.close();
    return 0;
}
