// WordCount.cpp

#include "WordCount.h"

using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(const std::string& word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int total=0;
	for (size_t i=0; i<CAPACITY; i++){
		total+=table[i].size();
	}
	return total;
}

int WordCount::getNumUniqueWords() const {
	int total=0;
	for (size_t i=0; i<CAPACITY; i++){
		total+=table[i].size();
	}
	return total;
}

int WordCount::getWordCount(const std::string& word) const {
	string w = makeValidWord(word);
	int key = hash(w);
	for (size_t i=0; i<table[key].size(); i++){
		if (w == table[key][i].first){
			return table[key][i].second;
		}
	}
	return 0;
}
	
int WordCount::incrWordCount(const std::string& word) {
	string w = makeValidWord(word);
	if (w==""){
		return 0;
	}
	int key = hash(w);
	for (size_t i=0; i<table[key].size(); i++){
		if (w == table[key][i].first){
			table[key][i].second+=1;
			return table[key][i].second;
		}
	}
	table[key].push_back(pair<string,int>(w, 1));
	return 1;
}

int WordCount::decrWordCount(const std::string& word) {
	string w = makeValidWord(word);
	int key = hash(w);
	for (size_t i=0; i<table[key].size(); i++){
		if (w == table[key][i].first){
			table[key][i].second-=1;
			if (table[key][i].second==0){
				table[key].erase(table[key].begin() + i);
				return 0;
			}
			return table[key][i].second;
		}
	}
	return -1;
}


bool WordCount::isWordChar(char c) {
	if ((c<='z' && c>='a') || (c<='Z' && c>='A')){
		return true;
	}
	return false;
}

std::string WordCount::makeValidWord(const std::string& word) {
		string w;
	for (size_t i=0; i<word.length(); i++){
		if (isWordChar(word[i])){
			if (word[i]<='Z' && word[i]>='A'){
				w+=tolower(word[i]);
			}
			else{
				w+=word[i];
			}
		}
		else{
			if ((word[i] == '\'' || word[i]== '-') && isWordChar(word[i-1]) && isWordChar(word[i+1])){
				w+=word[i];
			}
		}
	}
	return w;
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
		vector<pair<string,int>> temp;
	for (size_t i=0; i<CAPACITY; i++){
		for (size_t j=0; j<table[i].size(); j++){
			temp.push_back(table[i][j]);
		}
	}
	bool sort = false;
	vector<pair<string,int>> other;
	while (sort==false){
		sort = true;
		for (size_t i=0; i<temp.size()-1; i++){
			if (temp[i].first < temp[i+1].first){
				other.push_back(temp[i]);
				temp[i] = temp[i+1];
				temp[i+1] = other[0];
				other.pop_back();
				sort = false;
			}
		}
	}
	for (size_t i=0; i<temp.size(); i++){
		out<<temp[i].first<<","<<temp[i].second<<endl;
	}
	return;
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
		vector<pair<string,int>> temp;
	for (size_t i=0; i<CAPACITY; i++){
		for (size_t j=0; j<table[i].size(); j++){
			temp.push_back(table[i][j]);
		}
	}
	bool sort = false;
	vector<pair<string,int>> other;
	while (sort==false){
		sort = true;
		for (size_t i=0; i<temp.size()-1; i++){
			if (temp[i].second > temp[i+1].second){
				other.push_back(temp[i]);
				temp[i] = temp[i+1];
				temp[i+1] = other[0];
				other.pop_back();
				sort = false;
			}
			else if (temp[i].second == temp[i+1].second){
				if (temp[i].first > temp[i+1].first){
					other.push_back(temp[i]);
					temp[i] = temp[i+1];
					temp[i+1] = other[0];
					other.pop_back();
					sort = false;
				}
			}
		}
	}
	for (size_t i=0; i<temp.size(); i++){
		out<<temp[i].first<<","<<temp[i].second<<endl;
	}
	return;
}

void WordCount::addAllWords(const std::string& text) {
	string bruh;
	for (size_t i=0; i<text.size(); i++){
		if ((text[i] == ' ' || text[i] == '\n' || text[i] == '\t') && bruh!=""){
			incrWordCount(bruh);
			bruh="";
		}
		else{
			bruh+=text[i];
		}
	}
	if (bruh!=""){
		incrWordCount(bruh);
	}
	return;
}
