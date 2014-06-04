//
//  SqliteHandler.h
//
//  Created by beckheng on 14-5-4.
//
//

#ifndef __beckheng__SqliteHandler__
#define __beckheng__SqliteHandler__

#include <iostream>

#include <vector>
#include <string>
#include <map>

#include <sqlite3.h>

typedef std::vector<std::map<std::string, std::string>> DataTable;
typedef std::map<std::string, std::string> DataRow;

namespace yaoheng { namespace lin {
	class SqliteHandler {
	public:
		SqliteHandler(std::string pPath);
		~SqliteHandler();
		
		bool isDbExists();
		DataTable executeQuery(std::string sql); // SELECT statement
		long executeUpdate(std::string sql); // INSERT UPDATE DELETE statement
		long executeUpdateAnGetIdentity(std::string sql); // INSERT AND GET NEW IDENTITY SEQUENCE ID
		
		DataRow getFirstRow(std::string sql);
		
		static std::string dbEncode(std::string str);
		
	private:
		std::string path;
	};
} }


#endif
