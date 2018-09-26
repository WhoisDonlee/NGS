#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{

    ifstream file1(argv[1]), file2(argv[2]);
    string line1, line2;

    int i = 0;

    while (!file1.eof())
    {
        getline(file1, line1);
        getline(file2, line2);

        if (line1 == "")
            continue;

        i++;

        cout << "   " << line1 << endl;
        cout << "   " << line2 << endl;
    }
    return 0;
}