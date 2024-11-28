CREATE EXTENSION IF NOT EXISTS pgcrypto;


CREATE OR REPLACE FUNCTION add_auth_entry()
RETURNS TRIGGER AS $$
DECLARE
    p_auth_id BIGINT;
    sn BIGINT;
    p_password_hash TEXT;
BEGIN
    -- Generate a unique auth_id
    SELECT (EXTRACT(EPOCH FROM NOW())::bigint) INTO sn;
    p_auth_id := sn + (SELECT NEXTVAL('AUTHIDSEQ'));

    -- Hash the password from the NEW record
    p_password_hash := crypt(NEW.passwd, gen_salt('bf'));

    -- Insert the new record into the auth table
    INSERT INTO auth (auth_id, user_id, password_hash)
    VALUES (p_auth_id, NEW.user_id, p_password_hash);

    NEW.passwd := ' ';
    RETURN NEW;
END;
$$ LANGUAGE plpgsql;


-- Create the trigger
CREATE OR REPLACE TRIGGER auth_trigger
BEFORE INSERT ON users
FOR EACH ROW
EXECUTE FUNCTION add_auth_entry();
