//  Copyright (c) 2007-2009 Facebook
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

#ifndef SCRIBE_MODULE_H
#define SCRIBE_MODULE_H

#define SCRIBE_MODULE_VERSION 0xFF0001FF
#define SCRIBE_STANDARD_MODULE_STUFF  \
  SCRIBE_MODULE_VERSION,        \
  NULL,                         \
  __FILE__

class scribeHandler;

extern "C" {

typedef struct scribe_module_t {
  /** Used to check the module's version number is compatible 
   *  with Scribe's current version.
   */
  int version;
  
  /** @private : Internal DSO handle for this module. */
  void *dso_handle;
  
  /** __FILE__ from the module */
  const char *name;
  
  void (*register_func) (scribe_module_t *module, scribeHandler *scribe);
} scribe_module_t;

#define SCRIBE_MODULE_DECL(modname, regfunc) \
  scribe_module_t modname ## _module =  \
  {                                     \
    PWT_STANDARD_MODULE_STUFF,          \
    regfunc                             \
  };

};

#endif // SCRIBE_SERVER_H
