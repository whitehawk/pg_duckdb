#include "pgduckdb/pgduckdb_utils.hpp"

extern "C" {
#include "postgres.h"
#include "utils/memutils.h"
#include "utils/palloc.h"
}

namespace pgduckdb::pg {

MemoryContext
MemoryContextCreate(MemoryContext parent, const char *name) {
	return PostgresFunctionGuard(::AllocSetContextCreateInternal, parent, name, ALLOCSET_DEFAULT_MINSIZE,
	                             ALLOCSET_DEFAULT_INITSIZE, ALLOCSET_DEFAULT_MAXSIZE);
}

MemoryContext
MemoryContextSwitchTo(MemoryContext target) {
	return PostgresFunctionGuard(::MemoryContextSwitchTo, target);
}

void
MemoryContextReset(MemoryContext context) {
	PostgresFunctionGuard(::MemoryContextReset, context);
}

// GPDB-specific
#undef MemoryContextDelete

void
MemoryContextDelete(MemoryContext context) {
#if 0 // GPDB-specific
	PostgresFunctionGuard(::MemoryContextDelete, context);
#else
	PostgresFunctionGuard(::MemoryContextDeleteGPDB, context);
#endif
}

} // namespace pgduckdb::pg
