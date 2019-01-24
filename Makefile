.PHONY:all
all:server client
.PHONY:server 
server:server.cc
	g++ $^ -g -o $@ -lpthread 
.PHONY:client
client:client.cc 
	g++ $^ -g -o $@ -lpthread 

.PHONY:clean
clean:
	rm server client
