#include <vector>
#include <memory>
#include <thread> 

unsigned int myhash(const std::string& key) {
	int h = 0;
	for (int i = 0; i < key.size(); ++i) {
		h = 257 * h + key[i];
	}
	return h;
}

unsigned int myhash(const int& key) {
	return key * 10000001;
}

template<class Key, class Value>
class HashMap {
public:

	HashMap() {
		H.resize(2);
	}

	void insert(const Key& key, const Value& value) {
		int h = myhash(key) % H.size();
		
		while (H[h] != nullptr) {
			h = myhash(h) % H.size();
		}
		++size;
		H[h] = std::make_shared<std::pair<Key, Value> >(key, value);

		if (H.size() / size < 3) {
			std::thread rehash_thread	(&HashMap::rehash, this);
			rehash_thread.join();
		}
	}

	// Returns value in out parameter value_out
	bool find(Key key, Value* value_out) {
		int h = myhash(key) % H.size();

		while (H[h] != nullptr) {
			if (H[h]->first == key) {
				*value_out = H[h]->second;
				return true;
			}
			h = myhash(h) % H.size();
		}
		return false;
	}
	
	// Returns true if found.
	bool erase(const Key& key) {
		// 1 point for implementing this function correctly. NOTE: you can not actually just set the item to null,
		// because the item must be replaced by the last item in the chain.
		return false;
	}

private:

	std::vector<std::shared_ptr<std::pair<Key, Value> > > expanding_map;
	std::vector<std::shared_ptr<std::pair<Key, Value> > > H;
	bool rehashing = false;
	int size = 0;

	void rehash(){
		rehashing = true;
		expanding_map.empty();
		expanding_map.resize(size*10);
		for (std::shared_ptr<std::pair<Key, Value> > pair : H){
			if (pair != nullptr){
				int h = myhash(pair->first) % expanding_map.size();
				while (expanding_map[h] != nullptr) {
					h = myhash(h) % expanding_map.size();
				}
				expanding_map[h] = std::make_shared<std::pair<Key, Value> >(pair->first, pair->second);
			}
		}
		H = expanding_map;
		rehashing = false;
	}
};