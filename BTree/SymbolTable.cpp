#include "SymbolTable.h"
#include <string>


namespace {

}

inline auto gnem::SymbolTable::search_loop(std::string key) noexcept -> decltype(auto)
{
	Node** ret_addr = &root; // it is never null because has reserved space in SymbolTable

	// *ret_addr can be null for example when the tree is just created and there is no root populated
	while (*ret_addr != nullptr)
	{
		auto cmp = (*ret_addr)->key.compare(key);
		     if (cmp < 0) ret_addr = &((*ret_addr)->left);
		else if (cmp > 0) ret_addr = &((*ret_addr)->right);
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