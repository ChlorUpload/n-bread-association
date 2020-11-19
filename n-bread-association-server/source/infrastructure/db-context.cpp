#include "db-context.h"

#include "category.h"
#include "product.h"
#include "user.h"

#include <iomanip>
#include <sstream>

namespace
{
std::tm str_to_time(std::string const& time)
{
    std::tm            t;
    std::istringstream ss(time);
    ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");
    return t;
}

std::string time_to_str(std::tm const& time)
{
    std::string        str;
    std::ostringstream ss;
    ss << std::put_time(&time, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
}

/* get */

template <>
Iterator<Category> DbContext::get<Category>()
{
    std::unique_ptr<sql::Statement> stmt { _con->createStatement() };
    return Iterator<Category> { stmt->executeQuery(
        "SELECT * FROM `categories`") };
}

template <>
Iterator<CategoryProductMap> DbContext::get<CategoryProductMap>()
{
    std::unique_ptr<sql::Statement> stmt { _con->createStatement() };
    return Iterator<CategoryProductMap> { stmt->executeQuery(
        "SELECT * FROM `categoryproducts`") };
}

template <>
Iterator<Product> DbContext::get<Product>()
{
    std::unique_ptr<sql::Statement> stmt { _con->createStatement() };
    return Iterator<Product> { stmt->executeQuery("SELECT * FROM `products`") };
}

template <>
Iterator<MemberProductMap> DbContext::get<MemberProductMap>()
{
    std::unique_ptr<sql::Statement> stmt { _con->createStatement() };
    return Iterator<MemberProductMap> { stmt->executeQuery(
        "SELECT * FROM `memberproducts`") };
}

template <>
Iterator<User> DbContext::get<User>()
{
    std::unique_ptr<sql::Statement> stmt { _con->createStatement() };
    return Iterator<User> { stmt->executeQuery("SELECT * FROM `users`") };
}

/* read */

template <>
std::vector<Category> const& DbContext::read<Category>()
{
    return _categories;
}

template <>
std::vector<CategoryProductMap> const& DbContext::read<CategoryProductMap>()
{
    return _cp_map;
}

template <>
std::vector<Product> const& DbContext::read<Product>()
{
    return _products;
}

template <>
std::vector<MemberProductMap> const& DbContext::read<MemberProductMap>()
{
    return _mp_map;
}

template <>
std::vector<User> const& DbContext::read<User>()
{
    return _users;
}

/* create */

template <>
bool DbContext::create<Category>(Category const& model)
{
    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "INSERT INTO `nba`.`categories` (`name`) VALUES (?)") };

    pre_stmt->setString(1, model.name.c_str());

    pre_stmt->executeUpdate();

    Category c = model;
    c.id       = get_last_id();
    if (c.id == -1) return false;

    _categories.push_back(c);
    return true;
}

template <>
bool DbContext::create<CategoryProductMap>(CategoryProductMap const& model)
{
    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "INSERT INTO `nba`.`categoryproducts` (`category_id`, `product_id`) "
        "VALUES (?, ?)") };

    pre_stmt->setInt(1, model.category_id);
    pre_stmt->setInt(2, model.product_id);

    pre_stmt->executeUpdate();

    CategoryProductMap cpm = model;
    cpm.id                 = get_last_id();
    if (cpm.id == -1) return false;

    _cp_map.push_back(cpm);
    return true;
}

template <>
bool DbContext::create<Product>(Product const& model)
{
    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "INSERT INTO `nba`.`products` (`title`, `host_id`, `price`, "
        "`quantity`, `announce`, `url`, `chat_url`, `deliver`, `created_at`, "
        "`expires_at`) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)") };

    pre_stmt->setString(1, model.title);
    pre_stmt->setInt(2, model.host_id);
    pre_stmt->setInt(3, model.price);
    pre_stmt->setInt(4, model.quantity);
    pre_stmt->setString(5, model.announce.c_str());
    pre_stmt->setString(6, model.url.c_str());
    pre_stmt->setString(7, model.chat_url.c_str());
    pre_stmt->setInt(8, static_cast<int>(model.deliver));
    pre_stmt->setString(9, time_to_str(model.created_at));
    pre_stmt->setString(10, time_to_str(model.expires_at));

    Product p = model;
    p.id      = get_last_id();
    if (p.id == -1) return false;

    _products.push_back(p);
    return true;
}

template <>
bool DbContext::create<MemberProductMap>(MemberProductMap const& model)
{
    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "INSERT INTO `nba`.`memberproducts` (`member_id`, `product_id`, "
        "`quantity`) VALUES (?, ?, ?)") };

    pre_stmt->setInt(1, model.member_id);
    pre_stmt->setInt(2, model.product_id);
    pre_stmt->setInt(3, model.quantity);

    pre_stmt->executeUpdate();

    MemberProductMap mpm = model;
    mpm.id               = get_last_id();
    if (mpm.id == -1) return false;

    _mp_map.push_back(mpm);
    return true;
}

template <>
bool DbContext::create<User>(User const& model)
{
    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "INSERT INTO `nba`.`users` (`name`, `email`, `password`, "
        "`phone`, `verified`) VALUES (?, ?, ?, ?, '0')") };

    pre_stmt->setString(1, model.name.c_str());
    pre_stmt->setString(2, model.email.c_str());
    pre_stmt->setString(3, model.encrypted_pw.c_str());
    pre_stmt->setString(4, model.phone.c_str());

    pre_stmt->executeUpdate();

    User u = model;
    u.id   = get_last_id();
    if (u.id == -1) return false;

    _users.push_back(u);
    return true;
}

/* update */

template <>
bool DbContext::update<Category>(Category const& model)
{
    auto it = std::find_if(_categories.begin(),
                           _categories.end(),
                           [&](Category const& c) { return c.id == model.id; });
    if (it == _categories.end()) return false;
    *it = model;

    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "UPDATE `nba`.`categories` SET `name` = ? WHERE (`id` = ?)") };

    pre_stmt->setString(1, model.name.c_str());

    pre_stmt->setInt(2, model.id);

    pre_stmt->executeUpdate();
    return true;
}

template <>
bool DbContext::update<CategoryProductMap>(CategoryProductMap const& model)
{
    auto it = std::find_if(
        _cp_map.begin(), _cp_map.end(), [&](CategoryProductMap const& cpm) {
            return cpm.id == model.id;
        });
    if (it == _cp_map.end()) return false;
    *it = model;

    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "UPDATE `nba`.`categoryproducts` SET `category_id` = ?, `product_id` = "
        "? WHERE "
        "(`id` = ?)") };

    pre_stmt->setInt(1, model.category_id);
    pre_stmt->setInt(2, model.product_id);

    pre_stmt->setInt(3, model.id);

    pre_stmt->executeUpdate();
    return true;
}

template <>
bool DbContext::update<Product>(Product const& model)
{
    auto it = std::find_if(_products.begin(),
                           _products.end(),
                           [&](Product const& p) { return p.id == model.id; });
    if (it == _products.end()) return false;
    *it = model;

    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "UPDATE `nba`.`products` SET `title` = ?, `host_id` = ?, "
        "`price` = ?, `quantity` = ?, `announce` = ?, `url` = ?, `chat_url` = "
        "?, `deliver` = ?, `created_at` = ?, `expires_at` = ? WHERE (`id` = "
        "?)") };

    pre_stmt->setString(1, model.title.c_str());
    pre_stmt->setInt(2, model.host_id);
    pre_stmt->setInt(3, model.price);
    pre_stmt->setInt(4, model.quantity);
    pre_stmt->setString(5, model.announce.c_str());
    pre_stmt->setString(6, model.url.c_str());
    pre_stmt->setString(7, model.chat_url.c_str());
    pre_stmt->setInt(8, static_cast<int>(model.deliver));
    pre_stmt->setString(9, time_to_str(model.created_at));
    pre_stmt->setString(10, time_to_str(model.expires_at));

    pre_stmt->setInt(11, model.id);

    pre_stmt->executeUpdate();
    return true;
}

template <>
bool DbContext::update<MemberProductMap>(MemberProductMap const& model)
{
    auto it = std::find_if(
        _mp_map.begin(), _mp_map.end(), [&](MemberProductMap const& mpm) {
            return mpm.id == model.id;
        });
    if (it == _mp_map.end()) return false;
    *it = model;

    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "UPDATE `nba`.`memberproducts` SET `member_id` = ?, `product_id` = ?, "
        "`quantity` = ? WHERE (`id` = ?)") };

    pre_stmt->setInt(1, model.member_id);
    pre_stmt->setInt(2, model.product_id);
    pre_stmt->setInt(3, model.quantity);

    pre_stmt->setInt(4, model.id);

    pre_stmt->executeUpdate();
    return true;
}

template <>
bool DbContext::update<User>(User const& model)
{
    auto it = std::find_if(_users.begin(), _users.end(), [&](User const& u) {
        return u.id == model.id;
    });
    if (it == _users.end()) return false;
    *it = model;

    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "UPDATE `nba`.`users` SET `name` = ?, `email` = ?, `password` = ?, "
        "`phone` = ?, `verified` = ? WHERE (`id` = ?)") };

    pre_stmt->setString(1, model.name.c_str());
    pre_stmt->setString(2, model.email.c_str());
    pre_stmt->setString(3, model.encrypted_pw.c_str());
    pre_stmt->setString(4, model.phone.c_str());
    pre_stmt->setBoolean(5, model.verified);

    pre_stmt->setInt(6, model.id);

    pre_stmt->executeUpdate();
    return true;
}

/* get value */

template <>
void Iterator<Category>::get_value()
{
    Category c;
    c.id   = _result->getInt("id");
    c.name = _result->getString("name");

    _val = c;
}

template <>
void Iterator<CategoryProductMap>::get_value()
{
    CategoryProductMap cpm;
    cpm.category_id = _result->getInt("category_id");
    cpm.product_id  = _result->getInt("product_id");

    _val = cpm;
}

template <>
void Iterator<Product>::get_value()
{
    Product p;
    p.id         = _result->getInt("id");
    p.host_id    = _result->getInt("host_id");
    p.price      = _result->getInt("price");
    p.quantity   = _result->getInt("quantity");
    p.announce   = _result->getString("announce");
    p.url        = _result->getString("url");
    p.chat_url   = _result->getString("chat_url");
    p.deliver    = static_cast<Deliver>(_result->getInt("deliver"));
    p.created_at = str_to_time(_result->getString("created_at"));
    p.expires_at = str_to_time(_result->getString("expires_at"));
    _val         = p;
}

template <>
void Iterator<MemberProductMap>::get_value()
{
    MemberProductMap mpm;
    mpm.product_id = _result->getInt("product_id");
    mpm.member_id  = _result->getInt("member_id");
    mpm.quantity   = _result->getInt("quantity");

    _val = mpm;
}

template <>
void Iterator<User>::get_value()
{
    User u;
    u.id           = _result->getInt("id");
    u.name         = _result->getString("name");
    u.email        = _result->getString("email");
    u.encrypted_pw = _result->getString("password");
    u.phone        = _result->getString("phone");
    u.verified     = _result->getBoolean("verified");

    _val = u;
}

/* remove */

template <>
bool DbContext::remove<Category>(int id)
{
    auto& it = std::find_if(_categories.begin(),
                            _categories.end(),
                            [&](Category& c) { return c.id == id; });
    if (it == _categories.end()) return false;
    _categories.erase(it);

    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "DELETE FROM `nba`.`categories` WHERE (`id` = ?)") };
    pre_stmt->setInt(1, id);
    pre_stmt->executeUpdate();

    return true;
}

template <>
bool DbContext::remove<CategoryProductMap>(int id)
{
    auto& it = std::find_if(_cp_map.begin(),
                            _cp_map.end(),
                            [&](CategoryProductMap& c) { return c.id == id; });
    if (it == _cp_map.end()) return false;
    _cp_map.erase(it);

    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "DELETE FROM `nba`.`categoryproducts` WHERE (`id` = ?)") };
    pre_stmt->setInt(1, id);
    pre_stmt->executeUpdate();

    return true;
}

template <>
bool DbContext::remove<Product>(int id)
{
    auto& it = std::find_if(_products.begin(),
                            _products.end(),
                            [&](Product& c) { return c.id == id; });
    if (it == _products.end()) return false;
    _products.erase(it);

    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "DELETE FROM `nba`.`products` WHERE (`id` = ?)") };
    pre_stmt->setInt(1, id);
    pre_stmt->executeUpdate();

    return true;
}

template <>
bool DbContext::remove<MemberProductMap>(int id)
{
    auto& it = std::find_if(_mp_map.begin(),
                            _mp_map.end(),
                            [&](MemberProductMap& c) { return c.id == id; });
    if (it == _mp_map.end()) return false;
    _mp_map.erase(it);

    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "DELETE FROM `nba`.`memberproducts` WHERE (`id` = ?)") };
    pre_stmt->setInt(1, id);
    pre_stmt->executeUpdate();

    return true;
}

template <>
bool DbContext::remove<User>(int id)
{
    auto& it = std::find_if(
        _users.begin(), _users.end(), [&](User& c) { return c.id == id; });
    if (it == _users.end()) return false;
    _users.erase(it);

    std::unique_ptr<sql::PreparedStatement> pre_stmt { _con->prepareStatement(
        "DELETE FROM `nba`.`users` WHERE (`id` = ?)") };
    pre_stmt->setInt(1, id);
    pre_stmt->executeUpdate();

    return true;
}

int DbContext::get_last_id()
{
    std::unique_ptr<sql::Statement> stmt { _con->createStatement() };
    std::unique_ptr<sql::ResultSet> res { stmt->executeQuery(
        "SELECT @@identity As id") };
    if (res->next()) { return res->getInt("id"); }
    else
    {
        return -1;
    }
}

/* constructor */

DbContext::DbContext() :
    _con { create_connection() },
    _categories(),
    _cp_map(),
    _products(),
    _mp_map(),
    _users()
{
    std::copy(get<Category>(),
              Iterator<Category> {},
              std::back_insert_iterator { _categories });
    std::copy(get<CategoryProductMap>(),
              Iterator<CategoryProductMap> {},
              std::back_insert_iterator { _cp_map });
    std::copy(get<Product>(),
              Iterator<Product> {},
              std::back_insert_iterator { _products });
    std::copy(get<MemberProductMap>(),
              Iterator<MemberProductMap> {},
              std::back_insert_iterator { _mp_map });
    std::copy(
        get<User>(), Iterator<User> {}, std::back_insert_iterator { _users });
}

sql::Driver* DbContext::_driver = nullptr;