#pragma once

#include <map>
#include <list>
#include <vector>

enum fb_status {
	ALIVE,
	WARNING
};

struct detailedStatus {
	std::vector<fb_status> getStatus();
};

class scribeHandler {
public:
	fb_status getStatus();
private:
	fb_status status;

	typedef std::list<detailedStatus*> store_list_t;
	typedef std::map<std::string, store_list_t*> category_map_t;

	category_map_t categories;
};

