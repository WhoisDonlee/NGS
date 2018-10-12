#include <fstream>
#include <vector>

using namespace std;

class Trimmer {
    private:
        int asciiBase = 64;
        string name, name2, seq, ascii, line;
        vector<int> qscore;

        ofstream writeFile;

        void calcQscores();
        int getQscoreAverage();

        template <typename Iterator>
        void trimLoop(Iterator begin, Iterator end, string rev = "forward");

    public:
        Trimmer(string filename, string writeFile);
        
        ifstream file;
        
        string getLine();
        string getName();
        string getName2();
        string getSeq();
        string getAscii();
        vector<int> getQscore();

        void setName(string n);
        void setName2(string n);
        void setSeq(string s);
        void setAscii(string a);

        void getNextLine();
        void writeToFile();
        bool trim();


};