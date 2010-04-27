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
  ~StdoutStore();

  bool handleMessages(boost::shared_ptr<logentry_vector_t> messages);
  bool open();
  bool isOpen();
  void configure(pStoreConf configuration);
  void close();
  void flush();
  boost::shared_ptr<Store> copy(const std::string &category);

};

StdoutStore::StdoutStore(const std::string& category,
                         bool readable, bool multi_category):
  Store(category, "stdout", multi_category)
{
  
}

StdoutStore::~StdoutStore()
{
  flush();
}

bool StdoutStore::isOpen()
{
  return true;
}

bool StdoutStore::open()
{
  return true;
}

void StdoutStore::close()
{
  flush();
}

void StdoutStore::flush()
{
  fflush(stdout);
}

void StdoutStore::configure(pStoreConf conf)
{
}

bool StdoutStore::handleMessages(boost::shared_ptr<logentry_vector_t> messages)
{
  for (logentry_vector_t::iterator iter = messages->begin();
       iter != messages->end();
       ++iter) {
    logentry_ptr_t m = (*iter);
    /* could buffer this into a single fwrite, but meh, this works for a demo */
    fprintf(stdout, "[%s] ", m->category.c_str());
    fwrite(m->message.data(), m->message.size(), 1, stdout);
    fwrite("\n", 1, 1, stdout);
  }
  return true;
}

boost::shared_ptr<Store> StdoutStore::copy(const std::string &category) {
  StdoutStore *store = new StdoutStore(category, false, multiCategory);
  boost::shared_ptr<Store> copied = boost::shared_ptr<Store>(store);
  return copied;
}


Store* stdout_store_create(void *baton, const std::string& category,
                           bool readable, bool multi_category)
{
  return new StdoutStore(category, readable, multi_category);
}

void stdout_register(scribe_module_t *module, scribeHandler *scribe)
{
  std::string n = "stdout";
  Store::registerStore(n, stdout_store_create, NULL);
}

extern "C" {
  SCRIBE_MODULE_DECL(stdout, stdout_register);
};
