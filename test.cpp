#include "WordCount.h"
#include "tddFuncs.h"
#include <iostream>
#include <sstream>
using namespace std;

int main() {
	cout << "Testing"<< endl;
	
	WordCount second;
	ostringstream s1;
	ostringstream s2;
	s1 << "a,1\nis,1\nfu'n,2\nsentence,2\n";
	second.addAllWords("Sentence is a fu'n fu'n sentence");
	second.dumpWordsSortedByOccurence(s2);
	string result1 = s1.str();
	string result2 = s2.str();
	ASSERT_EQUALS(result1, result2);

	WordCount third;
	ostringstream s3;
	ostringstream s4;
	s3 << "sentenc'e,2\nis,1\na,1\n";
	third.addAllWords("Sentenc'e is a sentenc'e");
	third.dumpWordsSortedByWord(s4);
	string result3 = s3.str();
	string result4 = s4.str();
	ASSERT_EQUALS(result3, result4);

}