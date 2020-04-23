#include <iostream>
#include <vector>
#include "FileQuery.h"
#include <fstream>
#include <map>
#include <string>
using namespace std;

FileQuery::FileQuery(const string& filename) :file_name{ filename }
{
	
	string text, content = "", punctuation = "����,.";
	vector<string> file_content;
	ifstream f;
	f.open(filename);

	//���ļ��еľ��ӷŽ�content�ַ�����
	while (getline(f, text))
		file_content.push_back(text);
	for (unsigned int i = 0; i < file_content.size(); i++)
		content += file_content[i];

	//��content����ȡ������
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

	//��sentences_�ĸ���copy_file���ֵ�˳����������
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
	cout << "�ı����ֵ�˳�����Ϊ��" << endl;
	for (unsigned int i = 0; i < copy_file.size(); i++)
		cout << copy_file[i] << endl;



}



void FileQuery::PrintSentencesFiltered(const string& str)
{
	cout << "����" << str << "�е��ʵľ����У�" << endl;
	unsigned int start_pos = str.find_first_not_of(",. ");
	vector<string> word;

	//��ȡstr�е�ÿ�����ʵ�word��
	while (start_pos != str.npos)
	{
		unsigned int end_pos = str.find_first_of(",. ", start_pos);
		word.push_back(str.substr(start_pos, end_pos - start_pos));
		start_pos = str.find_first_not_of(",. ", end_pos);
	}

	//��ȡsentences_�ĵ��ʣ�ͬʱ��word�е�ÿ�����ʽ��бȽϣ�������ͬ������þ���
	for (unsigned int i = 0; i < sentences_.size(); i++)
	{
		unsigned int start_pos = sentences_[i].find_first_not_of(" :��()����-");
		while (start_pos != sentences_[i].npos)
		{
			unsigned int end_pos = sentences_[i].find_first_of(" :��()����-", start_pos);
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
				start_pos = sentences_[i].find_first_not_of(" :��()����-", end_pos);
		}
	}

}




void FileQuery::PrintWordCount()
{
	cout << "�ı��и����ʵĳ��ִ������£�" << endl;
	map<string, int> word;

	//��map��¼���ʳ��ִ���
	for (unsigned int i = 0; i < sentences_.size(); i++)
	{
		unsigned int start_pos = sentences_[i].find_first_not_of(" :��()����-");
		while (start_pos != sentences_[i].npos)
		{
			unsigned int end_pos = sentences_[i].find_first_of(" :��()����-", start_pos);
			string temp_word = sentences_[i].substr(start_pos, end_pos - start_pos);
			for (unsigned int j = 0; j < temp_word.size(); j++)
				temp_word[j] = tolower(temp_word[j]);
			if (word[temp_word])
				word[temp_word] += 1;
			else
				word[temp_word] = 1;
			start_pos = sentences_[i].find_first_not_of(" :��()����-", end_pos);
		}
	}

	//�õ����������������
	map<string, int>::iterator iter;
	for (iter = word.begin(); iter != word.end(); iter++)
		cout << iter->first << "��" << iter->second << endl;
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

	//������ȡ�ļ��е�ÿ�� �� file_content����file_content��ÿһ������滻����
	unsigned int word_pos = 0;
	for (unsigned int i = 0; i < file_content.size(); i++)
	{
		word_pos = file_content[i].find(old_word, 1);
		while (word_pos != file_content[i].npos)
		{
			//����ҵ��ĵ���ǰ���Ƿ��пո�������˵�����ǵ�����Ƕ�������滻
			if (isalpha(file_content[i][word_pos - 1]) == 0 && isalpha(file_content[i][word_pos + old_word.length()]) == 0)
				file_content[i].replace(word_pos, old_word.length(), new_word);
			word_pos = file_content[i].find(old_word, word_pos + 1);
		}
	}
	//�滻��file_content����file_content����д���ļ������и���
	ofstream g;
	g.open(file_name, ios::trunc);
	for (unsigned int i = 0; i < file_content.size(); i++)
		g << file_content[i] << "\n";
	g.close();

	//�滻���ʺ����sentences_�������ԭ��sentences_,֮���빹�캯���д�����ͬ
	vector<string>().swap(sentences_);
	vector<string>().swap(file_content);
	string  punctuation = "����,.",content="";
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

