#include <iostream>
#include <random>
#include <fstream>
#include <unordered_map>
#include <map>
#include <deque>

const int emp_disk_blocks = (int)1e3;
const int dept_disk_block = (int)1e2;
const int proj_disk_block = (int)5e2;
const int recd_per_disk = (int)1e1;
const int address_size = (int)1e6;
const int page_id_size = (int)1e3;

using namespace std;

unordered_map<string, bool> address_map;

string get_address(string s);
void generate_pid(string s1, string s2, int, int, int, int);


int main(){

	int address;

	generate_pid("E", "D", 0, 1000, emp_disk_blocks, dept_disk_block);
	generate_pid("D", "E", 1000, 0, dept_disk_block, emp_disk_blocks);
	generate_pid("P", "D", 1100, 1000, proj_disk_block, dept_disk_block);
	generate_pid("D", "P", 1000, 1100, dept_disk_block, proj_disk_block);

	//  Emp X Dept


}

void generate_pid(string s1, string s2, int start_r, int start_s, int r_block_size, int s_block_size){
	int e, E;
	int d, D;
	int p, P;
	int t_e, t_d, t_p;
	string S, R;
	string pattern = "";

	for( e= 1+start_r; e<= r_block_size+start_r ; e++ ){
		
		R = s1 + "_" + to_string(e);

		pattern += "\n" + R;
		
		for( d= 1+start_s; d<=s_block_size+start_s; d++ ){
			
			S = s2 + "_" + to_string(d);

			pattern += "\n" + S;

			for ( t_e=1; t_e<=recd_per_disk; t_e++ ){

				pattern += "\n" + R;

				for ( t_d=1; t_d<=recd_per_disk; t_d++){

					pattern += "\n" + S;
				}
			}
		}
	}
	
	string file = s1 + "_" + s2; 
	ofstream outfile;
	outfile.open(file,  ofstream::out);
	
	if(!outfile.is_open()){
		cout << "Error in writing to file: " << file << '\n';
		_Exit(0);
	}

	outfile << pattern;

	pattern.clear();
	outfile.close();
	return;

}

