#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    // loops through command line arguments (filenames)
    for(int i = 1; i < argc; i++)
    {
        int count = 0;
        string id;
        string seq;
        vector<int> qscore;

        ifstream ifile(argv[i]);
        string line;

        // loops through file lines
        while(ifile >> line) {
            // cout << count << line << endl;
            
            cout << count << " : "; 
            switch (count)
            {
                case 0:
                    cout << line << endl;
                    break;
            
                case 1:
                    cout << line << " ASD " << endl;
                    break;

                case 2:
                    cout << "+++++++++++++++++++" << endl;
                    break;

                case 3:
                    cout << "ASCIIIIIIIIIIIIIIIIIIIIII" << endl;
                    break;

                default:
                    break;
            }

            count < 3 ? count++ : count=0;  
        }
        cout << argv[i] << endl;

        // int num = '!';
        // cout << num;
    }

    
    
}

int getQscore(string seq) {

}