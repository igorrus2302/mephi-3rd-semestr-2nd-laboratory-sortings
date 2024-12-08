#pragma once

#include <iostream>
#include <string>
#include <cstdlib>

#include "names.h"

class People {

private:

    std::string firstName;
    std::string lastName;
    std::string patronymic;
    std::string birthDate;
    int accountBalance;

    std::string GenerateRandomBirthDate() {
        int day = rand() % 30 + 1;
        int month = rand() % 12 + 1;
        int year = rand() % 65 + 1960;

        char buffer[11];
        snprintf(buffer, sizeof(buffer), "%02d.%02d.%04d", day, month, year);
        return std::string(buffer);
    }

public:

    People() {
        firstName = firstNames[rand() % countFirstNames];
        lastName = lastNames[rand() % countLastNames];
        patronymic = patronymics[rand() % countPatronymics];
        birthDate = GenerateRandomBirthDate();
        accountBalance = rand() % 1000001;
    }

    People(std::string firstName, std::string lastName, std::string patronymic, std::string birthDate, int accountBalance) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->patronymic = patronymic;
        this->birthDate = birthDate;
        this->accountBalance = accountBalance;
    }

    bool operator<(const People& other) const { return accountBalance < other.accountBalance; }
    bool operator>(const People& other) const { return accountBalance > other.accountBalance; }
    bool operator<=(const People& other) const { return accountBalance <= other.accountBalance; }
    bool operator>=(const People& other) const { return accountBalance >= other.accountBalance; }
    bool operator==(const People& other) const { return accountBalance == other.accountBalance; }
    bool operator!=(const People& other) const { return accountBalance != other.accountBalance; }


    std::string GetFirstName() const { return firstName; }
    std::string GetLastName() const { return lastName; }
    std::string GetPatronymic() const { return patronymic; }
    std::string GetBirthDate() const { return birthDate; }
    int GetAccountBalance() const { return accountBalance; }

    friend std::ostream& operator<<(std::ostream& os, const People& person) {
        os << "Name: " << person.firstName << " " << person.lastName << " " << person.patronymic
           << ", Birth Date: " << person.birthDate << ", Account Balance: " << person.accountBalance;
        return os;
    };

};


