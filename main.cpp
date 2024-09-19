#include <iostream>
#include <fstream>
#include <optional>
#include <string>
#include "interpreter.hpp"

optional<string> GetFileContents(string path){
	ifstream File(path);
	
	auto Reverse = [](string s) -> string {
		string fin = "";
		for (int i=s.length()-1;i>=0;i--)
			fin+=s[i];
		return fin;
	};
	
	if (!File.is_open()) {
		cout << "Could not locate file" << endl;
		return nullopt;
	}
	
	if (Reverse(path).find(Reverse(".bf"))!=0){
		cout <<  "Can only interprete files with .bf extension" << endl;
		return nullopt;
	}
	
	string line, contents;
	while (getline(File, line))
		contents+=line;
		
	File.close();
	return contents;
}

int main(){
	cout << "Brainfuck Interpreter\n(c) WAP Industries.\n";
	
	while (true){
		Interpreter.Init();
		
		string input;
		cout << "\n>> ";
		cin>>input;
		if (input=="quit") 
			break;
		
		optional<string> FileContents = GetFileContents(input);
		if (!FileContents.has_value()) 
			continue;
		
		Interpreter.CURRENT_CODE = FileContents.value();
		Interpreter.Interprete();
		
		cout << endl;
	}
	return 0;
}