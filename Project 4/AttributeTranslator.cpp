// Name: Annie Tran
// UID: 905717479
// Project 4: Unhinged
// AttributeTranslator.cpp

#include "AttributeTranslator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

AttributeTranslator::AttributeTranslator()
{
    pair=nullptr;
}
AttributeTranslator::~AttributeTranslator()
{
    delete pair;
}
bool AttributeTranslator::Load(std::string filename)
{
    std::ifstream infile(filename);
    if (!infile)
        return false;
    else
    {
        std::string line, srcKey, srcAtt, srcVal, comAtt, comVal;
        while (getline(infile, line))
        {
            std::istringstream iss(line);
            std::getline(iss, srcAtt, ',');
            std::getline(iss,srcVal, ',');
            srcKey = srcAtt+srcVal;
            std::getline(iss, comAtt, ',');
            std::getline(iss,comVal, ',');
            
            AttValPair compareAV(comAtt, comVal);
            std::vector<AttValPair> *compatible = compatibleRT.search(srcKey);
            if (compatible != nullptr) //pairs already exists
            {
               if (std::find(compatible->begin(), compatible->end(), compareAV) == compatible->end())
               {
                   pair = new AttValPair(comAtt, comVal);
                   compatible->push_back(*pair);
               }
            }
            else                    //key doesn't exist yet
            {
                std::vector<AttValPair> compatible;     //create a vector to hold compatible pairs
                pair = new AttValPair(comAtt, comVal);
                compatible.push_back(*pair);           //push compatible pair to vector
                compatibleRT.insert(srcKey, compatible); //insert source key and vector into radix tree
            }
        }
    }
    return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
    std::string key, att, val;
    att = source.attribute;
    val = source.value;
    key = att+val;          //add together to use as a key when mapping with RadixTree
    if (compatibleRT.search(key) == nullptr) //key is not there
    {
        std::vector<AttValPair> compatible;
        return compatible;
    }
    else
    {
        std::vector<AttValPair> *compatible;
        compatible = compatibleRT.search(key);
        return *compatible;                 //returns the whole vector
    }
}
