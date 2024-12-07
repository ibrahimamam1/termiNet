create sequence if not exists IDSEQ
As Integer
MINVALUE 0
No MAXVALUE
CACHE 20
OWNED BY users.user_id;

create sequence if not exists AUTHIDSEQ
As Integer
MINVALUE 0
No MAXVALUE
CACHE 20
OWNED BY auth.auth_id;

create sequence if not exists THREADSEQ
As Integer
MINVALUE 0
No MAXVALUE
CACHE 20
OWNED BY threads.thread_id;

-- create sequence if not exists CATEGORYSEQ
-- As Integer
-- MINVALUE 1
-- No MAXVALUE
-- CACHE 0
-- OWNED BY categories.category_id;

create sequence if not exists CommunitySeq
As Integer
MINVALUE 1
No MAXVALUE
OWNED BY communities.community_id;
