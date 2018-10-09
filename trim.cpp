#include <iostream>
#include <fstream>
#include <vector>
#include <deque>

using namespace std;

class Trimmer {
private:
    int asciiBase = 64;
    string name;
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
    void calcQscores(string asciiArray) {
        this->qscore.clear();
        for (char& c : asciiArray) {
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
                        cout << "pre:\t" << this->getSeq() << endl;
                        this->setSeq(this->getSeq().substr(count-(windowsize-1)));
                        cout << "done:\t" << this->getSeq() << endl;
                    } else {
                        cout << "pre:\t" << this->getSeq() << endl;
                        this->setSeq(this->getSeq().substr(0, (this->getSeq().size()-count)+(windowsize-1)));
                        cout << "done:\t" << this->getSeq() << endl;
                    }
                    break;
                }
                total -= subQscore[0];
                subQscore.pop_front();
            }
            count++;
        }
        cout << endl;
    }

public:
    ifstream file;

    /**
     * Trimmer class constructor
     * 
     * @param filename  path to fastq file
     **/
    Trimmer(string filename) {
        this->file = ifstream(filename);        
    }

    void getNextLine() { getline(this->file, line); }

    string getName() { return this->name; }
    void setName(string name){ this->name = name; }

    string getSeq(){ return this->seq; }
    void setSeq(string seq){ this->seq = seq; }

    vector<int> getQscore() { return this->qscore; }
    void clearQscore() { this->qscore.clear(); }

    string getLine() { return this->line; }

    vector<int> getQscore() { return this->qscore; }

    /**
     * main trim function
     * Calls method to calculate qscore, creates fwd and rev iterators, calls trimLoop (fwd/rev)
     * Checks if trimmed read size is high enough
     * 
     * @param asciiArray    ascii string used to calculate qscores in calcQscores(asciiArray)
     **/
    bool trim(string asciiArray) {
        string trimmed;
        this->calcQscores(asciiArray);

        // if(this->getQscoreAverage() < 20) {
        //     return false;
        // }

        vector<int>::iterator it = this->getQscore().begin();
        vector<int>::iterator ite = this->getQscore().end();
        vector<int>::reverse_iterator rit = this->getQscore().rbegin();
        vector<int>::reverse_iterator rite = this->getQscore().rend();

        cout << this->getSeq() << endl;

        trimLoop(it, ite);
        trimLoop(rit, rite, "reverse");

        if (this->getSeq().size() <= 30) {
            return false;
        }        
        return true;
    }
};

int main(int argc, char **argv)
{
    Trimmer trimobj1(argv[1]);
    Trimmer trimobj2(argv[2]);

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
            break;
        case 3:
            if(trimobj1.trim(trimobj1.getLine()) && trimobj2.trim(trimobj2.getLine())) {
                cout << "Both true" << endl;
                cout << trimobj1.getName() << endl;
                cout << trimobj2.getName() << endl;
            }
            // trimobj1.trim(trimobj1.getLine());
            // trimobj2.trim(trimobj2.getLine());
            // cout << trimobj1.getName() << endl << trimobj1.getSeq() << endl;
            // cout << trimobj2.getName() << endl << trimobj2.getSeq() << endl;
            break;
        default:
            break;
        }

        count < 3 ? count++ : count = 0;
    }
    return 0;
}