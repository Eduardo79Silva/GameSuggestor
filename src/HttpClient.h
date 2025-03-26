#pragma once

#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>

class HttpClient {
public:
  HttpClient();
  ~HttpClient();
  nlohmann::json callAPI(const std::string &url);

private:
  CURL *handle;
  static size_t WriteCallback(void *contents, size_t size, size_t nmemb,
                              std::string *userData);
};
