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
		auto cmp = current->key.compare(key);

		     if (cmp < 0) current_addr = &(current->right);
		else if (cmp > 0) current_addr = &(current->left);
		else break;
		
        parent = current;
	}
	return std::tuple{ current_addr, parent };
}

inline void gnem::SymbolTable::search_loop2(std::string key, gnem::SymbolTable::Node** start) noexcept
{
	auto ret_addr = start; // it is never null because has reserved space in SymbolTable

	// *ret_addr can be null for example when the tree is just created and there is no root populated
	for (auto current = *start; current != nullptr; current = *start)
	{
		auto cmp = current->key.compare(key);
		     if (cmp < 0) start = &(current->right);
		else if (cmp > 0) start = &(current->right);
		else break;
	}
	return;
}

void gnem::SymbolTable::put(std::string key, std::optional<int> value) {
	auto [nodo, parent] = search_loop(key);

	if (*nodo == nullptr) {
		// asign it to tmp to avoid modification of tree in case of memory alocation failure 
		auto tmp = new Node{ key, value }; // can throw exception
		tmp->parent = parent;
		*nodo = tmp;
		// go up and increase count by +1 for each passed node until getting the root 
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


std::string gnem::SymbolTable::floor(std::string key) {
	Node* current = root;

	Node* max_less_than_key = nullptr;

	while (current != nullptr)
	{
		auto cmp = key.compare(current->key);
		if (cmp == 0) {
			return current->key; // max = current
		}
		if (cmp < 0) { // key < current
			current = current->left;
			continue;
		}
		if (max_less_than_key)
		{
			if (max_less_than_key->key.compare(current->key) < 0) // curent < key && current > max
				max_less_than_key = current; // may be it is if on the right subtree there is no key less than G and greater than max_less_than_key
		}
		else
		{
			max_less_than_key = current;
		}
		current = current->right;
	}
	if (max_less_than_key) return max_less_than_key->key;
	return "";

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