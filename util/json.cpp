//
//  json.cpp
//  TestPrj
//
//  Created by beckheng on 14-5-23.
//  Copyright (c) 2014年 beckheng. All rights reserved.
//

#include "json.h"

void putMember(rapidjson::Document &document, const char *name, rapidjson::Value &val)
{
	using namespace rapidjson;
	
	Document::AllocatorType& allocator = document.GetAllocator();
	
	if (document.IsObject())
	{
		if (!document.HasMember(name))
		{
			document.AddMember(name, val, allocator);
		}
		else if (document[name].IsArray())
		{
			document[name].PushBack(val, allocator);
		}
		else
		{
			document[name] = val;
		}
	}
}

void putMember(rapidjson::Document &document, rapidjson::Value &object, const char *name, rapidjson::Value &val)
{
	using namespace rapidjson;
	
	Document::AllocatorType& allocator = document.GetAllocator();
	
	if (object.IsObject())
	{
		if (!object.HasMember(name))
		{
			object.AddMember(name, val, allocator);
		}
		else if (document[name].IsArray())
		{
			document[name].PushBack(val, allocator);
		}
		else
		{
			document[name] = val;
		}
	}
}

void putMember(rapidjson::Document &document, rapidjson::Value &array, rapidjson::Value &v)
{
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	
	if (array.IsArray())
	{
		array.PushBack(v, allocator);
	}
}

rapidjson::StringBuffer jsonToStringBuffer(const rapidjson::Document &document)
{
	rapidjson::StringBuffer buf;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buf);
	document.Accept(writer);
	
	return buf;
}
