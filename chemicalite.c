#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT1

#include "chemicalite.h"
#include "molecule.h"
#include "bitstring.h"
#include "rdtree.h"

/*
** Register the chemicalite module with database handle db.
*/
int sqlite3_chemicalite_init(sqlite3 *db)
{
  int rc = SQLITE_OK;
  
  if (rc == SQLITE_OK) {
    rc = chemicalite_init_molecule(db);
  }
  
  if (rc == SQLITE_OK) {
    rc = chemicalite_init_bitstring(db);
  }
  
  if (rc == SQLITE_OK) {
    rc = chemicalite_init_rdtree(db);
  }
  
  /* if (rc == SQLITE_OK) { */
  /*   rc = chemicalite_init_XYZ(db); */
  /* } */
  
  return rc;
}

int sqlite3_extension_init(sqlite3 *db, char **pzErrMsg,
			   const sqlite3_api_routines *pApi)
{
  SQLITE_EXTENSION_INIT2(pApi)
  return sqlite3_chemicalite_init(db);
}
