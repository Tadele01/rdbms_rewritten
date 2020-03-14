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
#include <fstream>
using namespace std;

const string QUERY_END = ";";
const int MIN_QUERY_SIZE = 3;
const int MAX_KEYWORD_SIZE = 3;
const char* WORKING_DIR = "/home/tade/Documents/databases";
vector<string> keywords = {
		"create",
		"table", 
		"values", 
		"database", 
		"use",
		"describe",
		"drop",
		"show",
		"databases",
		"tables", 
		"into", 
		"from",		
		"intersect",
		"union",
		"crossproduct",
		"join",	
		"setdifference",
		"project" };

vector<string> identifiers = {"int", "string", "bool", "char"};
void generate_error(int code);
vector<string> table_helper(vector<string> vector_form);
void working_dir_mover(){
	
	chdir(WORKING_DIR);
}
bool is_working_dir(){
	char* current_dir;
	string working_dir = "/home/tade/Documents/databases";
	current_dir = get_current_dir_name();
	string my_string(current_dir);
	string dir_ak = current_dir;
	if(dir_ak.compare(working_dir) == 0){
		return true;
	}
	else{
		return false;
	}
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
	bool is_working = is_working_dir();
	char* current_dir = get_current_dir_name();
	string my_string(current_dir);
	if(is_working){
		generate_error(12);
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
		generate_error(10);
	}
	else{
		cout << dbname << " database removed" << endl;
	}
}

void create_database(string dbname){	
	working_dir_mover();
	const char* database_name = dbname.c_str();
	if(mkdir(database_name, 0777) == -1){
		generate_error(9);
	}
	else{
		cout << dbname << " database created" << endl;
	}
}

void create_table(string tablename, vector<string> query){
	bool is_working = is_working_dir();
	char* current_dir = get_current_dir_name();
	string my_string(current_dir);
	int last_index = query.size() ;
	if(is_working){
		generate_error(12);
	}
	else{
		fstream fout;
		fout.open(tablename+".csv", ios::out | ios::app); 
		for(int i = 1; i <= last_index; i++){
			if(i%2 != 0){
				fout << query[i - 1] << ":";
			}
			else{
				fout << query[i - 1] << ",";
			}
		}
		fout << "\n" ;
	}	
}


void use_database(string dbname){
	working_dir_mover();
	const char* database_name = dbname.c_str();
	chdir(database_name);
	cout << "database changed to : " << database_name << endl;
}

void describe_table(string tablename){
	bool is_working = is_working_dir();
	char* current_dir = get_current_dir_name();
	string my_string(current_dir);
	if(is_working){
		generate_error(12);
	}
	else{
		
	}
}
vector<string> vectorizer(string sql_query){
	vector<string> vector_form;
	istringstream stream(sql_query);
	do{
		string sub;
		stream >> sub;
		vector_form.push_back(sub);
	}while(stream);
	vector_form.pop_back();
	return vector_form;
}

vector<string> table_helper(vector<string> vector_form, int start_index, int flag){
	vector<string> new_vector;
	vector<string> parsed;
	vector<string> collector;
	int last_index = vector_form.size() - 2;
	string comma = ",";
	for(int i = start_index; i < last_index; i++){
		new_vector.push_back(vector_form[i]);
	}
	for(int i = 0; i < new_vector.size(); i++){
		if(comma.compare(new_vector[i]) == 0){
			if(parsed.size() == 2){
				if(flag){
					string dtype = parsed[1];
					if(count(identifiers.begin(), identifiers.end(), dtype)){
						collector.insert(collector.end(), parsed.begin(), parsed.end());
						parsed.erase(parsed.begin(), parsed.end());
					}
					else{
						generate_error(11);
					}
				}
				else{
					collector.insert(collector.end(), parsed.begin(), parsed.end());
					parsed.erase(parsed.begin(), parsed.end());	
				}
			}
			else{
				generate_error(6);
			}
		}
		else{
			parsed.push_back(new_vector[i]);
		}
	}
	return collector;
}
int table_not_exists(){
	return 0;
}

void generate_error(int code){
	cout<<"error_code: "<<code<<" : ";
    switch(code){
        case 0: cout<<"Table not present\n";
            break;
        case 1: cout<<"Column name not present in table\n";
            break;
        case 2: cout<<"No of column does not match\n";
            break;
        case 3: cout<<"Condition specified not present in table\n";
            break;
        case 4: cout<<"Wrong condition operation\n";
            break;
        case 5: cout<<"Insert semicolon at the end of a query\n";
            break;
        case 6: cout<<"Syntax error in query\n";
            break;
        case 7: cout<<"Multiple columns with same name please perform Rename operation\n";
            break;
        case 8: cout<<"Relations are Union incompatible\n";
            break;
		case 9: cout<<"Database already existed\n";
			break;
		case 10: cout<<"Database does not exist\n";
			break;
		case 11: cout<<"Undefined data type\n";
			break;
		case 12: cout<<"Please select a database\n";
			break;
		case 13: cout<<"Invalid table name\n";
			break;
    };

}

void insert_values(string tablename, vector<string> query){
	bool is_working = is_working_dir();
	char* current_dir = get_current_dir_name();
	string my_string(current_dir);
	int last_index = query.size() ;
	if(is_working){
		generate_error(12);
	}
	else{
		fstream fout;
		fout.open(tablename+".csv", ios::out | ios::app); 
		for(int i = 0; i < last_index; i++){
			fout << query[i] << ",";
		}
		fout << "\n" ;
	}	
}
void query_parser(string sql_query){
	vector<string> vector_form = vectorizer(sql_query);
	int query_size = vector_form.size();
	int last_index = query_size - 1;
	string semi_colon = vector_form[last_index];
	string first = vector_form[0];
	if(query_size < MIN_QUERY_SIZE){
		generate_error(6);
	}
	
	if (semi_colon.compare(QUERY_END) != 0){
		generate_error(5);
	}
	else if(query_size == 3){
		string db_or_table = vector_form[1];
		if(db_or_table.compare("tables") == 0){
			show_tables();
		}	
		else if(db_or_table.compare("databases") == 0){
			show_databases();
		}
	}
	else if(first.compare("use") == 0){
		string name = vector_form[2];
		use_database(name);
	}
	else if(first.compare("create") == 0){
		string table_or_db = vector_form[1];
		string name = vector_form[2];
		if(table_or_db.compare("table") == 0){
			string starting_brace = vector_form[3];
			string closing_brace = vector_form[query_size - 2];
			if(starting_brace.compare("(") ==0 and closing_brace.compare(")") == 0){
				vector<string> query = table_helper(vector_form, 4, 1); 
				create_table(name, query);	
			}
			else{
				generate_error(6);		
			}
		}
		else if(table_or_db.compare("database") == 0){
			create_database(name);
		}
		else{
			generate_error(6);
		}
	}
	else if(first.compare("drop") == 0){
		string db = vector_form[1];
		string name = vector_form[2];	
		if(db.compare("database") == 0){
			drop_database(name);	
		}
		
	}
	else if(first.compare("insert") == 0 ){
		string into = vector_form[1];
		string tablename = vector_form[2];
		string values = vector_form[3];
		string starting_brace = vector_form[4];
		string closing_brace = vector_form[query_size - 2];
		if(count(keywords.begin(), keywords.end(), tablename)){
			generate_error(13);
		}
		if(table_not_exists()){
			generate_error(0);
		}
		if(starting_brace.compare("(") ==0 and closing_brace.compare(")") == 0){
			vector<string> query = table_helper(vector_form, 5, 0);
			insert_values(tablename, query);	
		}
		
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
	working_dir_mover();
	cout<< "\n>> ";
	while(getline(cin, sql_query)){
		string formatted_sql_query = input_formatter(sql_query);
		boost::trim_right(formatted_sql_query);
		if(formatted_sql_query=="exit"){
			cout << "Bye \n";
			break;
		}
		else if(formatted_sql_query!=""){
			query_parser(formatted_sql_query);
			
		}
		cout<< "\n>> ";
	}
	return 0;
	
}
