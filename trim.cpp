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

    void calcQscores(string asciiArray) {
        this->qscore.clear();
        for (char& c : asciiArray) {
            this->qscore.push_back((int)c-this->asciiBase);
        }
    }

    int getQscoreAverage() {
        int average=0;
        for (int i : this->getQscore()) {
            average += i;
        }
        average = average/this->getQscore().size();
        return average;
    }

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
    Trimmer(string filename) {
        this->file = ifstream(filename);        
    }

    void getNextLine() { getline(this->file, line); }

    string getName() { return this->name; }
    void setName(string name){ this->name = name; }

    string getSeq(){ return this->seq; }
    void setSeq(string seq){ this->seq = seq; }

    string getLine() { return this->line; }

    vector<int> getQscore() { return this->qscore; }

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
// Example program
// #include <iostream>
// #include <string>
// #include <iterator>
// #include <vector>

// using namespace std;

// template <typename Iterator>
// void doStuff(Iterator begin, Iterator end) {
//     for (begin; begin < end; begin++) {
//         cout << *begin << endl;
//     }
// }

// int main()
// {
//     vector<int> ar;
//     for (int i = 1; i <=5; i++) {
//         ar.push_back(i);   
//     }
    
//     vector<int>::iterator ptr = ar.begin();
//     vector<int>::iterator ptre = ar.end();

//     vector<int>::reverse_iterator itr = ar.rbegin();
//     vector<int>::reverse_iterator itre = ar.rend();

//     doStuff(ptr, ptre);
//     doStuff(itr, itre);

    
//     cout << endl;
//     return 0;
// }