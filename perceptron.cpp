#include <vector>

struct Input {
	bool value;
	double weight;
};

struct Perceptron {
	double threshold;

	bool input(std::vector<Input> inputs) {
		double total{0}, totalWeight{0};
		for (const auto &input : inputs) {
			total += input.value * input.weight;
			totalWeight += input.weight;
		}
		return (total / totalWeight) > threshold;
	}
};

int main(){
	Perceptron p{0.5};

	printf("%s\n", p.input({
		{true, 1},
		{false, 1}
	}) ? "yes" : "no");

}
