#include "SymbolTable.h"
#include <string>


namespace {

}

inline auto gnem::SymbolTable::search_loop(std::string key) noexcept -> decltype(auto)
{
	auto ret_addr = &root; // it is never null because has reserved space in SymbolTable

	// *ret_addr can be null for example when the tree is just created and there is no root populated
	for(auto current = *ret_addr; current != nullptr; current = *ret_addr)
	{
		auto cmp = current->key.compare(key);
		     if (cmp < 0) ret_addr = &(current->right);
		else if (cmp > 0) ret_addr = &(current->left);
		else break;
	}
	return ret_addr;
}

inline auto gnem::SymbolTable::search_loop2(std::string key, gnem::SymbolTable::Node* start) noexcept -> decltype(auto)
{
	auto ret_addr = &start; // it is never null because has reserved space in SymbolTable

	// *ret_addr can be null for example when the tree is just created and there is no root populated
	for (auto current = *ret_addr; current != nullptr; current = *ret_addr)
	{
		auto cmp = current->key.compare(key);
		     if (cmp < 0) ret_addr = &(current->left);
		else if (cmp > 0) ret_addr = &(current->right);
		else break;
	}
	return ret_addr;
}

void gnem::SymbolTable::put(std::string key, std::optional<int> value) {
	auto nodo = search_loop(key);

	if (*nodo == nullptr)
		*nodo = new Node{ key, value }; // can throw exception
	else
		(*nodo)->val = value;
}
std::optional<int> gnem::SymbolTable::get(std::string key) noexcept {
	auto nodo = search_loop(key);
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