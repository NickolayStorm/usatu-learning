-- DROP FUNCTION get_id_by_name(CHAR(20), CHAR(20));


CREATE OR REPLACE FUNCTION get_id_by_name( indentyNick
						CHAR(20), pass CHAR(20)
					) RETURNS INT 
	AS $$
DECLARE 
	_id int;
	_count int;
BEGIN
	SELECT COUNT(*), id INTO _count, _id FROM player 
					WHERE 
						player.nick = indentyNick AND player.pas_hash = pass
			GROUP BY id ; 

	IF _count <> 1 THEN
		RETURN 0;
	ELSE
		RETURN _id;
	END IF;
END;
$$ LANGUAGE plpgsql;
--'player_2', 'Hf4DoCFm7'
