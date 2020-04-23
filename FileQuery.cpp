#include <iostream>
#include <vector>
#include "FileQuery.h"
#include <fstream>
#include <map>
#include <string>
using namespace std;

FileQuery::FileQuery(const string& filename) :file_name{ filename }
{
	
	string text, content = "", punctuation = "，。,.";
	vector<string> file_content;
	ifstream f;
	f.open(filename);

	//将文件中的句子放进content字符串中
	while (getline(f, text))
		file_content.push_back(text);
	for (unsigned int i = 0; i < file_content.size(); i++)
		content += file_content[i];

	//从content中提取出句子
	unsigned int start_pos = content.find_first_not_of(punctuation);
	while (start_pos != content.npos)
	{
		unsigned int end_pos = content.find_first_of(punctuation, start_pos);
		string sentence = content.substr(start_pos, end_pos - start_pos);
		if (sentence[0] == ' ')
			sentence = sentence.erase(0, 1);
		sentences_.push_back(sentence);
		start_pos = content.find_first_not_of(punctuation, end_pos);
	}
	f.close();
}




void FileQuery::PrintSentencesOrdered()
{
	vector<string> copy_file = sentences_;
	string t = "";

	//对sentences_的复制copy_file按字典顺序排序后输出
	for (unsigned int i = 0; i < copy_file.size(); i++)
	{
		for (unsigned int j = i; j < copy_file.size(); j++)
		{
			if (copy_file[i] > copy_file[j])
			{
				t = copy_file[i];
				copy_file[i] = copy_file[j];
				copy_file[j] = t;
			}
		}
	}
	cout << "文本按字典顺序输出为：" << endl;
	for (unsigned int i = 0; i < copy_file.size(); i++)
		cout << copy_file[i] << endl;



}



void FileQuery::PrintSentencesFiltered(const string& str)
{
	cout << "包含" << str << "中单词的句子有：" << endl;
	unsigned int start_pos = str.find_first_not_of(",. ");
	vector<string> word;

	//提取str中的每个单词到word中
	while (start_pos != str.npos)
	{
		unsigned int end_pos = str.find_first_of(",. ", start_pos);
		word.push_back(str.substr(start_pos, end_pos - start_pos));
		start_pos = str.find_first_not_of(",. ", end_pos);
	}

	//提取sentences_的单词，同时与word中的每个单词进行比较，若有相同则输出该句子
	for (unsigned int i = 0; i < sentences_.size(); i++)
	{
		unsigned int start_pos = sentences_[i].find_first_not_of(" :：()（）-");
		while (start_pos != sentences_[i].npos)
		{
			unsigned int end_pos = sentences_[i].find_first_of(" :：()（）-", start_pos);
			for (unsigned int j = 0; j < word.size(); j++)
			{
				if (sentences_[i].substr(start_pos, end_pos - start_pos) == word[j])
				{
					cout << sentences_[i] << endl;
					end_pos = sentences_[i].npos;
					break;
				}
			}
			if (end_pos == sentences_[i].npos)
				break;
			else
				start_pos = sentences_[i].find_first_not_of(" :：()（）-", end_pos);
		}
	}

}




void FileQuery::PrintWordCount()
{
	cout << "文本中各单词的出现次数如下：" << endl;
	map<string, int> word;

	//用map记录单词出现次数
	for (unsigned int i = 0; i < sentences_.size(); i++)
	{
		unsigned int start_pos = sentences_[i].find_first_not_of(" :：()（）-");
		while (start_pos != sentences_[i].npos)
		{
			unsigned int end_pos = sentences_[i].find_first_of(" :：()（）-", start_pos);
			string temp_word = sentences_[i].substr(start_pos, end_pos - start_pos);
			for (unsigned int j = 0; j < temp_word.size(); j++)
				temp_word[j] = tolower(temp_word[j]);
			if (word[temp_word])
				word[temp_word] += 1;
			else
				word[temp_word] = 1;
			start_pos = sentences_[i].find_first_not_of(" :：()（）-", end_pos);
		}
	}

	//用迭代器遍历进行输出
	map<string, int>::iterator iter;
	for (iter = word.begin(); iter != word.end(); iter++)
		cout << iter->first << "：" << iter->second << endl;
}


void FileQuery::ReplaceWord(const string& old_word, const string& new_word)
{
	string text;
	ifstream f;
	vector<string> file_content;
	f.open(file_name);
	while (getline(f, text))
		file_content.push_back(text);
	f.close();

	//重新提取文件中的每行 到 file_content，对file_content的每一项进行替换单词
	unsigned int word_pos = 0;
	for (unsigned int i = 0; i < file_content.size(); i++)
	{
		word_pos = file_content[i].find(old_word, 1);
		while (word_pos != file_content[i].npos)
		{
			//检查找到的单词前后是否有空格，若有则说明这是单词内嵌，不能替换
			if (isalpha(file_content[i][word_pos - 1]) == 0 && isalpha(file_content[i][word_pos + old_word.length()]) == 0)
				file_content[i].replace(word_pos, old_word.length(), new_word);
			word_pos = file_content[i].find(old_word, word_pos + 1);
		}
	}
	//替换完file_content后，则将file_content内容写入文件，进行覆盖
	ofstream g;
	g.open(file_name, ios::trunc);
	for (unsigned int i = 0; i < file_content.size(); i++)
		g << file_content[i] << "\n";
	g.close();

	//替换单词后更新sentences_，先清空原有sentences_,之后与构造函数中大致相同
	vector<string>().swap(sentences_);
	vector<string>().swap(file_content);
	string  punctuation = "，。,.",content="";
	f.open(file_name);
	while (getline(f, text))
		file_content.push_back(text);
	for (unsigned int i = 0; i < file_content.size(); i++)
		content += file_content[i];
	unsigned int start_pos = content.find_first_not_of(punctuation);
	while (start_pos != content.npos)
	{
		unsigned int end_pos = content.find_first_of(punctuation, start_pos);
		string sentence = content.substr(start_pos, end_pos - start_pos);
		if (sentence[0] == ' ')
			sentence = sentence.erase(0, 1);
		sentences_.push_back(sentence);
		start_pos = content.find_first_not_of(punctuation, end_pos);
	}
	f.close();
}

