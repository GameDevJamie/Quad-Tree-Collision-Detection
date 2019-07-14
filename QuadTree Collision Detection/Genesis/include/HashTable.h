#pragma once

#include "Defines.h"
#include <unordered_map>

namespace Genesis
{
	template<typename TKey, typename TValue>
	class HashTable
	{
		private:
			std::unordered_map<TKey, TValue> m_HashTable;

			//Prevent Copy Constructor and Assignment Operator from being used
			HashTable(const HashTable&);
			HashTable& operator=(const HashTable&);

		public:
			HashTable(const TInt32& reserve = 100)
			{
				m_HashTable.reserve(reserve);
			}
			~HashTable()
			{ 
				RemoveAllKeyValues(); 
			}

			//Returns a list of all Keys currently in the Table
			std::vector<TKey> GetKeys()
			{
				std::vector<TKey> keys;
				keys.reserve(m_HashTable.size());
				
				for (auto it : m_HashTable)
				{
					keys.push_back(it.first);
				}

				return keys;
			}

			//Returns a list of all Values in table
			std::vector<TValue> GetValues()
			{
				std::vector<TValue> values;
				values.reserve(m_HashTable.size());

				for (auto it : m_HashTable)
				{
					values.push_back(it.second);
				}

				return values;
			}

			//Returns the number of elements in the table
			//inline TInt32 GetSize() { return m_HashTable.size(); }

			bool LookUp(const TKey& key, TValue* value)
			{
				auto it = m_HashTable.find(key);
				if (it == m_HashTable.end()) return false;
				
				(*value) = (it->second);
				return true;
			}

			bool LookUpIndex(const TInt32& index, TValue* value)
			{
				if (index < 0) return false;
				if (index >= m_HashTable.size()) return false;

				auto it = m_HashTable.begin();
				int count = 0;
				while (count < index)
				{
					it++;
					count++;
				}

				(*value) = (it->second);

				return true;
			}

			//Insert a new Key and Value pair into the Hash Table
			//If the Key already exists, updates the value
			void SetKeyValue(const TKey& key, const TValue& value)
			{
				m_HashTable[key] = value;
			}

			//Remove the given key from the table, along with its corresponding Value
			bool RemoveKeyValue(const TKey& key)
			{
				auto it = m_HashTable.find(key);
				if (it == m_HashTable.end()) return false;

				m_HashTable.erase(key);
				return true;
			}

			//Removes all Keys and their corresponding Values
			void RemoveAllKeyValues()
			{
				m_HashTable.clear();
			}
	};
}