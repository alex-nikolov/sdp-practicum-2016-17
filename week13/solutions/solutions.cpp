#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>

using namespace std;

// Задача 1, за другия вариант е аналогично.
struct Node {
	int data;
	Node* left;
	Node* right;
	
	Node(int _data) {
		data = _data;
		left = right = NULL;
	}
};

int height(Node* root) {
	if (!root || (!root->left && !root->right))
		return 0;
		
	return 1 + max(height(root->left), height(root->right));
}

int heavierLefties(Node* root) {
	// Ако няма възел или няма деца, няма как лявото му поддърво да е по-високо от дясното
	if (!root || (!root->left && !root->right))
		return 0;
		
	// Вече сме в случая да има поне 1 дете. Ако той няма ляво дете, то няма как условието да е
	// изпълнено за текущия възел и продължаваме рекурсивно надолу.
	if (!root->left)
		return heavierLefties(root->right);
	
	// Стигнали сме дотук, т.е. има ляво дете. Ако няма дясно поддърво, то условието е изпълнено за
	// текущия връх и връща 1 + резултата от рекурсивното извикване.
	if (!root->right)
		return 1 + heavierLefties(root->left);
	
	// В момента сме в случая, в който възелът има две деца. Пускаме функцията height за лявото
	// и дясното поддърво и ако условието е изпълнено, връщаме 1 + резултата от рекурсивните
	// извиквания за двете поддървета.
	if (height(root->left) > height(root->right))
		return 1 + heavierLefties(root->left) + heavierLefties(root->right);
	
	// Ако има 2 деца и лявото поддърво не е по-високо от дясното, връщаме само резултата от
	// рекурсивните извиквания върху двете поддървета.
	return heavierLefties(root->left) + heavierLefties(root->right);
}



// Задача 2
struct Player {
	string name;
	string position;
	string nationality;
	string team;
	string league;
	
	Player(string _name, string _pos, string _nat, string _team, string _league) {
		name = _name;
		position = _pos;
		nationality = _nat;
		team = _team;
		league = _league;
	}

	// Без това дава грешка
	Player() {
	}
};

// Указателите по-долу са за да не правим излишни копирания или за да не извършваме излишни търсения.
class Formation {
	map<string, Player> playerPositions;
	map<string, vector<string> > graph;
	
	int rightPositionChem(string const& position, Player* player) {
		// Сравняваме само с първите две букви от позицията.
		return (player->position == position.substr(0, 2)) ? 4 : 0;
	}
	
	int linksChem(vector<string>* neighbours, Player* player, string const& position) {
		double totalLinks = 0;

		for (int i = 0; i < neighbours->size(); i++) {
			Player* neighbour = &(playerPositions[neighbours->operator[](i)]);

			int edgeChem = 0;
			
			if (player->nationality == neighbour->nationality)
				edgeChem++;
			if (player->team == neighbour->team)
				edgeChem++;
			if (player->league == neighbour->league)
				edgeChem++;
			
			if (edgeChem > 2)
				edgeChem--;
			
			totalLinks += edgeChem;
		}
		
		int linksChem = (totalLinks / (neighbours->size() * 2)) * 12;
		return (linksChem > 6) ? 6 : linksChem;
	}

public:
	void addVertex(string const& position) {
		graph[position] = vector<string>();
	}

	void addEdge(string const& from, string const& to) {
		vector<string>* fromVector = &graph[from];

		if (find(fromVector->begin(), fromVector->end(), to) == fromVector->end()) {
			fromVector->push_back(to);
			graph[to].push_back(from);
		}
	}

	void addPlayer(string const& position, Player const& player) {
		playerPositions[position] = player;
	}

	int playerChemistry(string const& position) {
		Player* player = &playerPositions[position];
		vector<string>* neighbours = &graph[position];
		
		return rightPositionChem(position, player) + linksChem(neighbours, player, position);
	}
	
	int teamChemistry() {
		int totalChem = 0;

		for (map<string, Player>::iterator it = playerPositions.begin(); it != playerPositions.end(); it++)
			totalChem += playerChemistry(it->first);
		
		return (totalChem > 100) ? 100 : totalChem;
	}
};


int main() {
	Node* root = new Node(1);
	root->left = new Node(5);
	root->right = new Node(8);
	root->left->left = new Node(2);
	root->left->left->right = new Node(5);
	root->left->left->right->left = new Node(7);
	root->right->left = new Node(6);
	root->right->right = new Node(7);
	root->right->left->right = new Node(8);
	root->right->right->left = new Node(9);
	
	cout << heavierLefties(root) << endl << endl;


	Formation _4_4_2;

	_4_4_2.addVertex("GK");
	_4_4_2.addVertex("CB1");
	_4_4_2.addVertex("CB2");
	_4_4_2.addVertex("LB");
	_4_4_2.addVertex("RB");
	_4_4_2.addVertex("CM1");
	_4_4_2.addVertex("CM2");
	_4_4_2.addVertex("LM");
	_4_4_2.addVertex("RM");
	_4_4_2.addVertex("ST1");
	_4_4_2.addVertex("ST2");
	
	_4_4_2.addEdge("GK", "CB1");
	_4_4_2.addEdge("GK", "CB2");
	_4_4_2.addEdge("CB1", "CB2");
	_4_4_2.addEdge("CB1", "LB");
	_4_4_2.addEdge("CB1", "CM1");
	_4_4_2.addEdge("CB2", "RB");
	_4_4_2.addEdge("CB2", "CM2");
	_4_4_2.addEdge("LB", "LM");
	_4_4_2.addEdge("RB", "RM");
	_4_4_2.addEdge("LM", "CM1");
	_4_4_2.addEdge("LM", "ST1");
	_4_4_2.addEdge("RM", "CM2");
	_4_4_2.addEdge("RM", "ST2");
	_4_4_2.addEdge("CM1", "CM2");
	_4_4_2.addEdge("CM1", "ST1");
	_4_4_2.addEdge("CM2", "ST2");
	_4_4_2.addEdge("ST1", "ST2");


	Player neuer("NEUEEEER", "GK", "German", "Bayern", "Bundesliga");

	Player boateng("Boateng", "CB", "German", "Bayern", "Bundesliga");
	Player alaba("Alaba", "LB", "Spanish", "Real Madrid", "La Liga");
	Player smalling("Smalling", "CB", "English", "Man United", "Premier League");
	Player walker("Walker", "RB", "English", "Tottenham", "Premier League");
	
	Player ronaldo("Ronaldo", "LM", "Protuguese", "Real Madrid", "La Liga");
	Player iniesta("Iniesta", "CM", "Spanish", "Barcelona", "La liga");
	Player pogba("Pogba", "CM", "French", "Man United", "Premier League");
	Player messi("Messi", "RM", "Argentinian", "Barcelona", "La Liga");
	
	Player griezmann("Griezmann", "ST", "French", "Atletico Madrid", "La Liga");
	Player lewandowski("Lewandowski", "ST", "Polish", "Bayern", "Bundesliga");


	_4_4_2.addPlayer("GK", neuer);

	_4_4_2.addPlayer("CB1", boateng);
	_4_4_2.addPlayer("CB2", smalling);
	_4_4_2.addPlayer("LB", alaba);
	_4_4_2.addPlayer("RB", walker);

	_4_4_2.addPlayer("LM", ronaldo);
	_4_4_2.addPlayer("CM1", iniesta);
	_4_4_2.addPlayer("CM2", pogba);
	_4_4_2.addPlayer("RM", messi);

	_4_4_2.addPlayer("ST1", lewandowski);
	_4_4_2.addPlayer("ST2", griezmann);

	cout << "Neuer: " << _4_4_2.playerChemistry("GK") << endl << endl;

	cout << "Alaba: " << _4_4_2.playerChemistry("LB") << endl;
	cout << "Boateng: " << _4_4_2.playerChemistry("CB1") << endl;
	cout << "Smalling: " << _4_4_2.playerChemistry("CB2") << endl;
	cout << "Walker: " << _4_4_2.playerChemistry("RB") << endl << endl;

	cout << "Ronaldo: " << _4_4_2.playerChemistry("LM") << endl;
	cout << "Iniesta: " << _4_4_2.playerChemistry("CM1") << endl;
	cout << "Pogba: " << _4_4_2.playerChemistry("CM2") << endl;
	cout << "Messi: " << _4_4_2.playerChemistry("RM") << endl << endl;

	cout << "Lewandowski: " << _4_4_2.playerChemistry("ST1") << endl;
	cout << "Griezmann: " << _4_4_2.playerChemistry("ST2") << endl << endl;
	
	cout << "Total chem: " << _4_4_2.teamChemistry();
}
