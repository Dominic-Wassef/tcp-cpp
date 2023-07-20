#!/usr/bin/perl

use strict;
use warnings;

my $command = "g++ -Wall -g -o server src/main.cpp src/server.cpp src/request_handler.cpp src/message_service.cpp";

print "Compiling the server...\n";

my $output = `$command 2>&1`;
my $exit_code = $? >> 8;

if ($exit_code == 0) {
    print "Successfully compiled the server!\n";
} else {
    print "Failed to compile the server. Error message:\n$output\n";
}
