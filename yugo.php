<!--      Start the HTML Page with a comment         -->
<!--      Print out the title, etc. and opening tags -->
<html>
<head>
  <title>Welcome to Tong Yu's Serach Engine</title>
  <style>
    input[type=text] {
        width: 40%;
        margin-top:10px;
        margin-bottom:15px;
        border: 3px solid #ccc;
        -webkit-transition: 0.5s;
        transition: 0.5s;
        outline: none;
        font-size: 15px;
        background-image: url('searchicon.png');
        background-position: 10px 10px;
        background-repeat: no-repeat;
        padding: 12px 20px 12px 40px;
    }
    input[type=text]:focus {
        border: 3px solid #555;
    }
    input[type=submit]:hover {
        border: 3px solid #555;
    }
    input[type=submit]{
      background-color: white;
      color: black;
      border: 2px solid #e7e7e7;
      padding: 12px 16px;
      text-decoration: none;
      margin: 8px 4px;
      cursor: pointer;
      font-size:15px;
    }
    .header {
    overflow: hidden;
    background-color: #f1f1f1;
    padding: 0px 10px;
    }

    .header a {
      float: left;
      color: black;
      text-align: center;
      padding: 15px;
      text-decoration: none;
      font-size: 18px;
      line-height: 20px;
      border-radius: 4px;
    }

    .header a.logo {
      font-size: 25px;
      font-weight: bold;
    }

    .header a:hover {
      background-color: #ddd;
      color: black;
    }

    .header-right {
      float: right;
    }

    .center {
        display: block;
        margin-left: auto;
        margin-right: auto;
        width: 50%;
        margin-top: 75px;

    }
    .header a.active {
      background-color: black;
      color: white;
      padding: 5px 5px;
      margin: 10px;

    }

    .footer {
    overflow: hidden;
    background-color: #f1f1f1;
    position: absolute;
    right: 0;
    bottom: 0;
    left: 0;
    width: 100%;
    }

    .center1 {
      text-align: center;
    }
    .pagination {
    display: inline-block;
    }

    .pagination a {
        color: black;
        float: left;
        padding: 8px 16px;
        text-decoration: none;
    }

    .pagination a.active {
        background-color: #808080;
        color: white;
        border-radius: 5px;
    }

    .pagination a:hover:not(.active) {
        background-color: #ddd;
        border-radius: 5px;
    }

    h3 {
      padding-left: 80px;
      padding-bottom: 0px;
      margin-bottom: 0px;
    }
    h4 {
      padding-left: 82px;
      margin-top: 0px;
      padding-bottom: 10px;
    }

  </style>
</head>
<body>
  <div class="header">
  <img class="main-logo" src="2.png" height ="45px"/>
    <div class="header-right">
      <a href="#about">About</a>
      <a href="#more">More</a>
      <a class ="active" href="#sign-in">Sign In</a>
    </div>
  </div>

<!--      Here comes the php portion of the page     -->
<?php

//------------------------------------------------------
// Now a php comment
// This is the main program that either processes the form
// data or prints the form to capture data
//------------------------------------------------------
if (isset($_POST['stage']) && ($_POST['stage'] == 'process'))
{
   process_form();
}
else
{
   print_form();
}

//------------------------------------------------------
// This is the function that prints the form
//------------------------------------------------------
function print_form()
{
echo <<<END
<img class="center" src="3.png"/>
<form action="$_SERVER[PHP_SELF]" method="post">

<center><td><input type="Text" name="userInput" placeholder ="search here">
</td><br></center>

<td><input type="hidden" name="stage" value="process"</td>
<center><td>
  <input type="Submit" name="submit" value="Yugo Search" align="MIDDLE">
  &nbsp;&nbsp;
  <input type="Submit" value="I'm feeling lucky!" align="MIDDLE">
</td></center>

</form>
<div class="footer">
  <center><p>Created by Tong Yu</p></center>
</div>
END;
}

//------------------------------------------------------
// This is the function that processes the form data
//------------------------------------------------------
function process_form()
{
   $userInput = $_POST[userInput];
   //echo "<h2>Username: " . $userInput . "</h2></br>";

   // create the linux command
   $command = './retrieve.exe ' .  $userInput;
   // echo $command;

   // call a compiled program that generated more HTML output
   echo exec ("$command");
}

?>

</body>
</html>
