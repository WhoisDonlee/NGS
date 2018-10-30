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
  int GC;
  int min = 0;
  int max = 0;
  int avg = 0;
  int totalLength = 0;
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
  int getTotalLength();
  vector<int> getConsensus();

  void setSeq(string s);
  void setMin(int m);
  void setMax(int m);
  void setAvg(int a);
  void setGC(int gc);
  void addTotalLength(int t);

  void getNextLine();
  void writeToFile(string line);

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
