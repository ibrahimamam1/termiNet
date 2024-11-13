CREATE OR REPLACE FUNCTION login_check(email TEXT, p_pass TEXT)
RETURNS BOOLEAN AS $$
DECLARE
    p_hash TEXT;
    u_id INTEGER;
BEGIN
    SELECT user_id INTO u_id FROM users WHERE user_email = email;

    -- Check if the user exists
    IF u_id IS NULL THEN
        RETURN FALSE;
    END IF;

    SELECT password_hash INTO p_hash FROM auth WHERE user_id = u_id;

    -- Compare the input password with the stored hash
    IF crypt(p_pass, p_hash) = p_hash THEN
        RETURN TRUE;
    ELSE
        RETURN FALSE;
    END IF;
END;
$$ LANGUAGE plpgsql;

