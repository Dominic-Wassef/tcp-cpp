#!/usr/bin/perl

use strict;
use warnings;

my $port = 8080;
my $pid = `lsof -t -i:$port`;

if ($pid) {
    print "Killing process $pid on port $port\n";
    kill 'TERM', $pid or die "Couldn't kill process $pid: $!\n";
}
else {
    print "No process listening on port $port\n";
}