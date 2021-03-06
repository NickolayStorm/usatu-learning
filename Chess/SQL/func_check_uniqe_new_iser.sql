--DROP FUNCTION check_uniqe_new_player(CHAR(20));


CREATE OR REPLACE FUNCTION check_uniqe_new_player( newNick
						CHAR(20)
					) RETURNS BOOLEAN
	AS $$
DECLARE 
	_count int;
BEGIN
	SELECT COUNT(*)  INTO _count FROM player 
					WHERE 
						player.nick = newNick; 

	IF _count <> 0 THEN
		RETURN FALSE;
	ELSE
		RETURN TRUE;
	END IF;
END;
$$ LANGUAGE plpgsql;
--SELECT check_uniqe_new_player('x');
--'player_2', 'Hf4DoCFm7'
