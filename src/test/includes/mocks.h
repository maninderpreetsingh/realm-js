////////////////////////////////////////////////////////////////////////////
//
// Copyright 2021 Realm Inc.
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
#include "common/object/interfaces.hpp"

struct MockedCollection: public IOCollection{
        realm::Mixed mixed;
        MockedCollection(double start): mixed{start} {}
        realm::Mixed get(std::string) override{
            
            //printf("Collection::Get-> %f \n", ret);
            return mixed;
        }

        void set(std::string key, realm::Mixed val) override{
           mixed = val;
        }

        void remove(std::string key) override {
            printf("calling remove...");
        }

        bool contains(std::string key) override {
            return true;
        }
};

struct MockedGetterSetter: public accessor::IAccessor{
    IOCollection *collection{nullptr};

    MockedGetterSetter(IOCollection *_collection): collection{_collection}{}

    void set(accessor::Arguments args) {
        double N = JSValueToNumber(args.context, args.value, nullptr);
        collection->set("N", realm::Mixed(N));

        if(N == -1){
            args.throw_error("Error: No Negative Number Please.");
        }
    }

    JSValueRef get(accessor::Arguments args) {
        return JSValueMakeNumber(args.context, collection->get(args.property_name).get_double());
    }

    ~MockedGetterSetter(){}
};