#include "ourvector.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include<iomanip>
#include <cmath>
using namespace std;
//--------------------------------------------------------------------------
// struct for voters where i put in data for the 2nd file
struct voters{
    string state;
    int numbers;
};
//--------------------------------------------------------------------------
// struct for the first data, 2 vectors made to hold Dem and Rep votes
struct districts{
    string state;
    int district;
    ourvector<int> Rep;
    ourvector<int> Dem;
};
//-------------------------------------------------------------------------
// change the string to an int
int changetoNum(string word) {
    int num;
    std::stringstream ss(word);  //  changes it
    ss >> num;  //  puts it in num
    return num;
}
//--------------------------------------------------------------------------
// opens the file if cant then it returns 1
int fileopen(ifstream &file , string name) {
    file.open(name);
    if (!file.is_open()) {
      return 1;  //  1 indicates error
  }
  return 0;
}
//--------------------------------------------------------------------------
// gets the state and it erases that from the line
// the eraser is substr from its starting to when it ends
string getState(string &line) {
    size_t pos = line.find(",");
    string name = line.substr(0, pos);
    line = line.substr(pos+1, line.size()-name.size()-1);
    return name;
}
//--------------------------------------------------------------------------
// gets the district by following the count
// also pushes the vlaues of Dem and Rep
int getDis(string line , ourvector<districts>&v ,
ourvector<int> &Rep, ourvector<int> &Dems) {
    int count = 0;
    while (!line.empty()) {
        string Dem;
        count++;
        size_t pos = line.find(",");
        string st = line.substr(0, pos);
        line = line.substr(pos+1, line.size());
        // st gets use the district then i remove
        // it from the line
        pos = line.find(",");
        Dem = line.substr(0, pos);
        Dems.push_back(changetoNum(Dem));
        line = line.substr(pos+1, line.size());
        // after that i get the Dem cause dem is right
        // after district then i erase that
        pos = line.find(",");
        string var;
        if ((int)pos == -1) {
            var = line;
            line = "";
        } else {
            var = line.substr(0, pos);
            line = line.substr(pos+1, line.size());
        }
        Rep.push_back(changetoNum(var));
        // after Dem i push in Rep and erase that
        // the entire line loops until empty
    }
    return count;
}
//--------------------------------------------------------------------------
// this function i use it to load all the data
void loadData(string filename , ourvector<districts> &d ,
bool &x , districts &tmp) {
    // opens file
    ifstream inFile;
    // if the file cant open then cout this
    if (fileopen(inFile, filename) == 1) {
        x = false;
        cout<< "-----------------------------" << endl << endl;
        cout<< "Invalid first file, try again." << endl;
    } else {
        x = true;
        string line;
        cout<< "-----------------------------" << endl << endl;
        cout<< "Reading: " << filename << endl;
        getline(inFile , line , '\n');
        // if the file opens then i read the first line
        // push it thru a loop until empty
        while (!inFile.eof()) {
        ourvector<int> Reps;
        ourvector<int> Dems;
        string state = getState(line);
        // gets the state
        int x = getDis(line , d , Reps , Dems);
        // gets the regular
        tmp.state = state;
        tmp.district = x;
        tmp.Rep = Reps;
        tmp.Dem = Dems;
        d.push_back(tmp);
        // push it all in and repeat
        getline(inFile , line , '\n');
        }
    }
}
//--------------------------------------------------------------------------
// this is for the 2nd file and gets us the votes
int getVotes(string &line) {
    size_t pos = line.find("\n");
    string name = line.substr(0, pos);
    line = line.substr(pos+1, line.size()-name.size()-1);
    // same process go until end of line is reached and
    // put it in
    int num;
    std::stringstream ss(name);
    ss >> num;
    // converts it into int
    return num;
}
//--------------------------------------------------------------------------
// opens up 2nd file similar method but diff ifs
void loadData1(string &filename, ourvector<voters> &v, bool &x) {
    // opens file
    ifstream inFile;
    // if the first file cant open then x becomes false
    // else if it does then x is still false but couts
    // a statement i do this by using the bool x i passed
    // thru
    if (fileopen(inFile, filename) == 1 || x == false) {
       if (x == true) {
           cout<< "Invalid second file, try again." << endl;
           x = false;
        } else { x = false;
        }
    } else {
        string line;
        cout<< "Reading: " << filename << endl;
        getline(inFile, line, '\n');
    // adds in data to vector until file is empty
    // same process as load
        while (!inFile.eof()) {
            voters tmp;
            string state;
            int votes;
            state = getState(line);
            votes = getVotes(line);
            tmp.state = state;
            tmp.numbers = votes;
            v.push_back({tmp.state, tmp.numbers});
            getline(inFile, line, '\n');
        }
    }
}
//--------------------------------------------------------------------------
// searches for the state
void search(bool &check , ourvector<districts> &v ,
string &sear , string &c) {
    check = false;
    // loops thru vector until it finds the right
    // state if not check is passed as false
     for (auto &e : v) {
            if (e.state == sear) {
                c = sear;
                check = true;
            }
        }
}
//--------------------------------------------------------------------------
// first i make all the letters lower case
// then i capatilzr the first words
void capitalize(string &str) {
	bool check;
	check = false;
	// makes all the letters lower
	for (int i = 1; i < str.length(); ++i) {
        str[i] = std::tolower(str[i]);
    }

	for(int i = 0; i < str.length(); i++) {
	    // this checks if its a new word
		if(check == false && (str.at(i) >= 'a' && str.at(i) <= 'z')) {
			str.at(i) = str.at(i) + 'A'-'a';
		}
		// checks if its a capital now
		if((str.at(i) >= 'a' && str.at(i) <= 'z') ||
		(str.at(i) >= 'A' && str.at(i) <= 'Z')) {
			check = true;
		} else {
			check = false;
		}
	}
}
//-------------------------------------------------------------------------
// statements for printing
void statements(bool &data , bool &x , string &word , string &c) {
        if (data == true) {
            cout<< "Data loaded? Yes" << endl;
        } else if (data != true) {
            cout<< "Data loaded? No" << endl;
        } if (c == "") {
            c = "N/A";
        }
        cout<< "State: "<< c << endl << endl;
}
//-------------------------------------------------------------------------
// rounds up the value
double round(double var) {
    double value = (int) (var * 10000 + .005);
    return (double) value / 10000;
}
//--------------------------------------------------------------------------
// gets the stat and checks if a state is gerrymandered or not
void stats(ourvector<districts> &d , ourvector<voters> &v ,
int &Dw , int &Rw , double &eff , string &party , string &word) {
    int i;
    int x;
    // loop thru and get the index for
    // the state
    for (i = 0; i < d.size(); i++) {
      if (word == d[i].state) {
          break;
       }
    }
    int total = 0;
    int count = 0;
    // loop thru the districts of the state
    for (int j = 0; j < d[i].Dem.size(); j++) {
        count++;
        total += (d[i].Dem[j]+d[i].Rep[j]);
        int half = ((d[i].Dem[j] + d[i].Rep[j]) / 2) + 1;
        // if dem greater then add them while
        // subtracting over half
        if (d[i].Dem[j] > d[i].Rep[j]) {
            Dw += d[i].Dem[j] - half;
            Rw += d[i].Rep[j];
        } else if (d[i].Dem[j] < d[i].Rep[j]) {
            // same process but with Rep 
            Rw += d[i].Rep[j] - half;
            Dw += d[i].Dem[j];
        }
    }
    // loop thru and get the index
    for (x = 0; x < v.size(); x++) {
        if (word == v[x].state) {
            break;
        }
    }
    bool check;
    // if Dem wasted is greater than dem-rep/total
    if (Dw > Rw) {
        eff = (Dw-Rw) / (double)total;
        check = true;
    } else if (Dw < Rw) {
        // same process but Rep greater
        eff = (Rw-Dw) / (double)total;
        check = false;
    }
    // make it into double digits from .003443 etc
    eff = eff * 100;
    cout << endl;
    cout << "-----------------------------"<< endl << endl;
    // if Efficiency is greater than 7 or
    // if theres more than 3 district than cout this
    if (eff > 7 && count >= 3) {
        cout << "Gerrymandered: Yes" << endl;
        if (check == true) {
            int x = eff;
            cout << "Gerrymandered against: Democrats" << endl;
            // turn eff into 6 digits at least
            if (9 >= x) {
                cout << "Efficiency Factor: "<< fixed <<
                setprecision(5)<< eff<< "%"<< endl;
            } else {
                // else do the regular
                cout << "Efficiency Factor: " << fixed <<
                setprecision(4) << eff << "%" << endl;
            }
        } else {
             // else just do this if it has 6 digits
            cout << "Gerrymandered against: Republicans" << endl;
            cout << "Efficiency Factor: " << fixed<<
            setprecision(4) << eff<< "%"<< endl;
        }
    } else if (eff < 7 || count < 3) {
        // if Rep greater same as the Rep
        cout << "Gerrymandered: No" << endl;
    }
    cout << "Wasted Democratic votes: " << Dw << endl;
    cout << "Wasted Republican votes: " << Rw << endl;
    cout << "Eligible voters: " << v[x].numbers << endl << endl;
}
//--------------------------------------------------------------------------
// plots the Dem with D and Rep with R based on the
// overall percentage by districts tho
void plot(ourvector<districts> &d , string &word) {
    int i;
    ourvector<string> k;
    // loop thru until i get the state
    // when i do just break and get index
    for (i = 0; i < d.size(); i++) {
      if (word == d[i].state) {
          break;
      }
    }
    double y = 0;
    // print out the districts
    for (int j = 0; j < d[i].Dem.size(); j++) {
         cout << "District: " << j+1 << endl;
         // if Dem greater than do this
        if (d[i].Dem[j] > d[i].Rep[j]) {
            // get the wasted votes
            y = (double) (d[i].Dem[j]) /
            (double) (d[i].Dem[j] + d[i].Rep[j]) - .005;
            // round it down
            int count = llround(y * 100);
            // loop thru and print out D or R
            for (int k = 0; k < count; k++) {
                cout << "D";
            }
            for (count = count; count < 100; count++) {
                cout << "R";
            }
        } else if (d[i].Dem[j] < d[i].Rep[j]) {
            // same process but with Rep greater than Dem
            y = (double) (d[i].Rep[j]) /
            (double) (d[i].Rep[j] + d[i].Dem[j]) + .005;
            int count = llround(y * 100);
            string back = "";
            // put it in a string called back
            for (int k = 0; k < count; k++) {
                back += "R";
            }
            for (count = count; count < 100; count++) {
                back += "D";
            }
            // then i print everything backwards
            for (int i = 1; i <= back.length(); i++) {
                cout << back[back.length() - i];
            }
        }
        cout << endl;
    }
    cout << endl;
}
//--------------------------------------------------------------------------
void votes(ourvector<districts> &d , string &word) {
    int index;
    for (index = 0; index < d.size(); index++) {
      if (word == d[index].state) {
          break;
      }
    }
    double y;
    double x;
    int total;
    for(int j = 0; j < d[index].Dem.size(); j++){
        total = d[index].Dem[j] + d[index].Rep[j];
        y = (double) (d[index].Dem[j]) / (double) total;
        x = (double) (d[index].Rep[j]) / (double) total;
        cout << "Districts: " << j + 1 << endl;
        cout << "There are " << y * 100 << "%  Democrats " << endl;
        cout << "There are " << x * 100 << "%  Republicans " <<endl << endl;
    }
}
//--------------------------------------------------------------------------
// check if the word matches with the data and return
// true if it matches
bool match(string &word , ourvector<districts>&d) {
    for (int i = 0; i < d.size(); i++) {
        if (d[i].state == word) {
            return true;
        }
    }
    return false;
}
//--------------------------------------------------------------------------
int main() {
    // main code
    districts tmp;
    ourvector<districts> d;
    ourvector<voters> v;
    bool data;
    cout << "Welcome to the Gerrymandering App!" <<endl << endl;
    cout << "Data loaded? No" << endl;
    cout << "State: N/A" << endl << endl;
    cout << "Enter command: ";
    string filename;
    string filename2;
    string command;
    cin >> command;
    // if stat and plot before load then print this
    if (command == "plot" || command == "stats") {
        cout << endl << "-----------------------------" << endl;
        cout << "No data loaded, please load data first." << endl<< endl;
    } if (command == "search") {
        // same with search but added a cin cause it comes with more data
        cin >> command;
        cout << endl << "-----------------------------" << endl;
        cout << "No data loaded, please load data first." << endl << endl;
    } if (command == "load") {
        // if its load than load the data
        cin >> filename;
        cin >> filename2;
        loadData(filename, d, data, tmp);
        // print statements for file 1
        for (int i = 0; i < d.size(); i++) {
            cout << "..."<< d[i].state << "..."<< d[i].district <<
            " districts total" << endl;
        }
        cout << endl;
        // load data for file 2
        loadData1(filename2, v, data);
        // print out for fiel 2
        for (int i = 0; i < v.size(); i++) {
            if (match(v[i].state, d) == true) {
            cout << "..." << v[i].state << "..." <<
            v[i].numbers << " eligible voters" << endl;
            }
        }
        cout<< endl;
    }
    string com;
    bool x = false;
    string word;
    string c;
    // until user doesnt put in exit
    while (com != "exit") {
        // statements line print out
        statements(data, x, word, c);
        cout << "Enter command: ";
        cin >> com;
        // if its load again same as the previous
        // load function same process
        if (com == "load") {
            string tmp1, tmp2;
            cin >> tmp1;
            cin >> tmp2;
            if (data != true) {
                loadData(tmp1, d, data, tmp);
                for (int i = 0; i < d.size(); i++) {
                    cout << "..." << d[i].state << "..." << d[i].district <<
                    " districts total" << endl;
                }
                cout << endl;
                loadData1(tmp2, v, data);
                for (int i = 0; i < v.size(); i++) {
                if (match(v[i].state, d) == true) {
                cout << "..." << v[i].state << "..." <<
                v[i].numbers << " eligible voters" << endl;
                    }
                }
                cout << endl;
            } else {
                // if data is in there then do this
                cout << endl << "-----------------------------" << endl;
                cout << "Already read data in, exit and start over."
                << endl << endl;
            }
        }
        // if its search
        if (com == "search") {
            getline(cin, word);
            // weird bug but theres a emtpy char so i delete it
            word.erase(0, 1);
            // capatalize the words
            capitalize(word);
            cout << "-----------------------------" << endl << endl;
            // if file isnt there then do this
            if (data != true) {
                cout << endl << "-----------------------------" << endl;
                cout << "No data loaded, please load data first."
                << endl << endl;
            } else {
                // look for the state with this function
                search(x, d, word, c);
                // now if state isnt there then do this
                if (x == false) {
                    cout << "State does not exist, search again."
                    << endl << endl;
                }
            }
        }
        // if user puts in stats
        if (com == "stats") {
            // now if theres a state loaded
            if (c != "N/A") {   
                int q = 0;
                int w = 0;
                double a = 0;
                string g;
                // call stats
                stats(d, v, q, w, a, g, word);
            } else {
                // else do this
                cout << endl << "-----------------------------" << endl;
                cout << "No state indicated, please search for state first."
                << endl << endl;
            }
        } 
        if (com == "plot") {
            // if user puts in plot
            // if state exits then do this
            if (c != "N/A") {
                cout << "-----------------------------" << endl << endl;
                capitalize(c);
                plot(d, c);
            } else if (data == false) {
                // if there isnt a data then do this
                cout << endl << "-----------------------------" << endl;
                cout << "No data loaded, please load data first."
                << endl << endl;
            } else {
                // if there isnt a state then do this
                 cout << endl << "-----------------------------" << endl;
                 cout << "No state indicated, please search for state first."
                 << endl << endl;
            }
        } 
        if (com == "Votes") {
            // if user puts in a vote
            if (c != "") {
                votes(d , c);
            } else {
                 cout << endl << "-----------------------------" << endl;
                 cout << "No state indicated, please search for state first."
                 << endl;}
        }
    }
    cout << endl << "-----------------------------" << endl;
    return 0;
}
