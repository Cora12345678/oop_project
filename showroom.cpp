#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <cstdlib>
#include <unordered_map>

using namespace std;

// Class definitions...

class Car
{
private:
    string modelNo, carName, quality, color, company, transmission;
    double batteryCapacity;

public:
    Car(const string &model, const string &name, const string &qual, const string &col, const string &com, const string &trans, double capacity)
        : modelNo(model), carName(name), quality(qual), color(col), company(com), transmission(trans), batteryCapacity(capacity) {}

    // Getter functions...

    const string &getModelNo() const { return modelNo; }
    const string &getCarName() const { return carName; }
    const string &getQuality() const { return quality; }
    const string &getcolor() const { return color; }
    const string &getcompany() const { return company; }
    const string &gettransmission() const { return transmission; }
    double getBatteryCapacity() const { return batteryCapacity; }

    void setBatteryCapacity(double newCapacity)
    {
        batteryCapacity = newCapacity;
    }
};

class Sign_up
{
private:
    string username;
    string password;
    string email;

public:
    Sign_up(const string &name, const string &p, const string &e)
        : username(name), password(p), email(e) {}

    const string &getUsername() const
    {
        return username;
    }

    const string &getPassword() const
    {
        return password;
    }

    const string &getEmail() const
    {
        return email;
    }

    void setPassword(const string &newPwd)
    {
        password = newPwd;
    }
};

class record_cars
{
private:
    static const int MAX_SHOWROOM_CAPACITY = 100;
    int totalCars;
    unordered_map<string, int> carsPerCompany;
    unordered_map<string, int> carsPerCompanyName; // New map for cars per company name

public:
    vector<Car> cars;

    record_cars() : totalCars(0)
    {
        // Load existing car data from the file to initialize totalCars
        loadExistingCarData();
    }

    void updateBatteryCapacity(const string &modelNo, double newCapacity)
    {
        for (auto &car : cars)
        {
            if (car.getModelNo() == modelNo)
            {
                car.setBatteryCapacity(newCapacity);
                break;
            }
        }

        // Update statistics and save the updated car data to the file
        updateStatistics();
        saveCarData();

        // Reload the existing car data to reflect the changes
        loadExistingCarData();
    }

    // Function to load existing car data from the file
    void loadExistingCarData()
    {
        if (!cars.empty())
        {
            // If the cars vector is not empty, it means the data is already loaded
            cout << "Car data is already loaded." << endl;
            return;
        }

        ifstream carFile("car_data.txt");
        string carLine;

        totalCars = 0; // Reset totalCars count

        while (getline(carFile, carLine))
        {
            totalCars++;
        }

        carFile.close();
    }

    // Add a new car to the showroom
    Car &addCar(const Car &car)
    {
        if (totalCars >= MAX_SHOWROOM_CAPACITY)
        {
            cout << "Sorry, the showroom is full. No more cars can be added. :( " << endl;
            // Return a reference to the first car in the vector (dummy reference)
            return cars[0];
        }

        totalCars++;

        if (carsPerCompany.find(car.getCarName()) != carsPerCompany.end())
        {
            carsPerCompany[car.getCarName()]++;
        }
        else
        {
            carsPerCompany[car.getCarName()] = 1;
        }

        cars.push_back(car);
        cout << "Car added successfully to the showroom. :) " << endl;

        // Update the statistics and save the updated car data to the file
        updateStatistics();
        saveCarData();

        // Reload the existing car data to reflect the changes
        loadExistingCarData();

        // Return a reference to the added car
        return cars.back();
    }

    void updateStatistics()
    {
        // Reset statistics
        carsPerCompany.clear();
        carsPerCompanyName.clear();

        for (const auto &car : cars)
        {
            if (carsPerCompany.find(car.getCarName()) != carsPerCompany.end())
            {
                carsPerCompany[car.getCarName()]++;
            }
            else
            {
                carsPerCompany[car.getCarName()] = 1;
            }

            // Update cars per company name
            if (carsPerCompanyName.find(car.getCarName()) != carsPerCompanyName.end())
            {
                carsPerCompanyName[car.getCarName()]++;
            }
            else
            {
                carsPerCompanyName[car.getCarName()] = 1;
            }
        }
    }
    void displayStatistics() const
    {
        cout << endl
             << endl
             << endl;
        cout << "---------------------------------\n";
        cout << "Total Cars in Showroom: " << totalCars << endl;
        cout << "Cars per Company:" << endl;
        cout << "---------------------------------\n"
             << endl;

        unordered_map<string, vector<const Car *>> carsByCompany; // Map to store cars with the same model and name

        // Group cars by company name
        for (const auto &car : cars)
        {
            string key = car.getCarName() + " - " + car.getcompany();
            carsByCompany[key].push_back(&car);
        }

        // Display cars grouped by company name
        for (const auto &entry : carsByCompany)
        {
            cout << "  " << entry.first << ": " << entry.second.size() << " cars" << endl;

            // Display details of each car with the same model and name
            for (const auto &car : entry.second)
            {
                cout << "    Model Number: " << car->getModelNo() << endl;
                cout << "    Car Name: " << car->getCarName() << endl;
                cout << "    Quality: " << car->getQuality() << endl;
                cout << "    Color: " << car->getcolor() << endl;
                cout << "    Transmission Type: " << car->gettransmission() << endl;
                cout << "    Battery Capacity: " << car->getBatteryCapacity() << " Ah" << endl;
                cout << "---------------------------------\n";
            }
        }
    }

    // Save car data to a file
    void saveCarData() const
    {
        ofstream carFile("car_data.txt");
        for (const auto &car : cars)
        {
            carFile << car.getModelNo() << "," << car.getCarName() << "," << car.getQuality() << "," << car.getcolor() << "," << car.getcompany() << "," << car.gettransmission() << "," << car.getBatteryCapacity() << "\n";
        }
        carFile.close();
    }
};

class CustomerInfo
{
private:
    string customerName;
    string contactNumber;
    string carModelNo; // To store the model number of the purchased/rented car

public:
    CustomerInfo(const string &name, const string &contact, const string &modelNo)
        : customerName(name), contactNumber(contact), carModelNo(modelNo) {}

    const string &getCustomerName() const
    {
        return customerName;
    }

    const string &getContactNumber() const
    {
        return contactNumber;
    }

    const string &getCarModelNo() const
    {
        return carModelNo;
    }

    // Convert customer information to a string for saving to a file
    string toString() const
    {
        return customerName + "," + contactNumber + "," + carModelNo + "\n";
    }
   static void loadExistingCustomerData(vector<CustomerInfo> &customerInfoList) {
    ifstream customerFile("customer.txt");
    if (customerFile.is_open()) {
        string line;
        while (getline(customerFile, line)) {
            stringstream ss(line);
            string customerName, contactNumber, carModelNo;

            // Use getline directly with stringstream
            getline(ss, customerName, ',');
            getline(ss, contactNumber, ',');
            getline(ss, carModelNo, ',');

            CustomerInfo customerInfo(customerName, contactNumber, carModelNo);
            customerInfoList.push_back(customerInfo);
        }
        customerFile.close();
    }
}

};

class Customer
{
public:
    static void displayCustomerInfo(const vector<CustomerInfo> &customerInfoList)
    {
        cout << "\nCustomer Information:\n";
        cout << "---------------------------------\n";
        for (const auto &customerInfo : customerInfoList)
        {
            cout << "Customer Name: " << customerInfo.getCustomerName() << endl;
            cout << "Contact Number: " << customerInfo.getContactNumber() << endl;
            cout << "Car Model Number: " << customerInfo.getCarModelNo() << endl;
            cout << "---------------------------------\n";
        }
    }
    static void checkCarInformation(const record_cars &carRecorder)
    {
        string carName, modelNo;

        cout << "Enter the car name: ";
        cin >> carName;

        cout << "Enter the model number: ";
        cin >> modelNo;

        bool carFound = false;

        for (const auto &car : carRecorder.cars)
        {
            if (car.getCarName() == carName && car.getModelNo() == modelNo)
            {
                cout << endl
                     << endl
                     << endl;
                cout << "---------------------------------\n";
                cout << "Car Information: " << endl;
                cout << "Model Number: " << car.getModelNo() << endl;
                cout << "Car Name: " << car.getCarName() << endl;
                cout << "Quality: " << car.getQuality() << endl;
                cout << "Color: " << car.getcolor() << endl;
                cout << "Company: " << car.getcompany() << endl;
                cout << "Transmission Type: " << car.gettransmission() << endl;
                cout << "Battery Capacity: " << car.getBatteryCapacity() << " Ah" << endl;
                cout << "---------------------------------\n";
                cout << endl
                     << endl
                     << endl;

                carFound = true;
                break;
            }
        }

        if (!carFound)
        {
            cout << "Car not found with the provided information." << endl;
        }
    }
    static void purchaseOrRentCar(record_cars &carRecorder, vector<CustomerInfo> &customerInfoList)
    {
        string carName, modelNo;

        carRecorder.loadExistingCarData(); // Load existing car data
         CustomerInfo::loadExistingCustomerData(customerInfoList);

        cout << "Enter the car name you want to purchase or rent: ";
        cin >> carName;

        cout << "Enter the model number of the car: ";
        cin >> modelNo;

        bool carFound = false;
        char purchaseOption;

        for (const auto &car : carRecorder.cars)
        {
            if (car.getCarName() == carName && car.getModelNo() == modelNo)
            {
                carFound = true;

                // Display the full car information
                cout << endl
                     << endl
                     << endl;
                cout << "---------------------------------\n";
                cout << "Car Information: " << endl;
                cout << "Model Number: " << car.getModelNo() << endl;
                cout << "Car Name: " << car.getCarName() << endl;
                cout << "Quality: " << car.getQuality() << endl;
                cout << "Color: " << car.getcolor() << endl;
                cout << "Company: " << car.getcompany() << endl;
                cout << "Transmission Type: " << car.gettransmission() << endl;
                cout << "Battery Capacity: " << car.getBatteryCapacity() << " Ah" << endl;
                cout << "---------------------------------\n"
                     << endl
                     << endl
                     << endl;

                // Continue with the purchase or rent process
                double totalPrice = car.getBatteryCapacity() * 500; // Assuming a simple pricing based on battery capacity

                char purchaseOption;
                cout << "Do you want to purchase or rent the car? (p/r): ";
                cin >> purchaseOption;

                string customerName, contactNumber;
                cout << "Enter your name: ";
                cin >> customerName;

                cout << "Enter your contact number: ";
                cin >> contactNumber;

                int rentalPeriod = 0; // New variable for rental period
                if (purchaseOption == 'r')
                {
                    cout << "Enter the rental period (in days): ";
                    cin >> rentalPeriod;
                }

                // Rest of the purchase or rent process...

                // Display the receipt
                cout << "\nReceipt: " << endl;
                cout << "---------------------------------\n";
                cout << "Customer Name: " << customerName << endl;
                cout << "Contact Number: " << contactNumber << endl;
                cout << "Car Model Number: " << car.getModelNo() << endl;
                cout << "Car Name: " << car.getCarName() << endl;
                cout << "Total Price: $" << totalPrice << endl;
                if (purchaseOption == 'r')
                {
                    cout << "Rental Period: " << rentalPeriod << " days" << endl;
                }

                cout << "---------------------------------\n"
                     << endl;

                // Update the battery capacity if the car is rented

                if (purchaseOption == 'r')
                {
                    // Adjust the battery capacity based on some logic (e.g., decrease by 10% for each day of rental)
                    double newCapacity = car.getBatteryCapacity() * 0.9; // Adjust as needed
                    carRecorder.updateBatteryCapacity(car.getModelNo(), newCapacity);

                    // Add the customer to the list with a note that it's a rental
                    CustomerInfo customerInfo(customerName, contactNumber, car.getModelNo() + " (Rental)");
                    customerInfoList.push_back(customerInfo);
                }
                else if (purchaseOption == 'p')
                {
                    // Add the customer to the list with a note that it's a purchase
                    CustomerInfo customerInfo(customerName, contactNumber, car.getModelNo() + " (Purchase)");
                    customerInfoList.push_back(customerInfo);
                }

                // Save customer data after either a purchase or rent
                saveCustomerData(customerInfoList);

                break;
            }
        }
    }
    static void saveCustomerData(const vector<CustomerInfo> &customerInfoList)
    {
        ofstream customerFile("customer.txt");
        for (const auto &customerInfo : customerInfoList)
        {
            customerFile << customerInfo.getCustomerName() << ","
                         << customerInfo.getContactNumber() << ","
                         << customerInfo.getCarModelNo() << "\n";
        }
        customerFile.close();
    }

    static void returnRentedCar(record_cars &carRecorder)
    {
        if (carRecorder.cars.empty())
        {
            cout << "No cars are currently on rent." << endl;
            return;
        }

        string carName, modelNo;
        carRecorder.loadExistingCarData(); // Load existing car data

        cout << "Enter the car name you are returning: ";
        cin >> carName;

        cout << "Enter the model number of the car: ";
        cin >> modelNo;

        bool carFound = false;
        double meterReading;
        char carCondition;

        for (auto &car : carRecorder.cars)
        {
            if (car.getCarName() == carName && car.getModelNo() == modelNo)
            {
                carFound = true;

                cout << "Enter the meter reading of the car: ";
                cin >> meterReading;

                cout << "Rate the condition of the car (A: Excellent, B: Good, C: Average, D: Poor): ";
                cin >> carCondition;

                double netWorth = calculateNetWorth(car.getBatteryCapacity(), meterReading, carCondition);

                car.setBatteryCapacity(netWorth);

                cout << "The net worth of the car has been updated based on meter reading and condition." << endl;
                cout << "New Battery Capacity (net worth): " << car.getBatteryCapacity() << " Ah" << endl;

                break;
            }
        }

        if (!carFound)
        {
            cout << "Car not found with the provided information." << endl;
        }
    }

private:
    static double calculateNetWorth(double batteryCapacity, double meterReading, char carCondition)
    {
        // Assume a simple formula for net worth calculation
        double netWorth = batteryCapacity * exp(-0.001 * meterReading);

        // Adjust net worth based on car condition
        switch (carCondition)
        {
        case 'A':
            netWorth *= 5; // Excellent condition
            break;
        case 'B':
            netWorth *= 3; // Good condition
            break;
        case 'C':
            netWorth *= 2;
            //  adjustment for average condition
            break;
        case 'D':
            netWorth *= 1; // Poor condition
            break;
        default:
            cout << "Invalid car condition. Assuming average condition." << endl;
            // No adjustment for average condition
        }

        return netWorth;
    }

    // Load customer data from a file
    static void loadCustomerData(vector<CustomerInfo> &customerInfoList)
    {
        ifstream customerFile("customer.txt");
        string customerLine;

        while (getline(customerFile, customerLine))
        {
            size_t pos = customerLine.find(",");
            if (pos != string::npos)
            {
                size_t pos2 = customerLine.find(",", pos + 1);
                string customerName = customerLine.substr(0, pos);
                string contactNumber = customerLine.substr(pos + 1, pos2 - pos - 1);
                string carModelNo = customerLine.substr(pos2 + 1);
                CustomerInfo customerInfo(customerName, contactNumber, carModelNo);
                customerInfoList.push_back(customerInfo);
            }
        }

        customerFile.close();
    }
};

class Login
{
private:
    record_cars carRecorder;
    vector<Sign_up> users;
    vector<CustomerInfo> customerInfoList;

public:
    bool loggedIn;
    vector<Car> cars;

    Login() : loggedIn(false)
    {
        loadUserData();
        loadCarData();
    }
    void loadCustomerData()
    {
        ifstream customerFile("customer.txt");
        string customerLine;

        while (getline(customerFile, customerLine))
        {
            size_t pos = customerLine.find(",");
            if (pos != string::npos)
            {
                size_t pos2 = customerLine.find(",", pos + 1);
                string customerName = customerLine.substr(0, pos);
                string contactNumber = customerLine.substr(pos + 1, pos2 - pos - 1);
                string carModelNo = customerLine.substr(pos2 + 1);
                CustomerInfo customerInfo(customerName, contactNumber, carModelNo);
                customerInfoList.push_back(customerInfo);
            }
        }

        customerFile.close();
    }

    // Load user data from a file
    void loadUserData()
    {
        ifstream userFile("user_data.txt");
        string userLine;

        while (getline(userFile, userLine))
        {
            size_t pos = userLine.find(",");
            if (pos != string::npos)
            {
                size_t pos2 = userLine.find(",", pos + 1);
                string uname = userLine.substr(0, pos);
                string pwd = userLine.substr(pos + 1, pos2 - pos - 1);
                string email = userLine.substr(pos2 + 1);
                users.emplace_back(uname, pwd, email);
            }
        }

        userFile.close();
    }

    // Load car data from a file

    // Load car data from a file
    void loadCarData()
    {
        ifstream carFile("car_data.txt");
        string carLine;

        carRecorder.cars.clear(); // Clear the vector before loading data

        while (getline(carFile, carLine))
        {
            size_t pos = carLine.find(",");
            if (pos != string::npos)
            {
                string model = carLine.substr(0, pos);
                size_t pos2 = carLine.find(",", pos + 1);
                string carName = carLine.substr(pos + 1, pos2 - pos - 1);
                size_t pos3 = carLine.find(",", pos2 + 1);
                string quality = carLine.substr(pos2 + 1, pos3 - pos2 - 1);
                size_t pos4 = carLine.find(",", pos3 + 1);
                string color = carLine.substr(pos3 + 1, pos4 - pos3 - 1);
                size_t pos5 = carLine.find(",", pos4 + 1);
                string company = carLine.substr(pos4 + 1, pos5 - pos4 - 1);
                size_t pos6 = carLine.find(",", pos5 + 1);
                string transmission = carLine.substr(pos5 + 1, pos6 - pos5 - 1);

                // Convert the battery capacity string to double
                double capacity;
                try
                {
                    capacity = stod(carLine.substr(pos6 + 1));
                }
                catch (const std::invalid_argument &e)
                {
                    cerr << "Invalid argument: " << e.what() << endl;
                    continue; // Skip this line and move to the next one
                }
                catch (const std::out_of_range &e)
                {
                    cerr << "Out of range: " << e.what() << endl;
                    continue; // Skip this line and move to the next one
                }

                carRecorder.cars.emplace_back(model, carName, quality, color, company, transmission, capacity);
            }
        }

        carFile.close();

        // Update the 'cars' vector used in other parts of the program
        cars = carRecorder.cars;
    }

    void loadUserCarData(const string &uname)
    {
        // Load car data for the logged-in user from the showroom

        cars.clear(); // Clear the vector before loading data

        for (const auto &car : carRecorder.cars)
        {
            if (car.getCarName() == uname)
            {
                cars.push_back(car);
            }
        }

        cout << "Car data loaded for user: " << uname << endl;
    }
    void loadCarDataOnLogin()
    {
        // Reload car data from the file during login
        loadCarData();

        // Update the 'cars' vector used in other parts of the program
        cars = carRecorder.cars;

        cout << "Car data loaded for user." << endl;
    }

    // Save car data to a file

    void saveCarData() const
    {
        ofstream carFile("car_data.txt");
        for (const auto &car : carRecorder.cars)
        {
            carFile << car.getModelNo() << ","
                    << car.getCarName() << ","
                    << car.getQuality() << ","
                    << car.getcolor() << ","
                    << car.getcompany() << ","
                    << car.gettransmission() << ","
                    << car.getBatteryCapacity() << "\n";
        }
        carFile.close();
    }

    // Save user data to a file
    void saveUserData() const
    {
        ofstream userFile("user_data.txt");
        for (const auto &user : users)
        {
            userFile << user.getUsername() << "," << user.getPassword() << "," << user.getEmail() << "\n";
        }
        userFile.close();
    }

    // Sign up a new user
    void signUp()
    {
        string username, password, email;

        cout << "Enter your desired username: ";
        cin >> username;

        // Check if the username is already taken
        for (const auto &user : users)
        {
            if (user.getUsername() == username)
            {
                cout << "Sorry, the username is already taken. Please choose a different one." << endl;
                return;
            }
        }

        cout << "Enter your password: ";
        cin >> password;

        cout << "Enter your email address: ";
        cin >> email;

        users.emplace_back(username, password, email);
        cout << "Registration successful! Welcome, " << username << " :)" << endl;

        // Save the updated user data to the file
        saveUserData();
    }

    // Log in an existing user
    void logIn()
    {
        string username, password;

        cout << "Enter your username: ";
        cin >> username;

        cout << "Enter your password: ";
        cin >> password;

        // Check if the username and password match
        for (const auto &user : users)
        {
            if (user.getUsername() == username && user.getPassword() == password)
            {
                loggedIn = true;
                cout << "Login successful! Welcome back, " << username << " :)" << endl;

                // Load car data for the logged-in user
                loadUserCarData(username);

                return;
            }
        }

        cout << "Invalid username or password. Please try again." << endl;
    }

    // Log out the current user
    void logOut()
    {
        if (loggedIn)
        {
            saveCarData();
            cout << "Logging out... Goodbye!" << endl;
            loggedIn = false;
        }
        else
        {
            cout << "No user is currently logged in." << endl;
        }
    }
    bool isLoggedIn() const
    {
        return loggedIn;
    }

    // Display the main menu
    void displayMainMenu()
    {
        while (loggedIn)
        {
            int choice;
            cout << endl
                 << endl
                 << endl;
            cout << "---------------------------------";
            cout << "\n      Main Menu      \n";
            cout << "---------------------------------\n";
            cout << "1. View Showroom Statistics\n";
            cout << "2. Add Car to Showroom\n";
            cout << "3. Check Car Information\n";
            cout << "4. Purchase/Rent Car\n";
            cout << "5. Return Rented Car\n";
            cout << "6. Display customer info\n";
            cout << "7. Logout\n";
            cout << "---------------------------------\n";
          
                cout << "Enter your choice: ";
             while (!(cin >> choice) || cin.fail() || choice < 1 || choice > 7)
        {
            cout << "please dont corrupt me . Please enter a number between 1 and 7.\n";
            cin.clear();                               // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Enter your choice: ";
        }

            switch (choice)
            {
            case 1:
                if (loggedIn)
                {
                    // Display showroom statistics
                    carRecorder.displayStatistics();
                }
                else
                {
                    cout << "You need to log in first to view showroom statistics." << endl;
                }
                break;
            case 2:
                if (loggedIn)
                {
                    // Add a new car to the showroom
                    string modelNo, carName, quality, color, company, transmission;
                    double batteryCapacity;

                    cout << "Enter the model number of the car: ";
                    cin >> modelNo;

                    cout << "Enter the name of the car: ";
                    cin >> carName;

                    cout << "Enter the quality of the car: ";
                    cin >> quality;

                    cout << "Enter the color of the car: ";
                    cin >> color;

                    cout << "Enter the company of the car: ";
                    cin >> company;

                    cout << "Enter the transmission type of the car: ";
                    cin >> transmission;

                    cout << "Enter the battery capacity of the car (in Ah): ";
                    cin >> batteryCapacity;

                    Car newCar(modelNo, carName, quality, color, company, transmission, batteryCapacity);
                    carRecorder.addCar(newCar);
                }
                else
                {
                    cout << "You need to log in first to add a car to the showroom." << endl;
                }
                break;
            case 3:
                if (loggedIn)
                {
                    // Check car information
                    Customer::checkCarInformation(carRecorder);
                }
                else
                {
                    cout << "You need to log in first to check car information." << endl;
                }
                break;
            case 4:
                if (loggedIn)
                {
                    // Purchase/Rent car
                    Customer::purchaseOrRentCar(carRecorder, customerInfoList);
                }
                else
                {
                    cout << "You need to log in first to purchase/rent a car." << endl;
                }
                break;
            case 5:
                if (loggedIn)
                {
                    // Return rented car
                    Customer::returnRentedCar(carRecorder);
                }
                else
                {
                    cout << "You need to log in first to return a rented car." << endl;
                }
                break;
            case 6:
                if (loggedIn)
                {
                    // Display customer information
                    Customer::displayCustomerInfo(customerInfoList);
                }
                else
                {
                    cout << "You need to log in first to view customer information." << endl;
                }
                break;
            case 7:
                cout << "Logging out... Returning to Login Page. Goodbye!" << endl;
                loggedIn = false; // Logout the user
                return;           // Return to the login page
            default:
                cout << "Invalid option. Please choose a valid option from the menu." << endl;
                break;
            }
        }
    }
};

int main()
{
    Login loginSystem;

    // Load user data and car data at the beginning
    loginSystem.loadUserData();
    loginSystem.loadCarData();
    while (true)
    {
        if (!loginSystem.isLoggedIn())
        {
            int choice;
            cout << "-------------------------------------------------\n";
            cout << "     Welcome to Car Showroom Management System      \n";
            cout << "-------------------------------------------------\n";
            cout << "1. Login\n";
            cout << "2. Sign Up\n";
            cout << "3. Exit\n";
            cout << "-------------------------------------------------\n";
            cout << "Enter your choice: ";

            cin >> choice;

            switch (choice)
            {
            case 1:
                loginSystem.logIn();
                break;
            case 2:
                loginSystem.signUp();
                break;
            case 3:
                // Save user and car data before exiting
                loginSystem.saveUserData();
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Dont try to corrupt me ." << endl;
            }
        }
        else
        {
            loginSystem.displayMainMenu();
            loginSystem.saveCarData();
        }
        if (cin.fail())
        {
            cout << "Invalid input. Please enter a valid numeric choice.\n";
            cin.clear();                                         // Clear input buffer to restore cin to a usable state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
    }

    return 0;
}
