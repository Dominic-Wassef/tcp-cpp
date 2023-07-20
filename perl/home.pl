#!/usr/bin/perl
use strict;
use warnings;

print <<EOF;
<!DOCTYPE html>
<html>
  <head>
    <title>Home</title>
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
    <h1>This is the Home Page</h1>
    <form action="/message" method="POST">
      <div class="form-group">
        <label for="user_message">Enter a message:</label><br />
        <input type="text" id="user_message" name="user_message" /><br />
        <input type="submit" value="Submit" class="btn btn-primary" />
      </div>
    </form>
    <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js"></script>
  </body>
</html>
EOF
