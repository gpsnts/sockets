#pragma once

#ifndef CONNECTION_SETTINGS_HPP_
#define CONNECTION_SETTINGS_HPP_

enum ConnectionStatus
{
  PENDING,
  CONNECTED,
  CANCELED,
  WAITING
};

#define CONNECTION_PORT 1337
#define HOST "localhost"

#endif // CONNECTION_SETTINGS_HPP_
