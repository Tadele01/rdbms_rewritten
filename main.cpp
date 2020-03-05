#include<bits/stdc++.h>
#include<iostream>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include <boost/algorithm/string.hpp>

using namespace std;
const char* WORKING_DIR = "/home/tade/Documents/databases";
void working_dir_mover(){
	
	chdir(WORKING_DIR);
}
void show_databases(){
	DIR *dir = opendir(WORKING_DIR);
	struct dirent *entry = readdir(dir);
	while (entry != NULL){
		if(entry->d_type == DT_DIR)
			printf("%s\n", entry->d_name);
		entry = readdir(dir);
	}
	closedir(dir);
}



string space_remover(string sql_query){
	string temp;
	istringstream stream(sql_query);
	do{
		string sub;
		stream >> sub;
		temp += sub;
		temp += " ";
	}while(stream);
	return temp;
}
string ignore_case(string sql_query){
	string transformed = sql_query;
	transform(transformed.begin(), transformed.end(), transformed.begin(), ::tolower);
	return transformed;
}

string input_formatter(string sql_query){
	string formatted;
	formatted = space_remover(sql_query);
	formatted = ignore_case(formatted);
	return formatted;
}
int main(){	
	string sql_query;
	cout << "TQL..\n\n";
	cout << ">> ";
	while(getline(cin, sql_query)){
		string formatted_sql_query = input_formatter(sql_query);
		boost::trim_right(formatted_sql_query);
		if(formatted_sql_query=="exit"){
			cout << "Good Bye \n";
			break;
		}
		else if(formatted_sql_query!=""){
			working_dir_mover();
			cout << get_current_dir_name() << endl; 
		}
		cout<< "\n>> ";
	}
	return 0;
	
}
