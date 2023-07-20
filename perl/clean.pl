#!/usr/bin/perl

use strict;
use warnings;

my $command = "rm -f server";

print "Cleaning up the server executable...\n";

my $output = `$command 2>&1`;
my $exit_code = $? >> 8;

if ($exit_code == 0) {
    print "Successfully cleaned up!\n";
} else {
    print "Failed to clean up. Error message:\n$output\n";
}
