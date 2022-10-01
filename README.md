# Unhinged
App to have these basic features:
* It must be able to support up to 100k members
* Each member can have dozens of attribute-value pairs! For example, "occupation" -> "pet stylist" where "occupation" is the attribute and "pet stylist" is the value
* To identify compatible members, the Unhinged app translates a member's attribute-value pairs to a set of compatible attribute-value pairs, then ranks the order of all potential matches for a member by identifying the people with the most compatible attribute-value pairs to that member

Classes used in the app:
* PersonProfile: class that represents a person and all of their attribute-value pairs
* MemberDatabase: class that stores all member's profiles(name, email, attributes for each member)
* AttributeTranslator: a class capable of translating an input attribute(e.g. "hobby" -> "eating") into a set of compatible attributes (e.g. "job" -> "chef", or "hobby" -> "cooking") for potential matches
* MatchMaker: class that identifies and rank-orders matches to other member profiles for a given member
* RadixTree: class that implements a templated map using the radix tree data structure

Example:
Enter the member's email for whom you want to find matches: smbirg@hotmail.com
The member has the following attributes:
hobby --> coding
job --> professor
gender --> male
hobby --> baking
favorite food --> b'stilla
How many shared attributes must matches have? 5
The following members were good matches:
Jamie Lai at jamie_lai24143@hotmail.com with 13 matches! Stephen Li at slee1724@gmail.com with 11 matches!
Emile Gin at egin9389@xfinity.com with 10 matches!
Jame Buoy at jamebuoy2008@gmail.com with 6 matches! Karrie Wong at kw4224@aol.com with 6 matches!
