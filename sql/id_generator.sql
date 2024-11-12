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
OWNED BY users.user_id;
