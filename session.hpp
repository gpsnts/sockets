#pragma once

// System
#include <array>
#include <memory>
#include <string>
#include <fstream>

// Libs
#include <boost/asio.hpp>

using namespace std;
using namespace boost;

using Socket = boost::asio::ip::tcp::socket;

class Session : public std::enable_shared_from_this<Session> // Shared ptr
{
  public:
		Session(Socket socket);
		~Session();

		void procedure();

	private:
		
};