create table if not exists auth(
    auth_id integer primary key,
    user_id integer ,
    password_hash text
);

create table if not exists users(
    user_id integer primary key,
    user_name text,
    user_email text,
    user_sex text,
    user_dob date,
    user_bio text,
    passwd text,
    created_at date,
);

create table if not exists communities(
community_id integer primary key,
name varchar(50) not null,
description text,
icon_image text,
banner_image text,
created_at date
);

create table if not exists users_communities(
    user_id integer,
    community_id integer,
    primary key(user_id, community_id)
);

create table if not exists threads(
    thread_id integer primary key,
    title varchar(200) not null,
    content text,
    created_at date,
    author_id integer not null,
    community_id integer,
    parent_thread_id integer,
);




create table if not exists categories(
    category_id integer primary key,
    category_name text
);
insert into categories(category_id, category_name) values (1, 'Art');
insert into categories(category_id, category_name) values (2, 'Science');
insert into categories(category_id, category_name) values (3, 'Sports');
insert into categories(category_id, category_name) values (4, 'Politics');
insert into categories(category_id, category_name) values (5, 'News');
insert into categories(category_id, category_name) values (6, 'Entertainment');
insert into categories(category_id, category_name) values (7, 'Technology');
insert into categories(category_id, category_name) values (8, 'Writing');
insert into categories(category_id, category_name) values (9, 'Pop culture');
insert into categories(category_id, category_name) values (10, 'Writing');
insert into categories(category_id, category_name) values (11, 'Popular Culture');
insert into categories(category_id, category_name) values (12, 'Anime');
insert into categories(category_id, category_name) values (13, 'Manga');
insert into categories(category_id, category_name) values (14, 'Video Games');
insert into categories(category_id, category_name) values (15, 'Movies');

create table if not exists community_categories(
    community_id integer,
    category_id integer,
    primary key (community_id, category_id)
);



