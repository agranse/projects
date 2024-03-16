create table users (
    userID int not null auto_increment primary key,
    username varchar(255) not null,
    pass varchar(60) not null
);

create table posts (
    postID int not null auto_increment primary key,
    postMessage text not null,
    postLikeCount int not null default 0,
    userID int not null,
    FOREIGN KEY (userID) REFERENCES users(userID)
);

