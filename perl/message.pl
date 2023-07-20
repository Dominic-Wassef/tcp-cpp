#!/usr/bin/perl
use strict;
use warnings;
use CGI;

my $cgi = new CGI;
my $user_message = $cgi->param('user_message');

print <<EOF;
<!DOCTYPE html>
<html>
  <head>
    <title>Message</title>
    <link
      rel="stylesheet"
      href="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css"
    />
  </head>
  <body>
    <nav class="navbar navbar-expand-lg navbar-light bg-light">
      <a class="navbar-brand" href="/">Homepage</a>
      <div class="collapse navbar-collapse">
        <ul class="navbar-nav">
          <li class="nav-item">
            <a class="nav-link" href="/home">Home</a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="/message">Message</a>
          </li>
        </ul>
      </div>
    </nav>
    <h1>Your message has been received!</h1>
    <p>This is your message: $user_message</p>
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js"></script>
  </body>
</html>
EOF
