/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */
#include <iostream>
#include <memory>
#include <Broker.h>


using namespace qpid::broker;
using namespace qpid::sys;

Broker::Broker(const Configuration& config) :
    acceptor(Acceptor::create(config.getPort(),
                              config.getConnectionBacklog(),
                              config.getWorkerThreads(),
                              config.isTrace())),
    factory(config.getStore())
{ }


Broker::shared_ptr Broker::create(int16_t port) 
{
    Configuration config;
    config.setPort(port);
    return create(config);
}

Broker::shared_ptr Broker::create(const Configuration& config) {
    return Broker::shared_ptr(new Broker(config));
}    
        
void Broker::run() {
    acceptor->run(factory);
}

void Broker::shutdown() {
    acceptor->shutdown();
}

Broker::~Broker() { }

const int16_t Broker::DEFAULT_PORT(5672);
