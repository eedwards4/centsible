<h1>Centsible</h1>
Created by Ethan Edwards

A program for managing multiple banking/investment accounts within a (CURRENTLY NOT SECURE) desktop application.

<h2>CURRENT FEATURES/ROADMAP</h2>
Currently you can:
<ul>
  <li>Add/remove bank + investment accounts</li>
  <li>View some historical data on your accounts (if you put it into the database yourself)</li>
</ul>

In the future, you'll be able to:
<ul>
  <li>
    IMPORTANT, COMING IN THE FIRST RELASE VERSION
    <ul>
      <li>Edit existing accounts</li>
      <li>Pull data from the stock market for your investments (right now this feature is not working)</li>
      <li>Pull data from your live bank accounts for up to date information on your total "disposable" income</li>
      <li>Not put in historical records yourself</li>
    </ul>
  </li>
  <li>
    TRIVIAL, COMING WHEN I CAN
    <ul>
      <li>See analytics for all of your accounts, both individual and as a group</li>
      <li>See information (news ect) related to your investments</li>
      <li>Not wait for those slow python scripts (I hate these but I hate mongo's c++ API more)</li>
    </ul>
  </li>
</ul>

<h2>Build instructions</h2>

NOTE: THIS PROBABLY WILL NOT RUN ON YOUR MACHINE!!!! AS THE SOFTWARE IS CURRENTLY IN ALPHA ALPHA THERE ARE A LOT OF WILD AND WACKY THINGS
      THAT I DID TO MAKE IT SORT OF WORK. <b>THIS WILL BE FIXED LONG BEFORE RELEASE!</b>

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
