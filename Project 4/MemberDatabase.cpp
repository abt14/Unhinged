// Name: Annie Tran
// UID: 905717479
// Project 4: Unhinged
// MemberDatabase.cpp

#include "MemberDatabase.h"
#include <fstream>
#include <iostream>
#include <sstream>


MemberDatabase::MemberDatabase()
{
    m_person = nullptr;
}
MemberDatabase::~MemberDatabase()
{
    delete m_person;
}

bool MemberDatabase::LoadDatabase(std::string filename)
{
    std::ifstream infile(filename);
    if (!infile)
        return false;
    else
    {
        std::string line, name, email;
        int lineNumber = 0;
        while (getline(infile, line))
        {
            lineNumber++;   //track of line # for each person to separate name/email from attribute pairs
            if (line=="")
            {
                lineNumber=0; //set back to 0 for the next person
                emailRadixTree.insert(email, m_person); //insert
            }
            if (lineNumber==1)
                name = line; //store the name
            if (lineNumber==2)
            {
                email = line; //store the email and create a person
                if (emailRadixTree.search(email) != nullptr)    //means that this email already exists
                    return false;
                else
                    m_person = new PersonProfile(name, email);
            }
            if (lineNumber >= 4)    //skip the line with num of pairs
            {
                std::istringstream iss(line);
                std::string attribute, value;
                std::getline(iss, attribute, ',');
                std::getline(iss, value, ',');
                AttValPair av (attribute, value);
                m_person->AddAttValPair(av);
                std::string AttValPairKey = attribute+value;    //use as a key for the radix tree
                               
                //to keep track of all the emails that have the same attributes
                if (sharedAttRT.search(AttValPairKey) != nullptr) //pair already exists
                {
                    std::vector<std::string>* emails = sharedAttRT.search(AttValPairKey);
                    if (((*emails)[emails->size()-1]) != email) //checks for duplicates - last position in vector to see if the email has already been pushed to the vector -> if not then add
                    emails->push_back(email); //O(1)
                }
                else
                {
                    std::vector<std::string> emails;
                    emails.push_back(email);
                    sharedAttRT.insert(AttValPairKey, emails);
                }
            }
        }
        emailRadixTree.insert(email, m_person);     //need this in order to insert last person profile
    }
    return true;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
    std::string key, att, val;
    att = input.attribute;
    val = input.value;
    key = att+val;
    if (sharedAttRT.search(key)== nullptr) //key is not there
    {
        std::vector<std::string> emails;
        return emails;
    }
    else
    {
        std::vector<std::string>* emailsPtr = sharedAttRT.search(key);
        return *emailsPtr;
    }
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
    if (emailRadixTree.search(email) == nullptr) //does not exist
        return nullptr;
    else
    {
        PersonProfile** temp = emailRadixTree.search(email);
        return *temp;
    }
}
