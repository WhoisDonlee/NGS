#include "qc.h"

QualityControl::QualityControl(string filename, string writeFile)
{
    this->file = ifstream(filename);
    this->writeFile = ofstream(writeFile);
}

string QualityControl::getLine() const { return this->line; };
string QualityControl::getSeq() { return this->seq; };
int QualityControl::getMin() { return this->min; };
int QualityControl::getAvg() { return this->max; };
int QualityControl::getMax() { return this->avg; };
int QualityControl::getGC() { return this->GC; };

void QualityControl::setSeq(string s) { this->seq = s; };
void QualityControl::setMin(int m) { this->min = m; };
void QualityControl::setMax(int m) { this->max = m; };
void QualityControl::setAvg(int a) { this->avg = a; };
void QualityControl::setGC(int gc) { this->GC = gc; };

void QualityControl::getNextLine() { getline(this->file, line); };
void QualityControl::writeToFile()
{
    this->writeFile << this->getGC() << ": " << this->getSeq() << endl;
}