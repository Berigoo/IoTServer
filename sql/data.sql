CREATE TABLE data(
    id INT AUTO_INCREMENT PRIMARY KEY,
    uuid VARCHAR(255) NOT NULL,
    value VARCHAR(1024),
    session VARCHAR(255),
    FOREIGN KEY (uuid) REFERENCES devices(uuid)
);