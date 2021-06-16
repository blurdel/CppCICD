#include <iostream>
#include <thread>
#include <future>
using namespace std;


struct ARGS {
	string name;
	int num;
};

void worker1(string name, int num)
{
	for (int i = 0; i < num; ++i) {
		this_thread::sleep_for(chrono::milliseconds(100));
		cout << name << " count: " << i << endl;
	}
}

int worker2(void* pArgs)
{
	if (pArgs == nullptr) {
		return 0;
	}

	ARGS *args = (ARGS*) pArgs;
	int count = args->num;

	try {

		for (int i = 0; i < count; ++i) {
			this_thread::sleep_for(chrono::milliseconds(500));
			cout /* << this_thread::get_id() << " "*/ << args->name << " count: " << i << endl;
		}

	}
	catch (std::exception& e) {
		cout << "Caught exception: " << e.what() << endl;
	}
	return count;
}


int main()
{
	cout << "Running ..." << endl;

	ARGS args {"worker1", 10};

	auto fut1 = std::async(worker2, &args);
	cout << fut1.get() << endl;
}
