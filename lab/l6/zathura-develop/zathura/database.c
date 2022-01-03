/* SPDX-License-Identifier: Zlib */

#include "database.h"

G_DEFINE_INTERFACE(ZathuraDatabase, zathura_database, G_TYPE_OBJECT)

static void
zathura_database_default_init(ZathuraDatabaseInterface* GIRARA_UNUSED(iface))
{
}

bool
zathura_db_add_bookmark(zathura_database_t* db, const char* file,
                        zathura_bookmark_t* bookmark)
{
  g_return_val_if_fail(ZATHURA_IS_DATABASE(db) && file != NULL && bookmark != NULL, false);

  return ZATHURA_DATABASE_GET_INTERFACE(db)->add_bookmark(db, file, bookmark);
}

bool
zathura_db_remove_bookmark(zathura_database_t* db, const char* file, const char*
                           id)
{
  g_return_val_if_fail(ZATHURA_IS_DATABASE(db) && file != NULL && id != NULL, false);

  return ZATHURA_DATABASE_GET_INTERFACE(db)->remove_bookmark(db, file, id);
}

girara_list_t*
zathura_db_load_bookmarks(zathura_database_t* db, const char* file)
{
  g_return_val_if_fail(ZATHURA_IS_DATABASE(db) && file != NULL, NULL);

  return ZATHURA_DATABASE_GET_INTERFACE(db)->load_bookmarks(db, file);
}

girara_list_t*
zathura_db_load_jumplist(zathura_database_t* db, const char* file)
{
  g_return_val_if_fail(ZATHURA_IS_DATABASE(db) && file != NULL, NULL);

  return ZATHURA_DATABASE_GET_INTERFACE(db)->load_jumplist(db, file);
}

bool
zathura_db_save_jumplist(zathura_database_t* db, const char* file, girara_list_t* jumplist)
{
  g_return_val_if_fail(ZATHURA_IS_DATABASE(db) && file != NULL && jumplist != NULL, NULL);

  return ZATHURA_DATABASE_GET_INTERFACE(db)->save_jumplist(db, file, jumplist);
}

bool
zathura_db_set_fileinfo(zathura_database_t* db, const char* file, const uint8_t* hash_sha256,
                        zathura_fileinfo_t* file_info)
{
  g_return_val_if_fail(ZATHURA_IS_DATABASE(db) && file != NULL && hash_sha256 != NULL && file_info != NULL, false);

  return ZATHURA_DATABASE_GET_INTERFACE(db)->set_fileinfo(db, file, hash_sha256, file_info);
}

bool
zathura_db_get_fileinfo(zathura_database_t* db, const char* file, const uint8_t* hash_sha256,
                        zathura_fileinfo_t* file_info)
{
  g_return_val_if_fail(ZATHURA_IS_DATABASE(db) && file != NULL && hash_sha256 != NULL && file_info != NULL, false);

  return ZATHURA_DATABASE_GET_INTERFACE(db)->get_fileinfo(db, file, hash_sha256, file_info);
}

girara_list_t*
zathura_db_get_recent_files(zathura_database_t* db, int max, const char* basepath)
{
  g_return_val_if_fail(ZATHURA_IS_DATABASE(db), NULL);

  return ZATHURA_DATABASE_GET_INTERFACE(db)->get_recent_files(db, max, basepath);
}

static int
bookmarks_compare(const void* l, const void* r)
{
  const zathura_bookmark_t* lhs = l;
  const zathura_bookmark_t* rhs = r;

  return zathura_bookmarks_compare(lhs, rhs);
}

static void
bookmarks_free(void* p)
{
  zathura_bookmark_t* bookmark = p;
  zathura_bookmark_free(bookmark);
}

girara_list_t* bookmarks_list_new(void)
{
  return girara_sorted_list_new2(bookmarks_compare, bookmarks_free);
}
