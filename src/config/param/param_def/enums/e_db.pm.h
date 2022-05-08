#pragma once


namespace biot { 

// 数据库类型
enum class BiotAppDbType {
	DB_TYPE_SQLITE3                      = 0,                     ///< sqlite3
	DB_TYPE_MONGODB                      = 1,                     ///< mongodb
	DB_TYPE_MYSQL                        = 2,                     ///< mysql
	DB_TYPE_LEVELDB                      = 3,                     ///< leveldb
	DB_TYPE_CUSTOM                       = 4,                     ///< 自研
};

}
