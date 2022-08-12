//main.cpp

#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>

const std::string MEMBERS_FILE    = "/Users/annietran/UCLA Courses/Winter2022/CS32/Project 4/Unhinged/members.txt";
const std::string TRANSLATOR_FILE = "/Users/annietran/UCLA Courses/Winter2022/CS32/Project 4/Unhinged/translator.txt";

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);

int main() {
    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }

    while (findMatches(mdb, at))
        ;

    std::cout << "Happy dating!" << std::endl;
}

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
{
      // Prompt for email
    std::string email;
    const PersonProfile* pp;
    for (;;) {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

      // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }

      // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

      // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else {
        std::cout << "The following members were good matches:" << std::endl;;
        for (const auto& emailCount : emails) {
            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}

////_______________________MY OWN TESTING________________
//#include <iostream>
//#include "RadixTree.h"
//#include "PersonProfile.h"
//#include <map>
//#include <unordered_set>
//#include "provided.h"
//#include "MemberDatabase.h"
//#include "AttributeTranslator.h"
//#include <fstream>
//#include "MatchMaker.h"
//#include <cassert>
//using namespace std;

//int main()
//{
////    //TESTS FOR RADIX TREE
////        RadixTree<int> r;
////    r.insert("card", 10);    //insert word into empty radix tree
////    r.insert("car", 2);      //word inserted has a prefix in the tree "card" but "card" has leftover letter "d"
////    r.insert("cardigan", 5); //word inserted has existing prefix "car" then traces to "d" but key has leftover letters "igan"
////    r.insert("castle", 6);  //word inserted shares letters "ca" so "car" prefix must split w/ leftover "stle" in key
////    r.insert("water", 4);   //insert word into radix tree
////    r.insert("watch", 3);   //shares "wat" with "water" but different ending so must split into two
////    r.insert("waste", 8);   //shares "wa" with prefix "wat" but needs to split
////    r.insert("wish", 0);     //shares "w" with "wa" but needs to split;
////
////    //check if values above are in the radixTree
////    int* value;
////    assert ((value = r.search("card")) && *value == 10);
////    assert ((value = r.search("car")) && *value == 2);
////    assert ((value = r.search("cardigan")) && *value == 5);
////    assert ((value = r.search("castle")) && *value == 6);
////    assert ((value = r.search("water")) && *value == 4);
////    assert ((value = r.search("watch")) && *value == 3);
////    assert ((value = r.search("waste")) && *value == 8);
////    assert ((value = r.search("wish")) && *value == 0);
////    cerr << "Passed search tests" << endl;
////
////    //check how program would behave if try to search for non existing values in the radix tree
////    int *notInRT = r.search("hi");      //"hi" is not in radix tree so should return nullpointer
////    cerr << notInRT << endl;            //should return 0x0 (aka nullptr)
////    notInRT = r.search("ca");           //not in radix tree
////    cerr << notInRT << endl;            //should return 0x0 (aka nullptr)
////    notInRT = r.search("w");            //not in radix tree
////    cerr << notInRT << endl;               //should return 0x0 (aka nullptr)
//
////    //TESTS FOR PERSONPROFILE
////    PersonProfile p("annie", "at03@ucla.edu"); //create person
////    cerr << p.GetName() << endl;               //should return "at03@ucla.edu"
////    cerr << p.GetEmail() << endl;              //should return "annie"
////    AttValPair at ("major", "cs");             //"major" is the key in the radixTree
////    p.AddAttValPair(at);
////    AttValPair at2 ("interest", "knitting");    //"interest" is the key in the radixTree
////    p.AddAttValPair(at2);
////    AttValPair at3 ("interest", "piano");       //"interest" already exists but "piano" is a different attribute
////    p.AddAttValPair(at3);
////    AttValPair at4 ("interest", "knitting");    //this pair already exists->shouldn't be counted
////    p.AddAttValPair(at4);
////    AttValPair at5 ("hobby", "piano");          //pair has same attribute as another key but different key
////    p.AddAttValPair(at5);
////    AttValPair at6 ("food", "eggrolls");
////    p.AddAttValPair(at6);
////    AttValPair at7 ("food", "eggrolls");        //pair already exists -> do nothing
////    p.AddAttValPair(at7);
////    AttValPair at8 ("food", "ice cream");
////    p.AddAttValPair(at8);
////    cerr << p.GetNumAttValPairs() << endl;      //should return 6
////
////    for (int k=0; k!=p.GetNumAttValPairs(); k++)
////    {
////        AttValPair av;
////        p.GetAttVal(k, av);                     //tests the GetAttVal() method
////        std:: cerr << av.attribute << " -> " << av.value << std::endl;  //should not print repeats
////    }
//
        //SOME TESTS FOR MEMBERDATABASE
//    MemberDatabase h;
//    bool value = h.LoadDatabase("/Users/annietran/UCLA Courses/Winter2022/CS32/Project 4/Unhinged/members.txt");
////    cerr << value << endl;          //should return true
////    //check that emails are loaded onto database
////    cerr << h.GetMemberByEmail("AbFow2483@charter.net") << endl;
////    cerr << h.GetMemberByEmail("MatthBuckner@hotmail.com") << endl;
////    cerr << h.GetMemberByEmail("BennetG444@earthlink.net") << endl;
////    cerr << h.GetMemberByEmail("ELand@live.com") << endl;
////    cerr << h.GetMemberByEmail("aaaa@.aaa") << endl;            //should return 0x0 aka nullptr
////    AttValPair av("hobby", "painting");
////    vector<string> temp = h.FindMatchingMembers(av);    //test FindMatchingMembers() function
////    for (int i=0; i<temp.size(); i++)                   //should return all emails that contains "hobby,painting" according to the file
////        cerr << temp[i] << endl;
////    AttValPair av2 ("trait", "crazy");
////    vector<string> temp2 = h.FindMatchingMembers(av2);    //test FindMatchingMembers() function
////    for (int i=0; i<temp2.size(); i++)                   //should return all emails that contains "job,librarian" according to the file
////        cerr << temp2[i] << endl;
////    AttValPair av3 ("interest", "rich");                //if can't find any members with attribute-value
////    vector<string> notPresent = h.FindMatchingMembers(av3);
////    for (int i=0; i<notPresent.size(); i++)             //should return empty vector
////        cerr << notPresent[i] << endl;
//
//      //SOME TESTS FOR ATTRIBUTE TRANSLATOR
//    AttributeTranslator a;
//    bool loadSuccess = a.Load("/Users/annietran/UCLA Courses/Winter2022/CS32/Project 4/Unhinged/translator.txt");
//    cerr << loadSuccess << endl;            //should return true
//    AttValPair av ("trait", "dirty");
//    std::vector<AttValPair> temp = a.FindCompatibleAttValPairs(av);     //test FindCompatibleAttValPairs()
//    for (int i=0; i<temp.size(); i++)
//        std::cout << temp[i].attribute << "->" << temp[i].value << std:: endl;  //"hobby,woodworking,job,nurse" is duplicated in text file but should not be duplicated in the vector - should print out 10 compatible pairs
////    AttValPair av2 ("trait", "unrealistic");
////    std::vector<AttValPair> temp2 = a.FindCompatibleAttValPairs(av2);     //test FindCompatibleAttValPairs()
////    for (int i=0; i<temp2.size(); i++)
////        std::cout << temp2[i].attribute << "->" << temp2[i].value << std:: endl;  //should print out 3 compatible pairs
////    AttValPair av3 ("interest", "piano");           //not in file
////    std::vector<AttValPair> temp3 = a.FindCompatibleAttValPairs(av3);     //test FindCompatibleAttValPairs()
////    for (int i=0; i<temp3.size(); i++)
////        std::cout << temp3[i].attribute << "->" << temp3[i].value << std:: endl;  //should print nothing - no compatible pair
//
//
//    //SOME TESTS FOR MATCHMAKER
//    MatchMaker m(h,a);
//    int threshold = 6;
//    std::vector<EmailCount> results = m.IdentifyRankedMatches("AdoniO6950@aol.com", threshold);
//    if (results.empty())
//        cerr << "We found no one who was compatible" << endl;
//    else
//    {
//        for (const auto& match: results)
//            cerr << match.email << " has " << match.count << " attribute-value pairs in common" << endl;
//    }
//}

