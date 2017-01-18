<?php
session_start(); /* Starts the session */

if(!isset($_SESSION['UserData']['Username'])){
	header("location:login.php");
	exit;
}

header("Refresh:15");

$light = $_GET['light'];
if($light == "on") {
  $jsonString = file_get_contents('light.json');
  $data = json_decode($jsonString, true);
  $data['light'] = "on";
  $newJsonString = json_encode($data);
  file_put_contents('light.json', $newJsonString);
  redirect('http://www.independentpower.co.za/ESP8266/index.php');
  } 
else if ($light == "off") {
  $jsonString = file_get_contents('light.json');
  $data = json_decode($jsonString, true);
  $data['light'] = "off";
  $newJsonString = json_encode($data);
  file_put_contents('light.json', $newJsonString);
  redirect('http://www.independentpower.co.za/ESP8266/index.php');
}
?>

<?php function redirect($url)
{
    header('Location: '.$url);
    exit();
}
?>
<html>
  <head>      
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    
    <title>ESP8266 Grey Water Pump Control</title>
   
    <script src="https://code.jquery.com/jquery-2.1.4.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/js/bootstrap.min.js"></script>
    <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css" rel="stylesheet">
    <link rel="stylesheet" href="//maxcdn.bootstrapcdn.com/font-awesome/4.3.0/css/font-awesome.min.css">

  </head>
  <body>
   <div class="light-status well col-md-8 col-md-offset-2" style="margin-top: 5px; text-align:center">
          <?php
            $contents = file_get_contents('http://www.independentpower.co.za/ESP8266/light.json');
            $contents = utf8_encode($contents);
            $results = json_decode($contents);
            echo("STATUS: Pump ");
            print $results->{'light'}
          ?>
          
        </div>
    <div class="row" style="margin-top: 20px;">
      <div class="col-md-2 col-md-offset-5">
        <a href="?light=on" class="btn btn-success btn-block btn-lg">Turn On</a>
        <br />
        <a href="?light=off" class="led btn btn-danger btn-block btn-lg">Turn Off</a>
        <br />
      </div>
      </div>
        
      </div>
    </div>
      <div class="row" style="margin-top: 20px;">
      <div class="col-md-2 col-md-offset-5">
    <a href="logout.php" class="led btn btn-default btn-block btn">Click here to Logout </a>.
</div>
      </div>

  </body>
</html>
