//
//  json.h
//
//  Created by beckheng on 14-5-23.
//  Copyright (c) 2014年 beckheng. All rights reserved.
//

// don't support T for std::*
// rapidjson wrapper

#ifndef __beckheng__json__
#define __beckheng__json__

#include <iostream>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/filestream.h>
#include <rapidjson/stringbuffer.h>

void putMember(rapidjson::Document &document, const char *name, rapidjson::Value &val);
void putMember(rapidjson::Document &document, rapidjson::Value &object, const char *name, rapidjson::Value &val);
void putMember(rapidjson::Document &document, rapidjson::Value &array, rapidjson::Value &v);

rapidjson::StringBuffer jsonToStringBuffer(const rapidjson::Document &document);

template <typename T>
void putMember(rapidjson::Document &document, const char *name, T val)
{
	rapidjson::Value v(val);
	putMember(document, name, v);
}

template <typename T>
void putMember(rapidjson::Document &document, rapidjson::Value &object, const char *name, T val)
{
	rapidjson::Value v(val);
	putMember(document, object, name, v);
}

template <typename T>
void putMember(rapidjson::Document &document, rapidjson::Value &array, T val)
{
	rapidjson::Value v(val);
	
	putMember(document, array, v);
}

#endif /* defined(__beckheng__json__) */
