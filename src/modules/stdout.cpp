//  Copyright (c) 2007-2008 Facebook
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
// See accompanying file LICENSE or visit the Scribe site at:
// http://developers.facebook.com/scribe/
//

#include "../scribe_module.h"
#include "../store.h"

class StdoutStore : public Store {
public:
  StdoutStore(const std::string& category,
              bool readable, bool multi_category);
};


Store* stdout_store_create(void *baton, const std::string& category,
                           bool readable, bool multi_category)
{
  return new StdoutStore(category, readable, multi_category);
}

void stdout_register(scribe_module_t *module, scribeHandler *scribe)
{
  Store::registerStore("stdout", stdout_store_create, NULL);
}

extern "C" {
  SCRIBE_MODULE_DECL(stdout, stdout_register)
};
