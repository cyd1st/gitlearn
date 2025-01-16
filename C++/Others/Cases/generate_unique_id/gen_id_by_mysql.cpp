// sudo apt-get update
// sudo apt-get install libmysqlclient-dev
// g++ gen_id_by_mysql.cpp -lmysqlclient
// need connect to a mysql database.
#include <iostream>
#include <mysql/mysql.h>

long long getAutoIncrementId(MYSQL *conn)
{
    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_query(conn, "SELECT LAST_INSERT_ID()");
    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);

    return std::stoll(row[0]);
}

int main()
{
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        std::cout << "mysql_init() failed" << std::endl;
        return EXIT_FAILURE;
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        std::cout << "Last inserted ID: " << getAutoIncrementId(conn) << std::endl;
    } else {
        std::cerr << "Connection failed: " << mysql_error(conn) << std::endl;
        // std::cerr << "Connection failed!" << std::endl;
    }

    mysql_close(conn);
    return 0;
}