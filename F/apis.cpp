#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>       // std::string
#include <sstream>      // std::ostringstream
#include <math.h>
#include <sys/stat.h>
#include <vector>
#include <algorithm>

#include <curl/curl.h>  
//#include "nlohmann/json.hpp"
#include "json.hpp"

int cmp_nums_desc(int l, int r) { return l > r; }

static size_t curlwritebuf(void *contents, size_t size, size_t nmemb, std::string *sbuf)
{ 
 //printf("curlwritebuf\n");
 size_t realsize = size * nmemb;
 int bufcurlen = sbuf->length();
 //printf("sbuf length: %d\n", sbuf->length());
 sbuf->append((char *)contents, realsize);
 //printf("sbuf append length: %d\n", sbuf->length());
 //printf("sbuf append: %s\n", sbuf->c_str());
 //printf("curlwritebuf: %d\n", realsize);
 return realsize;
}

int main() {
 std::string url;
 std::getline(std::cin, url);

 int port;
 scanf("%d", &port);

 int a, b;
 scanf("%d", &a);
 scanf("%d", &b);

 if (url[url.length() - 1] == '/') {
  url.erase(url.length() - 1, 1);
 }

 std::ostringstream ourls;
 ourls << url;

 if (port != 80) {
  //snprintf(url, url.capacity(), ":%d", port);
  ourls << ':' << port;
 }

 //snprintf(url, url.capacity(), "/?a=%d&b=%d", a, b);
 ourls << '/' << "?a=" << a << "&b=" << b;

 url = ourls.str();

 //printf("url: %s\n", url.c_str());

 std::string sbuf;

  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlwritebuf);

    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &sbuf);
 
    res = curl_easy_perform(curl);
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    curl_easy_cleanup(curl);
/*
*/
 //printf("sbuf\n");
 //sbuf = "";
 //char astr[20] = "1234567890123456789";
 //printf("astr: %s\n", astr);
 //curlwritebuf(&astr, sizeof(char), 19, &sbuf);

 //printf("asdfasdf\n");
 //printf("sbuf: %s\n", sbuf.c_str());

 //sbuf = "[8,6,-2,2,4,17,256,1024,-17,-19]";

 nlohmann::json gotnums = nlohmann::json::parse(sbuf.c_str());
 //printf("json: %s\n", sbuf.c_str());

 std::vector<int> nums;
 for (int i = 0; i < gotnums.size(); i++) {
  int num = gotnums.at(i);
  nums.push_back(num);
 }
 std::sort(nums.begin(), nums.end(), cmp_nums_desc);
 for (std::vector<int>::iterator it = nums.begin(); it != nums.end(); ++it) {
  int num = *it;
  printf("%d\n", num);
 }
 return 0;
}