#include "e_db.if.h"


namespace biot { 

template <> const char* get_enum_as_str<BiotAppDbType>(BiotAppDbType e) {
	switch(e) {
		case BiotAppDbType::DB_TYPE_SQLITE3:                 return "BiotAppDbType::DB_TYPE_SQLITE3";
		case BiotAppDbType::DB_TYPE_MONGODB:                 return "BiotAppDbType::DB_TYPE_MONGODB";
		case BiotAppDbType::DB_TYPE_MYSQL:                   return "BiotAppDbType::DB_TYPE_MYSQL";
		case BiotAppDbType::DB_TYPE_LEVELDB:                 return "BiotAppDbType::DB_TYPE_LEVELDB";
		case BiotAppDbType::DB_TYPE_CUSTOM:                  return "BiotAppDbType::DB_TYPE_CUSTOM";
		default: return nullptr;
	}
}

template <> const char* get_enum_str<BiotAppDbType>(BiotAppDbType e) {
	switch(e) {
		case BiotAppDbType::DB_TYPE_SQLITE3:                 return "BiotAppDbType::DB_TYPE_SQLITE3";
		case BiotAppDbType::DB_TYPE_MONGODB:                 return "BiotAppDbType::DB_TYPE_MONGODB";
		case BiotAppDbType::DB_TYPE_MYSQL:                   return "BiotAppDbType::DB_TYPE_MYSQL";
		case BiotAppDbType::DB_TYPE_LEVELDB:                 return "BiotAppDbType::DB_TYPE_LEVELDB";
		case BiotAppDbType::DB_TYPE_CUSTOM:                  return "BiotAppDbType::DB_TYPE_CUSTOM";
		default: return nullptr;
	}
}

template <> BiotAppDbType get_enum_value<BiotAppDbType>(const char* str) {
	static std::map<std::string, BiotAppDbType> emap = {
		{"BiotAppDbType::DB_TYPE_SQLITE3",               BiotAppDbType::DB_TYPE_SQLITE3},
		{"BiotAppDbType::DB_TYPE_MONGODB",               BiotAppDbType::DB_TYPE_MONGODB},
		{"BiotAppDbType::DB_TYPE_MYSQL",                 BiotAppDbType::DB_TYPE_MYSQL},
		{"BiotAppDbType::DB_TYPE_LEVELDB",               BiotAppDbType::DB_TYPE_LEVELDB},
		{"BiotAppDbType::DB_TYPE_CUSTOM",                BiotAppDbType::DB_TYPE_CUSTOM},
	};

	if (!str) { if (sizeof(BiotAppDbType) < sizeof(uint32_t)) { return static_cast<BiotAppDbType>(UINT64_MAX); } else { return static_cast<BiotAppDbType>(UINT64_MAX); } }

	auto key = emap.find(str);

	if (emap.end() == key) { if (sizeof(BiotAppDbType) < sizeof(uint64_t)) { return static_cast<BiotAppDbType>(UINT32_MAX); } else { return static_cast<BiotAppDbType>(UINT64_MAX); } }

	return key->second;
}

template <> bool in_enum_range<BiotAppDbType>(BiotAppDbType e) {
	switch(e) {
		case BiotAppDbType::DB_TYPE_SQLITE3:                 return true;
		case BiotAppDbType::DB_TYPE_MONGODB:                 return true;
		case BiotAppDbType::DB_TYPE_MYSQL:                   return true;
		case BiotAppDbType::DB_TYPE_LEVELDB:                 return true;
		case BiotAppDbType::DB_TYPE_CUSTOM:                  return true;
		default: return false;
	}
}


}
