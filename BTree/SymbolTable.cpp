#include "SymbolTable.h"
#include <string>


namespace {

}

inline auto gnem::SymbolTable::search_loop(std::string key) noexcept -> decltype(auto)
{
	auto current_addr = &root; // it is never null because has reserved space in SymbolTable
	decltype(root) parent = nullptr;

	// *current_addr can be null for example when the tree is just created and there is no root populated
	for(auto current = *current_addr; current != nullptr; current = *current_addr)
	{
		auto cmp = key.compare(current->key);

		     if (cmp < 0) current_addr = &(current->left); // key < current
		else if (cmp > 0) current_addr = &(current->right);// key > current
		else break;                                        // key== current
		
        parent = current;
	}
	return std::tuple{ current_addr, parent };
}

void gnem::SymbolTable::put(std::string key, std::optional<int> value) {
	auto [nodo, parent] = search_loop(key);

	if (*nodo == nullptr) {
		// asign it to tmp to avoid modification of tree in case of memory alocation failure 
		auto tmp = new Node{ key, value }; // can throw exception
		tmp->parent = parent;
		*nodo = tmp;
		// go up and increase count by +1 for each passed node until getting the root 
		for (; tmp != nullptr; tmp = tmp->parent)
			tmp->count++;
	}
	else
		(*nodo)->val = value;
}
std::optional<int> gnem::SymbolTable::get(std::string key) noexcept {
	auto [nodo, _] = search_loop(key);
	if (*nodo == nullptr)
		return std::optional<int>();// *nodo = new Node{ key, value }; // can throw exception
	else
		return (*nodo)->val;
}

/// <summary>Maximum less then key from parameter. For example floor("G")</summary>
/// <param name="key">key to compare with. For example "G"</param>
/// <returns>
/// 1) 'key' passed in argument if Node with such key is found in tree. For example: G if G is present in tree.
/// 2) empty string if there is no Node with key less than passed in arguments. 
/// 3) maximum which is less than 'key' 
/// </returns>
std::string gnem::SymbolTable::floor(std::string key) noexcept {
	auto current = root;
	decltype(current) max_less_than_key = nullptr;

	while (current != nullptr)
	{
		auto cmp = key.compare(current->key);
			
		     if (cmp < 0) current = current->left; // key < current
		else if (cmp > 0)                          // key > current
		{
			max_less_than_key = current;
			current = current->right; // we are going to the right so there are if so greatest keys than current saved into max_less_than_key
		}
		else return current->key; // 1) max = current
	}
	if (max_less_than_key) return max_less_than_key->key; // 3) found maximum less than 'key'
	return ""; // 2) no nodes with key less than 'key'
}

/// <summary>
/// Count number of keys less than given 'key' in argument
/// </summary>
/// <param name="key">given key to found how many are there keys less than that</param>
/// <returns>size_t : number keys less than given in argument</returns>
size_t gnem::SymbolTable::rank(std::string key) noexcept {
	size_t ret = 0;

	auto current = root;
	decltype(current) max_less_than_key = nullptr;

	while (current != nullptr)
	{
		auto cmp = key.compare(current->key);

		if (cmp < 0) current = current->left;// key < current
		else                                 // key >= current
		{
			ret += size(current->left);

			if (cmp > 0)                     // key > current
			{
				ret += 1;
				current = current->right; // we are going to the right because given key is greater than current
			}
			else break;      // key== current
		}
	}
	return ret; 
}

bool gnem::SymbolTable::contains(std::string key) {
	return get(key).has_value();
}

void gnem::SymbolTable::remove(std::string key) {
	put(key, std::optional<int>());
}

std::vector<std::string> const& gnem::SymbolTable::keys() const
{
	return keys_;
}