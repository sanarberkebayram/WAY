#include "WAY/SQLiteDatabase.hpp"

namespace WAY {
    SQLiteDatabase::SQLiteDatabase(const std::string& path) : storage(createStorage(path)) {
        storage.sync_schema();
    }

    std::optional<User> SQLiteDatabase::getUserByUsername(const std::string& username) {
        auto users = storage.get_all<User>(sqlite_orm::where(sqlite_orm::c(&User::username) == username));
        if (users.empty()) {
            return std::nullopt;
        }
        return users.front();
    }

    std::optional<User> SQLiteDatabase::getUserByGoogleId(const std::string& google_id) {
        auto users = storage.get_all<User>(sqlite_orm::where(sqlite_orm::c(&User::google_id) == google_id));
        if (users.empty()) {
            return std::nullopt;
        }
        return users.front();
    }

    void SQLiteDatabase::addUser(const User& user) {
        storage.insert(user);
    }
}
