# !bin/bash
cat ./drop_tables.sql | psql LAB3
cat ./create.sql | psql LAB3 

cat ./func_check_uniqe_new_iser.sql | psql LAB3
cat ./func_return_id_by_name.sql | psql LAB3
cat ./function_for_create_field.sql | psql LAB3
cat ./trigger_after_new_game.sql | psql LAB3
cat ./func_check_collisions.sql | psql LAB3
cat ./func_is_can_move.sql | psql LAB3
cat ./func_move.sql | psql LAB3

cat ./insert_data.sql | psql LAB3



