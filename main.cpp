#include <iostream>
#include <random>

using namespace std;
random_device rd;
mt19937 rng(rd());

//function to properly cout the return from knapsack
void prepareSubset(int arr[4][2], int best[4], int value, int weight) {
	int i = 0;

	cout << "Best subset:\n";
	while (best[i] < 5) {
		cout << "[" << arr[best[i]][0] << ", " << arr[best[i]][1] << "]" << endl;
		i++;
	}
	cout << "Best subset weight: " << weight << endl;
	cout << "Best subset value: " << value << endl;
}

int* knapsack(int arr[4][2], int cap) {
	int highestValue = 0;
	int highestWeight = 0;

	int totalValue = 0;
	int totalWeight = 0;

	//size will have a max of 4
	int size = 0;

	//array to store the best possible subset
	int best[4] = { 5,5,5,5 };

	for (int i = 0; i < 16; i++) {

		//array to store current subset being observed
		int temp[4] = { 0,0,0,0 };

		for (int j = 0; j < 4; j++) {

			if ((i & (1 << j)) != 0) {

				//check to see if adding subset value to array will put it over the capacity
				int test = totalWeight + arr[j][0];
				if (test > cap) {
					continue;
				}
				if (test <= cap) {
					totalWeight += arr[j][0];
					temp[size] = j;
					size++;
				}
			}
		}
		//summing value of current subset
		for (int i = 0; i < size; i++) {
			totalValue += arr[temp[i]][1];
		}
		//setting new best subset
		if (totalValue > highestValue) {
			for (int i = 0; i < size; i++) {
				best[i] = temp[i];
				highestValue = totalValue;
				highestWeight = totalWeight;
			}
		}
		//resetting values for next iteration
		size = 0;
		totalWeight = 0;
		totalValue = 0;
	}
	prepareSubset(arr, best, highestValue, highestWeight);
	return best;
}

int main() {

	srand(time(NULL));
	uniform_int_distribution<int> weight(1, 10);
	uniform_int_distribution<int> value(1, 5);
	uniform_int_distribution<int> capacity(8, 13);

	//randomly generating problem values
	int myArray[4][2] = {
		{weight(rng), value(rng)},
		{weight(rng), value(rng)},
		{weight(rng), value(rng)},
		{weight(rng), value(rng)}
	};
	int cap = capacity(rng);

	cout << "Knapack capacity is" << " " << cap << endl;
	cout << "Possible contents to put in knapsack:\n";
	cout << "WEIGHT/VALUE\n";
	cout << "[" << myArray[0][0] << ", " << myArray[0][1] << "]" << endl;
	cout << "[" << myArray[1][0] << ", " << myArray[1][1] << "]" << endl;
	cout << "[" << myArray[2][0] << ", " << myArray[2][1] << "]" << endl;
	cout << "[" << myArray[3][0] << ", " << myArray[3][1] << "]" << endl;
	cout << "\n\n";

	//set capacity to eight for best results, theoretically could be any number
	knapsack(myArray, cap);
}