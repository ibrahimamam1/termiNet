create table if not exists iconsBucket(
    icon_id serial primary key,
    filename text not null,
    filedata BYTEA not null,
    uploaded_by integer references users(user_id),
    uploaded_at timestamp default current_timestamp
);

create table if not exists bannersBucket(
    icon_id serial primary key,
    filename text not null,
    filedata BYTEA not null,
    uploaded_by integer references users(user_id),
    uploaded_at timestamp default current_timestamp
);
