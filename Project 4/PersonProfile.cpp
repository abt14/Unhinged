// Name: Annie Tran
// UID: 905717479
// Project 4: Unhinged
// PersonProfile.cpp

#include "PersonProfile.h"

PersonProfile::PersonProfile (std::string name, std::string email): m_name(name), m_email(email) {}

PersonProfile::~PersonProfile() {}

std::string PersonProfile::GetName() const
{
    return m_name;
}

std::string PersonProfile::GetEmail() const
{
    return m_email;
}
void PersonProfile::AddAttValPair (const AttValPair& attval)
{
    std::set<std::string>* values = rt.search(attval.attribute);  //gets value from radixTree mapping -> set<string>
    if (values!=nullptr)    //key already exists
    {
        if (values->insert(attval.value).second == true)    //0(logN) if set item was successfuly inserted, will return true
            m_pairs.push_back(attval); //O(1)
    }
    else
    {
        std::set<std::string> valueSet;
        rt.insert(attval.attribute, valueSet); //O(logN)
        std::set<std::string>* getValues = rt.search(attval.attribute);
        getValues->insert(attval.value); //O(logN)
        m_pairs.push_back(attval); //O(1)
    }
}

int PersonProfile::GetNumAttValPairs()const
{
    return m_pairs.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
    if (attribute_num<0 || attribute_num >= GetNumAttValPairs())
        return false;
    else
    {
        attval = m_pairs[attribute_num];
        return true;
    }
}
