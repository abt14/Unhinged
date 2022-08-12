// Name: Annie Tran
// UID: 905717479
// Project 4: Unhinged
// MatchMaker.cpp

#include "MatchMaker.h"
#include <unordered_set>
#include <unordered_map>

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
{
    m_mdb = &mdb;
    m_at = &at;
}
MatchMaker::~MatchMaker()
{}
std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
    if (m_mdb->GetMemberByEmail(email)==nullptr)        //get the email
    {
        std::vector<EmailCount> emptyVector;
        return emptyVector;
    }
    std::unordered_set<std::string> uniqueStringCompare;
    std::vector <AttValPair> uniqueSet;
    const PersonProfile *person = m_mdb->GetMemberByEmail(email); //get person's profile
    for (int i=0; i < person->GetNumAttValPairs(); i++)
    {
        AttValPair av;
        person->GetAttVal(i, av);
        std::vector<AttValPair> compatibleList = m_at->FindCompatibleAttValPairs(av); //find list of compatible pairs for each attval pair
        for (int j=0; j<compatibleList.size(); j++)
        {
            std::string key, att, val;
            att = compatibleList[j].attribute;
            val = compatibleList[j].value;
            key = att+val;
            if (uniqueStringCompare.insert(key).second == true)      //if set item was successfuly inserted, will return true
                uniqueSet.push_back(compatibleList[j]);
        }
    }
    std::unordered_map<std::string,int> possibleMatches;        //keep track emails that could be a possible match and the count
    for (int k=0; k<uniqueSet.size(); k++)
    {
        std::vector<std::string> vectorEmails = m_mdb->FindMatchingMembers(uniqueSet[k]);   //find matching members for each compatible pair
        for (int m=0; m<vectorEmails.size(); m++)
        {
            if (vectorEmails[m] == email)
                continue;
            if (possibleMatches.find(vectorEmails[m]) != possibleMatches.end())         //email in the map already
                (*possibleMatches.find(vectorEmails[m])).second++;                      //increment the match count
            else
                possibleMatches.insert({vectorEmails[m],1});                            //insert email into map
        }
    }
    
    std::set<EmailCount> sortedMatches;         //will sort the candidate by match count and then alphabetically by email
    std::unordered_map<std::string,int>::iterator it;
    for (it = possibleMatches.begin(); it != possibleMatches.end(); it++)
    {
        if ((*it).second >= threshold)                          //if the candidate exceeds the match threshold, insert in set
        {
            EmailCount match((*it).first, (*it).second);
            sortedMatches.insert(match);
        }
    }
    
    std::vector<EmailCount> finalCompatatibleMatches;       //push all the candidates in the set to the vector and return
    std::set<EmailCount>::iterator s_it;
    for (s_it = sortedMatches.begin(); s_it != sortedMatches.end(); s_it++)
        finalCompatatibleMatches.push_back((*s_it));
    
    return finalCompatatibleMatches;
}

//support function - overloaded comparison operator to sort finalCompatibleMatches based on count and email
bool operator<(const EmailCount &a, const EmailCount &b)
{
    if (a.count > b.count)
        return true;
    else if (a.count == b.count)
        return a.email < b.email;
    else
        return false;
}
