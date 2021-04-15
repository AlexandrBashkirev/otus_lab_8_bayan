#pragma once
#include <string>
#include "file_hash_data.h"

namespace flaber {

	class file_hash_iterator
	{

	public:

		using node_type = radix_tree_node;
		using value_type = std::string;
		using value_ref = value_type &;
		using value_ptr = value_type *;

		auto operator->() const
		{
			return const_cast<const value_ptr>(&value);
		}

		auto operator*() const
		{
			return const_cast<const value_ref>(value);
		}

		radix_tree_iterator& operator++()
		{
			find_next();
			return *this;
		}

		bool operator!=(const file_hash_iterator& right)
		{
			return current_idx != right.current_idx;
		}

		bool operator==(const file_hash_iterator& right)
		{
			return current_idx == right.current_idx;
		}

		file_hash_iterator(file_hash_data* _current) : 
			current(_current)
		{ }
		file_hash_iterator(const file_hash_iterator& node) = default;
		~file_hash_iterator() = default;

	private:
		

		file_hash_iterator() = delete;

		const file_hash_data* data;
		size_t current_idx;
		value_type value;


		void find_next(const flaber::radix_tree_node* node)
		{
			current_idx++;
			if(current_idx >= data->hashes.size())
			{
				if (!data->file_stream.is_open())
					data->file_stream.open(data->path_to_file, std::ios::in | std::ios::binary | std::ios::ate);

				file_stream.seekg(current_idx * block_size, std::ios_base::beg);
				std::memset(buffer.get(), 0, block_size);
				file_stream.read(buffer.get(), block_size);

				data->hashes.insert(data->hashes.end(), hasher->hash(buffer.get(), block_size));
			}
			value = 
		}
		
	};
	
}