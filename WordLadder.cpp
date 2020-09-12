#include "WordLadder.h"

WordLadder::WordLadder(const string & filename){
  ifstream inFS;
  string term;
  inFS.open(filename);
  if (!inFS.is_open()){ //checking if the file opened correctly
    cout << "Error opening " << filename << endl;
    return;
  } 
  while (inFS >> term){ //inFS stores the words from the file into term
    if (term.length() != 5){
      cout << "A terms contains more/less than 5 characters." << endl;
      return;
    }
    dict.push_back(term); //adding term into list
  }
  inFS.close();
}

void WordLadder::outputLadder(const string &start, const string &end, const string &outputFile){
  stack<string> termStack;
  queue<stack<string>> stackQueue;
  stack<string> copyStack;
  string topTerm;
  list<string> outputList;
  ofstream outFS;
  unsigned charDiff = 0;
  outFS.open(outputFile);
  if (!outFS.is_open()){
    cout << "Error opening " << outputFile << endl;
    return;
  }
  if ((termExists(start) == false) || (termExists(end) == false)){ //helper checks if the words aren't in dict
    outFS << "No Word Ladder Found." << endl;
    outFS.close();
    return;
  }
  if (start == end){
    outFS << start << endl;
    outFS.close();
    return;
  }
  termStack.push(start);
  stackQueue.push(termStack);
  while(!stackQueue.empty()){
    termStack = stackQueue.front();
    topTerm = termStack.top(); //nextLine searches for a word that is off by 1 character
    for(list<string>::iterator it = dict.begin(); it != dict.end(); ++it){
        string currentTerm = *it;
        charDiff = 0; //reseting it for each dictionary entry
        for (unsigned i = 0; i < topTerm.length(); ++i){
          if (topTerm.at(i) != currentTerm.at(i)){
            charDiff++;
          }
        }
      if (charDiff == 1){
        //copy oftermStack, push on the currentTerm
        copyStack = termStack;
        copyStack.push(currentTerm);
        if (currentTerm == end){
          //no more in the word ladder
          while(!copyStack.empty()){
            outputList.push_front(copyStack.top());
            copyStack.pop();
          }
          for(list<string>::iterator it = outputList.begin(); it != outputList.end(); ++it){
            outFS << *it << endl;
          }
          outFS.close();
          return;
        }else{
          //enqueue newStack and remove the word from the dict
          stackQueue.push(copyStack);
          it = dict.erase(it);
          --it;
        }
      }
    }
    stackQueue.pop();
  }
  if(stackQueue.empty()){
    outFS << "No Word Ladder Found." << endl;
    outFS.close();
    return;
  }
}


bool WordLadder::termExists(const string & term){ //helper 
  for (list<string>::iterator it = dict.begin(); it != dict.end(); ++it){
    if (*it == term){
      return true;
    }
  }
  return false;
}

// for each word of the dictionary, I want to compare it to the top word i have right now.
// to do so, for each word, compare the different characters btwn the current term and the dict term