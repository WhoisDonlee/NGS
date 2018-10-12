#include <deque>
#include "trim.h"

Trimmer::Trimmer(string filename, string writeFile) {
    this->file = ifstream(filename);
    this->writeFile = ofstream(writeFile);
}

string Trimmer::getLine() { return this->line; }
string Trimmer::getName() { return this->name; }
string Trimmer::getName2() { return this->name2; };
string Trimmer::getSeq() { return this->seq; }
string Trimmer::getAscii() { return this->ascii; }
vector<int> Trimmer::getQscore() { return this->qscore; }

void Trimmer::setName(string n) { this->name = n; }
void Trimmer::setName2(string n) { this->name2 = n; }
void Trimmer::setSeq(string s) { this->seq = s; }
void Trimmer::setAscii(string a) { this->ascii = a; }

void Trimmer::getNextLine() { getline(this->file, line); }

bool Trimmer::trim() {
    string trimmed;
    this->calcQscores();

    vector<int>::iterator it = this->getQscore().begin();
    vector<int>::iterator ite = this->getQscore().end();
    vector<int>::reverse_iterator rit = this->getQscore().rbegin();
    vector<int>::reverse_iterator rite = this->getQscore().rend();

    this->trimLoop(it, ite);
    this->trimLoop(rit, rite, "reverse");

    if (this->getSeq().size() <= 30) {
        return false;
    }
    return true;
}

void Trimmer::writeToFile() {
    this->writeFile << this->getName() << endl;
    this->writeFile << this->getSeq() << endl;
    this->writeFile << this->getName2() << endl;
    this->writeFile << this->getAscii() << endl;
}

/**
 * Calculates the Qscores acording to the ascii base table and puts them into vector<int> qscore
 * 
 * 
 * @param asciiArray string with ascii symbols representing the qscore
 **/
void Trimmer::calcQscores() {
    this->qscore.clear();
    for (char& c : this->getAscii()) {
        this->qscore.push_back((int)c-this->asciiBase);
    }
}

/**
 * Loops through the vector array with a sliding window
 * Cuts off parts with too low Qscore
 * 
 * @param begin begin of fwd or rev iterator
 * @param end   end of fwd or rev iterator
 * @param rev   trims off the end of the sequence if input = "reverse"
 **/
template <typename Iterator> 
void Trimmer::trimLoop(Iterator begin, Iterator end, string rev) {
    int windowsize=5, minscore=20, total=0, count=0;
    deque<int> subQscore;

    for ( ; begin < end; begin++) {
        subQscore.push_back(*begin);
        total += *begin;
        if (subQscore.size() >= windowsize) {
            if (total > (minscore*windowsize)) {
                if (rev != "reverse") {
                    this->setSeq(this->getSeq().substr(count-(windowsize-1)));
                } else {
                    this->setSeq(this->getSeq().substr(0, (this->getSeq().size()-count)+(windowsize-1)));
                }
                break;
            }
            total -= subQscore[0];
            subQscore.pop_front();
        }
        count++;
    }
}