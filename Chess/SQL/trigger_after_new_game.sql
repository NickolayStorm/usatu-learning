CREATE OR REPLACE FUNCTION after_insert_new_game() RETURNS TRIGGER
AS $$
BEGIN
		EXECUTE create_new_field(NEW.id);
	RETURN NEW;
END;
$$ LANGUAGE plpgsql;

CREATE TRIGGER after_new_game AFTER 
		INSERT
ON games FOR EACH ROW
EXECUTE PROCEDURE after_insert_new_game();
