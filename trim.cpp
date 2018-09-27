#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{

    ifstream file1(argv[1]), file2(argv[2]);
    string line1, line2;

    int count = 0;

    string name1, name2;
    string seq1, seq2;
    vector<int> qscore1, qscore2;

    while (!file1.eof())
    {
        getline(file1, line1);
        getline(file2, line2);

        if (line1 == "")
            continue;

        switch (count)
        {
        case 0:
            name1 = line1, name2 = line2;
            break;
        case 1:
            seq1 = line1, seq2 = line2;
            break;
        case 2:
            break;
        case 3:
            qscore1.push_back(count);
            qscore2.push_back(count);
            cout << name1 << endl
                 << seq1 << endl;
            cout << name2 << endl
                 << seq2 << endl;
            break;
        default:
            break;
        }

        count < 3 ? count++ : count = 0;
    }
    return 0;
}