#include "people.h"
#include "comparings.h"


int CompareByFirstName(const People& a,  const People& b)
{
    return a.GetFirstName().compare(b.GetFirstName());
}

int CompareByLastName(const People& a, const People& b)
{
    return a.GetLastName().compare(b.GetLastName());
}

int CompareByPatronymic(const People& a, const People& b)
{
    return a.GetPatronymic().compare(b.GetPatronymic());
}

int CompareByBirthDate(const People& a, const People& b)
{
    return a.GetBirthDate().compare(b.GetBirthDate());
}

int CompareByAccountBalance(const People& a, const People& b)
{
    return (a.GetAccountBalance() < b.GetAccountBalance()) ? -1 : (a.GetAccountBalance() > b.GetAccountBalance() ? 1 : 0);
}

int CompareByTwoAttributesWrapper(const People& a, const People& b)
{
    return CompareByTwoAttributes(a, b, &People::GetFirstName, &People::GetLastName);
}

int CompareByStringAndIntWrapper(const People& a, const People& b)
{
    return CompareByStringAndInt(a, b, &People::GetFirstName, &People::GetAccountBalance);
}

int CompareByStringAndIntWrapper2(const People& a, const People& b)
{
    return CompareByStringAndInt(a, b, &People::GetBirthDate, &People::GetAccountBalance);
}

int CompareByIntAndStringWrapper(const People& a, const People& b)
{
    return CompareByIntAndString(a, b, &People::GetAccountBalance, &People::GetBirthDate);
}
