#pragma once
#include<iostream>
#include<map>
#include<queue>
using namespace std;


int getLevenshteinDistance(string, string);

class Node {

public:
	char letter;
	bool wordStatus;
	map<char, Node*>children;
	Node(char ,Node*);
	string actualWord;
	Node* parent;

};

class Dictionary {
	Node* root;
public:

	Dictionary();

	Node* getRoot();

	void add(string);

	bool spellCheck(string);

	vector<string> getWordRecommendation(string);

private:
	void getValidWords(string,Node*, priority_queue<pair<int, string>, vector<pair<int, string>>, struct CustomLength>&);



};
