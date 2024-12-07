#pragma once

int CompareByFirstName(const People& a, const People& b);
int CompareByLastName(const People& a, const People& b);
int CompareByPatronymic(const People& a, const People& b);
int CompareByBirthDate(const People& a, const People& b);
int CompareByAccountBalance(const People& a, const People& b);

int CompareByTwoAttributesWrapper(const People& a, const People& b);
int CompareByStringAndIntWrapper(const People& a, const People& b);
int CompareByStringAndIntWrapper2(const People& a, const People& b);
int CompareByIntAndStringWrapper(const People& a, const People& b);


template <typename T>
int CompareByTwoAttributes(
        const T& a,
        const T& b,
        std::string (T::*getFirstAttribute)() const,
        std::string (T::*getSecondAttribute)() const
) {
    auto firstA = (a.*getFirstAttribute)();
    auto firstB = (b.*getFirstAttribute)();
    int comparison = (firstA < firstB) ? -1 : (firstA > firstB ? 1 : 0);
    if (comparison != 0) return comparison;

    auto secondA = (a.*getSecondAttribute)();
    auto secondB = (b.*getSecondAttribute)();

    return (secondA < secondB) ? -1 : (secondA > secondB ? 1 : 0);
}

template <typename T>
int CompareByStringAndInt(
        const T& a,
        const T& b,
        std::string (T::*getFirstAttribute)() const,
        int (T::*getSecondAttribute)() const
) {
    std::string firstAttributeA = (a.*getFirstAttribute)();
    std::string firstAttributeB = (b.*getFirstAttribute)();
    int firstComparison = (firstAttributeA < firstAttributeB) ? -1 : (firstAttributeA > firstAttributeB ? 1 : 0);

    if (firstComparison != 0)
    {
        return firstComparison;
    }

    int secondAttributeA = (a.*getSecondAttribute)();
    int secondAttributeB = (b.*getSecondAttribute)();

    return (secondAttributeA < secondAttributeB) ? -1 : (secondAttributeA > secondAttributeB ? 1 : 0);
}


template <typename T>
int CompareByIntAndString(
        const T& a,
        const T& b,
        int (T::*getFirstAttribute)() const,
        std::string (T::*getSecondAttribute)() const
) {
    int firstAttributeA = (a.*getFirstAttribute)();
    int firstAttributeB = (b.*getFirstAttribute)();
    int firstComparison = (firstAttributeA < firstAttributeB) ? -1 : (firstAttributeA > firstAttributeB ? 1 : 0);

    if (firstComparison != 0)
    {
        return firstComparison;
    }

    std::string secondAttributeA = (a.*getSecondAttribute)();
    std::string secondAttributeB = (b.*getSecondAttribute)();

    return (secondAttributeA < secondAttributeB) ? -1 : (secondAttributeA > secondAttributeB ? 1 : 0);
}


