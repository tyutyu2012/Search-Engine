#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <string.h>
using namespace std;

const int TABLE_SIZE = 90000;

// struct to store term weight and docId
struct result {
  double termW;
  string docId;
};

// this is used to sort (vector of results) using term weight
struct by_termW {
    bool operator()(result const &a, result const &b) {
        return a.termW > b.termW;
    }
};

// hash function to find the index
long hashIndex(string Key){
  unsigned long Sum = 0;
  unsigned long Index;


   // add all the characters of the key together
   for (int i=0; i < Key.length(); i++)
      Sum = (Sum * 19) + Key[i];  // Mult sum by 19, add byte value of char

   Index = Sum % TABLE_SIZE;

   return Index;
}

// downcase all the input
string downcase(string token)
{
  string downcaseString = "";
  for(int i = 0; i < token.length(); i++)
  {
    if(token.at(i) <= 'Z' && token.at(i) >= 'A')
      downcaseString += (token.at(i) - ('Z' - 'z'));
    else
      downcaseString += token.at(i);
  }
  //cout << downcaseString << endl;
  return downcaseString;
}

int main(int argc, char *argv[])
{
  // open dict file and posting file
  ifstream dicFile("dict.txt");
  ifstream postingFile("posting.txt");

  //vector of results, this will store all the data found by the query
  vector<result> vectorResult;

  //map and set are used when there are more than two parameters
  unordered_map<string, double> umap;
  set<string> values;

  if(argc == 2) {
    // downcase the input token
    string inputToken = downcase(argv[1]);
    // use seekg to find the location, 71 because i setw to this specific value
    dicFile.seekg(hashIndex(inputToken) * 71);

    // initialize variables to hold token, #doc, and start index
    string token;
    int numberOfDocument, startIndex;
    // read the file
    dicFile >> token >> numberOfDocument >> startIndex;

    // if the token is -1, that means value is not exist, end the query
    if(token == "-1") {
      cout << "not found" << endl;
      return 0;
    }

    int probing = 0;
    // probe 100 times, if token = -1, return no found
    while(token != inputToken && probing < 100) {
      dicFile >> token >> numberOfDocument >> startIndex;
      probing ++;
      if(token == "-1"){
        cout << "not found" << endl;
        return 0;
      }
    }
    // if probes 100 times, it's probably not there
    if(probing > 99) {
      cout << "not found" << endl;
      return 0;
    }

    //cout << setw(50) << "token" << setw(10) << "#D" << setw(15) << "sIndex" << endl;
    //cout << setw(50) << token << setw(10) << numberOfDocument << setw(15) << startIndex << endl;

    // use the index from dict to the find to the location of the posting file
    postingFile.seekg(startIndex * 36);
    string docId;
    int freq;
    double termW;
    //cout << setw(10) << "docId" << setw(10) << "freq" << setw(15) << "termW" << endl;

    // store all the result into vectorResult
    for(int i = 0; i < numberOfDocument; i++) {
      postingFile >> docId >> freq >> termW;
      //cout << setw(10) << docId << setw(10) << freq << setw(15) << termW << endl;
      result r;
      r.termW = termW;
      r.docId = docId;
      vectorResult.push_back(r);
    }

    // sort the vectorResult by term weight
    sort(vectorResult.begin(), vectorResult.end(), by_termW());

    // only print the top 10 result
    int showList = vectorResult.size();
    if(showList > 10){
      showList = 10;
    }
    //cout << setw(10) << "docId" << setw(15) << "docName" << setw(15) << "weight" << endl;

    cout << "<form method=\"post\"><center><input type=\"Text\" value="<< argv[1] << " placeholder =\"search here\"></center></form>";
    for(int i = 0; i < showList; i++) {
      string docName = vectorResult.at(i).docId + ".html";
      string href ="href=\"http://www.csce.uark.edu/~sgauch/5533/files/" + docName + "\"";
      //cout << setw(10) << vectorResult.at(i).docId << setw(15) << docName << setw(15) << vectorResult.at(i).termW << endl;
      //cout << vectorResult.at(i).docId <<" " <<vectorResult.at(i).termW << endl;
      cout <<"<a " << href  << ">";
      cout << "<h3>" << docName <<"</h3></a>";
      cout << "<h4>http://www.csce.uark.edu/~sgauch/5533/files/";
      cout << "  term weight: "<<vectorResult.at(i).termW ;
      cout << "</h4>";
    }
    cout << "<div class=\"center1\"><div class=\"pagination\"><a href=\"#\">&laquo;</a><a href=\"#\" class=\"active\">1</a><a href=\"#\" >2</a><a href=\"#\">3</a><a href=\"#\">4</a><a href=\"#\">&raquo;</a></div></div>";
  }
  else if(argc > 2) {

    for(int i = 1; i < argc; i++) {
          // downcase the input token
          string inputToken = downcase(argv[i]);
          // use seekg to find the location, 71 because i setw to this specific value
          dicFile.seekg(hashIndex(inputToken) * 71, ios::beg);

          string token;
          int numberOfDocument, startIndex;
          dicFile >> token >> numberOfDocument >> startIndex;
          int probing = 0;
          // probe 100 times, if token = -1, return no found
          while(token != inputToken && probing < 100) {
            dicFile >> token >> numberOfDocument >> startIndex;
            probing ++;
            if(token == "-1"){
              //cout << "not found" << endl;
              break;
            }
          }

          if(probing < 100) {
            //cout << setw(50) << "token" << setw(10) << "#D" << setw(15) << "sIndex" << endl;
            //cout << setw(50) << token << setw(10) << numberOfDocument << setw(15) << startIndex << endl;

            // use the index from dict to the find to the location of the posting file
            postingFile.seekg(startIndex * 36);
            string docId;
            int freq;
            double termW;
            //cout << setw(10) << "docId" << setw(10) << "freq" << setw(15) << "termW" << endl;

            // store all the docId into a set
            // store term weight into hash table, easy for addition
            for(int i = 0; i < numberOfDocument; i++) {
              postingFile >> docId >> freq >> termW;
              //cout << setw(10) << docId << setw(10) << freq << setw(15) << termW << endl;
              values.insert(docId);

              if (umap.find(docId) == umap.end()) {
                //cout << docId << " not found\n\n";
                umap[docId] = termW;

              }
              // If key found then iterator to that key is returned
              else {
                //cout << "Found " << docId << "\n\n";
                //cout << "termW is " << umap.at(docId) << endl;
                umap[docId] = termW + umap.at(docId);
              }
            }
          }
        }
        // for every value in set values, add the termW and docId into vector result
        for (auto value : values) {
          result r;
          r.termW = umap.at(value);
          r.docId = value;
          vectorResult.push_back(r);
        }

        // sort the vector result
        sort(vectorResult.begin(), vectorResult.end(), by_termW());
        int showList = vectorResult.size();
        if(showList > 10){
          showList = 10;
        }
        //print out the top 10
        cout << "<form method=\"post\"><center><input type=\"Text\" value=\""<< argv[1] << " " << argv[2] << "\"" << " placeholder =\"search here\"></center></form>";
        for(int i = 0; i < showList; i++) {
          string docName = vectorResult.at(i).docId + ".html";
          string href ="href=\"http://www.csce.uark.edu/~sgauch/5533/files/" + docName + "\"";
          //cout << setw(10) << vectorResult.at(i).docId << setw(15) << docName << setw(15) << vectorResult.at(i).termW << endl;
          //cout << vectorResult.at(i).docId <<" " <<vectorResult.at(i).termW << endl;
          cout <<"<a " << href  << ">";
          cout << "<h3>" << docName <<"</h3></a>";
          cout << "<h4>http://www.csce.uark.edu/~sgauch/5533/files/" << docName;
          cout << "term weight: "<<vectorResult.at(i).termW ;
          cout << "</h4>";
        }
        cout << "<div class=\"center1\"><div class=\"pagination\"><a href=\"#\">&laquo;</a><a href=\"#\" class=\"active\">1</a><a href=\"#\" >2</a><a href=\"#\">3</a><a href=\"#\">4</a><a href=\"#\">&raquo;</a></div></div>";

  }
  return 0;
}
