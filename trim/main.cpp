#include "trim.h"
#include <iostream>
#include <string.h>

int main(int argc, char **argv)
{
    if (strcmp(argv[1], "-h") == 0)
    {
        cout << "Dit script trimt paired reads op basis van phredscore." << endl;
        cout << "Het script wordt als volgt aangeroepen: ./trim.out <sample_1.fastq> <sample_2.fastq> <output_1.fastq> <output_2.fastq>" << endl;
        cout << "Voorbeeld: ./trim.out infected_1.fq infected_2.fq inf_trim_1.fq inf_trim_2.fq" << endl;
    }
    else
    {

        Trimmer trimobj1(argv[1], argv[3]);
        Trimmer trimobj2(argv[2], argv[4]);
        // Trimmer trimobj1(argv[1], "out_testbestand1trim.fastq");
        // Trimmer trimobj2(argv[2], "out_testbestand2trim.fastq");

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
    }
    return 0;
}