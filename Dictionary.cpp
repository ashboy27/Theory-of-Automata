#include"Dictionary.h"

using namespace std;


struct CustomLength {
	bool operator()(pair<int, string>& p1, pair<int, string>& p2) {
		bool status = p1.first == p2.first? p1.second>p2.second: p1.first>p2.first;	//compare based on the distance first and then lexographical order
		return status;
	}
};

int getLevenshteinDistance(string word1, string word2) {

	int length1 = word1.size();
	int length2 = word2.size();
	vector<vector<int>>dp(length1+1,vector<int>(length2+1)); 
	
	if (length1 == 0) {
		return length2;
	}
	if (length2 == 0) {
		return length1;
	}

	for (int i = 0; i <= length1; i++)
		dp[i][0] = i;
	for (int j = 0; j <= length2; j++)
		dp[0][j] = j;

	

	for (int i = 1; i <= length1; i++) {

		for (int j = 1; j <= length2; j++) {
			
			int additionalCost=0;		//cost of changing current character
			if (word2[j - 1] != word1[i - 1]) {
				additionalCost++;
			}
			int minAboveFront = min(dp[i - 1][j] + 1, dp[i][j - 1]+1);	//stores minimum of the cell at top and cell at right

			int newCost = dp[i - 1][j - 1] + additionalCost;			//the cost of changing all characters from start to current+cost of changing current character

			dp[i][j] = min(minAboveFront,newCost);
			
		}
	}

	return dp[length1][length2];	//the last index stores the total minimum cost to convert word 1 to word 2
}

Node::Node(char ch, Node* parent) : letter(ch), wordStatus(false),parent(parent) {}

Dictionary::Dictionary() {

	root = new Node('*',NULL);
	char start = 'a';

	for (int i = 0; i < 26; ++i) {

		root->children[start] = new Node(start,root);

	}
	root->children['a']->wordStatus = true;
	root->children['a']->actualWord = "a";


}


Node* Dictionary::getRoot() {
	return this->root;
}

void Dictionary::add(string word) {

	Node* temp = getRoot();
	Node* parent = temp->parent;
	for (char letter : word) {

		if (temp->children.find(letter) != temp->children.end()) {
			//take temp to this child
			parent = temp;
			temp = temp->children[letter];
		}
		else {
			//else add this letter as roots child
			temp->children[letter] = new Node(letter,temp);
			parent = temp;
			temp = temp->children[letter];
			
		}
	}
	temp->wordStatus = true;
	temp->actualWord = word;
	
	return;

}


bool Dictionary::spellCheck(string word) {

	Node* temp = getRoot();
	for (char letter : word) {
		if (temp->children.find(letter) == temp->children.end()) {
			return false;
		}
		temp = temp->children[letter];
	}
	return temp->wordStatus;

}


vector<string>Dictionary::getWordRecommendation(string word) {

	priority_queue<pair<int, string>, vector<pair<int, string>>, CustomLength>getMinDistanceWords;//priority assigned to words based on their Levenshtein distance


	Node* temp = getRoot();
	temp = temp->children[word[0]];
	getValidWords(word, temp, getMinDistanceWords);

	vector<string>returnWords;

	for (int i = 0; i < 3; ++i) {
		returnWords.push_back(getMinDistanceWords.top().second);
		getMinDistanceWords.pop();
	}

	return returnWords;
	

}





void Dictionary::getValidWords(string word,Node *start, priority_queue<pair<int, string>, vector<pair<int, string>>, CustomLength>&getMinDistanceWords) {

	
	Node* startNode = start;
	queue<Node*>traverseWords;
	traverseWords.push(startNode);
	while (traverseWords.empty() == false) {
		Node* temp = traverseWords.front();
		traverseWords.pop();
		if (temp->wordStatus == true) {
			int levenshteinDistance = getLevenshteinDistance(word, temp->actualWord);
			getMinDistanceWords.push({levenshteinDistance,temp->actualWord});
		}
		for (pair<int , Node* > childPair : temp->children) {
			traverseWords.push(childPair.second);
		}
	}

	return;
	
}

