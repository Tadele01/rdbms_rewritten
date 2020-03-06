#include<bits/stdc++.h>
#include<sys/stat.h>
#include<sys/types.h>
#include <boost/algorithm/string.hpp>
#include <dirent.h>
#include <stdio.h>
#include <typeinfo>
#include <string.h>
#include <iostream>
#include <unistd.h>
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

void show_tables(){
	char* current_dir;
	string working_dir = "/home/tade/Documents/databases";
	current_dir = get_current_dir_name();
	string my_string(current_dir);
	if(current_dir == working_dir){
		cout << "please select a database" << endl;
	}
	else{
		DIR *dir;
		struct dirent *ent;
		if((dir = opendir(current_dir)) != NULL){
			while((ent = readdir(dir)) != NULL){
				printf("%s\n", ent->d_name);
			}
			closedir(dir);
		}
		else{
			perror("");
		}
	}	
}

void drop_database(string dbname){
	working_dir_mover();
	const char* database_name = dbname.c_str();
	if(rmdir(database_name) !=0){
		cout << "Database does not exist" << endl;
	}
	else{
		cout << dbname << " database removed" << endl;
	}
}

void create_database(string dbname){
	working_dir_mover();	
	const char* database_name = dbname.c_str();
	if(mkdir(database_name, 0777) == -1){
		cerr << "Error : "<< strerror(errno) << endl;
	}
	cout << dbname << " database created" << endl;	
}

void use_database(string dbname){
	working_dir_mover();
	const char* database_name = dbname.c_str();
	chdir(database_name);
	cout << "database changed to : " << dbname << endl;
}

void describe_table(string tablename){
	char* current_dir;
	string working_dir = "/home/tade/Documents/databases";
	current_dir = get_current_dir_name();
	string my_string(current_dir);
	if(current_dir == working_dir){
		cout << "please select a database" << endl;
	}
	else{
		
	}
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
			
			drop_database(formatted_sql_query);
		}
		cout<< "\n>> ";
	}
	return 0;
	
}
