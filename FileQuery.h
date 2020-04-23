#ifndef _FILEQUERY_H_
#define _FILEQUERY_H_



#include <iostream>
#include <vector>
using namespace std;

class FileQuery
{
public:
	FileQuery(const string& filename);
	void PrintSentencesOrdered();
	void PrintSentencesFiltered(const string& str);
	void PrintWordCount();
	void ReplaceWord(const string& old_word, const string& new_word);
	~FileQuery() { cout << "Filequery对象被析构" << endl; }
private:
	vector<string> sentences_;
	string file_name;
};

#endif 