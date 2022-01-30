#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

struct Interval
{
  int beg {}, end{};
  Interval(int bt, int et): beg{bt}, end{et} {}
};

struct Point
{
  int index {}, value {};
  string type {};

  Point(int pos, int time, string side): index{pos}, value{time}, type{side} {}

  bool operator<(const Point& p) const {
    return (this->value < p.value);
  }
};

std::tuple<string, string> parse(string s, string delim)
{
  // Return two strings separated by a delimiter
  int ipos = s.find(delim);
  string s1 = s.substr(0, ipos);
  string s2 = s.substr(ipos+size(delim), size(s));
  return std::make_tuple(s1, s2);
}

void get_intervals(string s, vector<Interval>& arr)
{
  // Get beginning and ending times
  string beginTime, endTime;
  std::tie(beginTime, endTime) = parse(s, " - ");

  // Get hour and minute for beginning time
  string shr, smin;
  std::tie(shr, smin) = parse(beginTime, ":");
  int ihr = std::stoi(shr);
  int imin = std::stoi(smin);
  int btime = ihr*100 + imin;

  // Get hour and minute for ending time
  std::tie(shr, smin) = parse(endTime, ":");
  ihr = std::stoi(shr);
  imin = std::stoi(smin);
  int etime = ihr*100 + imin;

  arr.push_back(Interval(btime, etime));
}


void get_overlapping_intervals(const vector<Interval>& input, vector<Interval>& output)
{
  // Elements of p are end points of all intervals
  vector<Point> p;
  for (int i=0; i!=size(input); i++) {
    p.push_back(Point(i, input[i].beg, "beg"));
    p.push_back(Point(i, input[i].end, "end"));
  }
  // Sort the elements of p according to time: O(NlogN)
  std::sort(p.begin(), p.end());

  bool added;
  int openInterval = -1;

  // Find overlapping intervals: O(N)
  for (int i=0; i!=size(p); i++) {
    int index = p[i].index;
    if (p[i].type == "beg") {
      if (openInterval == -1) {
        openInterval = index;
        added = false;
      }
      else {
        output.push_back(input[index]);
        if (!added) {
          output.push_back(input[openInterval]);
          added = true;
        }
        if (input[index].end > input[openInterval].end) {
          openInterval = index;
          added = true;
        }
      }
    }
    else if (p[i].type == "end") {
      if (index == openInterval) {
        openInterval = -1;
        added = false;
      }
    }
  }
}

int main()
{
  // Get intervals from a text file
  std::ifstream infile("schedule.txt");
  string line;
  vector<Interval> iarr;
  while (std::getline(infile, line)) {
    get_intervals(line, iarr);
  }

  // Print out the intervals
  std::cout << "*** Intervals ***" << std::endl;
  std::cout << "start_time, end_time" << std::endl;
  for (Interval n : iarr) std::cout << n.beg << ", " << n.end << std::endl;
  std::cout << '\n';

  // Get overlapping intervals
  vector<Interval> oarr;
  get_overlapping_intervals(iarr, oarr);

  // Print out the overlapping intervals
  std::cout << "*** Overlapping intervals ***" << std::endl;
  std::cout << "start_time, end_time" << std::endl;
  for (Interval n : oarr) std::cout << n.beg << ", " << n.end << std::endl;

  return 0;
}
