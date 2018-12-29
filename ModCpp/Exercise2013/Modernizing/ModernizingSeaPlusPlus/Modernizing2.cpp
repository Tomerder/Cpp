#include "Modernizing2.h"

// https://github.com/facebookarchive/scribe/blob/master/src/scribe_server.cpp#L149

fb_status scribeHandler::getStatus() {
	fb_status return_status(status);
	if (status == ALIVE) {
		for (category_map_t::iterator cat_iter = categories.begin();
			cat_iter != categories.end();
			++cat_iter) {
			for (store_list_t::iterator store_iter = cat_iter->second->begin();
				store_iter != cat_iter->second->end();
				++store_iter) {
				if (!(*store_iter)->getStatus().empty()) {
					return_status = WARNING;
					return return_status;
				}
			} // for each store
		} // for each category
	} // if we don't have an interesting top level status
	return return_status;
}

std::vector<fb_status> detailedStatus::getStatus() {
	std::vector<fb_status> result;
	result.push_back(ALIVE);
	result.push_back(WARNING);
	return result;
}