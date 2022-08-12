// Name: Annie Tran
// UID: 905717479
// Project 4: Unhinged
// MatchMaker.h

#ifndef MatchMaker_h
#define MatchMaker_h

#include "provided.h"
#include "MemberDatabase.h"
#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include <string>
#include <vector>

class MatchMaker{
public:
    MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
    ~MatchMaker();
    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;
private:
    const MemberDatabase* m_mdb;
    const AttributeTranslator* m_at;
};
#endif /* MatchMaker_h */
