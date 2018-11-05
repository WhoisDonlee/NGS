#include "qc.h"
#include <iostream>

void loopFile(QualityControl &qc);

int main(int argc, char **argv)
{
    // QualityControl qc1(argv[1], "out_testbestand1.qc");
    // QualityControl qc2(argv[2], "out_testbestand2.qc");
    QualityControl qc1(argv[1], argv[3]);
    QualityControl qc2(argv[2], argv[4]);

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
            qc.writeToFile(to_string(qc.calcGC()) + "%:\t" + qc.getSeq());
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

    qc.writeToFile("Min: " + to_string(qc.getMin()));
    qc.writeToFile("Max: " + to_string(qc.getMax()));
    qc.writeToFile("Avg: " + to_string(qc.getTotalLength() / total));
    qc.writeToFile("GC% per position:");
    string consensus;
    for (int i : qc.getConsensus())
    {
        consensus += to_string(100 * i / total) + "%\t";
    };
    qc.writeToFile(consensus);
}