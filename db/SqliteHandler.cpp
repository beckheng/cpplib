//
//  SqliteHandler.cpp
//
//  Created by beckheng on 14-5-4.
//
//

#include "SqliteHandler.h"

#include <stdlib.h>

using namespace yaoheng::lin;

SqliteHandler::SqliteHandler(std::string pPath)
{
	path = pPath;
}

SqliteHandler::~SqliteHandler()
{
	
}

std::string SqliteHandler::dbEncode(std::string str)
{
	if (str.size() == 0)
	{
		return "";
	}
	
	std::string out;
	for (int i = 0; i < str.size(); i++) {
		char c = str[i];
		switch (c) {
			case '\\':
				out.append("\\\\");
				break;
			case '\r':
				out.append("\\r");
				break;
			case '\n':
				out.append("\\n");
				break;
			case '\t':
				out.append("\\t");
				break;
			case '\b':
				out.append("\\b");
				break;
			case '\'':
				out.append("\'\'");
				break;
			case '\"':
				out.append("\\\"");
				break;
			default:
				out += c;
				break;
		}
	}
	
	return out;
}

bool SqliteHandler::isDbExists()
{
	bool ret = false;
	
	FILE* f = fopen(path.c_str(), "r");
	if (f != NULL)
	{
		ret = true;
		
		fclose(f);
	}
	
	return ret;
}

DataTable SqliteHandler::executeQuery(std::string sql)
{
	using namespace std;
	DataTable rows;
	
	sqlite3* db = NULL;
	char* errmsg = NULL;
	char** dbResult;
	int nRow, nColumn, index, i, j;
	int result = sqlite3_open(path.c_str(), &db);
	if (result == SQLITE_OK)
	{
		result = sqlite3_get_table(db, sql.c_str(), &dbResult, &nRow, &nColumn, &errmsg);
		if (result == SQLITE_OK)
		{
			index = nColumn;
			
			for (i = 0; i < nRow; i++) {
				DataRow item;
				for (j = 0; j < nColumn; j++) {
					string value(dbResult[index]);
					item.insert(pair<string, string>(dbResult[j], value));
					
					++index;
				}
				rows.push_back(item);
			}
		}
		else
		{
			printf("sqlite_error %s\n", errmsg);
		}
	}
	sqlite3_free(errmsg);
	sqlite3_free_table(dbResult);
	sqlite3_close(db);
	
	return rows;
}

long SqliteHandler::executeUpdate(std::string sql)
{
	long ret = -1;
	char *errmsg = 0;
	
	sqlite3* db = NULL;
	int result = sqlite3_open(path.c_str(), &db);
	if (result == SQLITE_OK)
	{
		result = sqlite3_exec(db, sql.c_str(), NULL, NULL, &errmsg);
		if (result == SQLITE_OK)
		{
			ret = sqlite3_changes(db);
		}
		else
		{
			printf("sqlite_error %s\n", errmsg);
		}
	}
	sqlite3_free(errmsg);
	sqlite3_close(db);
	
	return ret;
}

long SqliteHandler::executeUpdateAnGetIdentity(std::string sql)
{
	long ret = -1;
	char *errmsg = 0;
	
	sqlite3* db = NULL;
	int result = sqlite3_open(path.c_str(), &db);
	if (result == SQLITE_OK)
	{
		result = sqlite3_exec(db, sql.c_str(), NULL, NULL, &errmsg);
		if (result == SQLITE_OK)
		{
			ret = sqlite3_last_insert_rowid(db);
		}
		else
		{
			printf("sqlite_error %s\n", errmsg);
		}
	}
	sqlite3_free(errmsg);
	sqlite3_close(db);
	
	return ret;
}

DataRow SqliteHandler::getFirstRow(std::string sql)
{
	DataRow row;
	
	DataTable rows = executeQuery(sql);
	if (rows.size() > 0)
	{
		row = rows[0];
	}
	
	return row;
}
