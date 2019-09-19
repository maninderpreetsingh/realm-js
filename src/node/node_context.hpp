////////////////////////////////////////////////////////////////////////////
//
// Copyright 2016 Realm Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////

#pragma once

#include "node_types.hpp"
#include "napi.h"
#include "node_napi_convert.hpp"

namespace realm {
namespace js {

//template<>
//inline v8::Local<v8::Context> node::Context::get_global_context(v8::Isolate* isolate) {
//	return isolate->GetCurrentContext();
//}

template<>
inline Napi::Object node::Context::get_global_context(Napi::Env env) {
	return env.Global();
}

//template<>
//inline AbstractExecutionContextID node::Context::get_execution_context_id(v8::Isolate* isolate)
//{
//	return reinterpret_cast<AbstractExecutionContextID>(isolate);
//}


//NAPI: AbstractExecutionContextID does not exists in NAPI
template<>
inline AbstractExecutionContextID node::Context::get_execution_context_id(Napi::Env env)
{
	v8::Isolate* isolate = realm::node::getIsolate(env);
    return reinterpret_cast<AbstractExecutionContextID>(isolate);
}

} // js
} // realm
