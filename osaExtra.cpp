#include <iostream>
#include <fstream>
#include <vector>

using namespace std;


class Stack {
private:
	int* myStack;
	int head = 0, inOps = 0, outOps = 0, size;
	enum states { empty, full, ok };
	states checkResult;
	int toReturn;

	states fullOrEmpty() {
		if (inOps == outOps) {
			return states::empty;
		}
		else if (inOps - outOps == size) {
			return states::full;
		}
		else
			return states::ok;
	}

	void translateHead() {
		if (head > size)
			head = 0;
	}

public:
	Stack(int arraySize) {
		size = arraySize;
		myStack = new int[size];
	}

	~Stack() {
		delete[] myStack;
	}

	bool is_empty() {
		if (inOps == outOps) {
			return true;
		}
		else
			return false;
	}

	void add(int arg) {
		translateHead();
		checkResult = fullOrEmpty();
		if (checkResult != states::full) {
			inOps++;
			myStack[head] = arg;
			head++;
		}
	}

	int out() {
		checkResult = fullOrEmpty();
		if (checkResult != states::empty) {
			outOps++;
			toReturn = myStack[head - 1];
			myStack[head - 1] = 0;
			head--;
			return toReturn;
		}
		return -1;
	}

};

class Graph {
	int** matrix;
	bool* visited;
	int* ways;
	int start;
	int size;

public:

	Graph(int N, int start, int** myMatrix) {
		matrix = new int* [N];
		for (int j = 0; j < N; j++) {
			int* temp = new int[N];
			for (int i = 0; i < N; i++) {
				temp[i] = 0;
			}
			matrix[j] = temp;
		}
		size = N;

		visited = new bool[N];
		for (int o = 0; o < N; o++) {
			visited[o] = 0;
		}
		ways = new int[N];
		for (int u = 0; u < N; u++) {
			ways[u] = 0;
		}
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				matrix[i][j] = myMatrix[i][j];
			}
		}
	}

	void add_edge(int from, int to) {
		matrix[from][to] = 1;
	}

	vector<int> find_ways() {
		vector<int> toReturn;
		Stack stack(size);
		stack.add(start);
		visited[start] = 1;
		ways[start] = -1;
		while (!stack.is_empty())
		{
			int unit = stack.out();
			toReturn.push_back(unit);	
			for (int i = 0; i < size; i++)
			{
				if ((visited[i] == 0) && (matrix[unit][i] == 1))
				{
					stack.add(i);

					visited[i] = 1;
				}
			}
		}
		return toReturn;
	}
};

void print(vector<int> arr, int size) {
	for (int i = 0; i < size; i++) {
		cout << arr[i] << " ";
	}
	cout << endl << endl;
}

int** random_matrix_builder(int size, bool need_to_print) {
	int** matrix = new int* [size];
	for (int j = 0; j < size; j++) {
		int* temp = new int[size];
		for (int i = 0; i < size; i++) {
			temp[i] = 0;
		}
		matrix[j] = temp;
	}
	int num;
	srand(time(NULL));
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			num = rand();
			if (i == j) {
				matrix[i][j] = 0;
			}
			if (num % 2 == 0) {
				matrix[i][j] = 0;
			}
			else {
				matrix[i][j] = 1;
			}
		}
	}
	if (need_to_print) {
		for (int i = 0; i < 30; i++) {
			for (int j = 0; j < 30; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	return matrix;
}

int main(int count, char** params)
{
	setlocale(LC_ALL, "");
	bool need_to_print;
	if (string(params[3]) == "print") {
		need_to_print = 1;
	}
	else  {
		need_to_print = 0;
	}
	Graph g(atoi(params[1]), atoi(params[2]), random_matrix_builder(atoi(params[1]), need_to_print));
	cout << endl << endl;
	print(g.find_ways(), atoi(params[1]));
	system("pause");
	return 0;
}