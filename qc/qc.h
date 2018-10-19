#ifndef QC_H
#define QC_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class QualityControl
{
private:
  string seq, line;
  int GC, min, max, avg;
  vector<int> consensusGC;

  ofstream writeFile;

  void addToConsensus();

public:
  QualityControl(string filename, string writeFile);

  ifstream file;

  string getLine() const;
  string getSeq();
  int getMin();
  int getMax();
  int getAvg();
  int getGC();
  vector<int> getConsensus();

  void setSeq(string s);
  void setMin(int m);
  void setMax(int m);
  void setAvg(int a);
  void setGC(int gc);

  void getNextLine();
  void writeToFile();

  int calcGC();
};

#endif // QC_H

/**
 * open file
 * read per line
 *  calc GC
 *  add consensus
 * Min
 * Max
 * Avg 
 **/
