# Gerrymandering
Each line of districts.txt contains a state name followed by district information in groups of three. The first of the three is the district number, the second is the democratic votes in that district and the third the republican votes in that district. Some states do not number the districts.  For example, any state with one district has a district “number” AL.  Search the text file to see for yourself.  To keep things simple, you should store this single district with the number 1 instead of AL, which is also how it will print in the console.  See test cases for details.  Depending on the size of the state, there will be a different number of districts. For example:

Arkansas,1,63555,124139,2,103477,123073,3,0,151630,4,87742,110789

Alaska,AL,114596,142566

Rhode Island,1,87060,58877,2,105716,63844

Notice that the data is separated with commas (“,”) instead of the spaces. We are using commas because some state names contain spaces and we want to preserve those spaces.  You should use C++ strings and C++’s string library functions.  You should also use C++ streams for file reading.  It is recommended to use getline instead of the insertion operator (<<) for the file reading.  See lecture notes and lab for file reading template code.  The district numbers and the vote counts will always be integers.

Number of eligible voters in each state: eligible_voters.txt

Every state name in districts.txt is also in eligible_voters.txt, so you do not need to worry about a state having district data but no eligible voter data.  If there is a state in eligible_voters.txt but not contained in district.txt, that state should be ignore (should not be stored in your vector, should not be found when search is called, and should not be printed out during load).  Each line of eligible_voters.txt contains a state name, followed by the eligible voter count for that state. For example:

Alabama,3606103

Alaska,519501

Arizona,4738332

Arkansas,2148441

California,25278803

Note:  Your code will be tested on other files of the same format.  Do not assume that the files only have some number of lines, only have US state names, or anything else about the files other than what has been described here about their format. 

Note 2:  Think about how you are going to store this data.  Think about it…now.  Don’t get too deep in file reading and string parsing and calculations before reading through the rest of the project and deciding where you want to put all this.  One ourvector?  Multiple ourvectors?  Structs?  The choice is yours.  No abstractions or data structures are allowed other than ourvecotor.  A little planning will go a long way!

Calculating Gerrymandering

You can determine gerrymandering for states with three or more districts by counting up and comparing the wasted votes cast for each party.  For states with less than three districts, you cannot determine gerrymandering.  We will define a wasted vote as any vote not needed to win the election. That means all votes for the party that loses the district seat are wasted as well as all votes for the winning party other than the “over half” they need to win the majority.  The “over half” is defined as the least number of votes that is over half of the total number of votes in the district.  For example, if there were 10 total votes, then 6 would be over half.  If there were 9 total votes, then 5 would be over half. 
