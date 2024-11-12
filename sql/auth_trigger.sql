CREATE OR REPLACE FUNCTION add_auth_entry(p_user_id INTEGER, p_password TEXT)
RETURNS VOID AS $$
DECLARE
    p_auth_id INTEGER;
    p_password_hash TEXT;
BEGIN
    -- Generate a unique auth_id

    p_auth_id := (EXTRACT(EPOCH FROM NOW())::bigint * 100000) + NEXTVAL('AUTHIDSEQ');

    -- Hash the password
    p_password_hash := crypt(p_password, gen_salt('bf', 10));

    -- Insert the new record into the auth table
    INSERT INTO auth (auth_id, user_id, password_hash)
    VALUES (p_auth_id, p_user_id, p_password_hash);
END;
$$ LANGUAGE plpgsql;

-- Create the trigger
CREATE OR REPLACE TRIGGER auth_trigger
BEFORE INSERT
ON users
FOR EACH ROW
EXECUTE PROCEDURE add_auth_entry(NEW.id, NEW.password);