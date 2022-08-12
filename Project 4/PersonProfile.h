// Name: Annie Tran
// UID: 905717479
// Project 4: Unhinged
// PersonProfile.h

#ifndef PersonProfile_h
#define PersonProfile_h

#include "provided.h"
#include "RadixTree.h"
#include <string>
#include <vector>
#include <set>

class PersonProfile
{
public:
    PersonProfile (std::string name, std::string email);
    ~PersonProfile();
    std::string GetName() const;
    std::string GetEmail() const;
    void AddAttValPair (const AttValPair& attval);
    int GetNumAttValPairs()const;
    bool GetAttVal(int attribute_num, AttValPair& attval) const;
private:
    std::string m_name;
    std::string m_email;
    std::vector<AttValPair> m_pairs;
    RadixTree<std::set<std::string>> rt;
};

#endif /* PersonProfile_h */
