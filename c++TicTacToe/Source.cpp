#include <iostream>
#include <string>
#include <iomanip>
#include<random>
#include<vector>
#include <time.h> 
using namespace std;

struct TreeNode
{
	char board[9];
	vector<TreeNode*> children;
	int pos;
	

	TreeNode(char board[9], int lastPos)
	{
		for (int i = 0; i < 9; i++)
		{
			this->board[i] = board[i];
		}
	}
};

//Finished
void printboard(char board[]){
	for (int x = 0; x < 9; x++){
		cout << board[x];
		cout << "|";
		if (x == 2 || x == 5){
			cout<<endl;
			for (int y = 0; y < 6; y++){
				cout << "-";
			}
			cout<<endl;
		}
	}
	cout << endl;
}

//Finshed
bool isSpotEmpty(int spot, char board[]){
	if (spot < 0 || spot > 8) return false;
	if (board[spot] == ' '){
		return true;
	}
	return false;
}

//Finished but game ties are buggy
string checkGameState(char board[]){
	string win="Win";
	string loose="Loose";
	string tie="Tie";
	string playing = "Playing";
	//check for win
	if (board[0] == board[1] && board[2] == board[0]){
		if (board[0] == ' '){

		}
		else if (board[0] == 'X'){
			return win;
		}
		else{
			return loose;
		}
	}
	else if (board[3] == board[4] && board[3] == board[5]) {
		if (board[3] == ' '){

		}
		else if (board[3] == 'X'){
			return win;
		}
		else{
			return loose;
		}
	}
	else if (board[6] == board[7] && board[6] == board[8]) {
		if (board[6] == ' '){

		}
		else if (board[6] == 'X'){
			return win;
		}
		else{
			return loose;
		}
	}
	else if (board[0] == board[3] && board[0] == board[6]){
		if (board[0] == ' '){

		}
		else if (board[0] == 'X'){
			return win;
		}
		else{
			return loose;
		}
	}
	else if (board[1] == board[4] && board[1] == board[7]) {
		if (board[1] == ' '){

		}
		else if (board[1] == 'X'){
			return win;
		}
		else{
			return loose;
		}
	}
	else if (board[2] == board[5] && board[2] == board[8]) {
		if (board[2] == ' '){

		}
		else if (board[2] == 'X'){
			return win;
		}
		else{
			return loose;
		}
	}
	else if (board[0] == board[4] && board[0] == board[8]) {
		if (board[0] == ' '){

		}
		else if (board[0] == 'X'){
			return win;
		}
		else{
			return loose;
		}
	}
	else if (board[2] == board[4] && board[2] == board[6]) {
		if (board[2] == ' '){

		}
		else if (board[2] == 'X'){
			return win;
		}
		else{
			return loose;
		}
	}

	//check for empty spots left
	for (int x = 0; x < 9; x++){
		if (isSpotEmpty(x, board)){
			return playing;
		}
	}

	//else we have a tie
	return tie;
}

void populateTree(TreeNode &node,char turn){

	for (int x = 0; x < 9; x++){
		TreeNode * child = new TreeNode(node.board, x);
		if (isSpotEmpty(x, child->board)){
			child->board[x] = turn;
			node.children.push_back(child);
		}
	}
	for (int z = 0; z < node.children.size(); z++){
		if (turn == 'X'){
			if (checkGameState(node.children[z]->board) == "Playing")
				populateTree(*node.children[z], 'O');
		}
		else{
			if (checkGameState(node.children[z]->board) == "Playing")
				populateTree(*node.children[z], 'X');
		}
	}
}

int getMoveScore(TreeNode node, char turn = 'X'){
	int score = -2;
	if (node.children.empty()){
		//loss for ai
		if (checkGameState(node.board) == "Win"){
			return -1;
		}
		//win for ai
		else if (checkGameState(node.board) == "Loose"){
			return 1;
		}
		//tie for ai
		else if (checkGameState(node.board)=="Tie") {
			return 0;
		}
	}
	//node has potential plays left
	if (turn == 'X'){
		score = 999;
		for (int x = 0; x < node.children.size(); x++){
			if (getMoveScore(*node.children[x], 'O') < score){
				score = getMoveScore(*node.children[x], 'O');
			}
		}
	}
	else{
		score = -999;
		for (int x = 0; x < node.children.size(); x++){
			if (getMoveScore(*node.children[x], 'X') > score){
				score = getMoveScore(*node.children[x], 'X');
			}
		}
	}
	return score;
}

//Finished
int main(){
	srand(time(NULL));
	char x = 'X';
	char o = 'O';
	char empty = ' ';
	bool gameover = false;
	char board[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8' };
	string gameResult = "Playing";
	int LastMove = -1;

	//start the game
	cout << "Welcome to Tic Tac Toe" << endl;
	cout << endl;

	//show the board states
	cout << "The board values are as follows:" << endl;
	printboard(board);
	//reset board states
	for (int i = 0; i < 9; i++){
		board[i] = empty;
	}
	cout << endl;

	TreeNode node(board, 0);
	populateTree(node,'X');

	////////////////////////////////////////////////////////////
	//run the turn cycles
	////////////////////////////////////////////////////////////

	while (!gameover){
		//chose your move
		cout << "choose your move(0-8)" << endl;
		int move = -1;
		while (move < 0 || move > 8){
			cin >> move;
			if (!isSpotEmpty(move, board)){
				move = -1;
			}
		}
		board[move] = x;
		LastMove = move;
		printboard(board);

		//check for gamestate change
		gameResult = checkGameState(board);
		if (gameResult != "Playing"){
			gameover = true;
		}

		//computer move
		//populateTree(node, LastMove);
		cout << "Computer Move" << endl;
		move = -1;
		//while (!isSpotEmpty(move, board)){
		//	move = static_cast<int>((rand() % 9));
		//}
		int score = -999;
		for (int x = 0; x < node.children.size(); x++){
			if (getMoveScore(*node.children[x], 'X') < score){
				score = getMoveScore(*node.children[x], 'X');
				move = x;
			}
		}
		board[move] = o;
		LastMove = move;
		printboard(board);

		//check for gamestate change
		gameResult = checkGameState(board);
		if (gameResult != "Playing"){
			gameover = true;
		}
	}

	//display the result of the game
	cout << endl;
	cout << "Game Over! You " << gameResult << "!" << endl;
	cout << endl;

	system("pause");
	return 0;
}