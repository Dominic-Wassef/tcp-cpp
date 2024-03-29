#!/usr/bin/perl
use strict;
use warnings;

print <<EOF;
<!DOCTYPE html>
<html>
  <head>
    <title>Homepage</title>
    <!-- Bootstrap CSS -->
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
    <h1>Welcome to the Homepage!</h1>
    <button
      onclick="location.href='/home'"
      type="button"
      class="btn btn-primary"
    >
      Go to the next page
    </button>
    <!-- Bootstrap JS and jQuery -->
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js"></script>
  </body>
</html>
EOF
