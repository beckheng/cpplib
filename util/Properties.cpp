//
//  Properties.cpp
//  FlyingTigerServer
//
//  Created by beckheng on 14-5-13.
//  Copyright (c) 2014年 beckheng. All rights reserved.
//

#include "Properties.h"

void Properties::load(const std::string &path)
{
	using namespace std;
	
	m.clear();
	
	ifstream infile(path.c_str());
	if (!infile)
	{
		cout << "load file " << path << " error\n";
		return;
	}
	
	string line, key, value;
	size_t pos;
	while (getline(infile, line)) {	
		if (line.empty())
		{
			continue;
		}
		
		if (line[0] == '#')
		{
			continue;
		}
		
		pos = line.find("=");
		if (pos == string::npos)
		{
			continue;
		}
		
		key = line.substr(0, pos);
		trim(key);
		if (key.empty())
		{
			continue;
		}
		
		value = line.substr(pos+1, line.size());
		trim(value);
		
		m[key] = value;
		
//		cout << line << "(" << line.size() << ")\n" << key << " = " << value << "\n";
	}
	
	infile.close();
}

void Properties::setProperty(std::string key, std::string value)
{
	m[key] = value;
}

std::vector<std::string> Properties::propertyNames()
{
	using namespace std;
	
	vector<string> names;
	
	map<string, string>::const_iterator it = m.begin();
	for (; it != m.end(); ++it) {
		names.push_back(it->first);
	}
	
	return names;
}

void Properties::trim(std::string &s)
{
	static const char whitespace[] = " \n\t\v\r\f";
    s.erase(0, s.find_first_not_of(whitespace));
    s.erase(s.find_last_not_of(whitespace) + 1U);
}
