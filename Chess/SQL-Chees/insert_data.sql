INSERT INTO player(nick, pas_hash)  VALUES('player_1', 'Hf4DoCFm7');
INSERT INTO player (nick, pas_hash) VALUES('player_2', 'Hf4DoCm7');
INSERT INTO player (nick, pas_hash) VALUES('Johny75', '12345');
INSERT INTO player (nick, pas_hash) VALUES('Nick', '12345');
INSERT INTO piece (name) VALUES --по одному разу 
				  ('White rook'), --1
				  ('White knight'), --2
				  ('White bishop'), --3
				  ('White king'), --4
				  ('White queen'), --5
				  ('White pawn'), --6
				  ('Black rook'), --7
				  ('Black knight'), --8
				  ('Black bishop'), --9
				  ('Black queen'), --10
				  ('Black king'), --11
				  ('Black pawn'); --12
INSERT INTO piece_turn (piece, "a-h", "1_8", "move", "chop") VALUES
				--пешки 1-4 
				(6, 0, 1, FALSE, TRUE),
				(6, 0, 2, TRUE, TRUE),
				(12, 0, -1, FALSE, TRUE),
				(12, 0, -2, TRUE, TRUE),
				--рубят 4-8
				(6, 1, 1, TRUE, TRUE),
				(6, -1, 1, TRUE, TRUE),
				(12, 1, -1, TRUE, TRUE),
				(12, -1, -1, TRUE, TRUE),
				--ладья 9-71
				(1, 1,0, FALSE, FALSE),
				(1, 2, 0, FALSE, FALSE),
				(1, 3, 0, FALSE,FALSE),
				(1, 4, 0, FALSE, FALSE),
				(1, 5, 0, FALSE, FALSE),
				(1, 6, 0, FALSE, FALSE),
				(1, 7, 0, FALSE, FALSE),
				(1, 8, 0, FALSE, FALSE),
				
				(1, 0,1, FALSE, FALSE),
				(1, 0, 2, FALSE, FALSE),
				(1, 0, 3, FALSE,FALSE),
				(1, 0, 4, FALSE, FALSE),
				(1, 0, 5, FALSE, FALSE),
				(1, 0, 6, FALSE, FALSE),
				(1, 0, 7, FALSE, FALSE),
				(1, 0, 8, FALSE, FALSE),
					
				(7, 1,0, FALSE, FALSE),
				(7, 2, 0, FALSE, FALSE),
				(7, 3, 0, FALSE,FALSE),
				(7, 4, 0, FALSE, FALSE),
				(7, 5, 0, FALSE, FALSE),
				(7, 6, 0, FALSE, FALSE),
				(7, 7, 0, FALSE, FALSE),
				(7, 8, 0, FALSE, FALSE),
				
				(7, 0,1, FALSE, FALSE),
				(7, 0, 2, FALSE, FALSE),
				(7, 0, 3, FALSE,FALSE),
				(7, 0, 4, FALSE, FALSE),
				(7, 0, 5, FALSE, FALSE),
				(7, 0, 6, FALSE, FALSE),
				(7, 0, 7, FALSE, FALSE),
				(7, 0, 8, FALSE, FALSE),
				
				(1, -1,0, FALSE, FALSE),
				(1, -2, 0, FALSE, FALSE),
				(1, -3, 0, FALSE,FALSE),
				(1, -4, 0, FALSE, FALSE),
				(1, -5, 0, FALSE, FALSE),
				(1, -6, 0, FALSE, FALSE),
				(1, -7, 0, FALSE, FALSE),
				(1, -8, 0, FALSE, FALSE),
				
				(1, 0, -1, FALSE, FALSE),
				(1, 0, -2, FALSE, FALSE),
				(1, 0, -3, FALSE,FALSE),
				(1, 0, -4, FALSE, FALSE),
				(1, 0, -5, FALSE, FALSE),
				(1, 0, -6, FALSE, FALSE),
				(1, 0, -7, FALSE, FALSE),
				(1, 0, -8, FALSE, FALSE),
					
				(7, -1, 0, FALSE, FALSE),
				(7, -2, 0, FALSE, FALSE),
				(7, -3, 0, FALSE, FALSE),
				(7, -4, 0, FALSE, FALSE),
				(7, -5, 0, FALSE, FALSE),
				(7, -6, 0, FALSE, FALSE),
				(7, -7, 0, FALSE, FALSE),
				(7, -8, 0, FALSE, FALSE),
				
				(7, 0, -1, FALSE, FALSE),
				(7, 0, -2, FALSE, FALSE),
				(7, 0, -3, FALSE, FALSE),
				(7, 0, -4, FALSE, FALSE),
				(7, 0, -5, FALSE, FALSE),
				(7, 0, -6, FALSE, FALSE),
				(7, 0, -7, FALSE, FALSE),
				(7, 0, -8, FALSE, FALSE),
				--слон-кун 73-136
				(3, 1, 1, FALSE, FALSE),
				(3, 2, 2, FALSE, FALSE),
				(3, 3, 3, FALSE, FALSE),
				(3, 4, 4, FALSE, FALSE),
				(3, 5, 5, FALSE, FALSE),
				(3, 6, 6, FALSE, FALSE),
				(3, 7, 7, FALSE, FALSE),
				(3, 8, 8, FALSE, FALSE),
				
				(3, 1, -1, FALSE, FALSE),
				(3, 2, -2, FALSE, FALSE),
				(3, 3, -3, FALSE, FALSE),
				(3, 4, -4, FALSE, FALSE),
				(3, 5, -5, FALSE, FALSE),
				(3, 6, -6, FALSE, FALSE),
				(3, 7, -7, FALSE, FALSE),
				(3, 8, -8, FALSE, FALSE),	
					
				(3, -1, 1, FALSE, FALSE),
				(3, -2, 2, FALSE, FALSE),
				(3, -3, 3, FALSE, FALSE),
				(3, -4, 4, FALSE, FALSE),
				(3, -5, 5, FALSE, FALSE),
				(3, -6, 6, FALSE, FALSE),
				(3, -7, 7, FALSE, FALSE),
				(3, -8, 8, FALSE, FALSE),
				
				(3, -1, -1, FALSE, FALSE),
				(3, -2, -2, FALSE, FALSE),
				(3, -3, -3, FALSE, FALSE),
				(3, -4, -4, FALSE, FALSE),
				(3, -5, -5, FALSE, FALSE),
				(3, -6, -6, FALSE, FALSE),
				(3, -7, -7, FALSE, FALSE),
				(3, -8, -8, FALSE, FALSE),	
					
				(9, 1, 1, FALSE, FALSE),
				(9, 2, 2, FALSE, FALSE),
				(9, 3, 3, FALSE, FALSE),
				(9, 4, 4, FALSE, FALSE),
				(9, 5, 5, FALSE, FALSE),
				(9, 6, 6, FALSE, FALSE),
				(9, 7, 7, FALSE, FALSE),
				(9, 8, 8, FALSE, FALSE),
				
				(9, 1, -1, FALSE, FALSE),
				(9, 2, -2, FALSE, FALSE),
				(9, 3, -3, FALSE, FALSE),
				(9, 4, -4, FALSE, FALSE),
				(9, 5, -5, FALSE, FALSE),
				(9, 6, -6, FALSE, FALSE),
				(9, 7, -7, FALSE, FALSE),
				(9, 8, -8, FALSE, FALSE),	
					
				(9, -1, 1, FALSE, FALSE),
				(9, -2, 2, FALSE, FALSE),
				(9, -3, 3, FALSE,FALSE),
				(9, -4, 4, FALSE, FALSE),
				(9, -5, 5, FALSE, FALSE),
				(9, -6, 6, FALSE, FALSE),
				(9, -7, 7, FALSE, FALSE),
				(9, -8, 8, FALSE, FALSE),
				
				(9, -1, -1, FALSE, FALSE),
				(9, -2, -2, FALSE, FALSE),
				(9, -3, -3, FALSE,FALSE),
				(9, -4, -4, FALSE, FALSE),
				(9, -5, -5, FALSE, FALSE),
				(9, -6, -6, FALSE, FALSE),
				(9, -7, -7, FALSE, FALSE),
				(7, 8, -8, FALSE, FALSE)
;
					   
INSERT INTO games (player_1, player_2, complete, start_time) VALUES (1,2,FALSE, '2011-05-16 15:36:38'); --'dd-mm-yyyy hh24:mi:ss'
INSERT INTO games (player_1, player_2, complete, start_time) VALUES (1,2,FALSE, NOW()); 
INSERT INTO message (id_game, id_player, time, text) VALUES (1,1,'2011-05-16 15:37:45', 'Hello, world');

--INSERT INTO piece_turn (piece, "a-h", "1_8", ff) VALUES (1,0,2,FALSE);
--INSERT INTO piece_turn (piece, "a-h", "1_8", ff) VALUES (2,0,1,TRUE);

--INSERT INTO game_turn (id_game, id_turn, time) VALUES (1,2,'2011-05-16 15:36:45');
--INSERT INTO "state" VALUES (1,1,1,1,TRUE);
