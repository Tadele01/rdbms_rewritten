#include<bits/stdc++.h>
#include<iostream>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>

using namespace std;

void working_dir_mover(){
	string working_dir = "/home/tade/Documents/databases";
	chdir(working_dir);
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
		if(formatted_sql_query=="exit"){
			cout<<"\n\nGood bye...\n";
			break;
		}
		else if(formatted_sql_query!=""){
			working_dir_mover();
		}
		cout<< "\n>> ";
	}
	return 0;
	
}
