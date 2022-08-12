// Name: Annie Tran
// UID: 905717479
// Project 4: Unhinged
// AttributeTranslator.h

#ifndef AttributeTranslator_h
#define AttributeTranslator_h

#include "provided.h"
#include "RadixTree.h"
#include <string>
#include <vector>

class AttributeTranslator{
public:
    AttributeTranslator();
    ~AttributeTranslator();
    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;
private:
    RadixTree<std::vector<AttValPair>>compatibleRT;
    AttValPair* pair;
};
#endif /* AttributeTranslator_h */
