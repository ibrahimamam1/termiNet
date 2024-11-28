create table if not exists users(
    user_id integer primary key,
    user_name text,
    user_email text,
    user_sex text,
    user_dob date,
    user_bio text,
    passwd text,
    created_at date
);

create table if not exists threads(
    thread_id integer primary key,
    title varchar(200) not null,
    content text,
    created_at date,
    author_id integer not null,
    community_id integer,
    parent_thread_id integer
);

create table if not exists communities(
community_id integer primary key,
name varchar(50) not null,
description text,
created_at date
);

create table if not exists auth(
    auth_id integer primary key,
    user_id integer ,
    password_hash text
);


