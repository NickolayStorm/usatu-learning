#! /bin/bash

echo 'Drop tables... (drop_tables.sql)' && \
cat ./drop_tables.sql | sudo su - postgres -c "psql users -U labuser" && \
echo 'Create tables... (create_tables.sql)' && \
cat ./create_tables.sql | sudo su - postgres -c "psql users -U labuser" && \
echo 'Insert default data (insert.sql)' && \
cat ./insert.sql | sudo su - postgres -c "psql users -U labuser"
exit 0
