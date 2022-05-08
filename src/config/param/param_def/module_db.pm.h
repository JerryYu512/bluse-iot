#pragma once

#include <vector>
#include <string>
#include <stdint.h>
#include <iostream>
#include "enums/e_db.pm.h"
#include "module_db.pm.h"

namespace biot { 

typedef struct BiotAppDbLocal_s BiotAppDbLocal;
typedef struct BiotAppDb_s BiotAppDb;

struct BiotAppDbLocal_s {
	BiotAppDbType dbtype;
	BiotAppDbLocal_s() {
		dbtype = static_cast<BiotAppDbType>(0);
	}
};

struct BiotAppDb_s {
	BiotAppDbLocal localdb;
	BiotAppDb_s() {
	}
};


}
