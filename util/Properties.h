//
//  Properties.h
//  FlyingTigerServer
//
//  Created by beckheng on 14-5-13.
//  Copyright (c) 2014年 beckheng. All rights reserved.
//

#ifndef __FlyingTigerServer__Properties__
#define __FlyingTigerServer__Properties__

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>

class Properties {
public:
	void load(const std::string &path);
	
	template <class T>
	T getProperty(const std::string &key, T defaultValue)
	{
		std::map<std::string, std::string>::const_iterator it = m.find(key);
		if (it != m.end())
		{
			std::stringstream value(m[key]);
			
			T o;
			value >> o;
			
			return o;
		}
		else
		{
			return defaultValue;
		}
	}
	
	void setProperty(std::string key, std::string value);
	
	std::vector<std::string> propertyNames();
	
private:
	static void trim(std::string &s);
	
	std::map<std::string, std::string> m;
};

#endif /* defined(__FlyingTigerServer__Properties__) */
