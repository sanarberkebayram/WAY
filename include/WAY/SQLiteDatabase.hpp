#pragma once

#include "WAY/IDatabase.hpp"
#include <string>
#include <vector>
#include "WAY/User.hpp"
#include <sqlite_orm/sqlite_orm.h>

namespace WAY {

    inline auto createStorage(const std::string& path) {
        return sqlite_orm::make_storage(
            path,
            sqlite_orm::make_table("users",
                sqlite_orm::make_column("id", &User::id, sqlite_orm::primary_key().autoincrement()),
                sqlite_orm::make_column("username", &User::username),
                sqlite_orm::make_column("password_hash", &User::password_hash),
                sqlite_orm::make_column("google_id", &User::google_id)
            )
        );
    }

    class SQLiteDatabase : public IDatabase {
    public:
        explicit SQLiteDatabase(const std::string& path);
        
        std::optional<User> getUserByUsername(const std::string& username) override;
        std::optional<User> getUserByGoogleId(const std::string& google_id) override;
        void addUser(const User& user) override;

    private:
        decltype(createStorage("")) storage;
    };
}
