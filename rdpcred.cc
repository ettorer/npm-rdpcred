#include <node.h>
#include <v8.h>
#include <uv.h>

#include <windows.h>
#include <wincred.h>

namespace cred {

	using node::AtExit;
	using v8::Exception;
	using v8::Function;
	using v8::FunctionCallbackInfo;
	using v8::Isolate;
	using v8::Local;
	using v8::Number;
	using v8::Boolean;
	using v8::Object;
	using v8::String;
	using v8::Value;
	using v8::Persistent;
	using v8::Handle;
	using v8::HandleScope;

	//Add the credentials to the Credential Manager
	//The input parameters are 3: targetName, username, passord
	//Return value is a boolean
	void add(const FunctionCallbackInfo<Value>& args)
	{
		Isolate* isolate = args.GetIsolate();
		if (args.Length() < 3) {// Throw an Error that is passed back to JavaScript
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
			return;
		}
		if (!args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString()) {
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
			return;
		}
		Local<String> t = args[0]->ToString();
		uint16_t* targetName = (uint16_t*)malloc((t->Length() + 1) * sizeof(uint16_t));
		t->Write(targetName);

		Local<String> u = args[1]->ToString();
		uint16_t* user = (uint16_t*)malloc((u->Length() + 1) * sizeof(uint16_t));
		u->Write(user);

		Local<String> p = args[2]->ToString();
		uint16_t* password = (uint16_t*)malloc((p->Length() + 1) * sizeof(uint16_t));
		p->Write(password);

		DWORD cbCreds = sizeof(uint16_t)*(1 + wcslen((LPWSTR)password));
		CREDENTIALW Credentials;
		memset(&Credentials, 0, sizeof(Credentials));
		Credentials.Type = CRED_TYPE_GENERIC;
		Credentials.TargetName = (LPWSTR)targetName;
		Credentials.CredentialBlobSize = cbCreds;
		Credentials.CredentialBlob = (LPBYTE)password;
		Credentials.Persist = CRED_PERSIST_LOCAL_MACHINE;
		Credentials.UserName = (LPWSTR)user;

		BOOL ok = ::CredWriteW(&Credentials, 0);

		free(targetName);
		free(user);
		free(password);

		if (ok) {
			args.GetReturnValue().Set(Boolean::New(isolate, true));
		} else {
			args.GetReturnValue().Set(Boolean::New(isolate, false));
		}
	}

	//Remove credentials: the parameter is the targetName
	//Return value is a boolean
	void del(const FunctionCallbackInfo<Value>& args)
	{
		Isolate* isolate = args.GetIsolate();
		if (args.Length() < 1) {// Throw an Error that is passed back to JavaScript
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong number of arguments")));
			return;
		}
		if (!args[0]->IsString()) {
			isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, "Wrong arguments")));
			return;
		}

		Local<String> s = args[0]->ToString();
		uint16_t* targetName = (uint16_t*)malloc((s->Length() + 1) * sizeof(uint16_t));
		s->Write(targetName);

		BOOL ok = ::CredDeleteW((LPWSTR)targetName, CRED_TYPE_GENERIC, 0);

		if (ok) {
			args.GetReturnValue().Set(Boolean::New(isolate, true));
		}
		else {
			args.GetReturnValue().Set(Boolean::New(isolate, false));
		}

		free(targetName);
	}

	void init(Local<Object> exports) {
		NODE_SET_METHOD(exports, "add", add);
		NODE_SET_METHOD(exports, "del", del);
	}

	NODE_MODULE(windows, init)
}
