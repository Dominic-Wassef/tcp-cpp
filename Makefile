# Variables
PERL = perl

# Targets
all: server

server:
	$(PERL) src/perl/compile.pl

stop:
	$(PERL) src/perl/stop_server.pl

clean:
	$(PERL) src/perl/clean.pl
