#include <iostream>
#include <string>
#include "FileQuery.h"
#include "Shape.h"



void TestQuery()
{
	string filename = "TwoCities.txt";
	FileQuery example(filename);
	example.PrintSentencesOrdered();
	cout << endl;
	example.PrintSentencesFiltered("epoch,the");
	cout << endl;
	example.PrintWordCount();
	cout << endl;
	example.ReplaceWord("was", "is");
	cout <<"�滻'was'Ϊ'is'��";
	example.PrintSentencesOrdered();
	cout << endl;
}


void TestShape()
{
	Rectangle rect(4.0, 5.0);
	Circle cir(3.0);
	Square squ(5.0);

	cout << "�������Ϊ��" << rect.GetArea() << endl;
	cout << "Բ�����Ϊ��" << cir.GetArea() << endl;
	cout << "���������Ϊ��" << squ.GetArea() << endl;
}


int main()
{
	cout << "TestQuery���������" << endl;
	cout << endl;
	TestQuery();
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "TestShape���������" << endl;
	TestShape();
	return 0;

}