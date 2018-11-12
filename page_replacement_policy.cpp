#include <iostream>
#include <random>
#include <fstream>
#include <iterator>
#include <unordered_map>
#include <map>
#include <list>

using namespace std;

const int buffer_size = (int)5;
const int page_id_size = (int)1e3;


static int page_fault;
static int page_hit;

list<string> page_buffer;
unordered_map <string, list<string>::iterator > page_table;
unordered_map <int, bool> address_map;
unordered_map <string, int> page_address;

list<string> buffer(buffer_size);


random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(1,page_id_size);

int get_address(void);
void LRU_schedule(string pid);
void MRU_schedule(string pid);
void show_list();



int main(){
	string file = "E_D";
	string pid;
	ifstream infile;
	int type;
	do {
	cout << "Enter file: ";
	cin >> file; 
	cout << "\nReplacement policy: \n 1. LRU \n 2. MRU\n";
	cin >> type;

	if(!(type ==1 || type == 2))
		break;

	switch(type){
		case 1:
			infile.open(file);

			if(!infile.is_open()){
				cout << "Error in open file: " << file << '\n';
				_Exit(1);
			}
			
			while(infile.good()){
				getline(infile, pid, '\n');

				LRU_schedule(pid);
			}
			
			break;

		case 2:
			infile.open(file);

			if(!infile.is_open()){
				cout << "Error in open file: " << file << '\n';
				_Exit(1);
			}

			while(infile.good()){
				getline(infile, pid, '\n');

				MRU_schedule(pid);
			}

			break;	
	}
	cout << "\n*********************************************\n\n";
	cout << '\t' << "# Page Hit:    " << page_hit << '\n';
	cout << '\t' << "# Page Fault:  " << page_fault << '\n';
	cout << "\n*********************************************\n"; 

	page_fault = 0;
	page_hit = 0;
	infile.close();
	page_table.clear();
	address_map.clear();
	page_address.clear();
	page_buffer.clear();	
	
	}while(type ==1 || type == 2);

	return 0;	
}

void LRU_schedule(string pid){
	int address;
	string p_pid;

	bool not_exist = (page_table.find(pid) == page_table.end()); 
	
	if(not_exist){
		page_fault += 1;
		if(page_buffer.size() == buffer_size){
			// front in case of MRU
			p_pid = page_buffer.back();
			page_buffer.pop_back();
			page_table.erase(p_pid);
		}
	}
	else{
		page_hit += 1;
		page_buffer.erase(page_table[pid]);
	}

	page_buffer.push_front(pid);
	page_table[pid] = page_buffer.begin();

	//show_list();

	return;
}

void MRU_schedule(string pid){
	int address;
	string p_pid;
	bool not_exist = (page_table.find(pid) == page_table.end());

	if(not_exist){
		page_fault += 1;
		if(page_buffer.size() == buffer_size){
			p_pid = page_buffer.front();
			page_buffer.pop_front();
			page_table.erase(p_pid);
		}
	}
	else{
		page_hit += 1;
		page_buffer.erase(page_table[pid]);
	}

	page_buffer.push_front(pid);
	page_table[pid] = page_buffer.begin();

	//show_list();

	return;
}

int get_address(){
	int address;
	address = dis(gen);
	
	while(address_map.find(address) != address_map.end())
		address = dis(gen);

	address_map[address] = true;

	return address;
}

void show_list(){
	for(auto l : page_buffer)
		cout << l << '\t';
	cout << '\n';

	return;
}