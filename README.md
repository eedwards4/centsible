<h1>Centsible</h1>
Created by Ethan Edwards

A program for managing multiple banking/investment accounts within a (CURRENTLY NOT SECURE) desktop application.

<h2>Build instructions</h2>
This project utilizes cmake to build. To install cmake, go to https://cmake.org/download/ and follow the instructions.
In order to properly interface with a database, you will need to set up your own [mongoDB Atlas account](https://www.mongodb.com/atlas/database) and create the following database
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
</ul>

--------------------------------------------------------------------

Once you've created the database, create a file in the /mongo directory named "mongo_login.txt" and populate it with the following information in the following order:

<ul>
  <li>Atlas username</li>
  <li>Atlas password</li>
  <li><b>ONLY THIS PART OF THE ACCESS URL:</b> [@centsibleexample.i6gri7x.mongodb.net] : <i>Your url should look similar, but not identical to this one</i></li>
</ul>

<h2>Run instructions</h2>
Just run the program! Currently there are no runtime arguments so all you need to do is double-click.
