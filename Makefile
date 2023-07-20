# Variables
PERL = perl

# Targets
all: server

server:
	$(PERL) perl/compile.pl

stop:
	$(PERL) perl/stop_server.pl

clean:
	$(PERL) perl/clean.pl
