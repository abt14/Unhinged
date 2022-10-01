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
<br />Enter the member's email for whom you want to find matches: sm<span>birg<span>@hotmail.com
<br />The member has the following attributes:
<br />hobby --> coding
<br />job --> professor
<br />gender --> male
<br />hobby --> baking
<br />favorite food --> b'stilla
<br />How many shared attributes must matches have? 5
<br />The following members were good matches:
<br />Jamie Lai at jamie_lai<span>24143<span>@hotmail.com with 13 matches! 
<br />Stephen Li at slee<span>1724<span>@gmail.com with 11 matches!
<br />Emile Gin at egin<span>9389<span>@xfinity.com with 10 matches!
<br />Jame Buoy at jame<span>buoy2008<span>@gmail.com with 6 matches! 
<br />Karrie Wong at kw<span>4224<span>@aol.com with 6 matches!
