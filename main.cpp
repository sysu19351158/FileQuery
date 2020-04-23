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
	cout <<"替换'was'为'is'后";
	example.PrintSentencesOrdered();
	cout << endl;
}


void TestShape()
{
	Rectangle rect(4.0, 5.0);
	Circle cir(3.0);
	Square squ(5.0);

	cout << "矩形面积为：" << rect.GetArea() << endl;
	cout << "圆形面积为：" << cir.GetArea() << endl;
	cout << "正方形面积为：" << squ.GetArea() << endl;
}


int main()
{
	cout << "TestQuery函数结果：" << endl;
	cout << endl;
	TestQuery();
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	cout << "TestShape函数结果：" << endl;
	TestShape();
	return 0;

}