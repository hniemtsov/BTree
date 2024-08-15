#pragma once
#include <optional>
#include <vector>
#include <string>

namespace gnem
{
	/// <summary>
	/// Key must be Comparable, can be imposed by Concept C++20
	/// 
	/// </summary>
	class SymbolTable
	{ 
		struct Node {
			std::string key;
			std::optional<int> val;
			Node* left = nullptr;
			Node* right= nullptr;
		};
		Node* root = nullptr;
	public:

		inline auto search_loop(std::string key) noexcept -> decltype(auto);

		//SymbolTable(); // ctor Do I need?
		void put(std::string key, std::optional<int> value); // overwrites old value with new value - Are you ok with that
		std::optional<int>  get(std::string key) noexcept; 

		bool contains(std::string key);
		void remove(std::string key);

		const std::vector<std::string>& keys() const;
		//{
		//	return keys_;
		//} 

		std::vector<std::string> keys_;
	};
}

