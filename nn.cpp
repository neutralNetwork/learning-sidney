#include <vector>
#include <iostream>

struct Node {

	struct Connection {
		Node &to;
		double weight;

		void send(double value) {
			to.inputsFired++;
			to.value += value * weight;
			if (to.inputsFired == to.inputs) {
				to.fire(to.fired() ? 1 : 0);
			}
		}
	};

	unsigned int inputs = 0;
	unsigned int inputsFired = 0;
	double value = 0;
	double bias;
	std::vector<Connection> outputs;

	Node(double _bias) :
		bias(_bias)
	{}
	void connect(Node &to, double weight) {
		outputs.push_back(Connection{to, weight});
		to.inputs++;
	}
	void fire(double value) {
		for (auto &output : outputs) {
			output.send(value);
		}
	}
	bool fired() {
		return value + bias > 0;
	}
};

int main() {
	Node in1{0};
	Node in2{0};
	Node out{3};
	Node carry{3};

	Node m1{3};
	Node m2{3};
	Node m3{3};

	in1.connect(m1, -2);
	in2.connect(m1, -2);
	in1.connect(m2, -2);
	in2.connect(m3, -2);
	m1.connect(m2, -2);
	m1.connect(m3, -2);
	m2.connect(out, -2);
	m3.connect(out, -2);
	m1.connect(carry, -4);

	in1.fire(1);
	in2.fire(1);

	std::cout << carry.fired() << out.fired() << std::endl;
}
