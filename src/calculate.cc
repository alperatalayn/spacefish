#include <node.h>
#include <string>
#include <iostream>
#include "board.h"
#include "move.h"
#include "generator.h"
using namespace v8;
namespace calculate
{
	void Initial(const FunctionCallbackInfo<Value>&args)
	{
		Isolate* isolate = args.GetIsolate();
		Board b;
		b.initialize();
		std::string str = b.createFEN();
		auto result = String::NewFromUtf8(isolate,str.c_str());
		args.GetReturnValue().Set(result.ToLocalChecked());
	}

	void MakeMove(const FunctionCallbackInfo<Value>&args)
	{
		Isolate* isolate = args.GetIsolate();
		Local<Context> context = isolate->GetCurrentContext();
		// Check the number of arguments passed.
		if (args.Length() != 3) {
		  // Throw an Error that is passed back to JavaScript
		  isolate->ThrowException(Exception::TypeError(
		      String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
		  return;
		}

		// Check the argument types
		if (!args[0]->IsString() || !args[1]->IsNumber() || !args[2]->IsNumber()) {
		  isolate->ThrowException(Exception::TypeError(
		      String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
		  return;
		}

		Board b;
		Move m;
		int source = (int)(args[1]->Int32Value(context).FromJust());
		int destination = (int)(args[2]->Int32Value(context).FromJust());
		m.setSrc(source);
		m.setDest(destination);
		v8::String::Utf8Value str(isolate, args[0]);
	    std::string cppStr(*str);
		b.parseFEN(cppStr);
		b.move(m);
		std::string finalStr = b.createFEN();
		auto result = String::NewFromUtf8(isolate,finalStr.c_str());
		args.GetReturnValue().Set(result.ToLocalChecked());
	}
	void GetLegals(const FunctionCallbackInfo<Value>&args)
	{
		Isolate* isolate = args.GetIsolate();
		Local<Context> context = isolate->GetCurrentContext();
		// Check the number of arguments passed.
		if (args.Length() != 1) {
		  // Throw an Error that is passed back to JavaScript
		  isolate->ThrowException(Exception::TypeError(
		      String::NewFromUtf8(isolate, "Wrong number of arguments").ToLocalChecked()));
		  return;
		}

		// Check the argument types
		if (!args[0]->IsString()) {
		  isolate->ThrowException(Exception::TypeError(
		      String::NewFromUtf8(isolate, "Wrong arguments").ToLocalChecked()));
		  return;
		}

		Board b;
		Generator g;
		v8::String::Utf8Value str(isolate, args[0]);
	    std::string cppStr(*str);
		b.parseFEN(cppStr);
		std::queue<Move> legals= g.legalToRootFive(b);
		// Create a new empty array.
	  	Local<Array> result = Array::New(isolate,legals.size());
	  	int ctr=0;
		while (!legals.empty())
		{	
	  		Local<Object> o = Object::New(isolate);
			Move m = legals.front();
			legals.pop();
			o->Set(context,String::NewFromUtf8(isolate,"src").ToLocalChecked(),Number::New(isolate,m.getSrc()));
			o->Set(context,String::NewFromUtf8(isolate,"dest").ToLocalChecked(),Number::New(isolate,m.getDest()));
			result->Set(context,ctr, o);
			ctr++;
		}
		
		args.GetReturnValue().Set(result);
	}
	
	void Initialize(Local<Object> exports)
	{
		NODE_SET_METHOD(exports,"getFen",Initial);
		NODE_SET_METHOD(exports,"getLegals",GetLegals);
		NODE_SET_METHOD(exports,"move",MakeMove);
	}	
	NODE_MODULE(NODE_GYP_MODULE_NAME,Initialize);
};
