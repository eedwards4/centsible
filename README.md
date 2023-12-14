<h1>Centsible</h1>
Created by Ethan Edwards

A program for managing multiple banking/investment accounts within a (CURRENTLY NOT SECURE) desktop application.

<h2>Build instructions</h2>
This project utilizes cmake to build. To install cmake, go to <a href="https://cmake.org/download/">the cmake website</a> and follow the instructions.
In order to properly interface with a database, you will need to set up your own <a href="https://www.mongodb.com/atlas/database">mongoDB Atlas account</a> and create the following database
(This keeps your data private, so it's just a little bit important):

--------------------------------------------------------------------
<ul>
  <li><b>database name</b>: data</li>
  <li><b>collections:</b>
    <ul>
      <li>banks</li>
      <li>investments</li>
    </ul>
  </li>
  <li><b>database name</b>: chrono_data</li>
  <li>
    <b>collections:</b>
    <ul>
      <li>banks</li>
      <li>investments</li>
    </ul>
  </li>
</ul>

--------------------------------------------------------------------

Once you've created the database, create a file in the <a href="https://github.com/eedwards4/centsible/tree/main/mongo">/mongo</a> directory named "mongo_login.txt" and populate it with the following information in the following order:

<ul>
  <li>Atlas username</li>
  <li>Atlas password</li>
  <li><b>ONLY THIS PART OF THE ACCESS URL:</b> [@centsibleexample.i6gri7x.mongodb.net] : <i>Your url should look similar, but not identical to this one</i></li>
</ul>

This project uses <a href="https://www.qt.io/blog/qt-6.6.1-released">QT 6.6.1</a> for its GUI. QT has a few <b>very</b> annoying bugs.
If you are experiencing issues compiling, please refer to <a href="https://github.com/eedwards4/centsible/blob/main/bugfix.txt">this bugfix file</a> for more infomation on known issues.

<h2>Run instructions</h2>
Just run the program! Currently there are no runtime arguments so all you need to do is double-click.
