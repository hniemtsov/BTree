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
			Node* parent = nullptr;
			size_t count = 0;
		};
		Node* root = nullptr;
	public:

		//SymbolTable(); // ctor Do I need?
		void put(std::string key, std::optional<int> value); // overwrites old value with new value - Are you ok with that
		std::optional<int>  get(std::string key) noexcept; 

		std::string floor(std::string key) noexcept;
		size_t rank(std::string key) noexcept;

		bool contains(std::string key);
		void remove(std::string key);

		const std::vector<std::string>& keys() const;

		size_t size() {
			return size(root);
		}

	private:
		inline auto search_loop(std::string key) noexcept -> decltype(auto);

		size_t size(Node* x)
		{
			return ((nullptr == x) ? 0 : x->count);
		}

		std::vector<std::string> keys_;
	};
}

