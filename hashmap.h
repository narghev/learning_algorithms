#pragma once
#include <vector>
#include <memory>

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
		H.resize(5);
	}

	void insert(const Key& key, const Value& value) {
		int h = myhash(key) % H.size();
		
		while (H[h] != nullptr) {
			h = myhash(h) % H.size();
		}
		++size;
		H[h] = std::make_shared<std::pair<Key, Value> >(key, value);

		if (H.size() / size < 3) {
			rehash();
			// rehash everything.
			// 1 point for implementing the re-hashing, hash table expansion.
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

	void rehash(){
		std::vector<std::shared_ptr<std::pair<Key, Value> > > expanded_map;
		expanded_map.resize(size*3);
		for (auto pair : H){
			if (pair != nullptr){
				int h = myhash(pair->first) % expanded_map.size();
				while (expanded_map[h] != nullptr) {
					h = myhash(h) % expanded_map.size();
				}
				expanded_map[h] = std::make_shared<std::pair<Key, Value> >(pair->first, pair->second);
			}
		}
		H = expanded_map;
	}

	int size; // N
	// The hashmap.
	std::vector<std::shared_ptr<std::pair<Key, Value> > > H;
};