#! /bin/bash
echo 'Start PostgreSQL server:'
echo 'Needs root prenission!'
sudo systemctl start postgresql && \
cd ./WebApp/Database && \
echo 'Init Database (Database/init.sh):' && \
sleep 1 && \
./init.sh && \
echo 'Build application (Go build)' && \
cd ../ && \
sleep 1 && \
go build *.go && \
echo 'Start server... ' && \
#привет, костыль
mv ./database server && \
sleep 1 && \
./server #& \
#sleep 3 && \
#echo 'Open Firefox page: localhost:3000' && \
#firefox localhost:3000


