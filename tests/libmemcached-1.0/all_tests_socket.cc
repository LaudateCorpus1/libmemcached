/*  vim:expandtab:shiftwidth=2:tabstop=2:smarttab:
 * 
 *  Libmemcached Client and Server 
 *
 *  Copyright (C) 2012 Data Differential, http://datadifferential.com/
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are
 *  met:
 *
 *      * Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *      * Redistributions in binary form must reproduce the above
 *  copyright notice, this list of conditions and the following disclaimer
 *  in the documentation and/or other materials provided with the
 *  distribution.
 *
 *      * The names of its contributors may not be used to endorse or
 *  promote products derived from this software without specific prior
 *  written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <config.h>
#include <libtest/test.hpp>

#include "tests/basic.h"
#include "tests/debug.h"
#include "tests/deprecated.h"
#include "tests/error_conditions.h"
#include "tests/exist.h"
#include "tests/ketama.h"
#include "tests/namespace.h"
#include "tests/parser.h"
#include "tests/libmemcached-1.0/dump.h"
#include "tests/libmemcached-1.0/generate.h"
#include "tests/libmemcached-1.0/haldenbrand.h"
#include "tests/libmemcached-1.0/stat.h"
#include "tests/touch.h"
#include "tests/callbacks.h"
#include "tests/pool.h"
#include "tests/print.h"
#include "tests/replication.h"
#include "tests/server_add.h"
#include "tests/virtual_buckets.h"

#include "tests/libmemcached-1.0/setup_and_teardowns.h"


#include "tests/libmemcached-1.0/mem_functions.h"
#include "tests/libmemcached-1.0/encoding_key.h"

/* Collections we are running */
#include "tests/libmemcached-1.0/all_tests.h"

#include "tests/libmemcached_world_socket.h"

void get_world(Framework *world)
{
  world->collections= collection;

  world->_create= (test_callback_create_fn*)world_create;
  world->_destroy= (test_callback_destroy_fn*)world_destroy;

  world->item._startup= (test_callback_fn*)world_test_startup;
  world->item.set_pre((test_callback_fn*)world_pre_run);
  world->item.set_flush((test_callback_fn*)world_flush);
  world->item.set_post((test_callback_fn*)world_post_run);
  world->_on_error= (test_callback_error_fn*)world_on_error;

  world->collection_startup= (test_callback_fn*)world_container_startup;
  world->collection_shutdown= (test_callback_fn*)world_container_shutdown;

  world->set_runner(new LibmemcachedRunner);
}
