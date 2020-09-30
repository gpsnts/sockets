#pragma once

#ifndef CONNECTION_SETTINGS_HPP_
#define CONNECTION_SETTINGS_HPP_

#define DEFAULT_PORT 1337
#define DEFAULT_HOST "localhost"

// System
#include <iostream>
#include <fstream>
#include <string>

// Libs
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/thread.hpp>
#include <boost/make_shared.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>

// Libs - namespaces
using namespace std;
using namespace boost;
using TCP       = boost::asio::ip::tcp;
using Socket    = TCP::socket;
using Resolver  = TCP::resolver;

#endif // CONNECTION_SETTINGS_HPP_
