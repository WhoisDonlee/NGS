#include "qc.h"
#include <iostream>

void loopFile(QualityControl &qc);

int main(int argc, char **argv)
{
    QualityControl qc1(argv[1], "qc_output/file1.qc");
    QualityControl qc2(argv[2], "qc_output/file2.qc");

    loopFile(qc1);
    loopFile(qc2);

    return 0;
};

void loopFile(QualityControl &qc)
{
    int count = 0;
    while (!qc.file.eof())
    {
        qc.getNextLine();

        if (qc.getLine() == "")
            continue;

        switch (count)
        {
        case 1:
            qc.setSeq(qc.getLine());
            cout << qc.calcGC() << "%:\t" << qc.getSeq() << endl;
            // qc.getGC();
            // cout << qc.getSeq();

            break;
        default:
            break;
        }
        count < 3 ? count++ : count = 0;
    }
    for (int i : qc.getConsensus())
    {
        cout << i << " ";
    }
    cout << endl;
}
/**
 * open file
 * read per line
 *  calc GC
 *  add consensus
 * Min
 * Max
 * Avg 
 **/