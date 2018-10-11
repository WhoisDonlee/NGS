#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

class Trimmer {
private:
    int asciiBase = 64;
    string name;
    string name2;
    string seq;
    string ascii;
    vector<int> qscore;

    string line;

    /**
     * Calculates the Qscores acording to the ascii base table and puts them into vector<int> qscore
     * 
     * 
     * @param asciiArray string with ascii symbols representing the qscore
     **/
    void calcQscores() {
        this->qscore.clear();
        for (char& c : this->getAscii()) {
            this->qscore.push_back((int)c-this->asciiBase);
        }
    }

    /**
     * Calculates the average qscore of the qscore vector
     **/
    int getQscoreAverage() {
        int average=0;
        for (int i : this->getQscore()) {
            average += i;
        }
        average = average/this->getQscore().size();
        return average;
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
    void trimLoop(Iterator begin, Iterator end, string rev = "forward") {

        int windowsize=5, minscore=20, total=0, count=0;
        deque<int> subQscore;

        for ( ; begin < end; begin++) {
            subQscore.push_back(*begin);
            total += *begin;
            if (subQscore.size() >= windowsize) {
                if (total > (minscore*windowsize)) {
                    if(rev != "reverse") {
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
        // cout << endl;
    }

public:
    ifstream file;
    ofstream writeFile;

    /**
     * Trimmer class constructor
     * 
     * @param filename  path to fastq file
     **/
    Trimmer(string filename, string writeFile) {
        this->file = ifstream(filename);        
        this->writeFile = ofstream(writeFile);
    }

    void getNextLine() { getline(this->file, line); }

    string getName() { return this->name; }
    void setName(string name){ this->name = name; }

    string getName2() { return this->name2; }
    void setName2(string name){ this->name2 = name; }

    string getSeq(){ return this->seq; }
    void setSeq(string seq){ this->seq = seq; }

    string getAscii() { return this->ascii; }
    void setAscii(string ascii){ this->ascii = ascii; }

    vector<int> getQscore() { return this->qscore; }
    void clearQscore() { this->qscore.clear(); }

    string getLine() { return this->line; }

    /**
     * main trim function
     * Calls method to calculate qscore, creates fwd and rev iterators, calls trimLoop (fwd/rev)
     * Checks if trimmed read size is high enough
     * 
     * @param asciiArray    ascii string used to calculate qscores in calcQscores(asciiArray)
     **/
    bool trim() {
        string trimmed;
        this->calcQscores();

        // if(this->getQscoreAverage() < 20) {
        //     return false;
        // }

        vector<int>::iterator it = this->getQscore().begin();
        vector<int>::iterator ite = this->getQscore().end();
        vector<int>::reverse_iterator rit = this->getQscore().rbegin();
        vector<int>::reverse_iterator rite = this->getQscore().rend();

        // cout << this->getSeq() << endl;

        trimLoop(it, ite);
        trimLoop(rit, rite, "reverse");

        if (this->getSeq().size() <= 30) {
            return false;
        }        
        return true;
    }

    void writeToFile() {
        this->writeFile << this->getName() << endl;
        this->writeFile << this->getSeq() << endl;
        this->writeFile << this->getName2() << endl;
        this->writeFile << this->getAscii() << endl;
    }
};

int main(int argc, char **argv)
{
    Trimmer trimobj1(argv[1], "trim_output/test1.trim");
    Trimmer trimobj2(argv[2], "trim_output/test2.trim");

    int count = 0;

    while (!trimobj1.file.eof())
    {
        trimobj1.getNextLine();
        trimobj2.getNextLine();

        if (trimobj1.getLine() == "")
            continue;

        switch (count)
        {
        case 0:
            trimobj1.setName(trimobj1.getLine());
            trimobj2.setName(trimobj2.getLine());
            break;
        case 1:
            trimobj1.setSeq(trimobj1.getLine());
            trimobj2.setSeq(trimobj2.getLine());
            break;
        case 2:
            trimobj1.setName2(trimobj1.getLine());
            trimobj2.setName2(trimobj2.getLine());
            break;
        case 3:
            trimobj1.setAscii(trimobj1.getLine());
            trimobj2.setAscii(trimobj2.getLine());
            if(trimobj1.trim() && trimobj2.trim()) {
                trimobj1.writeToFile();
                trimobj2.writeToFile();
            }
            break;
        default:
            break;
        }

        count < 3 ? count++ : count = 0;
    }
    return 0;
}