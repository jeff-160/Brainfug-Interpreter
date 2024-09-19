#include <vector>
#define MEMORY_SIZE 30000
using namespace std;

struct BFInterpreter {
	unsigned char CELLS[MEMORY_SIZE];
	int IPOINTER = 0, MPOINTER = 0;
	
	bool ENDED = false;
	string CURRENT_CODE = "";
	vector<int> QUEUE;

	void Init(){
		fill(begin(this->CELLS), end(this->CELLS), 0);
		this->IPOINTER = this->MPOINTER = 0;
		this->QUEUE.clear();
		this->CURRENT_CODE = "";
		this->ENDED = false;
	}

	bool CheckIndex(){
		return (
			this->IPOINTER>=0 &&
			this->IPOINTER<this->CURRENT_CODE.length()
		);
	}

	void Error(string s){
		cout<< s;
		this->ENDED = true;
	}
	
	void Interprete() {
		while (!this->ENDED){
			switch (this->CURRENT_CODE[this->IPOINTER]){
				case '>':
					this->MPOINTER++;
					if (this->MPOINTER>=MEMORY_SIZE)
						this->Error("Out of bounds memory access with index " + to_string(this->MPOINTER));
					break;
				case '<':
					this->MPOINTER--;
					if (this->MPOINTER<0)
						this->Error("Out of bounds memory access with index " + to_string(this->MPOINTER));
					break;
					
				case '+':
					this->CELLS[this->MPOINTER]++;
					break;
				case '-':
					this->CELLS[this->MPOINTER]--;
					break;
				
				case '[':
					if ((bool)this->CELLS[this->MPOINTER])
						this->QUEUE.push_back(this->IPOINTER);
					else{
						int count = 0;
						while (true) {
							this->IPOINTER++;
							if (!this->CheckIndex()) 
								break;
							if (this->CURRENT_CODE[this->IPOINTER] == '[') 
								count++;
							else if (this->CURRENT_CODE[this->IPOINTER] == ']') {
								if (count) 
									count--;
								else 
									break;
							}
						}
					}
					break;
				case ']':
					if (this->QUEUE.size()==0)
						this->Error("'[' expected");
					else
						this->IPOINTER = this->QUEUE.back()-1;
					break;
					
				case ',':
					char input;
					cin >> input;
					this->CELLS[this->MPOINTER] = (int)input;
					break;

				case '.':
					char c = this->CELLS[this->MPOINTER];
					cout<< (((int)c)<20 ? '?' : c);
					break;
			}
			this->IPOINTER++;

			if (!this->CheckIndex()) break;
		}
	}
};

BFInterpreter Interpreter;