#include "trim.h"
#include <iostream>

int main(int argc, char **argv)
{
    // Trimmer trimobj1(argv[1], argv[3]);
    // Trimmer trimobj2(argv[2], argv[4]);
    Trimmer trimobj1(argv[1], "trim_output/trim1.fastq");
    Trimmer trimobj2(argv[2], "trim_output/trim2.fastq");

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
            if (trimobj1.trim() && trimobj2.trim())
            {
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