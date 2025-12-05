CREATE TABLE userPluginGroup (
	id INTEGER DEFAULT (0) PRIMARY KEY AUTOINCREMENT,
	name TEXT(100) NOT NULL,
	create_time REAL NOT NULL,
	modify_time REAL NOT NULL
);
CREATE TABLE userPlugin (
	id INTEGER DEFAULT (0) NOT NULL PRIMARY KEY AUTOINCREMENT,
	group_id INTEGER NOT NULL,
	name TEXT(100) NOT NULL,
	note TEXT(500),
	"type" INTEGER DEFAULT (0) NOT NULL,
	"path" TEXT(200) NOT NULL,
	thumb BLOB,
	create_time REAL NOT NULL,
	modify_time REAL NOT NULL,
	CONSTRAINT userPlugin_FK FOREIGN KEY (group_id) REFERENCES userPluginGroup(id)
);
CREATE TABLE dataDir (
	id INTEGER DEFAULT (0) NOT NULL PRIMARY KEY AUTOINCREMENT,
	parent_id INTEGER DEFAULT (0) NOT NULL,
	group_id INTEGER NOT NULL,
	name TEXT NOT NULL,
	value BLOB,
	property BLOB,
	create_time REAL, 
    modify_time REAL
);
CREATE TABLE dataSource (
	id INTEGER DEFAULT (0) NOT NULL PRIMARY KEY AUTOINCREMENT,
	data_dir_id INTEGER NOT NULL,
	source_plugin_id TEXT NOT NULL,
	source_args TEXT NOT NULL,
	create_time REAL, 
    modify_time REAL,
	CONSTRAINT dataSource_dataDir_FK FOREIGN KEY (data_dir_id) REFERENCES dataDir(id)
);
CREATE TABLE dataMarket (
	id INTEGER DEFAULT (0) NOT NULL PRIMARY KEY AUTOINCREMENT,
	data_source_id INTEGER NOT NULL,
	data_name TEXT NOT NULL,
	request_method TEXT,
	request_args TEXT,
	request_period INTEGER,
	process_code TEXT,	
	create_time REAL, 
    modify_time REAL,
	CONSTRAINT dataMarket_dataSource_FK FOREIGN KEY (data_source_id) REFERENCES dataSource(id)
);
