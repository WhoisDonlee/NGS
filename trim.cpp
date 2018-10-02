#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Trimmer {
private:
    int asciiBase = 64;
    string name;
    string seq;
    string ascii;
    vector<int> qscore;

    string line;

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

    vector<int> getQscore() { return this->qscore; }
    void clearQscore() { this->qscore.clear(); }

    string getLine() { return this->line; }

    vector<int> calcQscores(string asciiArray) {
        for (char& c : asciiArray) {
            this->qscore.push_back((int)c-this->asciiBase);
        }
        return this->qscore;
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
            trimobj1.calcQscores(trimobj1.getLine());
            trimobj2.calcQscores(trimobj2.getLine());
            
            cout << trimobj1.getName() << endl << trimobj1.getSeq() << endl;
            cout << trimobj2.getName() << endl << trimobj2.getSeq() << endl;

            trimobj1.clearQscore();
            trimobj2.clearQscore();
            break;
        default:
            break;
        }

        count < 3 ? count++ : count = 0;
    }
    return 0;
}