// Name: Annie Tran
// UID: 905717479
// Project 4: Unhinged
// MemberDatabase.cpp

#ifndef MemberDatabase_h
#define MemberDatabase_h

#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"
#include <string>
#include <vector>

class MemberDatabase{
public:
    MemberDatabase();
    ~MemberDatabase();
    bool LoadDatabase(std::string filename);
    std::vector<std::string>FindMatchingMembers(const AttValPair& input) const;
    const PersonProfile* GetMemberByEmail(std::string email) const;
private:
    RadixTree<PersonProfile*> emailRadixTree;
    RadixTree<std::vector<std::string>> sharedAttRT;
    PersonProfile* m_person;
};
#endif /* MemberDatabase_h */
