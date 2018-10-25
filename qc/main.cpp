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
    int total = 0;
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
            cout << qc.getSeq().length() << " : " << qc.getMax() << endl;
            if (qc.getSeq().length() > qc.getMax())
            {
                qc.setMax(qc.getSeq().length());
            }
            else if ((qc.getSeq().length() < qc.getMin()) || (qc.getMin() == 0))
            {
                qc.setMin(qc.getSeq().length());
            }
            qc.addTotalLength(qc.getSeq().length());
            total++;

            break;
        default:
            break;
        }
        count < 3 ? count++ : count = 0;
    }

    cout << "Min: " << qc.getMin() << endl;
    cout << "Max: " << qc.getMax() << endl;
    cout << "Avg: " << qc.getTotalLength() / total << endl;
    cout << "GC% per position: " << endl;
    for (int i : qc.getConsensus())
    {
        cout << 100 * i / total << "%\t";
    };
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