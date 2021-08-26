#pragma once

#include <string>
#include <functional>

class Client {
public:
  void getResponseFromServer(std::string message, std::function<void(std::string)> clb);
};
