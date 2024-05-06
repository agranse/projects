#include "Singleton.h"

using namespace std;

Singleton::Singleton() {}

Singleton* Singleton::instance = nullptr;

Singleton* Singleton::getInstance() {
    if (instance == nullptr) {
        instance = new Singleton();
    }
    return instance;
}

void Singleton::increaseNumPackages() {
    numPackages++;
}

void Singleton::increaseNumDeliveries() {
    numDeliveries++;
}

void Singleton::pushNumPackageMiles(std::string line) {
    packageMiles.push_back(line);
}

void Singleton::outputData() {
    ofstream fp;
    fp.open("dataTesting.csv");
    fp << "Drone, Miles, PackageName, Strategy, Status\n";
    for (string s : packageMiles) {
        fp << s << "\n";
    }
    fp.close();
}
