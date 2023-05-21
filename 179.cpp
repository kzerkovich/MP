#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

enum Cell {
	Floor,
	Wall
};

typedef pair<int, int> Coord;

pair<Coord, Coord> min_box(Coord a, Coord b) {
	if (a < b)
		return make_pair(a, b);
	else
		return make_pair(b, a);
}

string read_line() {
	string tmp;
	cin >> tmp;
	return tmp;
}

pair<int, int> read_pair() {
	int a, b;
	cin >> a >> b;
	return make_pair(a, b);
}

class Sokoban {
private:
	int n, m, nm, init_state, win_state;
	unsigned int box_count;
	vector<vector<Cell>> walls;
	vector<int> states;

public:
	int coord_enc(Coord a) {
		return a.second * this->m + a.first;
	}

	Coord coord_dec(int state) {
		return make_pair(state % this->m, state / this->m);
	}

	int box_state_enc(vector<Coord>& boxes) {
		switch (this->box_count) {
		case 1:
			 return this->coord_enc(boxes[0]);
			break;
		case 2:
			pair<Coord, Coord> tmp = min_box(boxes[0], boxes[1]);
			int box0 = this->coord_enc(tmp.second);
			int box1 = this->coord_enc(tmp.first);
			return box1 * this->nm + box0;
			break;
		}
	}

	vector<Coord> box_state_dec(int state) {
		vector<Coord> tmp(2);
		switch (this->box_count) {
		case 1:
			tmp[0] = this->coord_dec(state);
			tmp[1] = make_pair(-2, -2);
			break;
		case 2:
			tmp[0] = this->coord_dec(state % this->nm);
			tmp[1] = this->coord_dec(state / this->nm);
			break;
		}
		
		return tmp;
	}

	int state_enc(Coord player, vector<Coord>& boxes) {
		return this->box_state_enc(boxes) * this->nm + this->coord_enc(player);
	}

	pair<Coord, vector<Coord>> state_dec(int state) {
		return make_pair(this->coord_dec(state % this->nm), this->box_state_dec(state / this->nm));
	}

	Sokoban() {
		pair<int, int> field = read_pair();
		n = field.first;
		m = field.second;
		nm = n * m;

		Coord player = make_pair(-1, -1);
		vector<Coord> boxes, goals;

		for (int i = 0; i < n; i++) {
			vector<Cell> row;
			string line = read_line();
			for (int j = 0; j < line.size(); j++) {
				switch (line[j])
				{
				case '.':
					row.push_back(Floor);
					break;
				case '#':
					row.push_back(Wall);
					break;
				case 'M':
					player = make_pair(j, i);
					row.push_back(Floor);
					break;
				case 'B':
					boxes.push_back(make_pair(j, i));
					row.push_back(Floor);
					break;
				case 'X':
					goals.push_back(make_pair(j, i));
					row.push_back(Floor);
					break;
				}
			}
			walls.push_back(row);
		}

		if (player == make_pair(-1, -1)) {
			cout << "MISSION IMPOSSIBLE";
			exit;
		}
		this->n = n;
		this->m = m;
		this->nm = nm;
		this->walls = walls;
		this->box_count = boxes.size();
		this->init_state = this->state_enc(player, boxes);
		this->win_state = this->box_state_enc(goals);
		this->states = vector<int>(n * n * n * m * m * m, -1);
	}

	bool check_free_cell(Coord a) {
		int x = a.first;
		int y = a.second;

		return x >= 0 && y >= 0 && x < this->m && y < this->n && this->walls[y][x] == Floor;
	}


	vector<int> neighbors(int state) {
		vector<int> result(4);
		pair<Coord, vector<Coord>> tmp = this->state_dec(state);
		vector<pair<int, int>> moves = { make_pair(-1, 0), make_pair(1, 0), make_pair(0, -1), make_pair(0, 1) };

		for (int i = 0; i < 4; i++) {
			auto player = make_pair((tmp.first.first + moves[i].first), (tmp.first.second + moves[i].second));
			if (this->check_free_cell(player)) {
				auto boxes = tmp.second;
				int box_id = -1;
				for (int j = 0; j < boxes.size(); j++) {
					if (player == boxes[j]) {
						box_id = j;
						break;
					}
				}

				if (-1 != box_id) {
					boxes[box_id].first += moves[i].first;
					boxes[box_id].second += moves[i].second;

					if (!this->check_free_cell(boxes[box_id]) || boxes[box_id] == boxes[1 - box_id]) continue;
				}
				result.push_back(this->state_enc(player, boxes));
			}
		}
		return result;
	}

	bool is_winning_state(int current) {
		return ((current / this->nm) == this->win_state);
	}

	void diff(string& prefix, Coord from, Coord to) {
		Coord diff = make_pair(to.first - from.first, to.second - from.second);
		int x = diff.first;
		int y = diff.second;
		string tmp;
		if (x == -1 && y == 0) tmp = "RIGHT";
		if (x == 1 && y == 0) tmp = "LEFT";
		if (x == 0 && y == -1) tmp = "DOWN";
		if (x == 0 && y == 1) tmp = "UP";
		cout << "\n" + prefix + " " + tmp;
	}

	void print_path(int current) {
		vector<pair<Coord, vector<Coord>>> states;
		states.push_back(this->state_dec(current));

		while (current != this->init_state) {
			current = this->states[current];
			states.push_back(this->state_dec(current));
		}

		cout << states.size() - 1;
		reverse(states.begin(), states.end());

		for (int i = 1; i < states.size(); i++) {
			Coord player_to = states[i - 1].first;
			vector<Coord> boxes_to = states[i - 1].second;
			string prefix;
			if (states[i].second == boxes_to) {
				prefix = "MOVE";
			}
			else prefix = "PUSH";
			diff(prefix, states[i].first, player_to);
		}
	}

	void find() {
		queue<int> queue;
		queue.push(this->init_state);

		while (!queue.empty()) {
			auto current = queue.front();
			queue.pop();
			if (this->is_winning_state(current)) {
				this->print_path(current);
				return;
			}
			for (auto const& e : this->neighbors(current)) {
				if (this->states[e] == -1) {
					queue.push(e);
					this->states[e] = current;
				}
			}
		}
		cout << "MISSION IMPOSSIBLE";
	}

};

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	Sokoban game;
	game.find();

	return 0;
}