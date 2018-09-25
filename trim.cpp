#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {
    // loops through command line arguments (filenames)
    for(int i = 1; i < argc; i++)
    {
        int count = 0;

        ifstream ifile(argv[i]);
        string line;

        // loops through file lines
        while(ifile >> line) {
            if (count==4) {
                count = 0;
            }
                cout << line[0] << count << endl;

            // cout << line << endl;
            count++;
        }
        cout << argv[i] << endl;

        int num = '!';
        cout << num;
    }

    
    
}