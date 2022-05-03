#ifndef _TEST_H_
#define _TEST_H_
#include <iostream>
#include <string>
#include <mysqlx/xdevapi.h>

void run_test () {
	const std::string HOST {"localhost"};
	const int PORT {33060};
	const std::string USER {"root"};
	const std::string PWD {"root"};

	mysqlx::Session *session {nullptr};
	mysqlx::Schema *db {nullptr};
	mysqlx::Collection *table {nullptr};
	mysqlx::DocResult *results {nullptr};

	session = new mysqlx::Session(HOST, PORT, USER, PWD);
	db = new mysqlx::Schema(session->getSchema("test_db"));
	table = new mysqlx::Collection(db->createCollection("test_table", true));
	//table = new mysqlx::Collection(db->getCollection("test_table",));
	//table->remove("true").execute();
	table->add(R"({"name": "test10", "date": "May, 03 2022"})").execute();
	results = new mysqlx::DocResult(table->find("name != ''").execute());

	mysqlx::DbDoc test = results->fetchOne();

	for (int i = 0; test; ++i, test = results->fetchOne()) {
		std::cout << "Title: " << test["name"] << std::endl << "Date: " << test["date"] << std::endl;
	}

	delete session;
	delete db;
	delete table;
	delete results;

	std::cout << "done!" << std::endl;

}
#endif