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
        int posStart, posEnd, windowsize=5, minscore=20, total=0, count=0;
        deque<int> subQscore;
        this->calcQscores(asciiArray);
        // TODO
        // if(vectoraverage < 20) {
        //     return false;
        // }

        for (int i : this->getQscore()) {
            subQscore.push_back(i);
            total += i;
            if (subQscore.size() >= windowsize) {
                if (total > (minscore*windowsize)) {
                    trimmed = this->getSeq().substr(count-(windowsize-1));
                    goto Return;
                }
                total -= subQscore[0];
                subQscore.pop_front();
            }
            count++;
       }
       Return:
        if (trimmed.size() <= 30) {
            return false;
        }        
        return true;
        // this->setSeq(trimmed); 
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