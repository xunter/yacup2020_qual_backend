#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>       // std::string
#include <sstream>      // std::ostringstream
#include <math.h>
#include <sys/stat.h>
#include <vector>
#include <algorithm>
#include <cstring>

//#include "nlohmann/json.hpp"
#include "json.hpp"


struct offer {
 std::string offer_id;
 int market_sku;
 int price;
 std::string sor;
};

struct feed {
 std::vector<offer> offers;
};

int cmp_offers(offer &l, offer &r) {
 if (l.price == r.price) {
  const char *lstr = l.offer_id.c_str();
  const char *rstr = r.offer_id.c_str();
  return strcmp(lstr, rstr);
 }
 return l.price < r.price;
}

int main() {
 int n, m;
 scanf("%d %d\n", &n, &m);

 std::vector<feed> feeds(n);
 std::vector<offer> offerstotal;
 for (int i = 0; i < n; i++) {
  std::string sbuf;
  std::getline(std::cin, sbuf);

  nlohmann::json jsonfeed = nlohmann::json::parse(sbuf.c_str());
  auto jsonoffers = jsonfeed["offers"];
  std::vector<offer> offers;
  for (int i = 0; i < jsonoffers.size(); i++) {
   auto jsonoffer = jsonoffers[i];
   offer o;
   jsonoffer.at("offer_id").get_to(o.offer_id);
   jsonoffer.at("market_sku").get_to(o.market_sku);
   jsonoffer.at("price").get_to(o.price);

   //std::cout << "offer_id=" << o.offer_id << ", market_sku=" << o.market_sku << ", price=" << o.price << std::endl;

   offers.push_back(o);
   offerstotal.push_back(o);
  }

  feed f;
  f.offers = offers;
  feeds.push_back(f);
  //printf("offers: %d\n", offers.size());
 }
 
 std::sort(offerstotal.begin(), offerstotal.end(), cmp_offers);
 nlohmann::json jsonofferstotal = nlohmann::json::array();
 for (int i = 0; i < (offerstotal.size() > m ? m : offerstotal.size()); i++) {
  offer o = offerstotal[i];
  nlohmann::json jsonoffer = { {"offer_id", o.offer_id }, { "market_sku", o.market_sku }, { "price", o.price } };
  jsonofferstotal.push_back(jsonoffer);
 }
 nlohmann::json jsontotal = {{ "offers" , jsonofferstotal }};

 std::cout << jsontotal.dump() << std::endl;

 return 0;
}